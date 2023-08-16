#ifndef __PRINTF_H
#define __PRINTF_H

#ifndef USE_PRINTF
    #define USE_PRINTF (1)
#endif


#ifndef USE_DEBUG
    #define USE_DEBUG (0)
#endif


#if USE_PRINTF
    #include <stdio.h>      
    #define xprintf(...)    printf(__VA_ARGS__)
#else
    #define xprintf(...)
#endif  /* USE_PRINTF */


#if USE_DEBUG
    #include <stdio.h>      
    #define DRVLOG(...)    printf(__VA_ARGS__)
#else
    #define DRVLOG(...)
#endif  /* USE_DEBUG */ 


#endif /* __PRINTF_H */
