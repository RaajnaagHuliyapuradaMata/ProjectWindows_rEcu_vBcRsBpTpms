

#include "DcmDspUds_Rdpi_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
static Dcm_DspRdpiState_ten Dcm_stDspRdpiState_en;
static Dcm_OpStatusType s_Dcm_DspCondChkRdOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

static uint8 s_nrPeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_Dsp_RdpiIni   (void)
{

    Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
    s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
}

static Std_ReturnType Dcm_RdpiIsTransmissionModeSupported(uint8 dataTransmissionMode_u8);
static Std_ReturnType Dcm_RdpiIsTransmissionModeSupported(uint8 dataTransmissionMode_u8)
{
    Std_ReturnType dataRetVal_u8;

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
    else
    {

    }

    return dataRetVal_u8;
}

Std_ReturnType Dcm_RdpiIsDidCondtionChkReadSupported(Dcm_DIDIndexType_tst * idxDidIndexType_st)
{
    uint16 idxIndex_u16;
    Std_ReturnType dataCondChkRetVal_u8;
    const Dcm_DIDConfig_tst * ptrDidConfig;
    const Dcm_DataInfoConfig_tst * ptrSigConfig;
    const Dcm_SignalDIDSubStructConfig_tst * ptrControlSigConfig;
    void * ptrDIDFnc;
    dataCondChkRetVal_u8=E_OK;
    ptrDIDFnc=NULL_PTR;
    ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];

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
            else
            {
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

    return dataCondChkRetVal_u8;
}

static void Dcm_ResetRdpiStateVariables(uint8 idxIndex_u8, Dcm_RdpiTxModeType_ten dataOverflowValue_en,
                                                       uint16 dataId_u16, uint16 idxPeriodicId_u16,
                                                       uint32 cntrTime_u32,boolean dataRange_b);
static void Dcm_ResetRdpiStateVariables(uint8 idxIndex_u8, Dcm_RdpiTxModeType_ten dataOverflowValue_en,
                                                      uint16 dataId_u16, uint16 idxPeriodicId_u16,
                                                      uint32 cntrTime_u32,boolean dataRange_b)
{
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en= dataOverflowValue_en;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16=dataId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].idxPeriodicId_u16=idxPeriodicId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].cntrTime_u32=cntrTime_u32;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataRange_b=dataRange_b;
}

Std_ReturnType Dcm_DcmReadDataByPeriodicIdentifier(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Dcm_DIDIndexType_tst s_Dcm_idxDidIndexType_st;
    uint32 dataSessionMask_u32;
    uint32 dataSecurityMask_u32;
    const Dcm_ExtendedDIDConfig_tst * adrExtendedConfig_pcst;
    uint8 idxIndex_u8;
    uint8 dataTransmissionMode_u8;
    Dcm_RdpiTxModeType_ten dataOverflowValue_en;
    boolean isValidId_b;
    boolean isScheduler_b;
    Std_ReturnType retVal_u8;
    Std_ReturnType dataCondChkRetVal_u8;
    const Dcm_DIDConfig_tst * ptrDidConfig;
    static uint32 s_idxLoop_qu32;
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
    Std_ReturnType IsDIDAvailFnc_u8 = E_NOT_OK;
#endif

    *dataNegRespCode_u8        = 0x00;

    isValidId_b             = FALSE;
    isScheduler_b = FALSE;
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

    if (OpStatus == DCM_CANCEL)
    {

        Dcm_Dsp_RdpiIni();

        retVal_u8 = E_OK;
    }
    else
    {

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
                                s_idxLoop_qu32 = 1u;

                                while(s_idxLoop_qu32 < (pMsgContext->reqDataLen))
                                {

                                    if((E_OK == Dcm_Lok_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))&&(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE))
                                    {

                                        ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];
                                        adrExtendedConfig_pcst=Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
                                        isScheduler_b = (ptrDidConfig->dataDynamicDid_b!=FALSE)? TRUE : FALSE;

                                        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
                                        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                                        if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
                                        {
                                            IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
                                        }

                                        if((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||
                                                ((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) &&
                                                        (IsDIDAvailFnc_u8 == E_OK)))
#endif
                                        {

                                            if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
                                            {

                                                if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
                                                {

                                                    s_Dcm_idxDidIndexType_st.dataopstatus_b=s_Dcm_DspCondChkRdOpStatus_u8;

                                                    dataCondChkRetVal_u8=Dcm_RdpiIsDidCondtionChkReadSupported(&s_Dcm_idxDidIndexType_st);

                                                    if(E_OK==dataCondChkRetVal_u8)
                                                    {
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)

                                                        if( ptrDidConfig->dataDynamicDid_b!=FALSE)
                                                        {
                                                            if(E_OK==Dcm_DspGetIndexOfDDDI_u8((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u),&(s_Dcm_idxDidIndexType_st.idxIndex_u16)))
                                                            {
                                                                if(Dcm_DDDIBaseConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].dataDDDIRecordContext_pst->nrCurrentlyDefinedRecords_u16==0)
                                                                {

                                                                    if(isValidId_b!=FALSE)
                                                                    {
                                                                        *dataNegRespCode_u8 = 0x00;
                                                                        isScheduler_b = TRUE;
                                                                    }

                                                                    else
                                                                    {
                                                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                                                    }
                                                                }

                                                                else
                                                                {
                                                                    *dataNegRespCode_u8 = 0x00;
                                                                    isScheduler_b = FALSE;
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

                                                            if((idxIndex_u8==DCM_CFG_MAX_DID_SCHEDULER) && (isScheduler_b == FALSE))
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

                                                        s_idxLoop_qu32 = pMsgContext->reqDataLen;
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
                                    s_idxLoop_qu32++;
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
                else
                {

#if(DCM_CFG_RDPIISOVERSION==DCM_ISO14229_1_2013_03)
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
#else
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
#endif
                }
            }
            else
            {
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

            else
            {
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

                else
                {

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
            else
            {

                for(s_idxLoop_qu32=1;s_idxLoop_qu32 < (pMsgContext->reqDataLen);s_idxLoop_qu32++)
                {

                    if((E_OK == Dcm_Lok_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))&&(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE))
                    {

                        ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

                        if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
                        {
                            IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
                        }

                        if((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) && (IsDIDAvailFnc_u8==E_OK)))
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

                                        Dcm_ResetRdpiStateVariables(idxIndex_u8,dataOverflowValue_en,(uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u),
                                                s_Dcm_idxDidIndexType_st.idxIndex_u16,(uint32)0x01,s_Dcm_idxDidIndexType_st.dataRange_b);
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
#include "Dcm_MemMap.h"
#endif
