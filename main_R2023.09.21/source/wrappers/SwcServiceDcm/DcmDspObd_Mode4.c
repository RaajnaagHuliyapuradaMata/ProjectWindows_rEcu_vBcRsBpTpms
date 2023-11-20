#include "Std_Types.hpp"

#include "DcmDspObd_Mode4_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode4_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspObdMode04Type_ten,DCM_VAR) Dcm_stDspObdMode04State_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_DcmObdMode04_Ini(void){

   if((Dcm_stDspObdMode04State_en != DCM_DSP_MODE04_INIT) && (Dcm_stDspObdMode04State_en != DCM_DSP_MODE04_UNINIT))
   {
    	Dem_DcmCancelOperation();
   }

    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmObdMode04 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;
   VAR(Std_ReturnType,AUTOMATIC) stObdMode04Appl_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    *dataNegRespCode_u8   = 0x0u;
    dataDemClrRetVal_u8 = DEM_CLEAR_OK;
   stObdMode04Appl_u8 = E_NOT_OK;
    dataRetVal_u8=E_NOT_OK;

    DCM_UNUSED_PARAM(OpStatus);

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_DcmObdMode04_Ini();

        dataRetVal_u8 = E_OK;
   }
   else{
        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_INIT)
        {

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

                DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_INVALID_LENGTH)
            }
        }

        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_CLEAR)
        {

            dataDemClrRetVal_u8 = Dem_ClearDTC( DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_OBD
   ,     DEM_DTC_ORIGIN_PRIMARY_MEMORY);

            switch(dataDemClrRetVal_u8)
            {

                case (Dem_ReturnClearDTCType)DEM_CLEAR_OK:
                {

                    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
                    dataRetVal_u8=E_OK;
                    break;
                }

                case (Dem_ReturnClearDTCType)DEM_CLEAR_PENDING:
                {

                    dataRetVal_u8=DCM_E_PENDING;
                    break;
                }

                case (Dem_ReturnClearDTCType)DEM_CLEAR_WRONG_DTC:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_WRONG_DTCORIGIN:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_FAILED:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_MEMORY_ERROR:
                default:
                {

                    DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_PARAM)
                    *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                    break;
                }
            }
        }

        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_UNINIT)
        {

            DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_UNINIT)

            *dataNegRespCode_u8  = DCM_E_SUBFUNCTIONNOTSUPPORTED; ;
        }
     }

        if(*dataNegRespCode_u8 != 0x0u)
        {

            Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
            dataRetVal_u8=E_NOT_OK;
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

