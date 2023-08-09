

#ifndef DCMDSPUDS_RDPI_INF_H
#define DCMDSPUDS_RDPI_INF_H

#include "Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) )

#include "DcmDspUds_Rdpi_Prot.h"

#include "DcmCore_DslDsd_Prot.h"

#include "DcmDspUds_Uds_Prot.h"

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdbi_Prot.h"
#endif
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dddi_Prot.h"
#endif
#include "Dcm_Cfg_SchM.h"

#endif

#endif

