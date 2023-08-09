

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
    P2VAR(  CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC    ) lControllerState_p;
    VAR (uint8, AUTOMATIC           ) lControllerId_u8      = 0;
    VAR (   CanIf_PduModeType, AUTOMATIC                        ) lChannelMode_en;

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
    P2VAR(CanIf_NotifStatusType, AUTOMATIC, AUTOMATIC) lTxNotifPtr;
#endif

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
    VAR (CanIf_ControllerModeType, AUTOMATIC) lDeviceMode_en;
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
    VAR(uint8, AUTOMATIC) llocalCoreId_u8 ;
    VAR(uint8, AUTOMATIC) ldestCoreId_u8;
    VAR(uint16, AUTOMATIC) lpipeId_u16 ;
    VAR(CanIf_XCore_PipeTxRxParams_st, AUTOMATIC) lpipeParams_st;
    VAR(PduInfoType, AUTOMATIC) pduInfoDummy_st;
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)
    const CanIf_Cfg_TxBufferConfig_tst* lCanIf_TxBufferConfig_p;
    uint8* lDataBuf_p;
    P2VAR (CanIf_Cfg_CanIdBuffer_tst,AUTOMATIC, AUTOMATIC  ) lCanIdBuf_p;
    uint32 lBufferId;
    VAR(uint8, AUTOMATIC) sdu_temp[CANIF_PRV_MAX_BUFFER_SIZE] = {0};
    Can_PduType Pdu_temp = {NULL_PTR, 0, 0, 0};
    Can_HwHandleType lHth_uo = 0;
    Can_ReturnType lCanRetVal;
    Std_ReturnType lTxBufferRetVal = E_NOT_OK;
    uint8 lClearIndex;
    uint8 lDataIndex;
    uint8 lDataMaxLen;
    Pdu_temp.sdu = &sdu_temp[0];
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_TX_CONFIRMATION_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_VOID_RET(CanTxPduId >= CANIF_TOTAL_TXPDUS, CANIF_TX_CONFIRMATION_SID,CANIF_E_PARAM_LPDU)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
    CANIF_DET_REPORT_ERROR_VOID_RET((ltxPduCustId_t == 0xFFFFu), CANIF_TX_CONFIRMATION_SID, CANIF_E_PARAM_LPDU)
    lTxPduConfig_pst   = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
#if (CANIF_RB_NODE_CALIBRATION == STD_OFF)
    lCtrlConfig_pst    = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr;
#else
    lCtrlConfig_pst = &(CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr[lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->getCtrlCfg()]);
#endif
    lControllerId_u8   = lCtrlConfig_pst->CtrlId;

    lControllerState_p = CanIf_Lok_ControllerState_ast + lControllerId_u8;
    lChannelMode_en    = lControllerState_p->ChannelMode;

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
    lTxNotifPtr = CanIf_Lok_TxNotification_aen;
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)
    lCanIf_TxBufferConfig_p = lTxPduConfig_pst->CanIf_TxBufferConfigPtr;
    lDataBuf_p                 = lCanIf_TxBufferConfig_p->DataBuf;
    lCanIdBuf_p                  = lCanIf_TxBufferConfig_p->CanIdBuf;
    lDataMaxLen                  = lCanIf_TxBufferConfig_p->CanIfBufferMaxDataLength;
    lBufferId                = lCanIf_TxBufferConfig_p->CanIfBufferId;
    lHth_uo                   = lCanIf_TxBufferConfig_p->CanIf_HthConfigPtr->CanObjectId;
#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    if((lCtrlConfig_pst->PnCtrlEn == TRUE) && (lControllerState_p->BlPnTxFilter != FALSE))
    {
        lControllerState_p->BlPnTxFilter = FALSE;
    }

#endif

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)

    SchM_Enter_CanIf_ControllerState();

    lDeviceMode_en = lControllerState_p->DeviceMode;

if( ((lControllerState_p->CanIf_TxCnfmStatus) != CANIF_TX_RX_NOTIFICATION) && (lDeviceMode_en == CANIF_CS_STARTED))
{

    lControllerState_p->CanIf_TxCnfmStatus = CANIF_TX_RX_NOTIFICATION;
}

    SchM_Exit_CanIf_ControllerState();
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

    if (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus  != CANIF_TXBUFFER_EMPTY)
    {

        SchM_Enter_CanIf_TxBufAccessNoNest();

        lTxBufferRetVal = CanIf_Lok_ReadTxBuffer(lCanIf_TxBufferConfig_p, &Pdu_temp);

        SchM_Exit_CanIf_TxBufAccessNoNest();

        if(lTxBufferRetVal == E_OK)
        {

            lCanRetVal = Can_Write(lHth_uo, &Pdu_temp);

            if((lCanRetVal == CAN_OK)||(lCanRetVal == CAN_NOT_OK))
            {

                SchM_Enter_CanIf_TxBufAccessNoNest();

                lClearIndex = (CanIf_Lok_TxBufferRam_ast[lBufferId].last_index);
               *(lDataBuf_p + ((lCanIdBuf_p[lClearIndex].BufferIndex)*(lDataMaxLen+1)) + 0)    = 0xFF;
               #if(CANIF_TRIGGERTRANSMIT_SUPPORT == STD_ON)

                lTxPduConfig_pst    = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + \
                                                                ((lCanIdBuf_p + lClearIndex)->swPduHandle);
                if(lTxPduConfig_pst->TxPduTriggerTransmit!=TRUE)
#endif
                {

                     for(lDataIndex=1; lDataIndex < lDataMaxLen; lDataIndex++)
                     {
                         *(lDataBuf_p + (lCanIdBuf_p[lClearIndex].BufferIndex*(lDataMaxLen+1)) + lDataIndex) = 0;
                     }
                }

                 CanIf_Lok_TxPduRam_ast[(lCanIdBuf_p + lClearIndex)->swPduHandle].pdu_buffered_flag = FALSE;
                 (lCanIdBuf_p + lClearIndex)->BufferIndex = 0;
                  (lCanIdBuf_p + lClearIndex)->CanId = 0;
                  (lCanIdBuf_p + lClearIndex)->SduLength = 0;
                 (lCanIdBuf_p + lClearIndex)->swPduHandle = 0;

                 (CanIf_Lok_TxBufferRam_ast[lBufferId].last_index) = (lClearIndex - 1)&0xFFu;
                 if((CanIf_Lok_TxBufferRam_ast[lBufferId].last_index) == 0xFF)
                 {
                     (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus) = CANIF_TXBUFFER_EMPTY;
                 }
                 else if(CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus == CANIF_TXBUFFER_FULL)
                 {
                     (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus) = CANIF_TXBUFFER_READY;
                 }
                 else
                 {

                 }

                 SchM_Exit_CanIf_TxBufAccessNoNest();
            }
        }
    }
#endif

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)

if( FALSE != lTxPduConfig_pst->TxPduReadNotifyStatus )
{

    *(lTxNotifPtr + CanTxPduId) = CANIF_TX_RX_NOTIFICATION;

}
#endif

if((NULL_PTR != lTxPduConfig_pst->UserTxConfirmation) && (lChannelMode_en == CANIF_ONLINE))
{

    if ((lTxPduConfig_pst->TxPduTxUserUL == PDUR ) || (lTxPduConfig_pst->TxPduTxUserUL == USER ) || (CANIF_XCORE_CFG_ENABLED == STD_OFF))
    {
        (void)CanIf_XCore_LocalCore_TxConfirmation(lTxPduConfig_pst);
    }
    else
    {
		
        #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
        llocalCoreId_u8 = Schm_CanIf_XCore_GetCurrentCoreId();
        ldestCoreId_u8 = CanIf_XCore_Config_pcst->CanIf_XCoreUserTypeCoreAffinity[lTxPduConfig_pst->TxPduTxUserUL];
        lpipeId_u16 = CanIf_XCore_Config_pcst->CanIf_XCoreTxConfirmationPipeMatrix[llocalCoreId_u8][ldestCoreId_u8];
        pduInfoDummy_st.SduDataPtr = NULL_PTR;
        pduInfoDummy_st.SduLength = 0;

        lpipeParams_st.userType_e = lTxPduConfig_pst->TxPduTxUserUL;
        lpipeParams_st.PduId = CanTxPduId;
        lpipeParams_st.PduInfoPtr = &pduInfoDummy_st;
        lpipeParams_st.ControllerId_u8 = lControllerId_u8;

        if(lpipeId_u16 == CANIF_XCORE_INVALID_PIPE_ID)
        {
            (void)CanIf_XCore_LocalCore_TxConfirmation(lTxPduConfig_pst);
        }
        else
        {
            (void)CanIf_XCore_PipeWrite(lpipeId_u16, &lpipeParams_st);
        }
        #endif
		
    }
}
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_TxConfirmation(P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_TxPduConfig_pst)
{
   Std_ReturnType lretval = E_OK;
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
   CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_TxPduConfig_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
   lTxPduConfig_pst = CanIf_TxPduConfig_pst;
   lTxPduConfig_pst->UserTxConfirmation(lTxPduConfig_pst->TxPduTargetPduId);

   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
