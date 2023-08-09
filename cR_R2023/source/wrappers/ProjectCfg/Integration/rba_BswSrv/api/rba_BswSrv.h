
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef RBA_BSWSRV_H
#define RBA_BSWSRV_H

#include "Std_Types.h"

#define RBA_BSWSRV_VENDOR_ID   (6)
#define RBA_BSWSRV_MODULE_ID   (255)
#define RBA_BSWSRV_INSTANCE_ID (0)

#define RBA_BSWSRV_SW_MAJOR_VERSION (3)
#define RBA_BSWSRV_SW_MINOR_VERSION (0)
#define RBA_BSWSRV_SW_PATCH_VERSION (0)

#  define RBA_BSWSRV_PARAM_UNUSED(param)          (void)(param)
#  define RBA_BSWSRV_PRV_C_IMPL

typedef unsigned long long rba_BswSrv_uint64;

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.h"
extern void* rba_BswSrv_MemCopy(void* xDest_pv, const void* xSrc_pcv, uint32 numBytes_u32);
extern void* rba_BswSrv_MemSet(void* xDest_pv, sint32 xPattern_u32, uint32 numBytes_u32);
extern sint32 rba_BswSrv_MemCompare(const void* xSrc1_pcv, const void* xSrc2_pcv, uint32 numBytes_u32);
#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.h"

LOCAL_INLINE uint32 rba_BswSrv_ByteOrderSwap32(uint32 Input_u32);
LOCAL_INLINE uint16 rba_BswSrv_ByteOrderSwap16(uint16 Input_u16);
LOCAL_INLINE void   rba_BswSrv_MemCopy64(rba_BswSrv_uint64* xDest_pu64, const rba_BswSrv_uint64* xSrc_pcu64, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy32(uint32* xDest_pu32, const uint32* xSrc_pcu32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy16(uint16* xDest_pu16, const uint16* xSrc_pcu16, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy8(uint8* xDest_pu8, const uint8* xSrc_pcu8, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare64(const rba_BswSrv_uint64* xSrc1_pcu64, const rba_BswSrv_uint64* xSrc2_pcu64, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare32(const uint32* xSrc1_pcu32, const uint32* xSrc2_pcu32, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare16(const uint16* xSrc1_pcu16, const uint16* xSrc2_pcu16, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare8(const uint8* xSrc1_pcu8, const uint8* xSrc2_pcu8, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet64(rba_BswSrv_uint64* xDest_pu64, rba_BswSrv_uint64 xPattern_u64, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet32(uint32* xDest_pu32, uint32 xPattern_u32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet16(uint16* xDest_pu16, uint32 xPattern_u32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet8(uint8* xDest_pu8, uint32 xPattern_u32, uint32 numBytes_u32);

LOCAL_INLINE uint32 rba_BswSrv_ByteOrderSwap32(uint32 Input_u32)
{
    uint32 retVal_u32;

    retVal_u32 = (Input_u32 << 24) | ((Input_u32 & 0xFF00u) << 8) | ((Input_u32 & 0x00FF0000u) >> 8) | (Input_u32 >> 24);

    return retVal_u32;
}

LOCAL_INLINE uint16 rba_BswSrv_ByteOrderSwap16(uint16 Input_u16)
{
    uint16 retVal_u16;

    retVal_u16 = ((Input_u16 & 0x00FFu) << 8) | ((Input_u16 & 0xFF00u) >> 8);

    return retVal_u16;
}

LOCAL_INLINE void rba_BswSrv_MemCopy64(rba_BswSrv_uint64* xDest_pu64, const rba_BswSrv_uint64* xSrc_pcu64, uint32 numBytes_u32)
{

    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {
        *xDest_pu64 = *xSrc_pcu64;
        xDest_pu64++;
        xSrc_pcu64++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemCopy32(uint32* xDest_pu32, const uint32* xSrc_pcu32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {
        *xDest_pu32 = *xSrc_pcu32;
        xDest_pu32++;
        xSrc_pcu32++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemCopy16(uint16* xDest_pu16, const uint16* xSrc_pcu16, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {
        *xDest_pu16 = *xSrc_pcu16;
        xDest_pu16++;
        xSrc_pcu16++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemCopy8(uint8* xDest_pu8, const uint8* xSrc_pcu8, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = *xSrc_pcu8;
        xDest_pu8++;
        xSrc_pcu8++;
    }

    return;
}

LOCAL_INLINE uint32 rba_BswSrv_MemCompare64(const rba_BswSrv_uint64* xSrc1_pcu64, const rba_BswSrv_uint64* xSrc2_pcu64, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {

        if (*xSrc1_pcu64++ != *xSrc2_pcu64++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

LOCAL_INLINE uint32 rba_BswSrv_MemCompare32(const uint32* xSrc1_pcu32, const uint32* xSrc2_pcu32, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {

        if (*xSrc1_pcu32++ != *xSrc2_pcu32++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

LOCAL_INLINE uint32 rba_BswSrv_MemCompare16(const uint16* xSrc1_pcu16, const uint16* xSrc2_pcu16, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {

        if (*xSrc1_pcu16++ != *xSrc2_pcu16++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

LOCAL_INLINE uint32 rba_BswSrv_MemCompare8(const uint8* xSrc1_pcu8, const uint8* xSrc2_pcu8, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {

        if (*xSrc1_pcu8++ != *xSrc2_pcu8++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

LOCAL_INLINE void rba_BswSrv_MemSet64(rba_BswSrv_uint64* xDest_pu64, rba_BswSrv_uint64 xPattern_u64, uint32 numBytes_u32)
{

    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {
        *xDest_pu64 = xPattern_u64;
        xDest_pu64++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemSet32(uint32* xDest_pu32, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {
        *xDest_pu32 = xPattern_u32;
        xDest_pu32++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemSet16(uint16* xDest_pu16, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {
        *xDest_pu16 = (uint16)xPattern_u32;
        xDest_pu16++;
    }

    return;
}

LOCAL_INLINE void rba_BswSrv_MemSet8(uint8* xDest_pu8, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = (uint8)xPattern_u32;
        xDest_pu8++;
    }

    return;
}

#endif

