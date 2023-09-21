#include "Std_Types.hpp"

#include "DcmDspObd_Mode1_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode1_Priv.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode01 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8;
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8;
#if(DCM_CFG_DSP_OBDMODE1_SINT32_SR_ENABLED != DCM_CFG_OFF)
   VAR(sint32,     AUTOMATIC) dataSignal_s32;
#endif
   VAR(uint32,     AUTOMATIC) dataPIDMaskVal_u32;
   VAR(uint32,     AUTOMATIC) dataCalPIDBitMask_u32;
   VAR(uint32,     AUTOMATIC) dataPidRunTimeMask_u32;
   VAR(Dcm_MsgLenType, AUTOMATIC) nrResMaxDataLen_u32;
   VAR(Dcm_MsgLenType, AUTOMATIC) nrReqDataLen_u32;
   VAR(uint16_least,   AUTOMATIC) idxPIDRes_qu16;
   VAR(uint16,     AUTOMATIC) idxSupportInfo_u16;
   VAR(uint16,     AUTOMATIC) idxDataSource_u16;
#if(DCM_CFG_DSP_OBDMODE1_UINT16_SR_ENABLED != DCM_CFG_OFF)
   VAR(uint16,     AUTOMATIC) dataSignal_u16;
#endif
#if(DCM_CFG_DSP_OBDMODE1_SR_ENABLED != DCM_CFG_OFF)
   VAR(uint16,     AUTOMATIC) nrElements_u16;
   VAR(uint32,     AUTOMATIC) dataSignal_u32;
   VAR(uint16,     AUTOMATIC) idxLoop_u16;
#endif
   VAR(uint16,     AUTOMATIC) posnPidData_u16;
#if(DCM_CFG_DSP_OBDMODE1_SINT16_SR_ENABLED != DCM_CFG_OFF)
   VAR(sint16,     AUTOMATIC) dataSignal_s16;
#endif
   VAR(uint8_least,    AUTOMATIC) nrPid_qu8;
   VAR(uint8_least,    AUTOMATIC) idxPIDStart_qu8;
   VAR(uint8_least,    AUTOMATIC) idxPIDData_qu8;
   VAR(uint8_least,    AUTOMATIC) nrPIDChk_qu8;
   VAR(uint8,     AUTOMATIC) adrTmpBuf_au8[DCM_OBDMODE01_REQ_LEN_MAX];
   VAR(uint8,     AUTOMATIC) idxPID_u8;
   VAR(uint8,     AUTOMATIC) nrMultiple_u8;
   VAR(uint8,     AUTOMATIC) dataSupportInfoByte_u8;
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
   VAR(uint8,     AUTOMATIC) idxPidMaskDet_u8;
#endif
   VAR(Std_ReturnType, AUTOMATIC) dataGetPIDRetVal_u8;
   VAR(Std_ReturnType, AUTOMATIC) dataReturnValue_u8;
   VAR(boolean,AUTOMATIC) stPIDFound_b;
#if(DCM_CFG_DSP_OBDMODE1_UINT8_SR_ENABLED != DCM_CFG_OFF)
   VAR(uint8,     AUTOMATIC)   dataSignal_u8;
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT8_SR_ENABLED != DCM_CFG_OFF)
   VAR(sint8,     AUTOMATIC)   dataSignal_s8;
#endif
#if(DCM_CFG_DSP_OBDMODE1_BOOL_SR_ENABLED != DCM_CFG_OFF)
   VAR(boolean,     AUTOMATIC)   dataSignal_b;
#endif
   VAR(boolean,AUTOMATIC) stInfrastructureError_b;

#if(DCM_CFG_DSP_OBDMODE1_SINT32_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s32 = 0x0;
#endif
#if(DCM_CFG_DSP_OBDMODE1_UINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u16 = 0x0u;
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s16 = 0x0;
#endif
#if(DCM_CFG_DSP_OBDMODE1_UINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u8  = 0x0u;
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s8  = 0x0;
#endif
#if(DCM_CFG_DSP_OBDMODE1_BOOL_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_b   = FALSE;
#endif
#if(DCM_CFG_DSP_OBDMODE1_SR_ENABLED != DCM_CFG_OFF)
    nrElements_u16 = 0x0u;
    dataSignal_u32 = 0x0u;
   idxLoop_u16  = 0x0u;
