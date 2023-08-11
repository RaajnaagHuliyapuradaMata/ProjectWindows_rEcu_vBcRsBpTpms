

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Rdtc_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(DCM_CFG_DSP_REPORTDTC_OR_USERDEFINEDMEMORYDTC_SNAPSHOTRECORDBYDTCNUMBER != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static uint8 s_SnapShotRecordRDTCSubFunction_u8;

static Std_ReturnType s_SubServiceReturnValue_u8;
static uint8 s_DTCStatus_u8;
static uint8 s_MaxRecordstoRead_Rdtc_u8;
static Dcm_NegativeResponseCodeType s_NegResponse_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
static Dem_DTCOriginType s_DemDTCOriginMemory_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static boolean s_isFreezeFrameRecordSupported_b = FALSE;

static void Dcm_Lok_EnableRecordUpdate(Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType EnableRecordUpdateResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    EnableRecordUpdateResult_u8 = Dem_EnableDTCRecordUpdate(ClientId_u8);

    if(E_OK == EnableRecordUpdateResult_u8)
    {
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_INITIAL;
        s_isFreezeFrameRecordSupported_b = FALSE;
        s_SubServiceReturnValue_u8 = E_OK;
    }
    else if(DEM_PENDING == EnableRecordUpdateResult_u8)
    {

    }
    else
    {

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(EnableRecordUpdateResult_u8);
    }
}

static void Dcm_Lok_ReportDTCSnapshotRecords(Dcm_MsgContextType *pMsgContext,
                                                   Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    boolean isDemNoSuchElementReturned_b = FALSE;
    boolean isPendingReturned_b = FALSE;
    uint8 LoopIndex_u8 = 0x00;
    uint16 DTCFreezeFrameDataSize_u16;
    Dcm_MsgLenType FilledResponseLength_u32;
    Std_ReturnType GetNextSnapshotRecordResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    do
    {
        LoopIndex_u8++;

        FilledResponseLength_u32 = pMsgContext->resDataLen;

        DTCFreezeFrameDataSize_u16 = (uint16)(pMsgContext->resMaxDataLen - FilledResponseLength_u32);

        GetNextSnapshotRecordResult_u8 = Dem_GetNextFreezeFrameData(ClientId_u8,
                                                                    &pMsgContext->resData[FilledResponseLength_u32],
                                                                    &DTCFreezeFrameDataSize_u16);
        if(E_OK == GetNextSnapshotRecordResult_u8)
        {

            if(DTCFreezeFrameDataSize_u16 > 0x00)
            {

                pMsgContext->resDataLen = (DTCFreezeFrameDataSize_u16 + FilledResponseLength_u32);
            }
            s_isFreezeFrameRecordSupported_b = TRUE;
            Dcm_DspRDTCRecordNum_u8++;

        }
        else if(DEM_PENDING == GetNextSnapshotRecordResult_u8)
        {

            isPendingReturned_b = TRUE;
        }
        else if(DEM_NO_SUCH_ELEMENT == GetNextSnapshotRecordResult_u8)
        {
            isDemNoSuchElementReturned_b = TRUE;
            break;
        }
        else
        {

            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(GetNextSnapshotRecordResult_u8);
        }

    }while((0x00 == *dataNegRespCode_u8)&&(FALSE == isPendingReturned_b)&& \
           (LoopIndex_u8 < DCM_CFG_RDTC_MAXNUMRECREAD)&&(Dcm_DspRDTCRecordNum_u8 <= s_MaxRecordstoRead_Rdtc_u8));

    if((0x00 == *dataNegRespCode_u8)&&(FALSE == isPendingReturned_b)&& \
            ((isDemNoSuchElementReturned_b == TRUE)||(Dcm_DspRDTCRecordNum_u8 > s_MaxRecordstoRead_Rdtc_u8)))
    {
        if(s_isFreezeFrameRecordSupported_b == TRUE)
        {

            RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_ENABLERECORDUPDATE;
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    if(*dataNegRespCode_u8 != 0x00)
    {
        s_NegResponse_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
    }
}

static void Dcm_Lok_NumberOfRecordstoReport(void)
{
    if(0xFF == Dcm_DspRDTCRecordNum_u8)
    {

        Dcm_DspRDTCRecordNum_u8 = 0x01;
        s_MaxRecordstoRead_Rdtc_u8 = 0xFE;
    }
    else
    {

        s_MaxRecordstoRead_Rdtc_u8 = Dcm_DspRDTCRecordNum_u8;
    }

    RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REPORTDTCRECORDS;
}

static void Dcm_Lok_CheckforSizeOfSnapshotRecords(const Dcm_MsgContextType *pMsgContext,
                                                  Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType SnapshotRecordSizeResult_u8 = E_NOT_OK;
    uint16 SizeOfSnapshotRecord_u16 = 0x00;

    *dataNegRespCode_u8 = 0x00;

    SnapshotRecordSizeResult_u8 = Dem_GetSizeOfFreezeFrameSelection(ClientId_u8, &SizeOfSnapshotRecord_u16);

    if(E_OK == SnapshotRecordSizeResult_u8)
    {
        if(pMsgContext->resMaxDataLen >= (Dcm_MsgLenType)(SizeOfSnapshotRecord_u16 + pMsgContext->resDataLen))
        {

            Dcm_Lok_NumberOfRecordstoReport();
        }
        else
        {
            *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
        }
    }
    else if(DEM_PENDING == SnapshotRecordSizeResult_u8)
    {

    }
    else if(DEM_NO_SUCH_ELEMENT == SnapshotRecordSizeResult_u8)
    {
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(SnapshotRecordSizeResult_u8);
    }
    if(*dataNegRespCode_u8 != 0x00)
    {
        s_NegResponse_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
    }
}

static void Dcm_Lok_FillResponseMandatoryBytes(Dcm_MsgContextType *pMsgContext)
{
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)
    if(DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER == s_SnapShotRecordRDTCSubFunction_u8)
    {

        pMsgContext->resData[0x05] = s_DTCStatus_u8;
        pMsgContext->resData[0x04] = pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE];
        pMsgContext->resData[0x03] = pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE];
        pMsgContext->resData[0x02] = pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE];
        pMsgContext->resData[0x01] = (uint8)s_DemDTCOriginMemory_u16;
        pMsgContext->resData[0x00] = s_SnapShotRecordRDTCSubFunction_u8;

        pMsgContext->resDataLen = 0x06;
    }
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)

    if(DSP_REPORT_SNAPSHOT_RECORD_BY_DTC == s_SnapShotRecordRDTCSubFunction_u8)
    {

        pMsgContext->resData[0x04] = s_DTCStatus_u8;
        pMsgContext->resData[0x03] = pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE];
        pMsgContext->resData[0x02] = pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE];
        pMsgContext->resData[0x01] = pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE];
        pMsgContext->resData[0x00] = s_SnapShotRecordRDTCSubFunction_u8;

        pMsgContext->resDataLen = 0x05;
    }
