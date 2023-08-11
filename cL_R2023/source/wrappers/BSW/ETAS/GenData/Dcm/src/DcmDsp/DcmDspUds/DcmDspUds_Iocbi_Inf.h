

#ifndef DCMDSPUDS_IOCBI_INF_H
#define DCMDSPUDS_IOCBI_INF_H

#include "Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspUds.h"
#include "DcmDspUds_Iocbi_Prot.h"
#endif
#include "DcmAppl.h"

 #if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#endif

#endif

