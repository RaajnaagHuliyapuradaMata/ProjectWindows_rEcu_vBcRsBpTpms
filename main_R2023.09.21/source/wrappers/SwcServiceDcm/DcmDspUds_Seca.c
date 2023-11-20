#include "Std_Types.hpp"

#include "DcmDspUds_Seca_Inf.hpp"

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) )
#include "DcmDspUds_Seca_Prv.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8, DCM_VAR)  Dcm_DspSecTabIdx_u8;
VAR(uint8, DCM_VAR)  Dcm_DspSecAccType_u8;
static VAR(uint8, DCM_VAR)   Dcm_Lok_stCmpKey_u8;
static VAR(Dcm_SecLevelType, DCM_VAR)    Dcm_Lok_dataSecLevel_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8_least, DCM_VAR)  Dcm_Lok_idxSecTab_qu8;

static P2CONST(Dcm_Dsp_Security_t,AUTOMATIC,DCM_INTERN_DATA) Dcm_Lok_ptrSecurityConfig_p;
static P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)   Dcm_Lok_ptrSecaFnc_p;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
#endif
static VAR(uint8,AUTOMATIC)                     Dcm_Lok_dataSecAccType_u8;
static VAR(uint8,AUTOMATIC)                     Dcm_Lok_dataSubFunc_u8;
static VAR(uint32,AUTOMATIC)                    Dcm_Lok_nrSeedLen_u32;
static VAR(Dcm_Dsp_SecaStates_ten,AUTOMATIC)    Dcm_Lok_substSeca_en;
static VAR(Std_ReturnType,AUTOMATIC)            Dcm_Lok_dataRetGetSeed_u8;

static VAR(Std_ReturnType,AUTOMATIC)            Dcm_Lok_dataRetValue_u8;
static VAR(Std_ReturnType,AUTOMATIC)            Dcm_Lok_secaServRetValue_u8;

static VAR(uint32,AUTOMATIC)                    Dcm_Lok_nrDelay_u32;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
static VAR(boolean,AUTOMATIC)                   Dcm_Lok_stBuffer_b;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

static VAR(boolean, DCM_VAR)      Dcm_Lok_flgApplFuncCall_b;
#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

static VAR(boolean, DCM_VAR)      Dcm_Lok_Dcm_SecaRteCallPlaced_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

FUNC (void,DCM_CODE) Dcm_ResetAsynchSecaFlag(void){

     Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;
}
#endif

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_NewSecurityLevelToUnlock
                            (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                              P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
#else
static FUNC(void,DCM_CODE) Dcm_Lok_NewSecurityLevelToUnlock
                            (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                              P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
#endif
{
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

   VAR(uint32,AUTOMATIC)      l_idxSeed_qu32;

    Dcm_Lok_nrSeedLen_u32 = Dcm_Lok_ptrSecurityConfig_p->Seed_size_u32;

   for(l_idxSeed_qu32 =0; (l_idxSeed_qu32 < Dcm_Lok_nrSeedLen_u32); l_idxSeed_qu32++)
   {

        if(Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].SeedBuff[l_idxSeed_qu32] != 0x0)
        {

        Dcm_Lok_stBuffer_b = TRUE;
        break;
        }
   }

   if(Dcm_Lok_stBuffer_b != FALSE)
   {

        for(l_idxSeed_qu32 =0; (l_idxSeed_qu32 < Dcm_Lok_nrSeedLen_u32); l_idxSeed_qu32++)
        {

        pMsgContext->resData[l_idxSeed_qu32 + 0x1u] = Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].SeedBuff[l_idxSeed_qu32];
        }

        pMsgContext->resData[0] = Dcm_Lok_dataSubFunc_u8;

        pMsgContext->resDataLen = (Dcm_MsgLenType)(l_idxSeed_qu32 + 1u);
        Dcm_Lok_secaServRetValue_u8=E_OK;
   }
   else
#endif
   {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)

        if( Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32 != 0x00u)
        {

            DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]), &(pMsgContext->reqData[1])
   ,     Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32);
        }

#endif

        *OpStatus = DCM_CHECKDATA;

        Dcm_Lok_substSeca_en = DCM_DSP_SECA_GENSEED;
#if((DCM_CFG_DSP_SECA_STORESEED == DCM_CFG_OFF) && (DCM_CFG_IN_PARAM_MAXLEN <= 0u))
        (void)(pMsgContext);
