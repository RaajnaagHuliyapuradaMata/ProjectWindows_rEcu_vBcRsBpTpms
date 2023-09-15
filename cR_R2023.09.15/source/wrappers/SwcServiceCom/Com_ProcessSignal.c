#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RxSigUpdateBit
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_ProcessSigUpdateBit(
                                        VAR(Com_SignalIdType,AUTOMATIC)                 SignalId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(uint8, AUTOMATIC)                           UpdateBitStatus
   ,     P2VAR(uint16_least, AUTOMATIC, COM_APPL_DATA)   Idx_SigToutPtr
                                                                );
#endif

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_CopyRxSignal(
                                        VAR(Com_SignalIdType,AUTOMATIC)                 SignalId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(Com_BitsizeType, AUTOMATIC)                 Size
                                                         );

#if defined(COM_RxSigInvalid) || defined (COM_RxFilters)
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_ValidateRxSignal(
                                        VAR(Com_SignalIdType, AUTOMATIC)                SignalId
   ,     P2VAR(Com_SigMaxType, AUTOMATIC, COM_APPL_DATA) RxNewValPtr
                                                            );
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_Lok_ProcessSignal(
                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)                       RxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
                                          )
{
   Com_RxIpduConstPtrType          RxIPduConstPtr;
   Com_RxSigConstPtrType           RxSigConstPtr;
   Com_RxSigRamPtrType             RxSigRamPtr;
   VAR(uint16_least, AUTOMATIC)    Idx_Sig_ui;
   VAR(uint16_least, AUTOMATIC)    limit_ui;
#ifdef COM_RxSigUpdateBit
   VAR(uint16_least, AUTOMATIC)    Idx_SigTout;
   VAR(uint8, AUTOMATIC)           UpdateBitStatus;
#endif

   VAR(boolean, AUTOMATIC)         ProcessSignal_b;

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxSigUpdateBit
#ifdef COM_RxSigUpdateTimeout

   if((RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(RxPduId)))
   {

        UpdateBitStatus = UPDATEBIT_APPLICABLE;
   }
   else
#endif
   {
        UpdateBitStatus = UPDATEBIT_NOT_APPLICABLE;
   }

    Idx_SigTout = 0u;

#endif

    limit_ui      = (uint16_least)RxIPduConstPtr->RxSigId_Index + (uint16_least)RxIPduConstPtr->No_Of_Sig_Ref;
    RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

   for(Idx_Sig_ui = (uint16_least)RxIPduConstPtr->RxSigId_Index; Idx_Sig_ui < limit_ui; Idx_Sig_ui++)
   {

        ProcessSignal_b = COM_TRUE;

#ifdef COM_RxSigUpdateBit

        if(Com_Lok_ProcessSigUpdateBit( (Com_SignalIdType)Idx_Sig_ui, PduInfoPtr, UpdateBitStatus, &Idx_SigTout ))
#endif
        {
            VAR(Com_BitsizeType, AUTOMATIC)     Size;
            VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
            VAR(uint8, AUTOMATIC)               SigType;
            VAR(uint8, AUTOMATIC)               SigEndianess;

            ConstByteValue_u8  = RxSigConstPtr->General;

            SigType            = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
            SigEndianess       = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            if(SigType != COM_UINT8_DYN)
#endif
            {
                VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) SigLastByteNo;

                Size = RxSigConstPtr->BitSize;

                if(SigEndianess == COM_LITTLEENDIAN)
                {
                    VAR(Com_BitpositionType, AUTOMATIC) lastBitPosition;

                    lastBitPosition = (RxSigConstPtr->Bit_Pos +
                                      ((SigType == COM_UINT8_N) ? ((Com_BitpositionType)Size * 8u) : Size));

                    SigLastByteNo   = (Type_SwcServiceCom_tLengthPdu)((lastBitPosition != 0u) ? ((lastBitPosition - 1u) >> 3u) : (0u));
                }
                else{

                    SigLastByteNo   = (Type_SwcServiceCom_tLengthPdu)(RxSigConstPtr->Bit_Pos >> 3u);
                }

                if((SigLastByteNo + 1u) > PduInfoPtr->SduLength)
                {

                    ProcessSignal_b = COM_FALSE;
                }
            }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            else{
                VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) StartByteNo;

                StartByteNo = (Type_SwcServiceCom_tLengthPdu)(RxSigConstPtr->Bit_Pos >> 3u);

                Size = ((COM_GET_RXPDURAM_S(RxPduId).RxIPduLength > StartByteNo) ?

                       (Com_BitsizeType)( COM_GET_RXPDURAM_S(RxPduId).RxIPduLength - StartByteNo ) :

                       (0u));
            }
#endif

            if(ProcessSignal_b != COM_FALSE)
            {
                ProcessSignal_b = Com_Lok_CopyRxSignal((Com_SignalIdType)Idx_Sig_ui, PduInfoPtr, Size);
            }

        }

#ifdef COM_RxSignalNotify

        Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,ProcessSignal_b);
#else

        (void)(ProcessSignal_b);
#endif

        RxSigConstPtr++;
        RxSigRamPtr++;

   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_RxSigUpdateBit

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_ProcessSigUpdateBit(
                                                    VAR(Com_SignalIdType,AUTOMATIC)                 SignalId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(uint8, AUTOMATIC)                           UpdateBitStatus
   ,     P2VAR(uint16_least, AUTOMATIC, COM_APPL_DATA)   Idx_SigToutPtr
                                                                )
{
   Com_RxSigConstPtrType                                       RxSigConstPtr;
#ifdef COM_RxSigUpdateTimeout
   Com_RxIpduConstPtrType                                      RxIPduConstPtr;
   P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST)   SigTimeOutConfigPtr;
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)                     SigTimeOutTicksPtr;
#endif
   VAR(boolean, AUTOMATIC)                                     IsUpdateBitSet;

    IsUpdateBitSet = COM_TRUE;

    RxSigConstPtr  = COM_GET_RXSIG_CONSTDATA(SignalId);

   if(Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General))
   {
        VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) UB_ByteNo_u8;
        VAR(boolean, AUTOMATIC)       updateBitValue_b;

        UB_ByteNo_u8     = (Type_SwcServiceCom_tLengthPdu)(RxSigConstPtr->Update_Bit_Pos >> 3u);

        updateBitValue_b = Com_GetUpdateBitValue(PduInfoPtr->SduDataPtr, RxSigConstPtr->Update_Bit_Pos, UB_ByteNo_u8);

        if(((UB_ByteNo_u8 + 1u) <= PduInfoPtr->SduLength) && (updateBitValue_b == COM_FALSE))
        {

            IsUpdateBitSet  = COM_FALSE;
        }
#ifdef COM_RxSigUpdateTimeout
        else{

            UpdateBitStatus <<= 1u;
        }

        if(UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
        {
            RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef);

            SigTimeOutConfigPtr = (RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref) + (*Idx_SigToutPtr);

            if(SigTimeOutConfigPtr->SigId == (uint16)SignalId)
            {
                if(UpdateBitStatus == UPDATEBIT_SET)
                {

                    SigTimeOutTicksPtr  = (RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p) + (*Idx_SigToutPtr);

                    SchM_Enter_Com_RxSigToTicks();

#if(COM_ENABLE_JITTERFLITER == STD_ON)

                    (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 2;
#else

                    (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 1;

#endif

                    SchM_Exit_Com_RxSigToTicks();
                }

                (*Idx_SigToutPtr)++;

            }

        }

#else

        (void)(UpdateBitStatus);
        (void)(Idx_SigToutPtr);
#endif

   }

    return IsUpdateBitSet;
}
#endif

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_CopyRxSignal(
                                              VAR(Com_SignalIdType,AUTOMATIC)                 SignalId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(Com_BitsizeType, AUTOMATIC)                 Size
                                                         )
{
   Com_RxIpduConstPtrType                  RxIPduConstPtr;
   Com_RxSigConstPtrType                   RxSigConstPtr;
   Com_RxSigRamPtrType                     RxSigRamPtr;
   VAR(Com_SigMaxType, AUTOMATIC)          RxSigNewVal;
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)               RxPduId;
   VAR(Com_MainFuncType, AUTOMATIC)        rxMainFuncId;
   VAR(uint8, AUTOMATIC)                   ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)                   SigType;
   VAR(uint8, AUTOMATIC)                   SigEndianess;
   VAR(boolean, AUTOMATIC)                 copySignal_b;

    RxSigConstPtr      = COM_GET_RXSIG_CONSTDATA(SignalId);
    RxSigRamPtr        = &COM_GET_RXSIGNALFLAG(SignalId);

    RxPduId            = RxSigConstPtr->IpduRef;
    RxIPduConstPtr     = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    rxMainFuncId       = RxIPduConstPtr->MainFunctionRef;

   ConstByteValue_u8  = RxSigConstPtr->General;

    SigType            = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
    SigEndianess       = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

    RxSigNewVal        = 0u;
   copySignal_b       = COM_TRUE;

#ifdef COM_RXSIG_FLOAT64SUPP
   if(SigType == COM_FLOAT64)
   {
        VAR(float64, AUTOMATIC) RxSigNewVal_f64;

        RxSigNewVal_f64 = Com_UnPackFloatSignal( SigEndianess, RxSigConstPtr->Bit_Pos, PduInfoPtr->SduDataPtr );

        SchM_Enter_Com_RxSigBuff(RXINDICATION);

        COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId,RxSigConstPtr->SigBuff_Index) = RxSigNewVal_f64;
        SchM_Exit_Com_RxSigBuff(RXINDICATION);
   }
   else
#endif

   {

        if( !((SigType == COM_UINT8_N)
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
             ||(SigType == COM_UINT8_DYN)
#endif
            ))
        {
            RxSigNewVal = Com_UnpackSignal( SigEndianess, RxSigConstPtr->Bit_Pos, Size, PduInfoPtr->SduDataPtr
   ,     ((SigType & 0x01u) != 0x0u));
        }
        else{
            RxSigNewVal = (Com_SigMaxType)Com_UnpackOpaqueSignal(RxSigConstPtr->Bit_Pos, Size, PduInfoPtr->SduDataPtr);
        }

#if defined(COM_RxSigInvalid) || defined(COM_RxFilters)

        copySignal_b = Com_Lok_ValidateRxSignal( SignalId, &RxSigNewVal );

#endif
   }

#if defined(COM_RxSigInvalid) || defined(COM_RxFilters)
   if(copySignal_b != COM_FALSE)
#endif
   {

        if((Size != 0u)

#ifdef COM_RXSIG_FLOAT64SUPP

        && (SigType != COM_FLOAT64)
#endif

           )
        {
            VAR(Com_SigBuffIndexType,AUTOMATIC) SigBuff_Index;

            SigBuff_Index = RxSigConstPtr->SigBuff_Index;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            if(SigType != COM_UINT8_DYN)
#endif
            {
                SchM_Enter_Com_RxSigBuff(RXINDICATION);

                if(SigType != COM_UINT8_N)
                {

                    Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigNewVal, rxMainFuncId);
                }
                else{

                    Com_ByteCopy( &COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId,SigBuff_Index)
   ,     (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size );
                }

                SchM_Exit_Com_RxSigBuff(RXINDICATION);
            }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            else{
                SchM_Enter_Com_RxSigDynBuff();

                Com_ByteCopy( &COM_GET_SIGTYPEUINT8DYN_BUFF(rxMainFuncId,SigBuff_Index)
   ,     (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size );

                SchM_Exit_Com_RxSigDynBuff();
            }
#endif
        }

#ifdef COM_SIGNALGATEWAY

        if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields))
        {

            Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr->rxSigRAMFields,COM_TRUE);

            COM_GET_IS_GWSIG_UPDATED( RxPduId ) = COM_TRUE;
        }
#endif

   }

    return copySignal_b;
}

#if defined(COM_RxSigInvalid) || defined (COM_RxFilters)

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_ValidateRxSignal(
                                                VAR(Com_SignalIdType, AUTOMATIC)                SignalId
   ,     P2VAR(Com_SigMaxType, AUTOMATIC, COM_APPL_DATA) RxNewValPtr
                                                            )
{
   Com_RxSigConstPtrType   RxSigConstPtr;
   Com_RxSigRamPtrType     RxSigRamPtr;
   VAR(uint8, AUTOMATIC)   ConstByteValue_u8;
   VAR(boolean, AUTOMATIC) isValidRxSig_b;

    RxSigConstPtr     = COM_GET_RXSIG_CONSTDATA(SignalId);
   isValidRxSig_b    = COM_TRUE;

    RxSigRamPtr       = &COM_GET_RXSIGNALFLAG(SignalId);
   ConstByteValue_u8 = RxSigConstPtr->rxSignalFields;

#ifdef COM_RxSigInvalid
   {
        VAR(uint8, AUTOMATIC) InvAction;

        InvAction = Com_GetValue(RXSIG,_INVACTION,ConstByteValue_u8);

        if((InvAction != (uint8)COM_NONE) && ((Com_SigMaxType)RxSigConstPtr->DataInvalid_Val == *RxNewValPtr))
        {
            if( InvAction == (uint8)COM_REPLACE )
            {
                VAR(Com_SigMaxType,AUTOMATIC) RxSigVal;

                RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

#ifdef COM_RXSIG_INT64

                if( Com_GetValue(GEN,_TYPE,RxSigConstPtr->General) == COM_SINT64 )
                {
                    RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
                }
                else{

                }
#endif

                (*RxNewValPtr) = RxSigVal;
            }

#ifdef COM_RxSigInvalidNotify
            else{

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
        VAR(uint8, AUTOMATIC) filterAlgo_u8;

        filterAlgo_u8 = Com_GetValue(RXSIG,_FILTRALG,ConstByteValue_u8);

        if( ( COM_FALSE != isValidRxSig_b ) && ( COM_NOTCONFIGURED != filterAlgo_u8 ) )
        {

#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))

            if(!((Com_GetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields) == COM_TRUE) &&
                 (COM_MASKED_NEW_DIFFERS_MASKED_OLD == filterAlgo_u8))
            ){
#endif
               isValidRxSig_b = Com_Filter(
                     uint32)(*RxNewValPtr)
                  ,  filterAlgo_u8
                  ,  RxSigConstPtr->Filter_Index
                  ,  COM_TRUE
               );
#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
            }
            else{
                Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
            }
#endif
        }
   }
#endif
    return (isValidRxSig_b);
}
#endif

