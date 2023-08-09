

#include "CanSM_Prv.h"

#if (CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetBaudrate(VAR(NetworkHandleType, AUTOMATIC) Network,CONST(uint16,AUTOMATIC) BaudRateConfigID)

{

    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

	VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
	
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
	
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;

	CanSM_FuncVal_uo = E_NOT_OK;

	
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_SETBAUDRATE_SID),
                           ((uint8)CANSM_E_UNINIT))

	Network = CanSM_GetHandle(Network);

    CANSM_REPORT_ERROR_NOK(((uint8)Network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                            ((uint8)CANSM_SETBAUDRATE_SID),
                            ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))

    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[Network];
    CanSM_CurrBORState_en = CanSM_currBOR_State_en[Network];

   	
    if(CanSM_Network_Init_ab[Network] == TRUE)
		{
			
			if(CanSM_CurrNwMode_en != CANSM_BSM_S_CHANGE_BAUDRATE)
				{

				
					if((CanSM_CurrNwMode_en == CANSM_BSM_S_FULLCOM) && (CanSM_CurrBORState_en == CANSM_S_NO_BUS_OFF) && (BaudRateConfigID != (uint16)0xFFFFu) )
						{

	
	                        CanSM_BaudRateConfigID_Value_au16[Network] = BaudRateConfigID;

					
					        CanSM_FuncVal_uo = E_OK;

							
							CanSM_CurrNw_Mode_en[Network]=CANSM_BSM_S_CHANGE_BAUDRATE;

							
							CanSM_ChangeBR_Substates_en[Network] = CANSM_BSM_CHANGE_BR_SYNC;

						
							CanSM_BswM_Mode_en = CANSM_BSWM_CHANGE_BAUDRATE;

							
							BswM_CanSM_CurrentState(CanSM_Network_pcst[Network].ComM_channelId_uo,CanSM_BswM_Mode_en);

						}
				}
		}
	else
		{
	        CanSM_FuncVal_uo = E_NOT_OK;
		}
    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
