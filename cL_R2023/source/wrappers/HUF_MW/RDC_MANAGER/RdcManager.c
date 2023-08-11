

#include "RdcManager.h"

#include "RdcRingBufferX.h"
#include "TmsManagerX.h"
#include "EnvManagerX.h"
#include "RdcStandstillX.h"

static boolean Rdc__BO_IdRead;

static Rdc__Struct_WsLastTelegramData Rdc__S_LastTelegrams[RDC__NUMBER_OF_WS];

static uint32 Rdc__U32_ECUTimestamp;

static uint64 Rdc__U64_StartValueCGMTimestamp;

static uint64 Rdc__U64_CurrentValueCGMTimestamp;

static boolean Rdc__CheckStartOfId(uint8 *PU8_TelegramData);

static void Rdc__StoreIds(void);

static boolean Rdc__CheckIdAfterAutolearn(struct rfstruct* PS_TelegramData, uint32* PU32_Timestamp);

extern void Rdc_Init(void)
{
  uint8 U8_Counter;

  Rdc__BO_IdRead = FALSE;

  Rdc__U32_ECUTimestamp = RDC__TIMESTAMP_INIT;
  Rdc__U64_StartValueCGMTimestamp = RDC__CGM_TIMESTAMP_INIT;
  Rdc__U64_CurrentValueCGMTimestamp = RDC__CGM_TIMESTAMP_INIT;

  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    Rdc__S_LastTelegrams[U8_Counter].U32_Timestamp = RDC__TIMESTAMP_INIT;
    Rdc__S_LastTelegrams[U8_Counter].U32_WsId = RDC__WS_ID_INIT;
    Rdc__S_LastTelegrams[U8_Counter].U8_PacketID = RDC__WS_PCK_ID_INIT;
  }

  RdcRb_Init();
  RdcSt_Init();
}

//RST Debug RX
//uint16 ushTgCounter_CorrectSid = 0;
//extern uint16 Debug_GetTGCtCorrectSid(void)
//{
//  return ushTgCounter_CorrectSid;
//}

extern void Rdc_ProcessTelegram(struct rfstruct* PS_TelegramData)
{
  boolean BO_StoreTelegram = FALSE;
  uint32 U32_Timestamp = 0U;

  ClientIf_GetECUTimeStampValue(&U32_Timestamp);

  //////////////////if(HufIf_CheckCRC8(PS_TelegramData->buffer, PS_TelegramData->level) != FALSE)   Ändern 3 > check CRC8 in ata_Rec.c now (like SYMC and ealier projects)
  //////////////////{

    if(Rdc__CheckStartOfId(PS_TelegramData->buffer) != FALSE)
    {
      boolean BO_IsDeveloperModeActive = Tms_IsDeveloperModeActive();
      boolean BO_IsAutolearnFinished = Tms_IsAutolearnFinished();

      if((BO_IsDeveloperModeActive == FALSE) && (BO_IsAutolearnFinished != FALSE))
      {

        if(Rdc__CheckIdAfterAutolearn(PS_TelegramData, &U32_Timestamp) != FALSE)
        {
          BO_StoreTelegram = TRUE;
        }
        else
        {

        }
      }
      else
      {
        BO_StoreTelegram = TRUE;
      }
    }
    else
    {

      //ushTgCounter_CorrectSid++; //RST Debug Rx sid failed
    }
  #if 0

      }
      else
      {

      }
  #endif

  if(BO_StoreTelegram != FALSE)
  {

    if(FALSE != RdcSt_IsStandstillMonitoringActive())
    {

      RdcSt_ProcessStandstillTelegram(PS_TelegramData->buffer);
    }
    else
    {

      RdcRb_StoreTelegram(PS_TelegramData, &U32_Timestamp);
    }
  }
  else
  {

  }
}

extern void Rdc_ForwardRfDataToTms(void)
{
  tsEnv_Data* PS_EnvData = Env_GetEnvironmentData();

  while(RdcRb_IsBufferEmpty() == FALSE)
  {
    tsWS_RxDataIn* PS_RxData = RdcRb_ReadTelegram();
    HufIf_RCtSaReTelDec(PS_RxData, PS_EnvData);
  }
}

