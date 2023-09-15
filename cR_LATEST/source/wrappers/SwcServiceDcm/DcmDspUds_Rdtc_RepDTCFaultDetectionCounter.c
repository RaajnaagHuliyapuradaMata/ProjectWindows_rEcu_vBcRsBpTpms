#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFaultDetectionCounter (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint8_least,     AUTOMATIC) cntrLoop_qu8;
   VAR(sint8,     AUTOMATIC) cntrFault_s8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC)    dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8;
   VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;
   VAR(uint16,     AUTOMATIC)  nrFltDTC_u16;
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataRespLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataResMaxLen_u32;
   VAR(Std_ReturnType,     AUTOMATIC)  dataServRetval_u8;
   VAR(boolean,     AUTOMATIC) isProtocolIPCanFD_b = FALSE;

   *dataNegRespCode_u8      = 0x0;
    dataServRetval_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

   	if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
   	{

   		Dcm_DspRDTCFilledRespLen_u32 = 0x0;
   		Dcm_DspTotalRespLenFilled_u32 = 0x0;

   		Dcm_DspFillZeroes_b     = FALSE;

   		dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( 0x00
   ,  DEM_DTC_KIND_ALL_DTCS
   ,  DEM_DTC_FORMAT_UDS
   ,  DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,  DEM_FILTER_WITH_SEVERITY_NO
   ,  DEM_SEVERITY_NO_SEVERITY
   ,  DEM_FILTER_FOR_FDC_YES
   		);

   		if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
   		{

   			pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

   			pMsgContext->resDataLen=1;

   			Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
   		}

   		else
   		{

   			*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

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

   	dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

   	if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
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

   	else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
   	{

            dataServRetval_u8=DCM_E_PENDING;
   	}
   	else
   	{

   		*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

            dataServRetval_u8=E_NOT_OK;
   	}
   }

   else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
   	cntrLoop_qu8 = 0;

   	dataResMaxLen_u32 = pMsgContext->resMaxDataLen;
   	do
   	{
   		cntrLoop_qu8++;

   		dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(&dataDTC_u32, &cntrFault_s8);

   		if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
   		{

   			dataRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32;

   			pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 16u);
   			dataRespLen_u32++;
   			pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 8u);
   			dataRespLen_u32++;
   			pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32);
   			dataRespLen_u32++;
   			pMsgContext->resData[dataRespLen_u32] = (uint8)(cntrFault_s8);
   			dataRespLen_u32++;

   			Dcm_DspRDTCFilledRespLen_u32 = dataRespLen_u32;

   			Dcm_DspTotalRespLenFilled_u32 = (Dcm_DspTotalRespLenFilled_u32 + 0x04u);

   			if(Dcm_DspTotalRespLenFilled_u32 >=  pMsgContext->resDataLen)
   			{
   				dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
   			}

   		}

   		else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
   		{

                dataServRetval_u8=DCM_E_PENDING;
   			break;
   		}

   		else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
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
   		if((dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC) || (((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > dataResMaxLen_u32) && (isProtocolIPCanFD_b!=FALSE))||  ((Dcm_DspRDTCFilledRespLen_u32>=7u)&&(isProtocolIPCanFD_b==FALSE)))
   		{

   			if(Dcm_DspFirstPageSent_b == FALSE)
   			{

   				Dcm_DspFirstPageSent_b = TRUE;
   			}
   			if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
   			{

   				dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;

   				Dcm_Dsp_RDTCFillZero(dataRespLen_u32);
   			}

   			Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

   			Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);

   			Dcm_DspRDTCFilledRespLen_u32 = 0x0;

   			dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
   		}

   	}while((cntrLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK));
   }
   else
   {

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
   {

   }

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
   {

   	dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u32;

   	Dcm_Dsp_RDTCFillZero(dataRespLen_u32);

   	Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

   	Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);

   	Dcm_DspRDTCFilledRespLen_u32 = 0;
   }

   return dataServRetval_u8;
}

#else

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFaultDetectionCounter (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
   							{
   VAR(uint8_least,     AUTOMATIC) cntrLoop_qu8;
   VAR(sint8,     AUTOMATIC) cntrFault_s8;
   VAR(Dem_ReturnSetFilterType,     AUTOMATIC) dataRetSetDTCFilter_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8;
   VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;
   VAR(uint16,     AUTOMATIC)  nrFltDTC_u16;
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataRespLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataResMaxLen_u32;
   VAR(Std_ReturnType,     AUTOMATIC)  dataServRetval_u8;

    (void)(OpStatus);
    *dataNegRespCode_u8      = 0x0;
    dataServRetval_u8=DCM_E_PENDING;

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {

   	if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
   	{

   		dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( 0x00
   ,  DEM_DTC_KIND_ALL_DTCS
   ,  DEM_DTC_FORMAT_UDS
   ,  DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,  DEM_FILTER_WITH_SEVERITY_NO
   ,  DEM_SEVERITY_NO_SEVERITY
   ,  DEM_FILTER_FOR_FDC_YES
   		);

   		if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
   		{

   			pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

   			pMsgContext->resDataLen=1;

   			Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
   		}

   		else
   		{

   			*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataServRetval_u8=DCM_E_PENDING;
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

   	dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

   	if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
   	{
   		if(nrFltDTC_u16>0)
   		{

   		Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
   		}
   		else
   		{

   		Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
            dataServRetval_u8=E_OK;
   		}
   	}

   	else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
   	{

            dataServRetval_u8=DCM_E_PENDING;
   	}
   	else
   	{

   		*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataServRetval_u8=E_NOT_OK;
   	}

   }

   else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
   	cntrLoop_qu8 = 0x00;

   	dataResMaxLen_u32 = pMsgContext->resMaxDataLen;

   	dataRespLen_u32 = pMsgContext->resDataLen;

   	do
   	{
   		cntrLoop_qu8++;

   		dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(&dataDTC_u32, &cntrFault_s8);

   					if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
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

   					else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
   					{

                            dataServRetval_u8=DCM_E_PENDING;

   						break;;
   					}

   					else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
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
   else
   {
   	dataServRetval_u8=E_NOT_OK;
   }

    return dataServRetval_u8;
}

#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

