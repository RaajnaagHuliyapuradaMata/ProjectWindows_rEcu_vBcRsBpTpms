
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)

#include "rba_DemObdBasic_Dcm.h"
#include "rba_DemObdBasic_Prv.h"
#include "DcmDspObd_Mode1_Inf.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

Std_ReturnType Dem_DcmReadDataOfPID21(uint8* PID21value)
{
    Std_ReturnType retVal;

    if (rba_DemObdBasic_IsObdMasterEcu())
    {
        (void)PID21value;
        retVal = E_OK;
    }
    else
    {

        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Dem_DcmReadDataOfPID31(uint8* PID31value)
{
    Std_ReturnType retVal;

    if (rba_DemObdBasic_IsObdMasterEcu())
    {
        (void)PID31value;
        retVal = E_OK;
    }
    else
    {

        retVal = E_NOT_OK;
    }
    return retVal;
}

Std_ReturnType Dem_DcmReadDataOfPID4D(uint8* PID4Dvalue)
{
    Std_ReturnType retVal;

    if (rba_DemObdBasic_IsObdMasterEcu())
    {
        (void)PID4Dvalue;
        retVal = E_OK;
    }
    else
    {

        retVal = E_NOT_OK;
    }
    return retVal;
}

Std_ReturnType Dem_DcmReadDataOfPID4E(uint8* PID4Evalue)
{
    Std_ReturnType retVal;

    if (rba_DemObdBasic_IsObdMasterEcu())
    {
	(void) PID4Evalue;
        retVal = E_OK;
    }
    else
    {

        retVal = E_NOT_OK;
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif