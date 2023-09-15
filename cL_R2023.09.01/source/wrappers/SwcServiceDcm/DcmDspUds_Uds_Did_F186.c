
#include "DcmDspUds_Uds_Inf.hpp"
#include "Rte_Dcm.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType Dcm_DidServices_F186_ReadData(uint8 * adrData_pu8)
{
    Std_ReturnType dataRetVal_u8;
    Dcm_SesCtrlType dataSessId_u8;

    dataRetVal_u8 = Dcm_GetSesCtrlType(&dataSessId_u8);

   if(dataRetVal_u8 == E_OK)
   {
    	adrData_pu8[0] = (uint8)dataSessId_u8;
   }

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

