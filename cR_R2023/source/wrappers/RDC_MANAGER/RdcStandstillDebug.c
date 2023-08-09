

#include "RdcStandstillDebug.h"

#ifdef DEBUG_PRESSURE_ON_KEY

#include "Com.h"
#include "CanManagerX.h"
#include "Com_PbCfg_InternalId.h"
#include "CanTrcv.h"
#include "RdcStandstillX.h"
#include "SysManagerX.h"
#include "iTpms_Interface.h"

tStandstillDebugMsg tStandstillMonDebugMsg[cSIZE_SSM_MESSAGE_FIFO];     //Fifo array for ssm debug messages
tStandstillDebugMsg* pStandstillMonDebugMsg = tStandstillMonDebugMsg;   //Pointer to fifo entry for writing purpose
uint8 ucFifoPointerRead = 0;                                            //To manage the fifo read and write pointers
uint8 ucFifoPointerWrite = 0;
boolean bMessageTrigger = FALSE;

const uint8 SSMDEBUG_CAU8_WakeByTau[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_WAKE_BY_TAU_FL, cSSMDEBUG_EVENT_WAKE_BY_TAU_FR, cSSMDEBUG_EVENT_WAKE_BY_TAU_RL, cSSMDEBUG_EVENT_WAKE_BY_TAU_RR};
const uint8 SSMDEBUG_CAU8_RecWs[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_REC_WS_FL, cSSMDEBUG_EVENT_REC_WS_FR, cSSMDEBUG_EVENT_REC_WS_RL, cSSMDEBUG_EVENT_REC_WS_RR};
const uint8 SSMDEBUG_CAU8_WindowExpired[RDC__NUMBER_OF_WS] = {cSSMDEBUG_EVENT_WINDOW_EXPIRED_FL, cSSMDEBUG_EVENT_WINDOW_EXPIRED_FR, cSSMDEBUG_EVENT_WINDOW_EXPIRED_RL, cSSMDEBUG_EVENT_WINDOW_EXPIRED_RR};

//extern void Debug_GetAtaRecCounters(uint8* Ct1_Systemfehler, uint8* Ct2_TgLen, uint8* Ct3_Crc);
//extern void Debug_GetIdNotInHistoryCounter(uint8* pucIdnihCt);
//extern void Debug_GetWrongSidCounter(uint8* ucCtWrongSid);

//void SSMDEBUG_GetReceptionFailedCounters(tStandstillDebugMsg* tDebugData)
//{
//  Debug_GetAtaRecCounters(0, 0, (uint8*)&tDebugData->ucRecCntFL);  // number of TGs lost because of wrong CRC
//  Debug_GetWrongSidCounter((uint8*)&tDebugData->ucRecCntFR);       // number of TGs lost because of wrong SID
//  Debug_GetIdNotInHistoryCounter((uint8*)&tDebugData->ucRecCntRL); // number of TGs lost because of failed history check
//}

void SSMDEBUG_MainFunction(void)
{
  if (bMessageTrigger == TRUE)
  {
    CANMGR_SetFullCommunicationMode();
    TRCV_Normal();

    CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);

    Com_TriggerIPDUSend(ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0);
  }
}

void SSMDEBUG_SetEvent(uint8 ucEventType)
{
  //Dcm_SesCtrlType currentsession;

  if(FALSE != RdcSt_IsDebugMessagingActive())
  {

    pStandstillMonDebugMsg->ucEventType = ucEventType;

    RdcSt_LoadDebugData(pStandstillMonDebugMsg);

    if (ucEventType == cSSMDEBUG_EVENT_WAKEUP)
    {
      pStandstillMonDebugMsg->ucEventType |= (SYSMGR_GetEcuMode() & 0x0f);
    }

    else if ((ucEventType & cSSMDEBUG_EVENT_DEEPSTOP) == cSSMDEBUG_EVENT_DEEPSTOP)
    {
      RdcSt_LoadDebugData_NextWakeupTimer(pStandstillMonDebugMsg);
    }

    ucFifoPointerWrite++;
    ucFifoPointerWrite %= cSIZE_SSM_MESSAGE_FIFO;
    pStandstillMonDebugMsg = &tStandstillMonDebugMsg[ucFifoPointerWrite];

    bMessageTrigger = TRUE;
  }
}

tStandstillDebugMsg* SSMDEBUG_GetPointerToBuffer(void)
{
  tStandstillDebugMsg* pFifoEntry;

  pFifoEntry = &tStandstillMonDebugMsg[ucFifoPointerRead];
  return pFifoEntry;
}

void SSMDEBUG_StopTrigger(void)
{
  tStandstillDebugMsg* pFifoEntry;

  pFifoEntry = &tStandstillMonDebugMsg[ucFifoPointerRead];
  pFifoEntry->ucEventType = 0x00;
  //bMessageTrigger = FALSE;

  ucFifoPointerRead++;
  ucFifoPointerRead %= cSIZE_SSM_MESSAGE_FIFO;

  if (ucFifoPointerRead == ucFifoPointerWrite)
  {
    bMessageTrigger = FALSE;
  }
}

void SSMDEBUG_SetEvent_in_QuietMode(uint8 ucEventType, uint8 ucTgType, uint32 ulSensorId)
{
  if(FALSE != RdcSt_IsDebugMessagingActive())
  {
    pStandstillMonDebugMsg->ucEventType = ucEventType;
    pStandstillMonDebugMsg->ucRecCntFL = (uint8)((ulSensorId>>24) & 0xff);
    pStandstillMonDebugMsg->ucRecCntFR = (uint8)((ulSensorId>>16) & 0xff);
    pStandstillMonDebugMsg->ucRecCntRL = (uint8)((ulSensorId>> 8) & 0xff);
    pStandstillMonDebugMsg->ucRecCntRR = (uint8)((ulSensorId>> 0) & 0xff);
    pStandstillMonDebugMsg->ucWindowTime[0] = ucTgType;
    pStandstillMonDebugMsg->ucWindowTime[1] = 0;
    pStandstillMonDebugMsg->ucWindowTime[2] = 0;

    ucFifoPointerWrite++;
    ucFifoPointerWrite %= cSIZE_SSM_MESSAGE_FIFO;
    pStandstillMonDebugMsg = &tStandstillMonDebugMsg[ucFifoPointerWrite];

    bMessageTrigger = TRUE;
  }
}

#endif //DEBUG_PRESSURE_ON_KEY

void LTGDEBUG_SetEvent(uint8 ucTgType, uint32 ulSensorId, uint8 ucFilterType)
{
  #ifdef DEBUG_LOST_TELEGRAMS
  uint32 ulTimestamp;

  if(FALSE != RdcSt_IsDebugMessagingActive())
  {
    pStandstillMonDebugMsg->ucEventType = cLTGDEBUG_EVENT_FILTERED;
    pStandstillMonDebugMsg->ucEventType |= ucFilterType;
    pStandstillMonDebugMsg->ucRecCntFL = (uint8)((ulSensorId>>24) & 0xff);
    pStandstillMonDebugMsg->ucRecCntFR = (uint8)((ulSensorId>>16) & 0xff);
    pStandstillMonDebugMsg->ucRecCntRL = (uint8)((ulSensorId>> 8) & 0xff);
    pStandstillMonDebugMsg->ucRecCntRR = (uint8)((ulSensorId>> 0) & 0xff);
    pStandstillMonDebugMsg->ucWindowTime[0] = ucTgType;

    ClientIf_GetECUTimeStampValue(&ulTimestamp);
    pStandstillMonDebugMsg->ucWindowTime[1] = (ulTimestamp >> 8) & 0xff;
    pStandstillMonDebugMsg->ucWindowTime[2] = (ulTimestamp >> 0) & 0xff;

    if (ucFilterType >= cFILTER_CHAIN_START) //skip all filter events that come before cFILTER_CHAIN_START
    {

      ucFifoPointerWrite++;
      ucFifoPointerWrite %= cSIZE_SSM_MESSAGE_FIFO;
      pStandstillMonDebugMsg = &tStandstillMonDebugMsg[ucFifoPointerWrite];

      bMessageTrigger = TRUE;
    }
  }
  #endif //DEBUG_LOST_TELEGRAMS
}

