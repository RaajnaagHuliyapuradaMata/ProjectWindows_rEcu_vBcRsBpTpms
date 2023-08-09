

#include "DcmDspUds_Seca_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Priv.h"

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

 FUNC(void, DCM_CODE) Dcm_Lok_DspSecurityConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
	VAR(uint8,AUTOMATIC) dataSecLevel_u8;

    if (((status_u8 == DCM_RES_POS_OK) || (status_u8 == DCM_RES_POS_NOT_OK))
											&& (Dcm_DspChgSecLevel_b != FALSE))
    {

        dataSecLevel_u8 = (uint8)((Dcm_DspSecAccType_u8 + 1u)>>1u);

        Dcm_Lok_SetSecurityLevel (dataSecLevel_u8);

        Dcm_DspSecAccType_u8 = 0x0;

        Dcm_DspSecTabIdx_u8  = 0x0;
    }

    Dcm_DspChgSecLevel_b   = FALSE;
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																    status_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

