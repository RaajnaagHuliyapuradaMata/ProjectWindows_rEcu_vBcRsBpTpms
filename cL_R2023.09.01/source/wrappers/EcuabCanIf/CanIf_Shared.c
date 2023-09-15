#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"
boolean CanIf_Lok_InitStatus_b;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"

CanIf_ControllerStateType CanIf_Lok_ControllerState_ast[CANIF_TOTAL_CTRLS];

