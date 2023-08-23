#include "devices.h"
#include <stdio.h>

struct __FILE{
    int handle;
};

FILE __stdout;

int fputc(int ch, FILE *f)
{
    (void)f;
    UARTDevice *ptDev = UARTDevFind("UART DEBUG");
    if(NULL == ptDev)   
        return 0;
    if(ptDev->Write(ptDev, (unsigned char*)&ch, 1) == 1)
        return ch;
    return 0;
}



