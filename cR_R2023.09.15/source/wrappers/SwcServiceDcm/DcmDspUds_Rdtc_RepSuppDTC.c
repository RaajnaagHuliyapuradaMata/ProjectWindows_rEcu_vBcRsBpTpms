#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#if(   (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF)\
                               \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)\
                                 \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
static FUNC(Dcm_MsgLenType, DCM_CODE)Dcm_Dsp_CalTotalResLengthForDTC(VAR(uint16,AUTOMATIC) NumOfFltDTC_u16,VAR(uint8,AUTOMATIC) reqSubfunction);
#endif
static FUNC(uint8, DCM_CODE)Dcm_Dsp_GetDTCRequestLength(CONST(uint8,AUTOMATIC) reqSubfunction);
static FUNC(uint8, DCM_CODE)Dcm_Dsp_CalDTCActiveMask(CONST(uint8,AUTOMATIC) statusAvailMask_u8
   ,     CONST(uint8,AUTOMATIC) reqDtcStatus_u8
   ,     CONST(uint8,AUTOMATIC) reqSubfunction);
static FUNC(void, DCM_CODE)Dcm_Dsp_CalDTCKindAndOrigin(P2VAR(Dem_DTCOriginType,AUTOMATIC,DCM_INTERN_DATA) dataDtcOrigin_u8
   ,     P2VAR(Dem_DTCKindType,AUTOMATIC,DCM_INTERN_DATA) dataDtcKind_u8
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) dataDtcStatus_u8
   ,     CONST(uint8,AUTOMATIC) reqSubfunction
   ,     CONST(uint8,AUTOMATIC) reqDtcOriginData);
static FUNC(void, DCM_CODE)Dcm_Dsp_FillResBytesAndLength(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     CONST(uint8,AUTOMATIC) reqSubfunction
   ,     CONST(uint8,AUTOMATIC) statusAvailMask_u8);
