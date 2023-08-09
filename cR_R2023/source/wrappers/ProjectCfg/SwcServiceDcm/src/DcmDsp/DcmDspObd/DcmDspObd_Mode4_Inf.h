

#ifndef DCMDSPOBD_MODE4_INF_H
#define DCMDSPOBD_MODE4_INF_H

#include "Dcm.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#include "Dem.h"

#include "DcmCore_DslDsd_Prot.h"
#include "DcmAppl.h"

#endif

#endif
