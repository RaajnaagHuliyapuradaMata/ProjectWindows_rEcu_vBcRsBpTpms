
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Iocbi_Inf.h"
#include "Rte_Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_DcmCheckControlMaskAndState(uint16 nrDID_u16, uint8 dataIoParam_u8,
													const uint8 * adrCtlStateAndMask_pcst,uint16 dataCtlStateAndMaskLen_u16
													)
{

	Std_ReturnType retVal;
	

	
	uint16 dataControlMaskLen_u16;
	Dcm_DIDIndexType_tst idxIocbiDidIndexType_st;
	retVal = E_OK;
	(void)nrDID_u16;
	(void)dataIoParam_u8;
	(void)adrCtlStateAndMask_pcst;
	(void)dataCtlStateAndMaskLen_u16;
	if (Dcm_Lok_GetIndexOfDID (nrDID_u16,&idxIocbiDidIndexType_st) == E_OK)
	{
		dataControlMaskLen_u16 = (uint16)((uint16)((uint32)(Dcm_DIDConfig[idxIocbiDidIndexType_st.idxIndex_u16].nrSig_u16-1u)/8u)+1u);
	}
	else
	{
		retVal = E_NOT_OK;
	}

	

	return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

