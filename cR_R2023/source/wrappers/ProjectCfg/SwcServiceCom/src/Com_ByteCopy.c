

#include "Com_Prv.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_ByteCopy(P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) dest,
                                 P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) src,
                                 VAR(uint32, AUTOMATIC) Len)
{

    rba_BswSrv_MemCopy8(dest,src,Len);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

