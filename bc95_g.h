

#define BC95G_MAX_SOCKS 7

#define BC95G_SOCK_TYPE_TCP    "STREAM"
#define BC95G_SOCK_TYPE_UDP    "DGRAM"

#define BC95G_PROTO_TYPE_TCP   "6"
#define BC95G_PROTO_TYPE_UDP   "17"

#define BC95G_DEF_LIST_PORT    "56000"

#define EQUALS_TO_ASCII        "="
#define COMMA_ASCII            ","

#define UNO_LENGTH             1

#define BC95G_EN_PORT_LISTEN   "1"
#define BC95G_NO_PORT_LISTEN   "0"

#define TCP_SOCK_ONE   "1"
#define TCP_SOCK_TWO   "2"
#define TCP_SOCK_THREE "3"
#define TCP_SOCK_FOUR  "4"
#define TCP_SOCK_FIVE  "5"
#define TCP_SOCK_SIX   "6"
#define TCP_SOCK_SEVEN "7"

#define UDP_SOCK_ONE   "1"
#define UDP_SOCK_TWO   "2"
#define UDP_SOCK_THREE "3"
#define UDP_SOCK_FOUR  "4"
#define UDP_SOCK_FIVE  "5"
#define UDP_SOCK_SIX   "6"
#define UDP_SOCK_SEVEN "7"

#define MAX_DATA_LENGTH 500

void bc95g_uart_init (void);

int bc95g_uart_print (uint8_t*, int);

bool bc95g_chk_response (uint8_t*);

bool bc95g_create_socket (uint8_t*, uint8_t*, uint8_t);

bool bg95g_send_data (uint8_t*, uint8_t*, uint8_t*, uint8_t*);

void bc95g_get_imei(uint8_t*);


void test_gprs(void);

void test_gprs1(void);

void test_gprs2(void);

void test_gprs3(void);

void test_gprs4(void);

void test_gprs5(void);