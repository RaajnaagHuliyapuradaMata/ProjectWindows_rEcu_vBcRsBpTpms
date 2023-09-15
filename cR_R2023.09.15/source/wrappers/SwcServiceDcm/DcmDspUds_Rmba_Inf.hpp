

#ifndef DCMDSPUDS_RMBA_INF_H
#define DCMDSPUDS_RMBA_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rmba_Prot.hpp"
#endif
#include "DcmAppl.hpp"
#endif

#endif

