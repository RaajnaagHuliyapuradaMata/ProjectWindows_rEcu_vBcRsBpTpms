#include "Std_Types.hpp"

#include "DcmDspObd_Mode2_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode2_Priv.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode02 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8;
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8;
   VAR(uint32,     AUTOMATIC)   dataPIDBitMask_u32;
   VAR(uint32,     AUTOMATIC)   dataCalBitMask_u32;
   VAR(uint32,     AUTOMATIC)   nrDTC_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC)   nrResDataLen_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC)   nrReqDataLen_u32;
   VAR(Dcm_MsgLenType,AUTOMATIC)   nrResMaxDataLen_u32;
   VAR(uint16,		   AUTOMATIC)   idxDataSource_u16;
   VAR(uint8_least,   AUTOMATIC)   nrPIDChk_qu8;
   VAR(uint8_least,   AUTOMATIC)   nrPIDValid_qu8;
   VAR(uint8_least,   AUTOMATIC)   idxPIDStart_qu8;
   VAR(uint8_least,   AUTOMATIC)   idxPIDData_qu8;
   VAR(uint8,     AUTOMATIC)   nrMultiple_u8;
   VAR(uint8,     AUTOMATIC)   idxPID_u8;
   VAR(uint8,     AUTOMATIC)   adrTmpBuf_au8[3];
   VAR(uint8,     AUTOMATIC)   nrBufSize_u8;
   VAR(uint8,     AUTOMATIC)   nrPid_u8;
   VAR(Std_ReturnType,AUTOMATIC)   dataRetGet_u8;
   VAR(Std_ReturnType,AUTOMATIC)   dataRetVal_u8;
   VAR(boolean,     AUTOMATIC)   isPIDFound_b;
   VAR(boolean,     AUTOMATIC)   flgGetDTCNum_b;

    *dataNegRespCode_u8    		 = 0x0u;
    nrDTC_u32     		 = 0x00;
    adrTmpBuf_au8[0] 		 = 0x00;
    nrReqDataLen_u32       = (pMsgContext->reqDataLen);
    nrPIDValid_qu8        = 0x00;
    nrResDataLen_u32 		 = 0x00;
    nrMultiple_u8  		 = 0;

    flgGetDTCNum_b          = TRUE;
   idxPIDStart_qu8       = 0x00;
    nrPid_u8       = 0x00;
   idxDataSource_u16 = 0x00;
   idxPIDData_qu8        = 0x00;

   isPIDFound_b         = FALSE;
    dataRetVal_u8=E_NOT_OK;

    DCM_UNUSED_PARAM(OpStatus);

   if((nrReqDataLen_u32==0x02uL)||(nrReqDataLen_u32==0x04uL)||(nrReqDataLen_u32==0x06uL))
   {

        adrReqBuf_pu8 = pMsgContext->reqData;

        for(nrPIDChk_qu8=0;(nrPIDChk_qu8 < nrReqDataLen_u32);nrPIDChk_qu8 +=2u)
        {

            if((adrReqBuf_pu8[nrPIDChk_qu8] & 0x1Fu)==0u)
            {

                nrMultiple_u8++;
            }

            if((adrReqBuf_pu8[nrPIDChk_qu8 + 1u]) == 0x00u)
            {

                adrTmpBuf_au8[nrPIDValid_qu8] = adrReqBuf_pu8[nrPIDChk_qu8];

                nrPIDValid_qu8++;
            }

        }

        if((nrMultiple_u8 == 0u) || (nrMultiple_u8 == (uint8)(nrReqDataLen_u32 >> 1u) ))
        {

            adrRespBuf_pu8 = pMsgContext->resData;

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

            for(nrPIDChk_qu8=0;(nrPIDChk_qu8 < nrPIDValid_qu8);nrPIDChk_qu8++)
            {

                idxPID_u8 = (uint8)((adrTmpBuf_au8[nrPIDChk_qu8]) / DCM_OBDMODE02_SUPPPID);

                dataPIDBitMask_u32 = Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].BitMask_u32;

                if(nrMultiple_u8 != 0)
                {
                	if(dataPIDBitMask_u32 > 0u)
   				{
                
                		if(nrResMaxDataLen_u32>=0x06uL)
                		{

   						adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
   						nrResDataLen_u32++;

   						adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
   						nrResDataLen_u32++;

   						adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 24u);
   						nrResDataLen_u32++;
   						adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 16u);
   						nrResDataLen_u32++;
   						adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 8u);
   						nrResDataLen_u32++;
   						adrRespBuf_pu8[nrResDataLen_u32] = (uint8) dataPIDBitMask_u32;
   						nrResDataLen_u32++;

   						nrResMaxDataLen_u32 = nrResMaxDataLen_u32 - 0x06uL;

   						*dataNegRespCode_u8 = 0x0u;
                		}
                
                		else
                		{
                
   						DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

   						*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

   						break;
                		}
                	}
                }

                else{

                	dataCalBitMask_u32 = ((uint32)1u << ((uint32)32u - ((adrTmpBuf_au8[nrPIDChk_qu8]) % 0x20)));

   				if((dataPIDBitMask_u32 & dataCalBitMask_u32)> 0uL)
   				{

   					if((DCM_DSPMODE02_PID02 == adrTmpBuf_au8[nrPIDChk_qu8])||(flgGetDTCNum_b != FALSE))
   					{

   						flgGetDTCNum_b = FALSE;

   						if(Dem_GetDTCOfOBDFreezeFrame(0x00, &nrDTC_u32) != E_OK)
   						{
   							nrDTC_u32 = 0x00;
   						}
   					}

   					if(DCM_DSPMODE02_PID02 == adrTmpBuf_au8[nrPIDChk_qu8])
   					{
   						if(nrResMaxDataLen_u32 >= 0x04uL)
   						{

   							adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
   							nrResDataLen_u32++;

   							adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
   							nrResDataLen_u32++;

   							adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(nrDTC_u32 >> 16u);
   							nrResDataLen_u32++;
   							adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(nrDTC_u32 >> 8u);
   							nrResDataLen_u32++;

   							nrResMaxDataLen_u32 = nrResMaxDataLen_u32 - 0x04uL;

   							*dataNegRespCode_u8 = 0u;
   						}
   						else
   						{
                   
   							DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

   							*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

   							nrPIDValid_qu8 = nrPIDChk_qu8 ;
   						}

   					}
   					else{
   						if((nrDTC_u32 & 0xFFFF00uL)> 0uL){
   							idxPIDStart_qu8 = Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].StartIndex_u8;
   							isPIDFound_b = FALSE;
   						    dataRetGet_u8   = E_OK;
   							for(nrPid_u8 = (uint8)idxPIDStart_qu8;((nrPid_u8 <(idxPIDStart_qu8 +(Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].NumPids_u8))) && (isPIDFound_b == FALSE));nrPid_u8++
                        ){
   								if( adrTmpBuf_au8[nrPIDChk_qu8] == (Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Id_u8)
                              ){
   									isPIDFound_b = TRUE;
   									if(nrResMaxDataLen_u32>=(uint32)(Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8+2)
                                 ){
   										idxPIDData_qu8 = Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].DataSourcePid_ArrayIndex_u16;
   										for(idxDataSource_u16=(uint16)(nrResDataLen_u32+2uL);idxDataSource_u16<(nrResDataLen_u32+Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8+2u);idxDataSource_u16++
                                 ){
   											adrRespBuf_pu8[idxDataSource_u16] = 0x00;
   										}
   										for(idxDataSource_u16= (uint16)idxPIDData_qu8;((idxDataSource_u16<(idxPIDData_qu8+Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Num_DataSourcePids_u8)) && (dataRetGet_u8==E_OK));idxDataSource_u16++
                                 ){
   											nrBufSize_u8 = (uint8)Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8;
   											dataRetGet_u8 = Dem_ReadDataOfOBDFreezeFrame(adrTmpBuf_au8[nrPIDChk_qu8],(uint8)(idxDataSource_u16-idxPIDData_qu8)
   ,  &adrRespBuf_pu8[nrResDataLen_u32 +Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Pos_data_u8+2u]
   ,  &nrBufSize_u8);
   											if(dataRetGet_u8 == E_OK){
   												if(nrBufSize_u8 >Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8){
   													dataRetGet_u8=E_NOT_OK;
   												}
   											}
   										}
   										if(dataRetGet_u8 == E_OK){
   											adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
   											nrResDataLen_u32++;
   											adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
   											nrResDataLen_u32++;
   											nrResDataLen_u32 = nrResDataLen_u32 + Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8;
   											nrResMaxDataLen_u32 =  nrResMaxDataLen_u32 - (2uL + (Dcm_MsgLenType)Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8);
   											*dataNegRespCode_u8 = 0u;
   										}
   										else{
   											DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_RET_E_NOT_OK)
   										}
   									}
   									else{
   										DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
   											*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   										nrPIDValid_qu8 = nrPIDChk_qu8;
   										break;
   									}
   								}
   							}
   						}
   					}
   				}
                }
            }
            pMsgContext->resDataLen = nrResDataLen_u32;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_MIXED_MODE)
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INVALID_LENGTH)
   }

   if(*dataNegRespCode_u8 != 0x0u)
   {

        dataRetVal_u8=E_NOT_OK;

   }
   else{
        dataRetVal_u8=E_OK;
   }

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

