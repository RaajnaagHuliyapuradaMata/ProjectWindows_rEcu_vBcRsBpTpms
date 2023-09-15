
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Seca_Inf.hpp"
#include "Rte_Dcm.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Dcm_StatusType DcmAppl_DcmCheckSeed(
                                                    uint32 SeedLen
   ,                                                   const uint8 * Seed
                                                  )
{
   uint8 ret_val;
   uint8 ctIndex;

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
