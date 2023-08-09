

#include "RdcStandstill.h"
#include "RdcRingbuffer.h"
#include "RdcManager.h"
#include "iTpms_Interface.h"
#include "TauX.h"
#include "SysManagerX.h"
#include "EnvManagerX.h"
#include "NvmManagerX.h"
#include "version.h"
#include "Rte_Nvm_Type.h"
#include "Mcu.h"

static boolean RRAM  RdcSt__BO_IsStandstillMonitoringActive;
static boolean RRAM RdcSt__BO_HasSyncPeriodExpired;

static uint32 RdcSt__U32_StartOfStandstillTimestamp;
static uint32 RdcSt__AU32_StartOfWakeupPeriod[RDC__NUMBER_OF_WS];

static uint8 RdcSt__U8_MonitoringStatus;
static uint8 RRAM RdcSt__U8_ExtendedWakeup;

static uint8 ucRepeatForwardSSMTelegramToLib = 0;

static RdcSt__Struct_WSData RRAM RdcSt__AS_WSData[RDC__NUMBER_OF_WS];

static uint8 RRAM RdcSt__U8_MainTimer;
static uint32 RRAM RdcSt__U32_ElapsedTimeInMs;

static RdcSt__Union_PressureOnKeyConfig RRAM RdcSt__UN_PressureOnKeyConfig;
static uint32 RRAM RdcSt__U32_WakeupInterval_xms;
static uint32 RRAM RdcSt__U32_WakeTime_xms;
static uint32 RRAM RdcSt__U32_WakeOffset_xms;

static uint64 RRAM RdcSt__U64_CGMTimestampAtStart;
static uint32 RRAM AU32_MonitoringTimeForEachWs_xms[RDC__NUMBER_OF_WS];
static uint32 RRAM AU32_LastReceptionTimestampForEachWs_xms[RDC__NUMBER_OF_WS];

static void RdcSt__UpdateSyncPeriod(void);

static void RdcSt__UpdateMonitoringStatus(void);

static void RdcSt__UpdateWakeupTimer(void);

static boolean RdcSt__AreTimersExpiringSoon(void);

static void RdcSt__SaveDataInNvm(void);

static void RdcSt__LoadDataFromNvm(void);

static void RdcSt__UpdateConfig(void);

static boolean RdcSt__DataExistsInNvm(void);

static void Rdc__ConvertLatestReceptionToEpochTime(uint8 *PU8_TimeAndDateString);

static void RdcSt__SaveStatusInNvm(void);

//static void RdcSt__ReadAndSortIDs(void);

extern void RdcSt_SetForwardingSSMTelegramFromRRAMToLibRepetitionCounter(uint8 ucRepeat)
{
  ucRepeatForwardSSMTelegramToLib = ucRepeat;
  RdcSt_ForwardStandstillDataToTms();
}

extern uint8 RdcSt_GetForwardingSSMTelegramFromRRAMToLibRepetitionCounter(void)
{
  return ucRepeatForwardSSMTelegramToLib;
}

extern void RdcSt_Init(void)
{
  RdcSt__UpdateConfig(); //RST Debug XXX: get config form NVM
  //RdcSt__ReadAndSortIDs(); //RST Debug XXX: check IDs on startup to be ready to put any P/T telegram into RRAM
  RdcSt_ReadAndSortIDs();
}

extern void RdcSt_InitBSWNvM(void)
{
  uint8 U8_Buffer;

  U8_Buffer = RDCST__PRESSURE_ON_KEY_ENABLED_INIT;
  NvmMGR_WriteBSWMember(NVM_E_PRESSURE_ON_KEY_ENABLED, &U8_Buffer);

  U8_Buffer = RDCST__WAKEUP_INTERVAL_INIT_XMIN;
  NvmMGR_WriteBSWMember(NVM_E_WAKEUP_INTERVAL, &U8_Buffer);

  U8_Buffer = RDCST__WAKE_TIME_INIT_X100MS;
  NvmMGR_WriteBSWMember(NVM_E_WAKE_TIME, &U8_Buffer);

  U8_Buffer = RDCST__WAKE_OFFSET_INIT_X100MS;
  NvmMGR_WriteBSWMember(NVM_E_WAKE_OFFSET, &U8_Buffer);

  U8_Buffer = RDCST__POKDB_INIT;
  NvmMGR_WriteBSWMember(NVM_E_POKDB, &U8_Buffer);
}

extern void RdcSt_ClearRramData(void)
{
  uint8 U8_Counter;
  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    #ifdef DEBUG_PRESSURE_ON_KEY
    SSMDEBUG_SetEvent_in_QuietMode(cSSMDEBUG_EVENT_RRAM_DATA_CLEAR, 0xff, RdcSt__AS_WSData[U8_Counter].U32_WsId);
    #endif

    RdcSt__AS_WSData[U8_Counter].U8_Pressure = RDCST__PRESSURE_INVALID_VALUE;
    RdcSt__AS_WSData[U8_Counter].U8_Temperature = RDCST__TEMPERATURE_INVALID_VALUE;
    RdcSt__AS_WSData[U8_Counter].U16_ReceivedCounter = 0;
  }
}

extern void RdcSt_StartStandstillMonitoring(void)
{
  RdcSt__UpdateConfig();

  if(FALSE != RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_PressureOnKeyEnabled)
  {
    uint8 U8_Counter;

    ClientIf_GetECUTimeStampValue(&RdcSt__U32_StartOfStandstillTimestamp);
    Tau_Init();

    Rdc_StoreLatestCGMTimestamp(&RdcSt__U64_CGMTimestampAtStart);

    //RdcSt__ReadAndSortIDs();
    RdcSt_ReadAndSortIDs();

    for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
    {

      //RdcSt__AS_WSData[U8_Counter].U8_Pressure = RDCST__PRESSURE_INVALID_VALUE;
      //RdcSt__AS_WSData[U8_Counter].U8_Temperature = RDCST__TEMPERATURE_INVALID_VALUE;
      RdcSt__AS_WSData[U8_Counter].U16_ReceivedCounter = 0U;

      AU32_MonitoringTimeForEachWs_xms[U8_Counter] = 0U;
      AU32_LastReceptionTimestampForEachWs_xms[U8_Counter] = 0U;
    }

    RdcSt__BO_IsStandstillMonitoringActive = TRUE;
    RdcSt__BO_HasSyncPeriodExpired = FALSE;
    RdcSt__U8_MonitoringStatus = RDCST__MONITORING_STATUS_CLEAR;
    RdcSt__U8_ExtendedWakeup = RDCST__EXTENDED_WAKEUP_CLEAR;
    RdcSt__U8_MainTimer = RDC__NUMBER_OF_WS;
    RdcSt__U32_ElapsedTimeInMs = 0U;

    RdcSt__U32_WakeupInterval_xms = RDCST__WAKEUP_TIMER_MINS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin) * RDCST__WAKEUP_TIMER_INITIAL_MULTIPLIER;
    RdcSt__U32_WakeTime_xms = RDCST__WAKEUP_TIMER_100MS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeTime_x100ms);
    RdcSt__U32_WakeOffset_xms = RDCST__WAKEUP_TIMER_100MS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeOffset_x100ms);
    #ifdef DEBUG_PRESSURE_ON_KEY
    SSMDEBUG_SetEvent(cSSMDEBUG_EVENT_START_SSM);
    #endif

    #ifdef DEBUG_PRESSURE_ON_KEY
    //RST Debug XXX -< test deepstop and timer wakeup
    //Tau_StartTimer(TAU_E_CHANNEL_2, 6000);
    //SYSMGR_SetEcuEvent(cECUEVENT_DEEPSTOP);
    //SSMDEBUG_SetEvent(cSSMDEBUG_EVENT_DEEPSTOP+0x0F); //0xEF = Timer test
    #endif

  }

  else
  {
    SYSMGR_SetEcuEvent(cECUEVENT_SHUTDOWN);
    #ifdef DEBUG_PRESSURE_ON_KEY
    SSMDEBUG_SetEvent(cSSMDEBUG_EVENT_SHUTDOWN_SSMOFF); //SSM is off by diag service
    #endif
  }

}

extern void RdcSt_StopStandstillMonitoring(void)
{
  uint8 U8_Counter;

  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    Tau_StopTimer((Tau_Enum_Channels) U8_Counter);
  }

  RdcSt__BO_IsStandstillMonitoringActive = FALSE;
}

extern boolean RdcSt_IsStandstillMonitoringActive(void)
{
  return RdcSt__BO_IsStandstillMonitoringActive;
}

extern void RdcSt_SavePressuresAndTemperaturesInRRAM(uint8 *PU8_TelegramData)
{
  uint8 U8_Counter;
  uint32 U32_WsId;
  uint8 U8_PackageId = PU8_TelegramData[0];

  if ((U8_PackageId == RDCST__PACKAGE_ID_AK_STD)
   || (U8_PackageId == RDCST__PACKAGE_ID_STATUS)
   || (U8_PackageId == RDCST__PACKAGE_ID_STATUS_LEARN)
   || (U8_PackageId == RDCST__PACKAGE_ID_STANDSTILL))
  {

    U32_WsId = ((uint32) PU8_TelegramData[1]<<24) | ((uint32) PU8_TelegramData[2]<<16) | ((uint32) PU8_TelegramData[3]<<8) | ((uint32) PU8_TelegramData[4]);

    for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
    {

      if(U32_WsId == RdcSt__AS_WSData[U8_Counter].U32_WsId)
      {
        RdcSt__AS_WSData[U8_Counter].U8_Pressure = PU8_TelegramData[5];
        RdcSt__AS_WSData[U8_Counter].U8_Temperature = PU8_TelegramData[6];

        #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent_in_QuietMode(cSSMDEBUG_EVENT_COPY_TG_TO_RRAM, PU8_TelegramData[0], U32_WsId);
        #endif
      }
    }
  }
}

