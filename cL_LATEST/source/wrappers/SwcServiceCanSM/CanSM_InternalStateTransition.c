

#include "CanSM_Prv.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
NetworkHandleType CanSM_GetHandle(NetworkHandleType ComMChannelId)
{

   uint8 loop_uo;

   uint8 CanSM_NetworkIdx_u8 = CANSM_ZERO;

   for(loop_uo =0; loop_uo < CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; loop_uo++)
   {

   	if(CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_NetworkConf_pcst[loop_uo].ComM_channelId_uo == ComMChannelId)
        {

   	    CanSM_NetworkIdx_u8 = (NetworkHandleType)loop_uo;
            break;
        }
        else{

            CanSM_NetworkIdx_u8 = CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 + (uint8)1;
        }
   }
    return CanSM_NetworkIdx_u8;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_StopCtrl(NetworkHandleType network)
{

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   uint8 CanSM_ControllerId_u8;

   uint8 CanSM_Ctrl_index_u8;

#if(CANSM_SET_BAUDRATE_API == STD_ON)

   ComM_ModeType CanSM_ComM_Mode_uo;
#endif

   CanSM_NetworkModeStateType_ten CanSM_CurrNwMode_en;

   uint8 CanSM_Controller_Counter_u8 = 0;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   {

        CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STOPPED))
            {

                CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
            }
            else{

                 CanSM_Controller_Counter_u8++;
            }
   }

   if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
   {

        if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
        {

            CanSM_Ctrl_ModeInd_ab[network] = FALSE;

            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

            CanSM_Controller_Counter_u8 = CANSM_ZERO;

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_NORMAL;
            }
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;
            }
#else
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;
            }
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SET_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
            {

                CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_NOCOM;

                CanSM_ComM_Mode_uo = COMM_NO_COMMUNICATION;

                ComM_BusSM_ModeIndication(CanSM_NetworkConf_ps->ComM_channelId_uo, &CanSM_ComM_Mode_uo);

                for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                {

                    CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

                    if(E_NOT_OK == CanIf_SetBaudrate(CanSM_ControllerId_u8,CanSM_BaudRateConfigID_Value_au16[network]))
                    {

                        CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

                    }
                    else
                    {

                        CanSM_Controller_Counter_u8++;
                    }

                }

                if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
                {

                    CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED;
                }
            }
#endif

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
            {
                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
            {
                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
            {
                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STARTED;
            }

            else{

            }
        }

        else{

            SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CC_STOPPED_WAIT;
            }
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED_WAIT;
            }
#else
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED_WAIT;
            }
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SET_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
            {

                CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STOPPED_WAIT;
            }
