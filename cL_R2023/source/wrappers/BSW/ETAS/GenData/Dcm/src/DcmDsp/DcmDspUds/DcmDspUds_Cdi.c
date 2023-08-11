
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Cdi_Prv.h"
#include "Rte_Dcm.h"

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
static uint32 DTCId_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static Std_ReturnType  s_serviceRetVal_u8;
static uint8 ClientID_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)

static Std_ReturnType Dcm_Lok_CDIConditionCheck(Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType Result = E_OK;
    if(Dcm_CDIUserConditionCheck_pf != (CDIUserConditionCheck_pf)NULL_PTR)
    {
        Result = (*Dcm_CDIUserConditionCheck_pf) (DTCId_u32,dataNegRespCode_u8);
    }
    if(Result == E_OK)
    {
        if(Dcm_CdiModeRuleRef_pf != (Cdi_ModeRuleRef_pf)NULL_PTR)
        {

            Result = ((*Dcm_CdiModeRuleRef_pf) (dataNegRespCode_u8) == TRUE)?E_OK:E_NOT_OK;
        }
    }
    if(Result == E_NOT_OK)
    {
        *dataNegRespCode_u8 = (*dataNegRespCode_u8 == 0x0u)?DCM_E_CONDITIONSNOTCORRECT:*dataNegRespCode_u8;
    }
    else
    {
        *dataNegRespCode_u8 = 0x00u;
    }
    return Result;
}
#endif

static void Dcm_Lok_CDISelectDTCFilter(Dcm_SrvOpStatusType* OpStatus,\
                                      const Dcm_MsgContextType* pMsgContext,\
                                      Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType Result = E_NOT_OK;

    if(pMsgContext->reqDataLen == DCM_CDI_REQ_LEN)
    {

        DTCId_u32 = (((uint32)(pMsgContext->reqData[DCM_POS_DTC_HIGHBYTE]) << DCM_POS_DTC_BIT16) | \
                ((uint32)(pMsgContext->reqData[DCM_POS_DTC_MIDDLEBYTE]) << DCM_POS_DTC_BIT8) | \
                (uint32)(pMsgContext->reqData[DCM_POS_DTC_LOWBYTE]));

        Result = Dem_SelectDTC(ClientID_u8,DTCId_u32,DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);

        if(Result == E_OK)
        {

            *OpStatus = DCM_CHECKDATA;
        }
        else
        {
            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(Result);
        }
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
}

static void DCM_Lok_GetDTCSelectionResult(Dcm_SrvOpStatusType* OpStatus,
                                                 Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

    Std_ReturnType Result = Dem_GetDTCSelectionResultForClearDTC(ClientID_u8);

    if(Result == E_OK)
    {
#if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)
        if(Dcm_Lok_CDIConditionCheck(dataNegRespCode_u8) == E_OK)
#endif
        {
            *OpStatus = DCM_PROCESSSERVICE;
        }
    }
    else if (Result == DEM_PENDING)
    {
        s_serviceRetVal_u8 = DCM_E_PENDING;
    }
    else
    {
        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(Result);
    }
}

static void Dcm_Lok_ClearDTCInformation(Dcm_SrvOpStatusType* OpStatus,\
                                               Dcm_MsgContextType* pMsgContext,\
                                               Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType Result = Dem_ClearDTC(ClientID_u8);

    switch(Result)
    {

        case E_OK :
            #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
            DcmAppl_DcmClearRoeEventInformation();
            #endif
            pMsgContext->resDataLen = 0x0u;
            *OpStatus = DCM_INITIAL;
            s_serviceRetVal_u8 = E_OK;
            break;

        case DEM_PENDING:

            s_serviceRetVal_u8 = DCM_E_PENDING;
            break;

        default:
            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(Result);
            break;
    }
}

Std_ReturnType Dcm_DcmClearDiagnosticInformation(Dcm_SrvOpStatusType OpStatus,\
                                                 Dcm_MsgContextType* pMsgContext,\
                                                 Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    ClientID_u8 = Dcm_Lok_GetDemClientId(DCM_UDSCONTEXT);
    *dataNegRespCode_u8   = 0x0u;
    s_serviceRetVal_u8 = DCM_E_PENDING;

    if (OpStatus == DCM_CANCEL)
    {
        s_serviceRetVal_u8 = E_OK;
    }
    else
    {

        if (Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {
            Dcm_Lok_CDISelectDTCFilter(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
        }

        if (Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {
            DCM_Lok_GetDTCSelectionResult(&Dcm_SrvOpstatus_u8,dataNegRespCode_u8);
        }

        if (Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {
            Dcm_Lok_ClearDTCInformation(&Dcm_SrvOpstatus_u8, pMsgContext, dataNegRespCode_u8);
        }

        if(*dataNegRespCode_u8 != 0x0u)
        {
            s_serviceRetVal_u8 = E_NOT_OK;

            pMsgContext->resDataLen = 0x0u;

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        }
    }
    return s_serviceRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif
