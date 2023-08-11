
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

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
Std_ReturnType DcmAppl_DcmStoreRoeDidInfo( uint16 Did,
                                                               uint8 RoeeventID,
                                                               Dcm_DspRoeEventState_ten RoeEventStatus,
                                                               uint16 SourceAddress,
                                                               boolean dspRoeStorageState_b,
                                                               Dcm_OpStatusType OpStatus,
                                                               boolean dspRoeSessionIsDefault_b,
                                                               Dcm_NegativeResponseCodeType * ErrorCode)
{
	Std_ReturnType retVal_u8 = E_OK;
	*ErrorCode = 0x0;
    (void)(Did);
    (void)(RoeeventID);
    (void)(RoeEventStatus);
    (void)(SourceAddress);
    (void)(dspRoeStorageState_b);
    (void)(OpStatus);
    (void)(dspRoeSessionIsDefault_b);
	
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
#endif
#endif
