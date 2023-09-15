

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP

#ifdef COM_RxSigGrpUpdateBit
LOCAL_INLINE boolean Com_Lok_ProcessSigGrpUpdateBit(
                                            Com_SignalGroupIdType       SigGrpId
   ,                                           const PduInfoType *         PduInfoPtr
                                                   );
#endif

LOCAL_INLINE void Com_Lok_IpduBuffToSecondBuff(
                                            Com_SignalGroupIdType       SigGrpId
   ,                                           const uint8 *               BufferPtr
   ,                                           uint8                       ValidateSigGrp_u8
                                              );

#if defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters)
LOCAL_INLINE uint8 Com_Lok_ValidateRxSignalGroup(Com_SignalGroupIdType SigGrpId, const uint8 * BufferPtr);

LOCAL_INLINE uint8 Com_Lok_ValidateRxGroupSignal(uint16_least GrpSigId, Com_SigMaxType RxNewVal_GrpSig);
#endif

LOCAL_INLINE void Com_Lok_CopySecondaryBuffer(Com_RxSigGrpConstPtrType RxSigGrpConstPtr, const uint8 * Buffer);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_Lok_ProcessSignalGroup(PduIdType RxPduId, const PduInfoType * PduInfoPtr)
{
   Com_RxIpduConstPtrType          RxIpduConstPtr;
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
#if defined(COM_SIGNALGROUPGATEWAY) || defined(COM_RxSignalGrpNotify)
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
   uint16_least                    idx_SigGrpId_u16;
   uint16_least                    maxSigGrpId_u16;
   uint8                           ValidateSigGrp_u8;
#ifdef COM_RxSigGrpUpdateTimeout
   uint16_least                    Idx_SigTout;
   uint8                           IpduUpdateBitStatus;
   uint8                           SigGrpUpdateBitStatus;
#endif

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxSigGrpUpdateTimeout

   if((RxIpduConstPtr->SignalGrpTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(RxPduId)))
   {

        IpduUpdateBitStatus = COM_UPDATEBIT_APPLICABLE;
   }
   else{

        IpduUpdateBitStatus = COM_UPDATEBIT_NOT_APPLICABLE;
   }

    Idx_SigTout = COM_ZERO;
#endif

   idx_SigGrpId_u16  = RxIpduConstPtr->FirstRxSigGrp_Index;
    maxSigGrpId_u16   = idx_SigGrpId_u16 + RxIpduConstPtr->No_Of_SigGrp_Ref;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(idx_SigGrpId_u16);

#if defined(COM_SIGNALGROUPGATEWAY) || defined(COM_RxSignalGrpNotify)
    RxSigGrpRamPtr    = &COM_GET_RXSIGGRPFLAG(idx_SigGrpId_u16);
#endif

   for( ; idx_SigGrpId_u16 < maxSigGrpId_u16; idx_SigGrpId_u16++)
   {
        ValidateSigGrp_u8  = COM_SET;

#ifdef COM_RxSigGrpUpdateTimeout
        SigGrpUpdateBitStatus = IpduUpdateBitStatus;
#endif

        if(
#ifdef COM_RxSigGrpUpdateBit
             (Com_Lok_ProcessSigGrpUpdateBit( (Com_SignalGroupIdType)idx_SigGrpId_u16, PduInfoPtr)) &&
#endif
             (RxSigGrpConstPtr->lastByte_u8 <= PduInfoPtr->SduLength)
           )
        {
#if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters) || defined(COM_SIGNALGROUPGATEWAY)
            uint8   constByteValue_u8;
# ifdef COM_SIGNALGROUPGATEWAY
            boolean isGwSigGrp_b;
# endif
# if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)
            boolean isValidationReq_b;
# endif
            constByteValue_u8 = RxSigGrpConstPtr->rxSignalGrpFields;

# ifdef COM_SIGNALGROUPGATEWAY
            isGwSigGrp_b      = Com_GetValue(RXSIGGRP,_ISGWSIGGRP,constByteValue_u8);
# endif

# if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)
            isValidationReq_b =
#  ifdef COM_SIGNALGROUPGATEWAY

                (isGwSigGrp_b == COM_FALSE) &&
#  endif

                ((Com_GetValue(RXSIGGRP,_INVACTION,constByteValue_u8) != COM_NONE)
#  ifdef COM_RxFilters
                 || (Com_GetValue(RXSIGGRP,_FILTEREVALREQ,constByteValue_u8) != COM_FALSE)
#  endif
                );

            if(isValidationReq_b)
            {
                ValidateSigGrp_u8 = Com_Lok_ValidateRxSignalGroup((Com_SignalGroupIdType)idx_SigGrpId_u16
   ,                                                                              PduInfoPtr->SduDataPtr);
            }

            if(ValidateSigGrp_u8 != (uint8)COM_RESET)
# endif
#endif
            {

                Com_Lok_IpduBuffToSecondBuff((Com_SignalGroupIdType)idx_SigGrpId_u16, PduInfoPtr->SduDataPtr
   ,                                                                                      ValidateSigGrp_u8);

#ifdef COM_SIGNALGROUPGATEWAY

                if(isGwSigGrp_b)
                {

                    Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);

                    COM_GET_IS_GWSIG_UPDATED( RxPduId ) = COM_TRUE;
                }
#endif

#ifdef COM_RxSigGrpUpdateTimeout
                SigGrpUpdateBitStatus <<= COM_ONE;
#endif
            }
        }
        else{

            ValidateSigGrp_u8 = COM_RESET;
        }

#ifdef COM_RxSigGrpUpdateTimeout

        if(SigGrpUpdateBitStatus != COM_UPDATEBIT_NOT_APPLICABLE)
        {
            Com_Lok_LoadSigGrpTimeoutValue((Com_SignalGroupIdType)idx_SigGrpId_u16, SigGrpUpdateBitStatus, &Idx_SigTout);
        }
#endif

#ifdef COM_RxSignalGrpNotify

        Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,(ValidateSigGrp_u8 != (uint8)COM_RESET));
