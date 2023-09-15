

#ifndef ECUM_PRV_RTEACTIONS_H
#define ECUM_PRV_RTEACTIONS_H

#include "EcuM_Types.hpp"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

extern FUNC(void, ECUM_CODE) EcuM_Lok_RteModeSwitch ( VAR(Rte_ModeType_EcuM_Mode, AUTOMATIC) Mode);

extern FUNC(uint8, ECUM_CODE ) EcuM_Lok_GetRteMode(void);

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

#endif

#endif
