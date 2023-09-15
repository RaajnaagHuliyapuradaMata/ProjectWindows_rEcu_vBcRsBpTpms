#include "Std_Types.hpp"

#include "types.hpp"
#include "BswM_ComM.hpp"
#include "BswM_CanSM.hpp"
#include "BswM.hpp"
#include "EcuM_Cfg_Startup.hpp"
#include "CfgSwcServiceBswM.hpp"

CONST(Type_CfgSwcServiceBswM_st, BSWM_CONST) CfgSwcServiceBswM_cst = {
      NULL_PTR
   ,  NULL_PTR
};

void BswM_CanSM_CurrentState(uint8 ucComM_channelId, CanSM_BswMCurrentStateType eCanSM_BswM_Mode){}
void BswM_Init(const Type_CfgSwcServiceBswM_st* tBswmConfig){}
void BswM_Deinit(void){}
void BswM_EcuM_CurrentWakeup (uint32 EcuM_Lok_dataExpiredWakeupEvents_u32 , uint8 ucWupStatusMode){}
void BswM_ComM_CurrentMode(NetworkHandleType ChannelIndex, ComM_ModeType channelMode_e){}

