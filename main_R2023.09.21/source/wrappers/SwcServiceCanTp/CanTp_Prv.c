/******************************************************************************/
/* File   : CanTp_Prv.c                                                       */
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
#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.hpp"
const uint8 CanTp_State[CfgSwcServiceCanTp_dNumSubStates] = {0, 1, 1, 1, 1, 2, 2, 2, 2};
const uint8 CanTp_AddressSize[CANTP_ADDRESS_ARRAY_SIZE]   = {0, 1, 1, 1, 0};
const uint8 CanTp_PciFrameType[CANTP_PCI_ARRAY_SIZE]      = {0, 0, 1, 1, 2, 3};
const uint8 CanTp_PciSize[CANTP_PCI_ARRAY_SIZE]           = {1, 2, 2, 6, 1, 3};

#if(CANTP_CANFD_SUPPORT == CANTP_ON)
const uint8 CanTp_CanDlTable[CANTP_CANDL_ARRAY_SIZE] = {
      0x08
   ,  0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0c,0x0c,0x0c,0x0c,0x10,0x10,0x10,0x10
   ,  0x14,0x14,0x14,0x14,0x18,0x18,0x18,0x18,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
   ,  0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30
   ,  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40
};
#endif
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.hpp"
CanTp_ChannelType CanTp_Channel[CANTP_MAX_CHANNEL_SIZE];
CanTp_ChannelIdType CanTp_TxConfirmationChannel[CANTP_MAX_NPDU_LENGTH];

#if(CANTP_CYCLE_COUNTER == CANTP_ON)
volatile CanTp_TickType CanTp_MainFunctionTicks;
#endif

const Type_CfgSwcServiceCanTp_st *CanTp_CfgPtr;
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"
uint8 CanTp_SubState[CANTP_MAX_CHANNEL_SIZE];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.hpp"
static void CanTp_Lok_Transmit(
      const CanTp_TxContextType*          Context
   ,        Type_SwcServiceCom_stInfoPdu* SduInfoPtr
   ,  const Type_SwcServiceCom_stInfoPdu* CanIfTxInfoPtr
){
   Type_SwcServiceCom_tLengthPdu RemBufSize;
   if(
         Context->ElapsedValue
      <= Context->CsTicks
   ){
            switch(
               PduR_CanTpCopyTxData(
                     Context->PduRPduHandleId
                  ,  SduInfoPtr
                  ,  NULL_PTR
                  ,  &RemBufSize
               )
            ){
               case BUFREQ_OK:
                  if(
                        RemBufSize
                     >= Context->PayLoadLength
                  ){
                    CanTp_Channel[Context->ChannelId].InitialTicks = Context->Value;
                    CanTp_SubState[Context->ChannelId] = CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION;
                    CanTp_Lok_CanIfTransmit(Context, CanIfTxInfoPtr);
                  }
                  break;

               case BUFREQ_E_BUSY:
                  break;

               default:
                  CanTp_Lok_PduRConfirmation(
                        Context->PduRApiId
                     ,  Context->PduRPduHandleId
                     ,  E_NOT_OK
                  );
                  CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
                  break;
            }
        }
   else{
            CanTp_Lok_PduRConfirmation(
                  Context->PduRApiId
               ,  Context->PduRPduHandleId
               ,  E_NOT_OK
            );
            CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
   }
}

