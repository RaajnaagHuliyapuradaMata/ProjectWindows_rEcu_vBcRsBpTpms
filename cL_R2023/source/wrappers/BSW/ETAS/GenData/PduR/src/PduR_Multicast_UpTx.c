

#include "PduR_Prv.h"
#include "PduR_Mc.h"
#include "PduR_Gw.h"

#if defined(PDUR_DCM_SUPPORT) && (PDUR_DCM_SUPPORT != 0)

#include "PduR_Dcm.h"
#include "PduR_Dcm_Up.h"
#endif

#if defined(PDUR_DLT_SUPPORT) && (PDUR_DLT_SUPPORT != 0)
#include "PduR_Dlt.h"
#include "PduR_Dlt_Up.h"
#endif

#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)

#include "PduR_Com.h"
#include "PduR_Com_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_Com_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_COM_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

#if defined(PDUR_MULTICAST_TO_TP_SUPPORT) && (PDUR_MULTICAST_TO_TP_SUPPORT != 0)

#if defined(PDUR_DCM_SUPPORT) && (PDUR_DCM_SUPPORT != 0)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_Dcm_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_DCM_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_DLT_SUPPORT) && (PDUR_DLT_SUPPORT != 0)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_Dlt_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_DLT_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_GwMcTx_Transmit_Func(PduIdType id, const PduInfoType * info)
{
    return PduR_MF_UpToLo(PDUR_GW_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)

#include "PduR_IpduM.h"
#include "PduR_IpduM_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_IpduM_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_IPDUM_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_SECOC_SUPPORT) && (PDUR_SECOC_SUPPORT != 0)

#include "PduR_SECOC.h"
#include "PduR_SECOC_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_SecOC_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_SECOC_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_LDCOM_SUPPORT) && (PDUR_LDCOM_SUPPORT != 0)

#include "PduR_LDCOM.h"
#include "PduR_LDCOM_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_LdCom_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_LDCOM_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

#if defined(PDUR_J1939DCM_SUPPORT) && (PDUR_J1939DCM_SUPPORT != 0)

#include "PduR_J1939DCM.h"
#include "PduR_J1939DCM_Up.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_MF_J1939Dcm_Transmit_Func( PduIdType id, const PduInfoType * info )
{
    return PduR_MF_UpToLo(PDUR_J1939DCM_MC_TX_BASE, id, info);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

