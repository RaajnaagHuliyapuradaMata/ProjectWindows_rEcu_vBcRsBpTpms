

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TxFilters
LOCAL_INLINE FUNC(void,COM_CODE) Com_Lok_TxChangeMode_Signal            (VAR(Com_IpduIdType, AUTOMATIC) TxIpduId);

# ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void,COM_CODE) Com_Lok_TxChangeMode_SignalGroup       (VAR(Com_IpduIdType, AUTOMATIC) TxIpduId);
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_TxChangeMode_GroupSignal    (VAR(Com_IpduIdType, AUTOMATIC) TxIpduId,
                                                                         Com_TxGrpSigConstPtrType TxGrpSigConstPtr);
# endif
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void,COM_CODE) Com_TxChangeMode(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId)
{

    Com_TxIpduConstPtrType                          TxIPduConstPtr;

    Com_TxIpduRamPtrType                            TxIpduRamPtr;
    VAR(uint8, AUTOMATIC)                           LatestTransMode_u8;
    VAR(boolean, AUTOMATIC)                         Mode;

    Mode = COM_TRUE;
    TxIPduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr     = &COM_GET_TXPDURAM_S(TxIpduId);

#ifdef COM_TxFilters
    TxIpduRamPtr->Com_TMSTrueCounter_u8 = 0;

    if (Com_GetValue(TXIPDU,_FILTEREVALREQ,TxIPduConstPtr->txIPduFields) != COM_FALSE )
    {
        Com_Lok_TxChangeMode_Signal(TxIpduId);

#ifdef COM_TX_SIGNALGROUP
        Com_Lok_TxChangeMode_SignalGroup(TxIpduId);
#endif

        if (TxIpduRamPtr->Com_TMSTrueCounter_u8 != 0)
        {

            Mode = COM_TRUE;
        }
        else
        {

            Mode = COM_FALSE;
        }
    }
#endif

    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

    Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);

    LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;
    Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,LatestTransMode_u8);

    if( 0u != ( LatestTransMode_u8 & COM_TXMODE_MIXED ) )
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxIpduId, (TxIpduRamPtr->CurrentTxModePtr));

        TxIpduRamPtr ->Com_n_Tick_Tx = 0;

        TxIpduRamPtr ->Com_n = 0;

#ifdef COM_MIXEDPHASESHIFT
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,
                                                TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif

    }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxFilters

LOCAL_INLINE FUNC(void,COM_CODE) Com_Lok_TxChangeMode_Signal(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId)
{

    Com_TxIpduConstPtrType                          TxIPduConstPtr;

    Com_TxIpduRamPtrType                            TxIpduRamPtr;

    Com_TxSigConstPtrType                           TxSigConstPtr;

    Com_TxSigRamPtrType                             TxSigRamPtr;
    VAR(uint16_least, AUTOMATIC)                    Index_ui;
    VAR(Com_SigMaxType, AUTOMATIC)                  TxNewVal;
    VAR(uint8, AUTOMATIC)                           FilterAlg_u8;
    VAR(uint8, AUTOMATIC)                           ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)                           Type;
    VAR(boolean, AUTOMATIC)                         Filter_Val;

    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
    TxSigRamPtr     = &COM_GET_TXSIGNALFLAG(TxIPduConstPtr->TxSigId_Index);

    for(Index_ui = TxIPduConstPtr->No_Of_Sig_Ref; Index_ui != 0u; Index_ui--)
    {
        FilterAlg_u8 = (uint8)Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields);

        if(FilterAlg_u8 != (uint8)COM_NOTCONFIGURED)
        {
            ConstByteValue_u8 = TxSigConstPtr->General;
            Type = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

            if(Type != (uint8)COM_UINT8_N)
            {
                TxNewVal = Com_UnpackSignal( Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8),
                                             TxSigConstPtr->Bit_Pos,
                                             TxSigConstPtr->BitSize,
                                             TxIPduConstPtr ->BuffPtr,
                                             ((Type & 0x01u) != 0x0u));
            }
            else
            {
                TxNewVal = 0;

            }

            Filter_Val = Com_Filter((uint32)TxNewVal,FilterAlg_u8, TxSigConstPtr->Filter_Index, COM_FALSE);

            if (Filter_Val != COM_FALSE)
            {

                TxIpduRamPtr ->Com_TMSTrueCounter_u8++;
            }

            Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,Filter_Val);
        }
        TxSigConstPtr++;
        TxSigRamPtr++;
    }
}
#endif

