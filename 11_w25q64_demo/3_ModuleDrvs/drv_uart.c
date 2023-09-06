#include "drv_uart.h"
#include "errno.h"
#include "usart.h"
#include "string.h"
#include "libs.h"
#include "dev_config/uart_config.h"
#include "stm32f4xx_hal.h"


void Uart1DrvWaitTxCplt(void);
int UARTDrvInit(struct UARTDev *ptDev);
int UARTDrvWrite(struct UARTDev *ptDev,const unsigned char *buf,unsigned short length);
int UARTDrvRead(struct UARTDev *ptDev,unsigned char *buf,unsigned short length);

unsigned char rxdata;

unsigned char rxdatabuf[255];

static volatile unsigned char gUart1TxCpltFlage  = 0;


static RingBuff *gUART1Buffer = NULL;

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
            if(strstr(ptDev->name, "UART DEBUG"))
            {
                gUART1Buffer = RingBuffNew((unsigned char)255);
                if(NULL == gUART1Buffer)
                    return -EIO;
                HAL_StatusTypeDef status = HAL_UART_Receive_IT(&huart1,(uint8_t *)(&rxdata), 1);
                if(HAL_OK != status) 
                    return -EIO;
            }
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
            status = HAL_UART_Transmit_IT(&huart1,(uint8_t *)buf, length);
            if(HAL_OK != status)
                return -EIO;
            Uart1DrvWaitTxCplt();
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
   // HAL_StatusTypeDef status;
    switch(ptDev->channel)
    {   
        case 1:
            if(NULL != gUART1Buffer)
            {
                int ret = gUART1Buffer->Read(gUART1Buffer,(uint8_t *)(buf),length);
                return ret;
            }
                
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


static void Uart1DrvWaitTxCplt()
{
    while(1 != gUart1TxCpltFlage);
    gUart1TxCpltFlage  = 0;
    
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(NULL != gUART1Buffer)
        gUART1Buffer->Write(gUART1Buffer,(uint8_t *)(&rxdata),1);
    HAL_StatusTypeDef status = HAL_UART_Receive_IT(&huart1,(uint8_t *)(&rxdata), 1);
   
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  
    gUart1TxCpltFlage = 1;
    
}

