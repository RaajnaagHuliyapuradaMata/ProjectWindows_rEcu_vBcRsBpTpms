#ifndef ECUM_CALLOUT_H
#define ECUM_CALLOUT_H

#include "EcuM_Cfg_Startup.hpp"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"
extern void EcuM_ErrorHook( uint16 reason );

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern void EcuM_AL_DriverRestart (const Type_CfgSwcServiceEcuM_st * ConfigPtr );
#endif//ECUM_SLEEP_SUPPORT_ENABLE

extern void EcuM_OnGoOffOne(void);
extern void EcuM_OnGoOffTwo(void);
extern void EcuM_AL_SwitchOff(void);
extern void EcuM_AL_Reset( EcuM_ResetType reset );
extern void EcuM_StartWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern void EcuM_StopWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern void EcuM_CheckValidation( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern void infSwcApplEcuMSwcServiceEcuM_vSwitchOsModeApp(void);

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern void EcuM_EnableWakeupSources ( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern void EcuM_DisableWakeupSources ( Type_SwcServiceEcuM_tSourceWakeup wakeupSource );
extern uint8 EcuM_CheckRamHash (void);
extern void EcuM_GenerateRamHash(void);
extern void EcuM_StartCheckWakeup( Type_SwcServiceEcuM_tSourceWakeup wakeupSource);
extern void EcuM_SleepActivity(void);
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"

#endif

