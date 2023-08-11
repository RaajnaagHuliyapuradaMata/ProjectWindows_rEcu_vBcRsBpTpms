
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Uds_Inf.h"
#include "Rte_Dcm.h"

#if (((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_UserMemoryRangeModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8,uint32 adrMemoryAddress_u32,uint32 dataDataLength_u32,Dcm_Direction_t dataDirection_en)
{
	Std_ReturnType retVal_u8 = E_OK;
	*Nrc_u8= 0x00;
	
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

