#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void,COM_CODE) Com_TxChangeMode(
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) TxIpduId
){
   VAR(uint8,   AUTOMATIC)    LatestTransMode_u8;
   VAR(boolean, AUTOMATIC)    Mode           = COM_TRUE;
       Com_TxIpduConstPtrType TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
       Com_TxIpduRamPtrType   TxIpduRamPtr   = &COM_GET_TXPDURAM_S(TxIpduId);
   Com_SetRamValue(
         TXIPDU
      ,  _TXMODESTATE
      ,  TxIpduRamPtr->Com_TransMode
      ,  Mode
   );
   Com_SetCurrentTxModePtr(
         TxIpduRamPtr
      ,  TxIPduConstPtr
      ,  Com_GetValue(
               TXIPDU
            ,  _TMS
            ,  TxIPduConstPtr->txIPduFields
         )
      ,  Mode
   );
   LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;
   Com_SetRamValue(
         TXIPDU
      ,  _LATESTMODE
      ,  TxIpduRamPtr->Com_TransMode
      ,  LatestTransMode_u8
   );
   if(
         0u
      != (
               LatestTransMode_u8
            &  COM_TXMODE_MIXED
         )
   ){
        TxIpduRamPtr->Com_Tick_Tx   = COM_GET_TXIPDU_TIMEPERIOD(TxIpduId, (TxIpduRamPtr->CurrentTxModePtr));
        TxIpduRamPtr->Com_n_Tick_Tx = 0;
        TxIpduRamPtr->Com_n         = 0;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

