#ifndef __DRIVERS_H
#define __DRIVERS_H
#include "config.h"


#if USE_GPIO_DRIVER
    #include "drv_gpio.h"
    #define USE_GPIO_DEVICE
#endif

#if USE_UART_DRIVER
    #include "drv_uart.h"
    #define USE_UART_DEVICE
#endif

#endif /* __DRIVERS_H */
