#include "EcuM.hpp"
#include "EcuM_Callout.hpp"
#include "EcuM_Cfg_SchM.hpp"
#include "Rte_Main.hpp"
#include "Os.hpp"
#include "BswM.hpp"

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.hpp"
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
Type_SwcServiceEcuM_stInfoTargetShutdown EcuM_Rn_dataShutdownInfo_st;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"
void EcuM_StartupTwo(void)
        {
   if( SwcServiceEcuM_bIsInitialised == TRUE )
      {
   if( FALSE == EcuM_Lok_flgIsStartupTwoCalled_ab[0] )
   {
        SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseStartOsPost;
        EcuM_Lok_flgIsStartupTwoCalled_ab[0] = TRUE;
        SchM_Init();
        BswM_Init(SwcServiceEcuM_pcstCfg->stRefCfgModules.pcstCfgSwcServiceBswM);
   }
   else{
   }
        }
   else{
#if( ECUM_DEV_ERROR_DETECT == STD_ON )
         (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_START_TWO_APIID, ECUM_E_UNINIT );
#endif
         return;
     }
}

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
Std_ReturnType EcuM_Rn_NvMSingleBlockCallbackFunction(
        uint8 ServiceId
   ,       uint8 JobResult)
        {
    Std_ReturnType returnvalue_u8 = E_NOT_OK;
   if((ServiceId==0x0c) && (JobResult==NVM_REQ_OK))
   {
        EcuM_Lok_flgNvMReadStatus_b=TRUE;
        EcuM_Lok_dataShutdownInfo_st=EcuM_Rn_dataShutdownInfo_st;
        EcuM_Rn_dataShutdownInfo_st=SwcServiceEcuM_stInfoTargetShutdown;
        (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
         returnvalue_u8   =   E_OK;
   }
   else if((ServiceId==0x13) && (JobResult==NVM_REQ_OK))
   {
        returnvalue_u8   =   E_OK;
   }
   else{
   }
    return returnvalue_u8;
}
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"
