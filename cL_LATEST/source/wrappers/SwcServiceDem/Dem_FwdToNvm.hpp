

#ifndef DEM_FWDTONVM_H
#define DEM_FWDTONVM_H

#include "Dem_EventStatusNvData.hpp"
#include "Dem_EvMemNvData.hpp"
#include "Dem_GenericNvData.hpp"
#include "Dem_DisturbanceMemoryNvData.hpp"

#include "Dem_EvBuffTypes.hpp"
#include "Dem_IndicatorAttributesNvData.hpp"
#include "Dem_NvmHashIdNvData.hpp"

#if(DEM_CFG_OBD == DEM_CFG_OBD_ON)

#include "rba_DemObdBasic_DemNvData.hpp"

#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )

#include "rba_DemBfm_NvData.hpp"

#endif

#endif
