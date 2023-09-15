
#include "types.hpp"
#include "Com.hpp"
#include "Com_Cbk.hpp"
#include "Com_PBcfg_InternalId.hpp"
#include "CanManager.hpp"
#include "iTpms_Interface.hpp"
#include "rba_BswSrv.hpp"
#include "DemManagerX.hpp"
#include "DemAppInterfaceX.hpp"
#include "AdcX.hpp"
#include "version.hpp"

#ifdef DEBUG_PRESSURE_ON_KEY
#include "RdcStandstillDebugX.hpp"
#include "SysManagerX.hpp"
#endif

static sHMI_LMC tLordstownHmiMessage;
static sSTATUS_LMC tLordstownStatusMessage;

static volatile uint64 ulMilliseconds = 0;

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_ApplicationCyclic(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  tsCAN_Message tTPM_ApplicationCyclicMessage;
  boolean BO_TransmitMessage;
  uint8 U8_Counter;
  uint8* PU8_ApplicationCyclicMessageData;

  BO_TransmitMessage = FALSE;
  PU8_ApplicationCyclicMessageData = ((uint8 *) &tTPM_ApplicationCyclicMessage);

  (void) HufIf_CanMsgTransmit(CAN_MSG_Debug_CYCLIC, &tTPM_ApplicationCyclicMessage);

  for(U8_Counter = 0; U8_Counter < sizeof(tTPM_ApplicationCyclicMessage); U8_Counter++)
  {

   if(PU8_ApplicationCyclicMessageData[U8_Counter] != 0x00U)
   {
      BO_TransmitMessage = TRUE;
   }
   else{

   }
  }

  if(FALSE != BO_TransmitMessage)
  {
    (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_ApplicationCyclicMessage, ptr->SduLength);
  }
  else{

    // RST Info: skipping of a cyclic message is not possible. If this feature is necessary, the message must be declared as "on event" in the .dbc
  }

  return BO_TransmitMessage;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_TirePT(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  CAN_HMI_type tPressureData;
  tsHMI_Temperature_RefPres tTemperatureData;

  uint8 ucLearnLocateStatus;

  (void)HufIf_CanMsgTransmit(CAN_MSG_HMI_CYCLIC, (tsCAN_Message*)&tPressureData);

  (void)HufIf_CanMsgTransmit(CAN_MSG_HMI_TEMP_CYCLIC, (tsCAN_Message*)&tTemperatureData);

  tLordstownHmiMessage.TPMS_TireP_FL = tPressureData.ucTP_FL;
  tLordstownHmiMessage.TPMS_TireP_FR = tPressureData.ucTP_FR;
  tLordstownHmiMessage.TPMS_TireP_RL = tPressureData.ucTP_RL;
  tLordstownHmiMessage.TPMS_TireP_RR = tPressureData.ucTP_RR;
  tLordstownHmiMessage.TPMS_TireT_FL = tTemperatureData.ucTT_FL - 10;
  tLordstownHmiMessage.TPMS_TireT_FR = tTemperatureData.ucTT_FR - 10;
  tLordstownHmiMessage.TPMS_TireT_RL = tTemperatureData.ucTT_RL - 10;
  tLordstownHmiMessage.TPMS_TireT_RR = tTemperatureData.ucTT_RR - 10;

  (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tLordstownHmiMessage, ptr->SduLength);

  Dem_SetCurrentTirePressures(tPressureData.ucTP_FL, tPressureData.ucTP_FR, tPressureData.ucTP_RL, tPressureData.ucTP_RR);
  ucLearnLocateStatus = ((uint8)tPressureData.bTPMS_Learn_Status << 1) + (uint8)tPressureData.bTPMS_Locate_Status;
  Dem_SetCurrentLearnLocateStatus(ucLearnLocateStatus);

  Dem_SetCurrentTireTemperatures(tTemperatureData.ucRP_FL, tTemperatureData.ucRP_FR, tTemperatureData.ucRP_RL, tTemperatureData.ucRP_RR);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_Status(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{

   CAN_HMI_type tPressureData;
   tsHMI_Temperature_RefPres tTemperatureData;

   (void)HufIf_CanMsgTransmit(CAN_MSG_HMI_CYCLIC, (tsCAN_Message*)&tPressureData);

   (void)HufIf_CanMsgTransmit(CAN_MSG_HMI_TEMP_CYCLIC, (tsCAN_Message*)&tTemperatureData);

   tLordstownStatusMessage.bTPMS_Status_FL = tPressureData.bTPS_FL;
   tLordstownStatusMessage.bTPMS_Status_FR = tPressureData.bTPS_FR;
   tLordstownStatusMessage.bTPMS_Status_RL = tPressureData.bTPS_RL;
   tLordstownStatusMessage.bTPMS_Status_RR = tPressureData.bTPS_RR;
   tLordstownStatusMessage.bTPMS_Val_FL = tPressureData.bTPV_FL;
   tLordstownStatusMessage.bTPMS_Val_FR = tPressureData.bTPV_FR;
   tLordstownStatusMessage.bTPMS_Val_RL = tPressureData.bTPV_RL;
   tLordstownStatusMessage.bTPMS_Val_RR = tPressureData.bTPV_RR;

   tLordstownStatusMessage.bTMPS_InflationMonitoring_Status = tPressureData.bTMP_S;

   tLordstownStatusMessage.bTPMS_TempWarning_FL = tPressureData.bTemp_Warning_FL;
   tLordstownStatusMessage.bTPMS_TempWarning_FR = tPressureData.bTemp_Warning_FR;
   tLordstownStatusMessage.bTPMS_TempWarning_RL = tPressureData.bTemp_Warning_RL;
   tLordstownStatusMessage.bTPMS_TempWarning_RR = tPressureData.bTemp_Warning_RR;

   tLordstownStatusMessage.bTPMS_Learn_Status = tPressureData.bTPMS_Learn_Status;
   tLordstownStatusMessage.bTPMS_Locate_Status = tPressureData.bTPMS_Locate_Status;

   tLordstownStatusMessage.ucTPMS_Tire_Ref_Press_FL = tTemperatureData.ucRP_FL;
   tLordstownStatusMessage.ucTPMS_Tire_Ref_Press_FR = tTemperatureData.ucRP_FR;
   tLordstownStatusMessage.ucTPMS_Tire_Ref_Press_RL = tTemperatureData.ucRP_RL;
   tLordstownStatusMessage.ucTPMS_Tire_Ref_Press_RR = tTemperatureData.ucRP_RR;

   (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tLordstownStatusMessage, ptr->SduLength);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_ApplicationResponse(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  tsCAN_Message tTPM_ApplicationResponseMessage;

#ifdef DEBUG_PRESSURE_ON_KEY
  tStandstillDebugMsg* dataBuffer;

  dataBuffer = SSMDEBUG_GetPointerToBuffer();
  if(dataBuffer->ucEventType != 0x00)
  {
  	// PC 05/2020: Had to comment these lines out, because debug messaging was not working in MONITOR mode.
//    if(SYSMGR_GetEcuMode() == cECUMODE_WAKE) //RST info: comment this line out to be able to send app response message in all modes
//    {                                                          //also check Com_IPdu_NotificationCallback_ApplicationResponse!

      rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)dataBuffer, ptr->SduLength);
//    }
  }
  else{
#endif

  (void) HufIf_CanMsgTransmit(CAN_MSG_DEBUG_RES, &tTPM_ApplicationResponseMessage);
  (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_ApplicationResponseMessage, ptr->SduLength);

#ifdef DEBUG_PRESSURE_ON_KEY
  }
#endif

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if 0

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void,COM_CODE) Com_IPdu_NotificationCallback_ApplicationResponse(void){
#ifdef DEBUG_PRESSURE_ON_KEY
  // PC 05/2020: Had to comment these lines out, because debug messaging was not working in MONITOR mode.
//  if(SYSMGR_GetEcuMode() == cECUMODE_WAKE) //RST info: comment this line out to be able to send app response message in all modes
//  {                                                    //also check Com_IPdu_Callout_ApplicationResponse_TPM!
    SSMDEBUG_StopTrigger();
//  }
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_TPMS_ApplicationRequest(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr) // UndCC_Line(MISRA12_8.2)
{
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ApplicationRequest_UpdateValues(&AU8_Buffer[0]);

  Com_TriggerIPDUSend(ComConf_ComIPdu_Internal_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_RdcData(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);
  CANMGR_RdcDataTPM_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_EPOCHTime(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //contains clock value from CGM ECU. Our local clock shall be synchronized to the CGM clock with this signal. ABS message timestamps are based on CGM clock.
  uint8 AU8_Buffer[8];
  sEpochTime_LMC sLmcTime;

  (void) rba_BswSrv_MemCopy((uint8*)&sLmcTime, ptr->SduDataPtr, ptr->SduLength);

  ulMilliseconds = (uint64)((uint64)sLmcTime.ucSeconds[5]  << 40);
  ulMilliseconds += (uint64)((uint64)sLmcTime.ucSeconds[4] << 32);
  ulMilliseconds += (uint64)((uint64)sLmcTime.ucSeconds[3] << 24);
  ulMilliseconds += (uint64)((uint64)sLmcTime.ucSeconds[2] << 16);
  ulMilliseconds += (uint64)((uint64)sLmcTime.ucSeconds[1] << 8 );
  ulMilliseconds += (uint64)sLmcTime.ucSeconds[0];
  ulMilliseconds *= 1000;
  ulMilliseconds += (uint64)(sLmcTime.bMillisec & 0x3ff);           //max. 1000

  AU8_Buffer[5] = ((ulMilliseconds & 0x3) << 6) + (sLmcTime.bValid << 5);
  AU8_Buffer[4] = (ulMilliseconds >> 2U) & 0xff;
  AU8_Buffer[3] = (ulMilliseconds >> 10U) & 0xff;
  AU8_Buffer[2] = (ulMilliseconds >> 18U) & 0xff;
  AU8_Buffer[1] = (ulMilliseconds >> 26U) & 0xff;
  AU8_Buffer[0] = (ulMilliseconds >> 34U) & 0xff;

  CANMGR_ClockSynchronization_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_VCU_WheelSpeed_Front(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //Contains wheel speeds in km/h -> the 4 wheel speeds shall be used to calculate vehicle speed
  //Contains wheel directions also
  uint8 AU8_Buffer[8];
  sWheelSpeed_RIVIAN sWSRivian;
  sWheelSpeed_LMC sWSLmc;

  (void) rba_BswSrv_MemCopy((uint8*)&sWSLmc, ptr->SduDataPtr, ptr->SduLength);

  sWSRivian.bChecksum = sWSLmc.bChecksum;
  sWSRivian.bMessageCounter = sWSLmc.bMessageCounter;

  switch(sWSLmc.bWheelDirL)
  {
   case 1: //LMC Forward
      sWSRivian.bWheelDirL = 0; //Rivian Forward
   break;

   case 2: //LMC Reverse
      sWSRivian.bWheelDirL = 1; //Rivian reverse
   break;

    default: //LMC invalid / unknown
      sWSRivian.bWheelDirL = 3; //Rivian unknown
   break;
  }

  switch(sWSLmc.bWheelDirR)
  {
  case 1: //LMC Forward
   sWSRivian.bWheelDirR = 0; //Rivian Forward
   break;

  case 2: //LMC Reverse
   sWSRivian.bWheelDirR = 1; //Rivian reverse
   break;

  default: //LMC invalid / unknown
   sWSRivian.bWheelDirR = 3; //Rivian unknown
   break;
  }

  sWSRivian.bWheelSpeedL = (sWSLmc.bWheelSpeedL >> 5) * 100;
  sWSRivian.bWheelSpeedR = (sWSLmc.bWheelSpeedR >> 5) * 100;

  sWSRivian.bWheelSpeedLValid = sWSLmc.bWheelSpeedLValid;
  sWSRivian.bWheelSpeedRValid = sWSLmc.bWheelSpeedRValid;

  AU8_Buffer[0] = sWSRivian.bChecksum;
  AU8_Buffer[1] = (sWSRivian.bWheelSpeedRValid << 6) | (sWSRivian.bWheelSpeedLValid << 4) | sWSRivian.bMessageCounter;
  AU8_Buffer[2] = (sWSRivian.bWheelSpeedL & 0xff00U) >> 8;
  AU8_Buffer[3] = sWSRivian.bWheelSpeedL & 0xff;
  AU8_Buffer[4] = (sWSRivian.bWheelSpeedR & 0xff00U) >> 8;
  AU8_Buffer[5] = sWSRivian.bWheelSpeedR & 0xff;
  AU8_Buffer[6] = ((sWSRivian.bWheelDirL << 6) | (sWSRivian.bWheelDirR << 4)) & 0xf0;
  AU8_Buffer[7] = 0x00;

  CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues(AU8_Buffer);
  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_VCU_WheelSpeed_Rear(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //Contains wheel speeds in km/h -> the 4 wheel speeds shall be used to calculate vehicle speed
  //Contains wheel directions also
  uint8 AU8_Buffer[8];
  sWheelSpeed_RIVIAN sWSRivian;
  sWheelSpeed_LMC sWSLmc;

  (void)rba_BswSrv_MemCopy((uint8*)&sWSLmc, ptr->SduDataPtr, ptr->SduLength);

  sWSRivian.bChecksum = sWSLmc.bChecksum;
  sWSRivian.bMessageCounter = sWSLmc.bMessageCounter;

  switch(sWSLmc.bWheelDirL)
  {
  case 1: //LMC Forward
   sWSRivian.bWheelDirL = 0; //Rivian Forward
   break;

  case 2: //LMC Reverse
   sWSRivian.bWheelDirL = 1; //Rivian reverse
   break;

  default: //LMC invalid / unknown
   sWSRivian.bWheelDirL = 3; //Rivian unknown
   break;
  }

  switch(sWSLmc.bWheelDirR)
  {
  case 1: //LMC Forward
   sWSRivian.bWheelDirR = 0; //Rivian Forward
   break;

  case 2: //LMC Reverse
   sWSRivian.bWheelDirR = 1; //Rivian reverse
   break;

  default: //LMC invalid / unknown
   sWSRivian.bWheelDirR = 3; //Rivian unknown
   break;
  }

  sWSRivian.bWheelSpeedL = (sWSLmc.bWheelSpeedL >> 5) * 100;
  sWSRivian.bWheelSpeedR = (sWSLmc.bWheelSpeedR >> 5) * 100;

  sWSRivian.bWheelSpeedLValid =  sWSLmc.bWheelSpeedLValid;
  sWSRivian.bWheelSpeedRValid =  sWSLmc.bWheelSpeedRValid;

  AU8_Buffer[0] = sWSRivian.bChecksum;
  AU8_Buffer[1] = (sWSRivian.bWheelSpeedRValid << 6) | (sWSRivian.bWheelSpeedLValid << 4) | sWSRivian.bMessageCounter;
  AU8_Buffer[2] = (sWSRivian.bWheelSpeedL & 0xff00U) >> 8;
  AU8_Buffer[3] = sWSRivian.bWheelSpeedL & 0xff;
  AU8_Buffer[4] = (sWSRivian.bWheelSpeedR & 0xff00U) >> 8;
  AU8_Buffer[5] = sWSRivian.bWheelSpeedR & 0xff;
  AU8_Buffer[6] = ((sWSRivian.bWheelDirL << 6) | (sWSRivian.bWheelDirR << 4)) & 0xf0;
  AU8_Buffer[7] = 0x00;

  CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues(AU8_Buffer);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_ESP_WheelPulses(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  // Contains wheel pulse counters, message counter, checksum. timestamp is missing for Lordstown.
  static uint8 aucTemp[8];

  (void)rba_BswSrv_MemCopy(aucTemp, ptr->SduDataPtr, ptr->SduLength);
  CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues((uint8*)&aucTemp);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_CGW_VCU_Ambient_Info(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  // Contains ambietn temperature.
  uint8 AU8_Buffer[8];

  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);
   CANMGR_TMM_Status_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_BCM_PowerMode(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //ignition state can be derived from this information.
  //PowerMode >=2 means "ignition on".  (OIL125)
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  AU8_Buffer[2] = AU8_Buffer[0] & 0x07;
  CANMGR_VehSts_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_IPdu_Callout_CGW_VCU_Powertrain_Info(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //gear signal: driving direction shall be derived from this
  //RST Info: drivin direction is derived from wheel directions. So nothing to do here.

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_IPdu_Callout_CGW_ODO(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //Ododmeter reading. Only used for did F104 read odo value. Makes no sense as so many customer requirements do...
  uint8 AU8_Buffer[8];
  uint32 ulMileage;

  (void)rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);
  ulMileage = (AU8_Buffer[3] << 24) + (AU8_Buffer[2] << 16) + (AU8_Buffer[1] << 8) + AU8_Buffer[0];
  Dem_SetCurrentMileage(ulMileage);
  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_IPdu_Callout_CGW_VehicleSpeed(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //RST Todo fill with life or skip it.
  //Nothing to do here, veh speed is derivd from wheel speeds
  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
