#include"cttp.h"

static bool timeout = false;

static void EncodeStatusLine(string* statusLine, string response, int* count);
static void StringToOption(Option** opt, string optStr);
static void EncodeResHeader(OptionList** optLst, string response, int* count);
static void EncodeBody(Data** body, string response, int* count);
static Response* EncodeResponse(string response, int flag);
static string SetStatusLine(const string method, URL* url);
static string SetHeader(OptionList* opts);
static int talk(int sockfd, const struct sockaddr_in* addr,const char* sendMsg, char *restrict recvMsg,  int sendLen, int recvLen);

Response* CTTP_GET(OptionList* opts, URL* url, Data* data, int flag) {
    static const string method = "GET";
    string response = CTTP_REQ(opts, url, data, method);
    return EncodeResponse(response, flag);
}
Response* CTTP_POST(OptionList* opts, URL* url, Data* data, int flag) {
    static const string method = "POST";
    string response = CTTP_REQ(opts, url, data, method);
    return EncodeResponse(response, flag);
}
Response* CTTP_PUT(OptionList* opts, URL* url, Data* data, int flag) {
    static const string method = "PUT";
    string response = CTTP_REQ(opts, url, data, method);
    return EncodeResponse(response, flag);
}
Response* CTTP_DELETE(OptionList* opts, URL* url, Data* data, int flag) {
    static const string method = "DELETE";
    string response = CTTP_REQ(opts, url, data, method);
    return EncodeResponse(response, flag);
}

