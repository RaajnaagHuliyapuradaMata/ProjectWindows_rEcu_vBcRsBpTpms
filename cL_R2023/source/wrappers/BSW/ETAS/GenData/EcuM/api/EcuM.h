#ifndef ECUM_H
#define ECUM_H

#include "Std_Types.h"
#include "EcuM_Types.h"
#include "EcuM_Generated_Types.h"
#include "EcuM_Cfg_Version.h"

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE != FALSE)
#include "SchM_EcuM.h"
#include "Rte_EcuM_Type.h"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

#include "EcuM_Cfg_RbExt.h"
#include "EcuM_Cfg_RbMo.h"
#include "EcuM_Cfg_PbExt.h"
#include "EcuM_Cbk.h"

#define ECUM_WKSTATUS_NONE      0
#define ECUM_WKSTATUS_PENDING   1
#define ECUM_WKSTATUS_VALIDATED 2
#define ECUM_WKSTATUS_EXPIRED   3
#define ECUM_RUNSTATUS_UNKNOWN                           (EcuM_RunStatusType)(0U)
#define ECUM_RUNSTATUS_REQUESTED                         (EcuM_RunStatusType)(1U)
#define ECUM_RUNSTATUS_RELEASED                           (EcuM_RunStatusType)(2U)
#define ECUM_SUBSTATE_MASK                   (EcuM_StateType)(0x0fU)
#define ECUM_STATE_STARTUP                   (EcuM_StateType)(0x10U)
#define ECUM_STATE_RUN                       (EcuM_StateType)(0x30U)
#define ECUM_STATE_APP_RUN                   (EcuM_StateType)(0x32U)
#define ECUM_STATE_APP_POST_RUN              (EcuM_StateType)(0x33U)
#define ECUM_STATE_SHUTDOWN                  (EcuM_StateType)(0x40U)
#define ECUM_STATE_SLEEP                     (EcuM_StateType)(0x50U)

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#define Rte_Switch_currentMode_currentMode(data) ( ((Std_ReturnType )RTE_E_OK) )
#define Rte_Mode_currentMode_currentMode()  (RTE_MODE_EcuM_Mode_STARTUP)
#define RTE_E_OK               ((Std_ReturnType)0u)
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#define ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_MemMap.h"
extern Type_SwcServiceEcuM_stInfoTargetShutdown EcuM_Rn_dataShutdownInfo_st;
#define ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_MemMap.h"
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"
extern void EcuM_MainFunction(void);
#else//ECUM_CFG_ECUC_RB_RTE_IN_USE
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

extern void EcuM_StartupTwo(void);
extern Std_ReturnType EcuM_GoDown(uint16 caller);
extern Std_ReturnType EcuM_GoDownHaltPoll(uint16 caller);
extern void EcuM_Shutdown(void );
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_GetValidatedWakeupEvents(void);
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_GetExpiredWakeupEvents( void );
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_GetPendingWakeupEvents( void );

#if (ECUM_SLEEP_SUPPORT_ENABLE != FALSE)
extern Std_ReturnType EcuM_GoHalt(void);
extern Std_ReturnType EcuM_GoPoll(void);
#endif//ECUM_SLEEP_SUPPORT_ENABLE

extern void EcuM_ClearWakeupEvent (Type_SwcServiceEcuM_tSourceWakeup sources);
extern  void EcuM_GetVersionInfo (Std_VersionInfoType * versioninfo);
extern  Std_ReturnType EcuM_SelectBootTarget(EcuM_BootTargetType target);
extern  Std_ReturnType EcuM_GetBootTarget(EcuM_BootTargetType * target);

extern Std_ReturnType EcuM_GetShutdownTarget(
                                        Type_SwcServiceEcuM_tTargetShutdown * shutdownTarget,
                                        Type_SwcServiceEcuM_tModeShutdown * shutdownMode);

extern Std_ReturnType EcuM_SelectShutdownTarget(
                                        Type_SwcServiceEcuM_tTargetShutdown shutdownTarget,
                                        Type_SwcServiceEcuM_tModeShutdown shutdownMode );

extern Std_ReturnType EcuM_SelectShutdownCause( Type_SwcServiceEcuM_tCauseShutdown shutdownCause );

extern Std_ReturnType EcuM_GetShutdownCause(
                                        Type_SwcServiceEcuM_tCauseShutdown * shutdownCause );

extern Std_ReturnType EcuM_GetLastShutdownTarget(
                                        Type_SwcServiceEcuM_tTargetShutdown * shutdownTarget,
                                        Type_SwcServiceEcuM_tModeShutdown * shutdownMode );

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
extern Std_ReturnType EcuM_Rn_NvMSingleBlockCallbackFunction (
                                        uint8 ServiceId,
                                        uint8 JobResult);
Std_ReturnType EcuM_Rn_GetLastShutdownInfo(
        EcuM_ShutdownInfoType * shutdownCauseInfo);
#endif //ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern Std_ReturnType EcuM_RequestRUN( EcuM_UserType user );
extern Std_ReturnType EcuM_ReleaseRUN( EcuM_UserType user );
extern Std_ReturnType EcuM_RequestPOST_RUN( EcuM_UserType user );
extern Std_ReturnType EcuM_ReleasePOST_RUN( EcuM_UserType user );
extern void EcuM_SetState(EcuM_StateType state);
extern void EcuM_KillAllRUNRequests( void );
extern void EcuM_KillAllPostRUNRequests( void );
extern void EcuM_Rn_KillAllRequests( void );
extern void EcuM_Rn_CurrentState ( void );
#endif//ECUM_CFG_MODE_HANDLING

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"
#endif
