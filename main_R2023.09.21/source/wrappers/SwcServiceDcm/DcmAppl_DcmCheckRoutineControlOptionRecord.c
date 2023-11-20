#include "Std_Types.hpp"

#include "DcmDspUds_Rc_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckRoutineControlOptionRecord(VAR(uint16,AUTOMATIC) nrRID_u16
   ,     VAR(uint8,AUTOMATIC) dataSubFunc_u8,P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrRoutineCtrlOptRec_pcst,VAR(uint16,AUTOMATIC) dataRoutineCtrlOptRecSize_u16)
{
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   	(void)(nrRID_u16);
   	(void)(adrRoutineCtrlOptRec_pcst);
   	(void)(dataRoutineCtrlOptRecSize_u16);
   	(void)(dataSubFunc_u8);
   	return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
