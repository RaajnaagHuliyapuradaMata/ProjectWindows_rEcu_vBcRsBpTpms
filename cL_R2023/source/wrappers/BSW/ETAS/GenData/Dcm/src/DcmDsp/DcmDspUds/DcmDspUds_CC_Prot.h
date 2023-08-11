

#ifndef DCMDSPUDS_CC_PROT_H
#define DCMDSPUDS_CC_PROT_H

typedef enum
{
    DCM_DSP_CC_INITIAL  = 1,
    DCM_DSP_CC_CHECKDATA,
    DCM_DSP_CC_PROCESSSERVICE,
    DCM_DSP_CC_ERROR
}Dcm_CCStateType_ten;

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF))
extern void Dcm_Lok_DspCommCntrlConfirmation(
	Dcm_IdContextType dataIdContext_u8,
	PduIdType dataRxPduId_u8,
	uint16 dataSourceAddress_u16,
	Dcm_ConfirmationStatusType status_u8
														 );

LOCAL_INLINE boolean Dcm_Lok_CC_IsSupportedInSession( Dcm_SesCtrlType ActiveSession_u8)
{

    uint8_least idxIndex_qu8;
    uint8 nrSessions_u8;
    boolean flgStatus_b;
    uint32 sessioncheck_u32;

    uint32 dataSessionsAllowed_u32;
    uint8 nrService_u8;

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

                 nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;

                  for(idxIndex_qu8 = 0x0; idxIndex_qu8 < nrService_u8 ; idxIndex_qu8++)
                  {

                      if(( Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].sid_u8 == DCM_DSP_SID_COMMUNICATIONCONTROL)&&(Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].servicelocator_b !=FALSE ) )
                      {

                          break;
                      }
                  }
                  dataSessionsAllowed_u32 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].allowed_session_b32;
                  sessioncheck_u32=(Dcm_DsldGetActiveSessionMask_u32() &  dataSessionsAllowed_u32);
                  if((idxIndex_qu8 >= nrService_u8) || ( sessioncheck_u32== 0u))
                  {

                      flgStatus_b = FALSE;
                  }

            }

return flgStatus_b;
}

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

