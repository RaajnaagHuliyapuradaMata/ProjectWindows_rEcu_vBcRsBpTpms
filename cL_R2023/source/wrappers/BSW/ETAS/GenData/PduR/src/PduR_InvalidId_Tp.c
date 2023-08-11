

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_invId_TpCopyRxData(PduIdType id,
                                                                const PduInfoType * info,
                                                                PduLengthType * bufferSizePtr)
{

    (void)id;
    (void)info;
    (void)bufferSizePtr;

    return BUFREQ_E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_invId_TpStartOfReception(PduIdType id,
                                                                    PduLengthType TpSduLength,
                                                                    PduLengthType * bufferSizePtr)
{

    (void)id;
    (void)TpSduLength;
    (void)bufferSizePtr;

    return BUFREQ_E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_invId_TpRxIndication(PduIdType id,
                                                  Std_ReturnType result)
{

    (void)id;
    (void)result;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_invId_TpCopyTxData( PduIdType id,
                                                                const PduInfoType * info,
                                                                RetryInfoType * retry,
                                                                PduLengthType * availableDataPtr )
{

    info = info;

    (void)id;
    (void)info;
    (void)retry;
    (void)availableDataPtr;

    return BUFREQ_E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_invId_TpTxConfirmation(PduIdType id,
                                                    Std_ReturnType result)
{

    (void)id;
    (void)result;
}

Std_ReturnType PduR_invId_UpCancelReceive(PduIdType id)
{

    (void)id;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

