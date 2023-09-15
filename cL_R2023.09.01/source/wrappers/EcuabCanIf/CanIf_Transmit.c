#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"

Std_ReturnType CanIf_Transmit(
            PduIdType    CanIfTxSduId
   ,  const PduInfoType* CanIfTxInfoPtr
){
         Std_ReturnType             lRetVal_en       = E_OK;
         uint16                     ltxPduCustId_t   = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
   const CanIf_Cfg_TxPduConfig_tst* lTxPduConfig_pst = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

   if(
         (
               lTxPduConfig_pst->TxTruncEnabled_b
            == FALSE
         )
      && (
               CanIfTxInfoPtr->SduLength
            >  (uint32)lTxPduConfig_pst->TxPduLength_u8
         )
   ){
      lRetVal_en = E_NOT_OK;
   }
   else{
      lRetVal_en = CanIf_XCore_LocalCore_Transmit(
            CanIfTxSduId
         ,  CanIfTxInfoPtr
      );
   }
   return lRetVal_en;
}

Std_ReturnType CanIf_XCore_LocalCore_Transmit(
            PduIdType    CanIfTxSduId
   ,  const PduInfoType* CanIfTxInfoPtr
){
         Std_ReturnType             lRetVal_en            = E_NOT_OK;
         Can_PduType                lPduInfo_st          = {NULL_PTR, 0, 0, 0};
         Can_ReturnType             lCanStatus_en        = CAN_NOT_OK;
         PduLengthType              lSduLength           = 0;
         uint32                     lCanId_u32           = 0;
         uint16                     ltxPduCustId_t       = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
   const CanIf_Cfg_TxPduConfig_tst* lTxPduConfig_pst     = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
         Can_HwHandleType           lHth_uo              = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanObjectId;
         uint8                      lControllerId_u8     = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr->CtrlId;
         CanIf_ControllerStateType* lControllerState_en  = CanIf_Lok_ControllerState_ast + lControllerId_u8;
         uint8                      Ctrl_Pdu_Var         = lControllerState_en->Ctrl_Pdu_mode;
         uint8                      Pdu_mode_Lcl         = Ctrl_Pdu_Var & BIT_MASK_CTRL_MODE;
         uint8                      Ctrl_mode_Lcl        = (Ctrl_Pdu_Var& BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT;
   if(
   (( Ctrl_mode_Lcl == (uint8)CANIF_CS_STARTED) && (Pdu_mode_Lcl == (uint8)CANIF_ONLINE))
   ){
      if(lTxPduConfig_pst->TxPduCanId != 0xFFFFFFFFu){
         lCanId_u32 = lTxPduConfig_pst->TxPduCanId;
      }
      else{
      }

      if(
            CanIfTxInfoPtr->SduLength
         >  lTxPduConfig_pst->TxPduLength_u8
      ){
         lSduLength = lTxPduConfig_pst->TxPduLength_u8;
      }
      else{
         lSduLength = CanIfTxInfoPtr->SduLength;
      }

      lPduInfo_st.id           = (Can_IdType)lCanId_u32;
      lPduInfo_st.id          &= CANIF_MSB_BIT_RESET;
      lPduInfo_st.id          |= ( ((Can_IdType)lTxPduConfig_pst->TxPduCanIdType) << CANIF_CANID_BIT_SHIFT );
      lPduInfo_st.swPduHandle  = lTxPduConfig_pst->TxPduId;
      lPduInfo_st.sdu          = CanIfTxInfoPtr->SduDataPtr;
      lPduInfo_st.length       = (uint8)lSduLength;
      lCanStatus_en = CanIf_Write_Integration(lHth_uo, &lPduInfo_st);

           if(lCanStatus_en == CAN_OK  ){lRetVal_en = E_OK;}
      else if(lCanStatus_en == CAN_BUSY){lRetVal_en = E_NOT_OK;}
      else                              {lRetVal_en = E_NOT_OK;}
   }
   else{
   }
   return lRetVal_en;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"


