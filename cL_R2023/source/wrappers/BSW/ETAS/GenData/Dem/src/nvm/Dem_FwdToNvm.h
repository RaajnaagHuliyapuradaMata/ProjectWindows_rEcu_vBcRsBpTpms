

#ifndef DEM_FWDTONVM_H
#define DEM_FWDTONVM_H

#include "Dem_EventStatusNvData.h"
#include "Dem_EvMemNvData.h"
#include "Dem_GenericNvData.h"
#include "Dem_DisturbanceMemoryNvData.h"

#include "Dem_EvBuffTypes.h"
#include "Dem_IndicatorAttributesNvData.h"
#include "Dem_NvmHashIdNvData.h"

#if (DEM_CFG_OBD == DEM_CFG_OBD_ON)

#include "rba_DemObdBasic_DemNvData.h"

#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )

#include "rba_DemBfm_NvData.h"

#endif

#endif
