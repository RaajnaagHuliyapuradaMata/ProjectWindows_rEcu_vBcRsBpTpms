#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(uint8,     DCM_VAR) s_nrRDTCLoopEnd_u8;

static VAR (uint8,     DCM_VAR) s_dataRDTCSubFunc_u8;

static VAR(Dem_DTCOriginType,     DCM_VAR) s_dataDemDTCOrigin_u8;

static VAR(boolean,     DCM_VAR) s_IsRecordSupported;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDataRecordByDTCNumber (VAR(Dcm_SrvOpStatusType,AUTOMATIC) Opstatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Dcm_MsgLenType,AUTOMATIC) dataRemainBuffer_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC) dataFillRespLen_u32;
   VAR(uint8_least,AUTOMATIC) idxLoop_qu8;
   VAR(uint8,AUTOMATIC) nrReqLength_u8 = 0x00u;
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
   VAR (uint16,     AUTOMATIC) nrSizeOfFreezeFrame_u16;
   VAR(Dem_ReturnGetFreezeFrameDataByDTCType,   AUTOMATIC) dataRetGetFFDataRecByDTC_u8;
   VAR(Dem_ReturnGetSizeOfFreezeFrameByDTCType,   AUTOMATIC) dataRetGetFFDataRecSizeByDTC_u8;
#endif
   VAR(Dem_ReturnGetStatusOfDTCType,     AUTOMATIC) stRetGetStatusOfDTC_u8;
   VAR(  Dem_ReturnDisableDTCRecordUpdateType   ,     AUTOMATIC) stRetDisableDTCRecUpdate_u8;
   VAR( uint8,     AUTOMATIC) stDTCStatus_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataRetEnableDTCRecUpdate_u8;
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
   VAR(Dem_ReturnGetExtendedDataRecordByDTCType,AUTOMATIC) dataRetGetExtDataRecByDTC_u8;
