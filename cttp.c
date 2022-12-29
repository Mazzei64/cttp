#include"cttp.h"

static const char* TEST_REQ = "POST /auth/authenticate HTTP/1.1\nHost: localhost\nAccept: */*,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate, br\nContent-Type: application/json\nContent-Length: 59\nConnection: keep-alive\n\n{\"userName\":\"5597803327979\",\"password\":\"1896@$!Agija@$!ad\"}";

static string SetStatusLine(const string method, URL* url);
static string SetHeader(OptionList* opts);
static int talk(int sockfd, const struct sockaddr_in* addr,const char* sendMsg, char *restrict recvMsg,  int sendLen, int recvLen);

static const char* REQ_HEADER = "POST /auth/authenticate HTTP/1.1\nHost: localhost:8090\nAccept: */*,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate, br\nConnection: keep-alive\n\n{\"userName\":\"5597803327979\",\"password\":\"1896@$!Agija@$!ad\"}";

string CTTP_GET(OptionList* opts, URL* url, Data* data) {
    const string method = "GET";
    const unsigned int RECV_MSG_LEN = 2048;
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

    char msgReturn[RECV_MSG_LEN];
    memset(msgReturn, 0x00, RECV_MSG_LEN);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(url->port);
    addr.sin_addr.s_addr = inet_addr(url->address);

    int talkRet = talk(sockfd, &addr, request, msgReturn, reqLen, RECV_MSG_LEN);
    if(talkRet == -1) {
        printf("[LOG]Connection failed...\n");
        return NULL;
    }else if (talkRet == -2) {
        printf("[LOG]Failed to send message...\n");
        return NULL;
    }else if (talkRet == -3) {
        printf("[LOG]Failed to read message...\n");
        return NULL;
    }
    
    printf("[LOG]Message returned is: %s\n", msgReturn);
    free(statusLine);
    free(headerStr);
    return NULL;
}

string CTTP_POST(OptionList* opts, URL* url, Data* data) {
    const string method = "POST";
    const unsigned int RECV_MSG_LEN = 2048;
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

    string msgReturn = (string)calloc(RECV_MSG_LEN, sizeof(char));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(url->port);
    addr.sin_addr.s_addr = inet_addr(url->address);
    // set timeout.
    int talkRet = talk(sockfd, &addr, (const char*)request, msgReturn, reqLen, RECV_MSG_LEN);
    if(talkRet == -1) {
        printf("[LOG]Connection failed...\n");
        return NULL;
    }else if (talkRet == -2) {
        printf("[LOG]Failed to send message...\n");
        return NULL;
    }else if (talkRet == -3) {
        printf("[LOG]Failed to read message...\n");
        return NULL;
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
static string SetStatusLine(const string method, URL* url){
    short statusLineLen = 4 + strlen(url->route) + 10;
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
static int talk(int sockfd, const struct sockaddr_in* addr,const char* sendMsg, char *restrict recvMsg,  int sendLen, int recvLen) {
    int connected;
    if((connected = connect(sockfd, (const struct sockaddr*)addr, (socklen_t)sizeof(struct sockaddr_in))) == -1) return -1;
    printf("[LOG]Connection was a success...\n");
    int sendBytes = 0;
    int len = strlen(TEST_REQ);
    if((sendBytes = send(sockfd, sendMsg, sendLen, 0)) < sendLen) return -2;
    printf("[LOG]Message sent with num of bytes: %d\n", sendBytes);
    int readBytes = 0;
    if(read(sockfd, recvMsg, recvLen) <= 0) return -3;
    return 0;
}