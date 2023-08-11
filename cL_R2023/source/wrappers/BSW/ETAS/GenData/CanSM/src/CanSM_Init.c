

#include "CanSM_Prv.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_TimerConfig_tst CanSM_TimerConfig_ast[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Init_ab;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_NetworkModeStateType_ten CanSM_CurrNw_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_BusOffRecoveryStateType_ten CanSM_currBOR_State_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_BusOff_Cntr_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_BORMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_BusOff_Indicated_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_MutexMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
ComM_ModeType CanSM_ReqComM_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Wuvalidation_Start_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_BusOffISRPend_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

CanSM_ChangeBR_Substates_ten CanSM_ChangeBR_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
uint16 CanSM_BaudRateConfigID_Value_au16[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#endif

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_Num_Unsuccessful_ModeReq_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Trcv_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

boolean CanSM_ModeChangeReq_flag[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

CanSM_ReqCanTrcv_States CanSM_ReqMode_a[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Ctrl_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_PreNoCom_Substates_ten CanSM_PreNoCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_PN_Substate_Ind_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
ComM_ModeType CanSM_BusSMMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_PreFullCom_Substates_ten CanSM_PreFullCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_WakeUpValidation_Substates_ten CanSM_WakeUpValidation_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_TxTimeoutException_Substates_ten CanSM_TxTimeoutexception_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
uint16 CanSM_ModeRepeatReq_Time_u16;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_ModeRepeatReq_Max_u8;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_CANControllerStateType_ten CanSM_ControllerState_en[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Network_Init_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_ControllerIndications_ab[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_BOR_Controller_Stopped_stateType_ten CanSM_BOR_Controller_Stopped_state_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
const CanSM_NetworkConf_tst * CanSM_Network_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
const Type_CfgSwcServiceCanSM_st * CanSM_ConfigSet_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_DSM_REINIT_ENABLED != STD_OFF)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
CanSM_NetworkConf_DEM_tst CanSM_DSM_ReInit_Status_ast[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#endif

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Passive_b;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_Rn_DisableBusOffRecovery_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
uint8 CanSM_GetBusOffDelay_Value_u8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
boolean CanSM_BOR_SilentCom_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
void CanSM_Init(const Type_CfgSwcServiceCanSM_st* ConfigPtr)
{

    uint8 CanSM_NetworkIdx_u8;

    uint8 CanSM_ControllerId_u8;

    uint8 CanSM_Ctrl_index_u8;

    const CanSM_NetworkConf_tst * CanSM_NetworkConf_ps;

    #if(CANSM_VARIANT_INFO == CANSM_VARIANT_PRE_COMPILE)

    CanSM_ConfigSet_pcst = &CanSM_ConfigSet[0];
    (void)ConfigPtr;
    #else

    CANSM_REPORT_ERROR((ConfigPtr==NULL_PTR),(uint8)CANSM_INIT_SID,(uint8)CANSM_E_INIT_FAILED)

    CanSM_ConfigSet_pcst = ConfigPtr;
    #endif

    CanSM_Network_pcst = CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst;

    CanSM_ModeRepeatReq_Max_u8   = CanSM_ConfigSet_pcst->CanSMModeRequestRepetitionMax_u8;

    CanSM_ModeRepeatReq_Time_u16 = CanSM_ConfigSet_pcst->CanSMModeRequestRepetitionTime_u16;

    for(CanSM_NetworkIdx_u8 =0; CanSM_NetworkIdx_u8 < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; CanSM_NetworkIdx_u8++)
    {

        CanSM_CurrNw_Mode_en[CanSM_NetworkIdx_u8]                      = CANSM_BSM_S_NOT_INITIALIZED;
        CanSM_currBOR_State_en[CanSM_NetworkIdx_u8]                    = CANSM_BOR_IDLE;
        CanSM_BusOff_Cntr_au8[CanSM_NetworkIdx_u8]                     = CANSM_ZERO;
        CanSM_BORMode_au8[CanSM_NetworkIdx_u8]                         = CANSM_RECOVERY_DISABLED;
        CanSM_ReqComM_Mode_en[CanSM_NetworkIdx_u8]                     = COMM_NO_COMMUNICATION ;
        CanSM_BusOffISRPend_ab[CanSM_NetworkIdx_u8]                    = FALSE;
        CanSM_Ctrl_ModeInd_ab[CanSM_NetworkIdx_u8]                     = FALSE;
        CanSM_Network_Init_ab[CanSM_NetworkIdx_u8]                     = FALSE;
        CanSM_MutexMode_au8[CanSM_NetworkIdx_u8]                       = CANSM_MUTEX_FREE;

        CanSM_Wuvalidation_Start_ab[CanSM_NetworkIdx_u8]                = FALSE;
        CanSM_PreNoCom_Substates_en[CanSM_NetworkIdx_u8]               = CANSM_DEFAULT;
        CanSM_PreFullCom_Substates_en[CanSM_NetworkIdx_u8]             = CANSM_PRE_FULLCOM_DEFAULT;
        CanSM_WakeUpValidation_Substates_en[CanSM_NetworkIdx_u8]       = CANSM_WAKEUP_VALIDATION_DEFAULT;

        CanSM_ReqMode_a[CanSM_NetworkIdx_u8] = CANSM_CANTRCV_DEFAULT;

        CanSM_ModeChangeReq_flag[CanSM_NetworkIdx_u8] = FALSE;

        #if(CANSM_SET_BAUDRATE_API == STD_ON)
        CanSM_ChangeBR_Substates_en[CanSM_NetworkIdx_u8]               = CANSM_BR_DEFAULT;
        #endif
        CanSM_TxTimeoutexception_Substates_en[CanSM_NetworkIdx_u8]     = CANSM_TxTimeoutException_DEFAULT;
        CanSM_Num_Unsuccessful_ModeReq_au8[CanSM_NetworkIdx_u8]        = CANSM_ZERO;
        CanSM_BusOff_Indicated_ab[CanSM_NetworkIdx_u8]                  = FALSE;
        CanSM_InitTimer(CanSM_NetworkIdx_u8);
        CanSM_BOR_Controller_Stopped_state_en[CanSM_NetworkIdx_u8]    = CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED;
        #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
        CanSM_Passive_b                                                = FALSE;
        #endif

        CanSM_Rn_DisableBusOffRecovery_ab[CanSM_NetworkIdx_u8]         = FALSE;

        CanSM_GetBusOffDelay_Value_u8[CanSM_NetworkIdx_u8]             = CANSM_ZERO;
        CanSM_BOR_SilentCom_ab[CanSM_NetworkIdx_u8]                     = FALSE;

        CanSM_NetworkConf_ps = &CanSM_Network_pcst[CanSM_NetworkIdx_u8];

        #if(CANSM_SET_BAUDRATE_API == STD_ON)

        CanSM_BaudRateConfigID_Value_au16[CanSM_NetworkIdx_u8] = 0xFFFFu;
        #endif

        CanSM_CurrNw_Mode_en[CanSM_NetworkIdx_u8] = CANSM_BSM_S_PRE_NOCOM;

        if(CanSM_Network_pcst[CanSM_NetworkIdx_u8].Trcv_hndle_u8 != 255u)
            {
                CanSM_Trcv_ModeInd_ab[CanSM_NetworkIdx_u8] = FALSE;
                #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

                if(CanSM_Network_pcst[CanSM_NetworkIdx_u8].TrcvPnConfig_b == TRUE)
                    {

                        CanSM_PN_Substate_Ind_ab[CanSM_NetworkIdx_u8] = FALSE;
                    }
                #endif
            }
        else
            {
                CanSM_Trcv_ModeInd_ab[CanSM_NetworkIdx_u8] = TRUE;
            }

        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
            {

                CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

                CanSM_ControllerState_en[CanSM_ControllerId_u8] = CANSM_ControllerState_UNINIT ;

                CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] = FALSE;
            }

        Dem_ReportErrorStatus(CanSM_Network_pcst[CanSM_NetworkIdx_u8].BusOffEventId_uo,DEM_EVENT_STATUS_PASSED);

        #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
        CanSM_DSM_ReInit_Status_ast[CanSM_NetworkIdx_u8].CanSM_DEM_Eventstatus_u8 = DEM_EVENT_STATUS_PASSED;
        #endif

    }

        CanSM_Init_ab = (boolean)CANSM_INITED;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
void CanSM_DeInitPnNotSupported(NetworkHandleType network)
{

    CanSM_PreNoCom_Substates_ten CanSM_PreNoCom_Substates;

    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
        switch(CanSM_PreNoCom_Substates)
        {
            case CANSM_S_CC_STOPPED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_SLEEP;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

               }

                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_CC_SLEEP_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network]==TRUE)
                {

                    CanSM_Ctrl_ModeInd_ab[network]=FALSE;

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }

            }
            break;

            case CANSM_S_TRCV_NORMAL_WAIT:
            {

                if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                {

                    if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                        {

                            CanSM_Trcv_ModeInd_ab[network] = FALSE;
                        }

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                }
                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_TRCV_STANDBY_WAIT:
            {

                if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                {

                    if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                    {

                        CanSM_Trcv_ModeInd_ab[network] = FALSE;
                    }

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_PreNoCom_Exit(network);
                }

                else
                {
                   if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_TRCV_STANDBY;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

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

        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CC_STOPPED;

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

        CANSM_REPORT_ERROR_NO_CONDITON(((uint8)CANSM_MAINFUNCTION_SID),(uint8)(CANSM_E_MODE_REQUEST_TIMEOUT))

    }

    if(CanSM_PreNoCom_Substates == CANSM_S_CC_STOPPED)
        {

            CanSM_StopCtrl(network);

            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
        }

    if(CanSM_PreNoCom_Substates == CANSM_S_CC_SLEEP)
        {

            CanSM_SleepCtrl(network);

            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
        }

    if(CanSM_PreNoCom_Substates == CANSM_S_TRCV_NORMAL)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255)
            {

                CanSM_Trcv_ModeInd_ab[network] = TRUE;

                CanSM_PreNoCom_Substates_en[network] = CANSM_S_TRCV_STANDBY;

            }
            else
            {
                #if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

                CanSM_NormalTrcv(network);
                #endif

            }
        }

    if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
            {

                CanSM_Trcv_ModeInd_ab[network] = TRUE;

                CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;
				
				CanSM_PreNoCom_Exit(network);

            }
            else
            {
                #if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

                CanSM_StandbyTrcv(network);
                #endif

            }

        }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
void CanSM_DeInitPnSupported(NetworkHandleType network)
{

    CanSM_PreNoCom_Substates_ten CanSM_PreNoCom_Substates;

    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
        switch(CanSM_PreNoCom_Substates)
        {
            case CANSM_S_PN_CLEAR_WUF_WAIT:
            {

                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_PN_Substate_Ind_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CC_STOPPED;

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_CLEAR_WUF;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_CC_STOPPED_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_TRCV_NORMAL;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_CC_STOPPED;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_TRCV_NORMAL_WAIT:
            {

                if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Trcv_ModeInd_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_TRCV_STANDBY;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_TRCV_NORMAL;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_TRCV_STANDBY_WAIT:
            {

                if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Trcv_ModeInd_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CC_SLEEP;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_TRCV_STANDBY;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_CC_SLEEP_WAIT:
            {

                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
               }
            }
            break;

            case CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT:
            {

                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {

                    CanSM_PN_Substate_Ind_ab[network]   = FALSE;
                    CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
                    CanSM_Trcv_ModeInd_ab[network]      = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
					
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

					
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    CanSM_PreNoCom_Exit(network);
                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT:
            {

                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {

                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    CanSM_PN_Substate_Ind_ab[network]   = FALSE;
                    CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
                    CanSM_Trcv_ModeInd_ab[network]      = FALSE;

                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                else
                {

                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {

                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP;

                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

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

            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

            CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

            CANSM_REPORT_ERROR_NO_CONDITON(((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))

        }

    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CLEAR_WUF)
    {

        CanSM_PN_ClearWufTrcv(network);

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CC_STOPPED)
    {

        CanSM_StopCtrl(network);

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    if(CanSM_PreNoCom_Substates == CANSM_S_PN_TRCV_NORMAL)
    {
        #if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

        CanSM_NormalTrcv(network);
        #endif

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

    }

    if(CanSM_PreNoCom_Substates == CANSM_S_PN_TRCV_STANDBY)
    {
        #if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)

        CanSM_StandbyTrcv(network);
        #endif

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CC_SLEEP)
    {

        CanSM_SleepCtrl(network);

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    if(CanSM_PreNoCom_Substates == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
    {

        CanSM_CheckWakeUpFlagInSleep(network);

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    if(CanSM_PreNoCom_Substates == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
    {

        CanSM_CheckWakeUpFlagNotInSleep(network);

        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
