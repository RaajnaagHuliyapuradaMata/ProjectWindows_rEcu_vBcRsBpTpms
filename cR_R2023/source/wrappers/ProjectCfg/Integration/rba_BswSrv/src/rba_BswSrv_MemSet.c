
#include "rba_BswSrv.h"

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.h"

void* rba_BswSrv_MemSet(void* xDest_pv, sint32 xPattern_u32, uint32 numBytes_u32)
{

    uint32  adDest_u32 = (uint32)xDest_pv;
    uint32* xDest_pu32;
    uint16* xDest_pu16;
    uint8* xDest_pu8;
    uint8  xPattern_u8  = (uint8)xPattern_u32;
    uint32 ctLoop_u32;

    xPattern_u32 = xPattern_u8 + (xPattern_u8 << 8) + (xPattern_u8 << 16) + (xPattern_u8 << 24);

    if ((numBytes_u32 >= 1) && ((adDest_u32 & 0x01) != 0))
    {

        xDest_pu8 = (uint8*)adDest_u32;
        numBytes_u32 -= 1;
        *xDest_pu8 = (uint8)xPattern_u32;
        adDest_u32++;
    }

    if ((numBytes_u32 >= 2) && ((adDest_u32 & 0x02) != 0))
    {

        xDest_pu16 = (uint16*)adDest_u32;
        numBytes_u32 -= 2;
        *xDest_pu16 = (uint16)xPattern_u32;
        adDest_u32 += 2;
    }

    xDest_pu32 = (uint32*)adDest_u32;
    if (numBytes_u32 >= 4)
    {
        ctLoop_u32 = numBytes_u32 / 4;
        numBytes_u32 &= 0x03;
        do
        {
            *xDest_pu32 = (uint32)xPattern_u32;
            xDest_pu32++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }

    xDest_pu16 = (uint16*)xDest_pu32;
    if (numBytes_u32 >= 2)
    {
        numBytes_u32 -= 2;
        *xDest_pu16 = (uint16)xPattern_u32;
        xDest_pu16++;
    }

    xDest_pu8 = (uint8*)xDest_pu16;
    if(numBytes_u32 > 0)
    {
        *xDest_pu8 = (uint8)xPattern_u32;
    }
    return xDest_pv;
}

#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.h"

