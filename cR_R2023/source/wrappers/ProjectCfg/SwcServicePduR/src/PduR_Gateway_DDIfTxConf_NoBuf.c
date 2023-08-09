

#include "PduR_Prv.h"
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_GF_DDIf_NoBuf_TxConfirmation_Func(VAR(PduIdType, AUTOMATIC) gwayId)
{

    (void)gwayId;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

