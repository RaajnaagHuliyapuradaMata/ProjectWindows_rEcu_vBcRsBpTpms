

#include "CanIf_Prv.h"

#if (CANIF_DIRECT_HW_WRITE == STD_ON)

#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_DirectHw_Write (const uint32 * p_tx_data_buff_u32,
    uint32 data_len_u32,
    const rba_CanDirectHWInfo_o * hw_info_po)
{
    uint8 lControllerId_u8    = 0;
    uint16 ltxPduCustId_t;

    Std_ReturnType Status;

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[hw_info_po->swPduHandle];

    lControllerId_u8 =  CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[ltxPduCustId_t].CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;

    if (CANIF_CS_STARTED == ((CanIf_Lok_ControllerState_ast[lControllerId_u8].Ctrl_Pdu_mode &BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT))
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

Std_ReturnType CanIf_Get_DirectHw_Info (PduIdType CanTxPduId,
                                                  rba_CanDirectHWInfo_o * hw_info_po

                                                                )
{

    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;

    uint16 ltxPduCustId_t;

    Can_PduType PduInfo_Write;
    Std_ReturnType Status;

   #if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)

    uint32 * DynIdPtr_Temp;
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
void CanIf_ControllerErrorPassive(uint8 ControllerId)
{

#if (CANIF_RB_ERROR_PASSIVE_SUPPORT != STD_OFF)
    const CanIf_CallbackFuncType * CallBackPtr_Temp;

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
void CanIf_ResetDynamicTxId(PduIdType CanTxPduId)
{
#if(CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
    uint16 ltxPduCustId_t;
    Can_IdType LdCanIdType;
    uint32 * lDynId_p;

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
Std_ReturnType CanIf_Rn_ReadTxPduCanId(
                                                    PduIdType CanIfTxPduId,
                                                    uint32 * TxPduCanId)
{
    Std_ReturnType RetVal = E_NOT_OK;
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    uint32 * lDynId_p;
#endif
    uint32 lCanId_u32             = 0;
    uint16 ltxPduCustId_t;
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
      if(lTxPduConfig_pst->TxPduCanId != 0xFFFFFFFFu){
                lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
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
Std_ReturnType CanIf_Rn_ReadRxPduCanId( PduIdType CanIfRxPduId,
        uint32 * RxPduCanId)
{
    Std_ReturnType Status_t = E_OK;
    const CanIf_Cfg_RxPduType_tst * RxPduCfg_pcst;

#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

    const CanIf_Cfg_Hrhtype_tst * HrhCfg_pcst;
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK(CanIf_Lok_InitStatus_b == FALSE, CANIF_RB_READRXPDUCANID_SID,CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfRxPduId>=CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t), CANIF_READ_RX_MSG_ID_SID,
            CANIF_E_INVALID_RXPDUID)

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxPduId]== CANIF_INVALID_ID), CANIF_READ_RX_MSG_ID_SID,
                        CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxPduId];

#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

    HrhCfg_pcst = (CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst) + RxPduCfg_pcst->Hrhref_t;

    CANIF_DET_REPORT_ERROR_NOT_OK(HrhCfg_pcst->HrhInfo_e == CANIF_PRV_BASIC_RANGE_E, CANIF_READ_RX_MSG_ID_SID, \
                                                                                    CANIF_E_INVALID_RXPDUID)
#endif

        *RxPduCanId = (uint32)RxPduCfg_pcst->RxPduCanId;

    return (Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_ReturnTxPduId(
                                                     PduIdType CanIfTxTargetPduId,
                                                    PduIdType * CanIfTxPduIdPtr
                                                    )
{
    uint16_least CanIf_TotalTxPduId;
    PduIdType PduIdx_Temp;
    Std_ReturnType Ret_Val = E_NOT_OK;
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
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
Std_ReturnType CanIf_ReturnRxPduId(PduIdType CanIfRxTargetPduId,
        PduIdType * CanIfRxPduIdPtr)
{
    PduIdType PduIdx_t;

    Std_ReturnType Status_t= E_NOT_OK;

    const CanIf_Cfg_RxPduType_tst * RxPduCfg_pcst;

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

