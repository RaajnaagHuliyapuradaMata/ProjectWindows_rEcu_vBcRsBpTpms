#ifndef CANIF_INTEGRATION_H
#define CANIF_INTEGRATION_H

#define CANIF_WRITE_INTEGRATION_VERSION (2U)
#define CANIF_CONTROLLERMODEINDICATION_VERSION (2U)
#define CANIF_SETCONTROLLERMODE_INTEGRATION_VERSION (2U)

#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"

extern Can_ReturnType CanIf_Write_Integration(Can_HwHandleType Hth,const Can_PduType* PduInfoPtr);
extern void CanIf_ControllerModeIndication( uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
extern FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerMode_Integration( uint8 Controller, Can_StateTransitionType Transition);


#endif
