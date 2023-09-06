#include "ring_buffer.h"
#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static int RingBuffWrite(RingBuff *ptBuff,const unsigned char *src,unsigned int length);
static int RingBuffRead(RingBuff *ptBuff,unsigned char *dst,unsigned int length);
static int RingBuffClear(RingBuff *ptBuff);
static int RingBuffFree(RingBuff *ptBuff);



RingBuff * RingBuffNew(unsigned char length)
{
    if(0 == length)
        return NULL;

    RingBuff *ptBuff = (RingBuff *)malloc(sizeof(RingBuff));

    if(NULL == ptBuff)
        return NULL;
    if(NULL != ptBuff->info.pHead)
        free((unsigned char *)ptBuff->info.pHead);

    ptBuff->info.pHead =  (unsigned char *)malloc(length);

    ptBuff->info.pEnd = ptBuff->info.pHead + length;

    ptBuff->info.pValid = ptBuff->info.pHead;

    ptBuff->info.pValidEnd= ptBuff->info.pHead;
    
    ptBuff->info.nBuffLength = length;
    
    ptBuff->info.nValidLength = 0;

    ptBuff->Write = RingBuffWrite;

    ptBuff->Read = RingBuffRead;

    ptBuff->Clear = RingBuffClear;

    ptBuff->Free = RingBuffFree;

    return ptBuff;

}



int RingBuffWrite(RingBuff *ptBuff,const unsigned char *src,unsigned int length)
{
    unsigned int len1 = 0,len2 = 0;
    //unsigned int move_len = 0;
    if (NULL == ptBuff)
    {
        return -EINVAL;
    }
    if (length > ptBuff->info.nBuffLength)
    {
        return -EINVAL;
    }
    if (NULL == ptBuff->info.pHead)
    {
        return -EINVAL;
    }
    
    if (ptBuff->info.pEnd < (ptBuff->info.pValidEnd + length))
    {
        len1 = (unsigned int)(ptBuff->info.pEnd - ptBuff->info.pValidEnd);
        len2 = length - len1;

        memcpy(ptBuff->info.pValidEnd,src,len1);

        memcpy(ptBuff->info.pHead,(void *)((unsigned int)src+(unsigned int)len1),len2);

        ptBuff->info.pValidEnd = (unsigned char *)((unsigned int)(ptBuff->info.pHead) + len2);
    }
    else
    {
        len1 = length;
        len2 = 0;

        memcpy(ptBuff->info.pValidEnd,src,len1);
        ptBuff->info.pValidEnd = (unsigned char *)((unsigned int)(ptBuff->info.pValidEnd) + len1);
    }

    if (ptBuff->info.nBuffLength < (ptBuff->info.nValidLength+length))
    {
        ptBuff->info.pValid = ptBuff->info.pValidEnd;
        ptBuff->info.nValidLength = ptBuff->info.nBuffLength;
    }
    else
    {
        ptBuff->info.nValidLength = ptBuff->info.nValidLength + length;

    }
    
    return (int)length; 
}
int RingBuffRead(RingBuff *ptBuff,unsigned char *dst,unsigned int length)
{
    unsigned int len1 = 0,len2 = 0;
    if (NULL == ptBuff)
    {
        return -EINVAL;
    }
    if (NULL == ptBuff->info.pHead)
    {
        return -EINVAL;
    }

    if (0 == ptBuff->info.nValidLength)
    {
        return -ENOMEM;
    }

    if (length > ptBuff->info.nValidLength)
    {
        length = ptBuff->info.nValidLength;
    }

    if (ptBuff->info.pEnd < (ptBuff->info.pValid + length))
    {
        len1 = (unsigned int)(ptBuff->info.pEnd - ptBuff->info.pValid);
        len2 = length - len1;
        memcpy(dst,ptBuff->info.pValid,len1);
        memcpy((unsigned char *)((unsigned int)dst+len1),ptBuff->info.pHead,len2);

        ptBuff->info.pValid = (unsigned char *)((unsigned int)ptBuff->info.pHead + len2);
    }
    else
    {
        memcpy(dst,ptBuff->info.pValid,length);

        ptBuff->info.pValid = (unsigned char *)((unsigned int)ptBuff->info.pValid + length);
    }
    
    ptBuff->info.nValidLength-=length;
    return (int)length;
}
int RingBuffClear(RingBuff *ptBuff)
{
    if (NULL == ptBuff)
    {
        return -EINVAL;
    }
    if (NULL == ptBuff->info.pHead)
    {
        return -EINVAL;
    }else
    {
        memset(ptBuff->info.pHead,0,ptBuff->info.nBuffLength);
    }
    ptBuff->info.pValid = ptBuff->info.pValidEnd = ptBuff->info.pHead;
    ptBuff->info.nValidLength = 0;
    return EXIT_SUCCESS;
}

int RingBuffFree(RingBuff *ptBuff)
{
     if (NULL == ptBuff)
    {
        return -EINVAL;
    }
    if (NULL == ptBuff->info.pHead)
    {
        return -EINVAL;
    }else
    {
        free(ptBuff->info.pHead);
    }
    free(ptBuff);

    ptBuff->info.nBuffLength = 0;

    ptBuff->info.nValidLength = 0;

    ptBuff->info.pEnd = NULL;

    ptBuff->info.pHead = NULL;

    ptBuff->info.pValid = NULL;

    ptBuff->info.pValidEnd = NULL;

    return EXIT_SUCCESS;
}
