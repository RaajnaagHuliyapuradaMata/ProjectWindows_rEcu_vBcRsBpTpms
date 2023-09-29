#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_InternalMainFunctionRx(
   VAR(Com_MainFuncType,AUTOMATIC) RxMainFuncId
){
   VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC) ltIndexIdPduRx;
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) ltIdIPduRxStart;
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) ltIdIPduRxEnd;

   if(COM_INIT == Com_Uninit_Flag){
      ltIdIPduRxStart    =                   Com_MainFunctionCfg[RxMainFuncId].StartIPduId;
      ltIdIPduRxEnd      = ltIdIPduRxStart + Com_MainFunctionCfg[RxMainFuncId].NumOfIpdus;

      for(
         ltIndexIdPduRx = (Type_SwcServiceCom_tIdPdu)ltIdIPduRxStart;
         ltIndexIdPduRx < (Type_SwcServiceCom_tIdPdu)ltIdIPduRxEnd;
         ltIndexIdPduRx ++
      ){
         if(
            Com_GetRamValue(
                  RXIPDU
               ,  _PDUSTATUS
               ,  Com_RxIpduRam_s[ltIndexIdPduRx].RxFlags
            )
         ){
            Com_SetRamValue(
                  RXIPDU
               ,  _INDICATION
               ,  Com_RxIpduRam_s[ltIndexIdPduRx].RxFlags
               ,  COM_FALSE
            );
         }
      }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
