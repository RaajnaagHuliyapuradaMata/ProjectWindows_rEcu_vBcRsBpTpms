#include "Std_Types.hpp"

#include "EcuM.hpp"

#include "CfgMcalMcu.hpp"
#if(!defined(CFGMCALMCU_AR_RELEASE_MAJOR_VERSION) || (CFGMCALMCU_AR_RELEASE_MAJOR_VERSION != 4))
   #error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(CFGMCALMCU_AR_RELEASE_MINOR_VERSION) || (CFGMCALMCU_AR_RELEASE_MINOR_VERSION != 2))
   #error "AUTOSAR minor version undefined or mismatched"
#endif
#include "ComM.hpp"
#if(!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != 4))
   #error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != 2))
   #error "AUTOSAR minor version undefined or mismatched"
#endif

#define ECUM_START_SEC_CONST_8
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_STOP_SEC_CONST_8
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

CONST( Type_SwcServiceEcuM_stListRefsPncWakeup,  ECUM_CONST)  EcuM_Cfg_dataWkupPNCRef_cast[CfgSwcServiceEcuM_dNumSourceWakeup]=
{
   { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR }
};

CONST( EcuM_Cfg_dataWkupSrcStruct_tst,  ECUM_CONST)  EcuM_Cfg_idxWakeupSourcesPC_au32[CfgSwcServiceEcuM_dNumSourceWakeup] =
{
{      FALSE          ,     255                                   ,  McalMcu_eReasonReset_Undefined   ,     0         ,     FALSE  ,     CfgSwcServiceEcuM_dPOWER
   ,   0             },
{      FALSE          ,     255                                   ,  McalMcu_eReasonReset_Undefined   ,     0         ,     FALSE  ,     CfgSwcServiceEcuM_dRESET
   ,   0             },
{      FALSE          ,     255                                   ,  McalMcu_eReasonReset_Undefined   ,     0         ,     FALSE  ,     CfgSwcServiceEcuM_dINTERNAL_RESET
   ,   0             },
{      FALSE          ,     255                                   ,  McalMcu_eReasonReset_Undefined   ,     0         ,     FALSE  ,     CfgSwcServiceEcuM_dINTERNAL_WDG
   ,   0             },
{      FALSE          ,     255                                   ,  McalMcu_eReasonReset_Undefined   ,     0         ,     FALSE  ,     CfgSwcServiceEcuM_dEXTERNAL_WDG
   ,   0             }
};

#if ECUM_SLEEP_SUPPORT_ENABLE

CONST( EcuM_Cfg_dataSleepModeStruct_tst,  ECUM_CONST)  EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES]=
{
};
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#if ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

volatile VAR( EcuM_Cfg_CheckWakeupSrc_tst,  ECUM_VAR_CLEARED_UNSPECIFIED)  EcuM_Cfg_CheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup] =
{

{  CfgSwcServiceEcuM_dPOWER,     0 ,     ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dRESET,     0 ,     ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dINTERNAL_RESET,     0 ,     ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dINTERNAL_WDG,     0 ,     ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dEXTERNAL_WDG,     0 ,     ECUM_FLAG_RESET_E}
};
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"

CONST( uint16,  ECUM_CONST)  EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN]  =
{
    1
};

#define ECUM_STOP_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"

