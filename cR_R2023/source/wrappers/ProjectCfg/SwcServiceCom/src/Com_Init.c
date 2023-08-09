

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_StatusType,COM_VAR)         Com_Uninit_Flag;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST) Com_Lok_Config_pcst;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_CompareVersionInfo(
                                               P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) srcVersionInfo,
                                               P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) destVersionInfo
                                                            );
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_Receive(void);

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_Send(void);

#ifdef COM_IPDU_WITHOUT_IPDUGROUPREF
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_IpduWoGroupRef(VAR(PduIdType, AUTOMATIC) IpduId);
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_TxSignal(VAR(PduIdType, AUTOMATIC) IpduId);

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_TxSignalGroup(VAR(PduIdType, AUTOMATIC) IpduId);

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_GroupSignal(Com_TxIpduConstPtrType TxIPduConstPtr,
                                                              Com_TxSigGrpConstPtrType TxSigGrpConstPtr);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_Init(P2CONST(Type_CfgSwcServiceCom_st, AUTOMATIC, COM_APPL_DATA) config)
{

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    Com_RxGwQueuePtrType          l_RxGwQueuePtr_struc;
#endif
#ifdef COM_F_ONEEVERYN
    VAR(uint16_least, AUTOMATIC)  Idx_ui;
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
{

    VAR(Std_VersionInfoType, AUTOMATIC) versionInfo_s;

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

        Com_Lok_Config_pcst = (P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST))config->Com_ConfigData;
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

    rba_BswSrv_MemSet8(&Com_IpduGrpVector[COM_ZERO]   ,(uint32)COM_ZERO,(uint32)COM_NUM_ARR_IPDUGRPVECT);
    rba_BswSrv_MemSet8(&Com_IpduGrpVector_DM[COM_ZERO],(uint32)COM_ZERO,(uint32)COM_NUM_ARR_IPDUGRPVECT);

#if (COM_COMMON_TX_PERIOD == STD_ON)

    Com_ReducedPeriod_u16 = COM_ZERO;
#endif

#ifdef COM_F_ONEEVERYN

    for (Idx_ui = COM_ZERO; Idx_ui < COM_GET_NUM_SIG_GRPSIG_WITH_ONE_EVERY_N_FILTER; Idx_ui++)
    {
        COM_GET_ONEEVERYN( Idx_ui ).Period     = COM_GET_ONEEVERYN_CONST( Idx_ui ).Period;
        COM_GET_ONEEVERYN( Idx_ui ).Offset     = COM_GET_ONEEVERYN_CONST( Idx_ui ).Offset;
        COM_GET_ONEEVERYN( Idx_ui ).Occurrence = COM_GET_ONEEVERYN_CONST( Idx_ui ).Occurrence;
    }
#endif

    Com_Lok_Init_Receive();

    Com_Lok_Init_Send();

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

    rba_BswSrv_MemSet8(&Com_TxIpduControlVector[COM_ZERO],(uint32)0xFFu,(uint32)COM_NUM_ARR_TXIPDUCONTROLVECTOR);
#endif
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

    rba_BswSrv_MemSet8(&Com_RxIpduControlVector[COM_ZERO],(uint32)0xFFu,(uint32)COM_NUM_ARR_RXIPDUCONTROLVECTOR);
#endif

    Com_Uninit_Flag = COM_INIT;

}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_CompareVersionInfo(
                  P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) srcVersionInfo,
                  P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) destVersionInfo
                                                           )
{
    VAR(boolean, AUTOMATIC)   stEqual_b;
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

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_Receive(void)
{

    Com_RxIpduRamPtrType          RxIPduRamPtr;
    Com_RxIpduConstPtrType        RxIPduConstPtr;
    Com_RxSigConstPtrType         RxSigConstPtr;
    VAR(uint16_least, AUTOMATIC)  Idx_ui;
    VAR(uint16_least, AUTOMATIC)  Idx_ByteNSig_ui;

#ifdef COM_RX_SIGNALGROUP
    Com_RxSigGrpConstPtrType      RxSigGrpConstPtr;
    VAR(uint16_least, AUTOMATIC)  Idx_SigGrp_ui;
#endif

    Com_RxSigRamPtrType                 RxSigRamPtr;
    VAR(Com_SigMaxType,AUTOMATIC)       RxSigVal;
    VAR(Com_MainFuncType,AUTOMATIC)     rxMainFuncId;
#ifdef COM_RxFilters
# ifdef COM_F_MASKEDNEWDIFFERSOLD
    VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
# endif
#endif
#if defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP )
    VAR(uint8, AUTOMATIC)               Type;
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    Com_RxGwQueuePtrType          l_RxGwQueuePtr_struc;

    l_RxGwQueuePtr_struc                        = COM_GET_RXGWQUEUE_S;
    l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux  = COM_ZERO;
    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = COM_ZERO;
    l_RxGwQueuePtr_struc->RxGwQueuePtr          = &COM_GET_RXGWQUEUE_AUX(0);
#endif

    RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(0);

    for(Idx_ui = COM_ZERO; Idx_ui < COM_GET_NUM_RX_IPDU; Idx_ui++)
    {

        COM_GET_IPDUCOUNTER_S(Idx_ui)  = (uint8)COM_ZERO;
        COM_GET_IPDUCOUNTER_DM(Idx_ui) = (uint8)COM_ZERO;

        RxIPduRamPtr ->RxFlags      = (uint8)COM_ZERO;
        RxIPduRamPtr ->RxIPduLength = COM_ZERO;

        Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIPduRamPtr->RxFlags,COM_FALSE);

        RxSigRamPtr     = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
        RxSigConstPtr   = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

        rxMainFuncId    = RxIPduConstPtr->MainFunctionRef;

        for(Idx_ByteNSig_ui  = (uint16_least)(RxIPduConstPtr->No_Of_Sig_Ref);Idx_ByteNSig_ui != (uint16_least)COM_ZERO; Idx_ByteNSig_ui-- )
        {

            RxSigRamPtr->rxSigRAMFields = (uint8)COM_ZERO;

            RxSigVal    = (Com_SigMaxType)RxSigConstPtr->Init_Val;

#if defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP )

            Type        = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif

#ifdef COM_RXSIG_INT64

            if ( Type == COM_SINT64 )
            {
                RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
            }
            else
            {

            }
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
                Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigVal, rxMainFuncId);
            }

#ifdef COM_RxFilters
# ifdef COM_F_MASKEDNEWDIFFERSOLD

            ConstByteValue_u8 = RxSigConstPtr->rxSignalFields;

            if(Com_GetValue(RXSIG,_FILTRALG,ConstByteValue_u8) == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
            {

                COM_GET_F_OLDVALUE(RxSigConstPtr->Filter_Index) = (uint32)RxSigVal;
            }
# endif
#endif
            RxSigRamPtr++;
            RxSigConstPtr++;
        }

#ifdef COM_RX_SIGNALGROUP
        {

            Com_RxSigGrpRamPtrType RxSigGrpRamPtr;
            RxSigGrpRamPtr = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);

            RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( RxIPduConstPtr->FirstRxSigGrp_Index );

            for (Idx_SigGrp_ui  = (uint16_least)RxIPduConstPtr->No_Of_SigGrp_Ref;Idx_SigGrp_ui != (uint16_least)COM_ZERO;Idx_SigGrp_ui-- )
            {
                Com_Lok_SigGrpReplaceToInit( RxSigGrpConstPtr, rxMainFuncId );

                RxSigGrpRamPtr->rxSigGrpRAMFields = (uint8)COM_ZERO;

                RxSigGrpRamPtr++;
                RxSigGrpConstPtr++;
            }
        }
