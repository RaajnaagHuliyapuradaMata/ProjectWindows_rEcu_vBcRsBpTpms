

#ifndef ECUM_CBK_H
#define ECUM_CBK_H

#include "Std_Types.h"

#include "EcuM_Types.h"

#include "EcuM_Generated_Types.h"

#include "EcuM_Cfg_Version.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

extern FUNC( void, ECUM_CODE ) EcuM_SetWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );

extern FUNC( void, ECUM_CODE ) EcuM_ValidateWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );

extern FUNC( void , ECUM_CODE ) EcuM_EndCheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources );

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#endif

