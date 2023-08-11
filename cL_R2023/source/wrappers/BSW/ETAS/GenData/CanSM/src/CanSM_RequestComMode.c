

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
Std_ReturnType CanSM_RequestComMode( NetworkHandleType network,ComM_ModeType ComM_Mode )
{

    Std_ReturnType CanSM_FuncVal_uo;

    CanSM_NetworkModeStateType_ten CanSM_CurrNwMode_en;

    CanSM_BusOffRecoveryStateType_ten CanSM_CurrBORState_en;

    #if(CANSM_SET_BAUDRATE_API == STD_ON)

    CanSM_ChangeBR_Substates_ten CanSM_ChangeBR_State_en;
    #endif

    CanSM_TxTimeoutException_Substates_ten CanSM_TxToutException_state_en;

    CanSM_FuncVal_uo = E_OK;

    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_REQUESTCOMMODE_SID),
                           ((uint8)CANSM_E_UNINIT))

    network = CanSM_GetHandle(network);

    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_REQUESTCOMMODE_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

    CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];

    #if(CANSM_SET_BAUDRATE_API == STD_ON)

    CanSM_ChangeBR_State_en = CanSM_ChangeBR_Substates_en[network];
    #endif

    CanSM_TxToutException_state_en = CanSM_TxTimeoutexception_Substates_en[network];

    if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM)&&(ComM_Mode == COMM_NO_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
          (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
          #if(CANSM_SET_BAUDRATE_API == STD_ON)
          (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
          #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION ;

                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

            }

        else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM)&&(ComM_Mode == COMM_NO_COMMUNICATION )&&
              (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
              (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
              (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
              (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
              (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
              #if(CANSM_SET_BAUDRATE_API == STD_ON)
              ((CanSM_ChangeBR_State_en == CANSM_BR_S_CC_STARTED_WAIT)) &&
              #endif
              (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
             )
                {

                    CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION ;

                }

    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM)&&
          (ComM_Mode == COMM_SILENT_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
          (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
          #if(CANSM_SET_BAUDRATE_API == STD_ON)
          ((CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT) || (CanSM_ChangeBR_State_en == CANSM_BR_S_CC_STARTED_WAIT))&&
            #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {

                CanSM_ReqComM_Mode_en[network] = COMM_SILENT_COMMUNICATION ;

            }

    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_SILENTCOM)&&
          (ComM_Mode == COMM_NO_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
          (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
            #if(CANSM_SET_BAUDRATE_API == STD_ON)
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION ;

                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
            }
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en== CANSM_BSM_S_SILENTCOM)&&
            (ComM_Mode == COMM_FULL_COMMUNICATION )&&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
            #if(CANSM_SET_BAUDRATE_API == STD_ON)
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
            (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
           )
                {

                    CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;
                }
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en== CANSM_BSM_S_NOCOM)&&
            (ComM_Mode == COMM_FULL_COMMUNICATION )&&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            (CanSM_BusOff_Indicated_ab[network]!= TRUE)&&
            #if(CANSM_SET_BAUDRATE_API == STD_ON)
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
            (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
           )
                {

                    CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;

                    CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_FULLCOM;
                }
		
    else if((CanSM_Network_Init_ab[network] == TRUE) && (CanSM_CurrNwMode_en==CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_DEFAULT) &&
               (ComM_Mode == COMM_FULL_COMMUNICATION ))
       {

           CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;

		
           CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_FULLCOM;

       }

    else if((CanSM_Network_Init_ab[network] == TRUE)&&(CanSM_CurrNwMode_en!=CANSM_BSM_S_PRE_FULLCOM) &&
             (CanSM_CurrNwMode_en!=CANSM_BSM_S_PRE_NOCOM)&&
             (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
             (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
             (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
             (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
             (CanSM_BusOff_Indicated_ab[network]!= TRUE)    &&
            #if(CANSM_SET_BAUDRATE_API == STD_ON)
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
                         (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
            )
                {

                    CanSM_ReqComM_Mode_en[network] = ComM_Mode ;
                }
    else
        {

            CanSM_FuncVal_uo = E_NOT_OK;

        }

    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

