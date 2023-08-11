

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
Std_ReturnType CanSM_StopWakeupSource(NetworkHandleType network)
{
	
	Std_ReturnType stFuncVal;
	
	CanSM_NetworkModeStateType_ten CanSM_CurrNwMode_en;

    stFuncVal = E_NOT_OK;

	
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_STOPWAKEUPVALIDATION_SID),
                           ((uint8)CANSM_E_UNINIT))

	
    network = CanSM_GetHandle(network);

	
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_STOPWAKEUPVALIDATION_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

	CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

	
    if(( CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_Network_Init_ab[network] == TRUE))
		{
			stFuncVal = E_OK;
			
			CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
			
			CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

			
	if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
		{
			#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE)
				{
					
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
				}
			else
				{
					
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
				}
			#else
			
			CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
			#endif
		}
	else
		{
			
			CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
		}
	}

    return stFuncVal;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
