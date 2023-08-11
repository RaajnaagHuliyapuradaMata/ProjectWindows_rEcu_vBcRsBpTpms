

#include "CanSM_Prv.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

void CanSM_CheckTransceiverWakeFlagIndication(uint8 Transceiver)
{

	uint8 CanSM_network_indx_uo;
    boolean CanSM_st_TrcvConfigd;
	CanSM_NetworkModeStateType_ten CurrNwMode_Temp_uo;

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

        CANSM_REPORT_ERROR(CanSM_st_TrcvConfigd == FALSE,(uint8)CANSM_CHECKTRCVWAKEFLAGIND_SID,
                (uint8)CANSM_E_PARAM_TRANSCEIVER)
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
