

#include "CanSM_Prv.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

FUNC(void, CANSM_CODE) CanSM_CheckTransceiverWakeFlagIndication(VAR(uint8, AUTOMATIC) Transceiver)
{

	VAR(uint8, AUTOMATIC) CanSM_network_indx_uo;
    VAR(boolean, AUTOMATIC) CanSM_st_TrcvConfigd;
	VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurrNwMode_Temp_uo;

    CanSM_st_TrcvConfigd = FALSE;

	
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED ),
                           ((uint8)CANSM_CHECKTRCVWAKEFLAGIND_SID),
                           ((uint8)CANSM_E_UNINIT)
                          )

	for(CanSM_network_indx_uo =0; CanSM_network_indx_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; CanSM_network_indx_uo++)

    {
	    CurrNwMode_Temp_uo = CanSM_CurrNw_Mode_en[CanSM_network_indx_uo];
		
        if(CanSM_Network_pcst[CanSM_network_indx_uo].Trcv_hndle_u8 == Transceiver)
        {

            CANSM_REPORT_ERROR((CurrNwMode_Temp_uo == CANSM_BSM_S_NOT_INITIALIZED),
                               ((uint8)CANSM_CHECKTRCVWAKEFLAGIND_SID),
                               ((uint8)CANSM_E_UNINIT)
                               )

            CanSM_PN_Substate_Ind_ab[CanSM_network_indx_uo] = TRUE;

			CanSM_st_TrcvConfigd = TRUE;
            break;
        }
    }

    if(CanSM_st_TrcvConfigd == FALSE)
    {

        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,(uint8)CANSM_CHECKTRCVWAKEFLAGIND_SID,
                (uint8)CANSM_E_PARAM_TRANSCEIVER)

    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
