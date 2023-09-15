#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_ControllerErrorPassive(uint8 ControllerId){
    (void)ControllerId;
}

void CanIf_ResetDynamicTxId(Type_SwcServiceCom_tIdPdu CanTxPduId){
    (void)CanTxPduId;
}

Std_ReturnType CanIf_Rn_ReadTxPduCanId(
       Type_SwcServiceCom_tIdPdu CanIfTxPduId
   ,   uint32*   TxPduCanId
){
   Std_ReturnType RetVal = E_NOT_OK;
   const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
   uint32 lCanId_u32             = 0;
   uint16 ltxPduCustId_t;
   ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxPduId];
   lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
   if(
         lTxPduConfig_pst->TxPduCanId
      != 0xFFFFFFFFu
   ){
      lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
      lCanId_u32 &= CANIF_MSB_BIT_RESET;
      lCanId_u32 |= ( ((Can_IdType)lTxPduConfig_pst->TxPduCanIdType) << CANIF_CANID_BIT_SHIFT );
      RetVal = E_OK;
   }
   if(
         RetVal
      == E_OK
   ){
      *TxPduCanId  = lCanId_u32;
   }
   return RetVal;
}

Std_ReturnType CanIf_Rn_ReadRxPduCanId(
      Type_SwcServiceCom_tIdPdu CanIfRxPduId
   ,  uint32*   RxPduCanId
){
   Std_ReturnType Status_t = E_OK;
   const CanIf_Cfg_RxPduType_tst *RxPduCfg_pcst;
   RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxPduId];
   *RxPduCanId = (uint32)RxPduCfg_pcst->RxPduCanId;
   return (Status_t);
}

Std_ReturnType CanIf_ReturnTxPduId(
      Type_SwcServiceCom_tIdPdu  CanIfTxTargetPduId
   ,  Type_SwcServiceCom_tIdPdu* CanIfTxPduIdPtr
){
   uint16_least CanIf_TotalTxPduId;
   Type_SwcServiceCom_tIdPdu PduIdx_Temp;
   Std_ReturnType Ret_Val = E_NOT_OK;
   const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
   CanIf_TotalTxPduId = CanIf_Lok_ConfigSet_tpst->NumOfTxPdus;
   lTxPduConfig_pst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr;
   for(PduIdx_Temp=0; PduIdx_Temp<CanIf_TotalTxPduId; PduIdx_Temp++){
        if((lTxPduConfig_pst[PduIdx_Temp].TxPduTargetPduId == CanIfTxTargetPduId) &&
                                        (lTxPduConfig_pst[PduIdx_Temp].TxPduTxUserUL==USER)){
            *CanIfTxPduIdPtr = lTxPduConfig_pst[PduIdx_Temp].TxPduId;
            Ret_Val = E_OK;
            break;
        }
   }
   return Ret_Val;
}

Std_ReturnType CanIf_ReturnRxPduId(
      Type_SwcServiceCom_tIdPdu  CanIfRxTargetPduId
   ,  Type_SwcServiceCom_tIdPdu* CanIfRxPduIdPtr
){
         Type_SwcServiceCom_tIdPdu                PduIdx_t;
         Std_ReturnType           Status_t      = E_NOT_OK;
   const CanIf_Cfg_RxPduType_tst* RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst;

   for(
      PduIdx_t = 0;
      PduIdx_t < CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t;
      PduIdx_t ++
   ){
      if(
            (RxPduCfg_pcst[PduIdx_t].RxPduTargetId_t == CanIfRxTargetPduId)
         && (RxPduCfg_pcst[PduIdx_t].IndexForUL_u8   > (7u+CanIf_Lok_ConfigSet_tpst->NumCddRxPdus_t))
      ){
         *CanIfRxPduIdPtr = PduIdx_t;
         Status_t = E_OK;
         break;
      }
   }
   return Status_t;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

