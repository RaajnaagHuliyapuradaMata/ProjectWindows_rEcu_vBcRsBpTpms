
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspObd_Mode4_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode4_Priv.h"
#include "DcmAppl.h"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_OBD_Mode04(void)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	

	return retVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

#endif
