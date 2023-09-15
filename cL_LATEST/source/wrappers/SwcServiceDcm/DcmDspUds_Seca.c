
#include "DcmDspUds_Seca_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Seca_Prv.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
Dcm_SecLevelType Dcm_dataSecLevel_u8;
static Dcm_SecLevelType CurrentSecLevel_u8;
static uint8 s_idxSecTab_u8;
static Std_ReturnType s_SrvRetValue_u8;
uint8  Dcm_DspSecTabIdx_u8;
uint8  Dcm_DspSecAccType_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

void Dcm_ResetAsynchSecaFlag(void){

     s_Dcm_SecaRteCallPlaced_b = FALSE;
}
#endif

static void Dcm_Lok_CheckNRCForSeedRequest(const Dcm_MsgContextType* pMsgContext
   ,                                          Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    *dataNegRespCode_u8 = 0x00u;
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    Dcm_Lok_HasWaitCounterCycleExhausted(dataNegRespCode_u8);
   if(0x00 == *dataNegRespCode_u8)
#endif
   {
        *dataNegRespCode_u8 = (s_idxSecTab_u8 < DCM_CFG_DSP_NUMSECURITY)?0x00u:DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }
   if(0x00 == *dataNegRespCode_u8)
   {

        Dcm_ptrSecurityConfig_pcst = &Dcm_Dsp_Security[s_idxSecTab_u8];

        if(pMsgContext->reqDataLen != (0x01u + Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32))
        {
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else if((Dcm_ptrSecurityConfig_pcst->NumAttLock_u8 > 0) &&
                (Dcm_Dsp_Seca[s_idxSecTab_u8].FailedAtm_cnt_u8 >= Dcm_ptrSecurityConfig_pcst->NumAttLock_u8))
        {
            *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
        }
#if(DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_REQUEST_SEED)

        else if(Dcm_Dsp_Seca[s_idxSecTab_u8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
        {
            *dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
        }
#endif
        else{
            (void)(Dcm_GetSecurityLevel(&CurrentSecLevel_u8));
        }
   }
}

static void Dcm_Lok_CheckNRCForKeyRequest(const Dcm_MsgContextType* pMsgContext
   ,                                         Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    *dataNegRespCode_u8 = (s_idxSecTab_u8 < DCM_CFG_DSP_NUMSECURITY)?0x00u:DCM_E_SUBFUNCTIONNOTSUPPORTED;
   if(0x00u == *dataNegRespCode_u8)
   {
        Dcm_ptrSecurityConfig_pcst = &Dcm_Dsp_Security[s_idxSecTab_u8];
        Dcm_dataSecLevel_u8   = ((Dcm_DspSecAccType_u8+1)>>1u);
        if(pMsgContext->reqData[0] != (Dcm_DspSecAccType_u8 +1u))
        {
            *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
        }

        else if((TRUE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength) &&
                (pMsgContext->reqDataLen > (Dcm_ptrSecurityConfig_pcst->Key_size_u32+1u)))
        {
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else if( (FALSE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength) &&
                (pMsgContext->reqDataLen != (Dcm_ptrSecurityConfig_pcst->Key_size_u32+1u)))
        {
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }

#if(DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_SEND_KEY)
        else if(Dcm_Dsp_Seca[s_idxSecTab_u8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
        {
            *dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
        }
#endif
        else{
            *dataNegRespCode_u8 = 0x00u;
        }
   }
}

static void Dcm_Lok_ProcessSeedRequest(Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint8 loopcounter;
    *dataNegRespCode_u8 = 0x00;
    // Loop the security table array to point to requested Security level
   for(loopcounter=0x00u; (loopcounter < DCM_CFG_DSP_NUMSECURITY) &&
    (Dcm_Dsp_Security[loopcounter].Security_level_u8 != Dcm_dataSecLevel_u8); loopcounter++)
   {

   }
   s_idxSecTab_u8 = loopcounter;

    // NRC Check for Seed Request
    Dcm_Lok_CheckNRCForSeedRequest(pMsgContext,dataNegRespCode_u8);

   if(0x00 == *dataNegRespCode_u8)
   {
        Dcm_DspSecAccType_u8 = pMsgContext->reqData[0];
        Dcm_DspSecTabIdx_u8 = s_idxSecTab_u8;
        // Requested Security level is already active
        if(Dcm_dataSecLevel_u8 == CurrentSecLevel_u8)
        {
            Dcm_Lok_UpdateSeedResponseForActiveSec(pMsgContext,Dcm_ptrSecurityConfig_pcst->Seed_size_u32);
            s_SrvRetValue_u8 = E_OK;
            Dcm_DspSecTabIdx_u8 = 0x00u;
            Dcm_DspSecAccType_u8 = 0x00u;
        }
        else{
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

            if( (FALSE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength) &&
                 Dcm_Lok_IsSeedAlreadyStored(Dcm_ptrSecurityConfig_pcst->Seed_size_u32,s_idxSecTab_u8) )
            {
                Dcm_Lok_UpdateBufferWithStoredSeed(pMsgContext,Dcm_ptrSecurityConfig_pcst->Seed_size_u32,s_idxSecTab_u8);
                s_SrvRetValue_u8 = E_OK;
            }
            else
#endif
            {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)
                Dcm_Lok_StoreSecurityAddressRecord(pMsgContext,Dcm_ptrSecurityConfig_pcst);
#endif
                // Update State Machine to Next state to generate the seed from application callbacks
                Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }
        }
   }
}

static void Dcm_Lok_ProcessKeyRequest(const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint8 loopcounter;
    *dataNegRespCode_u8 = 0x00;

   for(loopcounter=0x00u; (loopcounter < DCM_CFG_DSP_NUMSECURITY) &&
    (Dcm_Dsp_Security[loopcounter].Security_level_u8 != Dcm_dataSecLevel_u8);loopcounter++)
   {

   }
   s_idxSecTab_u8 = loopcounter;
    // Perform NRC checks for received Key request
    Dcm_Lok_CheckNRCForKeyRequest(pMsgContext,dataNegRespCode_u8);
   if(0x00 == *dataNegRespCode_u8)
   {
        Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
   }
}

void Dcm_ResetAccessType(void){
    Dcm_DspSecAccType_u8=0;
}

static void Dcm_Lok_HandleNRCForCompareKey(Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint32 nrDelay_u32;
    Dcm_ptrSecurityConfig_pcst = &Dcm_Dsp_Security[s_idxSecTab_u8];
    *dataNegRespCode_u8 = DCM_E_INVALIDKEY;

   if((Dcm_Dsp_Seca[s_idxSecTab_u8].FailedAtm_cnt_u8) < Dcm_ptrSecurityConfig_pcst->NumAttDelay_u8)
   {
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY;
   }
   if((Dcm_Dsp_Seca[s_idxSecTab_u8].FailedAtm_cnt_u8) >= Dcm_ptrSecurityConfig_pcst->NumAttDelay_u8)
   {

        if(Dcm_ptrSecurityConfig_pcst->DelayTime_u32 > 0x00u)
        {
            nrDelay_u32 = ((Dcm_ptrSecurityConfig_pcst->DelayTime_u32) * DCM_CFG_TASK_TIME_MS);

            nrDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime(Dcm_ptrSecurityConfig_pcst->Security_level_u8
   ,                   Dcm_Dsp_Seca[s_idxSecTab_u8].FailedAtm_cnt_u8
   ,                   nrDelay_u32);
            Dcm_Dsp_Seca[s_idxSecTab_u8].Residual_delay_u32 = (Dcm_Dsp_SecaGlobaltimer_u32 + (nrDelay_u32 / DCM_CFG_TASK_TIME_MS));
        }
        else{

            Dcm_Dsp_Seca[s_idxSecTab_u8].Residual_delay_u32 = 0x00u;
        }

#if(DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT != DCM_CFG_OFF)
        *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
#else
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY;
#endif
   }

   if(Dcm_ptrSecurityConfig_pcst->NumAttLock_u8 > 0)
   {

        if(Dcm_Dsp_Seca[s_idxSecTab_u8].FailedAtm_cnt_u8 == Dcm_ptrSecurityConfig_pcst->NumAttLock_u8)
        {

            DcmAppl_DcmSecurityLevelLocked((uint8)s_idxSecTab_u8);
            *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
        }
   }
}

static void Dcm_Lok_ProcessKeyApplication(Dcm_MsgContextType* pMsgContext
   ,                                         Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ApplRet_u8;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
   uint32 SeedCounter_u32;
#endif
   s_SrvRetValue_u8 = E_NOT_OK;
    ApplRet_u8 = Dcm_Lok_ProcessCompKeySM(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);

   switch(ApplRet_u8)
   {
        case E_OK:
        {
            Dcm_DspChgSecLevel_b = TRUE;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

            if(FALSE == Dcm_Dsp_Security[s_idxSecTab_u8].UseFlexibleLength)
            {

                for(SeedCounter_u32=0x0;(SeedCounter_u32 < Dcm_Dsp_Security[s_idxSecTab_u8].Seed_size_u32);SeedCounter_u32++)
                {

                    Dcm_Dsp_Seca[s_idxSecTab_u8].SeedBuff[SeedCounter_u32] = 0x00;
                }
            }
#endif
            s_SrvRetValue_u8 = E_OK;
            *dataNegRespCode_u8 = 0x00;
        }
        break;

        case DCM_E_COMPARE_KEY_FAILED:
           Dcm_Lok_HandleNRCForCompareKey(dataNegRespCode_u8);
           break;

        case DCM_E_PENDING:
            s_SrvRetValue_u8 = DCM_E_PENDING;
            *dataNegRespCode_u8 = 0x00;
            break;

        default:
            if(0x00 == *dataNegRespCode_u8)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
            break;
   }
}

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

void Dcm_Dsp_SecaClearSeed(void){
   uint8 idxSecTab_u8;
   uint32 SeedIdx_u32;
   uint32 Seedlen_u32;
   for(idxSecTab_u8=0;idxSecTab_u8 < DCM_CFG_DSP_NUMSECURITY; idxSecTab_u8++)
   {

        if(FALSE == Dcm_Dsp_Security[idxSecTab_u8].UseFlexibleLength)
        {

            Seedlen_u32 = Dcm_Dsp_Security[idxSecTab_u8].Seed_size_u32;

            for(SeedIdx_u32=0x0; (SeedIdx_u32 < Seedlen_u32); SeedIdx_u32++)
            {

                Dcm_Dsp_Seca[idxSecTab_u8].SeedBuff[SeedIdx_u32] = 0x0;
            }
        }
   }
}
#endif

static void Dcm_Lok_ProcessSeedApplication(Dcm_MsgContextType* pMsgContext
   ,                                          Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   uint32 SeedLength_u32;
    Std_ReturnType applRetValue_u8;
   s_SrvRetValue_u8 = E_NOT_OK; // Initialize service return value to E_NOT_OK

#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)
   if(TRUE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength)
   {

        SeedLength_u32 = (Dcm_ptrSecurityConfig_pcst->Seed_size_u32 > (pMsgContext->resMaxDataLen -0x01u))?
                                (pMsgContext->resMaxDataLen -0x01u):(Dcm_ptrSecurityConfig_pcst->Seed_size_u32);
        applRetValue_u8 = Dcm_Lok_CallSeedApplicationForFlexibleLength(&SeedLength_u32,pMsgContext
   ,                                                                      Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
   }
   else
#endif
   {

        SeedLength_u32 = Dcm_ptrSecurityConfig_pcst->Seed_size_u32;
        applRetValue_u8 = Dcm_Lok_CallSeedApplication(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
   }

    // Based on return value process further
   switch(applRetValue_u8)
   {
        case E_OK:
        {
            *dataNegRespCode_u8 = 0x00;

            pMsgContext->resData[0] = Dcm_DspSecAccType_u8;
            pMsgContext->resDataLen = (SeedLength_u32 + 1u);

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
            if(FALSE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength)
            {
                Dcm_Lok_StoreSeed(SeedLength_u32,pMsgContext);
            }
#endif
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
            s_SrvRetValue_u8=E_OK;
        }
        break;

        case DCM_E_PENDING:
        {
            Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
            s_SrvRetValue_u8 = DCM_E_PENDING;
            *dataNegRespCode_u8 = 0x00;
        }
        break;

        default:
        {
            if(*dataNegRespCode_u8 == 0x00u)
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
        }
        break;
   }
}

static void Dcm_Lok_ProcessNewSecaRequest(Dcm_MsgContextType* pMsgContext
   ,                                         Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

   uint8 dataSubFunc_u8 = pMsgContext->reqData[0];
    *dataNegRespCode_u8 = 0x00;

   if((dataSubFunc_u8 & 0x01u) > 0u)
   {
        Dcm_dataSecLevel_u8 = ((dataSubFunc_u8 + 1u)>>1u);
        Dcm_Lok_ProcessSeedRequest(pMsgContext,dataNegRespCode_u8);
   }
   else if(dataSubFunc_u8 != 0x0u)
   {
        Dcm_dataSecLevel_u8 = (dataSubFunc_u8 >> 1u);
        Dcm_Lok_ProcessKeyRequest(pMsgContext,dataNegRespCode_u8);
   }
   else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }
}

Std_ReturnType SwcServiceDcm_tSecurityAccess(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType* pMsgContext
   ,                                    Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
   s_SrvRetValue_u8 = E_NOT_OK;
    *dataNegRespCode_u8  = 0x0;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_SecaIni();
        s_SrvRetValue_u8 = E_OK;
   }
   else{

        if(Dcm_SrvOpstatus_u8==(DCM_INITIAL))
        {
            Dcm_Lok_ProcessNewSecaRequest(pMsgContext,dataNegRespCode_u8);
        }

        if(Dcm_SrvOpstatus_u8 ==(DCM_CHECKDATA))
        {
            Dcm_Lok_ProcessSeedApplication(pMsgContext,dataNegRespCode_u8);
        }

        if(Dcm_SrvOpstatus_u8 ==(DCM_PROCESSSERVICE))
        {
            Dcm_Lok_ProcessKeyApplication(pMsgContext,dataNegRespCode_u8);
        }

        if(*dataNegRespCode_u8 != 0x0u)
        {

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;

            Dcm_DspSecAccType_u8 = 0x0;
            Dcm_DspSecTabIdx_u8  = 0x0;
            s_SrvRetValue_u8=E_NOT_OK;
        }
   }
    return s_SrvRetValue_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
