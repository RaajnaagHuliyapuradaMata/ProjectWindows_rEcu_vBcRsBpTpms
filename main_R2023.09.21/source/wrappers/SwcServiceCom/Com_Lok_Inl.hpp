#ifndef COM_PRV_INL_H
#define COM_PRV_INL_H

LOCAL_INLINE FUNC(void, COM_CODE) Com_SetCurrentTxModePtr(
          Com_TxIpduRamPtrType   TxIpduRamPtr
   ,      Com_TxIpduConstPtrType TxIPduConstPtr
   ,  VAR(uint16,  AUTOMATIC)    TMSStatus
   ,  VAR(boolean, AUTOMATIC)    ModeRequested
);

LOCAL_INLINE FUNC(void, COM_CODE) Com_UpdateRxSignalBuffer(
          Com_RxSigConstPtrType        RxSigConstPtr
   ,  VAR(Com_SigMaxType,   AUTOMATIC) RxNewVal_Sig
   ,  VAR(Com_MainFuncType, AUTOMATIC) RxMainFuncId
);

LOCAL_INLINE FUNC(void, COM_CODE) Com_InitializePduBuffWithSignalInitValue(
      P2VAR(uint8,AUTOMATIC,     COM_APPL_DATA) BuffPtr
   ,    VAR(Com_SigMaxType,      AUTOMATIC    ) SigInitVal
   ,    VAR(Com_BitpositionType, AUTOMATIC    ) SigBitPos
   ,    VAR(Com_BitsizeType,     AUTOMATIC    ) SigBitSize
   ,    VAR(uint8,               AUTOMATIC    ) SigType
   ,    VAR(uint8,               AUTOMATIC    ) SigEndianess
);

LOCAL_INLINE boolean Com_CheckRxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId);
LOCAL_INLINE boolean Com_CheckTxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId);

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProceedToSendIpdu(
      VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Com_SendIpduInfo,              AUTOMATIC) sendIpduFlag_u16
);

LOCAL_INLINE FUNC(void, COM_CODE) Com_SetCurrentTxModePtr(
          Com_TxIpduRamPtrType   TxIpduRamPtr
   ,      Com_TxIpduConstPtrType TxIPduConstPtr
   ,  VAR(uint16,  AUTOMATIC)    TMSStatus
   ,  VAR(boolean, AUTOMATIC)    ModeRequested
){
   TxIpduRamPtr->CurrentTxModePtr = TxIPduConstPtr->Com_TMConstPtr;
   if(
         ModeRequested
      == COM_FALSE
   ){
      if((TMSStatus) == COM_TRUEMODE_VALID){
            TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo ;
        }
      if((TMSStatus) == COM_MODE_VALID){
            TxIpduRamPtr->CurrentTxModePtr++;
        }
   }
   else{
      if(
            TMSStatus
         == COM_FALSEMODE_VALID
      ){
         TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo;
      }
   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_UpdateRxSignalBuffer(
      Com_RxSigConstPtrType RxSigConstPtr
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal_Sig
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
){
   VAR(uint8,AUTOMATIC)    Type;
    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
   switch(Type >> 1u){
   case 0x00u:
      case (COM_BOOLEAN >> 1): COM_GET_SIGTYPEUINT8_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint8)RxNewVal_Sig; break;
      case 0x01u: COM_GET_SIGTYPEUINT16_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint16)RxNewVal_Sig; break;
      case 0x02u: COM_GET_SIGTYPEUINT32_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint32)RxNewVal_Sig; break;
      case 0x04u: Com_ByteCopyInit(&COM_GET_SIGTYPEUINT8_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) , (uint32)RxNewVal_Sig,RxSigConstPtr->BitSize); break;
      default: break;
   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_InitializePduBuffWithSignalInitValue(
      P2VAR(uint8,AUTOMATIC,COM_APPL_DATA) BuffPtr
   ,     VAR(Com_SigMaxType,AUTOMATIC)           SigInitVal
   ,     VAR(Com_BitpositionType,AUTOMATIC)      SigBitPos
   ,     VAR(Com_BitsizeType,AUTOMATIC)          SigBitSize
   ,     VAR(uint8,AUTOMATIC)                    SigType
   ,     VAR(uint8,AUTOMATIC)                    SigEndianess
){
   if(SigType != (uint8)COM_UINT8_N){
            Com_PackSignal( SigEndianess, SigBitPos, SigBitSize, SigInitVal, BuffPtr );
   }
   else{
        Type_SwcServiceCom_tLengthPdu ByteOffset_uo;
        ByteOffset_uo = ( Type_SwcServiceCom_tLengthPdu )( SigBitPos >> 3 );
        Com_ByteCopyInit( (BuffPtr + ByteOffset_uo), (uint32)SigInitVal, SigBitSize );
   }
}

LOCAL_INLINE boolean Com_CheckTxIPduStatus(
   Type_SwcServiceCom_tIdPdu IpduId
){
   return Com_GetRamValue(
         TXIPDU
      ,  _PDUSTATUS
      ,  COM_GET_TXPDURAM_S(IpduId).Com_TxFlags
   );
}

LOCAL_INLINE boolean Com_CheckRxIPduStatus(
   Type_SwcServiceCom_tIdPdu IpduId
){
    return Com_GetRamValue(
         RXIPDU
      ,  _PDUSTATUS
      ,  COM_GET_RXPDURAM_S(IpduId).RxFlags
   );
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProceedToSendIpdu(
      VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) ComTxPduId
   ,  VAR(Com_SendIpduInfo,              AUTOMATIC) sendIpduFlag_u16
){
   Com_TxIpduConstPtrType  TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
   Com_TxIpduRamPtrType    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
   if(
         (sendIpduFlag_u16.sigTransProp == COM_SET)
      && (
               Com_GetRamValue(
                     TXIPDU
                  ,  _LATESTMODE
                  ,  TxIpduRamPtr->Com_TransMode
               )
            <= COM_TXMODE_MIXED
         )
   ){
      sendIpduFlag_u16.isEventTrig = COM_SET;
      Com_Lok_SendIpdu(
            (Type_SwcServiceCom_tIdPdu)ComTxPduId
         ,  sendIpduFlag_u16
      );
   }
}

#endif

