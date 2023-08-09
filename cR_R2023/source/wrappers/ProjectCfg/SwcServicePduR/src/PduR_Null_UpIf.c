
#include "PduR_Prv.h"

#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)
#include "PduR_Com.h"
#include "PduR_Com_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_null_ComTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id )
{

    (void)id;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)
#include "PduR_IpduM.h"
#include "PduR_IpduM_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_null_IpduMTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id )
{

    (void)id;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

