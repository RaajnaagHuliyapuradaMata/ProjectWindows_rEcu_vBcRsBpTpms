#ifndef ECUM_CFG_H
#define ECUM_CFG_H

#include "CfgMcalMcu.hpp"
#include "Os.hpp"
#include "CfgSwcServiceEcuM.hpp"
#include "infMcalMcuSwcApplEcuM.hpp" //TBD: change to Types_McalMcu.hpp

#define ECUM_VERSION_INFO_API	(STD_OFF)
#define ECUM_DEV_ERROR_DETECT 	(STD_ON)
#define ECUM_INCLUDE_DET (STD_ON)
#define ECUM_CFG_MODE_HANDLING  (STD_OFF)
#define ECUM_CFG_STARTUP_CORE    OS_CORE_ID_MASTER
#define ECUM_SLEEP_SUPPORT_ENABLE  FALSE
#define ECUM_CFG_NUM_SLEEP_MODES  ((uint16)0)
#define ECUM_CFG_ECUC_RB_RTE_IN_USE  FALSE
#define ECUM_CFG_NUM_OS_CORES	((uint16)1)
#define ECUM_CFG_NUM_RESET_MODES	(3U)
#define ECUM_CFG_GODOWN_CALLER_ARR_LEN	(1U)
#define CfgSwcServiceEcuM_dNumSourceWakeup (5U)
#define ECUM_CFG_NUM_SHUTDOWN_CAUSE 4

typedef struct{
   boolean IsComChannelPresent ;
   uint8 ComChannelReferance;
    Type_McalMcu_eReasonReset   ResetReason;
   uint16  ValidationTimeout;
   boolean IsWakeupSourcePolling;
   uint32   WakeupSourceId;
   uint16 CheckWakeupTimeout;
}EcuM_Cfg_dataWkupSrcStruct_tst;

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_NORMAL_MCU_MODE ((Mcu_ModeType))
typedef struct{
   boolean IsCPUSuspend;
    Mcu_ModeType  EquivalentMcuMode;
   uint32   WakeupSourceMask;
}EcuM_Cfg_dataSleepModeStruct_tst;

typedef enum  {
    ECUM_FLAG_RESET_E = 0
   ,   ECUM_TIMER_STARTED_E = 1
   ,   ECUM_SET_WAKEUP_EVENT_E = 2
   ,   ECUM_END_CHECK_WAKEUP_E = 3
   ,   ECUM_TIMER_EXPIRED_E = 4
}EcuM_Wakeup_States_ten;

typedef struct{
   uint32   WakeupSourceId;
   uint16 CheckWakeupTimeout;
    EcuM_Wakeup_States_ten CheckWakeupStatus;
}EcuM_Cfg_CheckWakeupSrc_tst;
#endif

#define ECUM_START_SEC_CONFIG_DATA_8
#include "EcuM_Cfg_MemMap.hpp"
extern CONST( uint8, ECUM_CONST) CfgSwcServiceEcuM_au8HashPreCompile[CfgSwcServiceEcuM_dLenHash];
#define ECUM_STOP_SEC_CONFIG_DATA_8
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
extern CONST( EcuM_Cfg_dataWkupSrcStruct_tst,  ECUM_CONST)  EcuM_Cfg_idxWakeupSourcesPC_au32[CfgSwcServiceEcuM_dNumSourceWakeup];
extern CONST( Type_SwcServiceEcuM_stListRefsPncWakeup,  ECUM_CONST)  EcuM_Cfg_dataWkupPNCRef_cast[CfgSwcServiceEcuM_dNumSourceWakeup];

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern CONST( EcuM_Cfg_dataSleepModeStruct_tst  ,  ECUM_CONST)  EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES];
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
extern volatile VAR( EcuM_Cfg_CheckWakeupSrc_tst, ECUM_VAR_CLEARED_UNSPECIFIED )EcuM_Cfg_CheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup];
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"
   extern CONST( uint16, ECUM_CONST) EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN];
#define ECUM_STOP_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_CFG_NVM_BLOCK_CONFIGURED TRUE
#define ECUM_WKUP_SRC_START_BIT_MASK   ((uint32)0x00000001)
#define ECUM_UNCONFIGURED_WKP_SOURCES  (~ECUM_KNOWN_WAKEUP_SOURCES)

#define ECUM_UNINTENDED_RESET_MSK      (uint32) (  CfgSwcServiceEcuM_dINTERNAL_RESET | \
                                                    CfgSwcServiceEcuM_dEXTERNAL_WDG | \
                                                    CfgSwcServiceEcuM_dINTERNAL_WDG | \
                                                    CfgSwcServiceEcuM_dPOWER | \
                                                    CfgSwcServiceEcuM_dRESET \
                                         )

#define ECUM_KNOWN_WAKEUP_SOURCES      (uint32) (CfgSwcServiceEcuM_dPOWER | \
   	CfgSwcServiceEcuM_dRESET | \
   	CfgSwcServiceEcuM_dINTERNAL_RESET | \
   	CfgSwcServiceEcuM_dINTERNAL_WDG | \
   	CfgSwcServiceEcuM_dEXTERNAL_WDG \
   	)

#define ECUM_WAKEUP_SOURCES_WITH_VALIDATION     (uint32)(0x00u)

#define ECUM_WAKEUP_SOURCES_WITHOUT_VALIDATION     (uint32)(CfgSwcServiceEcuM_dPOWER| \
               CfgSwcServiceEcuM_dRESET| \
               CfgSwcServiceEcuM_dINTERNAL_RESET| \
               CfgSwcServiceEcuM_dINTERNAL_WDG| \
               CfgSwcServiceEcuM_dEXTERNAL_WDG \
               )

#define ECUM_NON_BASIC_WKUPS_MSK       ((ECUM_KNOWN_WAKEUP_SOURCES^ECUM_UNINTENDED_RESET_MSK))
#define EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig_0	((uint16)1)
#define EcuMConf_EcuMResetMode_ECUM_RESET_MCU	((EcuM_ResetType)0)
#define EcuMConf_EcuMResetMode_ECUM_RESET_WDGM	((EcuM_ResetType)1)
#define EcuMConf_EcuMResetMode_ECUM_RESET_IO	((EcuM_ResetType)2)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_UNKNOWN    ((Type_SwcServiceEcuM_tCauseShutdown)0)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE    ((Type_SwcServiceEcuM_tCauseShutdown)1)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM    ((Type_SwcServiceEcuM_tCauseShutdown)2)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM    ((Type_SwcServiceEcuM_tCauseShutdown)3)

#endif
