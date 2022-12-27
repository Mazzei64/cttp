#ifndef _CTPP_H_
#define _CTPP_H_

/*
    UNIX System Dependecies.
*/
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>

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
    Name:
        Upgrade-Insecure-Requests 
        
    Description:
        Tells a server which (presumably in the middle of a HTTP -> HTTPS migration) hosts mixed content that the client would prefer redirection to HTTPS and can handle Content-Security-Policy: upgrade-insecure-requests.
        
        Must not be used with HTTP/2
    
    Example:
        Upgrade-Insecure-Requests: 1

    */
   string upgradeInsecureReqs;

   /*
    Name:
        X-Requested-With
        
    Description:
        Mainly used to identify Ajax requests (most JavaScript frameworks send this field with value of XMLHttpRequest); also identifies Android apps using WebView
    
    Example:
        X-Requested-With: XMLHttpRequest

    */
   string XRequestedWith;

   /*
    Name:
        DNT
        
    Description:
        Requests a web application to disable their tracking of a user. This is Mozilla's version of the X-Do-Not-Track header field (since Firefox 4.0 Beta 11). Safari and IE9 also have support for this field. On March 7, 2011, a draft proposal was submitted to IETF. The W3C Tracking Protection Working Group is producing a specification.
    
    Example:
        DNT: 1 (Do Not Track Enabled)
        DNT: 0 (Do Not Track Disabled) 

    */
   string dnt;

   /*
    Name:
        X-Forwarded-For
        
    Description:
        A de facto standard for identifying the originating IP address of a client connecting to a web server through an HTTP proxy or load balancer. Superseded by Forwarded header.
    
    Example:
        X-Forwarded-For: client1, proxy1, proxy2
        X-Forwarded-For: 129.78.138.66, 129.78.64.103 

    */
   string XForwardedFor;

   /*
    Name:
        X-Forwarded-Host
        
    Description:
        A de facto standard for identifying the original host requested by the client in the Host HTTP request header, since the host name and/or port of the reverse proxy (load balancer) may differ from the origin server handling the request. Superseded by Forwarded header.
    
    Example:
        X-Forwarded-Host: en.wikipedia.org:8080
        X-Forwarded-Host: en.wikipedia.org 

    */
   string XForwardedHost;

   /*
    Name:
        X-Forwarded-Proto
        
    Description:
        A de facto standard for identifying the originating protocol of an HTTP request, since a reverse proxy (or a load balancer) may communicate with a web server using HTTP even if the request to the reverse proxy is HTTPS. An alternative form of the header (X-ProxyUser-Ip) is used by Google clients talking to Google servers. Superseded by Forwarded header.
    
    Example:
        X-Forwarded-Proto: https

    */
   string XForwardedProto;

   /*
    Name:
        Front-End-Https
        
    Description:
        Non-standard header field used by Microsoft applications and load-balancers
    
    Example:
        Front-End-Https: on

    */
   string frontEndHttps;

   /*
    Name:
        X-Http-Method-Override
        
    Description:
        Requests a web application to override the method specified in the request (typically POST) with the method given in the header field (typically PUT or DELETE). This can be used when a user agent or firewall prevents PUT or DELETE methods from being sent directly (note that this is either a bug in the software component, which ought to be fixed, or an intentional configuration, in which case bypassing it may be the wrong thing to do).
    
    Example:
        X-HTTP-Method-Override: DELETE

    */
   string XHttpMethodOverride;

   /*
    Name:
        X-ATT-DeviceId
        
    Description:
        Allows easier parsing of the MakeModel/Firmware that is usually found in the User-Agent String of AT&T Devices
    
    Example:
        X-Att-Deviceid: GT-P7320/P7320XXLPG

    */
   string XAttDeviceld;

   /*
    Name:
        X-Wap-Profile
        
    Description:
        Links to an XML file on the Internet with a full description and details about the device currently connecting. In the example to the right is an XML file for an AT&T Samsung Galaxy S2.
    
    Example:
        x-wap-profile: http://wap.samsungmobile.com/uaprof/SGH-I777.xml

    */
   string XWrapProfile;

   /*
    Name:
        Proxy-Connection
        
    Description:
        Implemented as a misunderstanding of the HTTP specifications. Common because of mistakes in implementations of early HTTP versions. Has exactly the same functionality as standard Connection field.
        
        Must not be used with HTTP/2.
    
    Example:
        Proxy-Connection: keep-alive

    */
   string proxyConnection;

   /*
    Name:
        X-UIDH
        
    Description:
        Server-side deep packet insertion of a unique ID identifying customers of Verizon Wireless; also known as "perma-cookie" or "supercookie"
    
    Example:
        X-UIDH: ...

    */
   string Xuidh;

   /*
    Name:
        X-Csrf-Token
        
    Description:
        Used to prevent cross-site request forgery. Alternative header names are: X-CSRFToken[40] and X-XSRF-TOKEN
    
    Example:
        X-Csrf-Token: i8XNjC4b8KVok4uw5RftR38Wgp2BFwql

    */
   string XCsrfToken;

   /*
    Name:
        X-Request-ID, X-Correlation-ID, Correlation-ID 
        
    Description:
        Correlates HTTP requests between a client and server.
    
    Example:
        X-Request-ID: f058ebd6-02f7-4d3f-942e-904344e8cde5

    */
   string XReqID;

   /*
    Name:
        Save-Data 
        
    Description:
        The Save-Data client hint request header available in Chrome, Opera, and Yandex browsers lets developers deliver lighter, faster applications to users who opt-in to data saving mode in their browser. 
    
    Example:
        Save-Data: on

    */
   string XReqID;

} NonStandardRequest;

