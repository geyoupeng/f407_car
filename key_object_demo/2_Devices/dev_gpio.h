#ifndef __DEV_GPIO_H_
#define __DEV_GPIO_H_


typedef struct GPIODev{
    
    char *name;
    
    void *port;
    
    unsigned int pin;
    
    int (*Init)(struct GPIODev *ptdev);
    
    int (*Write)(struct GPIODev *ptdev,unsigned char status);
    
    int (*Read)(struct GPIODev *ptdev);
    
    struct GPIODev *next;
}GPIODevice;



void GPIODevRegister(void);
void GPIODevInsert(GPIODevice *pDevices);
GPIODevice * GPIODevFind(char *name);


#endif /* __DEV_GPIO_H_ */