extern void RdcSt_ProcessStandstillTelegram(uint8 *PU8_TelegramData)
{
  uint8 U8_PackageId = PU8_TelegramData[0];

  if(U8_PackageId == RDCST__PACKAGE_ID_STANDSTILL)
  {
    uint8 U8_Counter;
    uint32 U32_WsId = ((uint32) PU8_TelegramData[1]<<24) | ((uint32) PU8_TelegramData[2]<<16) | ((uint32) PU8_TelegramData[3]<<8) | ((uint32) PU8_TelegramData[4]);

    for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
    {

      if(U32_WsId == RdcSt__AS_WSData[U8_Counter].U32_WsId)
      {
        uint32 U32_CurrentTimestamp;
        uint32 U32_TimerValue = RdcSt__U32_WakeupInterval_xms - RdcSt__U32_WakeOffset_xms;

        if(RdcSt__U8_MainTimer == RDC__NUMBER_OF_WS)
        {
          RdcSt__U8_MainTimer = U8_Counter;
        }
        else
        {

        }

        RdcSt__AS_WSData[U8_Counter].U8_Pressure = PU8_TelegramData[5];
        RdcSt__AS_WSData[U8_Counter].U8_Temperature = PU8_TelegramData[6];

        if(RdcSt__AS_WSData[U8_Counter].U16_ReceivedCounter < 0xFFFF)
        {
          RdcSt__AS_WSData[U8_Counter].U16_ReceivedCounter++;
        }

        RdcSt__U8_MonitoringStatus &= (~(((uint8) 1U) << U8_Counter));
        RdcSt__U8_ExtendedWakeup &= (~(((uint8) 1U) << U8_Counter));

        #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent(SSMDEBUG_CAU8_RecWs[U8_Counter]);
        #endif

        Tau_StartTimer((Tau_Enum_Channels) U8_Counter, U32_TimerValue);

        if(RdcSt__U8_MainTimer == U8_Counter)
        {
          RdcSt__U32_ElapsedTimeInMs += RdcSt__U32_WakeupInterval_xms;
        }
        else
        {

        }

        ClientIf_GetECUTimeStampValue(&U32_CurrentTimestamp);
        AU32_MonitoringTimeForEachWs_xms[U8_Counter] = (AU32_MonitoringTimeForEachWs_xms[U8_Counter] + RdcSt__U32_WakeupInterval_xms) + (U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Counter]);
        AU32_LastReceptionTimestampForEachWs_xms[U8_Counter] = AU32_MonitoringTimeForEachWs_xms[U8_Counter];
      }
      else
      {

      }
    }
  }
  else
  {

    RdcSt_SavePressuresAndTemperaturesInRRAM(PU8_TelegramData);
  }
}

extern void RdcSt_MainFunction(void)
{
  static boolean RdcSt__BO_SleepRequested = FALSE;

  if(FALSE != RdcSt_IsStandstillMonitoringActive())
  {
    RdcSt__UpdateMonitoringStatus();

    if(FALSE != RdcSt__BO_HasSyncPeriodExpired)
    {
      if(RdcSt__U8_MainTimer == RDC__NUMBER_OF_WS)
      {

        RdcSt_StopStandstillMonitoring();
        RdcSt__SaveStatusInNvm();
        RdcSt__SaveDataInNvm();
		
		    #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent(cSSMDEBUG_EVENT_SHUTDOWN_NO_SENSORS); //0xEF = final shutdown
        #endif
        SYSMGR_SetEcuEvent(cECUEVENT_SHUTDOWN);   //SYSMGR_SetEcuEvent(cECUEVENT_DEEPSTOP); //RST Debug -> to test the deepstop mode
      }
      else if((RdcSt__U8_MonitoringStatus == RDCST__MONITORING_STATUS_CLEAR) && (FALSE == RdcSt__BO_SleepRequested) && (FALSE == RdcSt__AreTimersExpiringSoon()))
      {
        RdcSt__UpdateWakeupTimer();
        SYSMGR_SetEcuEvent(cECUEVENT_DEEPSTOP);
        RdcSt__BO_SleepRequested = TRUE;

        #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent(cSSMDEBUG_EVENT_DEEPSTOP);
        #endif

      }
    }
    else
    {

      RdcSt__UpdateSyncPeriod();
    }
  }
  else
  {

  }
}

extern void RdcSt_ForwardStandstillDataToTms(void)
{
  uint8 U8_Counter;
  tsWS_RxDataIn S_RxData;
  tsEnv_Data* PS_EnvData = Env_GetEnvironmentData();

  if (RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_PressureOnKeyEnabled == TRUE)
  {

    ClientIf_GetECUTimeStampValue(&S_RxData.ulRxTimeStamp);

    S_RxData.uiRxRSSI = RDCST__DEFAULT_RSSI_FOR_STANDSTILL_TELEGRAMS;

    if(RdcSt__DataExistsInNvm() == TRUE)
    {
      //RdcSt__ReadAndSortIDs();
      RdcSt_ReadAndSortIDs();
      RdcSt__LoadDataFromNvm();
      #ifdef DEBUG_PRESSURE_ON_KEY
      SSMDEBUG_SetEvent_in_QuietMode(cSSMDEBUG_EVENT_NVM_CONTAINS_DATA, 0xFF, 0xFFFFFFFF);
      #endif
    }
    else
    {
      RdcSt__SaveStatusInNvm();
    }

    for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
    {
      if(RdcSt__AS_WSData[U8_Counter].U8_Pressure != RDCST__PRESSURE_INVALID_VALUE)
      {
        S_RxData.ucaTelegram[0] = RDCRB_SYNC_BYTES_MSB;
        S_RxData.ucaTelegram[1] = RDCRB_SYNC_BYTES_LSB;
        S_RxData.ucaTelegram[2] = RDCST__PACKAGE_ID_STANDSTILL;
        S_RxData.ucaTelegram[3] = ((uint8) (RdcSt__AS_WSData[U8_Counter].U32_WsId >> 24U));
        S_RxData.ucaTelegram[4] = ((uint8) (RdcSt__AS_WSData[U8_Counter].U32_WsId >> 16U));
        S_RxData.ucaTelegram[5] = ((uint8) (RdcSt__AS_WSData[U8_Counter].U32_WsId >> 8U));
        S_RxData.ucaTelegram[6] = ((uint8) (RdcSt__AS_WSData[U8_Counter].U32_WsId & 0xFFU));
        S_RxData.ucaTelegram[7] = RdcSt__AS_WSData[U8_Counter].U8_Pressure;
        S_RxData.ucaTelegram[8] = RdcSt__AS_WSData[U8_Counter].U8_Temperature;
        S_RxData.ucaTelegram[9] = 0x00U;

        HufIf_RCtSaReTelDec(&S_RxData, PS_EnvData);

        #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent_in_QuietMode(cSSMDEBUG_EVENT_TG_FORWARD, RDCST__PACKAGE_ID_STANDSTILL, RdcSt__AS_WSData[U8_Counter].U32_WsId);
        #endif
      }
      else
      {

        #ifdef DEBUG_PRESSURE_ON_KEY
        SSMDEBUG_SetEvent_in_QuietMode(cSSMDEBUG_EVENT_NO_RRAM_DATA, RDCST__PACKAGE_ID_STANDSTILL, RdcSt__AS_WSData[U8_Counter].U32_WsId);
        #endif
      }

    }
  }

  ucRepeatForwardSSMTelegramToLib--;
}

extern void RdcSt_StartMonitoringSpecificWS(uint8 U8_WsNumber)
{
  uint8 U8_MaskForSpecificWS = ((uint8) 1U) << U8_WsNumber;

  RdcSt__U8_MonitoringStatus |= U8_MaskForSpecificWS;

  ClientIf_GetECUTimeStampValue(&RdcSt__AU32_StartOfWakeupPeriod[U8_WsNumber]);

  if((RdcSt__U8_ExtendedWakeup & U8_MaskForSpecificWS) == U8_MaskForSpecificWS)
  {
    Tau_StopTimer((Tau_Enum_Channels) U8_WsNumber);
  }

  #ifdef DEBUG_PRESSURE_ON_KEY
  SSMDEBUG_SetEvent(SSMDEBUG_CAU8_WakeByTau[U8_WsNumber]);
  #endif
}

extern void RdcSt_ReadPressureOnKeyConfig(uint8 *PU8_Data)
{
  NvmMGR_ReadBSWMember(NVM_E_PRESSURE_ON_KEY_ENABLED, &PU8_Data[0]);
  NvmMGR_ReadBSWMember(NVM_E_WAKEUP_INTERVAL, &PU8_Data[1]);
  NvmMGR_ReadBSWMember(NVM_E_WAKE_TIME, &PU8_Data[2]);
  NvmMGR_ReadBSWMember(NVM_E_WAKE_OFFSET, &PU8_Data[3]);
  NvmMGR_ReadBSWMember(NVM_E_POKDB, &PU8_Data[4]);
}

extern void RdcSt_WritePressureOnKeyConfig(const uint8 *PU8_Data)
{
  NvmMGR_WriteBSWMember(NVM_E_PRESSURE_ON_KEY_ENABLED, &PU8_Data[0]);
  NvmMGR_WriteBSWMember(NVM_E_WAKEUP_INTERVAL, &PU8_Data[1]);
  NvmMGR_WriteBSWMember(NVM_E_WAKE_TIME, &PU8_Data[2]);
  NvmMGR_WriteBSWMember(NVM_E_WAKE_OFFSET, &PU8_Data[3]);
  NvmMGR_WriteBSWMember(NVM_E_POKDB, &PU8_Data[4]);
  Memstack_WriteBswNvmBlockOnEvent();

  RdcSt__UpdateConfig();

  RdcSt__U32_WakeupInterval_xms = RDCST__WAKEUP_TIMER_MINS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin) * RDCST__WAKEUP_TIMER_INITIAL_MULTIPLIER;
  RdcSt__U32_WakeTime_xms = RDCST__WAKEUP_TIMER_100MS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeTime_x100ms);
  RdcSt__U32_WakeOffset_xms = RDCST__WAKEUP_TIMER_100MS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeOffset_x100ms);
}

extern void RdcSt_ReadPressureOnKeyStatus(uint8 *PU8_Data)
{
  NvmMGR_ReadBSWMember(NVM_E_FL_RECEIVED_TG, &PU8_Data[0]);
  NvmMGR_ReadBSWMember(NVM_E_FR_RECEIVED_TG, &PU8_Data[2]);
  NvmMGR_ReadBSWMember(NVM_E_RL_RECEIVED_TG, &PU8_Data[4]);
  NvmMGR_ReadBSWMember(NVM_E_RR_RECEIVED_TG, &PU8_Data[6]);
  NvmMGR_ReadBSWMember(NVM_E_LAST_RECEPTION_TIME, &PU8_Data[8]);
  NvmMGR_ReadBSWMember(NVM_E_MONITORING_TIME, &PU8_Data[28]);
}

#ifdef DEBUG_PRESSURE_ON_KEY

