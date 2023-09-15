
#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_invId_UpTransmit( PduIdType id, const PduInfoType * ptr )
{

    (void)id;
    (void)ptr;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_invId_UpCancelTransmit(PduIdType id)
{

    (void)id;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

