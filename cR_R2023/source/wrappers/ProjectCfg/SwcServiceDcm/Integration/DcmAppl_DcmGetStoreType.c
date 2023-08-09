
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(uint8,DCM_APPL_CODE) DcmAppl_DcmGetStoreType(VAR(uint8, AUTOMATIC) dataBootType_u8,VAR(uint8, AUTOMATIC) SID)
{
	VAR(uint8,AUTOMATIC) retVal = DCM_NOTVALID_TYPE;

	

  //RST integration code start

  if (dataBootType_u8 == DCM_JUMPTOOEMBOOTLOADER)
  {
    retVal = DCM_WARMREQUEST_TYPE;
  }
  else if (dataBootType_u8 == DCM_JUMPTOSYSSUPPLIERBOOTLOADER)
  {
    retVal = DCM_WARMREQUEST_TYPE;
  }

  //RST integration code end

	return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif

