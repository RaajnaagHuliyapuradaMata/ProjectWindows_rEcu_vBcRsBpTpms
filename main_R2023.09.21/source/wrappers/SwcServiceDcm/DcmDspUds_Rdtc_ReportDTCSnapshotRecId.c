#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCSnapshotRecordIdentification (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(uint16,     AUTOMATIC) nrFiltRec_u16;

   VAR(Dcm_MsgLenType,     AUTOMATIC) nrResDataLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) nrResMaxDataLen_u32;
   VAR(uint8_least,     AUTOMATIC) idxLoop_qu8;
   VAR(uint8,     AUTOMATIC) dataRecordNum_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC) dataRetGetNextFiltRec_u8;

   VAR(Dem_ReturnSetFilterType,     AUTOMATIC) dataRetSetDTCFilterForRec_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataretVal_u8;

    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8 = 0;
    dataretVal_u8=DCM_E_PENDING;

   if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT )
   {

        if(pMsgContext->reqDataLen == DSP_RDTC_03_REQUEST_LENGTH)
        {

            dataRetSetDTCFilterForRec_u8 = Dem_SetFreezeFrameRecordFilter(DEM_DTC_FORMAT_UDS,&nrFiltRec_u16);

            if(dataRetSetDTCFilterForRec_u8 == DEM_FILTER_ACCEPTED)
            {
   			pMsgContext->resData[0] = DSP_REPORT_DTC_SNAPSHOT_RECORD;
                pMsgContext->resDataLen = 0x01;

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
            }

            else{

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8=E_NOT_OK;
            }
        }

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
   }

   else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP )
   {

        idxLoop_qu8 = 0x00;
        dataRetGetNextFiltRec_u8 = DEM_FILTERED_OK;

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        nrResDataLen_u32 = pMsgContext->resDataLen;

        while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMRECREAD) &&(dataRetGetNextFiltRec_u8 == DEM_FILTERED_OK)&&(*dataNegRespCode_u8==0))
        {
            idxLoop_qu8++;

            dataRetGetNextFiltRec_u8 = Dem_GetNextFilteredRecord(&dataDTC_u32, &dataRecordNum_u8);

            if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_OK)
            {

                if((nrResDataLen_u32 + 0x04u) <= nrResMaxDataLen_u32)
                {

                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32 >> 16u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32 >> 8u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = dataRecordNum_u8;
                    nrResDataLen_u32++;
                }
                else{

                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8=E_NOT_OK;
                }
            }

            else if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_PENDING)
            {

                dataretVal_u8=DCM_E_PENDING;
            }

            else if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8=E_OK;
            }
            else{

                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        pMsgContext->resDataLen = nrResDataLen_u32;
   }
   else
   {

        dataretVal_u8=E_NOT_OK;
   }
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

