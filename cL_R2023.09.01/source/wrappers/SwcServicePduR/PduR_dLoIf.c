

#include "PduR_Prv.hpp"

#include "PduR_Cfg.hpp"

#include "PduR_LoIf.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_CanIfTxConfirmation( PduIdType id )
{
   PduR_rCanIfTxConfirmation( id );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_CanIfRxIndication( PduIdType id
   ,                                               const PduInfoType * ptr)
{
   PduR_rCanIfRxIndication((id), (ptr));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

