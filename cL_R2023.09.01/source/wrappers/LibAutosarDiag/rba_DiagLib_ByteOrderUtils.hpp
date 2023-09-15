

#ifndef RBA_DIAGLIB_BYTEORDERUTILS_H
#define RBA_DIAGLIB_BYTEORDERUTILS_H

#include "Std_Types.hpp"
#include "Compiler.hpp"
#include "rba_BswSrv.hpp"

#define RBA_DIAGLIB_START_SEC_CODE
#include "rba_DiagLib_MemMap.hpp"

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_SwapByteOrderS(uint16 val)
{
    return rba_BswSrv_ByteOrderSwap16(val);
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_SwapByteOrderL(uint32 val)
{
    return rba_BswSrv_ByteOrderSwap32(val);
}

LOCAL_INLINE boolean rba_DiagLib_ByteOrderUtils_IsBigEndian(void){
   boolean isBigEndian = TRUE;
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
   isBigEndian = FALSE;
#endif
    return isBigEndian;
}

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_Htons(uint16 val)
{
   uint16 ret = val;
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderS(val);
#endif
    return ret;
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_Htonl(uint32 val)
{
   uint32 ret = val;
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderL(val);
#endif
    return ret;
}

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_Ntohs(uint16 val)
{
   uint16 ret = val;
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderS(val);
#endif
    return ret;
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_Ntohl(uint32 val)
{
   uint32 ret = val;
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderL(val);
#endif
    return ret;
}

//this function is only necessary until another function is implemented
//it is only temporarely necessary for the coverage and misra tests
boolean rba_DiagLib_ByteOrderUtils_Dummy(void);

#define RBA_DIAGLIB_STOP_SEC_CODE
#include "rba_DiagLib_MemMap.hpp"

#endif