#endif
}

static void Dcm_Lok_SnapshotRecordSelection(Dcm_MsgContextType *pMsgContext,
                                            Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType SelectSnapshotRecordResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    Dcm_DspRDTCRecordNum_u8 = pMsgContext->reqData[DCM_DSP_RDTC_EXTENDEDDATARECORDNUMBER];

    SelectSnapshotRecordResult_u8 = Dem_SelectFreezeFrameData(ClientId_u8, Dcm_DspRDTCRecordNum_u8);

    if(E_OK == SelectSnapshotRecordResult_u8)
    {

        Dcm_Lok_FillResponseMandatoryBytes(pMsgContext);

        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_GETRECORDSDATASIZE;
    }
    else if(DEM_PENDING == SelectSnapshotRecordResult_u8)
    {

    }
    else
    {

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(SelectSnapshotRecordResult_u8);
    }
    if(*dataNegRespCode_u8 != 0x00)
    {
        s_NegResponse_u8 = *dataNegRespCode_u8;
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE;
    }
}

static void Dcm_Lok_DisableSnapshotRecordUpdate(Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
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
    else
    {

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(DisableDTCRecordUpdateResult_u8);
    }
}

static void Dcm_Lok_StatusOfDTC(Dcm_MsgContextType *pMsgContext,
                                Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    Std_ReturnType DTCStatusResult_u8 = E_NOT_OK;

    *dataNegRespCode_u8 = 0x00;

    DTCStatusResult_u8 = Dem_GetStatusOfDTC(ClientId_u8, &s_DTCStatus_u8);

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
        s_SubServiceReturnValue_u8 = E_OK;
    }
    else
    {

        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(DTCStatusResult_u8);
    }
}

static void Dcm_Lok_GetDTCandDTCOrigin(const Dcm_MsgContextType *pMsgContext)
{

    Dsp_RdtcDTC_u32 =  ((((uint32) pMsgContext->reqData[DCM_DSP_RDTC_HIGHBYTE]) << DSP_RDTC_LSH_16BITS) |
                        (((uint32) pMsgContext->reqData[DCM_DSP_RDTC_MIDDLEBYTE]) << DSP_RDTC_LSH_08BITS) |
                         ((uint32) pMsgContext->reqData[DCM_DSP_RDTC_LOWBYTE]));

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)
    if(DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER == s_SnapShotRecordRDTCSubFunction_u8)
    {
        s_DemDTCOriginMemory_u16 = pMsgContext->reqData[DCM_DSP_RDTC_MEMORYSELECTION] + DCM_DTC_ORIGIN_MEMORY_SELECTION_VALUE;

    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)
    if(DSP_REPORT_SNAPSHOT_RECORD_BY_DTC == s_SnapShotRecordRDTCSubFunction_u8)
    {
        s_DemDTCOriginMemory_u16 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }
#endif
}

static void Dcm_Lok_GetRequestLengthandSelectDTC(const Dcm_MsgContextType *pMsgContext,
                                                 Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint8 RequestLength_u8 = 0x00u;
    Std_ReturnType SelectDTC_u8 = DEM_BUSY;

    *dataNegRespCode_u8 = 0x00;

    s_SnapShotRecordRDTCSubFunction_u8 = pMsgContext->reqData[DCM_DSP_RDTC_SUBFUNCTION];

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)
    if(DSP_REPORT_SNAPSHOT_RECORD_BY_DTC == s_SnapShotRecordRDTCSubFunction_u8)
    {

        RequestLength_u8 = DSP_RDTC_04_06_10_REQUEST_LENGTH;
    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)
    if(DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER == s_SnapShotRecordRDTCSubFunction_u8)
    {

        RequestLength_u8 = DSP_RDTC_18_19_REQUEST_LENGTH;
    }
#endif

    if(RequestLength_u8 == pMsgContext->reqDataLen)
    {

        Dcm_Lok_GetDTCandDTCOrigin(pMsgContext);

        SelectDTC_u8 = Dem_SelectDTC(ClientId_u8, Dsp_RdtcDTC_u32, DEM_DTC_FORMAT_UDS, s_DemDTCOriginMemory_u16);

        if(E_OK == SelectDTC_u8)
        {
            RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_STATUSOFDTC;
        }

        else
        {
            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(SelectDTC_u8);
        }
    }

    else
    {
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
        *dataNegRespCode_u8 = s_NegResponse_u8;
    }
    else if(Result_u8 == DEM_PENDING)
    {
        Result_u8 = DCM_E_PENDING;
    }
    else
    {
        // log DET, this condition should never occur, DTC Record update is still disabled
        DCM_DET_ERROR(DCM_RDTC_ID,DCM_E_ENABLEDTCRECORD_FAILED);

        *dataNegRespCode_u8 = s_NegResponse_u8;
        Result_u8 = E_NOT_OK;
    }
    return Result_u8;
}

static void Dcm_Lok_StatestoReportSnapshotRecords(Dcm_MsgContextType *pMsgContext,
                                                  Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{

    if(DCM_RDTC_SUBFUNCTION_INITIAL == RDTCExtendedandSnapshotDataState_en)
    {

        Dcm_Lok_GetRequestLengthandSelectDTC(pMsgContext, dataNegRespCode_u8);
    }

    if(DCM_RDTC_SUBFUNCTION_STATUSOFDTC == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_StatusOfDTC(pMsgContext, dataNegRespCode_u8);
    }

    if(DCM_RDTC_SUBFUNCTION_DISABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_DisableSnapshotRecordUpdate(dataNegRespCode_u8);
    }

    if(DCM_RDTC_SUBFUNCTION_SELECTRECORDSDATA == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_SnapshotRecordSelection(pMsgContext, dataNegRespCode_u8);
    }

    if(DCM_RDTC_SUBFUNCTION_GETRECORDSDATASIZE == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_CheckforSizeOfSnapshotRecords(pMsgContext, dataNegRespCode_u8);
    }

    if(DCM_RDTC_SUBFUNCTION_REPORTDTCRECORDS == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_ReportDTCSnapshotRecords(pMsgContext, dataNegRespCode_u8);
    }
}

Std_ReturnType Dcm_Dsp_ReportSnapshotRecordByDTCNumber(Dcm_SrvOpStatusType Opstatus,
                                                       Dcm_MsgContextType *pMsgContext,
                                                       Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{

    *dataNegRespCode_u8 = 0x00;
    s_SubServiceReturnValue_u8 = DCM_E_PENDING;

    DCM_UNUSED_PARAM(Opstatus);

    Dcm_Lok_StatestoReportSnapshotRecords(pMsgContext, dataNegRespCode_u8);

    if(DCM_RDTC_SUBFUNCTION_ENABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
    {
        Dcm_Lok_EnableRecordUpdate(dataNegRespCode_u8);
    }

    // To enable DTC record update in case of negative response
    // Separate state to handle asynchronous behavior of Enable DTC record update function
    if(DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
    {
        s_SubServiceReturnValue_u8 = Dcm_Lok_ReEnableRecordUpdate(dataNegRespCode_u8);
    }

    if(*dataNegRespCode_u8 != 0)
    {
        RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_INITIAL;
        s_SubServiceReturnValue_u8 = E_NOT_OK;
    }

    return s_SubServiceReturnValue_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif
