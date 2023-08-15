#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include "dev_gpio.h"


GPIO_Device * GPIODevicesHead(void);

int GPIODevicesNum(void);

int GPIODrvInit(struct GPIO_Dev *ptDev);
    
int GPIODrvWrite(struct GPIO_Dev *ptDev,int status);

int GPIODrvRead(struct GPIO_Dev *ptDev);


#endif /* __DRV_GPIO_H */
