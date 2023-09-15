

#ifndef DCMDSPUDS_ROE_PUB_H
#define DCMDSPUDS_ROE_PUB_H

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

typedef struct{
   uint8  EventType_u8;
   uint8  EventRecordLen_u8;
   uint8  ServiceRecordLen_u8;
}DcmDspRoeConf_t;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const DcmDspRoeConf_t DcmDspRoeEvents[DCM_ROE_MAX_EVENTS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
