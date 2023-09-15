

#include "PduR_Prv.hpp"
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

#if(AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_GF_DDIf_NoBuf_TxConfirmation_Func(PduIdType gwayId)
#else

void PduR_GF_DDIf_NoBuf_TxConfirmation_Func(PduIdType gwayId,Std_ReturnType result)
#endif
{

    (void)gwayId;
   #if(AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

