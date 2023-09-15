

#ifndef CANIF_CBK_H
#define CANIF_CBK_H

// #include "CanIf_Cfg.hpp"
#include "CanIf_RxIndication_Integration.hpp"

//#if CANIF_CFG_NUM_CANRXPDUIDS != CANIF_ZERO
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_RxIndication_Internal(P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_DATA)PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
//#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication( VAR(uint8,AUTOMATIC) TransceiverId
   ,     VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication( VAR(uint8,AUTOMATIC) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication( VAR(uint8,AUTOMATIC) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability( VAR(uint8,AUTOMATIC) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_TxConfirmation(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanTxPduId );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu* PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(VAR(uint8,AUTOMATIC) ControllerId );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication( VAR(uint8,AUTOMATIC) ControllerId
   ,     VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_ControllerErrorPassive( VAR(uint8, AUTOMATIC) ControllerId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif

