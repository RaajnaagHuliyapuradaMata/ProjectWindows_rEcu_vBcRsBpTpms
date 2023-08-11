

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

BufReq_ReturnType Com_CopyTxData(
                            PduIdType               PduId,
                            const PduInfoType*      PduInfoPtr,
                            RetryInfoType*          RetryInfoPtr,
                            PduLengthType*          availableDataPtr
                                )
{

    Com_TxIpduConstPtrType      TxIpduConstPtr;
    Com_TxIpduRamPtrType        TxIpduRamPtr;
    BufReq_ReturnType           return_value;

    return_value = BUFREQ_E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if (Com_Lok_DETCheck_Param_Ptr((PduId >= COM_GET_NUM_TX_IPDU), ((PduInfoPtr == NULL_PTR) || (availableDataPtr == NULL_PTR )), COMServiceId_CopyTxData))
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

        (void)RetryInfoPtr;

        if (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags))
        {

            if (PduInfoPtr->SduLength != COM_ZERO)
            {

                if ((PduInfoPtr->SduLength + TxIpduRamPtr->TxTPIPduLength) <= COM_GET_TPTXIPDULENGTH_AUO(PduId))
                {

                    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);

                    Com_ByteCopy((uint8*)(PduInfoPtr->SduDataPtr),
                                         (TxIpduConstPtr->BuffPtr + TxIpduRamPtr->TxTPIPduLength),
                                          PduInfoPtr->SduLength);

                    TxIpduRamPtr->TxTPIPduLength += PduInfoPtr->SduLength;

                    *availableDataPtr = COM_GET_TPTXIPDULENGTH_AUO(PduId) - TxIpduRamPtr->TxTPIPduLength;

                    return_value = BUFREQ_OK;
                }
            }
            else
            {

                *availableDataPtr = COM_GET_TPTXIPDULENGTH_AUO(PduId) - TxIpduRamPtr->TxTPIPduLength;

                return_value = BUFREQ_OK;
            }
        }
    }
    return return_value;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

