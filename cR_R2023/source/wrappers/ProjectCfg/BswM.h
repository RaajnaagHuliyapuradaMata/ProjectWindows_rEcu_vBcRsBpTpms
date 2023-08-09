

#ifndef _BSWM_H_
#define _BSWM_H_

#include "types.h"
#include "CanSM_BswM.h"

#define BSWM_AR_RELEASE_MAJOR_VERSION 4
#define BSWM_AR_RELEASE_MINOR_VERSION 2

// Define some missing types

typedef struct
{
    P2CONST( void, TYPEDEF, BSWM_CONST ) BswM_ConfigDataPtr;
    P2CONST( Std_VersionInfoType, TYPEDEF, BSWM_CONST ) BswM_VersionInfoPtr;
} Type_CfgSwcServiceBswM_st;

extern CONST(Type_CfgSwcServiceBswM_st, BSWM_CONST) BswM_Config;

extern void BswM_EcuM_CurrentWakeup (uint32 EcuM_Lok_dataExpiredWakeupEvents_u32 , uint8 ucWupStatusMode);
extern void BswM_Deinit(void);
extern void BswM_Init(const Type_CfgSwcServiceBswM_st* tBswmConfig);

#endif