#endif

   VAR(boolean,     AUTOMATIC) isPendingReturned_b;
   VAR(Std_ReturnType,     AUTOMATIC)  dataretVal_u8;

    *dataNegRespCode_u8 = 0x00;

   isPendingReturned_b = FALSE;
    dataFillRespLen_u32 = 0;
    dataretVal_u8 = DCM_E_PENDING;

    DCM_UNUSED_PARAM(Opstatus);

   if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
   {
        s_dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

        if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
        {
            nrReqLength_u8 = DSP_RDTC_04_06_10_REQUEST_LENGTH;
        }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
        if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
        {

            nrReqLength_u8 = DSP_RDTC_18_19_REQUEST_LENGTH;
        }

#endif

        if(nrReqLength_u8 == pMsgContext->reqDataLen)
        {

            Dsp_RdtcDTC_u32 =  ((((uint32) pMsgContext->reqData[0x01]) << DSP_RDTC_LSH_16BITS) |
                    (((uint32) pMsgContext->reqData[0x02]) << DSP_RDTC_LSH_08BITS) |
                    ((uint32) pMsgContext->reqData[0x03]));
            s_dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                    (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {

                s_dataDemDTCOrigin_u8 = pMsgContext->reqData[0x05];

            }
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)
            if(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)
            {

                s_dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_MIRROR_MEMORY;

            }
#endif

            stRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(Dsp_RdtcDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     s_dataDemDTCOrigin_u8
   ,     &stDTCStatus_u8);

            if(DEM_STATUS_OK == stRetGetStatusOfDTC_u8)
            {

                Dcm_DspRDTCRecordNum_u8 = pMsgContext->reqData[0x04];

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {

                    pMsgContext->resData[0x04] = pMsgContext->reqData[0x03];
                    pMsgContext->resData[0x03] = pMsgContext->reqData[0x02];
                    pMsgContext->resData[0x02] = pMsgContext->reqData[0x01];
                    pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                    pMsgContext->resData[0x01] = s_dataDemDTCOrigin_u8;
                    pMsgContext->resData[0x05] = stDTCStatus_u8;

                    pMsgContext->resDataLen = 0x06;

                }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
                {

                    pMsgContext->resData[0x03] = pMsgContext->reqData[0x03];
                    pMsgContext->resData[0x02] = pMsgContext->reqData[0x02];
                    pMsgContext->resData[0x01] = pMsgContext->reqData[0x01];
                    pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                    pMsgContext->resData[0x04] = stDTCStatus_u8;

                    pMsgContext->resDataLen = 0x05;
                }
#endif
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||\
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {
                	Dcm_DspRDTCSubFunc_en = DSP_RDTC_UPDATEDISABLED;
                }

            }

            else if(DEM_STATUS_FAILED==stRetGetStatusOfDTC_u8)
            {

                pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                pMsgContext->resDataLen = 0x01;
                dataretVal_u8 = E_OK;
            }

            else if((DEM_STATUS_WRONG_DTC == stRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== stRetGetStatusOfDTC_u8)||       \
                    (DEM_STATUS_WRONG_DTCKIND== stRetGetStatusOfDTC_u8))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }

            else{
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }

        else{
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
   }
   if(DSP_RDTC_UPDATEDISABLED==Dcm_DspRDTCSubFunc_en)
   {
        stRetDisableDTCRecUpdate_u8 = Dem_DisableDTCRecordUpdate(Dsp_RdtcDTC_u32,s_dataDemDTCOrigin_u8);

        if( DEM_DISABLE_DTCRECUP_OK == stRetDisableDTCRecUpdate_u8)
        {
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {
                if(Dcm_DspRDTCRecordNum_u8 == 0xFF)
                {
                    s_nrRDTCLoopEnd_u8   = 0xFF;
                }
                else if(Dcm_DspRDTCRecordNum_u8 == 0xFE)
                {
                    s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8;
                }
                else{

                    s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8 + 0x01;
                }
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_GETFFSIZE;
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM) \
                    ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {
                if(Dcm_DspRDTCRecordNum_u8 == 0x00)
                {

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                else{
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                    s_IsRecordSupported = FALSE;

                    if(Dcm_DspRDTCRecordNum_u8 == 0xEF)
                    {
                        s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8;
                    }
                    else if(Dcm_DspRDTCRecordNum_u8 < 0xF0)
                    {

                        s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8 + 0x01;
                    }
                    else if(Dcm_DspRDTCRecordNum_u8 == 0xFE)
                    {

                        Dcm_DspRDTCRecordNum_u8 = 0x90;
                        s_nrRDTCLoopEnd_u8   = 0xF0;
                    }
                    else if(Dcm_DspRDTCRecordNum_u8 == 0xFF)
                    {

                        Dcm_DspRDTCRecordNum_u8 = 0x01;
                        s_nrRDTCLoopEnd_u8   = 0xF0;
                    }
                    else
                    {
                        *dataNegRespCode_u8   = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
            }
#endif
        }
        else if(DEM_DISABLE_DTCRECUP_WRONG_DTC==stRetDisableDTCRecUpdate_u8)
        {

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }
        else if(DEM_DISABLE_DTCRECUP_PENDING == stRetDisableDTCRecUpdate_u8 )
        {

        }
        else{

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

        }

   }

   else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
   {
        idxLoop_qu8 = 0;

        do
        {
            idxLoop_qu8++;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {
                dataFillRespLen_u32 = (pMsgContext->resDataLen);
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)\
                    ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {

                dataFillRespLen_u32 = (pMsgContext->resDataLen + 1u);
            }
#endif

            if(pMsgContext->resMaxDataLen > dataFillRespLen_u32)
            {
                dataRemainBuffer_u32 = (pMsgContext->resMaxDataLen - dataFillRespLen_u32);
            }
            else{
                dataRemainBuffer_u32 = 0x00;
            }

            Dcm_DspMaxResDataLen_u16 = (uint16)dataRemainBuffer_u32;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {

                dataRetGetFFDataRecByDTC_u8 = Dem_GetFreezeFrameDataByDTC ( Dsp_RdtcDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     s_dataDemDTCOrigin_u8
   ,     Dcm_DspRDTCRecordNum_u8
   ,     &pMsgContext->resData[dataFillRespLen_u32]
   ,     &Dcm_DspMaxResDataLen_u16
                );

                if(DEM_GET_FFDATABYDTC_OK == dataRetGetFFDataRecByDTC_u8)
                {

                    if(Dcm_DspMaxResDataLen_u16 > 0x00)
                    {

                        pMsgContext->resDataLen = (Dcm_DspMaxResDataLen_u16 + dataFillRespLen_u32);
                    }
                    Dcm_DspRDTCRecordNum_u8++;
                    s_IsRecordSupported = TRUE;

                }

                else if(DEM_GET_FFDATABYDTC_PENDING == dataRetGetFFDataRecByDTC_u8)
                {

                    idxLoop_qu8 = DCM_CFG_RDTC_MAXNUMRECREAD;

                    isPendingReturned_b = TRUE;
                    dataretVal_u8 = DCM_E_PENDING;
                }

                else if(DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER == dataRetGetFFDataRecByDTC_u8)
                {
                    if(s_nrRDTCLoopEnd_u8 != 0xFF)
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {

                        Dcm_DspRDTCRecordNum_u8++;
                    }
                }

                else if(DEM_GET_FFDATABYDTC_WRONG_DTC == dataRetGetFFDataRecByDTC_u8)
                {

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }

                else if(DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE == dataRetGetFFDataRecByDTC_u8)
                {

                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                }

                else{

                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT ;
                }
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| \
                    (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {

                dataRetGetExtDataRecByDTC_u8 = Dem_GetExtendedDataRecordByDTC( Dsp_RdtcDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     s_dataDemDTCOrigin_u8
   ,     Dcm_DspRDTCRecordNum_u8
   ,     &pMsgContext->resData[dataFillRespLen_u32]
   ,     &Dcm_DspMaxResDataLen_u16
                );

                if(DEM_RECORD_OK == dataRetGetExtDataRecByDTC_u8)
                {

                    if(Dcm_DspMaxResDataLen_u16 > 0x00)
                    {

                        pMsgContext->resData[pMsgContext->resDataLen] = Dcm_DspRDTCRecordNum_u8;

                        pMsgContext->resDataLen = (Dcm_DspMaxResDataLen_u16 + dataFillRespLen_u32);
                    }

                    s_IsRecordSupported = TRUE;
                    Dcm_DspRDTCRecordNum_u8++;

                }

                else if(DEM_RECORD_PENDING == dataRetGetExtDataRecByDTC_u8)
                {

                    idxLoop_qu8 = DCM_CFG_RDTC_MAXNUMRECREAD;

                    isPendingReturned_b = TRUE;
                    dataretVal_u8 = DCM_E_PENDING;
                }

                else if(DEM_RECORD_WRONG_NUMBER == dataRetGetExtDataRecByDTC_u8)
                {
                    if(s_nrRDTCLoopEnd_u8 != 0xF0)
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {

                        Dcm_DspRDTCRecordNum_u8++;
                    }
                }

                else if(DEM_RECORD_WRONG_DTC == dataRetGetExtDataRecByDTC_u8)
                {

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }

                else if(DEM_RECORD_WRONG_BUFFERSIZE == dataRetGetExtDataRecByDTC_u8)
                {

                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                }

                else{

                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                }
            }
#endif
        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMRECREAD)             &&
                (0x00 == *dataNegRespCode_u8)                         &&
                (Dcm_DspRDTCRecordNum_u8 < s_nrRDTCLoopEnd_u8));
        if((Dcm_DspRDTCRecordNum_u8 >= s_nrRDTCLoopEnd_u8) && (0x00 == *dataNegRespCode_u8))
        {
            dataretVal_u8 = E_OK;
        }

        if((Dcm_DspRDTCRecordNum_u8 >= s_nrRDTCLoopEnd_u8) && (isPendingReturned_b == FALSE))
        {
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
            {
                if((s_IsRecordSupported==FALSE)&&(*dataNegRespCode_u8==0x00u)&&(pMsgContext->resDataLen==0x05u))
                {

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                else{

                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                }
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {
                    if((s_IsRecordSupported==FALSE)&&(*dataNegRespCode_u8==0x00u)&&(pMsgContext->resDataLen==0x06u))
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {

                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                    }

                }
#endif
        }
        else{

        }
   }
   else{

   }

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_GETFFSIZE)
   {
        dataRetGetFFDataRecSizeByDTC_u8=Dem_GetSizeOfFreezeFrameByDTC(Dsp_RdtcDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     s_dataDemDTCOrigin_u8
   ,     Dcm_DspRDTCRecordNum_u8
   ,     &nrSizeOfFreezeFrame_u16);
        if(DEM_GET_SIZEOFFF_OK == dataRetGetFFDataRecSizeByDTC_u8)
        {
            if(pMsgContext->resMaxDataLen >= (uint32)(nrSizeOfFreezeFrame_u16+0x5))
            {
                if(Dcm_DspRDTCRecordNum_u8 == 0xFF)
                {
                    Dcm_DspRDTCRecordNum_u8 = 0x00;
                }

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                s_IsRecordSupported = FALSE;
            }
            else{
                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
            }
        }

        else if(DEM_GET_SIZEOFFF_PENDING == dataRetGetFFDataRecSizeByDTC_u8)
        {
        }

        else if((DEM_GET_SIZEOFFF_WRONG_RNUM == dataRetGetFFDataRecSizeByDTC_u8)||
                (DEM_GET_SIZEOFFF_WRONG_DTC  == dataRetGetFFDataRecSizeByDTC_u8))
        {
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }

        else{
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT ;
        }
   }
#endif

   if(*dataNegRespCode_u8 != 0)
   {
        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
        dataretVal_u8 = E_NOT_OK;
   }

   if(DSP_RDTC_SFINIT == Dcm_DspRDTCSubFunc_en)
   {

        dataRetEnableDTCRecUpdate_u8 = Dem_EnableDTCRecordUpdate();
        (void)dataRetEnableDTCRecUpdate_u8;
        s_IsRecordSupported = FALSE;

   }

    return dataretVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

