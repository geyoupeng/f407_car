#ifndef __GPIO_CONFIG_H
#define __GPIO_CONFIG_H


#define PCS                  \
{                           \
    .name = "LCD CS",           \
    .value = 1,             \
    .port = GPIOD,          \
    .pin = GPIO_PIN_3,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define PDCX                  \
{                           \
    .name = "LCD pDCX",           \
    .value = 1,             \
    .port = GPIOF,          \
    .pin = GPIO_PIN_9,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define PRST                  \
{                           \
    .name = "LCD pRST",           \
    .value = 1,             \
    .port = GPIOG,          \
    .pin = GPIO_PIN_15,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define PBACK                  \
{                           \
    .name = "LCD pBACK",           \
    .value = 1,             \
    .port = GPIOE,          \
    .pin = GPIO_PIN_6,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define D1                  \
{                           \
    .name = "D1",           \
    .value = 1,             \
    .port = GPIOB,          \
    .pin = GPIO_PIN_12,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define D2                  \
{                           \
    .name = "D2",           \
    .value = 1,             \
    .port = GPIOB,          \
    .pin = GPIO_PIN_13,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,   \
    .next = NULL           \
}                           \


#define D3                  \
{                           \
    .name = "D3",           \
    .value = 1,             \
    .port = GPIOB,          \
    .pin = GPIO_PIN_14,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL            \
}                           \

#define D4                  \
{                           \
    .name = "D4",           \
    .value = 1,             \
    .port = GPIOB,          \
    .pin = GPIO_PIN_15,     \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,  \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define K1                  \
{                           \
    .name = "K1",           \
    .value = 1,             \
    .port = GPIOA,          \
    .pin = GPIO_PIN_0,      \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIOIrqDrvRead,    \
    .next = NULL            \
}                           \


#define K2                  \
{                           \
    .name = "K2",           \
    .value = 1,             \
    .port = GPIOA,          \
    .pin = GPIO_PIN_1,      \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIOIrqDrvRead,    \
    .next = NULL            \
}                           \


#define K3                  \
{                           \
    .name = "K3",           \
    .value = 1,             \
    .port = GPIOA,          \
    .pin = GPIO_PIN_2,      \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIOIrqDrvRead,    \
    .next = NULL            \
}                           \

#define K4                  \
{                           \
    .name = "K4",           \
    .value = 1,             \
    .port = GPIOA,          \
    .pin = GPIO_PIN_3,      \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIOIrqDrvRead,    \
    .next = NULL            \
}                           \



#define pCS                  \
{                           \
    .name = "W25Q64 CS",           \
    .value = 1,             \
    .port = GPIOA,          \
    .pin = GPIO_PIN_15,      \
    .Init = GPIODrvInit,    \
    .Write = GPIODrvWrite,     \
    .Read = GPIOIrqDrvRead,    \
    .next = NULL            \
}                           \



#endif   /* __GPIO_CONFIG_H */
