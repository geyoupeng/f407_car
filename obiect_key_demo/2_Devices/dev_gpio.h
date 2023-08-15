#ifndef __DEV_GPIO_H
#define __DEV_GPIO_H


typedef struct GPIO_Dev{
    
    char *name;
    
    void *port;
    
    unsigned int pin;
    
    int (*Init)(struct GPIO_Dev *ptDev);
    
    int (*Write)(struct GPIO_Dev *ptDev,int status);
    
    int (*Read)(struct GPIO_Dev *ptDev);
    
    struct GPIO_Dev *next;
}GPIO_Device;


void GPIODevRegister(void);
int GPIODevInsert(GPIO_Device *ptDev);
GPIO_Device *GPIODevFind(char *name);


#endif  /*__DEV_GPIO_H*/
