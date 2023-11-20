#include "Std_Types.hpp"

#include "DcmDspUds_Rdpi_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspRdpiState_ten, DCM_VAR) Dcm_stDspRdpiState_en;
static VAR (Dcm_OpStatusType, DCM_VAR) s_Dcm_DspCondChkRdOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(uint8,     DCM_VAR) s_nrPeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE)Dcm_Dsp_RdpiIni   (void){

    Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
   s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
}

static FUNC(Std_ReturnType,DCM_CODE)Dcm_RdpiIsTransmissionModeSupported(VAR(uint8,AUTOMATIC) dataTransmissionMode_u8);
static FUNC(Std_ReturnType,DCM_CODE)Dcm_RdpiIsTransmissionModeSupported(VAR(uint8,AUTOMATIC) dataTransmissionMode_u8)
{
   VAR(Std_ReturnType,     AUTOMATIC) dataRetVal_u8;

    dataRetVal_u8=E_NOT_OK;

   if((dataTransmissionMode_u8 > 0x00) && (dataTransmissionMode_u8 < 0x04))
   {

        if(((dataTransmissionMode_u8 == DCM_DSP_RDPI_SLOW_RATE)   && (DCM_CFG_PERIODICTX_SLOWRATE  !=0x00u)) ||
           ((dataTransmissionMode_u8 == DCM_DSP_RDPI_MEDIUM_RATE) && (DCM_CFG_PERIODICTX_MEDIUMRATE!=0x00u)) ||
           ((dataTransmissionMode_u8 == DCM_DSP_RDPI_FAST_RATE)   && (DCM_CFG_PERIODICTX_FASTRATE  !=0x00u)))
        {
            dataRetVal_u8=E_OK;
        }
   }
   else if(dataTransmissionMode_u8 == 0x04u)
   {
        dataRetVal_u8=E_OK;
   }
   else{

   }

    return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiIsDidCondtionChkReadSupported(P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st)
{
   VAR(uint16,     AUTOMATIC) idxIndex_u16;
   VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
    dataCondChkRetVal_u8=E_OK;
    ptrDIDFnc=NULL_PTR;
    ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];

   if(idxDidIndexType_st->dataRange_b==FALSE)
   {

        for(idxIndex_u16=0;((idxIndex_u16<ptrDidConfig->nrSig_u16)&&(dataCondChkRetVal_u8==E_OK));idxIndex_u16++)
        {
            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxIndex_u16].idxDcmDspDatainfo_u16];
            ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

            if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
            {
                ptrDIDFnc=ptrControlSigConfig->adrCondChkRdFnc_cpv;

               if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||             \
                   (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
               {

                   dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrDIDFnc))(&idxDidIndexType_st->dataNegRespCode_u8);
               }
               else{
                   if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                  (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC) ||
#endif
                  (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                   {

                       dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &idxDidIndexType_st->dataNegRespCode_u8);
                   }
               }

            }
        }
   }
   else{

        dataCondChkRetVal_u8=E_OK;
   }

    return dataCondChkRetVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_ResetRdpiStateVariables(VAR(uint8,AUTOMATIC)idxIndex_u8, VAR(Dcm_RdpiTxModeType_ten, AUTOMATIC) dataOverflowValue_en
   ,     VAR(uint16,AUTOMATIC)dataId_u16, VAR(uint16, AUTOMATIC) idxPeriodicId_u16
   ,     VAR(uint32,AUTOMATIC) cntrTime_u32,VAR(boolean,AUTOMATIC) dataRange_b);
static FUNC(void,DCM_CODE) Dcm_ResetRdpiStateVariables(VAR(uint8,AUTOMATIC)idxIndex_u8, VAR(Dcm_RdpiTxModeType_ten, AUTOMATIC) dataOverflowValue_en
   ,     VAR(uint16,AUTOMATIC)dataId_u16, VAR(uint16, AUTOMATIC) idxPeriodicId_u16
   ,     VAR(uint32,AUTOMATIC) cntrTime_u32,VAR(boolean,AUTOMATIC) dataRange_b)
{
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en= dataOverflowValue_en;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16=dataId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].idxPeriodicId_u16=idxPeriodicId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].cntrTime_u32=cntrTime_u32;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataRange_b=dataRange_b;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadDataByPeriodicIdentifier(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (Dcm_DIDIndexType_tst,     AUTOMATIC) s_Dcm_idxDidIndexType_st;
   VAR (uint32,AUTOMATIC) dataSessionMask_u32;
   VAR (uint32,AUTOMATIC) dataSecurityMask_u32;
   P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst;
   VAR(uint8,     AUTOMATIC) idxIndex_u8;
   VAR(uint8,     AUTOMATIC) dataTransmissionMode_u8;
   VAR(Dcm_RdpiTxModeType_ten,     AUTOMATIC) dataOverflowValue_en;
   VAR(boolean,     AUTOMATIC) isValidId_b;
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
   VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   static VAR(uint32,DCM_VAR) s_idxLoop_qu32;
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
   VAR (Std_ReturnType,AUTOMATIC) IsDIDAvailFnc_u8 = E_NOT_OK;
#endif

    *dataNegRespCode_u8        = 0x00;

   isValidId_b             = FALSE;
   s_nrPeriodicId_u8 = 0x00;
   s_Dcm_idxDidIndexType_st.idxIndex_u16   =   0;

   s_Dcm_idxDidIndexType_st.dataRange_b    =   FALSE;
   s_Dcm_idxDidIndexType_st.dataNegRespCode_u8=0;
    dataCondChkRetVal_u8=E_OK;
    dataSessionMask_u32=0;
    dataSecurityMask_u32=0;
    adrExtendedConfig_pcst=NULL_PTR;
    ptrDidConfig=NULL_PTR;
    retVal_u8 = E_NOT_OK;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RdpiIni();

        retVal_u8 = E_OK;
   }
   else{

        if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_INIT)
        {

            if(((pMsgContext->reqDataLen)!=0u)&&(DCMRDPIMINLENGTHCHECK((pMsgContext->reqDataLen),(pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE]))))
            {

                if(DCMRDPIMAXLENGTHCHECK( pMsgContext->reqDataLen ))
                {

                    dataTransmissionMode_u8 = pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE];

                    if(E_OK==Dcm_RdpiIsTransmissionModeSupported(dataTransmissionMode_u8))
                    {

                        if(dataTransmissionMode_u8==DCM_DSP_RDPI_STOP_SENDING)
                        {

                            Dcm_stDspRdpiState_en = DCM_DSP_RDPI_CHECKPERMISSION;
                        }
                        else
                        {

                            if(Dcm_NumOfActivePeriodicId_u8<DCM_CFG_MAX_DID_SCHEDULER)
                            {

                                for(s_idxLoop_qu32=1u;((s_idxLoop_qu32 < (pMsgContext->reqDataLen)) && (*dataNegRespCode_u8 ==0x00));s_idxLoop_qu32++)
                                {

                                    if(E_OK == Dcm_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))
                                    {

                                        if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
                                        {
                                            ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];
                                            adrExtendedConfig_pcst=Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
                                        }
#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

                                        else
                                        {
                                            adrExtendedConfig_pcst=Dcm_DIDRangeConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
                                        }
#endif

                                        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
                                        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                                       if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
   								   {
                                        IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
   								   }

                                        if((s_Dcm_idxDidIndexType_st.dataRange_b==TRUE) ||
                                           ((s_Dcm_idxDidIndexType_st.dataRange_b==FALSE) &&
                                             ((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||
                                              ((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) &&
                                               (IsDIDAvailFnc_u8 == E_OK)))))
#endif
                                        {

                                            if((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
                                            {

                                                if((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
                                                {

                                                    s_Dcm_idxDidIndexType_st.dataopstatus_b=s_Dcm_DspCondChkRdOpStatus_u8;

                                                    dataCondChkRetVal_u8=Dcm_RdpiIsDidCondtionChkReadSupported(&s_Dcm_idxDidIndexType_st);

                                                    if(E_OK==dataCondChkRetVal_u8)
                                                    {
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)

                                                        if(s_Dcm_idxDidIndexType_st.dataRange_b!=TRUE)
                                                        {

                                                            if( ptrDidConfig->dataDynamicDid_b!=FALSE)
                                                            {
                                                                if(E_OK==Dcm_DspGetIndexOfDDDI_u8((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u),&(s_Dcm_idxDidIndexType_st.idxIndex_u16)))
                                                                {
                                                                    if(Dcm_DDDIBaseConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].dataDDDIRecordContext_pst->nrCurrentlyDefinedRecords_u16==0)
                                                                    {
                                                                        *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
                                                                    }
                                                                }
                                                            }
                                                        }
#endif

                                                        if(*dataNegRespCode_u8==0x00)
                                                        {

                                                            for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER ;idxIndex_u8++)
                                                            {

                                                                if((Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == (pMsgContext->reqData[s_idxLoop_qu32]|0xF200u)) && (Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION))
                                                                {

                                                                    isValidId_b=TRUE;
                                                                    break;
                                                                }
                                                            }

                                                            if(idxIndex_u8==DCM_CFG_MAX_DID_SCHEDULER)
                                                            {

                                                                s_nrPeriodicId_u8++;

                                                                isValidId_b=TRUE;
                                                            }
                                                        }

                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
                                                    }
                                                    else if(DCM_E_PENDING==dataCondChkRetVal_u8)
                                                    {

                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_PENDING;
                                                        retVal_u8=DCM_E_PENDING;
                                                    }

                                                    else
                                                    {
                                                        if(s_Dcm_idxDidIndexType_st.dataNegRespCode_u8==0x00)
                                                        {

                                                            *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                                                        }
                                                        else
                                                        {

                                                            *dataNegRespCode_u8=s_Dcm_idxDidIndexType_st.dataNegRespCode_u8;
                                                        }

                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
                                                    }
                                                }

                                                else
                                                {
                                                    *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(*dataNegRespCode_u8 ==0x00)
                                {

                                    if((isValidId_b!=FALSE) && ((s_nrPeriodicId_u8+Dcm_NumOfActivePeriodicId_u8)<=DCM_CFG_MAX_DID_SCHEDULER))
                                    {
                                        Dcm_stDspRdpiState_en = DCM_DSP_RDPI_CHECKPERMISSION;
                                        s_nrPeriodicId_u8 = 0x00;
                                    }

                                    else
                                    {
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
                                }
                            }

                            else
                            {
                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            }
                        }
                    }

                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else{

#if(DCM_CFG_RDPIISOVERSION==DCM_ISO14229_1_2013_03)
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
#else
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
#endif
                }
            }
            else{
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }

        if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_CHECKPERMISSION)
        {

            dataTransmissionMode_u8 = pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE];

            if(dataTransmissionMode_u8 == DCM_DSP_RDPI_SLOW_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_SLOW_RATE;
            }

            else if(dataTransmissionMode_u8 == DCM_DSP_RDPI_MEDIUM_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_MEDIUM_RATE;
            }

            else if(dataTransmissionMode_u8 == DCM_DSP_RDPI_FAST_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_FAST_RATE;
            }

            else{
                dataOverflowValue_en = DCM_RDPI_NO_TRANMISSION;
            }

            if(dataTransmissionMode_u8 == DCM_DSP_RDPI_STOP_SENDING)
            {

                if(pMsgContext->reqDataLen == 0x01u)
                {
                    for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                    {

                        Dcm_ResetRdpiStateVariables(idxIndex_u8,DCM_RDPI_NO_TRANMISSION,(uint16)0x00,(uint16)0x00,(uint32)0x00,FALSE);
                    }
                    Dcm_NumOfActivePeriodicId_u8=0x00;
                }

                else{

                    for(s_idxLoop_qu32=1;s_idxLoop_qu32 < (pMsgContext->reqDataLen);s_idxLoop_qu32++)
                    {

                        for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                        {
                            if((Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == ((pMsgContext->reqData[s_idxLoop_qu32]|0xF200u))) && (Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION))
                            {

                                Dcm_ResetRdpiStateVariables(idxIndex_u8,DCM_RDPI_NO_TRANMISSION,(uint16)0x00,(uint16)0x00,(uint32)0x00,FALSE);
                                Dcm_NumOfActivePeriodicId_u8--;
                                break;
                            }
                        }
                    }
                }

                Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
            }
            else{

                for(s_idxLoop_qu32=1;s_idxLoop_qu32 < (pMsgContext->reqDataLen);s_idxLoop_qu32++)
                {

                    if(E_OK == Dcm_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))
                    {

                        if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
                        {

                            ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];
                        }
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

   					if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
   					{
   						  IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
   					}

                        if(((s_Dcm_idxDidIndexType_st.dataRange_b==FALSE))&&((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) && (IsDIDAvailFnc_u8==E_OK))))
#endif
                        {
                            s_nrPeriodicId_u8++;

                            for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                            {

                                if(Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == (pMsgContext->reqData[s_idxLoop_qu32]|0xF200u))
                                {

                                    if(Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en==DCM_RDPI_NO_TRANMISSION)
                                    {
                                        Dcm_NumOfActivePeriodicId_u8++;
                                    }

                                    Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en= dataOverflowValue_en;
                                    Dcm_PeriodicInfo_st[idxIndex_u8].cntrTime_u32=1;
                                    break;
                                }
                            }

                            if(idxIndex_u8==DCM_CFG_MAX_DID_SCHEDULER)
                            {

                                for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                                {
                                    if(Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en==DCM_RDPI_NO_TRANMISSION)
                                    {

                                        Dcm_ResetRdpiStateVariables(idxIndex_u8,dataOverflowValue_en,(uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u)
   ,     s_Dcm_idxDidIndexType_st.idxIndex_u16,(uint32)0x01,s_Dcm_idxDidIndexType_st.dataRange_b);
                                        Dcm_NumOfActivePeriodicId_u8++;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                }

                if(s_nrPeriodicId_u8 ==0x00)
                {
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                if((s_idxLoop_qu32 == pMsgContext->reqDataLen)&& (*dataNegRespCode_u8==0x00))
                {

                    Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
                }
            }

            if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_INIT)
            {

                pMsgContext->resDataLen=0x00;
                retVal_u8=E_OK;
            }
        }

        if(*dataNegRespCode_u8 != 0x0)
        {

            Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
            retVal_u8=E_NOT_OK;
        }
   }
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
