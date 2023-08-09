
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRoeDTCInfo(VAR(uint8,AUTOMATIC)  RoeeventID,
                                                P2VAR(Dcm_DspRoeEventState_ten,AUTOMATIC,DCM_INTERN_DATA) RoeEventStatus,
                                                P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) RoeEventWindowTime_u8,
                                                P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA)  SourceAddress,
                                                P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) StatusMask,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeCtrlStorageState_b,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeSetUpStorageState_b,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) dspRoeSession_b)
{

    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;

    (void)(RoeeventID);
    (void)(RoeEventStatus);
    (void)(RoeEventWindowTime_u8);
    (void)(SourceAddress);
    (void)(StatusMask);
    (void)(dspRoeCtrlStorageState_b);
    (void)(dspRoeSetUpStorageState_b);
    (void)(dspRoeSession_b);
    return retVal_u8;

	}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
