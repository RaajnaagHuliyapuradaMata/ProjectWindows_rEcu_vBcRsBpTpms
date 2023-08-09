
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Iocbi_Inf.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckControlMaskAndState(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint8,AUTOMATIC) dataIoParam_u8,
													P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrCtlStateAndMask_pcst,VAR(uint16,AUTOMATIC) dataCtlStateAndMaskLen_u16
													)
{

	VAR(Std_ReturnType,AUTOMATIC) retVal;
	

	
	VAR(uint16,AUTOMATIC)                       dataControlMaskLen_u16;
	VAR (Dcm_DIDIndexType_tst,DCM_VAR) idxIocbiDidIndexType_st;
	retVal = E_OK;
	(void)nrDID_u16;
	(void)dataIoParam_u8;
	(void)adrCtlStateAndMask_pcst;
	(void)dataCtlStateAndMaskLen_u16;
	if (Dcm_GetIndexOfDID (nrDID_u16,&idxIocbiDidIndexType_st) == E_OK)
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
#include "Dcm_Cfg_MemMap.h"
#endif

