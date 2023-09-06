#include "w25qxx.h"
#include "devices.h"
#include "my_type.h"
#include "errno.h"
#include "libs.h"


static int W25Q64Init(struct W25QDev *ptdev);
static int W25Q64Erase(struct W25QDev *ptdev, unsigned int addr, unsigned int sectors);
static int W25Q64Write(struct W25QDev *ptdev, unsigned int addr, unsigned char *wbuf, unsigned int length);
static int W25Q64Read(struct W25QDev *ptdev, unsigned int addr, unsigned char *rbuf, unsigned int length);



static W25QDevice  gW25Q64= {
    .name = "W25Q64",
    .Init = W25Q64Init,
    .Erase = W25Q64Erase,
    .Write = W25Q64Write,
    .Read = W25Q64Read
};

W25QDevice *GetW25Q64Device(void)
{
    
    return &gW25Q64;
    
}

static unsigned int ReadID()
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return 0;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return 0;
    unsigned char cmd = W25X_JedecDeviceID;
    unsigned char id[3] = {0};
    
    pCS->Write(pCS,0);    
    
    pS1->Write(pS1,&cmd,1);
    
    pS1->Read(pS1,id,3);
    pCS->Write(pCS,1); 
    unsigned int ID = 0;
    xprintf("ID is %x\r\n",ID);
    ID = (id[0]<<16)|(id[1]<<8)|(id[2]<<0);
    xprintf("ID is %x\r\n",ID);
    
    return ID;
    
}


static int W25Q64Init(struct W25QDev *ptdev)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if(W25Q64_ID != ReadID())
        return -EIO;
    
    
    return ESUCCESS;

}

static int EnableWrite(void)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    unsigned char cmd = W25X_WriteEnable;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,&cmd,1);
    if(1 != len)
        return -EIO;
    
    pCS->Write(pCS,1);
    
    return ESUCCESS;
}


static int WaitWrite(void)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    unsigned char cmd = W25X_ReadStatusReg;
    unsigned char status = 0xFF;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,&cmd,1);
    if(1 != len)
        return -EIO;
    while(status&0x01)
    {
       len = pS1->Read(pS1,&status,1);
       if(1 != len)
            return -EIO; 
    }
    
    
    pCS->Write(pCS,1);
    
    return ESUCCESS;
    
}

static int PowerDown(void)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    unsigned char cmd = W25X_PowerDown;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,&cmd,1);
    if(1 != len)
        return -EIO;
    
    pCS->Write(pCS,1);
    
    return ESUCCESS;
}

static int WakeUp(void)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    unsigned char cmd = W25X_ReleasePowerDown;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,&cmd,1);
    if(1 != len)
        return -EIO;
    
    pCS->Write(pCS,1);
    
    return ESUCCESS;
}











static int SectorErase(unsigned int addr)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if(W25Q64_SIZE < addr)
        return -EINVAL;
    unsigned char data[4];
    data[0] = W25X_SectorErase;
    data[1] = (addr&0xFF0000) >> 16;
    data[2] = (addr&0x00FF00) >> 8;
    data[3] = (addr&0x0000FF) >> 0;
    
    
    if(ESUCCESS != EnableWrite())
        return -EIO;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,data,4);
    if(4 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    
    
    if(ESUCCESS != WaitWrite())
        return -EIO;
    return ESUCCESS;
}



static int BlockErase32K(unsigned int addr)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if(W25Q64_SIZE < addr)
        return -EINVAL;
    unsigned char data[4];
    data[0] = 0x52;
    data[1] = (addr&0xFF0000) >> 16;
    data[2] = (addr&0x00FF00) >> 8;
    data[3] = (addr&0x0000FF) >> 0;
    
    
    if(ESUCCESS != EnableWrite())
        return -EIO;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,data,4);
    if(4 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    
    
    if(ESUCCESS != WaitWrite())
        return -EIO;
    return ESUCCESS;
    
}

static int BlockErase64K(unsigned int addr)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if(W25Q64_SIZE < addr)
        return -EINVAL;
    unsigned char data[4];
    data[0] = W25X_BlockErase;
    data[1] = (addr&0xFF0000) >> 16;
    data[2] = (addr&0x00FF00) >> 8;
    data[3] = (addr&0x0000FF) >> 0;
    
    
    if(ESUCCESS != EnableWrite())
        return -EIO;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,data,4);
    if(4 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    
    
    if(ESUCCESS != WaitWrite())
        return -EIO;
    return ESUCCESS;
    
}


static int ChipErase(unsigned int addr)
    

{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if(W25Q64_SIZE < addr)
        return -EINVAL;
    unsigned char cmd;
    cmd = W25X_ChipErase;
 
    
    
    if(ESUCCESS != EnableWrite())
        return -EIO;
    pCS->Write(pCS,0);    
    
    int len = pS1->Write(pS1,&cmd,1);
    if(1 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    
    
    if(ESUCCESS != WaitWrite())
        return -EIO;
    return ESUCCESS;
    
}

static int PageWrite(unsigned int addr,unsigned char *wbuf,unsigned short length)
{
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    if((NULL == wbuf)||(0 == length)||W25Q64_SIZE<addr)
        return -EINVAL;
    
    unsigned char data[4];
    data[0] = W25X_PageProgram;
    data[1] = (addr&0xFF0000) >> 16;
    data[2] = (addr&0x00FF00) >> 8;
    data[3] = (addr&0x0000FF) >> 0;
    
    if(EnableWrite() != ESUCCESS)
    {
        return -EIO;
    }
    
    pCS->Write(pCS,0); 
    
    int len = pS1->Write(pS1,data,4);
    if(4 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    len = pS1->Write(pS1,wbuf,length);
    if(length != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    if(ESUCCESS != WaitWrite())
        return -EIO;
    
    
    return (int)length;
    
}

static int W25Q64Erase(struct W25QDev *ptdev, unsigned int addr, unsigned int sectors)
{
     
     if((NULL == ptdev)||(0 == sectors)||W25Q64_SIZE<=addr)
        return -EINVAL;
     
     while(sectors--)
     {
         if(ESUCCESS != SectorErase(addr))
             return -EIO;
         addr = addr+W25Q64_SECTOR_SIZE;
     }
     return ESUCCESS;
    
}



static int W25Q64Write(struct W25QDev *ptdev, unsigned int addr, unsigned char *wbuf, unsigned int length)
{
    
    if((NULL == ptdev)||(NULL == wbuf)||(W25Q64_SIZE<addr)||(0==length))
        return -EINVAL;
    if(W25Q64_SIZE < length)
        length = W25Q64_SIZE;
    unsigned int init_len = length;
    
    //计算要擦出的扇区个数
    unsigned char dwSectorCount = (length + addr%W25Q64_SECTOR_SIZE)/W25Q64_SECTOR_SIZE +1;
    
    //擦除扇区
    
    if(ESUCCESS != W25Q64Erase(ptdev,addr,dwSectorCount))
        return -EIO;
    
    
    //分页写
    //计算要写的页
    unsigned char dwPageCount = (length + addr%W25Q64_PAGE_SIZE)/W25Q64_PAGE_SIZE +1;
    if(1 == dwPageCount)
    {
        if(length != PageWrite(addr,wbuf,length))
            return -EIO;
    }
    else{
        //计算第一页还能填充的数据
        unsigned short dwFirstBytes = 256 - addr%256;
        //在第一页填充数据  
        if(dwFirstBytes != PageWrite(addr,wbuf,dwFirstBytes))
            return -EIO;
        //偏移地址 和 写buf指针
        addr = addr + dwFirstBytes;
        wbuf = wbuf + dwFirstBytes;
        length = length - dwFirstBytes;
        while(length)
        {
            if(length > W25Q64_PAGE_SIZE)
            {
                if(W25Q64_PAGE_SIZE != PageWrite(addr,wbuf,W25Q64_PAGE_SIZE))
                    return -EIO;
                //偏移地址 和 写buf指针
                addr = addr + W25Q64_PAGE_SIZE;
                wbuf = wbuf + W25Q64_PAGE_SIZE;
                length = length - W25Q64_PAGE_SIZE;
            }else
            {
                if(length != PageWrite(addr,wbuf,length))
                    return -EIO;
                length = 0;
            }
            
            
            
        }
        
        
        
    }
   
    
    return (int)init_len;
    
    
}


static int W25Q64Read(struct W25QDev *ptdev, unsigned int addr, unsigned char *rbuf, unsigned int length)
{
    if((NULL == ptdev)||(W25Q64_SIZE<addr)||(0==length))
        return -EINVAL;
    if(W25Q64_SIZE < length)
        length = W25Q64_SIZE;
    GPIO_Device * pCS = GPIODevFind("W25Q64 CS");
    if(NULLDEV == pCS)
        return -EIO;
    SPIDevice * pS1 = SPIDevFind("SPI");
    if(NULLDEV == pS1)
        return -EIO;
    
    
    unsigned char data[4];
    data[0] = W25X_ReadData;
    data[1] = (addr&0xFF0000) >> 16;
    data[2] = (addr&0x00FF00) >> 8;
    data[3] = (addr&0x0000FF) >> 0;
    
    pCS->Write(pCS,0); 
    
    int len = pS1->Write(pS1,data,4);
    if(4 != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    len = pS1->Read(pS1,rbuf,length);
    if(length != len)
    {
        pCS->Write(pCS,1);
        return -EIO;
    }
    
    pCS->Write(pCS,1);
    
    return (int)length;
    
}