#endif

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
            {

                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
            {

                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
            {

                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED_WAIT;
            }

            else{

            }

            SchM_Exit_CanSM_BOR_Nw_ModesNoNest();

            CanSM_StartTimer(network);
        }
   }

   else{

        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {

            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
            {

              CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
            }
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

              CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
            }
#else
            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
            {

                CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
            }
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SET_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
            {
               CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

                CanSM_ChangeBR_Exit(network);
            }
#endif

            else if((CanSM_CurrNwMode_en== CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
            {
                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;

               CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

               CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

               CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

               if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

                    if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
               else{

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                }

            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
            {
                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;

                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

                if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

                    if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
               else{

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                }
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
            {

                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED;
            }

            else{

            }

            CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else{

        }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_StartCtrl(NetworkHandleType network)
{

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   uint8 CanSM_ControllerId_u8;

   uint8 CanSM_Ctrl_index_u8;

   CanSM_NetworkModeStateType_ten CanSM_CurrNwMode_en;

   uint8 CanSM_Controller_Counter_u8 = 0;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   {

        CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STARTED))
            {

                CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
            }
            else{

                 CanSM_Controller_Counter_u8++;
            }
   }

   if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
   {

        if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
        {

            CanSM_Ctrl_ModeInd_ab[network] = FALSE;

            CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

            if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
            {

                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
            }

#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if(CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED )
            {

                CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

                CanSM_ChangeBR_Exit(network);
            }
#endif

            else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
            {

                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
            {

                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_DEFAULT;
            }

            else{

            }

        }

        else{

            SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
            if((CanSM_CurrNwMode_en== CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
            {

                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT;
            }

#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if(CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED )
            {

                CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED_WAIT;
            }
#endif

            else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
            {

                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT;
            }

            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
            {

                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STARTED_WAIT;
            }

            else{

            }

            SchM_Exit_CanSM_BOR_Nw_ModesNoNest();

            CanSM_StartTimer(network);
        }
   }

   else{

        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {

            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
           if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
            {
                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;

                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

                if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

                    if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
                else{

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                }

            }
#if(CANSM_SET_BAUDRATE_API == STD_ON)
            else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SET_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED ))
            {
               CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

                CanSM_ChangeBR_Exit(network);
            }
#endif

            else if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
            {
                CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;

               CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

               CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

               CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

               if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

                    if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
               else{

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                }
            }

            else if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
            {

                CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED;
            }

            else{

            }

           CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else{

        }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_SleepCtrl(NetworkHandleType network)
{

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   uint8 CanSM_ControllerId_u8;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_Controller_Counter_u8 = 0;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   {

   	CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_SLEEP))
   		{

   			CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
   		}
   		else
   		{

   			 CanSM_Controller_Counter_u8++;
   		}

   }

   if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
   {

   	if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
   	{

   		CanSM_Ctrl_ModeInd_ab[network] = FALSE;

   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   	    if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
   	    {

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;
   	    }
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
   		{

              CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;
   		}
   		else
   	    {

   	    }
   		#else

   		CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;
   		#endif

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
   	}

   	else
   	{
   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CC_SLEEP_WAIT;
   		}
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP_WAIT;
   		}
   		else
   		{

   		}
   		#else

   		CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP_WAIT;
   		#endif

   		CanSM_StartTimer(network);
   	}
   }

   else{
        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {

            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
   	#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
   		}
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   		}
   		else
   		{

   		}
   	#else

   	     CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   	#endif

   	     CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else{

        }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_NormalTrcv(NetworkHandleType network)
{

   CanSM_NetworkModeStateType_ten CanSM_CurrNwMode_en;

   CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

   CanSM_ReqMode_a[network] = CANSM_CANTRCV_NORMAL;

   CanSM_ModeChangeReq_flag[network] = TRUE;

   if(E_OK == CanIf_SetTrcvMode(CanSM_Network_pcst[network].Trcv_hndle_u8,CANTRCV_TRCVMODE_NORMAL))
   {

        if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
   	{

   		CanSM_Trcv_ModeInd_ab[network]=FALSE;

            SchM_Enter_CanSM_BOR_Nw_ModesNoNest();

   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_STANDBY;
   		}
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;
   		}
   		#else
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;
   		}
   		#endif

   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
   		{

   			CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED;
   		}
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
   		{

   			CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;
   		}
   		else
   		{

   		}

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
   	}

   	else
   	{

   		SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_NORMAL_WAIT;
   		}
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL_WAIT;
   		}
   		#else
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL_WAIT;
   		}
   		#endif
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
   		{

   			CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT;
   		}

   		else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
   		{

   			CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT;
   		}
   		else
   		{

   		}

   		SchM_Exit_CanSM_BOR_Nw_ModesNoNest();

   		CanSM_StartTimer(network);
   	}
   }

   else
   {

        CanSM_ReqMode_a[network] = CANSM_CANTRCV_DEFAULT;

        CanSM_ModeChangeReq_flag[network] = FALSE;

   	if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
   		}
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   		}
   		#else
   		if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   		}
   		#endif
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
   		{
               CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;

               CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

               CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

               CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

               if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
               {
   #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

   				if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
   		else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
   		{
   			CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;

   			CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   			CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

   			CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

   			if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
   			{
   				#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

   				if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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
   			else{

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                }
   		}

   		else
   		{

   		}

   		CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   	}
   	else
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_StandbyTrcv(NetworkHandleType network)
{

   CanSM_ReqMode_a[network] = CANSM_CANTRCV_STANDBY;

   CanSM_ModeChangeReq_flag[network] = TRUE;

   if(E_OK == CanIf_SetTrcvMode(CanSM_Network_pcst[network].Trcv_hndle_u8,CANTRCV_TRCVMODE_STANDBY))
   {

        if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
   	{

   		CanSM_Trcv_ModeInd_ab[network]=FALSE;

            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

            CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CC_SLEEP;
   		}
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_DEFAULT;

   			CanSM_PreNoCom_Exit(network);
   		}
   		else
   		{

   		}
   		#else

   		CanSM_PreNoCom_Substates_en[network]= CANSM_DEFAULT;

   		CanSM_PreNoCom_Exit(network);

   		#endif

   	}

   	else
   	{
   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_STANDBY_WAIT;
   		}
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY_WAIT;
   		}
   		else
   		{

   		}
   		#else

   		CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY_WAIT;
   		#endif

   		CanSM_StartTimer(network);
   	}
   }

   else
   {

        CanSM_ReqMode_a[network] = CANSM_CANTRCV_DEFAULT;

        CanSM_ModeChangeReq_flag[network] = FALSE;

   	if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
   		}
   		else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL)
   		{

   			CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   		}
   		else
   		{

   		}
   		#else

   		CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
   		#endif

   		CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   	}
   	else
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_PN_ClearWufTrcv(NetworkHandleType network)
{

   if(E_OK == CanIf_ClearTrcvWufFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
   {

        if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
   	{

   		CanSM_PN_Substate_Ind_ab[network]=FALSE;

   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CC_STOPPED;
   		}

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   	}

   	else
   	{

   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CLEAR_WUF_WAIT;
   		}

   		CanSM_StartTimer(network);
   	}
   }

   else
   {
   	if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

   		CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   	}
   	else
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_CheckWakeUpFlagInSleep(NetworkHandleType network)
{

   if(E_OK == CanIf_CheckTrcvWakeFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
   {

        if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
   	{

            CanSM_PN_Substate_Ind_ab[network]   = FALSE;
            CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
            CanSM_Trcv_ModeInd_ab[network]      = FALSE;

   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_DEFAULT;
   		}

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

            CanSM_PreNoCom_Exit(network);

   	}

   	else
   	{
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT;
   		}

   		CanSM_StartTimer(network);
   	}
   }

   else
   {
   	if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

   		CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   	}
   	else
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_CheckWakeUpFlagNotInSleep(NetworkHandleType network)
{

   if(E_OK == CanIf_CheckTrcvWakeFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
   {

        if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
   	{

   		CanSM_PN_Substate_Ind_ab[network] = FALSE;

   		CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CLEAR_WUF;
   		}

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
   	}

   	else
   	{
   		if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
   		{

   			CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT;
   		}

   		CanSM_StartTimer(network);
   	}
   }

   else
   {
   	if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

   		CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   	}
   	else
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_SetBaudrate_StateMachine(NetworkHandleType network)
{

   CanSM_ChangeBR_Substates_ten CanSM_ChangeBaudrate_Substates;

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   uint8 CanSM_ControllerId_u8;

   uint8 CanSM_Ctrl_index_u8;

   uint16 CanSM_BaudConfigID_u16;

   uint8 CanSM_Controller_Counter_u8 = 0;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

   CanSM_BaudConfigID_u16 = CanSM_BaudRateConfigID_Value_au16[network];

   if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
   {
        switch(CanSM_ChangeBaudrate_Substates)
        {
            case CANSM_BR_S_CC_STOPPED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED;

                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                }

                else{
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STOPPED;

                        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_BR_S_CC_STARTED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network]==TRUE)
                {

                    CanSM_Ctrl_ModeInd_ab[network]=FALSE;

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    CanSM_ChangeBR_Exit(network);

                }

                else{
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STARTED;

                        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                    }
                }

            }
            break;

            default:

            break;

        }
   }
   else{

        CanSM_ChangeBR_Substates_en[network]=CANSM_BR_DEFAULT;

        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

        CanSM_ChangeBR_Exit(network);

        CANSM_REPORT_ERROR_NO_CONDITON(((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))

   }

   if(CanSM_ChangeBaudrate_Substates == CANSM_BSM_CHANGE_BR_SYNC)
   {

        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {

            CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

            if(E_NOT_OK == CanIf_SetBaudrate(CanSM_ControllerId_u8,CanSM_BaudConfigID_u16))
            {

            }
            else{
                 CanSM_Controller_Counter_u8++;
            }
        }

        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
        {
            CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

            CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

            CanSM_ChangeBR_Exit(network);
        }

        else{

            CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STOPPED;

            CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
            }
   }
   else{

   }

   if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STOPPED)
   {

        CanSM_StopCtrl(network);
        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
   }

   if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STARTED)
   {

        CanSM_StartCtrl(network);

   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_NO2FULL_COM(NetworkHandleType network)
{

   CanSM_PreFullCom_Substates_ten CanSM_PreFullCom_Substates;

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   const CanSM_NetworkConf_tst * NetworkConf_ps;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_ControllerId_u8;

   ComM_ModeType CanSM_reqComM_Mode_uo;

    NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

   if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
        {
            switch(CanSM_PreFullCom_Substates)
            {
                case CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT:
                {

                    if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                    {

                        if(CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                        {

                            CanSM_Trcv_ModeInd_ab[network] = FALSE;
                        }

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STOPPED;

                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    }
                    else
                    {

                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {

                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_TRCV_NORMAL;

                            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                        }
                    }
                }
                break;
   			case CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT:
                {

                    if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED;

                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                   }

                    else
                    {
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {

                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STOPPED;

                            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                        }
                    }
                }
                break;
   			case CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT:
   			{

   				if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
   				{
   					CanSM_Ctrl_ModeInd_ab[network] = FALSE;
   					CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_DEFAULT;

   					CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

   					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   					CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

   					BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

   					CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

   					CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

   					CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

   					CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

   					CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

   					CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

   					for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   					{
   						CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
   						#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
   						if(CanSM_Passive_b == TRUE)
   						{

   							(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_TX_OFFLINE_ACTIVE));
   						}
   						else
   						{

   							(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
   						}
   						#else

   						(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
   						#endif
   					}

   					CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
   					ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);
   				}

   				else
   				{
   					if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
   					{

   						CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

   						CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STARTED;

   						CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
   					}
   				}
   			}
            break;
            default:

            break;

        }
   }
   else{
   	CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;

   	CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

   	CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   	CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

   	CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

   	if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
        {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

            if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
            {

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
            }
            else{

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
            }
#else

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
#endif
        }
   	else{

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }
   }

   if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_TRCV_NORMAL)
   {
        if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
        {

            CanSM_Trcv_ModeInd_ab[network] = TRUE;

            CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED;

            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
        }
        else{
#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

            CanSM_NormalTrcv(network);
#endif

            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
        }
   }
   if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_CC_STOPPED)
   {

        CanSM_StopCtrl(network);

        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
   }

   if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_CC_STARTED)
   {

        CanSM_StartCtrl(network);

        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

        if(CanSM_PreFullCom_Substates== CANSM_PRE_FULLCOM_DEFAULT)
        {

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

   		BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

   		CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

   		CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

   		CanSM_StartTimer(network);

   		CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

   		CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

   		CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

   		for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   		{
   			CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
   			#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
   			if(CanSM_Passive_b == TRUE)
   			{

   				(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_TX_OFFLINE_ACTIVE));
   			}
   			else
   			{

   				(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
   			}
   			#else

   			(void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
   			#endif
   		}

   		CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
   		ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);

        }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_FULL2SILENT_COM(NetworkHandleType network)
{

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   const CanSM_NetworkConf_tst * NetworkConf_ps;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_ControllerId_u8;

   ComM_ModeType CanSM_reqComM_Mode_uo;

    NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_DISABLED;

   CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

   CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

   CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_SILENTCOM;

   CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;

   CanSM_BswM_Mode_en = CANSM_BSWM_SILENT_COMMUNICATION;
    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   {
        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_TX_OFFLINE));
   }

   CanSM_reqComM_Mode_uo = COMM_SILENT_COMMUNICATION ;
   ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo, &CanSM_reqComM_Mode_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_SILENT2FULL_COM(NetworkHandleType network)
{

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   const CanSM_NetworkConf_tst * NetworkConf_ps;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_ControllerId_u8 = 0;

   ComM_ModeType CanSM_reqComM_Mode_uo;

    NetworkConf_ps = &CanSM_Network_pcst[network];

   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
   {
        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
        if(CanSM_Passive_b == TRUE)
        {

            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_TX_OFFLINE_ACTIVE));
        }
        else{

            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
        }
