

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyRxData(VAR(PduIdType, AUTOMATIC) id,
                                                                P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
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

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpStartOfReception(VAR(PduIdType, AUTOMATIC) id,
                                                                    VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                    P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
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

FUNC( void, PDUR_CODE ) PduR_invId_TpRxIndication(VAR(PduIdType, AUTOMATIC) id,
                                                  VAR(Std_ReturnType, AUTOMATIC) result)
{

    (void)id;
    (void)result;

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyTxData( VAR(PduIdType, AUTOMATIC) id,
                                                                P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
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

FUNC( void, PDUR_CODE ) PduR_invId_TpTxConfirmation(VAR(PduIdType, AUTOMATIC) id,
                                                    VAR(Std_ReturnType, AUTOMATIC) result)
{

    (void)id;
    (void)result;
}

FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelReceive(VAR(PduIdType, AUTOMATIC) id)
{

    (void)id;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

