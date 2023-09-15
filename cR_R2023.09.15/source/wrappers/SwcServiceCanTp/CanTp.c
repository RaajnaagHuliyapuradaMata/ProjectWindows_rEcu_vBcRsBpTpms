#include "Std_Types.hpp"

#include "infSwcServiceCanTpSwcServiceSchM.hpp"

#include "CfgSwcServiceCanTp.hpp"
#include "CanTp.hpp"
#include "CanTp_Cbk.hpp"
#include "CanTp_Prv.hpp"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"
uint8 CanTp_MainState;
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.hpp"
#if(CANTP_VERSION_INFO_API == STD_ON)
void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo){
   if(
         versioninfo
      == NULL_PTR
   ){
   }
   else{
      versioninfo->vendorID         = CANTP_VENDOR_ID;
      versioninfo->moduleID         = CANTP_MODULE_ID;
      versioninfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = CANTP_SW_PATCH_VERSION;
   }
}
#endif

void CanTp_Init(
   const Type_CfgSwcServiceCanTp_st* CfgPtr
){
   CanTp_MainState = CANTP_OFF;
   CanTp_CfgPtr    = &CfgSwcServiceCanTp_cst;
   (void)CfgPtr;
   CanTp_Lok_RxParamInit();
   CanTp_Lok_QInit();
   CanTp_Lok_ArrayInit(
         &CanTp_SubState[0]
      ,  CanTp_CfgPtr->NumberOfChannels
      ,  CANTP_IDLE
   );
   CanTp_Lok_ArrayInit(
         &CanTp_TxConfirmationChannel[0]
      ,  CanTp_CfgPtr->NumberOfTxPdus
      ,  CANTP_INVALID_CHANNEL
   );
   CanTp_MainState = CANTP_ON;
}

#if(CANTP_CANTPLITE_SUPPORT != STD_ON)
void CanTp_Shutdown(void){
   CanTp_MainState = CANTP_OFF;
   CanTp_Lok_RxParamInit();
   CanTp_Lok_QInit();
   CanTp_Lok_ArrayInit(
         &CanTp_SubState[0]
      ,  CanTp_CfgPtr->NumberOfChannels
      ,  CANTP_IDLE
   );
   CanTp_Lok_ArrayInit(
         &CanTp_TxConfirmationChannel[0]
      ,  CanTp_CfgPtr->NumberOfTxPdus
      ,  CANTP_INVALID_CHANNEL
   );
   CanTp_CfgPtr = NULL_PTR;
}
#endif

void infSwcServiceCanTpSwcServiceSchM_vMainFunction(void){
   CanTp_ChannelIdType ChannelId;
   for(
      ChannelId = 0;
      ChannelId < CanTp_CfgPtr->NumberOfChannels;
      ChannelId ++
   ){
      CanTp_Lok_ExecuteState(ChannelId);
   }
   CanTp_IncrementCounter();
}

