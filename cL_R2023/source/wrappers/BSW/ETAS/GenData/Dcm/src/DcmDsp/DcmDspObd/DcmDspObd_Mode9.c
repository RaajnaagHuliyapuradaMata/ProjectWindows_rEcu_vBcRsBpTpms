
#include "Dcm_Cfg_Prot.h"
#include "DcmDspObd_Mode9_Priv.h"
#include "Rte_Dcm.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static uint8 Dcm_dataDspInfoType_u8;
static uint8 Dcm_idxDspInfoType_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
static uint16 Dcm_idxDspVehData_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
static Dcm_DspMode09Type_ten Dcm_stDspMode09_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_DcmObdMode09_Ini(void)
{

    if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
    {
        Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;

        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
        {

           (void)((*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))\
                    (DCM_CANCEL,NULL_PTR,NULL_PTR));
        }
    }
    Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
}

static void Dcm_Lok_Availability09Pid (
        Dcm_ObdMode9ContextType *ModeContext,
        uint8* adrRespBuf_pu8,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint16_least idxInfotypeResBuf_qu16;

    idxInfotypeResBuf_qu16 = 0x0u;

    for(ModeContext->nrInfoTypeChk_qu8 = 0;(ModeContext->nrInfoTypeChk_qu8 < ModeContext->nrReqDataLen_u32);\
    ModeContext->nrInfoTypeChk_qu8++)
    {

        ModeContext->idxInfoType_u8 =
                (uint8)((ModeContext->adrTmpBuf_au8[ModeContext->nrInfoTypeChk_qu8]) / DCM_OBDMODE09_SUPPINFOTYPE);

        ModeContext->dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[ModeContext->idxInfoType_u8].BitMask_u32;

        if(ModeContext->dataInfoTypeMaskVal_u32 > 0u)
        {

            if((pMsgContext->resMaxDataLen - idxInfotypeResBuf_qu16) > 0x4u)
            {

                adrRespBuf_pu8[idxInfotypeResBuf_qu16] = ModeContext->adrTmpBuf_au8[ModeContext->nrInfoTypeChk_qu8];
                idxInfotypeResBuf_qu16++;

                adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(ModeContext->dataInfoTypeMaskVal_u32 >> 24u);
                idxInfotypeResBuf_qu16++;
                adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(ModeContext->dataInfoTypeMaskVal_u32 >> 16u);
                idxInfotypeResBuf_qu16++;
                adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(ModeContext->dataInfoTypeMaskVal_u32 >> 8u);
                idxInfotypeResBuf_qu16++;
                adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8) ModeContext->dataInfoTypeMaskVal_u32;
                idxInfotypeResBuf_qu16++;

                *dataNegRespCode_u8 = 0x0u;
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

static void Dcm_Lok_CheckBitMask (
        Dcm_ObdMode9ContextType ModeContext,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint8_least nrInfoTypeMaxLoop_qu8;
    uint8_least idxinfoTypeStart_qu8;
    uint8_least nrInfotype_qu8;

    idxinfoTypeStart_qu8 = 0x0u;
    nrInfotype_qu8       = 0x0u;

    idxinfoTypeStart_qu8 = Dcm_Dsp_Mode9Bitmask_acs[ModeContext.idxInfoType_u8].StartIndex_u8;

    nrInfoTypeMaxLoop_qu8 = idxinfoTypeStart_qu8+(Dcm_Dsp_Mode9Bitmask_acs[ModeContext.idxInfoType_u8].NumInfotypes_u8);

    for(nrInfotype_qu8 = idxinfoTypeStart_qu8;
        nrInfotype_qu8 < nrInfoTypeMaxLoop_qu8;
        nrInfotype_qu8++)
    {

        if(Dcm_dataDspInfoType_u8 == (Dcm_Dsp_VehInfoArray_acs[nrInfotype_qu8].Infotype_u8))
        {

            Dcm_idxDspInfoType_u8 = (uint8)nrInfotype_qu8;

            Dcm_stDspMode09_en = DCM_DSP_MODE09_RUNNING;

            Dcm_idxDspVehData_u16 = Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16;

            pMsgContext->resData[0] = Dcm_dataDspInfoType_u8;

            if(Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].Is_NODI_Enabled_b != TRUE)
            {

                if((Dcm_dataDspInfoType_u8 >= DCM_OBDMODE09_INFOTYPE16)&&
                  (Dcm_dataDspInfoType_u8 <= DCM_OBDMODE09_INFOTYPE29))
                {

                    pMsgContext->resData[1] = DCM_OBDMODE09_NODIITID16_29;
                }
                else
                {

                    pMsgContext->resData[1] = (Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8);
                }

                    pMsgContext->resDataLen = 2;
            }
            else
            {
                pMsgContext->resDataLen = 1;
            }

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;

            *dataNegRespCode_u8 = 0x0u;

            break;
        }
    }
}

static void Dcm_Lok_ProcessDataOfOneInfotype (
        Dcm_ObdMode9ContextType *ModeContext,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint32 dataCalInfotypeBitMask_u32;

    dataCalInfotypeBitMask_u32 = 0x0u;

    if(ModeContext->nrReqDataLen_u32 == DCM_OBDMODE09_REQ_LEN)
    {

        Dcm_dataDspInfoType_u8 = ModeContext->adrTmpBuf_au8[0];

        ModeContext->idxInfoType_u8 = (uint8)(Dcm_dataDspInfoType_u8 / DCM_OBDMODE09_SUPPINFOTYPE);

        ModeContext->dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[ModeContext->idxInfoType_u8].BitMask_u32;

        dataCalInfotypeBitMask_u32 = ((uint32)1u << ((uint32)32u - ((Dcm_dataDspInfoType_u8) % 0x20)));

        if((ModeContext->dataInfoTypeMaskVal_u32 & dataCalInfotypeBitMask_u32) > 0u)
        {
            Dcm_Lok_CheckBitMask(*ModeContext,
                                  pMsgContext,
                                  dataNegRespCode_u8);
        }
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
    }
}

static Dcm_NegativeResponseCodeType Dcm_Lok_Mode09Init (
        Dcm_ObdMode9ContextType *ModeContext,
        Dcm_MsgContextType *pMsgContext,
        Dcm_NegativeResponseCodeType *dataNegRespCode_u8)
{
    uint8* adrRespBuf_pu8;
    uint8* adrReqBuf_pu8;
    uint8  nrMultiple_u8;

    nrMultiple_u8 = 0x0u;

    if((ModeContext->nrReqDataLen_u32 > DCM_OBDMODE09_REQ_LEN_MIN) &&
       (ModeContext->nrReqDataLen_u32 < DCM_OBDMODE09_REQ_LEN_MAX))
    {

        adrReqBuf_pu8 = pMsgContext->reqData;

        for(ModeContext->nrInfoTypeChk_qu8 = 0; (ModeContext->nrInfoTypeChk_qu8 < ModeContext->nrReqDataLen_u32); \
        ModeContext->nrInfoTypeChk_qu8++)
        {

            if((adrReqBuf_pu8[ModeContext->nrInfoTypeChk_qu8] & 0x1Fu) == 0u)
            {

                nrMultiple_u8++;
            }

            ModeContext->adrTmpBuf_au8[ModeContext->nrInfoTypeChk_qu8] = adrReqBuf_pu8[ModeContext->nrInfoTypeChk_qu8];
        }

        if((nrMultiple_u8 == 0) || (nrMultiple_u8 == ModeContext->nrReqDataLen_u32))
        {

            adrRespBuf_pu8 = pMsgContext->resData;

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            if(nrMultiple_u8 != 0)
            {
                Dcm_Lok_Availability09Pid (ModeContext,
                                           adrRespBuf_pu8,
                                           pMsgContext,
                                           dataNegRespCode_u8);
            }
            else
            {
                Dcm_Lok_ProcessDataOfOneInfotype (ModeContext,
                                                  pMsgContext,
                                                  dataNegRespCode_u8);
            }
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_MIXED_MODE)
        }
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
    }
    return(*dataNegRespCode_u8);
}

static Std_ReturnType Dcm_Lok_Mode09Pending (
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType dataRetVal_u8;

    dataRetVal_u8 = E_OK;

    if(Dcm_dataDspInfoType_u8 == 0x06)
    {

        dataRetVal_u8      = DCM_E_PENDING;
        Dcm_SrvOpstatus_u8 = DCM_PENDING;
    }
    else
    {
        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
        {

            (void)(*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))
                    (DCM_CANCEL,NULL_PTR,NULL_PTR);
        }

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_PENDING)

        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    }

    return (dataRetVal_u8);
}

