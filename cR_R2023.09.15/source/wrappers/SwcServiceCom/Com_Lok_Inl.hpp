

#ifndef COM_PRV_INL_H
#define COM_PRV_INL_H

LOCAL_INLINE
FUNC(void, COM_CODE) Com_SetCurrentTxModePtr(
                                Com_TxIpduRamPtrType                TxIpduRamPtr
   ,     Com_TxIpduConstPtrType              TxIPduConstPtr
   ,     VAR(uint16,AUTOMATIC)               TMSStatus
   ,     VAR(boolean,AUTOMATIC)              ModeRequested
                                            );

LOCAL_INLINE
FUNC(void, COM_CODE) Com_UpdateRxSignalBuffer(
                                Com_RxSigConstPtrType               RxSigConstPtr
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal_Sig
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
                                             );

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE
FUNC(void, COM_CODE) Com_UpdateRxGroupSignalSecondBuffer(
                                Com_RxGrpSigConstPtrType            RxGrpSigConstPtr
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
                                                        );
#endif

LOCAL_INLINE
FUNC(void, COM_CODE) Com_InitializePduBuffWithSignalInitValue(
                                P2VAR(uint8,AUTOMATIC,COM_APPL_DATA)    BuffPtr
   ,     VAR(Com_SigMaxType,AUTOMATIC)           SigInitVal
   ,     VAR(Com_BitpositionType,AUTOMATIC)      SigBitPos
   ,     VAR(Com_BitsizeType,AUTOMATIC)          SigBitSize
   ,     VAR(uint8,AUTOMATIC)                    SigType
   ,     VAR(uint8,AUTOMATIC)                    SigEndianess
                                                            );

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE
FUNC(void, COM_CODE) Com_Lok_SigGrpReplaceToInit(
                                Com_RxSigGrpConstPtrType            RxSigGrpConstPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
                                                );
#endif

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxNotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxErrNotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxTONotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallRxTONotifyCallback(Com_IpduIdType IpduId);
#endif

LOCAL_INLINE boolean Com_CheckRxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId);
LOCAL_INLINE boolean Com_CheckTxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId);

#if(COM_CONFIGURATION_USE_DET == STD_ON)

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_DETCheck_Void(uint8 ApiId);
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_DETCheck_Param(boolean isInValidParam, uint8 ApiId);
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_DETCheck_Ptr(boolean isInValidPtr, uint8 ApiId);
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_DETCheck_Param_Ptr(boolean isInValidParam, boolean isInValidPtr
   ,     uint8 ApiId);
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Ptr_Only(boolean isInValidPtr, uint8 ApiId);
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Param_Only(boolean isInValidParam, uint8 ApiId);

#endif

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) Com_CopyTxGroupSignalData( Com_SignalIdType    GrpSignalId
   ,     Com_SigMaxType      TxGrpSig_NewVal
   ,     Com_MainFuncType    TxMainFuncId );
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProceedToSendIpdu(
                                                VAR(Com_IpduIdType, AUTOMATIC)          ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC)        sendIpduFlag_u16
                                                           );

#ifdef COM_TxFilters
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_CheckModeChange(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId);
#endif

LOCAL_INLINE
FUNC(void, COM_CODE) Com_SetCurrentTxModePtr(
                                Com_TxIpduRamPtrType                TxIpduRamPtr
   ,     Com_TxIpduConstPtrType              TxIPduConstPtr
   ,     VAR(uint16,AUTOMATIC)               TMSStatus
   ,     VAR(boolean,AUTOMATIC)              ModeRequested
                                            )
{

    TxIpduRamPtr->CurrentTxModePtr = TxIPduConstPtr->Com_TMConstPtr;

   if(ModeRequested == COM_FALSE)
   {
        if((TMSStatus) == COM_TRUEMODE_VALID)
        {

            TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo ;
        }
        if((TMSStatus) == COM_MODE_VALID)
        {

            TxIpduRamPtr->CurrentTxModePtr++;
        }
   }
   else{
        if((TMSStatus) == COM_FALSEMODE_VALID)
        {
            TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo ;
        }
   }
}

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE
FUNC(void, COM_CODE) Com_UpdateRxGroupSignalSecondBuffer(
                                Com_RxGrpSigConstPtrType            RxGrpSigConstPtr
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
                                                        )
{
   VAR(uint8,AUTOMATIC)    Type;

    Type = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

   switch(Type >> 1u)
   {
   case 0x00u:

        COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint8)RxNewVal;
        break;

   case 0x01u:

        COM_GET_SECRXGRPSIGTYPEU16_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint16)RxNewVal;
        break;

   case 0x02u:

   case (COM_FLOAT32 >> 1u):

        COM_GET_SECRXGRPSIGTYPEU32_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint32)RxNewVal;
        break;

#ifdef COM_RXGRPSIG_INT64
   case 0x08u:

        COM_GET_SECRXGRPSIGTYPEU64_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = RxNewVal;
        break;
#endif

   case 0x03u:

        COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint8)RxNewVal;
        break;

   case 0x04u:

        Com_ByteCopyInit(&COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index)
   ,     (uint32)RxNewVal,RxGrpSigConstPtr->BitSize);
        break;
    default:

        break;

   }
}
#endif

LOCAL_INLINE
FUNC(void, COM_CODE) Com_UpdateRxSignalBuffer(
                                Com_RxSigConstPtrType               RxSigConstPtr
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal_Sig
   ,     VAR(Com_MainFuncType,AUTOMATIC)     RxMainFuncId
                                             )
{
   VAR(uint8,AUTOMATIC)    Type;

    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

   switch(Type >> 1u)
   {
   case 0x00u:
   case (COM_BOOLEAN >> 1):
        COM_GET_SIGTYPEUINT8_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint8)RxNewVal_Sig;
        break;

   case 0x01u:
        COM_GET_SIGTYPEUINT16_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint16)RxNewVal_Sig;
        break;

   case 0x02u:

#ifdef COM_FLOAT32SUPP
   case (COM_FLOAT32 >> 1u):
#endif

        COM_GET_SIGTYPEUINT32_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = (uint32)RxNewVal_Sig;
        break;

#ifdef COM_RXSIG_INT64
   case 0x08u:
        COM_GET_SIGTYPEUINT64_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) = RxNewVal_Sig;
        break;
#endif

   case 0x04u:
        Com_ByteCopyInit(&COM_GET_SIGTYPEUINT8_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index)
   ,     (uint32)RxNewVal_Sig,RxSigConstPtr->BitSize);
        break;
    default:

        break;
   }
}

LOCAL_INLINE
FUNC(void, COM_CODE) Com_InitializePduBuffWithSignalInitValue(
                                P2VAR(uint8,AUTOMATIC,COM_APPL_DATA)    BuffPtr
   ,     VAR(Com_SigMaxType,AUTOMATIC)           SigInitVal
   ,     VAR(Com_BitpositionType,AUTOMATIC)      SigBitPos
   ,     VAR(Com_BitsizeType,AUTOMATIC)          SigBitSize
   ,     VAR(uint8,AUTOMATIC)                    SigType
   ,     VAR(uint8,AUTOMATIC)                    SigEndianess
                                                            )
{
   if( SigType != (uint8)COM_UINT8_N )
   {

#if(defined(COM_TXSIG_FLOAT64SUPP) || defined(COM_TXGRPSIG_FLOAT64SUPP) ||\
    (defined(COM_RX_SIGNALGROUP_ARRAY) && defined(COM_RXGRPSIG_FLOAT64SUPP)))
        if( SigType == COM_FLOAT64 )
        {

            Com_PackFloatSignal( SigEndianess, SigBitPos, Com_getfloat64InitValue(SigInitVal), BuffPtr );
        }
        else
#endif

        {

            Com_PackSignal( SigEndianess, SigBitPos, SigBitSize, SigInitVal, BuffPtr );
        }
   }
   else{
        Type_SwcServiceCom_tLengthPdu ByteOffset_uo;

        ByteOffset_uo = ( Type_SwcServiceCom_tLengthPdu )( SigBitPos >> 3 );

        Com_ByteCopyInit( (BuffPtr + ByteOffset_uo), (uint32)SigInitVal, SigBitSize );
   }
}

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_SigGrpReplaceToInit(
                                                Com_RxSigGrpConstPtrType        RxSigGrpConstPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC) RxMainFuncId
                                                             )
{
   Com_RxGrpSigConstPtrType      RxGrpSigConstPtr;
# ifdef COM_RX_SIGNALGROUP_ARRAY
   Com_RxSigGrpArrayConstPtrType RxSigGrpArrayConstPtr;
   uint8                       * RxSigGrpArrayBufRamPtr;
   Type_SwcServiceCom_tLengthPdu                 SigGrpBitOffset;
# endif
   VAR(uint16_least, AUTOMATIC)  index_ui;
   VAR(Com_SigMaxType, AUTOMATIC) SigValue;
# if(defined(COM_RX_SIGNALGROUP_ARRAY) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_INT64))
   VAR(uint8, AUTOMATIC)         SigType;
# endif
# ifdef COM_RX_SIGNALGROUP_ARRAY
   boolean                       ConstIsSigGrpOfArrayType_b;

   ConstIsSigGrpOfArrayType_b = Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields);

   if( ConstIsSigGrpOfArrayType_b )
   {
        RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

        RxSigGrpArrayBufRamPtr = &COM_GET_RXSIGGRP_ARRAY_BUFF(RxMainFuncId, RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

        SigGrpBitOffset        = ( RxSigGrpArrayConstPtr->FirstByteNo * 8u );

        SchM_Enter_Com_RxSigGrpArrayBuff();
   }
   else
# endif
   {
        SchM_Enter_Com_RxGrpSigSecBuff();
   }

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA( RxSigGrpConstPtr->FirstGrpSig_Index );

   for( index_ui = (uint16_least)RxSigGrpConstPtr->No_Of_GrpSig; index_ui != (uint16_least)0; index_ui-- )
   {
# if(defined(COM_RX_SIGNALGROUP_ARRAY) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_INT64))
        SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
# endif

        SigValue = (Com_SigMaxType)RxGrpSigConstPtr->Init_Val;

#ifdef COM_RXGRPSIG_INT64

        SigValue = (SigType == COM_SINT64) ? (Com_SigMaxType)((sint64)((sint32)SigValue)) : SigValue;
#endif

# ifdef COM_RX_SIGNALGROUP_ARRAY
        if( ConstIsSigGrpOfArrayType_b )
        {
            Com_BitpositionType RelativeSigBitPos;

            RelativeSigBitPos = RxGrpSigConstPtr->Bit_Pos - ( Com_BitpositionType )SigGrpBitOffset;

            Com_InitializePduBuffWithSignalInitValue(
                                              RxSigGrpArrayBufRamPtr
   ,     SigValue
   ,     RelativeSigBitPos
   ,     RxGrpSigConstPtr->BitSize
   ,     SigType
   ,     Com_GetValue(RXGRPSIG,_ENDIANESS,RxGrpSigConstPtr->rxGrpSigFields) );
        }
        else
# endif
        {

# ifdef COM_RXGRPSIG_FLOAT64SUPP
            if(SigType == COM_FLOAT64)
            {
                COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) =
                                                                      Com_getfloat64InitValue(SigValue);
            }
            else
# endif

            {
                Com_UpdateRxGroupSignalSecondBuffer(RxGrpSigConstPtr, SigValue, RxMainFuncId);
            }
        }
# if defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD)

        if( ( COM_INIT != Com_Uninit_Flag ) && ( COM_MASKED_NEW_DIFFERS_MASKED_OLD == RxGrpSigConstPtr->Filter_Algo ) )
        {
            COM_GET_F_OLDVALUE(RxGrpSigConstPtr->Filter_Index) = (uint32)SigValue;
        }
# endif

        RxGrpSigConstPtr++;
   }
# ifdef COM_RX_SIGNALGROUP_ARRAY

   if( ConstIsSigGrpOfArrayType_b )
   {
        SchM_Exit_Com_RxSigGrpArrayBuff();
   }
   else
# endif
   {
        SchM_Exit_Com_RxGrpSigSecBuff();
   }
}
#endif

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxNotifyCallback(Com_IpduIdType IpduId)
        {
   Com_TxIpduConstPtrType TxIPduConstPtr;
   Com_TxSigConstPtrType TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType TxSigGrpConstPtr;
#endif
   uint8_least index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIPduConstPtr->TxSigId_Index; index_u8 < (TxIPduConstPtr->TxSigId_Index + TxIPduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->Notification_Cbk != NULL_PTR)
        {
            TxSigConstPtr->Notification_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIPduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIPduConstPtr->FirstTxSigGrp_Index + TxIPduConstPtr->No_Of_SigGrp_Ref); index_u8++)
   {
        if(TxSigGrpConstPtr->Notification_Cbk != NULL_PTR)
        {
            TxSigGrpConstPtr->Notification_Cbk();
        }
        TxSigGrpConstPtr++;
   }
#endif

        }
#endif

#ifdef COM_ERRORNOTIFICATION
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxErrNotifyCallback(Com_IpduIdType IpduId)
{

   Com_TxIpduConstPtrType TxIPduConstPtr;
   Com_TxSigConstPtrType TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType TxSigGrpConstPtr;
#endif
   uint8_least index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIPduConstPtr->TxSigId_Index; index_u8 < (TxIPduConstPtr->TxSigId_Index + TxIPduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->NotificationError_Cbk != NULL_PTR)
        {
            TxSigConstPtr->NotificationError_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIPduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIPduConstPtr->FirstTxSigGrp_Index + TxIPduConstPtr->No_Of_SigGrp_Ref); index_u8++)
   {
        if(TxSigGrpConstPtr->NotificationError_Cbk != NULL_PTR)
        {
            TxSigGrpConstPtr->NotificationError_Cbk();
        }
        TxSigGrpConstPtr++;
   }
#endif
}
#endif

#ifdef COM_TxIPduTimeOutNotify
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallTxTONotifyCallback(Com_IpduIdType IpduId)
{

   Com_TxIpduConstPtrType TxIPduConstPtr;
   Com_TxSigConstPtrType TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType TxSigGrpConstPtr;
#endif
   uint8_least index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIPduConstPtr->TxSigId_Index; index_u8 < (TxIPduConstPtr->TxSigId_Index + TxIPduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            TxSigConstPtr->TimeOutNotification_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIPduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIPduConstPtr->FirstTxSigGrp_Index + TxIPduConstPtr->No_Of_SigGrp_Ref); index_u8++)
   {
        if(TxSigGrpConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            TxSigGrpConstPtr->TimeOutNotification_Cbk();
        }
        TxSigGrpConstPtr++;
   }
#endif
}
#endif
#ifdef COM_RxIPduTimeoutNotify
LOCAL_INLINE FUNC(void, COM_CODE) Com_CallRxTONotifyCallback(Com_IpduIdType IpduId)
{

   Com_RxIpduConstPtrType RxIPduConstPtr;
   Com_RxSigConstPtrType RxSigConstPtr;
#ifdef COM_RX_SIGNALGROUP
   Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
#endif
   uint8_least index_u8;

    IpduId = COM_GET_RX_IPDU_ID(IpduId);
    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);
    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);
