#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void,COM_CODE) Com_ByteCopy(P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) dest
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) src
   ,     VAR(uint32, AUTOMATIC) Len)
{

    LibAutosar_vptrMemCopy8(dest,src,Len);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

