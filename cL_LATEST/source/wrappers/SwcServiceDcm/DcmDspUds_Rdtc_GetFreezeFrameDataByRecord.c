

#include "DcmDspUds_Rdtc_Inf.hpp"
#include "Rte_Dcm.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType Dcm_Dsp_GetFreezeFrameDataByRecord (Dcm_SrvOpStatusType OpStatus,\
                                                   Dcm_MsgContextType *pMsgContext,\
                                                   Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
   uint8   dataRDTCSubFunc_u8;
   uint8   dataRecordNum_u8;
   uint8   dataRetGetDTCOfOBDFreezeFrame_u8;
   uint8   dataRetGetSelectDTC_u8;
   uint8   dataretReadDataOfOBDFreezeFrame_u8 = E_OK;
   uint8   nrPid_u8;

   uint16  idxPIDData_qu16;
   uint16  dataAvailableBuffLen_u16;
   uint16  idxDataSource_u16;
   uint16  datafillBufLen_u16;

    Dcm_MsgLenType  dataFillRespLen_u32;
    Dcm_MsgLenType  dataRemainBuffer_u32;
    Std_ReturnType  dataRetGetStatusOfDTC_u8;
    Std_ReturnType retVal_u8 = DCM_E_PENDING;

   uint16  DidNumber_u16;
   static uint32  dataDTC_u32;
   static uint8   stDTCStatus_u8;
   boolean databreakLoop_b = FALSE;

    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8         = 0u;

    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

   if(DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER == dataRDTCSubFunc_u8 )
   {

        if(DSP_RDTC_05_REQLEN == pMsgContext->reqDataLen)
        {

            dataRecordNum_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC +1u];

            pMsgContext->resData[0] = DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER;
            pMsgContext->resDataLen = 0x01;

            dataFillRespLen_u32 = 6;

            if(dataRecordNum_u8 == 0x00u)
            {
                if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
                {

                    dataRetGetDTCOfOBDFreezeFrame_u8 = Dem_DcmGetDTCOfOBDFreezeFrame(dataRecordNum_u8
   ,                                                                                    &dataDTC_u32
   ,                                                                                    DEM_DTC_FORMAT_UDS);

                    if(E_OK == dataRetGetDTCOfOBDFreezeFrame_u8)
                    {

                        dataRetGetSelectDTC_u8 = Dem_SelectDTC(ClientId_u8
   ,                                                              dataDTC_u32
   ,                                                              DEM_DTC_FORMAT_UDS
   ,                                                              DEM_DTC_ORIGIN_PRIMARY_MEMORY);

                        if(E_OK == dataRetGetSelectDTC_u8)
                        {
                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_GETDTCSTATUS;
                        }
                        else
                        {
                            *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetSelectDTC_u8);
                            retVal_u8 = E_NOT_OK;
                        }
                    }

                    else
                    {

                        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetDTCOfOBDFreezeFrame_u8);
                        retVal_u8 = E_NOT_OK;
                    }
                }

                if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_GETDTCSTATUS)
                {

                    dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(ClientId_u8,&stDTCStatus_u8);

                    if(E_OK == dataRetGetStatusOfDTC_u8)
                    {
                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                    }

                    else if(DEM_NO_SUCH_ELEMENT == dataRetGetStatusOfDTC_u8)
                    {

                        pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                        pMsgContext->resDataLen = 0x01;
                        retVal_u8 = E_OK;
                    }
                    else if(DEM_PENDING == dataRetGetStatusOfDTC_u8)
                    {

                        retVal_u8 = DCM_E_PENDING;
                    }
                    else
                    {

                        *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetGetStatusOfDTC_u8);
                        retVal_u8 = E_NOT_OK;
                    }
                }

                if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
                {

                    pMsgContext->resData[dataFillRespLen_u32-5u] = dataRecordNum_u8;
                    pMsgContext->resData[dataFillRespLen_u32-4u] = (uint8)(dataDTC_u32>>16u);
                    pMsgContext->resData[dataFillRespLen_u32-3u] = (uint8)(dataDTC_u32>>8u);
                    pMsgContext->resData[dataFillRespLen_u32-2u] = (uint8)(dataDTC_u32);
                    pMsgContext->resData[dataFillRespLen_u32-1u] = stDTCStatus_u8;
                    pMsgContext->resData[dataFillRespLen_u32]    = DCM_CFG_DSP_NUMPIDSUPP_MODE2;

                    pMsgContext->resDataLen = dataFillRespLen_u32;

                    dataFillRespLen_u32++;

                    for(nrPid_u8 = 0; nrPid_u8 < DCM_CFG_DSP_NUMPIDSUPP_MODE2; nrPid_u8++)
                    {
                        DidNumber_u16 = (uint16)(Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Id_u8 + 0xF400u);

                        pMsgContext->resData[dataFillRespLen_u32] = (uint8)((DidNumber_u16 >> 0x08u) & 0x00FFu);
                        dataFillRespLen_u32++;

                        pMsgContext->resData[dataFillRespLen_u32] = (uint8)(DidNumber_u16 & 0x00FFu);
                        dataFillRespLen_u32++;

                        idxPIDData_qu16 = Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].DataSourcePid_ArrayIndex_u16;

                        for(idxDataSource_u16 = (uint16)idxPIDData_qu16;((idxDataSource_u16<(idxPIDData_qu16 + Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Num_DataSourcePids_u8)) && (dataretReadDataOfOBDFreezeFrame_u8 == E_OK));idxDataSource_u16++)
                        {

                            if(pMsgContext->resMaxDataLen > dataFillRespLen_u32)
                            {
                                dataRemainBuffer_u32 = (pMsgContext->resMaxDataLen - dataFillRespLen_u32);

                                dataAvailableBuffLen_u16 = \
                                        (uint8)Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8;

                                if(dataAvailableBuffLen_u16 > dataRemainBuffer_u32)
                                {
                                    databreakLoop_b = TRUE;
                                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                                    retVal_u8 = E_NOT_OK;
                                }
                            }

                            else
                            {
                                databreakLoop_b = TRUE;
                                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                                retVal_u8 = E_NOT_OK;
                            }

                            if(databreakLoop_b == FALSE)
                            {

                                dataretReadDataOfOBDFreezeFrame_u8 = \
                                        Dem_DcmReadDataOfOBDFreezeFrame(Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Id_u8,\
                                                                        (uint8)(idxDataSource_u16-idxPIDData_qu16), \
                                                                        &pMsgContext->resData[dataFillRespLen_u32], \
                                                                        &dataAvailableBuffLen_u16);

                                if(E_OK == dataretReadDataOfOBDFreezeFrame_u8)
                                {

                                    if(dataAvailableBuffLen_u16 == 0u)
                                    {
                                        for(datafillBufLen_u16 = 0; datafillBufLen_u16 < Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8 ; datafillBufLen_u16++)
                                        {
                                            pMsgContext->resData[dataFillRespLen_u32] = 0x00;
                                            dataFillRespLen_u32++;
                                            dataAvailableBuffLen_u16++;
                                        }
                                        pMsgContext->resDataLen = dataFillRespLen_u32 + dataAvailableBuffLen_u16;
                                    }
                                    else
                                    {

                                        pMsgContext->resDataLen = dataFillRespLen_u32 + dataAvailableBuffLen_u16;

                                        dataFillRespLen_u32 = dataFillRespLen_u32 + dataAvailableBuffLen_u16;
                                    }

                                    retVal_u8 = E_OK;
                                }

                                else
                                {
                                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                                    retVal_u8 = E_NOT_OK;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        if(databreakLoop_b != FALSE)
                        {
                            break;
                        }
                    }
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }

        }
        else{

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
   }

   if(0x0 != (*dataNegRespCode_u8))
   {
        retVal_u8=E_NOT_OK;
   }

    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