static FUNC(Dem_ReturnGetNextFilteredDTCType, DCM_CODE)Dcm_Dsp_FillResDtcBuffer(VAR(uint32,AUTOMATIC) dtcData_u32
   ,     P2VAR(Dcm_MsgLenType,AUTOMATIC,DCM_INTERN_DATA) respLenNr_u32
   ,     VAR(uint8,AUTOMATIC) stDTCStatus_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
                                                                               );

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSupportedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(uint8_least,     AUTOMATIC) idxLoop_qu8;
   VAR(Dcm_MsgLenType,     AUTOMATIC) nrRespLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) nrResMaxDataLen_u32;
   VAR(uint16,     AUTOMATIC) nrFltDTC_u16;
   VAR(uint8,     AUTOMATIC) nrReqLength_u8;
   VAR(uint8,     AUTOMATIC) dataStatusAvailMask_u8;
   VAR(uint8,     AUTOMATIC) stDTCStatus_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType,    AUTOMATIC) dataRetGetNextFiltDTC_u8;
   VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC) dataRetSetDTCFilter_u8;
   VAR(uint8,     AUTOMATIC) dataSubfunc_u8;
   VAR(Dem_DTCOriginType,     AUTOMATIC) dataDemDTCOrigin_u8;
   VAR(Dem_DTCKindType,     AUTOMATIC) dataDemDTCKind_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataretVal_u8;
   VAR(boolean,     AUTOMATIC) IsProtocolIPCanFD_b;
   static VAR(boolean,     DCM_VAR) dataPending_flag_b;

    dataRetGetNextFiltDTC_u8 = DEM_FILTERED_OK;
    *dataNegRespCode_u8     = 0x0;
    dataretVal_u8 = DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

        dataSubfunc_u8 = pMsgContext->reqData[0];

        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

            if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
            {

                Dcm_DspRDTCFilledRespLen_u32 = 0x00;
                Dcm_DspTotalRespLenFilled_u32 = 0x00;

                Dcm_DspFillZeroes_b     = FALSE;

                stDTCStatus_u8 = dataStatusAvailMask_u8;

                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                if(stDTCStatus_u8 != 0x0)
                {

                    dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

                    dataDemDTCKind_u8 = DEM_DTC_KIND_ALL_DTCS;

                    Dcm_Dsp_CalDTCKindAndOrigin(&dataDemDTCOrigin_u8
   ,     &dataDemDTCKind_u8
   ,     &stDTCStatus_u8
   ,     dataSubfunc_u8
   ,     pMsgContext->reqData[2]
                                               );

                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(stDTCStatus_u8
   ,     dataDemDTCKind_u8
   ,     DEM_DTC_FORMAT_UDS
   ,     dataDemDTCOrigin_u8
   ,     DEM_FILTER_WITH_SEVERITY_NO
   ,     DEM_SEVERITY_NO_SEVERITY
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
                else{

                    dataretVal_u8 = E_OK;
                }

                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }

            else{

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
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
        dataSubfunc_u8 = pMsgContext->reqData[0];

        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

        if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
        {

            if(nrFltDTC_u16 !=0)
            {

                pMsgContext->resDataLen = Dcm_Dsp_CalTotalResLengthForDTC(nrFltDTC_u16,dataSubfunc_u8);

                if(Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE)
                {

                    Dcm_DspFirstPageSent_b  = FALSE;

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    Dcm_StartPagedProcessing(pMsgContext);

                    Dcm_DspRDTCFilledRespLen_u32 = 2;
                    Dcm_DspTotalRespLenFilled_u32 = 2;

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                    if(dataSubfunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                    {

                        Dcm_DspRDTCFilledRespLen_u32 = 3;
                        Dcm_DspTotalRespLenFilled_u32 = 3;
                    }
#endif
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

            dataretVal_u8 = DCM_E_PENDING;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8 = E_NOT_OK;
        }
   }

   else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        idxLoop_qu8 = 0;

        nrResMaxDataLen_u32 = Dcm_DspRDTCMaxRespLen_u32;

        do
        {
            idxLoop_qu8++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(&dataDTC_u32, &stDTCStatus_u8);

            if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                if(   (Dcm_DsldPduInfo_st.SduLength != 0u)
                     &&(dataPending_flag_b == FALSE)
                   )
                {
                    nrRespLen_u32 = 0 ;
                    Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                    dataPending_flag_b = TRUE;
                }

                dataRetGetNextFiltDTC_u8 = Dcm_Dsp_FillResDtcBuffer(dataDTC_u32,&nrRespLen_u32,stDTCStatus_u8,pMsgContext);
            }

            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {

                dataretVal_u8 = DCM_E_PENDING;
                break;
            }

            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
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

            IsProtocolIPCanFD_b = Dcm_IsProtocolIPCanFD();

            if(     ((IsProtocolIPCanFD_b) && ((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > nrResMaxDataLen_u32))
                ||  ((!IsProtocolIPCanFD_b) && (Dcm_DspRDTCFilledRespLen_u32>=7u))
                ||  (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
              )
            {

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    Dcm_DspFirstPageSent_b = TRUE;
                }

                if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                {
                    if((Dcm_DsldPduInfo_st.SduLength != 0u) && (dataPending_flag_b == FALSE))
                    {
                        nrRespLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }

                    nrRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;
                    Dcm_Dsp_RDTCFillZero(nrRespLen_u32);
                }

                if(  ((Dcm_DspRDTCFilledRespLen_u32 +2u) >= Dcm_DslTransmit_st.TxResponseLength_u32)
                   ||((Dcm_DspRDTCFilledRespLen_u32 +2u) >= nrResMaxDataLen_u32)
                   ||((Dcm_DspTotalRespLenFilled_u32+1u) >= Dcm_DslTransmit_st.TxResponseLength_u32)
                  )
                {

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

                    Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
                    dataPending_flag_b =FALSE;

                    Dcm_DspRDTCFilledRespLen_u32 = 0x0;

                    dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }

        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK));
   }
   else{

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
   {

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
   {
        if((Dcm_DsldPduInfo_st.SduLength != 0u ) && (dataPending_flag_b == FALSE))
        {
            nrRespLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            dataPending_flag_b = TRUE;
        }

        nrRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;
        Dcm_Dsp_RDTCFillZero(nrRespLen_u32);

        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        dataPending_flag_b = FALSE ;
        Dcm_DspRDTCFilledRespLen_u32 = 0;
   }
    return dataretVal_u8;
}

static FUNC(Dcm_MsgLenType, DCM_CODE)Dcm_Dsp_CalTotalResLengthForDTC(VAR(uint16,AUTOMATIC) NumOfFltDTC_u16, VAR(uint8,AUTOMATIC) reqSubfunction)
{
    Dcm_MsgLenType totalLength = 0;

    totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x02);
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
   if(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
   {
        totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x03);
   }
#endif
    return totalLength;
}

#else

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSupportedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) nrRespLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) nrResMaxDataLen_u32;
   VAR(uint8_least,     AUTOMATIC) idxLoop_qu8;
   VAR(uint8,     AUTOMATIC) nrReqLength_u8;
   VAR(uint8,     AUTOMATIC) stDTCStatus_u8;
   VAR(uint8,     AUTOMATIC) dataStatusAvailMask_u8;
   VAR(uint8,     AUTOMATIC) dataSubfunc_u8;
   VAR(Dem_DTCOriginType,     AUTOMATIC) dataDemDTCOrigin_u8;
   VAR(Dem_DTCKindType,     AUTOMATIC) dataDemDTCKind_u8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC) dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataretVal_u8;
    (void)OpStatus;

    *dataNegRespCode_u8 = 0x0;
    dataretVal_u8=DCM_E_PENDING;

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

        dataSubfunc_u8 = pMsgContext->reqData[0];

        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

            if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
            {

                stDTCStatus_u8  = dataStatusAvailMask_u8;

                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                if(stDTCStatus_u8 != 0x0u)
                {

                    dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

                    dataDemDTCKind_u8 = DEM_DTC_KIND_ALL_DTCS;

                     Dcm_Dsp_CalDTCKindAndOrigin(&dataDemDTCOrigin_u8
   ,     &dataDemDTCKind_u8
   ,     &stDTCStatus_u8
   ,     dataSubfunc_u8
   ,     pMsgContext->reqData[2]
                                                );

                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(stDTCStatus_u8
   ,     dataDemDTCKind_u8
   ,     DEM_DTC_FORMAT_UDS
   ,     dataDemDTCOrigin_u8
   ,     DEM_FILTER_WITH_SEVERITY_NO
   ,     DEM_SEVERITY_NO_SEVERITY
   ,     DEM_FILTER_FOR_FDC_NO
                                                             );

                    if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                    {

                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                    }

                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataretVal_u8=E_NOT_OK;
                    }
                }
                else{

                    dataretVal_u8=E_OK;
                }

                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }

            else{

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
   }

   else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        idxLoop_qu8 = 0x00;

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        nrRespLen_u32 = pMsgContext->resDataLen;

        do
        {
            idxLoop_qu8++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(&dataDTC_u32, &stDTCStatus_u8);

            if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {

                if((nrRespLen_u32 + 0x04u) <= nrResMaxDataLen_u32)
                {
                   (void)Dcm_Dsp_FillResDtcBuffer(dataDTC_u32, &nrRespLen_u32, stDTCStatus_u8,pMsgContext);
                }
                else{

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8=E_NOT_OK;
                }
            }

            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {

                dataretVal_u8=DCM_E_PENDING;
                break;
            }

            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                idxLoop_qu8            = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataretVal_u8=E_OK;
            }
            else{

                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));

        pMsgContext->resDataLen = nrRespLen_u32;
   }
   else{

   }
    return dataretVal_u8;
}
#endif