static Std_ReturnType Dcm_Lok_GetVehInfoData (
        Dcm_ObdMode9ContextType *ModeContext,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint8          DataValueBufferSize_u8;
    Std_ReturnType dataRetVal_u8;

    dataRetVal_u8 = E_OK;

    if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen) >= (uint32)255u)
    {
        DataValueBufferSize_u8 = (uint8)255u;
    }
    else
    {
        DataValueBufferSize_u8 = (uint8)(pMsgContext->resMaxDataLen - pMsgContext->resDataLen);
    }

    ModeContext->dataInfotypeFnResult_u8 =
            (*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))
            (Dcm_SrvOpstatus_u8,&pMsgContext->resData[pMsgContext->resDataLen],&DataValueBufferSize_u8);

    if( ModeContext->dataInfotypeFnResult_u8 == E_OK)
    {

        pMsgContext->resDataLen += (uint32)DataValueBufferSize_u8;

        Dcm_idxDspVehData_u16++;
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    }
    else if(ModeContext->dataInfotypeFnResult_u8 == DCM_E_PENDING)
    {
        dataRetVal_u8 = Dcm_Lok_Mode09Pending(dataNegRespCode_u8);
    }
    else
    {
        dataRetVal_u8 = E_NOT_OK;

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        Dcm_SrvOpstatus_u8 = DCM_INITIAL;

        DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_NOT_OK)
    }
    return(dataRetVal_u8);
}