#ifdef COM_RX_SIGNALGROUP
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);
#endif

   for(index_u8 = RxIPduConstPtr->RxSigId_Index; index_u8 < (RxIPduConstPtr->RxSigId_Index + RxIPduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(RxSigConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            RxSigConstPtr->TimeOutNotification_Cbk();
        }
        RxSigConstPtr++;
   }
#ifdef COM_RX_SIGNALGROUP
   for(index_u8 = RxIPduConstPtr->FirstRxSigGrp_Index; index_u8 < (RxIPduConstPtr->FirstRxSigGrp_Index + RxIPduConstPtr->No_Of_SigGrp_Ref); index_u8++)
   {
        if(RxSigGrpConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            RxSigGrpConstPtr->TimeOutNotification_Cbk();
        }
        RxSigGrpConstPtr++;
   }
#endif
}
#endif
#endif

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) Com_CopyTxGroupSignalData( Com_SignalIdType    GrpSignalId
   ,     Com_SigMaxType      TxGrpSig_NewVal
   ,     Com_MainFuncType    TxMainFuncId )
{
   Com_TxGrpSigConstPtrType                   TxGrpSigConstPtr;
   VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC)  GrpSigBuff_Index;
   VAR(uint8, AUTOMATIC)                      Type;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(GrpSignalId);
    GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;
    Type = Com_GetValue(TXGRPSIG,_TYPE,TxGrpSigConstPtr->txGrpSigFields);

    SchM_Enter_Com_TxGrpSigBuffer();
   switch(Type >> 1u)
   {

        case 0x00u:
        case 0x03u:
            COM_GET_TXGRPSIGTYPEU8_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint8)TxGrpSig_NewVal;
            break;

        case 0x01u:
            COM_GET_TXGRPSIGTYPEU16_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint16)TxGrpSig_NewVal;
            break;

        case 0x02u:

#ifdef COM_FLOAT32SUPP
        case (COM_FLOAT32 >> 1u):
#endif

            COM_GET_TXGRPSIGTYPEU32_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint32)TxGrpSig_NewVal;
            break;

#ifdef COM_TXGRPSIG_INT64
        case 0x08u:
            COM_GET_TXGRPSIGTYPEU64_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint64)TxGrpSig_NewVal;
        break;
