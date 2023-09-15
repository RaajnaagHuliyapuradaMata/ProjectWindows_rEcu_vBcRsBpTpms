#include "DcmDspUds_Rdbi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_StRdbi_ten Dcm_stRdbi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_RdbiReqDidNb_u16;
uint16 Dcm_NumOfIndices_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_TotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
Dcm_OpStatusType Dcm_DspReadDidOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DIDIndexType_tst s_Dcm_idxRdbiDidIndexType_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
void Dcm_Dsp_RdbiIni (void){
   Dcm_NegativeResponseCodeType dataNegResCode_u8;
   Std_ReturnType dataCondChkRetVal_u8;
   Std_ReturnType dataReadIfcRetVal_u8;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   const Dcm_DataInfoConfig_tst * ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite * ptrControlSigConfig;

    dataCondChkRetVal_u8 = E_OK;
    dataReadIfcRetVal_u8 = E_OK;
    dataNegResCode_u8 = 0x0;
    ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
    ptrControlSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];

#if((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)||(DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF))

   if((Dcm_DspReadDidOpStatus_u8 == DCM_PENDING) && (Dcm_flgDspDidRangePending_b == FALSE))
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)    ||
                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
        {
                if((Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH) && (ptrControlSigConfig->adrCondChkRdFnc_cpv!=NULL_PTR))
                {

                dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(DCM_CANCEL, &dataNegResCode_u8);
            }
            if((Dcm_stRdbi_en == DCM_RDBI_GET_DATA)&&       \
                    (ptrSigConfig->adrReadFnc_cpv!=NULL_PTR))
            {
                    dataReadIfcRetVal_u8 = (*(ReadFunc2_ptr)(ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL,NULL_PTR);
                }
        }
#endif
   }
#endif
    Dcm_stRdbi_en         = DCM_RDBI_IDLE;
    Dcm_StLenCalc_en      = DCM_LENCALC_STATUS_INIT;
    SwcServiceDcm_eStatusGetData      = SwcServiceDcm_eStatusGetDataInit;
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
    Dcm_flgDspDidRangePending_b=FALSE;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);
    Dcm_PeriodicSchedulerRunning_b=FALSE;
    (void)dataCondChkRetVal_u8;
    (void)dataReadIfcRetVal_u8;
    (void)dataNegResCode_u8;
    (void )ptrDidConfig;
    (void )ptrSigConfig;
    (void )ptrControlSigConfig;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_LenCalc_ten Dcm_StLenCalc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
uint8 * Dcm_IdxList_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_NumberOfBytesInResponse_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_NumberOfProcessedDIDs_u16;
uint16 Dcm_NumberOfAcceptedDIDs_u16;

