#ifndef CANIF_INTEGRATION_H
#define CANIF_INTEGRATION_H

#define CANIF_WRITE_INTEGRATION_VERSION (2U)
#define CANIF_CONTROLLERMODEINDICATION_VERSION (2U)
#define CANIF_SETCONTROLLERMODE_INTEGRATION_VERSION (2U)

#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"

extern Type_McalCan_eReturn CanIf_Write_Integration(Type_McalCan_tHandleHw Hth,const Type_McalCan_stPdu* PduInfoPtr);
extern void CanIf_ControllerModeIndication( uint8 ControllerId, Type_EcuabCanIf_eModeController ControllerMode);
extern FUNC(Type_McalCan_eReturn, CANIF_CODE) CanIf_SetControllerMode_Integration( uint8 Controller, Type_McalCan_eStateTransition Transition);


#endif
