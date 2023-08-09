
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Seca_Inf.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Dcm_StatusType,DCM_APPL_CODE) DcmAppl_DcmCheckSeed(
                                                    VAR(uint32,AUTOMATIC) SeedLen,
                                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) Seed
                                                  )
{
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
#include "Dcm_Cfg_MemMap.h"

#endif
