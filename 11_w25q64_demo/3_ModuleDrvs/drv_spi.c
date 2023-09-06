#include "drv_spi.h"
#include "dev_config/spi_config.h"
#include "errno.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

static int SPIDrvInit(struct SPIDev *ptDev);
static int SPIDrvWrite(struct SPIDev *ptDev,unsigned char *wbuf,unsigned int length);
static int SPIDrvRead(struct SPIDev *ptDev,unsigned char *rbuf,unsigned int length);
static int SPIDrvWriteRead(struct SPIDev *ptDev,unsigned char *wbuf,unsigned char *rbuf,unsigned int length);


static SPIDevice gSpiDevices[] = {S1};



static int TxCpltFlag = 0;
static int RxCpltFlag = 0;
static int TxRxCpltFlag = 0;


void WaitTxComplete()
{
    while(0 == TxCpltFlag);
    TxCpltFlag = 0;
    
}

void WaitRxComplete()
{
    while(0 == RxCpltFlag);
    RxCpltFlag = 0;
    
}

void WaitTxRxComplete()
{
    while(0 == TxRxCpltFlag);
    TxRxCpltFlag = 0;
    
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    TxCpltFlag = 1;
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    RxCpltFlag = 1;
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    TxRxCpltFlag = 1;
}


int SPIDeviceNum()
{
    return sizeof(gSpiDevices)/sizeof(SPIDevice);
    
}


SPIDevice * SPIDeviceGetHead()
{
    return gSpiDevices;
    
}


int SPIDrvInit(struct SPIDev *ptDev)
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
        default:
            break;

    }
    return ESUCCESS;
}

int SPIDrvWrite(struct SPIDev *ptDev,unsigned char *wbuf,unsigned int length)
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == wbuf)
        return -EINVAL;
    int init_len = length;
    int len;
    switch(ptDev->channel)
    {
        case 1:
        {
     
            if(1 == length)
            {
                HAL_StatusTypeDef status = HAL_SPI_Transmit_IT(&hspi1, wbuf, length);
                if(HAL_OK != status)    
                    return -EIO;
            }else
            {
                while(length)
                {
                    if(length > 65536)
                        len = 65536;
                    else
                        len = length;
                    HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA(&hspi1, wbuf, len);
                    if(HAL_OK != status)    
                        return -EIO;
                    length = length - len;;
                    wbuf = wbuf + len;
                }
                
            }
            WaitTxComplete();
            break;
        }
        case 2:
            break;
        case 3:
            break;
        default:
            break;

    }
    return (int)init_len;
    
}



int SPIDrvRead(struct SPIDev *ptDev,unsigned char *rbuf,unsigned int length)  
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == rbuf)
        return -EINVAL;
    int init_len = length;
    int len;
    switch(ptDev->channel)
    {
        case 1:
        {
            if(1 == length)
            {
                HAL_StatusTypeDef status = HAL_SPI_Receive_IT(&hspi1, rbuf, length);
                if(HAL_OK != status)    
                    return -EIO;
            }else
            {
                while(length)
                {
                    if(length > 65536)
                        len = 65536;
                    else
                        len = length;
                    HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&hspi1, rbuf, len);
                    if(HAL_OK != status)    
                        return -EIO;
                    length = length - len;;
                    rbuf = rbuf + len;
                }
                
            }
            WaitRxComplete();
            break;
        }
        case 2:
            break;
        case 3:
            break;
        default:
            break;

    }
    return (int)init_len;
    
    
}


int SPIDrvWriteRead(struct SPIDev *ptDev,unsigned char *wbuf,unsigned char *rbuf,unsigned int length)
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == rbuf)
        return -EINVAL;
    unsigned int init_len = length;
    unsigned int len;
    switch(ptDev->channel)
    {
 
        case 1:
        {
            if(1 == length)
            {
                
                HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(&hspi1,wbuf ,rbuf, length);
                if(HAL_OK != status)    
                    return -EIO;
            }else
            {
                while(length)
                {
                    if(length > 65536)
                        len = 65536;
                    else
                        len = length;
                    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(&hspi1,wbuf ,rbuf,len);
                    if(HAL_OK != status)    
                        return -EIO;
                    length = length -  len;
                    rbuf = rbuf + len;
                    wbuf = wbuf + len;
                }
                
            }
            WaitTxRxComplete();
            break;
        }
        case 2:
            break;
        case 3:
            break;
        default:
            break;

    }
    return (int)init_len;
    
}
