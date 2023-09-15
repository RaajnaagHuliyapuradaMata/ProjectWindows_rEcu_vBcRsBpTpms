

#include "PduR_Prv.hpp"

#include "PduR_UpIf.hpp"

#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT == 1)
#include "PduR_Mc.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_ComTransmit( PduIdType id, const PduInfoType * ptr)
{
    return ((Std_ReturnType)PduR_rComTransmit( (id) , (ptr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

