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

#define DEFAULT 0
#define NORAW 1
#define RAWONLY 2

#define localhost "127.0.0.1"

#define DEFAULT_URL_ROUTE "/"
#define DEFAULT_URL_ADDRESS "127.0.0.1"
#define DEFAULT_URL_PORT 80
#define DEFAULT_URL_VERSION 1.1
#define DEFAULT_URL_PROTO HTTP

#define DEFAULT_OPTIONLIST_OPT_NAME "Host"
#define OPTIONLIST_SIZE default_optionslist_size
#define SET_OPTIONLIST_SIZE(size) default_optionslist_size = size
/*s
    Defined types" HTTP/"
*/
typedef unsigned char byte;
typedef char* string;
typedef enum { false = 0, true } bool;
typedef enum { HTTP = 0, HTTPS } http_proto;

/*
    Struct meant for encoding the http address from the url format.
*/
typedef struct {
    http_proto proto;
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
    TEST
*/
typedef struct {
    string statusLine;
    OptionList* responseHeader;
    Data* body;
    string raw;
    unsigned int resLen;
} Response;
/*
    Wrapper methods that call CTTP_REQ
*/
extern Response* CTTP_GET(OptionList* opts, URL* url, Data* data, int flag);
extern Response* CTTP_POST(OptionList* opts, URL* url, Data* data, int flag);
extern Response* CTTP_PUT(OptionList* opts, URL* url, Data* data, int flag);
extern Response* CTTP_DELETE(OptionList* opts, URL* url, Data* data, int flag);

/*
    Main method designed to establish a TCP connection and sending and receiving messages through the HTTP standard.
*/
extern string CTTP_REQ(OptionList* opts, URL* url, Data* data, string method);

/*
    Free Response from Memory.
*/
extern void FreeResponse(Response** response);
/*
    Contructor method for creating an object of the type OptionList.
*/
extern OptionList* NewOptionList();

/*
    Destructor method for creating an object of the type OptionList.
*/
extern void OptionListDestructor(OptionList** optLst);

/*
    OptionList method meant for adding a new Option object to the list.
*/
extern void AddOption(OptionList* optlst, Option* opt);

/*
    OptionList method meant for adding a Option Array of Option objects to the list.
*/
extern void AddOptions(OptionList* optlst, Option* optsArray, int count);

/*
    Constructor method for creating an object of the type Data.
*/
extern Data* NewData(const byte* data);

/*
    Desturctor method for freeing an object of the type Data.
*/
extern void DataDestructor(Data** data);

/*
    Destructor method for freeing an object of the type URL.
*/
extern void UrlDestructor(URL** url);

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

static unsigned int default_optionslist_size = 8;

#endif