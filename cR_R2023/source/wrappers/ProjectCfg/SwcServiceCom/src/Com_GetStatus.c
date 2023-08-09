

#include "Com_Prv.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void)
{
    return Com_Uninit_Flag;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

