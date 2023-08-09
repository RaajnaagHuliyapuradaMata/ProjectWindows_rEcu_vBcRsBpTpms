

#include "Dcm_Dsd_Prv.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
Dcm_SrvOpStatusType Dcm_SrvOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
Dcm_DsdStatesType_ten stDsdState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

#define DSDSUBSTATE_SERVICETABLE_INI      (1u)

#define DSDSUBSTATE_VERIFYDATA            (2u)

#define DSDSUBSTATE_SUPPLIER_NOTIFICATION (3u)

#define DSDSUBSTATE_SUBFUNCTION_CHECK     (4u)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

static uint8 stDsdSubState_u8 = DSDSUBSTATE_SERVICETABLE_INI;

void Dcm_Lok_ResetDsdSubStateMachine(void)
{
    stDsdSubState_u8 = DSDSUBSTATE_SERVICETABLE_INI;
}

boolean Dcm_Lok_IsVerifyDataProcessing(void)
{
    boolean Status = FALSE;
    if((stDsdState_en == DSD_VERIFY_DIAGNOSTIC_DATA) && (stDsdSubState_u8 == DSDSUBSTATE_SERVICETABLE_INI))
    {
        Status = TRUE;
    }
    return Status;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifyData_StateMachine(void)
{
    Std_ReturnType VerificationResult_u8 = E_NOT_OK;
    switch(stDsdSubState_u8)
    {

        case DSDSUBSTATE_SERVICETABLE_INI:
        {
            Dcm_Lok_DsdServiceTableInit();

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED == DCM_CFG_OFF)
            VerificationResult_u8 = E_OK;
#else
            VerificationResult_u8 = (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)?  \
                                     Dcm_Lok_DsdNotification(DCM_MANUFACTURERNOTIFICATION):E_OK;

            if(VerificationResult_u8 != E_OK)
            {
                break;
            }
            else
#endif
            {
                stDsdSubState_u8 = DSDSUBSTATE_VERIFYDATA;
            }
        }

        case DSDSUBSTATE_VERIFYDATA:
        {
            if(Dcm_Lok_DsdVerifyData() != E_OK)
            {
                VerificationResult_u8 = E_NOT_OK;
                break;
            }
            else
            {
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
                stDsdSubState_u8 = DSDSUBSTATE_SUPPLIER_NOTIFICATION;
#else
                stDsdSubState_u8 = DSDSUBSTATE_SUBFUNCTION_CHECK;
#endif
            }
        }

#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
        case DSDSUBSTATE_SUPPLIER_NOTIFICATION:
        {
             VerificationResult_u8 = (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)?   \
                                      Dcm_Lok_DsdNotification(DCM_SUPPLIERNOTIFICATION):E_OK;

             if(VerificationResult_u8 == E_OK)
             {
                 stDsdSubState_u8 = DSDSUBSTATE_SUBFUNCTION_CHECK;
             }
             else
             {
                 break;
             }
        }
#endif

        case DSDSUBSTATE_SUBFUNCTION_CHECK:
        {

            if(Dcm_Lok_IsSubFunctionSupported())
            {
                VerificationResult_u8 = Dcm_Lok_DsdCheckSubFunction();
            }
        }
        break;

         default:
         {
             VerificationResult_u8 = E_NOT_OK;
         }
         break;
    }

    if(VerificationResult_u8 != DCM_E_PENDING)
    {
        stDsdSubState_u8 = DSDSUBSTATE_SERVICETABLE_INI;
    }
    return VerificationResult_u8;
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

void Dcm_Lok_DsdStateMachine(void)
{
    switch(stDsdState_en)
    {

        case DSD_VERIFY_DIAGNOSTIC_DATA:
            if(Dcm_Lok_DsdVerifyData_StateMachine() != E_OK)
            {
                break;
            }
            else
            {
                Dcm_Lok_SetDsdState(DSD_CALL_SERVICE);
            }

        case DSD_CALL_SERVICE:

            Dcm_Lok_DsdProcessService();
            break;

        case DSD_WAITFORTXCONF:
            break;

        case DSD_SENDTXCONF_APPL:
            Dcm_Lok_DsdSendTxConfirmation();
            break;

        default:

            break;
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
