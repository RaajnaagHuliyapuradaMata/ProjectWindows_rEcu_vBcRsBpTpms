#ifndef COMM_H
#define COMM_H

#include "ComM_Cfg.h"
#include "ComM_Dcm.h"
#include "ComM_BusSM.h"
#include "ComM_EcuMBswM.h"
#include "ComM_Nm.h"
#include "ComM_Main.h"
#include "CfgSwcServiceComM.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

extern void ComM_Init(const Type_CfgSwcServiceComM_st * config);
extern void ComM_DeInit(void);
extern Std_ReturnType ComM_GetState(NetworkHandleType Channel, ComM_StateType *  State);
extern Std_ReturnType ComM_GetStatus(ComM_InitStatusType * Status);
extern void ComM_GetVersionInfo(Std_VersionInfoType * versioninfo);

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_GetMaxComMode(ComM_UserHandleType User, ComM_ModeType * ComMode);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_GetRequestedComMode(ComM_UserHandleType User, ComM_ModeType * ComMode);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_GetCurrentComMode(ComM_UserHandleType User, ComM_ModeType * ComMode);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_LimitChannelToNoComMode(NetworkHandleType Channel, boolean Status);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_LimitECUToNoComMode(boolean Status);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_PreventWakeUp(NetworkHandleType Channel, boolean Status);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_ReadInhibitCounter(uint16 * CounterValue);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_ResetInhibitCounter(void);
#endif

#ifndef COMM_RTE_GENERATED_APIS
extern Std_ReturnType ComM_GetInhibitionStatus(NetworkHandleType Channel, ComM_InhibitionStatusType * Status);
#endif

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if ( COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE )
 #define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
 #define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "ComM_MemMap.h"

extern const Type_CfgSwcServiceComM_st ComM_Config;
#if ( COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE )
 #define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
 #define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "ComM_MemMap.h"

#endif
