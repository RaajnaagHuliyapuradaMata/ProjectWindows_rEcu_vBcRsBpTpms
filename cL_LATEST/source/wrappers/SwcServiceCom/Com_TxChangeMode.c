

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TxFilters
LOCAL_INLINE void Com_Lok_TxChangeMode_Signal            (Com_IpduIdType TxIpduId);

# ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE void Com_Lok_TxChangeMode_SignalGroup       (Com_IpduIdType TxIpduId);
LOCAL_INLINE boolean Com_Lok_TxChangeMode_GroupSignal    (Com_IpduIdType TxIpduId
   ,                                                         Com_TxGrpSigConstPtrType TxGrpSigConstPtr);
# endif
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_TxChangeMode(Com_IpduIdType TxIpduId)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   uint8                       LatestTransMode_u8;
   boolean                     Mode;

    Mode           = COM_TRUE;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(TxIpduId);

#ifdef COM_TxFilters
    TxIpduRamPtr->Com_TMSTrueCounter_u16 = COM_ZERO;

   if(Com_GetValue(TXIPDU,_FILTEREVALREQ,TxIpduConstPtr->txIPduFields) != COM_FALSE )
   {
        Com_Lok_TxChangeMode_Signal(TxIpduId);

#ifdef COM_TX_SIGNALGROUP
        Com_Lok_TxChangeMode_SignalGroup(TxIpduId);
#endif

        if(TxIpduRamPtr->Com_TMSTrueCounter_u16 != COM_ZERO)
        {

            Mode = COM_TRUE;
        }
        else{

            Mode = COM_FALSE;
        }
   }
#endif

   Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

   Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIpduConstPtr,Mode);

    LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;
   Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,LatestTransMode_u8);

   if(COM_TX_MODE_IS_CYCLIC(LatestTransMode_u8))
   {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxIpduId, TxIpduRamPtr->CurrentTxModePtr);

        TxIpduRamPtr->Com_n_Tick_Tx = COM_ZERO;

        TxIpduRamPtr->Com_n = COM_ZERO;

#ifdef COM_MIXEDPHASESHIFT
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode
   ,                                               TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif

   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_TxFilters

LOCAL_INLINE void Com_Lok_TxChangeMode_Signal(Com_IpduIdType TxIpduId)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
   Com_TxSigRamPtrType         TxSigRamPtr;
   uint16_least                index_u16;
   Com_SigMaxType              TxNewVal;
   uint8                       FilterAlg_u8;
   uint8                       ConstByteValue_u8;
   uint8                       sigType;
   boolean                     Filter_Val;

    TxIpduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);
    TxSigRamPtr     = &COM_GET_TXSIGNALFLAG(TxIpduConstPtr->TxSigId_Index);

   for(index_u16 = TxIpduConstPtr->No_Of_Sig_Ref; index_u16 != COM_ZERO; index_u16--)
   {
        FilterAlg_u8 = (uint8)Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields);

        if(FilterAlg_u8 != (uint8)COM_NOTCONFIGURED)
        {
            ConstByteValue_u8 = TxSigConstPtr->General;
            sigType = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

            if(sigType != (uint8)COM_UINT8_N)
            {

                SchM_Enter_Com_TxIpduProtArea(IPDUGROUPSTART);

                TxNewVal = Com_UnpackSignal( Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8)
   ,                                            TxSigConstPtr->Bit_Pos
   ,                                            TxSigConstPtr->BitSize
   ,                                            TxIpduConstPtr ->BuffPtr
   ,                                            ((sigType & COM_ONE) != COM_ZERO));

                SchM_Exit_Com_TxIpduProtArea(IPDUGROUPSTART);
            }
            else{
                TxNewVal = COM_ZERO;

            }

            Filter_Val = Com_Filter((uint32)TxNewVal,FilterAlg_u8, TxSigConstPtr->Filter_Index, COM_FALSE);

            if(Filter_Val != COM_FALSE)
            {

                TxIpduRamPtr->Com_TMSTrueCounter_u16++;
            }

            Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,Filter_Val);
        }
        TxSigConstPtr++;
        TxSigRamPtr++;
   }
}

#ifdef COM_TX_SIGNALGROUP

