#include "my_delay.h"
#include "stm32f4xx_hal.h"



void mdelay(unsigned int msec)
{
    unsigned int timeout = msec;
    while(timeout)
    {
        unsigned int tick = 0;
        if(timeout >= (1<<24))
            tick = (1<<24) - 1;
        else
            tick = timeout;
        timeout = timeout - tick;
        HAL_Delay(tick);
    }
//    unsigned int tick = 0;
//    if(msec >= (1<<24))
//    {  
//       tick = (1<<24) - 1;
//    }else{   
//       tick = msec;
//    }
//    while(msec)
//    {
//        HAL_Delay(tick);
//        msec -= tick; 
//    }  
}

void secdelay(unsigned int sec)
{
    sec = sec * 1000;
    unsigned int tick;
    if(sec >= (1<<24))
    {  
       tick = (1<<24) - 1;
    }else{   
       tick = sec;
    }
    while(sec)
    {
        HAL_Delay(tick);
        sec -= tick; 
    }  
    
    
    
}
