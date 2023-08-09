

#include "PduR_Prv.h"

#include "PduR_Cfg.h"

#include "PduR_LoIf.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_CanIfTxConfirmation( VAR(PduIdType, AUTOMATIC) id )
{
    PduR_rCanIfTxConfirmation( id );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_CanIfRxIndication( VAR(PduIdType, AUTOMATIC) id,
                                                P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    PduR_rCanIfRxIndication((id), (ptr));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

