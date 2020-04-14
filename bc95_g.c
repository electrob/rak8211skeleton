#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"

#include "at_cmds.h"
#include "rak_uart_app.h"

#include "bc95_g.h"

void gsm_uart_init (void) {
    rak_uart_init(UART_USE_GPRS);
}

int gsm_uart_print(uint8_t *buffer, int nbytes)
{
    uint32_t err_code;
    for (uint32_t i = 0; i < nbytes; i++)
    {
        do
        {
            err_code = app_uart_put(buffer[i]);
            if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
            {
                //NRF_LOG_ERROR("Failed receiving NUS message. Error 0x%x. ", err_code);
                APP_ERROR_CHECK(err_code);
            }
        }
        while (err_code == NRF_ERROR_BUSY);
    }
    return err_code;
}

void test_gprs(void) {

    uint8_t at_cmd[] = "AT\r\n";
    gsm_uart_print(at_cmd, 4);
}




