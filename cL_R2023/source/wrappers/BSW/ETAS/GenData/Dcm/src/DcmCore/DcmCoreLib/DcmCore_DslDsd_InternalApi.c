
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

boolean Dcm_Lok_IsRxPduIdOBD(PduIdType DcmRxPduId)
{
    uint8 Counter;
    boolean IsRxPduIdObd_b = FALSE;

    for(Counter = 0u;Counter < DCM_OBD_RXSIZE;Counter++)
    {
        if(Dcm_Dsl_OBDRxPduIds[Counter] == DcmRxPduId)
        {
            IsRxPduIdObd_b = TRUE;
            break;
        }
    }
    return IsRxPduIdObd_b;
}

boolean Dcm_Lok_IsTxPduIdOBD(PduIdType DcmTxPduId)
{
    uint8 Counter;
    boolean IsTxPduIdObd_b = FALSE;

    for(Counter = 0u;Counter < DCM_OBD_TXSIZE;Counter++)
    {
        if(Dcm_Dsl_OBDTxPduIds[Counter] == DcmTxPduId)
        {
            IsTxPduIdObd_b = TRUE;
            break;
        }
    }
    return IsTxPduIdObd_b;
}
#endif

void Dcm_DsldSetsessionTiming(
                                               uint32 nrP2StarMax_u32,
                                               uint32 nrP2Max_u32
                                             )
{

    SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

    if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
#endif
    {

        Dcm_DsldTimer_st.dataTimeoutP2max_u32 = nrP2Max_u32;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = nrP2StarMax_u32;
    }
    SchM_Exit_Dcm_DsldTimer_NoNest();
}

uint32 Dcm_DsldGetActiveSecurityMask_u32 (void)
{
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSecurity_u8);
}

uint32 Dcm_DsldGetActiveSessionMask_u32 (void)
{
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSession_u8);
}

Std_ReturnType Dcm_ForceRespPend(void)
{
    Std_ReturnType dataRetValue_u8 = E_NOT_OK;
    Dcm_DsdStatesType_ten DsdState_en = Dcm_Lok_GetDsdState();

    if((Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_ROE_SOURCE) && (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE) && (DSD_CALL_SERVICE  == DsdState_en))
    {

        if(Dcm_DslTransmit_st.isForceResponsePendRequested_b == FALSE)
        {

            Dcm_DslTransmit_st.isForceResponsePendRequested_b = TRUE;

            Dcm_DslTransmit_st.TxBuffer_tpu8 = NULL_PTR;

            Dcm_DslTransmit_st.TxResponseLength_u32 = 0x00;

            Dcm_Lok_TriggerTransmit();

            dataRetValue_u8 = E_OK;
        }
    }
    return(dataRetValue_u8);
}

boolean Dcm_IsInfrastructureErrorPresent_b(uint8 dataInfrastrutureCode_u8)
{
	boolean stInfrastructStatus_b;
	if((dataInfrastrutureCode_u8 & 0x80u) != (0x00u))
	{
	
		stInfrastructStatus_b= TRUE;
	}
	else
	{
	
		stInfrastructStatus_b= FALSE;
	}
	return(stInfrastructStatus_b);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