#endif
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_ReqSecIsCurrentSecurityLevel
                           (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                            P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
   VAR(uint32,AUTOMATIC)  idxLoopSeed_qu32;

    pMsgContext->resData[0] = Dcm_Lok_dataSecAccType_u8;

   for(idxLoopSeed_qu32=1;(idxLoopSeed_qu32 <=Dcm_Lok_ptrSecurityConfig_p->Seed_size_u32);idxLoopSeed_qu32++)
   {
        pMsgContext->resData[idxLoopSeed_qu32] = 0x00;
   }

    pMsgContext->resDataLen = (uint8)idxLoopSeed_qu32;

    *OpStatus = DCM_INITIAL;

    Dcm_DspSecAccType_u8 = 0x0;

    Dcm_DspSecTabIdx_u8  = 0x0;
    Dcm_Lok_secaServRetValue_u8=E_OK;
}

static FUNC(void,DCM_CODE) Dcm_Lok_CurrentSecurityLevel
                            (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Dcm_SecLevelType,AUTOMATIC)   dataGetSecurityLevel_u8;
   VAR(Std_ReturnType,AUTOMATIC)     dataRetGetSecLevel_u8;

    dataRetGetSecLevel_u8 = Dcm_GetSecurityLevel(&dataGetSecurityLevel_u8);

   if(dataRetGetSecLevel_u8 == E_OK)
   {
        Dcm_DspSecTabIdx_u8  = (uint8)(Dcm_Lok_idxSecTab_qu8);
        Dcm_DspSecAccType_u8 = Dcm_Lok_dataSecAccType_u8;

        if(dataGetSecurityLevel_u8 == Dcm_Lok_dataSecLevel_u8)
        {
        Dcm_Lok_ReqSecIsCurrentSecurityLevel(&Dcm_SrvOpstatus_u8,pMsgContext);
        }

        else{
        Dcm_Lok_NewSecurityLevelToUnlock(&Dcm_SrvOpstatus_u8,pMsgContext);
        }
   }
   else{

    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecurityLevelConfigured
                           (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Lok_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];

   if(pMsgContext->reqDataLen != (0x01u + Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32))
   {

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }

   else if((Dcm_Lok_ptrSecurityConfig_p->NumAttLock_u8 > 0) &&
    (Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8 >= Dcm_Lok_ptrSecurityConfig_p->NumAttLock_u8))
   {
        *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
   }
#if(DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_REQUEST_SEED)

   else if(Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
   {
        *dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
   }
#endif
   else{
        Dcm_Lok_CurrentSecurityLevel(pMsgContext,dataNegRespCode_u8);
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaSeedRequest (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(uint8_least, DCM_VAR)  l_idxSecTab_qu8;

    Dcm_Lok_dataSecAccType_u8 = Dcm_Lok_dataSubFunc_u8;

    Dcm_Lok_dataSecLevel_u8 = ((Dcm_Lok_dataSecAccType_u8 + 1u)>>1u);

   for(l_idxSecTab_qu8=0; (l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY) &&
    (Dcm_Dsp_Security[l_idxSecTab_qu8].Security_level_u8 != Dcm_Lok_dataSecLevel_u8); l_idxSecTab_qu8++)
       {

       }

    Dcm_Lok_idxSecTab_qu8 = l_idxSecTab_qu8;

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

   if(Dcm_GetattemptCounterWaitCycle_u8 > DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
   {
#endif

        if(l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY)
        {
        Dcm_Lok_SecurityLevelConfigured (pMsgContext,dataNegRespCode_u8);
        }
        else{

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   }
   else{
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
#endif
}

static FUNC(void,DCM_CODE) Dcm_Lok_ReqSecaLvlConfigured
                            (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                              P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Lok_ptrSecurityConfig_p =&Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];

    Dcm_Lok_dataSecLevel_u8   = ((Dcm_DspSecAccType_u8+1)>>1u);

   if(Dcm_Lok_dataSubFunc_u8 != (Dcm_DspSecAccType_u8+1u))
   {

        *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
   }

   else if(pMsgContext->reqDataLen != (Dcm_Lok_ptrSecurityConfig_p->Key_size_u32 + 1u))
   {

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
#if(DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_SEND_KEY)

   else if(Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
   {

        *dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
   }
#endif
   else{

        *OpStatus = DCM_CHECKDATA;

        Dcm_Lok_substSeca_en = DCM_DSP_SECA_COMPAREKEY;
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_ChkForReqSecaLvl
                           (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(uint8_least, DCM_VAR)  l_idxSecTab_qu8;

    Dcm_Lok_dataSecLevel_u8 = (Dcm_Lok_dataSubFunc_u8 >> 1u);

   for(l_idxSecTab_qu8=0; (l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY) &&
    (Dcm_Dsp_Security[l_idxSecTab_qu8].Security_level_u8 != Dcm_Lok_dataSecLevel_u8); l_idxSecTab_qu8++)
   {

   }

    Dcm_Lok_idxSecTab_qu8 = l_idxSecTab_qu8;

   if(l_idxSecTab_qu8 >= DCM_CFG_DSP_NUMSECURITY)
   {

        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }
   else{
        Dcm_Lok_ReqSecaLvlConfigured(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaRequestState(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    Dcm_Lok_dataSubFunc_u8    = pMsgContext->reqData[0];

   if((Dcm_Lok_dataSubFunc_u8 & 0x01u) > 0u)
   {
        Dcm_Lok_SecaSeedRequest(pMsgContext,dataNegRespCode_u8);
   }
   else{
        if(Dcm_Lok_dataSubFunc_u8 != 0x0)
        {
            Dcm_Lok_ChkForReqSecaLvl(pMsgContext,dataNegRespCode_u8);
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyPnding
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    *dataNegRespCode_u8 =0x00u;
    Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
    Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
}

#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_SecaAsyncServerPt(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if(!Dcm_Lok_Dcm_SecaRteCallPlaced_b)
   {

        Dcm_Lok_stCmpKey_u8 =
        (*(Dcm_CompareKey_ptr4)(Dcm_Lok_ptrSecaFnc_p))(&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8);

        if(Dcm_Lok_stCmpKey_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Lok_stCmpKey_u8 = DCM_E_PENDING;
        }
        else{

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_stCmpKey_u8))
            {
                Dcm_Lok_stCmpKey_u8= E_NOT_OK;
            }
        }
   }
   else{

        Dcm_Lok_stCmpKey_u8 =
        (*(Dcm_CompareKey_ptr5)(Dcm_Lok_ptrSecurityConfig_p->Dsp_CompareKey_ResultFp))(dataNegRespCode_u8);

        if((Dcm_Lok_stCmpKey_u8 == RTE_E_OK) || (Dcm_Lok_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED))
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Lok_stCmpKey_u8 == RTE_E_NO_DATA)
        {
            Dcm_Lok_stCmpKey_u8 = DCM_E_PENDING;
        }
        else{
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_stCmpKey_u8))
               {
                    Dcm_Lok_stCmpKey_u8= E_NOT_OK;
               }
        }
   }
}
#endif
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCheckdataStValidKeyChk
                           (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
   if(Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

        if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_SecaAsyncServerPt(pMsgContext,dataNegRespCode_u8);
        }
        else
#endif
        {

            Dcm_Lok_stCmpKey_u8 = (*(Dcm_CompareKey_ptr1)(Dcm_Lok_ptrSecaFnc_p))(&(pMsgContext->reqData[1]),\
                                     Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
        }
   }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
   if(Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_FNC)
   {

        Dcm_Lok_stCmpKey_u8 = (*(Dcm_CompareKey_ptr3)(Dcm_Lok_ptrSecaFnc_p))
        (Dcm_Lok_ptrSecurityConfig_p->Key_size_u32,&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8,dataNegRespCode_u8);
   }
#endif
}

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_SecaUseAsynchronousServerCallPoint (void){

   if(!Dcm_Lok_Dcm_SecaRteCallPlaced_b)
   {

        Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                                 (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                                 (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);

        if(Dcm_Lok_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Lok_dataRetValue_u8 = DCM_E_PENDING;
        }
        else{

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8))
            {
                Dcm_Lok_dataRetValue_u8= E_NOT_OK;
            }
        }
   }
   else{

        Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct1)
                                 (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_Resultfp))();
        if(Dcm_Lok_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Lok_dataRetValue_u8 == RTE_E_NO_DATA)
        {
            Dcm_Lok_dataRetValue_u8 = DCM_E_PENDING;
        }
        else{
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8))
            {
                Dcm_Lok_dataRetValue_u8= E_NOT_OK;
            }
        }
   }
}
#endif

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Lok_SecaValidKeyNotificationToAppIsOk
                           (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
#else
static FUNC(void,DCM_CODE) Dcm_Lok_SecaValidKeyNotificationToAppIsOk
                           (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#endif
{
#if((DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)&&(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF))
   VAR(boolean, AUTOMATIC)  isInfrastructureErrorPresent_b = FALSE;

#endif

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_SecaUseAsynchronousServerCallPoint();
        }
        else
#endif
       {

            Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                                    (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                                    (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
       }
   }
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

   if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR) && \
    (Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER))
   {
        isInfrastructureErrorPresent_b = Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8);
   }

   if(isInfrastructureErrorPresent_b != FALSE)
   {

        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
   }
   else
#endif
#endif
   {
        if(DCM_E_PENDING == Dcm_Lok_dataRetValue_u8)
        {
            Dcm_Lok_flgApplFuncCall_b = TRUE;
            Dcm_Lok_substSeca_en = DCM_DSP_SECA_PENDING;
            Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
        }
        else{

            *OpStatus = DCM_PROCESSSERVICE;
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaUnlockSecurityLvl(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    *dataNegRespCode_u8 =0x00;
    Dcm_Lok_secaServRetValue_u8=E_OK;
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

    Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8 = 0;

    pMsgContext->resData[0] = (Dcm_DspSecAccType_u8+1);
    pMsgContext->resDataLen = 0x1;

   if(DCM_E_PENDING == DcmAppl_DcmSecaValidKey((uint8)Dcm_Lok_idxSecTab_qu8) )
   {
        Dcm_Lok_substSeca_en = DCM_DSP_SECA_PENDING;
   }
   else{
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
        Dcm_Lok_SecaValidKeyNotificationToAppIsOk(OpStatus,dataNegRespCode_u8);
#else
        Dcm_Lok_SecaValidKeyNotificationToAppIsOk(OpStatus);
#endif
   }
}

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyFailed (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
#else
static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyFailed (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#endif
{
#if((DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)&&(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF))
   VAR(boolean, AUTOMATIC)  isInfrastructureErrorPresent_b = FALSE;
#endif

    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

   if(Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8 < 0xFF)
   {

        Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8++;
   }

   if( DCM_E_PENDING == DcmAppl_DcmSecaInvalidKey((uint8)Dcm_Lok_idxSecTab_qu8))
   {
        Dcm_Lok_substSeca_en =DCM_DSP_SECA_PENDING;
   }
   else{
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Lok_SecaUseAsynchronousServerCallPoint();
            }
            else
#endif
            {

                Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                                        (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                                        (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

        if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR) && \
        (Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER))
        {
            isInfrastructureErrorPresent_b = Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8);
        }
        if(isInfrastructureErrorPresent_b != FALSE)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
        }
        else
#endif
#endif
        {
            if(DCM_E_PENDING==Dcm_Lok_dataRetValue_u8 )
            {
                Dcm_Lok_flgApplFuncCall_b = TRUE;
                Dcm_Lok_substSeca_en = DCM_DSP_SECA_PENDING;
                Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            }
            else{

                *OpStatus = DCM_PROCESSSERVICE;
            }
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyNotOk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
{
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    *OpStatus = DCM_PROCESSSERVICE;
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyNegResp
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(*dataNegRespCode_u8 == 0x00u)
   {

       *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKeyStatusChk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if(Dcm_Lok_stCmpKey_u8 ==E_OK)
   {
        Dcm_Lok_SecaUnlockSecurityLvl(OpStatus,pMsgContext,dataNegRespCode_u8);
   }
   else if(Dcm_Lok_stCmpKey_u8 ==DCM_E_PENDING)
   {
        Dcm_Lok_SecaCmpKeyPnding(dataNegRespCode_u8);
   }
   else if(Dcm_Lok_stCmpKey_u8 ==E_NOT_OK)
   {
        Dcm_Lok_SecaCmpKeyNotOk(OpStatus);
   }
   else if(Dcm_Lok_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
   {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
        Dcm_Lok_SecaCmpKeyFailed(OpStatus,dataNegRespCode_u8);
#else
        Dcm_Lok_SecaCmpKeyFailed(OpStatus);
#endif
   }
   else{
        Dcm_Lok_SecaCmpKeyNegResp(dataNegRespCode_u8);
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaCmpKey (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                           P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    Dcm_Lok_dataSecLevel_u8  = ((Dcm_DspSecAccType_u8+1)>>1u);

    Dcm_Lok_idxSecTab_qu8 = Dcm_DspSecTabIdx_u8;

    Dcm_Lok_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];

    Dcm_Lok_ptrSecaFnc_p= Dcm_Lok_ptrSecurityConfig_p->Dsp_CompareKey_fp;

    Dcm_Lok_flgApplFuncCall_b = FALSE;

    Dcm_Lok_SecaCheckdataStValidKeyChk(pMsgContext,dataNegRespCode_u8);

   if(  (Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_stCmpKey_u8) != FALSE) &&
    ((Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER) ))
   {

        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
   }
   else{

        Dcm_Lok_SecaCmpKeyStatusChk(OpStatus,pMsgContext,dataNegRespCode_u8);
   }
}

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_SecaAsyncServerCallPointChkForGetSeed
                            (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                             P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if(!Dcm_Lok_Dcm_SecaRteCallPlaced_b)
   {
        if(Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32!=0x00u)
        {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)

            Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr5)(Dcm_Lok_ptrSecaFnc_p))(&(Dcm_InParameterBuf_au8[0])
   ,     Dcm_DspSecaOpStatus_u8);
#endif
        }
        else{

            Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr6)(Dcm_Lok_ptrSecaFnc_p))(Dcm_DspSecaOpStatus_u8);
        }

        if(Dcm_Lok_dataRetGetSeed_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Lok_dataRetGetSeed_u8 = DCM_E_PENDING;
        }
        else{

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetGetSeed_u8))
            {
                Dcm_Lok_dataRetGetSeed_u8= E_NOT_OK;
            }
        }
   }
   else{

        Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr7)(Dcm_Lok_ptrSecurityConfig_p->Dsp_GetSeed_ResultFp))
                                    (&(pMsgContext->resData[1]),dataNegRespCode_u8);
        if(Dcm_Lok_dataRetGetSeed_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Lok_dataRetGetSeed_u8 == RTE_E_NO_DATA)
        {
            Dcm_Lok_dataRetGetSeed_u8 = DCM_E_PENDING;
        }
        else{
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetGetSeed_u8))
            {
                Dcm_Lok_dataRetGetSeed_u8= E_NOT_OK;
            }
        }
   }
}
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_GenerateSeedAsynchClientServer
                           (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

        if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_SecaAsyncServerCallPointChkForGetSeed(pMsgContext,dataNegRespCode_u8);
        }
        else
#endif
        {
            if(Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32!=0x00u)
            {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)

                Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr)(Dcm_Lok_ptrSecaFnc_p))( &(Dcm_InParameterBuf_au8[0])
   ,     Dcm_DspSecaOpStatus_u8,&(pMsgContext->resData[1]),dataNegRespCode_u8);
#endif
            }
            else{

                Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr3)(Dcm_Lok_ptrSecaFnc_p))(Dcm_DspSecaOpStatus_u8
   ,     &(pMsgContext->resData[1]),dataNegRespCode_u8);
            }
        }
   }
}
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_GenerateSeedAsynchFnc
                            (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_FNC)
   {
        if(Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32!=0x00u)
        {
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)

            Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_Lok_ptrSecurityConfig_p->Dsp_GetSeed_fp))(
                Dcm_Lok_dataSecLevel_u8
   ,     Dcm_Lok_nrSeedLen_u32
   ,     Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32
   ,     &(Dcm_InParameterBuf_au8[0])
   ,     &(pMsgContext->resData[1])
   ,     Dcm_DspSecaOpStatus_u8
   ,     dataNegRespCode_u8);
#endif
        }
        else{

            Dcm_Lok_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_Lok_ptrSecaFnc_p))(
                Dcm_Lok_dataSecLevel_u8
   ,     Dcm_Lok_nrSeedLen_u32
   ,     Dcm_Lok_ptrSecurityConfig_p->AccDataRecsize_u32
   ,     NULL_PTR
   ,     &(pMsgContext->resData[1])
   ,     Dcm_DspSecaOpStatus_u8
   ,     dataNegRespCode_u8);
        }
   }
}
#endif

static FUNC(void,DCM_CODE)Dcm_Lok_GetSeedReturnedWoError(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

   VAR(uint32,AUTOMATIC)      l_idxSeed_qu32;
#endif
    *dataNegRespCode_u8 = 0x00;
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

    pMsgContext->resData[0] = Dcm_DspSecAccType_u8;
    pMsgContext->resDataLen = (uint32)((uint32)Dcm_Lok_nrSeedLen_u32 + 1u);

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

   for(l_idxSeed_qu32=0x0; (l_idxSeed_qu32 < Dcm_Lok_nrSeedLen_u32); l_idxSeed_qu32++)
   {

        Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].SeedBuff[l_idxSeed_qu32] = pMsgContext->resData[l_idxSeed_qu32 + 0x1u];
   }
#endif

    *OpStatus = DCM_INITIAL;
    Dcm_Lok_secaServRetValue_u8=E_OK;
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaGenSeed (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                               P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Lok_ptrSecurityConfig_p= &Dcm_Dsp_Security[Dcm_DspSecTabIdx_u8];
    Dcm_Lok_ptrSecaFnc_p = Dcm_Lok_ptrSecurityConfig_p->Dsp_GetSeed_fp;

    Dcm_Lok_dataRetGetSeed_u8 = E_NOT_OK;

    Dcm_Lok_nrSeedLen_u32  = Dcm_Lok_ptrSecurityConfig_p->Seed_size_u32;
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    Dcm_Lok_GenerateSeedAsynchClientServer(pMsgContext,dataNegRespCode_u8);
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    Dcm_Lok_GenerateSeedAsynchFnc (pMsgContext,dataNegRespCode_u8);
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

   if((Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetGetSeed_u8)  != FALSE)\
        &&((Dcm_Lok_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)))
   {
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
   }
#endif

   if(Dcm_Lok_dataRetGetSeed_u8 == E_OK)
   {
        Dcm_Lok_GetSeedReturnedWoError (&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
   }
   else if(Dcm_Lok_dataRetGetSeed_u8 == DCM_E_PENDING)
   {
        *dataNegRespCode_u8 = 0x00u;
        Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
        Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
   }
   else{
        if(*dataNegRespCode_u8 == 0x00u)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
   }
}

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_SecaUseAsyncServerCallPointForSetSecaAttptCntr(void){

   if(!Dcm_Lok_Dcm_SecaRteCallPlaced_b)
   {

        Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                                    (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                                    (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
        if(Dcm_Lok_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Lok_dataRetValue_u8 = DCM_E_PENDING;
        }
        else{

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8))
            {
                Dcm_Lok_dataRetValue_u8= E_NOT_OK;
            }
        }
   }
   else{

        Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct1)
                                    (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_Resultfp))();
        if(Dcm_Lok_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Lok_dataRetValue_u8 == RTE_E_NO_DATA)
        {
            Dcm_Lok_dataRetValue_u8 = DCM_E_PENDING;
        }
        else{
            Dcm_Lok_Dcm_SecaRteCallPlaced_b = FALSE;

            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Lok_dataRetValue_u8))
            {
                Dcm_Lok_dataRetValue_u8= E_NOT_OK;
            }
        }
   }
}
#endif
#endif

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountTrue(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA)OpStatus)
{
    Dcm_Lok_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];
   if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
        }
        else
#endif
        {

            Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
            (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
            (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
        }
   }
   if((Dcm_Lok_dataRetValue_u8 == E_OK)||(Dcm_Lok_dataRetValue_u8 == E_NOT_OK))
   {
        Dcm_Lok_flgApplFuncCall_b = FALSE;
        *OpStatus = DCM_PROCESSSERVICE;
   }
   else{
        Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
   }
}
#endif

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalseCmpKeyOk
                            (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalseCmpKeyOk (void)
#endif
{

    Dcm_Lok_dataRetValue_u8 = DcmAppl_DcmSecaValidKey((uint8)Dcm_Lok_idxSecTab_qu8);
   if((Dcm_Lok_dataRetValue_u8 == E_OK)||(Dcm_Lok_dataRetValue_u8 == E_NOT_OK))
   {
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Lok_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
            }
            else
#endif
            {

                Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
        if(DCM_E_PENDING == Dcm_Lok_dataRetValue_u8)
        {
            Dcm_Lok_flgApplFuncCall_b = TRUE;
            Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;

        }
        else{
            Dcm_Lok_flgApplFuncCall_b = FALSE;
            *OpStatus = DCM_PROCESSSERVICE;
        }
#endif
   }
   else{
        Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
   }
}

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalseCmpKeyFailed
                            (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalseCmpKeyFailed (void)
#endif
{

    Dcm_Lok_dataRetValue_u8 = DcmAppl_DcmSecaInvalidKey((uint8)Dcm_Lok_idxSecTab_qu8);
   if((Dcm_Lok_dataRetValue_u8 == E_OK)||(Dcm_Lok_dataRetValue_u8 == E_NOT_OK))
   {
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if((Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if(Dcm_Lok_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Lok_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
            }
            else
#endif
            {

                Dcm_Lok_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
                (Dcm_Lok_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
                (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
        if(DCM_E_PENDING == Dcm_Lok_dataRetValue_u8)
        {
            Dcm_Lok_flgApplFuncCall_b = TRUE;
            Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;

        }
        else{
            Dcm_Lok_flgApplFuncCall_b = FALSE;
            *OpStatus = DCM_PROCESSSERVICE;
        }
#endif
   }
   else{
        Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
   }
}

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalse
                                (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
   static FUNC(void,DCM_CODE) Dcm_Lok_SecaStoreDelayCountFalse (void)
#endif
{
   if(Dcm_Lok_stCmpKey_u8 == E_OK)
   {
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Lok_SecaStoreDelayCountFalseCmpKeyOk(OpStatus);
#else
        Dcm_Lok_SecaStoreDelayCountFalseCmpKeyOk();
#endif
   }
   if(Dcm_Lok_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
   {
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    Dcm_Lok_SecaStoreDelayCountFalseCmpKeyFailed(OpStatus);
#else
    Dcm_Lok_SecaStoreDelayCountFalseCmpKeyFailed();
#endif
   }
}

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   static FUNC(void,DCM_CODE)  Dcm_Lok_SecaPending (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
   static FUNC(void,DCM_CODE)  Dcm_Lok_SecaPending (void)
#endif
{
    Dcm_Lok_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];
   if(FALSE != Dcm_Lok_flgApplFuncCall_b)
   {
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Lok_SecaStoreDelayCountTrue(OpStatus);
#endif
   }
   else{
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Lok_SecaStoreDelayCountFalse(OpStatus);
#else
        Dcm_Lok_SecaStoreDelayCountFalse();
#endif
   }
}

   static FUNC(void,DCM_CODE) Dcm_Lok_SecaCheckData (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if(Dcm_Lok_substSeca_en == DCM_DSP_SECA_COMPAREKEY)
   {

        Dcm_Lok_SecaCmpKey(OpStatus,pMsgContext,dataNegRespCode_u8);
   }

   if(Dcm_Lok_substSeca_en == DCM_DSP_SECA_GENSEED)
   {

        Dcm_Lok_SecaGenSeed(pMsgContext,dataNegRespCode_u8);
   }

   if(Dcm_Lok_substSeca_en == DCM_DSP_SECA_PENDING)
   {

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Lok_SecaPending(OpStatus);
#else
        Dcm_Lok_SecaPending();
#endif
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaProcessStCmpKeyOk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
{
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

   VAR(uint32,AUTOMATIC)  l_idxSeed_qu32;
#endif

    *OpStatus = DCM_INITIAL;

    Dcm_DspChgSecLevel_b = TRUE;
    Dcm_Lok_secaServRetValue_u8=E_OK;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

   for(l_idxSeed_qu32=0x0; (l_idxSeed_qu32 < Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8].Seed_size_u32); l_idxSeed_qu32++)
   {

        Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].SeedBuff[l_idxSeed_qu32] = 0x0;
   }
#endif
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaProcessStCmpKeyFailed
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Lok_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Lok_idxSecTab_qu8];
    *dataNegRespCode_u8 = DCM_E_INVALIDKEY;

   if((Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8) < Dcm_Lok_ptrSecurityConfig_p->NumAttDelay_u8)
   {
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY;
   }
   if((Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8) >= Dcm_Lok_ptrSecurityConfig_p->NumAttDelay_u8)
   {

        if(Dcm_Lok_ptrSecurityConfig_p->DelayTime_u32 > 0x00u)
        {
            Dcm_Lok_nrDelay_u32 = ((Dcm_Lok_ptrSecurityConfig_p->DelayTime_u32) * DCM_CFG_TASK_TIME_MS);

            Dcm_Lok_nrDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Lok_ptrSecurityConfig_p->Security_level_u8
   ,     Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8,Dcm_Lok_nrDelay_u32);
            Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].Residual_delay_u32 =
            (Dcm_Dsp_SecaGlobaltimer_u32 + (Dcm_Lok_nrDelay_u32 / DCM_CFG_TASK_TIME_MS));
        }
        else{

            Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].Residual_delay_u32 = 0x00u;
        }
#if(DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT != DCM_CFG_OFF)
        *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
#else
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY;
#endif
   }

   if(Dcm_Lok_ptrSecurityConfig_p->NumAttLock_u8 > 0)
   {

        if(Dcm_Dsp_Seca[Dcm_Lok_idxSecTab_qu8].FailedAtm_cnt_u8 == Dcm_Lok_ptrSecurityConfig_p->NumAttLock_u8)
        {

            DcmAppl_DcmSecurityLevelLocked((uint8)Dcm_Lok_idxSecTab_qu8);
            *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaProcesStCmpKeyNotOk
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(*dataNegRespCode_u8 == 0x00u)
   {

        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
   else{

   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaProcessService
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   if(Dcm_Lok_stCmpKey_u8 == E_OK)
   {
        Dcm_Lok_SecaProcessStCmpKeyOk(&Dcm_SrvOpstatus_u8);
   }
   else if(Dcm_Lok_stCmpKey_u8 == E_NOT_OK)
   {
        Dcm_Lok_SecaProcesStCmpKeyNotOk(dataNegRespCode_u8);
   }
   else if(Dcm_Lok_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
   {
        Dcm_Lok_SecaProcessStCmpKeyFailed(dataNegRespCode_u8);
   }
   else{
        Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaStateProcessing (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if((*OpStatus)==(DCM_INITIAL))
   {
        Dcm_Lok_SecaRequestState(pMsgContext,dataNegRespCode_u8);
   }

   if((*OpStatus)==(DCM_CHECKDATA))
   {
        Dcm_Lok_SecaCheckData(OpStatus,pMsgContext,dataNegRespCode_u8);
   }

   if((*OpStatus)==(DCM_PROCESSSERVICE))
   {
        Dcm_Lok_SecaProcessService(dataNegRespCode_u8);
   }
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tSecurityAccess (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,\
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,AUTOMATIC)     localdataServRetValue_u8;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    Dcm_Lok_stBuffer_b = FALSE;
#endif
    *dataNegRespCode_u8  = 0x0;
    Dcm_Lok_substSeca_en = Dcm_DspSecaStatus_en;
    Dcm_Lok_dataRetValue_u8 =E_OK;
    localdataServRetValue_u8 = DCM_E_PENDING;
    Dcm_Lok_secaServRetValue_u8=DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_SecaIni();

        Dcm_Lok_secaServRetValue_u8 = E_OK;
   }
   else{
        Dcm_Lok_SecaStateProcessing(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);

        if(*dataNegRespCode_u8 != 0x0u)
        {

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;

            Dcm_DspSecAccType_u8 = 0x0;
            Dcm_DspSecTabIdx_u8  = 0x0;
            Dcm_Lok_secaServRetValue_u8=E_NOT_OK;
        }

        Dcm_DspSecaStatus_en = Dcm_Lok_substSeca_en;
   }

    localdataServRetValue_u8 = Dcm_Lok_secaServRetValue_u8;
    return localdataServRetValue_u8;
}

FUNC(void,DCM_CODE) Dcm_ResetAccessType (void){
    Dcm_DspSecAccType_u8=0;
}

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

FUNC (void,DCM_CODE) Dcm_Dsp_SecaClearSeed (void){
   VAR (uint8_least,AUTOMATIC) idxSecTab_qu8;
   VAR (uint32,AUTOMATIC) SeedIdx_u32;
   VAR (uint32,AUTOMATIC) Seedlen_u32;
   for(idxSecTab_qu8=0;idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY; idxSecTab_qu8++)
   {

        Seedlen_u32 = Dcm_Dsp_Security[idxSecTab_qu8].Seed_size_u32;

        for(SeedIdx_u32=0x0; (SeedIdx_u32 < Seedlen_u32); SeedIdx_u32++)
        {

            Dcm_Dsp_Seca[idxSecTab_qu8].SeedBuff[SeedIdx_u32] = 0x0;
        }
   }
}

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

