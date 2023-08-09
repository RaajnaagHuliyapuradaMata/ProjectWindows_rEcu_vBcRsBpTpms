

#ifndef DCMDSPUDS_TRANSFERDATA_INF_H
#define DCMDSPUDS_TRANSFERDATA_INF_H

#include "Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"
#include "DcmAppl.h"
#endif

#if(DCM_CFG_DSP_TRANSFERDATA_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Memaddress_Calc_Prot.h"
#endif

#endif

