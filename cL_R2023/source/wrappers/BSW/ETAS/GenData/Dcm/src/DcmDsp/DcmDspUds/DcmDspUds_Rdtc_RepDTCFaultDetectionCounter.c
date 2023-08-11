
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Rdtc_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

Std_ReturnType Dcm_Dsp_ReportFaultDetectionCounter (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext,\
                                                                    Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint8_least                      cntrLoop_qu8;
    sint8                            cntrFault_s8;
    Std_ReturnType                   dataRetSetDTCFilter_u8;
    Std_ReturnType                   dataRetGetNextFiltDTC_u8;
    Std_ReturnType                   dataRetNumFltDTC_u8;
    uint16                           nrFltDTC_u16;
    uint32                           dataDTC_u32;
    Dcm_MsgLenType                   dataRespLen_u32;
    Dcm_MsgLenType                   dataResMaxLen_u32;
    Std_ReturnType                   dataServRetval_u8 = DCM_E_PENDING;
    boolean                          isProtocolIPCanFD_b = FALSE;
    static boolean                   RdtcDataPending_flag_b;

    *dataNegRespCode_u8      = 0x0;

    DCM_UNUSED_PARAM(OpStatus);

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {

        if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
        {

            Dcm_DspRDTCFilledRespLen_u32 = 0x0;
            Dcm_DspTotalRespLenFilled_u32 = 0x0;

            Dcm_DspFillZeroes_b     = FALSE;

            dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(ClientId_u8,
                                                    0x00,
                                                    DEM_DTC_FORMAT_UDS,
                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                    FALSE,
                                                    DEM_SEVERITY_NO_SEVERITY,
                                                    TRUE
                                                    );

            if(E_OK == dataRetSetDTCFilter_u8)
            {

                pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

                pMsgContext->resDataLen=1;

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
            }

            else
            {
                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetSetDTCFilter_u8);
                dataServRetval_u8=E_NOT_OK;
            }
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;

            dataServRetval_u8=E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
    {

        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(ClientId_u8,&nrFltDTC_u16);

        if(E_OK == dataRetNumFltDTC_u8)
        {

            if(nrFltDTC_u16 !=0)
            {

                pMsgContext->resDataLen = (Dcm_MsgLenType)(nrFltDTC_u16);
                pMsgContext->resDataLen <<= (Dcm_MsgLenType)0x02u;
                pMsgContext->resDataLen += (Dcm_MsgLenType)(0x01u);

                if(Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE)
                {

                    Dcm_DspFirstPageSent_b  = FALSE;

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    Dcm_StartPagedProcessing(pMsgContext);

                    Dcm_DspRDTCFilledRespLen_u32 = 0x01;
                    Dcm_DspTotalRespLenFilled_u32 = 0x01;

                }
                else
                {

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;

                    dataServRetval_u8=E_NOT_OK;
                }
            }
            else
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataServRetval_u8=E_OK;
            }
        }

        else if(DEM_PENDING == dataRetNumFltDTC_u8)
        {

            dataServRetval_u8=DCM_E_PENDING;
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

            dataServRetval_u8=E_NOT_OK;
        }
    }

    if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        cntrLoop_qu8 = 0;

        dataResMaxLen_u32 = pMsgContext->resMaxDataLen;

        do
        {
            cntrLoop_qu8++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(ClientId_u8,&dataDTC_u32, &cntrFault_s8);

            if(E_OK == dataRetGetNextFiltDTC_u8)
            {
                if (Dcm_DsldPduInfo_st.SduLength != 0u)
                {
                    if (RdtcDataPending_flag_b == FALSE)
                    {
                        dataRespLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        RdtcDataPending_flag_b = TRUE;
                    }
                }

                dataRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32;

                Dcm_DspRDTCRespBufPtr_u8[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 16u);
                dataRespLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 8u);
                dataRespLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[dataRespLen_u32] = (uint8)(dataDTC_u32);
                dataRespLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[dataRespLen_u32] = (uint8)(cntrFault_s8);
                dataRespLen_u32++;

                Dcm_DspRDTCFilledRespLen_u32 = dataRespLen_u32;

                Dcm_DspTotalRespLenFilled_u32 = (Dcm_DspTotalRespLenFilled_u32 + 0x04u);

                if(Dcm_DspTotalRespLenFilled_u32 >=  pMsgContext->resDataLen)
                {
                    dataRetGetNextFiltDTC_u8 = DEM_NO_SUCH_ELEMENT;
                }

            }

            else if(DEM_PENDING == dataRetGetNextFiltDTC_u8 )
            {

                dataServRetval_u8=DCM_E_PENDING;
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

                    dataServRetval_u8=E_NOT_OK;

                }

                else
                {

                    Dcm_ProcessPage(0);

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                }
            }

            isProtocolIPCanFD_b = Dcm_IsProtocolIPCanFD();
            if((dataRetGetNextFiltDTC_u8 == DEM_NO_SUCH_ELEMENT) || (((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > dataResMaxLen_u32) && (isProtocolIPCanFD_b!=FALSE))||  ((Dcm_DspRDTCFilledRespLen_u32>=7u)&&(isProtocolIPCanFD_b==FALSE)))
            {

                if(Dcm_DspFirstPageSent_b == FALSE)
                {

                    Dcm_DspFirstPageSent_b = TRUE;
                }
                if(dataRetGetNextFiltDTC_u8 == DEM_NO_SUCH_ELEMENT)
                {

                    dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;

                    Dcm_Dsp_RDTCFillZero(dataRespLen_u32);
                }

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

                Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
                RdtcDataPending_flag_b = FALSE;

                Dcm_DspRDTCFilledRespLen_u32 = 0x0;

                dataRetGetNextFiltDTC_u8 = DEM_NO_SUCH_ELEMENT;
            }
        }while((cntrLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == E_OK));
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
    {

    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
    {
        if((Dcm_DsldPduInfo_st.SduLength != 0u )&& (RdtcDataPending_flag_b == FALSE))
        {
            dataRespLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            RdtcDataPending_flag_b = TRUE;
        }

        dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;

        Dcm_Dsp_RDTCFillZero(dataRespLen_u32);

        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        RdtcDataPending_flag_b = FALSE;
        Dcm_DspRDTCFilledRespLen_u32 = 0;
    }

    return dataServRetval_u8;
}

