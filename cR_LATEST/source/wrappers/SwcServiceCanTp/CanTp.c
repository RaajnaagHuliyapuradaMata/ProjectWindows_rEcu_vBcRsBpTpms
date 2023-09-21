/******************************************************************************/
/* File   : CanTp.c                                                           */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infSwcServiceCanTpSwcServiceSchM.hpp"

#include "CfgSwcServiceCanTp.hpp"
#include "CanTp.hpp"
#include "CanTp_Cbk.hpp"
#include "CanTp_Prv.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"
uint8 CanTp_MainState;
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.hpp"
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
         MaxLength = (TX_DL > CANTP_DEFAULT_CAN_DL) ? CANTP_MAXFDFFDL : CANTP_MAXFFDL;
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

static Std_ReturnType CanTp_Lok_GetFcActiveChannel(
   CanTp_RxContextType* Context
){
         Std_ReturnType   Status = E_NOT_OK;
   const CanTp_TxSduType* TxConnection;
   if(
         Context->SduId
      <  CanTp_CfgPtr->NumberOfTxSdus
   ){
      TxConnection = CanTp_CfgPtr->TxSdu + Context->SduId;
      if(
            CanTp_SubState[TxConnection->ChannelId]
         == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME
      ){
         Context->ChannelId = TxConnection->ChannelId;
         Status = E_OK;
      }
   }
   return Status;
}

static uint8 CanTp_Lok_GetRxContext(
            CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
         uint8            ErrorId = CANTP_E_PARAM_CONFIG;
         CanTp_SduIdType  TxSduId;
         CanTp_SduIdType  RxSduId;
         uint8            FrameType;
         uint8*           SduDataPtr;
   const CanTp_TxSduType* TxConnection;
   const CanTp_RxSduType* RxConnection;
   const CanTp_RxPduType* RxPdu = CanTp_CfgPtr->RxPdu + Context->PduId;

   if(
         PduInfoPtr->SduDataPtr
      == NULL_PTR
   ){
      ErrorId = CANTP_E_PARAM_POINTER;
   }
   else{
      SduDataPtr       = PduInfoPtr->SduDataPtr;
      Context->Address = 0;
      RxSduId          = RxPdu->RxSduId;
      TxSduId          = RxPdu->TxSduId;
      if(
            RxPdu->GetSduPair
         != NULL_PTR
      ){
         Context->Address = *SduDataPtr;
         SduDataPtr++;
         RxPdu->GetSduPair(
               &TxSduId
            ,  &RxSduId
            ,  Context->Address
         );
      }
      FrameType = *SduDataPtr >> CANTP_FRAMETYPE_OFFSET;
      if(
            FrameType
         <  CfgSwcServiceCanTp_dNumFrameTypes
      ){
         Context->FrameType = FrameType;
         if(
               FrameType
            == CANTP_FLOWCONTROL_FRAME
         ){
            Context->SduId = TxSduId;
            if(
                  CanTp_Lok_GetFcActiveChannel(
                     Context
                  )
               == E_OK
            ){
               TxConnection             = CanTp_CfgPtr->TxSdu + Context->SduId;
               Context->PduRPduHandleId = TxConnection->PduRPduHandleId;
               Context->AddressSize     = CanTp_AddressSize[TxConnection->AddressFormatId];
               Context->IsPaddingOn     = CanTp_Lok_GetBit(TxConnection->BitFields, CANTP_PADDINGON);
               ErrorId                  = CANTP_NO_ERROR;
            }
         }
         else{
            Context->SduId = RxSduId;
            if(
                  Context->SduId
               <  CanTp_CfgPtr->NumberOfRxSdus
            ){
               RxConnection             = CanTp_CfgPtr->RxSdu + RxSduId;
               Context->ChannelId       = RxConnection->ChannelId;
               Context->PduRPduHandleId = RxConnection->PduRPduHandleId;
               Context->AddressSize     = CanTp_AddressSize[RxConnection->AddressFormatId];
               Context->IsPaddingOn     = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_PADDINGON);
               Context->IsFdEnabled     = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_FD_ENABLED);
               Context->IsFunctional    = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_FUNCTIONAL);

               ErrorId = (
                     Context->IsFunctional
                  && (
                           FrameType
                        != CANTP_SINGLE_FRAME
                     )
               )
               ?  CANTP_E_INVALID_TATYPE
               :  CANTP_NO_ERROR
               ;
            }
         }
      }
   }
   return ErrorId;
}

static Std_ReturnType CanTp_Lok_RxSduLengthCheck(
            CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   uint8         CAN_DL     = CANTP_INVALID_DL;
   uint8         DataOffset = 0;
   uint8         SF_DL      = 0;
   uint32        FF_DL      = 0;
   Type_SwcServiceCom_tLengthPdu FF_DLmin;
   Type_SwcServiceCom_tLengthPdu FfDlValue12bit;
   uint8         MaxCfSduLength;
   Type_SwcServiceCom_tLengthPdu SduLengthRemaining;
   uint8         RX_DL;
   uint8*        Data           = PduInfoPtr->SduDataPtr + Context->AddressSize;
   uint8         PciLowerNibble = Data[0] & CANTP_LOWERNIBBLE_MASK;

   switch(Context->FrameType){
      case CANTP_SINGLE_FRAME:
         if(
               PduInfoPtr->SduLength
            <= CANTP_DEFAULT_CAN_DL
         ){
            DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCAN];
            SF_DL = PciLowerNibble;
            if(
                  (
                        PciLowerNibble
                     != 0u
                  )
               && (
                        PciLowerNibble
                     <= (CANTP_DEFAULT_CAN_DL - DataOffset)
                  )
            ){
               CAN_DL = (
                  Context->IsPaddingOn
               )
               ?  CANTP_DEFAULT_CAN_DL
               :  (DataOffset + (uint8)PciLowerNibble)
               ;
            }
         }
         else{
            DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCANFD];
            SF_DL = Data[1];
            if(
                  (PciLowerNibble == 0u)
               && (SF_DL  > (7u - Context->AddressSize))
               && (SF_DL <= (PduInfoPtr->SduLength - DataOffset))
               && (
                        (Context->AddressSize + 2u + SF_DL)
                     <= CANTP_MAX_NPDU_LENGTH
                  )
            ){
               CAN_DL = (
                  Context->IsPaddingOn
               )
               ?  CanTp_Lok_GetCanDl(DataOffset + SF_DL)
               :  (DataOffset + SF_DL)
               ;
            }
         }
         break;

      case CANTP_FIRST_FRAME:
         CAN_DL         = (uint8)(PduInfoPtr->SduLength);
         RX_DL          = CanTp_Lok_IsRxDlInValid(CAN_DL) ? CANTP_INVALID_DL : CAN_DL;
         FF_DLmin       = RX_DL - Context->AddressSize - ((CAN_DL > CANTP_DEFAULT_CAN_DL) ? 1u : 0u);
         FfDlValue12bit = ((Data[0] & CANTP_LOWERNIBBLE_MASK) * 0x100u) + Data[1];
         if(
               FfDlValue12bit
            == 0u
         ){
            FF_DL = (Data[2] * 0x1000000u)
                  + (Data[3] * 0x10000u)
                  + (Data[4] * 0x100u)
                  +  Data[5]
                  ;

            DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCANFD];

            RX_DL = (
                  (FF_DL  > CANTP_MAXFDFFDL)
               || (FF_DL <= CANTP_MAXFFDL)
            )
            ?  CANTP_INVALID_DL
            :  RX_DL
            ;
         }
         else{
            FF_DL      = FfDlValue12bit;
            DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCAN];
         }
         RX_DL = (
               Context->IsFunctional
            || (
                     FF_DL
                  <  FF_DLmin
               )
         )
         ?  CANTP_INVALID_DL
         :  RX_DL
         ;

         CAN_DL = RX_DL;
         break;

      case CANTP_CONSECUTIVE_FRAME:
         SduLengthRemaining = CanTp_Channel[Context->ChannelId].SduLengthRemaining;
         Context->SN        = PciLowerNibble;
         RX_DL              = CanTp_Lok_GetRxDl(Context->ChannelId);
         DataOffset         = Context->AddressSize + CANTP_CF_PCISIZE;
         MaxCfSduLength     = RX_DL - DataOffset;

         CAN_DL = (
               SduLengthRemaining
            <  MaxCfSduLength
         )
         ?  (uint8)(SduLengthRemaining + DataOffset)
         :  RX_DL
         ;

         CAN_DL = (
            Context->IsPaddingOn
         )
         ?  CanTp_Lok_GetCanDl(CAN_DL)
         :  CAN_DL
         ;
         break;

      case CANTP_FLOWCONTROL_FRAME:
         Context->FlowStatus = PciLowerNibble;
         DataOffset          = Context->AddressSize + 1;
         CAN_DL = (
            Context->IsPaddingOn
         )
         ?  CANTP_DEFAULT_CAN_DL
         :  (CANTP_FC_PCISIZE  + Context->AddressSize)
         ;
         break;

      default:
         break;
   }
   Context->CAN_DL = CAN_DL;
   Context->DataOffset = DataOffset;

   Context->SduLength = (
         Context->FrameType
      == CANTP_SINGLE_FRAME
   )
   ?  SF_DL
   :  (Type_SwcServiceCom_tLengthPdu)FF_DL
   ;

   return CanTp_Cfg_DlcCheck(
         PduInfoPtr->SduLength
      ,  Context->CAN_DL
   );
}

static void CanTp_Lok_LengthError(
   const CanTp_RxContextType* Context
){
   uint8 Api;
   Api = (
         Context->FrameType
      == CANTP_FLOWCONTROL_FRAME
   )
   ?  CANTP_TX_PDUR_CONFIRMATION
   :  CANTP_RX_PDUR_CONFIRMATION
   ;

   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         (CanTp_SubState[Context->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME)
      || (CanTp_SubState[Context->ChannelId] == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME)
   ){
      CanTp_Lok_PduRConfirmation(
            Api
         ,  Context->PduRPduHandleId
         ,  E_NOT_OK
      );
      CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
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

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

