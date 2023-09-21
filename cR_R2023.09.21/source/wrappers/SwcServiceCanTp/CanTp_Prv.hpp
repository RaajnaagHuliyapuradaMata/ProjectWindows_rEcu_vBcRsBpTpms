#pragma once
/******************************************************************************/
/* File   : CanTp_Prv.hpp                                                     */
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
#include "CanTp.hpp"
#include "CanTp_Types.hpp"
#include "CanTp_Cfg_SchM.hpp"
#include "PduR_CanTp.hpp"
#include "CanIf.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANTP_SF_HIGHNIBBLE                                              (0x00u)
#define CANTP_FF_HIGHNIBBLE                                              (0x10u)
#define CANTP_CF_HIGHNIBBLE                                              (0x20u)
#define CANTP_FC_HIGHNIBBLE                                              (0x30u)
#define CANTP_DEFAULT_CAN_DL                                                (8u)
#define CANTP_DLCERROR                                                   (0xFFu)
#define CANTP_NO_ERROR                                                      (0u)
#define CANTP_CF_PCISIZE                                                    (1u)
#define CANTP_FC_PCISIZE                                                    (3u)
#define CANTP_NPCI_SFCAN                                                    (0u)
#define CANTP_NPCI_SFCANFD                                                  (1u)
#define CANTP_NPCI_FFCAN                                                    (2u)
#define CANTP_NPCI_FFCANFD                                                  (3u)
#define CANTP_NPCI_CF                                                       (4u)
#define CANTP_NPCI_FC                                                       (5u)
#define CANTP_NPCI_INVALID                                                  (6u)
#define CANTP_MAXFFDL                                                   (0xFFFu)
#define CANTP_MAXFDFFDL                                                (0xFFFFu)
#define CANTP_MAXBLOCKSIZE                                               (0xFFu)
#define CANTP_CANDL_ARRAY_SIZE                                             (65u)
#define CANTP_PCI_ARRAY_SIZE                                                (6u)
#define CANTP_ADDRESS_ARRAY_SIZE                                            (5u)
#define CANTP_STANDARD                                                      (0u)
#define CANTP_EXTENDED                                                      (1u)
#define CANTP_MIXED                                                         (2u)
#define CANTP_MILLISEC_MAX_RANGE                                         (0x7Fu)
#define CANTP_MICROSEC_MIN_RANGE                                         (0xF1u)
#define CANTP_MICROSEC_MAX_RANGE                                         (0xF9u)
#define CANTP_MAX_BS_VALUE                                               (0xFFu)
#define CANTP_TC_DISABLED                                                (0x10u)
#define CANTP_PADDINGON                                                  (0x08u)
#define CANTP_FUNCTIONAL                                                 (0x04u)
#define CANTP_FC_DISABLED                                                (0x02u)
#define CANTP_FD_ENABLED                                                 (0x01u)
#define CANTP_SINGLE_FRAME                                               (0x00u)
#define CANTP_FIRST_FRAME                                                (0x01u)
#define CANTP_CONSECUTIVE_FRAME                                          (0x02u)
#define CANTP_FLOWCONTROL_FRAME                                          (0x03u)
#define CfgSwcServiceCanTp_dNumFrameTypes                                (0x04u)
#define CANTP_FRAMETYPE_OFFSET                                           (0x04u)
#define CANTP_LOWERNIBBLE_MASK                                           (0x0Fu)
#define CANTP_INVALID_DL                                                 (0xFFu)
#define CANTP_INVALID_NOTIFY_VALUE                                       (0xFFu)
#define CANTP_INVALID_CHANNEL                           (CANTP_MAX_CHANNEL_SIZE)
#define CANTP_IDLE                                                          (0u)
#define CANTP_TRANSMISSION                                                  (1u)
#define CANTP_RECEPTION                                                     (2u)
#define CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED                              (1u)
#define CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION                             (2u)
#define CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME                                 (3u)
#define CANTP_TX_SEND_CONSECUTIVE_FRAME                                     (4u)
#define CANTP_RX_RECEPTION_REQUEST_ACCEPTED                                 (5u)
#define CANTP_RX_SEND_FC                                                    (6u)
#define CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION                           (7u)
#define CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME                                 (8u)
#define CfgSwcServiceCanTp_dNumSubStates                                    (9u)
#define CANTP_TX_PDUR_CONFIRMATION                                          (0u)
#define CANTP_RX_PDUR_CONFIRMATION                                          (1u)
#define CfgSwcServiceCanTp_dNumConfirmationTypesPduR                        (2u)
#define CANTP_TRIGGER_TX_CONFIRMATION                                       (0u)
#define CANTP_TRIGGER_RX_INDICATION                                         (1u)
#define CANTP_NUMBER_OF_TRIGGER_POINTS                                      (2u)
#define CANTP_FC_CTS                                                        (0u)
#define CANTP_FC_WAIT                                                       (1u)
#define CANTP_FC_OVERFLOW                                                   (2u)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define CanTp_Lok_PduRConfirmation(Api, id, result)  CfgSwcServiceCanTp_cafptrListConfirmationPduR[Api](id, result)
#define CanTp_Lok_ActivateMainFunction(TriggerPoint) CanTp_SchMTriggerApis[TriggerPoint]()
#define CanTp_Lok_ProcessFrame(Context, PduInfoPtr)  CfgSwcServiceCanTp_cafptrListProcessFrame[(Context)->FrameType](Context, PduInfoPtr)
#define CanTp_Lok_FrameType(id)                      CanTp_PciFrameType[CanTp_Channel[id].PciId]
#define CanTp_Lok_CreateFrame(id, PduInfoPtr)        CfgSwcServiceCanTp_cafptrListCreateFrame[CanTp_Lok_FrameType(id)](id, PduInfoPtr)
#define CanTp_Lok_ExecuteState(ChannelId)            CfgSwcServiceCanTp_cafptrListSubStates[CanTp_SubState[ChannelId]](ChannelId)
#define CanTp_Lok_GetTxChannelId(id)                 CanTp_CfgPtr->TxSdu[id].ChannelId
#define CanTp_Lok_GetRxChannelId(id)                 CanTp_CfgPtr->RxSdu[id].ChannelId
#define CanTp_Lok_GetState(ChannelId)                CanTp_State[CanTp_SubState[ChannelId]]
#define CanTp_Lok_GetRxCfgParam(id, param)           CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].Param[param]
#define CanTp_Lok_GetRxCfgFcWaitMax(id)              CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].FcWaitMax
#define CanTp_Lok_GetCfgAsArTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].AsArTicks
#define CanTp_Lok_GetCfgBsBrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].BsBrTicks
#define CanTp_Lok_GetCfgCsCrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].CsCrTicks
#define CanTp_Lok_GetTxActiveBits(id)                CanTp_CfgPtr->TxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#define CanTp_Lok_GetRxActiveBits(id)                CanTp_CfgPtr->RxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#define CanTp_Lok_RxParamInit()
#define CanTp_Lok_GetTxDl(Connection)                ((Connection)->TX_DL)
#define CanTp_Lok_GetCanDl(FrameLength)              (CanTp_CanDlTable[FrameLength])
#define CanTp_Lok_GetRxDl(ChannelId)                 (CanTp_Channel[ChannelId].RX_DL)
#define CanTp_Lok_SetRxDl(ChannelId, Value)          (CanTp_Channel[ChannelId].RX_DL = (Value))
#define CanTp_Lok_IsRxDlInValid(RX_DL)               (((RX_DL) != 0x08) && ((RX_DL) != 0x0C) && ((RX_DL) != 0x10) &&\
                                                      ((RX_DL) != 0x14) && ((RX_DL) != 0x18) && ((RX_DL) != 0x20) &&\
                                                      ((RX_DL) != 0x30) && ((RX_DL) != 0x40))

#define CanTp_Lok_QInit()
#define CanTp_Lok_PutInQ(ChannelId)
#define CanTp_Lok_GetFromQ(ChannelId)
#define CanTp_Lok_BurstMainFunction(Id, Point)
#define CanTp_IncrementCounter()                      (CanTp_MainFunctionTicks++)
#define CanTp_Lok_BuildBugOn(condition)              ((void)sizeof(char[1 - 2*!!(condition)]))

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef Std_ReturnType (*Type_SwcServiceCanTp_fptrCreateFrame)(CanTp_ChannelIdType ChannelId, Type_SwcServiceCom_stInfoPdu *PduInfoPtr);

typedef struct{
   boolean             IsFunctional;
   boolean             IsPaddingOn;
   boolean             IsFdEnabled;
   uint8               Address;
   uint8               FrameType;
   uint8               FlowStatus;
   uint8               SN;
   uint8               DataOffset;
   uint8               AddressFormatId;
   uint8               AddressSize;
   uint8               CAN_DL;
   CanTp_ChannelIdType ChannelId;
   CanTp_SduIdType     SduId;
   Type_SwcServiceCom_tIdPdu           PduId;
   Type_SwcServiceCom_tIdPdu           PduRPduHandleId;
   Type_SwcServiceCom_tLengthPdu       SduLength;
}CanTp_RxContextType;

typedef struct{
   uint8               PduRApiId;
   uint8               PayLoadLength;
   CanTp_ChannelIdType ChannelId;
   Type_SwcServiceCom_tIdPdu           TxConfirmationId;
   Type_SwcServiceCom_tIdPdu           PduId;
   Type_SwcServiceCom_tIdPdu           PduRPduHandleId;
   Type_SwcServiceCom_tLengthPdu       RemBufSize;
   CanTp_TickType      Value;
   CanTp_TickType      ElapsedValue;
   CanTp_TickType      CsTicks;
}CanTp_TxContextType;

typedef void (*Type_SwcServiceCanTp_fptrProcessFrame)(const CanTp_RxContextType *Context, const Type_SwcServiceCom_stInfoPdu *PduInfoPtr);

typedef struct{
   uint8 Param[2];
}CanTp_ParamPairType;

typedef void (*Type_SwcServiceCanTp_fptrSubState)(CanTp_ChannelIdType ChannelId);

typedef struct{
   uint8           RX_DL;
   uint8           PciId;
   uint8           FlowStatus;
   uint8           SN;
   uint8           BS;
   CanTp_SduIdType ActiveSduId;
   uint16          FcWait;
   Type_SwcServiceCom_tLengthPdu   BlockCfsRemaining;
   Type_SwcServiceCom_tLengthPdu   SduLengthRemaining;
   Type_SwcServiceCom_tLengthPdu   SduLength;
   CanTp_TickType  InitialTicks;
   CanTp_TickType  STminTicks;
}CanTp_ChannelType;

typedef CanTp_ChannelType *CanTp_ChannelPtrType;
typedef void (*Type_SwcServicePduR_fptrConfirmationTpLo)(Type_SwcServiceCom_tIdPdu id, Std_ReturnType result);
typedef void (*CanTp_SchMTriggerApiType)(void);
typedef Std_ReturnType (*CanTp_CanIfTransmitApiType)(Type_SwcServiceCom_tIdPdu TxPduId, const Type_SwcServiceCom_stInfoPdu* PduInfoPtr);

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.hpp"
extern CanTp_ChannelType CanTp_Channel[CANTP_MAX_CHANNEL_SIZE];
extern CanTp_ChannelIdType CanTp_TxConfirmationChannel[CANTP_MAX_NPDU_LENGTH];
extern volatile CanTp_TickType CanTp_MainFunctionTicks;
extern const Type_CfgSwcServiceCanTp_st *CanTp_CfgPtr;
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"
extern uint8 CanTp_SubState[CANTP_MAX_CHANNEL_SIZE];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.hpp"
extern const uint8 CanTp_State[CfgSwcServiceCanTp_dNumSubStates];
extern const uint8 CanTp_AddressSize[CANTP_ADDRESS_ARRAY_SIZE];
extern const uint8 CanTp_PciFrameType[CANTP_PCI_ARRAY_SIZE];
extern const uint8 CanTp_PciSize[CANTP_PCI_ARRAY_SIZE];
extern const uint8 CanTp_CanDlTable[CANTP_CANDL_ARRAY_SIZE];
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.hpp"
extern const Type_SwcServiceCanTp_fptrProcessFrame CfgSwcServiceCanTp_cafptrListProcessFrame[CfgSwcServiceCanTp_dNumFrameTypes];
extern const Type_SwcServiceCanTp_fptrCreateFrame CfgSwcServiceCanTp_cafptrListCreateFrame[CfgSwcServiceCanTp_dNumFrameTypes];
extern const Type_SwcServiceCanTp_fptrSubState CfgSwcServiceCanTp_cafptrListSubStates[CfgSwcServiceCanTp_dNumSubStates];
extern const Type_SwcServicePduR_fptrConfirmationTpLo  CfgSwcServiceCanTp_cafptrListConfirmationPduR[CfgSwcServiceCanTp_dNumConfirmationTypesPduR];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
LOCAL_INLINE void CanTp_GetElapsedValue(
      CanTp_TickType* Value
   ,  CanTp_TickType* ElapsedValue
){
   CanTp_TickType ValueIn = *Value;
   *Value = CanTp_MainFunctionTicks;
   *ElapsedValue = *Value - ValueIn;
}

LOCAL_INLINE boolean CanTp_Lok_GetBit(
      uint8 Value
   ,  uint8 Mask
){
    return ((Value & Mask) == Mask) ? TRUE : FALSE;
}

LOCAL_INLINE void CanTp_Lok_ArrayInit(
      uint8* ArrayPtr
   ,  uint32 Length
   ,  uint8  Item
){
   uint32 i;
   for(i = 0; i < Length; i++){
        ArrayPtr[i] = Item;
   }
}

LOCAL_INLINE boolean CanTp_Lok_IsNoDevError(
      uint32 id
   ,  uint8  ApiId
   ,  uint8  CanTpEInvalidId
){
   uint8 ErrorId;
   uint32 TotalIds = 0;
   boolean Status = TRUE;

   if(CanTp_MainState != CANTP_ON){
        ErrorId = CANTP_E_UNINIT;
   }
   else{
      switch(ApiId){
         case CANTP_CHANGEPARAMETER:
         case CANTP_READPARAMETER:
         case CANTP_CANCELRECEIVE:
            TotalIds = CanTp_CfgPtr->NumberOfRxSdus;
            break;

         case CANTP_TRANSMIT:
         case CANTP_CANCELTRANSMIT:
            TotalIds = CanTp_CfgPtr->NumberOfTxSdus;
            break;

         case CANTP_TXCONFIRMATION:
         case CANTP_TRIGGERTRANSMIT:
            TotalIds = CanTp_CfgPtr->NumberOfTxPdus;
            break;

         case CANTP_RXINDICATION:
            TotalIds = CanTp_CfgPtr->NumberOfRxPdus;
            break;
         default:
            break;
      }
      if(id >= TotalIds){
         ErrorId = CanTpEInvalidId;
      }
      else{
         ErrorId = CANTP_NO_ERROR;
      }
   }
   if(ErrorId != CANTP_NO_ERROR){
        Status = FALSE;
   }
   return Status;
}

LOCAL_INLINE Type_SwcServiceCom_tLengthPdu CanTp_Lok_GetTxBlockCfs(
   CanTp_ChannelIdType ChannelId
){
   uint8 PayLoadLength;
   const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId;
   uint8 TX_DL = CanTp_Lok_GetTxDl(Connection);
   uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
   Type_SwcServiceCom_tLengthPdu SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;
   PayLoadLength = TX_DL - CANTP_CF_PCISIZE - AddressSize;
   return ((SduLength % PayLoadLength) == 0u) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1u);
}

LOCAL_INLINE Type_SwcServiceCom_tLengthPdu CanTp_Lok_GetRxBlockCfs(
   CanTp_ChannelIdType ChannelId
){
   uint8 PayLoadLength;
   const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + CanTp_Channel[ChannelId].ActiveSduId;
   uint8 RX_DL = CanTp_Lok_GetRxDl(ChannelId);
   uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
   Type_SwcServiceCom_tLengthPdu SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;
   PayLoadLength = RX_DL - CANTP_CF_PCISIZE - AddressSize;
   return((SduLength % PayLoadLength) == 0u) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1u);
}

LOCAL_INLINE void CanTp_Lok_TxPciInit(
            uint8*       PciId
   ,        Type_SwcServiceCom_tIdPdu    CanTpTxSduId
   ,  const Type_SwcServiceCom_stInfoPdu* CanTpTxInfoPtr
){
   const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
   uint8 AddressLength;
   uint8 TX_DL = CanTp_Lok_GetTxDl(Connection);
   AddressLength = CanTp_AddressSize[Connection->AddressFormatId];
   if((CanTpTxInfoPtr->SduLength + AddressLength + 1u) <= CANTP_DEFAULT_CAN_DL){
        *PciId = CANTP_NPCI_SFCAN;
   }
   else if((TX_DL > CANTP_DEFAULT_CAN_DL) && ((CanTpTxInfoPtr->SduLength + AddressLength + 2u) <= TX_DL)){
        *PciId = CANTP_NPCI_SFCANFD;
   }
   else if((TX_DL > CANTP_DEFAULT_CAN_DL) && (CanTpTxInfoPtr->SduLength > CANTP_MAXFFDL)){
        *PciId = CANTP_NPCI_FFCANFD;
   }
   else{
        *PciId = CANTP_NPCI_FFCAN;
   }
}

LOCAL_INLINE void CanTp_Lok_CanIfTransmit(
      const CanTp_TxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         CanIfTxInfoPtr
){
   Type_SwcServiceCom_stInfoPdu CanIfTxInfo;
   uint8 SduBuffer[CANTP_MAX_NPDU_LENGTH];
   CanIfTxInfo.SduLength = CanIfTxInfoPtr->SduLength;
   CanIfTxInfo.SduDataPtr = CanIfTxInfoPtr->SduDataPtr;
   CanIfTxInfo.SduDataPtr = SduBuffer;
   if(CanTp_Lok_CreateFrame(Context->ChannelId, &CanIfTxInfo) == E_OK){
      CanTp_TxConfirmationChannel[Context->TxConfirmationId] = Context->ChannelId;
      if(
            CanIf_Transmit(
                  Context->PduId
               ,  &CanIfTxInfo
            )
         != E_OK
      ){
         CanTp_Lok_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
         CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
         CanTp_TxConfirmationChannel[Context->TxConfirmationId] = CANTP_INVALID_CHANNEL;
      }
   }
}

LOCAL_INLINE void CanTp_Lok_FcTransmit(
      const CanTp_TxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         CanIfTxInfoPtr
   ,        boolean              IsFcTransmitReady
   ,        CanTp_TickType       Value
){
   if(IsFcTransmitReady && (CanTp_SubState[Context->ChannelId] == CANTP_RX_SEND_FC)){
      CanTp_Channel[Context->ChannelId].InitialTicks = Value;
      CanTp_Channel[Context->ChannelId].PciId = CANTP_NPCI_FC;
      CanTp_SubState[Context->ChannelId] = CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION;
      CanTp_Lok_CanIfTransmit(Context, CanIfTxInfoPtr);
   }
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_GetConnectionAcceptance(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
         Std_ReturnType   RetValue = E_NOT_OK;
         uint8            NewChannelState = CANTP_IDLE;
         uint8            OldChannelState = CanTp_Lok_GetState(Context->ChannelId);
   (void)PduInfoPtr;
   if(OldChannelState == CANTP_IDLE){
      NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
   }
   else{
      if((OldChannelState == CANTP_RECEPTION)&&(CanTp_Channel[Context->ChannelId].ActiveSduId == Context->SduId)){
         NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
         CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
      }
   }
   if(NewChannelState == CANTP_RX_RECEPTION_REQUEST_ACCEPTED){
      CanTp_SubState[Context->ChannelId] = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
      RetValue = E_OK;
   }
   return RetValue;
}

LOCAL_INLINE void CanTp_Lok_SetTxBlockInfo(
      const CanTp_RxContextType* Context
   ,  const Type_SwcServiceCom_stInfoPdu*         PduInfoPtr
){
   uint8 *SduDataPtr;
   CanTp_ChannelPtrType Channel = &CanTp_Channel[Context->ChannelId];
   Type_SwcServiceCom_tLengthPdu BlockCfsRemaining;
   SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;
   if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS)
   {
      Channel->BS = *SduDataPtr;
      SduDataPtr++;
      if(*SduDataPtr <= CANTP_MILLISEC_MAX_RANGE){
         Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(*SduDataPtr * 1000u);
      }
      else if((*SduDataPtr < CANTP_MICROSEC_MIN_RANGE) || (*SduDataPtr > CANTP_MICROSEC_MAX_RANGE)){
         Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(127000u);
      }
      else{
         Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks((*SduDataPtr & CANTP_LOWERNIBBLE_MASK) * 100u);
      }
   }
   BlockCfsRemaining = CanTp_Lok_GetTxBlockCfs(Context->ChannelId);
   if((Channel->BS == 0u) || (Channel->BS > BlockCfsRemaining)){
      Channel->BlockCfsRemaining = BlockCfsRemaining;
   }
   else{
      Channel->BlockCfsRemaining = (uint16)Channel->BS;
   }
}

LOCAL_INLINE uint8 CanTp_Lok_GetRxParam(
      CanTp_SduIdType id
   ,  TPParameterType parameter
){
   uint8 value;
   value = (parameter == TP_STMIN)? (0u) : (1u);
   return CanTp_Lok_GetRxCfgParam(id, value);
}

LOCAL_INLINE void CanTp_Lok_SetRxBlockInfo(
            CanTp_ChannelIdType ChannelId
   ,  const Type_SwcServiceCom_tLengthPdu       RemBufSize
){
   uint8 BSMax;
   Type_SwcServiceCom_tLengthPdu BlockCfsRemaining;
   CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
   uint8 BS = Channel->BS;
   const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
   Type_SwcServiceCom_tLengthPdu OneFramePayloadLength = CanTp_Lok_GetRxDl(ChannelId) - CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;
   if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS)
   {
      BSMax = CanTp_Lok_GetRxParam(Channel->ActiveSduId, TP_BS);
      if(RemBufSize >= Channel->SduLengthRemaining){
         BS = BSMax;
      }
      else{
         BS = (uint8)(RemBufSize/OneFramePayloadLength);
         BS = ((BSMax != 0u) && (BS > BSMax)) ? BSMax : BS;
      }
   }
   if(
      ((BS == 0) && (RemBufSize < Channel->SduLengthRemaining)) ||
      ((BS != 0) && (RemBufSize < (BS * OneFramePayloadLength)) && (RemBufSize < Channel->SduLengthRemaining))
   ){
      Channel->FlowStatus = CANTP_FC_WAIT;
   }
   else{
      BlockCfsRemaining = CanTp_Lok_GetRxBlockCfs(ChannelId);
      Channel->BlockCfsRemaining = (BS != 0u) ? BS : BlockCfsRemaining;
      Channel->FlowStatus = CANTP_FC_CTS;
      Channel->STminTicks = 0;
   }
   Channel->BS = BS;
}

LOCAL_INLINE void CanTp_Lok_FcTxConfirmation(
   CanTp_ChannelIdType ChannelId
){
   const CanTp_ChannelType *Channel = CanTp_Channel + ChannelId;
   const CanTp_RxSduType *RxConnection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
   switch(Channel->FlowStatus){
      case CANTP_FC_CTS:
         CanTp_SubState[ChannelId] = CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME;
         break;

      case CANTP_FC_WAIT:
         CanTp_SubState[ChannelId] = (Channel->SduLengthRemaining > 0u) ? CANTP_RX_SEND_FC : CANTP_IDLE;
         break;

      case CANTP_FC_OVERFLOW:
         CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, RxConnection->PduRPduHandleId, E_NOT_OK);
         CanTp_SubState[ChannelId] = CANTP_IDLE;
         break;

      default:
         break;
   }
}

LOCAL_INLINE void CanTp_Lok_PrepareFcTransmit(
   CanTp_ChannelIdType ChannelId
){
   if(CanTp_Channel[ChannelId].BlockCfsRemaining == 0u){
      CanTp_Channel[ChannelId].FcWait = 0;
      CanTp_Channel[ChannelId].FlowStatus = CANTP_FC_WAIT;
      CanTp_SubState[ChannelId] = CANTP_RX_SEND_FC;
   }
}

LOCAL_INLINE void CanTp_Lok_PrepareFcRecieve(
   CanTp_ChannelIdType ChannelId
){
   CanTp_SubState[ChannelId] = CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME;
   CanTp_Channel[ChannelId].PciId = CANTP_NPCI_FC;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

