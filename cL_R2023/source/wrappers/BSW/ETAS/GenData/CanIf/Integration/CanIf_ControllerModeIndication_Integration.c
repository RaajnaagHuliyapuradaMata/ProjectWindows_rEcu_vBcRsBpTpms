
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Std_Types.h"
#include "CanIf_Cbk.h"
#include "CanIf_Integration.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

#if(CANIF_CONTROLLERMODEINDICATION_VERSION > 2)
void CanIf_ControllerModeIndication( uint8 ControllerId,
        Can_ControllerStateType ControllerMode )
{
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode_tmp = CANIF_CS_UNINIT;

    switch (ControllerMode)
    {
        case CAN_CS_SLEEP:
            ControllerMode_tmp = CANIF_CS_SLEEP;
            break;
        case CAN_CS_STARTED:
            ControllerMode_tmp = CANIF_CS_STARTED;
            break;
        case CAN_CS_STOPPED:
            ControllerMode_tmp = CANIF_CS_STOPPED;
            break;
        case CAN_CS_UNINIT:
            ControllerMode_tmp = CANIF_CS_UNINIT;
            break;
        default:
            break;
    }

    CanIf_ControllerModeIndication_Internal(ControllerId, ControllerMode_tmp);

#elif(CANIF_CONTROLLERMODEINDICATION_VERSION <= 2)
void CanIf_ControllerModeIndication( uint8 ControllerId,
        CanIf_ControllerModeType ControllerMode )
{

    CanIf_ControllerModeIndication_Internal(ControllerId, ControllerMode);
#endif
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