#if defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP)

LOCAL_INLINE FUNC(void,COM_CODE) Com_Lok_TxChangeMode_SignalGroup(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId)
{

    Com_TxIpduConstPtrType                          TxIPduConstPtr;

    Com_TxSigGrpConstPtrType                        TxSigGrpConstPtr;

    Com_TxGrpSigConstPtrType                        TxGrpSigConstPtr;

    Com_TxGrpSigRamPtrType                          TxGrpSigRamPtr;
    VAR(uint16_least, AUTOMATIC)                    GrpSig_Index_ui;
    VAR(uint16_least, AUTOMATIC)                    Index_ui;
    VAR(boolean, AUTOMATIC)                         Filter_Val;

    TxIPduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

    for(Index_ui = TxIPduConstPtr->No_Of_SigGrp_Ref; Index_ui!= 0u; Index_ui--)
    {
        if(Com_GetValue(TXSIGGRP,_FILTEREVALREQ,TxSigGrpConstPtr->txSignalGrpFields) != COM_FALSE)
        {

            TxGrpSigRamPtr = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

            TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

            for(GrpSig_Index_ui = TxSigGrpConstPtr->No_Of_GrpSig; GrpSig_Index_ui != 0u; GrpSig_Index_ui--)
            {

                if(TxGrpSigConstPtr->Filter_Algo != (uint8)COM_NOTCONFIGURED)
                {
                    Filter_Val = Com_Lok_TxChangeMode_GroupSignal(TxIpduId, TxGrpSigConstPtr);

                    Com_SetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields,Filter_Val);
                }
                TxGrpSigConstPtr++;
                TxGrpSigRamPtr++;
            }
        }
        TxSigGrpConstPtr++;
    }
}

LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_TxChangeMode_GroupSignal   (VAR(Com_IpduIdType, AUTOMATIC) TxIpduId,
                                                                        Com_TxGrpSigConstPtrType TxGrpSigConstPtr)
{

    Com_TxIpduConstPtrType                          TxIPduConstPtr;
    Com_TxIpduRamPtrType                            TxIpduRamPtr;
# ifdef COM_TX_SIGNALGROUP_ARRAY
    Com_TxSigGrpConstPtrType                        TxSigGrpConstPtr;
#endif
    VAR(Com_SigMaxType, AUTOMATIC)                  TxNewVal;
    VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC)       GrpSigBuff_Index;
    VAR(Com_MainFuncType,AUTOMATIC)                 txMainFuncId;
    VAR(uint8, AUTOMATIC)                           ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)                           Type;
    VAR(boolean, AUTOMATIC)                         Filter_Val;
# ifdef COM_TX_SIGNALGROUP_ARRAY
    VAR(boolean, AUTOMATIC)                         ConstIsSigGrpOfArrayType_b;
#endif

    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    txMainFuncId    = TxIPduConstPtr->MainFunctionRef;
    TxNewVal        = 0u;

    ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
    Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
# ifdef COM_TX_SIGNALGROUP_ARRAY
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef);
    ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
# endif
    if(Type != (uint8)COM_UINT8_N)
    {
# ifdef COM_TX_SIGNALGROUP_ARRAY
        if ( ConstIsSigGrpOfArrayType_b )
        {

            TxNewVal = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                         TxGrpSigConstPtr->Bit_Pos,
                                         TxGrpSigConstPtr->BitSize,
                                         TxIPduConstPtr->BuffPtr,
                                         ((Type & 0x01u) != 0x0u));

        }
        else
