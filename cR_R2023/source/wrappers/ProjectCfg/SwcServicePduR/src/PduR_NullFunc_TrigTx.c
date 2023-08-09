

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_NF_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) id,
                                                      P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA ) data)
{

    (void)id;
    (void)data;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

