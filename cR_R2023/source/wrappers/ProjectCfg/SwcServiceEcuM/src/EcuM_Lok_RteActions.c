

#include "EcuM_Cfg.h"                       //for the macro ECUM_CFG_ECUC_RB_RTE_IN_USE
#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#include "EcuM.h"
#else
#include "Rte_EcuM.h"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE
#include "EcuM_Lok_RteActions.h"            // for function prototypes of EcuM_Lok_RteModeSwitch,EcuM_Lok_GetRteMode

#if (ECUM_CFG_MODE_HANDLING == STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

FUNC(void, ECUM_CODE) EcuM_Lok_RteModeSwitch( VAR(Rte_ModeType_EcuM_Mode, AUTOMATIC) Mode)
{
    VAR(uint8, AUTOMATIC) mode;
    mode = Mode;

    (void)Rte_Switch_currentMode_EcuM_Mode(mode);      //Return value not required
}

FUNC( uint8, ECUM_CODE ) EcuM_Lok_GetRteMode(void)
{
    VAR(uint8, AUTOMATIC) return_value;

    return_value = Rte_Mode_currentMode_EcuM_Mode();

    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#else

#endif

