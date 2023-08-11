#include "CanIf_Prv.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
boolean CanIf_Lok_InitStatus_b;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

CanIf_ControllerStateType CanIf_Lok_ControllerState_ast[CANIF_TOTAL_CTRLS];

