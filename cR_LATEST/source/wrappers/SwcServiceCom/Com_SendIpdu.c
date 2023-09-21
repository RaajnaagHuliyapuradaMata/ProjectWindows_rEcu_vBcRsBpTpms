#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "PduR_Com.hpp"

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadPeriodicModeInfo(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(uint8,                     AUTOMATIC) isSigTriggered
);

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadEventModeInfo(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Com_SendIpduInfo,          AUTOMATIC) sendIpduFlag_u16
);

LOCAL_INLINE FUNC(Type_SwcServiceCom_tLengthPdu, COM_CODE) Com_Lok_CalculateTxPduLength(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(uint8,                     AUTOMATIC) isTrigIpduSendWithMetadata
);

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessTxReqStatus(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Std_ReturnType,            AUTOMATIC) ipduTransStatus_ui
);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_Lok_SendIpdu(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Com_SendIpduInfo,          AUTOMATIC) sendIpduFlag_u16
){
   VAR(boolean, AUTOMATIC) SendIpdu_b     = COM_FALSE;
   Com_TxIpduConstPtrType  TxIPduConstPtr = &CfgSwcServiceCom_castListInfoIpduTx[ComTxPduId];
   Com_TxIpduRamPtrType    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
   SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
   if(
         sendIpduFlag_u16.isEventTrig
      != COM_RESET
   ){
      VAR(boolean,AUTOMATIC) isEventMode;
      TxIpduRamPtr->Com_n_Tick_Tx = 0;
      if(
            sendIpduFlag_u16.isModeChangd
         == COM_SET
      ){
         isEventMode = Com_Lok_LoadPeriodicModeInfo(
               ComTxPduId
            ,  sendIpduFlag_u16.sigTransProp
         );
      }
      else{
         isEventMode = COM_TRUE;
      }
      if(
            isEventMode
         == COM_TRUE
      ){
         SendIpdu_b = Com_Lok_LoadEventModeInfo(
               ComTxPduId
            ,  sendIpduFlag_u16
         );
      }
   }
   else{
      SendIpdu_b = COM_TRUE;
      if(
            sendIpduFlag_u16.isTimeoutReq
         == COM_SET
      ){
         if(
               Com_GetRamValue(
                     TXIPDU
                  ,  _TICKTXTO
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            != COM_START
         ){
            Com_SetRamValue(
                  TXIPDU
               ,  _TICKTXTO
               ,  TxIpduRamPtr->Com_TxFlags
               ,  COM_START
            );
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
         }
      }
   }
   SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
   if(
         SendIpdu_b
      == COM_TRUE
   ){
      VAR(Type_SwcServiceCom_stInfoPdu, COM_VAR  ) ComTxIPduInfo;
      VAR(Std_ReturnType,               AUTOMATIC) ipduTransStatus_ui;
      VAR(boolean,                      AUTOMATIC) ipduCalloutStatus;
      ComTxIPduInfo.SduDataPtr = TxIPduConstPtr->BuffPtr;
      ComTxIPduInfo.SduLength  = Com_Lok_CalculateTxPduLength(
            ComTxPduId
         ,  sendIpduFlag_u16.isTriggerIpduSendWithMetadata
      );
      if(
            (
                  TxIPduConstPtr->CallOut
               != NULL_PTR
            )
         && (
               !(
                  Com_GetValue(
                        TXIPDU
                     ,  _ISCALLOUTFRMTRIGTRANS
                     ,  TxIPduConstPtr->txIPduFields
                  )
               )
            )
      ){
         SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
         ipduCalloutStatus = TxIPduConstPtr->CallOut(
               ComTxPduId
            ,  &ComTxIPduInfo
         );
         SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
      }
      else{
         ipduCalloutStatus = COM_TRUE;
      }
      if(
            ipduCalloutStatus
         == COM_TRUE
      ){
         ipduTransStatus_ui = PduR_ComTransmit(
               TxIPduConstPtr->PdurId
            ,  &ComTxIPduInfo
         );
      }
      else{
         ipduTransStatus_ui = E_NOT_OK;
      }
      Com_Lok_ProcessTxReqStatus(
            ComTxPduId
         ,  ipduTransStatus_ui
      );
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadPeriodicModeInfo(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(uint8,                     AUTOMATIC) isSigTriggered
){
   VAR(boolean, AUTOMATIC) isEventMode  = COM_FALSE;
   Com_TxIpduRamPtrType    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);
   TxIpduRamPtr->Com_n = 0;
   switch(
      Com_GetRamValue(
            TXIPDU
         ,  _LATESTMODE
         ,  TxIpduRamPtr->Com_TransMode
      )
   ){
      case COM_TXMODE_PERIODIC: {
            TxIpduRamPtr->Com_Tick_Tx = 1;
         }
         break;

      case COM_TXMODE_DIRECT: {
            isEventMode = COM_TRUE;
         }
         break;

      case COM_TXMODE_MIXED: {
            if(isSigTriggered != COM_SET){
               TxIpduRamPtr->Com_Tick_Tx = 1;
            }
            else{
               TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(
                     (Type_SwcServiceCom_tIdPdu)ComTxPduId
                  ,  TxIpduRamPtr->CurrentTxModePtr
               );
               TxIpduRamPtr->Com_Tick_Tx++;
               isEventMode = COM_TRUE;
            }
         }
         break;

      case COM_TXMODE_NONE: {
         }
         break;

      default: {
         }
         break;
   }
   return isEventMode;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadEventModeInfo(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Com_SendIpduInfo,          AUTOMATIC) sendIpduFlag_u16
){
   VAR(boolean,AUTOMATIC)  SendIpdu_b     = COM_FALSE;
   Com_TxIpduConstPtrType  TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
   Com_TxIpduRamPtrType    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
   if(
         sendIpduFlag_u16.ignoreRepetitions
      != COM_SET
   ){
      TxIpduRamPtr->Com_n = TxIpduRamPtr->CurrentTxModePtr->NumOfRepetitions;
   }
   else{
      TxIpduRamPtr->Com_n = 0;
   }
   if(
         sendIpduFlag_u16.isTimeoutReq
      == COM_SET
   ){
      Com_SetRamValue(
            TXIPDU
         ,  _TICKTXTO
         ,  TxIpduRamPtr->Com_TxFlags
         ,  COM_START
      );
      TxIpduRamPtr->Com_TickTxTimeout = (TxIPduConstPtr->Timeout_Fact + 1);
   }
   if(
         (
               TxIpduRamPtr->Com_MinDelayTick
            == 0u
         )
      && (
               Com_GetRamValue(
                     TXIPDU
                  ,  _MDT
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            == COM_FALSE
         )
   ){
      if(
            TxIpduRamPtr->Com_n
         == 0
      ){
         Com_SetRamValue(
               TXIPDU
            ,  _EVENTTRIG
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_TRUE
         );
         TxIpduRamPtr->Com_n_Tick_Tx = 1;
      }
      else{
         TxIpduRamPtr->Com_n_Tick_Tx = 1;
      }
   }
   else{
      Com_SetRamValue(
            TXIPDU
         ,  _MDT
         ,  TxIpduRamPtr->Com_TxFlags
         ,  COM_TRUE
      );
   }
   return SendIpdu_b;
}

LOCAL_INLINE FUNC(Type_SwcServiceCom_tLengthPdu, COM_CODE) Com_Lok_CalculateTxPduLength(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(uint8,                     AUTOMATIC) isTrigIpduSendWithMetadata
){
   Com_TxIpduConstPtrType TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
   (void)isTrigIpduSendWithMetadata;
   return TxIPduConstPtr->Size;
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessTxReqStatus(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Std_ReturnType,            AUTOMATIC) ipduTransStatus_ui
){
   Com_TxIpduConstPtrType  TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
   Com_TxIpduRamPtrType    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
   SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
   if(
         ipduTransStatus_ui
      == E_OK
   ){
      if(
            (
                  TxIPduConstPtr->Min_Delay_Time_Fact
               != 0u
            )
         && (
                  TxIpduRamPtr->Com_MinDelayTick
               == 0u
            )
      ){
         TxIpduRamPtr->Com_MinDelayTick = TxIPduConstPtr->Min_Delay_Time_Fact +
         (
            Com_GetRamValue(
                  TXIPDU
               ,  _EVENTTRIG
               ,  TxIpduRamPtr->Com_TxFlags
            )
         )
         ? 1u
         : 0u
         ;
      }
   }
   SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
}

