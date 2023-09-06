#ifndef __DRV_UART_H
#define __DRV_UART_H
#include "dev_uart.h"



int UARTDeviceNum(void);
UARTDevice *UARTDeviceGetHead(void);
int UARTDrvInit(struct UARTDev *ptDev);
int UARTDrvWrite(struct UARTDev *ptDev,const unsigned char *buf,unsigned short length);
int UARTDrvRead(struct UARTDev *ptDev,unsigned char *buf,unsigned short length);


#endif /* __DRV_UART_H */
