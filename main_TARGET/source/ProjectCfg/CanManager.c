#include "Std_Types.hpp"

#include "Types_SwcServiceComM.hpp"
#include "Types_SwcServiceEcuM.hpp"

#include "CanManager.hpp"
#include "types.hpp"
#include "Com.hpp"
#include "Dcm.hpp"
#include "Com_Cbk.hpp"
#include "Com_PBcfg_InternalId.hpp"
#include "ComM.hpp"
#include "EnvManagerX.hpp"
#include "RdcManagerX.hpp"
#include "DemManagerX.hpp"
#include "GpioX.hpp"
#include "CanTrcv.hpp"

#include "iTpms_Interface.hpp"

       S_SignalMissingDTCCnt SDTCMissingSigCnt;
static Com_IpduGroupVector   Vector_IPduGrpVctr;
static uint16                ushCanCommTimeout = 0;
static uint8                 ucCommControl     = DCM_ENABLE_RX_TX_NORM;

static void CANMGR_PduGroupInit(void){
   Com_ClearIpduGroupVector(Vector_IPduGrpVctr);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Rx,             TRUE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx,             FALSE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic,   FALSE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse, FALSE);
   Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
}

void CANMGR_Init(void){
   Type_SwcServiceEcuM_eModesEcu ucEcuMode;
   CANMGR_PduGroupInit();
   ucEcuMode = infSwcApplEcuM_eGetModeEcu();
   if(
         SwcServiceEcuM_eModeEcu_Quiet
      == ucEcuMode
   ){
      CANMGR_SetFullCommunicationMode();
      CANMGR_StartCommTimeout();
   }
   else if(
         SwcServiceEcuM_eModeEcu_Wake
      == ucEcuMode
   ){
      CANMGR_SetNoCommunicationMode();
      TRCV_Standby();
      GPIO_TjaErrInterrupt(c_IRQ_ACTIVE);
   }
   else{
   }
}

void CANMGR_PduGroupStart(Com_IpduGroupIdType tGroupId){
   if(ucCommControl == DCM_ENABLE_RX_TX_NORM){
      Com_SetIpduGroup(Vector_IPduGrpVctr, tGroupId, TRUE);
      Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
   }
}

void CANMGR_PduGroupStop(Com_IpduGroupIdType tGroupId){
   Com_SetIpduGroup(Vector_IPduGrpVctr, tGroupId, FALSE);
   Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
}

void CANMGR_SetFullCommunicationMode(void){
   Type_SwcServiceComM_tMode tCurrentComMode;
   (void) ComM_GetCurrentComMode(0, &tCurrentComMode);
   if(tCurrentComMode != COMM_FULL_COMMUNICATION){
      (void) ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
      ComM_CommunicationAllowed(0, TRUE);
   }
}

void CANMGR_SetNoCommunicationMode(void){
   Type_SwcServiceComM_tMode tCurrentComMode;
   (void) ComM_GetCurrentComMode(0, &tCurrentComMode);
   if(tCurrentComMode != COMM_NO_COMMUNICATION){
      (void) ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
   }
}

void CANMGR_StartCommTimeout(void){
   ushCanCommTimeout = cCAN_COMM_TIMEOUT;
}

void CANMGR_StopCommTimeout(void){
   ushCanCommTimeout = 0;
}

void CANMGR_TickCommTimeout(void){
   if(ushCanCommTimeout > 0){
      ushCanCommTimeout--;
      if(ushCanCommTimeout == 0){
         infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_TimeoutComm);
      }
   }
}

void CANMGR_ElongateCommTimeout(uint16 ushTime){
   (void)(ushTime);
   CANMGR_ResetCommTimeout();
}

static void CANMGR_ResetCommTimeout(void){
   if(ushCanCommTimeout > 0){
      CANMGR_StartCommTimeout();
   }
   else if(infSwcApplEcuM_eGetModeEcu() == SwcServiceEcuM_eModeEcu_Monitor){
      infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_WakeUpByCan);
   }
   else{
   }
}

void CANMGR_CommControlStatus(uint8 ucControlType){
   ucCommControl = ucControlType;
}

void CANMGR_ControlCyclicApplicationPdu(void){
   static boolean bCycAppPduIsStarted = FALSE;
   if(
         TRUE
      == infSwcApplTpmsSwcServiceComM_bIsEnabledMessageCyclic()
   ){
      if(
            SwcServiceEcuM_eModeEcu_Full
         == infSwcApplEcuM_eGetModeEcu()
      ){
         if(
               FALSE
            == bCycAppPduIsStarted
         ){
            CANMGR_PduGroupStart(
               ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic
            );
            bCycAppPduIsStarted = TRUE;
         }
      }
   }
   else{
      if(
            TRUE
         == bCycAppPduIsStarted
      ){
         CANMGR_PduGroupStop(
            ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic
         );
         bCycAppPduIsStarted = FALSE;
      }
   }
}

