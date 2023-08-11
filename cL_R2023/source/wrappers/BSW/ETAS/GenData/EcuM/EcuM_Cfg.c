

#include "EcuM.h"

#include "Mcu.h"
// #if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
	// #error "AUTOSAR major version undefined or mismatched"
// #endif
// #if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || ((MCU_AR_RELEASE_MINOR_VERSION != 2) && (MCU_AR_RELEASE_MINOR_VERSION != 3)))
	// #error "AUTOSAR minor version undefined or mismatched"
// #endif

#if( ECUM_INCLUDE_COMM == STD_ON )
#include "ComM.h"
	// #if (!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != 4))
		// #error "AUTOSAR major version undefined or mismatched"
	// #endif
	// #if (!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != 2))
		// #error "AUTOSAR minor version undefined or mismatched"
	// #endif
#endif

#define ECUM_START_SEC_CONST_8
#include "EcuM_MemMap.h"

#define ECUM_STOP_SEC_CONST_8
#include "EcuM_MemMap.h"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h"

const Type_SwcServiceEcuM_stListRefsPncWakeup EcuM_Cfg_dataWkupPNCRef_cast[CfgSwcServiceEcuM_dNumSourceWakeup]=
{
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR },
    { 0      ,   NULL_PTR }
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h"

const EcuM_Cfg_dataWkupSrcStruct_tst EcuM_Cfg_idxWakeupSourcesPC_au32[CfgSwcServiceEcuM_dNumSourceWakeup] =
{
{      FALSE          ,       255                                   ,  McalMcu_eReasonReset_Undefined   ,         0         ,        FALSE  ,              CfgSwcServiceEcuM_dPOWER,
    0             },
{      FALSE          ,       255                                   ,  McalMcu_eReasonReset_Undefined   ,         0         ,        FALSE  ,              CfgSwcServiceEcuM_dRESET,
    0             },
{      FALSE          ,       255                                   ,  McalMcu_eReasonReset_Undefined   ,         0         ,        FALSE  ,              CfgSwcServiceEcuM_dINTERNAL_RESET,
    0             },
{      FALSE          ,       255                                   ,  McalMcu_eReasonReset_Undefined   ,         0         ,        FALSE  ,              CfgSwcServiceEcuM_dINTERNAL_WDG,
    0             },
{      FALSE          ,       255                                   ,  McalMcu_eReasonReset_Undefined   ,         0         ,        FALSE  ,              CfgSwcServiceEcuM_dEXTERNAL_WDG,
    0             }
};

#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)

const EcuM_Cfg_dataSleepModeStruct_tst EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES]=
{
};
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h"

#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.h"

volatile EcuM_Cfg_CheckWakeupSrc_tst EcuM_Cfg_CheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup] =
{

{  CfgSwcServiceEcuM_dPOWER,                0 ,      ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dRESET,                0 ,      ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dINTERNAL_RESET,                0 ,      ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dINTERNAL_WDG,                0 ,      ECUM_FLAG_RESET_E},
{  CfgSwcServiceEcuM_dEXTERNAL_WDG,                0 ,      ECUM_FLAG_RESET_E}
};
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.h"

#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_CONST_16
#include "EcuM_MemMap.h"

const uint16 EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN]  =
{
    1
};

#define ECUM_STOP_SEC_CONST_16
#include "EcuM_MemMap.h"

