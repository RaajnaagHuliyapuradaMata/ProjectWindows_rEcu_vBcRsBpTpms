
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))

 #define DCM_START_SEC_CODE
 #include "Dcm_MemMap.h"
 Std_ReturnType DcmAppl_DcmSetUpRoeEvent (uint8 RoeeventID,
                                                              uint8 eventType,
                                                              boolean storageState,
                                                              uint8 eventWindowTime,
                                                              const uint8 * eventTypeRecord,
                                                              const uint8 * serviceToRespondToRecord,
                                                              Dcm_OpStatusType OpStatus,
                                                              Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal = E_OK;
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
#include "Dcm_MemMap.h"
#endif
#endif
#endif
