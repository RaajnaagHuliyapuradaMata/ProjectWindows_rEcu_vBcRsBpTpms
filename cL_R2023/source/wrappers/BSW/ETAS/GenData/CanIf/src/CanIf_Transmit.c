#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_Transmit(
   PduIdType CanIfTxSduId,
   const PduInfoType* CanIfTxInfoPtr){
    Std_ReturnType lRetVal_en;
    uint16 ltxPduCustId_t;
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;

    lRetVal_en = E_OK;
    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_TRANSMIT_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfTxSduId >= CANIF_TOTAL_TXPDUS), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfTxInfoPtr), CANIF_TRANSMIT_SID, CANIF_E_PARAM_POINTER)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
    CANIF_DET_REPORT_ERROR_NOT_OK((ltxPduCustId_t == 0xFFFFu), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

    if((lTxPduConfig_pst->TxTruncEnabled_b == FALSE) && (CanIfTxInfoPtr->SduLength> ((uint32)lTxPduConfig_pst->TxPduLength_u8
            ))){
#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

            CANIF_DET_REPORT_ERROR_NOT_OK(TRUE, CANIF_TRANSMIT_SID, CANIF_E_TXPDU_LENGTH_EXCEEDED)
#else
            lRetVal_en = E_NOT_OK;
#endif
    }
   else{
    }

   if(lRetVal_en == E_OK){
    lRetVal_en = CanIf_XCore_LocalCore_Transmit(CanIfTxSduId, CanIfTxInfoPtr);
    }
   else{
   }
    return lRetVal_en;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_XCore_LocalCore_Transmit(
                                                    PduIdType CanIfTxSduId,
                                                    const PduInfoType * CanIfTxInfoPtr
                                               )
{
    Std_ReturnType lRetVal_en           = E_NOT_OK;
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
    uint8 Ctrl_Pdu_Var;
    uint8 Pdu_mode_Lcl;
     uint8 Ctrl_mode_Lcl;
    CanIf_ControllerStateType * lControllerState_en;
    Can_PduType lPduInfo_st          = {NULL_PTR, 0, 0, 0};
    Can_ReturnType lCanStatus_en        = CAN_NOT_OK;
    Can_HwHandleType lHth_uo              = 0;
    uint16 ltxPduCustId_t;

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    uint8 lMaxSduLength_u8     = 0;
#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    uint8 CanifMSBbits_u8;
#endif
#endif
   PduLengthType lSduLength = 0;
   uint8 lControllerId_u8 = 0;
   uint32 lCanId_u32 = 0;

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    uint32 * lDynId_p;
#endif

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
    CANIF_DET_REPORT_ERROR_NOT_OK((ltxPduCustId_t == 0xFFFFu), CANIF_TRANSMIT_SID, CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfTxInfoPtr->SduDataPtr), CANIF_TRANSMIT_SID, CANIF_E_PARAM_POINTER)
    lHth_uo           = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanObjectId;
    lControllerId_u8  = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;
    lControllerState_en = CanIf_Lok_ControllerState_ast + lControllerId_u8;
    Ctrl_Pdu_Var=lControllerState_en->Ctrl_Pdu_mode;
    Pdu_mode_Lcl=  Ctrl_Pdu_Var& BIT_MASK_CTRL_MODE;
    Ctrl_mode_Lcl= (Ctrl_Pdu_Var& BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT;

    CANIF_DET_REPORT_ERROR_NOT_OK(((Pdu_mode_Lcl == (uint8)CANIF_OFFLINE)||(Ctrl_mode_Lcl == (uint8)CANIF_CS_STOPPED)), \
                                                CANIF_TRANSMIT_SID, CANIF_E_STOPPED)

    {
        if(
                (( Ctrl_mode_Lcl == (uint8)CANIF_CS_STARTED) && (Pdu_mode_Lcl == (uint8)CANIF_ONLINE))
        #if(CANIF_USER_TP_TX_OFFLINE_MODE != STD_OFF)

                ||((Ctrl_mode_Lcl == (uint8)CANIF_CS_STARTED) && (((Pdu_mode_Lcl  == (uint8)CANIF_TX_TP_ONLINE) && \
                        (lTxPduConfig_pst->TxPduTxUserUL == CAN_TP)) ||(( Pdu_mode_Lcl == (uint8)CANIF_TX_USER_TP_ONLINE) &&       \
                        ((lTxPduConfig_pst->TxPduTxUserUL == USER) || (lTxPduConfig_pst->TxPduTxUserUL == CAN_TP)))))
        #endif

              )
    {
#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
        if(lTxPduConfig_pst->TxPduType!= CANIF_STATIC)
        {

            lDynId_p = &CanIf_DynTxPduCanId_au32[0];

            lPduInfo_st.id = (Can_IdType)*(lDynId_p + (lTxPduConfig_pst->TxPduType));

                if(CanIfTxInfoPtr->SduLength>lTxPduConfig_pst->TxPduLength_u8)
                {
                    lSduLength = lTxPduConfig_pst->TxPduLength_u8;
                }
                else
                {
                    lSduLength = CanIfTxInfoPtr->SduLength;
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
                       lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
                }
            else{
                }
                    if( CanIfTxInfoPtr->SduLength > lTxPduConfig_pst->TxPduLength_u8 )
                    {
                        lSduLength = lTxPduConfig_pst->TxPduLength_u8;
                    }
                    else
                    {
                        lSduLength = CanIfTxInfoPtr->SduLength;
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
    lCanStatus_en = CanIf_Write_Integration(lHth_uo, &lPduInfo_st);

        if(lCanStatus_en == CAN_OK)
        {
            lRetVal_en = E_OK;
        }
        else if(lCanStatus_en == CAN_BUSY)
        {
            lRetVal_en = E_NOT_OK;
        }
        else
        {
            lRetVal_en = E_NOT_OK;
        }
    }
#if(CANIF_TXOFFLINEACTIVE_SUPPORT == STD_ON)
    else if(((uint8)CANIF_CS_STARTED == Ctrl_mode_Lcl )&&
                (Pdu_mode_Lcl == (uint8)CANIF_TX_OFFLINE_ACTIVE))
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
Std_ReturnType CanIf_CancelTransmit(
                                                    PduIdType CanIfTxSduId

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
