
#ifndef CANTP_CBK_H
#define CANTP_CBK_H

#include "CanTp_Cfg.hpp"
#if(CANTP_VARIANT != CANTP_PRE_COMPILE)
#include "CanTp_PBcfg.hpp"
#endif

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.hpp"

extern void CanTp_TxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId);
extern void CanTp_RxIndication(Type_SwcServiceCom_tIdPdu RxPduId, const Type_SwcServiceCom_stInfoPdu *PduInfoPtr);
#if(CANTP_TRIGGER_TRANSMIT_API == STD_ON)
extern Std_ReturnType CanTp_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu *PduInfoPtr);
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.hpp"

#endif
