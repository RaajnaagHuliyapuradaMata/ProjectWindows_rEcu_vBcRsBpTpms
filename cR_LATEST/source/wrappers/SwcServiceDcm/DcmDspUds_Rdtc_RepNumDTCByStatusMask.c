#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF)||\
 \
   (DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF)||\
    \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportNumberOfDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint16,     AUTOMATIC) nrFltDTC_u16;
   VAR(uint8,     AUTOMATIC) dataRDTCSubFunc_u8;
   VAR(Dem_DTCKindType,     AUTOMATIC) dataDTCKind_u8;
   VAR(Dem_DTCOriginType,     AUTOMATIC) dataDTCOrigin_u8;
   VAR(uint8,     AUTOMATIC)	stDTCStatus_u8;
   VAR(uint8,     AUTOMATIC) nrReqLength_u8;
   VAR(uint8,     AUTOMATIC) dataStatusAvailMask_u8;

   VAR (Dem_DTCSeverityType,     AUTOMATIC) dataDTCSeverity_u8;
   VAR(Dem_FilterWithSeverityType,     AUTOMATIC) dataDTCSeverityType_u8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC) dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetGetNumOfFiltDTC_u8;
   VAR(Std_ReturnType,AUTOMATIC)  dataretVal_u8;

    DCM_UNUSED_PARAM(OpStatus);
   *dataNegRespCode_u8 = 0;
    dataretVal_u8=DCM_E_PENDING;

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {
   	dataRDTCSubFunc_u8  =  pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
   	  \
   (DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
     \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF))
   	nrReqLength_u8     =  DSP_RDTC_01_11_12_REQUEST_LENGTH;
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
   	if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
   	{
   		nrReqLength_u8 = DSP_RDTC_07_REQUEST_LENGTH;
   	}
#endif

        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {

   		dataDTCSeverity_u8     = DEM_SEVERITY_NO_SEVERITY;

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
   		if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
   		{
   			dataDTCSeverity_u8 = pMsgContext->reqData[1];
   			if((dataDTCSeverity_u8 & 0x1Fu) != 0x0u)
   			{
   				*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataretVal_u8=E_NOT_OK;
   			}
   		}
#endif
            if(*dataNegRespCode_u8 == 0x0)
   		{

   			if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
   			{

   				stDTCStatus_u8   			= pMsgContext->reqData[1];

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
   				if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
   				{
   					stDTCStatus_u8 = pMsgContext->reqData[2];
   				}
#endif
   				pMsgContext->resData[0] = dataRDTCSubFunc_u8;
   				pMsgContext->resData[1] = dataStatusAvailMask_u8;

   				pMsgContext->resData[2] = Dem_GetTranslationType();

   				stDTCStatus_u8 = (dataStatusAvailMask_u8 & stDTCStatus_u8);

   				if(stDTCStatus_u8 != 0x0)
   				{
   					switch(dataRDTCSubFunc_u8)
   					{
   						case DSP_REPORT_NUM_STATUS_MASK_DTC:
   						dataDTCKind_u8         = DEM_DTC_KIND_ALL_DTCS;
   						dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
   						dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
   						break;

   						case DSP_REPORT_NUM_MIRROR_DTC:
   						dataDTCKind_u8   	   = DEM_DTC_KIND_ALL_DTCS;
   						dataDTCOrigin_u8       = DEM_DTC_ORIGIN_MIRROR_MEMORY;
   						dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
   						break;

   						case DSP_REPORT_NUM_EMISSION_DTC:
   						dataDTCKind_u8         = DEM_DTC_KIND_EMISSION_REL_DTCS;
   						dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
   						dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
   						break;

   						case DSP_REPORT_NUM_SEVERMASK_DTC:
   						default:
   						dataDTCKind_u8         = DEM_DTC_KIND_ALL_DTCS;
   						dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
   						dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_YES;
   						break;
   					}

   					dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( stDTCStatus_u8
   ,     dataDTCKind_u8
   ,     DEM_DTC_FORMAT_UDS
   ,     dataDTCOrigin_u8
   ,     dataDTCSeverityType_u8
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
                            dataretVal_u8=E_NOT_OK;
   					}
   				}

   				else
   				{

   					pMsgContext->resData[3] = 0x0;
   					pMsgContext->resData[4] = 0x0;
   					pMsgContext->resDataLen = 0x05;
                        dataretVal_u8=E_OK;
   				}
   			}

   			else
   			{

   				*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8=E_NOT_OK;
   			}
   		}
   		else
   		{

                dataretVal_u8=E_NOT_OK;
   		}
   	}

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        dataRetGetNumOfFiltDTC_u8 = Dem_GetNumberOfFilteredDTC ( &nrFltDTC_u16);

        if(dataRetGetNumOfFiltDTC_u8 == DEM_NUMBER_OK)
        {

            pMsgContext->resData[3] = (uint8) (nrFltDTC_u16>>0x08u);

            pMsgContext->resData[4] = (uint8) (nrFltDTC_u16);

            pMsgContext->resDataLen = 0x05;

            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
            dataretVal_u8=E_OK;
        }
        else if(dataRetGetNumOfFiltDTC_u8 == DEM_NUMBER_PENDING)
        {

             dataretVal_u8=DCM_E_PENDING;
        }
        else{
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8=E_NOT_OK;
        }
   }
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

