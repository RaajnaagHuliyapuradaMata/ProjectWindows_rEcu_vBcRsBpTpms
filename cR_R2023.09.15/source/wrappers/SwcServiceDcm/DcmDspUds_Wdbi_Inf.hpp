

#ifndef DCMDSPUDS_WDBI_INF_H
#define DCMDSPUDS_WDBI_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDspUds_Uds_Prot.hpp"

#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Wdbi_Prot.hpp"
#include "Dcm_Lcfg_DspUds.hpp"
#endif
#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif
#include "DcmAppl.hpp"
#endif

#endif

