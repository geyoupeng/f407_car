#include "devices.h"
#include "my_type.h"
#include "string.h"
#include "libs.h"
#include "stm32f4xx_hal.h"

void app_uart_test()
{
    UARTDevRegister();
    GPIODevRegister();
    UARTDevice * UartDebug =  UARTDevFind("UART DEBUG");
    if(NULLDEV == UartDebug)
        return;
    GPIO_Device * D1 =  GPIODevFind("D1");
    if(NULLDEV == D1)
        return;
    
    
    GPIO_Device * K1 =  GPIODevFind("K1");
    if(NULLDEV == K1)
        return;
    D1->Init(D1);
    K1->Init(K1);
    UartDebug->Init(UartDebug);
    int KeyStatus;
    char *str = "Hello World!";
    char *str1 = "Key is pressed";
    //char *str2 = "D1 OFF";
    char ch;
    //UartDebug->Write(UartDebug,(unsigned char *)str,strlen(str));
    xprintf("hello world\r\n%s\r\n",str);
    while(1)
    {
        KeyStatus = K1->Read(K1);
        if(0 == KeyStatus)
        {
            HAL_Delay(50);
            if(0 == KeyStatus)
                UartDebug->Write(UartDebug,(unsigned char *)str1,strlen(str1));
        }  
        UartDebug->Read(UartDebug,(unsigned char *)&ch,1);
        if(('c' == ch) || ('C' == ch))
        {
            D1->Write(D1,0);
        }
        if(('s' == ch) || ('S' == ch))
        {
            D1->Write(D1,1);
        }
    }
    
}
