
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStoreRoeDTCInfo( VAR(uint8,AUTOMATIC)  RoeeventID,
                                                             VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus,
                                                             VAR(uint16,AUTOMATIC)  SourceAddress,
                                                             VAR(uint8,AUTOMATIC) StatusMask,
                                                             VAR(boolean,AUTOMATIC) dspRoeStorageState_b,
                                                             VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                             VAR(boolean,AUTOMATIC) dspRoeSession_b,
                                                             P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	*ErrorCode = 0x0;
    (void)(RoeeventID);
    (void)(RoeEventStatus);
    (void)(SourceAddress);
    (void)(StatusMask);
    (void)(dspRoeStorageState_b);
    (void)(OpStatus);
    (void)(dspRoeSession_b);
	
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
#endif
