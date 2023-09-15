

#include "DcmDspUds_Iocbi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Iocbi_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

static Dcm_DspIOCBIStates_ten Dcm_stDspIocbiState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 Dcm_dataDspIocbiCtrlParam_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_OpStatusType Dcm_stDspIocbiOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DIDIndexType_tst s_Dcm_idxIocbiDidIndexType_st;
static uint16 s_ActiveDid_u16;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_ReadSignalLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static boolean s_IsIOCBISubfuncCalled_b;
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
static boolean s_IocbiRteCallPlaced_b;
#endif
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
static boolean s_DcmReadLengthRteCallPlaced_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_NUM_IOCBI_DIDS != 0x0)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_Dsp_IocbiStatusType_tst DcmDsp_IocbiStatus_array[DCM_CFG_NUM_IOCBI_DIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Dsp_IOCBI_Ini(void){
    Dcm_NegativeResponseCodeType dataNegResCode_u8;
    Std_ReturnType dataRetIocbiFunc_u8;
   uint16_least idxIocbiIndex_u16;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   const Dcm_DataInfoConfig_tst * ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite * ptrIOSigConfig;

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
   const Type_CfgSwcServiceDcm_stDidExtended * ptrDidExtendedConfig;
#endif

   void * ptrIOCBIFnc;
   uint16_least idxDidSignal_u16;

#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
   uint8 ControlMask_u8;
   uint16 ControlMask_u16;
   uint32 ControlMask_u32;
   ControlMask_u8 = 0;
   ControlMask_u16 = 0;
   ControlMask_u32 = 0;
#endif

   idxDidSignal_u16 = 0;

    dataNegResCode_u8 = 0x00;
    dataRetIocbiFunc_u8 = 0x00;
    ptrDidConfig = NULL_PTR;
    ptrSigConfig = NULL_PTR;
    ptrIOSigConfig = NULL_PTR;
    ptrIOCBIFnc = NULL_PTR;

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
   if(Dcm_stDspIocbiOpStatus_u8 == DCM_PENDING)
   {
        ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrIOSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
        ptrDidExtendedConfig = ptrDidConfig->pcstDidExtended;

        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
        if((ptrSigConfig->idxDcmDspControlInfo_u16 > 0) && (ptrIOSigConfig->idxDcmDspIocbiInfo_u16 > 0))
        {

            s_IsIOCBISubfuncCalled_b = TRUE;
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT) && ((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x08u)==0x08u))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;

                if((ptrIOCBIFnc!= NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                            dataRetIocbiFunc_u8=(*(ShortTermAdjustment9_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment10_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment11_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment12_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                        dataRetIocbiFunc_u8=(*(ShortTermAdjustment2_pfct)(ptrIOCBIFnc))  (NULL_PTR,DCM_CANCEL, &dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment6_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment7_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment8_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }
                }
            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE) && ((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x04u)==0x04u ))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;

                if((ptrIOCBIFnc != NULL_PTR) &&  ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                            dataRetIocbiFunc_u8=(*(FreezeCurrentState9_pfct)(ptrIOCBIFnc)) (DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState10_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState11_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState12_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                        dataRetIocbiFunc_u8=(*(FreezeCurrentState2_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, &dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState6_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState7_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(FreezeCurrentState8_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }
                }
            }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT) && ((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x02u)==0x02u ))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;

                if((ptrIOCBIFnc != NULL_PTR) &&   ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                            dataRetIocbiFunc_u8 = (*(ResetToDefault9_pfct) (ptrIOCBIFnc))(DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(ResetToDefault10_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(ResetToDefault11_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(ResetToDefault12_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                {
                    if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                    {

                        dataRetIocbiFunc_u8 = (*(ResetToDefault2_pfct) (ptrIOCBIFnc))(DCM_CANCEL, &dataNegResCode_u8);
                    }
                    else
                    {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                        {

                            dataRetIocbiFunc_u8=(*(ResetToDefault6_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                        }
                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                        {

                            dataRetIocbiFunc_u8=(*(ResetToDefault7_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                        }
                        else
                        {

                            dataRetIocbiFunc_u8=(*(ResetToDefault8_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                        }
#endif
                    }
                }
            }
            }
#endif

            s_IsIOCBISubfuncCalled_b = FALSE;
            (void) dataRetIocbiFunc_u8;
        }
   }
#endif

   for(idxIocbiIndex_u16=0u;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
   {
        ptrDidConfig =&CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];
        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16 ;
   }
   if(s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b == DCM_PENDING)
   {
        ptrSigConfig = &Dcm_DspDataInfo_st[CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];

        if((ptrSigConfig->adrReadFnc_cpv!=NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)|| (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
        {

            s_IsIOCBISubfuncCalled_b = TRUE;
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
   		if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
   		{

            	dataRetIocbiFunc_u8 = (*(ReadFunc11_ptr) (ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL);
   		}
   		else
#endif
   		{

               dataRetIocbiFunc_u8 = (*(ReadFunc2_ptr) (ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL, NULL_PTR);
   		}

            s_IsIOCBISubfuncCalled_b = FALSE;
            (void) dataRetIocbiFunc_u8;
        }
   }

    Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
   	s_DcmReadLengthRteCallPlaced_b = FALSE;
#endif
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
   s_IocbiRteCallPlaced_b = FALSE;
#endif
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxIocbiDidIndexType_st);
    DCM_UNUSED_PARAM(dataNegResCode_u8);
    DCM_UNUSED_PARAM(idxIocbiIndex_u16);
    DCM_UNUSED_PARAM(Dcm_dataDspIocbiCtrlParam_u8);
    DCM_UNUSED_PARAM(ptrDidConfig);
    DCM_UNUSED_PARAM(ptrIOSigConfig);
    DCM_UNUSED_PARAM(ptrSigConfig);
    DCM_UNUSED_PARAM(ptrIOCBIFnc);
    DCM_UNUSED_PARAM(idxDidSignal_u16);
}

Std_ReturnType Dcm_DcmInputOutputControlByIdentifier(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
   uint32 dataLength_u32;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   const Dcm_DataInfoConfig_tst * ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite * ptrIOSigConfig;
   const Dcm_SignalDIDIocbiConfig_tst * ptrIOCBIsigConfig;
   const Type_CfgSwcServiceDcm_stDidExtended * ptrDidExtendedConfig;
    Dcm_Dsp_IocbiStatusType_tst * ptrIOCBIStatusArrayConfig;
   void * ptrIOCBIFnc;
   uint16 dataSignalLength_u16;
   uint16 posnSigByte_u16;
   uint16 dataControlMaskLen_u16;
   uint16 dataCtlMaskOffset_u16;
   uint16 nrDID_u16;
   uint16_least idxIocbiIndex_u16;
    Std_ReturnType dataIocbiExeResult_u8;
    Std_ReturnType dataRetGetDid_u8;
    Std_ReturnType dataValidateIoMaskStatus_u8;
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
#if((DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   != DCM_CFG_OFF) || (DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   != DCM_CFG_OFF) )
   uint8 ControlMask_u8;
   uint16 ControlMask_u16;
   uint32 ControlMask_u32;
#endif
#endif
   uint8 dataIoCtrlParam_u8;
   uint8 posnSigBit_u8;
   uint8 posnCtlMaskByte_u8;
   uint8 posnCtlMaskBit_u8;
   boolean isModeChkRetval_b;
   boolean flgProcessReq_b;
    Dcm_NegativeResponseCodeType dataNrc_u8;
    Std_ReturnType dataretVal_u8;
    Std_ReturnType dataFuncRetVal_u8;
    Std_ReturnType dataServretVal_u8;

    *dataNegRespCode_u8 = 0x00;
    dataNrc_u8 = 0x00;
    dataIocbiExeResult_u8 = E_OK;

    flgProcessReq_b = TRUE;
    dataFuncRetVal_u8 = E_OK;
    dataServretVal_u8=DCM_E_PENDING;
   idxIocbiIndex_u16=0;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_IOCBI_Ini();

        dataServretVal_u8 = E_OK;
   }
   else{

        switch(Dcm_stDspIocbiState_en)
        {
            case DCM_IOCBI_IDLE:
            {
                if(pMsgContext->reqDataLen >= DSP_IOCBI_MINREQLEN)
                {
                    if(pMsgContext->reqData[2] <= 3)
                    {
                        nrDID_u16 = (uint16)(DSP_CONV_2U8_TO_U16 (pMsgContext->reqData[0], pMsgContext->reqData[1]));

                        if(Dcm_Lok_GetIndexOfDID (nrDID_u16,&s_Dcm_idxIocbiDidIndexType_st) == E_OK)
                        {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

                            if((s_Dcm_idxIocbiDidIndexType_st.dataRange_b==FALSE) && (*Dcm_DIDIsAvail[CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                            {
                                if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(nrDID_u16)!=E_OK)
                                {

                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                }
                            }
#endif
                            Dcm_DidSignalIdx_u16 = 0x0;
                            Dcm_ReadSignalLength_u16 = 0x0;

                            for(idxIocbiIndex_u16=0u;((idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS) && (*dataNegRespCode_u8 ==0x00u ));idxIocbiIndex_u16++)
                            {
                                if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16)
                                {
                                    ptrDidConfig = &CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];
                                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16 ;
                                }
                            }

                            if((flgProcessReq_b!= FALSE)&&(*dataNegRespCode_u8==0x00u))
                            {
                                Dcm_stDspIocbiState_en = DCM_IOCBI_CHKSUPPORT;
                            }
                        }
                        else
                        {
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                        DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_INVALID_CONTROL_PARAM)
                    }
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
                if(*dataNegRespCode_u8 != 0x0)
                {
                    break;
                }
            }

            case DCM_IOCBI_CHKSUPPORT:
            {
                ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];

                if((Dcm_DsldGetActiveSessionMask_u32()& (ptrDidConfig->pcstDidExtended->dataSessBitMask_u32))!= 0x00uL)
                {

                    nrDID_u16 = (uint16)(DSP_CONV_2U8_TO_U16 (pMsgContext->reqData[0], pMsgContext->reqData[1]));
                    while((Dcm_DidSignalIdx_u16<ptrDidConfig->nrSig_u16) && (*dataNegRespCode_u8==0u))
                    {
                        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                        ptrIOSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
                        ptrIOCBIsigConfig = &Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16];

                        if((ptrSigConfig->idxDcmDspControlInfo_u16 >0u) && (ptrIOSigConfig->idxDcmDspIocbiInfo_u16>0u))
                        {

                            if((pMsgContext->reqData[2] == DCM_IOCBI_SHORTTERMADJUSTMENT) && ((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x08u)==0x08u ))
                            {

                                if( ((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrShortTermAdjustment_cpv == NULL_PTR))
                                {

                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                                    {
                                        if((USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8) && ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
                                    else
                                    {
                                        if(((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == ptrDidConfig->didUsePort_u8) || (USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == ptrDidConfig->didUsePort_u8)) && (NULL_PTR == ptrDidConfig->ioControlRequest_cpv))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_FREEZECURRENTSTATE)&& ((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x04u)==0x04u ) )
                            {

                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrFreezeCurrentState_cpv == NULL_PTR))
                                {

                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                                    {
                                        if((USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8) && ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
                                    else
                                    {
                                        if(((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == ptrDidConfig->didUsePort_u8) || (USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == ptrDidConfig->didUsePort_u8)) && (NULL_PTR == ptrDidConfig->ioControlRequest_cpv))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_RESETTODEFAULT) &&((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x02u)==0x02u ))
                            {
                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrResetToDefault_cpv == NULL_PTR))
                                {

                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                                    {
                                        if((USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8) && ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
                                    else
                                    {
                                        if(((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == ptrDidConfig->didUsePort_u8) || (USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == ptrDidConfig->didUsePort_u8)) && (NULL_PTR == ptrDidConfig->ioControlRequest_cpv))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_RETURNCONTROLTOECU) &&((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x01u)==0x01u ))
                            {

                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrReturnControlEcu_cpv == NULL_PTR))
                                {

                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                                    {
                                        if((USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8) && ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
                                    else
                                    {
                                        if(((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == ptrDidConfig->didUsePort_u8) || (USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == ptrDidConfig->didUsePort_u8)) && (NULL_PTR == ptrDidConfig->ioControlRequest_cpv))
                                        {

                                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        }
                                    }
#endif
                                }
                            }
                            else
                            {

                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                            }
                        }
                        else
                        {

                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                            DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                        }
   				 Dcm_DidSignalIdx_u16++;
                    }
                    if(*dataNegRespCode_u8 == 0x00)
                    {

                        dataControlMaskLen_u16 = 0x0;
                        dataLength_u32 = 0x0;
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)

                        if(pMsgContext->reqData[2] == DCM_IOCBI_SHORTTERMADJUSTMENT)
                        {

                            s_IsIOCBISubfuncCalled_b = TRUE;

                            dataFuncRetVal_u8=Dcm_GetLengthOfDIDIndex(&s_Dcm_idxIocbiDidIndexType_st,&dataLength_u32,nrDID_u16);

                            s_IsIOCBISubfuncCalled_b = FALSE;
                        }
#endif
                        if(dataFuncRetVal_u8==E_OK)
                        {

                            ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                            ptrDidExtendedConfig = ptrDidConfig->pcstDidExtended;
                            if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_NO)
                            {
                                dataControlMaskLen_u16 = ptrDidExtendedConfig->dataCtrlMaskSize_u8;
                            }

                            if((pMsgContext->reqDataLen-3u) != (dataLength_u32 + dataControlMaskLen_u16))
                            {
                                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                            }
                            else
                            {

                                if((dataLength_u32 != 0u) || (dataControlMaskLen_u16 != 0u))
                                {

                                    dataValidateIoMaskStatus_u8 = DcmAppl_DcmCheckControlMaskAndState(nrDID_u16,pMsgContext->reqData[2],&(pMsgContext->reqData[3]),(uint16)(pMsgContext->reqDataLen-3u));
                                    if(dataValidateIoMaskStatus_u8 != E_OK)
                                    {
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_INVALID_CONTROL_DATA)
                                    }
                                }
                            }

                        }

                        else if(dataFuncRetVal_u8 == DCM_INFRASTRUCTURE_ERROR)
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                        else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                        {

                        }
                        else
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                    }
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION)
                }

                if((*dataNegRespCode_u8 == 0x0) && (dataFuncRetVal_u8 != DCM_E_PENDING))
                {
                    Dcm_stDspIocbiState_en = DCM_IOCBI_CHKCOND;

                    Dcm_DidSignalIdx_u16 = 0x0;
                }
                else{
                    break;
                }
            }

            case DCM_IOCBI_CHKCOND:
            {
                if(*dataNegRespCode_u8 == 0)
                {
                    ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                    ptrDidExtendedConfig = ptrDidConfig->pcstDidExtended;

                    if((Dcm_DsldGetActiveSecurityMask_u32()& (ptrDidExtendedConfig->dataSecBitMask_u32))!=0x00uL)
                    {

                        isModeChkRetval_b = TRUE;
                        if(ptrDidExtendedConfig->adrUserControlModeRule_pfct!=NULL_PTR)
                        {

                            dataFuncRetVal_u8 = (*ptrDidExtendedConfig->adrUserControlModeRule_pfct)(&dataNrc_u8,ptrDidConfig->dataDid_u16,DCM_SUPPORT_IOCONTROL);
                        }
                        else
                        {

                            dataFuncRetVal_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,ptrDidConfig->dataDid_u16,DCM_SUPPORT_IOCONTROL);
                        }
                        if(dataFuncRetVal_u8!=E_OK)
                        {
                            if(dataNrc_u8==0x00)
                            {
                                dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            }

                            isModeChkRetval_b = FALSE;
                        }
                        else
                        {
                            dataNrc_u8=0;
                        }
#if(DCM_CFG_DSP_MODERULEFORDIDCONTROL!=DCM_CFG_OFF)
                        if((dataNrc_u8==0x00 ) &&(NULL_PTR != ptrDidExtendedConfig->adrIocbiModeRuleChkFnc_pfct))
                        {
                            isModeChkRetval_b = (*(ptrDidExtendedConfig->adrIocbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                        }
#endif

                        if(FALSE!= isModeChkRetval_b)
                        {

                            if(pMsgContext->resMaxDataLen >= (uint16)(ptrDidConfig->dataMaxDidLen_u16+3u))
                            {
                                Dcm_stDspIocbiState_en = DCM_IOCBI_RUNNING;
                            }
                            else
                            {
                                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                            }
                        }
                        else
                        {
                            *dataNegRespCode_u8 = dataNrc_u8;
                        }
                    }
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                    }
                }
                if(*dataNegRespCode_u8 != 0x0)

                {
                    break;
                }
            }

            case DCM_IOCBI_RUNNING:
            {
                ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                ptrDidExtendedConfig = ptrDidConfig->pcstDidExtended;

                dataIoCtrlParam_u8 = pMsgContext->reqData[2];
                Dcm_dataDspIocbiCtrlParam_u8 = pMsgContext->reqData[2];
                if(ptrDidConfig->pcstDidExtended->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                {

                    dataCtlMaskOffset_u16 = (uint16)(pMsgContext->reqDataLen - ((uint32)((ptrDidConfig->nrSig_u16-1u)/8u) + 1u));

                    while((Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16)&&(*dataNegRespCode_u8==0x0u))
                    {
                        posnCtlMaskBit_u8 = 0x80;
                        if(ptrDidConfig->nrSig_u16 > 1u)
                        {

                            posnSigByte_u16 = (uint16)(Dcm_DidSignalIdx_u16/8u);

                            posnSigBit_u8 = (uint8)(Dcm_DidSignalIdx_u16%8);

                            posnCtlMaskByte_u8 = pMsgContext->reqData[dataCtlMaskOffset_u16 + posnSigByte_u16];

                            posnCtlMaskBit_u8 = (uint8)(((uint8)(posnCtlMaskByte_u8 << posnSigBit_u8)) & ((uint8)0x80));

                        }

                        s_IsIOCBISubfuncCalled_b = TRUE;

                        dataFuncRetVal_u8=Dcm_GetLengthOfSignal(&dataSignalLength_u16);

                        s_IsIOCBISubfuncCalled_b = FALSE;
                        if(dataFuncRetVal_u8 == E_OK)
                        {

                        }
                        else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                        {

                            dataIocbiExeResult_u8= DCM_E_PENDING;
                            break;
                        }

                        else
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }

                        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
                        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                        ptrIOSigConfig= &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];

                        if((posnCtlMaskBit_u8 == 0x80) && (*dataNegRespCode_u8 == 0x00))
                        {
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)

                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;

                                if(ptrIOCBIFnc != NULL_PTR)
                                {

                                    s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment1_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],dataNegRespCode_u8);
                                    }

#endif
#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {

                                            if(!s_IocbiRteCallPlaced_b)
                                            {

                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment9_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {

                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {

                                                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustmentResults_cpv;

                                               dataIocbiExeResult_u8=(*(ShortTermAdjustment13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {

                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment2_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],Dcm_stDspIocbiOpStatus_u8, dataNegRespCode_u8);
                                       }
                                    }

#endif

                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;

                                if(ptrIOCBIFnc != NULL_PTR)
                                {

                                    s_IsIOCBISubfuncCalled_b = TRUE;

                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {

                                        dataIocbiExeResult_u8=(*(FreezeCurrentState1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }

                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {

                                            if(!s_IocbiRteCallPlaced_b)
                                            {

                                                 dataIocbiExeResult_u8=(*(FreezeCurrentState9_pfct)(ptrIOCBIFnc)) (Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {

                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {

                                                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                                 ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentStateResults_cpv;

                                               dataIocbiExeResult_u8=(*(FreezeCurrentState13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {

                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {

                                        dataIocbiExeResult_u8=(*(FreezeCurrentState2_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);
                                         }
                                    }

                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;

                                if(ptrIOCBIFnc != NULL_PTR)
                                {

                                    s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED== DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {

                                        dataIocbiExeResult_u8=(*(ResetToDefault1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }
#endif

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {

                                            if(!s_IocbiRteCallPlaced_b)
                                            {

                                                 dataIocbiExeResult_u8=(*(ResetToDefault9_pfct)(ptrIOCBIFnc)) (Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {

                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {

                                                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                               ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefaultResults_cpv;

                                               dataIocbiExeResult_u8=(*(ResetToDefault13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {

                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {

                                            dataIocbiExeResult_u8=(*(ResetToDefault2_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);
                                        }
                                    }
#endif

                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;

                                if(ptrIOCBIFnc != NULL_PTR)
                                {

                                    s_IsIOCBISubfuncCalled_b = TRUE;

                                    if( (ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER))
                                    {

                                        dataIocbiExeResult_u8=(*(ReturnControlEcu1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }

                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }

                            if((Dcm_IsInfrastructureErrorPresent_b(dataIocbiExeResult_u8) != FALSE) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
                            {

                                *dataNegRespCode_u8 =DCM_E_GENERALREJECT;
                            }
                            else if(dataIocbiExeResult_u8 == E_OK)
                            {
                                *dataNegRespCode_u8 = 0x00;
                            }
                            else
                            {

                                break;
                            }
                        }

                        if((dataIocbiExeResult_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00) )
                        {
                            Dcm_ReadSignalLength_u16 += dataSignalLength_u16;
                        }

   				Dcm_DidSignalIdx_u16++;
                    }

                    if((E_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    {
                        Dcm_stDspIocbiState_en = DCM_IOCBI_READSTREC;

                        Dcm_DidSignalIdx_u16 = 0x0;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;

                    }
                    else if((E_NOT_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        break;
                    }
                    else
                    {
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;

                        if(DCM_E_PENDING == dataIocbiExeResult_u8)
                        {
                            *dataNegRespCode_u8 = 0x00;
                            dataServretVal_u8=DCM_E_PENDING;
                            Dcm_stDspIocbiOpStatus_u8 = DCM_PENDING;
                        }
                        break;
                    }
                }
                else if(ptrDidConfig->pcstDidExtended->dataCtrlMask_en == DCM_CONTROLMASK_EXTERNAL)
                {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                    dataFuncRetVal_u8=Dcm_GetLengthOfSignal(&dataSignalLength_u16);
                    if(dataFuncRetVal_u8 == E_OK)
                    {

                    }
                    else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                    {

                        dataIocbiExeResult_u8= DCM_E_PENDING;
                        dataServretVal_u8=DCM_E_PENDING;
                        break;
                    }
                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }

                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
                    ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                    ptrIOSigConfig= &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER))
                    {
                        if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                        {

                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].ioControlRequest_cpv;
                        }
                        else
                        {

                            ptrIOCBIFnc= ptrDidConfig->ioControlRequest_cpv;
                        }

                        if(ptrIOCBIFnc != NULL_PTR)
                        {

                            s_IsIOCBISubfuncCalled_b = TRUE;

                            dataIocbiExeResult_u8 =(*(IOControlrequest_pfct)(ptrIOCBIFnc))(Dcm_dataDspIocbiCtrlParam_u8,&pMsgContext->reqData[DSP_IOCBI_MINREQLEN],dataSignalLength_u16,ptrDidExtendedConfig->dataCtrlMaskSize_u8,Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);

                            s_IsIOCBISubfuncCalled_b = FALSE;
                        }
                    }
                    else
#endif
                    {
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)

                        if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;

                            if(ptrIOCBIFnc != NULL_PTR)
                            {

                                s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   == DCM_CFG_ON)

                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment3_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment4_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment5_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {

                                    }
                                }
#endif
#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {

#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        if(!s_IocbiRteCallPlaced_b)
                                        {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment10_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment11_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment12_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {

                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {

                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                            ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustmentResults_cpv;

                                            dataIocbiExeResult_u8=(*(ShortTermAdjustment13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                               s_IocbiRteCallPlaced_b = FALSE;
                                               *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment6_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment7_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment8_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {

                                        }
                                    }
                                }
#endif

                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }

                        }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)

                        if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;

                            if(ptrIOCBIFnc != NULL_PTR)
                            {

                                s_IsIOCBISubfuncCalled_b = TRUE;

                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                        dataIocbiExeResult_u8=(*(FreezeCurrentState3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(FreezeCurrentState4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(FreezeCurrentState5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {

                                    }
                                }

                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {

#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {

                                        if(!s_IocbiRteCallPlaced_b)
                                        {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                                dataIocbiExeResult_u8=(*(FreezeCurrentState10_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(FreezeCurrentState11_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(FreezeCurrentState12_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {

                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {

                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentStateResults_cpv;

                                                dataIocbiExeResult_u8=(*(FreezeCurrentState13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                               s_IocbiRteCallPlaced_b = FALSE;
                                               *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                            dataIocbiExeResult_u8=(*(FreezeCurrentState6_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                        }
                                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                        {
                                            ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                            dataIocbiExeResult_u8=(*(FreezeCurrentState7_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                        }
                                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                        {
                                            ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                    pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                            dataIocbiExeResult_u8=(*(FreezeCurrentState8_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                        }
                                        else
                                        {

                                        }
                                    }
                                }

                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)

                        if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;

                            if(ptrIOCBIFnc != NULL_PTR)
                            {

                                s_IsIOCBISubfuncCalled_b = TRUE;
#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED== DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                        dataIocbiExeResult_u8=(*(ResetToDefault3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ResetToDefault4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ResetToDefault5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {

                                    }
                                }
#endif

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {

#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {

                                        if(!s_IocbiRteCallPlaced_b)
                                        {

                                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                            {
                                               ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                                dataIocbiExeResult_u8=(*(ResetToDefault10_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(ResetToDefault11_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                                dataIocbiExeResult_u8=(*(ResetToDefault12_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {

                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {

                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                            ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefaultResults_cpv;

                                            dataIocbiExeResult_u8=(*(ResetToDefault13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                               s_IocbiRteCallPlaced_b = FALSE;
                                               *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                            dataIocbiExeResult_u8=(*(ResetToDefault6_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                        }
                                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                        {
                                            ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                            dataIocbiExeResult_u8=(*(ResetToDefault7_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                        }
                                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                        {
                                            ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                            pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                            dataIocbiExeResult_u8=(*(ResetToDefault8_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                        }
                                        else
                                        {

                                        }
                                    }
                                }
#endif

                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }
#endif

                        if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;

                            if(ptrIOCBIFnc != NULL_PTR)
                            {

                                s_IsIOCBISubfuncCalled_b = TRUE;

                                if((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)&& (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];

                                        dataIocbiExeResult_u8=(*(ReturnControlEcu3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ReturnControlEcu4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)]
   ,                                       pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);

                                        dataIocbiExeResult_u8=(*(ReturnControlEcu5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {

                                    }
                                }

                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }

                    }
                    if(E_OK == dataIocbiExeResult_u8)
                    {
                        Dcm_stDspIocbiState_en = DCM_IOCBI_READSTREC;

                        Dcm_DidSignalIdx_u16 = 0x0;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        Dcm_ReadSignalLength_u16 = dataSignalLength_u16;
                    }
                    else if((E_NOT_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        Dcm_ReadSignalLength_u16=0;
                        break;
                    }
                    else
                    {
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        if(DCM_E_PENDING == dataIocbiExeResult_u8)
                        {
                            *dataNegRespCode_u8 = 0x00;
                            dataServretVal_u8=DCM_E_PENDING;
                            Dcm_stDspIocbiOpStatus_u8 = DCM_PENDING;
                        }
                        break;
                    }
#endif
                }
                else{

                    dataServretVal_u8=E_NOT_OK;
                }
            }

            case DCM_IOCBI_READSTREC:
            {
                dataIoCtrlParam_u8 = pMsgContext->reqData[2];

                s_IsIOCBISubfuncCalled_b = TRUE;

                dataRetGetDid_u8 = Dcm_GetDIDData(&s_Dcm_idxIocbiDidIndexType_st,&pMsgContext->resData[3]);

                s_IsIOCBISubfuncCalled_b = FALSE;

                if(dataRetGetDid_u8 == E_OK)
                {

                    for(idxIocbiIndex_u16=0;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
                    {
                        ptrIOCBIStatusArrayConfig=&DcmDsp_IocbiStatus_array[idxIocbiIndex_u16];
                        if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == ptrIOCBIStatusArrayConfig->idxindex_u16)
                        {
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_IDLESTATE;
                            }
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RTD_ACTIVE;
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_FCS_ACTIVE;
                            }
#endif
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_STA_ACTIVE;
                            }
#endif
                        }
                    }

                    Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                    s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
                    s_Dcm_idxIocbiDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;

                    pMsgContext->resData[0] = pMsgContext->reqData[0];
                    pMsgContext->resData[1] = pMsgContext->reqData[1];
                    pMsgContext->resData[2] = dataIoCtrlParam_u8;
                    pMsgContext->resDataLen = Dcm_ReadSignalLength_u16+DSP_IOCBI_MINREQLEN;
                    dataServretVal_u8=E_OK;
                }
                else if(dataRetGetDid_u8 == DCM_E_PENDING)
                {
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_PENDING;
                    dataServretVal_u8=DCM_E_PENDING;
                    Dcm_DidSignalIdx_u16 = s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16;

                    for(idxIocbiIndex_u16=0;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
                    {
                        ptrIOCBIStatusArrayConfig=&DcmDsp_IocbiStatus_array[idxIocbiIndex_u16];
                        if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == ptrIOCBIStatusArrayConfig->idxindex_u16)
                        {

                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RCE_PENDING;
                            }

#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RTD_PENDING;
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_FCS_PENDING;
                            }
#endif
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {

                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_STA_PENDING;
                            }
#endif
                        }
                    }
                }

                else{
                    if(dataRetGetDid_u8 == E_NOT_OK)
                    {

                        dataretVal_u8 = DcmAppl_DcmReadDataNRC(CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].dataDid_u16,CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].pcstSignalDid[Dcm_DidSignalIdx_u16].posnSigBit_u16,dataNegRespCode_u8);
                        if(dataretVal_u8!=E_OK)
                        {

                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                    }
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }
                    s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
                    s_Dcm_idxIocbiDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                }
                break;
            }

            default:
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                break;
            }
        }

        if(*dataNegRespCode_u8 != 0x00 )
        {
            Dcm_DidSignalIdx_u16 = 0x0;
            dataServretVal_u8 = E_NOT_OK;
            Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
        }
   }
    return dataServretVal_u8;
}

void Dcm_ResetActiveIoCtrl(uint32 dataSessionMask_u32,
uint32 dataSecurityMask_u32,
boolean flgSessChkReqd_b)
{

   uint16 idxIocbiIndex_u16;
   uint16 idxSig_u16;
    Std_ReturnType dataRetIocbiFunc_u8;
    Dcm_NegativeResponseCodeType dataNegResCode_u8;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   const Dcm_DataInfoConfig_tst * ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite * ptrIOSigConfig;
   const Type_CfgSwcServiceDcm_stDidExtended * ptrDidExtendedConfig;
   void * ptrIOCBIFnc;
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
   uint8 ControlMask_u8;
   uint16 ControlMask_u16;
   uint32 ControlMask_u32;

   ControlMask_u8 = 0xFFu;
   ControlMask_u16 = 0xFFFFu;
   ControlMask_u32 = 0xFFFFFFFFu;
#endif
    dataRetIocbiFunc_u8 = E_NOT_OK;
    dataNegResCode_u8 = 0x00;

   for(idxIocbiIndex_u16 = 0; idxIocbiIndex_u16 < DCM_CFG_NUM_IOCBI_DIDS; idxIocbiIndex_u16++)
   {

        if((DCM_IOCBI_IDLESTATE != DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].IocbiStatus_en)                                                                           &&     \
                (CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].pcstDidExtended->dataIocbirst_b  != FALSE)                                    &&     \
                (((0x0u == ((CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].pcstDidExtended->dataSecBitMask_u32)  & dataSecurityMask_u32)))   ||     \
                        (((flgSessChkReqd_b) && (0x0u  == ((CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].pcstDidExtended->dataSessBitMask_u32) & dataSessionMask_u32))))))

        {
            ptrDidConfig = &CfgSwcServiceDcm_astListDid[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];

            for(idxSig_u16 = 0; idxSig_u16 < ptrDidConfig->nrSig_u16; idxSig_u16++)
            {
                ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[idxSig_u16].idxDcmDspDatainfo_u16];
                ptrIOSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];

#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                if(((USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8) && ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER))) || \
                   ((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == ptrDidConfig->didUsePort_u8)||(USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == ptrDidConfig->didUsePort_u8)))

                {
                    if(FALSE == ptrDidConfig->AtomicorNewSRCommunication_b)
                    {
                        ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].ioControlRequest_cpv;
                    }
                    else
                    {
                        ptrIOCBIFnc= ptrDidConfig->ioControlRequest_cpv;
                    }

                    if(ptrIOCBIFnc != NULL_PTR)
                    {

                        s_IsIOCBISubfuncCalled_b = TRUE;

                        dataRetIocbiFunc_u8 =(*(IOControlrequest_pfct)(ptrIOCBIFnc))(DCM_RETURN_CONTROL_TO_ECU,NULL_PTR,0,0,DCM_INITIAL,&dataNegResCode_u8);

                        s_IsIOCBISubfuncCalled_b = FALSE;
                    }
                    ptrIOCBIFnc = NULL_PTR;
                    (void)dataRetIocbiFunc_u8;
                    (void)dataNegResCode_u8;
                }

#endif
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;
                ptrDidExtendedConfig = ptrDidConfig->pcstDidExtended;

                if(((ptrDidConfig->pcstDidExtended->statusmaskIOControl_u8 & 0x01u) > 0u)
                        && (ptrIOCBIFnc != NULL_PTR))
                {
                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;

                    s_IsIOCBISubfuncCalled_b = TRUE;

                    if((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)
                            && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE))
                    {
                        if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {

                            dataRetIocbiFunc_u8 = (*(ReturnControlEcu1_pfct) (ptrIOCBIFnc))(&dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {

                                dataRetIocbiFunc_u8=(*(ReturnControlEcu3_pfct)(ptrIOCBIFnc)) (ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {

                                dataRetIocbiFunc_u8=(*(ReturnControlEcu4_pfct)(ptrIOCBIFnc)) (ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {

                                dataRetIocbiFunc_u8=(*(ReturnControlEcu5_pfct)(ptrIOCBIFnc)) (ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }

                    if(E_OK == dataRetIocbiFunc_u8)
                    {

                        DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].IocbiStatus_en = DCM_IOCBI_IDLESTATE;
                    }

                    s_IsIOCBISubfuncCalled_b = FALSE;
                    (void) dataNegResCode_u8;
                }
            }
        }

   }

    (void) dataSessionMask_u32;
    (void) dataSecurityMask_u32;
    (void) flgSessChkReqd_b;
}

Std_ReturnType Dcm_GetLengthOfSignal(uint16 * dataSigLength_u16)
{
   uint32 dataSigLength_u32;
    Std_ReturnType dataRetVal_u8;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   const Dcm_DataInfoConfig_tst * ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite * ptrIOSigConfig;
   void * ptrReadDataLenFnc;

    dataRetVal_u8 = E_NOT_OK;
    *dataSigLength_u16 = 0x0;
    ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
   if((ptrDidConfig->didUsePort_u8 == USE_ATOMIC_SENDER_RECEIVER_INTERFACE) || (ptrDidConfig->didUsePort_u8 == USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE))
   {
        while(Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16)
        {
            ptrSigConfig= &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
#if(DCM_CFG_DSP_CONTROL_FIXED_LEN_ENABLED != DCM_CFG_OFF)

            *dataSigLength_u16 += ptrSigConfig->dataSize_u16;
#endif
            Dcm_DidSignalIdx_u16++;
        }
        Dcm_DidSignalIdx_u16=0x0;
        dataRetVal_u8 = E_OK;
   }
   else{
        ptrSigConfig= &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrIOSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
        ptrReadDataLenFnc = ptrIOSigConfig->adrReadDataLengthFnc_pfct;

        if((ptrSigConfig->idxDcmDspControlInfo_u16 >0)&& (ptrReadDataLenFnc != NULL_PTR))
        {
#if(DCM_CFG_DSP_CONTROL_VAR_LEN_ENABLED != DCM_CFG_OFF)

            if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
            {

                dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrReadDataLenFnc))(dataSigLength_u16);
            }
            else{
                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if(!s_DcmReadLengthRteCallPlaced_b)
                        {

                            dataRetVal_u8 = (*(ReadDataLengthFnc6_pf)(ptrReadDataLenFnc))(s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b);
                            if(dataRetVal_u8 == E_OK)
                            {

                                s_DcmReadLengthRteCallPlaced_b = TRUE;
                                dataRetVal_u8 = DCM_E_PENDING;
                            }
                        }
                        else
                        {
                            ptrReadDataLenFnc = ptrIOSigConfig->adrReadDataLengthFncResults_pfct;

                            dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrReadDataLenFnc))(dataSigLength_u16);

                            if(dataRetVal_u8 == E_OK)
                            {
                                s_DcmReadLengthRteCallPlaced_b = FALSE;
                            }
                            else if(dataRetVal_u8 == RTE_E_NO_DATA)
                            {
                                dataRetVal_u8 = DCM_E_PENDING;
                            }
                            else
                            {

                                s_DcmReadLengthRteCallPlaced_b = FALSE;
                            }
                        }
                    }
                    else
#endif
                    {

                        dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrReadDataLenFnc))(s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b,dataSigLength_u16);
                    }
                }
            }
            if(dataRetVal_u8==E_OK)
            {

                if((*dataSigLength_u16 > ptrSigConfig->dataSize_u16) ||(*dataSigLength_u16==0))
                {
                    dataRetVal_u8 = E_NOT_OK;
                }
            }
            else if((dataRetVal_u8 == DCM_E_PENDING) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
            {
            }
            else{

                if((Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE)&&((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
                {
                    dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
                }
            }
#endif
        }
        else{
#if(DCM_CFG_DSP_CONTROL_FIXED_LEN_ENABLED != DCM_CFG_OFF)

            *dataSigLength_u16 = ptrSigConfig->dataSize_u16;
            dataRetVal_u8 = E_OK;
#endif
        }
   }

   if(dataRetVal_u8 == E_OK)
   {
        dataSigLength_u32=*dataSigLength_u16;
        *dataSigLength_u16=(uint16)dataSigLength_u32;
   }
    return dataRetVal_u8;
}

static void Dcm_SetFlagforIOCBI(boolean isFlag_b)
{

   s_IsIOCBISubfuncCalled_b = isFlag_b;
}

 void Dcm_Lok_DspIOCBIConfirmation(
 Dcm_IdContextType dataIdContext_u8,
 Type_SwcServiceCom_tIdPdu dataRxPduId_u8,
 uint16 dataSourceAddress_u16,
 Dcm_ConfirmationStatusType status_u8)
{
        if(dataIdContext_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)
        {

            Dcm_SetFlagforIOCBI(TRUE);
        }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  																status_u8);
        if(dataIdContext_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)
        {
            Dcm_SetFlagforIOCBI(FALSE);
        }
}

Std_ReturnType Dcm_GetActiveIOCBIDid(uint16 * dataDid_u16)
{

   if(s_IsIOCBISubfuncCalled_b != FALSE)
   {
        *dataDid_u16 = s_ActiveDid_u16;
        return (E_OK);
   }
   else{

        return E_NOT_OK;
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

