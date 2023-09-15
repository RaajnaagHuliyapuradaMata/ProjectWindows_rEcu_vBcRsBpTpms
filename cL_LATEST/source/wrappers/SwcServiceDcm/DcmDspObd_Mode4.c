
#include "DcmDspObd_Mode4_Priv.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE4_ENABLED  != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DspObdMode04Type_ten Dcm_stDspObdMode04State_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_DcmObdMode04_Ini(void){

    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
}

static void Dcm_Lok_DcmObdMode04CheckInitState (
        const Dcm_MsgContextType* pMsgContext
   ,       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType stObdMode04Appl_u8;

   if(pMsgContext->reqDataLen == DCM_OBDMODE04_REQ_LEN)
   {

        stObdMode04Appl_u8 = DcmAppl_OBD_Mode04();

        if(stObdMode04Appl_u8 == E_OK)
        {

            Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_CLEAR;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }
}

static Std_ReturnType Dcm_Lok_DcmObdMode04ClearDTC (Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint8          ClientID_u8;
    Std_ReturnType dataDemClrRetVal_u8;
    Std_ReturnType dataRetVal_u8;

    dataDemClrRetVal_u8 = E_OK;
    dataRetVal_u8       = E_NOT_OK;

   ClientID_u8 = Dcm_Lok_GetDemClientId(DCM_OBDCONTEXT);

    dataDemClrRetVal_u8 = Dem_ClearDTC(ClientID_u8);

   switch(dataDemClrRetVal_u8)
   {

        case E_OK:
        {

            Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
            dataRetVal_u8              = E_OK;
            break;
        }

        case DEM_PENDING:
        {

            dataRetVal_u8 = DCM_E_PENDING;
            break;
        }
        default:
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataRetVal_u8 = E_NOT_OK;
            break;
        }
   }
    return (dataRetVal_u8);
}

Std_ReturnType Dcm_DcmObdMode04 (
        Dcm_SrvOpStatusType OpStatus
   ,       Dcm_MsgContextType* pMsgContext
   ,       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint8 ClientID_u8;
    Std_ReturnType dataRetVal_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x0u;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_DcmObdMode04_Ini();

        dataRetVal_u8 = E_OK;
   }
   else{
        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_INIT)
        {
            Dcm_Lok_DcmObdMode04CheckInitState (pMsgContext
   ,                   dataNegRespCode_u8);
            ClientID_u8 = Dcm_Lok_GetDemClientId(DCM_OBDCONTEXT);

            if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_CLEAR)
            {
                dataRetVal_u8 = Dem_SelectDTC(ClientID_u8,DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
                if(dataRetVal_u8 == E_OK)
                {
                    dataRetVal_u8 = Dcm_Lok_DcmObdMode04ClearDTC(dataNegRespCode_u8);
                }

                else{
                    *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetVal_u8);
                }
            }
        }
        else if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_CLEAR)
        {
            dataRetVal_u8 = Dcm_Lok_DcmObdMode04ClearDTC(dataNegRespCode_u8);
        }
        else{

        }

        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_UNINIT)
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED; ;
        }
   }

   if(*dataNegRespCode_u8 != 0x0u)
   {

        Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
        dataRetVal_u8 = E_NOT_OK;
   }
   if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_INIT)
   {
        pMsgContext->resDataLen = 0x0u;

   }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

