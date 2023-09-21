#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_IPduTimeOut (VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_Modes       (VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_DirectMode  (VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_MixedMode   (VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_NoneMode    (VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_PeriodicMode(VAR(uint16_least, AUTOMATIC) TxPduId);
FUNC(void, COM_CODE) Com_Lok_MainFunctionTx_SendIPdu       (VAR(uint16_least, AUTOMATIC) TxPduId,  VAR(boolean, AUTOMATIC) SendIPdu);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_InternalMainFunctionTx(
   VAR(Com_MainFuncType,              AUTOMATIC) TxMainFuncId
){
   VAR(uint16_least,                  AUTOMATIC) Idx_Pdu_ui;
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) StartIPduId;
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) EndIPduId;
   VAR(boolean,                       AUTOMATIC) SendIPdu;
   VAR(boolean,                       AUTOMATIC) Timeout_Flag = COM_FALSE;
   VAR(boolean,                       AUTOMATIC) Notify_Flag  = COM_FALSE;
       Com_TxIpduConstPtrType                    TxIPduConstPtr;
       Com_TxIpduRamPtrType                      TxIpduRamPtr;
   if(
         Com_Uninit_Flag
      == COM_INIT
   ){
      StartIPduId    = COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).StartIPduId;
      EndIPduId      = StartIPduId + COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).NumOfIpdus;
      TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(StartIPduId);
      TxIpduRamPtr   = &COM_GET_TXPDURAM_S(StartIPduId);
      for(
         Idx_Pdu_ui = StartIPduId;
         Idx_Pdu_ui < EndIPduId;
         Idx_Pdu_ui ++
      ){
         if(
            Com_CheckTxIPduStatus(
               (Type_SwcServiceCom_tIdPdu)Idx_Pdu_ui
            )
         ){
            SchM_Enter_Com_TxIpduProtArea(MAINFUNCTIONTX);
            if(
                  Com_GetRamValue(
                        TXIPDU
                     ,  _CONFIR
                     ,  TxIpduRamPtr->Com_TxFlags
                  )
               == COM_TRUE
            ){
               Com_SetRamValue(
                     TXIPDU
                  ,  _CONFIR
                  ,  TxIpduRamPtr->Com_TxFlags
                  ,  COM_FALSE
               );
               Notify_Flag = (
                     Com_GetValue(
                           TXIPDU
                        ,  _SIGPROC
                        ,  TxIPduConstPtr->txIPduFields
                     )
                  == COM_DEFERRED
               );
            }
            else{
               Timeout_Flag = Com_Lok_MainFunctionTx_IPduTimeOut(
                  Idx_Pdu_ui
               );
            }
            SendIPdu = Com_Lok_MainFunctionTx_Modes(
               Idx_Pdu_ui
            );
            SchM_Exit_Com_TxIpduProtArea(MAINFUNCTIONTX);
            (void)Timeout_Flag;
            if(
                  Notify_Flag
               == COM_TRUE
            ){
               if(
                     TxIPduConstPtr->Notification_Cbk
                  != NULL_PTR
               ){
                  TxIPduConstPtr->Notification_Cbk();
               }
            }
            Com_Lok_MainFunctionTx_SendIPdu(
                  Idx_Pdu_ui
               ,  SendIPdu
            );
         }
         TxIPduConstPtr++;
         TxIpduRamPtr++;
      }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_TxIPduTimeOut
FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_IPduTimeOut(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,      AUTOMATIC) Timeout_Flag = COM_FALSE;
   Com_TxIpduRamPtrType         TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         (
               Com_GetRamValue(
                     TXIPDU
                  ,  _CONFIR
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            != COM_TRUE
         )
      && (
               Com_GetRamValue(
                     TXIPDU
                  ,  _TICKTXTO
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            == COM_START
         )
   ){
      if(
            TxIpduRamPtr->Com_TickTxTimeout
         != 0
      ){
         --TxIpduRamPtr->Com_TickTxTimeout;
      }
      else{
         Com_SetRamValue(
               TXIPDU
            ,  _TICKTXTO
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_STOP
         );
         TxIpduRamPtr->Com_n            = 0;
         TxIpduRamPtr->Com_MinDelayTick = 0;
         Timeout_Flag                   = COM_TRUE;
      }
   }
   return Timeout_Flag;
}

#endif

boolean Com_Lok_MainFunctionTx_Modes(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,      AUTOMATIC) SendIPdu     = COM_FALSE;
       Com_TxIpduRamPtrType     TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         TxIpduRamPtr->Com_MinDelayTick
      != 0
   ){
      --TxIpduRamPtr->Com_MinDelayTick;
   }
   switch(
      Com_GetRamValue(
            TXIPDU
         ,  _LATESTMODE
         ,  TxIpduRamPtr->Com_TransMode
      )
   ){
      case COM_TXMODE_DIRECT:   SendIPdu = Com_Lok_MainFunctionTx_DirectMode(   TxPduId); break;
      case COM_TXMODE_MIXED:    SendIPdu = Com_Lok_MainFunctionTx_MixedMode(    TxPduId); break;
      case COM_TXMODE_NONE:     SendIPdu = Com_Lok_MainFunctionTx_NoneMode(     TxPduId); break;
      case COM_TXMODE_PERIODIC: SendIPdu = Com_Lok_MainFunctionTx_PeriodicMode( TxPduId); break;
      default:                                                                            break;
   }
   return SendIPdu;
}

FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_DirectMode(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,    AUTOMATIC) SendIPdu     = COM_FALSE;
       Com_TxIpduRamPtrType   TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         TxIpduRamPtr->Com_n_Tick_Tx
      != 0
   ){
      --TxIpduRamPtr->Com_n_Tick_Tx;
   }
   if(
         TxIpduRamPtr->Com_MinDelayTick
      == 0
   ){
      if(
            Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags)
         == COM_TRUE
      ){
         SendIPdu = COM_TRUE;
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_FALSE
         );
      }
      else{
         if(
               (
                     TxIpduRamPtr->Com_n_Tick_Tx
                  == 0
               )
            && (
                     Com_GetRamValue(
                           TXIPDU
                        ,  _EVENTTRIG
                        ,  TxIpduRamPtr->Com_TxFlags
                     )
                  == COM_TRUE
               )
         ){
            SendIPdu = COM_TRUE;
         }
         else if(
               (
                     TxIpduRamPtr->Com_n_Tick_Tx
                  == 0
               )
            && (
                     TxIpduRamPtr->Com_n
                  != 0
               )
         ){
            SendIPdu = COM_TRUE;
         }
         else{
         }
      }
      if(
            TxIpduRamPtr->Com_n
         != 0
      ){
         if(
               TxIpduRamPtr->Com_n_Tick_Tx
            == 0
         ){
            TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
         }
      }
   }
   return SendIPdu;
}

FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_MixedMode(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,      AUTOMATIC) SendIPdu     = COM_FALSE;
       Com_TxIpduRamPtrType     TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         TxIpduRamPtr->Com_Tick_Tx
      != 0
   ){
      --TxIpduRamPtr->Com_Tick_Tx;
   }
   if(
         TxIpduRamPtr->Com_n_Tick_Tx
      != 0
   )
   {
      --TxIpduRamPtr ->Com_n_Tick_Tx;
   }
   if(
         TxIpduRamPtr->Com_MinDelayTick
      == 0
   ){
      if(
            Com_GetRamValue(
                  TXIPDU
               ,  _MDT
               ,  TxIpduRamPtr->Com_TxFlags
            )
         == COM_TRUE
      ){
         SendIPdu = COM_TRUE;
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_FALSE
         );
      }
      else{
         if(
               (
                     TxIpduRamPtr->Com_n_Tick_Tx
                  == 0
               )
            && (
                     Com_GetRamValue(
                           TXIPDU
                        ,  _EVENTTRIG
                        ,  TxIpduRamPtr->Com_TxFlags
                     )
                  == COM_TRUE
               )
         ){
            SendIPdu = COM_TRUE;
         }
         else if(
               (
                     TxIpduRamPtr->Com_n_Tick_Tx
                  == 0
               )
            && (
                     TxIpduRamPtr->Com_n
                  != 0
               )
         ){
            SendIPdu = COM_TRUE;
         }
         else{
            if(
                  (
                        TxIpduRamPtr->Com_Tick_Tx
                     == 0
                  )
               && (
                        TxIpduRamPtr->Com_n
                     == 0
                  )
            ){
               SendIPdu = COM_TRUE;
            }
         }
      }
      if(
            (
                  TxIpduRamPtr->Com_n
               != 0
            )
         && (
                  TxIpduRamPtr->Com_n_Tick_Tx
               == 0
            )
      ){
         TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
      }
   }
   else{
      if(
            (
                  TxIpduRamPtr->Com_Tick_Tx
               == 0
            )
         && (
                  TxIpduRamPtr->Com_n
               == 0
            )
      ){
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_TRUE
         );
      }
   }
   if(
         TxIpduRamPtr->Com_Tick_Tx
      == 0
   ){
      TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(
            TxPduId
         ,  TxIpduRamPtr->CurrentTxModePtr
      );
   }
   return SendIPdu;
}

FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_NoneMode(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,      AUTOMATIC) SendIPdu     = COM_FALSE;
   Com_TxIpduRamPtrType         TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         TxIpduRamPtr->Com_MinDelayTick
      == 0
   ){
      if(
            Com_GetRamValue(
                  TXIPDU
               ,  _MDT
               ,  TxIpduRamPtr->Com_TxFlags
            )
         == COM_TRUE
      ){
         SendIPdu = COM_TRUE;
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_FALSE
         );
      }
      else{
         if(
               Com_GetRamValue(
                     TXIPDU
                  ,  _EVENTTRIG
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            == COM_TRUE
         ){
            if(
                  TxIpduRamPtr->Com_n_Tick_Tx
               != 0
            ){
               TxIpduRamPtr->Com_n_Tick_Tx--;
            }
            if(
                  TxIpduRamPtr->Com_n_Tick_Tx
               == 0
            ){
               SendIPdu = COM_TRUE;
            }
         }
      }
   }
   return SendIPdu;
}

FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_PeriodicMode(
   VAR(uint16_least, AUTOMATIC) TxPduId
){
   VAR(boolean,      AUTOMATIC) SendIPdu     = COM_FALSE;
       Com_TxIpduRamPtrType     TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         TxIpduRamPtr->Com_Tick_Tx
      != 0
   ){
      --TxIpduRamPtr->Com_Tick_Tx;
   }
   if(
         TxIpduRamPtr->Com_MinDelayTick
      == 0
   ){
      if(
            Com_GetRamValue(
                  TXIPDU
               ,  _MDT
               ,  TxIpduRamPtr->Com_TxFlags
            )
         == COM_TRUE
      ){
         SendIPdu = COM_TRUE;
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_FALSE
         );
      }
      else{
         if(
               TxIpduRamPtr->Com_Tick_Tx
            == 0
         ){
            SendIPdu = COM_TRUE;
         }
         else if(
               Com_GetRamValue(
                     TXIPDU
                  ,  _EVENTTRIG
                  ,  TxIpduRamPtr->Com_TxFlags
               )
            == COM_TRUE
         ){
            if(
                  TxIpduRamPtr->Com_n_Tick_Tx
               != 0
            ){
               TxIpduRamPtr->Com_n_Tick_Tx--;
            }
            if(
                  TxIpduRamPtr->Com_n_Tick_Tx
               == 0
            ){
               SendIPdu = COM_TRUE;
            }
         }
         else{
         }
      }
   }
   else{
      if(
            TxIpduRamPtr->Com_Tick_Tx
         == 0
      ){
         Com_SetRamValue(
               TXIPDU
            ,  _MDT
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_TRUE
         );
      }
   }
   if(
         TxIpduRamPtr->Com_Tick_Tx
      == 0
   ){
      TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(
            TxPduId
         ,  TxIpduRamPtr->CurrentTxModePtr
      );
   }
   return SendIPdu;
}

FUNC(void, COM_CODE) Com_Lok_MainFunctionTx_SendIPdu(
      VAR(uint16_least, AUTOMATIC) TxPduId
   ,  VAR(boolean,      AUTOMATIC) SendIPdu
){
   VAR(uint8, AUTOMATIC)      LatestTransMode_u8;
       Com_TxIpduConstPtrType TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
       Com_TxIpduRamPtrType   TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxPduId);
   if(
         SendIPdu
      == COM_TRUE
   ){
      Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
      Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
      sendIpduFlag_u16.isEventTrig      =  COM_RESET;
      LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);
      if(
            (
                  (LatestTransMode_u8 & COM_TXMODE_MIXED)
               >  (uint8)0
            )
         && (
                  TxIPduConstPtr->Timeout_Fact
               != 0u
            )
      ){
         sendIpduFlag_u16.isTimeoutReq = COM_SET;
      }
      Com_Lok_SendIpdu(
            (Type_SwcServiceCom_tIdPdu)TxPduId
         ,  sendIpduFlag_u16
      );
   }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_IsTxScheduled(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,  VAR(uint16,                    AUTOMATIC) ComCallerTaskCycle
){
   Com_TxIpduRamPtrType                TxIpduRamPtr;
   VAR(boolean, AUTOMATIC)             IsTxScheduled;
   ComTxPduId   = COM_GET_TX_IPDU_ID(ComTxPduId);
   TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);
   (void)ComCallerTaskCycle;
   if(
         (
               Com_GetRamValue(
                     TXIPDU
                  ,  _LATESTMODE
                  ,  TxIpduRamPtr->Com_TransMode
               )
            == (uint8)COM_TXMODE_PERIODIC
         )
      && (
               TxIpduRamPtr->Com_Tick_Tx
            > 1u
         )
   ){
      IsTxScheduled = COM_FALSE;
   }
   else{
      IsTxScheduled = COM_TRUE;
   }
   return IsTxScheduled;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

