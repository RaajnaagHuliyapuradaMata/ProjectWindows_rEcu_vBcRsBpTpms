

#include "EcuM_Cfg.hpp"                       //for the macro ECUM_CFG_ECUC_RB_RTE_IN_USE
#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#include "EcuM.hpp"
#else
#include "Rte_EcuM.hpp"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE
#include "EcuM_Lok_RteActions.hpp"            // for function prototypes of EcuM_Lok_RteModeSwitch,EcuM_Lok_GetRteMode

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"

void EcuM_Lok_RteModeSwitch( Rte_ModeType_EcuM_Mode Mode)
{
   uint8 mode;
    mode = Mode;

    (void)Rte_Switch_currentMode_currentMode((mode));      //Return value not required
}

uint8 EcuM_Lok_GetRteMode(void){
   uint8 return_value;

    return_value = Rte_Mode_currentMode_currentMode();

    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

#else

#endif