extern void RdcSt_LoadDebugData(tStandstillDebugMsg *PS_Data)
{
  uint8 U8_Pos;
  uint32 U32_CurrentTimestamp;
  ClientIf_GetECUTimeStampValue(&U32_CurrentTimestamp);

  if(RdcSt__AS_WSData[RDCST_WS_FL].U16_ReceivedCounter < 0xFFU)
  {
    PS_Data->ucRecCntFL = RdcSt__AS_WSData[RDCST_WS_FL].U16_ReceivedCounter;
  }
  else
  {
    PS_Data->ucRecCntFL = 0xFFU;
  }

  if(RdcSt__AS_WSData[RDCST_WS_FR].U16_ReceivedCounter < 0xFFU)
  {
    PS_Data->ucRecCntFR = RdcSt__AS_WSData[RDCST_WS_FR].U16_ReceivedCounter;
  }
  else
  {
    PS_Data->ucRecCntFR = 0xFFU;
  }

  if(RdcSt__AS_WSData[RDCST_WS_RL].U16_ReceivedCounter < 0xFFU)
  {
    PS_Data->ucRecCntRL = RdcSt__AS_WSData[RDCST_WS_RL].U16_ReceivedCounter;
  }
  else
  {
    PS_Data->ucRecCntRL = 0xFFU;
  }

  if(RdcSt__AS_WSData[RDCST_WS_RR].U16_ReceivedCounter < 0xFFU)
  {
    PS_Data->ucRecCntRR = RdcSt__AS_WSData[RDCST_WS_RR].U16_ReceivedCounter;
  }
  else
  {
    PS_Data->ucRecCntRR = 0xFFU;
  }

  U8_Pos = (PS_Data->ucEventType & 0x0F);
  if(U8_Pos < RDC__NUMBER_OF_WS)
  {
    uint32 U32_WindowTime = U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Pos];
    PS_Data->ucWindowTime[0] = (U32_WindowTime >> 16) & 0xFFU;
    PS_Data->ucWindowTime[1] = (U32_WindowTime >> 8) & 0xFFU;
    PS_Data->ucWindowTime[2] = U32_WindowTime & 0xFFU;
  }
}

extern void RdcSt_LoadDebugData_NextWakeupTimer(tStandstillDebugMsg *PS_Data)
{
  typedef struct
  {
    uint32 ulTimerValue;
    uint8 ucNumber;
  } tTimer;

  tTimer tTimerValues[4];
  uint8 i;

  for (i=0; i<4; i++)
  {
    Tau_GetTimer((Tau_Enum_Channels)i, &tTimerValues[i].ulTimerValue);
    tTimerValues[i].ucNumber = i;
  }

  for (i=3; i>0; i--)
  {
    if (tTimerValues[i].ulTimerValue < tTimerValues[i-1].ulTimerValue)
    {
      tTimerValues[i-1].ulTimerValue = tTimerValues[i].ulTimerValue;
      tTimerValues[i-1].ucNumber = tTimerValues[i].ucNumber;
    }
  }

  PS_Data->ucRecCntFL = (tTimerValues[0].ulTimerValue >> 24) & 0xff;
  PS_Data->ucRecCntFR = (tTimerValues[0].ulTimerValue >> 16) & 0xff;
  PS_Data->ucRecCntRL = (tTimerValues[0].ulTimerValue >> 8 ) & 0xff;
  PS_Data->ucRecCntRR = (tTimerValues[0].ulTimerValue >> 0 ) & 0xff;

  PS_Data->ucEventType |= tTimerValues[0].ucNumber & 0x0f;

}

extern boolean RdcSt_IsDebugMessagingActive(void)
{
  return RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_POKDb;
}

#endif

static void RdcSt__UpdateSyncPeriod(void)
{
  uint32 U32_CurrentTimestamp;

  ClientIf_GetECUTimeStampValue(&U32_CurrentTimestamp);

  if((U32_CurrentTimestamp - RdcSt__U32_StartOfStandstillTimestamp) >= RDCST__SYNC_PERIOD_DURATION_MS)
  {

    RdcSt__BO_HasSyncPeriodExpired = TRUE;
  }
  else
  {

  }
}

static void RdcSt__UpdateMonitoringStatus(void)
{
  uint32 U32_CurrentTimestamp;
  uint8 U8_Counter;

  ClientIf_GetECUTimeStampValue(&U32_CurrentTimestamp);

  for(U8_Counter = 0; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {

    uint8 U8_MaskForSpecificWS = ((uint8) 1U) << U8_Counter;
    if((RdcSt__U8_MonitoringStatus & U8_MaskForSpecificWS) == U8_MaskForSpecificWS)
    {
      if (U32_CurrentTimestamp > RdcSt__AU32_StartOfWakeupPeriod[U8_Counter])
      {

        if((RdcSt__U8_ExtendedWakeup & U8_MaskForSpecificWS) == U8_MaskForSpecificWS)
        {

          if((U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Counter]) > RDCST__EXTENDED_WAKEUP_INTERVAL_MS)
          {

            RdcSt__U8_MonitoringStatus &= (~U8_MaskForSpecificWS);
            RdcSt__U8_ExtendedWakeup &= (~U8_MaskForSpecificWS);

            #ifdef DEBUG_PRESSURE_ON_KEY
            SSMDEBUG_SetEvent(SSMDEBUG_CAU8_WindowExpired[U8_Counter]);
            #endif

            if(RdcSt__U8_MainTimer == U8_Counter)
            {
              RdcSt__U32_ElapsedTimeInMs += RDCST__EXTENDED_WAKEUP_INTERVAL_MS;
            }
            else
            {

            }

            AU32_MonitoringTimeForEachWs_xms[U8_Counter] = (AU32_MonitoringTimeForEachWs_xms[U8_Counter] + RDCST__EXTENDED_WAKEUP_INTERVAL_MS) + (U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Counter]);
          }
          else
          {

          }
        }
        else
        {

          if((U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Counter]) > RdcSt__U32_WakeTime_xms)
          {
            uint32 U32_TimerValue = RdcSt__U32_WakeupInterval_xms - RdcSt__U32_WakeTime_xms;

            RdcSt__U8_MonitoringStatus &= (~U8_MaskForSpecificWS);
            RdcSt__U8_ExtendedWakeup |= U8_MaskForSpecificWS;
            Tau_StartTimer((Tau_Enum_Channels) U8_Counter, U32_TimerValue);

            #ifdef DEBUG_PRESSURE_ON_KEY
            SSMDEBUG_SetEvent(SSMDEBUG_CAU8_WindowExpired[U8_Counter]);
            #endif

            if(RdcSt__U8_MainTimer == U8_Counter)
            {
              RdcSt__U32_ElapsedTimeInMs += RdcSt__U32_WakeupInterval_xms;
            }
            else
            {

            }

            AU32_MonitoringTimeForEachWs_xms[U8_Counter] = (AU32_MonitoringTimeForEachWs_xms[U8_Counter] + RdcSt__U32_WakeupInterval_xms) + (U32_CurrentTimestamp - RdcSt__AU32_StartOfWakeupPeriod[U8_Counter]);
          }
          else
          {

          }
        }
      }
      else
      {

      }
    }
    else
    {

    }
  }
}

