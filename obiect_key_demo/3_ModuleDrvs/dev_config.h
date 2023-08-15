#ifndef __DEV_CONFIG_H
#define __DEV_CONFIG_H

#define D1                  \
{                           \
    .name = "D1",           \
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
    .port = GPIOA,          \
    .pin = GPIO_PIN_0,     \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define K2                  \
{                           \
    .name = "K2",           \
    .port = GPIOA,          \
    .pin = GPIO_PIN_1,     \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \


#define K3                  \
{                           \
    .name = "K3",           \
    .port = GPIOA,          \
    .pin = GPIO_PIN_2,     \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \

#define K4                  \
{                           \
    .name = "K4",           \
    .port = GPIOA,          \
    .pin = GPIO_PIN_3,     \
    .Init = GPIODrvInit,    \
    .Write = NULL,          \
    .Read = GPIODrvRead,    \
    .next = NULL           \
}                           \

#endif
