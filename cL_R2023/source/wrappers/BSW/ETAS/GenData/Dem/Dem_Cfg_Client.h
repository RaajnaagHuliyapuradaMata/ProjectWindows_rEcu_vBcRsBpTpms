

#ifndef DEM_CFG_CLIENT_H
#define DEM_CFG_CLIENT_H

#include "Std_Types.h"
#include "Dem_ClientHandlingTypes.h"

#define DEM_CLIENTS_COUNT_STANDARD    1u
#define DEM_CLIENTID_ARRAYLENGTH_STD      (DEM_CLIENTS_COUNT_STANDARD+1u)

#define DEM_CLIENTID_ARRAYLENGTH_TOTAL      (DEM_CLIENTID_ARRAYLENGTH_STD+1u)

#define DemConf_DemClient_DemClient     1u

#define DEM_CLIENTID_J1939 (DEM_CLIENTS_COUNT_STANDARD+1u)

#define DEM_CLIENTID_INVALID  0x00

#define DEM_CFG_CLIENT_NUMBER_OF_CLIENTS_USING_RTE 0u

#endif

