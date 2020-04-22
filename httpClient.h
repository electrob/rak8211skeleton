#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAX_HOST_NAME_LENGTH    20
#define MAX_PORT_LENGTH         6

#define HTTP_BUFF_MAX_LEN       500

#define HTTP_DEF_TCP_TIMEOUT    5000

#define HTTP_DEFAULT_PORT       "80"

#define HTTP_PROTOCOL_LEN       6

#define HTTP_PLAIN              "HTTP"
#define HTTP_SECURE             "HTTPS"

#define HTTP_DEFAULT_USR_AGNT   "rak8211"

#define HTTP_HOST_HEADER        "Host"
#define HTTP_USR_AGNT_HEADER    "User-Agent"
#define HTTP_CONN_HEADER        "Connection"

#define HTTP_URL                "/post"

#define HTTP_VERSION            "HTTP/1.1"

#define HTTP_CONTENT_LEN_HEADER "Content-Length"

#define HTTP_KEEP_ALIVE         "keep-alive"

#define HTTP_CONN_CLOSE         "close"

typedef enum {
    HTTP_CODE_CONTINUE = 100,
    HTTP_CODE_SWITCHING_PROTOCOLS = 101,
    HTTP_CODE_PROCESSING = 102,
    HTTP_CODE_OK = 200,
    HTTP_CODE_CREATED = 201,
    HTTP_CODE_ACCEPTED = 202,
    HTTP_CODE_NON_AUTHORITATIVE_INFORMATION = 203,
    HTTP_CODE_NO_CONTENT = 204,
    HTTP_CODE_RESET_CONTENT = 205,
    HTTP_CODE_PARTIAL_CONTENT = 206,
    HTTP_CODE_MULTI_STATUS = 207,
    HTTP_CODE_ALREADY_REPORTED = 208,
    HTTP_CODE_IM_USED = 226,
    HTTP_CODE_MULTIPLE_CHOICES = 300,
    HTTP_CODE_MOVED_PERMANENTLY = 301,
    HTTP_CODE_FOUND = 302,
    HTTP_CODE_SEE_OTHER = 303,
    HTTP_CODE_NOT_MODIFIED = 304,
    HTTP_CODE_USE_PROXY = 305,
    HTTP_CODE_TEMPORARY_REDIRECT = 307,
    HTTP_CODE_PERMANENT_REDIRECT = 308,
    HTTP_CODE_BAD_REQUEST = 400,
    HTTP_CODE_UNAUTHORIZED = 401,
    HTTP_CODE_PAYMENT_REQUIRED = 402,
    HTTP_CODE_FORBIDDEN = 403,
    HTTP_CODE_NOT_FOUND = 404,
    HTTP_CODE_METHOD_NOT_ALLOWED = 405,
    HTTP_CODE_NOT_ACCEPTABLE = 406,
    HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED = 407,
    HTTP_CODE_REQUEST_TIMEOUT = 408,
    HTTP_CODE_CONFLICT = 409,
    HTTP_CODE_GONE = 410,
    HTTP_CODE_LENGTH_REQUIRED = 411,
    HTTP_CODE_PRECONDITION_FAILED = 412,
    HTTP_CODE_PAYLOAD_TOO_LARGE = 413,
    HTTP_CODE_URI_TOO_LONG = 414,
    HTTP_CODE_UNSUPPORTED_MEDIA_TYPE = 415,
    HTTP_CODE_RANGE_NOT_SATISFIABLE = 416,
    HTTP_CODE_EXPECTATION_FAILED = 417,
    HTTP_CODE_MISDIRECTED_REQUEST = 421,
    HTTP_CODE_UNPROCESSABLE_ENTITY = 422,
    HTTP_CODE_LOCKED = 423,
    HTTP_CODE_FAILED_DEPENDENCY = 424,
    HTTP_CODE_UPGRADE_REQUIRED = 426,
    HTTP_CODE_PRECONDITION_REQUIRED = 428,
    HTTP_CODE_TOO_MANY_REQUESTS = 429,
    HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    HTTP_CODE_INTERNAL_SERVER_ERROR = 500,
    HTTP_CODE_NOT_IMPLEMENTED = 501,
    HTTP_CODE_BAD_GATEWAY = 502,
    HTTP_CODE_SERVICE_UNAVAILABLE = 503,
    HTTP_CODE_GATEWAY_TIMEOUT = 504,
    HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED = 505,
    HTTP_CODE_VARIANT_ALSO_NEGOTIATES = 506,
    HTTP_CODE_INSUFFICIENT_STORAGE = 507,
    HTTP_CODE_LOOP_DETECTED = 508,
    HTTP_CODE_NOT_EXTENDED = 510,
    HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED = 511
} t_http_codes;


class HTTPClient
{

public:

    HTTPClient();
    ~HTTPClient();

    bool begin(uint8_t * host);
    bool begin(uint8_t * host,  uint8_t * port, bool https);

    bool connected(void);

    /* Request */
    int GET();

    int POST(uint8_t * payload, uint16_t size);
    int POST(uint8_t * payload);
    
    int PUT(uint8_t * payload, uint16_t size);
    int PUT(uint8_t * payload);
    
    int sendRequest(const char * type);
    int sendRequest(const char * type, uint8_t * payload);
    int sendRequest(const char * type, uint8_t * payload, uint16_t payloadSize);

    void addHeader(uint8_t * http_req_buff, uint8_t * key, uint8_t * value);

    /* Response */
   // void collectHeaders(const char* headerKeys[], const size_t headerKeysCount);
    
    char _host[MAX_HOST_NAME_LENGTH] = {0};
    char _port[MAX_PORT_LENGTH] = {0};
    uint8_t _protocol[HTTP_PROTOCOL_LEN] = {0};
    
    bool _protocol_check = false;
    
    uint8_t _httpRequestBuffer[HTTP_BUFF_MAX_LEN] = {0};
    uint8_t _http_headers[HTTP_BUFF_MAX_LEN] = {0};

    uint8_t _userAgent[10] = {0};

protected:

    int returnError(int error);
    bool connect(void);
    
    

}
