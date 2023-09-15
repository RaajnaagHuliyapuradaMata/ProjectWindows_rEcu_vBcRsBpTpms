#ifndef PDUR_DCM_UP_H
#define PDUR_DCM_UP_H

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
#define PduR_iDcmTransmitID(id)           (PDUR_DCM_TX_BASE[(id)].loId)
#define PduR_iDcmTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_DCM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)
#define PduR_aDcmTransmit(id, ptr) PduR_iDcmTransmitFunc(id)(PduR_iDcmTransmitID(id), (ptr))
#define PduR_rDcmTransmit(id, ptr)                PduR_aDcmTransmit((id), (ptr))
#define PDUR_IH_Dcm_Transmit_Func            PDUR_DET_API(PduR_invId_UpTransmit)

extern Std_ReturnType PduR_MF_Dcm_Transmit_Func(
   PduIdType id,
   const PduInfoType* info);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

