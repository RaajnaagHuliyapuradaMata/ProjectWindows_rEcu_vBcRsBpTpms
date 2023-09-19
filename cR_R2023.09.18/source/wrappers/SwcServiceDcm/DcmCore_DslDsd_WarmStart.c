#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

VAR(Dcm_ProgConditionsType,DCM_VAR) Dcm_ProgConditions_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
 VAR(boolean,DCM_VAR) Dcm_SesChgOnWarmResp_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(uint8,DCM_CODE) Dcm_GetActiveConnectionIdx_u8 (void){
   VAR(uint8_least,AUTOMATIC)  idxProtcol_qu8;
   VAR(uint8_least,AUTOMATIC)  idxSession_qu8;
   VAR(uint8_least,AUTOMATIC)  idxIndex1_qu8;
   VAR(uint8_least,AUTOMATIC)  idxIndex2_qu8;
   VAR(uint8, AUTOMATIC)       idxConn_u8;
   idxConn_u8 = 0;

   for(idxProtcol_qu8 = 0; idxProtcol_qu8 < DCM_CFG_NUM_PROTOCOL; idxProtcol_qu8++)
   {
        if(Dcm_ProgConditions_st.ProtocolId == Dcm_DsldProtocol_pcst[idxProtcol_qu8].protocolid_u8)
        {
            break;
        }
   }

   if(idxProtcol_qu8 >= DCM_CFG_NUM_PROTOCOL)
   {
        idxProtcol_qu8 = 0;
        for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_CONN; idxIndex1_qu8++)
        {
            if(Dcm_DsldConnTable_pcst[idxIndex1_qu8].protocol_num_u8 == 0x0)
            {
                break;
            }
        }
   }

   for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
   {
        if(Dcm_ProgConditions_st.SessionLevel == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
        {
            break;
        }
   }
   if(idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
   {

        Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = (uint8)idxProtcol_qu8;

        for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_RX_PDUID; idxIndex1_qu8++)
        {
            if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].protocol_num_u8 == idxProtcol_qu8)
            {
                if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].testaddr_u16 == Dcm_ProgConditions_st.TesterSourceAddr)
                {
                    idxConn_u8 = Dcm_DsldRxTable_pcu8[idxIndex1_qu8];
                    break;
                }
            }
        }

        if(idxIndex1_qu8 >= DCM_CFG_NUM_RX_PDUID)
        {
            for(idxIndex2_qu8=0; idxIndex2_qu8<DCM_CFG_NUM_CONN; idxIndex2_qu8++)
            {
                if(Dcm_DsldConnTable_pcst[idxIndex2_qu8].protocol_num_u8 == idxProtcol_qu8)
                {
                    idxConn_u8 = (uint8)idxIndex2_qu8;
                    break;
                }
            }
        }
   }
   else{
        idxConn_u8 = 0;
   }
    return idxConn_u8;
}

FUNC(void,DCM_CODE) Dcm_DslDsdWarmStart(void){
   VAR(uint8_least,AUTOMATIC)  idxProtcol_qu8;
   VAR(uint8_least,AUTOMATIC)  idxSession_qu8;
   VAR(uint8,     AUTOMATIC)  dataSessionId_u8;
   VAR(uint8_least,AUTOMATIC)  nrReqLength_qu8;
   VAR(uint8_least,AUTOMATIC)  idxIndex1_qu8;
   VAR(uint8_least,AUTOMATIC)  idxIndex2_qu8;
   P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) protocol_table_pcs;
    Dcm_SesChgOnWarmResp_b =FALSE;
   if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
   {

        nrReqLength_qu8 = Dcm_ProgConditions_st.ReqResLen;

        for(idxProtcol_qu8 = 0; idxProtcol_qu8 < DCM_CFG_NUM_PROTOCOL; idxProtcol_qu8++)
        {
            if(Dcm_ProgConditions_st.ProtocolId == Dcm_DsldProtocol_pcst[idxProtcol_qu8].protocolid_u8)
            {
                break;
            }
        }

        if(idxProtcol_qu8 >= DCM_CFG_NUM_PROTOCOL)
        {
            idxProtcol_qu8 = 0;

            DCM_DET_ERROR(DCM_WARMSTART_ID , DCM_E_PROTOCOL_NOT_FOUND )
            for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_CONN; idxIndex1_qu8++)
            {
                if(Dcm_DsldConnTable_pcst[idxIndex1_qu8].protocol_num_u8 == 0x0)
                {
                    Dcm_ProgConditions_st.TesterSourceAddr = Dcm_DsldConnTable_pcst[idxIndex1_qu8].testaddr_u16;
                    break;
                }
            }
        }
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        if((Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET) ||  (Dcm_ProgConditions_st.Sid == 0x51))
        {
         idxSession_qu8 = DCM_DEFAULT_SESSION_IDX;
        }
        else
#endif
        {

            for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
            {
                if(Dcm_ProgConditions_st.SessionLevel == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
                {
                    break;
                }
            }
        }

        if(idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
        {

            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = (uint8)idxProtcol_qu8;

            for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_RX_PDUID; idxIndex1_qu8++)
            {
                if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].protocol_num_u8 == idxProtcol_qu8)
                {
                    if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].testaddr_u16 == Dcm_ProgConditions_st.TesterSourceAddr)
                    {
                        Dcm_DsldGlobal_st.nrActiveConn_u8 = Dcm_DsldRxTable_pcu8[idxIndex1_qu8];
                        break;
                    }
                }
            }

            if(idxIndex1_qu8 >= DCM_CFG_NUM_RX_PDUID)
            {
                for(idxIndex2_qu8=0; idxIndex2_qu8<DCM_CFG_NUM_CONN; idxIndex2_qu8++)
                {
                    if(Dcm_DsldConnTable_pcst[idxIndex2_qu8].protocol_num_u8 == idxProtcol_qu8)
                    {
                        Dcm_DsldGlobal_st.nrActiveConn_u8 = (uint8)idxIndex2_qu8;
                        break;
                    }
                }
            }

#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
            if((Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET) ||  (Dcm_ProgConditions_st.Sid == 0x51))
            {

                Dcm_DsldGlobal_st.idxActiveSession_u8 = DCM_DEFAULT_SESSION_IDX;

                Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
                Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;

                Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;

            }
            else
#endif
            {

                        Dcm_DsldGlobal_st.idxActiveSession_u8 = (uint8)idxSession_qu8;

                        dataSessionId_u8 = Dcm_ProgConditions_st.SessionLevel;
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

                        Dcm_GetP2Timings(&Dcm_DsldTimer_st.dataTimeoutP2max_u32, &Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32
   ,     (Dcm_SesCtrlType)dataSessionId_u8);
#else
                        DcmAppl_DcmGetP2Timings(&Dcm_DsldTimer_st.dataTimeoutP2max_u32, &Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32
   ,     (Dcm_SesCtrlType)dataSessionId_u8);
#endif

                        Dcm_Lok_SetSecurityLevel(Dcm_ProgConditions_st.SecurityLevel);
            }

            if((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE) && (nrReqLength_qu8 != 0x0u) && (Dcm_ProgConditions_st.ResponseRequired != FALSE))
            {

                Dcm_DsldGlobal_st.dataRequestLength_u16  = (uint16)nrReqLength_qu8;

                protocol_table_pcs = &Dcm_DsldProtocol_pcst[idxProtcol_qu8];

                protocol_table_pcs->rx_mainBuffer_pa[0] = Dcm_ProgConditions_st.Sid;
                nrReqLength_qu8--;

                if(nrReqLength_qu8 > 0x0u)
                {

                    protocol_table_pcs->rx_mainBuffer_pa[1] = Dcm_ProgConditions_st.SubFncId;
                    nrReqLength_qu8--;
                }

                DCM_MEMCOPY(&(protocol_table_pcs->rx_mainBuffer_pa[0x02]), Dcm_ProgConditions_st.ReqResBuf,nrReqLength_qu8);

                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = Dcm_ProgConditions_st.NumWaitPend;

                Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_START_PROTOCOL);

                if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 != 0)
                {

                    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32
   ,     (Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2StarTmrAdjust)
   ,     Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                }
                else{

                    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32
   ,     (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust)
   ,     Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                }
            }

            if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
            {

                Dcm_Lok_ReloadS3Timer();
            }

            if((Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE) && (nrReqLength_qu8 != 0x0u) && (Dcm_ProgConditions_st.ResponseRequired != FALSE))
            {

                Dcm_DslTransmit_st.TxResponseLength_u32  = nrReqLength_qu8;

                for(idxIndex1_qu8 = (nrReqLength_qu8-1u); idxIndex1_qu8 > 0x1u; idxIndex1_qu8--)
                {
                    Dcm_ProgConditions_st.ReqResBuf[idxIndex1_qu8]= Dcm_ProgConditions_st.ReqResBuf[idxIndex1_qu8-0x2u];
                }

                Dcm_ProgConditions_st.ReqResBuf[0] = Dcm_ProgConditions_st.Sid;
                Dcm_ProgConditions_st.ReqResBuf[1] = Dcm_ProgConditions_st.SubFncId;

                Dcm_DslTransmit_st.TxBuffer_tpu8 = &Dcm_ProgConditions_st.ReqResBuf[0];

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

                if(Dcm_ProgConditions_st.Sid == 0x50u)
                {
                for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
                        {
                            if(Dcm_ProgConditions_st.SubFncId == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
                            {
                                break;
                            }
                        }
                        if(idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
                        {
                            Dcm_ctDiaSess_u8=(uint8)idxSession_qu8;
                            Dcm_SesChgOnWarmResp_b=TRUE;
                        }
                }
#endif

                Dcm_Lok_SetDsdState(DSD_WAITFORTXCONF);
                Dcm_Lok_SetDslState(DSL_STATE_RESPONSE_TRANSMISSION);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_SEND_FINAL_RESPONSE);

                Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].
                                                      txpduid_num_u8;
            }

            Dcm_DsldGlobal_st.flgCommActive_b = TRUE;

            Dcm_DsldGlobal_st.datActiveSrvtable_u8= Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
                                                  sid_tableid_u8;

            Dcm_DsldSrvTable_pcst = \
                  CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

            Dcm_Dsd_ServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);
        }
        else{

        }

        if(Dcm_ProgConditions_st.ApplUpdated != FALSE)
        {
#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)

            BswM_Dcm_ApplicationUpdated();
#endif

            Dcm_ProgConditions_st.ApplUpdated = FALSE;
         }
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

         if(Dcm_ProgConditions_st.ReprogramingRequest != FALSE)
         {

             Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
         }
#endif

         Dcm_ProgConditions_st.ResponseRequired = FALSE;

         Dcm_ProgConditions_st.StoreType = DCM_NOTVALID_TYPE;
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

