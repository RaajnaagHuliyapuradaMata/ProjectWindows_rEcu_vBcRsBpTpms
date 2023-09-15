#include "Std_Types.hpp"

#include "DcmDspUds_Rdtc_Inf.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.hpp"
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.hpp"
#endif
#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR( uint32, DCM_VAR)  Dsp_RdtcDTC_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR( Dcm_DspRDTCSubFuncStates_ten, DCM_VAR)  Dcm_DspRDTCSubFunc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(uint8, DCM_VAR) Dcm_idxDspRDTCTab_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16,     DCM_VAR) Dcm_DspMaxResDataLen_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8,     DCM_VAR) Dcm_DspRDTCRecordNum_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_MsgLenType, DCM_VAR)  Dcm_DspRDTCMaxRespLen_u32;
VAR(Dcm_MsgLenType, DCM_VAR)  Dcm_DspRDTCFilledRespLen_u32;
VAR(Dcm_MsgLenType, DCM_VAR)  Dcm_DspTotalRespLenFilled_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16,     DCM_VAR)  Dcm_DspNumFltDTC_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR(boolean,     DCM_VAR)  Dcm_DspFirstPageSent_b;
VAR(boolean,     DCM_VAR)  Dcm_DspFillZeroes_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_MsgType,    DCM_VAR)  Dcm_DspRDTCRespBufPtr_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_ReadDTCInfo_Ini (void){
    Dem_DcmCancelOperation();

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)

    (void)Dem_EnableDTCRecordUpdate();
#endif
#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

    Dcm_adrUpdatePage_pfct = NULL_PTR;
#endif
}

FUNC(void, DCM_CODE) Dcm_Lok_DspReadDTCInfoConfirmation(VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,     VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,     VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,     VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
#if(DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

    Dcm_Dsp_ReadDTCInfo_Ini();
#endif
    DcmAppl_DcmConfirmation(dataIdContext_u8, dataRxPduId_u8,dataSourceAddress_u16, status_u8);
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tReadDTCInformation (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint8, AUTOMATIC)             dataRDTCSubFunc_u8;
   VAR(Std_ReturnType, AUTOMATIC)    dataServRetval_u8;

   P2CONST(Dcm_Dsld_SubServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSubservice_pcst;

    *dataNegRespCode_u8 = 0x00;
    dataServRetval_u8 = DCM_E_PENDING;

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

                Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
            }
        }

        if((Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE) || \
            (adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b == FALSE))
        {

            dataServRetval_u8 = (*adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].SubFunc_fp)(OpStatus
   ,     pMsgContext
   ,     dataNegRespCode_u8);
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

FUNC(void,DCM_CODE) Dcm_Dsp_RDTCUpdatePage(VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr
   ,     VAR(Dcm_MsgLenType,AUTOMATIC) PageLen)
{

   if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
   {

        Dcm_DspRDTCSubFunc_en = (Dcm_DspFillZeroes_b == FALSE) ? DSP_RDTC_SFFILLRESP : DSP_RDTC_SFFILLZERO;

   }

    Dcm_DspRDTCMaxRespLen_u32 = PageLen;
    Dcm_DspRDTCRespBufPtr_u8 = PageBufPtr;
}

FUNC(void,DCM_CODE) Dcm_Dsp_RDTCFillZero(VAR(Dcm_MsgLenType,AUTOMATIC) RemTotalResLen )
{
   VAR(uint32_least, AUTOMATIC) nrResLen_qu32 ;
   VAR(uint32_least, AUTOMATIC) dataRemBuffer_qu32;

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

FUNC(boolean,DCM_CODE) Dcm_IsProtocolIPCanFD(void){
   VAR(Dcm_ProtocolType,AUTOMATIC) activeProtocol_u8 = DCM_NO_ACTIVE_PROTOCOL;

   VAR(boolean,AUTOMATIC) retValue_b = TRUE;

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

