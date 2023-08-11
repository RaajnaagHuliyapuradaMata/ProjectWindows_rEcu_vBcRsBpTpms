

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_invId_IfRxIndication(PduIdType id, const PduInfoType * ptr)
{

    (void)id;
    (void)ptr;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_invId_IfTriggerTransmit( PduIdType id, PduInfoType * data )
{

    (void)id;
    (void)data;
    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
 #include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if (AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_invId_IfTxConfirmation( PduIdType id)
#else

void PduR_invId_IfTxConfirmation( PduIdType id, Std_ReturnType result)
#endif
{

    (void)id;
    #if (AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
    #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

