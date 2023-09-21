#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_GetFreezeFrameDataByRecord (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,     AUTOMATIC) retVal_u8;
   VAR(boolean,     AUTOMATIC) isNRCSet_b;
   VAR(uint8,     AUTOMATIC) stDTCStatus_u8;
   VAR(uint8,     AUTOMATIC) dataRDTCSubFunc_u8;
   VAR(uint8,     AUTOMATIC) dataRecordNum_u8;
   VAR(Dem_ReturnGetStatusOfDTCType,     AUTOMATIC) stRetGetStatusOfDTC_u8;
   VAR(Dem_ReturnGetFreezeFrameDataByRecordType,   AUTOMATIC) dataRetGetFreezeFrameDataByRecordType_u8;
   VAR(uint8,     AUTOMATIC) idxLoop_u8;
   VAR(uint8,     AUTOMATIC) NoDTCrecordCounter_u8 = 0;
   VAR(uint8,     AUTOMATIC) WrongDTCCounter_u8 = 0;
   VAR(uint16,     AUTOMATIC) dataAvailableBuffLen_u16;
   VAR(uint32,     AUTOMATIC) dataDTC_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataFillRespLen_u32;
   VAR(Dcm_MsgLenType,     AUTOMATIC) dataRemainBuffer_u32;

    *dataNegRespCode_u8 = 0x00;

   isNRCSet_b = FALSE;
    dataFillRespLen_u32 = 0;
    dataRetGetFreezeFrameDataByRecordType_u8 = DEM_GET_FFBYRECORD_OK ;
   stRetGetStatusOfDTC_u8  = DEM_STATUS_OK;
    retVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

   if(DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER == dataRDTCSubFunc_u8 )
   {

        if(DSP_RDTC_05_REQLEN == pMsgContext->reqDataLen)
        {

            dataRecordNum_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC +1u];

            pMsgContext->resData[0] = DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER;
            pMsgContext->resDataLen = 0x01;

            dataFillRespLen_u32 = 6;

            if(0xFF == dataRecordNum_u8 )
            {
                idxLoop_u8 = 0x00 ;
            }
            else{

                idxLoop_u8 = dataRecordNum_u8 ;
            }
            do
            {

                if(pMsgContext->resMaxDataLen > dataFillRespLen_u32)
                {
                    dataRemainBuffer_u32 = (pMsgContext->resMaxDataLen - dataFillRespLen_u32);
                }
                else{
                    dataRemainBuffer_u32 = 0x00;
                }

                dataAvailableBuffLen_u16 = (uint16)dataRemainBuffer_u32;

                dataRetGetFreezeFrameDataByRecordType_u8 = Dem_GetFreezeFrameDataByRecord(idxLoop_u8,DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,     &dataDTC_u32,&pMsgContext->resData[dataFillRespLen_u32]
   ,     &dataAvailableBuffLen_u16);

                if( DEM_GET_FFBYRECORD_OK == dataRetGetFreezeFrameDataByRecordType_u8)
                {

                    stRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC( dataDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,     &stDTCStatus_u8);

                    if(DEM_STATUS_OK ==stRetGetStatusOfDTC_u8)
                    {

                        pMsgContext->resData[dataFillRespLen_u32-5u] = idxLoop_u8;
                        pMsgContext->resData[dataFillRespLen_u32-4u] = (uint8)(dataDTC_u32>>16u);
                        pMsgContext->resData[dataFillRespLen_u32-3u] = (uint8)(dataDTC_u32>>8u);
                        pMsgContext->resData[dataFillRespLen_u32-2u] = (uint8)(dataDTC_u32);
                        pMsgContext->resData[dataFillRespLen_u32-1u] = stDTCStatus_u8;

                        pMsgContext->resDataLen = dataFillRespLen_u32+dataAvailableBuffLen_u16;
                        if(0xFF == dataRecordNum_u8 )
                        {

                            dataFillRespLen_u32 = dataFillRespLen_u32 + dataAvailableBuffLen_u16 + 5u;
                        }
                        else{
                            retVal_u8=E_OK;
                        }
                    }

                    else if(DEM_STATUS_FAILED==stRetGetStatusOfDTC_u8)
                    {

                        pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                        pMsgContext->resDataLen = 0x01;
                        retVal_u8=E_OK;
                    }

                    else if((DEM_STATUS_WRONG_DTC == stRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== stRetGetStatusOfDTC_u8)||       \
                            (DEM_STATUS_WRONG_DTCKIND== stRetGetStatusOfDTC_u8))
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                        isNRCSet_b = TRUE;
                    }

                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                        isNRCSet_b = TRUE;
                    }
                }

                else if(DEM_GET_FFBYRECORD_WRONG_RECORD == dataRetGetFreezeFrameDataByRecordType_u8 )
                {

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                        NoDTCrecordCounter_u8++ ;
                        WrongDTCCounter_u8++;

                }
                else if(DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD == dataRetGetFreezeFrameDataByRecordType_u8 )
                {
                    retVal_u8=E_OK;
                    NoDTCrecordCounter_u8++ ;

                    if(0xFF != dataRecordNum_u8 )
                    {

                        pMsgContext->resData[1] = dataRecordNum_u8;
                        pMsgContext->resDataLen =2;
                    }
                }

                else if(DEM_GET_FFBYRECORD_WRONG_BUFFERSIZE == dataRetGetFreezeFrameDataByRecordType_u8 )
                {

                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;

                }

                else{
                    if(0xFF != dataRecordNum_u8 )
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                        isNRCSet_b = TRUE;
                    }
                }

                if((DEM_GET_FFBYRECORD_OK == dataRetGetFreezeFrameDataByRecordType_u8) && (DEM_STATUS_FAILED == stRetGetStatusOfDTC_u8))
                {

                    break;
                }

                if(0xFF != dataRecordNum_u8)
                {

                    idxLoop_u8 = 0xFF;
                }
                else{
                    idxLoop_u8++;
                }

            }while((*dataNegRespCode_u8 != DCM_E_RESPONSETOOLONG )&&(idxLoop_u8 < 0xFFu)&& (isNRCSet_b != TRUE) );

            if((NoDTCrecordCounter_u8 == 0xFF) && (WrongDTCCounter_u8 != 0xFF))
            {
                pMsgContext->resData[1] = dataRecordNum_u8;
                pMsgContext->resDataLen =2;
            }

            if((0xFF == dataRecordNum_u8) && (pMsgContext->resDataLen >= 2u))
            {

                if((*dataNegRespCode_u8 !=0u) &&  (*dataNegRespCode_u8 != DCM_E_RESPONSETOOLONG) && (isNRCSet_b != TRUE))
                {
                    *dataNegRespCode_u8 = 0;
                }
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