# endif
        {
            GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

            switch(Type >> 1u)
            {
            case 0x00u:
            case 0x03u:
                TxNewVal = COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, GrpSigBuff_Index);
                break;

            case 0x01u:

                TxNewVal = COM_GET_TXGRPSIGTYPEU16_BUFF(txMainFuncId, GrpSigBuff_Index);
                break;

            case 0x02u:

                TxNewVal = COM_GET_TXGRPSIGTYPEU32_BUFF(txMainFuncId, GrpSigBuff_Index);
                break;

# ifdef COM_TXGRPSIG_INT64
            case 0x08u:

                TxNewVal = COM_GET_TXGRPSIGTYPEU64_BUFF(txMainFuncId, GrpSigBuff_Index);
                break;
# endif

            default:

                break;
            }
        }
    }
    else
    {

        TxNewVal = 0u;
    }

    Filter_Val = Com_Filter((uint32)TxNewVal, TxGrpSigConstPtr->Filter_Algo,
                        TxGrpSigConstPtr->Filter_Index,COM_FALSE);

    if (Filter_Val != COM_FALSE)
    {

        TxIpduRamPtr ->Com_TMSTrueCounter_u8++;
    }
    return Filter_Val;
}
#endif

#ifdef COM_TxFilters

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(boolean,COM_CODE) Com_Lok_SigTxChangeMode(VAR(Com_SignalIdType, AUTOMATIC) SignalId,
                                               VAR(uint32, AUTOMATIC) TxNewVal)
{

    Com_TxIpduRamPtrType    TxIpduRamPtr;
    Com_TxSigConstPtrType   TxSigConstPtr;
    Com_TxSigRamPtrType     TxSigRamPtr;
    VAR(Com_IpduIdType, AUTOMATIC)  TxIpduId;
    VAR(boolean, AUTOMATIC)         sig_TMSState;
    VAR(boolean, AUTOMATIC)         ReturnValue;

    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(SignalId);
    TxIpduId        = TxSigConstPtr->IpduRef;

    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);

    SchM_Enter_Com_TxIpduProtArea(SIGTXCHANGEMODE);
    {
        TxSigRamPtr     = &COM_GET_TXSIGNALFLAG(SignalId);

        if(Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields) > (uint16)COM_NEVER)
        {

            sig_TMSState = Com_Filter(TxNewVal,
                               (uint8)Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields),
                                   TxSigConstPtr->Filter_Index,COM_TRUE);

            if (Com_GetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields)!= sig_TMSState)
            {

                TxIpduRamPtr ->Com_TMSTrueCounter_u8 =
                       ((sig_TMSState != COM_FALSE) ? (TxIpduRamPtr ->Com_TMSTrueCounter_u8 + 1):
                                                    (TxIpduRamPtr ->Com_TMSTrueCounter_u8-1));

                Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,sig_TMSState);
            }
        }
    }

    ReturnValue = Com_Lok_CheckModeChange(TxIpduId);
    SchM_Exit_Com_TxIpduProtArea(SIGTXCHANGEMODE);

    return(ReturnValue);
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#if (defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP))

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(boolean,COM_CODE) Com_Lok_SigGrpTxChangeMode(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{

    Com_TxIpduConstPtrType  TxIPduConstPtr;
    Com_TxIpduRamPtrType    TxIpduRamPtr;

    Com_TxGrpSigRamPtrType                      TxGrpSigRamPtr;

    Com_TxSigGrpConstPtrType                    TxSigGrpConstPtr;

    Com_TxGrpSigConstPtrType                    TxGrpSigConstPtr;

    VAR(Com_SigMaxType, AUTOMATIC)              TxNewVal_GrpSig;
    VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC)   GrpSigBuff_Index;
    VAR(Com_IpduIdType, AUTOMATIC)              TxIpduId;
    VAR(uint16_least, AUTOMATIC)                GrpSig_Index_ui;
    VAR(uint8, AUTOMATIC)                       ConstByteValue_u8;
    VAR(boolean, AUTOMATIC)                     sig_TMSState;
    VAR(boolean, AUTOMATIC)                     ReturnValue;
    VAR(uint8, AUTOMATIC)                       Type;
    VAR(Com_MainFuncType,AUTOMATIC)             txMainFuncId;
#ifdef COM_TX_SIGNALGROUP_ARRAY
    boolean                                     ConstIsSigGrpOfArrayType_b;
#endif

    TxNewVal_GrpSig  = (Com_SigMaxType)COM_ZERO;
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);
    TxIpduId         = TxSigGrpConstPtr->IpduRef;

    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    SchM_Enter_Com_TxIpduProtArea(SIGGRPTXCHANGEMODE);

    TxGrpSigRamPtr              = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

    TxGrpSigConstPtr            = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

    txMainFuncId = TxIPduConstPtr->MainFunctionRef;

