#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSeverityOfDTC(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint32,AUTOMATIC)          dataDTC_u32;
   VAR(uint8,AUTOMATIC)           dataHighByte_u8;
   VAR(uint8,AUTOMATIC)           dataMiddleByte_u8;
   VAR(uint8,AUTOMATIC)           dataLowByte_u8;
   VAR( uint8,AUTOMATIC)		   stDTCStatus_u8;
   VAR(uint8,AUTOMATIC)           dataFunctionalUnit_u8;
   VAR(Dem_ReturnGetStatusOfDTCType,AUTOMATIC)    dataRetGetStatusOfDTC_u8;
   VAR(Dem_ReturnGetSeverityOfDTCType,AUTOMATIC)  dataRetGetSeverityOfDTC_u8;
   VAR(Dem_ReturnGetFunctionalUnitOfDTCType,AUTOMATIC) dataRetGetFuncUnitOfDTC_u8;

   VAR(Dem_DTCSeverityType, AUTOMATIC) dataDTCSeverity_u8;
   VAR(uint8,AUTOMATIC)  dataRDTC0x09StMask_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataretVal_u8;

    DCM_UNUSED_PARAM(OpStatus);

    *dataNegRespCode_u8 = 0x00;
    dataretVal_u8=DCM_E_PENDING;

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

        if(Dem_GetDTCStatusAvailabilityMask(&dataRDTC0x09StMask_u8) == E_OK)
        {

            dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(dataDTC_u32
   ,     DEM_DTC_KIND_ALL_DTCS
   ,     DEM_DTC_ORIGIN_PRIMARY_MEMORY
   ,     &stDTCStatus_u8
                                                  );

            if(dataRetGetStatusOfDTC_u8 == DEM_STATUS_OK)
            {

                dataRetGetSeverityOfDTC_u8 = Dem_GetSeverityOfDTC(dataDTC_u32,&dataDTCSeverity_u8);

                if((dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_OK)||
                   (dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_NOSEVERITY))
                {
   				dataRetGetFuncUnitOfDTC_u8 = Dem_GetFunctionalUnitOfDTC(dataDTC_u32,&dataFunctionalUnit_u8);
   				if(dataRetGetFuncUnitOfDTC_u8 == DEM_GET_SEVERITYOFDTC_OK)
   				{

   					pMsgContext->resData[0x00] = pMsgContext->reqData[0x0];
   					pMsgContext->resData[0x01] = dataRDTC0x09StMask_u8;

   					if(dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_NOSEVERITY)
   					{
   						dataDTCSeverity_u8 = 0x00;
   					}
   					pMsgContext->resData[0x02] = dataDTCSeverity_u8;
   					pMsgContext->resData[0x03] = dataFunctionalUnit_u8;
   					pMsgContext->resData[0x04] = dataHighByte_u8;
   					pMsgContext->resData[0x05] = dataMiddleByte_u8;
   					pMsgContext->resData[0x06] = dataLowByte_u8;
   					pMsgContext->resData[0x07] = stDTCStatus_u8;
   					pMsgContext->resDataLen    = 0x08;
                        dataretVal_u8=E_OK;
   				}
   				else
   				{
   					*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataretVal_u8=E_NOT_OK;
   				}
                }
                else if(dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_WRONG_DTC)
                {
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataretVal_u8=E_NOT_OK;
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    dataretVal_u8=E_NOT_OK;
                }
            }

            else if(DEM_STATUS_FAILED==dataRetGetStatusOfDTC_u8)
            {

                pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];

                pMsgContext->resDataLen = 0x01;
                dataretVal_u8=E_OK;
            }

            else if((DEM_STATUS_WRONG_DTC == dataRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== dataRetGetStatusOfDTC_u8)||       \
                    (DEM_STATUS_WRONG_DTCKIND== dataRetGetStatusOfDTC_u8))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8=E_NOT_OK;
            }

            else{
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        else{
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8=E_NOT_OK;
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        dataretVal_u8=E_NOT_OK;
   }
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

