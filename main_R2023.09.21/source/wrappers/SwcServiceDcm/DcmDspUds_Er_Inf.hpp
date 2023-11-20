

#ifndef DCMDSPUDS_ER_INF_H
#define DCMDSPUDS_ER_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.hpp"
#endif

#include "DcmDspUds_Er_Prot.hpp"
#endif
#include "DcmCore_DslDsd_Prot.hpp"

#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif
#include "DcmAppl.hpp"
#endif

#endif

