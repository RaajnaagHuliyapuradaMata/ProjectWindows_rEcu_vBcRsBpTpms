

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)
#include "PduR_Com.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_Com_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    Com_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)
#include "PduR_IpduM.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_IpduM_Transmit_Func(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    IpduM_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_SECOC_SUPPORT) && (PDUR_SECOC_SUPPORT != 0)
#include "PduR_SecOC.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_SecOC_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    SecOC_RxIndication(id, info);
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif
#endif

