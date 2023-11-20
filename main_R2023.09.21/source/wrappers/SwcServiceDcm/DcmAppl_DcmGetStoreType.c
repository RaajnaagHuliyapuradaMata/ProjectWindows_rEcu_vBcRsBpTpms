#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(uint8,DCM_APPL_CODE) DcmAppl_DcmGetStoreType(VAR(uint8, AUTOMATIC) dataBootType_u8,VAR(uint8, AUTOMATIC) SID)
{
   VAR(uint8,AUTOMATIC) retVal = DCM_NOTVALID_TYPE;
   if(dataBootType_u8 == DCM_JUMPTOOEMBOOTLOADER){
    retVal = DCM_WARMREQUEST_TYPE;
  }
   else if(dataBootType_u8 == DCM_JUMPTOSYSSUPPLIERBOOTLOADER){
    retVal = DCM_WARMREQUEST_TYPE;
  }
   return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

