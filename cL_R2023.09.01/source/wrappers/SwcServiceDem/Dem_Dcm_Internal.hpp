

#ifndef DEM_DCM_INTERNAL_H
#define DEM_DCM_INTERNAL_H

#include "Dem_Cfg.hpp"
#include "Dem_Cfg_Client.hpp"
#include "Platform_Types.hpp"

#if(DEM_CFG_CHECKAPICONSISTENCY == FALSE) && (DEM_CFG_CLIENT_NUMBER_OF_CLIENTS_USING_RTE > 0)
#define DEM_HIDE_RTE_APIS
#endif
#include "Dem_Dcm.hpp"

#endif

