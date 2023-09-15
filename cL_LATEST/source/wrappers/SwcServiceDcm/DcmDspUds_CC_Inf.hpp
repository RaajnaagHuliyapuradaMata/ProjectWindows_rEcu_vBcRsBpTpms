

#ifndef DCMDSPUDS_CC_INF_H
#define DCMDSPUDS_CC_INF_H

#include "Dcm.hpp"
#include "DcmDspUds_Uds_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF))
#include "BswM_Dcm.hpp"
#endif

#endif

