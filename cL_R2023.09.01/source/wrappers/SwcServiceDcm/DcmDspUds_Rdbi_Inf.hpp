

#ifndef DCMDSPUDS_RDBI_INF_H
#define DCMDSPUDS_RDBI_INF_H

#include "Dcm.hpp"
#include "rba_BswSrv.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.hpp"

#include "DcmDspUds_Rdbi_Prot.hpp"

#include "DcmDspUds_Uds_Prot.hpp"

#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dddi_Prot.hpp"
#endif

#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspUds.hpp"
#endif

#include "DcmAppl.hpp"

#endif

#endif
