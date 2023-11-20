#include "Std_Types.hpp"

#include "DcmDspUds_Seca_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
#include "DcmDspUds_Seca_Prv.hpp"

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8,AUTOMATIC) Dcm_GetattemptCounterWaitCycle_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static VAR(boolean,AUTOMATIC) waitRequested_b;

static VAR(uint8,AUTOMATIC) waitRequestedIdx_qu8[DCM_CFG_DSP_NUMSECURITY];
static VAR(Std_ReturnType,AUTOMATIC)     dataRetValue_u8;
static VAR(uint8,AUTOMATIC) attemptCounter_u8;

static FUNC(void,DCM_CODE) Dcm_Lok_SecaGetattemptCounterCheck(void){

   if(waitRequested_b != FALSE)
   {
        Dcm_GetattemptCounterWaitCycle_u8++ ;
   }
   else{

   	Dcm_Dsp_SecaPowerOnDelayIni();

   	Dcm_GetattemptCounterWaitCycle_u8 = ((DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)+1u);
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_GetattemptCounterWaitCycleExhaused(void){
   VAR(uint8_least,AUTOMATIC) l_idxSeca_qu8;  

   for(l_idxSeca_qu8 = 0x0; l_idxSeca_qu8 < DCM_CFG_DSP_NUMSECURITY; l_idxSeca_qu8++)
   {
        if((Dcm_Dsp_Security[l_idxSeca_qu8].Dsp_GetAttempCounter_fp!=NULL_PTR)&&
   	(waitRequestedIdx_qu8[l_idxSeca_qu8] != 0))
        {
            Dcm_Dsp_Seca[l_idxSeca_qu8].FailedAtm_cnt_u8 = Dcm_Dsp_Security[l_idxSeca_qu8].NumAttDelay_u8;
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if(Dcm_Dsp_Security[l_idxSeca_qu8].UseAsynchronousServerCallPoint_b)
            {

                dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter1_pfct)
   			(Dcm_Dsp_Security[l_idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_CANCEL);
            }
            else
#endif
            {

                dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter_pfct)
   			(Dcm_Dsp_Security[l_idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_CANCEL,&attemptCounter_u8);
            }
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SecaDelayCountRead(void){
   static  VAR(uint8_least,AUTOMATIC) idxSeca_qu8;  

   for(idxSeca_qu8 = 0x0; idxSeca_qu8 < DCM_CFG_DSP_NUMSECURITY; idxSeca_qu8++)
   {
        if(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_fp!=NULL_PTR)
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if(Dcm_Dsp_Security[idxSeca_qu8].UseAsynchronousServerCallPoint_b)
            {
                if(waitRequestedIdx_qu8[idxSeca_qu8] != 0)
                {

   				dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter1_pfct)
   				(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_PENDING);
                }
                else{

   				dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter1_pfct)
   				(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_INITIAL);
                }
                if(dataRetValue_u8 == E_OK)
                {

                    dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter2_pfct)
   				(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_Resultfp))(&attemptCounter_u8);
                }
            }
            else
#endif
            {
                if(waitRequestedIdx_qu8[idxSeca_qu8] != 0)
                {

                    dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter_pfct)
   				(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_PENDING,&attemptCounter_u8);
                }
                else{

                    dataRetValue_u8 = (*(Dcm_GetSecurityAttemptCounter_pfct)
   				(Dcm_Dsp_Security[idxSeca_qu8].Dsp_GetAttempCounter_fp))(DCM_INITIAL,&attemptCounter_u8);
                }
            }

   		switch(dataRetValue_u8)
   		{
   		    case E_OK:
                {

                   Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8 = attemptCounter_u8;

                   waitRequestedIdx_qu8[idxSeca_qu8]=0;
                }
   			break;

                case DCM_E_PENDING:
                {
                   waitRequested_b =TRUE;

                   waitRequestedIdx_qu8[idxSeca_qu8] =1;
                }
   			break;

                case E_NOT_OK:
                {

                   Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8 = Dcm_Dsp_Security[idxSeca_qu8].NumAttDelay_u8;

                   waitRequestedIdx_qu8[idxSeca_qu8]=0;
                }
   			break;

   			default:

   			break;
   		}
   		if((E_OK != dataRetValue_u8 )&&(DCM_E_PENDING != dataRetValue_u8)&&(E_NOT_OK != dataRetValue_u8))
   		{

   			Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8 =0;
   			waitRequestedIdx_qu8[idxSeca_qu8]=0;
   		}

   	}
        else{

            Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8 = Dcm_Dsp_Security[idxSeca_qu8].NumAttDelay_u8;

            waitRequestedIdx_qu8[idxSeca_qu8]=0;
        }
   }
}

FUNC(void,DCM_CODE) Dcm_Dsp_RestoreDelayCount(void){
    dataRetValue_u8 =E_NOT_OK;
    waitRequested_b=FALSE;

   if(Dcm_GetattemptCounterWaitCycle_u8 < DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
   {

        Dcm_Lok_SecaDelayCountRead();

        Dcm_Lok_SecaGetattemptCounterCheck();
   }
   else{

   	Dcm_Lok_GetattemptCounterWaitCycleExhaused();

        Dcm_Dsp_SecaPowerOnDelayIni();

        Dcm_GetattemptCounterWaitCycle_u8++;
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

