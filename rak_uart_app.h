
#include "app_uart.h"
#include "app_error.h"

#include "rak8211.h"

#define GSM_RXBUF_MAXSIZE 600
#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 2048                        /**< UART RX buffer size. */

typedef enum {
              UART_USE_IDLE=0,
              UART_USE_GPRS,
              UART_USE_GPS,
              LOG_USE_UART
}uart_use_t;

uint8_t Gsm_RxByte(void);
void Gsm_RingBuf(uint8_t);
void uart_event_handle(app_uart_evt_t*);
void rak_uart_init(uart_use_t);