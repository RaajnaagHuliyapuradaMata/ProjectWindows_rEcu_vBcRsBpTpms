#ifndef DEM_CFG_CLIENT_H
#define DEM_CFG_CLIENT_H

#include "Dem_ClientHandlingTypes.hpp"

#define DEM_CLIENTS_COUNT      2u
#define DEM_CLIENTID_ARRAYLENGTH      (DEM_CLIENTS_COUNT+1u)
#define DemConf_DemClient_DemClient     1u
#define DEM_CLIENTID_J1939 DEM_CLIENTS_COUNT

#define DEM_CFG_CLIENTPARAMS { \
 \
{0,0}, \
{DemConf_DemClient_DemClient,    1},\
 \
}

#endif

