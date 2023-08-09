
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_GF_TTIf_Buf_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId )
{
    (void)gwayId;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

