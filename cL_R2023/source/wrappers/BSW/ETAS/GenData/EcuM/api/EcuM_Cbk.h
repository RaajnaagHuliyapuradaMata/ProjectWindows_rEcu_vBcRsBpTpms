

#ifndef ECUM_CBK_H
#define ECUM_CBK_H

#include "Std_Types.h"

#include "EcuM_Types.h"

#include "EcuM_Generated_Types.h"

#include "EcuM_Cfg_Version.h"

#include "EcuM_Cfg_CbkStartup.h"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

extern void EcuM_SetWakeupEvent( Type_SwcServiceEcuM_tSourceWakeup sources );

extern void EcuM_ValidateWakeupEvent( Type_SwcServiceEcuM_tSourceWakeup sources );

extern void EcuM_CheckWakeup( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );

extern void EcuM_EndCheckWakeup( Type_SwcServiceEcuM_tSourceWakeup sources );

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#endif

