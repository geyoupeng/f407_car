#include "drv_uart.h"
#include "errno.h"
#include "usart.h"
#include "dev_config.h"
#include "stm32f4xx_hal.h"

int UARTDrvInit(struct UARTDev *ptDev);
int UARTDrvWrite(struct UARTDev *ptDev,const unsigned char *buf,unsigned short length);
int UARTDrvRead(struct UARTDev *ptDev,unsigned char *buf,unsigned short length);



static UARTDevice UARTDevices[] = {UART_DEBUG};

int UARTDeviceNum()
{
    
    return sizeof(UARTDevices)/sizeof(UARTDevice);
}

UARTDevice *UARTDeviceGetHead()
{
    return UARTDevices;
}


int UARTDrvInit(struct UARTDev *ptDev)
{
    if(NULL == ptDev)
        return -EINVAL;
    switch(ptDev->channel)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        
    }
    return ESUCCESS;
    
}
int UARTDrvWrite(struct UARTDev *ptDev,const unsigned char *buf,unsigned short length)
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == buf)
        return -EINVAL;
    HAL_StatusTypeDef status;
    switch(ptDev->channel)
    {
        case 1:
            status = HAL_UART_Transmit(&huart1,(uint8_t *)buf, length, length * 10);
            if(HAL_OK != status)
                return -EIO;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        
    }
    return ESUCCESS;

}
int UARTDrvRead(struct UARTDev *ptDev,unsigned char *buf,unsigned short length)
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == buf)
        return -EINVAL;
    HAL_StatusTypeDef status;
    switch(ptDev->channel)
    {   
        case 1:
            status = HAL_UART_Receive(&huart1, buf, length, length * 10);
            if(HAL_OK != status)
                return -EIO;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        
    }
    return ESUCCESS;
    
    
}