#endif

        RxIPduRamPtr++;
        RxIPduConstPtr++;
    }

}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_Send(void)
{

    Com_TxIpduRamPtrType           TxIpduRamPtr;
    Com_TxIpduConstPtrType         TxIPduConstPtr;
    VAR(uint16, AUTOMATIC)         Idx_ui;

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

    for(Idx_ui = COM_ZERO; Idx_ui < COM_GET_NUM_TX_IPDU; Idx_ui++)
    {

        TxIpduRamPtr ->Com_TxFlags      = (uint16)COM_ZERO;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
        TxIpduRamPtr->Com_DynLength     = COM_ZERO;
#endif
        TxIpduRamPtr->CurrentTxModePtr  = TxIPduConstPtr->Com_TMConstPtr;

        rba_BswSrv_MemSet8((TxIPduConstPtr->BuffPtr),(uint32)TxIPduConstPtr->PaddingByte, (uint32)TxIPduConstPtr->Size);

        if(Com_GetValue( TXIPDU,_PDUWITHPDUGRP,TxIPduConstPtr->txIPduFields ) != COM_FALSE)
        {
            COM_GET_IPDUCOUNTER_S(Idx_ui + COM_GET_NUM_RX_IPDU) = COM_ZERO;

            Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_TRUE);

            Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,(uint8)COM_TXMODE_NONE);

            #ifdef COM_MIXEDPHASESHIFT

            Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,COM_FALSE);
            #endif

        }
