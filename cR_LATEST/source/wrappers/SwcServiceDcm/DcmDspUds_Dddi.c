#include "Std_Types.hpp"

#include "DcmDspUds_Dddi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

VAR (Dcm_DddiDefineById_ten,DCM_VAR) Dcm_stAddIdRecords_en;

#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
static VAR (Dcm_DddiWriteOrClear_ten,DCM_VAR) s_isWriteOrClear_en;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16 ,DCM_VAR) Dcm_AddIdCurrentBlockIndex_u16;

static VAR (uint16,DCM_VAR) s_ActiveDDDI_u16;

#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint32,DCM_VAR) Dcm_AddIdCurrentLength_u32;

static VAR (uint32,DCM_VAR) s_dataLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspDddidOpStatus_u8;

static VAR (Std_ReturnType, DCM_VAR) s_dataFunctionRetVal_u8;

static VAR (Std_ReturnType, DCM_VAR) s_dataLengthFuncRetVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxSrcDidIndexType_st;
VAR (Dcm_DddiDefineByMem_ten,DCM_VAR) Dcm_stAddMemRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

VAR (uint16 ,     DCM_VAR) Dcm_AddMemCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_DddiServiceStatus_ten ,DCM_VAR)   Dcm_DspStDddi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(boolean,DCM_CODE)Dcm_DddiCheckOverflow(VAR(uint32,AUTOMATIC) MemLength_u32, VAR(uint32,AUTOMATIC) AddIdCurrentLength_u32, VAR(uint16,AUTOMATIC) MaxDidLen_u16);

static FUNC(boolean,DCM_CODE)Dcm_DddiCheckOverflow(VAR(uint32,AUTOMATIC) MemLength_u32, VAR(uint32,AUTOMATIC) AddIdCurrentLength_u32, VAR(uint16,AUTOMATIC) MaxDidLen_u16)
{
   VAR(boolean,AUTOMATIC) flag_b;
    flag_b = FALSE;

  if( (uint32)MaxDidLen_u16 > MemLength_u32)
  {
       if(((uint32)(MaxDidLen_u16) - ( MemLength_u32)) >= AddIdCurrentLength_u32)
       {
           flag_b = TRUE;
       }

       else{

       }
  }

  else{

  }
  return flag_b;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetDynamicSignalConfiguration(uint16 DidIndex_u16);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetDynamicSignalConfiguration(uint16 DidIndex_u16)
{
   VAR (uint32,     AUTOMATIC) dataSigLength_u32;
   VAR (uint16,     AUTOMATIC) dataSigLength_u16;
   VAR (uint16,     AUTOMATIC) index_u16;
   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR(boolean,     AUTOMATIC) stVariableLength_b;

    dataSigLength_u32   = 0x00;
    dataSigLength_u16   = 0x00;

   stVariableLength_b  = FALSE;
    dataRetVal_u8       = E_NOT_OK;

   for(index_u16=0;index_u16<Dcm_DIDConfig[DidIndex_u16].nrSig_u16;index_u16++)
   {

        if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataFixedLength_b   !=FALSE)
        {

            if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataType_u8!=DCM_BOOLEAN)
            {

                Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32=Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16;
                Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32=Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataSize_u16;
            }

            else{

                Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32  = (Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16/8)*8;

                Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = 8 ;
            }

            dataRetVal_u8=E_OK;
        }

        else if(stVariableLength_b==FALSE)
        {

            stVariableLength_b=TRUE;

            Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32 =Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16;
        }

        else{

            Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32 =Dcm_DynamicSignalConfig_cast[(index_u16-1)].sigPosnBit_u32+Dcm_DynamicSignalConfig_cast[(index_u16-1)].sigDataSize_u32;
        }

        if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataFixedLength_b   ==FALSE)
        {

            if(((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_FNC) || \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC) ||    \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) ||   \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)) &&     \
                    ((Dcm_DIDConfig[DidIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32 >0x00u) && (Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct != NULL_PTR)))

            {

                if(FALSE==Dcm_DIDConfig[DidIndex_u16].dataDynamicDid_b)
                {

                    if((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_FNC) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                    {
                        dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(&dataSigLength_u16);
                    }
                    else
                    {
                        if((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                ||  (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                        )
                        {

                            dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(s_Dcm_idxSrcDidIndexType_st.dataopstatus_b,&dataSigLength_u16);
                        }
                   }
                   Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = dataSigLength_u16*8uL;
                }
                else{

                    dataRetVal_u8 = (*(ReadDataLengthFnc2_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(&dataSigLength_u32);

                    Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = dataSigLength_u32*8uL;

                }

                if(dataRetVal_u8==E_OK)
                {

                    if(((Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 > Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataSize_u16) ||(Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32==0u)) &&(Dcm_DIDConfig[DidIndex_u16].dataDynamicDid_b == FALSE))
                    {
                        dataRetVal_u8 = E_NOT_OK;
                        break;
                    }
                }
                else if((dataRetVal_u8==DCM_E_PENDING) && ((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        ||  (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                ))
                {
                }
                else{

                }
            }
        }
   }
    return(dataRetVal_u8);
}

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

static FUNC(Std_ReturnType, DCM_CODE) Dcm_isDDDIDSupported(uint16 DynamicIdentifier_u16);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_isDDDIDSupported(uint16 DynamicIdentifier_u16)
{
   VAR(uint16,AUTOMATIC) index_u16;
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    retVal_u8 =E_OK;

   for(index_u16 =0x00;index_u16<Dcm_DIDcalculateTableSize_u16();index_u16++)
   {
        if(Dcm_DIDConfig[index_u16].dataDid_u16==DynamicIdentifier_u16)
        {
            break;
        }
   }
   if(index_u16==Dcm_DIDcalculateTableSize_u16())
   {
        retVal_u8= E_NOT_OK;
   }
   else{
        if(*Dcm_DIDIsAvail[Dcm_DIDConfig[index_u16].idxDIDSupportedFnc_u16]!=NULL_PTR)
        {
            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[index_u16].idxDIDSupportedFnc_u16]))(DynamicIdentifier_u16)!=E_OK)
            {
                retVal_u8 = E_NOT_OK;
            }
        }
   }
    return retVal_u8;
}
#endif

FUNC (void,DCM_CODE) Dcm_DDDI_Ini (void){
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED == DCM_CFG_OFF)
   VAR (uint32,AUTOMATIC) idxLoop_u32;

   VAR (uint16,AUTOMATIC) dataSize_u16= Dcm_DddiCalculateTableSize_u16 ();
   P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
#endif

   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) NegResCode_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataCondChkRetVal_u8;

    dataCondChkRetVal_u8 = E_OK;
    NegResCode_u8 = 0x0;

   if((Dcm_DspDddidOpStatus_u8 == DCM_PENDING) && (Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETSUPPORT))
   {
        if(((Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16 >0u) && (Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32 >0x00u))&&
                ((Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrCondChkRdFnc_cpv)!= NULL_PTR)&&
                ((Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) ||
                        (Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)))
        {

            dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrCondChkRdFnc_cpv))(DCM_CANCEL, &NegResCode_u8);
        }
   }
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
   if((Dcm_DspDddidOpStatus_u8 == DCM_PENDING)&&(Dcm_DspStDddi_en == DCM_DDDI_SENDRESP))
   {

        (void)DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR
   ,     s_ActiveDDDI_u16
   ,     DCM_CANCEL
   ,     s_isWriteOrClear_en);
   }

   s_ActiveDDDI_u16 = 0;
#else
   for(idxLoop_u32=0; idxLoop_u32<dataSize_u16;idxLoop_u32++)
   {

        stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDDDIRecordContext_pst;
        Dcm_DddiResetCompleteContext (stContext_st);
        stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataPDIRecordContext_pst;
        Dcm_DddiResetCompleteContext (stContext_st);
   }
#endif

    Dcm_DspStDddi_en  = DCM_DDDI_IDLE;

    Dcm_stAddIdRecords_en  = DCM_DDDI_DEFINE_BY_ID_INIT;
    Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;

    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxSrcDidIndexType_st);

    (void)dataCondChkRetVal_u8;
    (void)NegResCode_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDDDI (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (uint8, AUTOMATIC) dataSubFunction_u8;
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
   static VAR (uint16, AUTOMATIC) s_idxIndexForStore_u16;
   VAR (Std_ReturnType, AUTOMATIC) dataRetValFromNvMStorage_u8;
#endif
   VAR (uint16,AUTOMATIC) idxIndex_u16;
   VAR (uint32,AUTOMATIC) idxLoop_u32;
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8;

    *dataNegRespCode_u8             = 0;
   idxIndex_u16 = 0;
    dataRetVal_u8=DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_DDDI_Ini();

        dataRetVal_u8 = E_OK;
   }
   else{
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
    dataRetValFromNvMStorage_u8 = E_OK;
#endif
        if(Dcm_DspStDddi_en==DCM_DDDI_IDLE)
        {

            dataSubFunction_u8=pMsgContext->reqData[0];

            if(dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER)
            {
#if( DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                VAR (uint32,AUTOMATIC) idxRdpi_u32;
#endif

                if(pMsgContext->reqDataLen == DCM_DDDI_MIN_LENGTH)
                {

                    VAR (uint16,AUTOMATIC) nrIds_u16 = Dcm_DddiCalculateTableSize_u16 ();
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    for(idxLoop_u32=0; idxLoop_u32<nrIds_u16;idxLoop_u32++)
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
                        *dataNegRespCode_u8 =0x00;
                        if(Dcm_isDDDIDSupported(Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16)!=E_OK)
                        {

                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                        }
                        if(*dataNegRespCode_u8 ==0x00)
#endif
                        {
                            P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDDDIRecordContext_pst;

                            Dcm_DddiResetCompleteContext (stContext_st);
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataPDIRecordContext_pst;

                            Dcm_DddiResetCompleteContext (stContext_st);
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                            for(idxRdpi_u32=0;idxRdpi_u32<DCM_CFG_MAX_DID_SCHEDULER;idxRdpi_u32++)
                            {
                                if(Dcm_PeriodicInfo_st[idxRdpi_u32].dataId_u16==Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16)
                                {
                                    Dcm_PeriodicInfo_st[idxRdpi_u32].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                                    Dcm_NumOfActivePeriodicId_u8--;
                                }
                            }
#endif
                        }
                    }

                    Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                }

                else if((pMsgContext->reqDataLen) == (DCM_DDDI_MIN_LENGTH + 2u))
                {
                    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                    VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;

                    VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                    dataDid_u16  <<=  8u;
                    dataDid_u16   |= (uint16)pMsgContext->reqData[2];

                    dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);

                    if(dataFuncRetVal_u8==E_OK)
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                        if(Dcm_isDDDIDSupported(dataDid_u16)!=E_OK)
                        {

                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                        }
#endif
                        if(*dataNegRespCode_u8==0x00)
                        {

                            s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;

                            Dcm_DddiResetCompleteContext (stContext_st);
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;

                            Dcm_DddiResetCompleteContext (stContext_st);
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                            for(idxRdpi_u32=0;idxRdpi_u32<DCM_CFG_MAX_DID_SCHEDULER;idxRdpi_u32++)
                            {
                                if(Dcm_PeriodicInfo_st[idxRdpi_u32].dataId_u16==Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16)
                                {
                                    Dcm_PeriodicInfo_st[idxRdpi_u32].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                                    Dcm_NumOfActivePeriodicId_u8--;
                                }
                            }
#endif

                            Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                        }
                    }

                    else
                    {

                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                    }
                }

                else{
                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }

            else if(dataSubFunction_u8==DCM_DEFINITION_BY_ID)
            {

                VAR (uint32,AUTOMATIC) dataReqMsgLen_u32=((uint32)pMsgContext->reqDataLen)-3uL;

                if((dataReqMsgLen_u32>0u) && ((dataReqMsgLen_u32 % 4u)==0u))
                {
                    VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;

                    VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                    dataDid_u16  <<=  8u;
                    dataDid_u16   |= (uint16)pMsgContext->reqData[2];

                    dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);

                    if(dataFuncRetVal_u8==E_OK)
                    {
                        VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st;

                        dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&idxsrcDidIndexType_st);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

                        if((dataFuncRetVal_u8 == E_OK) && (idxsrcDidIndexType_st.dataRange_b == FALSE) && (*Dcm_DIDIsAvail[Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                        {
                            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                            {
                                dataFuncRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif
                        if(dataFuncRetVal_u8==E_OK)
                        {

                            if(((Dcm_DsldGetActiveSessionMask_u32() & \
                                    (Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32))!= 0x00uL))
                            {

                                if((Dcm_DsldGetActiveSecurityMask_u32()& \
                                        (Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSecRead_u32))!=0x00uL)
                                {
                                    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                                    P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst =Dcm_DDDIBaseConfig_cast[idxIndex_u16].addrRecord_pst;

                                    VAR (uint16,AUTOMATIC) nrBlocks_u16=(uint16)(dataReqMsgLen_u32/4uL);
                                    stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;

                                    if((nrBlocks_u16+(stContext_st->nrCurrentlyDefinedRecords_u16)) <=
                                            Dcm_DDDIBaseConfig_cast[idxIndex_u16].nrMaxNumOfRecords_u16)
                                    {

                                        P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8=&pMsgContext->reqData[3];

                                        s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)

                                        s_idxIndexForStore_u16 = idxIndex_u16;
#endif

                                        dataFuncRetVal_u8=Dcm_DcmDddiAddIdRecords_u8(nrBlocks_u16,stContext_st->nrCurrentlyDefinedRecords_u16
   ,     adrSourceBuffer_pcu8,adrRecord_pst,dataNegRespCode_u8,idxIndex_u16,(pMsgContext->resMaxDataLen-2u));

                                        if(dataFuncRetVal_u8==E_OK)
                                        {

                                            stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);
                                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;
                                            stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);

                                            Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                                            Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                                        }
                                        else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                                        {

                                            Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                                        }

                                        else
                                        {

                                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                            Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                                        }
                                    }

                                    else
                                    {

                                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_EXCEEDED_MAX_RECORDS )
                                    }
                                }

                                else
                                {

                                    *dataNegRespCode_u8      = DCM_E_SECURITYACCESSDENIED;
                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                }
                            }

                            else
                            {

                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                                DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION )
                            }
                        }

                        else
                        {

                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED)
                        }
                    }

                    else
                    {

                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                    }
                }
                else{

                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }

            else if(dataSubFunction_u8==DCM_DEFINITION_BY_MEMORYADDRESS)
            {

                if(pMsgContext->reqDataLen>=DCM_DDDI_MEMADDR_MINLEN)
                {

                    VAR (uint8,AUTOMATIC) dataAdrAndLenFormatIdentifier_u8 = pMsgContext->reqData[3];

                    VAR (uint8,AUTOMATIC) nrBytesForAddress_u8 = dataAdrAndLenFormatIdentifier_u8 & 0x0Fu;

                    VAR (uint8,AUTOMATIC) nrBytesForLength_u8 = (dataAdrAndLenFormatIdentifier_u8>>4u);

                    VAR (uint8,AUTOMATIC) dataBlockLen_u8 = nrBytesForAddress_u8 + nrBytesForLength_u8;

                    VAR (uint16,AUTOMATIC) dataReqMsgLen_u16 = (uint16)(pMsgContext->reqDataLen-4u);

                    if(( nrBytesForAddress_u8 == 0 ) || ( nrBytesForLength_u8 == 0 ) || ( nrBytesForAddress_u8 > 4 ) || ( nrBytesForLength_u8 > 4))
                    {

                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;

                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_INVALID_ADDRLENGTH_FORMAT )
                    }

                    else
                    {

                        if((dataReqMsgLen_u16%dataBlockLen_u8)==0)
                        {

                            VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;

                            VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                            dataDid_u16  <<=  8u;
                            dataDid_u16   |= (uint16)pMsgContext->reqData[2];

                            dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);

                            if(dataFuncRetVal_u8==E_OK)
                            {
                                VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxDidIndexType_st;

                                dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&idxDidIndexType_st);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

                                if((dataFuncRetVal_u8 == E_OK) && (idxDidIndexType_st.dataRange_b ==FALSE)&& (*Dcm_DIDIsAvail[Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                                {
                                    if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                                    {
                                        dataFuncRetVal_u8 = E_NOT_OK;
                                    }
                                }
#endif
                                if(dataFuncRetVal_u8==E_OK)
                                {

                                    if(((Dcm_DsldGetActiveSessionMask_u32() & \
                                            (Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32))!= 0x00uL))
                                    {

                                        if((Dcm_DsldGetActiveSecurityMask_u32()& \
                                                (Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSecRead_u32))!=0x00uL)
                                        {
                                            P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                                            P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst =
                                                    Dcm_DDDIBaseConfig_cast[idxIndex_u16].addrRecord_pst;

                                            VAR (uint16,AUTOMATIC) nrBlocks_u16 = (uint16)(dataReqMsgLen_u16/dataBlockLen_u8);

                                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;

                                            if((nrBlocks_u16+(stContext_st->nrCurrentlyDefinedRecords_u16)) <=
                                                    Dcm_DDDIBaseConfig_cast[idxIndex_u16].nrMaxNumOfRecords_u16)
                                            {
                                                P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8 = &pMsgContext->reqData[4];

                                                    s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)

                                                    s_idxIndexForStore_u16 = idxIndex_u16;
#endif

                                                dataFuncRetVal_u8=Dcm_DcmDddiAddMemRecords_u8(nrBlocks_u16,stContext_st->nrCurrentlyDefinedRecords_u16
   ,     adrSourceBuffer_pcu8,adrRecord_pst,dataNegRespCode_u8, nrBytesForAddress_u8,nrBytesForLength_u8
   ,     idxIndex_u16,(pMsgContext->resMaxDataLen-2u));

                                                if(dataFuncRetVal_u8==E_OK)
                                                {

                                                    stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);
                                                    stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;
                                                    stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);

                                                    Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                                                }
                                                else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                                                {

                                                }

                                                else
                                                {

                                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                                }
                                            }

                                            else
                                            {
                                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                            }
                                        }

                                        else
                                        {
                                            *dataNegRespCode_u8      = DCM_E_SECURITYACCESSDENIED;
                                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                        }
                                    }

                                    else
                                    {
                                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                    }
                                }
                                else
                                {
                                    *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                }
                            }

                            else
                            {
                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                            }
                        }

                        else
                        {
                            *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                        }
                    }
                }

                else{

                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }

            else{

                *dataNegRespCode_u8      = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
            }
        }

        if(Dcm_DspStDddi_en == DCM_DDDI_SENDRESP)
        {
            dataSubFunction_u8=pMsgContext->reqData[0];
            if((dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER) && (pMsgContext->reqDataLen == DCM_DDDI_MIN_LENGTH))
            {
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                s_isWriteOrClear_en = DCM_DDDI_CLEARALL;

                dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR
   ,     0
   ,     Dcm_DspDddidOpStatus_u8
   ,     s_isWriteOrClear_en);
                if(dataRetValFromNvMStorage_u8==DCM_E_PENDING)
                {

                    Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataRetValFromNvMStorage_u8 != E_OK)
                {

                    DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NVM_UPDATION_NOT_OK )

                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    s_ActiveDDDI_u16 = 0;
                    s_idxIndexForStore_u16 = 0;
                }
                else{

                }
                if(dataRetValFromNvMStorage_u8!= DCM_E_PENDING)
                {

                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    s_ActiveDDDI_u16 = 0;
                    s_idxIndexForStore_u16 = 0;
                    dataRetVal_u8 = E_OK;
                }
