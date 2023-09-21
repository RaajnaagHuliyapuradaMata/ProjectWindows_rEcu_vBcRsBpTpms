#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_CODE) Dcm_Lok_ConfirmationRespPendForBootloader(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) Status_u8)
{
   if(Status_u8 == DCM_RES_NEG_OK)
   {

   	if(Dcm_BootLoaderState_en == DCM_BOOT_WAIT)
   	{
   		if(Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)
   		{

   			Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMREQ;
   		}
   		else if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)
   		{

   			Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMRESP;
   		}
   		else
   		{

   			Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMINIT;
   		}
   	}
   	else
   	{
   	    if(Dcm_BootLoaderState_en ==DCM_BOOT_WAIT_FOR_RESET)
   	    {
                if((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)||
                        (Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE))
                {

                    Dcm_BootLoaderState_en = DCM_BOOT_PERFORM_RESET;
                }
   	    }
   	}
   }
   else
   {
   	if((Dcm_BootLoaderState_en == DCM_BOOT_WAIT) || (Dcm_BootLoaderState_en ==DCM_BOOT_WAIT_FOR_RESET))
   	{

   		Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
   	}
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

