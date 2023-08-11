

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)

LOCAL_INLINE boolean Com_CompareVersionInfo(
                                    const Std_VersionInfoType * srcVersionInfo,
                                    const Std_VersionInfoType * destVersionInfo
                                           );
#endif

LOCAL_INLINE void Com_Lok_Init_Receive(void);

LOCAL_INLINE void Com_Lok_Init_RxSignal(PduIdType IpduId);

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void Com_Lok_Init_RxSignalGroup(PduIdType IpduId);
#endif

LOCAL_INLINE void Com_Lok_Init_Send(void);

LOCAL_INLINE void Com_Lok_Init_TxSignal(PduIdType IpduId);

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE void Com_Lok_Init_TxSignalGroup(PduIdType IpduId);

LOCAL_INLINE void Com_Lok_Init_GroupSignal(
                                    Com_TxIpduConstPtrType   TxIpduConstPtr,
                                    Com_TxSigGrpConstPtrType TxSigGrpConstPtr
                                          );
#endif

#ifdef COM_IPDU_WITHOUT_IPDUGROUP_EXISTS
LOCAL_INLINE void Com_Lok_Init_RxIpduWoGroupRef(PduIdType IpduId);
LOCAL_INLINE void Com_Lok_Init_TxIpduWoGroupRef(PduIdType IpduId);
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

Com_StatusType             Com_Uninit_Flag;

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
const Com_ConfigData_tst * Com_Lok_Config_pcst;
#endif

#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

void Com_Init(const Type_CfgSwcServiceCom_st * config)
{

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    Com_RxGwQueuePtrType        l_RxGwQueuePtr_struc;
#endif
#ifdef COM_F_ONEEVERYN
    uint16_least                index_u16;
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
{

    Std_VersionInfoType         versionInfo_s;

    Com_GetVersionInfo(&versionInfo_s);

# if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Ptr_Only((config == NULL_PTR), COMServiceId_Init))
#endif
    {

        if(Com_CompareVersionInfo(&versionInfo_s, config->versionInfo))
        {

            ComAppl_IncompatibleGenerator();

            return;
        }

        Com_Lok_Config_pcst = (const Com_ConfigData_tst * )config->Com_ConfigData;

    }
}
#else
    (void)config;
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    l_RxGwQueuePtr_struc                        = COM_GET_RXGWQUEUE_S;
    l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux  = COM_ZERO;
    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = COM_ZERO;
    l_RxGwQueuePtr_struc->RxGwQueuePtr          = &COM_GET_RXGWQUEUE_AUX(0);
#endif

    rba_BswSrv_MemSet8(Com_IpduGrpVector, COM_ZERO, COM_NUM_ARR_IPDUGRPVECT);

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
    rba_BswSrv_MemSet8(Com_IpduGrpVector_DM, COM_ZERO, COM_NUM_ARR_IPDUGRPVECT);
#endif

#if (COM_COMMON_TX_PERIOD == STD_ON)

    Com_ReducedPeriod_u16 = COM_ZERO;
#endif

#ifdef COM_F_ONEEVERYN

    for (index_u16 = COM_ZERO; index_u16 < COM_GET_NUM_SIG_GRPSIG_WITH_ONE_EVERY_N_FILTER; index_u16++)
    {
        COM_GET_ONEEVERYN( index_u16 ).Period     = COM_GET_ONEEVERYN_CONST( index_u16 ).Period;
        COM_GET_ONEEVERYN( index_u16 ).Offset     = COM_GET_ONEEVERYN_CONST( index_u16 ).Offset;
        COM_GET_ONEEVERYN( index_u16 ).Occurrence = COM_GET_ONEEVERYN_CONST( index_u16 ).Occurrence;
    }
#endif

    Com_Lok_Init_Receive();

    Com_Lok_Init_Send();

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

    rba_BswSrv_MemSet8(Com_TxIpduControlVector, COM_MAX_U8_VALUE, COM_NUM_ARR_TXIPDUCONTROLVECTOR);
#endif

#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

    rba_BswSrv_MemSet8(Com_RxIpduControlVector, COM_MAX_U8_VALUE, COM_NUM_ARR_RXIPDUCONTROLVECTOR);
#endif

    Com_Uninit_Flag = COM_INIT;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
LOCAL_INLINE boolean Com_CompareVersionInfo(const Std_VersionInfoType * srcVersionInfo,
                                            const Std_VersionInfoType * destVersionInfo)
{
    boolean     stEqual_b;
    stEqual_b = COM_TRUE;

    if ((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
        (srcVersionInfo->moduleID == destVersionInfo->moduleID) &&
        (srcVersionInfo->sw_major_version == destVersionInfo->sw_major_version) &&
        (srcVersionInfo->sw_minor_version == destVersionInfo->sw_minor_version) &&
        (srcVersionInfo->sw_patch_version == destVersionInfo->sw_patch_version)
    )
    {
        stEqual_b = COM_FALSE;
    }
    return stEqual_b;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

LOCAL_INLINE void Com_Lok_Init_Receive(void)
{
    Com_RxIpduRamPtrType        RxIpduRamPtr;
    Com_RxIpduConstPtrType      RxIpduConstPtr;
    uint16_least                idx_IpduId_u16;

    RxIpduRamPtr   = &COM_GET_RXPDURAM_S(0);

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(0);

    for(idx_IpduId_u16 = COM_ZERO; idx_IpduId_u16 < COM_GET_NUM_RX_IPDU; idx_IpduId_u16++)
    {

        RxIpduRamPtr->RxFlags      = COM_ZERO;
        RxIpduRamPtr->RxIPduLength = COM_ZERO;

#if defined(COM_RxIPduTimeout) && defined(COM_RX_DUAL_CYCLE_SUPPPORT)
        RxIpduRamPtr->RxDualCycTicks_u16 = COM_ZERO;
#endif

#ifdef COM_IPDU_WITHOUT_IPDUGROUP_EXISTS
        if (Com_GetValue(RXIPDU,_PDUWITHPDUGRP,RxIpduConstPtr->rxIPduFields ) == COM_FALSE)
        {

            Com_Lok_Init_RxIpduWoGroupRef((PduIdType)idx_IpduId_u16);
        }
        else
#endif
        {
            COM_GET_IPDUCOUNTER_S(idx_IpduId_u16)  = COM_ZERO;

# if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
            COM_GET_IPDUCOUNTER_DM(idx_IpduId_u16) = COM_ZERO;
# endif
        }

        Com_Lok_Init_RxSignal((PduIdType)idx_IpduId_u16);

#ifdef COM_RX_SIGNALGROUP

        Com_Lok_Init_RxSignalGroup((PduIdType)idx_IpduId_u16);
#endif

        RxIpduRamPtr++;
        RxIpduConstPtr++;
    }
}

LOCAL_INLINE void Com_Lok_Init_RxSignal(PduIdType IpduId)
{
    Com_RxIpduConstPtrType      RxIpduConstPtr;
    Com_RxSigConstPtrType       RxSigConstPtr;
    Com_RxSigRamPtrType         RxSigRamPtr;
    uint16_least                idx_Sig_u16;
    Com_SigMaxType              RxSigVal;
    Com_MainFuncType            rxMainFuncId;

#if defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP )
    uint8                       Type;
#endif

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);

    RxSigConstPtr   = COM_GET_RXSIG_CONSTDATA(RxIpduConstPtr->RxSigId_Index);
    RxSigRamPtr     = &COM_GET_RXSIGNALFLAG(RxIpduConstPtr->RxSigId_Index);

    rxMainFuncId    = RxIpduConstPtr->MainFunctionRef;

    for (idx_Sig_u16 = RxIpduConstPtr->No_Of_Sig_Ref; idx_Sig_u16 != COM_ZERO; idx_Sig_u16--)
    {

        RxSigRamPtr->rxSigRAMFields = COM_ZERO;

        RxSigVal    = RxSigConstPtr->Init_Val;

#if defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP )

        Type        = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif

#ifdef COM_RXSIG_FLOAT64SUPP

        if(Type == COM_FLOAT64)
        {

            COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId,RxSigConstPtr->SigBuff_Index) =
                                                     Com_getfloat64InitValue(RxSigVal);
        }
        else
#endif

        {
#ifdef COM_RXSIG_INT64

            if ( Type == COM_SINT64 )
            {
                RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
            }
            else
            {

            }
#endif

            Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigVal, rxMainFuncId);
        }

#if defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD)

        if(Com_GetValue(RXSIG,_FILTRALG,RxSigConstPtr->rxSignalFields) == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
        {

            COM_GET_F_OLDVALUE(RxSigConstPtr->Filter_Index) = (uint32)RxSigVal;
        }
#endif

        RxSigRamPtr++;
        RxSigConstPtr++;
    }
}

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE void Com_Lok_Init_RxSignalGroup(PduIdType IpduId)
{
    Com_RxIpduConstPtrType          RxIpduConstPtr;
    Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
    Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
    uint16_least                    idx_SigGrp_u16;
    Com_MainFuncType                rxMainFuncId;

    RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(IpduId);
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIpduConstPtr->FirstRxSigGrp_Index);
    RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIpduConstPtr->FirstRxSigGrp_Index);
    rxMainFuncId     = RxIpduConstPtr->MainFunctionRef;

    for (idx_SigGrp_u16 = RxIpduConstPtr->No_Of_SigGrp_Ref; idx_SigGrp_u16 != COM_ZERO; idx_SigGrp_u16--)
    {
        Com_Lok_SigGrpReplaceToInit( RxSigGrpConstPtr, rxMainFuncId );

        RxSigGrpRamPtr->rxSigGrpRAMFields = (uint8)COM_ZERO;

        RxSigGrpRamPtr++;
        RxSigGrpConstPtr++;
    }
}

