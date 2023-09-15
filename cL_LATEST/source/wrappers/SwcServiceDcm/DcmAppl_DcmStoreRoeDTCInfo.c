
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType DcmAppl_DcmStoreRoeDTCInfo( uint8 RoeeventID
   ,                                                            Dcm_DspRoeEventState_ten RoeEventStatus
   ,                                                            uint16 SourceAddress
   ,                                                            uint8 StatusMask
   ,                                                            boolean dspRoeStorageState_b
   ,                                                            Dcm_OpStatusType OpStatus
   ,                                                            boolean dspRoeSession_b
   ,                                                            Dcm_NegativeResponseCodeType * ErrorCode)
{
   Std_ReturnType retVal_u8 = E_OK;
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
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif
#endif
