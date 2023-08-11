#ifndef ECUM_CFG_STARTUP_H
#define ECUM_CFG_STARTUP_H

#include "Os.h"

#include "CanIf.h"
#include "ComM.h"
#include "CanSM.h"
#include "PduR.h"
#include "Com.h"
#include "CanTp.h"
#include "FiM.h"
#include "BswM.h"

#define ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_MemMap.h"
extern const Type_CfgSwcServiceEcuM_st EcuM_Config;
#define ECUM_NO_OF_ECUMCONFIGSETS 1
extern const Type_CfgSwcServiceEcuM_st * const EcuM_EcuMConfigurations_cpcast[ECUM_NO_OF_ECUMCONFIGSETS];
#define ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_MemMap.h"

#endif