void CANMGR_ApplicationRequest_UpdateValues(uint8* PU8_DataPointer){
   Type_SwcApplTpms_stMessageCan lstMessageCan;
   lstMessageCan.lptru8Data0 = PU8_DataPointer[0];
   lstMessageCan.lptru8Data1 = PU8_DataPointer[1];
   lstMessageCan.lptru8Data2 = PU8_DataPointer[2];
   lstMessageCan.lptru8Data3 = PU8_DataPointer[3];
   lstMessageCan.lptru8Data4 = PU8_DataPointer[4];
   lstMessageCan.lptru8Data5 = PU8_DataPointer[5];
   lstMessageCan.lptru8Data6 = PU8_DataPointer[6];
   lstMessageCan.lptru8Data7 = PU8_DataPointer[7];
   (void) infSwcApplTpmsSwcServiceCom_tCalloutRxMessage(
         CAN_MSG_DEBUG_REQ
      ,  &lstMessageCan
   );
   CANMGR_ResetCommTimeout();
}

void CANMGR_RdcDataTPM_UpdateValues(uint8* PU8_DataPointer){
   Rdc_ForwardSimulatedRfDataToTms(PU8_DataPointer);
   CANMGR_ResetCommTimeout();
}

void CANMGR_ClockSynchronization_UpdateValues(uint8* PU8_DataPointer){
   boolean BO_ClockSignalValid = (PU8_DataPointer[5]>> 5U) & 0x01U;
   if(FALSE != BO_ClockSignalValid){
      uint64 U64_ClockValue = (
            (((uint64) PU8_DataPointer[0]) << 34U)
         |  (((uint64) PU8_DataPointer[1]) << 26U) 
         |  (((uint64) PU8_DataPointer[2]) << 18U) 
         |  (((uint64) PU8_DataPointer[3]) << 10U) 
         |  (((uint64) PU8_DataPointer[4]) << 2U) 
         |  (((uint64) PU8_DataPointer[5]) >> 6U)
      );
      Rdc_SynchronizeToCGMTimestamp(U64_ClockValue);
      DemMGR_RxReceived(DEMMGR_E_BCM_PERIPHERAL_MASTER_CLOCK_INDEX);
   }
   else{
   }
   CANMGR_ResetCommTimeout();
}

void CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
   static uint8 U8_LastFrontMessageCounter    = CANMGR__ESP_WSPEED_FRONT_MESSAGE_COUNTER_INVALID;
          uint8 U8_CurrentFrontMessageCounter = PU8_DataPointer[1] & 0x0FU;
   if(U8_CurrentFrontMessageCounter != U8_LastFrontMessageCounter){
      U8_LastFrontMessageCounter = U8_CurrentFrontMessageCounter;
      if(U8_CurrentFrontMessageCounter != CANMGR__ESP_WSPEED_FRONT_MESSAGE_COUNTER_INVALID){
         uint8 U8_FrontLeftWheelQualifier  = (PU8_DataPointer[1] >> 4) & 0x03U;
         uint8 U8_FrontRightWheelQualifier = (PU8_DataPointer[1] >> 6) & 0x03U;
         uint16 U16_FrontLeftWheelSpeed    = (((uint16) PU8_DataPointer[2]) << 8) | ((uint16) PU8_DataPointer[3]);
         uint16 U16_FrontRightWheelSpeed   = (((uint16) PU8_DataPointer[4]) << 8) | ((uint16) PU8_DataPointer[5]);
         if(CANMGR__WSPEED_QUALIFIER_BIT_NORMAL == U8_FrontLeftWheelQualifier){
            uint8 U8_FrontLeftWheelDirection = (PU8_DataPointer[6] >> 6U) & 0x03U;
            Env_SetWheelInfo(ENV_E_FRONT_LEFT_WHEEL_INDEX, U16_FrontLeftWheelSpeed, (Env_Enum_VehicleDirection) U8_FrontLeftWheelDirection);
         }
         if(CANMGR__WSPEED_QUALIFIER_BIT_NORMAL == U8_FrontRightWheelQualifier){
            uint8 U8_FrontRightWheelDirection = (PU8_DataPointer[6] >> 4U) & 0x03U;
            Env_SetWheelInfo(ENV_E_FRONT_RIGHT_WHEEL_INDEX, U16_FrontRightWheelSpeed, (Env_Enum_VehicleDirection) U8_FrontRightWheelDirection);
         }
         if(
               (CANMGR__WSPEED_QUALIFIER_BIT_FAULT >= U8_FrontRightWheelQualifier)
            && (CANMGR__WSPEED_QUALIFIER_BIT_FAULT >= U8_FrontLeftWheelQualifier)
         ){
            DemMGR_RxReceived(DEMMGR_E_ESP_WSPEED_FRONT_BODY_LCAN_INDEX1);
         }
         if(
               (CANMGR__WSPEED_SPEED_INVALID != U16_FrontLeftWheelSpeed)
            && (CANMGR__WSPEED_SPEED_INVALID != U16_FrontRightWheelSpeed)
         ){
            DemMGR_RxReceived(DEMMGR_E_ESP_WSPEED_FRONT_BODY_LCAN_INDEX2);
         }
      }
   }
   CANMGR_ResetCommTimeout();
}

void CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
   static uint8 u8CounterMessageRearLast    = CANMGR__ESP_WSPEED_REAR_MESSAGE_COUNTER_INVALID;
          uint8 u8CounterMessageRearCurrent = PU8_DataPointer[1] & 0x0FU;
   if(u8CounterMessageRearCurrent != u8CounterMessageRearLast){
      u8CounterMessageRearLast = u8CounterMessageRearCurrent;
      if(u8CounterMessageRearCurrent != CANMGR__ESP_WSPEED_FRONT_MESSAGE_COUNTER_INVALID){
         uint8  U8_RearLeftWheelQualifier = (PU8_DataPointer[1] >> 4) & 0x03U;
         uint8  U8_RearRightWheelQualifier = (PU8_DataPointer[1] >> 6) & 0x03U;
         uint16 U16_RearLeftWheelSpeed = (((uint16) PU8_DataPointer[2]) << 8) | ((uint16) PU8_DataPointer[3]);
         uint16 U16_RearRightWheelSpeed = (((uint16) PU8_DataPointer[4]) << 8) | ((uint16) PU8_DataPointer[5]);
         if(CANMGR__WSPEED_QUALIFIER_BIT_NORMAL == U8_RearLeftWheelQualifier){
            uint8 U8_RearLeftWheelDirection = (PU8_DataPointer[6] >> 6U) & 0x03U;
            Env_SetWheelInfo(ENV_E_REAR_LEFT_WHEEL_INDEX, U16_RearLeftWheelSpeed, (Env_Enum_VehicleDirection) U8_RearLeftWheelDirection);
         }
         if(CANMGR__WSPEED_QUALIFIER_BIT_NORMAL == U8_RearRightWheelQualifier){
            uint8 U8_RearRightWheelDirection = (PU8_DataPointer[6] >> 4U) & 0x03U;
            Env_SetWheelInfo(ENV_E_REAR_RIGHT_WHEEL_INDEX, U16_RearRightWheelSpeed, (Env_Enum_VehicleDirection) U8_RearRightWheelDirection);
         }
         if(
               (CANMGR__WSPEED_QUALIFIER_BIT_FAULT >= U8_RearRightWheelQualifier)
            && (CANMGR__WSPEED_QUALIFIER_BIT_FAULT >= U8_RearLeftWheelQualifier)
         ){
            DemMGR_RxReceived(DEMMGR_E_ESP_WSPEED_REAR_BODY_LCAN_INDEX1);
         }
         if(
               (CANMGR__WSPEED_SPEED_INVALID != U16_RearLeftWheelSpeed)
            && (CANMGR__WSPEED_SPEED_INVALID != U16_RearRightWheelSpeed)
         ){
            DemMGR_RxReceived(DEMMGR_E_ESP_WSPEED_REAR_BODY_LCAN_INDEX2);
         }
      }
   }
   CANMGR_ResetCommTimeout();
}

void CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues(uint8* PU8_DataPointer){
   static uint8 u8CounterMessageRearLast    = CANMGR__ESP_WHEEL_PULSE_MESSAGE_COUNTER_INVALID;
          uint8 u8CounterMessageRearCurrent = PU8_DataPointer[1] & 0x0FU;
   if(u8CounterMessageRearLast != u8CounterMessageRearCurrent){
      u8CounterMessageRearLast = u8CounterMessageRearCurrent;
      if(CANMGR__ESP_WHEEL_PULSE_MESSAGE_COUNTER_INVALID != u8CounterMessageRearCurrent){
         boolean BO_FrontLeftPulseQualifier  = (PU8_DataPointer[1] >> 7) & 0x01U;
         boolean BO_FrontRightPulseQualifier = (PU8_DataPointer[1] >> 5) & 0x01U;
         boolean BO_RearLeftPulseQualifier   = (PU8_DataPointer[1] >> 6) & 0x01U;
         boolean BO_RearRightPulseQualifier  = (PU8_DataPointer[1] >> 4) & 0x01U;
         boolean bMessageInvalid             = FALSE;
         Type_SwcApplTpms_stWheelPulseStamped tTPM_WheelPulse_Structure;
         uint16 U16_WheelPulseTimestamp;
         U16_WheelPulseTimestamp = (((uint16) PU8_DataPointer[6]) << 8) | ((uint16) PU8_DataPointer[7]);
         tTPM_WheelPulse_Structure.ulAbsTimeStamp = Rdc_ConvertWheelPulseTimestamp(U16_WheelPulseTimestamp);
         tTPM_WheelPulse_Structure.uiSimTimeStamp = 0xFFFFU;
         tTPM_WheelPulse_Structure.ucAge = 0xFFU;
         if(FALSE != BO_FrontLeftPulseQualifier)  {tTPM_WheelPulse_Structure.uiPulseCtrFL = PU8_DataPointer[2];} else{tTPM_WheelPulse_Structure.uiPulseCtrFL = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE; bMessageInvalid = TRUE;}
         if(FALSE != BO_FrontRightPulseQualifier) {tTPM_WheelPulse_Structure.uiPulseCtrFR = PU8_DataPointer[4];} else{tTPM_WheelPulse_Structure.uiPulseCtrFR = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE; bMessageInvalid = TRUE;}
         if(FALSE != BO_RearLeftPulseQualifier)   {tTPM_WheelPulse_Structure.uiPulseCtrRL = PU8_DataPointer[3];} else{tTPM_WheelPulse_Structure.uiPulseCtrRL = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE; bMessageInvalid = TRUE;}
         if(FALSE != BO_RearRightPulseQualifier)  {tTPM_WheelPulse_Structure.uiPulseCtrRR = PU8_DataPointer[5];} else{tTPM_WheelPulse_Structure.uiPulseCtrRR = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE; bMessageInvalid = TRUE;}
         HufIf_RCtAbsEnvData(&tTPM_WheelPulse_Structure);
         if(FALSE == bMessageInvalid){
            DemMGR_RxReceived(DEMMGR_E_ESP_WHEEL_PULSE_STAMPED_INDEX);
         }
      }
   }
   CANMGR_ResetCommTimeout();
}

void CANMGR_TMM_Status_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
   uint8 U8_AmbientTemperature = PU8_DataPointer[0];
   if(CANMGR__TMM_STATUS_INVALID_SIGNAL_THRESHOLD >= U8_AmbientTemperature){
      Env_SetAmbientTemperature(U8_AmbientTemperature);
      DemMGR_RxReceived(DEMMGR_E_TMM_STATUS_BODY_LCAN_INDEX);
   }
   CANMGR_ResetCommTimeout();
}

void CANMGR_VehSts_BodyLCAN_UpdateValues(
   uint8* PU8_DataPointer
){
   uint8                  U8_VehicleStatus = PU8_DataPointer[2] & 0x0F;
   Env_Enum_IgnitionState EN_IgnitionState;
   if(U8_VehicleStatus > CANMGR__IGNITION_ON_TRESHOLD){
      EN_IgnitionState = ENV_E_IGNITION_ON;
   }
   else{
      EN_IgnitionState = ENV_E_IGNITION_OFF;
   }
   if(U8_VehicleStatus != CANMGR__VEH_STS_INVALID_SIGNAL){
      DemMGR_RxReceived(DEMMGR_E_VEH_STS_BODY_LCAN_INDEX);
   }
   Env_SetIgnitionStateFromBus(EN_IgnitionState);
   Env_SetVehicleMode(U8_VehicleStatus);
   CANMGR_ResetCommTimeout();
}

void CANMGR_VmsStsReq_BodyLCAN_UpdateValues(
   uint8* PU8_DataPointer
){
   static uint8 u8CounterMessageRearLast    = CANMGR__VMS_STS_REQ_MESSAGE_COUNTER_INVALID;
          uint8 u8CounterMessageRearCurrent = PU8_DataPointer[1] & 0x0FU;
   if(u8CounterMessageRearLast != u8CounterMessageRearCurrent){
      u8CounterMessageRearLast = u8CounterMessageRearCurrent;
      if(u8CounterMessageRearCurrent != CANMGR__VMS_STS_REQ_MESSAGE_COUNTER_INVALID){
         boolean BO_RoadMode;
         BO_RoadMode = (PU8_DataPointer[3] >> 3U) & 0x01U;
         Env_SetRoadMode(BO_RoadMode);
         DemMGR_RxReceived(DEMMGR_E_VMS_STS_REQ_BODY_LCAN_INDEX);
      }
   }
   CANMGR_ResetCommTimeout();
}

