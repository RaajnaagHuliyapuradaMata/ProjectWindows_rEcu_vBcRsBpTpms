
#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Inf.hpp"
#endif
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
#define DCM_RDPI_SID 0x2Au
#endif

#if((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u))

void Dcm_Dsd_CallRTEConfirmation(Dcm_ConfirmationStatusType ConfirmationStatus_u8,boolean context)
{
   uint8_least idxIndex_qu8;
    Dcm_MsgContextType MsgContext_st;

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
   if(context == DCM_OBDCONTEXT)
   {
        MsgContext_st = Dcm_OBDMsgContext_st;
   }
   else
#endif
   {
        MsgContext_st = Dcm_DsldMsgContext_st;
   }
#if(DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u)
   for(idxIndex_qu8=0x00u; idxIndex_qu8<DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS; idxIndex_qu8++)
   {
        (void)(*Dcm_Rte_ManufacturerConfirmation_a[idxIndex_qu8])
                (MsgContext_st.idContext,MsgContext_st.msgAddInfo.reqType
   ,               Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[MsgContext_st.dcmRxPduId]].testaddr_u16
   ,               ConfirmationStatus_u8);
   }
#endif
#if(DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u)
   for(idxIndex_qu8=0x00u; idxIndex_qu8<DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS; idxIndex_qu8++)
   {
        (void)(*Dcm_Rte_SupplierConfirmation_a[idxIndex_qu8])
                (MsgContext_st.idContext,MsgContext_st.msgAddInfo.reqType
   ,               Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[MsgContext_st.dcmRxPduId]].testaddr_u16
   ,               ConfirmationStatus_u8);
   }
#endif
#if(DCM_PARALLELPROCESSING_ENABLED == DCM_CFG_OFF)
    (void)context;
#endif
}
#endif

LOCAL_INLINE void Dsd_Lok_TesterSourceConfirmation(Dcm_ConfirmationStatusType ConfirmationStatus_u8)
{

   if(Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE)
   {
        if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b != FALSE)
        {

            Dcm_DspConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,                   Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,                   ConfirmationStatus_u8);
        }
        else{

            DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,                   Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,                   ConfirmationStatus_u8);
        }
   }
   else{
#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)

        if((ConfirmationStatus_u8 == DCM_RES_NEG_OK) || (ConfirmationStatus_u8 == DCM_RES_NEG_NOT_OK))
        {

            DcmAppl_DcmConfirmation_DcmNegResp(Dcm_DsldMsgContext_st.idContext
   ,                   Dcm_DsldMsgContext_st.dcmRxPduId,ConfirmationStatus_u8);
        }
#endif

        if(Dcm_isGeneralRejectSent_b != FALSE)
        {
            DcmAppl_DcmConfirmation_GeneralReject(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,                   ConfirmationStatus_u8);

            Dcm_isGeneralRejectSent_b = FALSE;
        }
        if((ConfirmationStatus_u8 == DCM_RES_POS_OK) || (ConfirmationStatus_u8 == DCM_RES_POS_NOT_OK))
        {

            DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext, Dcm_DsldMsgContext_st.dcmRxPduId
   ,                   Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,                   ConfirmationStatus_u8);
        }
   }
#if((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u))
    Dcm_Dsd_CallRTEConfirmation(ConfirmationStatus_u8,DCM_UDSCONTEXT);
#endif
}

void Dcm_Lok_DsdSendTxConfirmation(void){

    Dcm_ConfirmationStatusType ConfirmationStatus_u8 =
            (Dcm_DsldGlobal_st.dataResult_u8 == E_OK) ?
                ((Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_OK:DCM_RES_NEG_OK) :
                ((Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_NOT_OK:DCM_RES_NEG_NOT_OK);

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

   if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
   {

        Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
        if(ConfirmationStatus_u8 == DCM_RES_POS_NOT_OK)
        {

            DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);
        }
   }
#endif

   if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)
   {
        Dsd_Lok_TesterSourceConfirmation(ConfirmationStatus_u8);
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
   else if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
   {
        Dcm_Lok_ROEResetOnConfirmation();

        DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,Dcm_DsldMsgContext_st.dcmRxPduId
   ,       Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16,ConfirmationStatus_u8);
   }
#endif
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
   else if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE)
   {

        DcmAppl_DcmConfirmationRDPI(DCM_RDPI_SID,Dcm_DsldMsgContext_st.dcmRxPduId,ConfirmationStatus_u8);
   }
#endif
   else{

   }

    Dcm_Lok_SetDsdState(DSD_IDLE);
}

void Dcm_Dsd_ServiceIni(uint8 ServiceTableIndex_u8)
{

   uint8 idxIndex_u8;
   uint8 NumberOfServices_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[ServiceTableIndex_u8].num_services_u8;

   const Dcm_Dsld_ServiceType * adrSrvTable_pcst =
                          CfgSwcServiceDcm_stDsld.sid_table_pcs[ServiceTableIndex_u8].ptr_service_table_pcs;

   for(idxIndex_u8 = NumberOfServices_u8; idxIndex_u8 != 0x00u; idxIndex_u8--)
   {
        if(adrSrvTable_pcst->Service_init_fp != NULL_PTR )
        {
            (*adrSrvTable_pcst->Service_init_fp)();
        }
        adrSrvTable_pcst++;
   }
}
