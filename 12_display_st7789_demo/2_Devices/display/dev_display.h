#ifndef __DEV_DISPLAY_H_
#define __DEV_DISPLAY_H_

#define USE_ST7789V_DEVICE (1)

typedef struct DisplayDevice{
    char *name;
    void *FBBase;
    unsigned short wXres;
    unsigned short wYres;
    unsigned short wBpp;
    unsigned int dwSize;
    int (*Init)(struct DisplayDevice *ptDev);
    int (*DisplayON)(struct DisplayDevice *ptDev);
    int (*DisplayOFF)(struct DisplayDevice *ptDev);
    int (*SetDisplayWindow)(struct DisplayDevice *ptDev, \
                           unsigned short wXs,unsigned short wYs,   \
                           unsigned short wXe,unsigned short wYe);
                           
    int (*SetPixel)(struct DisplayDevice *ptDev, \
                   unsigned short wX,unsigned short wY,   \
                   unsigned short wColor);
    int (*Flush)(struct DisplayDevice *ptDev);
    
    
}DisplayDevice;



#if USE_ST7789V_DEVICE
    #include "dev_st7789v.h"
#endif










#endif  /*  __DEV_DISPLAY_H_ */