static uint16 s_dataDID_Rdbi_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Dcm_LenCalcRet_ten Dcm_DspGetTotalLengthOfDIDs_en (uint8 * adrSourceIds_pu8
   ,       uint16 nrDids_u16
   ,       uint16 * adrNumOfIndices_pu16
   ,       uint32 * adrTotalLength_pu32
   ,       Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Dcm_LenCalcRet_ten dataRetVal_u8;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
    dataRetVal_u8 = DCM_LENCALC_RETVAL_OK;
    ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

   if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_INIT)
   {
        Dcm_NumberOfBytesInResponse_u32 = 0;
        Dcm_NumberOfProcessedDIDs_u16   = 0;
        Dcm_NumberOfAcceptedDIDs_u16    = 0;
        Dcm_IdxList_pu8                   = adrSourceIds_pu8;
        Dcm_DidSignalIdx_u16            = 0x0;
        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
   }

   while((dataRetVal_u8 == DCM_LENCALC_RETVAL_OK) &&
            (Dcm_NumberOfProcessedDIDs_u16 < nrDids_u16) &&
            ((Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETINDEX) ||
                    (Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETLENGTH) ||
                    (Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETSUPPORT)))
   {
        if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETINDEX)
        {

            Std_ReturnType dataFuncRetVal_en;

            s_dataDID_Rdbi_u16 = (uint16)(((uint16)(adrSourceIds_pu8[Dcm_NumberOfProcessedDIDs_u16 * 2]))<<8u)+
                    (uint16)((uint16)(adrSourceIds_pu8[(Dcm_NumberOfProcessedDIDs_u16 * 2)+1]));

            dataFuncRetVal_en = Dcm_Lok_GetIndexOfDID(s_dataDID_Rdbi_u16, &s_Dcm_idxRdbiDidIndexType_st);
            if(dataFuncRetVal_en==E_OK)
            {
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETSUPPORT;
                Dcm_DidSignalIdx_u16 = 0x0;
            }
            else if(dataFuncRetVal_en==DCM_E_PENDING)
            {
                dataRetVal_u8=DCM_LENCALC_RETVAL_PENDING;
            }
            else{
                Dcm_NumberOfProcessedDIDs_u16++;
            }
        }
        if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETSUPPORT)
        {
            Dcm_SupportRet_t dataSupportInfo_st;
            ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataSupportInfo_st=Dcm_GetSupportOfIndex (&s_Dcm_idxRdbiDidIndexType_st, DCM_SUPPORT_READ,dataNegRespCode_u8 );
            switch(dataSupportInfo_st)
            {
                case DCM_SUPPORT_OK:
                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETLENGTH;
                    Dcm_DidSignalIdx_u16 = 0x0;
                    break;

                case DCM_SUPPORT_SESSION_VIOLATED:
                    Dcm_NumberOfProcessedDIDs_u16++;
                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                    break;
                case DCM_SUPPORT_SECURITY_VIOLATED:

                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                    dataRetVal_u8 = DCM_LENCALC_RETVAL_ERROR;
                    break;

                case DCM_SUPPORT_CONDITION_VIOLATED:

                    if(*dataNegRespCode_u8 == DCM_E_REQUESTOUTOFRANGE)
                    {
                        Dcm_NumberOfProcessedDIDs_u16++;
                        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                    }
                    else
                    {
                        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                        dataRetVal_u8 = DCM_LENCALC_RETVAL_ERROR;
                    }
                    break;
                case DCM_SUPPORT_CONDITION_PENDING:
                    dataRetVal_u8 = DCM_LENCALC_RETVAL_PENDING;
                    break;
                default:

                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    dataRetVal_u8 = DCM_LENCALC_RETVAL_ERROR;
                    break;
            }
        }
        if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETLENGTH)
        {
            uint32 dataLength_u32;
            Std_ReturnType dataFuncRetVal_en;
            ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex(&s_Dcm_idxRdbiDidIndexType_st,&dataLength_u32,s_dataDID_Rdbi_u16);
            if(dataFuncRetVal_en==E_OK )
            {
                if(dataLength_u32>0u)
                {
                            Dcm_NumberOfBytesInResponse_u32 = (uint32)(Dcm_NumberOfBytesInResponse_u32 + dataLength_u32);
                            Dcm_NumberOfAcceptedDIDs_u16 ++;
                            Dcm_NumberOfProcessedDIDs_u16++;
                            *Dcm_IdxList_pu8= (uint8)(s_dataDID_Rdbi_u16>>8u);
                            Dcm_IdxList_pu8++;
                            *Dcm_IdxList_pu8= (uint8)s_dataDID_Rdbi_u16;
                            Dcm_IdxList_pu8++;
                            Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                }
                else{
                    Dcm_NumberOfProcessedDIDs_u16++;
                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                }
            }
            else if(dataFuncRetVal_en == DCM_INFRASTRUCTURE_ERROR)
            {
                *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
            }
            else if(dataFuncRetVal_en == E_NOT_OK)
            {
                *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
            }
            else if(dataFuncRetVal_en == DCM_E_PENDING)
            {
                dataRetVal_u8 = DCM_LENCALC_RETVAL_PENDING;
            }
            else{
                if(*dataNegRespCode_u8 == 0x00)
                {
                    *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                }
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
            }
        }
   }
   if(dataRetVal_u8 == DCM_LENCALC_RETVAL_OK)
   {
        *adrTotalLength_pu32    = Dcm_NumberOfBytesInResponse_u32;
        *adrNumOfIndices_pu16   = Dcm_NumberOfAcceptedDIDs_u16;
        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
   }
   (void)ptrDidConfig;
    return (dataRetVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Type_SwcServiceDcm_eStatusGetData SwcServiceDcm_eStatusGetData;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static Std_ReturnType s_readDataLengthFnc_retVal_u8;

static Std_ReturnType s_dataReadIfcVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_GetDataNumOfIndex_u16;

static uint16 s_dataID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_GetDataTotalLength_u32;

static uint32 s_posnTargetSig_u32;

static uint32 s_datalengthinfo_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Type_SwcServiceDcm_eRetValGetData Dcm_GetData_en(
      const uint8*                        adrIdBuffer_pcu8
   ,        uint8*                        adrTargetBuffer_pu8
   ,        uint16                        nrIndex_u16
   ,        Dcm_NegativeResponseCodeType* dataNegRespCode_u8
   ,        uint32                        adrTotalLength_pu32
){
   const  Type_CfgSwcServiceDcm_stDid*        ptrDidConfig;
   const  Dcm_DataInfoConfig_tst*           ptrSigConfig;
   const  Type_CfgSwcServiceDcm_stInfoDidWrite* ptrControlSigConfig;
   void*  ptrRDBIFnc;
          Std_ReturnType                    dataNrcRetval_u8 = E_OK;
          Type_SwcServiceDcm_eRetValGetData leRetValGetData  = SwcServiceDcm_eRetValGetDataOk;
   static uint32                            Dcm_DataLengthOfCurrentData_u32;
          boolean                           FixedLength_b=TRUE;

   *dataNegRespCode_u8 = 0x0;
   if(SwcServiceDcm_eStatusGetData == SwcServiceDcm_eStatusGetDataInit){
      Dcm_GetDataNumOfIndex_u16     = nrIndex_u16;
      Dcm_GetDataTotalLength_u32    = adrTotalLength_pu32;
      SwcServiceDcm_eStatusGetData  = SwcServiceDcm_eStatusGetDataLength;
      s_dataReadIfcVal_u8           = E_OK;
      s_readDataLengthFnc_retVal_u8 = E_OK;
      s_datalengthinfo_u32          = 0;
   }
   while(
         (Dcm_GetDataNumOfIndex_u16 > 0)
      && (
               (SwcServiceDcm_eStatusGetData == SwcServiceDcm_eStatusGetDataPayload)
            || (SwcServiceDcm_eStatusGetData == SwcServiceDcm_eStatusGetDataLength)
         )
      && (leRetValGetData == SwcServiceDcm_eRetValGetDataOk)
   ){
      if(SwcServiceDcm_eStatusGetData == SwcServiceDcm_eStatusGetDataLength){
         Std_ReturnType dataFuncRetVal_en;
         s_dataID_u16 = (uint16)(
            (uint16)((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1)*2u)]<<(uint8)8) +
            ((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1u)*2u)+1u])
         );
         dataFuncRetVal_en = Dcm_Lok_GetIndexOfDID(s_dataID_u16, &s_Dcm_idxRdbiDidIndexType_st);
         if(dataFuncRetVal_en == E_OK){
            dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex(
                  &s_Dcm_idxRdbiDidIndexType_st
               ,  &Dcm_DataLengthOfCurrentData_u32
               ,  s_dataID_u16
            );
         }
         switch(dataFuncRetVal_en){
            case E_OK:
               SwcServiceDcm_eStatusGetData = SwcServiceDcm_eStatusGetDataPayload;
               Dcm_DidSignalIdx_u16 = 0x0u;
               s_datalengthinfo_u32 = 0x0u;
               Dcm_DspReadDidOpStatus_u8=DCM_INITIAL;
               break;

            case DCM_E_PENDING:
               leRetValGetData = SwcServiceDcm_eRetValGetDataPending;
               break;

            case E_NOT_OK:
            case DCM_INFRASTRUCTURE_ERROR:
            default:
               leRetValGetData = SwcServiceDcm_eRetValGetDataErrorInternal;
               SwcServiceDcm_eStatusGetData = SwcServiceDcm_eStatusGetDataInit;
               break;
         }
      }
      if(SwcServiceDcm_eStatusGetData == SwcServiceDcm_eStatusGetDataPayload){
            uint32 posnTarget_u32= (Dcm_GetDataTotalLength_u32 - Dcm_DataLengthOfCurrentData_u32);
            uint32 dataSignallength_u32;
            ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataSignallength_u32 = 0x0;
         if(s_dataReadIfcVal_u8 != DCM_E_PENDING){
                DCM_MEMSET(&adrTargetBuffer_pu8[posnTarget_u32], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, Dcm_DataLengthOfCurrentData_u32);
            }
         if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b == FALSE){
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
            while(
                  (Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16)
               && (USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8)
            ){
               ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
               ptrControlSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
               if(
                  (
                        (s_readDataLengthFnc_retVal_u8 == E_OK)
                     && (s_dataReadIfcVal_u8 == E_OK)
                  )
                  || (s_readDataLengthFnc_retVal_u8 == DCM_E_PENDING)
               ){
                  if(FALSE != FixedLength_b){
                     s_posnTargetSig_u32 = (posnTarget_u32+(ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].posnSigBit_u16));
                     if(
                           (ptrSigConfig->dataType_u8==DCM_BOOLEAN)
                        && (
                                 ((Dcm_DidSignalIdx_u16==(ptrDidConfig->nrSig_u16-1)))
                              || (
                                       ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16  ].posnSigBit_u16
                                    != ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16+1].posnSigBit_u16
                                 )
                           )
                     ){
                        s_datalengthinfo_u32+=1u;
                     }
                     else if(ptrSigConfig->dataType_u8 != DCM_BOOLEAN){
                        s_datalengthinfo_u32  = ((ptrSigConfig->dataSize_u16) + (ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].posnSigBit_u16));
                     }
                     else{
                     }
                     s_readDataLengthFnc_retVal_u8 = E_OK;
                  }
                  else{
                  }
               }
               if(ptrSigConfig->adrReadFnc_cpv != NULL_PTR){
                  ptrRDBIFnc=ptrSigConfig->adrReadFnc_cpv;
                  if(
                        (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)
                     || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                  ){
                  }
#if(DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)
                  else if(
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
                     || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                  ){
                     s_dataReadIfcVal_u8 = (*(ReadFunc2_ptr)(ptrRDBIFnc))(Dcm_DspReadDidOpStatus_u8, &adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                  }
#endif
                  else{
                  }
                  if(s_dataReadIfcVal_u8 != E_OK){
                     break;
                  }
                  else{
                     Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                  }
               }
               else{
               }
               Dcm_DidSignalIdx_u16++;
            }
            switch(s_dataReadIfcVal_u8){
               case E_OK:{
                  posnTarget_u32=(posnTarget_u32-2u);
                  adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((ptrDidConfig->dataDid_u16)>>8u);
                  adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((ptrDidConfig->dataDid_u16));
                  Dcm_GetDataTotalLength_u32 = (Dcm_GetDataTotalLength_u32 - (Dcm_DataLengthOfCurrentData_u32 + 2u));
                  Dcm_GetDataNumOfIndex_u16--;
                  SwcServiceDcm_eStatusGetData=SwcServiceDcm_eStatusGetDataLength;
                  break;
               }

               case DCM_E_PENDING:{
                  *dataNegRespCode_u8=0x00;
                  leRetValGetData = SwcServiceDcm_eRetValGetDataPending;
                  break;
               }

               case DCM_E_REQUEST_ENV_NOK:{
                  if(E_OK == s_readDataLengthFnc_retVal_u8){
                     dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,s_posnTargetSig_u32,dataNegRespCode_u8);
                  }
                  if(dataNrcRetval_u8 != E_OK){
                     *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                  }
                  leRetValGetData =SwcServiceDcm_eRetValGetDataConditionsInvalid;
                  SwcServiceDcm_eStatusGetData = SwcServiceDcm_eStatusGetDataInit;
                  Dcm_DidSignalIdx_u16 = 0x0;
                  break;
               }

               case E_NOT_OK:{
                  if(E_OK == s_readDataLengthFnc_retVal_u8){
                     dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(
                           s_dataID_u16
                        ,  s_posnTargetSig_u32
                        ,  dataNegRespCode_u8
                     );
                  }
                  if(dataNrcRetval_u8 != E_OK){
                     *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                  }
                  leRetValGetData = SwcServiceDcm_eRetValGetDataErrorInternal;
                  SwcServiceDcm_eStatusGetData = SwcServiceDcm_eStatusGetDataInit;
                  Dcm_DidSignalIdx_u16 = 0x0;
                  break;
               }

               default:{
                  leRetValGetData = SwcServiceDcm_eRetValGetDataErrorInternal;
                  SwcServiceDcm_eStatusGetData = SwcServiceDcm_eStatusGetDataInit;
                  Dcm_DidSignalIdx_u16 = 0x0;
                  break;
               }
            }
#endif
         }
         else{
         }
         (void)dataSignallength_u32;
      }
   }
   if(leRetValGetData == SwcServiceDcm_eRetValGetDataOk){
      SwcServiceDcm_eStatusGetData=SwcServiceDcm_eStatusGetDataInit;
   }
   (void )ptrDidConfig;
   (void )ptrSigConfig;
   (void )ptrControlSigConfig;
   return leRetValGetData;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType SwcServiceDcm_tReadDataByIdentifier(
      Dcm_SrvOpStatusType           OpStatus
   ,  Dcm_MsgContextType*           pMsgContext
   ,  Dcm_NegativeResponseCodeType* dataNegRespCode_u8
){
   Std_ReturnType dataRetVal_u8;
   *dataNegRespCode_u8   = 0x0u;
   dataRetVal_u8=DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL){
      Dcm_Dsp_RdbiIni();
      dataRetVal_u8 = E_OK;
   }
   else{
      if(Dcm_stRdbi_en == DCM_RDBI_IDLE){
         if(
               (pMsgContext->reqDataLen < DCM_RDBI_SIZE_DID)
            || ((pMsgContext->reqDataLen & 0x0001u) != 0uL)
         ){
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
         }
         else{
            Dcm_RdbiReqDidNb_u16 = (uint16)(pMsgContext->reqDataLen / DCM_RDBI_SIZE_DID);
            if(
                  (DCM_CFG_MAXDIDTOREAD != 0u)
               && (Dcm_RdbiReqDidNb_u16 > DCM_CFG_MAXDIDTOREAD)
            ){
               *dataNegRespCode_u8  = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
               Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
            }
            else{
               Dcm_stRdbi_en = DCM_RDBI_GET_LENGTH;
            }
         }
      }
      if(Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH){
         Dcm_LenCalcRet_ten dataFuncRetVal_en;
         dataFuncRetVal_en = Dcm_DspGetTotalLengthOfDIDs_en(
               &pMsgContext->reqData[0]
            ,  Dcm_RdbiReqDidNb_u16
            ,  &Dcm_NumOfIndices_u16
            ,  &Dcm_TotalLength_u32
            ,  dataNegRespCode_u8
         );
         switch(dataFuncRetVal_en){
            case DCM_LENCALC_RETVAL_OK:
               Dcm_TotalLength_u32 = (uint32)(Dcm_TotalLength_u32 + (2 * Dcm_NumOfIndices_u16));
               pMsgContext->resDataLen = (Dcm_MsgLenType)Dcm_TotalLength_u32;
               if(Dcm_TotalLength_u32<= pMsgContext->resMaxDataLen){
                  Dcm_stRdbi_en = DCM_RDBI_GET_DATA;
               }
               else{
                  *dataNegRespCode_u8  = DCM_E_RESPONSETOOLONG;
                  Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
               }
               if(
                     (Dcm_RdbiReqDidNb_u16 > 1)
                  && (Dcm_NumOfIndices_u16!=0)
                  && (Dcm_stRdbi_en == DCM_RDBI_GET_DATA)
               ){
                  Std_ReturnType dataCheckLenRetVal_u8;
                  dataCheckLenRetVal_u8 = DcmAppl_DcmCheckRdbiResponseLength(
                        Dcm_TotalLength_u32
                     ,  Dcm_NumOfIndices_u16
                     ,  dataNegRespCode_u8
                  );
                  if(
                        (*dataNegRespCode_u8==0)
                     && (dataCheckLenRetVal_u8 != E_OK)
                  ){
                     *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                     Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                  }
                  else if(
                        (*dataNegRespCode_u8 !=0)
                     && (dataCheckLenRetVal_u8 != E_OK)
                  ){
                     Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                  }
               }
               Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
               break;

            case DCM_LENCALC_RETVAL_PENDING:
               Dcm_DspReadDidOpStatus_u8 = DCM_PENDING;
               dataRetVal_u8=DCM_E_PENDING;
               break;

            case DCM_LENCALC_RETVAL_ERROR:
               Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
               Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
               break;

            default:
               *dataNegRespCode_u8  = DCM_E_GENERALREJECT;
               Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
               Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
               break;
         }
      }
      if(Dcm_stRdbi_en == DCM_RDBI_GET_DATA){
         if(Dcm_NumOfIndices_u16==0){
            *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
         }
         else{
            switch(
               Dcm_GetData_en(
                     &pMsgContext->reqData[0]
                  ,  pMsgContext->resData
                  ,  Dcm_NumOfIndices_u16
                  ,  dataNegRespCode_u8
                  ,  Dcm_TotalLength_u32
               )
            ){
               case SwcServiceDcm_eRetValGetDataOk:
                  pMsgContext->resDataLen =  Dcm_TotalLength_u32;
                  Dcm_DidSignalIdx_u16 = 0x0;
                  dataRetVal_u8=E_OK;
                  Dcm_stRdbi_en = DCM_RDBI_IDLE;
                  Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                  break;

               case SwcServiceDcm_eRetValGetDataPending:
                  Dcm_DspReadDidOpStatus_u8 = DCM_PENDING;
                  dataRetVal_u8=DCM_E_PENDING;
                  break;

               case SwcServiceDcm_eRetValGetDataConditionsInvalid:
                  *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                  Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                  Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                  break;

               case SwcServiceDcm_eRetValGetDataErrorInternal:
               default:
                  if(0x0 == *dataNegRespCode_u8){
                  *dataNegRespCode_u8  = DCM_E_GENERALREJECT;
                  }
                  Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                  Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                  break;
            }
         }
      }
      if(Dcm_stRdbi_en == DCM_RDBI_NEG_RESP){
         Dcm_DidSignalIdx_u16 = 0x0;
         dataRetVal_u8=E_NOT_OK;
         Dcm_stRdbi_en = DCM_RDBI_IDLE;
      }
   }
   return dataRetVal_u8;
}

Std_ReturnType Dcm_GetActiveRDBIDid(uint16 * dataDid_u16)
{
    Std_ReturnType dataRetVal_u8;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
    ptrDidConfig =&CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
    dataRetVal_u8 = E_NOT_OK;
   if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b==FALSE)
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )

        *dataDid_u16 = ptrDidConfig->dataDid_u16;
#endif
        dataRetVal_u8 = E_OK;
   }
   else{
   }
    return (dataRetVal_u8);
}

void Dcm_Lok_DspRdbiConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  PduIdType dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8)
{
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  																status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

