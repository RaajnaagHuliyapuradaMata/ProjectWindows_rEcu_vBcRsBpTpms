#include "Std_Types.hpp"

#include "EcuM_Cfg.hpp"
#include "EcuM.hpp"
#include "EcuM_Lok_RteActions.hpp"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
FUNC(void, ECUM_CODE) EcuM_Lok_RteModeSwitch( VAR(Rte_ModeType_EcuM_Mode, AUTOMATIC) Mode)
{
   VAR(uint8, AUTOMATIC) mode;
    mode = Mode;

    (void)Rte_Switch_currentMode_EcuM_Mode(mode);
}

FUNC(uint8, ECUM_CODE ) EcuM_Lok_GetRteMode(void){
   VAR(uint8, AUTOMATIC) return_value;

    return_value = Rte_Mode_currentMode_EcuM_Mode();

    return return_value;
}
#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
#else
#endif

