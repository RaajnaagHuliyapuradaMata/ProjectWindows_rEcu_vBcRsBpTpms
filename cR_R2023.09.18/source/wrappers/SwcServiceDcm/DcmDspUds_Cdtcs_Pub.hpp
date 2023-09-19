

#ifndef DCMDSPUDS_CDTCS_PUB_H
#define DCMDSPUDS_CDTCS_PUB_H

#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)

#define DCM_PRV_CDTC_POSITION_SUBFUNC    0x00u

#define DCM_PRV_CDTC_REQUEST_LENGTH      0x01u

#define DCM_PRV_CDTC_RECORD_LENGTH      0x03u

#define DCM_PRV_CDTC_OFF                 0x02u

#define DCM_PRV_CDTC_ON                  0x01u
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern FUNC(boolean,DCM_CODE) Dcm_GetControlDTCSetting_EnableStatus(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

#ifndef     DCM_CDTC_POSITION_SUBFUNC
#define DCM_CDTC_POSITION_SUBFUNC   DCM_PRV_CDTC_POSITION_SUBFUNC
#endif
#ifndef     DCM_CDTC_REQUEST_LENGTH
#define DCM_CDTC_REQUEST_LENGTH     DCM_PRV_CDTC_REQUEST_LENGTH
#endif
#ifndef     DCM_CDTC_OFF
#define DCM_CDTC_OFF                DCM_PRV_CDTC_OFF
#endif
#ifndef     DCM_CDTC_ON
#define DCM_CDTC_ON                 DCM_PRV_CDTC_ON
#endif

#endif
