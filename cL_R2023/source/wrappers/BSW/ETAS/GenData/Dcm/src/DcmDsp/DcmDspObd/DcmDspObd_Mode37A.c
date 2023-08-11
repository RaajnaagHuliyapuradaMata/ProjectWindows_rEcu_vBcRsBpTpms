
#include "Dcm_Cfg_Prot.h"
#include "DcmDspObd_Mode37A_Priv.h"
#include "Rte_Dcm.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE37A_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static Std_ReturnType Dcm_Lok_CheckDTCFilteredStatus (
        Dcm_MsgLenType  nrResMaxDataLen_u32,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint8                            ClientID_u8;
    uint32                           dataMode37ADtc_u32;
    uint8                            stMode37ADTC_u8;
    Dcm_MsgLenType                   nrResDTCDataLen_u32;
    uint32_least                     cntrLoop_qu32;
    Dem_ReturnGetNextFilteredDTCType dataRetGetNextFilt_u8;
    Std_ReturnType                   dataRetVal_u8;

    dataRetVal_u8 = E_OK;

    nrResDTCDataLen_u32 = 1;

    nrResMaxDataLen_u32 = nrResMaxDataLen_u32>>1u;

    for(cntrLoop_qu32 = 0x0u; ((cntrLoop_qu32 < nrResMaxDataLen_u32) && (*dataNegRespCode_u8 == 0x0u)); cntrLoop_qu32++)
    {
        ClientID_u8 = Dcm_Lok_GetDemClientId(DCM_OBDCONTEXT);

        dataRetGetNextFilt_u8 = Dem_GetNextFilteredDTC(ClientID_u8,
                                                       &dataMode37ADtc_u32,
                                                       &stMode37ADTC_u8);
        if(dataRetGetNextFilt_u8 == E_OK)
        {

            pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 16uL);
            nrResDTCDataLen_u32++;
            pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 8uL);
            nrResDTCDataLen_u32++;
        }
        else if(dataRetGetNextFilt_u8 == DEM_NO_SUCH_ELEMENT)
        {

            pMsgContext->resData[0] = (uint8)nrResDTCDataLen_u32 >> 1uL;

            break;
        }
        else
        {

           *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            dataRetVal_u8      = E_NOT_OK;
        }
    }

    pMsgContext->resDataLen = nrResDTCDataLen_u32;

    return(dataRetVal_u8);
}

Std_ReturnType Dcm_DcmObdMode37A (
        Dcm_SrvOpStatusType OpStatus,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint8                   ClientID_u8;
    Dcm_MsgLenType          nrResMaxDataLen_u32;
    uint8                   dataDTCStatusMask_u8;
    Dem_DTCOriginType       dataDTCOrigin_u16;
    Dem_ReturnSetFilterType dataRetSetDTCFilter_u8;
    Std_ReturnType          dataRetVal_u8;

    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8 = 0x0u;

    dataDTCStatusMask_u8  = 0x08;
    dataDTCOrigin_u16      = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    dataRetVal_u8         = E_OK;

    if(pMsgContext->reqDataLen == DCM_OBDMODE37A_REQLEN)
    {

        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        switch(pMsgContext->idContext)
        {
            case 0x03u:
            {

                dataDTCStatusMask_u8 = 0x08;
                dataDTCOrigin_u16     = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x07u:
            {

                dataDTCStatusMask_u8 = 0x04;
                dataDTCOrigin_u16     = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x0Au:
            {

                dataDTCStatusMask_u8 = 0x00;
                dataDTCOrigin_u16     = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
                break;
            }
            default:
            {

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                dataRetVal_u8       = E_NOT_OK;
                break;
            }
        }

        if((pMsgContext->idContext == 0x03u)||
           (pMsgContext->idContext == 0x07u)||
           (pMsgContext->idContext == 0x0Au))
        {
            ClientID_u8 = Dcm_Lok_GetDemClientId(DCM_OBDCONTEXT);

            dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(ClientID_u8,
                                                      dataDTCStatusMask_u8,
                                                      DEM_DTC_FORMAT_OBD,
                                                      dataDTCOrigin_u16,
                                                      FALSE,
                                                      DEM_SEVERITY_NO_SEVERITY,
                                                      FALSE);
            if(dataRetSetDTCFilter_u8 == E_OK)
            {
                dataRetVal_u8 = Dcm_Lok_CheckDTCFilteredStatus(nrResMaxDataLen_u32,
                                                               pMsgContext,
                                                               dataNegRespCode_u8);
            }
            else
            {

                *dataNegRespCode_u8 = Dcm_Lok_SetErrorCodeForDemOperation(dataRetSetDTCFilter_u8);
                dataRetVal_u8       = E_NOT_OK;
            }
        }
    }

    else
    {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         dataRetVal_u8      = E_NOT_OK;
    }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif
