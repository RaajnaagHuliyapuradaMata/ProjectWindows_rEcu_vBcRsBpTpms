

#include "Com_Prv.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ByteCopyInit(uint8 * dest, uint32 Init_Val, uint32 Length)
{
    while(Length > COM_ZERO)
    {
        *(dest) = (uint8)(Init_Val >> (8UL*(Length-1UL)));
        dest++;
        --Length;
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

