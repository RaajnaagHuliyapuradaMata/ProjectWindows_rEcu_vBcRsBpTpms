

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
Com_StatusType Com_GetStatus(void){

    return Com_Uninit_Flag;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

