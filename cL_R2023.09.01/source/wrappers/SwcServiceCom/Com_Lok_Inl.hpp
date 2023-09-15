

#ifndef COM_PRV_INL_H
#define COM_PRV_INL_H

LOCAL_INLINE void Com_SetCurrentTxModePtr(
                                    Com_TxIpduRamPtrType            TxIpduRamPtr
   ,                                   Com_TxIpduConstPtrType          TxIpduConstPtr
   ,                                   boolean                         ModeRequested
                                         );

LOCAL_INLINE void Com_UpdateRxSignalBuffer(
                                    Com_RxSigConstPtrType           RxSigConstPtr
   ,                                   Com_SigMaxType                  RxNewVal_Sig
   ,                                   Com_MainFuncType                RxMainFuncId
                                          );

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void Com_UpdateRxGroupSignalSecondBuffer(
                                    Com_RxGrpSigConstPtrType        RxGrpSigConstPtr
   ,                                   Com_SigMaxType                  RxNewVal
   ,                                   Com_MainFuncType                RxMainFuncId
                                                     );
#endif

LOCAL_INLINE void Com_InitializePduBuffWithSignalInitValue(
                                    uint8 *                         BuffPtr
   ,                                   Com_SigMaxType                  SigInitVal
   ,                                   Com_BitpositionType             SigBitPos
   ,                                   Com_BitsizeType                 SigBitSize
   ,                                   uint8                           SigType
   ,                                   uint8                           SigEndianess
                                             );

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE
void Com_Lok_SigGrpReplaceToInit(Com_RxSigGrpConstPtrType RxSigGrpConstPtr, Com_MainFuncType RxMainFuncId);
#endif

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
LOCAL_INLINE void Com_CallTxNotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE void Com_CallTxErrNotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE void Com_CallTxTONotifyCallback(Com_IpduIdType IpduId);
LOCAL_INLINE void Com_CallRxTONotifyCallback(Com_IpduIdType IpduId);
#endif

LOCAL_INLINE boolean Com_CheckRxIPduStatus(PduIdType IpduId);
LOCAL_INLINE boolean Com_CheckTxIPduStatus(PduIdType IpduId);

#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
LOCAL_INLINE boolean Com_CheckRxIPduControlViaRbaNdsEcuVariant(PduIdType IpduId);
#endif

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
LOCAL_INLINE boolean Com_CheckTxIPduControlViaRbaNdsEcuVariant(PduIdType IpduId);
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)

LOCAL_INLINE boolean Com_Lok_DETCheck_Param(boolean isInValidParam, uint8 ApiId);
LOCAL_INLINE boolean Com_Lok_DETCheck_Ptr(boolean isInValidPtr, uint8 ApiId);
LOCAL_INLINE boolean Com_Lok_DETCheck_Param_Ptr(boolean isInValidParam, boolean isInValidPtr,uint8 ApiId);
LOCAL_INLINE boolean Com_Lok_DETCheck_Ptr_Only(boolean isInValidPtr, uint8 ApiId);
LOCAL_INLINE boolean Com_Lok_DETCheck_Param_Only(boolean isInValidParam, uint8 ApiId);

#endif

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE void Com_CopyTxGroupSignalData(
                                    Com_SignalIdType                GrpSignalId
   ,                                   Com_SigMaxType                  TxGrpSig_NewVal
   ,                                   Com_MainFuncType                TxMainFuncId
                                           );
#endif

LOCAL_INLINE void Com_Lok_ProceedToSendIpdu(Com_IpduIdType  ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16);

#ifdef COM_TxFilters
LOCAL_INLINE boolean Com_Lok_CheckModeChange(Com_IpduIdType TxIpduId);
#endif

#ifdef COM_TX_IPDUCOUNTER
LOCAL_INLINE void Com_Lok_TxIpduInitializeCounter(PduIdType ComTxPduId);
#endif

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE void Com_Lok_LoadSigTimeoutValue(
                                        Com_SignalIdType        SignalId
   ,                                       uint8                   SigUpdateBitStatus
   ,                                       uint16_least *          Idx_SigToutPtr
                                             );
#endif

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE void Com_Lok_LoadSigGrpTimeoutValue(
                                        Com_SignalGroupIdType   SigGrpId
   ,                                       uint8                   SigUpdateBitStatus
   ,                                       uint16_least *          Idx_SigToutPtr
                                                );
#endif

LOCAL_INLINE void Com_SetCurrentTxModePtr(
                                    Com_TxIpduRamPtrType            TxIpduRamPtr
   ,                                   Com_TxIpduConstPtrType          TxIpduConstPtr
   ,                                   boolean                         ModeRequested
                                         )
{
   uint16      TMSStatus;

    TMSStatus = Com_GetValue(TXIPDU,_TMS,TxIpduConstPtr->txIPduFields);

    TxIpduRamPtr->CurrentTxModePtr = TxIpduConstPtr->Com_TMConstPtr;

   if(ModeRequested == COM_FALSE)
   {
        if(TMSStatus == COM_TRUEMODE_VALID)
        {

            TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo;
        }
        else if(TMSStatus == COM_MODE_VALID)
        {

            TxIpduRamPtr->CurrentTxModePtr++;
        }
        else{

        }
   }
   else{
        if(TMSStatus == COM_FALSEMODE_VALID)
        {
            TxIpduRamPtr->CurrentTxModePtr = &Com_NONE_TransModeInfo;
        }
        else{

        }
   }
}

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void Com_UpdateRxGroupSignalSecondBuffer(
                                    Com_RxGrpSigConstPtrType        RxGrpSigConstPtr
   ,                                   Com_SigMaxType                  RxNewVal
   ,                                   Com_MainFuncType                RxMainFuncId
                                                     )
{
   uint8       Type;

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

# ifdef COM_GRPSIGFLOAT32SUPP
   case (COM_FLOAT32 >> 1u):

# endif

        COM_GET_SECRXGRPSIGTYPEU32_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint32)RxNewVal;
        break;

# ifdef COM_RXGRPSIG_INT64
   case 0x08u:

        COM_GET_SECRXGRPSIGTYPEU64_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = RxNewVal;
        break;
# endif

   case 0x03u:

        COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = (uint8)RxNewVal;
        break;

   case 0x04u:

        Com_ByteCopyInit(&COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index)
   ,                        (uint32)RxNewVal,RxGrpSigConstPtr->BitSize);
        break;
    default:

        break;

   }
}
#endif

LOCAL_INLINE void Com_UpdateRxSignalBuffer(
                                    Com_RxSigConstPtrType           RxSigConstPtr
   ,                                   Com_SigMaxType                  RxNewVal_Sig
   ,                                   Com_MainFuncType                RxMainFuncId
                                          )
{
   uint8       Type;

    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

   switch(Type >> 1u)
   {
   case 0x00u:
   case (COM_BOOLEAN >> 1u):
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
   ,                        (uint32)RxNewVal_Sig,RxSigConstPtr->BitSize);
        break;
    default:

        break;
   }
}

