
#include "DcmDspUds_Rdtc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType Dcm_Dsp_ReportDTCSnapshotRecordIdentification(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext,\
                                                                        Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
   uint32                          dataDTC_u32;
   uint16                          nrFiltRec_u16;
   uint16                          idxLoop_qu16 = 0x00u;
   uint8                           dataRecordNum_u8;
    Dcm_MsgLenType                  nrResDataLen_u32;
    Dcm_MsgLenType                  nrResMaxDataLen_u32;
    Std_ReturnType                  dataRetGetNextFiltRec_u8     = E_OK;
    Std_ReturnType                  dataRetSetDTCFilterForRec_u8 = E_NOT_OK;
    Std_ReturnType                  dataretVal_u8 = DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8 = 0;

   if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT )
   {

        if(pMsgContext->reqDataLen == DSP_RDTC_03_REQUEST_LENGTH)
        {

            dataRetSetDTCFilterForRec_u8 = Dem_SetFreezeFrameRecordFilter(ClientId_u8,DEM_DTC_FORMAT_UDS,&nrFiltRec_u16);

            if(E_OK == dataRetSetDTCFilterForRec_u8)
            {
                pMsgContext->resData[0] = DSP_REPORT_DTC_SNAPSHOT_RECORD;
                pMsgContext->resDataLen = 0x01;

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
            }

            else{
                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetSetDTCFilterForRec_u8);
                dataretVal_u8=E_NOT_OK;
            }
        }

        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
   }

   if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        nrResDataLen_u32 = pMsgContext->resDataLen;

        while((idxLoop_qu16 < DCM_CFG_RDTC_MAXNUMRECREAD) &&(dataRetGetNextFiltRec_u8 == E_OK)&&(*dataNegRespCode_u8==0))
        {
            idxLoop_qu16++;

            dataRetGetNextFiltRec_u8 = Dem_GetNextFilteredRecord(ClientId_u8,&dataDTC_u32, &dataRecordNum_u8);

            if(E_OK == dataRetGetNextFiltRec_u8)
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

            else if(DEM_PENDING == dataRetGetNextFiltRec_u8)
            {

                dataretVal_u8 = DCM_E_PENDING;
            }

            else if(DEM_NO_SUCH_ELEMENT == dataRetGetNextFiltRec_u8)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8=E_OK;
            }
            else{

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        pMsgContext->resDataLen = nrResDataLen_u32;
   }
   else{

        dataretVal_u8=E_NOT_OK;
   }

    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

