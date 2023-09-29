#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

//TBD: Optimize code
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) TxPduId
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
){
   VAR(Std_ReturnType,                AUTOMATIC) Status             = E_OK;
       Com_TxIpduConstPtrType                    TxIPduConstPtr     = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
   VAR(uint16,                        AUTOMATIC) ConstByteValue_u16 = TxIPduConstPtr->txIPduFields;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) Size               = TxIPduConstPtr->Size;

   if(
      !(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)TxPduId))
   ){
      Status = E_NOT_OK;
   }
   SchM_Enter_Com_TxIpduProtArea(TRIGGERTRANSMIT);
   Com_ByteCopy(
         PduInfoPtr->SduDataPtr
      ,  TxIPduConstPtr->BuffPtr
      ,  (uint32)Size
   );
   PduInfoPtr ->SduLength = Size;
   SchM_Exit_Com_TxIpduProtArea(TRIGGERTRANSMIT);
   if(
         (E_NOT_OK  != Status)
      && (COM_FALSE != Com_GetValue(TXIPDU, _ISCALLOUTFRMTRIGTRANS, ConstByteValue_u16))
   ){
      (void)TxIPduConstPtr->CallOut(
            TxPduId
         ,  PduInfoPtr
      );
   }
   return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

