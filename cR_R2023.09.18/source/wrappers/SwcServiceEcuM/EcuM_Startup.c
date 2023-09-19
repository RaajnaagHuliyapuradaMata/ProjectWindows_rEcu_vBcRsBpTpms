#include "Std_Types.hpp"

#include "EcuM.hpp"
#include "EcuM_Callout.hpp"
#include "EcuM_Cfg_SchM.hpp"
#include "Rte_Main.hpp"
#include "Os.hpp"

#if(!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif

#if(!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "BswM.hpp"

#if(!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif

#if(!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.hpp"
#if(!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif

#if(!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif

#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
VAR( Type_SwcServiceEcuM_stInfoTargetShutdown, ECUM_VAR_SAVED_ZONE0_UNSPECIFIED ) EcuM_Rn_dataShutdownInfo_st;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
FUNC(void, ECUM_CODE) EcuM_StartupTwo(void)
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
FUNC(Std_ReturnType, ECUM_CODE) EcuM_Rn_NvMSingleBlockCallbackFunction(
        VAR(uint8, AUTOMATIC) ServiceId
   ,     VAR(uint8, AUTOMATIC) JobResult)
        {
   VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;
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
#include "EcuM_Cfg_MemMap.hpp"
