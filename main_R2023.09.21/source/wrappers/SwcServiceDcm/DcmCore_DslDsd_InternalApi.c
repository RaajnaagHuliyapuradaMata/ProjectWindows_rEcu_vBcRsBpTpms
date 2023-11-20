#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_CODE) Dcm_DsldSetsessionTiming(
                                               VAR(uint32, AUTOMATIC) nrP2StarMax_u32
   ,     VAR(uint32, AUTOMATIC) nrP2Max_u32
                                             )
{

    SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

   if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
#endif
   {

        Dcm_DsldTimer_st.dataTimeoutP2max_u32 = nrP2Max_u32;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = nrP2StarMax_u32;
   }
    SchM_Exit_Dcm_DsldTimer_NoNest();
}

FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSecurityMask_u32 (void){
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSecurity_u8);
}

FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSessionMask_u32 (void){
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSession_u8);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_ForceRespPend(void){
   VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8 = E_NOT_OK;
   VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en = Dcm_Lok_GetDsdState();

   if((Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_ROE_SOURCE) && (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE) && (DSD_CALL_SERVICE  == DsdState_en))
   {

        if(Dcm_DslTransmit_st.isForceResponsePendRequested_b == FALSE)
        {

            Dcm_DslTransmit_st.isForceResponsePendRequested_b = TRUE;

            Dcm_DslTransmit_st.TxBuffer_tpu8 = NULL_PTR;

            Dcm_DslTransmit_st.TxResponseLength_u32 = 0x00;

            Dcm_Lok_TriggerTransmit();

            dataRetValue_u8 = E_OK;
        }
   }
    return(dataRetValue_u8);
}

FUNC(boolean,DCM_CODE) Dcm_IsInfrastructureErrorPresent_b(VAR(uint8,AUTOMATIC) dataInfrastrutureCode_u8)
{
   VAR(boolean,AUTOMATIC) stInfrastructStatus_b;
   if((dataInfrastrutureCode_u8 & 0x80u) != (0x00u))
   {

   	stInfrastructStatus_b= TRUE;
   }
   else
   {

   	stInfrastructStatus_b= FALSE;
   }
   return(stInfrastructStatus_b);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