#endif

        RxSigGrpConstPtr++;
#if defined(COM_SIGNALGROUPGATEWAY) || defined(COM_RxSignalGrpNotify)
        RxSigGrpRamPtr++;
#endif

   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_RxSigGrpUpdateBit

LOCAL_INLINE boolean Com_Lok_ProcessSigGrpUpdateBit(
                                                 Com_SignalGroupIdType       SigGrpId
   ,                                                const PduInfoType *         PduInfoPtr
                                                   )
{
   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;
   boolean                             isUpdateBitSet_b;

   isUpdateBitSet_b = COM_TRUE;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

   if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields))
   {
        PduLengthType   UB_ByteNo_u8;

        UB_ByteNo_u8     = (PduLengthType)(RxSigGrpConstPtr->Update_Bit_Pos >> 3u);

        if((UB_ByteNo_u8 + COM_ONE) <= PduInfoPtr->SduLength)
        {

            isUpdateBitSet_b  = Com_GetUpdateBitValue( PduInfoPtr->SduDataPtr
   ,                                                      RxSigGrpConstPtr->Update_Bit_Pos
   ,                                                      UB_ByteNo_u8 );
        }
        else{

        }
   }

    return isUpdateBitSet_b;
}

#endif

LOCAL_INLINE void Com_Lok_IpduBuffToSecondBuff(
                                            Com_SignalGroupIdType  SigGrpId
   ,                                           const uint8 *          BufferPtr
   ,                                           uint8                  ValidateSigGrp_u8
                                              )
{
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_MainFuncType                rxMainFuncId;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

    rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef))->MainFunctionRef;

# if !(defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters))
    (void)ValidateSigGrp_u8;
# endif

# if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)
   if(ValidateSigGrp_u8 != COM_REPLACE_TO_INIT)
# endif
   {

# ifdef COM_RX_SIGNALGROUP_ARRAY
        if(Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields))
        {
            Com_RxSigGrpArrayConstPtrType RxSigGrpArrayConstPtr;
            uint8                       * RxSigGrpArrayBufRamPtr;

            RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

            RxSigGrpArrayBufRamPtr =
                               &COM_GET_RXSIGGRP_ARRAY_BUFF( rxMainFuncId, RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

            Com_Get_SchM_Enter_Com_RxSigGrpArrayBuff

            Com_ByteCopy((uint8 *)(RxSigGrpArrayBufRamPtr)
   ,                  (const uint8 *)(BufferPtr + RxSigGrpArrayConstPtr->FirstByteNo)
   ,                                 (RxSigGrpConstPtr->lastByte_u8 - RxSigGrpArrayConstPtr->FirstByteNo));

            Com_Get_SchM_Exit_Com_RxSigGrpArrayBuff
        }
        else
# endif
        {
            Com_Lok_CopySecondaryBuffer(RxSigGrpConstPtr, BufferPtr);
        }

   }
# if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)
   else{

        Com_Lok_SigGrpReplaceToInit(RxSigGrpConstPtr, rxMainFuncId);
   }
# endif
}

LOCAL_INLINE void Com_Lok_CopySecondaryBuffer(Com_RxSigGrpConstPtrType RxSigGrpConstPtr, const uint8 * Buffer)
{

   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   uint16_least                    idx_GrpSig_u16;
   Com_MainFuncType                rxMainFuncId;
   uint8                           SigType;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

    rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef))->MainFunctionRef;

   Com_Get_SchM_Enter_Com_RxGrpSigSecBuff

   for(idx_GrpSig_u16 = RxSigGrpConstPtr->No_Of_GrpSig; idx_GrpSig_u16 > COM_ZERO; idx_GrpSig_u16--)
   {
        SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

        if(SigType != (uint8)COM_UINT8_N)
        {
            uint8   SigEndianess;

            SigEndianess = Com_GetValue(RXGRPSIG,_ENDIANESS,RxGrpSigConstPtr->rxGrpSigFields);

# ifdef COM_RXGRPSIG_FLOAT64SUPP
            if(SigType == COM_FLOAT64)
            {
                float64 RxNewVal_f64;

                RxNewVal_f64 = Com_UnPackFloatSignal( SigEndianess, RxGrpSigConstPtr->Bit_Pos, Buffer );

                COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(rxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index) = RxNewVal_f64;
            }
            else
# endif

            {
                Com_SigMaxType  RxGrpSig_NewVal;

                RxGrpSig_NewVal = Com_UnpackSignal( SigEndianess
   ,                                                   RxGrpSigConstPtr->Bit_Pos
   ,                                                   RxGrpSigConstPtr->BitSize, Buffer
   ,                                                   ((SigType & COM_ONE)) != COM_ZERO);

                Com_UpdateRxGroupSignalSecondBuffer(RxGrpSigConstPtr, RxGrpSig_NewVal, rxMainFuncId);
            }
        }
        else{
            Com_ByteCopy( &COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId,RxGrpSigConstPtr->RxGrpSigBuff_Index)
   ,                         (Buffer +(RxGrpSigConstPtr->Bit_Pos >> 3u))
   ,                          RxGrpSigConstPtr->BitSize );
        }
        RxGrpSigConstPtr++;
   }
   Com_Get_SchM_Exit_Com_RxGrpSigSecBuff
}

#if defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters)

