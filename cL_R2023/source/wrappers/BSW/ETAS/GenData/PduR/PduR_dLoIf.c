

#include "PduR_Prv.h"

#include "PduR_Cfg.h"

#include "PduR_LoIf.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_CanIfTxConfirmation( PduIdType id )
{
    PduR_rCanIfTxConfirmation( id );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_CanIfRxIndication( PduIdType id,
                                                const PduInfoType * ptr)
{
    PduR_rCanIfRxIndication((id), (ptr));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

