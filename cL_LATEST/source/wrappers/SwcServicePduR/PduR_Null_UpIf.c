
#include "PduR_Prv.hpp"

#if defined(PDUR_J1939RM_SUPPORT) && (PDUR_J1939RM_SUPPORT != 0)
#include "PduR_J1939Rm.hpp"
#include "PduR_J1939Rm_Up.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

#if(AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_null_J1939RmTxConfirmation( Type_SwcServiceCom_tIdPdu id )
#else

void PduR_null_J1939RmTxConfirmation( Type_SwcServiceCom_tIdPdu id , Std_ReturnType result)
#endif
{

    (void)id;
#if(AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

