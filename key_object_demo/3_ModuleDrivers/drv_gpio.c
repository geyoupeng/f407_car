#include "dev_gpio.h"
#include "errno.h"
#include "stm32f4xx_hal.h"
#include "dev_config.h"


int GPIODrvInit(struct GPIODev *ptdev);
int GPIODrvWrite(struct GPIODev *ptdev,unsigned char status);
int GPIODrvRead(struct GPIODev *ptdev);




static GPIODevice gGPIODevices[] = {D1,D2,D3,D4};

GPIODevice *GPIODevsHead()
{ 
    return gGPIODevices;
}

int GPIODevsNum()
{ 
    return sizeof(gGPIODevices)/sizeof(GPIODevice);
}


int GPIODrvInit(struct GPIODev *ptdev)
{
    if(NULL == ptdev)
        return -EINVAL;
    return ESUCCESS;
}

int GPIODrvWrite(struct GPIODev *ptdev,unsigned char status)
{
    if(NULL == ptdev)
        return -EINVAL;
    if(0 !=status && 1 !=status)
        return -EINVAL;
    HAL_GPIO_WritePin(ptdev->port, ptdev->pin , status);
    return ESUCCESS;
}

int GPIODrvRead(struct GPIODev *ptdev)
{
    if(NULL == ptdev)
        return -EINVAL;
    int status = HAL_GPIO_ReadPin(ptdev->port, ptdev->pin);
    return ESUCCESS;
}

