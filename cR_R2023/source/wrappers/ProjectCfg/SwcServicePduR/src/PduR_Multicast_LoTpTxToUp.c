

#include "PduR_Prv.h"
#include "PduR_Mc.h"

#if defined(PDUR_MULTICAST_TO_TP_SUPPORT) && (PDUR_MULTICAST_TO_TP_SUPPORT != 0)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_MF_McTpTx_CopyTxData( VAR(PduIdType, AUTOMATIC) mcId,
                                                                     P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                     P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
{
    VAR(BufReq_ReturnType, AUTOMATIC) r;

    P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST ) mcTable = PDUR_LOTP_TX_MC_BASE + mcId;
    P2VAR( PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state = PDUR_LOTP_TX_STATE_BASE + mcId;

    SchM_Enter_PduR_LockMcTpTxCopyTxData();

    if (state->pduPtr == NULL_PTR)
    {

        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        state->allocError = PDUR_BASE_RPTBL(upTpTxDataTablePtr)[mcTable->toUp.upProvideTxBufID].PduR_upTpCopyTxDataFunc(mcTable->toUp.upId, state->pduPtr, retry, availableDataPtr);
        #else
        state->allocError = PduR_upTpCopyTxDataTable[mcTable->toUp.upProvideTxBufID].PduR_upTpCopyTxDataFunc(mcTable->toUp.upId, state->pduPtr, retry, availableDataPtr);
        #endif
        if (state->allocError != BUFREQ_OK)
        {

            state->pduPtr = NULL_PTR;
        }
    }
    if(info != NULL_PTR)
    {
    }

    info = state->pduPtr;
    r = state->allocError;

    SchM_Exit_PduR_LockMcTpTxCopyTxData();

    return r;

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_TxConfirmation( VAR(PduR_LayerType, AUTOMATIC) layerId,
                                                       VAR(PduIdType, AUTOMATIC) mcId,
                                                       VAR(Std_ReturnType, AUTOMATIC) result)
{

    P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST ) mcTable = PDUR_LOTP_TX_MC_BASE + mcId;
    P2VAR(   PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state = PDUR_LOTP_TX_STATE_BASE + mcId;

    (void)layerId;

    SchM_Enter_PduR_LockMcTpTxConf();

    if (state->txFailure == E_OK)
    {
        state->txFailure = result;
    }

    state->txConf += 1;
    if (state->txConf == mcTable->destLowerLayers)
    {

        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        PDUR_BASE_RPTBL(upTpTxConfTablePtr)[mcTable->toUp.upTxConfirmationID].PduR_upTpTxConfirmationFunc (mcTable->toUp.upId, state->txFailure);
        #else
        PduR_upTpTxConfirmationTable[mcTable->toUp.upTxConfirmationID].PduR_upTpTxConfirmationFunc (mcTable->toUp.upId, state->txFailure);
        #endif

        PduR_iInit_multicast(state);
    }

    SchM_Exit_PduR_LockMcTpTxConf();
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

