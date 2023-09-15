#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Dcm_StatusType,DCM_CODE) Dcm_PrepareKwpTimingValues(
                                        P2CONST(Dcm_Dsld_KwpTimerServerType,AUTOMATIC,DCM_APPL_CONST) TimerServerNew
                                                        )
{
   VAR(uint8,AUTOMATIC) idxLimitTmg_u8;
   VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;

    dataReturnValue_u8 = DCM_E_TI_PREPARE_LIMITS;

   if(TimerServerNew != NULL_PTR)
   {

        idxLimitTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_limit_idx_u8;

        if( (TimerServerNew->P2_max_u32 <= Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P2_max_u32)
             && (TimerServerNew->P3_max_u32 <= Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P3_max_u32))
        {

            SchM_Enter_Dcm_DsldTimer_NoNest();
            Dcm_DsldKwpReqTiming_st.P2_max_u32 = TimerServerNew-> P2_max_u32;
            Dcm_DsldKwpReqTiming_st.P3_max_u32 = TimerServerNew-> P3_max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();

            dataReturnValue_u8 = E_OK;
        }
   }
    return(dataReturnValue_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

