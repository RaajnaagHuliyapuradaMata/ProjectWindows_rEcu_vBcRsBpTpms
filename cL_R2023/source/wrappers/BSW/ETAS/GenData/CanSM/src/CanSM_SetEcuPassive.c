

#include "CanSM_Prv.h"

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
Std_ReturnType CanSM_SetEcuPassive(boolean CanSM_Passive)
{
	
	Std_ReturnType stFuncVal;

	
	uint8 CanSM_NetworkIdx_u8;
	
    const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;
	
	uint8 CanSM_ControllerId_u8 = 0;
	
	uint8 CanSM_Ctrl_index_u8;
	
	CanSM_Network_pcst = CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst;

	stFuncVal = E_NOT_OK;

    CanSM_Passive_b =  CanSM_Passive;

	
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),((uint8)CANSM_ECUPASSIVE_SID),((uint8)CANSM_E_UNINIT))

	
	for(CanSM_NetworkIdx_u8 =0; CanSM_NetworkIdx_u8 < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; CanSM_NetworkIdx_u8++)
		{
			if(CanSM_Network_Init_ab[CanSM_NetworkIdx_u8] == TRUE)
				{
					
					CanSM_NetworkConf_ps = &CanSM_Network_pcst[CanSM_NetworkIdx_u8];
					
					for(CanSM_Ctrl_index_u8 =0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ; CanSM_Ctrl_index_u8++)
						{
							
							CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
							
							if(CanSM_Passive_b == TRUE)
								{
									
							
									(void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_TX_OFFLINE_ACTIVE));
								}
							else
								{
									
							
									(void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
								}
								
							stFuncVal = E_OK;
						}
				}
			else
				{
					break;
				}
		}

    return stFuncVal;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
