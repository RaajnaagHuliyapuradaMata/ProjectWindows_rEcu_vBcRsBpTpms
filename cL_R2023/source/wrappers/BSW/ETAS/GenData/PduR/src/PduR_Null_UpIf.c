
#include "PduR_Prv.h"

#if defined(PDUR_J1939RM_SUPPORT) && (PDUR_J1939RM_SUPPORT != 0)
#include "PduR_J1939Rm.h"
#include "PduR_J1939Rm_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if (AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_null_J1939RmTxConfirmation( PduIdType id )
#else

void PduR_null_J1939RmTxConfirmation( PduIdType id , Std_ReturnType result)
#endif
{

    (void)id;
    #if (AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
    #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

