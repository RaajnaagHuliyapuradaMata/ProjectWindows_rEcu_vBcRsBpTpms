

#ifndef DEM_NVMHASHIDNVDATA_H
#define DEM_NVMHASHIDNVDATA_H

#include "Platform_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_Cfg_Nvm.hpp"

typedef uint8 Dem_NvmHashIdType;

#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED == DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK)
DEM_ARRAY_DECLARE(Dem_NvmHashIdType, Dem_HashIdInNvm, DEM_NVM_HASH_ID_SIZE);
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#endif