static FUNC(uint8, DCM_CODE)Dcm_Dsp_GetDTCRequestLength(CONST(uint8,AUTOMATIC) reqSubfunction)
{
   VAR(uint8, AUTOMATIC) reqLength_u8;

    reqLength_u8 = DSP_RDTC_0A_15_REQLEN;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)|| \
                               \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)|| \
                                 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF))

   if(    (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)

         || (reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)

         || (reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
       )
   {
        reqLength_u8 = DSP_REPDTCBYSTMASK_REQLEN;
   }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
   if(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
   {

        reqLength_u8 = DSP_RDTC_17_REQLEN;
   }
#endif

    return reqLength_u8;
}

static FUNC(uint8, DCM_CODE)Dcm_Dsp_CalDTCActiveMask(CONST(uint8,AUTOMATIC) statusAvailMask_u8, CONST(uint8,AUTOMATIC) reqDtcStatus_u8,CONST(uint8,AUTOMATIC) reqSubfunction )
{
   uint8 calDTCStatus_u8 = statusAvailMask_u8;

#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)   \
                                 \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)   \
                                   \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)   \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

                if(     (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)

                      ||(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)

                      ||(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                      ||(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                  )
                {

                    calDTCStatus_u8 = (statusAvailMask_u8 & reqDtcStatus_u8);
                }
#endif

    return calDTCStatus_u8;
}

static FUNC(void, DCM_CODE)Dcm_Dsp_CalDTCKindAndOrigin(P2VAR(Dem_DTCOriginType,AUTOMATIC,DCM_INTERN_DATA) dataDtcOrigin_u8
   ,     P2VAR(Dem_DTCKindType,AUTOMATIC,DCM_INTERN_DATA) dataDtcKind_u8,

                        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) dataDtcStatus_u8
   ,     CONST(uint8,AUTOMATIC) reqSubfunction
   ,     CONST(uint8,AUTOMATIC) reqDtcOriginData
                                                      )
{

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                    if(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                    {

                        *dataDtcOrigin_u8 = reqDtcOriginData;
                    }
#else
                    DCM_UNUSED_PARAM(reqDtcOriginData);
#endif

#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF))

                    if(  (reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)
                       ||(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                      )
                    {

                        *dataDtcStatus_u8 = DSP_REPORT_ALL_DTC;
                    }

                    if(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                    {

                        *dataDtcOrigin_u8 = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
                    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)

                    if(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                    {

                        *dataDtcOrigin_u8 = DEM_DTC_ORIGIN_MIRROR_MEMORY;
                    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)

                    if(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                    {

                        *dataDtcKind_u8 = DEM_DTC_KIND_EMISSION_REL_DTCS;
                    }
#else
                    DCM_UNUSED_PARAM(dataDtcKind_u8);
#endif
}

static FUNC(void, DCM_CODE)Dcm_Dsp_FillResBytesAndLength(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     CONST(uint8,AUTOMATIC) reqSubfunction
   ,     CONST(uint8,AUTOMATIC) statusAvailMask_u8)
{
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                if(reqSubfunction  == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                {
                    pMsgContext->resData[1] = pMsgContext->reqData[2];
                    pMsgContext->resData[2] = statusAvailMask_u8;
                    pMsgContext->resDataLen = 0x03;
                }
#endif

#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)\
                              \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)\
                                \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF))

                if(   (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)

                    ||(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)

                    ||(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                    ||(reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)
                    ||(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                  )
                {
                    pMsgContext->resData[1] = statusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;
                }

#endif

                pMsgContext->resData[0] = reqSubfunction;
}

static FUNC(Dem_ReturnGetNextFilteredDTCType, DCM_CODE)Dcm_Dsp_FillResDtcBuffer(    VAR(uint32,AUTOMATIC) dtcData_u32
   ,     P2VAR(Dcm_MsgLenType,AUTOMATIC,DCM_INTERN_DATA) respLenNr_u32
   ,     VAR(uint8,AUTOMATIC) stDTCStatus_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
                                                                               )
{
    Dem_ReturnGetNextFilteredDTCType RetGetNextFiltDtc = DEM_FILTERED_OK;

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

    *respLenNr_u32 = Dcm_DspRDTCFilledRespLen_u32;

    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32 >> 16u);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32 >> 8u);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = stDTCStatus_u8;
    (*respLenNr_u32)++;

    Dcm_DspRDTCFilledRespLen_u32 = *respLenNr_u32;

    Dcm_DspTotalRespLenFilled_u32 = (Dcm_DspTotalRespLenFilled_u32 + 0x04u);

   if(Dcm_DspTotalRespLenFilled_u32 >= pMsgContext->resDataLen)
   {
        RetGetNextFiltDtc = DEM_FILTERED_NO_MATCHING_DTC;
   }
#else

        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32 >> 16u);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32 >> 8u);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = stDTCStatus_u8;
        (*respLenNr_u32)++;

#endif
    return RetGetNextFiltDtc;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif

