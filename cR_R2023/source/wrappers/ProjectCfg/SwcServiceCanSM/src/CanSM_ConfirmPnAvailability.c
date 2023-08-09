

#include "CanSM_Prv.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8, AUTOMATIC) TransceiverId)
{

	VAR(uint8_least, AUTOMATIC) network_indx_uo;
    VAR(boolean, AUTOMATIC) CanSM_TrcvConfigd_b;
	VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurrNwMode_Temp_uo;
	VAR(uint8, AUTOMATIC) CanSM_networkHandle_u8;

	CanSM_TrcvConfigd_b = FALSE;

	
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED),((uint8)CANSM_CONFIRMPNAVAILABILITY_SID),((uint8)CANSM_E_UNINIT))

	for(network_indx_uo =0; network_indx_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; network_indx_uo++)
    {
	    CurrNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
		
        if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8 == TransceiverId)
        {

            CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurrNwMode_Temp_uo),
                               ((uint8)CANSM_CONFIRMPNAVAILABILITY_SID),
                               ((uint8)CANSM_E_UNINIT)
                               )

        CanSM_TrcvConfigd_b = TRUE;

            CanSM_networkHandle_u8 = CanSM_Network_pcst[network_indx_uo].ComM_channelId_uo;

            CanNm_ConfirmPnAvailability((NetworkHandleType)CanSM_networkHandle_u8);

            break;
        }

    }

    if(CanSM_TrcvConfigd_b == FALSE)
    {

        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,(uint8)CANSM_CONFIRMPNAVAILABILITY_SID, (uint8)CANSM_E_PARAM_TRANSCEIVER)

    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