#endif
                if(Dcm_DspDddidOpStatus_u8 != DCM_PENDING)
                {

                    pMsgContext->resData[0] = pMsgContext->reqData[0];

                    pMsgContext->resDataLen =  1;
                    Dcm_DspStDddi_en = DCM_DDDI_IDLE;
                    dataRetVal_u8=E_OK;
                }
            }
            else{
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                if((dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER) && (pMsgContext->reqDataLen == (DCM_DDDI_MIN_LENGTH + 2u)))
                {
                    s_isWriteOrClear_en = DCM_DDDI_CLEAR;

                    dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR
   ,     s_ActiveDDDI_u16
   ,     Dcm_DspDddidOpStatus_u8
   ,     s_isWriteOrClear_en);
                }
                else if((dataSubFunction_u8==DCM_DEFINITION_BY_ID)||(dataSubFunction_u8==DCM_DEFINITION_BY_MEMORYADDRESS))
                {
                    s_isWriteOrClear_en = DCM_DDDI_WRITE;

                    dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(&Dcm_DDDIBaseConfig_cast[s_idxIndexForStore_u16]
   ,     s_ActiveDDDI_u16
   ,     Dcm_DspDddidOpStatus_u8
   ,     s_isWriteOrClear_en);
                }
                else{

                }
                if(dataRetValFromNvMStorage_u8==DCM_E_PENDING)
                {

                    Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataRetValFromNvMStorage_u8 != E_OK)
                {

                    DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NVM_UPDATION_NOT_OK )

                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    s_idxIndexForStore_u16 = 0;

                    s_ActiveDDDI_u16 = 0;
                }
                else{

                }
                if(dataRetValFromNvMStorage_u8!= DCM_E_PENDING)
                {

                    s_idxIndexForStore_u16 = 0;

                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    s_ActiveDDDI_u16 = 0;
                    dataRetVal_u8=E_OK;
                }
#endif
                if( Dcm_DspDddidOpStatus_u8 != DCM_PENDING)
                {

                    pMsgContext->resData[2] = pMsgContext->reqData[2];
                    pMsgContext->resData[1] = pMsgContext->reqData[1];
                    pMsgContext->resData[0] = pMsgContext->reqData[0];

                    pMsgContext->resDataLen =  3;

                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;

                    Dcm_DspStDddi_en = DCM_DDDI_IDLE;

                    dataRetVal_u8=E_OK;
                }

            }
        }

        if(Dcm_DspStDddi_en == DCM_DDDI_NEGRESP)
        {

            Dcm_DspStDddi_en = DCM_DDDI_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
   }
    return dataRetVal_u8;
}

FUNC (void,DCM_CODE) Dcm_DddiResetCompleteContext(P2VAR(Dcm_DddiIdContext_tst, AUTOMATIC,DCM_INTERN_DATA) adrContext_pst)
{

    adrContext_pst->nrCurrentlyDefinedRecords_u16=0;
    adrContext_pst->posnCurrentPosInDataBuffer_u16=0;
    adrContext_pst->idxCurrentRecord_u16=0;
}

FUNC (void,DCM_CODE) Dcm_DddiResetProcessingInfoInContext (
        P2VAR(Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrPtrToContext_pst
)
{

    adrPtrToContext_pst->posnCurrentPosInDataBuffer_u16=0;
    adrPtrToContext_pst->idxCurrentRecord_u16=0;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiReadById_u8 (P2CONST (Dcm_DddiDefId_tst,AUTOMATIC,DCM_INTERN_CONST) adrRecord_pst
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) adrLength_pu16
   ,     P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8)
{
   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR (Std_ReturnType, AUTOMATIC)  dataReadIfcRetVal_u8;
#if(DCM_CFG_DSP_DIDBUFFER == DCM_STACK_BUFFER)
   VAR (uint8,AUTOMATIC) Dcm_DspDidBuffer_au8[DCM_CFG_LONGESTSINGLEDID];
#else
   static VAR (uint8,AUTOMATIC) Dcm_DspDidBuffer_au8[DCM_CFG_LONGESTSINGLEDID];
#endif

   if(FALSE == adrRecord_pst->stCurrentDidRangeStatus_b)
   {
        s_Dcm_idxSrcDidIndexType_st.idxIndex_u16 = adrRecord_pst->idxOfDid_u16;

        s_Dcm_idxSrcDidIndexType_st.dataRange_b = FALSE;

        dataReadIfcRetVal_u8 = Dcm_GetDIDData(&s_Dcm_idxSrcDidIndexType_st,Dcm_DspDidBuffer_au8);
   }
   else{
#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
        s_Dcm_idxSrcDidIndexType_st.dataRangeDid_16 = adrRecord_pst->dataSrcDid_u16;
#endif

        s_Dcm_idxSrcDidIndexType_st.dataRange_b = TRUE;
        dataReadIfcRetVal_u8 = Dcm_GetDIDData(&s_Dcm_idxSrcDidIndexType_st,Dcm_DspDidBuffer_au8);
   }
   if(s_Dcm_idxSrcDidIndexType_st.dataNegRespCode_u8 == 0x00)
   {
        switch(dataReadIfcRetVal_u8)
        {

            case (Std_ReturnType)E_OK:
                {

                DCM_MEMCOPY(adrData_pu8, &Dcm_DspDidBuffer_au8[adrRecord_pst->posnInSourceDataRecord_u8-1],adrRecord_pst->dataMemorySize_u8);

                *adrLength_pu16 = adrRecord_pst->dataMemorySize_u8;
                s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
                s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8 = E_OK;
                }
            break;
            case (Std_ReturnType)DCM_E_PENDING:
                    dataRetVal_u8 = DCM_E_PENDING;
            break;
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
            case (Std_ReturnType)DCM_E_REQUEST_ENV_NOK:
                    s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
            s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
            dataRetVal_u8 = DCM_E_REQUEST_ENV_NOK;
            break;
#endif

            case (Std_ReturnType)E_NOT_OK:
            default:
                s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
                s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8 = E_NOT_OK;
                break;
        }
   }
   else{
        dataRetVal_u8 = E_NOT_OK;
   }
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiRead_u8 (P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8=E_OK;

   P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;

   if(Dcm_PeriodicSchedulerRunning_b)
   {
        adrContext_pst = adrConfig_pcst->dataPDIRecordContext_pst;
   }
   else{
        adrContext_pst = adrConfig_pcst->dataDDDIRecordContext_pst;
   }
   if(adrContext_pst->nrCurrentlyDefinedRecords_u16>0)
   {

        while((adrContext_pst->idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16) &&
                (dataRetVal_u8 == E_OK))
        {

            if(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
            {
                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                VAR (uint16,AUTOMATIC) dataLength_u16;

                dataFuncRetVal_u8 = Dcm_DddiReadById_u8 (&(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st)
   ,     &dataLength_u16,&adrData_pu8[adrContext_pst->posnCurrentPosInDataBuffer_u16]);

                if(dataFuncRetVal_u8 == E_OK)
                {

                    adrContext_pst->posnCurrentPosInDataBuffer_u16 = (uint16)(adrContext_pst->posnCurrentPosInDataBuffer_u16 + dataLength_u16);
                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else if(dataFuncRetVal_u8 == E_NOT_OK)
                {
                    dataRetVal_u8=E_NOT_OK;

                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
                else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                {
                    dataRetVal_u8=DCM_E_PENDING;
                }
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                else if(dataFuncRetVal_u8 == DCM_E_REQUEST_ENV_NOK)
                {
                    dataRetVal_u8=DCM_E_REQUEST_ENV_NOK;

                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
#endif

                else{
                    dataRetVal_u8=E_NOT_OK;

                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
            }

            else if(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
            {
                VAR (Dcm_ReadMemoryRet_t,AUTOMATIC) dataFuncRetVal_en;

                dataFuncRetVal_en =DcmAppl_Dcm_ReadMemory (Dcm_DspDddidOpStatus_u8,0
   ,     (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32)
   ,     (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32)
   ,     &adrData_pu8[adrContext_pst->posnCurrentPosInDataBuffer_u16]
   ,     dataNegRespCode_u8);

                if(dataFuncRetVal_en == DCM_READ_OK)
                {
                    *dataNegRespCode_u8 =0x00;

                    adrContext_pst->posnCurrentPosInDataBuffer_u16 = (uint16)(adrContext_pst->posnCurrentPosInDataBuffer_u16 + adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32);
                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else if(dataFuncRetVal_en == DCM_READ_PENDING)
                {
                    *dataNegRespCode_u8 =0x00;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataFuncRetVal_en == DCM_READ_FORCE_RCRRP)
                {
                    *dataNegRespCode_u8 =0x00;
                    dataRetVal_u8=DCM_E_PENDING;

                    (void)Dcm_ForceRespPend();
                }
                else{
                    dataRetVal_u8=E_NOT_OK;
                    if(*dataNegRespCode_u8 == 0x00)
                    {
                        *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                    }

                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }

            }

            else{
                dataRetVal_u8=E_NOT_OK;
                Dcm_DddiResetCompleteContext (adrContext_pst);
            }
        }
   }
   else{
        dataRetVal_u8 = E_NOT_OK;
   }
   if(dataRetVal_u8 == E_OK)
   {

        Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
   }
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DspGetIndexOfDDDI_u8 (VAR (uint16,AUTOMATIC) dataDid_u16
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16)
{
   VAR (uint32,     AUTOMATIC) posnValue_u32;
   VAR (uint32,     AUTOMATIC) posnStart_u32;
   VAR (uint32,     AUTOMATIC) posnEnd_u32;
   VAR (uint32,     AUTOMATIC) dataSize_u32;
   VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;

    dataSize_u32 = Dcm_DddiCalculateTableSize_u16 ();
    posnStart_u32 = 0;
    posnEnd_u32 = dataSize_u32 -1u;
    posnValue_u32 = posnEnd_u32/2u;

   if(Dcm_DDDIBaseConfig_cast[posnStart_u32].dataDddId_u16 == dataDid_u16)
   {
        *idxIndex_u16=(uint16)posnStart_u32;
        dataRetVal_u8=E_OK;
   }

   else if(Dcm_DDDIBaseConfig_cast[posnEnd_u32].dataDddId_u16 == dataDid_u16)
   {
        *idxIndex_u16=(uint16)posnEnd_u32;
        dataRetVal_u8=E_OK;
   }
   else{
        while(posnValue_u32 > 0u)
        {
            posnValue_u32 += posnStart_u32;
            if(Dcm_DDDIBaseConfig_cast[posnValue_u32].dataDddId_u16 == dataDid_u16)
            {
                *idxIndex_u16=(uint16)posnValue_u32;
                dataRetVal_u8=E_OK;
                break;
            }
            else if(Dcm_DDDIBaseConfig_cast[posnValue_u32].dataDddId_u16 > dataDid_u16)
            {
                posnEnd_u32 = posnValue_u32;
            }
            else{
                posnStart_u32 = posnValue_u32;
            }
            posnValue_u32 = (posnEnd_u32-posnStart_u32)/2u ;
        }
   }
    return (dataRetVal_u8);
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddIdRecords_u8 (VAR (uint16,AUTOMATIC)nrBlocks_u16
   ,     VAR (uint16,AUTOMATIC) nrCurrentlyDefinedRecords_u16
   ,     P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8
   ,     P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR (uint16,AUTOMATIC) idxIndex_u16
   ,     VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32)
{

   VAR (Std_ReturnType,AUTOMATIC) dataRetValGetLen_u8;

   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR (boolean, AUTOMATIC) flgRdpi_b;
   static VAR (uint16,AUTOMATIC) Dcm_dataDID_u16;

    flgRdpi_b = FALSE ;
    dataRetVal_u8        = E_OK;

   if(Dcm_stAddIdRecords_en==DCM_DDDI_DEFINE_BY_ID_INIT)
   {

        Dcm_AddIdCurrentBlockIndex_u16 = 0;
        Dcm_stAddIdRecords_en            = DCM_DDDI_DEFINE_BY_ID_GETINDEX;

        Dcm_AddIdCurrentLength_u32     = 0;
        s_dataLength_u32 = 0;
        s_dataFunctionRetVal_u8 = E_OK;
        s_dataLengthFuncRetVal_u8 = E_OK;
   }

    dataRetValGetLen_u8=Dcm_DddiGetLen_u8 (&Dcm_DDDIBaseConfig_cast[idxIndex_u16], &Dcm_AddIdCurrentLength_u32);
   if(dataRetValGetLen_u8==E_OK)
   {

        while((Dcm_AddIdCurrentBlockIndex_u16<nrBlocks_u16) && (dataRetVal_u8==E_OK))
        {
            if(Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETINDEX)
            {

                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                VAR (uint16,     AUTOMATIC) dataDid_u16;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                VAR (uint16,     AUTOMATIC) idxLoop_u16;
#endif

                dataDid_u16=(uint16)((uint16)(((uint16)adrSourceBuffer_pcu8[Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH])<<8u)+
                        ((uint8)adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+1u]));
                Dcm_dataDID_u16=dataDid_u16;

                if(dataDid_u16 == Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16)
                {
                    *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                    dataRetVal_u8 = E_NOT_OK;
                }

                else{

                    dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&s_Dcm_idxSrcDidIndexType_st);
                    if(E_OK == dataFuncRetVal_u8 )
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

                        if((s_Dcm_idxSrcDidIndexType_st.dataRange_b ==FALSE)&& (*Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                        {
                            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                            {
                                dataFuncRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        if(E_OK == dataFuncRetVal_u8 )
                        {
                            for(idxLoop_u16=0;idxLoop_u16<Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16;idxLoop_u16++)
                            {
                                if(Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[idxLoop_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
                                {
                                    dataFuncRetVal_u8=E_NOT_OK;
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    break;
                                }
                            }
                        }
#endif
                    }

                    if(dataFuncRetVal_u8==E_OK)
                    {
                        VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st;

                        dataFuncRetVal_u8 = Dcm_GetIndexOfDID (Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16,&idxsrcDidIndexType_st);
                        if((dataFuncRetVal_u8 ==E_OK) &&  (((adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+3u])+ Dcm_AddIdCurrentLength_u32) <=  Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16))
                        {
                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_GETSUPPORT;
                        }
                        else
                        {
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8 = E_NOT_OK;
                        }
                    }
                    else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                    {

                        dataRetVal_u8 = DCM_E_PENDING;
                    }

                    else
                    {

                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;

                        if(FALSE== flgRdpi_b)
                        {
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                        }

                        dataRetVal_u8               = E_NOT_OK;
                    }
                }
            }
            if(Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETSUPPORT)
            {
                VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_en;

                dataSupportInfo_en=Dcm_GetSupportOfIndex (&s_Dcm_idxSrcDidIndexType_st,DCM_SUPPORT_READ,dataNegRespCode_u8);

                switch(dataSupportInfo_en)
                {
                    case DCM_SUPPORT_OK:
                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_GETLENGTH;
                        s_dataLength_u32 = 0;
                        s_dataFunctionRetVal_u8 = E_OK;
                        s_dataLengthFuncRetVal_u8 = E_OK;
                        break;
                    case DCM_SUPPORT_SESSION_VIOLATED:
                    case DCM_SUPPORT_SECURITY_VIOLATED:
                    case DCM_SUPPORT_CONDITION_VIOLATED:

                        Dcm_stAddIdRecords_en=DCM_DDDI_DEFINE_BY_ID_INIT;
                        dataRetVal_u8=E_NOT_OK;
                        break;
                    case DCM_SUPPORT_CONDITION_PENDING:

                        dataRetVal_u8=DCM_E_PENDING;
                        break;
                    default:

                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                        dataRetVal_u8               = E_NOT_OK;
                        *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                        break;
                }
            }
            if(Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETLENGTH)
            {
                if(((s_dataFunctionRetVal_u8==E_OK)&&(s_dataLengthFuncRetVal_u8==E_OK))||(s_dataFunctionRetVal_u8==DCM_E_PENDING))
                {

                    s_dataFunctionRetVal_u8 = Dcm_GetLengthOfDIDIndex (&s_Dcm_idxSrcDidIndexType_st,&s_dataLength_u32,Dcm_dataDID_u16);

                }

                if(s_dataFunctionRetVal_u8==E_OK)
                {

#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF )

                    if(((s_dataLength_u32 <=  Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16) && (FALSE== s_Dcm_idxSrcDidIndexType_st.dataRange_b)) ||((s_dataLength_u32 <=  Dcm_DIDRangeConfig_cast[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16)&& (FALSE != s_Dcm_idxSrcDidIndexType_st.dataRange_b )))
#else
                        if( s_dataLength_u32 <=  Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16 )
#endif
                        {

                            VAR (uint8,AUTOMATIC) posnInSourceDataRecord_u8=
                                    adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+2u];

                            if(posnInSourceDataRecord_u8==0)
                            {

                                Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                dataRetVal_u8               = E_NOT_OK;
                            }
                            else
                            {

                                VAR (uint8,AUTOMATIC) dataMemorySize_u8=
                                        adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+3u];

                                if((s_dataLength_u32+1u) >= (posnInSourceDataRecord_u8+dataMemorySize_u8))
                                {

                                    VAR(boolean,AUTOMATIC) flgErrorIndn_b = FALSE;

                                    VAR(boolean,AUTOMATIC) flgValidDef_b = FALSE;
                                    VAR(uint16,AUTOMATIC) idxSignal1_u16;
                                    VAR(uint16,AUTOMATIC) idxSignal2_u16;
                                    if(FALSE== s_Dcm_idxSrcDidIndexType_st.dataRange_b)
                                    {

                                        s_dataLengthFuncRetVal_u8 = Dcm_GetDynamicSignalConfiguration(s_Dcm_idxSrcDidIndexType_st.idxIndex_u16);
                                        if(s_dataLengthFuncRetVal_u8 == E_OK)
                                        {

                                            for(idxSignal1_u16=0; (idxSignal1_u16 < Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16)&&(flgErrorIndn_b==FALSE);idxSignal1_u16++)
                                            {
                                                if((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32) ==((posnInSourceDataRecord_u8-(uint8)1u)*8u))
                                                {
                                                    for(idxSignal2_u16=idxSignal1_u16;(idxSignal2_u16<Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16)&&(flgErrorIndn_b==FALSE);
                                                            idxSignal2_u16++)
                                                    {
                                                        if(((Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigPosnBit_u32) +
                                                                (Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigDataSize_u32)) ==
                                                                        (((posnInSourceDataRecord_u8-(uint8)1u) + dataMemorySize_u8)*8u))
                                                        {

                                                            flgValidDef_b = TRUE;
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            if(((Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigPosnBit_u32) +
                                                                    (Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigDataSize_u32)) >
                                                            ((((posnInSourceDataRecord_u8-(uint8)1u) + dataMemorySize_u8)*8u)))
                                                            {

                                                                flgErrorIndn_b = TRUE;
                                                            }
                                                        }
                                                    }
                                                }

                                                else
                                                {
                                                    if(((((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32) < (((uint8)(posnInSourceDataRecord_u8-1)*8)))&& (((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32)+Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigDataSize_u32)>(((uint8)(posnInSourceDataRecord_u8-1u)*8u)))))&& (flgValidDef_b == FALSE))
                                                    {

                                                        flgErrorIndn_b = TRUE;
                                                    }
                                                }

                                                if(flgValidDef_b != FALSE)
                                                {
                                                    break;
                                                }
                                            }
                                        }

                                        else if(s_dataLengthFuncRetVal_u8 == DCM_E_PENDING)
   									{

                                            dataRetVal_u8               = DCM_E_PENDING;

                                        }

                                        else
                                        {

                                            *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                                            Dcm_stAddIdRecords_en       = DCM_DDDI_DEFINE_BY_ID_INIT;
                                            dataRetVal_u8               = E_NOT_OK;
                                        }
                                    }
                                    else
                                    {
                                        if(s_dataLength_u32 == (uint32)((posnInSourceDataRecord_u8-(uint8)1) + dataMemorySize_u8))
                                        {

                                        }
                                        else
                                        {
                                            if(s_dataLength_u32 > (uint32)((posnInSourceDataRecord_u8-(uint8)1) + dataMemorySize_u8))
                                            {

                                                flgErrorIndn_b = TRUE;
                                            }

                                        }
                                        s_dataLengthFuncRetVal_u8 = E_OK;
                                    }
                                    if(s_dataLengthFuncRetVal_u8 != DCM_E_PENDING)
                                    {
                                        if(flgErrorIndn_b == FALSE)
                                        {

                                            if((Dcm_AddIdCurrentLength_u32+dataMemorySize_u8) <= (uint16)nrResponseBufferLen_u32)
                                            {

                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDefinitionType_u8
                                                = DCM_DEFINITION_BY_ID;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataIdAccess_st.
                                                idxOfDid_u16 = s_Dcm_idxSrcDidIndexType_st.idxIndex_u16;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataIdAccess_st.
                                                posnInSourceDataRecord_u8 = posnInSourceDataRecord_u8;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.dataMemorySize_u8 =  dataMemorySize_u8;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.stCurrentDidRangeStatus_b =  s_Dcm_idxSrcDidIndexType_st.dataRange_b;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.dataSrcDid_u16 =  Dcm_dataDID_u16;

                                                Dcm_AddIdCurrentBlockIndex_u16++;

                                                Dcm_AddIdCurrentLength_u32 = (uint16)(Dcm_AddIdCurrentLength_u32 + dataMemorySize_u8);
                                                Dcm_stAddIdRecords_en         = DCM_DDDI_DEFINE_BY_ID_GETINDEX;
                                            }
                                            else
                                            {

                                                Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                                *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                                dataRetVal_u8               = E_NOT_OK;
                                            }
                                        }
                                        else
                                        {

                                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                            dataRetVal_u8               = E_NOT_OK;
                                        }
                                    }
                                }
                                else
                                {

                                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                    *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                    dataRetVal_u8               = E_NOT_OK;
                                }
                            }
                        }
                        else
                        {

                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8               = E_NOT_OK;
                        }
                }
                else if(s_dataFunctionRetVal_u8 == DCM_E_PENDING)
                {

                    dataRetVal_u8=DCM_E_PENDING;
                }

                else{

                    *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                    dataRetVal_u8               = E_NOT_OK;
                }
            }
        }
   }

   else{
        *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
        dataRetVal_u8               = E_NOT_OK;
   }
   if(dataRetVal_u8 == E_OK)
   {
        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
   }
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddMemRecords_u8 (VAR (uint16,AUTOMATIC)nrBlocks_u16
   ,     VAR (uint16,AUTOMATIC)nrCurrentlyDefinedRecords_u16
   ,     P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8
   ,     P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR (uint8,AUTOMATIC)nrBytesForAddress_u8
   ,     VAR (uint8,AUTOMATIC)nrBytesForLength_u8
   ,     VAR (uint16,AUTOMATIC) idxIndex_u16
   ,     VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32)
{
   VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st;
   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR (Std_ReturnType,AUTOMATIC) stGetMemAccess_u8;
   VAR (Std_ReturnType,AUTOMATIC) dataRetValGetLen_u8;

    dataRetVal_u8        = E_OK;

   if(Dcm_stAddMemRecords_en==DCM_DDDI_DEFINE_BY_MEM_INIT)
   {
        Dcm_AddIdCurrentLength_u32     = 0;

        if((nrBytesForAddress_u8>4u) || (nrBytesForLength_u8>4u) || (nrBytesForAddress_u8==0) || (nrBytesForLength_u8==0))
        {

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_u8       = E_NOT_OK;
        }
        else{

            Dcm_AddMemCurrentBlockIndex_u16= 0;
            Dcm_stAddMemRecords_en           = DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT;
        }
   }

    dataRetValGetLen_u8 = Dcm_DddiGetLen_u8 (&Dcm_DDDIBaseConfig_cast[idxIndex_u16], &Dcm_AddIdCurrentLength_u32);
   if(dataRetValGetLen_u8 == E_OK)
   {

        while((Dcm_AddMemCurrentBlockIndex_u16<nrBlocks_u16) &&(dataRetVal_u8==E_OK))
        {
            if(Dcm_stAddMemRecords_en == DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT)
            {

                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                VAR (Dcm_DDDI_DEF_MEM_t,AUTOMATIC) dataMemRecord_st;
                VAR (uint32,AUTOMATIC) idxLoop_u32;
                P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrInputBuffer_pcu8;
                VAR(boolean,AUTOMATIC) flgValidMemoryAccess_b;

                flgValidMemoryAccess_b = FALSE;
                dataMemRecord_st.adrDddiMem_u32   =0x00;
                dataMemRecord_st.dataMemLength_u32 =0x00;

                adrInputBuffer_pcu8=adrSourceBuffer_pcu8+ ((nrBytesForLength_u8+nrBytesForAddress_u8)*Dcm_AddMemCurrentBlockIndex_u16);

                for(idxLoop_u32=0;idxLoop_u32<nrBytesForAddress_u8;idxLoop_u32++)
                {
                    dataMemRecord_st.adrDddiMem_u32 = (dataMemRecord_st.adrDddiMem_u32<<8u)+(*adrInputBuffer_pcu8);

                    adrInputBuffer_pcu8++;
                }

                for(idxLoop_u32=0;idxLoop_u32<nrBytesForLength_u8;idxLoop_u32++)
                {
                    dataMemRecord_st.dataMemLength_u32 = ((dataMemRecord_st.dataMemLength_u32<<8u)+(*adrInputBuffer_pcu8));

                    adrInputBuffer_pcu8++;
                }

                dataFuncRetVal_u8 = Dcm_GetIndexOfDID (Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16,&idxsrcDidIndexType_st);
                flgValidMemoryAccess_b = Dcm_DddiCheckOverflow(dataMemRecord_st.dataMemLength_u32,Dcm_AddIdCurrentLength_u32,Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16);
                if((dataFuncRetVal_u8 ==E_OK) &&  (flgValidMemoryAccess_b == TRUE))
                {

                    dataFuncRetVal_u8=DcmAppl_DDDI_Read_Memory_Condition (&dataMemRecord_st, dataNegRespCode_u8);
                    if(dataFuncRetVal_u8 == E_NOT_OK)
                    {
                        if(*dataNegRespCode_u8 ==0x00)
                        {
                            *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                        }
                        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                        dataRetVal_u8 = E_NOT_OK;
                    }
                    else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                    {

                        dataRetVal_u8 = DCM_E_PENDING;
                        *dataNegRespCode_u8          = 0;
                    }
                    else if(dataFuncRetVal_u8 == E_OK)
                    {
                        *dataNegRespCode_u8= 0;

                        stGetMemAccess_u8=DcmAppl_DcmGetPermissionForMemoryAccess_u8(dataMemRecord_st.adrDddiMem_u32,dataMemRecord_st.dataMemLength_u32,DCM_SUPPORT_WRITE);
                        if(stGetMemAccess_u8 == E_OK)
                        {

                            if((Dcm_AddIdCurrentLength_u32+dataMemRecord_st.dataMemLength_u32) <= nrResponseBufferLen_u32)
                            {

                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDefinitionType_u8
                                = DCM_DEFINITION_BY_MEMORYADDRESS;
                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32
                                = dataMemRecord_st.dataMemLength_u32;
                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32
                                = dataMemRecord_st.adrDddiMem_u32;
                                Dcm_AddMemCurrentBlockIndex_u16++;

                                Dcm_AddIdCurrentLength_u32 = (uint16)(Dcm_AddIdCurrentLength_u32 + dataMemRecord_st.dataMemLength_u32);
                            }
                            else
                            {

                                Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                                *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                                dataRetVal_u8                = E_NOT_OK;
                            }
                        }
                        else
                        {

                            Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                            *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8                = E_NOT_OK;
                        }
                    }

                    else
                    {
                        if(*dataNegRespCode_u8 == 0x00)
                        {

                            *dataNegRespCode_u8          = DCM_E_GENERALREJECT;
                        }
                        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                        dataRetVal_u8                = E_NOT_OK;
                    }
                }

                else{

                    *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                    Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                    dataRetVal_u8                = E_NOT_OK;
                }
            }
        }
   }

   else{

        *dataNegRespCode_u8          = DCM_E_GENERALREJECT;
        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
        dataRetVal_u8                = E_NOT_OK;
   }
   if(dataRetVal_u8 == E_OK)
   {

        Dcm_stAddMemRecords_en=DCM_DDDI_DEFINE_BY_MEM_INIT;
   }
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiGetLen_u8 (P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrLen_pu32)
{
   VAR (uint32,AUTOMATIC) idxCurrentRecord_u16 = 0;
   P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;
   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8 = E_OK;

    *adrLen_pu32=0;

   if(Dcm_PeriodicSchedulerRunning_b)
   {
        adrContext_pst=adrConfig_pcst->dataPDIRecordContext_pst;
   }
   else{
        adrContext_pst=adrConfig_pcst->dataDDDIRecordContext_pst;
   }

   for(; idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16; idxCurrentRecord_u16++)
   {

        if(adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
        {

            VAR (uint32,AUTOMATIC) dataLenOfThisRecord_u32=adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8;

            *adrLen_pu32 = *adrLen_pu32 + dataLenOfThisRecord_u32;
        }

        else if(adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
        {

            VAR (uint32,AUTOMATIC) dataLenOfThisRecord_u32 = adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32;

            *adrLen_pu32 = (uint16)(*adrLen_pu32 + dataLenOfThisRecord_u32);
        }

        else{
            dataRetVal_u8 = E_NOT_OK;
            Dcm_DddiResetCompleteContext (adrContext_pst);
            break;
        }
   }
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiGetCondition_u8(P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8=E_OK;
   VAR (Std_ReturnType,   AUTOMATIC) stGetMemAccess_u8;
   P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;

   if(Dcm_PeriodicSchedulerRunning_b)
   {
        adrContext_pst=adrConfig_pcst->dataPDIRecordContext_pst;
   }
   else{
        adrContext_pst=adrConfig_pcst->dataDDDIRecordContext_pst;
   }

   while((adrContext_pst->idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16) &&
            (dataRetVal_u8 == E_OK))
   {

        if(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
        {
            VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_en;
            VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxDidCondIndexType_st;

            idxDidCondIndexType_st.idxIndex_u16 = adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16;
            idxDidCondIndexType_st.dataRange_b =  adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b;
            idxDidCondIndexType_st.dataopstatus_b = Dcm_DspDataOpstatus_u8;

            dataSupportInfo_en = Dcm_GetSupportOfIndex (&idxDidCondIndexType_st, DCM_SUPPORT_READ,dataNegRespCode_u8);

            if(dataSupportInfo_en == DCM_SUPPORT_OK)
            {
                Dcm_DspDataOpstatus_u8 = DCM_INITIAL;

                adrContext_pst->idxCurrentRecord_u16++;
            }
            else if(dataSupportInfo_en == DCM_SUPPORT_CONDITION_PENDING)
            {
                Dcm_DspDataOpstatus_u8 = DCM_PENDING;
                dataRetVal_u8 = DCM_E_PENDING;
            }
            else{
                Dcm_DspDataOpstatus_u8 = DCM_INITIAL;
                dataRetVal_u8 = E_NOT_OK;

                Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
            }
        }

        else if(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
        {
            VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;

            dataFuncRetVal_u8 = DcmAppl_DDDI_Read_Memory_Condition   (
                    &(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st)
   ,     dataNegRespCode_u8
            );
            if(dataFuncRetVal_u8 == E_OK)
            {
                *dataNegRespCode_u8=0x00;

                stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32,adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32
   ,     DCM_SUPPORT_READ);
                if(stGetMemAccess_u8 == E_OK)
                {

                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataRetVal_u8=E_NOT_OK;

                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
            }
            else if(dataFuncRetVal_u8 == DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;
                dataRetVal_u8 = DCM_E_PENDING;
            }
            else{
                if(*dataNegRespCode_u8 == 0x00)
                {
                    *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                }
                dataRetVal_u8=E_NOT_OK;

                Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
            }
        }

        else{
            dataRetVal_u8 = E_NOT_OK;
            Dcm_DddiResetCompleteContext (adrContext_pst);
        }
   }
   if(dataRetVal_u8 == E_OK)
   {
        Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
   }
    return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDDDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{

    *dataDid_u16 = s_ActiveDDDI_u16;
    return (E_OK);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveSourceDataId(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataSrcDid_u16,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) posnSrcDataRec_u8, P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrMemSize_u8)
{

   VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8=E_NOT_OK;
   static VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8=E_NOT_OK;

   VAR (uint16,AUTOMATIC) idxIndex_u16;

   P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst;

   P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContextDddi_pst;

    dataFuncRetVal_u8 = Dcm_GetActiveDid(dataSrcDid_u16);
   if(dataFuncRetVal_u8== E_OK)
   {

        while(Dcm_DspGetIndexOfDDDI_u8(*dataSrcDid_u16,&idxIndex_u16) == E_OK)
        {

            adrConfig_pcst = &Dcm_DDDIBaseConfig_cast[idxIndex_u16];
            adrContextDddi_pst = adrConfig_pcst->dataDDDIRecordContext_pst;

            *dataSrcDid_u16 = adrConfig_pcst->addrRecord_pst[adrContextDddi_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.dataSrcDid_u16;

            *posnSrcDataRec_u8 = adrConfig_pcst->addrRecord_pst[adrContextDddi_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.posnInSourceDataRecord_u8;

            *adrMemSize_u8 = adrConfig_pcst->addrRecord_pst[adrContextDddi_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8;
            dataRetVal_u8 = E_OK;
            if((*dataSrcDid_u16 <0xf3ffu) && (*dataSrcDid_u16 >0xf200u))
            {

            }
            else{

                break;
            }
        }

   }
   else{

   }
        return(dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
