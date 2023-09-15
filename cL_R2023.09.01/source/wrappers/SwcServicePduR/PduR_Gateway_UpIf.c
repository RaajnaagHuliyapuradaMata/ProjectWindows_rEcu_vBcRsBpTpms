

#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"

#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)
#include "PduR_Com.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_Com_Transmit_Func( PduIdType id, const PduInfoType * info)
{
   Com_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)
#include "PduR_IpduM.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_IpduM_Transmit_Func(PduIdType id, const PduInfoType * info)
{
    IpduM_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

#if defined(PDUR_SECOC_SUPPORT) && (PDUR_SECOC_SUPPORT != 0)
#include "PduR_SecOC.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_SecOC_Transmit_Func( PduIdType id, const PduInfoType * info)
{
    SecOC_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif
#endif

