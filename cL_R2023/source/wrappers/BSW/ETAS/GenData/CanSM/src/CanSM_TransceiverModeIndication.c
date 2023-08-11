

#include "CanSM_Prv.h"

#if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
void CanSM_TransceiverModeIndication(uint8 TransceiverId,CanTrcv_TrcvModeType TransceiverMode)
{

	uint8_least network_indx_uo;
	#if (CANSM_DEV_ERROR_DETECT != STD_OFF)
	
    boolean CanSM_TrcvConfigd_b;
	#endif
    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

    CanSM_NetworkModeStateType_ten CurNwMode_Temp_uo;
    #endif

    CanSM_ReqCanTrcv_States  CanSM_CanTrcvState_en;

    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

	CanSM_TrcvConfigd_b = FALSE;
    #endif
	
	(void)TransceiverMode;
	
		
	CanSM_CanTrcvState_en = CANSM_CANTRCV_DEFAULT;

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

                    if(TransceiverMode == CANTRCV_TRCVMODE_NORMAL)
                    {
                        CanSM_CanTrcvState_en = CANSM_CANTRCV_NORMAL;
                    }
                    else if(TransceiverMode == CANTRCV_TRCVMODE_SLEEP)
                    {
                        CanSM_CanTrcvState_en = CANSM_CANTRCV_SLEEP;
                    }
                    else if(TransceiverMode == CANTRCV_TRCVMODE_STANDBY)
                    {
                        CanSM_CanTrcvState_en = CANSM_CANTRCV_STANDBY;
                    }
                    else
                    {

                    }

                    if((CanSM_ReqMode_a[network_indx_uo]== CanSM_CanTrcvState_en) && (CanSM_ModeChangeReq_flag[network_indx_uo] == TRUE))
                    {

                        CanSM_Trcv_ModeInd_ab[network_indx_uo]=TRUE;
                        CanSM_ModeChangeReq_flag[network_indx_uo] = FALSE;
                    }
                    else
                    {

                    }

                    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)
                    CanSM_TrcvConfigd_b = TRUE;
                    #endif
                    break;
                }
        }

        CANSM_REPORT_ERROR(CanSM_TrcvConfigd_b == FALSE, (uint8)CANSM_TRCVMODEINDICATION_SID,
                (uint8)CANSM_E_PARAM_TRANSCEIVER)
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
