

#ifndef DCMDSPUDS_CC_PROT_H
#define DCMDSPUDS_CC_PROT_H

typedef enum{
    DCM_DSP_CC_INITIAL  = 1
   ,   DCM_DSP_CC_CHECKDATA
   ,   DCM_DSP_CC_PROCESSSERVICE
   ,   DCM_DSP_CC_ERROR
}Dcm_CCStateType_ten;

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF))
extern FUNC(void, DCM_CODE) Dcm_Lok_DspCommCntrlConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   													 );

LOCAL_INLINE boolean Dcm_Lok_CC_IsSupportedInSession( VAR(Dcm_SesCtrlType,DCM_VAR) ActiveSession_u8)
{

   VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
   VAR(uint8,AUTOMATIC) nrSessions_u8;
   VAR(boolean,AUTOMATIC)  flgStatus_b;

   VAR(uint32,AUTOMATIC) dataSessionsAllowed_u32;
   VAR(uint8,AUTOMATIC) nrService_u8;

    flgStatus_b = TRUE;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

            if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
            {
                nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
            }
            else
#endif
            {
                nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
            }

             for(idxIndex_qu8 = 0x1; idxIndex_qu8 < nrSessions_u8 ; idxIndex_qu8++)
             {
                 //if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== dataSesCtrlType_u8)
                 if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== ActiveSession_u8)
                 {

                     break;
                 }
             }
             if(idxIndex_qu8 != nrSessions_u8)
             {

                 nrService_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;

                  for(idxIndex_qu8 = 0x0; idxIndex_qu8 < nrService_u8 ; idxIndex_qu8++)
                  {

                      if(( CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].sid_u8 == DCM_DSP_SID_COMMUNICATIONCONTROL)&&(CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].servicelocator_b !=FALSE ) )
                      {

                          break;
                      }
                  }
                  dataSessionsAllowed_u32 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].allowed_session_b32;
                  if((idxIndex_qu8 >= nrService_u8) || ((Dcm_DsldGetActiveSessionMask_u32() &  dataSessionsAllowed_u32) == 0u))
                  {

                      flgStatus_b = FALSE;
                  }

            }

return flgStatus_b;
}

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

