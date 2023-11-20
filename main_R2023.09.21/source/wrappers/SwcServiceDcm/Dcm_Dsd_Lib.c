#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

LOCAL_INLINE void Dsd_Lok_TesterSourceConfirmation(
   Dcm_ConfirmationStatusType ConfirmationStatus_u8){
   if(Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE){
      if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b != FALSE){
            Dcm_DspConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,     Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,     ConfirmationStatus_u8);
        }
        else{
            DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,     Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,     ConfirmationStatus_u8);
        }
   }
   else{
      if(Dcm_isGeneralRejectSent_b != FALSE){
            DcmAppl_DcmConfirmation_GeneralReject(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,     ConfirmationStatus_u8);
            Dcm_isGeneralRejectSent_b = FALSE;
        }
      if((ConfirmationStatus_u8 == DCM_RES_POS_OK) || (ConfirmationStatus_u8 == DCM_RES_POS_NOT_OK)){
            DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,     Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,     ConfirmationStatus_u8);
        }
   }
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
void Dcm_Lok_DsdSendTxConfirmation(void){
    Dcm_ConfirmationStatusType ConfirmationStatus_u8 =
            (Dcm_DsldGlobal_st.dataResult_u8 == E_OK) ?
                ((Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_OK:DCM_RES_NEG_OK) :
                ((Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_NOT_OK:DCM_RES_NEG_NOT_OK);
   if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE){
        Dsd_Lok_TesterSourceConfirmation(ConfirmationStatus_u8);
   }
   else{
   }
    Dcm_Lok_SetDsdState(DSD_IDLE);
}

void Dcm_Dsd_ServiceIni(
   uint8 ServiceTableIndex_u8){
   uint8 idxIndex_u8;
   uint8 NumberOfServices_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[ServiceTableIndex_u8].num_services_u8;
   const Dcm_Dsld_ServiceType *adrSrvTable_pcst = CfgSwcServiceDcm_stDsld.sid_table_pcs[ServiceTableIndex_u8].ptr_service_table_pcs;
   for(idxIndex_u8 = NumberOfServices_u8; idxIndex_u8 != 0x00u; idxIndex_u8--){
      if(adrSrvTable_pcst->Service_init_fp != NULL_PTR){
            (*adrSrvTable_pcst->Service_init_fp)();
        }
        adrSrvTable_pcst++;
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