#else

Std_ReturnType Dcm_Dsp_ReportFaultDetectionCounter (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext,\
                                                                    Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint8_least                       cntrLoop_qu8;
    sint8                             cntrFault_s8;
    Std_ReturnType                    dataRetSetDTCFilter_u8;
    Std_ReturnType                    dataRetGetNextFiltDTC_u8;
    Std_ReturnType                    dataRetNumFltDTC_u8;
    uint16                            nrFltDTC_u16;
    uint32                            dataDTC_u32;
    Dcm_MsgLenType                    dataRespLen_u32;
    Dcm_MsgLenType                    dataResMaxLen_u32;
    Std_ReturnType                    dataServRetval_u8 = DCM_E_PENDING;

    (void)(OpStatus);
    *dataNegRespCode_u8 = 0x0;

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {

        if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
        {

            dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(ClientId_u8,
                                                    0x00,
                                                    DEM_DTC_FORMAT_UDS,
                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                    FALSE,
                                                    DEM_SEVERITY_NO_SEVERITY,
                                                    TRUE
                                                    );

            if(E_OK == dataRetSetDTCFilter_u8 )
            {

                pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

                pMsgContext->resDataLen=1;

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
            }

            else
            {
                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetSetDTCFilter_u8);
                dataServRetval_u8=E_NOT_OK;
            }
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataServRetval_u8=E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
    {

        dataResMaxLen_u32 = pMsgContext->resMaxDataLen;

        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(ClientId_u8,&nrFltDTC_u16);

        if(E_OK == dataRetNumFltDTC_u8)
        {

            if(nrFltDTC_u16 !=0)
            {

                dataRespLen_u32 = ((((Dcm_MsgLenType)nrFltDTC_u16) << 0x02u) + 0x01u);

                if(dataRespLen_u32 <= dataResMaxLen_u32)
                {

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                }
                else
                {

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;

                    dataServRetval_u8=E_NOT_OK;
                }
            }
            else
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataServRetval_u8=E_OK;
            }
        }

        else if(DEM_PENDING == dataRetNumFltDTC_u8)
        {

            dataServRetval_u8=DCM_E_PENDING;
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

            dataServRetval_u8=E_NOT_OK;
        }
    }

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        cntrLoop_qu8 = 0x00;

        dataResMaxLen_u32 = pMsgContext->resMaxDataLen;

        dataRespLen_u32 = pMsgContext->resDataLen;

        do
        {
            cntrLoop_qu8++;

            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(ClientId_u8,&dataDTC_u32, &cntrFault_s8);

            if(E_OK == dataRetGetNextFiltDTC_u8)
            {

                if((dataRespLen_u32 + 0x04u) <= dataResMaxLen_u32)
                {

                    pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 16u);
                    dataRespLen_u32++;
                    pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 8u);
                    dataRespLen_u32++;
                    pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32);
                    dataRespLen_u32++;
                    pMsgContext->resData[dataRespLen_u32] = (uint8)(cntrFault_s8);
                    dataRespLen_u32++;
                }
                else
                {

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataServRetval_u8=E_NOT_OK;
                }
            }

            else if(DEM_PENDING == dataRetGetNextFiltDTC_u8)
            {

                dataServRetval_u8=DCM_E_PENDING;
                break;
            }

            else if(DEM_NO_SUCH_ELEMENT == dataRetGetNextFiltDTC_u8)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                cntrLoop_qu8          = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataServRetval_u8=E_OK;
            }
            else
            {

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataServRetval_u8=E_NOT_OK;
            }
        }while((cntrLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));

        pMsgContext->resDataLen = dataRespLen_u32;
    }

    return dataServRetval_u8;
}

#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

