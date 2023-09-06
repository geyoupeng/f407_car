#include "dev_uart.h"
#include "drivers.h"
#include "errno.h"
#include "string.h"
#include "my_type.h"

static UARTDevice *gUARTDeviceHead = NULLDEV;

void UARTDevRegister(void)
{
    int num = UARTDeviceNum();
    UARTDevice * tmp = UARTDeviceGetHead();
    for(char i = 0;i< num;i++)
        UARTDevInsert(&tmp[i]);
    
}


int UARTDevInsert(UARTDevice *ptDev)
{
    if(NULLDEV == ptDev)
        return -EINVAL;
    
    if(NULLDEV == gUARTDeviceHead)
    {
        gUARTDeviceHead = ptDev;
    }else
    {
        ptDev->next =gUARTDeviceHead;
        gUARTDeviceHead = ptDev;
    }
    
    
    return ESUCCESS;
    
}
UARTDevice * UARTDevFind(char *name)
{
     if(NULLDEV == name)
        return NULLDEV;
     UARTDevice * tmp = gUARTDeviceHead;
     while(tmp)
     {
         if(strstr(tmp->name,name))
             return tmp;
         tmp = tmp->next;
     }
     return NULLDEV;
    
}
