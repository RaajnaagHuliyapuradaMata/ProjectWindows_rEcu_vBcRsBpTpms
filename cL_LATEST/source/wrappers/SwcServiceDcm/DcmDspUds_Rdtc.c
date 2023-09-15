
#include "DcmDspUds_Rdtc_Inf.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dsp_RdtcDTC_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_DspRDTCSubFuncStates_ten Dcm_DspRDTCSubFunc_en;
#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)

Dcm_DspRDTCSubFunctionState_en RDTCExtendedandSnapshotDataState_en;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 Dcm_idxDspRDTCTab_u8;
uint8 ClientId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_DspRDTCRecordNum_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
Dcm_MsgLenType Dcm_DspRDTCMaxRespLen_u32;
Dcm_MsgLenType Dcm_DspRDTCFilledRespLen_u32;
Dcm_MsgLenType Dcm_DspTotalRespLenFilled_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_DspNumFltDTC_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_DspFirstPageSent_b;
boolean Dcm_DspFillZeroes_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_MsgType Dcm_DspRDTCRespBufPtr_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Dsp_ReadDTCInfo_Ini (void){

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)

   if(DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE == RDTCExtendedandSnapshotDataState_en)
   {
        //log DET as this should not happen
        DCM_DET_ERROR(DCM_RDTC_ID,DCM_E_ENABLEDTCRECORD_FAILED);
   }
#endif

#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

    Dcm_adrUpdatePage_pfct = NULL_PTR;
#endif
}

void Dcm_Lok_DspReadDTCInfoConfirmation(Dcm_IdContextType dataIdContext_u8
   ,                                                       Type_SwcServiceCom_tIdPdu dataRxPduId_u8
   ,                                                       uint16 dataSourceAddress_u16
   ,                                                       Dcm_ConfirmationStatusType status_u8)
{
#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

    Dcm_Dsp_ReadDTCInfo_Ini();
#endif
    DcmAppl_DcmConfirmation(dataIdContext_u8, dataRxPduId_u8,dataSourceAddress_u16, status_u8);
}

Std_ReturnType SwcServiceDcm_tReadDTCInformation (Dcm_SrvOpStatusType OpStatus
   ,                                    Dcm_MsgContextType * pMsgContext
   ,                                    Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
   uint8 dataRDTCSubFunc_u8;
    Std_ReturnType dataServRetval_u8;

   const Dcm_Dsld_SubServiceType * adrSubservice_pcst;

    *dataNegRespCode_u8 = 0x00;
    dataServRetval_u8 = DCM_E_PENDING;

   ClientId_u8 = Dcm_Lok_GetDemClientId(DCM_UDSCONTEXT);

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_ReadDTCInfo_Ini();

        dataServRetval_u8 = E_OK;
   }
   else{
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
        if(pMsgContext->msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
        {

            adrSubservice_pcst = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs[Dcm_DsldSrvIndex_u8].ptr_subservice_table_pcs;
        }
        else
#endif
        {

            adrSubservice_pcst = (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]).ptr_subservice_table_pcs;
        }

        if(Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {

            dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

   		Dcm_idxDspRDTCTab_u8=0;
            while((Dcm_idxDspRDTCTab_u8 < DCM_CFG_NUMRDTCSUBFUNC) )
            {

                if(adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].subservice_id_u8 == dataRDTCSubFunc_u8)
                {

                    break;
                }
            Dcm_idxDspRDTCTab_u8++;
            }

            if(adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b != FALSE)
            {

                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;

#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
                    RDTCExtendedandSnapshotDataState_en = DCM_RDTC_SUBFUNCTION_INITIAL;
#endif

                Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
            }
        }

        if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {

            dataServRetval_u8 = (*adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].SubFunc_fp)(OpStatus
   ,                                                                                      pMsgContext
   ,                                                                                      dataNegRespCode_u8);
        }
        if(adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b == FALSE)
        {

                    dataServRetval_u8 = (*adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].SubFunc_fp)(Dcm_ExtSrvOpStatus_u8
   ,                           pMsgContext
   ,                           dataNegRespCode_u8);
                    if(dataServRetval_u8 == DCM_E_PENDING)
                    {
                        Dcm_ExtSrvOpStatus_u8 = DCM_PENDING;
                    }
                    else
                    {
                        Dcm_ExtSrvOpStatus_u8 = DCM_INITIAL;
                    }
         }

        if((*dataNegRespCode_u8 != 0) && (adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b != FALSE))
        {

            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        }
   }
    return dataServRetval_u8;
}

#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

void Dcm_Dsp_RDTCUpdatePage(Dcm_MsgType PageBufPtr
   ,                                          Dcm_MsgLenType PageLen)
{

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
   {

        Dcm_DspRDTCSubFunc_en = (Dcm_DspFillZeroes_b == FALSE) ? DSP_RDTC_SFFILLRESP : DSP_RDTC_SFFILLZERO;

   }

    Dcm_DspRDTCMaxRespLen_u32 = PageLen;
    Dcm_DspRDTCRespBufPtr_u8 = PageBufPtr;
}

void Dcm_Dsp_RDTCFillZero(Dcm_MsgLenType RemTotalResLen )
{
   uint32_least nrResLen_qu32 ;
   uint32_least dataRemBuffer_qu32;

    Dcm_DspFillZeroes_b = TRUE;

    dataRemBuffer_qu32 = Dcm_DspRDTCMaxRespLen_u32 - Dcm_DspRDTCFilledRespLen_u32;

   if(RemTotalResLen != 0u)
   {

        if(RemTotalResLen > dataRemBuffer_qu32)
        {
            RemTotalResLen = dataRemBuffer_qu32;
        }
        dataRemBuffer_qu32 = RemTotalResLen + Dcm_DspRDTCFilledRespLen_u32;

        for(nrResLen_qu32=Dcm_DspRDTCFilledRespLen_u32; nrResLen_qu32< dataRemBuffer_qu32; nrResLen_qu32++)
        {
            Dcm_DspRDTCRespBufPtr_u8[nrResLen_qu32] = 0x0;
        }

        Dcm_DspTotalRespLenFilled_u32 += RemTotalResLen;

        Dcm_DspRDTCFilledRespLen_u32 += RemTotalResLen;
   }
}

boolean Dcm_IsProtocolIPCanFD(void){
    Dcm_ProtocolType activeProtocol_u8 = DCM_NO_ACTIVE_PROTOCOL;

   boolean retValue_b = TRUE;

    (void)Dcm_GetActiveProtocol(&activeProtocol_u8);

#if(DCM_CFG_CANFD_ENABLED==DCM_CFG_OFF)

   if((activeProtocol_u8==DCM_UDS_ON_CAN)||(activeProtocol_u8==DCM_ACEA_ON_CAN)|| \

       (activeProtocol_u8==DCM_KWP_ON_CAN)|| (activeProtocol_u8==DCM_OBD_ON_CAN))

   {

        retValue_b= FALSE;
   }
   else

#endif
   {
        if((activeProtocol_u8==DCM_UDS_ON_FLEXRAY)||(activeProtocol_u8==DCM_ACEA_ON_FLEXRAY)|| \

           (activeProtocol_u8==DCM_OBD_ON_FLEXRAY))

        {

            retValue_b= FALSE;
        }
   }
    return (retValue_b);
}

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif

