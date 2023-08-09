

#include "CanIf_Prv.h"

#if (CANIF_DIRECT_HW_WRITE == STD_ON)

#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_DirectHw_Write (P2CONST(uint32, AUTOMATIC, CANIF_APPL_DATA) p_tx_data_buff_u32,
    VAR(uint32, AUTOMATIC) data_len_u32,
    P2CONST(rba_CanDirectHWInfo_o, AUTOMATIC, CANIF_APPL_DATA) hw_info_po)
{
    VAR (uint8, AUTOMATIC) lControllerId_u8    = 0;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;

    VAR (   CanIf_ControllerModeType, AUTOMATIC                 ) lDeviceMode_en;

    VAR (Std_ReturnType, AUTOMATIC ) Status;

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[hw_info_po->swPduHandle];

    lControllerId_u8 =  CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[ltxPduCustId_t].CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;

    lDeviceMode_en = CanIf_Lok_ControllerState_ast[lControllerId_u8].DeviceMode;

    if (CANIF_CS_STARTED == lDeviceMode_en)
    {
        Status = rba_Can_DirectHw_Write (p_tx_data_buff_u32, data_len_u32, hw_info_po);
    }
    else
    {
        Status = E_NOT_OK;
    }

    return Status;
}
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.h"

#endif

#if (CANIF_DIRECT_HW_WRITE == STD_ON)

#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_Get_DirectHw_Info (VAR(PduIdType, AUTOMATIC) CanTxPduId,
                                                  P2VAR(rba_CanDirectHWInfo_o, AUTOMATIC, CANIF_APPL_DATA) hw_info_po

                                                                )
{

    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;

    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;

    VAR(Can_PduType,AUTOMATIC) PduInfo_Write;
    VAR(Std_ReturnType,AUTOMATIC) Status;

   #if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) DynIdPtr_Temp;
   #endif

    Status = E_NOT_OK;

    #if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)

    DynIdPtr_Temp = CanIf_DynTxPduCanId_au32;
    #endif

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];

    if(ltxPduCustId_t == 0xFFFFu)
    {

    }
    else
    {
        lTxPduConfig_pst = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

        hw_info_po->swPduHandle = lTxPduConfig_pst->TxPduId;
        hw_info_po->Handle_uo = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanObjectId;

        PduInfo_Write.swPduHandle = hw_info_po->swPduHandle;

        #if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)

        if(lTxPduConfig_pst->TxPduType != CANIF_STATIC)
        {

            PduInfo_Write.id = (Can_IdType)*(DynIdPtr_Temp + (lTxPduConfig_pst->TxPduType));

        }
        else
        #endif
        {

                PduInfo_Write.id = (Can_IdType)((lTxPduConfig_pst->TxPduCanId));

                PduInfo_Write.id &= CANIF_MSB_BIT_RESET;
                PduInfo_Write.id |= (((Can_IdType)(lTxPduConfig_pst->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);

        }

        Status = rba_Can_Get_DirectHw_Info((Can_HwHandleType)hw_info_po->Handle_uo, &PduInfo_Write, hw_info_po);
    }
    return (Status);
}
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.h"

#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ControllerErrorPassive(VAR(uint8, AUTOMATIC) ControllerId)
{

#if (CANIF_RB_ERROR_PASSIVE_SUPPORT != STD_OFF)
    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;

    CANIF_DET_REPORT_ERROR((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONTROLLER_ERRORPASSIVE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_CONTROLLER_ERRORPASSIVE_SID, CANIF_E_PARAM_CONTROLLER)

    CallBackPtr_Temp = &CanIf_Callback;

    if(NULL_PTR != CallBackPtr_Temp->User_ControllerErrorPassive)
    {
        CallBackPtr_Temp->User_ControllerErrorPassive(ControllerId);
    }
#else

    (void)ControllerId;
#endif
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ResetDynamicTxId(VAR(PduIdType, AUTOMATIC) CanTxPduId)
{
#if(CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    VAR(Can_IdType, AUTOMATIC) LdCanIdType;

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) lDynId_p;

    CANIF_DET_REPORT_ERROR((FALSE == CanIf_Lok_InitStatus_b), CANIF_RESET_DYNAMIC_TXID_SID,CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR((CanTxPduId >= CANIF_TOTAL_TXPDUS), CANIF_RESET_DYNAMIC_TXID_SID,CANIF_E_PARAM_LPDU)

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];

    CANIF_DET_REPORT_ERROR((ltxPduCustId_t == 0xFFFFu), CANIF_RESET_DYNAMIC_TXID_SID,CANIF_E_PARAM_LPDU)

    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

    CANIF_DET_REPORT_ERROR((CANIF_STATIC == lTxPduConfig_pst->TxPduType), CANIF_RESET_DYNAMIC_TXID_SID,CANIF_E_PARAM_LPDU)

    lDynId_p = CanIf_DynTxPduCanId_au32;

    if(lTxPduConfig_pst->TxPduType != CANIF_STATIC)
    {

        LdCanIdType = (lTxPduConfig_pst->TxPduCanId);
        LdCanIdType &= CANIF_MSB_BIT_RESET;
        LdCanIdType |= (((Can_IdType)(lTxPduConfig_pst->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);

        *(lDynId_p + (lTxPduConfig_pst->TxPduType)) = LdCanIdType;

    }
#else
    (void)CanTxPduId;
#endif
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Rn_ReadTxPduCanId(
                                                    VAR(PduIdType,AUTOMATIC) CanIfTxPduId,
                                                    P2VAR(uint32, AUTOMATIC, AUTOMATIC) TxPduCanId)
{

    VAR(Std_ReturnType,AUTOMATIC) RetVal = E_NOT_OK;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    P2VAR(uint32,AUTOMATIC,AUTOMATIC) lDynId_p;
#endif
    VAR (uint32, AUTOMATIC         ) lCanId_u32             = 0;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_RB_READ_TXPDU_CANID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfTxPduId >= CANIF_TOTAL_TXPDUS), \
                                                                    CANIF_RB_READ_TXPDU_CANID, CANIF_E_INVALID_TXPDUID)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxPduId];
    CANIF_DET_REPORT_ERROR_NOT_OK((ltxPduCustId_t == 0xFFFFu), CANIF_RB_READ_TXPDU_CANID, CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
        if(lTxPduConfig_pst->TxPduType!= CANIF_STATIC)
        {
           lDynId_p = &CanIf_DynTxPduCanId_au32[0];
           lCanId_u32 = (Can_IdType)*(lDynId_p + (lTxPduConfig_pst->TxPduType));
           RetVal = E_OK;
        }
        else
#endif
        {
            if(lTxPduConfig_pst->TxPduCanId!= 0xFFFFFFFFu)
            {
#if (CANIF_RB_CALIBRATION == STD_OFF)
                lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
#else
                lCanId_u32 = lTxPduConfig_pst->getTxPduCanId();
#endif
                lCanId_u32 &= CANIF_MSB_BIT_RESET;
                lCanId_u32 |= ( ((Can_IdType)lTxPduConfig_pst->TxPduCanIdType) << CANIF_CANID_BIT_SHIFT );
                RetVal = E_OK;
            }
        }
        if(RetVal == E_OK)
        {
            *TxPduCanId  = lCanId_u32;
        }
    return RetVal;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Rn_ReadRxPduCanId( VAR(PduIdType, AUTOMATIC)CanIfRxPduId,
        P2VAR(uint32, AUTOMATIC, CANIF_APPL_DATA)RxPduCanId)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t = E_OK;

    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

#if (CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    P2VAR(Can_IdType,AUTOMATIC,AUTOMATIC) DynRxPduIdPtr_Temp;
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK(CanIf_Lok_InitStatus_b == FALSE, CANIF_RB_READRXPDUCANID_SID,CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfRxPduId>=CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t), CANIF_READ_RX_MSG_ID_SID,
            CANIF_E_INVALID_RXPDUID)

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxPduId]== INVALID_ID), CANIF_READ_RX_MSG_ID_SID,
                        CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxPduId];

    CANIF_DET_REPORT_ERROR_NOT_OK(RxPduCfg_pcst->RxPduCanId == 0xFFFFFFFFu, CANIF_READ_RX_MSG_ID_SID, \
                                                                                    CANIF_E_INVALID_RXPDUID)

#if (CANIF_RB_CHANGERXPDUID_API != STD_OFF)
    if((RxPduCfg_pcst ->RxPduType) != CANIF_STATIC)
    {

        DynRxPduIdPtr_Temp = &CanIf_DynRxPduCanId_au32[0];

        *RxPduCanId = (Can_IdType)*(DynRxPduIdPtr_Temp + (RxPduCfg_pcst ->RxPduType));
    }
    else
#endif

    {

        #if (CANIF_RB_CALIBRATION == STD_ON)
        if(RxPduCfg_pcst->getCanId !=NULL_PTR)
        {
            *RxPduCanId = (uint32)RxPduCfg_pcst->getCanId();
        }
        else
        {
            *RxPduCanId = (uint32)RxPduCfg_pcst->RxPduCanId;
        }
        #else
        *RxPduCanId = (uint32)RxPduCfg_pcst->RxPduCanId;
        #endif
    }

    return (Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_ReturnTxPduId(
                                                     VAR(PduIdType, AUTOMATIC) CanIfTxTargetPduId,
                                                    P2VAR(PduIdType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxPduIdPtr
                                                    )
{
    VAR (uint16_least, AUTOMATIC) CanIf_TotalTxPduId;
    VAR (PduIdType,AUTOMATIC) PduIdx_Temp;
    VAR (Std_ReturnType,AUTOMATIC) Ret_Val = E_NOT_OK;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    CANIF_DET_REPORT_ERROR_NOT_OK(CanIf_Lok_InitStatus_b == FALSE, CANIF_RETURN_TX_PDU_ID_SID,CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfTxPduIdPtr), CANIF_RETURN_TX_PDU_ID_SID,CANIF_E_PARAM_POINTER)
    CanIf_TotalTxPduId = CanIf_Lok_ConfigSet_tpst->NumOfTxPdus;
    lTxPduConfig_pst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr;

    for(PduIdx_Temp=0; PduIdx_Temp<CanIf_TotalTxPduId; PduIdx_Temp++)
    {
        if((lTxPduConfig_pst[PduIdx_Temp].TxPduTargetPduId == CanIfTxTargetPduId) &&
                                        (lTxPduConfig_pst[PduIdx_Temp].TxPduTxUserUL==USER))
        {
            *CanIfTxPduIdPtr = lTxPduConfig_pst[PduIdx_Temp].TxPduId;
            Ret_Val = E_OK;
            break;
        }

    }
    return Ret_Val;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReturnRxPduId(VAR(PduIdType, AUTOMATIC) CanIfRxTargetPduId,
        P2VAR(PduIdType, AUTOMATIC, AUTOMATIC) CanIfRxPduIdPtr)
{
    VAR (PduIdType,AUTOMATIC) PduIdx_t;
    VAR(Std_ReturnType,AUTOMATIC) Status_t= E_NOT_OK;
    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;
    CANIF_DET_REPORT_ERROR_NOT_OK(CanIf_Lok_InitStatus_b == FALSE, CANIF_RETURN_RX_PDU_ID_SID,CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfRxPduIdPtr), CANIF_RETURN_RX_PDU_ID_SID,CANIF_E_PARAM_POINTER)
    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst;

    for( PduIdx_t=0;  PduIdx_t<CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t;  PduIdx_t++)
    {
        if((RxPduCfg_pcst[PduIdx_t].RxPduTargetId_t == CanIfRxTargetPduId) &&
                (RxPduCfg_pcst[PduIdx_t].IndexForUL_u8 >(7u+CanIf_Lok_ConfigSet_tpst->NumCddRxPdus_t)))
        {
            *CanIfRxPduIdPtr = PduIdx_t;
            Status_t = E_OK;
            break;
        }
    }
    return Status_t;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#if ((CANIF_RB_READMSGID_API == STD_ON))
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(uint32, CANIF_CODE) CanIf_ReadTxMsgId( VAR(uint16, AUTOMATIC) msgHandleTx_u16 )
{
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) TxPduConfigTable_Temp;
    VAR(Can_IdType, AUTOMATIC) CanId = 0xFFFFFFFFu;
    VAR(PduIdType, AUTOMATIC) index;
    VAR (uint16_least, AUTOMATIC) CanIf_TotalTxPdus;
    CANIF_DET_REPORT_ERROR(CanIf_Lok_InitStatus_b == FALSE, CANIF_READ_TX_MSG_ID_SID,CANIF_E_UNINIT)
    lTxPduConfig_pst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr;
    CanIf_TotalTxPdus = CanIf_Lok_ConfigSet_tpst->NumOfTxPdus;

    for(index = 0; index < CanIf_TotalTxPdus; index++)
    {
        TxPduConfigTable_Temp = lTxPduConfig_pst + index;
        if((uint16)(TxPduConfigTable_Temp->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanObjectId) == msgHandleTx_u16)
        {
#if ( CANIF_RB_CALIBRATION == STD_ON )
            if(TxPduConfigTable_Temp->getTxPduCanId != NULL_PTR)
            {
                CanId = TxPduConfigTable_Temp->getTxPduCanId();
            }
            else
#endif
            {
                CanId = TxPduConfigTable_Temp->TxPduCanId;
            }
            break;
        }
    }

    return ( (uint32)CanId );
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_RB_READMSGID_API == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(uint32, CANIF_CODE) CanIf_ReadRxMsgId( VAR(uint16, AUTOMATIC) msgHandleRx_u16 )
{

    P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst;

    VAR(Can_IdType, AUTOMATIC) lCanId_t;

    lCanId_t = 0;

    CANIF_DET_REPORT_ERROR_NOT_OK(CanIf_Lok_InitStatus_b == FALSE, CANIF_READ_RX_MSG_ID_SID,CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((msgHandleRx_u16>=CANIF_CFG_TOTAL_HOH_NUM), CANIF_READ_RX_MSG_ID_SID,
            CANIF_E_PARAM_HRH)

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[msgHandleRx_u16] ==  INVALID_ID), CANIF_READ_RX_MSG_ID_SID,
            CANIF_E_PARAM_HRH)

    HrhCfg_pcst = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[msgHandleRx_u16];

    CANIF_DET_REPORT_ERROR_NOT_OK((HrhCfg_pcst->HrhInfo_e != CANIF_PRV_FULL_E), CANIF_READ_RX_MSG_ID_SID,
            CANIF_E_PARAM_HRH)

    lCanId_t = HrhCfg_pcst->CanId_t;

    return (lCanId_t);

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
#if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Rn_ChangeRxPduCanId(VAR(PduIdType,AUTOMATIC) CanRxPduId, VAR(Can_IdType,AUTOMATIC) CanId)
{
    P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst;
    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;
    P2VAR(Can_IdType,AUTOMATIC,AUTOMATIC) DynRxPduIdPtr_Temp;
    VAR(Can_HwHandleType,AUTOMATIC) CanHrh_u8;
    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) ControllerState_ps;
    VAR (CanIf_ControllerModeType, AUTOMATIC) DeviceMode_tst;
    VAR (Std_ReturnType, AUTOMATIC ) Status = E_NOT_OK;

#if CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF
     VAR(uint8, AUTOMATIC)canifMSBbits_u8;
#endif

     CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_RB_CHANGERXPDUID_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanRxPduId >= (CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t)), \
                    CANIF_RB_CHANGERXPDUID_SID,CANIF_E_INVALID_RXPDUID)

     CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanRxPduId]== INVALID_ID), \
                                    CANIF_RB_CHANGERXPDUID_SID,CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = (CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst) + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanRxPduId];

   CANIF_DET_REPORT_ERROR_NOT_OK((CANIF_STATIC == (RxPduCfg_pcst->RxPduType)), CANIF_RB_CHANGERXPDUID_SID,CANIF_E_INVALID_RXPDUID)

#if CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF

    canifMSBbits_u8 = (uint8)(CanId >> CANIF_CANID_BIT_SHIFT);

    CANIF_DET_REPORT_ERROR_NOT_OK((((canifMSBbits_u8 == CANIF_ZERO)|| \
            (canifMSBbits_u8 == CANIF_ONE)) && ((CanId & CANIF_MSB_BIT_RESET) > CANIF_CAN_STD_VAL)),
            CANIF_RB_CHANGERXPDUID_SID, CANIF_E_PARAM_CANID)

    CANIF_DET_REPORT_ERROR_NOT_OK((((canifMSBbits_u8 == CANIF_TWO)||(canifMSBbits_u8 == CANIF_THREE)) && \
            ((CanId & CANIF_MSB_BIT_RESET)  > CANIF_CAN_XTD_VAL)), CANIF_RB_CHANGERXPDUID_SID, CANIF_E_PARAM_CANID)
#endif

    HrhCfg_pcst = (CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst) + RxPduCfg_pcst->Hrhref_t;

    CanHrh_u8 = HrhCfg_pcst -> CanObjectId;

    ControllerState_ps = CanIf_Lok_ControllerState_ast + HrhCfg_pcst->ControllerId_u8;

    DeviceMode_tst = ControllerState_ps->DeviceMode;

    if( DeviceMode_tst  == CANIF_CS_STOPPED)
    {

        if((RxPduCfg_pcst ->RxPduType) != CANIF_STATIC)
        {

            DynRxPduIdPtr_Temp = &CanIf_DynRxPduCanId_au32[0] + (RxPduCfg_pcst ->RxPduType);

            *DynRxPduIdPtr_Temp = CanId;

            Status = rba_Can_ChangeRxCanId(CanHrh_u8, CanId);
        }
    }
    else
    {

        Status = E_NOT_OK;
    }

    return Status;

}

#endif

