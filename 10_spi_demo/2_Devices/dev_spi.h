#ifndef __DEV_SPI_H
#define __DEV_SPI_H

typedef struct SPIDev{
    
    char *name;
    unsigned char channel;
    int (*Init)(struct SPIDev *ptDev);
    int (*Write)(struct SPIDev *ptDev,unsigned char *wbuf,unsigned int length);
    int (*Read)(struct SPIDev *ptDev,unsigned char *rbuf,unsigned int length);
    int (*WriteRead)(struct SPIDev *ptDev,unsigned char *wbuf,unsigned char *rbuf,unsigned int length);
    struct SPIDev *next;    
}SPIDevice;


void SPIDevRegister(void);
int SPIDevInsert(SPIDevice *ptDev);
SPIDevice * SPIDevFind(char *name);

#endif /* __DEV_SPI_H */
