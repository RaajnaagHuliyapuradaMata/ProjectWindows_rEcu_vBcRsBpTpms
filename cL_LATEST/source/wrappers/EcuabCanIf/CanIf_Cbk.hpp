#ifndef CANIF_CBK_H
#define CANIF_CBK_H

#include "CanIf_Integration.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_RxIndication_Internal(const Can_HwType * Mailbox
   ,       const Type_SwcServiceCom_stInfoPdu * PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_TrcvModeIndication( uint8 TransceiverId
   ,       CanTrcv_TrcvModeType TransceiverMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_ClearTrcvWufFlagIndication( uint8 TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_CheckTrcvWakeFlagIndication( uint8 TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_ConfirmPnAvailability( uint8 TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_TxConfirmation(Type_SwcServiceCom_tIdPdu CanTxPduId );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu* PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_ControllerBusOff(uint8 ControllerId );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_ControllerModeIndication_Internal( uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_ControllerErrorPassive( uint8 ControllerId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif

