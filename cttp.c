#include"cttp.h"

static int talk(int sockfd, const struct sockaddr_in* addr,const char *restrict sendMsg, char *restrict recvMsg,  int sendLen, int recvLen);

static const char* REQ_HEADER = "POST /auth/authenticate HTTP/1.1\nHost: localhost:8090\nAccept: */*,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate, br\nConnection: keep-alive\n\n{\"userName\":\"5597803327979\",\"password\":\"1896@$!Agija@$!ad\"}";

HTTPResponse* CTTP_GET(HTTPRequest* http_req, string url) {
    const string method = "GET";
    // Parse Url and format request's Request Line.
    // Parse the HTTPRequest struct into the header and body, and concatenate to form the final request string.

    const char* msgToSend = "Hi, Pete!\n";
    const int msgToSendLen = strlen(REQ_HEADER);
    char msgReturn[10000];
    memset(msgReturn, 0x00, 10000);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8090);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int talkRet = talk(sockfd, &addr, REQ_HEADER, msgReturn, 12, 1000);
    if(talkRet == -1) {
        printf("[LOG]Connection failed...\n");
        return -1;
    }else if (talkRet == -2) {
        printf("[LOG]Failed to send message...\n");
        return -1;
    }else if (talkRet == -3) {
        printf("[LOG]Failed to read message...\n");
        return -1;
    }
    
    printf("[LOG]Message returned is: %s\n", msgReturn);
    return NULL;
}
static int talk(int sockfd, const struct sockaddr_in* addr,const char *restrict sendMsg, char *restrict recvMsg,  int sendLen, int recvLen) {
    int connected;
    if((connected = connect(sockfd, (const struct sockaddr*)addr, (socklen_t)sizeof(struct sockaddr_in))) == -1) return -1;
    printf("[LOG]Connection was a success...\n");
    int sendBytes = 0;
    if((sendBytes = send(sockfd, sendMsg, sendLen, 0)) < sendLen) return -2;
    printf("[LOG]Message sent with num of bytes: %d\n", sendBytes);
    int readBytes = 0;
    if(read(sockfd, recvMsg, recvLen) <= 0) return -3;
    return 0;
}