static Std_ReturnType Dcm_Lok_Mode09Running (
        Dcm_ObdMode9ContextType *ModeContext,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType dataReturnVal_u8 = E_NOT_OK;

    do
    {

        if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen) >=
                (uint32)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].Infodatatype_size_u8))
        {

            if((Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf) != NULL_PTR)
            {
                dataReturnVal_u8 = Dcm_Lok_GetVehInfoData (ModeContext,
                                                           pMsgContext,
                                                           dataNegRespCode_u8);
            }
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            ModeContext->dataInfotypeFnResult_u8 = E_NOT_OK;

            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
        }
    }

    while ((Dcm_idxDspVehData_u16 <
            (Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16+ \
                    Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8)) && \
            (ModeContext->dataInfotypeFnResult_u8==E_OK));

    if(ModeContext->dataInfotypeFnResult_u8 == E_OK)
    {

        Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
        dataReturnVal_u8   = E_OK;
    }

    return(dataReturnVal_u8);
}

Std_ReturnType Dcm_DcmObdMode09 (
        Dcm_SrvOpStatusType OpStatus,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType          dataRetVal_u8;
    Dcm_ObdMode9ContextType ModeContext;

    *dataNegRespCode_u8                 = 0x0u;
    ModeContext.adrTmpBuf_au8[0]        = 0x0u;
    ModeContext.nrReqDataLen_u32        = (pMsgContext->reqDataLen);
    ModeContext.dataInfotypeFnResult_u8 = E_NOT_OK;
    dataRetVal_u8                       = E_OK;

    if (OpStatus == DCM_CANCEL)
    {
        Dcm_DcmObdMode09_Ini();
    }
    else
    {
        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_INIT)
        {
            *dataNegRespCode_u8 = Dcm_Lok_Mode09Init (&ModeContext,
                                                      pMsgContext,
                                                      dataNegRespCode_u8);
        }

        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
        {
            dataRetVal_u8 = Dcm_Lok_Mode09Running (&ModeContext,
                                                   pMsgContext,
                                                   dataNegRespCode_u8);
        }

        if(*dataNegRespCode_u8 != 0x0u)
        {
            dataRetVal_u8      = E_NOT_OK;
            Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
        }
    }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif
