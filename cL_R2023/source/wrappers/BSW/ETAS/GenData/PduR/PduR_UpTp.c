

#include "PduR_Prv.h"
#include "PduR_Cfg.h"

#include "PduR_UpTp.h"

#include "PduR_Dcm.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_DcmTransmit( PduIdType id, const PduInfoType * ptr)
{
    return (PduR_rDcmTransmit( (id) , (ptr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

