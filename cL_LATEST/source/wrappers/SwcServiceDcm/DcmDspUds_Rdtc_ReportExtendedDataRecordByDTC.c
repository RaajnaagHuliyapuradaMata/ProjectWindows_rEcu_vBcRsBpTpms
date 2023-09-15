

#include "DcmDspUds_Rdtc_Inf.hpp"
#include "Rte_Dcm.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if(DCM_CFG_DSP_REPORTDTC_OR_MIRRORMEMORYDTC_OR_USERDEFINEDDTC_EXTENDEDDATARECORDBYDTCNUMBER != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 s_RDTCSubFunction_u8;

static Std_ReturnType s_SubfunctionReturnValue_u8;
static uint8 s_DTCStatus_Rdtc_u8;
static uint8 s_MaxRecordstoRead_u8;
static Dcm_NegativeResponseCodeType s_NegResponseCode_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

static Dem_DTCOriginType s_DemDTCOrigin_Rdtc_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static boolean s_isExtendedDataRecordSupported_b = FALSE;

static void Dcm_Lok_EnableRecordUpdate(Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType EnableRecordUpdateResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    EnableRecordUpdateResult_u8 = Dem_EnableDTCRecordUpdate(ClientId_u8);

   if(E_OK == EnableRecordUpdateResult_u8)
   {
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_INITIAL;
        s_isExtendedDataRecordSupported_b = FALSE;
        s_SubfunctionReturnValue_u8 = E_OK;
   }
   else if(DEM_PENDING == EnableRecordUpdateResult_u8)
   {

   }
   else{
        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(EnableRecordUpdateResult_u8);
   }
}

static void Dcm_Lok_ReportDTCRecords(Dcm_MsgContextType *pMsgContext
   ,                                               Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
   boolean isNoSuchElemetReturned_b = FALSE;
   boolean isPendingReturned_b = FALSE;
    Std_ReturnType GetNextExtendedDataResult_u8 = E_NOT_OK;
   uint8 LoopIndex_u8 = 0x00;
   uint16 DTCExtendedDataSize_u16;
    Dcm_MsgLenType FilledResponseLength_u32;

    *dataNegRespCode_u8 = 0x00;

    do
   {
        LoopIndex_u8++;

        FilledResponseLength_u32 = pMsgContext->resDataLen;

        DTCExtendedDataSize_u16 = (uint16)(pMsgContext->resMaxDataLen - FilledResponseLength_u32);

        GetNextExtendedDataResult_u8 = Dem_GetNextExtendedDataRecord(ClientId_u8
   ,                                                                 &pMsgContext->resData[FilledResponseLength_u32]
   ,                                                                 &DTCExtendedDataSize_u16);
        if(E_OK == GetNextExtendedDataResult_u8)
        {

            if(DTCExtendedDataSize_u16 > 0x00)
            {

                pMsgContext->resDataLen = (DTCExtendedDataSize_u16 + FilledResponseLength_u32);
            }
            s_isExtendedDataRecordSupported_b = TRUE;
            Dcm_DspRDTCRecordNum_u8++;
        }
        else if(DEM_PENDING == GetNextExtendedDataResult_u8)
        {

            isPendingReturned_b = TRUE;
        }
        else if(DEM_NO_SUCH_ELEMENT == GetNextExtendedDataResult_u8)
        {

            isNoSuchElemetReturned_b = TRUE;
            break;
        }
        else{

            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(GetNextExtendedDataResult_u8);
        }

   }while((0x00 == *dataNegRespCode_u8)&&(FALSE == isPendingReturned_b)&& \
           (LoopIndex_u8 < DCM_CFG_RDTC_MAXNUMRECREAD)&&(Dcm_DspRDTCRecordNum_u8 <= s_MaxRecordstoRead_u8));

   if((0x00 == *dataNegRespCode_u8)&&(FALSE == isPendingReturned_b)&& \
       ((isNoSuchElemetReturned_b == TRUE)||(Dcm_DspRDTCRecordNum_u8 > s_MaxRecordstoRead_u8)))
   {
        if(s_isExtendedDataRecordSupported_b == TRUE)
        {

            RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_ENABLERECORDUPDATE;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }
   }
   if(*dataNegRespCode_u8 != 0x00)
   {
        s_NegResponseCode_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
   }
}

static void Dcm_Lok_NumberOfRecordstoReport(void){

   if(Dcm_DspRDTCRecordNum_u8 <= 0xEF)
   {
        s_MaxRecordstoRead_u8 = Dcm_DspRDTCRecordNum_u8;
   }
   else if(0xFE == Dcm_DspRDTCRecordNum_u8)
   {

        Dcm_DspRDTCRecordNum_u8 = 0x90;
        s_MaxRecordstoRead_u8 = 0xEF;
   }
   else{
        if(0xFF == Dcm_DspRDTCRecordNum_u8)
        {

            Dcm_DspRDTCRecordNum_u8 = 0x01;
            s_MaxRecordstoRead_u8 = 0xEF;
        }
   }

    RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REPORTDTCRECORDS;
}

static void Dcm_Lok_CheckforSizeOfExtendedDataRecords(const Dcm_MsgContextType *pMsgContext
   ,                                                     Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType ExtendedDataRecordSizeResult_u8 = E_NOT_OK;
   uint16 SizeOfExtendedDataRecord_u16 = 0x00;

    *dataNegRespCode_u8 = 0x00;

    ExtendedDataRecordSizeResult_u8 = Dem_GetSizeOfExtendedDataRecordSelection(ClientId_u8
   ,                                                                              &SizeOfExtendedDataRecord_u16);

   if(E_OK == ExtendedDataRecordSizeResult_u8)
   {
        if(pMsgContext->resMaxDataLen >= (Dcm_MsgLenType)(SizeOfExtendedDataRecord_u16 + pMsgContext->resDataLen))
        {
            Dcm_Lok_NumberOfRecordstoReport();
        }
        else{
            *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
        }
   }
   else if(DEM_PENDING == ExtendedDataRecordSizeResult_u8)
   {

   }
   else if(DEM_NO_SUCH_ELEMENT == ExtendedDataRecordSizeResult_u8)
   {

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
   else{

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(ExtendedDataRecordSizeResult_u8);
   }
   if(*dataNegRespCode_u8 != 0x00)
   {
        s_NegResponseCode_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
   }
}

static void Dcm_Lok_FillResponseMandatoryBytes(Dcm_MsgContextType *pMsgContext)
{
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF)
   if(DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER == s_RDTCSubFunction_u8)
   {

        pMsgContext->resData[0x05] = s_DTCStatus_Rdtc_u8;
        pMsgContext->resData[0x04] = pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE];
        pMsgContext->resData[0x03] = pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE];
        pMsgContext->resData[0x02] = pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE];
        pMsgContext->resData[0x01] = (uint8)s_DemDTCOrigin_Rdtc_u16;
        pMsgContext->resData[0x00] = s_RDTCSubFunction_u8;

        pMsgContext->resDataLen = 0x06;
   }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

   if((DSP_REPORT_EXTENDED_DATA_RECORD == s_RDTCSubFunction_u8)|| \
       (DSP_REPORT_EXTENDED_REC_MIRROR_MEM == s_RDTCSubFunction_u8))
   {

        pMsgContext->resData[0x04] = s_DTCStatus_Rdtc_u8;
        pMsgContext->resData[0x03] = pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE];
        pMsgContext->resData[0x02] = pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE];
        pMsgContext->resData[0x01] = pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE];
        pMsgContext->resData[0x00] = s_RDTCSubFunction_u8;

        pMsgContext->resDataLen = 0x05;
   }
#endif
}

static void Dcm_Lok_ExtendedDataRecordSelection(Dcm_MsgContextType *pMsgContext
   ,                                               Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType SelectExtendedDataRecordResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    Dcm_DspRDTCRecordNum_u8 = pMsgContext->reqData[DCM_DSP_RDTC_EXTENDEDDATARECORDNUMBER];

   if((0x00 == Dcm_DspRDTCRecordNum_u8)|| \
       ((Dcm_DspRDTCRecordNum_u8 >= 0xF0) && (Dcm_DspRDTCRecordNum_u8 <= 0xFD)))
   {

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
   else{
        SelectExtendedDataRecordResult_u8 = Dem_SelectExtendedDataRecord(ClientId_u8, Dcm_DspRDTCRecordNum_u8);

        if(E_OK == SelectExtendedDataRecordResult_u8)
        {

            Dcm_Lok_FillResponseMandatoryBytes(pMsgContext);
            RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_GETRECORDSDATASIZE;
        }
        else if(DEM_PENDING == SelectExtendedDataRecordResult_u8)
        {

        }
        else{

            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(SelectExtendedDataRecordResult_u8);
        }
   }
   if(*dataNegRespCode_u8 != 0x00)
   {
        s_NegResponseCode_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
   }
}

static void Dcm_Lok_DisableExtendedDataRecordUpdate(Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType DisableDTCRecordUpdateResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    DisableDTCRecordUpdateResult_u8 = Dem_DisableDTCRecordUpdate(ClientId_u8);

   if(E_OK == DisableDTCRecordUpdateResult_u8)
   {

        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_SELECTRECORDSDATA;
   }
   else if(DEM_PENDING == DisableDTCRecordUpdateResult_u8)
   {

   }
   else{

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(DisableDTCRecordUpdateResult_u8);
   }
}

static void Dcm_Lok_GetStatusOfDTC(Dcm_MsgContextType *pMsgContext
   ,                                                  Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType DTCStatusResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    DTCStatusResult_u8 = Dem_GetStatusOfDTC(ClientId_u8, &s_DTCStatus_Rdtc_u8);

   if(E_OK == DTCStatusResult_u8)
   {
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_DISABLERECORDUPDATE;
   }
   else if(DEM_PENDING == DTCStatusResult_u8)
   {

   }
   else if(DEM_NO_SUCH_ELEMENT == DTCStatusResult_u8)
   {

        pMsgContext->resData[DCM_DSP_RDTC_SUBFUNCTION] = pMsgContext->reqData[DCM_DSP_RDTC_SUBFUNCTION];

        pMsgContext->resDataLen = 0x01;
        s_SubfunctionReturnValue_u8 = E_OK;
   }
   else{

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(DTCStatusResult_u8);
   }
}

static void Dcm_Lok_GetDTCandDTCOrigin(const Dcm_MsgContextType *pMsgContext)
{

    Dsp_RdtcDTC_u32 =  ((((uint32) pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE]) << DSP_RDTC_LSH_16BITS) |
                        (((uint32) pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE]) << DSP_RDTC_LSH_08BITS) |
                         ((uint32) pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE]));

   s_DemDTCOrigin_Rdtc_u16 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF)
   if(DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER == s_RDTCSubFunction_u8)
   {
        s_DemDTCOrigin_Rdtc_u16 = pMsgContext->reqData[DCM_DSP_RDTC_MEMORYSELECTION] + DCM_DTC_ORIGIN_MEMORY_SELECTION_VALUE;
   }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)
   if(DSP_REPORT_EXTENDED_REC_MIRROR_MEM == s_RDTCSubFunction_u8)
   {
        s_DemDTCOrigin_Rdtc_u16 = DEM_DTC_ORIGIN_MIRROR_MEMORY;
   }
#endif
}

static void Dcm_Lok_RequestLengthandSelectDTC(const Dcm_MsgContextType *pMsgContext
   ,                                             Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
   uint8 RequestLength_u8 = 0x00;
    Std_ReturnType SelectDTC_u8 = DEM_BUSY;

    *dataNegRespCode_u8 = 0x00;
   s_RDTCSubFunction_u8 = pMsgContext->reqData[DCM_DSP_RDTC_SUBFUNCTION];

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))
   if((DSP_REPORT_EXTENDED_DATA_RECORD == s_RDTCSubFunction_u8)|| \
       (DSP_REPORT_EXTENDED_REC_MIRROR_MEM == s_RDTCSubFunction_u8))
   {

        RequestLength_u8 = DSP_RDTC_04_06_10_REQUEST_LENGTH;
   }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF)
   if(DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER == s_RDTCSubFunction_u8)
   {

        RequestLength_u8 = DSP_RDTC_18_19_REQUEST_LENGTH;
   }
