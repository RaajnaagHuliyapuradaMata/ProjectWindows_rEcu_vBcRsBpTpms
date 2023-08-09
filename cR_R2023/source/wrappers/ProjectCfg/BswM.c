

#include "types.h"
#include "BswM_ComM.h"
#include "BswM_CanSM.h"
#include "BswM.h"
#include "EcuM_Cfg_Startup.h"

// Define missing types for Ecum
CONST(Type_CfgSwcServiceBswM_st, BSWM_CONST) BswM_Config =
{
  NULL_PTR,
  NULL_PTR
};

void BswM_CanSM_CurrentState(uint8 ucComM_channelId, CanSM_BswMCurrentStateType eCanSM_BswM_Mode)
{
  // just a dummy
}

void BswM_Init(const Type_CfgSwcServiceBswM_st* tBswmConfig)
{

}

void BswM_Deinit(void)
{

}

void BswM_EcuM_CurrentWakeup (uint32 EcuM_Lok_dataExpiredWakeupEvents_u32 , uint8 ucWupStatusMode)
{

}

void BswM_ComM_CurrentMode(NetworkHandleType ChannelIndex, ComM_ModeType channelMode_e)
{

}

