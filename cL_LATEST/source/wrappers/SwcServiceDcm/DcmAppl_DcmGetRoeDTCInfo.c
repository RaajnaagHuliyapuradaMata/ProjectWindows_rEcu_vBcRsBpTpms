
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType DcmAppl_DcmGetRoeDTCInfo(uint8 RoeeventID
   ,                                               Dcm_DspRoeEventState_ten * RoeEventStatus
   ,                                               uint8 * RoeEventWindowTime_u8
   ,                                               uint16 * SourceAddress
   ,                                               uint8 * StatusMask
   ,                                               boolean * dspRoeCtrlStorageState_b
   ,                                               boolean * dspRoeSetUpStorageState_b
   ,                                               boolean * dspRoeSession_b)
{

    Std_ReturnType retVal_u8;
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
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif
