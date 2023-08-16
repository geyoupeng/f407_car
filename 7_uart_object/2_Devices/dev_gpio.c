#include "dev_gpio.h"
#include "drivers.h"
#include "errno.h"
#include "string.h"
#include "my_type.h"

static GPIO_Device * gGPIODevices = NULLDEV;

void GPIODevRegister(void)
{
    GPIO_Device *tmp = GPIODevicesHead();
    int num = GPIODevicesNum();
    for(int i = 0;i< num ;i++)
        GPIODevInsert(&tmp[i]);
}

int GPIODevInsert(GPIO_Device *ptDev)
{
    if(NULLDEV == ptDev)
        return -EINVAL;
    if(NULLDEV == gGPIODevices)
    {
        gGPIODevices = ptDev;
    }else
    {
        ptDev->next = gGPIODevices;
        gGPIODevices = ptDev;

    }
    return ESUCCESS;
}

GPIO_Device *GPIODevFind(char *name)
{
    GPIO_Device * tmp = gGPIODevices;
    
    while(NULLDEV != tmp)
    {
        if(strstr(tmp->name,name))
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    
    return NULLDEV;
 
}
