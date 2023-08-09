

#include "PduR_Prv.h"

#include "PduR_Cfg.h"

#include "PduR_LoTp.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_CanTpRxIndication( VAR(PduIdType, AUTOMATIC) id, VAR(Std_ReturnType, AUTOMATIC) std)
{
    PduR_rCanTpRxIndication((id), (std));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_CanTpTxConfirmation( VAR(PduIdType, AUTOMATIC) id,
                                                  VAR(Std_ReturnType, AUTOMATIC) std)
{
    PduR_rCanTpTxConfirmation( (id), (std));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyRxData( VAR(PduIdType, AUTOMATIC) id,
                                                                P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    return (PduR_rCanTpCopyRxData( (id), (info), (bufferSizePtr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpStartOfReception( VAR(PduIdType, AUTOMATIC) id,
                                                                P2CONST(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                                VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    return (PduR_rCanTpStartOfReception( (id), (info),(TpSduLength), (bufferSizePtr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyTxData( VAR(PduIdType, AUTOMATIC) id,
                                                                    P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                    P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                    P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
{
    return (PduR_rCanTpCopyTxData( (id), (info), (retry), (availableDataPtr)));

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

