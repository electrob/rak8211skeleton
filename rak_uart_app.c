
#include "rak_uart_app.h"

//static 
uint16_t rxReadIndex  = 0;
//static 
uint16_t rxWriteIndex = 0;
//static 
uint16_t rxCount      = 0;

uint8_t Gsm_RxBuf[GSM_RXBUF_MAXSIZE];

uart_use_t use_uart_type = UART_USE_IDLE;

/*uint8_t Gsm_RxByte(void)
{
    int c = -1;

    __disable_irq();
    if (rxCount > 0)
    {
        c = Gsm_RxBuf[rxReadIndex];

        rxReadIndex++;
        if (rxReadIndex == GSM_RXBUF_MAXSIZE)
        {
            rxReadIndex = 0;
        }
        rxCount--;
    }
    __enable_irq();

    return c;
}
*/
void Gsm_RingBuf(uint8_t in_data)
{
    Gsm_RxBuf[rxWriteIndex] = in_data;
    rxWriteIndex++;
    rxCount++;

    if (rxWriteIndex == GSM_RXBUF_MAXSIZE)
    {
        rxWriteIndex = 0;
    }

    /* Check for overflow */
    if (rxCount == GSM_RXBUF_MAXSIZE)
    {
        rxWriteIndex = 0;
       // rxCount      = 0;
        rxReadIndex  = 0;
    }
}

void uart_event_handle(app_uart_evt_t * p_event)
{
    static uint8_t index = 0;
    uint32_t       err_code;
    uint8_t rx_data;

    switch (p_event->evt_type)
    {
    case APP_UART_DATA_READY:
         app_uart_get(&rx_data);
         Gsm_RingBuf(rx_data);

        /*if(uart_use == GPS_USE_UART)
        {
            uint8_t rx_data;
            if( app_uart_get( &rx_data ) == 0 )
            {
                Gps_data_update(rx_data);
                //SEGGER_RTT_printf(0, "%c", rx_data);
            }
        }*/

        break;
    case APP_UART_FIFO_ERROR:
        APP_ERROR_HANDLER(p_event->data.error_code);
        break;

    default:
        break;
    }
}

void rak_uart_init(uart_use_t uart_use)
{
    uint32_t err_code;
    
    app_uart_close();
    
    use_uart_type = uart_use;

    app_uart_comm_params_t comm_params;

    switch(uart_use) 
    {
      case UART_USE_GPS:
          comm_params.rx_pin_no = GPS_RXD;
          comm_params.tx_pin_no = GPS_TXD;
          comm_params.rts_pin_no = 0;
          comm_params.cts_pin_no = 0;
          comm_params.flow_control = APP_UART_FLOW_CONTROL_DISABLED;
          comm_params.use_parity = false;
          comm_params.baud_rate = UART_BAUDRATE_BAUDRATE_Baud9600;

          APP_UART_FIFO_INIT(&comm_params,
                            UART_RX_BUF_SIZE,
                            UART_TX_BUF_SIZE,
                            uart_event_handle,
                            APP_IRQ_PRIORITY_LOW,
                            err_code);

          APP_ERROR_CHECK(err_code);
          break;

      case UART_USE_GPRS:
          comm_params.rx_pin_no = GPRS_TXD;
          comm_params.tx_pin_no = GPRS_RXD;
          comm_params.rts_pin_no = 0;
          comm_params.cts_pin_no = 0;
          comm_params.flow_control = APP_UART_FLOW_CONTROL_DISABLED;
          comm_params.use_parity = false;
          comm_params.baud_rate = UART_BAUDRATE_BAUDRATE_Baud9600;

          APP_UART_FIFO_INIT(&comm_params,
                            UART_RX_BUF_SIZE,
                            UART_TX_BUF_SIZE,
                            uart_event_handle,
                            APP_IRQ_PRIORITY_LOW,
                            err_code);

          APP_ERROR_CHECK(err_code);
          break;
      
      default:
        break;
    }
}
