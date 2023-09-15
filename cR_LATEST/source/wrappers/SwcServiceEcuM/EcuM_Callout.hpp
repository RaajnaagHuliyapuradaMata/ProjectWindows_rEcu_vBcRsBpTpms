#ifndef ECUM_CALLOUT_H
#define ECUM_CALLOUT_H

#include "EcuM_Cfg_Startup.hpp"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.hpp"
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_ErrorHook( VAR(uint16, AUTOMATIC) reason );

#if ECUM_SLEEP_SUPPORT_ENABLE
extern FUNC (void , ECUM_CALLOUT_CODE ) EcuM_AL_DriverRestart (P2CONST(Type_CfgSwcServiceEcuM_st, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr );
#endif//ECUM_SLEEP_SUPPORT_ENABLE

extern FUNC(void , ECUM_CALLOUT_CODE ) EcuM_OnGoOffOne(void);
extern FUNC(void , ECUM_CALLOUT_CODE ) EcuM_OnGoOffTwo(void);
extern FUNC(void , ECUM_CALLOUT_CODE ) EcuM_AL_SwitchOff(void);
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_AL_Reset( VAR(EcuM_ResetType, AUTOMATIC) reset );
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_StartWakeupSources( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_StopWakeupSources( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_CheckValidation( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(void , ECUM_CALLOUT_CODE ) infSwcApplEcuMSwcServiceEcuM_vSwitchOsModeApp(void);

#if ECUM_SLEEP_SUPPORT_ENABLE
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_EnableWakeupSources ( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_DisableWakeupSources ( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource );
extern FUNC(uint8, ECUM_CALLOUT_CODE )EcuM_CheckRamHash (void);
extern FUNC(void, ECUM_CALLOUT_CODE ) EcuM_GenerateRamHash(void);
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartCheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource);
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void);
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.hpp"

#endif

