

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_RxIndication_Internal( P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox,
        P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA)PduInfoPtr)
{
    P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst;
    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

    #if CANIF_CFG_UL_RX == STD_ON
    VAR(PduInfoType, AUTOMATIC) ULPduInfoTyp_tst;
    #endif

    VAR(PduInfoType, AUTOMATIC) PduInfoTemp_tst;

    #if CANIF_CFG_USER_RX_ENABLED == STD_ON
    VAR(CanIf_PduInfoType, AUTOMATIC) ULPduInfoTypUSER_tst;
    #endif

    VAR(uint8,AUTOMATIC)Index_u8;
    VAR(uint8,AUTOMATIC)ModeChkStatus = CANIF_PRV_INVALID_CHANNEL_MODE;
    VAR(PduIdType,AUTOMATIC)PduId_qu8;

    #if (CANIF_BASIC_CAN_SUPPORT == STD_ON)
    VAR(uint8_least,AUTOMATIC)RngLstPduId_qu8;
    #endif

    VAR(Can_IdType,AUTOMATIC)CanIdNoIdType_t;
    VAR(boolean, AUTOMATIC) IdFound_b = FALSE;
     VAR(uint8, AUTOMATIC) CanIdPduType_u8;
     P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) ControllerState_ps;
     VAR (CanIf_ControllerModeType, AUTOMATIC) DeviceMode_tst;
     VAR (CanIf_PduModeType, AUTOMATIC) ChannelMode_tst;

    #if (CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) dynRxPduId_pu32;

    VAR(uint32,AUTOMATIC) rxcanid_u32 = 0;
    #endif

    #if(CANIF_CFG_DLC_CHECK == STD_ON)
    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;
	
    VAR(PduLengthType, AUTOMATIC) lConfigRxPduDlc;
    #endif
    #if(CANIF_METADATA_SUPPORT == STD_ON)

   // VAR(uint8,AUTOMATIC) CanId_Temp_u8;

    VAR(uint8,AUTOMATIC) SduDataBuffer_au8[SDU_DATA_BUFF_SIZE] = {0};

    #endif

    #if(CANIF_CANNM_TXID_FILTER != STD_OFF)
    P2CONST(Can_IdType, AUTOMATIC, AUTOMATIC) CanNmTxId_pt;
    #endif
    //RxPduCbk_pcst = CanIf_Lok_RxUSERName_ta_fct;

    #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
    VAR(uint8, AUTOMATIC) localCoreId_u8 ;
    VAR(uint8, AUTOMATIC) destCoreId_u8;
    VAR(uint16, AUTOMATIC) pipeId_u16 ;
    VAR(CanIf_XCore_PipeTxRxParams_st, AUTOMATIC) xCorePipeTxRxParams;
    #endif

    #if (STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    P2VAR(CanIf_NotifStatusType,AUTOMATIC, AUTOMATIC) RxNotifPtr_pen;

    RxNotifPtr_pen = CanIf_Lok_RxNotification_taen;
    // this array should be initialized to CANIF_NO_NOTIFICATION value in initialization.
    #endif

    #if(CANIF_CFG_DLC_CHECK == STD_ON)

    CallBackPtr_Temp = &CanIf_Callback;
    #endif

    CANIF_DET_REPORT_ERROR_VOID_RET(CanIf_Lok_InitStatus_b == FALSE, CANIF_RX_INDICATION_SID, CANIF_E_UNINIT);

    CANIF_DET_REPORT_ERROR_VOID_RET(((Mailbox == NULL_PTR) || (PduInfoPtr == NULL_PTR) ||((PduInfoPtr != NULL_PTR) &&
            (PduInfoPtr->SduDataPtr == NULL_PTR))),CANIF_RX_INDICATION_SID, CANIF_E_PARAM_POINTER);

    CanIdNoIdType_t = Mailbox->CanId & CANIF_PRV_MSB_BIT_RESET;

    CANIF_DET_REPORT_ERROR_VOID_RET(Mailbox->ControllerId>= CANIF_TOTAL_CTRLS ,CANIF_RX_INDICATION_SID, CANIF_E_PARAM_POINTER);

    CANIF_DET_REPORT_ERROR_VOID_RET((Mailbox->Hoh>=CANIF_CFG_TOTAL_HOH_NUM), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_HOH);
    CANIF_DET_REPORT_ERROR_VOID_RET((CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[Mailbox->Hoh] ==  INVALID_ID), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_HOH);

    CanIdPduType_u8 = (uint8)((Mailbox->CanId)>>CANIF_CANID_BIT_SHIFT);

    CANIF_DET_REPORT_ERROR_VOID_RET((((CanIdPduType_u8 == CANIF_ZERO)||(CanIdPduType_u8 == CANIF_ONE))&& (CanIdNoIdType_t > CANIF_CAN_STD_VAL))||
                    (((CanIdPduType_u8 == CANIF_TWO)||(CanIdPduType_u8 == CANIF_THREE))&& (CanIdNoIdType_t > CANIF_CAN_XTD_VAL)), CANIF_RX_INDICATION_SID, CANIF_E_PARAM_CANID);

    CANIF_DET_REPORT_ERROR_VOID_RET((((CanIdPduType_u8 == CANIF_ZERO)||(CanIdPduType_u8 == CANIF_TWO))&& (PduInfoPtr->SduLength > 8u))||
                        (((CanIdPduType_u8 == CANIF_ONE)||(CanIdPduType_u8 == CANIF_THREE))&& (PduInfoPtr->SduLength > 64u)), CANIF_RX_INDICATION_SID, CANIF_E_DATA_LENGTH_MISMATCH);

    HrhCfg_pcst = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[Mailbox->Hoh];
    #if(CANIF_CANNM_TXID_FILTER != STD_OFF)
    CanNmTxId_pt = CanIf_Lok_ConfigSet_tpst->NmtxIdPtr;
    #endif

    ControllerState_ps= CanIf_Lok_ControllerState_ast + Mailbox->ControllerId;

    SchM_Enter_CanIf_ControllerState();
    DeviceMode_tst = ControllerState_ps->DeviceMode;
    ChannelMode_tst = ControllerState_ps->ChannelMode;

    #if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON && CANIF_PUBLIC_BUSOFF_RECOVERY_FROM_RXINDICATION == STD_ON )

    ControllerState_ps->CanIf_TxCnfmStatus = CANIF_TX_RX_NOTIFICATION;
    #endif

    SchM_Exit_CanIf_ControllerState();

    #if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    if(ControllerState_ps->BlPnTxFilter == TRUE)
    {
       ControllerState_ps->BlPnTxFilter = FALSE;
    }
    #endif

    if(CANIF_CS_STARTED == DeviceMode_tst)
    {

        if((CANIF_TX_OFFLINE == ChannelMode_tst)||(CANIF_ONLINE == ChannelMode_tst))
        {
            ModeChkStatus = CANIF_PRV_VALID_CHANNEL_MODE;
        }

        #if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
        else
        {
            ModeChkStatus = CANIF_PRV_WAKEUP_MODE;
        }
        #endif

        #if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_OFF)
        if(ModeChkStatus == CANIF_PRV_VALID_CHANNEL_MODE)
        #endif
        {

            Index_u8 = 0;

            switch(HrhCfg_pcst->HrhInfo_e)
            {

                case CANIF_PRV_FULL_E:
                {

                    PduId_qu8 = HrhCfg_pcst->PduIdx_t;

                    do{

                        RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;

                        #if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)

                        if((RxPduCfg_pcst->RxPduType) != CANIF_STATIC)
                        {

                            dynRxPduId_pu32 = &CanIf_DynRxPduCanId_au32[0];

                            rxcanid_u32 = (Can_IdType)*(dynRxPduId_pu32 + (RxPduCfg_pcst->RxPduType));

                            rxcanid_u32 = rxcanid_u32 & CANIF_PRV_MSB_BIT_RESET;

                            if((((RxPduCfg_pcst->CanIdtype_u8) &(CANIF_PRV_CANID_TYPE_MASK))==(((RxPduCfg_pcst->CanIdtype_u8)>>CANIF_PRV_FOUR)& CanIdPduType_u8)) && (CanIdNoIdType_t == rxcanid_u32))
                            {

                                IdFound_b = TRUE;
                                break;
                            }
                        }
                        else
                        #endif
                        {
                            #if (CANIF_RB_CALIBRATION == STD_ON)

                            if((((RxPduCfg_pcst->CanIdtype_u8)&(CANIF_PRV_CANID_TYPE_MASK))==(((RxPduCfg_pcst->CanIdtype_u8)>>CANIF_PRV_FOUR)& CanIdPduType_u8))&&(CanIdNoIdType_t == RxPduCfg_pcst->getCanId()))
                            #else
                            if((((RxPduCfg_pcst->CanIdtype_u8)&(CANIF_PRV_CANID_TYPE_MASK))==(((RxPduCfg_pcst->CanIdtype_u8)>>CANIF_PRV_FOUR)& CanIdPduType_u8))&&(CanIdNoIdType_t == RxPduCfg_pcst->RxPduCanId))
                            #endif
                            {

                                IdFound_b = TRUE;
                                break;
                            }
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

        #if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
        if(ModeChkStatus==  CANIF_PRV_WAKEUP_MODE)
        {
            #if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_BY_NM == STD_ON)
            if(RxPduCfg_pcst->ULisCanNm_b == TRUE)
            #endif
            {
                ControllerState_ps->ValidationSts_b = CANIF_SET;
            }
        }
        else
        #endif
        {

            #if(CANIF_CANNM_TXID_FILTER != STD_OFF)

            if((RxPduCfg_pcst->IndexForUL_u8 == CANIF_ONE) && (CanNmTxId_pt != NULL_PTR) && (*(CanNmTxId_pt + (RxPduCfg_pcst->RxPduTargetId_t)) == CanIdNoIdType_t))
            {
                IdFound_b = FALSE;
            }
            if(IdFound_b==TRUE)
            #endif
            {

                #if ( CANIF_CFG_DLC_CHECK == STD_ON )
                //check if below statement is correct
                //Also the below statement might not be needed as the correct rxpdu would be selected in the above statements
                RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;

                #if (CANIF_RB_CALIBRATION == STD_ON)
                if( RxPduCfg_pcst->getRxPduDlc != NULL_PTR )
                {
                    lConfigRxPduDlc = RxPduCfg_pcst->getRxPduDlc();
                }
                else
                #endif
                {
                    lConfigRxPduDlc = RxPduCfg_pcst->RxPduDlc_u8;
                }

                if( (PduInfoPtr->SduLength < lConfigRxPduDlc) && (NULL_PTR != CallBackPtr_Temp->Dlc_Error_Notification) )
                {

                    (void)CallBackPtr_Temp->Dlc_Error_Notification(PduId_qu8, (uint8)(PduInfoPtr->SduLength));
                }

                CANIF_DET_REPORT_ERROR_VOID_RET((PduInfoPtr->SduLength < lConfigRxPduDlc), CANIF_RX_INDICATION_SID, CANIF_E_INVALID_DLC)

                if( PduInfoPtr->SduLength >= lConfigRxPduDlc )
                #endif
                {

                    #if(CANIF_METADATA_SUPPORT == STD_ON)
                    PduInfoTemp_tst.SduLength = PduInfoPtr->SduLength + RxPduCfg_pcst->MetadataLength_u8;
                    // ULPduInfoTyp_tst.SduLength = PduInfoPtr->SduLength + RxPduCfg_pcst->MetadataLength_u8;
                    #else
                    PduInfoTemp_tst.SduLength = PduInfoPtr->SduLength;
                    //ULPduInfoTyp_tst.SduLength = PduInfoPtr->SduLength;
                    #endif
                    #if CANIF_CFG_USER_RX_ENABLED == STD_ON
                    ULPduInfoTypUSER_tst.SduLength= PduInfoTemp_tst.SduLength;
                    #endif
                    #if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduLength= PduInfoTemp_tst.SduLength;
                    #endif

                    //SduLength_u32 = ULPduInfoTyp_tst.SduLength;

                    #if(CANIF_METADATA_SUPPORT == STD_ON)

                    for(Index_u8 =0; Index_u8 < PduInfoPtr->SduLength; Index_u8++)
                    {
                        SduDataBuffer_au8[Index_u8] = PduInfoPtr->SduDataPtr[Index_u8];
                    }

                    if(RxPduCfg_pcst->MetadataLength_u8 >= 1u)
                    {

                        for(Index_u8 = (uint8)(PduInfoPtr->SduLength); Index_u8 < (uint8)(PduInfoTemp_tst.SduLength); Index_u8++)
                        {

                            SduDataBuffer_au8[Index_u8]= (uint8)(CanIdNoIdType_t & CANIF_GET_ONE_BYTE);
                            CanIdNoIdType_t = (CanIdNoIdType_t>>SHIFT_8);
                        }
                    }
                    PduInfoTemp_tst.SduDataPtr = (uint8*)(&SduDataBuffer_au8[0]);
                    //ULPduInfoTyp_tst.SduDataPtr = (uint8*)(&SduDataBuffer_au8[0]);
                    #else
                    PduInfoTemp_tst.SduDataPtr =(uint8*)(PduInfoPtr->SduDataPtr);
                    //ULPduInfoTyp_tst.SduDataPtr = (uint8*)(PduInfoPtr->SduDataPtr);
                    #endif
                    #if CANIF_CFG_USER_RX_ENABLED == STD_ON
                    ULPduInfoTypUSER_tst.SduDataPtr= PduInfoTemp_tst.SduDataPtr;
                    #endif
                    #if CANIF_CFG_UL_RX == STD_ON
                    ULPduInfoTyp_tst.SduDataPtr= PduInfoTemp_tst.SduDataPtr;
                    #endif

                      #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
                      if((CANIF_READ_NOTIFSTATUS_DATA == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8) || (CANIF_READ_NOTIFSTATUS == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8))
                      {
                          *(RxNotifPtr_pen + PduId_qu8) = CANIF_TX_RX_NOTIFICATION;
                      }
                      #endif
                    // for J1939Tp function pointer i am not able to test in this stand. Please make sure this test is done in Com stack stand.

                    #if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
                    if((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS_DATA) || (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8== CANIF_READ_DATA))
                    {

                        CanIf_Lok_WriteRxBuffer(PduInfoTemp_tst.SduDataPtr, RxPduCfg_pcst,PduInfoPtr->SduLength,Mailbox->CanId);
                    }
                    #endif

                    if(RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_NO_UL)
                    {
                        #if CANIF_CFG_USER_RX_ENABLED == STD_ON
                        if(RxPduCfg_pcst->IndexForUL_u8 > (CANIF_PRV_SEVEN+ CanIf_Lok_ConfigSet_tpst->NumCddRxPdus_t))
                        {

                            ULPduInfoTypUSER_tst.SduCanId = (uint32)((Mailbox->CanId) & CANIF_MSB_BIT_RESET);
                            CanIf_Lok_ConfigSet_tpst->RxUSER_Ptr[(RxPduCfg_pcst->IndexForUL_u8)-(CANIF_PRV_EIGHT+CanIf_Lok_ConfigSet_tpst->NumCddRxPdus_t)].CanIfRxPduUserRxIndicationUser(RxPduCfg_pcst->RxPduTargetId_t, &ULPduInfoTypUSER_tst);
                        }
                        else
                        #endif
                        {
                            #if CANIF_CFG_UL_RX == STD_ON

                            if (RxPduCfg_pcst->IndexForUL_u8 != CANIF_PRV_SIX)
                            {
                                #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
                                uint8_least RxPduCfg_IndexForUL_u8 = 0;
                                localCoreId_u8 = Schm_CanIf_XCore_GetCurrentCoreId();

                                if (RxPduCfg_pcst->IndexForUL_u8 > (uint8_least) CDD)
                                {
                                    RxPduCfg_IndexForUL_u8 = (uint8_least)CDD;
                                    destCoreId_u8 = CanIf_XCore_Config_pcst->CanIf_XCoreUserTypeCoreAffinity[RxPduCfg_IndexForUL_u8];
                                }
                                else
                                {
                                    destCoreId_u8 = CanIf_XCore_Config_pcst->CanIf_XCoreUserTypeCoreAffinity[RxPduCfg_pcst->IndexForUL_u8];
                                }
                                pipeId_u16 = CanIf_XCore_Config_pcst->CanIf_XCoreRxPipeMatrix[localCoreId_u8][destCoreId_u8];

                                if(pipeId_u16 == CANIF_XCORE_INVALID_PIPE_ID)
                                {

                                   (void) CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                                }
                                else
                                {
                                    xCorePipeTxRxParams.PduId = (PduIdType)PduId_qu8;
                                    xCorePipeTxRxParams.PduInfoPtr = &ULPduInfoTyp_tst;
                                    xCorePipeTxRxParams.callbackIndex_u8 = (uint8)RxPduCfg_pcst->IndexForUL_u8;
                                    xCorePipeTxRxParams.ControllerId_u8 = Mailbox->ControllerId;

                                    (void)CanIf_XCore_PipeWrite(pipeId_u16, &xCorePipeTxRxParams);
                                }
                                #else

                                (void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &ULPduInfoTyp_tst);
                                #endif
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

FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_RxIndication(P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_RXPduConfig_pst,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANIF_CFG_CONST) CanIf_ULPduinfo_pst)
{
   Std_ReturnType lretval = E_OK;
   P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduConfig_pst;
   CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_RXPduConfig_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
   CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_ULPduinfo_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
   RxPduConfig_pst = CanIf_RXPduConfig_pst;

#if CANIF_CFG_UL_RX == STD_ON
   CanIf_Lok_ConfigSet_tpst->RxAutosarUL_Ptr[RxPduConfig_pst->IndexForUL_u8].CanIfRxPduIndicationName(RxPduConfig_pst->RxPduTargetId_t, CanIf_ULPduinfo_pst);
#endif

   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