Std_ReturnType CanTp_Transmit(
            Type_SwcServiceCom_tIdPdu    CanTpTxSduId
   ,  const Type_SwcServiceCom_stInfoPdu* CanTpTxInfoPtr
){
   Std_ReturnType RetVal = E_NOT_OK;
   CanTp_TickType Value = 0;
   CanTp_TickType ElapsedValue;
   uint16 MaxLength;
   uint8 PciId;
   uint8 ErrorId;
   uint8 PayloadLength;
   uint8 TX_DL;
   const CanTp_TxSduType *Connection;
   CanTp_ChannelType *Channel;
   Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
   Channel = CanTp_Channel + Connection->ChannelId;

   if(CanTpTxInfoPtr == NULL_PTR){
      ErrorId = CANTP_E_PARAM_POINTER;
   }
   else if(CanTpTxInfoPtr->SduLength == 0u){
      ErrorId = CANTP_E_COM;
   }
   else{
      CanTp_Lok_TxPciInit(&PciId, CanTpTxSduId, CanTpTxInfoPtr);
      TX_DL = CanTp_Lok_GetTxDl(Connection);
      if(CanTp_Lok_GetBit(Connection->BitFields, CANTP_FUNCTIONAL)){
         PayloadLength = TX_DL - 1 - CanTp_AddressSize[Connection->AddressFormatId];
         MaxLength = (PciId <= CANTP_NPCI_SFCANFD) ? (PayloadLength - 1) : PayloadLength;
      }
      else{
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
         MaxLength = (TX_DL > CANTP_DEFAULT_CAN_DL) ? CANTP_MAXFDFFDL : CANTP_MAXFFDL;
#endif
      }
      ErrorId = (CanTpTxInfoPtr->SduLength > MaxLength) ? CANTP_E_INVALID_TATYPE : CANTP_NO_ERROR;
   }
   if(ErrorId != CANTP_NO_ERROR){
   }
   else{
      CanTp_GetElapsedValue(&Value, &ElapsedValue);
      SchM_Enter_CanTp_EXCLUSIVE_AREA();
      if(CanTp_Lok_GetState(Connection->ChannelId) == CANTP_IDLE){
         Channel->ActiveSduId = CanTpTxSduId;
         Channel->PciId = PciId;
         Channel->SduLength = CanTpTxInfoPtr->SduLength;
         Channel->InitialTicks = Value;
         Channel->STminTicks = CANTP_INVALID_STMIN_TICKS;
         CanTp_SubState[Connection->ChannelId] = CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED;
         RetVal = E_OK;
      }
      SchM_Exit_CanTp_EXCLUSIVE_AREA();
   }
   return(RetVal);
}

#if(CANTP_CANTPLITE_SUPPORT != CANTP_ON)
Std_ReturnType CanTp_CancelTransmit(
   Type_SwcServiceCom_tIdPdu CanTpTxSduId
){
   Std_ReturnType RetVal = E_NOT_OK;
   const CanTp_TxSduType *Connection;
   boolean TcDisabled;
   Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
   TcDisabled = CanTp_Lok_GetBit(Connection->BitFields, CANTP_TC_DISABLED);
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         (TcDisabled)
      || (CanTp_Lok_GetState(Connection->ChannelId) != CANTP_TRANSMISSION)
      || (CanTpTxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId)
   ){
   }
   else{
      CanTp_Lok_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
      if(CanTp_SubState[Connection->ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION){
         CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
      }
      CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
      RetVal = E_OK;
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
   return (RetVal);
}

Std_ReturnType CanTp_CancelReceive(
   Type_SwcServiceCom_tIdPdu CanTpRxSduId
){
   uint8 PayLoadLength;
   Std_ReturnType RetVal = E_NOT_OK;
   const CanTp_RxSduType *Connection;
   Connection = CanTp_CfgPtr->RxSdu + CanTpRxSduId;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         (CanTp_Lok_GetState(Connection->ChannelId) != CANTP_RECEPTION)
      || (CanTpRxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId)
   ){
   }
   else{
      PayLoadLength = CanTp_Lok_GetRxDl(Connection->ChannelId) -
      CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;
      if(CanTp_Channel[Connection->ChannelId].SduLengthRemaining > PayLoadLength){
         CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
         if(CanTp_SubState[Connection->ChannelId] == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION){
            CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
         }
         CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
         RetVal = E_OK;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
   return (RetVal);
}
#endif

void CanTp_TxConfirmation(
   Type_SwcServiceCom_tIdPdu TxPduId
){
   CanTp_ChannelType*  Channel;
   CanTp_ChannelIdType ChannelId;
   uint8               SubState;
   CanTp_TickType      Value = 0;
   CanTp_TickType      ElapsedValue;
   uint8               MaxCopyLength;
   const               CanTp_TxSduType* TxConnection;

   CanTp_GetElapsedValue(&Value, &ElapsedValue);
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   ChannelId = CanTp_TxConfirmationChannel[TxPduId];
   Channel = CanTp_Channel + ((ChannelId < CanTp_CfgPtr->NumberOfChannels) ? ChannelId : 0);
   SubState = (ChannelId < CanTp_CfgPtr->NumberOfChannels) ? CanTp_SubState[ChannelId] : CANTP_IDLE;
   switch(SubState){
      case CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION:
         Channel->InitialTicks = Value;
         CanTp_Lok_FcTxConfirmation(ChannelId);
         CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL;
         break;

      case CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION:
         Channel->InitialTicks = Value;
         TxConnection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
         MaxCopyLength = CanTp_Lok_GetTxDl(TxConnection) -
         CanTp_AddressSize[TxConnection->AddressFormatId] - CanTp_PciSize[Channel->PciId];
         Channel->SduLengthRemaining = (
               Channel->SduLengthRemaining
            <  MaxCopyLength
         )
         ?  0u
         :  (Channel->SduLengthRemaining - MaxCopyLength)
         ;
         if(Channel->PciId == CANTP_NPCI_CF){
            Channel->SN++;
            Channel->SN &= CANTP_LOWERNIBBLE_MASK ;
            Channel->BlockCfsRemaining--;
         }
         if(Channel->SduLengthRemaining == 0u){
            CanTp_SubState[ChannelId] = CANTP_IDLE;
            CanTp_Lok_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, TxConnection->PduRPduHandleId, E_OK);
         }
         else{
            if(Channel->BlockCfsRemaining != 0u){
               CanTp_SubState[ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
            }
            else{
               CanTp_Lok_PrepareFcRecieve(ChannelId);
            }
         }
         CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL;
         break;

      default:
         break;
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
   CanTp_Lok_BurstMainFunction(ChannelId, CANTP_TRIGGER_TX_CONFIRMATION);
}

void CanTp_RxIndication(
            Type_SwcServiceCom_tIdPdu    RxPduId
   ,  const Type_SwcServiceCom_stInfoPdu* PduInfoPtr
){
   CanTp_RxContextType Context;
   uint8               ErrorId;
   Context.PduId     = RxPduId;
   Context.FrameType = 0;
   Context.ChannelId = 0;

#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
   if(CanTp_Lok_IsNoDevError(RxPduId, CANTP_RXINDICATION, CANTP_E_INVALID_RX_ID))
#endif
   {
      if(
            PduInfoPtr
         == NULL_PTR
      ){
      }
      else{
         ErrorId = CanTp_Lok_GetRxContext(
               &Context
            ,  PduInfoPtr
         );
         if(
               ErrorId
            != CANTP_NO_ERROR
         ){
         }
         else if(
            CanTp_Lok_RxSduLengthCheck(
                  &Context
               ,  PduInfoPtr
            )
            != E_OK
         ){
            CanTp_Lok_LengthError(
               &Context
            );
         }
         else{
            CanTp_Lok_ProcessFrame(
                  &Context
               ,  PduInfoPtr
            );
            CanTp_Lok_BurstMainFunction(
                  Context.ChannelId
               ,  CANTP_TRIGGER_RX_INDICATION
            );
         }
      }
   }
}

#if(CANTP_TRIGGER_TRANSMIT_API == CANTP_ON)
Std_ReturnType CanTp_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu *PduInfoPtr){
    Std_ReturnType Status = E_NOT_OK;
   CanTp_ChannelIdType ChannelId;
   uint8 TX_DL = CANTP_DEFAULT_CAN_DL;
#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
   if(CanTp_Lok_IsNoDevError(TxPduId, CANTP_TRIGGERTRANSMIT, CANTP_E_INVALID_TX_ID))
#endif
   {
        if(PduInfoPtr == NULL_PTR){
        }
        else{
            ChannelId = CanTp_TxConfirmationChannel[TxPduId];
            SchM_Enter_CanTp_EXCLUSIVE_AREA();
            if(ChannelId < CanTp_CfgPtr->NumberOfChannels){
                TX_DL = (CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION) ?
                        CanTp_Lok_GetTxDl(CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId) : TX_DL;
                if((PduInfoPtr->SduLength < TX_DL) || (PduInfoPtr->SduDataPtr == NULL_PTR)){
                }
                else{
                    Status = CanTp_Lok_CreateFrame(ChannelId, PduInfoPtr);
                }
            }
            SchM_Exit_CanTp_EXCLUSIVE_AREA();
        }
   }
    return Status;
}
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.hpp"