LOCAL_INLINE void Com_Lok_TxChangeMode_SignalGroup(Com_IpduIdType TxIpduId)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
   Com_TxGrpSigRamPtrType          TxGrpSigRamPtr;
   uint16_least                    idx_SigGrp_u16;
   uint16_least                    idx_GrpSig_u16;
   boolean                         Filter_Val;

    TxIpduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);

   for(idx_SigGrp_u16 = TxIpduConstPtr->No_Of_SigGrp_Ref; idx_SigGrp_u16 > COM_ZERO; idx_SigGrp_u16--)
   {
        if(Com_GetValue(TXSIGGRP,_FILTEREVALREQ,TxSigGrpConstPtr->txSignalGrpFields) != COM_FALSE)
        {

            TxGrpSigRamPtr = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

            TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

            for(idx_GrpSig_u16 = TxSigGrpConstPtr->No_Of_GrpSig; idx_GrpSig_u16 > COM_ZERO; idx_GrpSig_u16--)
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

LOCAL_INLINE boolean Com_Lok_TxChangeMode_GroupSignal(Com_IpduIdType TxIpduId, Com_TxGrpSigConstPtrType TxGrpSigConstPtr)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxIpduRamPtrType            TxIpduRamPtr;
# ifdef COM_TX_SIGNALGROUP_ARRAY
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
#endif
   Com_SigMaxType                  TxNewVal;
   Com_TxGrpSigBuffIndexType       GrpSigBuff_Index;
   Com_MainFuncType                txMainFuncId;
   uint8                           ConstByteValue_u8;
   uint8                           sigType;
   boolean                         Filter_Val;

    TxIpduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);
    txMainFuncId    = TxIpduConstPtr->MainFunctionRef;
    TxNewVal        = COM_ZERO;

   ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
   sigType = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
# ifdef COM_TX_SIGNALGROUP_ARRAY
    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef);
# endif
   if(sigType != (uint8)COM_UINT8_N)
   {
# ifdef COM_TX_SIGNALGROUP_ARRAY
        if(Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields) == COM_TRUE)
        {

            SchM_Enter_Com_TxIpduProtArea(IPDUGROUPSTART);

            TxNewVal = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8)
   ,                                        TxGrpSigConstPtr->Bit_Pos
   ,                                        TxGrpSigConstPtr->BitSize
   ,                                        TxIpduConstPtr->BuffPtr
   ,                                        ((sigType & COM_ONE) != COM_ZERO));

            SchM_Exit_Com_TxIpduProtArea(IPDUGROUPSTART);
        }
        else