#else

        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_ONLINE));
#endif
   }

   CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

   CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

   CanSM_StartTimer(network);

   CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

   CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

   CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

   CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
   ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);

   CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_TxTimeoutException_StateMachine(NetworkHandleType Channel)
{

   CanSM_TxTimeoutException_Substates_ten CanSM_TxTimeoutException_en;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_ControllerId_u8 = 0;

   CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

   if(CanSM_Num_Unsuccessful_ModeReq_au8[Channel] < CanSM_ModeRepeatReq_Max_u8)
   {
        switch(CanSM_TxTimeoutException_en)
        {
            case CANSM_TxTimeoutException_S_CC_STOPPED_WAIT :
            {

                if(CanSM_Ctrl_ModeInd_ab[Channel] == TRUE)
                {

                    CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[Channel] = FALSE;

                    CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STARTED;

                    CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

                    CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;
               }

                else{
                    if(CanSM_TimerConfig_ast[Channel].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;

                        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
                    }

                }
            }
            break;

            case  CANSM_TxTimeoutException_S_CC_STARTED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[Channel] == TRUE)
                {

                    CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[Channel] = FALSE;

                    CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_DEFAULT;

                    CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

                    CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;

                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[Channel].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[Channel].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                        if(CanSM_Passive_b == TRUE)
                        {

                            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_TX_OFFLINE_ACTIVE));
                        }
                        else
                        {

                            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
                        }
#else

                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
#endif
                    }

                    CanSM_currBOR_State_en[Channel] = CANSM_S_NO_BUS_OFF;

                    CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_FULLCOM;

               }

                else{
                    if(CanSM_TimerConfig_ast[Channel].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STARTED;

                        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
                    }

                }
            }
            break;
            default:

            break;

        }
   }
   else{

        CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;

        CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;

        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

        CANSM_REPORT_ERROR_NO_CONDITON((uint8)CANSM_MAINFUNCTION_SID, (uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
   }

   if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_S_CC_STOPPED)
   {

        CanSM_StopCtrl(Channel);

        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
   }

   if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_S_CC_STARTED)
   {

        CanSM_StartCtrl(Channel);

        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
        if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_DEFAULT)
        {

            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[Channel].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
            {
                CanSM_ControllerId_u8 = CanSM_Network_pcst[Channel].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                if(CanSM_Passive_b == TRUE)
                {

                    (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_TX_OFFLINE_ACTIVE));
                }
                else{

                    (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
                }
#else

                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
#endif
            }

            CanSM_currBOR_State_en[Channel] = CANSM_S_NO_BUS_OFF;

            CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_FULLCOM;
        }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#if(CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_ChangeBR_Exit(NetworkHandleType network)
{

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   uint8 CanSM_Ctrl_index_u8;

   uint8 CanSM_ControllerId_u8 = 0;

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   ComM_ModeType CanSM_ComM_ModeType_uo;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_BaudRateConfigID_Value_au16[network] = 0xFFFFu;

   if(CanSM_ReqComM_Mode_en[network]==COMM_FULL_COMMUNICATION)
   {

        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_FULLCOM;

        CanSM_StartTimer(network);

        CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

        CanSM_BORMode_au8[network] = (uint8)CANSM_RECOVERY_ENABLED;

        CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

        CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

        BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {
            CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
            if(CanSM_Passive_b == TRUE)
            {

                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_TX_OFFLINE_ACTIVE));
            }
            else{

                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
            }
#else

            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_ONLINE));
#endif
        }

        CanSM_ComM_ModeType_uo = COMM_FULL_COMMUNICATION;
        ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_ComM_ModeType_uo);
   }

   else if(CanSM_ReqComM_Mode_en[network]==COMM_NO_COMMUNICATION)
   {

        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

       if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
        {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

            if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
            {

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
            }
            else{

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
            }
#else

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
#endif
        }
       else{

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }

   }

   else if(CanSM_ReqComM_Mode_en[network]==COMM_SILENT_COMMUNICATION)
   {

        CanSM_FULL2SILENT_COM(network);
   }

   else{

   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"

void CanSM_WakeUpValidation_StateMachine(NetworkHandleType network)
{

   CanSM_WakeUpValidation_Substates_ten CanSM_WakeUpValidation_Substates;

   CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

   if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
   {
        switch(CanSM_WakeUpValidation_Substates)
        {
            case CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT:
            {

                if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                {

                    if(CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                    {

                        CanSM_Trcv_ModeInd_ab[network] = FALSE;
                    }

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;

                    CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }
                else{

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                    }
                }
            }
            break;
   		case CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED;

                    CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   			}

                else{
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;

                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                    }
                }
            }
            break;
   		case CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT:
   		{

   			if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
   			{
   				CanSM_Ctrl_ModeInd_ab[network] = FALSE;

   				CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_DEFAULT;

   				CanSM_Wuvalidation_Start_ab[network] = FALSE;

   				CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

   				CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   			}

   			else
   			{
   				if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
   				{

   					CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

   					CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STARTED;

   					CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
   				}
   			}
   		}
   		break;
   		default:

   		break;

        }
   }
   else
   {
   	CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;

   	CanSM_Wuvalidation_Start_ab[network] = FALSE;

   	CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

   	CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   	CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

   	CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

   	if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
   		{
   			#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

   			if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
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

   if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL)
   {
   	if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
   	{

   		CanSM_Trcv_ModeInd_ab[network] = TRUE;

   		CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;

   		CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
   	}
   	else
   	{
#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

   		CanSM_NormalTrcv(network);
#endif

   		CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
   	}
   }
   if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED)
   {

   	CanSM_StopCtrl(network);

   	CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
   }
   if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_CC_STARTED)
   {

   	CanSM_StartCtrl(network);

   	CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

   	if(CanSM_WakeUpValidation_Substates== CANSM_WAKEUP_VALIDATION_DEFAULT)
   	{

   		CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   		CanSM_Wuvalidation_Start_ab[network] = FALSE;

   	}
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_PreNoCom_Exit(NetworkHandleType network)
{

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   CanSM_Network_Init_ab[network] = TRUE;

   CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

    BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

   if(CanSM_Wuvalidation_Start_ab[network] == TRUE)
   {

        CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;

        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

   }
   else{
        CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_BOR_SilentCom_Exit(NetworkHandleType network)
{

   const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

   CanSM_BswMCurrentStateType CanSM_BswM_Mode_en;

   ComM_ModeType CanSM_ComM_Mode_uo;

   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

   CanSM_Ctrl_ModeInd_ab[network] = FALSE;

   CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

   CanSM_BOR_SilentCom_ab[network] = FALSE;

   CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

   if(CanSM_ReqComM_Mode_en[network] == COMM_NO_COMMUNICATION)
   {

   	CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

   	CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

   	if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
        {
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

            if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
            {

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
            }
            else{

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
            }
#else

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
#endif
        }
   	else{

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }

   }
   else{

       CanSM_BswM_Mode_en = CANSM_BSWM_SILENT_COMMUNICATION;

       BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

       CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;

       CanSM_ComM_Mode_uo = COMM_SILENT_COMMUNICATION;
       ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_ComM_Mode_uo);

   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
