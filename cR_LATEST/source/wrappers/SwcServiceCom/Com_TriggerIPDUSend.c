#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

//TBD: Optimize code
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_TriggerIPDUSend(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId
){
   Com_TxIpduRamPtrType   TxIpduRamPtr   = &COM_GET_TXPDURAM_S(PduId);
   Com_TxIpduConstPtrType TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);
   if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)PduId)){
      Com_SendIpduInfo sendIpduFlag_u16  = COM_CLEAR_SENDIPDU_FLAGS;
      sendIpduFlag_u16.isEventTrig       = COM_SET;
      sendIpduFlag_u16.isModeChangd      = COM_RESET;
      sendIpduFlag_u16.isTimeoutReq      = (0u != TxIPduConstPtr->Timeout_Fact)? COM_SET : COM_RESET;
      sendIpduFlag_u16.ignoreRepetitions = COM_SET;
      Com_Lok_SendIpdu((Type_SwcServiceCom_tIdPdu) PduId, sendIpduFlag_u16);
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

