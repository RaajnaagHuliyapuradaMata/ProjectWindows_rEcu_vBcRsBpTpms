

#include "CanSM_Prv.h"

#if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8, AUTOMATIC) TransceiverId,VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode)
{

	VAR(uint8_least, AUTOMATIC)  network_indx_uo;

	
    VAR(boolean, AUTOMATIC)  CanSM_TrcvConfigd_b;

    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurNwMode_Temp_uo;
    #endif

	CanSM_TrcvConfigd_b = FALSE;

	
	(void)TransceiverMode;

    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED ),
                           ((uint8)CANSM_TRCVMODEINDICATION_SID),
                           ((uint8)CANSM_E_UNINIT)
                          )

	for(network_indx_uo =0; network_indx_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; network_indx_uo++)
        {

            if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8==TransceiverId)
                {
                    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

                    CurNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
                    #endif

                    CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurNwMode_Temp_uo),
                                       ((uint8)CANSM_TRCVMODEINDICATION_SID),
                                       ((uint8)CANSM_E_UNINIT))

                    CanSM_Trcv_ModeInd_ab[network_indx_uo] = TRUE;

                    CanSM_TrcvConfigd_b = TRUE;
                    break;
                }
        }

    if(CanSM_TrcvConfigd_b == FALSE)
    {

        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,
                           (uint8)CANSM_TRCVMODEINDICATION_SID,
                           (uint8)CANSM_E_PARAM_TRANSCEIVER
                           )

    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
