
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Uds_Prot.h"

#if ((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)\
		|| (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermissionForMemoryAccess_u8(
																	VAR(uint32,  AUTOMATIC) adrMemoryAddress_u32,
																	VAR(uint32,  AUTOMATIC) dataDataLength_u32,
																	VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en
																   )
 {
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	
    (void)(adrMemoryAddress_u32);
    (void)(dataDataLength_u32);
    (void)(dataDirection_en);

	

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

