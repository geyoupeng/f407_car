#include "dev_display.h"
#include "devices.h"
#include "errno.h"
#include "my_type.h"
#include "libs.h"


static int ST7789VInit(DisplayDevice *ptDev);
static int ST7789VDisplayON(DisplayDevice *ptDev);
static int ST7789VDisplayOFF(DisplayDevice *ptDev);



static int ST7789VSetDisplayWindow(struct DisplayDevice *ptDev, \
                           unsigned short wXs,unsigned short wYs,   \
                           unsigned short wXe,unsigned short wYe);

static int ST7789VFlush(struct DisplayDevice *ptDev);

static int ST7789VSetPixel(struct DisplayDevice *ptDev, \
                           unsigned short wX,unsigned short wY, \
                           unsigned short wcolor);

static DisplayDevice gST7789V = {
    .name = "ST7789V",
    .FBBase = NULL,
    .wXres = 240,
    .wYres = 360,
    .wBpp = 16,
    .dwSize = 0,
    .Init = ST7789VInit,
    .DisplayON = ST7789VDisplayON,
    .DisplayOFF = ST7789VDisplayOFF,
    .SetDisplayWindow = ST7789VSetDisplayWindow,              
    .SetPixel = ST7789VSetPixel,
    .Flush = ST7789VFlush
};


DisplayDevice *GetST7789V()
{
    
    return &gST7789V;
}

static int WriteRegister(unsigned char reg)
{
    GPIO_Device *pDCX = GPIODevFind("LCD pDCX");
    if(NULLDEV == pDCX)
    {
        return -EINVAL;
    }
    SPIDevice *pSPI1 = SPIDevFind("SPI");
    if(NULLDEV == pSPI1)
    {
        return -EINVAL;
    }
    pDCX->Write(pDCX,0);
    if(1 != pSPI1->Write(pSPI1,&reg,1))
    {
        pDCX->Write(pDCX,1);
        return -EIO;
    }
    pDCX->Write(pDCX,1);
    return ESUCCESS;
}


static int WriteData(unsigned char *buf,unsigned short length)
{
    SPIDevice *pSPI1 = SPIDevFind("SPI");
    if(NULLDEV == pSPI1)
    {
        return -EINVAL;
    }
    return pSPI1->Write(pSPI1,buf,length);
}


static int ReadData(unsigned char *buf,unsigned short length)
{
    SPIDevice *pSPI1 = SPIDevFind("SPI");
    if(NULLDEV == pSPI1)
    {
        return -EINVAL;
    }
    return pSPI1->Read(pSPI1,buf,length);
}

static int HWReset(void)
{
    GPIO_Device *pRST = GPIODevFind("LCD pRST");
    if(NULLDEV == pRST)
    {
        return -EINVAL;
    }
    pRST->Write(pRST,0);
    mdelay(150);
    pRST->Write(pRST,1);
    mdelay(5);
    return ESUCCESS;
}


static int SWReset(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x01);
    
    pCS->Write(pCS,1);
    
    if(ESUCCESS == ret)
    {
        mdelay(5);
        return ESUCCESS; 
    }
    return ret;
   
}


static int ReadDisplayID(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x04);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    unsigned char data[4] = {0};
    ret = ReadData(data,4);
    if(4 != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    pCS->Write(pCS,1);
    
    unsigned int ID = (data[1]<<16)|(data[2]<<8)|(data[3]<<0);
    
    
    return (int)ID;

}


static int ReadDisplayStatus(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x09);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    unsigned char data[5];
    ret = ReadData(data,5);
    if(5 != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    pCS->Write(pCS,1); 
    
    return (int)(data[1]);

}



static int ReadDisplayPixelFormat(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x0C);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    unsigned char data[2];
    ret = ReadData(data,2);
    if(2 != ret)
    {
        pCS->Write(pCS,1);
        return ret;
    }
    pCS->Write(pCS,1); 
    
    return (int)(data[1]);

}


static int SleepIn(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x10);
    pCS->Write(pCS,1);
    if(ESUCCESS == ret)
    {
        mdelay(5);
    }
    
    return ret;
    
}



static int SleepOut(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x11);
    pCS->Write(pCS,1);
    if(ESUCCESS == ret)
    {
        mdelay(5);
    }
    
    return ret;
    
}

static int SetPartialModeON(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    
    int ret = WriteRegister(0x12);
    pCS->Write(pCS,1);
   
    
    return ret;
    
}

static int SetNormalModeON(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x13);
    pCS->Write(pCS,1);
   
    
    return ret;
    
}


static int SetInversionOFF(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x20);
    pCS->Write(pCS,1);
   
    
    return ret;
    
}

static int SetInversionON(void)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x21);
    pCS->Write(pCS,1);
   
    
    return ret;
    
}

static int ST7789VDisplayOFF(DisplayDevice *ptDev)
{
    
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x28);
    pCS->Write(pCS,1);
   
    
    return ret;
    
    
}

static int ST7789VDisplayON(DisplayDevice *ptDev)
{
    
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x29);
    pCS->Write(pCS,1);
   
    
    return ret;
    
    
}

static int ST7789VSetDisplayWindow(struct DisplayDevice *ptDev, \
                           unsigned short wXs,unsigned short wYs,   \
                           unsigned short wXe,unsigned short wYe)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x2A);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    unsigned char data[4] = {wXs>>8,wXs,wXe>>8,wXe};
    ret = WriteData(data,4);
    if(4 != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    
    ret = WriteRegister(0x2B);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    unsigned char data1[4]={wYs>>8,wYs,wYe>>8,wYe};
    ret = WriteData(data1,4);
    if(4 != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    pCS->Write(pCS,1);
    
    ptDev->wXres = wXe - wXs;
    ptDev->wYres = wYe - wYs;
    ptDev->dwSize = (ptDev->wXres)*(ptDev->wYres)*(ptDev->wBpp)/8;
    
    return ESUCCESS;
}

static int ST7789VFlush(struct DisplayDevice *ptDev)
{
    if(NULLDEV == ptDev)
        return -EINVAL;
    if(NULLDEV == ptDev->FBBase)
        return -ENOMEM;
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x2c);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    ret = WriteData(ptDev->FBBase, ptDev->dwSize);
    pCS->Write(pCS,1);
    
    if(ptDev->dwSize != ret)
        return -EIO;
    printf("ST7789VFlush  WriteData %d\r\n",ret);
    
    return ret;
}

static int SetMemDataAddrCtrl(unsigned char value)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x36);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    ret = WriteData(&value,1);
    pCS->Write(pCS,1);
    if(1 != ret) return ret;
    return ESUCCESS;
}

static int SetPixelFormat(unsigned char mode)
{
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pCS->Write(pCS,0);
    int ret = WriteRegister(0x3A);
    if(ESUCCESS != ret)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    unsigned char param = 0x55;
    if(12 == mode)
        param = 0x53;
    else if(16 == mode)
        param = 0x55;
    else if(18 == mode)
        param = 0x66;
    ret = WriteData(&param,1);
    pCS->Write(pCS,1);
    
    if(1 != ret) return ret;
    return ESUCCESS;
    
    
}

static int ST7789VSetPixel(struct DisplayDevice *ptDev, \
                           unsigned short wX,unsigned short wY, \
                           unsigned short wcolor)
{
   if(NULLDEV == ptDev)
       return -EINVAL;
   if(NULLDEV == ptDev->FBBase)
       return -ENOMEM;
   
   unsigned short *pbuf = (unsigned short *)ptDev->FBBase;
   pbuf = pbuf + (wY*(ptDev->wXres)+wX);
   *pbuf = wcolor;
   
   
   return ESUCCESS;
}
static int ST7789VInit(DisplayDevice *ptDev)
{
    if(NULLDEV == ptDev)
       return -EINVAL;
    GPIO_Device *pCS = GPIODevFind("LCD CS");
    if(NULLDEV == pCS)
    {
        printf("pCS is NULL\r\n");
        return -EINVAL;
    }
    GPIO_Device *pDCX = GPIODevFind("LCD pDCX");
    if(NULLDEV == pDCX)
    {
        return -EINVAL;
    }
    GPIO_Device *pRST = GPIODevFind("LCD pRST");
    if(NULLDEV == pRST)
    {
        return -EINVAL;
    }
    GPIO_Device *pBACK = GPIODevFind("LCD pBACK");
    if(NULLDEV == pCS)
    {
        return -EINVAL;
    }
    pBACK->Write(pBACK, 0);
     SPIDevice *pSPI1 = SPIDevFind("SPI");
    if(NULLDEV == pSPI1)
    {
        return -EINVAL;
    }
    
    unsigned int ID = ReadDisplayID();
    printf("st7789 id is 0x%X\r\n",ID);
    
    
    int ret = -1;
    ret = HWReset();
    if(ESUCCESS != ret)
    {
        printf("HWReset failed %d\r\n",ret);
        return ret;
    }
    ret = SleepOut();
    if(ESUCCESS != ret)
    {
        printf("SleepOut failed %d\r\n",ret);
        return ret;
    }
    ret = SetNormalModeON();
    if(ESUCCESS != ret)
    {
        printf("SetNormalModeON failed %d\r\n",ret);
        return ret;
    }
    
    ret = SetInversionOFF();
    if(ESUCCESS != ret)
    {
        printf("SetInversionOFF failed %d\r\n",ret);
        return ret;
    }
    
    ret = SetMemDataAddrCtrl(0x00);
    if(ESUCCESS != ret)
    {
        printf("SetMemDataAddrCtrl failed %d\r\n",ret);
        return ret;
    }
    ret = SetPixelFormat(16);
    if(ESUCCESS != ret)
    {
        printf("SetPixelFormat failed %d\r\n",ret);
        return ret;
    }
    
    ret = ST7789VDisplayON(ptDev);
    if(ESUCCESS != ret)
    {
        printf("ST7789VDisplayON failed %d\r\n",ret);
        return ret;
    }
    
    return ESUCCESS;
}





