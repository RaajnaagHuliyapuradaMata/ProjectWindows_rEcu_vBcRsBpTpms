

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void * SignalDataPtr)
{
#ifdef COM_EffectiveSigGrpTOC
    Com_TxSigGrpRamPtrType          TxSigGrpRamPtr;
#endif
    Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
    Com_SigMaxType                  TxNewVal;
    uint8                           ConstByteValue_u8;
    uint8                           Type;
    Com_MainFuncType                txMainFuncId;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if (Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_GRPSIGNALS),(SignalDataPtr == NULL_PTR),
                                    COMServiceId_UpdateShadowSignal))
#endif
    {
        SignalId = COM_GET_TXGRPSIGNAL_ID(SignalId);

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);

        txMainFuncId = (COM_GET_TX_IPDU_CONSTDATA((COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
        Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
        TxNewVal = COM_ZERO;

        if(Type != (uint8)COM_UINT8_N)
        {
            switch(Type)
            {

            case COM_UINT8:
            case COM_SINT8:

                TxNewVal = *(const uint8 * )SignalDataPtr;
                break;
            case COM_UINT16:
            case COM_SINT16:

                TxNewVal = *(const uint16 * )SignalDataPtr;
                break;
            case COM_BOOLEAN:

                TxNewVal = COM_BOOL_TO_UNSIGNED(*(const boolean * )SignalDataPtr);
                break;
            case COM_UINT32:
            case COM_SINT32:

                TxNewVal = *(const uint32 * )SignalDataPtr;
                break;
#ifdef COM_TXGRPSIG_INT64
            case COM_UINT64:
            case COM_SINT64:

                TxNewVal = *(const uint64 * )SignalDataPtr;
                break;
#endif

#ifdef COM_GRPSIGFLOAT32SUPP
            case COM_FLOAT32:
            {
                uint32 TxNewVal_u32;

                TxNewVal_u32 = COM_ZERO;

                (void)rba_BswSrv_MemCopy( (void *)(&TxNewVal_u32),(const void *)SignalDataPtr, COM_F32_SIZE_IN_BYTES );

                TxNewVal = TxNewVal_u32;
            }
                break;
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
            case COM_FLOAT64:

                SchM_Enter_Com_TxGrpSigBuffer();
                COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index) =
                        *(const float64 * )SignalDataPtr;
                SchM_Exit_Com_TxGrpSigBuffer();
                break;
#endif

            default:

                break;
            }

            Com_CopyTxGroupSignalData(SignalId, TxNewVal, txMainFuncId);

#ifdef COM_EffectiveSigGrpTOC
            TxSigGrpRamPtr = &COM_GET_TXSIGGRPFLAG(TxGrpSigConstPtr->SigGrpRef);

            if((Com_GetValue(TXGRPSIG,_TP,ConstByteValue_u8) != COM_FALSE)  &&
               (COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) != (Com_OldValTrigOnChngType)TxNewVal))
            {

                COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxNewVal;
                Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr ->txSigGrpRAMFields,COM_TRUE);
            }
#endif
        }
        else
        {

            SchM_Enter_Com_TxGrpSigBuffer();

            Com_ByteCopy(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index),
                    (const uint8 * )SignalDataPtr,(uint32)TxGrpSigConstPtr->BitSize);

            SchM_Exit_Com_TxGrpSigBuffer();
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

