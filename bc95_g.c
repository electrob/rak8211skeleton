#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"

#include "nrf_memobj.h"

#include "at_cmds.h"
#include "rak_uart_app.h"

#include "bc95_g.h"

extern uint16_t rxCount;
extern uint8_t Gsm_RxBuf[GSM_RXBUF_MAXSIZE];
extern uint16_t rxWriteIndex;

extern nrf_memobj_pool_t const* app_at_mem_pool;

void bc95g_uart_init (void) {
    rak_uart_init(UART_USE_GPRS);
}

int bc95g_uart_print(uint8_t *buffer, int nbytes)
{
    uint32_t err_code;
    rxCount = 0;
    for (uint32_t i = 0; i < nbytes; i++)
    {
        do
        {
            err_code = app_uart_put(buffer[i]);
            if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
            {
                APP_ERROR_CHECK(err_code);
            }
        }
        while (err_code == NRF_ERROR_BUSY);
    }
    return err_code;
}

bool bc95g_chk_response (uint8_t *search_value) {
    if (strnstr(search_value, Gsm_RxBuf, rxWriteIndex) != NULL) {
        return true;
    } else {
        return false;
    }
}

bool bc95g_create_socket (uint8_t *sock_type, 
                          uint8_t *protocol_type, 
                          uint8_t number_of_sockets) {
    
    uint8_t at_cmd_length = 0;
    uint8_t *c;

    uint8_t at_cmd[30] = {0};

    at_cmd_length = strlen(BC95G_CREATE_SOCK) +
                    UNO_LENGTH +
                    strlen(sock_type) + 
                    UNO_LENGTH +
                    strlen(protocol_type) +
                    UNO_LENGTH +
                    strlen(BC95G_DEF_LIST_PORT) +
                    UNO_LENGTH +
                    strlen(BC95G_EN_PORT_LISTEN) +
                    UNO_LENGTH + UNO_LENGTH;
    
    if(number_of_sockets > BC95G_MAX_SOCKS) {
      return false;
    }

    strncat(at_cmd, BC95G_CREATE_SOCK, strlen(BC95G_CREATE_SOCK));
    strncat(at_cmd, EQUALS_TO_ASCII, strlen(EQUALS_TO_ASCII));
    strncat(at_cmd, sock_type, strlen(sock_type));
    strncat(at_cmd, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd, protocol_type, strlen(protocol_type));
    strncat(at_cmd, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd, BC95G_DEF_LIST_PORT, strlen(BC95G_DEF_LIST_PORT));
    strncat(at_cmd, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd, BC95G_EN_PORT_LISTEN, strlen(BC95G_EN_PORT_LISTEN));
    strncat(at_cmd, "\r\n", 2);
}

bool bg95g_send_data (uint8_t *sock_number,
                      uint8_t *server_ip,
                      uint8_t *server_port,
                      uint8_t *data) {
    
    uint8_t len_t = 0;
    uint16_t loop = 0;
    uint16_t i = 0;

    uint8_t at_cmd_connect_len = 0;
    uint16_t at_cmd_send_len = 0;

    uint8_t at_cmd_connect[30] = {0};

    uint8_t at_cmd_send[1050] = {0};
    uint8_t data_in_hex[1000] = {0};

    uint16_t data_len = strlen(data);
    uint8_t data_len_to_string[5] = {0}; 
    
    
    if(strlen(data) > MAX_DATA_LENGTH) {
        return false;
    }

    sprintf(data_len_to_string, "%ld", data_len);
    
    while(data_len_to_string[len_t] != '\0') {
        len_t++;
    }
    
    while(data[loop] != '\0') {
        sprintf((char*)(data_in_hex+i),"%02X", data[loop]);
        loop+=1;
        i+=2;
    }

    at_cmd_connect_len = strlen(BC95G_TCP_CONNECT) +
                         UNO_LENGTH +
                         strlen(sock_number) + 
                         UNO_LENGTH +
                         strlen(server_ip) +
                         UNO_LENGTH +
                         strlen(server_port) +
                         UNO_LENGTH + UNO_LENGTH;
    
    at_cmd_send_len = strlen(BC95G_TCP_SEND) +
                      UNO_LENGTH +
                      strlen(sock_number) +
                      UNO_LENGTH +
                      strlen(data) +
                      UNO_LENGTH + UNO_LENGTH;
    
    strncat(at_cmd_connect, BC95G_TCP_CONNECT, strlen(BC95G_TCP_CONNECT));
    strncat(at_cmd_connect, EQUALS_TO_ASCII, strlen(EQUALS_TO_ASCII));
    strncat(at_cmd_connect, sock_number, strlen(sock_number));
    strncat(at_cmd_connect, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd_connect, server_ip, strlen(server_ip));
    strncat(at_cmd_connect, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd_connect, server_port, strlen(server_port));
    strncat(at_cmd_connect, "\r\n", 2);
    
    strncat(at_cmd_send, BC95G_TCP_SEND, strlen(BC95G_TCP_SEND));
    strncat(at_cmd_send, EQUALS_TO_ASCII, strlen(EQUALS_TO_ASCII));
    strncat(at_cmd_send, sock_number, strlen(sock_number));
    strncat(at_cmd_send, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd_send, data_len_to_string, strlen(data_len_to_string));
    strncat(at_cmd_send, COMMA_ASCII, strlen(COMMA_ASCII));
    strncat(at_cmd_send, data, strlen(data));
    strncat(at_cmd_send, "\r\n", 2);

}


void bc95g_get_imei(uint8_t *store_imei) {
    bc95g_uart_print(BC95G_GET_IMEI, strlen(BC95G_GET_IMEI));
}

void test_gprs1(void) {
    uint8_t at_cmd[] = "AT+CEREG=1\r\n";
    bc95g_uart_print(at_cmd, strlen(at_cmd));
}

void test_gprs2(void) {
    uint8_t at_cmd[] = "AT+CEREG?\r\n";
    bc95g_uart_print(at_cmd, strlen(at_cmd));
}

void test_gprs3(void) {
    uint8_t at_cmd[] = "AT+NCCID?\r\n";
    bc95g_uart_print(at_cmd, strlen(at_cmd));
}

void test_gprs4(void) {
    uint8_t at_cmd[] = "AT+CFUN?\r\n";
    bc95g_uart_print(at_cmd, strlen(at_cmd));
}

void test_gprs5(void) {
    uint8_t at_cmd[] = "AT+COPS?\r\n";
    bc95g_uart_print(at_cmd, strlen(at_cmd));
}