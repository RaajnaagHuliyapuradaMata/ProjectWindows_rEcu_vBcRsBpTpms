#include "Std_Types.hpp"

#include "EcuM.hpp"

#include "CfgMcalMcu.hpp"
#include "ComM.hpp"

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
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"
CONST( uint16,  ECUM_CONST)  EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN]  =
{
    1
};
#define ECUM_STOP_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"

