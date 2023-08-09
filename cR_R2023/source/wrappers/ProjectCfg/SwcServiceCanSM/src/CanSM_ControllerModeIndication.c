

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(VAR(uint8, AUTOMATIC) ControllerId,VAR(CanIf_ControllerModeType,AUTOMATIC) ControllerMode)
{

    VAR(uint8, AUTOMATIC) network_indx_u8;

    VAR(uint8_least, AUTOMATIC) CanSM_ControllerId_u8;

    VAR(uint8_least, AUTOMATIC) CanSM_Ctrl_index_u8;

    VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8;

    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;

    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurNwMode_Temp_uo;
    #endif

    CanSM_Controller_Counter_u8 =  CANSM_ZERO;

    CANSM_REPORT_ERROR((ControllerId >= CANSM_NUM_CAN_CONTROLLERS),
                       (uint8)CANSM_CTRLMODEINDICATION_SID,
                       (uint8)CANSM_E_PARAM_CONTROLLER)

    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_CTRLMODEINDICATION_SID),
                           ((uint8)CANSM_E_UNINIT)
                           )

    (void)ControllerMode;

    network_indx_u8 = (uint8)CanSM_ConfigSet_pcst->CanSM_NetworktoCtrlConf_pcu8[ControllerId];

    CanSM_NetworkConf_ps = &CanSM_Network_pcst[network_indx_u8];

    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)

    CurNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_u8];
    #endif

    CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurNwMode_Temp_uo),
                           ((uint8)CANSM_CTRLMODEINDICATION_SID),
                           ((uint8)CANSM_E_UNINIT)
                           )

    CanSM_ControllerIndications_ab[ControllerId] = TRUE;

    if(CanSM_NetworkConf_ps->SizeofController_u8 > 1u)
    {

        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {

            CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

            if(CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] == TRUE)
            {
                CanSM_Controller_Counter_u8++ ;
            }
        }
        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
        {

            CanSM_Ctrl_ModeInd_ab[network_indx_u8] = TRUE;

            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
            {

                CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

                CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] = FALSE;
            }
        }
    }
    else
    {

        CanSM_Ctrl_ModeInd_ab[network_indx_u8] = TRUE;

        CanSM_ControllerIndications_ab[ControllerId] = FALSE;
    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
