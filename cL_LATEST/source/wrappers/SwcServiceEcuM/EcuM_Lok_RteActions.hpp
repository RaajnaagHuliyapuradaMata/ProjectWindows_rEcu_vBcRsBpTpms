

#ifndef ECUM_PRV_RTEACTIONS_H
#define ECUM_PRV_RTEACTIONS_H

#include "EcuM_Types.hpp"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"

extern void EcuM_Lok_RteModeSwitch ( Rte_ModeType_EcuM_Mode Mode);

extern uint8 EcuM_Lok_GetRteMode(void);

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

#endif

#endif
