

#ifndef DCMDSPUDS_RDPI_INF_H
#define DCMDSPUDS_RDPI_INF_H

#include "Dcm.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) )

#include "DcmDspUds_Rdpi_Prot.hpp"

#include "DcmCore_DslDsd_Prot.hpp"

#include "DcmDspUds_Uds_Prot.hpp"

#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdbi_Prot.hpp"
#endif
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dddi_Prot.hpp"
#endif
#include "Dcm_Cfg_SchM.hpp"

#endif

#endif

