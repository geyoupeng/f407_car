#ifndef __DEV_CONFIG_H
#define __DEV_CONFIG_H


#define D1                    \
{                             \
    .name = "D1",             \
    .port = GPIOB,            \
    .pin = GPIO_PIN_12,       \
    .Init = GPIODrvInit,      \
    .Write = GPIODrvWrite,    \
    .Read = GPIODrvRead,      \
    .next = NULL              \
}                             \



#define D2                    \
{                             \
    .name = "D2",             \
    .port = GPIOB,            \
    .pin = GPIO_PIN_13,       \
    .Init = GPIODrvInit,      \
    .Write = GPIODrvWrite,    \
    .Read = GPIODrvRead,      \
    .next = NULL              \
}                             \


#define D3                    \
{                             \
    .name = "D1",             \
    .port = GPIOB,            \
    .pin = GPIO_PIN_14,       \
    .Init = GPIODrvInit,      \
    .Write = GPIODrvWrite,    \
    .Read = GPIODrvRead,      \
    .next = NULL              \
}                             \

#define D4                    \
{                             \
    .name = "D1",             \
    .port = GPIOB,            \
    .pin = GPIO_PIN_15,       \
    .Init = GPIODrvInit,      \
    .Write = GPIODrvWrite,    \
    .Read = GPIODrvRead,      \
    .next = NULL              \
}                             \


#endif /* __DEV_CONFIG_H */