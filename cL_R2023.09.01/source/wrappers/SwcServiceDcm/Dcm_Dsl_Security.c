

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Lok_SetSecurityLevel (Dcm_SecLevelType dataSecurityLevel_u8)
{
   uint8_least idxIndex_qu8;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
   uint32 dataSecurityMask_u32;
#endif

   const uint8 * adrSecurityLookupTable_pcu8;

    adrSecurityLookupTable_pcu8 = CfgSwcServiceDcm_stDsld.security_lookup_table_pcau8;

   for(idxIndex_qu8 = 0x0; idxIndex_qu8 < DCM_CFG_NUM_SECURITY_LEVEL ; idxIndex_qu8++)
   {
        if(adrSecurityLookupTable_pcu8[idxIndex_qu8]== dataSecurityLevel_u8)
        {

            break;
        }
   }

   if(idxIndex_qu8< DCM_CFG_NUM_SECURITY_LEVEL)
   {

        Dcm_DsldGlobal_st.idxActiveSecurity_u8 = (uint8)idxIndex_qu8;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))

        dataSecurityMask_u32 = Dcm_DsldGetActiveSecurityMask_u32();

    Dcm_ResetActiveIoCtrl(0xFFFFFFFFu,dataSecurityMask_u32,FALSE);
#endif
   }
   else{

        DCM_DET_ERROR(DCM_SETSECURITYLEVEL , DCM_E_SECURITYLEVEL_OUTOFBOUNDS )
   }
}

Std_ReturnType Dcm_GetSecurityLevel (Dcm_SecLevelType * SecLevel)
{
   if(SecLevel != NULL_PTR)
   {
        *SecLevel = CfgSwcServiceDcm_stDsld.security_lookup_table_pcau8[Dcm_DsldGlobal_st.idxActiveSecurity_u8];
   }
   else{

        DCM_DET_ERROR(DCM_BOOTLOADER_ID, DCM_E_PARAM_POINTER);
   }
    return (E_OK);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
