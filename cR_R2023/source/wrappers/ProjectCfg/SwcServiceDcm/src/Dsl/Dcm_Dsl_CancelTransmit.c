

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) || (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_CancelTransmit(void)
{
    VAR(Std_ReturnType,AUTOMATIC) cancelTxStatus = E_NOT_OK;
    VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en;
    VAR(uint8,AUTOMATIC) DslState_u8 = 0u;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    VAR(boolean,AUTOMATIC) isPagedBufferTransmissionInProgress_b = FALSE;
#endif

    SchM_Enter_Dcm_Global_NoNest();
    DsdState_en = Dcm_Lok_GetDsdState();
    DslState_u8   = Dcm_Lok_GetDslState();
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    isPagedBufferTransmissionInProgress_b = Dcm_DsldGlobal_st.flgPagedBufferTxOn_b;
#endif
    SchM_Exit_Dcm_Global_NoNest();

    if((DslState_u8 == DSL_STATE_WAITING_FOR_TXCONFIRMATION) || \
      ((DslState_u8 == DSL_STATE_ROETYPE1_RECEIVED) && (DsdState_en == DSD_WAITFORTXCONF)))
    {

        Dcm_isCancelTransmitInvoked_b = TRUE;
    }

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

    if(FALSE != isPagedBufferTransmissionInProgress_b)
    {

        Dcm_isCancelTransmitInvoked_b = TRUE;

        DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);
    }
#endif

    if(FALSE != Dcm_isCancelTransmitInvoked_b)
    {

		
        cancelTxStatus = PduR_DcmCancelTransmit(Dcm_DsldGlobal_st.dataOldtxPduId_u8);

		
        if(E_OK != cancelTxStatus)
        {

            Dcm_StopProtocol(Dcm_CurProtocol_u8);
            Dcm_isStopProtocolInvoked_b   = TRUE;
            Dcm_isCancelTransmitInvoked_b = FALSE;
        }
    }
    return(cancelTxStatus);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
