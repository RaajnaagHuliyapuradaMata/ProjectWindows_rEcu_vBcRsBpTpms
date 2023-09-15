#ifndef ECUM_CBK_H
#define ECUM_CBK_H

#include "EcuM_Types.hpp"
#include "EcuM_Generated_Types.hpp"
#include "EcuM_Cfg_Version.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
extern FUNC(void, ECUM_CODE ) EcuM_SetWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );
extern FUNC(void, ECUM_CODE ) EcuM_ValidateWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_CheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(void , ECUM_CODE ) EcuM_EndCheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );
#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

#endif