#endif

LOCAL_INLINE void Com_Lok_Init_Send(void)
{
    Com_TxIpduRamPtrType        TxIpduRamPtr;
    Com_TxIpduConstPtrType      TxIpduConstPtr;
    uint16_least                idx_IpduId_u16;

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

    for (idx_IpduId_u16 = COM_ZERO; idx_IpduId_u16 < COM_GET_NUM_TX_IPDU; idx_IpduId_u16++)
    {

        TxIpduRamPtr ->Com_TxFlags      = COM_ZERO;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
        TxIpduRamPtr->Com_DynLength     = COM_ZERO;
#endif
        TxIpduRamPtr->CurrentTxModePtr  = TxIpduConstPtr->Com_TMConstPtr;

        rba_BswSrv_MemSet8(TxIpduConstPtr->BuffPtr, TxIpduConstPtr->PaddingByte, TxIpduConstPtr->Size);

#ifdef COM_IPDU_WITHOUT_IPDUGROUP_EXISTS

        if (Com_GetValue(TXIPDU,_PDUWITHPDUGRP,TxIpduConstPtr->txIPduFields) == COM_FALSE)
        {

            Com_Lok_Init_TxIpduWoGroupRef((PduIdType)idx_IpduId_u16);
        }
        else
#endif
        {
            COM_GET_IPDUCOUNTER_S(idx_IpduId_u16 + COM_GET_NUM_RX_IPDU) = COM_ZERO;

            Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_TRUE);

            Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,(uint8)COM_TXMODE_NONE);

#ifdef COM_MIXEDPHASESHIFT

            Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,COM_FALSE);
#endif

        }

#ifdef COM_TxIPduTimeOut
        TxIpduRamPtr->Com_TickTxTimeout      = COM_ZERO;
#endif
#ifdef COM_TxFilters
        TxIpduRamPtr->Com_TMSTrueCounter_u16 = COM_ZERO;
#endif
        TxIpduRamPtr->Com_n                  = COM_ZERO;

        TxIpduRamPtr->Com_MinDelayTick       = COM_ZERO;

        Com_Lok_Init_TxSignal((PduIdType)idx_IpduId_u16);

#ifdef COM_TX_SIGNALGROUP

        Com_Lok_Init_TxSignalGroup((PduIdType)idx_IpduId_u16);
#endif

#ifdef COM_TX_IPDUCOUNTER

        if (TxIpduConstPtr->TxIpduCntr_Index != COM_TXIPDU_CNTR_INV_IDX)
        {

            Com_Lok_TxIpduInitializeCounter( (PduIdType)idx_IpduId_u16 );
        }
        else
        {

        }
#endif

        TxIpduConstPtr++;
        TxIpduRamPtr++;

    }
}

LOCAL_INLINE void Com_Lok_Init_TxSignal(PduIdType IpduId)
{

    Com_TxIpduConstPtrType      TxIpduConstPtr;
    Com_TxSigConstPtrType       TxSigConstPtr;
    Com_SigMaxType              TxSigNewVal;
    uint16_least                idx_Sig_u16;
#if (defined(COM_TxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD)) || defined(COM_EffectiveSigTOC)
    uint16                      ConstByteValue_u16;
#endif
#ifdef COM_EffectiveSigTOC
    uint16                      TxSigTp_u16;
#endif
#ifdef COM_TxSigUpdateBit
    PduLengthType               byteNo_uo;
#endif
    uint8                       ConstByteValue_u8;
    uint8                       Type;

    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);

    for (idx_Sig_u16 = TxIpduConstPtr->No_Of_Sig_Ref; idx_Sig_u16 != COM_ZERO; idx_Sig_u16--)
    {
        ConstByteValue_u8   = TxSigConstPtr->General;

        Type                = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

        TxSigNewVal         = TxSigConstPtr->Init_Val;

#ifdef COM_TXSIG_INT64

        if ( Type == COM_SINT64 )
        {
            TxSigNewVal = (Com_SigMaxType)((sint64)((sint32)TxSigNewVal));
        }
        else
        {

        }
#endif

        Com_InitializePduBuffWithSignalInitValue( TxIpduConstPtr->BuffPtr,
                                                  TxSigNewVal,
                                                  TxSigConstPtr->Bit_Pos,
                                                  TxSigConstPtr->BitSize, Type,
                                                  Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8)  );

