
#include "DcmDspObd_Mode2_Priv.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static void Dcm_Lok_ReadDataOfOBDFreezeFrame (
        Dcm_ObdContextType *ModeContext,
        const uint8 adrTmpBuf_au8[],
        uint8* adrRespBuf_pu8,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint16      idxDataSource_u16;
    uint16      nrBufSize_u16;
    uint8_least idxPIDData_qu8;

    idxPIDData_qu8    = 0x00;

    idxPIDData_qu8 = Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].DataSourcePid_ArrayIndex_u16;

    for(idxDataSource_u16=(uint16)(ModeContext->nrResDataLen_u32+2uL);
            idxDataSource_u16<(ModeContext->nrResDataLen_u32+Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Pid_Size_u8+2u);
            idxDataSource_u16++)
    {
        adrRespBuf_pu8[idxDataSource_u16] = 0x00;
    }

    for(idxDataSource_u16 = (uint16)idxPIDData_qu8;
            ((idxDataSource_u16<(idxPIDData_qu8+Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Num_DataSourcePids_u8)) && (ModeContext->dataRetGet_u8 == E_OK));
            idxDataSource_u16++)
    {

        nrBufSize_u16 = (uint8)Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8;

        ModeContext->dataRetGet_u8 =
                Dem_DcmReadDataOfOBDFreezeFrame(adrTmpBuf_au8[ModeContext->nrPIDChk_qu8],
                (uint8)(idxDataSource_u16-idxPIDData_qu8),
                &adrRespBuf_pu8[ModeContext->nrResDataLen_u32 +Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Pos_data_u8+2u],
                &nrBufSize_u16);

        if(ModeContext->dataRetGet_u8 == E_OK)
        {

            if(nrBufSize_u16 > Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8)
            {

                ModeContext->dataRetGet_u8 = E_NOT_OK;
            }
        }
    }
    if(ModeContext->dataRetGet_u8 == E_OK)
    {

        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = adrTmpBuf_au8[ModeContext->nrPIDChk_qu8];
        ModeContext->nrResDataLen_u32++;

        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = 0x00;
        ModeContext->nrResDataLen_u32++;

        ModeContext->nrResDataLen_u32 =
                ModeContext->nrResDataLen_u32 + Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Pid_Size_u8;

        ModeContext->nrResMaxDataLen_u32 =
                ModeContext->nrResMaxDataLen_u32 - (2uL + (Dcm_MsgLenType)Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Pid_Size_u8);

        *dataNegRespCode_u8 = 0u;
    }
    else
    {

    }
}

static void Dcm_Lok_specialPid02 (
        Dcm_ObdContextType *ModeContext,
        uint8* adrRespBuf_pu8,
        const uint8 adrTmpBuf_au8[],
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    if(ModeContext->nrResMaxDataLen_u32 >= 0x04uL)
    {

        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = adrTmpBuf_au8[ModeContext->nrPIDChk_qu8];
        ModeContext->nrResDataLen_u32++;

        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = 0x00;
        ModeContext->nrResDataLen_u32++;

        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8)(ModeContext->nrDTC_u32 >> 16u);
        ModeContext->nrResDataLen_u32++;
        adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8)(ModeContext->nrDTC_u32 >> 8u);
        ModeContext->nrResDataLen_u32++;

        ModeContext->nrResMaxDataLen_u32 = ModeContext->nrResMaxDataLen_u32 - 0x04uL;

        *dataNegRespCode_u8 = 0u;
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        ModeContext->nrPIDValid_qu8 = ModeContext->nrPIDChk_qu8;
    }
}

static void Dcm_Lok_OtherPid (
        Dcm_ObdContextType *ModeContext,
        uint8* adrRespBuf_pu8,
        const uint8 adrTmpBuf_au8[],
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

    if((ModeContext->nrDTC_u32 & 0xFFFF00uL) > 0uL)
    {

        ModeContext->idxPIDStart_qu8 = Dcm_Dsp_Mode2Bitmask_acs[ModeContext->idxPID_u8].StartIndex_u8;

        ModeContext->isPIDFound_b  = FALSE;
        ModeContext->dataRetGet_u8 = E_OK;

        for(ModeContext->nrPid_u8 = ModeContext->idxPIDStart_qu8;
                ((ModeContext->nrPid_u8 <(ModeContext->idxPIDStart_qu8 +(Dcm_Dsp_Mode2Bitmask_acs[ModeContext->idxPID_u8].NumPids_u8))) && (ModeContext->isPIDFound_b == FALSE));
                ModeContext->nrPid_u8++)
        {

            if(adrTmpBuf_au8[ModeContext->nrPIDChk_qu8] == (Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Pid_Id_u8))
            {

                ModeContext->isPIDFound_b = TRUE;

                if(ModeContext->nrResMaxDataLen_u32 >=
                        (uint32)(Dcm_Dsp_Mode2PidArray_acs[ModeContext->nrPid_u8].Pid_Size_u8+2))
                {
                    Dcm_Lok_ReadDataOfOBDFreezeFrame(ModeContext,
                                                     adrTmpBuf_au8,
                                                     adrRespBuf_pu8,
                                                     dataNegRespCode_u8);
                }
                else
                {

                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                    ModeContext->nrPIDValid_qu8 = ModeContext->nrPIDChk_qu8;
                    break;
                }
            }
        }
    }
}

static void Dcm_Lok_AvailabiltyPid (
        Dcm_ObdContextType *ModeContext,
        uint8* adrRespBuf_pu8,
        const uint8 adrTmpBuf_au8[],
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    if(ModeContext->dataPIDBitMask_u32 > 0u)
    {

        if(ModeContext->nrResMaxDataLen_u32 >= 0x06uL)
        {

            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = adrTmpBuf_au8[ModeContext->nrPIDChk_qu8];
            ModeContext->nrResDataLen_u32++;

            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = 0x00;
            ModeContext->nrResDataLen_u32++;

            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8)(ModeContext->dataPIDBitMask_u32 >> 24u);
            ModeContext->nrResDataLen_u32++;
            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8)(ModeContext->dataPIDBitMask_u32 >> 16u);
            ModeContext->nrResDataLen_u32++;
            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8)(ModeContext->dataPIDBitMask_u32 >> 8u);
            ModeContext->nrResDataLen_u32++;
            adrRespBuf_pu8[ModeContext->nrResDataLen_u32] = (uint8) ModeContext->dataPIDBitMask_u32;
            ModeContext->nrResDataLen_u32++;

            ModeContext->nrResMaxDataLen_u32 = ModeContext->nrResMaxDataLen_u32 - 0x06uL;

            *dataNegRespCode_u8 = 0x0u;
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
}

static void Dcm_Lok_NonAvailabiltyPid (
        Dcm_ObdContextType *ModeContext,
        uint8* adrRespBuf_pu8,
        const uint8 adrTmpBuf_au8[],
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

     ModeContext->dataCalBitMask_u32 =
             ((uint32)1u << ((uint32)32u -((adrTmpBuf_au8[ModeContext->nrPIDChk_qu8]) % 0x20)));

    if((ModeContext->dataPIDBitMask_u32 & ModeContext->dataCalBitMask_u32)> 0uL)
    {

        if((DCM_DSPMODE02_PID02 == adrTmpBuf_au8[ModeContext->nrPIDChk_qu8])||
           (ModeContext->flgGetDTCNum_b != FALSE))
        {

            ModeContext->flgGetDTCNum_b = FALSE;

            if(Dem_DcmGetDTCOfOBDFreezeFrame(0x00, &ModeContext->nrDTC_u32, DEM_DTC_FORMAT_OBD) != E_OK)
            {
                ModeContext->nrDTC_u32 = 0x00;
            }
        }

        if(DCM_DSPMODE02_PID02 == adrTmpBuf_au8[ModeContext->nrPIDChk_qu8])
        {
            Dcm_Lok_specialPid02(ModeContext,
                                 adrRespBuf_pu8,
                                 adrTmpBuf_au8,
                                 dataNegRespCode_u8);
        }
        else
        {
            Dcm_Lok_OtherPid(ModeContext,
                             adrRespBuf_pu8,
                             adrTmpBuf_au8,
                             dataNegRespCode_u8);
        }
    }
}

Std_ReturnType Dcm_DcmObdMode02 (
        Dcm_SrvOpStatusType OpStatus,
        Dcm_MsgContextType* pMsgContext,
        Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    uint8*             adrRespBuf_pu8;
    uint8*             adrReqBuf_pu8;
    Dcm_MsgLenType     nrReqDataLen_u32;
    uint8              adrTmpBuf_au8[3];
    Std_ReturnType     dataRetVal_u8;
    Dcm_ObdContextType ModeContext;

    *dataNegRespCode_u8          = 0x0u;
    ModeContext.nrDTC_u32        = 0x00;
    adrTmpBuf_au8[0]             = 0x00;
    nrReqDataLen_u32             = (pMsgContext->reqDataLen);
    ModeContext.nrPIDValid_qu8   = 0x00;
    ModeContext.nrResDataLen_u32 = 0x00;
    ModeContext.nrMultiple_u8    = 0x00;

    ModeContext.flgGetDTCNum_b  = TRUE;
    ModeContext.idxPIDStart_qu8 = 0x00;
    ModeContext.nrPid_u8        = 0x00;

    ModeContext.isPIDFound_b = FALSE;
    dataRetVal_u8            = E_NOT_OK;

    DCM_UNUSED_PARAM(OpStatus);

    if((nrReqDataLen_u32 == 0x02uL)||
       (nrReqDataLen_u32 == 0x04uL)||
       (nrReqDataLen_u32 == 0x06uL))
    {

        adrReqBuf_pu8 = pMsgContext->reqData;

        for(ModeContext.nrPIDChk_qu8 = 0;(ModeContext.nrPIDChk_qu8 < nrReqDataLen_u32);ModeContext.nrPIDChk_qu8 += 2u)
        {

            if((adrReqBuf_pu8[ModeContext.nrPIDChk_qu8] & 0x1Fu) == 0u)
            {

                ModeContext.nrMultiple_u8++;
            }

            if((adrReqBuf_pu8[ModeContext.nrPIDChk_qu8 + 1u]) == 0x00u)
            {

                adrTmpBuf_au8[ModeContext.nrPIDValid_qu8] = adrReqBuf_pu8[ModeContext.nrPIDChk_qu8];

                ModeContext.nrPIDValid_qu8++;
            }

        }

        if((ModeContext.nrMultiple_u8 == 0u) ||
           (ModeContext.nrMultiple_u8 == (uint8)(nrReqDataLen_u32 >> 1u)))
        {

            adrRespBuf_pu8 = pMsgContext->resData;

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            ModeContext.nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

            for(ModeContext.nrPIDChk_qu8 = 0;(ModeContext.nrPIDChk_qu8 < ModeContext.nrPIDValid_qu8);
                    ModeContext.nrPIDChk_qu8++)
            {

                ModeContext.idxPID_u8 = (uint8)((adrTmpBuf_au8[ModeContext.nrPIDChk_qu8]) / DCM_OBDMODE02_SUPPPID);

                ModeContext.dataPIDBitMask_u32 = Dcm_Dsp_Mode2Bitmask_acs[ModeContext.idxPID_u8].BitMask_u32;

                if(ModeContext.nrMultiple_u8 != 0)
                {
                    Dcm_Lok_AvailabiltyPid(&ModeContext,
                                           adrRespBuf_pu8,
                                           adrTmpBuf_au8,
                                           dataNegRespCode_u8);
                }

                else
                {
                    Dcm_Lok_NonAvailabiltyPid (&ModeContext,
                                               adrRespBuf_pu8,
                                               adrTmpBuf_au8,
                                               dataNegRespCode_u8);
                }
            }

            pMsgContext->resDataLen = ModeContext.nrResDataLen_u32;
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }

    dataRetVal_u8 = (*dataNegRespCode_u8 != 0x0u) ? E_NOT_OK : E_OK;

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