extern void Rdc_ForwardSimulatedRfDataToTms(uint8* PU8_DataPointer)
{
  tsWS_RxDataIn S_RxData;
  uint16 U16_SimulatedTimestamp;
  tsEnv_Data* PS_EnvData = Env_GetEnvironmentData();

  U16_SimulatedTimestamp = (((uint16) PU8_DataPointer[6]) << 8) | ((uint16) PU8_DataPointer[7]);

  if ((PU8_DataPointer[2] == RDC__LEARN_TELEGRAM_PACKAGE_ID) && (U16_SimulatedTimestamp != 0xFFFFU))
  {
    PU8_DataPointer[6] = 0xff;
    PU8_DataPointer[7] = 0xff;
  }

  ClientIf_GetECUTimeStampValue(&S_RxData.ulRxTimeStamp);
  //S_RxData.ulRxTimeStamp -= RDC__WHEEL_PULSE_TRAVEL_TIME_MS;  // RST Debug: try with constant delay. Maybe this should be made configurable by diagnostic service?

  S_RxData.ucaTelegram[9] = PU8_DataPointer[6];
  S_RxData.ucaTelegram[10] = PU8_DataPointer[7];

#if 0

  if ((PU8_DataPointer[2] == RDC__LEARN_TELEGRAM_PACKAGE_ID) && (U16_SimulatedTimestamp != 0xFFFFU))
  {
    S_RxData.ulRxTimeStamp = Rdc_ConvertWheelPulseTimestamp(U16_SimulatedTimestamp);
    S_RxData.ucaTelegram[9] = 0xFFU;
    S_RxData.ucaTelegram[10] = 0xFFU;
  }
  else
  {

    ClientIf_GetECUTimeStampValue(&S_RxData.ulRxTimeStamp);
    S_RxData.ulRxTimeStamp -= RDC__WHEEL_PULSE_TRAVEL_TIME_MS;  // RST Debug

    S_RxData.ucaTelegram[9] = PU8_DataPointer[6];
    S_RxData.ucaTelegram[10] = PU8_DataPointer[7];
  }
#endif

  S_RxData.uiRxRSSI = (uint16) PU8_DataPointer[3];

  S_RxData.ucaTelegram[0] = 0x00U;
  S_RxData.ucaTelegram[1] = 0x00U;
  S_RxData.ucaTelegram[2] = PU8_DataPointer[2];
  S_RxData.ucaTelegram[3] = PU8_DataPointer[0];
  S_RxData.ucaTelegram[4] = 0x00U;
  S_RxData.ucaTelegram[5] = 0x00U;
  S_RxData.ucaTelegram[6] = PU8_DataPointer[1];
  S_RxData.ucaTelegram[7] = PU8_DataPointer[4];
  S_RxData.ucaTelegram[8] = PU8_DataPointer[5];

  if(FALSE != RdcSt_IsStandstillMonitoringActive())
  {

    RdcSt_ProcessStandstillTelegram(&S_RxData.ucaTelegram[2]);
  }
  else
  {
    HufIf_RCtSaReTelDec(&S_RxData, PS_EnvData);
  }
}

extern void Rdc_IncrementTimestamp(void)
{
  Rdc__U32_ECUTimestamp++;
}

extern void Rdc_SynchronizeToCGMTimestamp(uint64 U64_CGMTimestamp)
{
  Rdc__U64_CurrentValueCGMTimestamp = U64_CGMTimestamp;

  if(RDC__CGM_TIMESTAMP_INIT == Rdc__U64_StartValueCGMTimestamp)
  {
    Rdc__U64_StartValueCGMTimestamp = U64_CGMTimestamp;
    Rdc__U32_ECUTimestamp = RDC__TIMESTAMP_INIT;
  }
  else
  {

    if(Rdc__U64_CurrentValueCGMTimestamp > Rdc__U64_StartValueCGMTimestamp)
    {
      Rdc__U32_ECUTimestamp = ((uint32) (Rdc__U64_CurrentValueCGMTimestamp - Rdc__U64_StartValueCGMTimestamp));
    }
    else
    {

    }
  }
}

extern uint32 Rdc_ConvertWheelPulseTimestamp(uint16 U16_WheelPulseTimestamp)
{
  uint32 U32_ConvertedTimestamp;

  if(RDC__CGM_TIMESTAMP_INIT != Rdc__U64_StartValueCGMTimestamp)
  {

    ClientIf_GetECUTimeStampValue(&U32_ConvertedTimestamp);
  }
  else
  {

    uint64 U64_WheelPulseAbsoluteTimestamp;

    if(U16_WheelPulseTimestamp < ((uint16) (Rdc__U64_CurrentValueCGMTimestamp & 0xFFFFU)))
    {

      U64_WheelPulseAbsoluteTimestamp = (Rdc__U64_CurrentValueCGMTimestamp & 0xFFFFFFFFFFFF0000U) | ((uint64) U16_WheelPulseTimestamp);
    }
    else
    {

      U64_WheelPulseAbsoluteTimestamp = ((Rdc__U64_CurrentValueCGMTimestamp & 0xFFFFFFFFFFFF0000U) - 0x10000U) | ((uint64) U16_WheelPulseTimestamp);
    }

    U32_ConvertedTimestamp = ((uint32) (U64_WheelPulseAbsoluteTimestamp - Rdc__U64_StartValueCGMTimestamp));
  }

  if(U32_ConvertedTimestamp > RDC__WHEEL_PULSE_TRAVEL_TIME_MS)
  {
    U32_ConvertedTimestamp -= RDC__WHEEL_PULSE_TRAVEL_TIME_MS;
  }

  return U32_ConvertedTimestamp;
}

