#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_SetProgConditions(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2CONST(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

