#include "devices.h"
#include "my_type.h"




void test_key_app()
{
    GPIODevRegister();
    GPIO_Device * D1 = GPIODevFind("D1");
    if(NULLDEV == D1)
        return;
    GPIO_Device * D2 = GPIODevFind("D2");
    if(NULLDEV == D2)
        return;
    GPIO_Device * D3 = GPIODevFind("D3");
    if(NULLDEV == D3)
        return;
    GPIO_Device * D4 = GPIODevFind("D4");
    if(NULLDEV == D4)
        return;
    GPIO_Device * K1 = GPIODevFind("K1");
    if(NULLDEV == K1)
        return;
    GPIO_Device * K2 = GPIODevFind("K2");
    if(NULLDEV == K2)
        return;
    GPIO_Device * K3 = GPIODevFind("K3");
    if(NULLDEV == K3)
        return;
    GPIO_Device * K4 = GPIODevFind("K4");
    if(NULLDEV == K4)
        return;
    K1->Init(K1);
    K1->Init(K2);
    K1->Init(K3);
    K1->Init(K4);
    D1->Init(D1);
    D1->Init(D2);
    D1->Init(D3);
    D1->Init(D4);
    int tmp;
    while(1)
    {
        if( 0 == K1->Read(K1))
        {
            tmp = D1->Read(D1);
            tmp = !tmp;
            D1->Write(D1,tmp);
        }
        if( 0 == K2->Read(K2))
        {
            tmp = D2->Read(D2);
            tmp = !tmp;
            D2->Write(D2,tmp);
        }
        if( 0 == K3->Read(K3))
        {
            tmp = D3->Read(D3);
            tmp = !tmp;
            D3->Write(D3,tmp);
        }
        if( 0 == K4->Read(K4))
        {
            tmp = D4->Read(D4);
            tmp = !tmp;
            D4->Write(D4,tmp);
        }
        
    }
}
