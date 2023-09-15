
#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

   static uint8 Dcm_Lok_idxSec_qu8;
   static uint32 Dcm_Lok_dataSecaGlobaltimer_u32;

#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP == DCM_CFG_OFF))
   static uint32 Dcm_Lok_nrPowerOnDelay_u32;
#endif

#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_ON))
static void Dcm_Lok_SecaPowerOnDelayExpired(void){
   uint32 nrDelay_u32;

   if(Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].FailedAtm_cnt_u8 >= Dcm_Dsp_Security[Dcm_Lok_idxSec_qu8].NumAttDelay_u8)
   {
        if(Dcm_Dsp_Security[Dcm_Lok_idxSec_qu8].DelayTime_u32 > 0x00u)
   	{
   	nrDelay_u32 = (Dcm_Dsp_Security[Dcm_Lok_idxSec_qu8].DelayTime_u32 * DCM_CFG_TASK_TIME_MS);

        nrDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Dsp_Security[Dcm_Lok_idxSec_qu8].Security_level_u8
   ,       Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].FailedAtm_cnt_u8,nrDelay_u32);
        nrDelay_u32 = (nrDelay_u32 / DCM_CFG_TASK_TIME_MS);
           if(nrDelay_u32 > Dcm_Lok_dataSecaGlobaltimer_u32)
            {

            Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = (nrDelay_u32 - Dcm_Lok_dataSecaGlobaltimer_u32);
            }
   		else
   		{

   		Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = 0;
   		}
        }
        else{
 		Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = 0;
        }
   }
   else{

    Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = 0;
   }
}

static void Dcm_Lok_SecaPowerOnDelayNotExpired(void){
   Dcm_Lok_nrPowerOnDelay_u32 = (Dcm_Lok_nrPowerOnDelay_u32 * DCM_CFG_TASK_TIME_MS);

    Dcm_Lok_nrPowerOnDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Dsp_Security[Dcm_Lok_idxSec_qu8].Security_level_u8
   ,   Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].FailedAtm_cnt_u8,Dcm_Lok_nrPowerOnDelay_u32);
    Dcm_Lok_nrPowerOnDelay_u32 = (Dcm_Lok_nrPowerOnDelay_u32 / DCM_CFG_TASK_TIME_MS);

   if(Dcm_Lok_nrPowerOnDelay_u32 > Dcm_Lok_dataSecaGlobaltimer_u32)
   {

    Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = Dcm_Lok_nrPowerOnDelay_u32 - Dcm_Lok_dataSecaGlobaltimer_u32;
   }
   else{

    Dcm_Dsp_Seca[Dcm_Lok_idxSec_qu8].Residual_delay_u32 = 0;
   }
}
#endif

static void Dcm_Lok_SecaWarmStart(void){
   uint8 dataNumBootSeclev_u8;
   uint8 l_idxSec_qu8;
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF))
   uint8 idxDcmSeclevel_u8;
    dataNumBootSeclev_u8=Dcm_ProgConditions_st.NumOfSecurityLevels;
#else
    dataNumBootSeclev_u8 = DCM_CFG_DSP_NUMSECURITY;
#endif

    Dcm_Lok_dataSecaGlobaltimer_u32 = ((Dcm_ProgConditions_st.ElapsedTime * 1000uL)/DCM_CFG_TASK_TIME_US);

   if(Dcm_Dsp_SecaGlobaltimer_u32 != 0xFFFFFFFFuL)
   {

        for(l_idxSec_qu8=0; l_idxSec_qu8 < dataNumBootSeclev_u8; l_idxSec_qu8++)
        {
   		Dcm_Lok_idxSec_qu8 = l_idxSec_qu8;
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF))
            for(idxDcmSeclevel_u8=0;idxDcmSeclevel_u8<DCM_CFG_DSP_NUMSECURITY;idxDcmSeclevel_u8++)
            {
   			if(Dcm_Dsp_Security[idxDcmSeclevel_u8].Security_level_u8==
   			   Dcm_ProgConditions_st.SecurityInformation[l_idxSec_qu8].SecurityLevel)
                {
                 break;
                }
            }
#else
   		Dcm_Lok_nrPowerOnDelay_u32 = (Dcm_Dsp_Security[l_idxSec_qu8].PowerOnDelay_u32);

            if(Dcm_Lok_nrPowerOnDelay_u32 <= Dcm_Lok_dataSecaGlobaltimer_u32)
            {
   			Dcm_Lok_SecaPowerOnDelayExpired();
            }

            else{
   			Dcm_Lok_SecaPowerOnDelayNotExpired();
            }
#endif
   	}
   }
}
#endif
#endif

void Dcm_DslDsdRestoreSecaTimer(void){
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

   if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
   {
        Dcm_Lok_SecaWarmStart();
   }
   else{

        Dcm_Dsp_SecaPowerOnDelayIni();
   }
#else

    Dcm_Dsp_SecaPowerOnDelayIni();
#endif
#endif
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