static void SwcApplCanTp_fptrProcessRxFrame_Single(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   Std_ReturnType     Result;
   Type_SwcServiceCom_stInfoPdu        SduInfo;
   Type_SwcServiceCom_tLengthPdu      RemBufSize;
   BufReq_ReturnType  RetValue;
   CanTp_TickType     ElapsedValue;
   CanTp_TickType     Value   = 0;
   CanTp_ChannelType* Channel = &CanTp_Channel[Context->ChannelId];

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;
   SduInfo.SduLength  = Context->SduLength;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();

   if(
      CanTp_Lok_GetConnectionAcceptance(
            Context
         ,  PduInfoPtr
      )
      == E_OK
   ){
      Channel->ActiveSduId = Context->SduId;
      Channel->SduLength = Context->SduLength;
      Channel->SduLengthRemaining = Context->SduLength;
      CanTp_Lok_SetRxDl(
            Context->ChannelId
         ,  (uint8)(PduInfoPtr->SduLength)
      );
      Channel->InitialTicks = Value;
      RetValue = PduR_CanTpStartOfReception(
            Context->PduRPduHandleId
         ,  &SduInfo
         ,  Context->SduLength
         ,  &RemBufSize
      );
      switch(RetValue){
         case BUFREQ_OK:
            if(
                  RemBufSize
               >= Context->SduLength
            ){
               RetValue = PduR_CanTpCopyRxData(
                     Context->PduRPduHandleId
                  ,  &SduInfo
                  ,  &RemBufSize
               );

               Result = (
                     RetValue
                  != BUFREQ_OK
               )
               ?  E_NOT_OK
               :  E_OK
               ;

               CanTp_Lok_PduRConfirmation(
                     CANTP_RX_PDUR_CONFIRMATION
                  ,  Context->PduRPduHandleId
                  ,  Result
               );
            }
            else{
               CanTp_Lok_PduRConfirmation(
                     CANTP_RX_PDUR_CONFIRMATION
                  ,  Context->PduRPduHandleId
                  ,  E_NOT_OK
               );
            }
            break;

         case BUFREQ_E_OVFL:
            CanTp_Lok_PduRConfirmation(
                  CANTP_RX_PDUR_CONFIRMATION
               ,  Context->PduRPduHandleId
               ,  E_NOT_OK
            );
            break;

         default:
            break;
      }
      CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrProcessRxFrame_First(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   CanTp_ChannelType *Channel = &CanTp_Channel[Context->ChannelId];
   Type_SwcServiceCom_stInfoPdu       SduInfo;
   Type_SwcServiceCom_tLengthPdu     RemBufSize;
   uint8             NewSubState = CANTP_IDLE;
   uint8             FlowStatus  = CANTP_FC_WAIT;
   uint8             PayLoadLength;
   CanTp_TickType    Value       = 0;
   CanTp_TickType    ElapsedValue;
   BufReq_ReturnType RetValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );

   PayLoadLength      = (uint8)(PduInfoPtr->SduLength - Context->DataOffset);
   SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;
   SduInfo.SduLength  = (Type_SwcServiceCom_tLengthPdu)PayLoadLength;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();

   if(
         CanTp_Lok_GetConnectionAcceptance(
               Context
            ,  PduInfoPtr
         )
      == E_OK
   ){
      Channel->ActiveSduId = Context->SduId;
      Channel->SduLength   = Context->SduLength;
      CanTp_Lok_SetRxDl(
            Context->ChannelId
         ,  (uint8)(PduInfoPtr->SduLength)
      );
      Channel->InitialTicks = Value;
      RetValue = PduR_CanTpStartOfReception(
            Context->PduRPduHandleId
         ,  &SduInfo
         ,  Context->SduLength
         ,  &RemBufSize
      );
      switch(RetValue){
         case BUFREQ_OK:
            if(
                  RemBufSize
               >= PayLoadLength
            ){
               if(
                     PduR_CanTpCopyRxData(
                           Context->PduRPduHandleId
                        ,  &SduInfo
                        ,  &RemBufSize
                     )
                  != BUFREQ_OK
               ){
                  CanTp_Lok_PduRConfirmation(
                        CANTP_RX_PDUR_CONFIRMATION
                     ,  Context->PduRPduHandleId
                     ,  E_NOT_OK
                  );
                  NewSubState = CANTP_IDLE;
               }
               else{
                  NewSubState                 = CANTP_RX_SEND_FC;
                  Channel->SduLengthRemaining = Context->SduLength - PayLoadLength;
                  Channel->BS                 = 0;
                  Channel->STminTicks         = CANTP_INVALID_STMIN_TICKS;
                  Channel->FcWait             = 0;
                  Channel->SN                 = 1;
               }
            }
            else{
               CanTp_Lok_PduRConfirmation(
                     CANTP_RX_PDUR_CONFIRMATION
                  ,  Context->PduRPduHandleId
                  ,  E_NOT_OK
               );
               NewSubState = CANTP_IDLE;
            }
            break;

         case BUFREQ_E_OVFL:
            FlowStatus  = CANTP_FC_OVERFLOW;
            NewSubState = CANTP_RX_SEND_FC;
            Channel->BS = 0;
            break;

         default:
            NewSubState = CANTP_IDLE;
            break;
      }
      if(
            CanTp_SubState[Context->ChannelId]
         == CANTP_RX_RECEPTION_REQUEST_ACCEPTED
      ){
         Channel->FlowStatus = FlowStatus;
         CanTp_SubState[Context->ChannelId] = NewSubState;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrProcessRxFrame_Consecutive(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   Type_SwcServiceCom_stInfoPdu          SduInfo;
   Type_SwcServiceCom_tLengthPdu        RemBufSize;
   uint8                PayloadLength;
   CanTp_TickType       ElapsedValue;
   BufReq_ReturnType    RetValue;
   CanTp_ChannelPtrType Channel     = &CanTp_Channel[Context->ChannelId];
   CanTp_TickType       Value       = Channel->InitialTicks;
   Std_ReturnType       NotifyValue = CANTP_INVALID_NOTIFY_VALUE;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   PayloadLength      = Context->CAN_DL - Context->DataOffset;
   SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         (
               CanTp_SubState[Context->ChannelId]
            == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME
         )
      &&	(
               Context->SduId
            == Channel->ActiveSduId
         )
      && (
               Channel->BlockCfsRemaining
            >  0u
         )
   ){
      NotifyValue = E_NOT_OK;
      if(
            Context->SN
         == Channel->SN
      ){
         Channel->InitialTicks = Value;

         SduInfo.SduLength = (
               Channel->SduLengthRemaining
            >  PayloadLength
         )
         ?  PayloadLength
         :  (uint8)Channel->SduLengthRemaining
         ;

         RetValue = PduR_CanTpCopyRxData(Context->PduRPduHandleId, &SduInfo, &RemBufSize);
         if(
               RetValue
            == BUFREQ_OK
         ){
            Channel->SN++;
            Channel->SN &= CANTP_LOWERNIBBLE_MASK;
            Channel->SduLengthRemaining -= SduInfo.SduLength;
            Channel->BlockCfsRemaining--;
            CanTp_Lok_PrepareFcTransmit(
               Context->ChannelId
            );

            NotifyValue = (
                  Channel->SduLengthRemaining
               != 0u
            )
            ?  CANTP_INVALID_NOTIFY_VALUE
            :  E_OK
            ;
         }
      }
      if(
            NotifyValue
         != CANTP_INVALID_NOTIFY_VALUE
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_RX_PDUR_CONFIRMATION
            ,  Context->PduRPduHandleId
            ,  NotifyValue
         );
         CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrProcessRxFrame_FlowControl(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   CanTp_ChannelPtrType Channel = &CanTp_Channel[Context->ChannelId];
   CanTp_TickType       Value   = Channel->InitialTicks;
   CanTp_TickType       ElapsedValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[Context->ChannelId]
      == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME
   ){
      Channel->InitialTicks = Value;
      switch(
         Context->FlowStatus
      ){
         case CANTP_FC_WAIT:
            Channel->FlowStatus = CANTP_FC_WAIT;
            break;

         case CANTP_FC_CTS:
            Channel->FlowStatus = CANTP_FC_CTS;
            CanTp_Lok_SetTxBlockInfo(
                  Context
               ,  PduInfoPtr
            );
            CanTp_SubState[Context->ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
            break;

         default:
            CanTp_Lok_PduRConfirmation(
                  CANTP_TX_PDUR_CONFIRMATION
               ,  Context->PduRPduHandleId
               ,  E_NOT_OK
            );
            CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
            break;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static Std_ReturnType SwcApplCanTp_fptrCreateTxFrame_Single(
      CanTp_ChannelIdType ChannelId
   ,  Type_SwcServiceCom_stInfoPdu*        PduInfoPtr
){
         Type_SwcServiceCom_stInfoPdu          SduInfo;
         Type_SwcServiceCom_tLengthPdu        RemBufSize;
         uint8*               SduDataPtr;
         uint8                DataOffset;
         uint8                PaddingOffset;
         uint8                CAN_DL;
         uint8                PciId;
         uint32               SduLength;
         uint32               SduLengthRemaining;
         Std_ReturnType       Status  = E_NOT_OK;
         CanTp_ChannelPtrType Channel = CanTp_Channel + ChannelId;
   const CanTp_TxSduType*     Connection;

   if(
         CanTp_SubState[ChannelId]
      == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION
   ){
      Connection            = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
      PciId                 = Channel->PciId;
      SduLength             = Channel->SduLength;
      SduLengthRemaining    = Channel->SduLengthRemaining;
      DataOffset            = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[PciId];
      CAN_DL                = CanTp_Lok_GetTxDl(Connection);
      SduDataPtr            = PduInfoPtr->SduDataPtr + DataOffset;
      SduInfo.SduDataPtr    = SduDataPtr;
      SduInfo.SduLength     = (uint8)SduLengthRemaining;
      PduInfoPtr->SduLength = 0;
      if(
            PduR_CanTpCopyTxData(
                  Connection->PduRPduHandleId
               ,  &SduInfo
               ,  NULL_PTR
               ,  &RemBufSize
            )
         != BUFREQ_OK
      ){
      }
      else{
         if(
            CanTp_Lok_GetBit(
                  Connection->BitFields
               ,  CANTP_PADDINGON
            )
         ){
            CAN_DL        = CanTp_Lok_GetCanDl(DataOffset + SduInfo.SduLength);
            PaddingOffset = (uint8)(DataOffset + SduInfo.SduLength);
            SduDataPtr    = PduInfoPtr->SduDataPtr + PaddingOffset;
            CanTp_Lok_ArrayInit(
                  SduDataPtr
               ,  CAN_DL - PaddingOffset
               ,  CANTP_PADDING_BYTE
            );
         }
         else{
            CAN_DL = (uint8)(DataOffset + SduInfo.SduLength);
         }
         SduDataPtr = PduInfoPtr->SduDataPtr;
         if(
            (Connection->AddressFormatId != 0)
         ){
            *SduDataPtr = Connection->Address;
            SduDataPtr++;
         }
         if(PciId == CANTP_NPCI_SFCAN){
            *SduDataPtr = (uint8)SduLength;
         }
         else{
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
            if(PciId == CANTP_NPCI_SFCANFD){
               SduDataPtr[0] = 0x00;
               SduDataPtr[1] = (uint8)SduLength;
            }
#endif
         }
         PduInfoPtr->SduLength = CAN_DL;
         Status = E_OK;
      }
   }
   return Status;
}

static Std_ReturnType SwcApplCanTp_fptrCreateTxFrame_First(
      CanTp_ChannelIdType ChannelId
   ,  Type_SwcServiceCom_stInfoPdu*        PduInfoPtr
){
   Type_SwcServiceCom_stInfoPdu            SduInfo;
   Type_SwcServiceCom_tLengthPdu          RemBufSize;
   uint32                 SduLength;
   uint8*                 SduDataPtr;
   uint8                  DataOffset;
   uint8                  CAN_DL;
   uint8                  PciId;
   CanTp_ChannelPtrType   Channel = CanTp_Channel + ChannelId;
   Std_ReturnType         Status = E_NOT_OK;
   const CanTp_TxSduType* Connection;
   if(
         CanTp_SubState[ChannelId]
      == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION
   ){
      Connection         = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
      PciId              = Channel->PciId;
      DataOffset         = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[PciId];
      CAN_DL             = CanTp_Lok_GetTxDl(Connection);
      SduLength          = Channel->SduLength;
      SduDataPtr         = PduInfoPtr->SduDataPtr + DataOffset;
      SduInfo.SduDataPtr = SduDataPtr;
      SduInfo.SduLength  = CAN_DL - DataOffset;
      PduInfoPtr->SduLength = 0;
      if(
            PduR_CanTpCopyTxData(
                  Connection->PduRPduHandleId
               ,  &SduInfo
               ,  NULL_PTR
               ,  &RemBufSize
            )
         != BUFREQ_OK
      ){
      }
      else{
         SduDataPtr = PduInfoPtr->SduDataPtr;
         if(
               (Connection->AddressFormatId != CANTP_STANDARD)
         ){
            *SduDataPtr = Connection->Address;
            SduDataPtr++;
         }
         if(PciId == CANTP_NPCI_FFCAN){
            SduDataPtr[0] = 0x10 + (uint8)(SduLength >> 0x08u);
            SduDataPtr[1] = (uint8)SduLength;
         }
         else{
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
            if(PciId == CANTP_NPCI_FFCANFD){
               SduDataPtr[0] = 0x10;
               SduDataPtr[1] = 0x00;
               SduDataPtr[2] = (uint8)(SduLength >> 0x18u);
               SduDataPtr[3] = (uint8)(SduLength >> 0x10u);
               SduDataPtr[4] = (uint8)(SduLength >> 0x08u);
               SduDataPtr[5] = (uint8)SduLength;
            }
#endif
         }
         PduInfoPtr->SduLength = CAN_DL;
         Status = E_OK;
      }
   }
   return Status;
}

static Std_ReturnType SwcApplCanTp_fptrCreateTxFrame_Consecutive(
      CanTp_ChannelIdType ChannelId
   ,  Type_SwcServiceCom_stInfoPdu*        PduInfoPtr
){
   Type_SwcServiceCom_tLengthPdu          RemBufSize;
   Type_SwcServiceCom_stInfoPdu            SduInfo;
   uint8                  PaddingOffset;
   uint8*                 SduDataPtr;
   uint8                  DataOffset;
   uint8                  CAN_DL;
   uint8                  SN;
   uint8                  MaxCopyLength;
   uint32                 SduLengthRemaining;
   CanTp_ChannelPtrType   Channel = CanTp_Channel + ChannelId;
   Std_ReturnType         Status = E_NOT_OK;
   const CanTp_TxSduType* Connection;

   if(
         CanTp_SubState[ChannelId]
      == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION
   ){
      Connection            = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
      SN                    = Channel->SN;
      SduLengthRemaining    = Channel->SduLengthRemaining;
      DataOffset            = CanTp_AddressSize[Connection->AddressFormatId] + CANTP_CF_PCISIZE;
      CAN_DL                = CanTp_Lok_GetTxDl(Connection);
      MaxCopyLength         = CAN_DL - DataOffset;
      SduInfo.SduDataPtr    = PduInfoPtr->SduDataPtr + DataOffset;

      SduInfo.SduLength = (
            SduLengthRemaining
         >  MaxCopyLength
      )
      ?  MaxCopyLength
      :  (uint8)SduLengthRemaining
      ;

      PduInfoPtr->SduLength = 0;
      if(
            PduR_CanTpCopyTxData(
                  Connection->PduRPduHandleId
               ,  &SduInfo
               ,  NULL_PTR
               ,  &RemBufSize
            )
         != BUFREQ_OK
      ){
      }
      else{
         if(SduLengthRemaining < MaxCopyLength){
            if(
               CanTp_Lok_GetBit(
                     Connection->BitFields
                  ,  CANTP_PADDINGON
               )
            ){
               CAN_DL        = CanTp_Lok_GetCanDl(DataOffset + SduInfo.SduLength);
               PaddingOffset = (uint8)(DataOffset + SduInfo.SduLength);
               SduDataPtr    = PduInfoPtr->SduDataPtr + PaddingOffset;
               CanTp_Lok_ArrayInit(
                     SduDataPtr
                  ,  CAN_DL - PaddingOffset
                  ,  CANTP_PADDING_BYTE
               );
            }
            else{
               CAN_DL = (uint8)(DataOffset + SduInfo.SduLength);
            }
         }
         SduDataPtr = PduInfoPtr->SduDataPtr;
         if(
               (Connection->AddressFormatId != CANTP_STANDARD)
         ){
            *SduDataPtr = Connection->Address;
            SduDataPtr++;
         }
         *SduDataPtr = (CANTP_CF_HIGHNIBBLE | SN);
         PduInfoPtr->SduLength = CAN_DL;
         Status = E_OK;
      }
   }
   return Status;
}

static Std_ReturnType SwcApplCanTp_fptrCreateTxFrame_FlowControl(
      CanTp_ChannelIdType ChannelId
   ,  Type_SwcServiceCom_stInfoPdu*        PduInfoPtr
){
   uint8*                 SduDataPtr = PduInfoPtr->SduDataPtr;
   uint8                  PaddingOffset;
   Type_SwcServiceCom_tLengthPdu          SduLength  = CANTP_FC_PCISIZE;
   CanTp_ChannelPtrType   Channel    = CanTp_Channel + ChannelId;
   Std_ReturnType         Status     = E_NOT_OK;
   uint8                  BS;
   uint8                  STMin;
   uint8                  FlowStatus;
   const CanTp_RxSduType* Connection;
   PduInfoPtr->SduLength = 0;
   if(
         CanTp_SubState[ChannelId]
      == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION
   ){
      Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
      STMin = CanTp_Lok_GetRxParam(Channel->ActiveSduId, TP_STMIN);
      FlowStatus = Channel->FlowStatus;
      BS = Channel->BS;
      if(
            (Connection->AddressFormatId != CANTP_STANDARD)
      ){
         *SduDataPtr = Connection->Address;
         SduDataPtr++;
         SduLength++;
      }
      *SduDataPtr = (uint8)(CANTP_FC_HIGHNIBBLE | FlowStatus);
      SduDataPtr++;
      *SduDataPtr = BS;
      SduDataPtr++;
      *SduDataPtr = STMin;
      SduDataPtr++;
      if(
         CanTp_Lok_GetBit(
               Connection->BitFields
            ,  CANTP_PADDINGON
         )
      ){
         PaddingOffset = CanTp_AddressSize[Connection->AddressFormatId] + CANTP_FC_PCISIZE;
         CanTp_Lok_ArrayInit(
               SduDataPtr
            ,  CANTP_DEFAULT_CAN_DL - PaddingOffset
            ,  CANTP_PADDING_BYTE
         );
         SduLength = CANTP_DEFAULT_CAN_DL;
      }
      PduInfoPtr->SduLength = SduLength;
      Status = E_OK;
   }
   return Status;
}

static void SwcApplCanTp_fptrSubState_TxSendConsecutiveFrame(
   CanTp_ChannelIdType ChannelId
){
   uint8                  CAN_DL;
   Type_SwcServiceCom_stInfoPdu            SduInfo;
   Type_SwcServiceCom_stInfoPdu            PduInfo;
   CanTp_ChannelIdType    TxConfirmationChannel;
   const CanTp_TxSduType* Connection;
   uint8                  MaxLength;
   CanTp_TxContextType    Context;
   CanTp_ChannelPtrType   Channel = &CanTp_Channel[ChannelId];

   Context.ChannelId  = ChannelId;
   Context.PduRApiId  = CANTP_TX_PDUR_CONFIRMATION;
   Context.Value      = Channel->InitialTicks;
   CanTp_GetElapsedValue(
         &(Context.Value)
      ,  &(Context.ElapsedValue)
   );
   SduInfo.SduLength  = 0;
   SduInfo.SduDataPtr = NULL_PTR;
   PduInfo.SduDataPtr = NULL_PTR;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();

   Connection = (
         CanTp_SubState[ChannelId]
      == CANTP_TX_SEND_CONSECUTIVE_FRAME
   )
   ?  (CanTp_CfgPtr->TxSdu + Channel->ActiveSduId)
   :  (const CanTp_TxSduType*) NULL_PTR
   ;

   TxConfirmationChannel = (
         Connection
      != NULL_PTR
   )
   ?  CanTp_TxConfirmationChannel[Connection->TxConfirmationId]
   :  0
   ;

   if(
         TxConfirmationChannel
      == CANTP_INVALID_CHANNEL
   ){
      Context.PduRPduHandleId  = Connection->PduRPduHandleId;
      Context.PduId            = Connection->TxPduId;
      Context.TxConfirmationId = Connection->TxConfirmationId;
      CAN_DL                   = CanTp_Lok_GetTxDl(Connection);
      PduInfo.SduLength        = CAN_DL;
      Context.CsTicks          = CanTp_Lok_GetCfgCsCrTicks(Connection);

      MaxLength                = CAN_DL - CANTP_CF_PCISIZE - CanTp_AddressSize[Connection->AddressFormatId];

      Context.PayLoadLength = (
            Channel->SduLengthRemaining
         <  MaxLength
      )
      ?  (uint8)(Channel->SduLengthRemaining)
      :  MaxLength
      ;


      if(
                  (Context.ElapsedValue >= Channel->STminTicks)
               || (Channel->PciId       != CANTP_NPCI_CF)
      ){
         Channel->PciId = CANTP_NPCI_CF;

            CanTp_Lok_Transmit(
               &Context
            ,  &SduInfo
            ,  &PduInfo
         );

      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_TxWaitForFlowControlFrame(
   CanTp_ChannelIdType ChannelId
){
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_TxSduType*     Connection;
         CanTp_TickType       Value = Channel->InitialTicks;
         CanTp_TickType       ElapsedValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[ChannelId]
      == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME
   ){
      Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
      if(
            ElapsedValue
         >  CanTp_Lok_GetCfgBsBrTicks(
               Connection
            )
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_TX_PDUR_CONFIRMATION
            ,  Connection->PduRPduHandleId
            ,  E_NOT_OK
         );
         CanTp_SubState[ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_TxWaitForConfirmation(
   CanTp_ChannelIdType ChannelId
){
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_TxSduType*     Connection;
         CanTp_TickType       Value   = Channel->InitialTicks;
         CanTp_TickType       ElapsedValue;
   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[ChannelId]
      == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION
   ){
      Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
      if(
            ElapsedValue
         >  CanTp_Lok_GetCfgAsArTicks(
               Connection
            )
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_TX_PDUR_CONFIRMATION
            ,  Connection->PduRPduHandleId
            ,  E_NOT_OK
         );
         CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
         CanTp_SubState[ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_TxRequestAccepted(
   CanTp_ChannelIdType ChannelId
){
         uint8                        CAN_DL;
         uint8                        DataOffset;
         Type_SwcServiceCom_stInfoPdu SduInfo;
         Type_SwcServiceCom_stInfoPdu PduInfo;
         CanTp_ChannelIdType          TxConfirmationChannel;
         CanTp_ChannelType*           Channel = &CanTp_Channel[ChannelId];
   const CanTp_TxSduType*             Connection;
         CanTp_TxContextType          Context;
   Context.ChannelId = ChannelId;
   Context.PduRApiId = CANTP_TX_PDUR_CONFIRMATION;
   Context.Value = Channel->InitialTicks;
   CanTp_GetElapsedValue(
         &(Context.Value)
      ,  &(Context.ElapsedValue)
   );
   SduInfo.SduLength  = 0;
   SduInfo.SduDataPtr = NULL_PTR;
   PduInfo.SduDataPtr = NULL_PTR;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();

   Connection = (
         CanTp_SubState[ChannelId]
      == CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED
   )
   ?  (CanTp_CfgPtr->TxSdu + Channel->ActiveSduId)
   :  (const CanTp_TxSduType*)NULL_PTR
   ;

   TxConfirmationChannel = (
         Connection
      != NULL_PTR
   )
   ?  CanTp_TxConfirmationChannel[Connection->TxConfirmationId]
   :  0
   ;

   if(
         TxConfirmationChannel
      == CANTP_INVALID_CHANNEL
   ){
      Context.PduRPduHandleId     = Connection->PduRPduHandleId;
      Context.PduId               = Connection->TxPduId;
      Context.TxConfirmationId    = Connection->TxConfirmationId;
      Channel->BlockCfsRemaining  = 0;
      Channel->SduLengthRemaining = Channel->SduLength;
      Channel->SN                 = 1;
      DataOffset                  = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[Channel->PciId];
      CAN_DL                      = CanTp_Lok_GetTxDl(Connection);
      PduInfo.SduLength           = CAN_DL;

      Context.PayLoadLength = (
            Channel->PciId
         >= CANTP_NPCI_FFCAN
      )
      ?  (CAN_DL - DataOffset)
      :  (uint8)(Channel->SduLength)
      ;

      Context.CsTicks   = CanTp_Lok_GetCfgCsCrTicks(
         Connection
      );

        CanTp_Lok_Transmit(
            &Context
         ,  &SduInfo
         ,  &PduInfo
      );
   }

   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_Idle(
   CanTp_ChannelIdType ChannelId
){
   (void)ChannelId;
}

static void SwcApplCanTp_fptrSubState_RxRequestAccepted(CanTp_ChannelIdType ChannelId){
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_RxSduType*     Connection;
         CanTp_TickType       Value   = Channel->InitialTicks;
         CanTp_TickType       ElapsedValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[ChannelId]
      == CANTP_RX_RECEPTION_REQUEST_ACCEPTED
   ){
      Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
      if(
            ElapsedValue
         >  CanTp_Lok_GetCfgBsBrTicks(Connection)
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_RX_PDUR_CONFIRMATION
            ,  Connection->PduRPduHandleId
            ,  E_NOT_OK
         );
         CanTp_SubState[ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_RxSendFlowControlFrame(
   CanTp_ChannelIdType ChannelId
){
         Type_SwcServiceCom_stInfoPdu          PduInfo;
         Type_SwcServiceCom_stInfoPdu          SduInfo;
         CanTp_TickType       ElapsedValue;
         CanTp_ChannelIdType  TxConfirmationChannel;
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_RxSduType*     Connection;
         CanTp_TickType       Value = Channel->InitialTicks;
         boolean              IsFcReady = (Channel->FlowStatus > CANTP_FC_WAIT) ? TRUE : FALSE;
         CanTp_TxContextType  Context;

   Context.ChannelId = ChannelId;
   Context.PduRApiId = CANTP_RX_PDUR_CONFIRMATION;
   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SduInfo.SduLength  = 0;
   SduInfo.SduDataPtr = NULL_PTR;
   PduInfo.SduLength  = CANTP_DEFAULT_CAN_DL;
   PduInfo.SduDataPtr = NULL_PTR;
   SchM_Enter_CanTp_EXCLUSIVE_AREA();

   Connection = (
         CanTp_SubState[ChannelId]
      == CANTP_RX_SEND_FC
   )
   ?  (CanTp_CfgPtr->RxSdu + Channel->ActiveSduId)
   :  (const CanTp_RxSduType*)NULL_PTR
   ;

   TxConfirmationChannel = (
         Connection
      != NULL_PTR
   )
   ?  CanTp_TxConfirmationChannel[Connection->TxConfirmationId]
   :  0
   ;

   if(
         TxConfirmationChannel
      == CANTP_INVALID_CHANNEL
   ){
      Channel->BlockCfsRemaining = 0;
      Context.PduRPduHandleId = Connection->PduRPduHandleId;
      Context.PduId = Connection->TxPduId;
      Context.TxConfirmationId = Connection->TxConfirmationId;
      if(
            Channel->FlowStatus
         != CANTP_FC_OVERFLOW
      ){
         if(
               PduR_CanTpCopyRxData(
                     Context.PduRPduHandleId
                  ,  &SduInfo
                  ,  &(Context.RemBufSize)
               )
            != BUFREQ_OK
         ){
            CanTp_Lok_PduRConfirmation(
                  Context.PduRApiId
               ,  Context.PduRPduHandleId
               ,  E_NOT_OK
            );
            CanTp_SubState[Context.ChannelId] = CANTP_IDLE;
            IsFcReady = FALSE;
         }
         else{
            if(
                  Channel->FlowStatus
               != CANTP_FC_CTS
            ){
               CanTp_Lok_SetRxBlockInfo(
                     ChannelId
                  ,  Context.RemBufSize
               );
               IsFcReady = (
                     Channel->FlowStatus
                  != CANTP_FC_CTS
               )
               ?  IsFcReady
               :  TRUE
               ;
            }
         }
         if(
               (Channel->FlowStatus == CANTP_FC_WAIT)
            && (
                     (
                           ElapsedValue
                        >= CanTp_Lok_GetCfgBsBrTicks(
                              Connection
                           )
                     )
                  || (
                           Channel->FcWait
                        == 0
                     )
            )
         ){
               if(
                     Channel->FcWait
                  <  CanTp_Lok_GetRxCfgFcWaitMax(
                        Channel->ActiveSduId
                     )
               ){
                     Channel->FcWait++;
                     Channel->InitialTicks = Value;
                     IsFcReady = TRUE;
               }
               else{
                  CanTp_Lok_PduRConfirmation(
                        Context.PduRApiId
                     ,  Context.PduRPduHandleId
                     ,  E_NOT_OK
                  );
                  CanTp_SubState[Context.ChannelId] = CANTP_IDLE;
               }
            }
      }
      CanTp_Lok_FcTransmit(
            &Context
         ,  &PduInfo
         ,  IsFcReady
         ,  Value
      );
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_RxWaitForFcTransmitConfirmation(
   CanTp_ChannelIdType ChannelId
){
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_RxSduType*     Connection;
         CanTp_TickType       Value = Channel->InitialTicks;
         CanTp_TickType       ElapsedValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[ChannelId]
      == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION
   ){
      Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
      if(
            ElapsedValue
         >  CanTp_Lok_GetCfgAsArTicks(
               Connection
            )
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_RX_PDUR_CONFIRMATION
            ,  Connection->PduRPduHandleId
            ,  E_NOT_OK
         );
         CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
         CanTp_SubState[ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

static void SwcApplCanTp_fptrSubState_RxWaitForConsecutiveFrame(
   CanTp_ChannelIdType ChannelId
){
         CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   const CanTp_RxSduType*     Connection;
         CanTp_TickType       Value = Channel->InitialTicks;
         CanTp_TickType       ElapsedValue;

   CanTp_GetElapsedValue(
         &Value
      ,  &ElapsedValue
   );
   SchM_Enter_CanTp_EXCLUSIVE_AREA();
   if(
         CanTp_SubState[ChannelId]
      == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME
   ){
      Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
      if(
            ElapsedValue
         >  CanTp_Lok_GetCfgCsCrTicks(
               Connection
            )
      ){
         CanTp_Lok_PduRConfirmation(
               CANTP_RX_PDUR_CONFIRMATION
            ,  Connection->PduRPduHandleId
            ,  E_NOT_OK
         );
         CanTp_SubState[ChannelId] = CANTP_IDLE;
      }
   }
   SchM_Exit_CanTp_EXCLUSIVE_AREA();
}
#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.hpp"
const Type_SwcServiceCanTp_fptrSubState CfgSwcServiceCanTp_cafptrListSubStates[CfgSwcServiceCanTp_dNumSubStates] = {
      &SwcApplCanTp_fptrSubState_Idle
   ,  &SwcApplCanTp_fptrSubState_TxRequestAccepted
   ,  &SwcApplCanTp_fptrSubState_TxWaitForConfirmation
   ,  &SwcApplCanTp_fptrSubState_TxWaitForFlowControlFrame
   ,  &SwcApplCanTp_fptrSubState_TxSendConsecutiveFrame
   ,  &SwcApplCanTp_fptrSubState_RxRequestAccepted
   ,  &SwcApplCanTp_fptrSubState_RxSendFlowControlFrame
   ,  &SwcApplCanTp_fptrSubState_RxWaitForFcTransmitConfirmation
   ,  &SwcApplCanTp_fptrSubState_RxWaitForConsecutiveFrame
};

const Type_SwcServiceCanTp_fptrProcessFrame CfgSwcServiceCanTp_cafptrListProcessFrame[CfgSwcServiceCanTp_dNumFrameTypes] = {
      &SwcApplCanTp_fptrProcessRxFrame_Single
   ,  &SwcApplCanTp_fptrProcessRxFrame_First
   ,  &SwcApplCanTp_fptrProcessRxFrame_Consecutive
   ,  &SwcApplCanTp_fptrProcessRxFrame_FlowControl
};

const Type_SwcServiceCanTp_fptrCreateFrame CfgSwcServiceCanTp_cafptrListCreateFrame[CfgSwcServiceCanTp_dNumFrameTypes] = {
      &SwcApplCanTp_fptrCreateTxFrame_Single
   ,  &SwcApplCanTp_fptrCreateTxFrame_First
   ,  &SwcApplCanTp_fptrCreateTxFrame_Consecutive
   ,  &SwcApplCanTp_fptrCreateTxFrame_FlowControl
};

const Type_SwcServicePduR_fptrConfirmationTpLo CfgSwcServiceCanTp_cafptrListConfirmationPduR[CfgSwcServiceCanTp_dNumConfirmationTypesPduR] = {
      &infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Tx
   ,  &infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Rx
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

