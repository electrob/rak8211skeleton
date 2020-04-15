
#include "app_uart.h"
#include "app_error.h"

#include "rak8211.h"

typedef enum {
              UART_USE_IDLE=0,
              UART_USE_GPRS,
              UART_USE_GPS,
              LOG_USE_UART
}uart_use_t;

void Gsm_RingBuf(uint8_t);
void uart_event_handle(app_uart_evt_t*);
void rak_uart_init(uart_use_t);