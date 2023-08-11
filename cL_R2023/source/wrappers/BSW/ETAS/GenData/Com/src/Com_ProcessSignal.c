

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_RxSigUpdateBit
LOCAL_INLINE boolean Com_Lok_ProcessSigUpdateBit(
                                        Com_SignalIdType    SignalId,
                                        const PduInfoType * PduInfoPtr
                                                );
#endif

LOCAL_INLINE boolean Com_Lok_CopyRxSignal(
                                        Com_SignalIdType    SignalId,
                                        const PduInfoType * PduInfoPtr,
                                        Com_BitsizeType     Size
                                         );

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_ProcessSignal(PduIdType RxPduId, const PduInfoType * PduInfoPtr)
{
    Com_RxIpduConstPtrType      RxIpduConstPtr;
    Com_RxSigConstPtrType       RxSigConstPtr;
#ifdef COM_RxSignalNotify
    Com_RxSigRamPtrType         RxSigRamPtr;
#endif
    uint16_least                idx_SigId_u16;
    uint16_least                maxRxSigId_u16;
#ifdef COM_RxSigUpdateTimeout
    uint16_least                Idx_SigTout;
    uint8                       IpduUpdateBitStatus;
    uint8                       SigUpdateBitStatus;
#endif

    boolean                     ProcessSignal_b;

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxSigUpdateTimeout

    if ((RxIpduConstPtr->SignalTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(RxPduId)))
    {

        IpduUpdateBitStatus = COM_UPDATEBIT_APPLICABLE;
    }
    else
    {
        IpduUpdateBitStatus = COM_UPDATEBIT_NOT_APPLICABLE;
    }

    Idx_SigTout = COM_ZERO;
#endif

    idx_SigId_u16   = RxIpduConstPtr->RxSigId_Index;
    maxRxSigId_u16  = idx_SigId_u16 + RxIpduConstPtr->No_Of_Sig_Ref;

    RxSigConstPtr   = COM_GET_RXSIG_CONSTDATA(idx_SigId_u16);
#ifdef COM_RxSignalNotify
    RxSigRamPtr     = &COM_GET_RXSIGNALFLAG(idx_SigId_u16);
#endif

    for ( ; idx_SigId_u16 < maxRxSigId_u16; idx_SigId_u16++ )
    {

        ProcessSignal_b = COM_TRUE;
#ifdef COM_RxSigUpdateTimeout
        SigUpdateBitStatus = IpduUpdateBitStatus;
#endif

#ifdef COM_RxSigUpdateBit

        if (Com_Lok_ProcessSigUpdateBit( (Com_SignalIdType)idx_SigId_u16, PduInfoPtr ))
#endif
        {
            Com_BitsizeType     Size;
            uint8               ConstByteValue_u8;
            uint8               SigType;
            uint8               SigEndianess;

            ConstByteValue_u8  = RxSigConstPtr->General;

            SigType            = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
            SigEndianess       = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            if (SigType != COM_UINT8_DYN)
#endif
            {
                PduLengthType       SigLastByteNo;

                Size = RxSigConstPtr->BitSize;

                if (SigEndianess != COM_BIGENDIAN)
                {
                    Com_BitpositionType     lastBitPosition;

                    lastBitPosition = (RxSigConstPtr->Bit_Pos +
                                      ((SigType == COM_UINT8_N) ? ((Com_BitpositionType)Size * 8u) : Size));

                    SigLastByteNo   = (PduLengthType)((lastBitPosition != COM_ZERO) ? ((lastBitPosition - COM_ONE) >> 3u) : (COM_ZERO));
                }
                else
                {

                    SigLastByteNo   = (PduLengthType)(RxSigConstPtr->Bit_Pos >> 3u);
                }

                if ((SigLastByteNo + COM_ONE) > PduInfoPtr->SduLength)
                {

                    ProcessSignal_b = COM_FALSE;
                }
            }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            else
            {
                PduLengthType       StartByteNo;

                StartByteNo = (PduLengthType)(RxSigConstPtr->Bit_Pos >> 3u);

                Size = ((COM_GET_RXPDURAM_S(RxPduId).RxIPduLength > StartByteNo) ?

                       (Com_BitsizeType)( COM_GET_RXPDURAM_S(RxPduId).RxIPduLength - StartByteNo ) :

                       (COM_ZERO));
            }
#endif

            if ((ProcessSignal_b) && Com_Lok_CopyRxSignal((Com_SignalIdType)idx_SigId_u16, PduInfoPtr, Size))
            {

#ifdef COM_RxSigUpdateTimeout

                SigUpdateBitStatus <<= COM_ONE;
#endif
            }
            else
            {
                ProcessSignal_b = COM_FALSE;
            }
        }
#ifdef COM_RxSigUpdateBit
        else
        {
            ProcessSignal_b = COM_FALSE;
        }
#endif

#ifdef COM_RxSigUpdateTimeout

        if (SigUpdateBitStatus != COM_UPDATEBIT_NOT_APPLICABLE)
        {
            Com_Lok_LoadSigTimeoutValue( (Com_SignalIdType)idx_SigId_u16, SigUpdateBitStatus, &Idx_SigTout );
        }
#endif

#ifdef COM_RxSignalNotify

        Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,ProcessSignal_b);
#else

        (void)(ProcessSignal_b);
#endif

        RxSigConstPtr++;
#ifdef COM_RxSignalNotify
        RxSigRamPtr++;
#endif

    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_RxSigUpdateBit

LOCAL_INLINE boolean Com_Lok_ProcessSigUpdateBit(
                                            Com_SignalIdType    SignalId,
                                            const PduInfoType * PduInfoPtr
                                                )
{
    Com_RxSigConstPtrType               RxSigConstPtr;
    boolean                             isUpdateBitSet_b;

    isUpdateBitSet_b = COM_TRUE;

    RxSigConstPtr  = COM_GET_RXSIG_CONSTDATA(SignalId);

    if (Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General))
    {
        PduLengthType       UB_ByteNo_u8;

        UB_ByteNo_u8     = (PduLengthType)(RxSigConstPtr->Update_Bit_Pos >> 3u);

        if ((UB_ByteNo_u8 + COM_ONE) <= PduInfoPtr->SduLength)
        {

            isUpdateBitSet_b  = Com_GetUpdateBitValue(PduInfoPtr->SduDataPtr,
                                                      RxSigConstPtr->Update_Bit_Pos,
                                                      UB_ByteNo_u8);
        }
        else
        {

        }
    }

    return isUpdateBitSet_b;
}
#endif

LOCAL_INLINE boolean Com_Lok_CopyRxSignal(
                                    Com_SignalIdType    SignalId,
                                    const PduInfoType * PduInfoPtr,
                                    Com_BitsizeType     Size
                                         )
{
    Com_RxIpduConstPtrType      RxIpduConstPtr;
    Com_RxSigConstPtrType       RxSigConstPtr;
    Com_SigMaxType              RxSigNewVal;
    PduIdType                   RxPduId;
    Com_MainFuncType            rxMainFuncId;
    uint8                       ConstByteValue_u8;
    uint8                       SigType;
    uint8                       SigEndianess;
    boolean                     copySignal_b;

    RxSigConstPtr      = COM_GET_RXSIG_CONSTDATA(SignalId);

    RxPduId            = RxSigConstPtr->IpduRef;
    RxIpduConstPtr     = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    rxMainFuncId       = RxIpduConstPtr->MainFunctionRef;

    ConstByteValue_u8  = RxSigConstPtr->General;

    SigType            = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
    SigEndianess       = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

    RxSigNewVal        = COM_ZERO;
    copySignal_b       = COM_TRUE;

#ifdef COM_RXSIG_FLOAT64SUPP
    if (SigType == COM_FLOAT64)
    {
        float64     RxSigNewVal_f64;

        RxSigNewVal_f64 = Com_UnPackFloatSignal( SigEndianess, RxSigConstPtr->Bit_Pos, PduInfoPtr->SduDataPtr );

        Com_Get_SchM_Enter_Com_RxSigBuff(RXINDICATION)

        COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId,RxSigConstPtr->SigBuff_Index) = RxSigNewVal_f64;
        Com_Get_SchM_Exit_Com_RxSigBuff(RXINDICATION)
    }
    else
#endif

    {

        if ( !((SigType == COM_UINT8_N)
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
             ||(SigType == COM_UINT8_DYN)
#endif
            ))
        {
            RxSigNewVal = Com_UnpackSignal( SigEndianess, RxSigConstPtr->Bit_Pos, Size, PduInfoPtr->SduDataPtr,
                                                                                    ((SigType & COM_ONE) != COM_ZERO));
        }
        else
        {
            RxSigNewVal = Com_UnpackOpaqueSignal(RxSigConstPtr->Bit_Pos, Size, PduInfoPtr->SduDataPtr);
        }

#if defined(COM_RxSigInvalid) || defined(COM_RxFilters)

#ifdef COM_SIGNALGATEWAY

        if (Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) == COM_FALSE)
#endif
        {

            copySignal_b = Com_Lok_ValidateRxSignal( SignalId, &RxSigNewVal );
        }

#endif
    }

#if defined(COM_RxSigInvalid) || defined(COM_RxFilters)
    if (copySignal_b != COM_FALSE)
#endif
    {

        if ((Size != COM_ZERO)

#ifdef COM_RXSIG_FLOAT64SUPP

        && (SigType != COM_FLOAT64)
#endif

           )
        {
            Com_SigBuffIndexType        SigBuff_Index;

            SigBuff_Index = RxSigConstPtr->SigBuff_Index;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            if (SigType != COM_UINT8_DYN)
#endif
            {
                Com_Get_SchM_Enter_Com_RxSigBuff(RXINDICATION)

                if (SigType != COM_UINT8_N)
                {

                    Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigNewVal, rxMainFuncId);
                }
                else
                {

                    Com_ByteCopy( &COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId,SigBuff_Index),
                                  (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size );
                }
                Com_Get_SchM_Exit_Com_RxSigBuff(RXINDICATION)

            }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            else
            {
                Com_Get_SchM_Enter_Com_RxSigDynBuff

                Com_ByteCopy( &COM_GET_SIGTYPEUINT8DYN_BUFF(rxMainFuncId,SigBuff_Index),
                              (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size );

                Com_Get_SchM_Exit_Com_RxSigDynBuff
            }
#endif
        }

#ifdef COM_SIGNALGATEWAY

        if (Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields))
        {

            Com_SetRamValue(RXSIG,_SIGNALFILLBIT,COM_GET_RXSIGNALFLAG(SignalId).rxSigRAMFields,COM_TRUE);

            COM_GET_IS_GWSIG_UPDATED( RxPduId ) = COM_TRUE;
        }
#endif

    }

    return copySignal_b;
}

#if defined(COM_RxSigInvalid) || defined (COM_RxFilters)

boolean Com_Lok_ValidateRxSignal(Com_SignalIdType SignalId, Com_SigMaxType * RxNewValPtr)
{
    Com_RxSigConstPtrType       RxSigConstPtr;
#if defined (COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD) && \
   (defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
    Com_RxSigRamPtrType         RxSigRamPtr;
#endif
    uint8                       rxSignalFields_u8;
    boolean                     isValidRxSig_b;

    isValidRxSig_b    = COM_TRUE;

    RxSigConstPtr     = COM_GET_RXSIG_CONSTDATA(SignalId);

#if defined (COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD) && \
   (defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
    RxSigRamPtr       = &COM_GET_RXSIGNALFLAG(SignalId);
#endif
    rxSignalFields_u8 = RxSigConstPtr->rxSignalFields;

#ifdef COM_RxSigInvalid
    {
        uint8   InvAction;

        InvAction = Com_GetValue(RXSIG,_INVACTION,rxSignalFields_u8);

        if ((InvAction != COM_NONE) && (RxSigConstPtr->DataInvalid_Val == *RxNewValPtr))
        {
            if ( InvAction == (uint8)COM_REPLACE )
            {
                Com_SigMaxType  RxSigVal;

                RxSigVal = RxSigConstPtr->Init_Val;

#ifdef COM_RXSIG_INT64

                if ( Com_GetValue(GEN,_TYPE,RxSigConstPtr->General) == COM_SINT64 )
                {
                    RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
                }
                else
                {

                }
#endif

                (*RxNewValPtr) = RxSigVal;
            }

#ifdef COM_RxSigInvalidNotify
            else
            {

                isValidRxSig_b = COM_FALSE;

                if(RxSigConstPtr->Sig_DataInvalid_Indication_Cbk != NULL_PTR)
                {
                    RxSigConstPtr->Sig_DataInvalid_Indication_Cbk();
                }

            }
#endif
        }
    }
#endif

#ifdef COM_RxFilters
    {
        uint8   filterAlgo_u8;

        filterAlgo_u8 = Com_GetValue(RXSIG,_FILTRALG,rxSignalFields_u8);

        if ( ( COM_FALSE != isValidRxSig_b ) && ( COM_NOTCONFIGURED != filterAlgo_u8 ) )
        {

#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))

            if(!((Com_GetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields) == COM_TRUE) &&
                 (COM_MASKED_NEW_DIFFERS_MASKED_OLD == filterAlgo_u8)))
            {
#endif
                isValidRxSig_b = Com_Filter((uint32)(*RxNewValPtr), filterAlgo_u8, RxSigConstPtr->Filter_Index,
                                                                                                     COM_TRUE);
#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
            }
            else
            {

                Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
            }
#endif
        }
    }
#endif

    return (isValidRxSig_b);
}
#endif

