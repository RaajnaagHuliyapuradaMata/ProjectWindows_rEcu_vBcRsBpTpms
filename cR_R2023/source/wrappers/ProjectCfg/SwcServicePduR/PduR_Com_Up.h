
#ifndef PDUR_COM_UP_H
#define PDUR_COM_UP_H

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)

#define PduR_iComTransmitID(id)           (id)

#define PduR_iComTransmitFunc(id)           (PDUR_CONFIG_SINGLE_IFTX_LO(Transmit))

#else

#define PduR_iComTransmitID(id)           (PDUR_COM_TX_BASE[(id)].loId)

#define PduR_iComTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_COM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

 #define PduR_rComTransmit(id, ptr)        PduR_dComTransmit((id), (ptr))
#else

 #define PduR_rComTransmit(id, ptr)        PduR_iComTransmitFunc(id)(PduR_iComTransmitID(id), (ptr))
#endif

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_Com_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

extern FUNC( void, PDUR_CODE ) PduR_null_ComTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id);

#define PDUR_IH_Com_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

