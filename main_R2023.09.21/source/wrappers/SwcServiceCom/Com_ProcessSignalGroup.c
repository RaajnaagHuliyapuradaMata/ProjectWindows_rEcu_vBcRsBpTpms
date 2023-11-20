#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP
#ifdef COM_RxSigGrpUpdateBit
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_ProcessSigGrpUpdateBit(
                                                VAR(Com_SignalGroupIdType,AUTOMATIC)            SigGrpId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(uint8, AUTOMATIC)                           UpdateBitStatus
   ,     P2VAR(uint16_least, AUTOMATIC, COM_APPL_DATA)   Idx_SigToutPtr
                                                                   );
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_IpduBuffToSecondBuff(
                                                VAR(Com_SignalGroupIdType,AUTOMATIC)            SigGrpId
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)        BufferPtr
   ,     VAR(uint8,AUTOMATIC)                            ValidateSigGrp_u8
                                                              );

#if defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters)
LOCAL_INLINE FUNC(uint8,COM_CODE) Com_Lok_ValidateRxSignalGroup(
                                                VAR(Com_SignalGroupIdType,AUTOMATIC)            SigGrpId
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)        BufferPtr
                                                               );

LOCAL_INLINE FUNC(uint8,COM_CODE) Com_Lok_ValidateRxGroupSignal(VAR(uint16_least, AUTOMATIC)    Idx_GrpSig_ui
   ,     VAR(Com_SigMaxType, AUTOMATIC)  RxNewVal_GrpSig);
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopySecondaryBuffer(Com_RxSigGrpConstPtrType RxSigGrpConstPtr
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Buffer);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_Lok_ProcessSignalGroup(
                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)                      RxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
                                               )
{
   Com_RxIpduConstPtrType          RxIPduConstPtr;
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
   VAR(uint16_least, AUTOMATIC)    Idx_SigGrp_ui;
   VAR(uint16_least, AUTOMATIC)    limit_ui;
   VAR(uint8, AUTOMATIC)           ValidateSigGrp_u8;
#ifdef COM_RxSigGrpUpdateBit
   VAR(uint16_least, AUTOMATIC)    Idx_SigTout;
   VAR(uint8, AUTOMATIC)           UpdateBitStatus;
#endif

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxSigGrpUpdateBit
#ifdef COM_RxSigGrpUpdateTimeout

   if((RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(RxPduId)))
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

    limit_ui          = (uint16_least)RxIPduConstPtr->FirstRxSigGrp_Index +
                        (uint16_least)RxIPduConstPtr->No_Of_SigGrp_Ref;
    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);
    RxSigGrpRamPtr    = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);

   for(Idx_SigGrp_ui = RxIPduConstPtr->FirstRxSigGrp_Index; Idx_SigGrp_ui < limit_ui; Idx_SigGrp_ui++)
   {
        ValidateSigGrp_u8  = COM_SET;

        if(
#ifdef COM_RxSigGrpUpdateBit
            (Com_Lok_ProcessSigGrpUpdateBit( (Com_SignalGroupIdType)Idx_SigGrp_ui, PduInfoPtr
   ,     UpdateBitStatus, &Idx_SigTout )) &&
#endif
            (RxSigGrpConstPtr->lastByte_u8 <= PduInfoPtr->SduLength)
           )
        {
#if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)

            if((Com_GetValue(RXSIGGRP,_INVACTION,RxSigGrpConstPtr->rxSignalGrpFields) != (uint8)COM_NONE)
#ifdef COM_RxFilters
               || (Com_GetValue(RXSIGGRP,_FILTEREVALREQ,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
#endif
               )
            {
                ValidateSigGrp_u8 = Com_Lok_ValidateRxSignalGroup((Com_SignalGroupIdType)Idx_SigGrp_ui
   ,     PduInfoPtr->SduDataPtr);
            }

            if(ValidateSigGrp_u8 != (uint8)COM_RESET)
#endif
            {

                Com_Lok_IpduBuffToSecondBuff((Com_SignalGroupIdType)Idx_SigGrp_ui, PduInfoPtr->SduDataPtr
   ,     ValidateSigGrp_u8);

#ifdef COM_SIGNALGROUPGATEWAY

                if(Com_GetValue(RXSIGGRP,_ISGWSIGGRP,RxSigGrpConstPtr->rxSignalGrpFields))
                {

                    Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);

                    COM_GET_IS_GWSIG_UPDATED( RxPduId ) = COM_TRUE;
                }
#endif

            }
        }
        else{

            ValidateSigGrp_u8 = COM_RESET;
        }

#ifdef COM_RxSignalGrpNotify

        Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,(ValidateSigGrp_u8 != (uint8)COM_RESET));
#endif

        RxSigGrpConstPtr++;
        RxSigGrpRamPtr++;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_RxSigGrpUpdateBit

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_ProcessSigGrpUpdateBit(
                                                    VAR(Com_SignalGroupIdType,AUTOMATIC)            SigGrpId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
   ,     VAR(uint8, AUTOMATIC)                           UpdateBitStatus
   ,     P2VAR(uint16_least, AUTOMATIC, COM_APPL_DATA)   Idx_SigToutPtr
                                                                   )
{
   Com_RxSigGrpConstPtrType                                    RxSigGrpConstPtr;
#ifdef COM_RxSigGrpUpdateTimeout
   Com_RxIpduConstPtrType                                      RxIPduConstPtr;
   P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST)   SigTimeOutConfigPtr;
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)                     SigTimeOutTicksPtr;
#endif
   VAR(boolean, AUTOMATIC)                                     IsUpdateBitSet;

    IsUpdateBitSet = COM_TRUE;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

   if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields))
   {
        VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)  UB_ByteNo_u8;
        VAR(boolean, AUTOMATIC)        updateBitValue_b;

        UB_ByteNo_u8     = (Type_SwcServiceCom_tLengthPdu)(RxSigGrpConstPtr->Update_Bit_Pos >> 3u);

        updateBitValue_b = Com_GetUpdateBitValue( PduInfoPtr->SduDataPtr
   ,     RxSigGrpConstPtr->Update_Bit_Pos
   ,     UB_ByteNo_u8 );

        if(((UB_ByteNo_u8 + 1u) <= PduInfoPtr->SduLength) && (updateBitValue_b == COM_FALSE))
        {

            IsUpdateBitSet = COM_FALSE;
        }
#ifdef COM_RxSigGrpUpdateTimeout
        else{

           UpdateBitStatus <<= 1u;
        }

        if(UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
        {
            RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef);

            SigTimeOutConfigPtr = (RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref) + (*Idx_SigToutPtr);

            if(SigTimeOutConfigPtr->SigId == (uint16)SigGrpId)
            {
                if(UpdateBitStatus == UPDATEBIT_SET)
                {

                    SigTimeOutTicksPtr  = (RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p) + (*Idx_SigToutPtr);

                    SchM_Enter_Com_RxSigGrpToTicks();

#if(COM_ENABLE_JITTERFLITER == STD_ON)

                    (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 2;
#else

                    (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 1;

#endif

                    SchM_Exit_Com_RxSigGrpToTicks();
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

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_IpduBuffToSecondBuff(VAR(Com_SignalGroupIdType,AUTOMATIC) SigGrpId
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)  BufferPtr
   ,     VAR(uint8,AUTOMATIC)  ValidateSigGrp_u8 )
{

   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;

   VAR(Com_MainFuncType, AUTOMATIC)    rxMainFuncId;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

    rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef))->MainFunctionRef;

   if(ValidateSigGrp_u8 != COM_REPLACE_TO_INIT)
   {
# ifdef COM_RX_SIGNALGROUP_ARRAY
        if(Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields))
        {
            Com_RxSigGrpArrayConstPtrType RxSigGrpArrayConstPtr;
            uint8                       * RxSigGrpArrayBufRamPtr;

            RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

            RxSigGrpArrayBufRamPtr =
                               &COM_GET_RXSIGGRP_ARRAY_BUFF( rxMainFuncId, RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

            SchM_Enter_Com_RxSigGrpArrayBuff();

            Com_ByteCopy((uint8 *)(RxSigGrpArrayBufRamPtr)
   ,     (const uint8 *)(BufferPtr + RxSigGrpArrayConstPtr->FirstByteNo)
   ,     ( RxSigGrpConstPtr->lastByte_u8 - RxSigGrpArrayConstPtr->FirstByteNo));

            SchM_Exit_Com_RxSigGrpArrayBuff();
        }
        else
# endif
        {
            Com_Lok_CopySecondaryBuffer(RxSigGrpConstPtr, BufferPtr);
        }
   }
   else{

        Com_Lok_SigGrpReplaceToInit(RxSigGrpConstPtr, rxMainFuncId);
   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopySecondaryBuffer(Com_RxSigGrpConstPtrType RxSigGrpConstPtr
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Buffer)
{

   Com_RxGrpSigConstPtrType            RxGrpSigConstPtr;
   VAR(uint16_least, AUTOMATIC)        index_ui;
   VAR(Com_MainFuncType, AUTOMATIC)    rxMainFuncId;
   VAR(uint8, AUTOMATIC)               SigType;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

    rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef))->MainFunctionRef;

    SchM_Enter_Com_RxGrpSigSecBuff();
   for(index_ui = (uint16_least)RxSigGrpConstPtr->No_Of_GrpSig; index_ui != (uint16_least)0; index_ui--)
   {

        SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

        if(SigType != (uint8)COM_UINT8_N)
        {
            VAR(uint8, AUTOMATIC) SigEndianess;

            SigEndianess = Com_GetValue(RXGRPSIG,_ENDIANESS,RxGrpSigConstPtr->rxGrpSigFields);

# ifdef COM_RXGRPSIG_FLOAT64SUPP
            if(SigType == COM_FLOAT64)
            {
                float64 RxNewVal_f64;

                RxNewVal_f64 = Com_UnPackFloatSignal( SigEndianess, RxGrpSigConstPtr->Bit_Pos, Buffer );

                COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(rxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) =
                                                                                                  RxNewVal_f64;
            }
            else
# endif

            {
                VAR(Com_SigMaxType,AUTOMATIC) RxGrpSig_NewVal;

                RxGrpSig_NewVal = Com_UnpackSignal( SigEndianess
   ,     RxGrpSigConstPtr->Bit_Pos
   ,     RxGrpSigConstPtr->BitSize, Buffer
   ,     ((SigType & (uint8)0x1)) != 0x0u);

                Com_UpdateRxGroupSignalSecondBuffer(RxGrpSigConstPtr, RxGrpSig_NewVal, rxMainFuncId);
            }
        }
        else{
            Com_ByteCopy( &COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index)
   ,     (Buffer +(RxGrpSigConstPtr->Bit_Pos >> 3u))
   ,     RxGrpSigConstPtr->BitSize );
        }
        RxGrpSigConstPtr++;
   }
    SchM_Exit_Com_RxGrpSigSecBuff();
}

#if defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters)

LOCAL_INLINE FUNC(uint8,COM_CODE) Com_Lok_ValidateRxSignalGroup(
                                                VAR(Com_SignalGroupIdType, AUTOMATIC)       SigGrpId
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)    BufferPtr
                                                               )
{

   Com_RxGrpSigConstPtrType            RxGrpSigConstPtr;

   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;

   Com_RxSigGrpRamPtrType              RxSigGrpRamPtr;
   VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal_GrpSig;
   VAR(uint16_least, AUTOMATIC)        Idx_GrpSig_ui;
   VAR(uint16_least, AUTOMATIC)        LastGrpSigId;
   VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)               ValidateSigGrp_u8;
   VAR(uint8, AUTOMATIC)               SigType;
#ifdef COM_RxFilters
   VAR(uint8, AUTOMATIC)               filterAlgo_u8;
#endif
   VAR(boolean, AUTOMATIC)             InvAction_b;

   ValidateSigGrp_u8 = COM_SET;
    RxNewVal_GrpSig   = 0;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);
    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);
    RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(SigGrpId);

    LastGrpSigId = RxSigGrpConstPtr->FirstGrpSig_Index + RxSigGrpConstPtr->No_Of_GrpSig;
   for( Idx_GrpSig_ui = RxSigGrpConstPtr->FirstGrpSig_Index;
         ((ValidateSigGrp_u8 == COM_SET) && (Idx_GrpSig_ui < LastGrpSigId)); Idx_GrpSig_ui++)
   {
        ConstByteValue_u8 = RxGrpSigConstPtr->rxGrpSigFields;
#ifdef COM_RxFilters
        filterAlgo_u8 = RxGrpSigConstPtr->Filter_Algo;
#endif
        InvAction_b   = Com_GetValue(RXGRPSIG,_INVACTION,ConstByteValue_u8);

        if((InvAction_b != COM_FALSE)
#ifdef COM_RxFilters
                || (filterAlgo_u8 != COM_NOTCONFIGURED)
#endif
                )
        {

            SigType = Com_GetValue(RXGRPSIG,_TYPE,ConstByteValue_u8);

            if(SigType == (uint8)COM_UINT8_N)
            {
                RxNewVal_GrpSig = (Com_SigMaxType)Com_UnpackOpaqueSignal(RxGrpSigConstPtr->Bit_Pos
   ,     RxGrpSigConstPtr->BitSize, BufferPtr);
            }

#ifdef COM_RXGRPSIG_FLOAT64SUPP
            else if(SigType == COM_FLOAT64)
            {

            }
#endif

            else{
                RxNewVal_GrpSig = Com_UnpackSignal(Com_GetValue(RXGRPSIG,_ENDIANESS,ConstByteValue_u8)
   ,     RxGrpSigConstPtr->Bit_Pos ,RxGrpSigConstPtr->BitSize, BufferPtr
   ,     ((SigType & 0x01u) != 0x0u));
            }

            ValidateSigGrp_u8 = Com_Lok_ValidateRxGroupSignal(Idx_GrpSig_ui, RxNewVal_GrpSig);
        }

        RxGrpSigConstPtr++;
   }

