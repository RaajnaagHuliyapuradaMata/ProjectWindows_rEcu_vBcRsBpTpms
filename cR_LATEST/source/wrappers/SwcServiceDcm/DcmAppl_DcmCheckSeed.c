#include "Std_Types.hpp"

#include "DcmDspUds_Seca_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Dcm_StatusType,DCM_APPL_CODE) DcmAppl_DcmCheckSeed(
                                                    VAR(uint32,AUTOMATIC) SeedLen
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) Seed
){
   VAR(uint8,AUTOMATIC) ret_val;
   VAR(uint8,AUTOMATIC) ctIndex;
   ctIndex = 0;
    ret_val = E_OK;
   if((Seed[0] == 0x00) || (Seed[0] == 0xFF))
   {
        for(ctIndex = 1; ctIndex < SeedLen; ctIndex++)
        {
            if(Seed[ctIndex-1] != Seed[ctIndex])
            {
                break;
            }
        }
   }
   if(ctIndex >= SeedLen)
   {
        ret_val = DCM_E_SEED_NOK;
   }
    return (ret_val);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
