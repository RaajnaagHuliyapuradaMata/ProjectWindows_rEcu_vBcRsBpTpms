

#ifndef FIM_CFG_PBCFG_H
#define FIM_CFG_PBCFG_H

#include "FiM_Types.h"

#define FIM_START_SEC_ROM_CONST
#include "FiM_MemMap.h"

extern const Type_CfgSwcServiceFiM_st FiMConfigSet;
#define FIM_POSTBUILD_CONFIGSET_NAME FiMConfigSet

#define FIM_STOP_SEC_ROM_CONST
#include "FiM_MemMap.h"
#endif
