
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#include "DcmMsgAuthenticationX.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void DcmAppl_DcmModifyResponse (
									uint8 dataSid_u8,
									uint8 dataNRC_u8,
									uint8 * adrBufPtr_pu8,
									uint32 * nrBufSize_pu32
							   		)
{

    // *nrBufSize_pu32 = 0;
	

  uint8 ucNumberOfBytesToAdd;

  ucNumberOfBytesToAdd = DcmAppendMessageAuthentication(dataSid_u8, adrBufPtr_pu8, (uint32)Dcm_DsldMsgContext_st.resDataLen, (uint8*)Dcm_DsldMsgContext_st.resData);
  if (ucNumberOfBytesToAdd == 0)
  {
    *nrBufSize_pu32 = 0;
  }
  else
  {
    *nrBufSize_pu32 = ucNumberOfBytesToAdd;
  }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