#if(defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)) && \
                                                    (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout))

   if(ValidateSigGrp_u8 != COM_RESET)
   {

        Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);
   }
#endif

    return(ValidateSigGrp_u8);
}

LOCAL_INLINE FUNC(uint8,COM_CODE) Com_Lok_ValidateRxGroupSignal(VAR(uint16_least, AUTOMATIC)        Idx_GrpSig_ui
   ,     VAR(Com_SigMaxType, AUTOMATIC)      RxNewVal_GrpSig)
{

   Com_RxGrpSigConstPtrType                    RxGrpSigConstPtr;

   Com_RxSigGrpConstPtrType                    RxSigGrpConstPtr;

   Com_RxSigGrpRamPtrType                      RxSigGrpRamPtr;
   VAR(Com_RxIntSignalGroupIdType, AUTOMATIC)  SignalGrpId;
   VAR(uint8, AUTOMATIC)                       ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)                       ConstByteValue_SignalGroup_u8;
   VAR(uint8, AUTOMATIC)                       SigType;
   VAR(uint8, AUTOMATIC)                       ValidateSigGrp_u8;
#ifdef COM_RxFilters
   VAR(uint8, AUTOMATIC)                       filterAlgo_u8;
   VAR(boolean, AUTOMATIC)                     filterVal_b;
#endif
   VAR(boolean, AUTOMATIC)                     InvAction_b;

    RxGrpSigConstPtr    = COM_GET_RXGRPSIG_CONSTDATA(Idx_GrpSig_ui);
    SignalGrpId         = RxGrpSigConstPtr->SigGrpRef;
    RxSigGrpConstPtr    = COM_GET_RXSIGGRP_CONSTDATA(SignalGrpId);
    RxSigGrpRamPtr      = &COM_GET_RXSIGGRPFLAG(SignalGrpId);

   ValidateSigGrp_u8 = COM_SET;

#ifdef COM_RxFilters
    filterAlgo_u8 = RxGrpSigConstPtr->Filter_Algo;
#endif
   ConstByteValue_u8 = RxGrpSigConstPtr->rxGrpSigFields;
    InvAction_b   = Com_GetValue(RXGRPSIG,_INVACTION,ConstByteValue_u8);
    SigType = Com_GetValue(RXGRPSIG,_TYPE,ConstByteValue_u8);

#if defined(COM_RxSigGrpInvalid)

   if((InvAction_b != COM_FALSE)
        && ((Com_SigMaxType)RxGrpSigConstPtr->DataInvalid_Val == RxNewVal_GrpSig)

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        && (SigType != COM_FLOAT64)
#endif

        )
   {
        ConstByteValue_SignalGroup_u8 = RxSigGrpConstPtr->rxSignalGrpFields;

        if(Com_GetValue(RXSIGGRP,_INVACTION,ConstByteValue_SignalGroup_u8) == (uint8)COM_REPLACE)
        {

            ValidateSigGrp_u8 = COM_REPLACE_TO_INIT;
        }
#ifdef COM_RxSigGrpInvalidNotify
        else{

            ValidateSigGrp_u8 = COM_RESET;

            if(RxSigGrpConstPtr->DataInvalid_Indication_Cbk != NULL_PTR)
            {
                RxSigGrpConstPtr->DataInvalid_Indication_Cbk();
            }
        }
#endif

   }
   else
#endif
   {
#ifdef COM_RxFilters

        if(filterAlgo_u8 != COM_NOTCONFIGURED)
        {

#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout))
            if(!((Com_GetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields) == COM_TRUE) &&
                 (COM_MASKED_NEW_DIFFERS_MASKED_OLD == filterAlgo_u8)))
#endif
            {

                filterVal_b = Com_Filter((uint32)RxNewVal_GrpSig,filterAlgo_u8,RxGrpSigConstPtr->Filter_Index,COM_TRUE);

                if(COM_TRUE != filterVal_b)
                {

                    ValidateSigGrp_u8 = COM_RESET;
                }
            }
        }
#endif
   }
    return ValidateSigGrp_u8;
}
#endif

#endif

