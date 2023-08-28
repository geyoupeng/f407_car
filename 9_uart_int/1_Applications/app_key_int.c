#include "devices.h"
#include "my_type.h"
#include "errno.h"




void test_key_int()
{
    
    GPIODevRegister();
    
    GPIO_Device * pK1 = GPIODevFind("K1");
    if(NULLDEV == pK1)
        return;
     GPIO_Device * pD1 = GPIODevFind("D1");
    if(NULLDEV == pD1)
        return;
    pK1->Init(pK1);
    pD1->Init(pD1);
    int status = 0;
    while(1)
    {
        status = pK1->Read(pK1);
        if(ESUCCESS == status)
            pD1->Write(pD1,pK1->value);
    }
    
    
}
