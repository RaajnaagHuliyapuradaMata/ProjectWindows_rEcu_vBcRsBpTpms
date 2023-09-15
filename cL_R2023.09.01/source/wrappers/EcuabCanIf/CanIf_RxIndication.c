#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_RxIndication_Internal(
      const Can_HwType*  Mailbox
   ,  const PduInfoType* PduInfoPtr
){
   const CanIf_Cfg_Hrhtype_tst*   HrhCfg_pcst;
   const CanIf_Cfg_RxPduType_tst* RxPduCfg_pcst;

#if CANIF_CFG_UL_RX == STD_ON
   PduInfoType ULPduInfoTyp_tst;
#endif

   PduInfoType                PduInfoTemp_tst;
   uint16                     HrhId_u16          = Mailbox->Hoh;
   uint8                      Index_u8;
   uint8                      ModeChkStatus      = CANIF_PRV_INVALID_CHANNEL_MODE;
   PduIdType                  PduId_qu8          = 0;
   Can_IdType                 CanIdNoIdType_t    = Mailbox->CanId & CANIF_PRV_MSB_BIT_RESET;
   boolean                    IdFound_b          = FALSE;
   uint8                      CanIdPduType_u8    = (uint8)((Mailbox->CanId)>>CANIF_CANID_BIT_SHIFT);
   CanIf_ControllerStateType* ControllerState_ps = CanIf_Lok_ControllerState_ast + Mailbox->ControllerId;
   CanIf_NotifStatusType*     RxNotifPtr_pen     = CanIf_Lok_RxNotification_taen;

   HrhCfg_pcst = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[HrhId_u16];

   if(
         (uint8)CANIF_CS_STARTED
      == (
               (
                     ControllerState_ps->Ctrl_Pdu_mode
                  &  BIT_MASK_PDU_MODE
               )
            >> CANIF_Ctrl_BIT_SHIFT
         )
   ){
      if(
            (
                  (uint8)CANIF_TX_OFFLINE
               == (
                        ControllerState_ps->Ctrl_Pdu_mode
                     &  BIT_MASK_CTRL_MODE
                  )
            )
         || (
                  (uint8)CANIF_ONLINE
               == (
                        ControllerState_ps->Ctrl_Pdu_mode
                     &  BIT_MASK_CTRL_MODE
                  )
            )
      ){
         ModeChkStatus = CANIF_PRV_VALID_CHANNEL_MODE;
      }
      if(
            ModeChkStatus
         == CANIF_PRV_VALID_CHANNEL_MODE
      ){
         Index_u8 = 0;
         switch(
            HrhCfg_pcst->HrhInfo_e
         ){
            case CANIF_PRV_FULL_E:
               PduId_qu8 = HrhCfg_pcst->PduIdx_t;
               do{
                  RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;
                  if(
                        (
                              (
                                    RxPduCfg_pcst->CanIdtype_u8
                                 &  CANIF_PRV_CANID_TYPE_MASK
                              )
                           == (
                                    (
                                          RxPduCfg_pcst->CanIdtype_u8
                                       >> CANIF_PRV_FOUR
                                    )
                                 &  CanIdPduType_u8
                              )
                        )
                     && (CanIdNoIdType_t == RxPduCfg_pcst->RxPduCanId)
                  ){
                     IdFound_b = TRUE;
                     break;
                  }
                  PduId_qu8++;
                  Index_u8++;
               }while(
                     HrhCfg_pcst->NumRxPdus_u32
                  >= Index_u8
               );
               break;
            
            default:
               IdFound_b = FALSE;
               break;
         }
      }
   }
   if(
         IdFound_b
      == TRUE
   ){
      PduInfoTemp_tst.SduLength = PduInfoPtr->SduLength;

#if CANIF_CFG_UL_RX == STD_ON
      ULPduInfoTyp_tst.SduLength= PduInfoTemp_tst.SduLength;
#endif
      PduInfoTemp_tst.SduDataPtr =(uint8*)(PduInfoPtr->SduDataPtr);

#if CANIF_CFG_UL_RX == STD_ON
      ULPduInfoTyp_tst.SduDataPtr= PduInfoTemp_tst.SduDataPtr;
#endif

      if(
            (CANIF_READ_NOTIFSTATUS_DATA == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8)
         || (CANIF_READ_NOTIFSTATUS      == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8)
      ){
         *(RxNotifPtr_pen + PduId_qu8) = CANIF_TX_RX_NOTIFICATION;
      }
      if(
            RxPduCfg_pcst->IndexForUL_u8
         != CANIF_PRV_NO_UL
      ){
#if CANIF_CFG_UL_RX == STD_ON
         if(
               RxPduCfg_pcst->IndexForUL_u8
            != CANIF_PRV_SIX
         ){
            (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
         }
         else{
            (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
         }
#endif
      }
   }
}

Std_ReturnType CanIf_XCore_LocalCore_RxIndication(
      const CanIf_Cfg_RxPduType_tst* CanIf_RXPduConfig_pst
   ,  const PduInfoType*             CanIf_ULPduinfo_pst
){
   Std_ReturnType lretval = E_OK;
#if CANIF_CFG_UL_RX == STD_ON
   const CanIf_Cfg_RxPduType_tst* RxPduConfig_pst = CanIf_RXPduConfig_pst;

   CanIf_Lok_ConfigSet_tpst->RxAutosarUL_Ptr[RxPduConfig_pst->IndexForUL_u8].CanIfRxPduIndicationName(
         RxPduConfig_pst->RxPduTargetId_t
      ,  CanIf_ULPduinfo_pst
   );
#endif
   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

