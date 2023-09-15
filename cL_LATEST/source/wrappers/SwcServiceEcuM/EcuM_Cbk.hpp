#ifndef ECUM_CBK_H
#define ECUM_CBK_H

#include "Std_Types.hpp"

#include "EcuM_Types.hpp"
#include "EcuM_Generated_Types.hpp"
#include "EcuM_Cfg_Version.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"
extern void EcuM_SetWakeupEvent( Type_SwcServiceEcuM_tSourceWakeup sources );
extern void EcuM_ValidateWakeupEvent( Type_SwcServiceEcuM_tSourceWakeup sources );
extern void EcuM_CheckWakeup( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern void EcuM_EndCheckWakeup( Type_SwcServiceEcuM_tSourceWakeup sources );
#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

#endif

