#include "Std_Types.hpp"

#include "DcmDspObd_Mode8_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE8_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode8_Priv.hpp"
#include "rba_BswSrv.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode08 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8;
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8;
   VAR(uint32,     AUTOMATIC) dataTidMaskVal_u32;
   VAR(uint32,     AUTOMATIC) dataCalTidBitMask_u32;
   VAR(Dcm_MsgLenType, AUTOMATIC) nrReqDataLen_u32;
   VAR(uint16_least,   AUTOMATIC) idxTidRes_qu16;
   VAR(uint8_least,    AUTOMATIC) nrTid_qu8;
   VAR(uint8_least,    AUTOMATIC) idxTidStart_qu8;
   VAR(uint8_least,    AUTOMATIC) nrNumTids_qu8;
   VAR(uint8_least,    AUTOMATIC) nrTidChk_qu8;
   VAR(uint8,     AUTOMATIC) adrTmpBuf_au8[DCM_OBDMODE08_REQ_LEN_MAX];
   VAR(uint8,     AUTOMATIC) idxTID_u8;
   VAR(uint8,     AUTOMATIC) nrMultiple_u8;
   VAR(Std_ReturnType, AUTOMATIC) stRetTID_u8;
   VAR(boolean,     AUTOMATIC) stTIDFound_u8;
   VAR(Std_ReturnType, AUTOMATIC) dataRetval_u8;

    *dataNegRespCode_u8   = 0x0u;
   idxTidRes_qu16 = 0;
    nrTid_qu8 = 0;
   idxTidStart_qu8 = 0;
    nrNumTids_qu8 = 0;
    dataCalTidBitMask_u32 = 0;
    adrTmpBuf_au8[0] = 0;

   stTIDFound_u8 = FALSE;
    nrMultiple_u8 = 0;
   idxTID_u8 = 0;
   stRetTID_u8 = 0;
    dataRetval_u8=E_NOT_OK;

    nrReqDataLen_u32 = (pMsgContext->reqDataLen);

    adrReqBuf_pu8 = pMsgContext->reqData;

    DCM_UNUSED_PARAM(OpStatus);

   if(((adrReqBuf_pu8[0] & 0x1Fu) != 0x00u) && (nrReqDataLen_u32 > DCM_OBDMODE08_REQ_LEN_MIN))
   {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        idxTID_u8 =(uint8) (adrReqBuf_pu8[0] / DCM_OBDMODE08_SUPPTID);

        dataTidMaskVal_u32 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].BitMask_u32;

        dataCalTidBitMask_u32 = ((uint32)1u << ((uint32)32u - ((adrReqBuf_pu8[0]) % 0x20)));

        if((dataTidMaskVal_u32 & dataCalTidBitMask_u32) > 0u)
        {

            idxTidStart_qu8 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].StartIndex_u8;
            nrNumTids_qu8 =  Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].NumTids_u8;

            stTIDFound_u8 = FALSE;

            for(nrTid_qu8 = idxTidStart_qu8;((nrTid_qu8 <(idxTidStart_qu8 + nrNumTids_qu8)) &&(stTIDFound_u8 == FALSE));nrTid_qu8++)
            {
            
                if( adrReqBuf_pu8[0] == (Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].Tid_Id_u8))
                {

                    stTIDFound_u8 = TRUE;

   				if(pMsgContext->resMaxDataLen>(uint32)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].OutBuffer_u8))
   				{

   					if(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].InBuffer_u8 == (nrReqDataLen_u32 - 1u))
   					{
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u )

   					    if(nrReqDataLen_u32 != 1u)
   					    {

   					        DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]), &(adrReqBuf_pu8[1]) ,nrReqDataLen_u32 - 1u);
   					    }
#endif

   						adrRespBuf_pu8 = pMsgContext->resData;

   						if(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].UsePort_b != FALSE)
   						{

   						    if(nrReqDataLen_u32 != 1u)
   						    {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u )

   						        stRetTID_u8 = ((*(RequestControl1_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
                                                                  (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],&Dcm_InParameterBuf_au8[0]));
#endif
   						    }
   						    else
   						    {

   						        stRetTID_u8 = ((*(RequestControl1_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
   						                                                                          (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],NULL_PTR));
   						    }

   						}
   						else
   						{

   						    if(nrReqDataLen_u32 != 1u)
   						     {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u )

   						         stRetTID_u8 = ((*(RequestControl2_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
   						                                                                  (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],&Dcm_InParameterBuf_au8[0]));
#endif
   						     }
   						    else
   						     {

   						          stRetTID_u8 = ((*(RequestControl2_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
   						                                                                                                 (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],NULL_PTR));
   						     }

   						}
   						if(stRetTID_u8==E_OK)
   						{

   								adrRespBuf_pu8[idxTidRes_qu16] = adrReqBuf_pu8[0];
   								idxTidRes_qu16++;

   								idxTidRes_qu16 = (idxTidRes_qu16 +
   												 (Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].OutBuffer_u8));

   								pMsgContext->resDataLen = idxTidRes_qu16;

   								*dataNegRespCode_u8   = 0x0u;
   						}
   						else
   						{

   							*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   						}
   					}
   					else
   					{

   						*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

   						DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_INVALID_LENGTH)
   					}
   				}
   				else
   				{

   					*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

   					DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
   				}
   			}
            }
        }
   }
   else{

        if((nrReqDataLen_u32 > DCM_OBDMODE08_REQ_LEN_MIN) && (nrReqDataLen_u32 < DCM_OBDMODE08_REQ_LEN_MAX))
        {

            for(nrTidChk_qu8=0;(nrTidChk_qu8 < nrReqDataLen_u32);nrTidChk_qu8++)
            {

                if((adrReqBuf_pu8[nrTidChk_qu8] & 0x1Fu)==0u)
                {

                    nrMultiple_u8++;
                }

                adrTmpBuf_au8[nrTidChk_qu8] = adrReqBuf_pu8[nrTidChk_qu8];
            }

            if(nrMultiple_u8 == nrReqDataLen_u32)
            {

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                adrRespBuf_pu8 = pMsgContext->resData;

                for(nrTidChk_qu8=0;(nrTidChk_qu8 < nrReqDataLen_u32);nrTidChk_qu8++)
                {

                    idxTID_u8 = (uint8)((adrTmpBuf_au8[nrTidChk_qu8]) / DCM_OBDMODE08_SUPPTID);

                    dataTidMaskVal_u32 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].BitMask_u32;

                    if(dataTidMaskVal_u32 > 0u)
                    {
                    	if((pMsgContext->resMaxDataLen - idxTidRes_qu16) > 0x4u)
                    	{

   						adrRespBuf_pu8[idxTidRes_qu16] = adrTmpBuf_au8[nrTidChk_qu8];
   						idxTidRes_qu16++;

   						adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 24u);
   						idxTidRes_qu16++;
   						adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 16u);
   						idxTidRes_qu16++;
   						adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 8u);
   						idxTidRes_qu16++;
   						adrRespBuf_pu8[idxTidRes_qu16] = (uint8) dataTidMaskVal_u32;
   						idxTidRes_qu16++;

   						*dataNegRespCode_u8   = 0x0;
                    	}
                    	else
                    	{
    
    						DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

   						break;
                    	}
                    }
                }

                pMsgContext->resDataLen = idxTidRes_qu16;
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_MIXED_MODE)
            }
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_INVALID_LENGTH)
        }
   }

   if(*dataNegRespCode_u8 != 0x0u)
   {

        dataRetval_u8=E_NOT_OK;
   }
   else{

        dataRetval_u8=E_OK;
   }

    return dataRetval_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

