#include "drv_gpio.h"
#include "dev_config.h"
#include "errno.h"
#include "stm32f4xx_hal.h"

static GPIO_Device GPIODevices[] = {D1,D2,D3,D4,K1,K2,K3,K4};

GPIO_Device * GPIODevicesHead()
{
    return GPIODevices;   
}

int GPIODevicesNum()
{
    
    return sizeof(GPIODevices)/sizeof(GPIO_Device);
}

int GPIODrvInit(struct GPIO_Dev *ptDev)
{
    if(NULL == ptDev)
        return -EINVAL;
    return ESUCCESS;
    
}
    
int GPIODrvWrite(struct GPIO_Dev *ptDev,int status)
{
    if(NULL == ptDev)
        return -EINVAL;
    if((0 != status) && (1 != status))
        return -EINVAL;
    
    HAL_GPIO_WritePin(ptDev->port,ptDev->pin,status);
    return ESUCCESS;
    
}

int GPIODrvRead(struct GPIO_Dev *ptDev)
{
    if(NULL == ptDev)
        return -EINVAL;
    int status = HAL_GPIO_ReadPin(ptDev->port,ptDev->pin);
    return status;
    
    
}
