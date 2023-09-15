
#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

#if(AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_GF_TTIf_Buf_TxConfirmation_Func( Type_SwcServiceCom_tIdPdu gwayId )
#else

void PduR_GF_TTIf_Buf_TxConfirmation_Func( Type_SwcServiceCom_tIdPdu gwayId,Std_ReturnType result)
#endif
{
    (void)gwayId;
#if(AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

