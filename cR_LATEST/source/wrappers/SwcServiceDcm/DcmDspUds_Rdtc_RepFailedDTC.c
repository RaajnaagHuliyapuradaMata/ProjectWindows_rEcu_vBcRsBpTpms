#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFailedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,     AUTOMATIC)    dataDTC_u32;
   VAR(Dem_ReturnGetDTCByOccurrenceTimeType,AUTOMATIC)    dataRetGetDTCByOccurTime_u8;
   VAR(Dem_ReturnGetStatusOfDTCType,AUTOMATIC)    dataRetGetStatusOfDTC_u8;
   VAR(uint8,AUTOMATIC)                           stDTCStatus_u8;
   VAR(uint8,     AUTOMATIC)    dataStatusAvailMask_u8;
   VAR(uint8,AUTOMATIC)                           dataRDTCSubFunc_u8;
   VAR(Std_ReturnType,AUTOMATIC)                  dataRetVal_u8;
   VAR(boolean,     AUTOMATIC) flgSubFnSupp_b;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8      =0x00;
    dataDTC_u32 = 0x00;

    flgSubFnSupp_b = TRUE;
    dataRetGetDTCByOccurTime_u8 = DEM_OCCURR_FAILED;

    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
    dataRetVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(pMsgContext->reqDataLen == DSP_RDTC_B_C_D_E_REQLEN)
   {

        if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
        {

            pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

            pMsgContext->resDataLen=1;
            if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_TEST_FAILED_DTC)
            {

                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_FIRST_FAILED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_CONFIRMED_DTC)
            {

                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_FIRST_DET_CONFIRMED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_TEST_FAILED_DTC)
            {

                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_MOST_RECENT_FAILED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_CONFIRMED_DTC)
            {

                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_MOST_REC_DET_CONFIRMED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else{

                flgSubFnSupp_b = FALSE;

                dataRetVal_u8=E_OK;
            }

            if(flgSubFnSupp_b != FALSE)
            {
                if((DEM_OCCURR_OK == dataRetGetDTCByOccurTime_u8) && (*dataNegRespCode_u8 == 0x00))
                {

                    dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(dataDTC_u32,DEM_DTC_KIND_ALL_DTCS,DEM_DTC_ORIGIN_PRIMARY_MEMORY,&stDTCStatus_u8);
                    if(DEM_STATUS_OK == dataRetGetStatusOfDTC_u8)
                    {

                        pMsgContext->resData[1] = dataStatusAvailMask_u8;
                        pMsgContext->resData[2] = (uint8)(dataDTC_u32>>16u);
                        pMsgContext->resData[3] = (uint8)(dataDTC_u32>>8u);
                        pMsgContext->resData[4] = (uint8)(dataDTC_u32);
                        pMsgContext->resData[5] = stDTCStatus_u8;

                        pMsgContext->resDataLen = 6;

                        dataRetVal_u8=E_OK;
                    }

                    else if(DEM_STATUS_FAILED==dataRetGetStatusOfDTC_u8)
                    {

                        pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                        pMsgContext->resDataLen = 0x01;

                         dataRetVal_u8=E_OK;
                    }

                    else if((DEM_STATUS_WRONG_DTC == dataRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== dataRetGetStatusOfDTC_u8)||       \
                            (DEM_STATUS_WRONG_DTCKIND== dataRetGetStatusOfDTC_u8))
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                         dataRetVal_u8=E_NOT_OK;
                    }

                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                         dataRetVal_u8=E_NOT_OK;
                    }
                }

                else if(DEM_OCCURR_FAILED == dataRetGetDTCByOccurTime_u8)
                {
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 2;

                    dataRetVal_u8=E_OK;
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                    dataRetVal_u8=E_NOT_OK;
                }
            }
        }
        else{
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

            dataRetVal_u8=E_NOT_OK;
        }
   }
   else{
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;

        dataRetVal_u8=E_NOT_OK;
   }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif
