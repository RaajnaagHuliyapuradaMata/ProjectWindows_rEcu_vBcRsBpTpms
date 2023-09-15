#ifndef CANIF_INTEGRATION_H
#define CANIF_INTEGRATION_H


#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
 //::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define CANIF_RX_INDICATION_VERSION (2U)
#define CANIF_WRITE_INTEGRATION_VERSION (2U)
#define CANIF_CONTROLLERMODEINDICATION_VERSION (2U)
#define CANIF_SETCONTROLLERMODE_INTEGRATION_VERSION (2U)

#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
#if(CANIF_RX_INDICATION_VERSION < 1)
extern FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                                 VAR(Can_HwHandleType, AUTOMATIC) Hrh
   ,                                                VAR(Can_IdType, AUTOMATIC) CanId
   ,                                                VAR(uint8, AUTOMATIC) CanDlc
   ,                                                P2CONST (uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
                                                );
#elif(CANIF_RX_INDICATION_VERSION >= 1)
extern FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                            P2CONST (Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,                                           P2CONST (PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
                                         );
#endif

extern Can_ReturnType CanIf_Write_Integration(Can_HwHandleType Hth,const Can_PduType* PduInfoPtr);

#if(CANIF_CONTROLLERMODEINDICATION_VERSION > 2)
extern void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode);
#elif(CANIF_CONTROLLERMODEINDICATION_VERSION <= 2)
extern void CanIf_ControllerModeIndication( uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
#endif

extern FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerMode_Integration( uint8 Controller, Can_StateTransitionType Transition);

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif
