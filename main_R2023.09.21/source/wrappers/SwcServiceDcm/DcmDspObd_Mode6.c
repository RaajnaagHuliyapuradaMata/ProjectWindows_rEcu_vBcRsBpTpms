#include "Std_Types.hpp"

#include "DcmDspObd_Mode6_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE6_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode06(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Dcm_MsgType,				 AUTOMATIC) adrResData_pu8;
   VAR(Dcm_MsgType,				 AUTOMATIC) adrReqData_pu8;
   VAR(Dcm_MsgLenType,				 AUTOMATIC) nrResDataLen_u32;
   VAR(Dcm_MsgLenType,				 AUTOMATIC) nrReqDataLen_u32;
   VAR(uint32,						 AUTOMATIC) dataBitMask_u32;
   VAR(uint16_least,				 AUTOMATIC) idxTid_qu32;
   VAR(uint16,						 AUTOMATIC) idxTidarrayLimit_u16;
   VAR(uint16,						 AUTOMATIC) dataTestVal_u16;
   VAR(uint16,						 AUTOMATIC) dataMinLimit_u16;
   VAR(uint16,					     AUTOMATIC) dataMaxLimit_u16;
   VAR(uint8_least,				 AUTOMATIC) idxReq_qu32;
   VAR(uint8_least,				 AUTOMATIC) idxObdMid_qu32;
   VAR(uint8,				         AUTOMATIC) stStatus_u8;
   VAR(Std_ReturnType,     AUTOMATIC) dataReturnValue_u8;
   VAR(uint8,     AUTOMATIC) adrTempBuffer_au8[8];
   VAR(uint8,						 AUTOMATIC) nrRange_u8;
   VAR(uint8,						 AUTOMATIC) dataMidArrayLimit_u8;
   VAR(boolean,					 AUTOMATIC) flgSplObdMid_b;

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

                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE
                           ){
                              dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16
                                 ,  &dataMinLimit_u16
                                 ,  &dataMaxLimit_u16
                                 ,  &stStatus_u8
                              );
                        	}
                        	else
                        	{
                        

                                dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL
   ,     																					 &dataTestVal_u16
   ,     																					 &dataMinLimit_u16
   ,     																					 &dataMaxLimit_u16
   ,     																					 &stStatus_u8);
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
                            idxTid_qu32++
                        ){
                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE
                           ){
                              dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16
                                 ,  &dataMinLimit_u16
                                 ,  &dataMaxLimit_u16
                                 ,  &stStatus_u8
                              );
                        	}
                        	else{
                              dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL
                                 ,  &dataTestVal_u16
                                 ,  &dataMinLimit_u16
                                 ,  &dataMaxLimit_u16
                                 ,  &stStatus_u8
                              );
                        	}
                            if(dataReturnValue_u8 == E_OK){
                                if(stStatus_u8 == DCM_DTRSTATUS_VISIBLE){
                                    if(nrRange_u8 == (Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8/0x20)){
                                        dataBitMask_u32 = dataBitMask_u32|(0x80000000u>>
                                            ((((Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8)%0x20) - 1)));
                                    }
                                    else{
                                        dataBitMask_u32 = dataBitMask_u32|0x01uL;
                                    }
                                    break;
                                }
                                else{
                                    if(stStatus_u8 != DCM_DTRSTATUS_INVISIBLE){
                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_WRONG_STATUSVALUE)
                                    }
                                }
                            }
                            else{
                                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                            }
                        }
                    }
                    if(dataBitMask_u32 != 0x0uL){
                    	if((nrResDataLen_u32+5uL)<=pMsgContext->resMaxDataLen){
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
                    	else{
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
        if(nrResDataLen_u32 != 0x0uL){
            pMsgContext->resDataLen = nrResDataLen_u32;
        }
        else{
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
   }
   if(*dataNegRespCode_u8 != 0){
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

