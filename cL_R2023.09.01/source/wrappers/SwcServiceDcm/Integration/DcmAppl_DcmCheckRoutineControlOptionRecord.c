
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

 #include "DcmDspUds_Rc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmCheckRoutineControlOptionRecord(uint16 nrRID_u16
   ,                                          uint8 dataSubFunc_u8,const uint8 * adrRoutineCtrlOptRec_pcst,uint16 dataRoutineCtrlOptRecSize_u16)
{
   Std_ReturnType retVal = E_OK;

   	(void)(nrRID_u16);
   	(void)(adrRoutineCtrlOptRec_pcst);
   	(void)(dataRoutineCtrlOptRecSize_u16);
   	(void)(dataSubFunc_u8);

   	return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
