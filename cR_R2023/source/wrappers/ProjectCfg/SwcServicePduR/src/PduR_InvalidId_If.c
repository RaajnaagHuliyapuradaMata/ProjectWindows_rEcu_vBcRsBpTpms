

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_invId_IfRxIndication(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{

    (void)id;
    (void)ptr;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_IfTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data )
{

    (void)id;
    (void)data;
    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
 #include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_invId_IfTxConfirmation( VAR(PduIdType, AUTOMATIC) id)
{

    (void)id;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

