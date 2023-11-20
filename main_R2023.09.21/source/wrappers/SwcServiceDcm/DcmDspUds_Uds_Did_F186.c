#include "Std_Types.hpp"

#include "DcmDspUds_Uds_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_DidServices_F186_ReadData(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8)
{
   VAR(Std_ReturnType,AUTOMATIC)  dataRetVal_u8;
   VAR(Dcm_SesCtrlType,AUTOMATIC) dataSessId_u8;

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

