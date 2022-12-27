#include"cttp.h";

HTTPResponse* CTTP_GET(HTTPRequest* http_req, string url) {
    const char* msgToSend = "Hi, Pete!\n";
    const int msgToSendLen = 12;
    char msgReturn[1000];
    memset(msgReturn, 0x00, 1000);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int connected;
    if((connected = connect(sockfd, (const struct sockaddr*)&addr, (socklen_t)sizeof(addr))) == -1) {
        printf("[LOG]Connection failed...\n");
        return NULL;
    }
    printf("[LOG]Connection was a success...\n");
    int sendBytes = 0;
    if((sendBytes = send(sockfd, msgToSend, msgToSendLen, 0)) < msgToSendLen) {
        printf("[LOG]Failed to send message...\n");
        return NULL;
    }
    printf("[LOG]Message sent with num of bytes: %d\n", sendBytes);
    int readBytes = 0;
    if((readBytes = read(sockfd, msgReturn, 1000)) <= 0) {
        printf("[LOG]Failed to read message...\n");
        return NULL;
    }
    printf("[LOG]Message returned is: %s\n", msgReturn);
    return NULL;
}