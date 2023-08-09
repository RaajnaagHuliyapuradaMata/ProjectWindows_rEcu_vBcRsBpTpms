
#ifndef CANTP_CBK_H
#define CANTP_CBK_H

#include "CanTp_Cfg.h"
#if(CANTP_VARIANT != CANTP_PRE_COMPILE)
#include "CanTp_PBcfg.h"
#endif

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

extern void CanTp_TxConfirmation(PduIdType TxPduId);
extern void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
#if(CANTP_TRIGGER_TRANSMIT_API == STD_ON)
extern Std_ReturnType CanTp_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr);
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"

#endif
