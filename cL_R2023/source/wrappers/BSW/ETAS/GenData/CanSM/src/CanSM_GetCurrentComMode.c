

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
Std_ReturnType CanSM_GetCurrentComMode( NetworkHandleType network,ComM_ModeType * ComM_ModePtr )
{
    Std_ReturnType stFuncVal;
    boolean CanSM_NwInitStatus_b;

    stFuncVal = E_NOT_OK;

	
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           (uint8)CANSM_GETCURRENTCOMMODE_SID,
                           (uint8)CANSM_E_UNINIT)

    network = CanSM_GetHandle(network);

    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                                                    (uint8)CANSM_GETCURRENTCOMMODE_SID,
                                                    (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

    CANSM_REPORT_ERROR_NOK((ComM_ModePtr == NULL_PTR),
                           (uint8)CANSM_GETCURRENTCOMMODE_SID,
                           (uint8)CANSM_E_PARAM_POINTER)

    CanSM_NwInitStatus_b =  CanSM_Network_Init_ab[network];

    if((CanSM_Init_ab == (boolean)CANSM_INITED) && (CanSM_NwInitStatus_b != FALSE))
    {

         *ComM_ModePtr = CanSM_BusSMMode_au8[network];

         stFuncVal = E_OK;
    }

    return(stFuncVal);
}

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
