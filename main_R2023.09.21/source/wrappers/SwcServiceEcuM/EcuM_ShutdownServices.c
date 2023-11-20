#include "Std_Types.hpp"

#include "EcuM.hpp"
#include "EcuM_Cfg_SchM.hpp"

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.hpp"
#if(!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "EcuM_Prv.hpp"
#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, ECUM_CODE ) EcuM_SelectShutdownCause( VAR(Type_SwcServiceEcuM_tCauseShutdown, AUTOMATIC) tCauseShutdown )
{
   VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;
   if( TRUE == SwcServiceEcuM_bIsInitialised  )
   {
        if    (FALSE == EcuM_Lok_flgShutdownInfoDoNotUpdate_b )
        {
            if(tCauseShutdown < ECUM_CFG_NUM_SHUTDOWN_CAUSE)
            {
                SchM_Enter_EcuM();
                EcuM_Lok_dataSelectedShutdownCause_u8 = tCauseShutdown;

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                EcuM_Rn_dataShutdownInfo_st.tCauseShutdown =EcuM_Lok_dataSelectedShutdownCause_u8;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
                SchM_Exit_EcuM();

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

                returnvalue_u8 = E_OK;
            }
            else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID 
   ,     ECUM_E_INVALID_PAR);
#endif //ECUM_DEV_ERROR_DETECT
            }
        }
        else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID 
   ,     ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT
        }
   }
   else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
   }
    return returnvalue_u8;
}

FUNC(Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownCause(
          P2VAR(Type_SwcServiceEcuM_tCauseShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownCause )
        {
   VAR(Std_ReturnType, AUTOMATIC) return_value_u8= E_NOT_OK;
   if(FALSE == SwcServiceEcuM_bIsInitialised)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
   }
   else{
        if(shutdownCause == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_NULL_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
        }
        else{
            SchM_Enter_EcuM();
            *shutdownCause = EcuM_Lok_dataSelectedShutdownCause_u8;
            SchM_Exit_EcuM();
            return_value_u8 = E_OK;
        }
   }
    return return_value_u8;
}

FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget(
        VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC) shutdownTarget
   ,     VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) shutdownMode )
        {
   VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

   if(TRUE == SwcServiceEcuM_bIsInitialised)
   {
        if(FALSE == EcuM_Lok_flgShutdownInfoDoNotUpdate_b)
        {
#if ECUM_SLEEP_SUPPORT_ENABLE
            if((shutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP)&& (shutdownMode < ECUM_CFG_NUM_SLEEP_MODES))
            {
                returnvalue_u8   =   E_OK;
            }
            else{
#endif
            if( ((shutdownTarget == ECUM_SHUTDOWN_TARGET_RESET) && ( shutdownMode < ECUM_CFG_NUM_RESET_MODES)) ||
                    (shutdownTarget == ECUM_SHUTDOWN_TARGET_OFF))
            {
                returnvalue_u8   =   E_OK;
            }
            else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID 
   ,     ECUM_E_STATE_PAR_OUT_OF_RANGE);
#endif //ECUM_DEV_ERROR_DETECT
            }
#if ECUM_SLEEP_SUPPORT_ENABLE
        }
#endif
            if(E_OK == returnvalue_u8)
            {
                SchM_Enter_EcuM();
                SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown = shutdownTarget;
                if((shutdownTarget == ECUM_SHUTDOWN_TARGET_RESET)||
                        (shutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP))
                {
                    SwcServiceEcuM_stInfoTargetShutdown.mode = shutdownMode;
                }
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                EcuM_Rn_dataShutdownInfo_st.tTargetShutdown=SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
                EcuM_Rn_dataShutdownInfo_st.mode=SwcServiceEcuM_stInfoTargetShutdown.mode;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
                SchM_Exit_EcuM();
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
            }
            else{
            }
        }
        else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID 
   ,     ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT
        }
   }
   else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
   }
    return returnvalue_u8;
}

FUNC(Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownTarget(
          P2VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC, ECUM_APPL_DATA) tTargetShutdown
   ,     P2VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
                        {
   VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC) dataShutdownTarget_u8;
   VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataMode_u16;
   VAR(Std_ReturnType, AUTOMATIC) return_value_u8 = E_NOT_OK;
   if(FALSE == SwcServiceEcuM_bIsInitialised)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_UNINIT);
#endif //ECUM_DEV_ERROR_DETECT

   }
   else{
        if(tTargetShutdown == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_NULL_POINTER);
#endif//ECUM_DEV_ERROR_DETECT
        }
        else{
            SchM_Enter_EcuM();
            dataShutdownTarget_u8   =   SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
            dataMode_u16         =   SwcServiceEcuM_stInfoTargetShutdown.mode;
            SchM_Exit_EcuM();
            *tTargetShutdown   =   dataShutdownTarget_u8;
            if(shutdownMode == NULL_PTR)
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
            else{
            }
            return_value_u8 = E_OK;
        }
   }
    return return_value_u8;
}

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget(
          P2VAR(Type_SwcServiceEcuM_tTargetShutdown, AUTOMATIC, ECUM_APPL_DATA) tTargetShutdown
   ,     P2VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC, ECUM_APPL_DATA) shutdownMode )
                                        {
   VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
   if(FALSE== SwcServiceEcuM_bIsInitialised )
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
   }
   else if(tTargetShutdown == NULL_PTR)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
   }
   else{
        returnvalue_u8 = E_OK;
   }
   if(returnvalue_u8 == E_OK)
   {
        if(FALSE!=EcuM_Lok_flgNvMReadStatus_b)
        {
            *tTargetShutdown = EcuM_Lok_dataShutdownInfo_st.tTargetShutdown;
            if(shutdownMode == NULL_PTR)
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID
   ,     ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
            }
            else if((EcuM_Lok_dataShutdownInfo_st.tTargetShutdown == ECUM_SHUTDOWN_TARGET_SLEEP) ||
                    (EcuM_Lok_dataShutdownInfo_st.tTargetShutdown == ECUM_SHUTDOWN_TARGET_RESET))
            {
                *shutdownMode = EcuM_Lok_dataShutdownInfo_st.mode;
            }
            else{
            }
        }
        else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_NVM_READ_FAILED);
#endif //ECUM_DEV_ERROR_DETECT
            returnvalue_u8 = E_NOT_OK;
        }
   }
#else //ECUM_CFG_NVM_BLOCK_CONFIGURED == FALSE
    (void)tTargetShutdown;
    (void)shutdownMode;

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_SERVICE_DISABLED );
#endif //ECUM_DEV_ERROR_DETECT
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

    return returnvalue_u8;
}

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
FUNC(Std_ReturnType, ECUM_CODE ) EcuM_Rn_GetLastShutdownInfo(
        P2VAR(EcuM_ShutdownInfoType, AUTOMATIC, ECUM_APPL_DATA) shutdownCauseInfo)
{
   VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;
   if( FALSE== SwcServiceEcuM_bIsInitialised )
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
   }
   else if(shutdownCauseInfo == NULL_PTR)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
   }
   else{
        returnvalue_u8 = E_OK;
   }
   if(returnvalue_u8 == E_OK)
   {
        if(FALSE!=EcuM_Lok_flgNvMReadStatus_b)
        {
            shutdownCauseInfo->tCauseShutdown = EcuM_Lok_dataShutdownInfo_st.tCauseShutdown;
        }
        else{
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
#include "EcuM_Cfg_MemMap.hpp"

