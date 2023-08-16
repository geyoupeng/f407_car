#include "dev_gpio.h"
#include "drivers.h"
#include "my_type.h"
#include "string.h"

static GPIODevice *gheadDevices = NULLDEV;


void GPIODevRegister(void)
{
    int num = GPIODevsNum();
    GPIODevice *tmp = GPIODevsHead();
    for(char i = 0;i < num; i++)
        GPIODevInsert(&tmp[i]);
}


void GPIODevInsert(GPIODevice *pDevices)
{
    
    if(NULLDEV == gheadDevices)
    {
        gheadDevices = pDevices;
    }else
    {
        pDevices->next = gheadDevices;
        gheadDevices = pDevices;
    } 
    
}
GPIODevice * GPIODevFind(char *name)
{
    
    
    GPIODevice *ptDevices = gheadDevices;
    while(NULLDEV != ptDevices)
    {
        if(strstr(ptDevices->name,name))
        {
            return ptDevices;
        } 
        ptDevices = ptDevices->next;
    }
    
    return NULLDEV;
    
    
}
