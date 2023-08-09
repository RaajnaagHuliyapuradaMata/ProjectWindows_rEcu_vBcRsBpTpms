
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

 #include "DcmDspUds_Rc_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckRoutineControlOptionRecord(VAR(uint16,AUTOMATIC) nrRID_u16,
                                           VAR(uint8,AUTOMATIC) dataSubFunc_u8,P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrRoutineCtrlOptRec_pcst,VAR(uint16,AUTOMATIC) dataRoutineCtrlOptRecSize_u16)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;

		(void)(nrRID_u16);
		(void)(adrRoutineCtrlOptRec_pcst);
		(void)(dataRoutineCtrlOptRecSize_u16);
		(void)(dataSubFunc_u8);
		
		return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
