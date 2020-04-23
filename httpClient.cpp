
#include "httpClient.h"
#include "bc95_g.h"

HTTPClient::HTTPClient()
{
}

HTTPClient::~HTTPClient()
{
}

bool HTTPClient::begin(uint8_t * host)
{
    if(begin(host, HTTP_DEFAULT_PORT, false)) {
        return true;
    } else {
        return false;
    }
}

bool HTTPClient::begin( uint8_t * host, uint8_t * port, bool https)
{
    strcpy(_host, host);
    strcpy(_port, port);
    if(https) {
        /* TODO: Implement HTTPS */
        //strcpy(_protocol, HTTP_SECURE);
        //__protocol_check = true
    } else {
        _protocol_check = false;
        strcpy(_protocol, HTTP_PLAIN);
    }

    return true;
}

/*
 * Connect to a server through a socket
 */
bool HTTPClient::connect(void)
{
    // TODO: Connect to the TCP
    bc95g_create_socket(BC95G_SOCK_TYPE_TCP, 
                        BC95G_PROTO_TYPE_TCP, 
                        TCP_SOCK_ONE);
}

/* 
 *GET Method in HTTP 
 */
int HTTPClient::GET()
{
    return sendRequest("GET");
}

/* 
 * POST Method in HTTP 
 */
int HTTPClient::POST(uint8_t * payload)
{
    return POST(payload, strlen(payload));
}

int HTTPClient::POST(uint8_t * payload, uint16_t size)
{
    return sendRequest("POST", payload, size);
}

/*
 * PUT Method in HTTP 
 */
int HTTPClient::PUT(uint8_t * payload) {
    return PUT(payload, strlen(payload));
}

int HTTPClient::PUT(uint8_t * payload, uint16_t size) {
    return sendRequest("PUT", payload, size);
}

/*
 * Function for formatting and sending data.
 *
 */
int HTTPClient::sendRequest(const char * type)
{
    return sendRequest(type, NULL, NULL);
}

int HTTPClient::sendRequest(const char * type, uint8_t * payload)
{
    return sendRequest(type, payload, strlen(payload));
}

int HTTPClient::sendRequest(const char * type, uint8_t * payload, uint16_t size)
{
    //TODO: Check for connection, only for keep alive
    
    strncat(_httpRequestBuffer, type, strlen(type));
    strncat(_httpRequestBuffer, " ", 1);
    strncat(_httpRequestBuffer, HTTP_URL, strlen(HTTP_URL));
    strncat(_httpRequestBuffer, " ", 1);
    strncat(_httpRequestBuffer, HTTP_VERSION, strlen(HTTP_VERSION));
    strncat(_httpRequestBuffer, "\r\n", 2);

    addHeader(_httpRequestBuffer, HTTP_HOST_HEADER, _host);
    addHeader(_httpRequestBuffer, HTTP_CONN_HEADER, HTTP_CONN_CLOSE);
    addHeader(_httpRequestBuffer, HTTP_USR_AGNT_HEADER, HTTP_DEFAULT_USR_AGNT);
    
    strncat(http_req_buff, "\r\n", 2);
    if(payload != NULL && size != NULL) {
        
        strncat(_httpRequestBuffer, HTTP_CONTENT_LEN_HEADER, strlen(payload));
    } 
    

    //Use bc95-g functions to send data
    bg95g_send_data_tcp(TCP_SOCK_ONE,
                        _host,
                        _port,
                        _httpRequestBuffer);
    return 1;
    // TODO: Send and Get response and clear the buffers
}

/*
 * Function for adding extra headers.
 * This should always be called within the send request in order to
 * add new headers.
 */
void HTTPClient::addHeader(uint8_t * http_req_buff, uint8_t * key, uint8_t * value)
{
    uint8_t len_v = 0;
    
  /*if(strstr(HTTP_HOST_HEADER, key)) {
        while(value[len_v] != '\0') {
            len_v++;
        }
    }*/
        
    strncat(http_req_buff, key, strlen(key));
    strncat(http_req_buff, ": ", 2);
    strncat(http_req_buff, value, strlen(value));
    strncat(http_req_buff, "\r\n", 2);
}