extern void Rdc_StoreLatestCGMTimestamp(uint64 *PU64_CGMTimestamp)
{
  *PU64_CGMTimestamp = Rdc__U64_CurrentValueCGMTimestamp;
}

static boolean Rdc__CheckStartOfId(uint8 *PU8_TelegramData)
{
  boolean BO_IsStartOfIdValid = FALSE;

  if((PU8_TelegramData[RDC__MSB_OF_ID_POS] >= RDC__VALID_MSB_OF_ID_START) &&
     (PU8_TelegramData[RDC__MSB_OF_ID_POS] <= RDC__VALID_MSB_OF_ID_END))
  {
    BO_IsStartOfIdValid = TRUE;
  }
  else
  {

  }

  return BO_IsStartOfIdValid;
}

static void Rdc__StoreIds(void)
{
  uint8 U8_Counter;
  NVM_BLOCK_TYPE U32_NvmBlock[RDC__NUMBER_OF_WS];

  (void) ClientIf_NvM_ReadBlock(RDC__GLOBAL_NVM_INDEX, RDC__NUMBER_OF_WS, &U32_NvmBlock[0]);

  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    Rdc__S_LastTelegrams[U8_Counter].U32_WsId = U32_NvmBlock[U8_Counter];
  }

  Rdc__BO_IdRead = TRUE;
}

static boolean Rdc__CheckIdAfterAutolearn(struct rfstruct* PS_TelegramData, uint32* PU32_Timestamp)
{
  uint8 U8_Counter;
  uint32 U32_WsId;
  boolean BO_ForwardRfData = FALSE;

  if(Rdc__BO_IdRead == FALSE)
  {
    Rdc__StoreIds();
  }
  else
  {

  }

  U32_WsId = ((uint32) PS_TelegramData->buffer[RDC__MSB_OF_ID_POS]<<24) | ((uint32) PS_TelegramData->buffer[RDC__MSB_OF_ID_POS + 1U]<<16) | ((uint32) PS_TelegramData->buffer[RDC__MSB_OF_ID_POS + 2U]<<8) | ((uint32) PS_TelegramData->buffer[RDC__MSB_OF_ID_POS + 3U]);

  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    if(U32_WsId == Rdc__S_LastTelegrams[U8_Counter].U32_WsId)
    {
      break;
    }
    else
    {

    }
  }

  if(U8_Counter < RDC__NUMBER_OF_WS)
  {

    if(((*PU32_Timestamp) > (Rdc__S_LastTelegrams[U8_Counter].U32_Timestamp + RDC__MINIMUM_TIME_DIF_MS)) ||
       (PS_TelegramData->buffer[RDC__PACKET_ID_POS] != Rdc__S_LastTelegrams[U8_Counter].U8_PacketID))
    {

      BO_ForwardRfData = TRUE;

      Rdc__S_LastTelegrams[U8_Counter].U32_Timestamp = (*PU32_Timestamp);
      Rdc__S_LastTelegrams[U8_Counter].U8_PacketID = PS_TelegramData->buffer[RDC__PACKET_ID_POS];
    }
  }
  else
  {

  }

  return BO_ForwardRfData;
}

void ClientIf_Debug_Init_Huf_SWC(void)
{
}

void ClientIf_Debug_RCtSaEnvData(const tsEnv_Data* spRxEnvDataIn)
{
}

void ClientIf_Debug_RCtSaReTelDec(const tsWS_RxDataIn* spRxDataIn,const tsEnv_Data* spEnvDataIn)
{
}

void ClientIf_Debug_RCtAbsEnvData(const tsEnvAbs_Data* spRxEnvAbsDataIn)
{
}

void ClientIf_Debug_RCtSaTpmsData(tsTPMS_Data* spTPMS_Data,const tsEnv_Data* spEnvData)
{
}

void ClientIf_Debug_GetVersion(struct struct_Version *sVersion)
{
}

void ClientIf_Debug_CheckCRC8(const uint8 * pucAkTel,boolean bReturnVal)
{
}

void ClientIf_GetECUTimeStampValue (uint32 *ulpECUTimeStamp)
{
  *ulpECUTimeStamp = Rdc__U32_ECUTimestamp;
}
