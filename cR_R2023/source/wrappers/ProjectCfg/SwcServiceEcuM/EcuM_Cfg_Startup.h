#ifndef ECUM_CFG_STARTUP_H
#define ECUM_CFG_STARTUP_H

#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
	#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
	#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "CanIf.h"
#include "ComM.h"
#include "CanSM.h"
#include "PduR.h"
#include "Com.h"
#include "CanTp.h"
#include "FiM.h"
#include "BswM.h"

#define ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
extern CONST( Type_CfgSwcServiceEcuM_st, ECUM_CONST ) EcuM_Config;
#define ECUM_NO_OF_ECUMCONFIGSETS 1
extern CONSTP2CONST(Type_CfgSwcServiceEcuM_st,AUTOMATIC,ECUM_CONST) EcuM_EcuMConfigurations_cpcast[ECUM_NO_OF_ECUMCONFIGSETS];
#define ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#endif

