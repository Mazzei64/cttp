#ifndef _CTPP_H_
#define _CTPP_H_

/*
    UNIX System Dependecies.
*/
#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>

#define getVar(var) #var

#define SET_RES_BUFFER_LEN(new_len) response_buffer_len = new_len
#define RES_BUFFER_LEN response_buffer_len

typedef unsigned char byte;
typedef char* string;

typedef enum { false = 0, true } bool;

typedef struct {
    string proto;
    string address;
    string route;
    string query;
    unsigned short port;
    float version;
} URL;

typedef struct {
    string name;
    string arg;
} Option;

typedef struct {
    Option** opts;
    unsigned short count;
    unsigned short size;
} OptionList;

typedef struct {
    byte* data;
    unsigned long int dataLen;
} Data;

extern string CTTP_GET(OptionList* opts, URL* url, Data* data);
extern string CTTP_POST(OptionList* opts, URL* url, Data* data);
extern string CTTP_PUT(OptionList* opts, URL* url, Data* data);
extern string CTTP_DELETE(OptionList* opts, URL* url, Data* data);
extern string CTTP_REQ(OptionList* opts, URL* url, Data* data, string method);

extern OptionList* NewOptionList();
extern void AddOption(OptionList* optlst, Option* opt);

extern Data* NewData(const byte* data);

static unsigned long int response_buffer_len = 2048;

#endif