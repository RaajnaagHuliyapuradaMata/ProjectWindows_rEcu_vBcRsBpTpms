
#include "rba_BswSrv.h"

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.h"

sint32 rba_BswSrv_MemCompare(const void* xSrc1_pcv, const void* xSrc2_pcv, uint32 numBytes_u32)
{
    const uint32* xSrc1_pcu32 = (const uint32*)xSrc1_pcv;
    const uint32* xSrc2_pcu32 = (const uint32*)xSrc2_pcv;
    const uint16* xSrc1_pcu16;
    const uint16* xSrc2_pcu16;
    const uint8* xSrc1_pcu8;
    const uint8* xSrc2_pcu8;
    uint32 ctLoop_u32;
    uint32 xTemp1_u32;
    uint32 xTemp2_u32;
    uint16 xTemp1_u16;
    uint16 xTemp2_u16;

    if ((numBytes_u32 >= 4) && ((((uint32)xSrc1_pcu32 | (uint32)xSrc2_pcu32) & 0x03) == 0))
    {
        ctLoop_u32 = numBytes_u32 / 4;
        numBytes_u32 &= 0x03;
        do
        {
            if(*xSrc1_pcu32 != *xSrc2_pcu32)
            {
                numBytes_u32 = 4;
                xTemp1_u32 = *xSrc1_pcu32;
                xTemp2_u32 = *xSrc2_pcu32;
                xSrc1_pcu32 = &xTemp1_u32;
                xSrc2_pcu32 = &xTemp2_u32;
                break;
            }
            xSrc1_pcu32++;
            xSrc2_pcu32++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }

    xSrc1_pcu16 = (const uint16*)xSrc1_pcu32;
    xSrc2_pcu16 = (const uint16*)xSrc2_pcu32;

    if ((numBytes_u32 >= 2) && ((((uint32)xSrc1_pcu16 | (uint32)xSrc2_pcu16) & 0x01) == 0))
    {
        ctLoop_u32 = numBytes_u32 / 2;
        numBytes_u32 &= 0x01;
        do
        {
            if(*xSrc1_pcu16 != *xSrc2_pcu16)
            {
                numBytes_u32 = 2;
                xTemp1_u16 = *xSrc1_pcu16;
                xTemp2_u16 = *xSrc2_pcu16;
                xSrc1_pcu16 = &xTemp1_u16;
                xSrc2_pcu16 = &xTemp2_u16;
                break;
            }
            xSrc1_pcu16++;
            xSrc2_pcu16++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }

    xSrc1_pcu8 = (const uint8*)xSrc1_pcu16;
    xSrc2_pcu8 = (const uint8*)xSrc2_pcu16;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        if(*xSrc1_pcu8 != *xSrc2_pcu8)
        {
            return (*xSrc1_pcu8 - *xSrc2_pcu8);
        }
        xSrc1_pcu8++;
        xSrc2_pcu8++;
    }
    return 0;
}
#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.h"

