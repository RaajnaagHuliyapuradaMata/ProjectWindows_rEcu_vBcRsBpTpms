
#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr )
{

    (void)id;
    (void)ptr;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelTransmit(VAR(PduIdType, AUTOMATIC) id)
{

    (void)id;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

