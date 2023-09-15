#pragma once
/******************************************************************************/
/* File   : EcuM_Cfg.hpp                                                      */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"
#include "Os.hpp"

#include "CfgSwcServiceEcuM.hpp"
#include "infMcalMcuSwcApplEcuM.hpp"


/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ECUM_VERSION_INFO_API	(STD_OFF)
#define ECUM_DEV_ERROR_DETECT 	(STD_ON)
#define ECUM_INCLUDE_DET (STD_ON)
#define ECUM_CFG_MODE_HANDLING  (STD_OFF)
#define ECUM_INCLUDE_COMM  (STD_ON)
#define ECUM_CFG_STARTUP_CORE    OS_CORE_ID_MASTER
#define ECUM_SLEEP_SUPPORT_ENABLE  FALSE
#define ECUM_CFG_NUM_SLEEP_MODES  ((uint16)0)
#define ECUM_CFG_ECUC_RB_RTE_IN_USE  FALSE
#define ECUM_CFG_NUM_OS_CORES	((uint16)1)
#define ECUM_CFG_NUM_RESET_MODES	(3U)
#define ECUM_CFG_GODOWN_CALLER_ARR_LEN	(1U)
#define CfgSwcServiceEcuM_dNumSourceWakeup (5U)
#define ECUM_CFG_NUM_SHUTDOWN_CAUSE 4

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
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
      ECUM_FLAG_RESET_E
   ,  ECUM_TIMER_STARTED_E
   ,  ECUM_SET_WAKEUP_EVENT_E
   ,  ECUM_END_CHECK_WAKEUP_E
   ,  ECUM_TIMER_EXPIRED_E
}EcuM_Wakeup_States_ten;

typedef struct{
   uint32                 WakeupSourceId;
   uint16                 CheckWakeupTimeout;
   EcuM_Wakeup_States_ten CheckWakeupStatus;
}EcuM_Cfg_CheckWakeupSrc_tst;
#endif

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"
extern CONST( EcuM_Cfg_dataWkupSrcStruct_tst,  ECUM_CONST)  EcuM_Cfg_idxWakeupSourcesPC_au32[CfgSwcServiceEcuM_dNumSourceWakeup];
extern CONST( Type_SwcServiceEcuM_stListRefsPncWakeup,  ECUM_CONST)  EcuM_Cfg_dataWkupPNCRef_cast[CfgSwcServiceEcuM_dNumSourceWakeup];

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern CONST( EcuM_Cfg_dataSleepModeStruct_tst  ,  ECUM_CONST)  EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES];
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
extern volatile VAR( EcuM_Cfg_CheckWakeupSrc_tst, ECUM_VAR_CLEARED_UNSPECIFIED )EcuM_Cfg_CheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup];
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_CONST_16
#include "EcuM_MemMap.hpp"
   extern CONST( uint16, ECUM_CONST) EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN];
#define ECUM_STOP_SEC_CONST_16
#include "EcuM_MemMap.hpp"

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

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

