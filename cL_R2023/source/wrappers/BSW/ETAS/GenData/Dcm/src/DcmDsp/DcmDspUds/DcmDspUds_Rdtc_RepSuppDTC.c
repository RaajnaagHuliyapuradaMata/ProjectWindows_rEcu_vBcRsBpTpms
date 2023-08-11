
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Rdtc_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(   (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF)\
                               \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)\
                                 \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static Dcm_MsgLenType Dcm_Dsp_CalTotalResLengthForDTC(uint16 NumOfFltDTC_u16, uint8 reqSubfunction);
static uint8 Dcm_Dsp_GetDTCRequestLength(const uint8 reqSubfunction);
static uint8 Dcm_Dsp_CalDTCActiveMask(const uint8 statusAvailMask_u8,const uint8 reqDtcStatus_u8,const uint8 reqSubfunction);
static void Dcm_Dsp_CalDTCOrigin(Dem_DTCOriginType *dataDtcOrigin_u16,uint8 *dataDtcStatus_u8,const uint8 reqSubfunction, \
        const uint8 reqDtcOriginData);
static void Dcm_Dsp_FillResBytesAndLength(Dcm_MsgContextType *pMsgContext,const uint8 reqSubfunction, \
                                          const uint8 statusAvailMask_u8);
static Std_ReturnType Dcm_Dsp_FillResDtcBuffer(uint32 dtcData_u32,Dcm_MsgLenType *respLenNr_u32, \
                                                       uint8 stDTCStatus_u8,const Dcm_MsgContextType *pMsgContext);

static Dcm_MsgLenType Dcm_Dsp_CalTotalResLengthForDTC(uint16 NumOfFltDTC_u16, uint8 reqSubfunction)
{
    Dcm_MsgLenType totalLength = 0;

    totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x02);
#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if (reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {
        totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x03);
    }
#else
    (void)reqSubfunction;
#endif
    return totalLength;
}

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

Std_ReturnType Dcm_Dsp_ReportSupportedDTC (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext,Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint32            dataDTC_u32;
    uint16            idxLoop_qu16;
    Dcm_MsgLenType    nrRespLen_u32;
    Dcm_MsgLenType    nrResMaxDataLen_u32;
    uint16            nrFltDTC_u16;
    uint8             nrReqLength_u8;
    uint8             dataStatusAvailMask_u8;
    uint8             stDTCStatus_u8;
    Std_ReturnType    dataRetGetNextFiltDTC_u8;
    Std_ReturnType    dataRetNumFltDTC_u8;
    Std_ReturnType    dataRetSetDTCFilter_u8;
    Dem_DTCOriginType dataDemDTCOrigin_u16;
    uint8             dataSubfunc_u8;
    Std_ReturnType    dataretVal_u8 = DCM_E_PENDING;
    boolean           IsProtocolIPCanFD_b;
    static boolean    isDataPending_flag_b;

    *dataNegRespCode_u8      = 0x0u;

    DCM_UNUSED_PARAM(OpStatus);

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {

        dataSubfunc_u8 = pMsgContext->reqData[0];

        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

            if(E_OK == Dem_GetDTCStatusAvailabilityMask(ClientId_u8,&dataStatusAvailMask_u8))
            {

                Dcm_DspRDTCFilledRespLen_u32  = 0x00;
                Dcm_DspTotalRespLenFilled_u32 = 0x00;

                Dcm_DspFillZeroes_b     = FALSE;

                stDTCStatus_u8 = dataStatusAvailMask_u8;

                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                if(stDTCStatus_u8 != 0x0)
                {
                    if(dataSubfunc_u8 == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                    {

                        dataDemDTCOrigin_u16 = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
                    }
                    else
                    {

                        dataDemDTCOrigin_u16 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                    }

                    Dcm_Dsp_CalDTCOrigin(&dataDemDTCOrigin_u16,&stDTCStatus_u8,dataSubfunc_u8,pMsgContext->reqData[2]);

                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(ClientId_u8,
                                                              stDTCStatus_u8,
                                                              DEM_DTC_FORMAT_UDS,
                                                              dataDemDTCOrigin_u16,
                                                              FALSE,
                                                              DEM_SEVERITY_NO_SEVERITY,
                                                              FALSE
                                                             );

                    if(E_OK == dataRetSetDTCFilter_u8)
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

                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }

            else
            {

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal_u8 = E_NOT_OK;
            }
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8 = E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
    {
        dataSubfunc_u8 = pMsgContext->reqData[0];

        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(ClientId_u8,&nrFltDTC_u16);

        if(E_OK == dataRetNumFltDTC_u8)
        {

            if(nrFltDTC_u16 != 0u)
            {

                pMsgContext->resDataLen = Dcm_Dsp_CalTotalResLengthForDTC(nrFltDTC_u16,dataSubfunc_u8);

                if(FALSE != Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen))
                {

                    Dcm_DspFirstPageSent_b  = FALSE;

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    Dcm_StartPagedProcessing(pMsgContext);

                    Dcm_DspRDTCFilledRespLen_u32 = 2;
                    Dcm_DspTotalRespLenFilled_u32 = 2;

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                    if(dataSubfunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                    {

                        Dcm_DspRDTCFilledRespLen_u32 = 3;
                        Dcm_DspTotalRespLenFilled_u32 = 3;
                    }
#endif
                }
                else
                {

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8 = E_OK;
            }
        }

        else if(DEM_PENDING == dataRetNumFltDTC_u8)
        {

            dataretVal_u8 = DCM_E_PENDING;
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8 = E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu16 = 0;

        nrResMaxDataLen_u32 = Dcm_DspRDTCMaxRespLen_u32;

        do
        {
            idxLoop_qu16++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(ClientId_u8,&dataDTC_u32, &stDTCStatus_u8);

            if(E_OK == dataRetGetNextFiltDTC_u8)
            {
                if ((Dcm_DsldPduInfo_st.SduLength != 0u) && (isDataPending_flag_b == FALSE))
                {
                    nrRespLen_u32 = 0 ;
                    Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                    isDataPending_flag_b = TRUE;
                }
                dataRetGetNextFiltDTC_u8 = Dcm_Dsp_FillResDtcBuffer(dataDTC_u32,&nrRespLen_u32,stDTCStatus_u8,pMsgContext);
            }

            else if(DEM_PENDING == dataRetGetNextFiltDTC_u8)
            {

                dataretVal_u8 = DCM_E_PENDING;
                break;
            }

            else if(DEM_NO_SUCH_ELEMENT == dataRetGetNextFiltDTC_u8)
            {

            }
            else
            {

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8 = E_NOT_OK;
                }

                else
                {

                    Dcm_ProcessPage(0);

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                }
            }

            IsProtocolIPCanFD_b = Dcm_IsProtocolIPCanFD();

            if(     ((IsProtocolIPCanFD_b) && ((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > nrResMaxDataLen_u32))
                ||  ((!IsProtocolIPCanFD_b) && (Dcm_DspRDTCFilledRespLen_u32>=7u))
                ||  (dataRetGetNextFiltDTC_u8 == DEM_NO_SUCH_ELEMENT)
              )
            {

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    Dcm_DspFirstPageSent_b = TRUE;
                }

                if(dataRetGetNextFiltDTC_u8 == DEM_NO_SUCH_ELEMENT)
                {
                    if((Dcm_DsldPduInfo_st.SduLength != 0u) && (isDataPending_flag_b == FALSE))
                    {
                        nrRespLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        isDataPending_flag_b = TRUE;
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
                    isDataPending_flag_b =FALSE;

                    Dcm_DspRDTCFilledRespLen_u32 = 0x0;

                    dataRetGetNextFiltDTC_u8 = DEM_NO_SUCH_ELEMENT;
                }
            }

        }while((idxLoop_qu16 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == E_OK));
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
    {

    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
    {
        if((Dcm_DsldPduInfo_st.SduLength != 0u ) && (isDataPending_flag_b == FALSE))
        {
            nrRespLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            isDataPending_flag_b = TRUE;
        }

        nrRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;
        Dcm_Dsp_RDTCFillZero(nrRespLen_u32);

        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        isDataPending_flag_b = FALSE ;
        Dcm_DspRDTCFilledRespLen_u32 = 0;
    }
    return dataretVal_u8;
}

#else

Std_ReturnType Dcm_Dsp_ReportSupportedDTC (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext,Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint32  dataDTC_u32;
    Dcm_MsgLenType  nrRespLen_u32;
    Dcm_MsgLenType  nrResMaxDataLen_u32;
    uint16  idxLoop_qu16;
    uint16  nrFltDTC_u16;
    uint8  nrReqLength_u8;
    uint8  stDTCStatus_u8;
    uint8  dataStatusAvailMask_u8;
    uint8  dataSubfunc_u8;
    Dem_DTCOriginType  dataDemDTCOrigin_u16;
    Std_ReturnType     dataRetSetDTCFilter_u8;
    Std_ReturnType     dataRetGetNextFiltDTC_u8;
    Std_ReturnType     dataretVal_u8 = DCM_E_PENDING;
    Std_ReturnType    dataRetNumFltDTC_u8;
    (void)OpStatus;

    *dataNegRespCode_u8 = 0x0;

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {

        dataSubfunc_u8 = pMsgContext->reqData[0];

        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

            if(E_OK == Dem_GetDTCStatusAvailabilityMask(ClientId_u8,&dataStatusAvailMask_u8))
            {

                stDTCStatus_u8  = dataStatusAvailMask_u8;

                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                if(stDTCStatus_u8 != 0x0u)
                {
                    if(dataSubfunc_u8 == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                    {

                        dataDemDTCOrigin_u16 = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
                    }
                    else
                    {

                        dataDemDTCOrigin_u16 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                    }

                    Dcm_Dsp_CalDTCOrigin(&dataDemDTCOrigin_u16,&stDTCStatus_u8,dataSubfunc_u8,pMsgContext->reqData[2]);

                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(ClientId_u8,
                                                              stDTCStatus_u8,
                                                              DEM_DTC_FORMAT_UDS,
                                                              dataDemDTCOrigin_u16,
                                                              FALSE,
                                                              DEM_SEVERITY_NO_SEVERITY,
                                                              FALSE
                                                             );

                    if(E_OK == dataRetSetDTCFilter_u8)
                    {

                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
                    }

                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataretVal_u8=E_NOT_OK;
                    }
                }
                else
                {

                    dataretVal_u8=E_OK;
                }

                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }

            else
            {

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
    {
        dataSubfunc_u8 = pMsgContext->reqData[0];

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

       dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(ClientId_u8,&nrFltDTC_u16);

       if(E_OK == dataRetNumFltDTC_u8)
       {

           if(nrFltDTC_u16 != 0u)
           {
               nrRespLen_u32 = Dcm_Dsp_CalTotalResLengthForDTC(nrFltDTC_u16,dataSubfunc_u8);

               if(nrRespLen_u32 <= nrResMaxDataLen_u32)
               {

                   Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
               }
               else
               {

                   *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                   dataretVal_u8 = E_NOT_OK;
               }
           }
           else
           {

               Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
               dataretVal_u8 = E_OK;
           }
       }

       else if(DEM_PENDING == dataRetNumFltDTC_u8)
       {

           dataretVal_u8 = DCM_E_PENDING;
       }
       else
       {

           *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
           dataretVal_u8 = E_NOT_OK;
       }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu16 = 0x00;

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        nrRespLen_u32 = pMsgContext->resDataLen;

        do
        {
            idxLoop_qu16++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(ClientId_u8,&dataDTC_u32, &stDTCStatus_u8);

            if(E_OK == dataRetGetNextFiltDTC_u8)
            {

                if((nrRespLen_u32 + 0x04u) <= nrResMaxDataLen_u32)
                {

                   (void)Dcm_Dsp_FillResDtcBuffer(dataDTC_u32, &nrRespLen_u32, stDTCStatus_u8,pMsgContext);
                }
                else
                {

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8=E_NOT_OK;
                }
            }

            else if(DEM_PENDING == dataRetGetNextFiltDTC_u8)
            {

                dataretVal_u8 = DCM_E_PENDING;
                break;
            }

            else if(DEM_NO_SUCH_ELEMENT == dataRetGetNextFiltDTC_u8)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                idxLoop_qu16           = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataretVal_u8 = E_OK;
            }
            else
            {

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal_u8=E_NOT_OK;
            }
        }while((idxLoop_qu16 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));

        pMsgContext->resDataLen = nrRespLen_u32;
    }

    return dataretVal_u8;
}
#endif

static uint8 Dcm_Dsp_GetDTCRequestLength(const uint8 reqSubfunction)
{
    uint8 reqLength_u8;

    reqLength_u8 = DSP_RDTC_0A_15_REQLEN;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)|| \
                               \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)|| \
                                 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF))

    if (    (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)

         || (reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)

         || (reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
       )
    {
        reqLength_u8 = DSP_REPDTCBYSTMASK_REQLEN;
    }
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if (reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {

        reqLength_u8 = DSP_RDTC_17_REQLEN;
    }
#endif

    return reqLength_u8;
}

static uint8 Dcm_Dsp_CalDTCActiveMask(const uint8 statusAvailMask_u8,const uint8 reqDtcStatus_u8,const uint8 reqSubfunction)
{
    uint8 calDTCStatus_u8 = statusAvailMask_u8;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF) ||  \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF) || \
                                \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF))

    if((reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK) || (reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC) || \
       (reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK) ||

       (reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK))

    {

        calDTCStatus_u8 = (statusAvailMask_u8 & reqDtcStatus_u8);
    }
#endif

    return calDTCStatus_u8;
}

static void Dcm_Dsp_CalDTCOrigin(Dem_DTCOriginType *dataDtcOrigin_u16,uint8 *dataDtcStatus_u8,const uint8 reqSubfunction, \
        const uint8 reqDtcOriginData)
{

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {

        *dataDtcOrigin_u16 = reqDtcOriginData + DCM_DTC_ORIGIN_MEMORY_SELECTION_VALUE;
    }
#else
    DCM_UNUSED_PARAM(reqDtcOriginData);
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF))

    if((reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)||(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS))
    {

        *dataDtcStatus_u8 = DSP_REPORT_ALL_DTC;
    }

    if(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
    {

        *dataDtcOrigin_u16 = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)

    if(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
    {

        *dataDtcOrigin_u16 = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
#endif
}

static void Dcm_Dsp_FillResBytesAndLength(Dcm_MsgContextType *pMsgContext,const uint8 reqSubfunction, \
                                          const uint8 statusAvailMask_u8)
{
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if(reqSubfunction  == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {
        pMsgContext->resData[1] = pMsgContext->reqData[2];
        pMsgContext->resData[2] = statusAvailMask_u8;
        pMsgContext->resDataLen = 0x03;
    }
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF) || \
      \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF))

    if((reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK) || (reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC) || \
       (reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)  || (reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS) || \

       (reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK))

    {
        pMsgContext->resData[1] = statusAvailMask_u8;
        pMsgContext->resDataLen = 0x02;
    }
#endif

    pMsgContext->resData[0] = reqSubfunction;
}

static Std_ReturnType Dcm_Dsp_FillResDtcBuffer(uint32 dtcData_u32,Dcm_MsgLenType *respLenNr_u32, \
                                                       uint8 stDTCStatus_u8,const Dcm_MsgContextType *pMsgContext)
{
    Std_ReturnType RetGetNextFiltDtc = E_OK;

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
        RetGetNextFiltDtc = DEM_NO_SUCH_ELEMENT;
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
#include "Dcm_MemMap.h"

#endif
#endif

