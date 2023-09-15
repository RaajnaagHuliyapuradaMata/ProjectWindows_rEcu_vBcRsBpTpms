

#ifndef DCMDSPUDS_WMBA_INF_H
#define DCMDSPUDS_WMBA_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Wmba_Prot.hpp"
#endif
#include "DcmAppl.hpp"
#endif

#endif

