#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_UpdateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC)  SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{
#ifdef COM_EffectiveSigGrpTOC
   Com_TxSigGrpRamPtrType TxSigGrpRamPtr;
#endif

   Com_TxGrpSigConstPtrType  TxGrpSigConstPtr;
   VAR(Com_SigMaxType, AUTOMATIC) TxNewVal;
   VAR(uint8, AUTOMATIC) ConstByteValue_u8;
   VAR(uint8, AUTOMATIC) Type;
   VAR(Com_MainFuncType,AUTOMATIC) txMainFuncId;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_GRPSIGNALS),(SignalDataPtr == NULL_PTR)
   ,     COMServiceId_UpdateShadowSignal))
#endif
   {
        SignalId = COM_GET_TXGRPSIGNAL_ID(SignalId);

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);

        txMainFuncId = (COM_GET_TX_IPDU_CONSTDATA((COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

        Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
        TxNewVal = 0u;

        if(Type != (uint8)COM_UINT8_N)
        {
            switch(Type)
            {

            case COM_UINT8:
            case COM_SINT8:

                TxNewVal = *(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
                break;
            case COM_UINT16:
            case COM_SINT16:

                TxNewVal = *(P2CONST(uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
                break;
            case COM_BOOLEAN:

                TxNewVal = COM_BOOL_TO_UNSIGNED(*(P2CONST(boolean,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
                break;
            case COM_UINT32:
            case COM_SINT32:

                TxNewVal = *(P2CONST(uint32,AUTOMATIC,COM_APPL_DATA))SignalDataPtr;
                break;
#ifdef COM_TXGRPSIG_INT64
            case COM_UINT64:
            case COM_SINT64:

                TxNewVal = *(P2CONST(uint64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
                break;
#endif

#ifdef COM_GRPSIGFLOAT32SUPP
            case COM_FLOAT32:

                (void)LibAutosar_vptrMemCopy( (void *)(&TxNewVal),(const void *)SignalDataPtr, 4 );
                break;
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
            case COM_FLOAT64:

                SchM_Enter_Com_TxGrpSigBuffer();
                COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index) =
                        *(P2CONST(float64,AUTOMATIC,COM_APPL_DATA))SignalDataPtr;
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
        else{

            SchM_Enter_Com_TxGrpSigBuffer();

            Com_ByteCopy(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,     (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr,(uint32)TxGrpSigConstPtr->BitSize);

            SchM_Exit_Com_TxGrpSigBuffer();
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

