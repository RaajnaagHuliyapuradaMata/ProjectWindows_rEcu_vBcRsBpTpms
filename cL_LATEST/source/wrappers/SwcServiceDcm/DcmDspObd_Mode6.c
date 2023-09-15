

#include "DcmDspObd_Mode6_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE6_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType Dcm_DcmObdMode06(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{

    Dcm_MsgType adrResData_pu8;
    Dcm_MsgType adrReqData_pu8;
    Dcm_MsgLenType nrResDataLen_u32;
    Dcm_MsgLenType nrReqDataLen_u32;
   uint32 dataBitMask_u32;
   uint16 dataTestVal_u16;
   uint16 dataMinLimit_u16;
   uint16 dataMaxLimit_u16;
   uint8_least idxReq_qu32;
   uint8_least idxObdMid_qu32;
    Std_ReturnType dataReturnValue_u8;
   uint8 adrTempBuffer_au8[8];
   boolean flgSplObdMid_b;
#if(DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_ON)
   uint16_least idxTid_qu32;
   uint16 idxTidarrayLimit_u16;
   uint8 stStatus_u8;
   uint8 nrRange_u8;
   uint8 dataMidArrayLimit_u8;
#elif(DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_OFF)
   uint8 Tid_Id_u8;
   uint8 idxTid_u8;
   uint8 UnitScale_u8;
   uint8 numberOfTIDs_u8;
   uint8 ObmidValue;
#endif

    adrResData_pu8       = pMsgContext->resData;
    adrReqData_pu8       = pMsgContext->reqData;
    nrReqDataLen_u32    = pMsgContext->reqDataLen;
    *dataNegRespCode_u8     = 0;
    dataReturnValue_u8=E_NOT_OK;
    nrResDataLen_u32    = 0;

    flgSplObdMid_b =  FALSE;
    adrTempBuffer_au8[0] = 0;

    DCM_UNUSED_PARAM(OpStatus);

   if((adrReqData_pu8[0] & 0x1fu) != 0x00u)
   {
        if(nrReqDataLen_u32 == 0x01u)
        {

            flgSplObdMid_b = FALSE;
            adrTempBuffer_au8[0] = adrReqData_pu8[0];
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INVALID_LENGTH)
        }
   }
   else if((nrReqDataLen_u32 != 0x00u)&&(nrReqDataLen_u32 < 0x07u))
   {

        flgSplObdMid_b = TRUE;

        for(idxObdMid_qu32=0; idxObdMid_qu32<nrReqDataLen_u32; idxObdMid_qu32++)
        {

            if((adrReqData_pu8[idxObdMid_qu32] & 0x1fu)== 0x00u)
            {

                adrTempBuffer_au8[idxObdMid_qu32] = adrReqData_pu8[idxObdMid_qu32];
            }
            else{

                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_MIXED_MODE)
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                break;
            }
        }
   }
   else{

        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INVALID_LENGTH)
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }

   if(*dataNegRespCode_u8 == 0)
   {
#if(DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_ON)

        if(flgSplObdMid_b == FALSE)
        {

            nrRange_u8 = (uint8)(adrTempBuffer_au8[0]/0x20);

            if(((Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].BitMask_u32) & (0x80000000uL>>((adrTempBuffer_au8[0]%0x20)- 1u))) != 0x00u)
            {

                dataMidArrayLimit_u8 = Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8 +
                                                  Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].NumMids_u8;

                for(idxObdMid_qu32= Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8;
                    idxObdMid_qu32 < dataMidArrayLimit_u8;
                    idxObdMid_qu32++)
                {

                    if(adrTempBuffer_au8[0] == Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8)
                    {

                        idxTidarrayLimit_u16 = (uint16)(Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Num_Tids_u8 +
                                                        Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16);

                        for(idxTid_qu32 = Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16;
                            idxTid_qu32 < idxTidarrayLimit_u16;
                            idxTid_qu32++)
                        {

                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE)
                        	{

                        		dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16
   ,                                                                                               					 &dataMinLimit_u16
   ,                                                                                               					 &dataMaxLimit_u16
   ,                                                                                               					 &stStatus_u8);
                        	}
                        	else
                        	{
                        

                                dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL
   ,                               																					 &dataTestVal_u16
   ,                               																					 &dataMinLimit_u16
   ,                               																					 &dataMaxLimit_u16
   ,                               																					 &stStatus_u8);
                        	}
                            if(dataReturnValue_u8 == E_OK)
                            {

                                if(stStatus_u8 == DCM_DTRSTATUS_VISIBLE)
                                {
                                	if((nrResDataLen_u32+9u)<=pMsgContext->resMaxDataLen)
                                	{

   									adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[0];
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = Dcm_Dsp_TidArray_acs[idxTid_qu32].Tid_Id_u8;
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = Dcm_Dsp_TidArray_acs[idxTid_qu32].UnitScale_u8;
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16>>8u);
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16);
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16>>8u);
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16);
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16>>8u);
   									nrResDataLen_u32++;
   									adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16);
   									nrResDataLen_u32++;
                                	}
                                	else
                                	{
                                    
                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                
                
   									*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                                        dataMidArrayLimit_u8 = (uint8)idxObdMid_qu32;
                                        break;
                                	}
                                }
                                else
                                {
                                    if(stStatus_u8 != DCM_DTRSTATUS_INVISIBLE)
                                    {

                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_WRONG_STATUSVALUE)
                                    }
                                }
                            }
                            else
                            {

                                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                            }
                        }

                        break;
                    }
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else{

            for(idxReq_qu32=0;idxReq_qu32<nrReqDataLen_u32;idxReq_qu32++)
            {
                nrRange_u8 = (uint8)(adrTempBuffer_au8[idxReq_qu32]/0x20);

                if(Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].BitMask_u32 != 0x00uL)
                {

                    dataBitMask_u32 = 0x0;

                    for(idxObdMid_qu32=Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8;
                        ((idxObdMid_qu32 < DCM_CFG_DSP_OBDMIDARRAYSIZE) && ((dataBitMask_u32 & 0x01u) != 0x01u));
                        idxObdMid_qu32++)
                    {

                        idxTidarrayLimit_u16 = (uint16)(Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Num_Tids_u8 +
                                                    Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16);

                        for(idxTid_qu32 = Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16;
                            idxTid_qu32 < idxTidarrayLimit_u16;
                            idxTid_qu32++)
                        {

                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE)
                        	{

                        		dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16
   ,                                                                                               					 &dataMinLimit_u16
   ,                                                                                               					 &dataMaxLimit_u16
   ,                                                                                               					 &stStatus_u8);
                        	}
                        	else
                        	{
                        

                                dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL
   ,                               																					 &dataTestVal_u16
   ,                               																					 &dataMinLimit_u16
   ,                               																					 &dataMaxLimit_u16
   ,                               																					 &stStatus_u8);
                        	}
                            if(dataReturnValue_u8 == E_OK)
                            {

                                if(stStatus_u8 == DCM_DTRSTATUS_VISIBLE)
                                {

                                    if(nrRange_u8 == (Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8/0x20))
                                    {

                                        dataBitMask_u32 = dataBitMask_u32|(0x80000000u>>
                                            ((((Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8)%0x20) - 1)));
                                    }
                                    else
                                    {

                                        dataBitMask_u32 = dataBitMask_u32|0x01uL;
                                    }

                                    break;
                                }
                                else
                                {
                                    if(stStatus_u8 != DCM_DTRSTATUS_INVISIBLE)
                                    {

                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_WRONG_STATUSVALUE)
                                    }
                                }
                            }
                            else
                            {

                                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                            }

                        }
                    }

                    if(dataBitMask_u32 != 0x0uL)
                    {
                    	if((nrResDataLen_u32+5uL)<=pMsgContext->resMaxDataLen)
                    	{
   						adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[idxReq_qu32];
   						nrResDataLen_u32++;
   						adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>24u);
   						nrResDataLen_u32++;
   						adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>16u);
   						nrResDataLen_u32++;
   						adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>8u);
   						nrResDataLen_u32++;
   						adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32);
   						nrResDataLen_u32++;
                    	}
                    	else
                    	{
                        
                            DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

    
    
   						*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                            dataBitMask_u32=0x01;

                            nrReqDataLen_u32 = idxReq_qu32;
                            break;
                    	}
                    }
                }
            }
        }