#if (defined(COM_TxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD)) || defined(COM_EffectiveSigTOC)
        ConstByteValue_u16 = TxSigConstPtr->txSignalFields;
#endif

#if (defined(COM_TxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD))
        if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u16) == (uint16)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
        {

            COM_GET_F_OLDVALUE(TxSigConstPtr->Filter_Index) = (uint32)TxSigNewVal;
        }
#endif

#ifdef COM_EffectiveSigTOC

        TxSigTp_u16 = Com_GetValue(TXSIG,_TP,ConstByteValue_u16);

        if (COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TxSigTp_u16))
        {
            COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxSigNewVal;
        }
#endif

#ifdef COM_TxSigUpdateBit

        if(Com_GetValue(GEN,_UPDBITCONF,ConstByteValue_u8))
        {

            byteNo_uo = (PduLengthType)(TxSigConstPtr->Update_Bit_Pos >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr, TxSigConstPtr->Update_Bit_Pos, byteNo_uo)
        }
#endif
        TxSigConstPtr++;
    }
}

#ifdef COM_TX_SIGNALGROUP

LOCAL_INLINE void Com_Lok_Init_TxSignalGroup(PduIdType IpduId)
{
    Com_TxIpduConstPtrType          TxIpduConstPtr;
    Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
    uint16_least                    idx_SigGrpId_u16;
    uint16_least                    firstSigGrpId;
    uint16_least                    maxSigGrpId;
#ifdef COM_TxSigGrpUpdateBit
    PduLengthType                   byteNo_uo;
#endif

    TxIpduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    firstSigGrpId    = TxIpduConstPtr->FirstTxSigGrp_Index;
    maxSigGrpId      = firstSigGrpId + TxIpduConstPtr->No_Of_SigGrp_Ref;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(firstSigGrpId);

    for (idx_SigGrpId_u16 = firstSigGrpId; idx_SigGrpId_u16 < maxSigGrpId; idx_SigGrpId_u16++)
    {

        Com_Lok_Init_GroupSignal(TxIpduConstPtr, TxSigGrpConstPtr);

#if defined(COM_EffectiveSigGrpTOC) || defined (COM_SIGNALGROUPGATEWAY)
        COM_GET_TXSIGGRPFLAG(idx_SigGrpId_u16).txSigGrpRAMFields = COM_ZERO;
#endif

#ifdef COM_TX_SIGNALGROUP_ARRAY

        if (Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields) != COM_TRUE)
#endif
        {

            Com_ShadowBuffToIpduBuff((Com_SignalGroupIdType)idx_SigGrpId_u16);
        }

#ifdef COM_TxSigGrpUpdateBit

        if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
        {

            byteNo_uo = (PduLengthType)(TxSigGrpConstPtr->Update_Bit_Pos >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr, TxSigGrpConstPtr->Update_Bit_Pos, byteNo_uo)
        }
#endif
        TxSigGrpConstPtr++;
    }
}

LOCAL_INLINE void Com_Lok_Init_GroupSignal(Com_TxIpduConstPtrType   TxIpduConstPtr,
                                           Com_TxSigGrpConstPtrType TxSigGrpConstPtr)
{

    Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
    Com_SigMaxType                  TxGrpSig_NewVal;
    uint16_least                    idx_GrpSigId_u16;
    uint16_least                    maxGrpSigId_u16;
    uint8                           ConstByteValue_u8;
    uint8                           Type;
    Com_MainFuncType                txMainFuncId;
#ifdef COM_TX_SIGNALGROUP_ARRAY
    boolean                         isSigGrpArrayAccess_b;
    isSigGrpArrayAccess_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    txMainFuncId        = TxIpduConstPtr->MainFunctionRef;

    idx_GrpSigId_u16    = TxSigGrpConstPtr->FirstGrpSig_Index;
    maxGrpSigId_u16     = idx_GrpSigId_u16 + TxSigGrpConstPtr->No_Of_GrpSig;

    TxGrpSigConstPtr    = COM_GET_TXGRPSIG_CONSTDATA(idx_GrpSigId_u16);

    for ( ; idx_GrpSigId_u16 < maxGrpSigId_u16; idx_GrpSigId_u16++)
    {

        TxGrpSig_NewVal     = TxGrpSigConstPtr->Init_Val;

        ConstByteValue_u8   = TxGrpSigConstPtr->txGrpSigFields;

        Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);

#ifdef COM_TXGRPSIG_INT64

        if ( Type == COM_SINT64 )
        {
            TxGrpSig_NewVal = (Com_SigMaxType)((sint64)((sint32)TxGrpSig_NewVal));
        }
        else
        {

        }
#endif

#ifdef COM_TX_SIGNALGROUP_ARRAY
        if ( isSigGrpArrayAccess_b )
        {
            Com_InitializePduBuffWithSignalInitValue( TxIpduConstPtr->BuffPtr,
                                                      TxGrpSig_NewVal,
                                                      TxGrpSigConstPtr->Bit_Pos,
                                                      TxGrpSigConstPtr->BitSize, Type,
                                                      Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8) );
        }
        else