string CTTP_REQ(OptionList* opts, URL* url, Data* data, string method) {
    char _route[2], _address[10];
    if(url == NULL) {
        URL _url;
        memset(&_url, 0x00, sizeof(URL));
        url = &_url;
    }
    if(url->route == NULL) {
        memset(_route, 0x00, 2);
        strncpy(_route, "/", 1);
        url->route = _route;
    }
    if(url->address == NULL) {
        memset(_address, 0x00, 10);
        strncpy(_address, DEFAULT_URL_ADDRESS, sizeof(char) * 9);
        url->address = _address;
    }
    if(url->port == 0)
        url->port = DEFAULT_URL_PORT;
    if(url->version == 0)
        url->version = DEFAULT_URL_VERSION;
    
    string statusLine = SetStatusLine(method, url);
    string headerStr = SetHeader(opts);
    unsigned int reqLen = 0;
    if(data != NULL)
       reqLen = strlen(statusLine) + strlen(headerStr) + data->dataLen;
    else
        reqLen = strlen(statusLine) + strlen(headerStr);

    char request[reqLen];
    memset(request, 0x00, reqLen);
    strcat(request, statusLine);
    strcat(request, headerStr);
    if(data != NULL) strcat(request, (string)data->data);

    string msgReturn = (string)calloc(RES_BUFFER_LEN, sizeof(char));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(url->port);
    addr.sin_addr.s_addr = inet_addr(url->address);
    
    int talkRet = talk(sockfd, &addr, (const char*)request, msgReturn, reqLen, RES_BUFFER_LEN);
    if(talkRet == -1) {
        const string connection_timeout_msg = "Connection failed...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }else if (talkRet == -2) {
        const string connection_timeout_msg = "Failed to send message...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }else if (talkRet == -3) {
        const string connection_timeout_msg = "Failed to read message...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }else if (talkRet == -4) {
        const string connection_timeout_msg = "Connection timeout...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }else if (talkRet == -5) {
        const string connection_timeout_msg = "Request timeout...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }else if (talkRet == -6) {
        const string connection_timeout_msg = "[LOG]Response timeout...\n";
        printf("[LOG]%s", connection_timeout_msg);
        strcpy(msgReturn, connection_timeout_msg);
        return msgReturn;
    }   
    free(statusLine);
    free(headerStr);
    return msgReturn;
}
void FreeResponse(Response** response) {
    if(*response == NULL) return;
    if((*response)->statusLine != NULL) {
        free((*response)->statusLine); 
        (*response)->statusLine = NULL;
    }
    if((*response)->responseHeader != NULL)
        OptionListDestructor(&((*response)->responseHeader));

    if((*response)->body != NULL)
        DataDestructor(&((*response)->body));

    if((*response)->raw != NULL) {
        free((*response)->raw);
        (*response)->raw = NULL;
        (*response)->resLen = 0;
    }
    free(*response);
    *response = NULL;
}
void AddOption(OptionList* optlst, Option* opt) {
    if(optlst == NULL || opt == NULL) return;
    if(optlst->count == optlst->size) {
        optlst->size += 8;
        optlst->opts = (Option**)realloc(optlst->opts, sizeof(Option*) * optlst->size);
    }
    optlst->opts[optlst->count] = opt;
    optlst->count = optlst->count + 1;   
}
void AddOptions(OptionList* optlst, Option* optsArray, int count) {
    for (size_t i = 0; i < count; i++) {
        AddOption(optlst, &optsArray[i]);
    }
}
OptionList* NewOptionList() {
    OptionList* optlst = (OptionList*)calloc(1, sizeof(OptionList));
    optlst->opts = (Option**)calloc(8, sizeof(Option*));
    optlst->size = 8;
    return optlst;
}
void OptionListDestructor(OptionList** optLst) {
    if(*optLst == NULL) return;
    register unsigned long int _rsp asm ("rsp");
    for (size_t i = 0; i < (*optLst)->count; i++) {
        if((unsigned long int)(((*optLst)->opts[i])) < _rsp) {
            free((*optLst)->opts[i]->name);
            free((*optLst)->opts[i]->arg);
            free((*optLst)->opts[i]);
            (*optLst)->opts[i] = NULL;
        }
    }
    free((*optLst)->opts);
    (*optLst)->opts = NULL;
    free(*optLst);
    *optLst = NULL;
}
Data* NewData(const byte* data) {
    if(data == NULL) return NULL;
    const unsigned int dataLen = strlen(data);
    Data* dt = (Data*)malloc(sizeof(Data));
    dt->data = (byte*)malloc(sizeof(byte) * dataLen);
    strcpy(dt->data, data);
    dt->dataLen = dataLen;
    return dt;
}
void DataDestructor(Data** data) {
    if(*data == NULL) return;
    memset((*data)->data, 0x00, (*data)->dataLen);
    free((*data)->data);
    memset(*data, 0x00, sizeof(Data));
    free(*data);
    (*data) = NULL;
}
/* Auxiliary Functions */
static void EncodeStatusLine(string* statusLine, string response, int* count) {
    while (response[*count] != '\n') (*count)++;
    (*count)++;
    (*statusLine) = (string)malloc(sizeof(char) * (*count));
    for (short i = 0; i < *count; i++)
        (*statusLine)[i] = response[i];
}
static void StringToOption(Option** opt, string optStr) {
    int count = 0, bufferIndex = 0;
    (*opt)->name = (string)calloc(24, sizeof(char));
    while (optStr[count] != ':') {
        (*opt)->name[bufferIndex] = optStr[count];
        bufferIndex++;
        count++;
    }
    count+=2;
    bufferIndex = 0;
    (*opt)->arg = (string)calloc(512, sizeof(char));
    while (optStr[count] != '\n') {
        (*opt)->arg[bufferIndex] = optStr[count];
        bufferIndex++;
        count++;
    }   
}
static void EncodeResHeader(OptionList** optLst, string response, int* count) {
    int lineLen = 0;
    char headerOptBuffer[1024];
    memset(headerOptBuffer, 0x00, 1024);
    *optLst = (OptionList*)calloc(1, sizeof(OptionList));
    for(;;){
        while (response[*count] != '\n') {
            headerOptBuffer[lineLen] = response[*count];
            lineLen++;
            (*count)++;
        }
        headerOptBuffer[lineLen] = response[*count];
        (*count)++;
        Option* option = (Option*)malloc(sizeof(Option));
        StringToOption(&option, headerOptBuffer);
        AddOption(*optLst, option);
        memset(headerOptBuffer, 0x00, 1024);
        if(response[*count] == '\n' || (response[*count] == '\r' && response[*(count) + 1] == '\n')) {
            if(response[*count] == '\r' && response[*(count) + 1] == '\n') (*count) += 2;
            else (*count)++;
            break;
        }
        lineLen = 0;
    }
}
static void EncodeBody(Data** body, string response, int* count) {
    int dataIndex = 0, dataSize = 1024;
    *body = (Data*)calloc(1, sizeof(Data));
    (*body)->data = (byte*)calloc(dataSize, sizeof(char));
    while (response[*count] != '\0') {
        (*body)->data[dataIndex] = response[*count];
        dataIndex++;
        (*count)++;
        if(dataIndex + 1 == dataSize) {
            (*body)->data = (byte*)realloc((*body)->data, dataSize * 2);
            dataSize *= 2;
        }
    }
    (*body)->dataLen = dataIndex + 1;
}
static Response* EncodeResponse(string response, int flag) {
    int count = 0;
    Response* res = (Response*)calloc(1, sizeof(Response));
    if(flag == DEFAULT){
        EncodeStatusLine(&res->statusLine, response, &count);
        EncodeResHeader(&res->responseHeader, response, &count);
        EncodeBody(&(res->body), response, &count);
        res->raw = (string)malloc(sizeof(char) * count);
        strncpy(res->raw, response, count);
        res->resLen = count;
    }
    else  if(flag == NORAW) {
        EncodeStatusLine(&res->statusLine, response, &count);
        EncodeResHeader(&res->responseHeader, response, &count);
        EncodeBody(&res->body, response, &count);
    }
    else  if(flag == RAWONLY) {
        count = strlen(response);
        res->raw = (string)malloc(sizeof(char) * count);
        strncpy(res->raw, response, count);
        res->resLen = count;
    }
    return res;
} 
static string SetStatusLine(const string method, URL* url){
    short statusLineLen;
    char statusLineProto[7];
    memset(statusLineProto, 0x00, sizeof(char) * 7);
    if(url->proto != HTTP && url->proto != HTTPS) url->proto = HTTP;
    if(url->proto == HTTP) {
        statusLineLen = strlen(method) + 1 + strlen(url->route) + 10;
        strncpy(statusLineProto, " HTTP/", 6);
    }
    else if(url->proto == HTTPS) {
        statusLineLen = strlen(method) + 1 + strlen(url->route) + 11;
        strncpy(statusLineProto, " HTTPS/", 7);
    }
    string statusLine;
    if(url->route[0] != '/') {
        statusLine++;
        statusLine = (string)malloc(sizeof(char) * statusLineLen);
        memset(statusLine, 0x00, statusLineLen);
        strcat(statusLine, method);
        strcat(statusLine, " /");
    }
    else {
        statusLine = (string)malloc(sizeof(char) * statusLineLen);
        memset(statusLine, 0x00, statusLineLen);
        strcat(statusLine, method);
        strcat(statusLine, " ");
    }
    strcat(statusLine, url->route);
    strcat(statusLine, statusLineProto);
    char versionCntrl[5];
    memset(versionCntrl, 0x00, 5);
    sprintf(versionCntrl, "%.1f\n", url->version);
    strcat(statusLine, versionCntrl);
    return statusLine;
}
static string SetHeader(OptionList* opts) {
    unsigned int headerStrLen = 0;
    for (int i = 0; i < opts->count; i++) {
        headerStrLen += strlen(opts->opts[i]->name) + 2 + strlen(opts->opts[i]->arg) + 1;
    }
    string headerStr = (string)calloc(headerStrLen + 1 ,sizeof(char));
    for (int i = 0; i < opts->count; i++) {
        strcat(headerStr, opts->opts[i]->name);
        strcat(headerStr, ": ");
        strcat(headerStr, opts->opts[i]->arg);
        strcat(headerStr, "\n");
    }
    strcat(headerStr, "\n");
    return headerStr;
}
static void TimeOut(int sig) {
    timeout = true;
}
static int talk(int sockfd, const struct sockaddr_in* addr,const char* sendMsg, char *restrict recvMsg,  int sendLen, int recvLen) {
    struct itimerval timer, oldtimer;
    struct sigaction handler;
    memset(&timer, 0x00, sizeof(struct itimerval));
    memset(&oldtimer, 0x00, sizeof(struct itimerval));
    memset(&handler, 0x00, sizeof(struct sigaction));
    handler.sa_handler = TimeOut;
    handler.sa_flags = 0;
    sigfillset(&handler.sa_mask);
    sigaction(SIGALRM, &handler, 0);
    timer.it_value.tv_sec = CONNECTION_TIMEOUT;
    timer.it_value.tv_usec = CONNECTION_TIMEOUT_MS;
    printf("[LOG]Attempting connnection with: %s\n", inet_ntoa(addr->sin_addr));
    setitimer(ITIMER_REAL, &timer, &oldtimer);
    int connected;
    if((connected = connect(sockfd, (const struct sockaddr*)addr, (socklen_t)sizeof(struct sockaddr_in))) == -1) {
        if(timeout == true) return -4;
        return -1;
    }
    printf("[LOG]Connection established with success.\n");
    setitimer(ITIMER_REAL, &oldtimer, NULL);
    timer.it_value.tv_sec = MSG_SEND_TIMEOUT;
    timer.it_value.tv_usec = MSG_SEND_TIMEOUT_MS;
    setitimer(ITIMER_REAL, &timer, &oldtimer);
    int sendBytes = 0;
    if((sendBytes = send(sockfd, sendMsg, sendLen, 0)) < sendLen) {
        if(timeout == true) return -5;
        return -2;
    }
    printf("[LOG]Message sent with num of bytes: %d\n", sendBytes);
    setitimer(ITIMER_REAL, &oldtimer, NULL);
    timer.it_value.tv_sec = MSG_RECV_TIMEOUT;
    timer.it_value.tv_usec = MSG_RECV_TIMEOUT_MS;
    setitimer(ITIMER_REAL, &timer, &oldtimer);
    int readBytes = 0;
    if(read(sockfd, recvMsg, recvLen) <= 0) {
        if(timeout == true) return -6;
        return -3;
    }
    setitimer(ITIMER_REAL, &oldtimer, NULL);
    return 0;
}