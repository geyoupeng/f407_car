#ifndef __DRIVERS_H_
#define __DRIVERS_H_

#ifndef USE_GPIO_DRIVER
    #include "drv_gpio.h"
    #define USE_GPIO_DEVICE
#endif

#ifndef USE_UART_DRIVER
    //#include "drv_uart.h"
    #define USE_UART_DRIVER
#endif


#endif /* __DRIVERS_H_ */ 