#ifdef COM_TX_SIGNALGROUP_ARRAY
    ConstIsSigGrpOfArrayType_b  = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    for(GrpSig_Index_ui = TxSigGrpConstPtr->No_Of_GrpSig; GrpSig_Index_ui != 0u; GrpSig_Index_ui--)
    {

        if((TxGrpSigConstPtr->Filter_Algo != (uint8)COM_NOTCONFIGURED) && (TxGrpSigConstPtr->Filter_Algo > COM_NEVER))
        {

            ConstByteValue_u8   = TxGrpSigConstPtr->txGrpSigFields;
            Type                = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);

            if(Type != (uint8)COM_UINT8_N)
            {
#ifdef COM_TX_SIGNALGROUP_ARRAY
                if (ConstIsSigGrpOfArrayType_b)
                {

                    TxNewVal_GrpSig = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                                        TxGrpSigConstPtr->Bit_Pos,
                                                        TxGrpSigConstPtr->BitSize,
                                                        TxIPduConstPtr->BuffPtr,
                                                        ((Type & 0x01u) != 0x0u));
                }
                else
#endif
                {
                    GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

                    switch(Type >> COM_ONE)
                    {
                    case 0x00u:
                    case 0x03u:
                        TxNewVal_GrpSig = COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, GrpSigBuff_Index);
                        break;

                    case 0x01u:

                        TxNewVal_GrpSig = COM_GET_TXGRPSIGTYPEU16_BUFF(txMainFuncId, GrpSigBuff_Index);
                        break;

                    case 0x02u:

                        TxNewVal_GrpSig = COM_GET_TXGRPSIGTYPEU32_BUFF(txMainFuncId, GrpSigBuff_Index);
                        break;

#ifdef COM_TXGRPSIG_INT64
                    case 0x08u:

                        TxNewVal_GrpSig = COM_GET_TXGRPSIGTYPEU64_BUFF(txMainFuncId, GrpSigBuff_Index);
                        break;
#endif

                    default:

                        break;
                    }
                }
            }
            else
            {

                TxNewVal_GrpSig = COM_ZERO;
            }

            sig_TMSState = Com_Filter((uint32)TxNewVal_GrpSig, TxGrpSigConstPtr->Filter_Algo,
                                                               TxGrpSigConstPtr->Filter_Index,COM_TRUE);

            if (Com_GetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields)!= sig_TMSState)
            {

                TxIpduRamPtr->Com_TMSTrueCounter_u8 =
                    ((sig_TMSState != COM_FALSE) ? (TxIpduRamPtr->Com_TMSTrueCounter_u8+1):
                                                        (TxIpduRamPtr->Com_TMSTrueCounter_u8-1));

                Com_SetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields,sig_TMSState);
            }
        }
        TxGrpSigConstPtr++;
        TxGrpSigRamPtr++;
    }

    ReturnValue = Com_Lok_CheckModeChange(TxIpduId);

    SchM_Exit_Com_TxIpduProtArea(SIGGRPTXCHANGEMODE);

    return(ReturnValue);
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

