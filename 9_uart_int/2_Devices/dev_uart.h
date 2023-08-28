#ifndef __DEV_UART_H
#define __DEV_UART_H


typedef struct UARTDev{
    char *name;
    unsigned char channel;
    int (* Init)(struct UARTDev *ptDev);
    int (* Write)(struct UARTDev *ptDev,const unsigned char *buf,unsigned short length);
    int (* Read)(struct UARTDev *ptDev,unsigned char *buf,unsigned short length);
    struct UARTDev* next;
}UARTDevice;


void UARTDevRegister(void);
int UARTDevInsert(UARTDevice *ptDev);
UARTDevice * UARTDevFind(char *name);

#endif /* __DEV_UART_H */