static void RdcSt__UpdateWakeupTimer(void)
{
  if(RdcSt__U32_ElapsedTimeInMs < RDCST__ELAPSED_TIME_1_DAY_MS)
  {

    RdcSt__U32_WakeupInterval_xms = RDCST__WAKEUP_TIMER_MINS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin) * RDCST__WAKEUP_TIMER_INITIAL_MULTIPLIER;
  }
  else if(RdcSt__U32_ElapsedTimeInMs < RDCST__ELAPSED_TIME_6_DAYS_MS)
  {

    RdcSt__U32_WakeupInterval_xms = RDCST__WAKEUP_TIMER_MINS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin) * RDCST__WAKEUP_TIMER_AFTER_1_DAY_MULTIPLIER;
  }
  else if(RdcSt__U32_ElapsedTimeInMs < RDCST__ELAPSED_TIME_22_DAYS_MS)
  {

    RdcSt__U32_WakeupInterval_xms = RDCST__WAKEUP_TIMER_MINS_TO_MS(RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin) * RDCST__WAKEUP_TIMER_AFTER_5_DAYS_MULTIPLIER;
  }
  else
  {

    RdcSt_StopStandstillMonitoring();
    RdcSt__SaveStatusInNvm();
    RdcSt__SaveDataInNvm();
    SYSMGR_SetEcuEvent(cECUEVENT_SHUTDOWN);   // SYSMGR_PrepareShutdown(10U); RST 26.10.2019 - do this via event and mode switch in Sys Manager
  }
}

static boolean RdcSt__AreTimersExpiringSoon(void)
{
  uint8 U8_Counter;
  boolean BO_AreTimersExpiringSoon = FALSE;

  for(U8_Counter = 0; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    uint32 U32_TimerValue;

    Tau_GetTimer((Tau_Enum_Channels) U8_Counter, &U32_TimerValue);

    if(U32_TimerValue < RDCST__TIMER_CLOSE_TO_EXPIRING_THRESHOLD_MS)
    {
      BO_AreTimersExpiringSoon = TRUE;
    }
  }

  return BO_AreTimersExpiringSoon;
}

static void RdcSt__SaveDataInNvm(void)
{
  uint8 U8_DataExistence = RDCST__DATA_EXISTENCE_TRUE;

  NvmMGR_WriteBSWMember(NVM_E_FL_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_FL].U8_Pressure);
  NvmMGR_WriteBSWMember(NVM_E_FL_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_FL].U8_Temperature);

  NvmMGR_WriteBSWMember(NVM_E_FR_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_FR].U8_Pressure);
  NvmMGR_WriteBSWMember(NVM_E_FR_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_FR].U8_Temperature);

  NvmMGR_WriteBSWMember(NVM_E_RL_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_RL].U8_Pressure);
  NvmMGR_WriteBSWMember(NVM_E_RL_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_RL].U8_Temperature);

  NvmMGR_WriteBSWMember(NVM_E_RR_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_RR].U8_Pressure);
  NvmMGR_WriteBSWMember(NVM_E_RR_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_RR].U8_Temperature);

  NvmMGR_WriteBSWMember(NVM_E_DATA_EXISTENCE, &U8_DataExistence);
}

static void RdcSt__LoadDataFromNvm(void)
{
  uint8 U8_DataExistence = RDCST__DATA_EXISTENCE_FALSE;

  NvmMGR_ReadBSWMember(NVM_E_FL_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_FL].U8_Pressure);
  NvmMGR_ReadBSWMember(NVM_E_FL_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_FL].U8_Temperature);

  NvmMGR_ReadBSWMember(NVM_E_FR_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_FR].U8_Pressure);
  NvmMGR_ReadBSWMember(NVM_E_FR_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_FR].U8_Temperature);

  NvmMGR_ReadBSWMember(NVM_E_RL_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_RL].U8_Pressure);
  NvmMGR_ReadBSWMember(NVM_E_RL_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_RL].U8_Temperature);

  NvmMGR_ReadBSWMember(NVM_E_RR_PRESSURE, &RdcSt__AS_WSData[RDCST_WS_RR].U8_Pressure);
  NvmMGR_ReadBSWMember(NVM_E_RR_TEMPERATURE, &RdcSt__AS_WSData[RDCST_WS_RR].U8_Temperature);

  NvmMGR_WriteBSWMember(NVM_E_DATA_EXISTENCE, &U8_DataExistence);
}

