#ifndef __DEVICES_H
#define __DEVICES_H
#include "drivers.h"

#ifdef USE_GPIO_DEVICE
    #include "dev_gpio.h"
#endif


#ifdef  USE_UART_DEVICE
    #include "dev_uart.h"
#endif


#ifdef  USE_SPI_DEVICE
    #include "dev_spi.h"
#endif



#endif
