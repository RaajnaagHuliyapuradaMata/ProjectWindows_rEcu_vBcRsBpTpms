#include "EcuM.h"
#include "EcuM_Cfg_SchM.h"

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.h"
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "EcuM_Prv.h"
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

Std_ReturnType EcuM_SelectShutdownCause( Type_SwcServiceEcuM_tCauseShutdown tCauseShutdown )
{
    Std_ReturnType returnvalue_u8 = E_NOT_OK;
    if ( TRUE == SwcServiceEcuM_bIsInitialised  )
    {
        if    (FALSE == EcuM_Lok_flgShutdownInfoDoNotUpdate_b )
        {
            if(tCauseShutdown < ECUM_CFG_NUM_SHUTDOWN_CAUSE)
            {
                SchM_Enter_EcuM();
                EcuM_Lok_dataSelectedShutdownCause_u8 = tCauseShutdown;

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                EcuM_Rn_dataShutdownInfo_st.tCauseShutdown =EcuM_Lok_dataSelectedShutdownCause_u8;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
                SchM_Exit_EcuM();

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

                returnvalue_u8 = E_OK;
            }
            else
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID ,
                        ECUM_E_INVALID_PAR);
#endif //ECUM_DEV_ERROR_DETECT
            }
        }
        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID ,
                    ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT
        }
    }
    else
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    return returnvalue_u8;
}

Std_ReturnType EcuM_GetShutdownCause(
          Type_SwcServiceEcuM_tCauseShutdown * shutdownCause )
        {
    Std_ReturnType return_value_u8= E_NOT_OK;
    if (FALSE == SwcServiceEcuM_bIsInitialised)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else
    {
        if(shutdownCause == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_NULL_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
        }
        else
        {
            SchM_Enter_EcuM();
            *shutdownCause = EcuM_Lok_dataSelectedShutdownCause_u8;
            SchM_Exit_EcuM();
            return_value_u8 = E_OK;
        }
    }
    return return_value_u8;
}

Std_ReturnType EcuM_SelectShutdownTarget(
        Type_SwcServiceEcuM_tTargetShutdown tTargetShutdown,
        Type_SwcServiceEcuM_tModeShutdown shutdownMode )
        {
    Std_ReturnType returnvalue_u8 = E_NOT_OK;

    if (TRUE == SwcServiceEcuM_bIsInitialised)
    {
        if(FALSE == EcuM_Lok_flgShutdownInfoDoNotUpdate_b)
        {
#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
            if ((tTargetShutdown == ECUM_SHUTDOWN_TARGET_SLEEP)&& (shutdownMode < ECUM_CFG_NUM_SLEEP_MODES))
            {
                returnvalue_u8   =   E_OK;
            }
            else
            {
#endif
            if( ((tTargetShutdown == ECUM_SHUTDOWN_TARGET_RESET) && ( shutdownMode < ECUM_CFG_NUM_RESET_MODES)) ||
                    (tTargetShutdown == ECUM_SHUTDOWN_TARGET_OFF))
            {
                returnvalue_u8   =   E_OK;
            }
            else
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID ,
                                                                        ECUM_E_STATE_PAR_OUT_OF_RANGE);
#endif //ECUM_DEV_ERROR_DETECT
            }
#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
        }
#endif
            if (E_OK == returnvalue_u8)
            {
                SchM_Enter_EcuM();
                SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown = tTargetShutdown;
                if ((tTargetShutdown == ECUM_SHUTDOWN_TARGET_RESET)||
                        (tTargetShutdown == ECUM_SHUTDOWN_TARGET_SLEEP))
                {
                    SwcServiceEcuM_stInfoTargetShutdown.mode = shutdownMode;
                }
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                EcuM_Rn_dataShutdownInfo_st.tTargetShutdown=SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
                EcuM_Rn_dataShutdownInfo_st.mode=SwcServiceEcuM_stInfoTargetShutdown.mode;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
                SchM_Exit_EcuM();
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
            }
            else
            {
            }
        }
        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID ,
                                                                    ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT
        }
    }
    else
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    return returnvalue_u8;
}

Std_ReturnType EcuM_GetShutdownTarget(
          Type_SwcServiceEcuM_tTargetShutdown * tTargetShutdown,
          Type_SwcServiceEcuM_tModeShutdown * shutdownMode)
                        {
    Type_SwcServiceEcuM_tTargetShutdown dataShutdownTarget_u8;
    Type_SwcServiceEcuM_tModeShutdown dataMode_u16;
    Std_ReturnType return_value_u8 = E_NOT_OK;
    if(FALSE == SwcServiceEcuM_bIsInitialised)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_UNINIT);
#endif //ECUM_DEV_ERROR_DETECT

    }
    else
    {
        if (tTargetShutdown == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_NULL_POINTER);
#endif//ECUM_DEV_ERROR_DETECT
        }
        else
        {
            SchM_Enter_EcuM();
            dataShutdownTarget_u8   =   SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
            dataMode_u16         =   SwcServiceEcuM_stInfoTargetShutdown.mode;
            SchM_Exit_EcuM();
            *tTargetShutdown   =   dataShutdownTarget_u8;
            if (shutdownMode == NULL_PTR)
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_PARAM_POINTER);
#endif //ECUM_DEV_ERROR_DETECT
            }
            else if((dataShutdownTarget_u8 == ECUM_SHUTDOWN_TARGET_RESET)||
                    (dataShutdownTarget_u8 == ECUM_SHUTDOWN_TARGET_SLEEP))
            {
                *shutdownMode = dataMode_u16;
            }
            else
            {
            }
            return_value_u8 = E_OK;
        }
    }
    return return_value_u8;
}

Std_ReturnType EcuM_GetLastShutdownTarget(
          Type_SwcServiceEcuM_tTargetShutdown * tTargetShutdown,
          Type_SwcServiceEcuM_tModeShutdown * shutdownMode )
                                        {
    Std_ReturnType returnvalue_u8 = E_NOT_OK;

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
    if (FALSE== SwcServiceEcuM_bIsInitialised )
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else if (tTargetShutdown == NULL_PTR)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else
    {
        returnvalue_u8 = E_OK;
    }
    if (returnvalue_u8 == E_OK)
    {
        if(FALSE!=EcuM_Lok_flgNvMReadStatus_b)
        {
            *tTargetShutdown = EcuM_Lok_dataShutdownInfo_st.tTargetShutdown;
            if(shutdownMode == NULL_PTR)
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID,
                        ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
            }
            else if ((EcuM_Lok_dataShutdownInfo_st.tTargetShutdown == ECUM_SHUTDOWN_TARGET_SLEEP) ||
                    (EcuM_Lok_dataShutdownInfo_st.tTargetShutdown == ECUM_SHUTDOWN_TARGET_RESET))
            {
                *shutdownMode = EcuM_Lok_dataShutdownInfo_st.mode;
            }
            else
            {
            }
        }
        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_NVM_READ_FAILED);
#endif //ECUM_DEV_ERROR_DETECT
            returnvalue_u8 = E_NOT_OK;
        }
    }
#else //ECUM_CFG_NVM_BLOCK_CONFIGURED == FALSE
    (void)shutdownTarget;
    (void)shutdownMode;

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_SERVICE_DISABLED );
#endif //ECUM_DEV_ERROR_DETECT
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

    return returnvalue_u8;
}

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
Std_ReturnType EcuM_Rn_GetLastShutdownInfo(
        EcuM_ShutdownInfoType * shutdownCauseInfo)
{
    Std_ReturnType returnvalue_u8 = E_NOT_OK;
    if ( FALSE== SwcServiceEcuM_bIsInitialised )
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else if (shutdownCauseInfo == NULL_PTR)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else
    {
        returnvalue_u8 = E_OK;
    }
    if (returnvalue_u8 == E_OK)
    {
        if(FALSE!=EcuM_Lok_flgNvMReadStatus_b)
        {
            shutdownCauseInfo->tCauseShutdown = EcuM_Lok_dataShutdownInfo_st.tCauseShutdown;
        }
        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_NVM_READ_FAILED);
#endif //ECUM_DEV_ERROR_DETECT
            returnvalue_u8 = E_NOT_OK;
        }
    }
    return returnvalue_u8;
}
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

