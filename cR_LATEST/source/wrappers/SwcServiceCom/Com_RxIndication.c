#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_RxIndication(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC               ) RxPduId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
){
   VAR(boolean, AUTOMATIC) rxIpduCalloutStatus = COM_TRUE;
   if(
      Com_CheckRxIPduStatus(RxPduId)
   ){
      SchM_Enter_Com_RxPduBuffer();
      Com_RxIpduRam_s[RxPduId].RxIPduLength = (
            PduInfoPtr->SduLength
         <= CfgSwcServiceCom_castListInfoIpduRx[RxPduId].Size
      )
      ?  PduInfoPtr->SduLength
      :  CfgSwcServiceCom_castListInfoIpduRx[RxPduId].Size
      ;

      Com_SetRamValue(
            RXIPDU
         ,  _INDICATION
         ,  Com_RxIpduRam_s[RxPduId].RxFlags
         ,  COM_TRUE
      );
      SchM_Exit_Com_RxPduBuffer();

      if(NULL_PTR != CfgSwcServiceCom_castListInfoIpduRx[RxPduId].CallOut){
         rxIpduCalloutStatus = CfgSwcServiceCom_castListInfoIpduRx[RxPduId].CallOut(
               RxPduId
            ,  PduInfoPtr
         );
      }
      else{
      }
      if(COM_TRUE == rxIpduCalloutStatus){
         if(
               CfgSwcServiceCom_castListInfoIpduRx[RxPduId].No_Of_Sig_Ref
            >  0u
         ){
            Com_Lok_ProcessSignal(
                  RxPduId
               ,  PduInfoPtr
            );
         }
      }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
