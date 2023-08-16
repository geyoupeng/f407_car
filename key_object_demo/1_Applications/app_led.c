#include "devices.h"
#include "my_type.h"
#include "errno.h"
#include "stm32f4xx_hal.h"



void app_led_test()
{
    
    GPIODevice *  pD1= GPIODevFind("D1");
    if(NULLDEV == pD1 )
        return;
    
    if(ESUCCESS != pD1->Init(pD1))
        return;
    int status;
    while(1)
    {
        status = pD1->Read(pD1);
        status = !status;
        pD1->Write(pD1,status);
        HAL_Delay(500);
    }
    
}
