#include "CanManager.hpp"
#include "iTpms_Interface.hpp"
#include "types.hpp"
#include "Com.hpp"
#include "Dcm.hpp"
#include "Com_Cbk.hpp"
#include "Com_PBcfg_InternalId.hpp"
#include "ComM.hpp"
#include "EnvManagerX.hpp"
#include "RdcManagerX.hpp"
#include "TmsManagerX.hpp"
#include "SysManagerX.hpp"
#include "DemManagerX.hpp"
#include "GpioX.hpp"
#include "CanTrcv.hpp"
#include "version.hpp"

static Com_IpduGroupVector Vector_IPduGrpVctr;
static uint16              ushCanCommTimeout = 0;
static uint8               ucCommControl = DCM_ENABLE_RX_TX_NORM;

static void CANMGR_PduGroupInit(void){
   Com_ClearIpduGroupVector(Vector_IPduGrpVctr);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Rx,             TRUE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx,             FALSE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic,   FALSE);
   Com_SetIpduGroup(Vector_IPduGrpVctr, ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse, FALSE);
   Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
}

extern void CANMGR_Init(void){
   uint8 ucEcuMode;
   CANMGR_PduGroupInit();
   ucEcuMode = SYSMGR_GetEcuMode();
   if(ucEcuMode == cECUMODE_QUIET){
      CANMGR_SetFullCommunicationMode();
      CANMGR_StartCommTimeout();
      DemMGR_StartMonitoring();
   }
   else if(ucEcuMode == cECUMODE_WAKE){
#ifdef DEBUG_PRESSURE_ON_KEY
      CANMGR_SetFullCommunicationMode();
      TRCV_Normal();
#else
      CANMGR_SetNoCommunicationMode();
      TRCV_Standby();
#endif
      GPIO_TjaErrInterrupt(c_IRQ_ACTIVE);
   }
   else{
   }
}

extern void CANMGR_PduGroupStart(Com_IpduGroupIdType tGroupId){
   if(ucCommControl == DCM_ENABLE_RX_TX_NORM){
      Com_SetIpduGroup(Vector_IPduGrpVctr, tGroupId, TRUE);
      Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
   }
}

extern void CANMGR_PduGroupStop(Com_IpduGroupIdType tGroupId){
   Com_SetIpduGroup(Vector_IPduGrpVctr, tGroupId, FALSE);
   Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE);
}

extern void CANMGR_SetFullCommunicationMode(void){
   ComM_ModeType tCurrentComMode;
   (void) ComM_GetCurrentComMode(0, &tCurrentComMode);
   if(tCurrentComMode != COMM_FULL_COMMUNICATION){
      (void) ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
      ComM_CommunicationAllowed(0, TRUE);
   }
}

extern void CANMGR_SetNoCommunicationMode(void){
   ComM_ModeType tCurrentComMode;
   (void) ComM_GetCurrentComMode(0, &tCurrentComMode);
   if(tCurrentComMode != COMM_NO_COMMUNICATION){
      (void) ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
   }
}

extern void CANMGR_StartCommTimeout(void){
   ushCanCommTimeout = cCAN_COMM_TIMEOUT;
}

extern void CANMGR_StopCommTimeout(void){
   ushCanCommTimeout = 0;
}

extern void CANMGR_TickCommTimeout(void){
   if(ushCanCommTimeout > 0){
      ushCanCommTimeout--;
      if(ushCanCommTimeout == 0){
         SYSMGR_SetEcuEvent(cECUEVENT_COMM_TIMEOUT);
      }
   }
}

extern void CANMGR_ElongateCommTimeout(uint16 ushTime){
#ifdef IGNORE_PRESSURE_ON_KEY
   if(ushCanCommTimeout > 0){
      ushCanCommTimeout = ushTime;
   }
   else{
      ushCanCommTimeout = cCAN_EXTENDED_COMM_TIMOUT;
   }
#else
   (void)(ushTime);
   CANMGR_ResetCommTimeout();
#endif
}

static void CANMGR_ResetCommTimeout(void){
   if(ushCanCommTimeout > 0){
      CANMGR_StartCommTimeout();
   }
#ifndef IGNORE_PRESSURE_ON_KEY
   else if(SYSMGR_GetEcuMode() == cECUMODE_MONITOR){
      SYSMGR_SetEcuEvent(cECUEVENT_CAN_WAKE);
   }
#endif
   else{
   }
}

extern void CANMGR_CommControlStatus(uint8 ucControlType){
   ucCommControl = ucControlType;
}

extern void CANMGR_ControlCyclicApplicationPdu(void){
   static boolean bCycAppPduIsStarted = FALSE;
   if(Tms_IsCyclicMessageEnabled() == TRUE){
      if(SYSMGR_GetEcuMode() == cECUMODE_FULL){
         if(bCycAppPduIsStarted == FALSE){
            CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
            bCycAppPduIsStarted = TRUE;
         }
      }
   }
   else{
      if(bCycAppPduIsStarted == TRUE){
         CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
         bCycAppPduIsStarted = FALSE;
      }
   }
}

extern void CANMGR_ApplicationRequest_UpdateValues(uint8* PU8_DataPointer){
   tsCAN_Message tTPM_ApplicationRequest;
   tTPM_ApplicationRequest.ucData0 = PU8_DataPointer[0];
   tTPM_ApplicationRequest.ucData1 = PU8_DataPointer[1];
   tTPM_ApplicationRequest.ucData2 = PU8_DataPointer[2];
   tTPM_ApplicationRequest.ucData3 = PU8_DataPointer[3];
   tTPM_ApplicationRequest.ucData4 = PU8_DataPointer[4];
   tTPM_ApplicationRequest.ucData5 = PU8_DataPointer[5];
   tTPM_ApplicationRequest.ucData6 = PU8_DataPointer[6];
   tTPM_ApplicationRequest.ucData7 = PU8_DataPointer[7];
   (void) HufIf_CanMsgReceive(CAN_MSG_DEBUG_REQ, &tTPM_ApplicationRequest);
   CANMGR_ResetCommTimeout();
}

extern void CANMGR_RdcDataTPM_UpdateValues(uint8* PU8_DataPointer){
   Rdc_ForwardSimulatedRfDataToTms(PU8_DataPointer);
   CANMGR_ResetCommTimeout();
}

extern void CANMGR_ClockSynchronization_UpdateValues(uint8* PU8_DataPointer){
   boolean BO_ClockSignalValid = (PU8_DataPointer[5]>> 5U) & 0x01U;
   CANMGR_ResetCommTimeout();
}

extern void CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
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

extern void CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
   static uint8 U8_LastRearMessageCounter    = CANMGR__ESP_WSPEED_REAR_MESSAGE_COUNTER_INVALID;
          uint8 U8_CurrentRearMessageCounter = PU8_DataPointer[1] & 0x0FU;
   if(U8_CurrentRearMessageCounter != U8_LastRearMessageCounter){
      U8_LastRearMessageCounter = U8_CurrentRearMessageCounter;
      if(U8_CurrentRearMessageCounter != CANMGR__ESP_WSPEED_FRONT_MESSAGE_COUNTER_INVALID){
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

extern void CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues(uint8* PU8_DataPointer){
   static uint8         ucLastMessageCounter = CANMGR__ESP_WHEEL_PULSE_MESSAGE_COUNTER_INVALID;
          uint8         ucCurrentMessageCounter;
          tsEnvAbs_Data tTPM_WheelPulse_Structure;
          boolean       ucQualifierFL, ucQualifierFR, ucQualifierRL, ucQualifierRR;
          boolean       bMessageInvalid = FALSE;
   ucCurrentMessageCounter = (PU8_DataPointer[6] >> 4) & 0xf;
   if(ucCurrentMessageCounter != ucLastMessageCounter){
      ucLastMessageCounter = ucCurrentMessageCounter;
      if(ucCurrentMessageCounter != CANMGR__ESP_WHEEL_PULSE_MESSAGE_COUNTER_INVALID){
         ucQualifierFL = ((PU8_DataPointer[5] >> 6) & 0x3);
         ucQualifierFR = ((PU8_DataPointer[5] >> 4) & 0x3);
         ucQualifierRL = ((PU8_DataPointer[5] >> 2) & 0x3);
         ucQualifierRR = ((PU8_DataPointer[5] >> 0) & 0x3);
         ClientIf_GetECUTimeStampValue(&tTPM_WheelPulse_Structure.ulAbsTimeStamp);
         tTPM_WheelPulse_Structure.uiSimTimeStamp = 0xFFFFU;
         tTPM_WheelPulse_Structure.ucAge = 0xFFU;
         if(ucQualifierFL == CANMGR__WPULSE_QUALIFIER_OK){
            tTPM_WheelPulse_Structure.uiPulseCtrFL = ((PU8_DataPointer[1] & 0x3) << 8) + ((PU8_DataPointer[0] & 0xff) >> 0);
         }
         else{
            tTPM_WheelPulse_Structure.uiPulseCtrFL = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE;
            bMessageInvalid = TRUE;
         }
         if(ucQualifierFR == CANMGR__WPULSE_QUALIFIER_OK){
            tTPM_WheelPulse_Structure.uiPulseCtrFR = ((PU8_DataPointer[2] & 0xf) << 6) + ((PU8_DataPointer[1] & 0xfc) >> 2);
         }
         else{
            tTPM_WheelPulse_Structure.uiPulseCtrFR = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE;
            bMessageInvalid = TRUE;
         }
         if(ucQualifierRL == CANMGR__WPULSE_QUALIFIER_OK){
            tTPM_WheelPulse_Structure.uiPulseCtrRL = ((PU8_DataPointer[3] & 0x3f) << 4) + ((PU8_DataPointer[2] & 0xf0) >> 4);
         }
         else{
            tTPM_WheelPulse_Structure.uiPulseCtrRL = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE;
            bMessageInvalid = TRUE;
         }
         if(ucQualifierRR == CANMGR__WPULSE_QUALIFIER_OK){
            tTPM_WheelPulse_Structure.uiPulseCtrRR = ((PU8_DataPointer[4] & 0xff) << 2) + ((PU8_DataPointer[3] & 0xc0) >> 6);
         }
         else{
            tTPM_WheelPulse_Structure.uiPulseCtrRR = CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE;
            bMessageInvalid = TRUE;
         }
         HufIf_RCtAbsEnvData(&tTPM_WheelPulse_Structure);
         if(bMessageInvalid == FALSE){
            DemMGR_RxReceived(DEMMGR_E_ESP_WHEEL_PULSE_STAMPED_INDEX);
         }
      }
   }
   CANMGR_ResetCommTimeout();
}

extern void CANMGR_TMM_Status_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
   uint8 U8_AmbientTemperature;
   if(PU8_DataPointer[1] == CANMGR__TMM_STATUS_VALID){
      U8_AmbientTemperature = PU8_DataPointer[0] - 60;
      if(
            (U8_AmbientTemperature > 87)
         && (U8_AmbientTemperature < 196)
      ){
         U8_AmbientTemperature = 87;
      }
      else if(
            (U8_AmbientTemperature > 195)
         && (U8_AmbientTemperature < 216)
      ){
         U8_AmbientTemperature = 216;
      }
      else{
      }
      U8_AmbientTemperature += 40;
      U8_AmbientTemperature <<= 1;
      Env_SetAmbientTemperature(U8_AmbientTemperature);
      DemMGR_RxReceived(DEMMGR_E_TMM_STATUS_BODY_LCAN_INDEX);
   }
   else{
      U8_AmbientTemperature = CANMGR__TMM_STATUS_INVALID_SIGNAL_THRESHOLD;
   }
   CANMGR_ResetCommTimeout();
}

extern void CANMGR_VehSts_BodyLCAN_UpdateValues(uint8* PU8_DataPointer){
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

void ClientIf_Debug_CanMsgTransmit(uint16 uiCanMsgID,tsCAN_Message* spCAN_Message,uint8 ucReturnVal){
}

void ClientIf_Debug_CanMsgReceive(uint16 uiCanMsgID,const tsCAN_Message* spCAN_Message,uint8 ucReturnVal){
}
