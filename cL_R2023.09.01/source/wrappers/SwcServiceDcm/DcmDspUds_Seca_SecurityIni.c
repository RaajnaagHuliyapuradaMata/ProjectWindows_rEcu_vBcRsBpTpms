
#include "DcmDspUds_Seca_Inf.hpp"
#include "Rte_Dcm.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Prv.hpp"

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

Dcm_Dsp_SecaType Dcm_Dsp_Seca[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_DspChgSecLevel_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
Dcm_OpStatusType Dcm_DspSecaOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)

static void Dcm_Lok_SecaIniForFlexibleLen(const Dcm_Dsp_Security_t* ptrSecurityConfig
   ,                                         Dcm_NegativeResponseCodeType dataNegRespCode_u8)
{
   void * ptrSecaFnc;
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    Dcm_SecLevelType   dataSecLevel_u8;
#endif
   if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
   {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
        ptrSecaFnc = ptrSecurityConfig->Dsp_GetSeed_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
        if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

            if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
            {

                if(ptrSecurityConfig->AccDataRecsize_u32!=0x00u)
                   {

                       (void)(*(Dcm_GetSeed_ptr10)(ptrSecaFnc))(0x00u,NULL_PTR,DCM_CANCEL);
                   }
                   else
                   {

                       (void)(*(Dcm_GetSeed_ptr11)(ptrSecaFnc))(0x00u,DCM_CANCEL);
                   }
            }
            else
#endif
            {
                if(ptrSecurityConfig->AccDataRecsize_u32!=0x00u)
                {

                    (void)(*(Dcm_GetSeed_ptr1)(ptrSecaFnc))(NULL_PTR,NULL_PTR,DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
                }
                else{

                    (void)(*(Dcm_GetSeed_ptr9)(ptrSecaFnc))(NULL_PTR,DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
                }
            }
            (void)dataNegRespCode_u8;
        }
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
        if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
        {

            dataSecLevel_u8  = ((Dcm_DspSecAccType_u8+1u)>>1u);

            (void)(*(Dcm_GetSeed_ptr8)(ptrSecaFnc))(
                                        dataSecLevel_u8
   ,                                       NULL_PTR
   ,                                       ptrSecurityConfig->AccDataRecsize_u32
   ,                                       NULL_PTR,NULL_PTR,DCM_CANCEL,&dataNegRespCode_u8);
            (void)dataNegRespCode_u8;
        }
#endif
   }
   if((Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE) && (FALSE != Dcm_Lok_CompareKeyActive()))
   {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
        ptrSecaFnc = ptrSecurityConfig->Dsp_CompareKey_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
        if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

            if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
            {

                (void)(*(Dcm_CompareKey_ptr6)(ptrSecaFnc))(0x00u,NULL_PTR, DCM_CANCEL);
            }
            else
#endif
            {

                (void)(*(Dcm_CompareKey_ptr3)(ptrSecaFnc))(0x00u,NULL_PTR, DCM_CANCEL,&dataNegRespCode_u8);
            }
        }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
        if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
        {

            (void)(*(Dcm_CompareKey_ptr3)(ptrSecaFnc))(ptrSecurityConfig->Key_size_u32,NULL_PTR
   ,           DCM_CANCEL,&dataNegRespCode_u8);
        }
#endif
   }
}
#endif

void Dcm_Dsp_SecaIni (void){

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
   void * ptrSecaFnc;
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    Dcm_SecLevelType dataSecLevel_u8;
#endif
   const Dcm_Dsp_Security_t * ptrSecurityConfig;
    Dcm_NegativeResponseCodeType dataNegRespCode_u8;
#endif

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)|| (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    dataNegRespCode_u8 = 0x0;
#endif

   if(Dcm_DspSecaOpStatus_u8 == DCM_PENDING)
   {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
        ptrSecurityConfig =&Dcm_Dsp_Security[Dcm_DspSecTabIdx_u8];
#endif
#if(DCM_CFG_DSP_SECA_USEFLEXIBLELENGTH != DCM_CFG_OFF)
        if(ptrSecurityConfig->UseFlexibleLength)
        {
            Dcm_Lok_SecaIniForFlexibleLen(ptrSecurityConfig,dataNegRespCode_u8);
        }
        else
#endif
        {
            if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
            {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
                ptrSecaFnc = ptrSecurityConfig->Dsp_GetSeed_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
                if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
                {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

                    if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
                    {

                        if(ptrSecurityConfig->AccDataRecsize_u32!=0x00u)
                           {

                               (void)(*(Dcm_GetSeed_ptr5)(ptrSecaFnc))(NULL_PTR,DCM_CANCEL);
                           }
                           else
                           {

                               (void)(*(Dcm_GetSeed_ptr6)(ptrSecaFnc))(DCM_CANCEL);
                           }
                    }
                    else
#endif
                    {
                        if(ptrSecurityConfig->AccDataRecsize_u32!=0x00u)
                        {

                            (void)(*(Dcm_GetSeed_ptr)(ptrSecaFnc))(NULL_PTR,DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
                        }
                        else
                        {

                            (void)(*(Dcm_GetSeed_ptr3)(ptrSecaFnc))(DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
                        }
                    }
                    (void)dataNegRespCode_u8;
                }
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
                if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
                {

                    dataSecLevel_u8  = ((Dcm_DspSecAccType_u8+1u)>>1u);

                    (void)(*(Dcm_GetSeed_ptr4)(ptrSecaFnc))(
                                                dataSecLevel_u8
   ,                                               ptrSecurityConfig->Seed_size_u32
   ,                                               ptrSecurityConfig->AccDataRecsize_u32
   ,                                               NULL_PTR,NULL_PTR,DCM_CANCEL,&dataNegRespCode_u8);
                    (void)dataNegRespCode_u8;
                }
#endif
            }
            if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
            {
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
                ptrSecaFnc = ptrSecurityConfig->Dsp_CompareKey_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
                if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
                {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

                    if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
                    {

                        (void)(*(Dcm_CompareKey_ptr4)(ptrSecaFnc))(NULL_PTR, DCM_CANCEL);
                    }
                    else
#endif
                    {

                        (void)(*(Dcm_CompareKey_ptr1)(ptrSecaFnc))(NULL_PTR, DCM_CANCEL,&dataNegRespCode_u8);
                    }
                }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
                if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
                {

                    (void)(*(Dcm_CompareKey_ptr3)(ptrSecaFnc))(ptrSecurityConfig->Key_size_u32,NULL_PTR
   ,                   DCM_CANCEL,&dataNegRespCode_u8);
                }
#endif
            }
        }
   }

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
    Dcm_ResetAsynchSecaFlag();
#endif

    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    // Reset Compare Key StateMachine
    Dcm_Lok_ResetCKStateMachine();

    Dcm_Dsp_SecaSessIni();
}

void Dcm_Dsp_SecaPowerOnDelayIni (void){
   uint8_least idxSecTab_qu8;
   uint32 dataDelayOnPowerOn_u32;

   for(idxSecTab_qu8=0;idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY;idxSecTab_qu8++)
   {
        if(Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8 >= Dcm_Dsp_Security[idxSecTab_qu8].NumAttDelay_u8)
        {
            dataDelayOnPowerOn_u32 =
            (Dcm_Dsp_Security[idxSecTab_qu8].DelayTime_u32 > Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32) ?
            Dcm_Dsp_Security[idxSecTab_qu8].DelayTime_u32 : Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32;
            if(dataDelayOnPowerOn_u32 > 0x00u)
            {
                dataDelayOnPowerOn_u32 = dataDelayOnPowerOn_u32 * DCM_CFG_TASK_TIME_MS;

                dataDelayOnPowerOn_u32 =
                DcmAppl_DcmGetUpdatedDelayTime(Dcm_Dsp_Security[idxSecTab_qu8].Security_level_u8
   ,               Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8,dataDelayOnPowerOn_u32);
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 =
                (Dcm_Dsp_SecaGlobaltimer_u32 + (dataDelayOnPowerOn_u32 / DCM_CFG_TASK_TIME_MS));
            }
            else{

                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = 0x00u;
            }
        }
        else{
            if(Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32 > 0x00u)
            {
                dataDelayOnPowerOn_u32 =
                DcmAppl_DcmGetUpdatedDelayForPowerOn(Dcm_Dsp_Security[idxSecTab_qu8].Security_level_u8
   ,               Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8
   ,               (Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32 * DCM_CFG_TASK_TIME_MS));
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = (dataDelayOnPowerOn_u32/DCM_CFG_TASK_TIME_MS);
            }
            else{
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = 0x00u;
            }
        }
   }
    return;
}

void Dcm_Dsp_SecaSessIni (void){

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    //Dcm_DspSecaStatus_en = DCM_DSP_SECA_REQUEST;

    Dcm_DspChgSecLevel_b = FALSE;

    Dcm_DspSecAccType_u8 = 0x0;

    Dcm_DspSecTabIdx_u8  = 0x0;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
