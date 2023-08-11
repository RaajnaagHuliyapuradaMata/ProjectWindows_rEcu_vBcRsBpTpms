

#ifndef DCMDSPUDS_RMBA_INF_H
#define DCMDSPUDS_RMBA_INF_H

#include "Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"
#if (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rmba_Prot.h"
#endif
#include "DcmAppl.h"
#endif

#endif

