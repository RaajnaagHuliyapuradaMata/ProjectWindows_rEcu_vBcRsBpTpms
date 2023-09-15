#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_ByteCopyInit(P2VAR(uint8,AUTOMATIC, COM_APPL_DATA) dest
   ,     VAR(uint32, AUTOMATIC) Init_Val
   ,     VAR(uint32, AUTOMATIC) Len)
{
   while(Len > (uint32)0)
   {
        *(dest) = (uint8)(Init_Val >> (8UL*(Len-1UL)));
        dest++;
        --Len;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

