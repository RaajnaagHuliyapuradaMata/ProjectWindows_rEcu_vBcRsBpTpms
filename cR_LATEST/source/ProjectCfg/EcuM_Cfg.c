#include "Std_Types.hpp"

#include "Types_SwcServiceComM.hpp"

#include "EcuM.hpp"

#include "CfgMcalMcu.hpp"
#include "ComM.hpp"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
CONST(Type_CfgSwcServiceEcuM_stInfoSourceWakeUp, ECUM_CONST) CfgSwcServiceEcuM_castListInfoSourceWakeUp[CfgSwcServiceEcuM_dNumSourceWakeup] = {
      {FALSE, 255, McalMcu_eResetReason_Undefined, 0, FALSE, CfgSwcServiceEcuM_dPOWER,          0}
   ,  {FALSE, 255, McalMcu_eResetReason_Undefined, 0, FALSE, CfgSwcServiceEcuM_dRESET,          0}
   ,  {FALSE, 255, McalMcu_eResetReason_Undefined, 0, FALSE, CfgSwcServiceEcuM_dINTERNAL_RESET, 0}
   ,  {FALSE, 255, McalMcu_eResetReason_Undefined, 0, FALSE, CfgSwcServiceEcuM_dINTERNAL_WDG,   0}
   ,  {FALSE, 255, McalMcu_eResetReason_Undefined, 0, FALSE, CfgSwcServiceEcuM_dEXTERNAL_WDG,   0}
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"
CONST(uint16, ECUM_CONST) EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN] = {1};
#define ECUM_STOP_SEC_CONST_16
#include "EcuM_Cfg_MemMap.hpp"

