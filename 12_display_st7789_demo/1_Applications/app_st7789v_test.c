#include "dev_display.h"
#include "devices.h"
#include "my_type.h"
#include "errno.h"
#include "libs.h"

unsigned short buf[50*50] = {0};
void clearScreen(unsigned short color);
void app_st7789_test()
{
    SPIDevRegister();
    GPIODevRegister();
    UARTDevRegister();
    
    DisplayDevice * st7789 = GetST7789V();
    
    if(NULLDEV == st7789)
        return;
    
    if(ESUCCESS != st7789->Init(st7789))
        return;
    st7789->FBBase = (unsigned short *)buf;
    
    st7789->SetDisplayWindow(st7789,0,0,50,50);
    
    for(unsigned int x = 0;x<50;x++)
    {
        for(unsigned int y = 0;y<50;y++)
            st7789->SetPixel(st7789,x,y,0x2444);
    }
    
    st7789->Flush(st7789);
    mdelay(1000);
//    unsigned short color = 0xFFFF;
//    while(1)
//    {
//        
//        clearScreen(color);
//        color = color -0xf;
//        mdelay(1);
//    }
    
}


void clearScreen(unsigned short color)
{
    DisplayDevice * st7789 = GetST7789V();    
    if(NULLDEV == st7789)
        return;
    unsigned short nbuf[240] = {0};
    for(unsigned int i = 0;i<240;i++)
        nbuf[i] = color;
    st7789->FBBase = nbuf;
    for(unsigned int i=0;i<360;i++)
    {
        st7789->SetDisplayWindow(st7789,0,i,240,i+1);
        st7789->Flush(st7789);
    }
        
}   