/*
    Description:
        Main struct for formatting the HTTP Header for HTTP requests, following the pre-requisited documented standards necessary.
*/
typedef struct {
    StandardRequest strq;
    NonStandardRequest nstrq;
} HTTPRequestHeader;

typedef struct {

    /*
    Name:
        Accept-CH 
        
    Description:
        Requests HTTP Client Hints
    
    Example:
        Accept-CH: UA, Platform

    Status:
        Experimental

    Standard:
        RFC 8942 (https://datatracker.ietf.org/doc/html/rfc8942)
    */
   string acceptCH;

   /*
    Name:
        Accept-CH 
        
    Description:
        Requests HTTP Client Hints
    
    Example:
        Accept-CH: UA, Platform

    Status:
        Experimental

    Standard:
        RFC 8942 (https://datatracker.ietf.org/doc/html/rfc8942)
    */
   string acceptCH;

   /*
    Name:
        Access-Control-Allow-Origin,
        Access-Control-Allow-Credentials,
        Access-Control-Expose-Headers,
        Access-Control-Max-Age,
        Access-Control-Allow-Methods,
        Access-Control-Allow-Headers 
        
    Description:
        Specifying which web sites can participate in cross-origin resource sharing
    
    Example:
        Access-Control-Allow-Origin: *

    Status:
        Permanent: standard

    Standard:
        RFC 7480 (https://datatracker.ietf.org/doc/html/rfc7480)
    */
   string allowInCrossOrigin;

   /*
    Name:
        Accept-Patch 
        
    Description:
        Specifies which patch document formats this server supports
    
    Example:
        Accept-Patch: text/example;charset=utf-8

    Status:
        Permanent

    Standard:
        RFC 5789 (https://datatracker.ietf.org/doc/html/rfc5789)
    */
   string acceptPath;

   /*
    Name:
        Accept-Ranges 
        
    Description:
        What partial content range types this server supports via byte serving
    
    Example:
        Accept-Ranges: bytes

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string acceptRanges;

   /*
    Name:
        Age 
        
    Description:
        The age the object has been in a proxy cache in seconds
    
    Example:
        Age: 12

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string age;

   /*
    Name:
        Allow 
        
    Description:
        Valid methods for a specified resource. To be used for a 405 Method not allowed
    
    Example:
        Allow: GET, HEAD

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string allow;

   /*
    Name:
        Alt-Svc 
        
    Description:
        A server uses "Alt-Svc" header (meaning Alternative Services) to indicate that its resources can also be accessed at a different network location (host or port) or using a different protocol
        
        When using HTTP/2, servers should instead send an ALTSVC frame.
    
    Example:
        Alt-Svc: http/1.1="http2.example.com:8001"; ma=7200

    Status:
        Permanent

    Standard:
        
    */
   string altSvc;

   /*
    Name:
        Cache-Control
        
    Description:
        Control options for the current connection and list of hop-by-hop response fields.
        
        Must not be used with HTTP/2.
    
    Example:
        Connection: close

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string cacheCtrl;

   /*
    Name:
        Content-Disposition
        
    Description:
        An opportunity to raise a "File Download" dialogue box for a known MIME type with binary format or suggest a filename for dynamic content. Quotes are necessary with special characters.
    
    Example:
        Content-Disposition: attachment; filename="fname.ext"

    Status:
        Permanent

    Standard:
        RFC 2616 (https://datatracker.ietf.org/doc/html/rfc2616)
        RFC 4021 (https://datatracker.ietf.org/doc/html/rfc4021)
        RFC 6266 (https://datatracker.ietf.org/doc/html/rfc6266)
        
    */
   string contentDisposition;

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
        Content-Language
        
    Description:
        The natural language or languages of the intended audience for the enclosed content
    
    Example:
        Content-Language: da

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string contentLanguage;

   /*
    Name:
        Content-Length
        
    Description:
        The length of the response body in octets (8-bit bytes)
    
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
        Content-Location
        
    Description:
        An alternate location for the returned data
    
    Example:
        Content-Location: /index.htm

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
        Content-Range
        
    Description:
        Where in a full body message this partial message belongs
    
    Example:
        Content-Range: bytes 21010-47021/47022

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string contentRange;

   /*
    Name:
        Content-Type
        
    Description:
        The MIME type of this content
    
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
        Date
        
    Description:
        The date and time that the message was sent (in "HTTP-date" format as defined by RFC 9110)
    
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
        Delta-Base
        
    Description:
        Specifies the delta-encoding entity tag of the response.
    
    Example:
        Delta-Base: "abc"

    Status:
        Permanent

    Standard:
        RFC 3229 (https://datatracker.ietf.org/doc/html/rfc3229)
    */
   string deltaBase;

   /*
    Name:
        ETag
        
    Description:
        An identifier for a specific version of a resource, often a message digest
    
    Example:
        ETag: "737060cd8c284d8af7ad3082f209582d"

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string eTag;

   /*
    Name:
        Expires
        
    Description:
        Gives the date/time after which the response is considered stale (in "HTTP-date" format as defined by RFC 9110)
    
    Example:
        Expires: Thu, 01 Dec 1994 16:00:00 GMT

    Status:
        Permanent

    Standard:
        RFC 9111 (https://datatracker.ietf.org/doc/html/rfc9111)
    */
   string expires;

   /*
    Name:
        IM
        
    Description:
        Instance-manipulations applied to the response.
    
    Example:
        IM: feed

    Status:
        Permanent

    Standard:
        RFC 3229 (https://datatracker.ietf.org/doc/html/rfc3229)
    */
   string im;

   /*
    Name:
        Last-Modified
        
    Description:
        The last modified date for the requested object (in "HTTP-date" format as defined by RFC 9110)
    
    Example:
        Last-Modified: Tue, 15 Nov 1994 12:45:26 GMT

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string lastModified;

   /*
    Name:
        Link
        
    Description:
        Used to express a typed relationship with another resource, where the relation type is defined by RFC 5988
    
    Example:
        Link: </feed>; rel="alternate"

    Status:
        Permanent

    Standard:
        RFC 5988 (https://datatracker.ietf.org/doc/html/rfc5988)
    */
   string link;

   /*
    Name:
        Location
        
    Description:
        Used in redirection, or when a new resource has been created.
    
    Example:
        Example 1: Location: http://www.w3.org/pub/WWW/People.html
        Example 2: Location: /pub/WWW/People.html

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
    */
   string location;

   /*
    Name:
        P3P
        
    Description:
        This field is supposed to set P3P policy, in the form of P3P:CP="your_compact_policy". However, P3P did not take off, most browsers have never fully implemented it, a lot of websites set this field with fake policy text, that was enough to fool browsers the existence of P3P policy and grant permissions for third party cookies.
    
    Example:
        P3P: CP="This is not a P3P policy! See https://en.wikipedia.org/wiki/Special:CentralAutoLogin/P3P for more info."

    Status:
        Permanent

    Standard:
        
    */
   string p3p;

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
        Preference-Applied 
        
    Description:
        Indicates which Prefer tokens were honored by the server and applied to the processing of the request.
    
    Example:
        Preference-Applied: return=representation

    Status:
        Permanent

    Standard:
        RFC 7240 (https://datatracker.ietf.org/doc/html/rfc7240)
        
    */
   string preferenceApplied;

   /*
    Name:
        Proxy-Authenticate 
        
    Description:
        Request authentication to access the proxy.
    
    Example:
        Proxy-Authenticate: Basic

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string proxyAuth;

   /*
    Name:
        Public-Key-Pins
        
    Description:
        HTTP Public Key Pinning, announces hash of website's authentic TLS certificate
    
    Example:
        Public-Key-Pins: max-age=2592000; pin-sha256="E9CZ9INDbd+2eRQozYqqbQ2yXLVKB9+xcprMF+44U1g=";

    Status:
        Permanent

    Standard:
        RFC 7469 (https://datatracker.ietf.org/doc/html/rfc7469)
        
    */
   string publicKeyPins;

   /*
    Name:
        Retry-After
        
    Description:
        If an entity is temporarily unavailable, this instructs the client to try again later. Value could be a specified period of time (in seconds) or a HTTP-date.
    
    Example:
        Example 1: Retry-After: 120
        Example 2: Retry-After: Fri, 07 Nov 2014 23:59:59 GMT

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string retryAfter;

   /*
    Name:
        Server
        
    Description:
        A name for the server
    
    Example:
        Server: Apache/2.4.1 (Unix)

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string server;

   /*
    Name:
        Set-Cookie
        
    Description:
        An HTTP cookie
    
    Example:
        Set-Cookie: UserID=JohnDoe; Max-Age=3600; Version=1

    Status:
        Permanent: standard

    Standard:
        RFC 6265 (https://datatracker.ietf.org/doc/html/rfc6265)
        
    */
   string setCookie;

   /*
    Name:
        Strict-Transport-Security
        
    Description:
        A HSTS Policy informing the HTTP client how long to cache the HTTPS only policy and whether this applies to subdomains.
    
    Example:
        Strict-Transport-Security: max-age=16070400; includeSubDomains

    Status:
        Permanent: standard

    Standard:
        
    */
   string hsts;

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
        Tk
        
    Description:
        Tracking Status header, value suggested to be sent in response to a DNT(do-not-track), possible values:

        "!" — under construction
        "?" — dynamic
        "G" — gateway to multiple parties
        "N" — not tracking
        "T" — tracking
        "C" — tracking with consent
        "P" — tracking only if consented
        "D" — disregarding DNT
        "U" — updated
    
    Example:
        Tk: ?

    Status:
        Permanent

    Standard:
        
    */
   string tk;

   /*
    Name:
        Upgrade
        
    Description:
        Ask the client to upgrade to another protocol.
        
        Must not be used in HTTP/2
    
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
        Vary
        
    Description:
        Tells downstream proxies how to match future request headers to decide whether the cached response can be used rather than requesting a fresh one from the origin server.
    
    Example:
        Example 1: Vary: *
        Example 2: Vary: Accept-Language

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string vary;

    /*
    Name:
        Via
        
    Description:
        Informs the client of proxies through which the response was sent.
    
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

   /*
    Name:
        WWW-Authenticate
        
    Description:
        Indicates the authentication scheme that should be used to access the requested entity.
    
    Example:
       WWW-Authenticate: Basic

    Status:
        Permanent

    Standard:
        RFC 9110 (https://datatracker.ietf.org/doc/html/rfc9110)
        
    */
   string wwwAuth;

   /*
    Name:
        X-Frame-Options
        
    Description:
        Clickjacking protection: deny - no rendering within a frame, sameorigin - no rendering if origin mismatch, allow-from - allow from specified location, allowall - non-standard, allow from any location
    
    Example:
       X-Frame-Options: deny

    Status:
        Obsolete

    Standard:
        
    */
   string XframeOpts;
   

} StandardResponse;

typedef struct {

    /*
    Name:
        Content-Security-Policy,
        X-Content-Security-Policy,
        X-WebKit-CSP
        
    Description:
        Content Security Policy definition. 
    
    Example:
       X-WebKit-CSP: default-src 'self'

    */
   string XWebkitCSP;

   /*
    Name:
        Expect-CT
        
    Description:
        Notify to prefer to enforce Certificate Transparency. 
    
    Example:
       Expect-CT: max-age=604800, enforce, report-uri="https://example.example/report"

    */
   string expectCT;

   /*
    Name:
        NEL
        
    Description:
        Used to configure network request logging. 
    
    Example:
       NEL: { "report_to": "name_of_reporting_group", "max_age": 12345, "include_subdomains": false, "success_fraction": 0.0, "failure_fraction": 1.0 }

    */
   string nel;

   /*
    Name:
        Permissions-Policy
        
    Description:
        To allow or disable different features or APIs of the browser. 
    
    Example:
       Permissions-Policy: fullscreen=(), camera=(), microphone=(), geolocation=(), interest-cohort=()

    */
   string permissionsPolicy;

   /*
    Name:
        Refresh
        
    Description:
        Used in redirection, or when a new resource has been created. This refresh redirects after 5 seconds. Header extension introduced by Netscape and supported by most web browsers. Defined by HTML Standard 
    
    Example:
       Refresh: 5; url=http://www.w3.org/pub/WWW/People.html

    */
   string refresh;

   /*
    Name:
        Report-To
        
    Description:
        Instructs the user agent to store reporting endpoints for an origin. 
    
    Example:
       Report-To: { "group": "csp-endpoint", "max_age": 10886400, "endpoints": [ { "url": "https-url-of-site-which-collects-reports" } ] }

    */
   string reportTo;

   /*
    Name:
        Status
        
    Description:
        CGI header field specifying the status of the HTTP response. Normal HTTP responses use a separate "Status-Line" instead, defined by RFC 9110. 
    
    Example:
       Status: 200 OK 

    */
   string status;

   /*
    Name:
        Timing-Allow-Origin
        
    Description:
        The Timing-Allow-Origin response header specifies origins that are allowed to see values of attributes retrieved via features of the Resource Timing API, which would otherwise be reported as zero due to cross-origin restrictions. 
    
    Example:
       Timing-Allow-Origin: *
       Timing-Allow-Origin: <origin>[, <origin>]* 

    */
   string timingAllowOrigin;

   /*
    Name:
        X-Content-Duration
        
    Description:
        Provide the duration of the audio or video in seconds; only supported by Gecko browsers 
    
    Example:
       X-Content-Duration: 42.666 

    */
   string XContentDuration;

   /*
    Name:
        X-Content-Type-Options
        
    Description:
        The only defined value, "nosniff", prevents Internet Explorer from MIME-sniffing a response away from the declared content-type. This also applies to Google Chrome, when downloading extensions. 
    
    Example:
       X-Content-Type-Options: nosniff 

    */
   string XContentTypeOpts;

   /*
    Name:
        X-Powered-By
        
    Description:
        Specifies the technology (e.g. ASP.NET, PHP, JBoss) supporting the web application (version details are often in X-Runtime, X-Version, or X-AspNet-Version) 
    
    Example:
       X-Powered-By: PHP/5.4.0 

    */
   string XPoweredBy;

   /*
    Name:
        X-Redirect-By
        
    Description:
        Specifies the component that is responsible for a particular redirect.
    
    Example:
      X-Redirect-By: WordPress
      X-Redirect-By: Polylang 

    */
   string XRedirectBy;

   /*
    Name:
        X-Request-ID, X-Correlation-ID
        
    Description:
        Correlates HTTP requests between a client and server.
    
    Example:
      X-Request-ID: f058ebd6-02f7-4d3f-942e-904344e8cde5 

    */
   string XReqID;

   /*
    Name:
        X-UA-Compatible
        
    Description:
        Recommends the preferred rendering engine (often a backward-compatibility mode) to use to display the content. Also used to activate Chrome Frame in Internet Explorer. In HTML Standard, only the IE=edge value is defined.
    
    Example:
        X-UA-Compatible: IE=edge
        X-UA-Compatible: IE=EmulateIE7
        X-UA-Compatible: Chrome=1 

    */
   string XUACompatible;

   /*
    Name:
        X-XSS-Protection
        
    Description:
        Cross-site scripting (XSS) filter
    
    Example:
        X-XSS-Protection: 1; mode=block

    */
   string XXSSProtection;


} NonStandardResponse;
/*
    Description:
        Main struct for formatting the HTTP Header for HTTP responses, following the pre-requisited documented standards necessary.
*/
typedef struct {
    StandardResponse stres;
    NonStandardResponse nstres;
} HTTPResponseHeader;

typedef struct {
    byte* dataStream;
} RequestBody;

typedef struct {
    byte* dataStream;
} ResponseBody;

typedef struct {
    HTTPRequestHeader reqH;
    RequestBody reqB;
} HTTPRequest;

typedef struct {
    HTTPResponseHeader resH;
    ResponseBody reqB;
} HTTPResponse;

extern HTTPResponse* CTTP_GET(HTTPRequest* http_req, string url);
extern HTTPResponse* CTTP_POST(HTTPRequest* http_req, string url);
extern HTTPResponse* CTTP_PUT(HTTPRequest* http_req, string url);
extern HTTPResponse* CTTP_DELETE(HTTPRequest* http_req, string url);

#endif