#endif

   if(RequestLength_u8 == pMsgContext->reqDataLen)
   {

        Dcm_Lok_GetDTCandDTCOrigin(pMsgContext);

        SelectDTC_u8 = Dem_SelectDTC(ClientId_u8, Dsp_RdtcDTC_u32, DEM_DTC_FORMAT_UDS, s_DemDTCOrigin_Rdtc_u16);

        if(E_OK == SelectDTC_u8)
        {

            RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_STATUSOFDTC;
        }

        else{
            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(SelectDTC_u8);
        }

   }

   else{
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
}

static Std_ReturnType Dcm_Lok_ReEnableRecordUpdate(Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType Result_u8;
    // Reset NRC as we dont want to trigger response before compeltion of enable DTC
    *dataNegRespCode_u8 = 0x00u;

    Result_u8 = Dem_EnableDTCRecordUpdate(ClientId_u8);
   if(Result_u8 == E_OK)
   {
        // set stored NRC to dataNegRespCode_u8 and trigger final negative response
        *dataNegRespCode_u8 = s_NegResponseCode_u8;
   }
   else if(Result_u8 == DEM_PENDING)
   {
        Result_u8 = DCM_E_PENDING;
   }
   else{
        // log DET, this condition should neer occur, DTC Record update is still disabled
        DCM_DET_ERROR(DCM_RDTC_ID,DCM_E_ENABLEDTCRECORD_FAILED);

        *dataNegRespCode_u8 = s_NegResponseCode_u8;
        Result_u8 = E_NOT_OK;
   }
    return Result_u8;
}

static void Dcm_Lok_StatestoReportExtendedData(Dcm_MsgContextType *pMsgContext
   ,                                              Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{

   if(DCM_RDTC_SUBFUNCTION_INITIAL == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_RequestLengthandSelectDTC(pMsgContext, dataNegRespCode_u8);
   }

   if(DCM_RDTC_SUBFUNCTION_STATUSOFDTC == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_GetStatusOfDTC(pMsgContext, dataNegRespCode_u8);
   }

   if(DCM_RDTC_SUBFUNCTION_DISABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_DisableExtendedDataRecordUpdate(dataNegRespCode_u8);
   }

   if(DCM_RDTC_SUBFUNCTION_SELECTRECORDSDATA == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_ExtendedDataRecordSelection(pMsgContext, dataNegRespCode_u8);
   }

   if(DCM_RDTC_SUBFUNCTION_GETRECORDSDATASIZE == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_CheckforSizeOfExtendedDataRecords(pMsgContext, dataNegRespCode_u8);
   }

   if(DCM_RDTC_SUBFUNCTION_REPORTDTCRECORDS == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_ReportDTCRecords(pMsgContext, dataNegRespCode_u8);
   }
}

Std_ReturnType Dcm_Dsp_ReportExtendedDataRecordByDTCNumber(Dcm_SrvOpStatusType Opstatus
   ,                                                          Dcm_MsgContextType *pMsgContext
   ,                                                          Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{

    *dataNegRespCode_u8 = 0x00;
   s_SubfunctionReturnValue_u8 = DCM_E_PENDING;

    DCM_UNUSED_PARAM(Opstatus);

    Dcm_Lok_StatestoReportExtendedData(pMsgContext, dataNegRespCode_u8);

   if(DCM_RDTC_SUBFUNCTION_ENABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
   {
        Dcm_Lok_EnableRecordUpdate(dataNegRespCode_u8);
   }

    // To enable DTC record update in case of negative response
    // Separate state to handle asynchronous behavior of Enable DTC record update function
   if(DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
   {
        s_SubfunctionReturnValue_u8 = Dcm_Lok_ReEnableRecordUpdate(dataNegRespCode_u8);
   }

   if(*dataNegRespCode_u8 != 0u)
   {
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_INITIAL;
        s_SubfunctionReturnValue_u8 = E_NOT_OK;
   }

    return s_SubfunctionReturnValue_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
