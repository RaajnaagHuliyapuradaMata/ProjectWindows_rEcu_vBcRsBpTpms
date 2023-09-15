

#ifndef DCMDSPUDS_SECA_PRV_H
#define DCMDSPUDS_SECA_PRV_H

#include "DcmDspUds_Seca_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))

#define CK_CallAsyncAppl 0x00u
#define CK_CallDcmAppl 0x01u
#define CK_CallSetAttemptCounter 0x02u
#define DCM_FAILEDATMCOUNTER_MAXVALUE 0xFFu

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static Std_ReturnType s_CompareKeyStatus_u8;
static uint8 CompareKey_StateMachine_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static boolean s_Dcm_SecaRteCallPlaced_b; // For ASCP handling of Rte_Read and Rte_Result call
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
extern uint8 Dcm_GetattemptCounterWaitCycle_u8;
#endif
extern uint8 Dcm_DspSecTabIdx_u8;
extern Dcm_SecLevelType  Dcm_dataSecLevel_u8;
extern uint8 Dcm_DspSecAccType_u8;
extern Dcm_OpStatusType Dcm_DspSecaOpStatus_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern boolean Dcm_DspChgSecLevel_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern void Dcm_Lok_DspSecurityConfirmation(
        Dcm_IdContextType dataIdContext_u8,        PduIdType dataRxPduId_u8
   ,       uint16 dataSourceAddress_u16,Dcm_ConfirmationStatusType status_u8);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define Dcm_Lok_CompareKeyActive()    ((CompareKey_StateMachine_u8 == CK_CallAsyncAppl)?TRUE:FALSE)
#define Dcm_Lok_ResetCKStateMachine() (CompareKey_StateMachine_u8 = CK_CallAsyncAppl)

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
LOCAL_INLINE void Dcm_Lok_HasWaitCounterCycleExhausted(Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    *dataNegRespCode_u8 = 0x00;
   if(Dcm_GetattemptCounterWaitCycle_u8 <= DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
   {
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
}
#endif

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_IsSeedAlreadyStored(const uint32 nrSeedLen_u32,const uint8 SecTabIdx_u8)
{
   boolean Flag = FALSE;
   uint32 idxSeed_u32;

   for(idxSeed_u32 =0; (idxSeed_u32 < nrSeedLen_u32); idxSeed_u32++)
   {

        if(Dcm_Dsp_Seca[SecTabIdx_u8].SeedBuff[idxSeed_u32] != 0x00u)
        {

            Flag = TRUE;
            break;
        }
   }
    return Flag;
}

LOCAL_INLINE void Dcm_Lok_StoreSeed(const uint32 SeedLength_u32,const Dcm_MsgContextType* pMsgContext)
{
   uint32 idxSeed_u32;

   for(idxSeed_u32=0x00; (idxSeed_u32 < SeedLength_u32); idxSeed_u32++)
   {

        Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].SeedBuff[idxSeed_u32] = pMsgContext->resData[idxSeed_u32 + 0x1u];
   }
}

LOCAL_INLINE void Dcm_Lok_UpdateBufferWithStoredSeed(Dcm_MsgContextType* pMsgContext,const uint32 SeedLength_u32
   ,                                                    const uint8 SecTabIdx_u8)
{
   uint32 idxSeed_u32;
   for(idxSeed_u32 =0; (idxSeed_u32 < SeedLength_u32); idxSeed_u32++)
   {

        pMsgContext->resData[idxSeed_u32 + 0x1u] = Dcm_Dsp_Seca[SecTabIdx_u8].SeedBuff[idxSeed_u32];
   }

    pMsgContext->resData[0] = pMsgContext->reqData[0];

    pMsgContext->resDataLen = (Dcm_MsgLenType)(idxSeed_u32 + 1u);
}

#endif

#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

LOCAL_INLINE void Dcm_Lok_StoreSecurityAddressRecord(const Dcm_MsgContextType* pMsgContext
   ,                                                    const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst)
{
   if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 != 0x00u)
   {

        DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]),&(pMsgContext->reqData[1]),Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32);
   }
}
#endif

LOCAL_INLINE void Dcm_Lok_UpdateSeedResponseForActiveSec(Dcm_MsgContextType* pMsgContext,uint32 SeedSize_u32)
{
   uint32 idxSeedCounter;
    // Store SubFunction
    pMsgContext->resData[0] = Dcm_DspSecAccType_u8;
    // Update Seed Response to zeros
   for(idxSeedCounter = 0x01u; idxSeedCounter <= SeedSize_u32;idxSeedCounter++)
   {
        pMsgContext->resData[idxSeedCounter] = 0x00u;
   }
    pMsgContext->resDataLen = idxSeedCounter;
}

#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_CheckLengthReturned(uint32 SeedLength_u32,const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_OK;
   if(SeedLength_u32 > Dcm_ptrSecurityConfig_pcst->Seed_size_u32)
   {
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        DCM_DET_ERROR(DCM_SECURITYACCESS_ID,DCM_E_INTERFACE_BUFFER_OVERFLOW);
        ReturnVal_u8 = E_NOT_OK;
   }
    return ReturnVal_u8;
}

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_AsyncFncForFlexibleSeedApl(uint32* SeedLength_u32,const Dcm_MsgContextType* pMsgContext
   ,                                                      const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                      Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_NOT_OK;
   if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 != 0x00u)
   {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr8)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(
                Dcm_dataSecLevel_u8
   ,               SeedLength_u32
   ,               Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32
   ,               &(Dcm_InParameterBuf_au8[0])
   ,               &(pMsgContext->resData[1])
   ,               Dcm_DspSecaOpStatus_u8
   ,               dataNegRespCode_u8);
#endif
   }
   else{

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr8)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(
                Dcm_dataSecLevel_u8
   ,               SeedLength_u32
   ,               Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32
   ,               NULL_PTR
   ,               &(pMsgContext->resData[1])
   ,               Dcm_DspSecaOpStatus_u8
   ,               dataNegRespCode_u8);
   }
    return ReturnVal_u8;
}
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_SSCPForFlexibleSeedApl(uint32* SeedLength_u32,const Dcm_MsgContextType* pMsgContext
   ,                          const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_NOT_OK;
   if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 !=0u)
   {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr1)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(SeedLength_u32
   ,                    &(Dcm_InParameterBuf_au8[0]),Dcm_DspSecaOpStatus_u8,&(pMsgContext->resData[1]),dataNegRespCode_u8);
#endif
   }
   else{

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr9)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(SeedLength_u32,Dcm_DspSecaOpStatus_u8
   ,                        &(pMsgContext->resData[1]),dataNegRespCode_u8);
   }
    return ReturnVal_u8;
}

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_ASCPForFlexibleSeedApl(uint32* SeedLength_u32,const Dcm_MsgContextType* pMsgContext
   ,                          const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType AplReturnval_u8 = RTE_E_TIMEOUT;

   if(!s_Dcm_SecaRteCallPlaced_b)
   {
        if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 != 0x00u)
        {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

            AplReturnval_u8 = (*(Dcm_GetSeed_ptr10)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(*SeedLength_u32
   ,                                                                 &(Dcm_InParameterBuf_au8[0]),Dcm_DspSecaOpStatus_u8);
#endif
        }
        else{

            AplReturnval_u8 = (*(Dcm_GetSeed_ptr11)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(*SeedLength_u32,Dcm_DspSecaOpStatus_u8);
        }

        if(AplReturnval_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = TRUE;
            AplReturnval_u8 = DCM_E_PENDING;
        }
   }
   else{

        AplReturnval_u8 = (*(Dcm_GetSeed_ptr12)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_ResultFp))
                                              (SeedLength_u32,&(pMsgContext->resData[1]),dataNegRespCode_u8);
        if(AplReturnval_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(AplReturnval_u8 == RTE_E_NO_DATA)
        {
            AplReturnval_u8 = DCM_E_PENDING;
        }
        else{
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
   }
    return AplReturnval_u8;
}

#endif
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_CallSeedApplicationForFlexibleLength(uint32* SeedLength_u32
   ,                                                       Dcm_MsgContextType* pMsgContext
   ,                                                       const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_NOT_OK;
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->UseAsynchronousServerCallPoint_b)
        {
            ReturnVal_u8 = Dcm_Lok_ASCPForFlexibleSeedApl(SeedLength_u32,pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        else
#endif
        {
            ReturnVal_u8 = Dcm_Lok_SSCPForFlexibleSeedApl(SeedLength_u32,pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        if(FALSE != Dcm_IsInfrastructureErrorPresent_b(ReturnVal_u8))
        {
            ReturnVal_u8 = E_NOT_OK;
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
   }
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_FNC)
   {
        ReturnVal_u8 = Dcm_Lok_AsyncFncForFlexibleSeedApl(SeedLength_u32,pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
   }
#endif

    // Verify whether the seed length returned is within limits
   if(ReturnVal_u8 == E_OK)
   {
        ReturnVal_u8 = Dcm_Lok_CheckLengthReturned(*SeedLength_u32,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
   }
    return ReturnVal_u8;
}

#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_AsyncFncForSeedApl(const Dcm_MsgContextType* pMsgContext
   ,                                                      const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                      Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_NOT_OK;
   uint32 nrSeedLen_u32 = Dcm_ptrSecurityConfig_pcst->Seed_size_u32;

   if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 != 0x00u)
   {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(
                Dcm_dataSecLevel_u8
   ,               nrSeedLen_u32
   ,               Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32
   ,               &(Dcm_InParameterBuf_au8[0])
   ,               &(pMsgContext->resData[1])
   ,               Dcm_DspSecaOpStatus_u8
   ,               dataNegRespCode_u8);
#endif
   }
   else{

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(
                Dcm_dataSecLevel_u8
   ,               nrSeedLen_u32
   ,               Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32
   ,               NULL_PTR
   ,               &(pMsgContext->resData[1])
   ,               Dcm_DspSecaOpStatus_u8
   ,               dataNegRespCode_u8);
   }
    return ReturnVal_u8;
}
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_SSCPForSeedApl(const Dcm_MsgContextType* pMsgContext
   ,                         const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                         Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8=E_NOT_OK;
   if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32 != 0u )
   {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(&(Dcm_InParameterBuf_au8[0])
   ,               Dcm_DspSecaOpStatus_u8,&(pMsgContext->resData[1]),dataNegRespCode_u8);
#endif
   }
   else{

        ReturnVal_u8 = (*(Dcm_GetSeed_ptr3)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(Dcm_DspSecaOpStatus_u8
   ,               &(pMsgContext->resData[1]),dataNegRespCode_u8);
   }
    return ReturnVal_u8;
}
#endif

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_ASCPForSeedApl(const Dcm_MsgContextType* pMsgContext
   ,       const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType AplReturnval_u8 = RTE_E_TIMEOUT;

   if(!s_Dcm_SecaRteCallPlaced_b)
   {
        if(Dcm_ptrSecurityConfig_pcst->AccDataRecsize_u32!=0u)
        {
#if(DCM_CFG_IN_PARAM_MAXLEN >0u)

            AplReturnval_u8 = (*(Dcm_GetSeed_ptr5)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(&(Dcm_InParameterBuf_au8[0]),Dcm_DspSecaOpStatus_u8);
#endif
        }
        else{

            AplReturnval_u8 = (*(Dcm_GetSeed_ptr6)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_fp))(Dcm_DspSecaOpStatus_u8);
        }

        if(AplReturnval_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = TRUE;
            AplReturnval_u8 = DCM_E_PENDING;
        }
   }
   else{

        AplReturnval_u8 = (*(Dcm_GetSeed_ptr7)(Dcm_ptrSecurityConfig_pcst->Dsp_GetSeed_ResultFp))(&(pMsgContext->resData[1]),dataNegRespCode_u8);
        if(AplReturnval_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(AplReturnval_u8 == RTE_E_NO_DATA)
        {
            AplReturnval_u8 = DCM_E_PENDING;
        }
        else{
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
   }
    return AplReturnval_u8;
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_CallSeedApplication(const Dcm_MsgContextType* pMsgContext
   ,                                                       const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ReturnVal_u8 = E_NOT_OK;
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->UseAsynchronousServerCallPoint_b)
        {
            ReturnVal_u8 = Dcm_Lok_ASCPForSeedApl(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        else
#endif
        {
            ReturnVal_u8 = Dcm_Lok_SSCPForSeedApl(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        if(FALSE != Dcm_IsInfrastructureErrorPresent_b(ReturnVal_u8))
        {
            ReturnVal_u8 = E_NOT_OK;
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
   }
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_FNC)
   {
        ReturnVal_u8 = Dcm_Lok_AsyncFncForSeedApl(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
   }
#endif
    return ReturnVal_u8;
}

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_SetAttemptCounterASP(const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst)
{
    Std_ReturnType dataRetValue_u8 = E_NOT_OK;
   if(!s_Dcm_SecaRteCallPlaced_b)
   {

        dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)(Dcm_ptrSecurityConfig_pcst->Dsp_SetAttempCounter_fp))
                                    (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].FailedAtm_cnt_u8);

        if(dataRetValue_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = TRUE;
            dataRetValue_u8 = DCM_E_PENDING;
        }
   }
   else{

        dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct1)(Dcm_ptrSecurityConfig_pcst->Dsp_SetAttempCounter_Resultfp))();
        if(dataRetValue_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(dataRetValue_u8 == RTE_E_NO_DATA)
        {
            dataRetValue_u8 = DCM_E_PENDING;
        }
        else{
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
   }
    return dataRetValue_u8;
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_SetAttemptCounter(const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst,

                                                      Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ApplReturn_u8 = E_OK;
   if(Dcm_ptrSecurityConfig_pcst->Dsp_SetAttempCounter_fp != NULL_PTR)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->UseAsynchronousServerCallPoint_b)
        {
            ApplReturn_u8 = Dcm_Lok_SetAttemptCounterASP(Dcm_ptrSecurityConfig_pcst);
        }
        else
#endif
        {

            ApplReturn_u8 = (*(Dcm_SetSecurityAttemptCounter_pfct)(Dcm_ptrSecurityConfig_pcst->Dsp_SetAttempCounter_fp))
              (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].FailedAtm_cnt_u8);
        }
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_CLIENT_SERVER)
        {
            if(FALSE != Dcm_IsInfrastructureErrorPresent_b(ApplReturn_u8))
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                ApplReturn_u8= E_NOT_OK;
            }
        }
#endif
   }
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER == DCM_CFG_OFF)
    (void)dataNegRespCode_u8;
#endif
    return ApplReturn_u8;
}

#endif

#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE void Dcm_Lok_ASCPForKeyApplFlexibleLen(const Dcm_MsgContextType* pMsgContext
   ,       const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

   if(!s_Dcm_SecaRteCallPlaced_b)
   {

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr6)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))
                ((pMsgContext->reqDataLen-1u),&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8);

        if(s_CompareKeyStatus_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = TRUE;
            s_CompareKeyStatus_u8 = DCM_E_PENDING;
        }
   }
   else{

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr5)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_ResultFp))(dataNegRespCode_u8);
        if((s_CompareKeyStatus_u8 == RTE_E_OK) || (s_CompareKeyStatus_u8 == DCM_E_COMPARE_KEY_FAILED))
        {
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(s_CompareKeyStatus_u8 == RTE_E_NO_DATA)
        {
            s_CompareKeyStatus_u8 = DCM_E_PENDING;
        }
        else{
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
   }
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_CompareKeyApplForFlexibleLen(const Dcm_MsgContextType* pMsgContext
   ,                                                                const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                                Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_ASCPForKeyApplFlexibleLen(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        else
#endif
        {

            s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr3)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))
                    ((pMsgContext->reqDataLen-1u),&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
        }

        if(FALSE != Dcm_IsInfrastructureErrorPresent_b(s_CompareKeyStatus_u8))
        {
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            s_CompareKeyStatus_u8= E_NOT_OK;
        }
   }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_FNC)
   {

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr3)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))
                ((pMsgContext->reqDataLen-1u),&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
   }
#endif

   if(s_CompareKeyStatus_u8 != DCM_E_PENDING)
   {
        CompareKey_StateMachine_u8 = CK_CallDcmAppl;
   }
    return s_CompareKeyStatus_u8 ;
}
#endif

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE void Dcm_Lok_ASCPForKeyAppl(const Dcm_MsgContextType* pMsgContext
   ,       const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,       Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{

   if(!s_Dcm_SecaRteCallPlaced_b)
   {

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr4)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))(&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8);

        if(s_CompareKeyStatus_u8 == RTE_E_OK)
        {
            s_Dcm_SecaRteCallPlaced_b = TRUE;
            s_CompareKeyStatus_u8 = DCM_E_PENDING;
        }
   }
   else{

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr5)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_ResultFp))(dataNegRespCode_u8);
        if((s_CompareKeyStatus_u8 == RTE_E_OK) || (s_CompareKeyStatus_u8 == DCM_E_COMPARE_KEY_FAILED))
        {
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(s_CompareKeyStatus_u8 == RTE_E_NO_DATA)
        {
            s_CompareKeyStatus_u8 = DCM_E_PENDING;
        }
        else{
            s_Dcm_SecaRteCallPlaced_b = FALSE;
        }
   }
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_CompareKeyAppl(const Dcm_MsgContextType* pMsgContext
   ,                                                  const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                  Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_CLIENT_SERVER)
   {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if(Dcm_ptrSecurityConfig_pcst->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Lok_ASCPForKeyAppl(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        else
#endif
        {

            s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr1)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))
                                    (&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
        }

        if(FALSE != Dcm_IsInfrastructureErrorPresent_b(s_CompareKeyStatus_u8))
        {
            * dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            s_CompareKeyStatus_u8= E_NOT_OK;
        }
   }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
   if(Dcm_ptrSecurityConfig_pcst->usePort == USE_ASYNCH_FNC)
   {

        s_CompareKeyStatus_u8 = (*(Dcm_CompareKey_ptr3)(Dcm_ptrSecurityConfig_pcst->Dsp_CompareKey_fp))
        (Dcm_ptrSecurityConfig_pcst->Key_size_u32,&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
   }
#endif

   if(s_CompareKeyStatus_u8 != DCM_E_PENDING)
   {
        CompareKey_StateMachine_u8 = CK_CallDcmAppl;
   }
    return s_CompareKeyStatus_u8 ;
}

LOCAL_INLINE void Dcm_Lok_ProcessKeyResult(Dcm_MsgContextType* pMsgContext)
{
   if(s_CompareKeyStatus_u8 == E_OK)
   {
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

        Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].FailedAtm_cnt_u8 = 0x00u;

        pMsgContext->resData[0] = (Dcm_DspSecAccType_u8+1u);
        pMsgContext->resDataLen = 0x1u;
   }
   else if(s_CompareKeyStatus_u8 == DCM_E_COMPARE_KEY_FAILED )
   {
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
        if(Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].FailedAtm_cnt_u8 < DCM_FAILEDATMCOUNTER_MAXVALUE)
        {

            Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].FailedAtm_cnt_u8++;
        }
   }
   else if(s_CompareKeyStatus_u8 == DCM_E_PENDING)
   {
        Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
   }
   else{
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
   }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_ProcessCompKeySM(Dcm_MsgContextType* pMsgContext
   ,                                                    const Dcm_Dsp_Security_t* Dcm_ptrSecurityConfig_pcst
   ,                                                    Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType ApplReturn_u8 = E_NOT_OK;

   if(CompareKey_StateMachine_u8 == CK_CallAsyncAppl)
   {
#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)
        if(TRUE == Dcm_ptrSecurityConfig_pcst->UseFlexibleLength)
        {
            ApplReturn_u8 = Dcm_Lok_CompareKeyApplForFlexibleLen(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }
        else
#endif
        {
            ApplReturn_u8 = Dcm_Lok_CompareKeyAppl(pMsgContext,Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
        }

        Dcm_Lok_ProcessKeyResult(pMsgContext);
   }
   if(CompareKey_StateMachine_u8 == CK_CallDcmAppl)
   {

        ApplReturn_u8 = (s_CompareKeyStatus_u8 == E_OK)?
                        DcmAppl_DcmSecaValidKey((uint8)Dcm_DspSecTabIdx_u8):
                        DcmAppl_DcmSecaInvalidKey((uint8)Dcm_DspSecTabIdx_u8);
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if(ApplReturn_u8 != DCM_E_PENDING)
        {
            ApplReturn_u8 = E_OK;
            CompareKey_StateMachine_u8 = CK_CallSetAttemptCounter;
        }
#endif
   }
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
   if(CompareKey_StateMachine_u8 == CK_CallSetAttemptCounter)
   {
        if((s_CompareKeyStatus_u8 == E_OK) || (s_CompareKeyStatus_u8 == DCM_E_COMPARE_KEY_FAILED))
        {
            ApplReturn_u8 = Dcm_Lok_SetAttemptCounter(Dcm_ptrSecurityConfig_pcst,dataNegRespCode_u8);
            if(ApplReturn_u8 != DCM_E_PENDING)
            {
                ApplReturn_u8 = E_OK;
            }
        }
   }
#endif

   if(ApplReturn_u8 != DCM_E_PENDING)
   {
        CompareKey_StateMachine_u8 = CK_CallAsyncAppl;
        ApplReturn_u8 = (ApplReturn_u8 >s_CompareKeyStatus_u8)?ApplReturn_u8:s_CompareKeyStatus_u8;
   }
    return ApplReturn_u8;
}

#endif
#endif
