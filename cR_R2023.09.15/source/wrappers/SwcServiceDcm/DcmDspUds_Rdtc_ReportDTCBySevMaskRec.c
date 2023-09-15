#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCBySeverityMaskRecord
                                  (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,     AUTOMATIC)  dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC)  nrResDataLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC)  nrResMaxDataLen_u32;
   VAR(uint16,     AUTOMATIC)  nrFltDTC_u16;
   VAR(uint8_least,     AUTOMATIC)  idxLoop_qu8;
   VAR(uint8,     AUTOMATIC)  dataDTCFunctionalUnit_u8;
   VAR(uint8,     AUTOMATIC)  dataStatusAvailMask_u8;
   VAR(uint8,     AUTOMATIC)  stDTCStatus_u8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC)  dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)  dataretGetNextFiltDTC_u8;
   VAR(Dem_DTCSeverityType,     AUTOMATIC)  dataDTCSeverity_u8;
   VAR(Std_ReturnType,     AUTOMATIC)  dataretVal_u8;
   static VAR(boolean, DCM_VAR) dataPending_flag_b;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8     = 0x00;
    dataretGetNextFiltDTC_u8 = DEM_FILTERED_OK;
    dataretVal_u8 = DCM_E_PENDING;

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

        if(pMsgContext->reqDataLen == DSP_REPDTCBYSEVMASK_REQLEN )
        {

            dataDTCSeverity_u8 = pMsgContext->reqData[1] ;

            if((dataDTCSeverity_u8 & 0x1Fu) == 0x00u)
            {

                if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
                {

                    Dcm_DspRDTCFilledRespLen_u32 = 0x0;
                    Dcm_DspTotalRespLenFilled_u32 = 0x0;

                    Dcm_DspFillZeroes_b     = FALSE;

                    stDTCStatus_u8 = pMsgContext->reqData[2];

                    pMsgContext->resData[0] = DSP_REPORT_DTC_BY_SEVERITY_MASK;
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;

                    stDTCStatus_u8 = (stDTCStatus_u8 & dataStatusAvailMask_u8);

                    if(stDTCStatus_u8 != 0x0)
                    {

                        dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(   stDTCStatus_u8
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     DEM_DTC_FORMAT_UDS
   ,     DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,     DEM_FILTER_WITH_SEVERITY_YES
   ,     dataDTCSeverity_u8
   ,     DEM_FILTER_FOR_FDC_NO
                                                             );
                        if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                        {

                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
                        }
                        else
                        {

                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            dataretVal_u8 = E_NOT_OK;
                        }
                    }
                    else
                    {

                        dataretVal_u8 = E_OK;
                    }

                }

                else{

                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8 = E_NOT_OK;
            }
        }

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8 = E_NOT_OK;
        }
   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
   {

        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

        if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
        {

            if(nrFltDTC_u16 !=0)
            {

                pMsgContext->resDataLen = (Dcm_MsgLenType)((Dcm_MsgLenType)(nrFltDTC_u16 * 0x06u) + (Dcm_MsgLenType)0x02);

                if((Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE) && (pMsgContext->resMaxDataLen > 7u))
                {

                    Dcm_DspFirstPageSent_b  = FALSE;

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    Dcm_StartPagedProcessing(pMsgContext);

                    Dcm_DspRDTCFilledRespLen_u32 = 0x02;
                    Dcm_DspTotalRespLenFilled_u32 = 0x02;

                }
                else{

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else{

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8 = E_OK;
            }
        }

        else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
        {

        }
        else{

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8 = E_NOT_OK;
        }
   }

   else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        idxLoop_qu8 = 0;

        nrResMaxDataLen_u32 = Dcm_DspRDTCMaxRespLen_u32;

        do
        {
            idxLoop_qu8++;

            dataretGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndSeverity(&dataDTC_u32
   ,     &stDTCStatus_u8
   ,     &dataDTCSeverity_u8
   ,     &dataDTCFunctionalUnit_u8);

            if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                if(Dcm_DsldPduInfo_st.SduLength != 0u)
                {
                    if(dataPending_flag_b == FALSE)
                    {
                        nrResDataLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }
                }

                 nrResDataLen_u32 = Dcm_DspRDTCFilledRespLen_u32;

                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = dataDTCSeverity_u8;
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = dataDTCFunctionalUnit_u8;
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32>>16u);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32>>8u);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = stDTCStatus_u8;
                nrResDataLen_u32++;

                Dcm_DspRDTCFilledRespLen_u32 = nrResDataLen_u32;

                Dcm_DspTotalRespLenFilled_u32 = Dcm_DspTotalRespLenFilled_u32 + (uint32)0x06;

                if(Dcm_DspTotalRespLenFilled_u32 >=  pMsgContext->resDataLen)
                {
                    dataretGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }

            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                break;
            }

            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {

            }
            else{

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    dataretVal_u8 = E_NOT_OK;
                }

                else{

                    Dcm_ProcessPage(0);

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                }
            }

            if((dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC) || (((Dcm_DspRDTCFilledRespLen_u32 + 0x06u) > nrResMaxDataLen_u32) && (Dcm_IsProtocolIPCanFD()!=FALSE))|| ((Dcm_DspRDTCFilledRespLen_u32>=7u)&&(Dcm_IsProtocolIPCanFD()==FALSE)))
            {

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    Dcm_DspFirstPageSent_b = TRUE;
                }

                if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                {
                    if((Dcm_DsldPduInfo_st.SduLength != 0u)&& (dataPending_flag_b == FALSE))
                    {
                        nrResDataLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }

                    nrResDataLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;
                    Dcm_Dsp_RDTCFillZero(nrResDataLen_u32);

                }
   			if(
   			        ((Dcm_DspRDTCFilledRespLen_u32 + 0x6u) >= Dcm_DslTransmit_st.TxResponseLength_u32)
   			        ||
   			        ((Dcm_DspRDTCFilledRespLen_u32 + 0x6u )>=   nrResMaxDataLen_u32)
   			        ||
   			        ((Dcm_DspTotalRespLenFilled_u32 + 1u)>= Dcm_DslTransmit_st.TxResponseLength_u32)
   			        )
                {

   			    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

   			    Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
   			    dataPending_flag_b = FALSE;

   			    Dcm_DspRDTCFilledRespLen_u32 = 0x0;

   			    dataretGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }

        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK));
   }
   else
   {

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
   {

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
   {
        if((Dcm_DsldPduInfo_st.SduLength != 0u )&& (dataPending_flag_b == FALSE))
        {
            nrResDataLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            dataPending_flag_b = TRUE;
        }

        nrResDataLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;
        Dcm_Dsp_RDTCFillZero(nrResDataLen_u32);

        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        dataPending_flag_b =FALSE;

        Dcm_DspRDTCFilledRespLen_u32 = 0;
   }
        return dataretVal_u8;
}

#else

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCBySeverityMaskRecord
                                  (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(uint32,     AUTOMATIC)  dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC)  nrResDataLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC)  nrResMaxDataLen_u32;
   VAR(uint8_least,     AUTOMATIC)  idxLoop_qu8;
   VAR(uint8,     AUTOMATIC)  dataDTCFunctionalUnit_u8;
   VAR(uint8,     AUTOMATIC)  dataStatusAvailMask_u8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC)     dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)  dataretGetNextFiltDTC_u8;
   VAR(uint8,     AUTOMATIC)  stDTCStatus_u8;
   VAR(Dem_DTCSeverityType,     AUTOMATIC)  dataDTCSeverity_u8;
   VAR(Std_ReturnType,     AUTOMATIC)  dataretVal_u8;

    (void)OpStatus;

    *dataNegRespCode_u8     = 0x00;
    dataretVal_u8 = DCM_E_PENDING;

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

        if(pMsgContext->reqDataLen == DSP_REPDTCBYSEVMASK_REQLEN )
        {

            dataDTCSeverity_u8 = pMsgContext->reqData[1] ;

            if((dataDTCSeverity_u8 & 0x1Fu) == 0x00u)
            {

                if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
                {

                    stDTCStatus_u8 = pMsgContext->reqData[2];

                    pMsgContext->resData[0] = DSP_REPORT_DTC_BY_SEVERITY_MASK;
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;

                    stDTCStatus_u8 = (stDTCStatus_u8 & dataStatusAvailMask_u8);

                    if(stDTCStatus_u8 != 0x0)
                    {

                        dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(   stDTCStatus_u8
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     DEM_DTC_FORMAT_UDS
   ,     DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,     DEM_FILTER_WITH_SEVERITY_YES
   ,     dataDTCSeverity_u8
   ,     DEM_FILTER_FOR_FDC_NO
                                                             );
                        if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                        {

                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                        }
                        else
                        {

                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            dataretVal_u8 = E_NOT_OK;
                        }
                    }
                    else
                    {

                        dataretVal_u8 = E_OK;
                    }

                }

                else{

                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8 = E_NOT_OK;
            }
        }

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8 = E_NOT_OK;
        }
   }

   else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        idxLoop_qu8 = 0;

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        nrResDataLen_u32 = pMsgContext->resDataLen;

        do
        {
            idxLoop_qu8++;

            dataretGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndSeverity(&dataDTC_u32
   ,     &stDTCStatus_u8
   ,     &dataDTCSeverity_u8
   ,     &dataDTCFunctionalUnit_u8);

            if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {

                if((nrResDataLen_u32 + 0x06u) <= nrResMaxDataLen_u32)
                {

                    pMsgContext->resData[nrResDataLen_u32] = dataDTCSeverity_u8;
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = dataDTCFunctionalUnit_u8;
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32>>16u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32>>8u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = stDTCStatus_u8;
                    nrResDataLen_u32++;
                }
                else{

                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8 = E_NOT_OK;
                }
            }

            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                break;
            }

            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                idxLoop_qu8            = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataretVal_u8 = E_OK;
            }

            else{
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8 = E_NOT_OK;
            }
        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));

        pMsgContext->resDataLen = nrResDataLen_u32;
   }
   else
   {

   }
    return dataretVal_u8;
}
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

