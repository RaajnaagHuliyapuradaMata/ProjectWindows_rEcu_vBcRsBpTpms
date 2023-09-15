#include "Std_Types.hpp"

#include "DcmDspUds_Cdi_Inf.hpp"
#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Cdi_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint32,DCM_VAR) Dcm_dataDspReqDTCId_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Std_ReturnType,AUTOMATIC)  s_dataRetVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(void,DCM_CODE) Dcm_PrivDTCLengthCheck(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                  P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                                  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(pMsgContext->reqDataLen == DCM_CDI_REQ_LEN)
   {

        Dcm_dataDspReqDTCId_u32 = (  ((uint32)(pMsgContext->reqData[DCM_POS_DTC_HIGHBYTE]  ) << DCM_POS_DTC_BIT16) | \
                ((uint32)(pMsgContext->reqData[DCM_POS_DTC_MIDDLEBYTE]) << DCM_POS_DTC_BIT8) | \
                (uint32)(pMsgContext->reqData[DCM_POS_DTC_LOWBYTE]));

        Dcm_dataDspReqDTCId_u32 = (Dcm_dataDspReqDTCId_u32 & DCM_DTC_GRP_MASK);

        if(Dcm_dataDspReqDTCId_u32 == DCM_DTC_GRP_MASK)
        {

            Dcm_dataDspReqDTCId_u32 = DEM_DTC_GROUP_ALL_DTCS;
        }

        *OpStatus = DCM_CHECKDATA;
   }

   else{

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
}

static FUNC(void,DCM_CODE) Dcm_PrivClearDTCInformation( P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
                                                        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;

    dataDemClrRetVal_u8 = Dem_ClearDTC( Dcm_dataDspReqDTCId_u32, DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);
   switch(dataDemClrRetVal_u8)
   {

        case DEM_CLEAR_OK :
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
            DcmAppl_DcmClearRoeEventInformation();
#endif

            pMsgContext->resDataLen = 0x0u;

            *OpStatus = DCM_INITIAL;
            s_dataRetVal_u8 = E_OK;
            break;

        case  DEM_CLEAR_PENDING:

            s_dataRetVal_u8 = DCM_E_PENDING;
            break;

        case DEM_CLEAR_WRONG_DTC:

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            break;

        case DEM_CLEAR_MEMORY_ERROR:

            *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
        break;

        default:

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        break;
   }
}

static FUNC(void,DCM_CODE)  DCM_PrivDTCConditionCheckfunc(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                          P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;
#if(DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED!=DCM_CFG_OFF)
       VAR(Std_ReturnType,AUTOMATIC)  retVal_u8;
       VAR(boolean , AUTOMATIC) isModeChkRetval_b;
       VAR(boolean , AUTOMATIC) isConditionChkflag_b;
       retVal_u8 = E_OK;

       isModeChkRetval_b = FALSE;
       isConditionChkflag_b = FALSE;
#endif

       dataDemClrRetVal_u8 = Dem_DcmCheckClearParameter (Dcm_dataDspReqDTCId_u32, DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);
       switch(dataDemClrRetVal_u8)
       {
           case DEM_CLEAR_OK:

#if(DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)

                   isConditionChkflag_b = TRUE;
#else

                   *OpStatus = DCM_PROCESSSERVICE;
#endif
               break;

           case DEM_CLEAR_PENDING:

               s_dataRetVal_u8 = DCM_E_PENDING;
               break;

           case DEM_CLEAR_WRONG_DTC :
           case DEM_CLEAR_WRONG_DTCORIGIN:

              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
               break;

           default:

               *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
               break;
       }

#if(DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)

     if((isConditionChkflag_b ==  TRUE)&& (Dcm_CDIUserConditionCheck_pf != NULL_PTR))
   {

        retVal_u8 = (*Dcm_CDIUserConditionCheck_pf) (Dcm_dataDspReqDTCId_u32,dataNegRespCode_u8);

        if(retVal_u8 == E_OK)
        {

            *dataNegRespCode_u8 = 0x00;

            *OpStatus = DCM_PROCESSSERVICE;
        }

        else{
            if(*dataNegRespCode_u8 == 0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
   }

   if((isConditionChkflag_b ==  TRUE)&&(retVal_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00u) && (Dcm_CdiModeRuleRef_pf != NULL_PTR))
   {

        isModeChkRetval_b = (*Dcm_CdiModeRuleRef_pf) (dataNegRespCode_u8);

        if(( isModeChkRetval_b == TRUE ) && (*dataNegRespCode_u8 == 0u ))
        {

            *OpStatus = DCM_PROCESSSERVICE;
        }
        else{

            if(*dataNegRespCode_u8 == 0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
   }

#endif
}

FUNC(void,DCM_CODE) Dcm_Dsp_CDIIni(void){

   if(Dcm_SrvOpstatus_u8 != DCM_INITIAL)
   {
        Dem_DcmCancelOperation();
   }

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tClearDiagnosticInformation (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,\
                                                                 P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
                                                                 P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    *dataNegRespCode_u8   = 0x0u;
     s_dataRetVal_u8 = DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL)
   {
        Dcm_Dsp_CDIIni();

        s_dataRetVal_u8 = E_OK;
   }

   else{

        if(Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {
            Dcm_PrivDTCLengthCheck(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);

        }

        if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {
            DCM_PrivDTCConditionCheckfunc(&Dcm_SrvOpstatus_u8,dataNegRespCode_u8);

        }

        if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {
            Dcm_PrivClearDTCInformation(&Dcm_SrvOpstatus_u8, pMsgContext, dataNegRespCode_u8);

        }

        if(*dataNegRespCode_u8 != 0x0u)
        {
            s_dataRetVal_u8 = E_NOT_OK;

            pMsgContext->resDataLen = 0x0u;

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;

        }
   }

    return s_dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

