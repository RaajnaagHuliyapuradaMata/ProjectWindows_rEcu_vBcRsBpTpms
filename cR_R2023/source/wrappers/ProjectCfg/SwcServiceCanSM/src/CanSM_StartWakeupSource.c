

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_StartWakeupSource(VAR(NetworkHandleType, AUTOMATIC) network)
{
	
	VAR(Std_ReturnType, AUTOMATIC) stFuncVal;
	
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
	
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORMode_en;

    stFuncVal = E_NOT_OK;

	
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_STARTWAKEUPVALIDATION_SID),
                           ((uint8)CANSM_E_UNINIT))

	
    network = CanSM_GetHandle(network);

	
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_STARTWAKEUPVALIDATION_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];
    CanSM_CurrBORMode_en = CanSM_currBOR_State_en[network];
	
	if((CanSM_Network_Init_ab[network] == TRUE) && ((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) || (CanSM_CurrNwMode_en == CANSM_BSM_S_NOCOM)) && ((CanSM_CurrBORMode_en == CANSM_BOR_IDLE) || (CanSM_CurrBORMode_en == CANSM_S_NO_BUS_OFF)))
		{
			
			CanSM_Wuvalidation_Start_ab[network] = TRUE;

			
			CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;

			
			CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

			stFuncVal = E_OK;
		}

    return stFuncVal;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
