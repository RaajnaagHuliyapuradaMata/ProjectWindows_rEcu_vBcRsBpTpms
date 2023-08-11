

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

void CanIf_RxIndication_Internal( const Can_HwType * Mailbox,
        const PduInfoType * PduInfoPtr)
{
    const CanIf_Cfg_Hrhtype_tst * HrhCfg_pcst;
    const CanIf_Cfg_RxPduType_tst * RxPduCfg_pcst;

    #if CANIF_CFG_UL_RX == STD_ON
    PduInfoType ULPduInfoTyp_tst;
    #endif

    PduInfoType PduInfoTemp_tst;
    uint16 HrhId_u16;
    uint8 Index_u8;
    uint8 ModeChkStatus = CANIF_PRV_INVALID_CHANNEL_MODE;
    PduIdType PduId_qu8 =0;

    #if (CANIF_BASIC_CAN_SUPPORT == STD_ON)
    uint8_least RngLstPduId_qu8;
    #endif

    Can_IdType CanIdNoIdType_t;
    boolean IdFound_b = FALSE;
     uint8 CanIdPduType_u8;
#if( CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON )
     uint8 lCtrlCustId_u8;
#endif
     CanIf_ControllerStateType* ControllerState_ps;

    #if(CANIF_CFG_DLC_CHECK == STD_ON)
    const CanIf_CallbackFuncType * CallBackPtr_Temp;
    PduLengthType lConfigRxPduDlc;
    #endif

    CanIf_NotifStatusType * RxNotifPtr_pen;
    RxNotifPtr_pen = CanIf_Lok_RxNotification_taen;

    #if(CANIF_CFG_DLC_CHECK == STD_ON)
    CallBackPtr_Temp = &CanIf_Callback;
    #endif

    CANIF_DET_REPORT_ERROR_VOID_RET(CanIf_Lok_InitStatus_b == FALSE, CANIF_RX_INDICATION_SID, CANIF_E_UNINIT);
    CANIF_DET_REPORT_ERROR_VOID_RET(((Mailbox == NULL_PTR) || (PduInfoPtr == NULL_PTR) ||((PduInfoPtr != NULL_PTR) &&
            (PduInfoPtr->SduDataPtr == NULL_PTR))),CANIF_RX_INDICATION_SID, CANIF_E_PARAM_POINTER);
    CANIF_DET_REPORT_ERROR_VOID_RET(Mailbox->ControllerId>= CANIF_TOTAL_CTRLS ,CANIF_RX_INDICATION_SID, CANIF_E_PARAM_POINTER);

    ControllerState_ps= CanIf_Lok_ControllerState_ast + Mailbox->ControllerId;

#if( CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON )
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[Mailbox->ControllerId];
#endif
    CANIF_DET_REPORT_ERROR_VOID_RET((lCtrlCustId_u8 == 0xFFu), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_CONTROLLERID)
    CANIF_DET_REPORT_ERROR_VOID_RET((Mailbox->Hoh>=CANIF_CFG_TOTAL_HOH_NUM), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_HOH);

    HrhId_u16 = Mailbox->Hoh;
    CanIdNoIdType_t = Mailbox->CanId & CANIF_PRV_MSB_BIT_RESET;
    CANIF_DET_REPORT_ERROR_VOID_RET((CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[HrhId_u16] ==  CANIF_INVALID_ID), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_HOH);
    CanIdPduType_u8 = (uint8)((Mailbox->CanId)>>CANIF_CANID_BIT_SHIFT);
    CANIF_DET_REPORT_ERROR_VOID_RET((((CanIdPduType_u8 == CANIF_ZERO)||(CanIdPduType_u8 == CANIF_ONE))&& (CanIdNoIdType_t > CANIF_CAN_STD_VAL))||
                    (((CanIdPduType_u8 == CANIF_TWO)||(CanIdPduType_u8 == CANIF_THREE))&& (CanIdNoIdType_t > CANIF_CAN_XTD_VAL)), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_CANID);
    CANIF_DET_REPORT_ERROR_VOID_RET((((CanIdPduType_u8 == CANIF_ZERO)||(CanIdPduType_u8 == CANIF_TWO))&& (PduInfoPtr->SduLength > 8u))||
                        (((CanIdPduType_u8 == CANIF_ONE)||(CanIdPduType_u8 == CANIF_THREE))&& (PduInfoPtr->SduLength > 64u)), CANIF_RX_INDICATION_SID, CANIF_E_DATA_LENGTH_MISMATCH);
    HrhCfg_pcst = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[HrhId_u16];

    #if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON && CANIF_PUBLIC_BUSOFF_RECOVERY_FROM_RXINDICATION == STD_ON )
    ControllerState_ps->CanIf_TxCnfmStatus = CANIF_TX_RX_NOTIFICATION;
    #endif

    if((uint8)CANIF_CS_STARTED == (((ControllerState_ps->Ctrl_Pdu_mode)& BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT))
    {
        if(((uint8)CANIF_TX_OFFLINE == ((ControllerState_ps->Ctrl_Pdu_mode)& BIT_MASK_CTRL_MODE))||((uint8)CANIF_ONLINE == ((ControllerState_ps->Ctrl_Pdu_mode)& BIT_MASK_CTRL_MODE)))
        {
            ModeChkStatus = CANIF_PRV_VALID_CHANNEL_MODE;
        }

        if(ModeChkStatus == CANIF_PRV_VALID_CHANNEL_MODE)
        {
            Index_u8 = 0;
            switch(HrhCfg_pcst->HrhInfo_e)
            {
                case CANIF_PRV_FULL_E:
                {
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
    if(IdFound_b == TRUE)
    {
        {
            {
                #if ( CANIF_CFG_DLC_CHECK == STD_ON )
               RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;
               lConfigRxPduDlc = RxPduCfg_pcst->RxPduDlc_u8;
                if( (PduInfoPtr->SduLength < lConfigRxPduDlc) && (NULL_PTR != CallBackPtr_Temp->Dlc_Error_Notification) )
                {
                    (void)CallBackPtr_Temp->Dlc_Error_Notification(PduId_qu8, (uint8)(PduInfoPtr->SduLength));
                }
                CANIF_DET_REPORT_ERROR_VOID_RET((PduInfoPtr->SduLength < lConfigRxPduDlc), CANIF_RX_INDICATION_SID, CANIF_E_INVALID_DLC)

                if( PduInfoPtr->SduLength >= lConfigRxPduDlc )
                #endif
                {
                    PduInfoTemp_tst.SduLength = PduInfoPtr->SduLength;
                    #if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduLength= PduInfoTemp_tst.SduLength;
                    #endif
                    PduInfoTemp_tst.SduDataPtr =(uint8*)(PduInfoPtr->SduDataPtr);
                    #if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduDataPtr= PduInfoTemp_tst.SduDataPtr;
                    #endif

                      if((CANIF_READ_NOTIFSTATUS_DATA == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8) || (CANIF_READ_NOTIFSTATUS == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8))
                      {
                          *(RxNotifPtr_pen + PduId_qu8) = CANIF_TX_RX_NOTIFICATION;
                      }
                    if(RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_NO_UL)
                    {
                        {
#if CANIF_CFG_UL_RX == STD_ON
                            if (RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_SIX)
                            {
                                (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                            }
                            else
                            {
                                (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                            }
                            #endif
                        }
                    }
                }
            }
        }
    }
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_XCore_LocalCore_RxIndication(const CanIf_Cfg_RxPduType_tst * CanIf_RXPduConfig_pst,
                                                                    const PduInfoType * CanIf_ULPduinfo_pst)
{
        Std_ReturnType lretval = E_OK;
#if CANIF_CFG_UL_RX == STD_ON
        const CanIf_Cfg_RxPduType_tst * RxPduConfig_pst;
#endif
        CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_RXPduConfig_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
        CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_ULPduinfo_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
#if CANIF_CFG_UL_RX == STD_ON
        RxPduConfig_pst = CanIf_RXPduConfig_pst;
        CanIf_Lok_ConfigSet_tpst->RxAutosarUL_Ptr[RxPduConfig_pst->IndexForUL_u8].CanIfRxPduIndicationName(RxPduConfig_pst->RxPduTargetId_t, CanIf_ULPduinfo_pst);
#endif
        return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

