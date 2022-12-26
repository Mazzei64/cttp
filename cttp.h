#ifndef _CTPP_H_
#define _CTPP_H_

typedef unsigned char byte;
typedef char* string;

/*
    Description:
        Standarized HTTP protocol header fields designed for HTTP Requests.
*/
typedef struct {
    /*
    Name:
        A-IM

    Description:
        Acceptable instance-manipulations for the request.
    
    Example:
        A-IM: feed

    Status:
        Permanent

    Standard:
        RFC 3229 (https://datatracker.ietf.org/doc/html/rfc3229)
    */
    string a_im;

    /*
    Name:
        Accept
        
    Description:
        Media type(s) that is/are acceptable for the response. See Content negotiation.
    
    Example:
        Accept: text/html

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string accept;

   /*
    Name:
        Accept-Charset
        
    Description:
        Character sets that are acceptable.
    
    Example:
        Accept-Charset: utf-8

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string acceptCS;

   /*
    Name:
        Accept-Datetime
        
    Description:
        Acceptable version in time.
    
    Example:
        Accept-Datetime: Thu, 31 May 2007 20:35:00 GMT

    Status:
        Provisional

    Standard:
        RFC 7089 (https://datatracker.ietf.org/doc/html/rfc7089)
    */
   string acceptDT;

    /*
    Name:
        Accept-Language
        
    Description:
        List of acceptable human languages for response. See Content negotiation.
    
    Example:
        Accept-Language: en-US

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string acceptLang;

   /*
    Name:
        Access-Control-Request-Method
        
    Description:
        Initiates a request for cross-origin resource sharing with Origin (below).
    
    Example:
        Access-Control-Request-Method: GET

    Status:
        Permanent

    Standard:

    */
   string accessCntrlRqMethod;

   /*
    Name:
        Authorization
        
    Description:
        Authentication credentials for HTTP authentication.
    
    Example:
        Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string authorization;

   /*
    Name:
        Cache-Control
        
    Description:
        Used to specify directives that must be obeyed by all caching mechanisms along the request-response chain.
    
    Example:
        Cache-Control: no-cache

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string cacheControl;

   /*
    Name:
        Connection
        
    Description:
        Control options for the current connection and list of hop-by-hop request fields.
        Must not be used with HTTP/2. 
    
    Example:
        Connection: keep-alive
        Connection: Upgrade

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string connection;

   /*
    Name:
        Content-Encoding
        
    Description:
        The type of encoding used on the data. See HTTP compression.
    
    Example:
        Content-Encoding: gzip

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string contentEncoding;

   /*
    Name:
        Content-Length
        
    Description:
        The length of the request body in octets (8-bit bytes).
    
    Example:
        Content-Length: 348

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string contentLen;

   /*
    Name:
        Content-MD5
        
    Description:
        A Base64-encoded binary MD5 sum of the content of the request body.
    
    Example:
        Content-MD5: Q2hlY2sgSW50ZWdyaXR5IQ==

    Status:
        Obsolete

    Standard:
        RFC 1544 (https://datatracker.ietf.org/doc/html/rfc1544)
        RFC 1864 (https://datatracker.ietf.org/doc/html/rfc1864)
        RFC 4021 (https://datatracker.ietf.org/doc/html/rfc4021)
    */
   string contentMD5;

   /*
    Name:
        Content-MD5
        
    Description:
        he Media type of the body of the request (used with POST and PUT requests).
    
    Example:
        Content-Type: application/x-www-form-urlencoded

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string contentType;

   /*
    Name:
        Cookie
        
    Description:
        An HTTP cookie previously sent by the server with Set-Cookie (below).
    
    Example:
        Cookie: $Version=1; Skin=new;

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string cookie;

   /*
    Name:
        Date
        
    Description:
        The date and time at which the message was originated (in "HTTP-date" format as defined by RFC 9110: HTTP Semantics, section 5.6.7 "Date/Time Formats").
    
    Example:
        Date: Tue, 15 Nov 1994 08:12:31 GMT

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string date;

   /*
    Name:
        Expect
        
    Description:
        Indicates that particular server behaviors are required by the client.
    
    Example:
        Expect: 100-continue

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string expect;

   /*
    Name:
        Forwarded
        
    Description:
        Disclose original information of a client connecting to a web server through an HTTP proxy.
    
    Example:
        Forwarded: for=192.0.2.60;proto=http;by=203.0.113.43 Forwarded: for=192.0.2.43, for=198.51.100.17

    Status:
        Permanent

    Standard:
        RFC 7239 (https://datatracker.ietf.org/doc/html/rfc7239)
    */
   string forwarded;

   /*
    Name:
        From
        
    Description:
        The email address of the user making the request.
    
    Example:
        From: user@example.com

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string from;

   /*
    Name:
        Host
        
    Description:
        The domain name of the server (for virtual hosting), and the TCP port number on which the server is listening. The port number may be omitted if the port is the standard port for the service requested.
        
        Mandatory since HTTP/1.1. If the request is generated directly in HTTP/2, it should not be used.
    
    Example:
        Host: en.wikipedia.org:8080
        Host: en.wikipedia.org 

    Status:

    Standard:

    */
   string host;

   /*
    Name:
        HTTP2-Settings
        
    Description:
        A request that upgrades from HTTP/1.1 to HTTP/2 MUST include exactly one HTTP2-Setting header field. The HTTP2-Settings header field is a connection-specific header field that includes parameters that govern the HTTP/2 connection, provided in anticipation of the server accepting the request to upgrade.
    
    Example:
        HTTP2-Settings: token64

    Status:
        Permanent: standard

    Standard:

    */
   string HTTP2Settings ;

    /*
    Name:
        If-Match
        
    Description:
        Only perform the action if the client supplied entity matches the same entity on the server. This is mainly for methods like PUT to only update a resource if it has not been modified since the user last updated it.
    
    Example:
        If-Match: "737060cd8c284d8af7ad3082f209582d"

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string ifMatch;

   /*
    Name:
        If-Modified-Since
        
    Description:
        Allows a 304 Not Modified to be returned if content is unchanged.
    
    Example:
        If-Modified-Since: Sat, 29 Oct 1994 19:43:31 GMT

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string ifModifiedSince;

   /*
    Name:
        If-None-Match
        
    Description:
       Allows a 304 Not Modified to be returned if content is unchanged, see HTTP ETag.
    
    Example:
        If-None-Match: "737060cd8c284d8af7ad3082f209582d"

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string ifNoneMatch;

   /*
    Name:
        If-Range
        
    Description:
       If the entity is unchanged, send me the part(s) that I am missing; otherwise, send me the entire new entity.
    
    Example:
        If-None-Match: "737060cd8c284d8af7ad3082f209582d"

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string ifRange;

   /*
    Name:
        If-Unmodified-Since
        
    Description:
       Only send the response if the entity has not been modified since a specific time.
    
    Example:
        If-Unmodified-Since: Sat, 29 Oct 1994 19:43:31 GMT

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string ifUnmodifiedSince;

   /*
    Name:
        Max-Forwards
        
    Description:
       Limit the number of times the message can be forwarded through proxies or gateways.
    
    Example:
        Max-Forwards: 10

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string maxForwards;

   /*
    Name:
        Origin
        
    Description:
       Initiates a request for cross-origin resource sharing (asks server for Access-Control-* response fields).
    
    Example:
        Origin: http://www.example-social-network.com

    Status:
        Permanent: standard


    Standard:
        RFC 6454 (https://datatracker.ietf.org/doc/html/rfc6454)
    */
   string origin;

   /*
    Name:
        Pragma
        
    Description:
       Implementation-specific fields that may have various effects anywhere along the request-response chain.
    
    Example:
        Pragma: no-cache

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string pragma;

   /*
    Name:
        Prefer
        
    Description:
       Allows client to request that certain behaviors be employed by a server while processing a request. 
    
    Example:
        Prefer: return=representation

    Status:
        Permanent

    Standard:
        RFC 7240 (https://datatracker.ietf.org/doc/html/rfc7240)
    */
   string prefer;

   /*
    Name:
        Range
        
    Description:
       Request only part of an entity. Bytes are numbered from 0. See Byte serving.
    
    Example:
        Range: bytes=500-999

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string range;

   /*
    Name:
        Referer
        
    Description:
       This is the address of the previous web page from which a link to the currently requested page was followed. (The word "referrer" has been misspelled in the RFC as well as in most implementations to the point that it has become standard usage and is considered correct terminology)
    
    Example:
        Referer: http://en.wikipedia.org/wiki/Main_Page

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string referer;

   /*
    Name:
        TE
        
    Description:
       The transfer encodings the user agent is willing to accept: the same values as for the response header field Transfer-Encoding can be used, plus the "trailers" value (related to the "chunked" transfer method) to notify the server it expects to receive additional fields in the trailer after the last, zero-sized, chunk.
       
       Only trailers is supported in HTTP/2.
    
    Example:
        TE: trailers, deflate

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string te;

   /*
    Name:
        Trailer
        
    Description:
       The Trailer general field value indicates that the given set of header fields is present in the trailer of a message encoded with chunked transfer coding.
    
    Example:
        Trailer: Max-Forwards

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string trailer;

   /*
    Name:
        Transfer-Encoding 
        
    Description:
       The form of encoding used to safely transfer the entity to the user. Currently defined methods are: chunked, compress, deflate, gzip, identity.
       
       Must not be used with HTTP/2.
    
    Example:
        Transfer-Encoding: chunked

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string transferEncoding;

   /*
    Name:
        User-Agent 
        
    Description:
        The user agent string of the user agent.
    
    Example:
        User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0s

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string userAgent;

   /*
    Name:
        Upgrade 
        
    Description:
        Ask the server to upgrade to another protocol.
        
        Must not be used in HTTP/2.[14] 
    
    Example:
        Upgrade: h2c, HTTPS/1.3, IRC/6.9, RTA/x11, websocket

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string upgrade;

   /*
    Name:
        Via 
        
    Description:
        Informs the server of proxies through which the request was sent.
    
    Example:
        Via: 1.0 fred, 1.1 example.com (Apache/1.1)

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string via;

   /*
    Name:
        Warning 
        
    Description:
        A general warning about possible problems with the entity body.
    
    Example:
        Warning: 199 Miscellaneous warning

    Status:
        Obsolete

    Standard:
        RFC 7234 (https://datatracker.ietf.org/doc/html/rfc7234)
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string warning;

} StandardRequest;

/*
    Description:
        Non-standarized HTTP protocol header fields designed for HTTP Requests.
*/
typedef struct {

    /*
        ...
    */

} NonStandardRequest;

/*
    Description:
        Main struct for formatting the HTTP Header for HTTP requests, following the pre-requisited documented standards necessary.
*/
typedef struct {
    StandardRequest strq;
    NonStandardRequest nstrq;
} HTTPRequestHeader;


#endif