#ifdef COM_IPDU_WITHOUT_IPDUGROUPREF
        else
        {

            Com_Lok_Init_IpduWoGroupRef(Idx_ui);
        }
#endif

#ifdef COM_TxIPduTimeOut
        TxIpduRamPtr->Com_TickTxTimeout     = COM_ZERO;
#endif
#ifdef COM_TxFilters
        TxIpduRamPtr->Com_TMSTrueCounter_u8 = COM_ZERO;
#endif
        TxIpduRamPtr->Com_n                 = COM_ZERO;

        TxIpduRamPtr->Com_MinDelayTick      = COM_ZERO;

        Com_Lok_Init_TxSignal(Idx_ui);

#ifdef COM_TX_SIGNALGROUP

        Com_Lok_Init_TxSignalGroup(Idx_ui);
#endif

        TxIPduConstPtr++;
        TxIpduRamPtr++;

    }
}

#ifdef COM_IPDU_WITHOUT_IPDUGROUPREF

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_IpduWoGroupRef(VAR(PduIdType, AUTOMATIC) IpduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    Com_TxIpduConstPtrType      TxIPduConstPtr;
    VAR(boolean, AUTOMATIC)     DefaultTMSStatus;

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    DefaultTMSStatus = Com_GetValue(TXIPDU,_DEFAULTTMSSTATUS,TxIPduConstPtr->txIPduFields);

    COM_GET_IPDUCOUNTER_S(IpduId + COM_GET_NUM_RX_IPDU) = COM_ONE;

    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags,COM_START);

    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,DefaultTMSStatus);

    Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),DefaultTMSStatus);

    Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);

    if(COM_RESET != (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) & COM_TXMODE_MIXED))
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEOFFSET(IpduId, TxIpduRamPtr->CurrentTxModePtr);
#ifdef COM_MIXEDPHASESHIFT

        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif
    }
}
#endif

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_TxSignal(VAR(PduIdType, AUTOMATIC) IpduId)
{

    Com_TxIpduConstPtrType         TxIPduConstPtr;
    Com_TxSigConstPtrType          TxSigConstPtr;
    VAR(Com_SigMaxType, AUTOMATIC) TxSigNewVal;
#if (defined(COM_TxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD)) || defined(COM_EffectiveSigTOC)

    VAR(uint16, AUTOMATIC)         ConstByteValue_u16;
#endif
#ifdef COM_EffectiveSigTOC

    VAR(uint16, AUTOMATIC)         TxSigTp_u16;
#endif

    VAR(uint16_least, AUTOMATIC)   Idx_ByteNSig_ui;

#ifdef COM_TxSigUpdateBit
    VAR(PduLengthType, AUTOMATIC)  ByteNo_u8;
#endif
    VAR(uint8, AUTOMATIC)          ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)          Type;

    TxIPduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

    for(Idx_ByteNSig_ui = TxIPduConstPtr->No_Of_Sig_Ref; Idx_ByteNSig_ui != COM_ZERO; Idx_ByteNSig_ui--)
    {

        ConstByteValue_u8   = TxSigConstPtr->General;

        Type                = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

        TxSigNewVal         = (Com_SigMaxType)TxSigConstPtr->Init_Val;

#ifdef COM_TXSIG_INT64

        if ( Type == COM_SINT64 )
        {
            TxSigNewVal = (Com_SigMaxType)((sint64)((sint32)TxSigNewVal));
        }
        else
        {

        }
#endif

        Com_InitializePduBuffWithSignalInitValue( TxIPduConstPtr->BuffPtr,
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

        ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;

        if((Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE) &&
                (Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General)))
        {

            ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Update_Bit_Pos>>3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigConstPtr->Update_Bit_Pos, ByteNo_u8)
        }
#endif
        TxSigConstPtr++;
    }
}

#ifdef COM_TX_SIGNALGROUP