#endif

        default:

        break;
   }
    SchM_Exit_Com_TxGrpSigBuffer();
}
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Void(uint8 ApiId)
{

   boolean Status;

    Status  = COM_TRUE;

   if(Com_Uninit_Flag == COM_UNINIT)
   {

        COM_REPORT_ERROR_CHECK(ApiId, COM_E_UNINIT);

        Status = COM_FALSE;
   }
   else{

   }

    return Status;
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Param(boolean isInValidParam, uint8 ApiId)
{

   uint8   ErrorId;
   boolean Status;

    ErrorId = COM_DET_NO_ERROR;
    Status  = COM_TRUE;

   if(Com_Uninit_Flag == COM_UNINIT)
   {
        ErrorId = COM_E_UNINIT;
   }
   else if(isInValidParam)
   {
        ErrorId = COM_E_PARAM;
   }
   else{

   }

   if(ErrorId != COM_DET_NO_ERROR)
   {

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId);

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Ptr(boolean isInValidPtr, uint8 ApiId)
{

   uint8   ErrorId;
   boolean Status;

    ErrorId = COM_DET_NO_ERROR;
    Status  = COM_TRUE;

   if(Com_Uninit_Flag == COM_UNINIT)
   {
        ErrorId = COM_E_UNINIT;
   }
   else if(isInValidPtr)
   {
        ErrorId = COM_E_PARAM_POINTER;
   }
   else{

   }

   if(ErrorId != COM_DET_NO_ERROR)
   {

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId);

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Param_Ptr(boolean isInValidParam, boolean isInValidPtr, uint8 ApiId)
{

   uint8   ErrorId;
   boolean Status;

    ErrorId = COM_DET_NO_ERROR;
    Status  = COM_TRUE;

   if(Com_Uninit_Flag == COM_UNINIT)
   {
        ErrorId = COM_E_UNINIT;
   }
   else if(isInValidParam)
   {
        ErrorId = COM_E_PARAM;
   }
   else if(isInValidPtr)
   {
        ErrorId = COM_E_PARAM_POINTER;
   }
   else{

   }

   if(ErrorId != COM_DET_NO_ERROR)
   {

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId);

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Ptr_Only(boolean isInValidPtr, uint8 ApiId)
{

   boolean Status;

    Status = COM_TRUE;

   if(isInValidPtr)
   {

        COM_REPORT_ERROR_CHECK(ApiId, COM_E_PARAM_POINTER);

        Status = COM_FALSE;
   }
   else{

   }

    return Status;
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_DETCheck_Param_Only(boolean isInValidParam, uint8 ApiId)
{

   boolean Status;

    Status = COM_TRUE;

   if(isInValidParam)
   {

        COM_REPORT_ERROR_CHECK(ApiId, COM_E_PARAM);

        Status = COM_FALSE;
   }
   else{

   }

    return Status;
}

#endif

LOCAL_INLINE boolean Com_CheckTxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId)
{
   VAR(boolean, AUTOMATIC) TxIPduStatus;

    TxIPduStatus =  Com_GetRamValue(TXIPDU,_PDUSTATUS,COM_GET_TXPDURAM_S(IpduId).Com_TxFlags)

#ifdef COM_TX_IPDUCONTROL_VIA_CALIBRATION
                && (COM_CheckTxIPduCalibrationVarStatus((Type_SwcServiceCom_tIdPdu)(IpduId)))
#endif
#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
                && (Com_CheckTxIPduControlViaRbaNdsEcuVariant((Type_SwcServiceCom_tIdPdu)(IpduId)))
#endif

                         ;

    return TxIPduStatus;
}

LOCAL_INLINE boolean Com_CheckRxIPduStatus(Type_SwcServiceCom_tIdPdu IpduId)
{
   VAR(boolean, AUTOMATIC) RxIPduStatus;

    RxIPduStatus = Com_GetRamValue(RXIPDU,_PDUSTATUS,COM_GET_RXPDURAM_S(IpduId).RxFlags)

#ifdef COM_RX_IPDUCONTROL_VIA_CALIBRATION
                && (COM_CheckRxIPduCalibrationVarStatus((Type_SwcServiceCom_tIdPdu)(IpduId)))
#endif
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
                && (Com_CheckRxIPduControlViaRbaNdsEcuVariant((Type_SwcServiceCom_tIdPdu)(IpduId)))
#endif

                        ;

    return RxIPduStatus;
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProceedToSendIpdu(
                                                VAR(Com_IpduIdType, AUTOMATIC)   ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC) sendIpduFlag_u16
                                                           )
{
   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)

   if(Com_GetValue(TXIPDU,_ISGWPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE)
   {

        if(sendIpduFlag_u16.sigTransProp == COM_SET)
        {

            Com_SetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }

#ifdef COM_TxFilters

        if(sendIpduFlag_u16.isModeChangd == COM_SET)
        {

            if(Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags))
            {
                Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
            }
            else{

                Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
            }
        }
#endif

#ifdef COM_TxIPduTimeOut
        if(sendIpduFlag_u16.isTimeoutReq == COM_SET)
        {

            Com_SetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }
#endif
   }
   else
#endif
   {

        if(((sendIpduFlag_u16.sigTransProp == COM_SET) &&
             (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) <= COM_TXMODE_MIXED))
#ifdef COM_TxFilters
            || (sendIpduFlag_u16.isModeChangd == COM_SET)
#endif
           )
        {

            sendIpduFlag_u16.isEventTrig = COM_SET;

            Com_Lok_SendIpdu((Type_SwcServiceCom_tIdPdu)ComTxPduId, sendIpduFlag_u16);
        }
   }
}

#ifdef COM_TxFilters

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_CheckModeChange(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId)
{

   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;
   VAR(boolean, AUTOMATIC) ReturnValue;
   VAR(boolean, AUTOMATIC) Mode;

    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    Mode            = COM_FALSE;
    ReturnValue     = COM_FALSE;

   if(TxIpduRamPtr ->Com_TMSTrueCounter_u8 != 0)
   {

        Mode = COM_TRUE;
   }

   if(Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode)
   {
        ReturnValue = COM_TRUE;

        Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

        Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);

        Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);

#ifdef COM_MIXEDPHASESHIFT

        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif

   }

    return(ReturnValue);
}

#endif

#endif

