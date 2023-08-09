

#include "CanIf_Prv.h"

#include "Can.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(VAR(PduIdType,AUTOMATIC) CanIfTxSduId,
        P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr)
{
    VAR (Std_ReturnType, AUTOMATIC) lRetVal_en;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
    VAR (CanIf_XCore_PipeTxRxParams_st, AUTOMATIC) lpipeParams_st;
    VAR (uint8, AUTOMATIC) llocalCoreId_u8;
    VAR (uint8, AUTOMATIC) ldestCoreId_u8;
    VAR (uint16, AUTOMATIC) lpipeId_u16;
    VAR (uint8, AUTOMATIC) lControllerId_u8    = 0;
#endif

    lRetVal_en = E_OK;
    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_TRANSMIT_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfTxSduId >= CANIF_TOTAL_TXPDUS), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfTxInfoPtr), CANIF_TRANSMIT_SID, CANIF_E_PARAM_POINTER)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
    CANIF_DET_REPORT_ERROR_NOT_OK((ltxPduCustId_t == 0xFFFFu), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

    if((lTxPduConfig_pst->TxTruncEnabled_b == FALSE) && (CanIfTxInfoPtr->SduLength> (lTxPduConfig_pst->TxPduLength_u8
            #if(CANIF_METADATA_SUPPORT == STD_ON)
            +lTxPduConfig_pst->MetaDataLength
            #endif
            )))
    {
#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
            CANIF_DET_REPORT_ERROR_NOT_OK(TRUE, CANIF_TRANSMIT_SID, CANIF_E_TXPDU_LENGTH_EXCEEDED)
#else
            lRetVal_en = E_NOT_OK;
#endif
    }
    else
    {
    }

    if(lRetVal_en ==E_OK)
    {

        #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

        lpipeParams_st.PduId = CanIfTxSduId;
        lpipeParams_st.PduInfoPtr = CanIfTxInfoPtr;

        lControllerId_u8  = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;

        lpipeParams_st.ControllerId_u8 = lControllerId_u8;

        llocalCoreId_u8 = Schm_CanIf_XCore_GetCurrentCoreId();

        ldestCoreId_u8 = CanIf_XCore_Config_pcst->CanIf_XCoreCanControllerCoreAffinity[lControllerId_u8];

    lpipeId_u16 = CanIf_XCore_Config_pcst->CanIf_XCoreTxPipeMatrix[llocalCoreId_u8][ldestCoreId_u8];

    if(lpipeId_u16 == CANIF_XCORE_INVALID_PIPE_ID)
    {

        lRetVal_en = CanIf_XCore_LocalCore_Transmit(CanIfTxSduId, CanIfTxInfoPtr);
    }
    else
    {

        lRetVal_en = CanIf_XCore_PipeWrite(lpipeId_u16, &lpipeParams_st);
    }

    #else

    lRetVal_en = CanIf_XCore_LocalCore_Transmit(CanIfTxSduId, CanIfTxInfoPtr);

        #endif

    }
    else
    {

    }
#else
    lRetVal_en = E_NOT_OK;

    return lRetVal_en;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_XCore_LocalCore_Transmit(
                                                    VAR(PduIdType,AUTOMATIC) CanIfTxSduId,
                                                    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr
                                               )
{
    VAR (Std_ReturnType, AUTOMATIC   ) lRetVal_en           = E_NOT_OK;

    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;

    P2VAR(  CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC    ) lControllerState_en;

    VAR (   CanIf_ControllerModeType, AUTOMATIC                 ) lDeviceMode_en;

    VAR (   CanIf_PduModeType, AUTOMATIC                        ) lChannelMode_en;

    VAR (Can_PduType, AUTOMATIC      ) lPduInfo_st          = {NULL_PTR, 0, 0, 0};
    VAR (Can_ReturnType, AUTOMATIC   ) lCanStatus_en        = CAN_NOT_OK;
    VAR (Can_HwHandleType, AUTOMATIC ) lHth_uo              = 0;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    VAR (uint8,AUTOMATIC             ) lMaxSduLength_u8     = 0;
#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    VAR(uint8,AUTOMATIC) CanifMSBbits_u8;
#endif
#endif
    VAR (PduLengthType, AUTOMATIC     ) lSduLength            = 0;
    VAR (uint8, AUTOMATIC           ) lControllerId_u8    = 0;

    VAR (uint32, AUTOMATIC         ) lCanId_u32             = 0;

#if(CANIF_METADATA_SUPPORT == STD_ON)
    VAR (uint32, AUTOMATIC         ) lStoredCanId_u32       = 0;
    VAR (uint32, AUTOMATIC         ) lMetadataCanId_u32     = 0;
    VAR (uint8_least, AUTOMATIC    ) lIndex_uo              = 0;
    P2VAR(uint8,AUTOMATIC,AUTOMATIC) lMetaDataPtr_u8;
#endif

#if((CANIF_PUBLIC_TXBUFFERING == STD_ON)&&(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON))
    uint8 lDataMaxLen;
#endif
#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON)

    VAR (boolean, AUTOMATIC) lPnTxFilter_b;
#endif

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    P2VAR(uint32,AUTOMATIC,AUTOMATIC) lDynId_p;
#endif

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];

    CANIF_DET_REPORT_ERROR_NOT_OK((ltxPduCustId_t == 0xFFFFu), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)

    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

#if(CANIF_TRIGGERTRANSMIT_SUPPORT != STD_ON)
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfTxInfoPtr->SduDataPtr), CANIF_TRANSMIT_SID, CANIF_E_PARAM_POINTER)
#else
    CANIF_DET_REPORT_ERROR_NOT_OK(((NULL_PTR == CanIfTxInfoPtr->SduDataPtr) && (lTxPduConfig_pst->TxPduTriggerTransmit == FALSE)),\
                                CANIF_TRANSMIT_SID, CANIF_E_PARAM_POINTER)
#endif

    lHth_uo           = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanObjectId;
#if(CANIF_RB_NODE_CALIBRATION == STD_OFF)
    lControllerId_u8  = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;
#else
    lControllerId_u8  = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->getCtrlCfg();
#endif

    lControllerState_en = CanIf_Lok_ControllerState_ast + lControllerId_u8;

    SchM_Enter_CanIf_ControllerState();

    lDeviceMode_en  = lControllerState_en->DeviceMode;
    lChannelMode_en = lControllerState_en->ChannelMode;

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    lPnTxFilter_b   = lControllerState_en->BlPnTxFilter;
#endif

    SchM_Exit_CanIf_ControllerState();

    CANIF_DET_REPORT_ERROR_NOT_OK(((lChannelMode_en == CANIF_OFFLINE)||(lDeviceMode_en == CANIF_CS_STOPPED)), \
                                                CANIF_TRANSMIT_SID, CANIF_E_STOPPED)

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    if((lPnTxFilter_b == TRUE) && ((lTxPduConfig_pst->TxPduPnFilterPdu)==FALSE))
    {
        lRetVal_en = E_NOT_OK;
    }
    else
#endif
    {

    if(
#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
        ((lPnTxFilter_b == TRUE)&&((lTxPduConfig_pst->TxPduPnFilterPdu)==TRUE))||((lPnTxFilter_b == FALSE)&&
#endif

        ((lDeviceMode_en == CANIF_CS_STARTED) && (lChannelMode_en == CANIF_ONLINE))

#if(CANIF_USER_TP_TX_OFFLINE_MODE != STD_OFF)

        ||((lDeviceMode_en == CANIF_CS_STARTED) && (((lChannelMode_en == CANIF_TX_TP_ONLINE) && \
                (lTxPduConfig_pst->TxPduTxUserUL == CAN_TP)) ||((lChannelMode_en == CANIF_TX_USER_TP_ONLINE) &&       \
                ((lTxPduConfig_pst->TxPduTxUserUL == USER) || (lTxPduConfig_pst->TxPduTxUserUL == CAN_TP)))))
#endif

      )
#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
      )
#endif
    {

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
        if(lTxPduConfig_pst->TxPduType!= CANIF_STATIC)
        {

            lDynId_p = &CanIf_DynTxPduCanId_au32[0];

            lPduInfo_st.id = (Can_IdType)*(lDynId_p + (lTxPduConfig_pst->TxPduType));

#if ( CANIF_RB_CALIBRATION == STD_ON )

            if( lTxPduConfig_pst->getTxPduDlc != NULL_PTR )
            {

                lSduLength = lTxPduConfig_pst->getTxPduDlc();
            }
            else
#endif
            {
                if(CanIfTxInfoPtr->SduLength>lTxPduConfig_pst->TxPduLength_u8)
                {
                    lSduLength = lTxPduConfig_pst->TxPduLength_u8;
                }
                else
                {
                    lSduLength = CanIfTxInfoPtr->SduLength;
                }
            }

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

            CanifMSBbits_u8 = (uint8)((lPduInfo_st.id)>>CANIF_CANID_BIT_SHIFT);

            if((CanifMSBbits_u8 == CANIF_ONE) ||(CanifMSBbits_u8 == CANIF_THREE))
            {
                lMaxSduLength_u8 = 64u;
            }
            else
            {
                lMaxSduLength_u8 = 8u;
            }
#endif
        }
        else
#endif
        {

#if(CANIF_METADATA_SUPPORT == STD_ON)
            if(lTxPduConfig_pst->MetaDataLength >= 1)
            {
                if(CanIfTxInfoPtr->SduLength>(lTxPduConfig_pst->TxPduLength_u8+lTxPduConfig_pst->MetaDataLength))
                {
                    lSduLength = lTxPduConfig_pst->TxPduLength_u8;
                }
                else
                {
                    lSduLength = (CanIfTxInfoPtr->SduLength)- (lTxPduConfig_pst->MetaDataLength);
                }

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

                if( (lTxPduConfig_pst->TxPduCanIdType == STANDARD_CAN) ||
                    (lTxPduConfig_pst->TxPduCanIdType == EXTENDED_CAN) )
                {

                    lMaxSduLength_u8 = 8u + lTxPduConfig_pst->MetaDataLength;
                }
                else
                {

                    lMaxSduLength_u8 = 64u + lTxPduConfig_pst->MetaDataLength;
                }
#endif

#if (CANIF_RB_CALIBRATION == STD_ON)
                if(lTxPduConfig_pst->getTxPduCanId != NULL_PTR )
                {
                    lStoredCanId_u32 = lTxPduConfig_pst->getTxPduCanId();
                }
                else
#endif
                {
                    lStoredCanId_u32 = lTxPduConfig_pst->TxPduCanId;
                }

                lMetaDataPtr_u8 = (uint8 *)(CanIfTxInfoPtr->SduDataPtr);

                lMetaDataPtr_u8 = lMetaDataPtr_u8 + (CanIfTxInfoPtr->SduLength-1u);

                for(lIndex_uo = 0; lIndex_uo < (lTxPduConfig_pst->MetaDataLength);lIndex_uo++)
                {

                    lMetadataCanId_u32 = (lMetadataCanId_u32<<8u) | (*lMetaDataPtr_u8);
                    lMetaDataPtr_u8--;

                }

                if(lTxPduConfig_pst->TxPduCanId!= 0xFFFFFFFFu)

                {

                    lCanId_u32 = ((lStoredCanId_u32) & (lTxPduConfig_pst->TxPduCanIdMask)) |
                            ((lMetadataCanId_u32) & (~(lTxPduConfig_pst->TxPduCanIdMask)));
                }
                else
                {

                    if( (lTxPduConfig_pst->TxPduCanIdType == STANDARD_CAN)  ||
                        (lTxPduConfig_pst->TxPduCanIdType == STANDARD_FD_CAN) )
                    {
                            lCanId_u32 = lMetadataCanId_u32 & 0x000007FFu;
                    }
                    else
                    {
                            lCanId_u32 = lMetadataCanId_u32 & 0x1FFFFFFFu;

                    }
                }

            }
            else
#endif
            {

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

                if( (lTxPduConfig_pst->TxPduCanIdType == STANDARD_CAN) ||
                    (lTxPduConfig_pst->TxPduCanIdType == EXTENDED_CAN) )
                {

                    lMaxSduLength_u8 = 8u;
                }
                else
                {

                    lMaxSduLength_u8 = 64u ;
                }
#endif

                if(lTxPduConfig_pst->TxPduCanId!= 0xFFFFFFFFu)
                {

#if (CANIF_RB_CALIBRATION == STD_ON)
                    if(lTxPduConfig_pst->getTxPduCanId != NULL_PTR )
                    {
                       lCanId_u32 = lTxPduConfig_pst->getTxPduCanId();
                    }
                    else
#endif
                    {
                       lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
                    }

                }
                else
                {

                }

#if ( CANIF_RB_CALIBRATION == STD_ON )

                if( lTxPduConfig_pst->getTxPduDlc != NULL_PTR )
                {

                    lSduLength = lTxPduConfig_pst->getTxPduDlc();
                }
                else
#endif
                {
                    if( CanIfTxInfoPtr->SduLength > lTxPduConfig_pst->TxPduLength_u8 )
                    {
                        lSduLength = lTxPduConfig_pst->TxPduLength_u8;
                    }
                    else
                    {
                        lSduLength = CanIfTxInfoPtr->SduLength;
                    }
                }
            }

            lPduInfo_st.id = (Can_IdType)lCanId_u32;

            lPduInfo_st.id &= CANIF_MSB_BIT_RESET;

            lPduInfo_st.id |= ( ((Can_IdType)lTxPduConfig_pst->TxPduCanIdType) << CANIF_CANID_BIT_SHIFT );

        }

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

        CANIF_DET_REPORT_ERROR(((uint8)CanIfTxInfoPtr->SduLength > lMaxSduLength_u8), \
CANIF_TRANSMIT_SID, CANIF_E_DATA_LENGTH_MISMATCH)
#endif
        lPduInfo_st.swPduHandle = lTxPduConfig_pst->TxPduId;
        lPduInfo_st.sdu         = CanIfTxInfoPtr->SduDataPtr;
        lPduInfo_st.length      = (uint8)lSduLength;

        lCanStatus_en = Can_Write(lHth_uo, &lPduInfo_st);

        if(lCanStatus_en == CAN_OK)
        {
            lRetVal_en = E_OK;
        }
        else if(lCanStatus_en == CAN_BUSY)
        {

    #if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

            if((lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIfBufferSize) > 0)
            {

                SchM_Enter_CanIf_TxBufAccessNoNest();

                lRetVal_en = CanIf_Lok_WriteTxBuffer(ltxPduCustId_t, lPduInfo_st);

                SchM_Exit_CanIf_TxBufAccessNoNest();
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
                lDataMaxLen = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIfBufferMaxDataLength;
#endif

                CANIF_DET_REPORT_ERROR(((lRetVal_en == E_OK) && ((uint8)lPduInfo_st.length > lDataMaxLen)),     \
                                                                    CANIF_TRANSMIT_SID, CANIF_E_DATA_LENGTH_MISMATCH)
            }
            else
            {
                lRetVal_en = E_NOT_OK;
            }
    #else
            lRetVal_en = E_NOT_OK;
    #endif
        }
        else
        {
            lRetVal_en = E_NOT_OK;
        }
    }
#if(CANIF_TXOFFLINEACTIVE_SUPPORT == STD_ON)
    else if((CANIF_CS_STARTED == lDeviceMode_en)&&
                (lChannelMode_en == CANIF_TX_OFFLINE_ACTIVE))
    {
        if(NULL_PTR != lTxPduConfig_pst->UserTxConfirmation)
        {
            lTxPduConfig_pst->UserTxConfirmation(lTxPduConfig_pst->TxPduTargetPduId);
        }

        lRetVal_en = E_OK;
    }
#endif
    else
    {

    }
  }
    return lRetVal_en;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#if (CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CancelTransmit(
                                                    VAR(PduIdType,AUTOMATIC) CanIfTxSduId

                                               )
{

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfTxSduId >= CANIF_TOTAL_TXPDUS), CANIF_CANCELTRANSMIT_SID, CANIF_E_INVALID_TXPDUID)

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId] == 0xFFFFu), \
                                                                    CANIF_CANCELTRANSMIT_SID, CANIF_E_INVALID_TXPDUID)

    (void)CanIfTxSduId;

        return E_OK;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif
