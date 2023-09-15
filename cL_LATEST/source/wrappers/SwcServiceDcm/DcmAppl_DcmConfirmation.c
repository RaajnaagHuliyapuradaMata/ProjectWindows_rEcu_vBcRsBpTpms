
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
#include "rba_DcmPma_Prot.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void DcmAppl_DcmConfirmation (
                                                Dcm_IdContextType idContext
   ,                                               Type_SwcServiceCom_tIdPdu dcmRxPduId
   ,                                               uint16 SourceAddress
   ,                                               Dcm_ConfirmationStatusType status
                                                 )
{

#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF) || (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_Confirmation(idContext, dcmRxPduId, status);
    (void)(SourceAddress);
#endif
#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
   if(idContext == RBA_DCMPMA_SID_PLANTMODEACTIVATION)
   {
        if((status == DCM_RES_POS_OK) && (rba_DcmPma_PlantModeActivation_en == RBA_DCMPMA_PLANTMODE_INIT2))
        {

            rba_DcmPma_PlantModeActivation (TRUE);
        }
   }
    (void)dcmRxPduId;
    (void)SourceAddress;
#endif
#else

    (void)(dcmRxPduId);
    (void)(idContext);
    (void)(status);
    (void)(SourceAddress);

    Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;

#endif
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

