
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

 #define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

uint8 DcmAppl_DcmGetStoreType(uint8 dataBootType_u8,uint8 SID)

{
	uint8 retVal = DCM_NOTVALID_TYPE;

	

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
#include "Dcm_MemMap.h"

#endif

