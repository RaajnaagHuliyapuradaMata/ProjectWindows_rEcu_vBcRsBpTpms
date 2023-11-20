

#ifndef DCMDSPUDS_RDTC_INF_H
#define DCMDSPUDS_RDTC_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#include "Dem.hpp"
#include "DcmAppl.hpp"

#include "DcmCore_DslDsd_Prot.hpp"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Inf.hpp"
#endif

#endif

#endif

