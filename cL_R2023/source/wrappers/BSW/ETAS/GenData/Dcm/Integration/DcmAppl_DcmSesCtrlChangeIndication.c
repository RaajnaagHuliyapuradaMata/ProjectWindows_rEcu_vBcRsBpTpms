
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
#include "rba_DcmPma_Prot.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void DcmAppl_DcmSesCtrlChangeIndication(
                                                        Dcm_SesCtrlType SesCtrlTypeOld,
                                                        Dcm_SesCtrlType SesCtrlTypeNew
                                                           )
{
#if (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)

        if((SesCtrlTypeNew == DCM_DEFAULT_SESSION) && (rba_DcmPma_PlantModeStatus_b != FALSE))
        {

            rba_DcmPma_PlantModeActivation (FALSE);
        }
#endif

    (void)(SesCtrlTypeOld);

    if(SesCtrlTypeNew != DCM_DEFAULT_SESSION)
    {

		
        if (SesCtrlTypeNew == DCM_PROGRAMMING_SESSION)
        {
			DcmAppl_Switch_DcmBootLoaderReset(); //trigger the bootloader jump here
		}

    }
    else
    {

        if(SesCtrlTypeOld != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
        {

        }

    }

    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

    #endif

    return;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

