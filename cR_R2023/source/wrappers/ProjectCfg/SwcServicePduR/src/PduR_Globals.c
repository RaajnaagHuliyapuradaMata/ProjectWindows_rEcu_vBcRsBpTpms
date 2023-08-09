

#include "PduR_Prv.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

P2CONST(PduR_PBConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Base;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

VAR(PduR_StateType, PDUR_VAR) PduR_State;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#if (PDUR_DSM_REINT_SUPPORT != STD_OFF)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

VAR(PduR_DsmReInitType, PDUR_VAR) PduR_DsmReInitStruct;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
#endif

