#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rak_uart_app.h"

void gps_uart_init (void) {
    rak_uart_init(UART_USE_GPS);
}



