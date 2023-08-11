

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Rdtc_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF)||\
     \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF)||\
     \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF))

#define DCM_SEVERITYMASK               (0x1Fu) //Only bit 7 to 5 of the severity mask byte are valid
#define DCM_SEVERITY_0x00              (0x00u)
#define DCM_STATUS_0x00                (0x00u)
#define DCM_RDTC_RESPONSELENGTH_0x05   (0x05u)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static void Dcm_Lok_GetRequestLength(uint8 RDTCSubFunc_u8,uint8 *RequestLenPtr_u8)
{

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
     \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF))

    *RequestLenPtr_u8 = DSP_RDTC_01_11_12_REQUEST_LENGTH;
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
    if(RDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
    {
        *RequestLenPtr_u8 = DSP_RDTC_07_REQUEST_LENGTH;
    }
#else
    (void)RDTCSubFunc_u8;
#endif
}

static Dem_DTCSeverityType Dcm_Lok_GetSeverity(const Dcm_MsgContextType *pMsgContext,\
                                               Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{

    uint8 DTCSeverity_u8 = DEM_SEVERITY_NO_SEVERITY;

    if(pMsgContext->reqData[DSP_RDTC_POSSUBFUNC] == DSP_REPORT_NUM_SEVERMASK_DTC)
    {

        DTCSeverity_u8 = pMsgContext->reqData[1];

        if(DTCSeverity_u8 != DCM_SEVERITY_0x00)
        {

            if((DTCSeverity_u8 & DCM_SEVERITYMASK) != 0x0u)
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
        }
    }

    return DTCSeverity_u8;
}

Std_ReturnType Dcm_Dsp_ReportNumberOfDTC (Dcm_SrvOpStatusType OpStatus,\
                                          Dcm_MsgContextType *pMsgContext,\
                                          Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint16              nrFltDTC_u16;
    uint8               dataStatusAvailMask_u8;
    uint8               stDTCStatus_u8;
    uint8               nrReqLength_u8;
    uint8               dataRDTCSubFunc_u8;
    Dem_DTCOriginType   dataDTCOrigin_u16;
    Dem_DTCSeverityType dataDTCSeverity;
    boolean             dataDTCSeverityType;
    Std_ReturnType              dataRetSetDTCFilter;
    Std_ReturnType              dataRetGetNumOfFiltDTC;
    Std_ReturnType              dataretVal;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8 = 0;
    dataretVal = DCM_E_PENDING;

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {

        dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

        Dcm_Lok_GetRequestLength(dataRDTCSubFunc_u8,&nrReqLength_u8);

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

            dataDTCSeverity = Dcm_Lok_GetSeverity(pMsgContext,dataNegRespCode_u8);

            if (*dataNegRespCode_u8 == 0x0)
            {

                if(E_OK == Dem_GetDTCStatusAvailabilityMask(ClientId_u8,&dataStatusAvailMask_u8))
                {

                    stDTCStatus_u8 = pMsgContext->reqData[1];

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
                    if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
                    {
                        stDTCStatus_u8 = pMsgContext->reqData[2];
                    }
#endif

                    pMsgContext->resData[0] = dataRDTCSubFunc_u8;
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;

                    pMsgContext->resData[2] = Dem_GetTranslationType(ClientId_u8);

                    stDTCStatus_u8 = (dataStatusAvailMask_u8 & stDTCStatus_u8);

                    if(stDTCStatus_u8 != DCM_STATUS_0x00)
                    {
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
                       if((pMsgContext->reqData[DSP_RDTC_POSSUBFUNC] == DSP_REPORT_NUM_SEVERMASK_DTC) &&\
                               (dataDTCSeverity == DCM_SEVERITY_0x00))
                       {
                              pMsgContext->resData[3] = 0x0;
                              pMsgContext->resData[4] = 0x0;
                              pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x05;
                              dataretVal=E_OK;
                       }
                       else
#endif
                       {

                            switch (dataRDTCSubFunc_u8)
                            {
                                case DSP_REPORT_NUM_STATUS_MASK_DTC:
                                dataDTCOrigin_u16   = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                                dataDTCSeverityType = FALSE;
                                break;

                                case DSP_REPORT_NUM_MIRROR_DTC:
                                dataDTCOrigin_u16   = DEM_DTC_ORIGIN_MIRROR_MEMORY;
                                dataDTCSeverityType = FALSE;
                                break;

                                case DSP_REPORT_NUM_EMISSION_DTC:
                                dataDTCOrigin_u16   = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
                                dataDTCSeverityType = FALSE;
                                break;

                                case DSP_REPORT_NUM_SEVERMASK_DTC:
                                default:
                                dataDTCOrigin_u16   = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                                dataDTCSeverityType = TRUE;
                                break;
                            }

                            dataRetSetDTCFilter = Dem_SetDTCFilter(ClientId_u8,
                                                                   stDTCStatus_u8,
                                                                   DEM_DTC_FORMAT_UDS,
                                                                   dataDTCOrigin_u16,
                                                                   dataDTCSeverityType,
                                                                   dataDTCSeverity,
                                                                   FALSE
                                                                 );

                            if(E_OK == dataRetSetDTCFilter)
                            {

                                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                            }

                            else
                            {

                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                dataretVal=E_NOT_OK;
                            }
                       }
                    }

                    else
                    {

                        pMsgContext->resData[3] = 0x0;
                        pMsgContext->resData[4] = 0x0;
                        pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x05;
                        dataretVal=E_OK;
                    }
                }

                else
                {

                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal=E_NOT_OK;
                }
            }
            else
            {

                dataretVal=E_NOT_OK;
            }
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal=E_NOT_OK;
        }
    }

    if (Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {

        dataRetGetNumOfFiltDTC = Dem_GetNumberOfFilteredDTC (ClientId_u8, &nrFltDTC_u16);

        if (E_OK == dataRetGetNumOfFiltDTC)
        {

            pMsgContext->resData[3] = (uint8) (nrFltDTC_u16>>0x08u);

            pMsgContext->resData[4] = (uint8) (nrFltDTC_u16);

            pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x05;

            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
            dataretVal=E_OK;
        }

        else if (DEM_PENDING == dataRetGetNumOfFiltDTC)
        {

             dataretVal=DCM_E_PENDING;
        }
        else
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal=E_NOT_OK;
        }
    }
    return dataretVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

