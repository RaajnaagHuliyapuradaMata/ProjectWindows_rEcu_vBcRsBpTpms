
#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_invId_UpTransmit( PduIdType id, const PduInfoType * ptr )
{

    (void)id;
    (void)ptr;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_invId_UpCancelTransmit(PduIdType id)
{

    (void)id;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