LOCAL_INLINE uint8 Com_Lok_ValidateRxSignalGroup(Com_SignalGroupIdType SigGrpId, const uint8 * BufferPtr)
{
   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_SigMaxType                  RxNewVal_GrpSig;
   uint16_least                    idx_GrpSigId_ui;
   uint16_least                    maxGrpSigId_u16;
   uint8                           ConstByteValue_u8;
   uint8                           ValidateSigGrp_u8;
   uint8                           SigType;
#ifdef COM_RxFilters
   uint8                           filterAlgo_u8;
#endif

   ValidateSigGrp_u8 = COM_SET;
    RxNewVal_GrpSig   = COM_ZERO;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(SigGrpId);

   idx_GrpSigId_ui   = RxSigGrpConstPtr->FirstGrpSig_Index;
    maxGrpSigId_u16   = idx_GrpSigId_ui + RxSigGrpConstPtr->No_Of_GrpSig;

    RxGrpSigConstPtr  = COM_GET_RXGRPSIG_CONSTDATA(idx_GrpSigId_ui);

   for( ; ((ValidateSigGrp_u8 == COM_SET) && (idx_GrpSigId_ui < maxGrpSigId_u16)); idx_GrpSigId_ui++)
   {
        ConstByteValue_u8 = RxGrpSigConstPtr->rxGrpSigFields;
#ifdef COM_RxFilters
        filterAlgo_u8 = RxGrpSigConstPtr->Filter_Algo;
#endif

        if((Com_GetValue(RXGRPSIG,_INVACTION,ConstByteValue_u8) != COM_FALSE)
#ifdef COM_RxFilters
           || (filterAlgo_u8 != COM_NOTCONFIGURED)
#endif
          )
        {
            SigType = Com_GetValue(RXGRPSIG,_TYPE,ConstByteValue_u8);

            if(SigType == COM_UINT8_N)
            {
                RxNewVal_GrpSig = Com_UnpackOpaqueSignal(RxGrpSigConstPtr->Bit_Pos,RxGrpSigConstPtr->BitSize,BufferPtr);
            }

#ifdef COM_RXGRPSIG_FLOAT64SUPP
            else if(SigType == COM_FLOAT64)
            {

            }
#endif

            else{
                RxNewVal_GrpSig = Com_UnpackSignal(Com_GetValue(RXGRPSIG,_ENDIANESS,ConstByteValue_u8)
   ,                                                   RxGrpSigConstPtr->Bit_Pos ,RxGrpSigConstPtr->BitSize, BufferPtr
   ,                                                   ((SigType & COM_ONE) != COM_ZERO));
            }

            ValidateSigGrp_u8 = Com_Lok_ValidateRxGroupSignal(idx_GrpSigId_ui, RxNewVal_GrpSig);
        }

        RxGrpSigConstPtr++;
   }

#if(defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)) && \
                                                    (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout))

   if(ValidateSigGrp_u8 != COM_RESET)
   {

        Com_SetRamValue(RXSIGGRP,_DMFILTERING,COM_GET_RXSIGGRPFLAG(SigGrpId).rxSigGrpRAMFields,COM_FALSE);
   }
#endif

    return ValidateSigGrp_u8;
}

LOCAL_INLINE uint8 Com_Lok_ValidateRxGroupSignal(uint16_least GrpSigId, Com_SigMaxType RxNewVal_GrpSig)
{
   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
#ifdef COM_RxSigGrpInvalid
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
#endif
#if defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD) && \
                             (defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout))
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
   Com_RxIntSignalGroupIdType      SignalGrpId;
#ifdef COM_RxSigGrpInvalid
   uint8                           ConstByteValue_u8;
#ifdef COM_RXGRPSIG_FLOAT64SUPP
   uint8                           SigType;
#endif
#endif
   uint8                           ValidateSigGrp_u8;

   ValidateSigGrp_u8 = COM_SET;

    RxGrpSigConstPtr  = COM_GET_RXGRPSIG_CONSTDATA(GrpSigId);
    SignalGrpId       = RxGrpSigConstPtr->SigGrpRef;

#if !(defined(COM_RxSigGrpInvalid) || (defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD) && \
                                      (defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout))))
    (void)SignalGrpId;
#endif

#if defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD) && \
   (defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout))
    RxSigGrpRamPtr    = &COM_GET_RXSIGGRPFLAG(SignalGrpId);
#endif

#ifdef COM_RxSigGrpInvalid

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(SignalGrpId);

   ConstByteValue_u8 = RxGrpSigConstPtr->rxGrpSigFields;

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    SigType = Com_GetValue(RXGRPSIG,_TYPE,ConstByteValue_u8);
#endif

   if((Com_GetValue(RXGRPSIG,_INVACTION,ConstByteValue_u8) != COM_FALSE)
        && (RxGrpSigConstPtr->DataInvalid_Val == RxNewVal_GrpSig)

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        && (SigType != COM_FLOAT64)
#endif

        )
   {
        if(Com_GetValue(RXSIGGRP,_INVACTION,RxSigGrpConstPtr->rxSignalGrpFields) == (uint8)COM_REPLACE)
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
        uint8   filterAlgo_u8;
        boolean filterVal_b;

        filterAlgo_u8 = RxGrpSigConstPtr->Filter_Algo;

        if(filterAlgo_u8 != COM_NOTCONFIGURED)
        {

#if defined(COM_F_MASKEDNEWDIFFERSOLD) && (defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout))
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

