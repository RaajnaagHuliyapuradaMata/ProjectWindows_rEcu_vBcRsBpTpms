

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_NF_TriggerTransmit_Func( PduIdType id
   ,                                                     PduInfoType * data)
{

    (void)id;
    (void)data;

    return E_NOT_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

