

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_ByteCopy(uint8 * dest, const uint8 * src, uint32 Len)
{

    rba_BswSrv_MemCopy8(dest,src,Len);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

