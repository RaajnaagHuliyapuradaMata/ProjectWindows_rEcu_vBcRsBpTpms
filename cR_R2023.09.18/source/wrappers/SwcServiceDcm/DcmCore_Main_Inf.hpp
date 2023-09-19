

#ifndef DCMCORE_MAIN_INF_H
#define DCMCORE_MAIN_INF_H

#include "Dcm.hpp"
#include "ComM_Dcm.hpp"

#include "Dcm_Cfg_SchM.hpp"
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.hpp"
#include "SchM_Dcm.hpp"
#endif
#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif

#include "DcmCore_DslDsd_Prot.hpp"
#include "Dcm_Dsl_Priv.hpp"

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Inf.hpp"
#endif

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Uds_Prot.hpp"
#include "DcmDspUds_Rc_Prot.hpp"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Dddi_Prot.hpp"
#endif

#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Iocbi_Prot.hpp"
#endif

#endif
#include "DcmAppl.hpp"

#endif

