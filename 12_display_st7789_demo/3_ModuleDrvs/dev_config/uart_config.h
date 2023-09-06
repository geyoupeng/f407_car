#ifndef __UART_CONFIG_H
#define __UART_CONFIG_H



#define UART_DEBUG          \
{                           \
    .name = "UART DEBUG",   \
    .channel = 1,          \
    .Init = UARTDrvInit,    \
    .Write = UARTDrvWrite,  \
    .Read = UARTDrvRead,    \
    .next = NULL            \
}   






#endif /* __UART_CONFIG_H */
