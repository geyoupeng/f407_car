#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H
#include "dev_gpio.h"


GPIODevice *GPIODevsHead(void);

int GPIODevsNum(void);

int GPIODrvInit(struct GPIODev *ptdev);

int GPIODrvWrite(struct GPIODev *ptdev,unsigned char status);

int GPIODrvRead(struct GPIODev *ptdev);

#endif /* __DRV_GPIO_H */
