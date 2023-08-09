
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Rmba_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)           ||  \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)    ||  \
    (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)           || \
    (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

 FUNC(Dcm_ReturnReadMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_ReadMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Rmba_Opstatus,
 														VAR(uint8,  AUTOMATIC) memoryid,
 														VAR(uint32,  AUTOMATIC) memoryaddress,
 														VAR(uint32,  AUTOMATIC) datalength,
 														P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) respbuf,
 														P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
 {
	
    VAR(Dcm_ReturnReadMemoryType,AUTOMATIC) retVal = DCM_READ_OK;
	

	return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
