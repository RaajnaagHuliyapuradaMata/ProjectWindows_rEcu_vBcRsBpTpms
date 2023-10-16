#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "SwcApplTpms_CAN_If.hpp"
#include "SwcApplTpms_DTC_If.hpp"
#include "StateManagerX.hpp"
#include "WAllocX.hpp"
#include "ProcDatX.hpp"
#include "BusMsgX.hpp"
#include "CalibrX.hpp"
#include "UsWarnX.hpp"
#include "SilaX.hpp"
#include "State_FzzX.hpp"
#include "state_bzx.hpp"
#include "abs_linX.hpp"
#include "SwcApplTpms_abs_lin.hpp"
#include "IDOM_X.hpp"
#include "SwcApplTpms_DevCanMessages.hpp"
#include "DevCanHandling.hpp"
#include "SwcApplTpms_LearnEOL.hpp"

#define TIME_TO_ALLOW_SAME_TGms           400U
#define ABS_SIMULATED_TIMESTAMP_INVALID   ((uint16) 0xFFFFU)
#define ABS_AGE_INVALID                   ((uint8) 0xFFU)
#define SIMULATED_TELEGRAM_SYNC_PATTERN   ((uint16) 0x0000U)

typedef struct{
  uint8 u8_TelType;
  uint8 u8_ID[4];
}IdentAndID;

typedef struct{
  IdentAndID U8_RFTelegFilter;
  uint32 u32_TimestampFirstFrame;
}RFTelegramFilter;

static RFTelegramFilter OneRFTelegramInformation[8];
static uint8            U8_PositionCnt;
static uint32           U32_SimulatedTimestamp;

Type_SwcApplTpms_stStatusBody g_sEnv_Data;

static void  Init_Sys_After_Kl15_Off        (void);
static void  Init_Std_Modules_After_Kl30_On (void);
static void  InitSameTGBuffer               (void);
static void  ProcessSimulatedTelegram       (Type_SwcApplTpms_stTelegramWS* spRxDataIn);

static uint8 u8CheckSameTG(
      const uint8* u8CurrentRFFrame
   ,        uint32 u32_TimeStamp
);
#pragma PRQA_NO_SIDE_EFFECTS u8CheckSameTG

void HufIf_Init_Huf_SWC(void){
   InitEEAll();
   Init_Huf_Common();
   Init_CAN_Data();
   DCM_InitCanDebug();
   DCH_Init();
   Init_Std_Modules_After_Kl30_On();
}

void HufIf_RCtSaReTelDec(
            Type_SwcApplTpms_stTelegramWS* spRxDataIn
   ,  const Type_SwcApplTpms_stStatusBody*    spEnvDataIn
){
   boolean l_bAnalizeAllRF = FALSE;
   uint16  l_uiSyncPattern;
   uint8   l_ucTelType;
   uint32  l_ulRxTimeStamp;
   uint32  ulId =
         (spRxDataIn->ucaTelegram[3] << 24)
      +  (spRxDataIn->ucaTelegram[4] << 16)
      +  (spRxDataIn->ucaTelegram[5] <<  8)
      +   spRxDataIn->ucaTelegram[6]
   ;

   HufIf_RCtSaEnvData(spEnvDataIn);
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      IncrementAllReceivedTelegCnt();
      l_uiSyncPattern = (((uint16)spRxDataIn->ucaTelegram[0]) << 8) | (spRxDataIn->ucaTelegram[1]);
      if(SIMULATED_TELEGRAM_SYNC_PATTERN != l_uiSyncPattern){
      }
      else{
         ProcessSimulatedTelegram(spRxDataIn);
      }
      l_ucTelType     = spRxDataIn->ucaTelegram[2];
      l_ulRxTimeStamp = spRxDataIn->ulRxTimeStamp;
      l_bAnalizeAllRF = DCH_IsDeveloperModeActive();
      if(
            (TRUE == l_bAnalizeAllRF)
         || (0    == u8CheckSameTG((uint8*)&spRxDataIn->ucaTelegram[2], l_ulRxTimeStamp))
      ){
         if(
               (
                     (TRUE == LearningWheelPosActiveSM())
                  || (TRUE == DCH_IsContinousAPCReadingActive())
               )
            && (l_ucTelType == cTelTypeRotatS)
         ){
            if(
                  (cRX_TIME_STAMP_INVALID != l_ulRxTimeStamp)
               && (0                      != l_ulRxTimeStamp)
            ){
               PutRotatSDataInBuffer(spRxDataIn);
            }
            else{
            }
         }
         else{
            if(
                  (TRUE == bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT))
               && (l_ucTelType == cTelTypeStandstill)
            ){
            }
            else{
               ReadReDataFromRingBuffer_iBTCM(spRxDataIn);
            }
         }
      }
      else{
      }
   }
   else{
   }
}

void HufIf_RCtSaEnvData(
   const Type_SwcApplTpms_stStatusBody* spRxEnvDataIn
){
   static uint16  sl_uiOldVehSpeed     = 0xFFFFU;
   static uint8   sl_ucOldKLstate      = VEH_IGN_OFF;
   static uint8   sl_ucOldVehDirection = cDriveDirStop;
   static boolean sl_bOldBCMFault      = FALSE;
          uint8   l_ucNewVehDirection  = 0U;
          uint16  l_uiNewVehSpeed      = 0U;
          uint8   l_ucNewKLstate       = 0U;
          boolean l_bNewBCMFault       = 0U;
   g_sEnv_Data = *spRxEnvDataIn;
   (void)VehStateGetKL15(&l_ucNewKLstate);
   if(
         sl_ucOldKLstate
      != l_ucNewKLstate
   ){
      if(
            Off
         == l_ucNewKLstate
      ){
         EvTerminal15OffFZZ();
         Init_Sys_After_Kl15_Off();
         sl_uiOldVehSpeed     = 0xFFFFU;
         sl_ucOldVehDirection = cDriveDirStop;
         sl_bOldBCMFault      = FALSE;
      }
      else if(ON == l_ucNewKLstate){
      DTC_RestoreActiveStatusfromEE();
      EvTerminal15OnFZZ();
      InitSameTGBuffer();
      DTC_StatusOfDTC |= cDTC_WAS_DELETED_TROUGH_DIAG;
      U32_SimulatedTimestamp = 0U;
      }
      else{
      }
      sl_ucOldKLstate = l_ucNewKLstate;
   }
   else{
   }
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      l_bNewBCMFault = g_sEnv_Data.bECU_Fault;
      if(
            sl_bOldBCMFault
         != l_bNewBCMFault
      ){
         EvBCMFaultStatusChanged(l_bNewBCMFault);
         sl_bOldBCMFault = l_bNewBCMFault;
      }
      else{
      }
      (void)ReceiveGetVehicleSpeed(&l_uiNewVehSpeed);
      if(sl_uiOldVehSpeed != l_uiNewVehSpeed){
         VehStateTriggerHysteresis(VEHSTATE_VEHICLE_SPEED_HYST_ID, l_uiNewVehSpeed);
         VehStateTriggerHysteresis(VEHSTATE_REDIAG_ACTIVE_HYST_ID, l_uiNewVehSpeed);
         EvVehicleSpeedChangedBZ(l_uiNewVehSpeed);
         sl_uiOldVehSpeed = l_uiNewVehSpeed;
      }
      else{
      }
      (void)ReceiveGetDirection(&l_ucNewVehDirection);
      if(sl_ucOldVehDirection != l_ucNewVehDirection){
         if(cDriveDirBackward == l_ucNewVehDirection){EvDriveDirectionBackwardFZZ();}
         else                                        {EvDriveDirectionForwardFZZ();}
         sl_ucOldVehDirection = l_ucNewVehDirection;
      }
      else{
      }
      if(CU16_NVM_ALL_CATEG_CONSISTENT != g_sEnv_Data.uiNvmBlockConsistence){
         EE_InconsistencyHandling(g_sEnv_Data.uiNvmBlockConsistence);
      }
      else{
      }
   }
   else{
   }
}

void HufIf_RCtAbsEnvData(
   const Type_SwcApplTpms_stWheelPulseStamped* spRxEnvAbsDataIn
){
   uint32 u32TempAbsTimeStamp;
   uint16 u16TempAbsSig[4];
   uint8  ucReceiveValid = TRUE;
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      ucReceiveValid &= ((spRxEnvAbsDataIn->uiPulseCtrFL <= 0xFE) ? TRUE : FALSE);
      ucReceiveValid &= ((spRxEnvAbsDataIn->uiPulseCtrFR <= 0xFE) ? TRUE : FALSE);
      ucReceiveValid &= ((spRxEnvAbsDataIn->uiPulseCtrRL <= 0xFE) ? TRUE : FALSE);
      ucReceiveValid &= ((spRxEnvAbsDataIn->uiPulseCtrRR <= 0xFE) ? TRUE : FALSE);
      if(TRUE == ucReceiveValid){
         u16TempAbsSig[0] = spRxEnvAbsDataIn->uiPulseCtrFL;
         u16TempAbsSig[1] = spRxEnvAbsDataIn->uiPulseCtrFR;
         u16TempAbsSig[2] = spRxEnvAbsDataIn->uiPulseCtrRL;
         u16TempAbsSig[3] = spRxEnvAbsDataIn->uiPulseCtrRR;
         if(ABS_SIMULATED_TIMESTAMP_INVALID == spRxEnvAbsDataIn->uiSimTimeStamp){
            u32TempAbsTimeStamp = spRxEnvAbsDataIn->ulAbsTimeStamp;
         }
         else{
            U32_SimulatedTimestamp += (uint32) spRxEnvAbsDataIn->uiSimTimeStamp;
            u32TempAbsTimeStamp     = U32_SimulatedTimestamp;
         }
         if(ABS_AGE_INVALID != spRxEnvAbsDataIn->ucAge){
            if(u32TempAbsTimeStamp <= (uint32) spRxEnvAbsDataIn->ucAge){
               u32TempAbsTimeStamp = 0U;
            }
            else{
               u32TempAbsTimeStamp -= (uint32) spRxEnvAbsDataIn->ucAge;
            }
         }
         else{
         }
         if(cRX_TIME_STAMP_INVALID != spRxEnvAbsDataIn->ulAbsTimeStamp){
            PutABS(u32TempAbsTimeStamp, u16TempAbsSig);
         }
      }
      else{
      }
   }
   else{
   }
}

void HufIf_RCtSaTpmsData(
   const Type_SwcApplTpms_stStatusBody* spEnvData
){
   uint8 ucLinStatus;
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      if(
            (TRUE == LearningWheelPosActiveSM())
         || (TRUE == DCH_IsContinousAPCReadingActive())
      ){
         while(
               (ucRotatSTelIndexGet != ucGetRotatSDataBufferIndex())
            && (ucRotatSTelIndexGet < cWsTelBufferSize)
         ){
            ucLinStatus = LinABS(
               pGetRotatSDataTFromBuffer(ucRotatSTelIndexGet)->RxDataIn.ulRxTimeStamp
            );
            if(cABS_OK == ucLinStatus){
               ReadReDataFromRingBuffer_iBTCM(
                  &(pGetRotatSDataTFromBuffer(ucRotatSTelIndexGet))->RxDataIn
               );
               ucRotatSTelIndexGet++;
               ucRotatSTelIndexGet %= cWsTelBufferSize;
            }
            else if(cABS_VALUE_TOO_OLD == ucLinStatus){
               break;
            }
            else{
               ucRotatSTelIndexGet++;
               ucRotatSTelIndexGet %= cWsTelBufferSize;
            }
         }
      }
   }
   else{
   }
   HufIf_RCtSaEnvData(spEnvData);
   if(TRUE == bGetBitFahrzeugzustandFZZ(cKL_15_EIN)){
      Huf_SWC_Basic_Timer();
   }
   else{
   }
   SwcApplTpms_vRunnableUpdateStatus();
}

static void Init_Sys_After_Kl15_Off(void){
  Init_Huf_Common();
  DCM_InitCanDebug();
  DCH_Init();
  InitPD();
  BusMsgInit();
  VehStateInit();
  InitABS();
  NvM2_PutDiagUsedToDeleteDTCEE(cDTC_WAS_DELETED_TROUGH_DIAG);
}

static void Init_Std_Modules_After_Kl30_On(void){
  InitSM();
  InitUSWAlgo(GETpucStartAdrWP());
  InitPD();
  EOL_InitLearnRoutine();
  BusMsgInit();
  VehStateInit();
  SilaInit();
  InitABS();
  InitIDOM();
  CalibrSetPressureCAL();
}

static void InitSameTGBuffer(void){
  uint8 ucArrayCnt,ucStructureCnt;
  for( ucArrayCnt = 0; ucArrayCnt< SIZE_ARRAY(OneRFTelegramInformation, RFTelegramFilter); ucArrayCnt++ ){
   for( ucStructureCnt = 0; ucStructureCnt < sizeof(IdentAndID); ucStructureCnt++ ){
      *((uint8*)&OneRFTelegramInformation[ucArrayCnt].U8_RFTelegFilter + ucStructureCnt ) = 0;
   }
    OneRFTelegramInformation[ucArrayCnt].u32_TimestampFirstFrame = 0;
  }
  U8_PositionCnt = 0;
}

static void ProcessSimulatedTelegram(
 Type_SwcApplTpms_stTelegramWS* spRxDataIn
){
   uint8  l_ucTelType;
   l_ucTelType = spRxDataIn->ucaTelegram[2];
   if(l_ucTelType == cTelTypeRotatS){
      uint16 U16_Timestamp = (((uint16)spRxDataIn->ucaTelegram[9]) << 8) | (spRxDataIn->ucaTelegram[10]);
      if(0xFFFFU != U16_Timestamp){
         U32_SimulatedTimestamp    += ((uint32) U16_Timestamp);
         spRxDataIn->ulRxTimeStamp  = U32_SimulatedTimestamp;
      }
   }
   else if(l_ucTelType == cTelTypeAK35def){
      g_sEnv_Data.uiNoiseRSSI = (uint16)spRxDataIn->ucaTelegram[9];
   }
   else{
   }
}

static uint8 u8CheckSameTG(
      const uint8* u8CurrentRFFrame
   ,        uint32 u32_TimeStamp
){
   uint8 Return,ucCntDataCell,ucArrayCnt;
   Return = 1;
   for(
      ucArrayCnt = 0;
      ucArrayCnt < SIZE_ARRAY(OneRFTelegramInformation, RFTelegramFilter);
      ucArrayCnt ++
   ){
      for(
         ucCntDataCell = 0;
         ucCntDataCell < sizeof(IdentAndID);
         ucCntDataCell ++
      ){
         if(
               u8CurrentRFFrame[ucCntDataCell]
            != *(
                     (uint8*)&OneRFTelegramInformation[ucArrayCnt].U8_RFTelegFilter
                  +  ucCntDataCell
               )
         ){
            break;
         }
         else{
            if(4 == ucCntDataCell){
               Return = 0;
            }
         }
      }
      if(0 == Return){
         break;
      }
   }
   if(1 == Return){
      if(
         U8_PositionCnt >= SIZE_ARRAY(OneRFTelegramInformation, RFTelegramFilter)
      ){
         U8_PositionCnt = 0;
      }
      for(
         ucCntDataCell = 0;
         ucCntDataCell < sizeof(IdentAndID);
         ucCntDataCell ++
      ){
         *((uint8*)&OneRFTelegramInformation[U8_PositionCnt].U8_RFTelegFilter + ucCntDataCell) = u8CurrentRFFrame[ucCntDataCell];
      }
      OneRFTelegramInformation[U8_PositionCnt].u32_TimestampFirstFrame = u32_TimeStamp;
      U8_PositionCnt++;
      Return = 0;
   }
   else{
      if(((u32_TimeStamp - OneRFTelegramInformation[ucArrayCnt].u32_TimestampFirstFrame) > TIME_TO_ALLOW_SAME_TGms)){
         OneRFTelegramInformation[ucArrayCnt].u32_TimestampFirstFrame = u32_TimeStamp;
      }
      else{
         Return = 1;
      }
   }
   return Return;
}

