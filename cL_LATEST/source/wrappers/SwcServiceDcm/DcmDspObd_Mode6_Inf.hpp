

#ifndef DCMDSPOBD_MODE6_INF_H
#define DCMDSPOBD_MODE6_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif

#if((DCM_CFG_DSP_OBDMODE6_ENABLED != DCM_CFG_OFF) && (DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_OFF))
#include "Dem.hpp"
#endif

#include "DcmCore_DslDsd_Prot.hpp"

#endif

#endif

