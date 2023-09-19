#ifndef CANIF_CBK_H
#define CANIF_CBK_H

#include "CanIf_Integration.hpp"

extern FUNC(void, CANIF_CODE) CanIf_RxIndication_Internal(P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_DATA)PduInfoPtr);

extern FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication( VAR(uint8,AUTOMATIC) TransceiverId
   ,     VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode);

FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication( VAR(uint8,AUTOMATIC) TransceiverId);

FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication( VAR(uint8,AUTOMATIC) TransceiverId);

FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability( VAR(uint8,AUTOMATIC) TransceiverId);

extern FUNC(void, CANIF_CODE) CanIf_TxConfirmation(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanTxPduId );

extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu* PduInfoPtr);

extern FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(VAR(uint8,AUTOMATIC) ControllerId );

extern FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication_Internal(
      VAR(uint8,                    AUTOMATIC) ControllerId
   ,  VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
);

extern FUNC(void, CANIF_CODE) CanIf_ControllerErrorPassive( VAR(uint8, AUTOMATIC) ControllerId);

#endif

