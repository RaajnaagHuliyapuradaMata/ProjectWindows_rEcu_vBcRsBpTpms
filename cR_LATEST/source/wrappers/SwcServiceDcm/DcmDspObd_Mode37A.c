#include "Std_Types.hpp"

#include "DcmDspObd_Mode37A_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmDspObd_Mode37A_Priv.hpp"

#if(DCM_CFG_DSP_OBDMODE37A_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmObdMode37A (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(uint32_least,   AUTOMATIC)  cntrLoop_qu32;
   VAR(uint32,     AUTOMATIC)  dataMode37ADtc_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC)  nrResMaxDataLen_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC)  nrResDTCDataLen_u32;
   VAR(uint8,     AUTOMATIC)  dataDTCStatusMask_u8;
   VAR(Dem_DTCOriginType,AUTOMATIC)    dataDTCOrigin_u8;
   VAR(Dem_ReturnSetFilterType,AUTOMATIC) dataRetSetDTCFilter_u8;
   VAR(uint8,     AUTOMATIC)     stMode37ADTC_u8;
   VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)   dataRetGetNextFilt_u8;
   VAR(Std_ReturnType,     AUTOMATIC)  dataRetVal_u8;

    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8     = 0x0u;

    dataDTCStatusMask_u8  = 0x08;
    dataDTCOrigin_u8      = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    dataRetVal_u8=E_NOT_OK;

   if(pMsgContext->reqDataLen == DCM_OBDMODE37A_REQLEN)
   {

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        switch(pMsgContext->idContext)
        {
            case 0x03u:
            {

                dataDTCStatusMask_u8 = 0x08;
                dataDTCOrigin_u8     =  DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x07u:
            {

                dataDTCStatusMask_u8 = 0x04;
                dataDTCOrigin_u8     =  DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x0Au:
            {

                dataDTCStatusMask_u8 = 0x00;
                dataDTCOrigin_u8     = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
                break;
            }
            default:
            {

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                break;
            }
        }

        if(*dataNegRespCode_u8 == 0x0)
        {
            dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( dataDTCStatusMask_u8
   ,     DEM_DTC_KIND_EMISSION_REL_DTCS
   ,     DEM_DTC_FORMAT_OBD
   ,     dataDTCOrigin_u8
   ,     DEM_FILTER_WITH_SEVERITY_NO
   ,     DEM_SEVERITY_NO_SEVERITY
   ,     DEM_FILTER_FOR_FDC_NO
                                                 );

            if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
            {

            	nrResDTCDataLen_u32 = 1;

                nrResMaxDataLen_u32 = nrResMaxDataLen_u32>>1u;

                for(cntrLoop_qu32=0x0u; ((cntrLoop_qu32 < nrResMaxDataLen_u32) && (*dataNegRespCode_u8 == 0x0u)); cntrLoop_qu32++)
                {

                    dataRetGetNextFilt_u8 = Dem_GetNextFilteredDTC(&dataMode37ADtc_u32, &stMode37ADTC_u8);

                    if(dataRetGetNextFilt_u8 == DEM_FILTERED_OK)
                    {

                        pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 16uL);
                        nrResDTCDataLen_u32++;
                        pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 8uL);
                        nrResDTCDataLen_u32++;
                    }
                    else if(dataRetGetNextFilt_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                    {

                        pMsgContext->resData[0] = (uint8)nrResDTCDataLen_u32 >> 1uL;
                        dataRetVal_u8=E_OK;

                        break;
                    }
                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                        DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_RET_E_NOT_OK)

                    }
                }

                pMsgContext->resDataLen = nrResDTCDataLen_u32;
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_PARAM)
            }
        }
   }

   else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_INVALID_LENGTH)
   }

   if(*dataNegRespCode_u8 !=0)
   {
        dataRetVal_u8=E_NOT_OK;
   }

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
