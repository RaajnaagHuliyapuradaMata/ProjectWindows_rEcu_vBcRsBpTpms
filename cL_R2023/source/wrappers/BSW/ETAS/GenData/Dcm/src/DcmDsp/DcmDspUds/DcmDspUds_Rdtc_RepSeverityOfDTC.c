
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Rdtc_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)

#define DCM_RDTC_RESPONSELENGTH_0x01   (0x01u)
#define DCM_RDTC_RESPONSELENGTH_0x08   (0x08u)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType Dcm_Dsp_ReportSeverityOfDTC(Dcm_SrvOpStatusType OpStatus,\
                                           Dcm_MsgContextType *pMsgContext,\
                                           Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint32 dataDTC_u32;
    uint8  dataHighByte_u8;
    uint8  dataMiddleByte_u8;
    uint8  dataLowByte_u8;
    uint8  dataFunctionalUnit_u8;

    Std_ReturnType  dataRetGetStatusOfDTC;
    Std_ReturnType  dataRetGetSelectDTC;
    Std_ReturnType  dataRetGetSeverityOfDTC;
    Std_ReturnType  dataRetGetFuncUnitOfDTC_u8;
    Std_ReturnType  dataretVal;

    static Dem_DTCSeverityType dataDTCSeverity_u8;
    static uint8  dataRDTC0x09StMask_u8;
    static uint8  stDTCStatus_Rdtc_u8;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8 = 0x00;
    dataretVal = DCM_E_PENDING;

    if(pMsgContext->reqDataLen == DSP_RDTC_09_REQUEST_LENGTH)
    {

        dataHighByte_u8     =   pMsgContext->reqData[0x01];
        dataMiddleByte_u8   =   pMsgContext->reqData[0x02];
        dataLowByte_u8      =   pMsgContext->reqData[0x03];
        dataDTC_u32         =   dataHighByte_u8;
        dataDTC_u32         =   (dataDTC_u32 << 0x8u);
        dataDTC_u32         =   (dataDTC_u32 | dataMiddleByte_u8);
        dataDTC_u32         =   (dataDTC_u32 << 0x8u);
        dataDTC_u32         =   (dataDTC_u32 | dataLowByte_u8);

        if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
        {

            if(E_OK == Dem_GetDTCStatusAvailabilityMask(ClientId_u8,&dataRDTC0x09StMask_u8))
            {

                dataRetGetSelectDTC = Dem_SelectDTC(ClientId_u8,
                                                    dataDTC_u32,
                                                    DEM_DTC_FORMAT_UDS,
                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY
                                                   );

                if(E_OK == dataRetGetSelectDTC)
                {
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_GETDTCSTATUS;
                }
                else
                {
                    *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetSelectDTC);
                    dataretVal=E_NOT_OK;
                }

            }

            else
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal=E_NOT_OK;
            }
        }

        if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_GETDTCSTATUS)
        {

            dataRetGetStatusOfDTC = Dem_GetStatusOfDTC(ClientId_u8,&stDTCStatus_Rdtc_u8);

            if(E_OK == dataRetGetStatusOfDTC)
            {
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_GETDTCSEVERITY;
            }

            else if(DEM_NO_SUCH_ELEMENT == dataRetGetStatusOfDTC)
            {

                pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                pMsgContext->resDataLen = DCM_RDTC_RESPONSELENGTH_0x01;
                dataretVal = E_OK;
            }
            else if(DEM_PENDING == dataRetGetStatusOfDTC)
            {

                dataretVal = DCM_E_PENDING;
            }
            else
            {

                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetStatusOfDTC);
                dataretVal=E_NOT_OK;
            }

        }

        if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_GETDTCSEVERITY)
        {

            dataRetGetSeverityOfDTC = Dem_GetSeverityOfDTC(ClientId_u8,&dataDTCSeverity_u8);

            if(E_OK == dataRetGetSeverityOfDTC)
            {
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
            }

            else if(DEM_PENDING == dataRetGetSeverityOfDTC)
            {

                dataretVal = DCM_E_PENDING;
            }
            else
            {

                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetSeverityOfDTC);
                dataretVal=E_NOT_OK;
            }
        }

        if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
        {

            dataRetGetFuncUnitOfDTC_u8 = Dem_GetFunctionalUnitOfDTC(ClientId_u8,&dataFunctionalUnit_u8);

            if(E_OK == dataRetGetFuncUnitOfDTC_u8)
            {

               pMsgContext->resData[0x00] = pMsgContext->reqData[0x0];
               pMsgContext->resData[0x01] = dataRDTC0x09StMask_u8;
               pMsgContext->resData[0x02] = dataDTCSeverity_u8;
               pMsgContext->resData[0x03] = dataFunctionalUnit_u8;
               pMsgContext->resData[0x04] = dataHighByte_u8;
               pMsgContext->resData[0x05] = dataMiddleByte_u8;
               pMsgContext->resData[0x06] = dataLowByte_u8;
               pMsgContext->resData[0x07] = stDTCStatus_Rdtc_u8;
               pMsgContext->resDataLen    = DCM_RDTC_RESPONSELENGTH_0x08;
               dataretVal=E_OK;
            }
            else if(DEM_PENDING == dataRetGetFuncUnitOfDTC_u8)
            {

               dataretVal = DCM_E_PENDING;
            }
            else
            {

                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetFuncUnitOfDTC_u8);
                dataretVal=E_NOT_OK;
            }
        }
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        dataretVal=E_NOT_OK;
    }
    return dataretVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