#endif
#ifdef COM_TXGRPSIG_FLOAT64SUPP
        if(Type == COM_FLOAT64)
        {

            COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index) =
                                                                             Com_getfloat64InitValue(TxGrpSig_NewVal);
        }
        else
#endif
        if(Type == COM_UINT8_N)
        {
            Com_ByteCopyInit(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index),
                            (uint32)TxGrpSig_NewVal,(uint32)TxGrpSigConstPtr->BitSize);
        }
        else
        {
            Com_CopyTxGroupSignalData( (Com_SignalIdType)(idx_GrpSigId_u16), TxGrpSig_NewVal, txMainFuncId );
        }

#if (defined(COM_TxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD))
        if(TxGrpSigConstPtr->Filter_Algo == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
        {

            COM_GET_F_OLDVALUE(TxGrpSigConstPtr->Filter_Index) = (uint32)TxGrpSig_NewVal;
        }
#endif
#ifdef COM_EffectiveSigGrpTOC

        if(Com_GetValue(TXGRPSIG,_TP,ConstByteValue_u8))
        {
            COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxGrpSig_NewVal;
        }
#endif
        TxGrpSigConstPtr++;
    }
}
#endif

#ifdef COM_IPDU_WITHOUT_IPDUGROUP_EXISTS
LOCAL_INLINE void Com_Lok_Init_RxIpduWoGroupRef(PduIdType IpduId)
{
    Com_RxIpduRamPtrType        RxIpduRamPtr;

    RxIpduRamPtr = &COM_GET_RXPDURAM_S(IpduId);

    COM_GET_IPDUCOUNTER_S(IpduId) = COM_ONE;

    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIpduRamPtr->RxFlags,COM_START);

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)

    if (Com_Lok_EnableRxDeadlineMonitoring((Com_IpduIdType)IpduId))
    {

        COM_GET_IPDUCOUNTER_DM(IpduId) = COM_ONE;

        Com_SetRamValue(RXIPDU,_DMSTATUS,RxIpduRamPtr->RxFlags,COM_START);
    }
    else
    {
        COM_GET_IPDUCOUNTER_DM(IpduId) = COM_ZERO;
    }

#endif

#ifdef COM_RX_IPDUCOUNTER

    Com_SetRamValue(RXIPDU,_IS_FIRST_RECEPTION,RxIpduRamPtr->RxFlags,COM_TRUE);
#endif
}
#endif

#ifdef COM_IPDU_WITHOUT_IPDUGROUP_EXISTS
LOCAL_INLINE void Com_Lok_Init_TxIpduWoGroupRef(PduIdType IpduId)
{
    Com_TxIpduRamPtrType        TxIpduRamPtr;
    Com_TxIpduConstPtrType      TxIpduConstPtr;
    uint8                       LatestTransMode_u8;
    boolean                     DefaultTMSStatus;

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    DefaultTMSStatus = Com_GetValue(TXIPDU,_DEFAULTTMSSTATUS,TxIpduConstPtr->txIPduFields);

    COM_GET_IPDUCOUNTER_S(IpduId + COM_GET_NUM_RX_IPDU) = COM_ONE;

    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags,COM_START);

    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,DefaultTMSStatus);

    Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIpduConstPtr,DefaultTMSStatus);

    LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;
    Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,LatestTransMode_u8);

    if (COM_TX_MODE_IS_CYCLIC(LatestTransMode_u8))
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEOFFSET(IpduId, TxIpduRamPtr->CurrentTxModePtr);
#ifdef COM_MIXEDPHASESHIFT

        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif
    }
}
#endif