static void RdcSt__UpdateConfig(void)
{
  NvmMGR_ReadBSWMember(NVM_E_PRESSURE_ON_KEY_ENABLED, &RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_PressureOnKeyEnabled);
  NvmMGR_ReadBSWMember(NVM_E_WAKEUP_INTERVAL, &RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeupInterval_xmin);
  NvmMGR_ReadBSWMember(NVM_E_WAKE_TIME, &RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeTime_x100ms);
  NvmMGR_ReadBSWMember(NVM_E_WAKE_OFFSET, &RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_WakeOffset_x100ms);
  NvmMGR_ReadBSWMember(NVM_E_POKDB, &RdcSt__UN_PressureOnKeyConfig.Struct_PressureOnKeyConfig.U8_POKDb);
}

static boolean RdcSt__DataExistsInNvm(void)
{
  boolean BO_DataExists = FALSE;
  uint8 U8_DataExistence;

  NvmMGR_ReadBSWMember(NVM_E_DATA_EXISTENCE, &U8_DataExistence);

  if(U8_DataExistence == RDCST__DATA_EXISTENCE_TRUE)
  {
    BO_DataExists = TRUE;
  }

  return BO_DataExists;
}

static void Rdc__ConvertLatestReceptionToEpochTime(uint8 *PU8_TimeAndDateString)
{
  uint8 U8_Counter;
  uint32 U32_LatestReceptionTimestamp_xms = 0U;
  uint64 U64_EpochTime;
  uint64 sec;
  uint16 quadricentennials, centennials, quadrennials, annuals;
  uint16 year, leap;
  uint16 yday, hour, min;
  uint16 month, mday;
  static const uint16 daysSinceJan1st[2][13]=
  {
    {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
    {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
  };

  for(U8_Counter = 0; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    if(AU32_LastReceptionTimestampForEachWs_xms[U8_Counter] > U32_LatestReceptionTimestamp_xms)
    {
      U32_LatestReceptionTimestamp_xms = AU32_LastReceptionTimestampForEachWs_xms[U8_Counter];
    }
  }

  U64_EpochTime = RdcSt__U64_CGMTimestampAtStart + U32_LatestReceptionTimestamp_xms;
  U64_EpochTime = U64_EpochTime / 1000U; //transform from ms to s

  // Re-bias from 1970 to 1601:
  // 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
  // (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
  sec = U64_EpochTime + 11644473600LL;

  // Remove multiples of 400 years (incl. 97 leap days)
  quadricentennials = (uint16)(sec / 12622780800ULL); // 400*365.2425*24*3600
  sec %= 12622780800ULL;

  // Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
  // (because multiples of 4*100=400 years (incl. leap days) have been removed)
  centennials = (uint16)(sec / 3155673600ULL); // 100*(365+24/100)*24*3600
  if (centennials > 3)
  {
    centennials = 3;
  }
  sec -= centennials * 3155673600ULL;

  // Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
  // (because multiples of 25*4=100 years (incl. leap days) have been removed)
  quadrennials = (uint16)(sec / 126230400); // 4*(365+1/4)*24*3600
  if (quadrennials > 24)
  {
    quadrennials = 24;
  }
  sec -= quadrennials * 126230400ULL;

  // Remove multiples of years (incl. 0 leap days), can't be more than 3
  // (because multiples of 4 years (incl. leap days) have been removed)
  annuals = (uint16)(sec / 31536000); // 365*24*3600
  if (annuals > 3)
  {
    annuals = 3;
  }
  sec -= annuals * 31536000ULL;

  // Calculate the year and find out if it's leap
  year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
  leap = !(year % 4) && (year % 100 || !(year % 400));

  // Calculate the day of the year and the time
  yday = sec / 86400;
  sec %= 86400;
  hour = sec / 3600;
  sec %= 3600;
  min = sec / 60;
  sec %= 60;

  // Calculate the month
  for (mday = month = 1; month < 13; month++)
  {
    if (yday < daysSinceJan1st[leap][month])
    {
      mday += yday - daysSinceJan1st[leap][month - 1];
      break;
    }
  }

  PU8_TimeAndDateString[0] = VERSION_ucDigitToAscii(year/1000U);
  PU8_TimeAndDateString[1] = VERSION_ucDigitToAscii((year/100U)%10U);
  PU8_TimeAndDateString[2] = VERSION_ucDigitToAscii((year/10U)%10U);
  PU8_TimeAndDateString[3] = VERSION_ucDigitToAscii(year%10U);
  PU8_TimeAndDateString[4] = '.';
  PU8_TimeAndDateString[5] = VERSION_ucDigitToAscii(month/10U);
  PU8_TimeAndDateString[6] = VERSION_ucDigitToAscii(month%10U);
  PU8_TimeAndDateString[7] = '.';
  PU8_TimeAndDateString[8] = VERSION_ucDigitToAscii(mday/10U);
  PU8_TimeAndDateString[9] = VERSION_ucDigitToAscii(mday%10U);
  PU8_TimeAndDateString[10] = ' ';
  PU8_TimeAndDateString[11] = VERSION_ucDigitToAscii(hour/10U);
  PU8_TimeAndDateString[12] = VERSION_ucDigitToAscii(hour%10U);
  PU8_TimeAndDateString[13] = ':';
  PU8_TimeAndDateString[14] = VERSION_ucDigitToAscii(min/10U);
  PU8_TimeAndDateString[15] = VERSION_ucDigitToAscii(min%10U);
  PU8_TimeAndDateString[16] = ':';
  PU8_TimeAndDateString[17] = VERSION_ucDigitToAscii(sec/10U);
  PU8_TimeAndDateString[18] = VERSION_ucDigitToAscii(sec%10U);
  PU8_TimeAndDateString[19] = '\0';
}

static void RdcSt__SaveStatusInNvm(void)
{
  uint8 AU8_TimeAndDateString[20];
  uint8 AU8_TemporaryBuffer[4];

  AU8_TemporaryBuffer[0] = (RdcSt__AS_WSData[RDCST_WS_FL].U16_ReceivedCounter >> 8) & 0xFFU;
  AU8_TemporaryBuffer[1] = RdcSt__AS_WSData[RDCST_WS_FL].U16_ReceivedCounter & 0xFFU;
  NvmMGR_WriteBSWMember(NVM_E_FL_RECEIVED_TG, &AU8_TemporaryBuffer[0]);

  AU8_TemporaryBuffer[0] = (RdcSt__AS_WSData[RDCST_WS_FR].U16_ReceivedCounter >> 8) & 0xFFU;
  AU8_TemporaryBuffer[1] = RdcSt__AS_WSData[RDCST_WS_FR].U16_ReceivedCounter & 0xFFU;
  NvmMGR_WriteBSWMember(NVM_E_FR_RECEIVED_TG, &AU8_TemporaryBuffer[0]);

  AU8_TemporaryBuffer[0] = (RdcSt__AS_WSData[RDCST_WS_RL].U16_ReceivedCounter >> 8) & 0xFFU;
  AU8_TemporaryBuffer[1] = RdcSt__AS_WSData[RDCST_WS_RL].U16_ReceivedCounter & 0xFFU;
  NvmMGR_WriteBSWMember(NVM_E_RL_RECEIVED_TG, &AU8_TemporaryBuffer[0]);

  AU8_TemporaryBuffer[0] = (RdcSt__AS_WSData[RDCST_WS_RR].U16_ReceivedCounter >> 8) & 0xFFU;
  AU8_TemporaryBuffer[1] = RdcSt__AS_WSData[RDCST_WS_RR].U16_ReceivedCounter & 0xFFU;
  NvmMGR_WriteBSWMember(NVM_E_RR_RECEIVED_TG, &AU8_TemporaryBuffer[0]);

  Rdc__ConvertLatestReceptionToEpochTime(&AU8_TimeAndDateString[0]);
  NvmMGR_WriteBSWMember(NVM_E_LAST_RECEPTION_TIME, &AU8_TimeAndDateString[0]);

  AU8_TemporaryBuffer[0] = (RdcSt__U32_ElapsedTimeInMs >> 24) & 0xFFU;
  AU8_TemporaryBuffer[1] = (RdcSt__U32_ElapsedTimeInMs >> 16) & 0xFFU;
  AU8_TemporaryBuffer[2] = (RdcSt__U32_ElapsedTimeInMs >> 8) & 0xFFU;
  AU8_TemporaryBuffer[3] = RdcSt__U32_ElapsedTimeInMs & 0xFFU;
  NvmMGR_WriteBSWMember(NVM_E_MONITORING_TIME, &AU8_TemporaryBuffer[0]);
}

//static void RdcSt__ReadAndSortIDs(void)
void RdcSt_ReadAndSortIDs(void)
{
  //uint8 U8_Counter;
  //NVM_BLOCK_TYPE U32_IDs[RDC__NUMBER_OF_WS];
  //uint8 U8_Positions[RDC__NUMBER_OF_WS];
  //
  //(void) ClientIf_NvM_ReadBlock(RDC__GLOBAL_NVM_INDEX, RDC__NUMBER_OF_WS, &U32_IDs[0]);
  //(void) ClientIf_NvM_ReadBlock(RDCST__GLOBAL_INDEX_WS_POS, 1U, (NVM_BLOCK_TYPE*) &U8_Positions[0]);

  //for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  //{
  //  if(U8_Positions[U8_Counter] < RDC__NUMBER_OF_WS)
  //  {
  //
  //    RdcSt__AS_WSData[U8_Positions[U8_Counter]].U32_WsId = U32_IDs[U8_Counter];
  //  }
  //}

  uint8 U8_Counter;
  NVM_BLOCK_TYPE U32_IDs[RDC__NUMBER_OF_WS];
  uint8 U8_Positions[RDC__NUMBER_OF_WS];
  uint32 ulLastIDs[4];
  boolean bIdConfigurationChanged = FALSE;

  for (U8_Counter = 0; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    ulLastIDs[U8_Counter] = RdcSt__AS_WSData[U8_Counter].U32_WsId;
  }

  (void) ClientIf_NvM_ReadBlock(RDC__GLOBAL_NVM_INDEX, RDC__NUMBER_OF_WS, &U32_IDs[0]);
  (void) ClientIf_NvM_ReadBlock(RDCST__GLOBAL_INDEX_WS_POS, 1U, (NVM_BLOCK_TYPE*) &U8_Positions[0]);

  for(U8_Counter = 0U; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    if(U8_Positions[U8_Counter] < RDC__NUMBER_OF_WS)
    {

      RdcSt__AS_WSData[U8_Positions[U8_Counter]].U32_WsId = U32_IDs[U8_Counter];
    }
  }

  for (U8_Counter = 0; U8_Counter < RDC__NUMBER_OF_WS; U8_Counter++)
  {
    if (RdcSt__AS_WSData[U8_Counter].U32_WsId != ulLastIDs[U8_Counter])
    {
      bIdConfigurationChanged = TRUE;
    }
  }

  if (bIdConfigurationChanged == TRUE)
  {
    RdcSt_ClearRramData();
  }
}
