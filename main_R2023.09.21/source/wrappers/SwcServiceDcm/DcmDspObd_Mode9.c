#include "Std_Types.hpp"

#include "DcmDspObd_Mode9_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

#include "DcmDspObd_Mode9_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(uint8, DCM_VAR) Dcm_dataDspInfoType_u8;

static VAR(uint8, DCM_VAR) Dcm_idxDspInfoType_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint16, DCM_VAR) Dcm_idxDspVehData_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,DCM_VAR) Dcm_stOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspMode09Type_ten,DCM_VAR) Dcm_stDspMode09_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_DcmObdMode09_Ini(void){

   if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
   {
        Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
#if(DCM_CFG_DSP_OBDMODE9_DEM_SUPP != DCM_CFG_OFF)

        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_DEM_FNC)
        {
            Dem_DcmCancelOperation();
        }
#endif

        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
        {

            (void)((*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(DCM_CANCEL,NULL_PTR,NULL_PTR));

        }
   }
    Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
    Dcm_stOpStatus_u8 = DCM_INITIAL;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode09 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8;
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8;
   VAR(uint8,AUTOMATIC) DataValueBufferSize_u8;
   VAR(uint32, AUTOMATIC) dataInfoTypeMaskVal_u32;
   VAR(uint32, AUTOMATIC) dataCalInfotypeBitMask_u32;
   VAR(Dcm_MsgLenType, AUTOMATIC) nrReqDataLen_u32;
   VAR(uint16_least, AUTOMATIC) idxInfotypeResBuf_qu16;
   VAR(uint8_least, AUTOMATIC) idxinfoTypeStart_qu8;
   VAR(uint8_least, AUTOMATIC) nrInfoTypeMaxLoop_qu8;
   VAR(uint8_least, AUTOMATIC) nrInfoTypeChk_qu8;
   VAR(uint8_least, AUTOMATIC) nrInfotype_qu8;
   VAR(uint8, AUTOMATIC) adrTmpBuf_au8[DCM_OBDMODE09_REQ_LEN_MAX];
   VAR(uint8, AUTOMATIC) idxInfoType_u8;
   VAR(uint8, AUTOMATIC) nrMultiple_u8;
   VAR(Std_ReturnType, AUTOMATIC) dataInfotypeFnResult_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    *dataNegRespCode_u8 = 0x0u;
   idxInfotypeResBuf_qu16 = 0x0u;
    nrInfotype_qu8 = 0x0u;
   idxinfoTypeStart_qu8 = 0x0u;
    dataCalInfotypeBitMask_u32 = 0x0u;
    adrTmpBuf_au8[0] = 0x0u;
    nrMultiple_u8 = 0x0u;
    nrReqDataLen_u32 = (pMsgContext->reqDataLen);
    dataInfotypeFnResult_u8 = E_NOT_OK;
    dataRetVal_u8 = E_NOT_OK;

   if(OpStatus == DCM_CANCEL)
   {
        Dcm_DcmObdMode09_Ini();
        dataRetVal_u8 = E_OK;
   }

   else{
        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_INIT)
        {

            if((nrReqDataLen_u32 > DCM_OBDMODE09_REQ_LEN_MIN) && (nrReqDataLen_u32 < DCM_OBDMODE09_REQ_LEN_MAX))
            {

                adrReqBuf_pu8 = pMsgContext->reqData;

                for(nrInfoTypeChk_qu8 = 0; (nrInfoTypeChk_qu8 < nrReqDataLen_u32); nrInfoTypeChk_qu8++)
                {

                    if((adrReqBuf_pu8[nrInfoTypeChk_qu8] & 0x1Fu)==0u)
                    {

                        nrMultiple_u8++;
                    }

                    adrTmpBuf_au8[nrInfoTypeChk_qu8] = adrReqBuf_pu8[nrInfoTypeChk_qu8];
                }

                if((nrMultiple_u8 == 0) || (nrMultiple_u8 == nrReqDataLen_u32))
                {

                    adrRespBuf_pu8 = pMsgContext->resData;

                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                    if(nrMultiple_u8 != 0)
                    {

                        for(nrInfoTypeChk_qu8 = 0;(nrInfoTypeChk_qu8 < nrReqDataLen_u32);nrInfoTypeChk_qu8++)
                        {

                            idxInfoType_u8 = (uint8)((adrTmpBuf_au8[nrInfoTypeChk_qu8]) / DCM_OBDMODE09_SUPPINFOTYPE);

                            dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].BitMask_u32;

                            if(dataInfoTypeMaskVal_u32 > 0u)
                            {

                                if((pMsgContext->resMaxDataLen - idxInfotypeResBuf_qu16) > 0x4u)
                                {

                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = adrTmpBuf_au8[nrInfoTypeChk_qu8];
                                    idxInfotypeResBuf_qu16++;

                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 24u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 16u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 8u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8) dataInfoTypeMaskVal_u32;
                                    idxInfotypeResBuf_qu16++;

                                    *dataNegRespCode_u8 = 0x0u;
                                    dataRetVal_u8 = E_OK;
                                }
                                else
                                {

                                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

                                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                                    break;
                                }
                            }
                        }

                        pMsgContext->resDataLen = idxInfotypeResBuf_qu16;
                    }
                    else
                    {

                        if(nrReqDataLen_u32 == DCM_OBDMODE09_REQ_LEN)
                        {

                            Dcm_dataDspInfoType_u8 = adrTmpBuf_au8[0];

                            idxInfoType_u8 = (uint8)(Dcm_dataDspInfoType_u8 / DCM_OBDMODE09_SUPPINFOTYPE);

                            dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].BitMask_u32;

                            dataCalInfotypeBitMask_u32 = ((uint32)1u << ((uint32)32u - ((Dcm_dataDspInfoType_u8) % 0x20)));

                            if((dataInfoTypeMaskVal_u32 & dataCalInfotypeBitMask_u32) > 0u)
                            {

                                idxinfoTypeStart_qu8 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].StartIndex_u8;

                                nrInfoTypeMaxLoop_qu8 = idxinfoTypeStart_qu8 +
                                (Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].NumInfotypes_u8);
                                for(nrInfotype_qu8 = idxinfoTypeStart_qu8;
                                        nrInfotype_qu8 < nrInfoTypeMaxLoop_qu8;
                                        nrInfotype_qu8++)
                                {

                                    if(Dcm_dataDspInfoType_u8 == (Dcm_Dsp_VehInfoArray_acs[nrInfotype_qu8].Infotype_u8))
                                    {

                                        Dcm_idxDspInfoType_u8 = (uint8)nrInfotype_qu8;

                                        Dcm_stDspMode09_en = DCM_DSP_MODE09_RUNNING;

                                        Dcm_idxDspVehData_u16 =Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16;

                                        pMsgContext->resData[0]=Dcm_dataDspInfoType_u8;

                                        if(Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].Is_NODI_Enabled_b!= TRUE)
                                        {

                                            pMsgContext->resData[1]=(Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8);

                                            pMsgContext->resDataLen = 2;
                                        }
                                        else
                                        {
                                            pMsgContext->resDataLen = 1;
                                        }
                                        Dcm_stOpStatus_u8 = DCM_INITIAL;

                                        *dataNegRespCode_u8 = 0x0u;

                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {

                            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
                        }
                    }
                }
                else{

                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_MIXED_MODE)
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
            }
        }

        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
        {

            do
            {

                if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen)>=(uint32)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].Infodatatype_size_u8))
                {

                    if((Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf)!=NULL_PTR)
                    {

                        if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen) >= (uint32)255u)
                        {
                            DataValueBufferSize_u8 = (uint8)255u;
                        }
                        else
                        {
                            DataValueBufferSize_u8 = (uint8)(pMsgContext->resMaxDataLen - pMsgContext->resDataLen);
                        }

                            dataInfotypeFnResult_u8 = (*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(Dcm_stOpStatus_u8,&pMsgContext->resData[pMsgContext->resDataLen],&DataValueBufferSize_u8);

                        if( dataInfotypeFnResult_u8 == E_OK)
                        {

                            pMsgContext->resDataLen += (uint32)DataValueBufferSize_u8;

                            Dcm_idxDspVehData_u16++;
                            Dcm_stOpStatus_u8 = DCM_INITIAL;
                        }
                        else if(dataInfotypeFnResult_u8 == DCM_E_PENDING)
                        {

                            if((Dcm_dataDspInfoType_u8 ==0x02)||(Dcm_dataDspInfoType_u8 ==0x04)||(Dcm_dataDspInfoType_u8 ==0x08)||(Dcm_dataDspInfoType_u8 ==0x0A)||(Dcm_dataDspInfoType_u8 ==0x0B))
                            {
#if(DCM_CFG_DSP_OBDMODE9_DEM_SUPP != DCM_CFG_OFF)
                                if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_DEM_FNC)
                                {
                                    Dem_DcmCancelOperation();
                                }
#endif
                                if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
                                {

                                    (void)(*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(DCM_CANCEL,NULL_PTR,NULL_PTR);
                                }

                                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                                DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_PENDING)

                                Dcm_stOpStatus_u8 = DCM_INITIAL;
                            }
                            else
                            {

                                dataRetVal_u8=DCM_E_PENDING;
                                Dcm_stOpStatus_u8 = DCM_PENDING;

                            }
                        }
                        else
                        {

                            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                            Dcm_stOpStatus_u8 = DCM_INITIAL;

                            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_NOT_OK)
                        }
                    }
                }
                else{

                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                    dataInfotypeFnResult_u8 = E_NOT_OK;

                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                }
            }
            while( (Dcm_idxDspVehData_u16< (Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16+Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8)) && (dataInfotypeFnResult_u8==E_OK));

            if(dataInfotypeFnResult_u8 == E_OK)
            {

                Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
                dataRetVal_u8=E_OK;
            }

        }

   	if(*dataNegRespCode_u8 != 0x0u)
   	{
   		 dataRetVal_u8=E_NOT_OK;
   		 Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
   	}
   	else
   	{
   		  if(dataRetVal_u8 != DCM_E_PENDING)
   		  {
   			   dataRetVal_u8=E_OK;
   		  }
   	}
   }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
