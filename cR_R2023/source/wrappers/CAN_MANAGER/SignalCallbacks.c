
#include "types.h"
#include "Com.h"
#include "Com_Cbk.h"
#include "Com_PBcfg_InternalId.h"
#include "CanManagerX.h"
#include "iTpms_Interface.h"
#include "rba_BswSrv.h"
#include "DemManagerX.h"
#include "DemAppInterfaceX.h"
#include "AdcX.h"
#include "version.h"

//RST Debug: for debugging only
//#include "EnvManagerX.h"

#ifdef DEBUG_PRESSURE_ON_KEY
#include "RdcStandstillDebugX.h"
#include "SysManagerX.h"
#endif

extern void Debug_GetTgRxIrqCounter(uint8* ucIrqCnt, uint32* ulTsDiff); //RST Debug Rx
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationCyclic_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
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
    else
    {

    }
  }

  if(FALSE != BO_TransmitMessage)
  {
    (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_ApplicationCyclicMessage, ptr->SduLength);
  }
  else
  {

    // RST Info: skipping of a cyclic message is not possible. If this feature is necessary, the message must be declared as "on event" in the .dbc
  }

  return BO_TransmitMessage;

  //RST Debug Rx
  //uint8 ucBuf[8];
  //uint32 ulTsdiff;
  //Debug_GetTgRxIrqCounter(&ucBuf[0], &ulTsdiff);               //interrupts, milliseconds between 2 interrupts
  //ucBuf[4] = (uint8)((ulTsdiff>>24) & 0xff);
  //ucBuf[3] = (uint8)((ulTsdiff>>16) & 0xff);
  //ucBuf[2] = (uint8)((ulTsdiff>>8) & 0xff);
  //ucBuf[1] = (uint8)(ulTsdiff & 0xff);
  //ucBuf[5]=ucBuf[6]=ucBuf[7]= 0xff;         //RST Debug Rx
  //rba_BswSrv_MemCopy(ptr->SduDataPtr, ucBuf, ptr->SduLength);
  //return TRUE;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

//RST Debug Rx
//extern void Debug_GetAtaRecCounters(uint8* Ct1_Systemfehler, uint8* Ct2_TgLen, uint8* Ct3_Crc);
//extern uint8 Debug_GetTGCtCorrectSid(void);

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMIPressure_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  tsCAN_Message tTPM_HMIPressureMessage;

  (void) HufIf_CanMsgTransmit(CAN_MSG_HMI_CYCLIC, &tTPM_HMIPressureMessage);
  (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_HMIPressureMessage, ptr->SduLength);

  //RST Debug: fill this message with some error counters
  //uint8 ucBuf[8];
  //Debug_GetAtaRecCounters(&ucBuf[1], &ucBuf[2], &ucBuf[3]);      //Systemfehler, TG Länge im buffer, CRC
  //ucBuf[4] = Debug_GetTGCtCorrectSid();               //Supplier ID ok
  //ucBuf[0]=ucBuf[5]=ucBuf[6]=ucBuf[7]= 0xff;         //
  //rba_BswSrv_MemCopy(ptr->SduDataPtr, ucBuf, ptr->SduLength);

  //RST Debug: fill this message with some interesting data
  //uint8 ucTemp;

  //Dem_GetData_EcuMode_RoadMode_LLStatus(&ucTemp);
  //ucBuf[0] = (ucTemp & 0xE0) >> 5;  //ECu mode
  //ucBuf[1] = (ucTemp & 0x10) >> 4;  //Road mode
  //ucBuf[2] = (ucTemp & 0x08) >> 3;  //Ignition state Lib
  //ucBuf[3] = (ucTemp & 0x04) >> 2;  //Coast Mode on/off
  //ucBuf[4] = (ucTemp & 0x02) >> 1;  //Learn status
  //ucBuf[5] = (ucTemp & 0x01) >> 0;  //Locate status
  //ucBuf[6] = (uint8)enGetIgnitionStateFromBus();
  //ucBuf[7] = 0xff;
  //rba_BswSrv_MemCopy(ptr->SduDataPtr, ucBuf, ptr->SduLength);
  //finish debug

  Dem_SetCurrentTirePressures(tTPM_HMIPressureMessage.ucData2, tTPM_HMIPressureMessage.ucData3, tTPM_HMIPressureMessage.ucData4, tTPM_HMIPressureMessage.ucData5);
  Dem_SetCurrentLearnLocateStatus(tTPM_HMIPressureMessage.ucData6);
  return TRUE;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMITempAndRefPress_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  tsCAN_Message tTPM_HMITempAndRefPressMessage;

  (void) HufIf_CanMsgTransmit(CAN_MSG_HMI_TEMP_CYCLIC, &tTPM_HMITempAndRefPressMessage);
  (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_HMITempAndRefPressMessage, ptr->SduLength);

  Dem_SetCurrentTireTemperatures(tTPM_HMITempAndRefPressMessage.ucData0, tTPM_HMITempAndRefPressMessage.ucData1, tTPM_HMITempAndRefPressMessage.ucData2, tTPM_HMITempAndRefPressMessage.ucData3);
  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationResponse_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr)
{
  tsCAN_Message tTPM_ApplicationResponseMessage;

  #ifdef DEBUG_PRESSURE_ON_KEY
  tStandstillDebugMsg* dataBuffer;

  dataBuffer = SSMDEBUG_GetPointerToBuffer();
  if (dataBuffer->ucEventType != 0x00)
  {
  	// PC 05/2020: Had to comment these lines out, because debug messaging was not working in MONITOR mode.
//    if (SYSMGR_GetEcuMode() == cECUMODE_WAKE) //RST info: comment this line out to be able to send app response message in all modes
//    {                                                          //also check Com_IPdu_NotificationCallback_ApplicationResponse!
//
      rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)dataBuffer, ptr->SduLength);
//    }
  }
  else
  {
  #endif

  (void) HufIf_CanMsgTransmit(CAN_MSG_DEBUG_RES, &tTPM_ApplicationResponseMessage);
  (void) rba_BswSrv_MemCopy(ptr->SduDataPtr, (uint8*)&tTPM_ApplicationResponseMessage, ptr->SduLength);

  #ifdef DEBUG_PRESSURE_ON_KEY
  }
  #endif

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_IPdu_NotificationCallback_ApplicationResponse(void)
{
  #ifdef DEBUG_PRESSURE_ON_KEY
  // PC 05/2020: Had to comment these lines out, because debug messaging was not working in MONITOR mode.
//  if (SYSMGR_GetEcuMode() == cECUMODE_WAKE) //RST info: comment this line out to be able to send app response message in all modes
//  {                                                    //also check Com_IPdu_Callout_ApplicationResponse_TPM!
    SSMDEBUG_StopTrigger();
//  }
  #endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationRequest(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ApplicationRequest_UpdateValues(&AU8_Buffer[0]);

  Com_TriggerIPDUSend(ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_RdcData_TPM(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_RdcDataTPM_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_BCM_peripheralMasterClock(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //contains clock value from CGM ECU. Our local clock shall be synchronized to the CGM clock with this signal. ABS message timestamps are based on CGM clock.
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ClockSynchronization_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_VehicleData. Contains wheel speeds in km/h -> the 4 wheel speeds shall be used to calculate vehicle speed
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_VehicleData. Contains wheel speeds in km/h -> the 4 wheel speeds shall be used to calculate vehicle speed
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
//FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr)
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_WheelPulseCount_TPM. Contains wheel pulse counters, timestamp, validity bits and message counter.
  //message counter shall be used to monitor if the message content is updated regularly.
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TMM_Status_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_EnvironmentData. Contains ambietn temperature.
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_TMM_Status_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VehSts_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_VehicleData. Contains the vehicle mode -> ignition state can be derived from this information.
  //VehModCurr >=3 means "ignition on".
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_VehSts_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VmsStsReq_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr)
{
  //replacement function for Com_IPdu_Callout_VehicleData. Contains the offroad mode.
  //DrvModPataOffRoadMod == 0/1
  uint8 AU8_Buffer[8];
  (void) rba_BswSrv_MemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength);

  CANMGR_VmsStsReq_BodyLCAN_UpdateValues(&AU8_Buffer[0]);

  return TRUE;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