LOCAL_INLINE void Com_InitializePduBuffWithSignalInitValue(
                                    uint8 *                         BuffPtr
   ,                                   Com_SigMaxType                  SigInitVal
   ,                                   Com_BitpositionType             SigBitPos
   ,                                   Com_BitsizeType                 SigBitSize
   ,                                   uint8                           SigType
   ,                                   uint8                           SigEndianess
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
        PduLengthType ByteOffset_uo;

        ByteOffset_uo = ( PduLengthType )( SigBitPos >> 3 );

        Com_ByteCopyInit( (BuffPtr + ByteOffset_uo), (uint32)SigInitVal, SigBitSize );
   }
}

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void Com_Lok_SigGrpReplaceToInit(Com_RxSigGrpConstPtrType RxSigGrpConstPtr, Com_MainFuncType RxMainFuncId)
{
   Com_RxGrpSigConstPtrType            RxGrpSigConstPtr;
# ifdef COM_RX_SIGNALGROUP_ARRAY
   Com_RxSigGrpArrayConstPtrType       RxSigGrpArrayConstPtr;
   uint8 *                             RxSigGrpArrayBufRamPtr;
   PduLengthType                       SigGrpBitOffset;
# endif
   uint16_least                        idx_RxGrpSig_u16;
   Com_SigMaxType                      SigValue;
# if(defined(COM_RX_SIGNALGROUP_ARRAY) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_INT64))
   uint8                               SigType;
# endif
# ifdef COM_RX_SIGNALGROUP_ARRAY
   boolean                             isSigGrpArrayAccess_b;

   isSigGrpArrayAccess_b = Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields);

   if( isSigGrpArrayAccess_b )
   {
        RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

        RxSigGrpArrayBufRamPtr = &COM_GET_RXSIGGRP_ARRAY_BUFF(RxMainFuncId, RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

        SigGrpBitOffset        = ( RxSigGrpArrayConstPtr->FirstByteNo * 8u );

        Com_Get_SchM_Enter_Com_RxSigGrpArrayBuff
   }
   else
# endif
   {
        Com_Get_SchM_Enter_Com_RxGrpSigSecBuff
   }

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA( RxSigGrpConstPtr->FirstGrpSig_Index );

   for( idx_RxGrpSig_u16 = RxSigGrpConstPtr->No_Of_GrpSig; idx_RxGrpSig_u16 > COM_ZERO; idx_RxGrpSig_u16-- )
   {
# if(defined(COM_RX_SIGNALGROUP_ARRAY) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_INT64))
        SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
# endif

        SigValue = RxGrpSigConstPtr->Init_Val;

#ifdef COM_RXGRPSIG_INT64

        SigValue = (SigType == COM_SINT64) ? (Com_SigMaxType)((sint64)((sint32)SigValue)) : SigValue;
#endif

# ifdef COM_RX_SIGNALGROUP_ARRAY
        if( isSigGrpArrayAccess_b )
        {
            Com_BitpositionType RelativeSigBitPos;

            RelativeSigBitPos = RxGrpSigConstPtr->Bit_Pos - ( Com_BitpositionType )SigGrpBitOffset;

            Com_InitializePduBuffWithSignalInitValue(
                                              RxSigGrpArrayBufRamPtr
   ,                                             SigValue
   ,                                             RelativeSigBitPos
   ,                                             RxGrpSigConstPtr->BitSize
   ,                                             SigType
   ,                                             Com_GetValue(RXGRPSIG,_ENDIANESS,RxGrpSigConstPtr->rxGrpSigFields) );
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

   if( isSigGrpArrayAccess_b )
   {
        Com_Get_SchM_Exit_Com_RxSigGrpArrayBuff
   }
   else
# endif
   {
        Com_Get_SchM_Exit_Com_RxGrpSigSecBuff
   }
}
#endif

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification
LOCAL_INLINE void Com_CallTxNotifyCallback(Com_IpduIdType IpduId)
        {
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType    TxSigGrpConstPtr;
#endif
   uint8_least                 index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIpduConstPtr->TxSigId_Index; index_u8 < (TxIpduConstPtr->TxSigId_Index + TxIpduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->Notification_Cbk != NULL_PTR)
        {
            TxSigConstPtr->Notification_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIpduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIpduConstPtr->FirstTxSigGrp_Index + TxIpduConstPtr->No_Of_SigGrp_Ref); index_u8++)
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
LOCAL_INLINE void Com_CallTxErrNotifyCallback(Com_IpduIdType IpduId)
{

   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType    TxSigGrpConstPtr;
#endif
   uint8_least                 index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIpduConstPtr->TxSigId_Index; index_u8 < (TxIpduConstPtr->TxSigId_Index + TxIpduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->NotificationError_Cbk != NULL_PTR)
        {
            TxSigConstPtr->NotificationError_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIpduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIpduConstPtr->FirstTxSigGrp_Index + TxIpduConstPtr->No_Of_SigGrp_Ref); index_u8++)
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
LOCAL_INLINE void Com_CallTxTONotifyCallback(Com_IpduIdType IpduId)
{

   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType    TxSigGrpConstPtr;
#endif
   uint8_least                 index_u8;

    IpduId = COM_GET_TX_IPDU_ID(IpduId);
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);
#ifdef COM_TX_SIGNALGROUP
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);
#endif

   for(index_u8 = TxIpduConstPtr->TxSigId_Index; index_u8 < (TxIpduConstPtr->TxSigId_Index + TxIpduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(TxSigConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            TxSigConstPtr->TimeOutNotification_Cbk();
        }
        TxSigConstPtr++;
   }
#ifdef COM_TX_SIGNALGROUP
   for(index_u8 = TxIpduConstPtr->FirstTxSigGrp_Index; index_u8 < (TxIpduConstPtr->FirstTxSigGrp_Index + TxIpduConstPtr->No_Of_SigGrp_Ref); index_u8++)
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
LOCAL_INLINE void Com_CallRxTONotifyCallback(Com_IpduIdType IpduId)
{

   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxSigConstPtrType       RxSigConstPtr;
#ifdef COM_RX_SIGNALGROUP
   Com_RxSigGrpConstPtrType    RxSigGrpConstPtr;
#endif
   uint8_least                 index_u8;

    IpduId = COM_GET_RX_IPDU_ID(IpduId);
    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);
    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIpduConstPtr->RxSigId_Index);
#ifdef COM_RX_SIGNALGROUP
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIpduConstPtr->FirstRxSigGrp_Index);
#endif

   for(index_u8 = RxIpduConstPtr->RxSigId_Index; index_u8 < (RxIpduConstPtr->RxSigId_Index + RxIpduConstPtr->No_Of_Sig_Ref); index_u8++)
   {
        if(RxSigConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            RxSigConstPtr->TimeOutNotification_Cbk();
        }
        RxSigConstPtr++;
   }
#ifdef COM_RX_SIGNALGROUP
   for(index_u8 = RxIpduConstPtr->FirstRxSigGrp_Index; index_u8 < (RxIpduConstPtr->FirstRxSigGrp_Index + RxIpduConstPtr->No_Of_SigGrp_Ref); index_u8++)
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
LOCAL_INLINE void Com_CopyTxGroupSignalData(
                                Com_SignalIdType        GrpSignalId
   ,                               Com_SigMaxType          TxGrpSig_NewVal
   ,                               Com_MainFuncType        TxMainFuncId
                                           )
{
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
   Com_TxGrpSigBuffIndexType       GrpSigBuff_Index;
   uint8                           Type;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(GrpSignalId);
    GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;
    Type = Com_GetValue(TXGRPSIG,_TYPE,TxGrpSigConstPtr->txGrpSigFields);

   switch(Type >> 1u)
   {
        case 0x00u:
        case 0x03u:
        {
            COM_GET_TXGRPSIGTYPEU8_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint8)TxGrpSig_NewVal;
        }
        break;

        case 0x01u:
        {
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_TxGrpSigBuffer();
#endif
            COM_GET_TXGRPSIGTYPEU16_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint16)TxGrpSig_NewVal;
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_TxGrpSigBuffer();
#endif
        }
        break;

        case 0x02u:

#ifdef COM_GRPSIGFLOAT32SUPP
        case (COM_FLOAT32 >> 1u):
#endif

        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_TxGrpSigBuffer();
#endif
            COM_GET_TXGRPSIGTYPEU32_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint32)TxGrpSig_NewVal;
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_TxGrpSigBuffer();
#endif
        }
        break;

#ifdef COM_TXGRPSIG_INT64
        case 0x08u:
        {
            SchM_Enter_Com_TxGrpSigBuffer();
            COM_GET_TXGRPSIGTYPEU64_BUFF(TxMainFuncId, GrpSigBuff_Index) = (uint64)TxGrpSig_NewVal;
            SchM_Exit_Com_TxGrpSigBuffer();
        }
        break;
#endif

        default:

        break;
   }
}
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)

LOCAL_INLINE boolean Com_Lok_DETCheck_Param(boolean isInValidParam, uint8 ApiId)
{

   uint8       ErrorId;
   boolean     Status;

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

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId)

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE boolean Com_Lok_DETCheck_Ptr(boolean isInValidPtr, uint8 ApiId)
{

   uint8       ErrorId;
   boolean     Status;

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

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId)

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE boolean Com_Lok_DETCheck_Param_Ptr(boolean isInValidParam, boolean isInValidPtr, uint8 ApiId)
{

   uint8       ErrorId;
   boolean     Status;

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

        COM_REPORT_ERROR_CHECK(ApiId, ErrorId)

        Status = COM_FALSE;
   }
    return Status;
}

LOCAL_INLINE boolean Com_Lok_DETCheck_Ptr_Only(boolean isInValidPtr, uint8 ApiId)
{

   boolean     Status;

    Status = COM_TRUE;

   if(isInValidPtr)
   {

        COM_REPORT_ERROR_CHECK(ApiId, COM_E_PARAM_POINTER)

        Status = COM_FALSE;
   }
   else{

   }

    return Status;
}

LOCAL_INLINE boolean Com_Lok_DETCheck_Param_Only(boolean isInValidParam, uint8 ApiId)
{

   boolean     Status;

    Status = COM_TRUE;

   if(isInValidParam)
   {

        COM_REPORT_ERROR_CHECK(ApiId, COM_E_PARAM)

        Status = COM_FALSE;
   }
   else{

   }

    return Status;
}

#endif

LOCAL_INLINE boolean Com_CheckTxIPduStatus(PduIdType IpduId)
{
   boolean     TxIPduStatus;

    TxIPduStatus = (Com_GetRamValue(TXIPDU,_PDUSTATUS,COM_GET_TXPDURAM_S(IpduId).Com_TxFlags))

#ifdef COM_TX_IPDUCONTROL_VIA_CALIBRATION
                && (Com_CheckTxIPduCalibrationVarStatus(IpduId))
#endif
#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
                && (Com_CheckTxIPduControlViaRbaNdsEcuVariant(IpduId))
#endif

                         ;

    return TxIPduStatus;
}

LOCAL_INLINE boolean Com_CheckRxIPduStatus(PduIdType IpduId)
{
   boolean     RxIPduStatus;

    RxIPduStatus = (Com_GetRamValue(RXIPDU,_PDUSTATUS,COM_GET_RXPDURAM_S(IpduId).RxFlags))

#ifdef COM_RX_IPDUCONTROL_VIA_CALIBRATION
                && (Com_CheckRxIPduCalibrationVarStatus(IpduId))
#endif
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
                && (Com_CheckRxIPduControlViaRbaNdsEcuVariant(IpduId))
#endif

                        ;

    return RxIPduStatus;
}

#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

LOCAL_INLINE boolean Com_CheckRxIPduControlViaRbaNdsEcuVariant(PduIdType IpduId)
{
   uint16   index_u16;
   uint8    bitOffset_u8;

   index_u16    = IpduId >> 3u;
   bitOffset_u8 = (uint8)(IpduId % 8u);

    return (((Com_RxIpduControlVector[index_u16] >> bitOffset_u8) & COM_ONE) != COM_ZERO);
}
#endif

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

LOCAL_INLINE boolean Com_CheckTxIPduControlViaRbaNdsEcuVariant(PduIdType IpduId)
{
   uint16   index_u16;
   uint8    bitOffset_u8;

   index_u16    = IpduId >> 3u;
   bitOffset_u8 = (uint8)(IpduId % 8u);

    return (((Com_TxIpduControlVector[index_u16] >> bitOffset_u8) & COM_ONE) != COM_ZERO);
}
#endif

LOCAL_INLINE void Com_Lok_ProceedToSendIpdu(Com_IpduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16)
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)

   if(Com_GetValue(TXIPDU,_ISGWPDU,COM_GET_TX_IPDU_CONSTDATA(ComTxPduId)->txIPduFields))
   {

        SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);

        if(sendIpduFlag_u16.isSigTriggered == COM_SET)
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

        SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
   }
   else
#endif
   {

        if(((sendIpduFlag_u16.isSigTriggered == COM_SET) &&
             (COM_TX_MODE_IS_EVENT(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))))
#ifdef COM_TxFilters
            || (sendIpduFlag_u16.isModeChangd == COM_SET)
#endif
           )
        {

            sendIpduFlag_u16.isEventTrig = COM_SET;

            Com_Lok_SendIpdu((PduIdType)ComTxPduId, sendIpduFlag_u16);
        }
   }
}

#ifdef COM_TxFilters

LOCAL_INLINE boolean Com_Lok_CheckModeChange(Com_IpduIdType TxIpduId)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   boolean                     ReturnValue;
   boolean                     Mode;

    TxIpduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);

    Mode            = COM_FALSE;
    ReturnValue     = COM_FALSE;

   if(TxIpduRamPtr->Com_TMSTrueCounter_u16 != COM_ZERO)
   {

        Mode = COM_TRUE;
   }

   if(Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode)
   {
        ReturnValue = COM_TRUE;

        Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

        Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIpduConstPtr,Mode);

        Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);

#ifdef COM_MIXEDPHASESHIFT

        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif

   }

    return(ReturnValue);
}

#endif

#ifdef COM_TX_IPDUCOUNTER

LOCAL_INLINE void Com_Lok_TxIpduInitializeCounter(PduIdType ComTxPduId)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxIpduCntrConstPtrType      TxIpduCntrConstPtr;
   uint8 *                         counterBytePtr;

    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduCntrConstPtr  = COM_GET_TX_IPDU_CNTR_CONSTDATA(TxIpduConstPtr->TxIpduCntr_Index);

   counterBytePtr      = (uint8 *)(TxIpduConstPtr->BuffPtr + (TxIpduCntrConstPtr->CntrBitPos / 8u));

   COM_GET_TXIPDU_CNTR_VAL(TxIpduConstPtr->TxIpduCntr_Index) = COM_ZERO;

   COM_PACK_CNTR_INTO_IPDU_BUFF((uint8 *)(counterBytePtr), (uint8)(TxIpduCntrConstPtr->CntrBitPos % 8u)
   ,                                          TxIpduCntrConstPtr->CntrBitSize, COM_ZERO);
}

#endif

#ifdef COM_RxSigUpdateTimeout

LOCAL_INLINE void Com_Lok_LoadSigTimeoutValue(
                                        Com_SignalIdType    SignalId
   ,                                       uint8               SigUpdateBitStatus
   ,                                       uint16_least *      Idx_SigToutPtr
                                             )
{
   Com_RxSigConstPtrType               RxSigConstPtr;
   Com_RxIpduConstPtrType              RxIpduConstPtr;
   const Com_SignalTimeoutInfo *       SigTimeOutConstPtr;
   uint16 *                            SigTimeOutRamPtr;

    RxSigConstPtr  = COM_GET_RXSIG_CONSTDATA(SignalId);

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef);

   if(*Idx_SigToutPtr < RxIpduConstPtr->SignalTimeout_Ref->numWithUpdateBit )
   {

        SigTimeOutConstPtr = &RxIpduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref[*Idx_SigToutPtr];

        if(SigTimeOutConstPtr->SigId == (uint16)SignalId)
        {
            if(SigUpdateBitStatus == COM_UPDATEBIT_SET)
            {

                SigTimeOutRamPtr = &RxIpduConstPtr->SignalTimeout_Ref->TimeoutTicks_p[*Idx_SigToutPtr];

                Com_Get_SchM_Enter_Com_RxSigToTicks

#if(COM_ENABLE_JITTERFLITER == STD_ON)

                (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout + 2u;
#else

                (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout + 1u;

#endif

                Com_Get_SchM_Exit_Com_RxSigToTicks
            }

            (*Idx_SigToutPtr)++;

        }
   }
}
#endif

#ifdef COM_RxSigGrpUpdateTimeout

LOCAL_INLINE void Com_Lok_LoadSigGrpTimeoutValue(
                                            Com_SignalGroupIdType   SigGrpId
   ,                                           uint8                   SigUpdateBitStatus
   ,                                           uint16_least *          Idx_SigToutPtr
                                                )
{
   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;
   Com_RxIpduConstPtrType              RxIpduConstPtr;
   const Com_SignalTimeoutInfo *       SigTimeOutConstPtr;
   uint16 *                            SigTimeOutRamPtr;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef);

   if(*Idx_SigToutPtr < RxIpduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit )
   {

        SigTimeOutConstPtr = &RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref[*Idx_SigToutPtr];

        if(SigTimeOutConstPtr->SigId == (uint16)SigGrpId)
        {
            if(SigUpdateBitStatus == COM_UPDATEBIT_SET)
            {

                SigTimeOutRamPtr = &RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p[*Idx_SigToutPtr];

                Com_Get_SchM_Enter_Com_RxSigGrpToTicks

#if(COM_ENABLE_JITTERFLITER == STD_ON)

                (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout + 2u;
#else

                (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout + 1u;

#endif

                Com_Get_SchM_Exit_Com_RxSigGrpToTicks
            }

            (*Idx_SigToutPtr)++;

        }
   }
}
#endif

#endif

