
#include "DcmDspUds_Rdtc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))

#define DCM_RDTC_RESPONSELENGTH_0x01   (0x01u)
#define DCM_RDTC_RESPONSELENGTH_0x02   (0x02u)
#define DCM_RDTC_RESPONSELENGTH_0x06   (0x06u)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType Dcm_Dsp_ReportFailedDTC (Dcm_SrvOpStatusType OpStatus,  \
                                       Dcm_MsgContextType *pMsgContext,\
                                       Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
   static uint8      dataStatusAvailMask_u8;
   static uint32     dataDTC_u32;
    Std_ReturnType    dataRetGetDTCByOccurTime_u8;
    Std_ReturnType    dataRetGetStatusOfDTC_u8;
    Std_ReturnType    dataRetGetSelectDTC_u8;
    Std_ReturnType    dataRetVal_u8;
   uint8             stDTCStatus_u8;
   uint8             dataRDTCSubFunc_u8;
   boolean           flgSubFnSupp_b;
    Dem_DTCRequestType DTCRequest;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8      =0x00;

    flgSubFnSupp_b = TRUE;
    dataRetGetDTCByOccurTime_u8 = E_NOT_OK;

    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
    dataRetVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {
        if(pMsgContext->reqDataLen == DSP_RDTC_B_C_D_E_REQLEN)
        {

             if(E_OK == Dem_GetDTCStatusAvailabilityMask(ClientId_u8,&dataStatusAvailMask_u8))
             {

                 pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

                 pMsgContext->resDataLen=1;

                 if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_TEST_FAILED_DTC)
                 {
                     DTCRequest = DEM_FIRST_FAILED_DTC;
                 }
                 else if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_CONFIRMED_DTC)
                 {
                     DTCRequest = DEM_FIRST_DET_CONFIRMED_DTC;
                 }
                 else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_TEST_FAILED_DTC)
                 {
                     DTCRequest = DEM_MOST_RECENT_FAILED_DTC;
                 }
                 else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_CONFIRMED_DTC)
                 {
                     DTCRequest = DEM_MOST_REC_DET_CONFIRMED_DTC;
                 }
                 else
                 {

                     flgSubFnSupp_b = FALSE;

                     dataRetVal_u8=E_OK;
                 }

                 if(flgSubFnSupp_b != FALSE)
                 {

                     dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(ClientId_u8,\
                                                                              DTCRequest,\
                                                                              &dataDTC_u32);

                     if((E_OK == dataRetGetDTCByOccurTime_u8) && (*dataNegRespCode_u8 == 0x00))
                     {
                         dataRetGetSelectDTC_u8 = Dem_SelectDTC(ClientId_u8,\
                                                                dataDTC_u32,\
                                                                DEM_DTC_FORMAT_UDS,\
                                                                DEM_DTC_ORIGIN_PRIMARY_MEMORY);

                         if(E_OK == dataRetGetSelectDTC_u8)
                         {
                             Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                         }
                         else
                         {
                             *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetSelectDTC_u8);
                             dataRetVal_u8 = E_NOT_OK;
                         }
                     }

                     else if(DEM_NO_SUCH_ELEMENT == dataRetGetDTCByOccurTime_u8)
                     {
                         pMsgContext->resData[1] = dataStatusAvailMask_u8;
                         pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x02;

                         dataRetVal_u8=E_OK;
                     }
                     else
                     {
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
   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {

        dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(ClientId_u8,&stDTCStatus_u8);

        if(E_OK == dataRetGetStatusOfDTC_u8)
        {

            pMsgContext->resData[1] = dataStatusAvailMask_u8;
            pMsgContext->resData[2] = (uint8)(dataDTC_u32>>16u);
            pMsgContext->resData[3] = (uint8)(dataDTC_u32>>8u);
            pMsgContext->resData[4] = (uint8)(dataDTC_u32);
            pMsgContext->resData[5] = stDTCStatus_u8;

            pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x06;

            dataRetVal_u8=E_OK;
        }

        else if(DEM_NO_SUCH_ELEMENT == dataRetGetStatusOfDTC_u8)
        {

            pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

            pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x01;

             dataRetVal_u8=E_OK;
        }

        else if(DEM_PENDING == dataRetGetStatusOfDTC_u8)
        {

            dataRetVal_u8 = DCM_E_PENDING;
        }
        else{
            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetStatusOfDTC_u8);
            dataRetVal_u8 = E_NOT_OK;
        }
   }

    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif
