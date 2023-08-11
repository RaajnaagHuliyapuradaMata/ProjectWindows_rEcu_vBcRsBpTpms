

#include "RdcStandstillDebug.h"

#ifdef DEBUG_PRESSURE_ON_KEY

#include "Com.h"
#include "CanManagerX.h"
#include "Com_PbCfg_InternalId.h"
#include "CanTrcv.h"
#include "RdcStandstillX.h"

tStandstillDebugMsg tStandstillMonDebugMsg;
boolean bMessageTrigger = FALSE;

const uint8 SSMDEBUG_CAU8_WakeByTau[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_WAKE_BY_TAU_FL, cSSMDEBUG_EVENT_WAKE_BY_TAU_FR, cSSMDEBUG_EVENT_WAKE_BY_TAU_RL, cSSMDEBUG_EVENT_WAKE_BY_TAU_RR};
const uint8 SSMDEBUG_CAU8_RecWs[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_REC_WS_FL, cSSMDEBUG_EVENT_REC_WS_FR, cSSMDEBUG_EVENT_REC_WS_RL, cSSMDEBUG_EVENT_REC_WS_RR};
const uint8 SSMDEBUG_CAU8_WindowExpired[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_WINDOW_EXPIRED_FL, cSSMDEBUG_EVENT_WINDOW_EXPIRED_FR, cSSMDEBUG_EVENT_WINDOW_EXPIRED_RL, cSSMDEBUG_EVENT_WINDOW_EXPIRED_RR};

void SSMDEBUG_MainFunction(void)
{
  if (bMessageTrigger == TRUE)
  {
    CANMGR_SetFullCommunicationMode();
    TRCV_Normal();

    CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);

    Com_TriggerIPDUSend(ComConf_ComIPdu_Internal_TPMS_ApplicationResponse_Can_Network_CANNODE_0);
  }
}

void SSMDEBUG_SetEvent(uint8 ucEventType)
{
  if(FALSE != RdcSt_IsDebugMessagingActive())
  {

    tStandstillMonDebugMsg.ucEventType = ucEventType;

    RdcSt_LoadDebugData(&tStandstillMonDebugMsg);

    bMessageTrigger = TRUE;
  }
}

tStandstillDebugMsg* SSMDEBUG_GetPointerToBuffer(void)
{
  return &tStandstillMonDebugMsg;
}

void SSMDEBUG_StopTrigger(void)
{
  tStandstillMonDebugMsg.ucEventType = 0x00;
  bMessageTrigger = FALSE;
}

#endif //DEBUG_PRESSURE_ON_KEY

