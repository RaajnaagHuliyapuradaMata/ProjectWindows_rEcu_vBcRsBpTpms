

#ifndef DCMDSPOBD_MODE4_INF_H
#define DCMDSPOBD_MODE4_INF_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif

#include "Dem.hpp"

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmAppl.hpp"

#endif

#endif