#elif(DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_OFF)

        if(flgSplObdMid_b == FALSE)
        {

            ObmidValue = adrTempBuffer_au8[0];

            if(Dem_DcmGetNumTIDsOfOBDMID(ObmidValue, &numberOfTIDs_u8)==E_OK)
            {

                for(idxTid_u8 = 0; idxTid_u8 < numberOfTIDs_u8; idxTid_u8++)
                {

                    if(Dem_DcmGetDTRData(ObmidValue, idxTid_u8, &Tid_Id_u8, &UnitScale_u8, &dataTestVal_u16, &dataMinLimit_u16, &dataMaxLimit_u16) == E_OK)
                    {
                        if((nrResDataLen_u32+9uL) <= pMsgContext->resMaxDataLen)
                        {

                            adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[0];
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = Tid_Id_u8;
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = UnitScale_u8;
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16>>8u);
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16);
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16>>8u);
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16);
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16>>8u);
                            nrResDataLen_u32++;
                            adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16);
                            nrResDataLen_u32++;
                        }
                        else
                        {

                            DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

                            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                            break;
                        }
                    }
                    else
                    {
                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                    }
                }
            }
            else{
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else{

            for(idxReq_qu32=0; idxReq_qu32<nrReqDataLen_u32; idxReq_qu32++)
            {
                ObmidValue = adrTempBuffer_au8[idxReq_qu32];

                if(Dem_DcmGetAvailableOBDMIDs(ObmidValue, &dataBitMask_u32) == E_OK)
                {

                    if((nrResDataLen_u32+5uL)<=pMsgContext->resMaxDataLen)
                    {
                        adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[idxReq_qu32];
                        nrResDataLen_u32++;
                        adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>24u);
                        nrResDataLen_u32++;
                        adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>16u);
                        nrResDataLen_u32++;
                        adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>8u);
                        nrResDataLen_u32++;
                        adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32);
                        nrResDataLen_u32++;
                    }
                    else
                    {

                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW);

                        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                        break;
                    }
                }
                else{
                    DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                }
            }
        }
#endif

        if(nrResDataLen_u32 != 0x0uL)
        {

            pMsgContext->resDataLen = nrResDataLen_u32;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }

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

