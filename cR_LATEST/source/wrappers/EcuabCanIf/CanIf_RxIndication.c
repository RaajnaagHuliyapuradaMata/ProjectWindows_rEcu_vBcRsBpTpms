#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_RxIndication_Internal( P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_DATA)PduInfoPtr
){
   P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst;
   P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

#if CANIF_CFG_UL_RX == STD_ON
   VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC) ULPduInfoTyp_tst;
#endif

   VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC) PduInfoTemp_tst;
   VAR(uint8,AUTOMATIC)Index_u8;
   VAR(uint8,AUTOMATIC)ModeChkStatus = CANIF_PRV_INVALID_CHANNEL_MODE;
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)PduId_qu8;
   VAR(Can_IdType,AUTOMATIC)CanIdNoIdType_t;
   VAR(boolean, AUTOMATIC) IdFound_b = FALSE;
   VAR(uint8, AUTOMATIC) CanIdPduType_u8;
   P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) ControllerState_ps;
   VAR (CanIf_ControllerModeType, AUTOMATIC) DeviceMode_tst;
   VAR (CanIf_PduModeType, AUTOMATIC) ChannelMode_tst;

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
   P2VAR(CanIf_NotifStatusType,AUTOMATIC, AUTOMATIC) RxNotifPtr_pen;
   RxNotifPtr_pen = CanIf_Lok_RxNotification_taen;
#endif

   CanIdNoIdType_t = Mailbox->CanId & CANIF_PRV_MSB_BIT_RESET;
   CanIdPduType_u8 = (uint8)((Mailbox->CanId)>>CANIF_CANID_BIT_SHIFT);
   HrhCfg_pcst = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[Mailbox->Hoh];
   ControllerState_ps= CanIf_Lok_ControllerState_ast + Mailbox->ControllerId;
   SchM_Enter_CanIf_ControllerState();
   DeviceMode_tst = ControllerState_ps->DeviceMode;
   ChannelMode_tst = ControllerState_ps->ChannelMode;
   SchM_Exit_CanIf_ControllerState();

   if(CANIF_CS_STARTED == DeviceMode_tst){
      if((CANIF_TX_OFFLINE == ChannelMode_tst)||(CANIF_ONLINE == ChannelMode_tst)){
         ModeChkStatus = CANIF_PRV_VALID_CHANNEL_MODE;
      }

#if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_OFF)
      if(ModeChkStatus == CANIF_PRV_VALID_CHANNEL_MODE)
#endif
        {
            Index_u8 = 0;
            switch(HrhCfg_pcst->HrhInfo_e){
                case CANIF_PRV_FULL_E:{
                    PduId_qu8 = HrhCfg_pcst->PduIdx_t;
                    do{
                        RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;
                            if((((RxPduCfg_pcst->CanIdtype_u8)&(CANIF_PRV_CANID_TYPE_MASK))==(((RxPduCfg_pcst->CanIdtype_u8)>>CANIF_PRV_FOUR)& CanIdPduType_u8))&&(CanIdNoIdType_t == RxPduCfg_pcst->RxPduCanId))
                            {
                                IdFound_b = TRUE;
                                break;
                            }
                        PduId_qu8++;
                        Index_u8++;
                    }while(HrhCfg_pcst->NumRxPdus_u32>= Index_u8);
                }break;
                default:
                    IdFound_b = FALSE;
                    break;
             }
        }
   }
   if(IdFound_b == TRUE){
                    PduInfoTemp_tst.SduLength = PduInfoPtr->SduLength;
#if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduLength= PduInfoTemp_tst.SduLength;
#endif

                    PduInfoTemp_tst.SduDataPtr =(uint8*)(PduInfoPtr->SduDataPtr);
#if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduDataPtr= PduInfoTemp_tst.SduDataPtr;
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
                      if((CANIF_READ_NOTIFSTATUS_DATA == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8) || (CANIF_READ_NOTIFSTATUS == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8)
                      ){
                          *(RxNotifPtr_pen + PduId_qu8) = CANIF_TX_RX_NOTIFICATION;
                      }
#endif
                    if(RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_NO_UL){
#if CANIF_CFG_UL_RX == STD_ON
                            if(RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_SIX){
                                (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                            }
                            else{
                                (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                            }
#endif
                    }
   }
}

FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_RxIndication(P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_RXPduConfig_pst
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_CFG_CONST) CanIf_ULPduinfo_pst
){
   Std_ReturnType lretval = E_OK;
   P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduConfig_pst;
   RxPduConfig_pst = CanIf_RXPduConfig_pst;

#if CANIF_CFG_UL_RX == STD_ON
   CanIf_Lok_ConfigSet_tpst->RxAutosarUL_Ptr[RxPduConfig_pst->IndexForUL_u8].CanIfRxPduIndicationName(RxPduConfig_pst->RxPduTargetId_t, CanIf_ULPduinfo_pst);
#endif

   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