# endif
        {
            GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

            switch(sigType >> 1u)
            {
            case 0x00u:
            case 0x03u:
                TxNewVal = COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, GrpSigBuff_Index);
                break;

            case 0x01u:

#if(CPU_TYPE == CPU_TYPE_8)
                Com_Get_SchM_Enter_Com_TxGrpSigBuffer
#endif
                TxNewVal = COM_GET_TXGRPSIGTYPEU16_BUFF(txMainFuncId, GrpSigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
                Com_Get_SchM_Exit_Com_TxGrpSigBuffer
#endif
                break;

            case 0x02u:
#if(CPU_TYPE != CPU_TYPE_32)
                Com_Get_SchM_Enter_Com_TxGrpSigBuffer
#endif

                TxNewVal = COM_GET_TXGRPSIGTYPEU32_BUFF(txMainFuncId, GrpSigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                Com_Get_SchM_Exit_Com_TxGrpSigBuffer
#endif
                break;

# ifdef COM_TXGRPSIG_INT64
            case 0x08u:
                Com_Get_SchM_Enter_Com_TxGrpSigBuffer

                TxNewVal = COM_GET_TXGRPSIGTYPEU64_BUFF(txMainFuncId, GrpSigBuff_Index);
                Com_Get_SchM_Exit_Com_TxGrpSigBuffer
                break;
# endif

            default:

                break;
            }
        }
   }
   else{

   }

    Filter_Val = Com_Filter((uint32)TxNewVal, TxGrpSigConstPtr->Filter_Algo
   ,                                             TxGrpSigConstPtr->Filter_Index, COM_FALSE);

   if(Filter_Val != COM_FALSE)
   {

        TxIpduRamPtr->Com_TMSTrueCounter_u16++;
   }
    return Filter_Val;
}
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_Lok_SigTxChangeMode(Com_SignalIdType SignalId, uint32 TxNewVal)
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
   Com_TxSigRamPtrType         TxSigRamPtr;
   Com_IpduIdType              TxIpduId;
   boolean                     sig_TMSState;
   boolean                     ReturnValue;

    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(SignalId);
    TxSigRamPtr     = &COM_GET_TXSIGNALFLAG(SignalId);
    TxIpduId        = TxSigConstPtr->IpduRef;

    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxIpduId);

    SchM_Enter_Com_TxIpduProtArea(SIGTXCHANGEMODE);

   if(Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields) > (uint16)COM_NEVER)
   {

        sig_TMSState = Com_Filter(TxNewVal
   ,                          (uint8)Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields)
   ,                                 TxSigConstPtr->Filter_Index, COM_TRUE);

        if(Com_GetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields) != sig_TMSState)
        {
            if(sig_TMSState != COM_FALSE)
            {

                TxIpduRamPtr->Com_TMSTrueCounter_u16++;
            }
            else{

                TxIpduRamPtr->Com_TMSTrueCounter_u16--;
            }

            Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,sig_TMSState);
        }
   }

    ReturnValue = Com_Lok_CheckModeChange(TxIpduId);

    SchM_Exit_Com_TxIpduProtArea(SIGTXCHANGEMODE);

    return(ReturnValue);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_Lok_SigGrpTxChangeMode(Com_SignalGroupIdType SignalGroupId)
{

   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxIpduRamPtrType            TxIpduRamPtr;
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
   Com_TxGrpSigRamPtrType          TxGrpSigRamPtr;

   Com_SigMaxType                  TxNewVal_GrpSig;
   Com_TxGrpSigBuffIndexType       GrpSigBuff_Index;
   uint16_least                    idx_GrpSig_u16;
   Com_IpduIdType                  TxIpduId;
   uint8                           ConstByteValue_u8;
   uint8                           sigType;
   Com_MainFuncType                txMainFuncId;
   boolean                         sig_TMSState;
   boolean                         ReturnValue;
#ifdef COM_TX_SIGNALGROUP_ARRAY
   boolean                         isSigGrpArrayAccess_b;
#endif

    TxSigGrpConstPtr  = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);
    TxIpduId          = TxSigGrpConstPtr->IpduRef;

    TxIpduConstPtr    = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);
    TxIpduRamPtr      = &COM_GET_TXPDURAM_S(TxIpduId);

    TxGrpSigConstPtr  = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);
    TxGrpSigRamPtr    = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

    txMainFuncId      = TxIpduConstPtr->MainFunctionRef;

#ifdef COM_TX_SIGNALGROUP_ARRAY
   isSigGrpArrayAccess_b  = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    SchM_Enter_Com_TxIpduProtArea(SIGGRPTXCHANGEMODE);

   for(idx_GrpSig_u16 = TxSigGrpConstPtr->No_Of_GrpSig; idx_GrpSig_u16 > COM_ZERO; idx_GrpSig_u16--)
   {

        if((TxGrpSigConstPtr->Filter_Algo != (uint8)COM_NOTCONFIGURED) && (TxGrpSigConstPtr->Filter_Algo > COM_NEVER))
        {
            ConstByteValue_u8   = TxGrpSigConstPtr->txGrpSigFields;
            sigType             = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);

            TxNewVal_GrpSig     = COM_ZERO;

            if(sigType != (uint8)COM_UINT8_N)
            {
#ifdef COM_TX_SIGNALGROUP_ARRAY
                if(isSigGrpArrayAccess_b)
                {

                    TxNewVal_GrpSig = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8)
   ,                                                       TxGrpSigConstPtr->Bit_Pos
   ,                                                       TxGrpSigConstPtr->BitSize
   ,                                                       TxIpduConstPtr->BuffPtr
   ,                                                       ((sigType & COM_ONE) != COM_ZERO));
                }
                else
#endif
                {
                    GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

                    switch(sigType >> 1u)
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
            else{

            }

            sig_TMSState = Com_Filter((uint32)TxNewVal_GrpSig, TxGrpSigConstPtr->Filter_Algo
   ,                                                              TxGrpSigConstPtr->Filter_Index, COM_TRUE);

            if(Com_GetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields) != sig_TMSState)
            {
                if(sig_TMSState != COM_FALSE)
                {

                    TxIpduRamPtr->Com_TMSTrueCounter_u16++;
                }
                else{

                    TxIpduRamPtr->Com_TMSTrueCounter_u16--;
                }

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
#include "Com_MemMap.hpp"

#endif

#endif

