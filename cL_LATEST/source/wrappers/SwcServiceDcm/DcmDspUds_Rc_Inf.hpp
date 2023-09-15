

#ifndef DCMDSPUDS_RC_INF_H
#define DCMDSPUDS_RC_INF_H

#include "Dcm.hpp"

#include "DcmCore_DslDsd_Prot.hpp"
#include "Dcm_Cfg_SchM.hpp"
#if( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rc_Prot.hpp"
#if((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF) && (DCM_CFG_IN_PARAM_MAXLEN > 0u))
#include "rba_BswSrv.hpp"
#endif
#endif
#include "DcmAppl.hpp"

#endif