LOCAL_INLINE FUNC(void, COM_CODE)   Com_Lok_Init_TxSignalGroup(VAR(PduIdType, AUTOMATIC) IpduId)
{

    Com_TxIpduConstPtrType         TxIPduConstPtr;
    Com_TxSigGrpConstPtrType       TxSigGrpConstPtr;
    VAR(uint16_least, AUTOMATIC)   Idx_ByteNSig_ui;
    VAR(uint16_least, AUTOMATIC)   Idx_SigGrp_ui;
    VAR(uint16_least, AUTOMATIC)    FirstTxSigGrp_Index;
#if defined (COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
    VAR(PduLengthType, AUTOMATIC)  ByteNo_u8;
#endif
#ifdef COM_EffectiveSigGrpTOC

    VAR(uint8, AUTOMATIC)          TxSigGrpTp_u8;
#endif
    VAR(uint8, AUTOMATIC)          ConstByteValue_u8;
#ifdef COM_TX_SIGNALGROUP_ARRAY
    boolean                        ConstIsSigGrpOfArrayType_b;
#endif

    TxIPduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    FirstTxSigGrp_Index = TxIPduConstPtr->FirstTxSigGrp_Index;

    Idx_ByteNSig_ui     = (uint16_least)FirstTxSigGrp_Index + (uint16_least)TxIPduConstPtr->No_Of_SigGrp_Ref;

    TxSigGrpConstPtr    = COM_GET_TXSIGGRP_CONSTDATA(FirstTxSigGrp_Index);

    for(Idx_SigGrp_ui   = (uint16_least)FirstTxSigGrp_Index; Idx_SigGrp_ui < Idx_ByteNSig_ui;
                             Idx_SigGrp_ui++ )
    {

#ifdef COM_TX_SIGNALGROUP_ARRAY
        ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

#ifdef COM_SIGNALGROUPGATEWAY

        Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,COM_GET_TXSIGGRPFLAG(Idx_SigGrp_ui).txSigGrpRAMFields, COM_FALSE);
#endif

        Com_Lok_Init_GroupSignal(TxIPduConstPtr, TxSigGrpConstPtr);

#ifdef COM_EffectiveSigGrpTOC

        TxSigGrpTp_u8 = Com_GetValue(TXSIGGRP,_TP,TxSigGrpConstPtr->txSignalGrpFields);

        if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TxSigGrpTp_u8))
        {

            Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,COM_GET_TXSIGGRPFLAG(Idx_SigGrp_ui).txSigGrpRAMFields,COM_FALSE);
        }
#endif
#ifdef COM_TX_SIGNALGROUP_ARRAY

        if ( ConstIsSigGrpOfArrayType_b != COM_TRUE )
#endif
        {

            Com_ShadowBuffToIpduBuff((Com_SignalGroupIdType)Idx_SigGrp_ui);
        }

#ifdef COM_TxSigGrpUpdateBit

        ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;

        if((Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE) &&
                (Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields)))
        {

            ByteNo_u8 = (PduLengthType)(TxSigGrpConstPtr ->Update_Bit_Pos>>3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigGrpConstPtr->Update_Bit_Pos, ByteNo_u8)
        }
#endif
        TxSigGrpConstPtr++;
    }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_Init_GroupSignal(Com_TxIpduConstPtrType TxIPduConstPtr,
                                                              Com_TxSigGrpConstPtrType TxSigGrpConstPtr)
{

    Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
    VAR(Com_SigMaxType, AUTOMATIC)  TxGrpSig_NewVal;
    VAR(uint16_least, AUTOMATIC)    Idx_TxGrpSig_ui;
    VAR(uint8, AUTOMATIC)           ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)           Type;
    VAR(Com_MainFuncType,AUTOMATIC) txMainFuncId;
#ifdef COM_TX_SIGNALGROUP_ARRAY
    boolean                         ConstIsSigGrpOfArrayType_b;
    ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    txMainFuncId        = TxIPduConstPtr->MainFunctionRef;

    TxGrpSigConstPtr    = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr-> FirstGrpSig_Index);

    for( Idx_TxGrpSig_ui  = (uint16_least)COM_ZERO; Idx_TxGrpSig_ui < (uint16_least)TxSigGrpConstPtr->No_Of_GrpSig;
                                                                          Idx_TxGrpSig_ui++)
    {

        TxGrpSig_NewVal     = (Com_SigMaxType)TxGrpSigConstPtr->Init_Val;

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
        if ( ConstIsSigGrpOfArrayType_b )
        {
            Com_InitializePduBuffWithSignalInitValue( TxIPduConstPtr->BuffPtr,
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
            Com_CopyTxGroupSignalData(
                ((Com_SignalIdType)(TxSigGrpConstPtr->FirstGrpSig_Index) + (Com_TxIntGrpSignalIdType)Idx_TxGrpSig_ui),
                TxGrpSig_NewVal, txMainFuncId
                                     );
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

