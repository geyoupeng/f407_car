

typedef struct RingBuffInfo
{
    /* data */
    unsigned char *pHead;                           /*buffer start address*/

    unsigned char *pEnd;                            /*buffer end address*/

    unsigned char *pValid;                           /*buffer end address*/

    unsigned char *pValidEnd;                        /*buffer end address*/

    unsigned int nBuffLength;                         /*buffer length*/

    unsigned int nValidLength;                        /*Valid data length*/
}RingBuffInfo;




typedef struct RingBuff
{
    /* data */

    RingBuffInfo info;


    int (*Write)(struct RingBuff *ptBuf,const unsigned char *src,unsigned int length);

    int (*Read)(struct RingBuff *ptBuf,unsigned char *dst,unsigned int length);

    int (*Clear)(struct RingBuff *ptBuf);

    int (*Free)(struct RingBuff *ptBuf);

    struct RingBuff *next;
}RingBuff;



RingBuff *RingBuffNew(unsigned char length);