#endif

    *dataNegRespCode_u8       = 0x00u;
    dataGetPIDRetVal_u8     = E_OK;
   idxPIDRes_qu16   = 0x00u;
    nrPid_qu8    = 0x00u;
   idxPIDStart_qu8    = 0x00u;
   idxPIDData_qu8     = 0x00u;
    dataCalPIDBitMask_u32 = 0x00u;
    adrTmpBuf_au8[0]    = 0x00u;

   stPIDFound_b      = FALSE;
    nrMultiple_u8     = 0x00u;

   stInfrastructureError_b = FALSE;
    dataReturnValue_u8=E_NOT_OK;

    nrReqDataLen_u32 = (pMsgContext->reqDataLen);

    DCM_UNUSED_PARAM(OpStatus);

   if((nrReqDataLen_u32 > DCM_OBDMODE01_REQ_LEN_MIN) && (nrReqDataLen_u32 < DCM_OBDMODE01_REQ_LEN_MAX))
   {

        adrReqBuf_pu8 = pMsgContext->reqData;

        for(nrPIDChk_qu8=0;(nrPIDChk_qu8 < nrReqDataLen_u32);nrPIDChk_qu8++)
        {

            if((adrReqBuf_pu8[nrPIDChk_qu8] & 0x1Fu)== 0u)
            {

                nrMultiple_u8++;
            }

            adrTmpBuf_au8[nrPIDChk_qu8] = adrReqBuf_pu8[nrPIDChk_qu8];
        }

        if((nrMultiple_u8 == 0u) || (nrMultiple_u8 == nrReqDataLen_u32 ))
        {

            adrRespBuf_pu8 = pMsgContext->resData;

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

            for(nrPIDChk_qu8 = 0;(nrPIDChk_qu8 < nrReqDataLen_u32);nrPIDChk_qu8++)
            {
                dataPidRunTimeMask_u32 = 0x0;

                idxPID_u8 = (uint8)((adrTmpBuf_au8[nrPIDChk_qu8]) / DCM_OBDMODE01_SUPPPID);

                dataPIDMaskVal_u32 = Dcm_Dsp_Mode1Bitmask_acs[idxPID_u8].BitMask_u32;

                if(nrMultiple_u8 != 0)
                {

                    if(nrResMaxDataLen_u32>=0x05u)
                    {

                        if(dataPIDMaskVal_u32 > 0u)
                        {

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

                            for(idxPidMaskDet_u8=0;idxPidMaskDet_u8<(Dcm_Dsp_Mode1Bitmask_acs[idxPID_u8].NumPids_u8);idxPidMaskDet_u8++)
                            {

                                if((Dcm_ActiveConfiguration_u8 & Dcm_Dsp_Mode1PidArray_acs[idxPidMaskDet_u8].Config_Mask)!= 0)
                                {

                                    dataPidRunTimeMask_u32=(dataPidRunTimeMask_u32 | (1 << (32-Dcm_Dsp_Mode1PidArray_acs[idxPidMaskDet_u8].Pid_Id_u8)));
                                }
                            }
#else
                            dataPidRunTimeMask_u32=dataPIDMaskVal_u32;
#endif

                            if(dataPidRunTimeMask_u32 > 0u)
                            {

                                adrRespBuf_pu8[idxPIDRes_qu16] = adrTmpBuf_au8[nrPIDChk_qu8];
                                idxPIDRes_qu16++;

                                adrRespBuf_pu8[idxPIDRes_qu16] = (uint8)(dataPidRunTimeMask_u32 >> 24u);
                                idxPIDRes_qu16++;
                                adrRespBuf_pu8[idxPIDRes_qu16] = (uint8)(dataPidRunTimeMask_u32 >> 16u);
                                idxPIDRes_qu16++;
                                adrRespBuf_pu8[idxPIDRes_qu16] = (uint8)(dataPidRunTimeMask_u32 >> 8u);
                                idxPIDRes_qu16++;
                                adrRespBuf_pu8[idxPIDRes_qu16] = (uint8) dataPidRunTimeMask_u32;
                                idxPIDRes_qu16++;

                                *dataNegRespCode_u8 = 0x0u;

                                nrResMaxDataLen_u32 = nrResMaxDataLen_u32-0x05uL;
                            }
                        }
                    }
                    else
                    {

                        DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

                        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                        break;
                    }
                }
                else{

                    dataCalPIDBitMask_u32 = ((uint32)1u << ((uint32)32u - ((adrTmpBuf_au8[nrPIDChk_qu8]) % 0x20)));

                    if((dataPIDMaskVal_u32 & dataCalPIDBitMask_u32) > 0u)
                    {

                        idxPIDStart_qu8 = Dcm_Dsp_Mode1Bitmask_acs[idxPID_u8].StartIndex_u8;

                        stPIDFound_b = FALSE;

                        dataGetPIDRetVal_u8 = E_OK;

                        for(nrPid_qu8 = idxPIDStart_qu8; ((nrPid_qu8 <(idxPIDStart_qu8 +(Dcm_Dsp_Mode1Bitmask_acs[idxPID_u8].NumPids_u8))) && (stPIDFound_b == FALSE)); nrPid_qu8++)
                        {
                            if( adrTmpBuf_au8[nrPIDChk_qu8] == (Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Pid_Id_u8))
                            {
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
                                if((Dcm_ActiveConfiguration_u8 & Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Config_Mask)!= 0)
#endif
                                {

                                    stPIDFound_b = TRUE;
                                    if(nrResMaxDataLen_u32>=(uint32)(Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Pid_Size_u8+1))
                                    {

                                        idxPIDData_qu8 = Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].DataSourcePid_ArrayIndex_u16;

                                        for(idxDataSource_u16 = (uint16)idxPIDRes_qu16;
                                            idxDataSource_u16 <(idxPIDRes_qu16 + Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Pid_Size_u8+1u);
                                            idxDataSource_u16++)
                                        {
                                            adrRespBuf_pu8[idxDataSource_u16] = 0x0;
                                        }

                                        for(idxDataSource_u16= (uint16)idxPIDData_qu8;
                                            ((idxDataSource_u16<(idxPIDData_qu8+Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Num_DataSourcePids_u8))&&(dataGetPIDRetVal_u8 == E_OK));
                                            idxDataSource_u16++)
                                        {

                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf!=NULL_PTR)
                                            {

                                                if((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].PidUsePort == OBD_USE_DATA_SYNCH_FNC)||
                                                   (Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].PidUsePort == OBD_USE_DATA_SYNCH_CLIENT_SERVER))
                                                {

                                                    posnPidData_u16=(uint16)(idxPIDRes_qu16+(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16/(uint16)8)+(uint16)1);

                                                    dataGetPIDRetVal_u8 = (*(GetPIDvalue1_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))
                                                                                       (&adrRespBuf_pu8[posnPidData_u16]);

                                                }
                                                else
                                                {
#if(DCM_CFG_DSP_OBDMODE1_SR_ENABLED != DCM_CFG_OFF)

                                                    if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].PidUsePort == OBD_USE_DATA_SENDER_RECEIVER)
                                                    {

                                                        if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_UINT8)
                                                        {
#if(DCM_CFG_DSP_OBDMODE1_UINT8_SR_ENABLED != DCM_CFG_OFF)
                                                            nrElements_u16 = (uint16)((uint32)Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/8u);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 8u)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue1_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_u8);
                                                                Dcm_DspArraySignal_au8[0] = dataSignal_u8;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue1_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_au8);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = (uint32)Dcm_DspArraySignal_au8[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*8u))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
#endif
                                                        }
#if(DCM_CFG_DSP_OBDMODE1_UINT16_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_UINT16)
                                                        {
                                                            nrElements_u16 = (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/16);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 16)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue2_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_u16);
                                                                Dcm_DspArraySignal_au16[0] = dataSignal_u16;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue2_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_au16);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = (uint32)Dcm_DspArraySignal_au16[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*16u)))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
                                                        }
#endif
#if(DCM_CFG_DSP_OBDMODE1_UINT32_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_UINT32)
                                                        {
                                                            nrElements_u16 = (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/32u);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 32u)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue3_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_u32);
                                                                Dcm_DspArraySignal_au32[0] = dataSignal_u32;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue3_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_au32);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = Dcm_DspArraySignal_au32[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*32u)))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
                                                        }
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT8_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_SINT8)
                                                        {
                                                            nrElements_u16 = (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/8u);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 8u)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue4_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_s8);
                                                                Dcm_DspArraySignal_as8[0] = dataSignal_s8;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue4_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_as8);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = (uint32)Dcm_DspArraySignal_as8[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*8u)))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
                                                        }
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT16_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_SINT16)
                                                        {
                                                            nrElements_u16 = (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/16u);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 16u)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue5_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_s16);
                                                                Dcm_DspArraySignal_as16[0] = dataSignal_s16;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue5_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_as16);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = (uint32)Dcm_DspArraySignal_as16[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*16u)))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
                                                        }
#endif
#if(DCM_CFG_DSP_OBDMODE1_SINT32_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_SINT32)
                                                        {
                                                            nrElements_u16 = (uint16)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16/32u);

                                                            if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Length_data_u16 == 32u)
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue6_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_s32);
                                                                Dcm_DspArraySignal_as32[0] = dataSignal_s32;
                                                            }
                                                            else
                                                            {

                                                                dataGetPIDRetVal_u8 = (*(GetPIDvalue6_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(Dcm_DspArraySignal_as32);
                                                            }

                                                            for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(dataGetPIDRetVal_u8 == E_OK)); idxLoop_u16++)
                                                            {
                                                                dataSignal_u32 = (uint32)Dcm_DspArraySignal_as32[idxLoop_u16];

                                                                Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16+(uint16)(idxLoop_u16*32u)))
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                            }
                                                        }
#endif
#if(DCM_CFG_DSP_OBDMODE1_BOOL_SR_ENABLED != DCM_CFG_OFF)

                                                        else if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8 == DCM_BOOLEAN)
                                                        {

                                                            dataGetPIDRetVal_u8 = (*(GetPIDvalue7_pf)(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].GetPIDvalue_pf))(&dataSignal_b);
                                                            dataSignal_u32 = 0x0u;

                                                            if(FALSE != dataSignal_b)
                                                            {
                                                                dataSignal_u32 = (uint32)0x01;
                                                            }

                                                            Dcm_StoreSignal(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataType_u8
   ,     (Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].Pos_data_u16)
   ,     &adrRespBuf_pu8[idxPIDRes_qu16 + 1u], dataSignal_u32
   ,     Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].dataEndianness_u8);
                                                        }
#endif
                                                        else
                                                        {

                                                        }
                                                    }
#endif
                                                }

                                                if((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].PidUsePort == OBD_USE_DATA_SYNCH_CLIENT_SERVER) || (Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].PidUsePort == OBD_USE_DATA_SENDER_RECEIVER))
                                                {
                                                    if(Dcm_IsInfrastructureErrorPresent_b(dataGetPIDRetVal_u8) != FALSE)
                                                    {

                                                        stInfrastructureError_b = TRUE;
                                                    }
                                                }
                                            }
                                        }

                                        if(dataGetPIDRetVal_u8==E_OK)
                                        {

                                            adrRespBuf_pu8[idxPIDRes_qu16] = adrTmpBuf_au8[nrPIDChk_qu8];

                                            idxPIDRes_qu16++;

                                            for(idxDataSource_u16=(uint16)idxPIDData_qu8;idxDataSource_u16<(idxPIDData_qu8+Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Num_DataSourcePids_u8);idxDataSource_u16++)
                                            {

                                                if(Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].ptr_supportinfo_pcs!=NULL_PTR)
                                                {

                                                    dataSupportInfoByte_u8 = (uint8)(0x01u<< ((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].SupportInfoBit_u8)%8u));

                                                    idxSupportInfo_u16 = (uint16)(idxPIDRes_qu16 +
                                                            Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].ptr_supportinfo_pcs->SupportInfoPos_u8 +
                                                                           (uint16)((Dcm_Dsp_Mode1DataSourcePid_acs[idxDataSource_u16].SupportInfoBit_u8)/8u));

                                                    adrRespBuf_pu8[idxSupportInfo_u16]= (adrRespBuf_pu8[idxSupportInfo_u16] | dataSupportInfoByte_u8);
                                                }
                                            }

                                            idxPIDRes_qu16 = (idxPIDRes_qu16 +(uint16)Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Pid_Size_u8);

                                            nrResMaxDataLen_u32 = (Dcm_MsgLenType) (nrResMaxDataLen_u32 - (1u + (Dcm_MsgLenType)Dcm_Dsp_Mode1PidArray_acs[nrPid_qu8].Pid_Size_u8));

                                            *dataNegRespCode_u8   = 0x0u;
                                        }

                                        else if(stInfrastructureError_b!=FALSE)
                                        {

                                            DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_RET_E_INFRASTRUCTURE_ERROR)

                                            stInfrastructureError_b=FALSE;
                                        }

                                        else
                                        {

                                            DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_RET_E_NOT_OK)
                                        }
                                    }
                                    else
                                    {

                                        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                                        DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

                                         nrReqDataLen_u32=nrPIDChk_qu8;

                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            pMsgContext->resDataLen = idxPIDRes_qu16;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_MIXED_MODE)
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        DCM_DET_ERROR(DCM_OBDMODE01_ID, DCM_E_INVALID_LENGTH)
   }

   if(*dataNegRespCode_u8 != 0)
   {
        dataReturnValue_u8=E_NOT_OK;
   }
   else{
        dataReturnValue_u8=E_OK;
   }

    return dataReturnValue_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

