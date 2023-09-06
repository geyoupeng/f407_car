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
    if(65536 < length)
        return -EINVAL;
    switch(ptDev->channel)
    {
        case 1:
            HAL_SPI_Transmit(&hspi1,wbuf,length,length*10);
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



int SPIDrvRead(struct SPIDev *ptDev,unsigned char *rbuf,unsigned int length)  
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == rbuf)
        return -EINVAL;
    if(65536 < length)
        return -EINVAL;
    switch(ptDev->channel)
    {
        case 1:
            HAL_SPI_Receive(&hspi1,rbuf,length,length*10);
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


int SPIDrvWriteRead(struct SPIDev *ptDev,unsigned char *wbuf,unsigned char *rbuf,unsigned int length)
{
    if(NULL == ptDev)
        return -EINVAL;
    if(NULL == rbuf)
        return -EINVAL;
    if(65536 < length)
        return -EINVAL;
    switch(ptDev->channel)
    {
 
        case 1:
            HAL_SPI_TransmitReceive(&hspi1,wbuf,rbuf,length,length*10);
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
