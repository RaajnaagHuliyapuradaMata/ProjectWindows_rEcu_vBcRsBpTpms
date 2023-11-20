#ifndef ECUM_H
#define ECUM_H

#include "EcuM_Types.hpp"
#include "EcuM_Generated_Types.hpp"
#include "EcuM_Cfg_Version.hpp"
#include "EcuM_Cbk.hpp"

#define ECUM_WKSTATUS_NONE                                                     0
#define ECUM_WKSTATUS_PENDING                                                  1
#define ECUM_WKSTATUS_VALIDATED                                                2
#define ECUM_WKSTATUS_EXPIRED                                                  3
#define ECUM_RUNSTATUS_UNKNOWN                          (EcuM_RunStatusType)(0U)
#define ECUM_RUNSTATUS_REQUESTED                        (EcuM_RunStatusType)(1U)
#define ECUM_RUNSTATUS_RELEASED                         (EcuM_RunStatusType)(2U)
#define ECUM_SUBSTATE_MASK                               (EcuM_StateType)(0x0fU)
#define ECUM_STATE_STARTUP                               (EcuM_StateType)(0x10U)
#define ECUM_STATE_RUN                                   (EcuM_StateType)(0x30U)
#define ECUM_STATE_APP_RUN                               (EcuM_StateType)(0x32U)
#define ECUM_STATE_APP_POST_RUN                          (EcuM_StateType)(0x33U)
#define ECUM_STATE_SHUTDOWN                              (EcuM_StateType)(0x40U)
#define ECUM_STATE_SLEEP                                 (EcuM_StateType)(0x50U)

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#define Rte_Switch_currentMode_EcuM_Mode(data) ( ((VAR(Std_ReturnType, AUTOMATIC))RTE_E_OK) )
#define Rte_Mode_currentMode_EcuM_Mode()  (RTE_MODE_EcuM_Mode_STARTUP)
#define RTE_E_OK               ((Std_ReturnType)0u)
#endif

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#define ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
extern VAR(Type_SwcServiceEcuM_stInfoTargetShutdown, ECUM_VAR_SAVED_ZONE0_UNSPECIFIED) EcuM_Rn_dataShutdownInfo_st;
#define ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
#endif

extern FUNC(void, ECUM_CODE) infSwcServiceEcuMSwcServiceSchM_vMainFunction(void);

extern FUNC(void,     ECUM_CODE) EcuM_StartupTwo               (void);
extern FUNC(Std_ReturnType,     ECUM_CODE) EcuM_GoDown                   (VAR(uint16, AUTOMATIC) caller);
extern FUNC(void,     ECUM_CODE) EcuM_Shutdown                 (void);
extern FUNC(Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE) EcuM_GetValidatedWakeupEvents (void);
extern FUNC(Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE) EcuM_GetExpiredWakeupEvents   (void);
extern FUNC(Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE) EcuM_GetPendingWakeupEvents   (void);

extern FUNC(void ,     ECUM_CODE) EcuM_ClearWakeupEvent (  VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources);
extern FUNC(void,     ECUM_CODE) EcuM_GetVersionInfo   (P2VAR(Std_VersionInfoType,     AUTOMATIC, ECUM_APPL_DATA) versioninfo);
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget (  VAR(EcuM_BootTargetType,     AUTOMATIC) target);
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget    (P2VAR(EcuM_BootTargetType,     AUTOMATIC, ECUM_APPL_DATA) target);

extern FUNC(Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownTarget(
      P2VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget
   ,  P2VAR(Type_SwcServiceEcuM_tModeShutdown,   AUTOMATIC, ECUM_APPL_DATA) shutdownMode
);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget(
      VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC) shutdownTarget
   ,  VAR(Type_SwcServiceEcuM_tModeShutdown,   AUTOMATIC) shutdownMode
);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownCause(VAR(Type_SwcServiceEcuM_tCauseShutdown, AUTOMATIC) shutdownCause);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownCause(
   P2VAR(Type_SwcServiceEcuM_tCauseShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownCause
);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget(
      P2VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget
   ,  P2VAR(Type_SwcServiceEcuM_tModeShutdown,   AUTOMATIC, ECUM_APPL_DATA) shutdownMode
);

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_Rn_NvMSingleBlockCallbackFunction (
      VAR(uint8, AUTOMATIC) ServiceId
   ,  VAR(uint8, AUTOMATIC) JobResult
);
FUNC(Std_ReturnType, ECUM_CODE ) EcuM_Rn_GetLastShutdownInfo(
        P2VAR(EcuM_ShutdownInfoType, AUTOMATIC, ECUM_APPL_DATA) shutdownCauseInfo
);
#endif

#endif
