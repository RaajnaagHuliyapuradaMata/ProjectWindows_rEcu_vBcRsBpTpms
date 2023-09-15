
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "CanIf_Integration.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"

FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerMode_Integration( uint8 Controller, Can_StateTransitionType Transition)
{
   Can_ReturnType retVal = CAN_NOT_OK;

#if(CANIF_SETCONTROLLERMODE_INTEGRATION_VERSION > 2)
   Can_ControllerStateType requestedState;

   switch(Transition)
   {
        case CAN_T_START:
            requestedState = CAN_CS_STARTED;
            break;
        case CAN_T_STOP:
            requestedState = CAN_CS_STOPPED;
            break;
        case CAN_T_SLEEP:
            requestedState = CAN_CS_SLEEP;
            break;
        case CAN_T_WAKEUP:
            requestedState = CAN_CS_STOPPED;
            break;
        default: //CAN_T_MAXTRANSITION is not used by CanIf anywhere.
            requestedState = CAN_CS_UNINIT;
   }
    // enum definition of Can_ReturnType are of the same value and meaning with Std_ReturnType.
    // typecast to Can_ReturnType makes no change in term of meaning and functionality.
    retVal = (Can_ReturnType)Can_SetControllerMode(Controller, requestedState);
#elif(CANIF_SETCONTROLLERMODE_INTEGRATION_VERSION <= 2)
    retVal = Can_SetControllerMode(Controller, Transition);
#endif

    return retVal;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
