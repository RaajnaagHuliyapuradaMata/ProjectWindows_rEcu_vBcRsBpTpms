#include "Std_Types.hpp"

#include "types.hpp"
#include "Com.hpp"
#include "Com_Cbk.hpp"
#include "Com_PBcfg_InternalId.hpp"
#include "CanManagerX.hpp"
#include "iTpms_Interface.hpp"
#include "rba_BswSrv.hpp"
#include "DemManagerX.hpp"
#include "DemAppInterfaceX.hpp"
#include "AdcX.hpp"

extern void Debug_GetTgRxIrqCounter(
   uint8* ucIrqCnt,
   uint32* ulTsDiff);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_IPdu_Callout_ApplicationCyclic_TPM(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) ltIdPdu
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) lptrstInfoPdu
){
   //TBD: Optimize memcopy
   Type_SwcApplTpms_stMessageCan stMessage;
   uint8                         lu8IndexByte;
   boolean                       lbNeedTransmit = FALSE;
   uint8*                        lptrubMessage = ((uint8*)&stMessage);

   (void)infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan(
         CAN_MSG_Debug_CYCLIC
      ,  &stMessage
   );

   for(
      lu8IndexByte = 0;
      lu8IndexByte < sizeof(stMessage);
      lu8IndexByte ++
   ){
      if(
            lptrubMessage[lu8IndexByte]
         != 0x00U
      ){
         lbNeedTransmit = TRUE;
         break;
      }
      else{
      }
   }

   if(
         FALSE
      != lbNeedTransmit
   ){
      (void)LibAutosar_vptrMemCopy(
            lptrstInfoPdu->SduDataPtr
         ,  (uint8*)&stMessage
         ,  lptrstInfoPdu->SduLength
      );
   }
   else{
   }

   return lbNeedTransmit;
}

FUNC(boolean, COM_CODE) Com_IPdu_Callout_HMIPressure_TPM(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) ptr
){
   Type_SwcApplTpms_stMessageCan stMessage;
   (void)infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan(
         CAN_MSG_HMI_CYCLIC
      ,  &stMessage
   );
   //TBD: Optimize memcopy
   (void)LibAutosar_vptrMemCopy(
         ptr->SduDataPtr
      ,  (uint8*)&stMessage
      ,  ptr->SduLength
   );
   Dem_SetCurrentTirePressures(
         stMessage.lptru8Data2
      ,  stMessage.lptru8Data3
      ,  stMessage.lptru8Data4
      ,  stMessage.lptru8Data5
   );
   Dem_SetCurrentLearnLocateStatus(
      stMessage.lptru8Data6
   );
   return TRUE;
}

FUNC(boolean, COM_CODE) Com_IPdu_Callout_TPMS_Software_ID_TPM(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) ptr
){
   //TBD: Optimize memcopy
   Type_SwcApplTpms_stMessageCan stMessage;
   (void)infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan(
         CAN_MSG_TPMS_Software_ID_CYCLIC
      ,  &stMessage
   );
   (void)LibAutosar_vptrMemCopy(
         ptr->SduDataPtr
      ,  (uint8*)&stMessage
      ,  ptr->SduLength
   );
   return TRUE;
}

FUNC(boolean, COM_CODE) Com_IPdu_Callout_HMITempAndRefPress_TPM(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) ptr
){
   //TBD: Optimize memcopy
   Type_SwcApplTpms_stMessageCan stMessage;
   (void)infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan(
         CAN_MSG_HMI_TEMP_CYCLIC
      ,  &stMessage
   );
   (void)LibAutosar_vptrMemCopy(
         ptr->SduDataPtr
      ,  (uint8*)&stMessage
      ,  ptr->SduLength
   );
   Dem_SetCurrentTireTemperatures(
         stMessage.lptru8Data0
      ,  stMessage.lptru8Data1
      ,  stMessage.lptru8Data2
      ,  stMessage.lptru8Data3
   );
   return TRUE;
}

FUNC(boolean, COM_CODE) Com_IPdu_Callout_ApplicationResponse_TPM(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) ptr
){
   //TBD: Optimize memcopy
   Type_SwcApplTpms_stMessageCan stMessage;
   (void)infSwcApplTpmsSwcServiceCom_tBuildTxMessageCan(
         CAN_MSG_DEBUG_RES
      ,  &stMessage
   );
   (void)LibAutosar_vptrMemCopy(
         ptr->SduDataPtr
      ,  (uint8*)&stMessage
      ,  ptr->SduLength
   );
   return TRUE;
}

//TBD: Optimize memcopy
FUNC(boolean, COM_CODE) Com_IPdu_Callout_ApplicationRequest        (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_ApplicationRequest_UpdateValues        (&AU8_Buffer[0]); Com_TriggerIPDUSend(ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0); return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_RdcData_TPM               (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_RdcDataTPM_UpdateValues                (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_BCM_peripheralMasterClock (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_ClockSynchronization_UpdateValues      (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN  (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues  (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped   (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues   (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_TMM_Status_BodyLCAN       (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_TMM_Status_BodyLCAN_UpdateValues       (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_VehSts_BodyLCAN           (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_VehSts_BodyLCAN_UpdateValues           (&AU8_Buffer[0]);                                                                                              return TRUE;}
FUNC(boolean, COM_CODE) Com_IPdu_Callout_VmsStsReq_BodyLCAN        (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr){uint8 AU8_Buffer[8]; (void)LibAutosar_vptrMemCopy(AU8_Buffer, ptr->SduDataPtr, ptr->SduLength); CANMGR_VmsStsReq_BodyLCAN_UpdateValues        (&AU8_Buffer[0]);                                                                                              return TRUE;}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
