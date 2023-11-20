#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
VAR(Com_StatusType,COM_VAR)         Com_Uninit_Flag;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST) Com_Lok_Config_pcst;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_Init_Receive(void);
FUNC(void, COM_CODE) Com_Lok_Init_Send(void);
FUNC(void, COM_CODE) Com_Lok_Init_TxSignal(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) IpduId);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_Init(
   P2CONST(Type_CfgSwcServiceCom_st, AUTOMATIC, COM_APPL_DATA) config
){
   (void)config;
   rba_BswSrv_MemSet8(
         &Com_IpduGrpVector[COM_ZERO]
      ,  (uint32)COM_ZERO
      ,  (uint32)COM_NUM_ARR_IPDUGRPVECT
   );
   rba_BswSrv_MemSet8(
         &Com_IpduGrpVector_DM[COM_ZERO]
      ,  (uint32)COM_ZERO
      ,  (uint32)COM_NUM_ARR_IPDUGRPVECT
   );
   Com_Lok_Init_Receive();
   Com_Lok_Init_Send();
   Com_Uninit_Flag = COM_INIT;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_Init_Receive(void){
   Com_RxIpduRamPtrType             RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);
   Com_RxIpduConstPtrType           RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(0);
   Com_RxSigConstPtrType            RxSigConstPtr;
   Com_RxSigRamPtrType              RxSigRamPtr;
   VAR(uint16_least,     AUTOMATIC) Idx_ui;
   VAR(uint16_least,     AUTOMATIC) Idx_ByteNSig_ui;
   VAR(Com_SigMaxType,   AUTOMATIC) RxSigVal;
   VAR(Com_MainFuncType, AUTOMATIC) rxMainFuncId;
   for(
      Idx_ui = COM_ZERO;
      Idx_ui < CfgSwcServiceCom_dNumIPduRx;
      Idx_ui ++
   ){
      COM_GET_IPDUCOUNTER_S(Idx_ui)  = (uint8)COM_ZERO;
      COM_GET_IPDUCOUNTER_DM(Idx_ui) = (uint8)COM_ZERO;
      RxIPduRamPtr ->RxFlags         = (uint8)COM_ZERO;
      RxIPduRamPtr ->RxIPduLength    = COM_ZERO;
      Com_SetRamValue(
            RXIPDU
         ,  _GWPDU_TOBEPROCESSED
         ,  RxIPduRamPtr->RxFlags
         ,  COM_FALSE
      );
      RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
      RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);
      rxMainFuncId  = RxIPduConstPtr->MainFunctionRef;
      for(
         Idx_ByteNSig_ui = (uint16_least)(RxIPduConstPtr->No_Of_Sig_Ref);
         Idx_ByteNSig_ui != (uint16_least)COM_ZERO;
         Idx_ByteNSig_ui --
      ){
         RxSigRamPtr->rxSigRAMFields = (uint8)COM_ZERO;
         RxSigVal                    = (Com_SigMaxType)RxSigConstPtr->Init_Val;
         Com_UpdateRxSignalBuffer(
               RxSigConstPtr
            ,  RxSigVal
            ,  rxMainFuncId
         );
         RxSigRamPtr++;
         RxSigConstPtr++;
      }
      RxIPduRamPtr++;
      RxIPduConstPtr++;
   }
}

FUNC(void, COM_CODE) Com_Lok_Init_Send(void){
   Com_TxIpduRamPtrType   TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);
   Com_TxIpduConstPtrType TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);
   VAR(uint16, AUTOMATIC) Idx_ui;
   for(
      Idx_ui = COM_ZERO;
      Idx_ui < CfgSwcServiceCom_dNumIPduTx;
      Idx_ui ++
   ){
      TxIpduRamPtr->Com_TxFlags      = (uint16)COM_ZERO;
      TxIpduRamPtr->CurrentTxModePtr = TxIPduConstPtr->Com_TMConstPtr;
      rba_BswSrv_MemSet8(
            TxIPduConstPtr->BuffPtr
         ,  (uint32)TxIPduConstPtr->PaddingByte
         ,  (uint32)TxIPduConstPtr->Size
      );
      if(
            Com_GetValue(
                  TXIPDU
               ,  _PDUWITHPDUGRP
               ,  TxIPduConstPtr->txIPduFields
            )
         != COM_FALSE
      ){
         COM_GET_IPDUCOUNTER_S(Idx_ui + CfgSwcServiceCom_dNumIPduRx) = COM_ZERO;
         Com_SetRamValue(
               TXIPDU
            ,  _TXMODESTATE
            ,  TxIpduRamPtr->Com_TransMode
            ,  COM_TRUE
         );
         Com_SetRamValue(
               TXIPDU
            ,  _LATESTMODE
            ,  TxIpduRamPtr->Com_TransMode
            ,  (uint8)COM_TXMODE_NONE
         );
      }
      TxIpduRamPtr->Com_TickTxTimeout = COM_ZERO;
      TxIpduRamPtr->Com_n             = COM_ZERO;
      TxIpduRamPtr->Com_MinDelayTick  = COM_ZERO;
      Com_Lok_Init_TxSignal(
         Idx_ui
      );
      TxIPduConstPtr++;
      TxIpduRamPtr++;
   }
}

FUNC(void, COM_CODE) Com_Lok_Init_TxSignal(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) IpduId
){
   Com_TxIpduConstPtrType         TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
   Com_TxSigConstPtrType          TxSigConstPtr  = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
   VAR(Com_SigMaxType, AUTOMATIC) TxSigNewVal;
   VAR(uint16_least,   AUTOMATIC) Idx_ByteNSig_ui;
   VAR(uint8,          AUTOMATIC) ConstByteValue_u8;
   VAR(uint8,          AUTOMATIC) Type;
   for(
      Idx_ByteNSig_ui = TxIPduConstPtr->No_Of_Sig_Ref;
      Idx_ByteNSig_ui != COM_ZERO;
      Idx_ByteNSig_ui --
   ){
      ConstByteValue_u8   = TxSigConstPtr->General;
      Type                = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
      TxSigNewVal         = (Com_SigMaxType)TxSigConstPtr->Init_Val;
      Com_InitializePduBuffWithSignalInitValue(
            TxIPduConstPtr->BuffPtr
         ,  TxSigNewVal
         ,  TxSigConstPtr->Bit_Pos
         ,  TxSigConstPtr->BitSize, Type
         ,  Com_GetValue(
                  GEN
               ,  _ENDIANESS
               ,  ConstByteValue_u8
            )
      );
      TxSigConstPtr++;
   }
}


