#include "devices.h"
#include "w25qxx.h"
#include "my_type.h"
#include "libs.h"
#include "stdlib.h"
#include "stm32f4xx_hal.h"

static unsigned char wbuf[20480] = {0};
static unsigned char rbuf[20480] = {0};

void w25q64_test()
{
    GPIODevRegister();
    UARTDevRegister();
    SPIDevRegister();
    
    
    W25QDevice * W25Q64= GetW25Q64Device();
    if(NULLDEV == W25Q64)
        return;
    
    W25Q64->Init(W25Q64);
    for(unsigned int i=0;i<20480;i++)
        wbuf[i] = i+10;
    unsigned int tick = HAL_GetTick();
    unsigned int addr = rand()%256;
    xprintf("addr is %d\r\n",addr);
    if(20480 != W25Q64->Write(W25Q64,addr,wbuf,20480))
        return;
    xprintf("Write 20480 bytes by SPI Time: %d\r\n", HAL_GetTick() - tick);
    
    
    tick = HAL_GetTick();
    if(256 != W25Q64->Read(W25Q64,addr,rbuf,256))
        return;
    xprintf("Write 20480 bytes by SPI Time: %d\r\n", HAL_GetTick() - tick);
    for(unsigned int i=0;i<256;i++)
    {
        if((i%16)==0 && i!=0)
        {
            xprintf("\r\n");
        }
        xprintf("0x%X\t",rbuf[i]);
    }
    xprintf("\r\n");
    
    
    
}
