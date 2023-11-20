#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void){
    return Com_Uninit_Flag;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

