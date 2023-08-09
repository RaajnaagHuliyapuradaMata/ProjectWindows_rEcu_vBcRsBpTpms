

#ifndef DCMDSPOBD_MODE2_INF_H
#define DCMDSPOBD_MODE2_INF_H

#include "Dcm.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)
#include "Dem.h"
#endif

#include "DcmCore_DslDsd_Prot.h"

#endif

#endif

