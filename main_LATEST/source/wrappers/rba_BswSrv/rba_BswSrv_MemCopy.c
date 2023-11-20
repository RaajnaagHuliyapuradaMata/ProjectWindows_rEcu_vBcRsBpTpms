#include "Std_Types.hpp"

#include "rba_BswSrv.hpp"

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.hpp"
void* LibAutosar_vptrMemCopy(void* xDest_pv, const void* xSrc_pcv, uint32 numBytes_u32)
{
   uint32* xDest_pu32       = (uint32*)xDest_pv;
   const uint32* xSrc_pcu32 = (const uint32*)xSrc_pcv;
   uint16* xDest_pu16;
   const uint16* xSrc_pcu16;
   uint8* xDest_pu8;
   const uint8* xSrc_pcu8;
   uint32 ctLoop_u32;

   if((numBytes_u32 >= 4) && ((((uint32)xDest_pu32 | (uint32)xSrc_pcu32) & 0x03) == 0))
   {
        ctLoop_u32 = numBytes_u32 / 4;
        numBytes_u32 &= 0x03;
        do
        {
            *xDest_pu32 = *xSrc_pcu32;
            xDest_pu32++;
            xSrc_pcu32++;
            ctLoop_u32--;
        }while(ctLoop_u32 > 0);
   }

    xDest_pu16 = (uint16*)xDest_pu32;
    xSrc_pcu16 = (const uint16*)xSrc_pcu32;

   if((numBytes_u32 >= 2) && ((((uint32)xDest_pu16 | (uint32)xSrc_pcu16) & 0x01) == 0))
   {
        ctLoop_u32 = numBytes_u32 / 2;
        numBytes_u32 &= 0x01;
        do
        {
            *xDest_pu16 = *xSrc_pcu16;
            xDest_pu16++;
            xSrc_pcu16++;
            ctLoop_u32--;
        }while(ctLoop_u32 > 0);
   }

    xDest_pu8 = (uint8*)xDest_pu16;
    xSrc_pcu8 = (const uint8*)xSrc_pcu16;

   for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
   {
        *xDest_pu8 = *xSrc_pcu8;
        xDest_pu8++;
        xSrc_pcu8++;
   }
    return xDest_pv;
}

#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.hpp"

