#include "drv_gpio.h"
#include "dev_config/gpio_config.h"
#include "errno.h"
#include "string.h"
#include "libs.h"
#include "stm32f4xx_hal.h"

static RingBuff *gK1Buffer = NULL;
static RingBuff *gK2Buffer = NULL;
static RingBuff *gK3Buffer = NULL;
static RingBuff *gK4Buffer = NULL;

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
    if(strstr(ptDev->name, "K1"))
    {
        gK1Buffer = RingBuffNew(sizeof(unsigned char)*10);
        if(NULL == gK1Buffer)
            return -EIO;
    }
    if(strstr(ptDev->name, "K2"))
    {
        gK1Buffer = RingBuffNew(sizeof(unsigned char)*10);
        if(NULL == gK1Buffer)
            return -EIO;
    }
    if(strstr(ptDev->name, "K3"))
    {
        gK1Buffer = RingBuffNew(sizeof(unsigned char)*10);
        if(NULL == gK1Buffer)
            return -EIO;
    }
    if(strstr(ptDev->name, "K4"))
    {
        gK1Buffer = RingBuffNew(sizeof(unsigned char)*10);
        if(NULL == gK1Buffer)
            return -EIO;
    }
    
    
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

int GPIOIrqDrvRead(struct GPIO_Dev *ptDev)
{
    if(NULL == ptDev)
        return -EINVAL;
    
    if(strstr(ptDev->name, "K1"))
    {
        if(NULL != gK1Buffer)
        {
            int ret = gK1Buffer->Read(gK1Buffer, (unsigned char*)&ptDev->value, 1);
            if(ret != 1)    return -EIO;
        }
    }
    if(strstr(ptDev->name, "K2"))
    {
        if(NULL != gK2Buffer)
        {
            int ret = gK2Buffer->Read(gK2Buffer, (unsigned char*)&ptDev->value, 1);
            if(ret != 1)    return -EIO;
        }
    }
    
    if(strstr(ptDev->name, "K3"))
    {
        if(NULL != gK1Buffer)
        {
            int ret = gK3Buffer->Read(gK3Buffer, (unsigned char*)&ptDev->value, 1);
            if(ret != 1)    return -EIO;
        }
    }
    
    if(strstr(ptDev->name, "K4"))
    {
        if(NULL != gK4Buffer)
        {
            int ret = gK4Buffer->Read(gK4Buffer, (unsigned char*)&ptDev->value, 1);
            if(ret != 1)    return -EIO;
        }
    }
    
    return ESUCCESS;
    
    
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:    // PA0--K1
        {
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
            if(NULL != gK1Buffer)
                gK1Buffer->Write(gK1Buffer, (unsigned char*)&state, 1);
            break;
        }
        case GPIO_PIN_1:    // PA1--K2
        {
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
            if(NULL != gK2Buffer)
                gK2Buffer->Write(gK2Buffer, (unsigned char*)&state, 1);
            break;
        }
        case GPIO_PIN_2:    // PA2--K3
        {
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
            if(NULL != gK3Buffer)
                gK3Buffer->Write(gK3Buffer, (unsigned char*)&state, 1);
            break;
        }
        case GPIO_PIN_3:    // PA3--K4
        {
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
            if(NULL != gK4Buffer)
                gK4Buffer->Write(gK4Buffer, (unsigned char*)&state, 1);
            break;
        }
        default:break;
    }
}
