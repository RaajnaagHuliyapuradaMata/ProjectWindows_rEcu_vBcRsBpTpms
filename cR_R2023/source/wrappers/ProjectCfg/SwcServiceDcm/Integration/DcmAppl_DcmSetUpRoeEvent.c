
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))

 #define DCM_START_SEC_CODE
 #include "Dcm_Cfg_MemMap.h"
 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSetUpRoeEvent (VAR(uint8,AUTOMATIC) RoeeventID,
                                                              VAR(uint8,AUTOMATIC) eventType,
                                                              VAR(boolean,AUTOMATIC) storageState,
                                                              VAR(uint8,AUTOMATIC) eventWindowTime,
                                                              P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) eventTypeRecord,
                                                              P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) serviceToRespondToRecord,
                                                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	*ErrorCode = 0x0;
	(void)(RoeeventID);
	(void)(eventType);
    (void)(storageState);
    (void)(eventWindowTime);
    (void)(eventTypeRecord);
    (void)(serviceToRespondToRecord);
    (void)(OpStatus);

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
#endif
