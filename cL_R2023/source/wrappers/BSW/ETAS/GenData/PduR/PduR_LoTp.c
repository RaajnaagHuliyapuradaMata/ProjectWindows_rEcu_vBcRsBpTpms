

#include "PduR_Prv.h"

#include "PduR_Cfg.h"

#include "PduR_LoTp.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_CanTpRxIndication( PduIdType id, Std_ReturnType std)
{
    PduR_rCanTpRxIndication((id), (std));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_CanTpTxConfirmation( PduIdType id,
                                                  Std_ReturnType std)
{
    PduR_rCanTpTxConfirmation( (id), (std));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_CanTpCopyRxData( PduIdType id,
                                                                const PduInfoType * info,
                                                                PduLengthType * bufferSizePtr)
{
    return (PduR_rCanTpCopyRxData( (id), (info), (bufferSizePtr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_CanTpStartOfReception( PduIdType id,
                                                                const PduInfoType * info,
                                                                PduLengthType TpSduLength,
                                                                PduLengthType * bufferSizePtr)
{
    return (PduR_rCanTpStartOfReception( (id), (info),(TpSduLength), (bufferSizePtr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_CanTpCopyTxData( PduIdType id,
                                                                    const PduInfoType * info,
                                                                    RetryInfoType * retry,
                                                                    PduLengthType * availableDataPtr )
{
    return (PduR_rCanTpCopyTxData( (id), (info), (retry), (availableDataPtr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

