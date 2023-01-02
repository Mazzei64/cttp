#include"cttp.h"

static bool timeout = false;

static string SetStatusLine(const string method, URL* url);
static string SetHeader(OptionList* opts);
static int talk(int sockfd, const struct sockaddr_in* addr,const char* sendMsg, char *restrict recvMsg,  int sendLen, int recvLen);

string CTTP_GET(OptionList* opts, URL* url, Data* data) {
    static const string method = "GET";
    return CTTP_REQ(opts, url, data, method);
}

string CTTP_POST(OptionList* opts, URL* url, Data* data) {
    static const string method = "POST";
    return CTTP_REQ(opts, url, data, method);
}

string CTTP_PUT(OptionList* opts, URL* url, Data* data) {
    static const string method = "PUT";
    return CTTP_REQ(opts, url, data, method);
}

string CTTP_DELETE(OptionList* opts, URL* url, Data* data) {
    static const string method = "DELETE";
    return CTTP_REQ(opts, url, data, method);
}

string CTTP_REQ(OptionList* opts, URL* url, Data* data, string method){
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
void AddOption(OptionList* optlst, Option* opt) {
    if(optlst->count == optlst->size)
        optlst->opts = (Option**)realloc(optlst->opts, sizeof(Option*) * (optlst->size + 8));
    optlst->opts[optlst->count] = opt;
    optlst->count = optlst->count + 1;   
}
OptionList* NewOptionList() {
    OptionList* optlst = (OptionList*)calloc(1, sizeof(OptionList));
    optlst->opts = (Option**)calloc(8, sizeof(Option*));
    optlst->size = 8;
    return optlst;
}
Data* NewData(const byte* data) {
    const unsigned int dataLen = strlen(data);
    Data* dt = (Data*)malloc(sizeof(Data));
    dt->data = (byte*)malloc(sizeof(byte) * dataLen);
    strcpy(dt->data, data);
    dt->dataLen = dataLen;
    return dt;
}

/* Auxiliary Functions */
static string SetStatusLine(const string method, URL* url){
    short statusLineLen = strlen(method) + 1 + strlen(url->route) + 10;
    string statusLine = (string)malloc(sizeof(char) * statusLineLen);
    memset(statusLine, 0x00, statusLineLen);
    strcat(statusLine, method);
    strcat(statusLine, " ");
    strcat(statusLine, url->route);
    strcat(statusLine, " HTTP/");
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