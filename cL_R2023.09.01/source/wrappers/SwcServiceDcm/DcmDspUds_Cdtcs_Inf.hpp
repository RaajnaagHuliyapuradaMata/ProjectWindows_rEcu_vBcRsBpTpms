

#ifndef DCMDSPUDS_CDTCS_INF_H
#define DCMDSPUDS_CDTCS_INF_H

#include "Dcm.hpp"
#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.hpp"
#endif
#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#include "DcmDspUds_Cdtcs_Prot.hpp"
#include "Dcm_Cfg_SchM.hpp"
#endif
#include "DcmAppl.hpp"

#endif

