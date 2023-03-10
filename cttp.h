/*  Project Name    :           CTTP
*   Version         :           1.0.0
*   Created date    :           02/01/2023
*   Last update     :           02/01/2023
*   Author          :           Bruno Mazzei
*   Description     :           Useful and easy-to-use API for making HTTP requests and handling responses.
*/

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
#include<signal.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<string.h>

/*
    Defined macros
*/
#define getVar(var) #var
#define SET_RES_BUFFER_LEN(new_len) response_buffer_len = new_len
#define RES_BUFFER_LEN response_buffer_len
#define SET_CONNECTION_TIMEOUT(timeout) connection_timeout_seconds = timeout
#define SET_CONNECTION_TIMEOUT_MS(timeout) connection_timeout_microseconds = timeout
#define CONNECTION_TIMEOUT connection_timeout_seconds
#define CONNECTION_TIMEOUT_MS connection_timeout_microseconds

#define SET_MSG_SEND_TIMEOUT(timeout)  msg_send_timeout_seconds = timeout
#define SET_MSG_SEND_TIMEOUT_MS(timeout) msg_send_timeout_microseconds = timeout
#define MSG_SEND_TIMEOUT msg_send_timeout_seconds
#define MSG_SEND_TIMEOUT_MS msg_send_timeout_microseconds

#define SET_MSG_RECV_TIMEOUT(timeout)  msg_recv_timeout_seconds = timeout
#define SET_MSG_RECV_TIMEOUT_MS(timeout) msg_recv_timeout_microseconds = timeout
#define MSG_RECV_TIMEOUT msg_recv_timeout_seconds
#define MSG_RECV_TIMEOUT_MS msg_recv_timeout_microseconds

/*
    Defined types
*/
typedef unsigned char byte;
typedef char* string;
typedef enum { false = 0, true } bool;

/*
    Struct meant for encoding the http address from the url format.
*/
typedef struct {
    string proto;
    string address;
    string route;
    string query;
    unsigned short port;
    float version;
} URL;

/*
    Struct meant for formating each header option.
*/
typedef struct {
    string name;
    string arg;
} Option;

/*
    Struct meant for organizing a list of options.
*/
typedef struct {
    Option** opts;
    unsigned short count;
    unsigned short size;
} OptionList;

/*
    Struct meant for organizing the raw byte stream of data.
*/
typedef struct {
    byte* data;
    unsigned long int dataLen;
} Data;

/*
    Wrapper methods that call CTTP_REQ
*/
extern string CTTP_GET(OptionList* opts, URL* url, Data* data);
extern string CTTP_POST(OptionList* opts, URL* url, Data* data);
extern string CTTP_PUT(OptionList* opts, URL* url, Data* data);
extern string CTTP_DELETE(OptionList* opts, URL* url, Data* data);
/*
    Main method designed to establish a TCP connection and sending and receiving messages through the HTTP standard.
*/
extern string CTTP_REQ(OptionList* opts, URL* url, Data* data, string method);

/*
    Contructor method for creating an object of the type OptionList.
*/
extern OptionList* NewOptionList();
/*
    OptionList method meant for adding a new Option object to the list.
*/
extern void AddOption(OptionList* optlst, Option* opt);

/*
    Constructor method for creating an object of the type Data.
*/
extern Data* NewData(const byte* data);

/*
    Default data variables.
*/
static unsigned long int response_buffer_len = 2048000;

static unsigned short connection_timeout_seconds = 5;
static unsigned int connection_timeout_microseconds = 0;
static unsigned short msg_send_timeout_seconds = 5;
static unsigned int msg_send_timeout_microseconds = 0;
static unsigned short msg_recv_timeout_seconds = 5;
static unsigned int msg_recv_timeout_microseconds = 0;

#endif