#include "dev_spi.h"
#include "drivers.h"
#include "errno.h"
#include "string.h"
#include "my_type.h"

static SPIDevice *gSPIDeviceHead = NULLDEV;

void SPIDevRegister(void)
{
    int num = SPIDeviceNum();
    SPIDevice * tmp = SPIDeviceGetHead();
    for(char i = 0;i< num;i++)
        SPIDevInsert(&tmp[i]);
    
}


int SPIDevInsert(SPIDevice *ptDev)
{
    if(NULLDEV == ptDev)
        return -EINVAL;
    
    if(NULLDEV == gSPIDeviceHead)
    {
        gSPIDeviceHead = ptDev;
    }else
    {
        ptDev->next = gSPIDeviceHead;
        gSPIDeviceHead = ptDev;
    }
    
    
    return ESUCCESS;
    
}
SPIDevice * SPIDevFind(char *name)
{
     if(NULLDEV == name)
        return NULLDEV;
     SPIDevice * tmp = gSPIDeviceHead;
     while(tmp)
     {
         if(strstr(tmp->name,name))
             return tmp;
         tmp = tmp->next;
     }
     return NULLDEV;
    
}
