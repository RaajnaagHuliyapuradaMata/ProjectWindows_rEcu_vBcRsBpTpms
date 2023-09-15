#include "DcmDspUds_Uds_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static uint32 s_datasignallength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)	|| \
(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

static Std_ReturnType s_dataRetVal_u8;
#endif
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
static Std_ReturnType s_dataLengthFnc_retVal_u8;
#endif
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
boolean Dcm_PeriodicSchedulerRunning_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
boolean Dcm_flgDspDidRangePending_b;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))
void Dcm_ConvBitsToBytes(uint32 * DataLenInBits){
   uint32 dataLen_u32;
   dataLen_u32 = (uint32)(*DataLenInBits/8u);
   if((*DataLenInBits%8u) != 0u){
      *DataLenInBits = (uint16)(dataLen_u32+1u);
   }
   else{
      *DataLenInBits = dataLen_u32;
   }
}

void Dcm_ResetDIDIndexstruct (Dcm_DIDIndexType_tst * idxDidIndexType_st){
   idxDidIndexType_st->dataNegRespCode_u8=0x0;
   idxDidIndexType_st->dataRange_b = FALSE;
   idxDidIndexType_st->idxIndex_u16 = 0x0;
   idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
   idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
   idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
   idxDidIndexType_st->flgNvmReadPending_b = FALSE;
}

Std_ReturnType Dcm_GetLengthOfDIDIndex(
Dcm_DIDIndexType_tst * idxDidIndexType_st
   ,                                                       uint32 * length_u32
   ,                                                       uint16 did_u16
){
   Std_ReturnType dataRetVal_u8;
   uint32 dataSigLength_u32;
   uint16 dataSigLength_u16;
   const Type_CfgSwcServiceDcm_stDid * ptrDidConfig;
   dataRetVal_u8 = E_NOT_OK;
   dataSigLength_u32 = 0x0u;
   dataSigLength_u16 = 0x0u;
   if(length_u32!= NULL_PTR){
      *length_u32 = 0x0u;
      if(idxDidIndexType_st->dataRange_b == FALSE){
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
         (void)did_u16;
         (void)dataSigLength_u32;
         (void)dataSigLength_u16;
         ptrDidConfig = &CfgSwcServiceDcm_astListDid[idxDidIndexType_st->idxIndex_u16];
         if(ptrDidConfig->dataFixedLength_b != FALSE){
            *length_u32 = ptrDidConfig->dataMaxDidLen_u16;
            dataRetVal_u8 = E_OK;
         }
         else{
         }
#endif
      }
      else{
      }
   }
   else{
   }
   return dataRetVal_u8;
}
#endif

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )
Std_ReturnType Dcm_Lok_GetIndexOfDID(
      uint16                did
   ,  Dcm_DIDIndexType_tst* idxDidIndexType_st
){
   uint32 posnStart_u32 = 0;
   uint32 dataSize_u32  = Dcm_DIDcalculateTableSize_u16();
   uint32 posnEnd_u32   = dataSize_u32 - 1u;
   uint32 posnDid_u32   = posnEnd_u32 / 2u;
   Std_ReturnType dataRetVal_u8 = DCM_E_REQUEST_NOT_ACCEPTED;
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
   if(CfgSwcServiceDcm_astListDid[posnStart_u32].dataDid_u16 == did){
      idxDidIndexType_st->idxIndex_u16 = (uint16)posnStart_u32;
      idxDidIndexType_st->dataRange_b = FALSE;
      idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
      idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
      dataRetVal_u8=E_OK;
   }
   else if(CfgSwcServiceDcm_astListDid[posnEnd_u32].dataDid_u16 == did){
      idxDidIndexType_st->idxIndex_u16=(uint16)posnEnd_u32;
      idxDidIndexType_st->dataRange_b = FALSE;
      idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
      idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
      dataRetVal_u8=E_OK;
   }
   else{
      while(posnDid_u32 > 0u){
         posnDid_u32 += posnStart_u32;
         if(CfgSwcServiceDcm_astListDid[posnDid_u32].dataDid_u16 == did){
            idxDidIndexType_st->idxIndex_u16=(uint16)posnDid_u32;
            idxDidIndexType_st->dataRange_b = FALSE;
            idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
            idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
            dataRetVal_u8=E_OK;
            break;
         }
         else if(CfgSwcServiceDcm_astListDid[posnDid_u32].dataDid_u16 > did){
            posnEnd_u32 = posnDid_u32;
         }
         else{
            posnStart_u32 = posnDid_u32;
         }
         posnDid_u32 = (posnEnd_u32-posnStart_u32)/2u;
      }
   }
#endif
   return (dataRetVal_u8);
}
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
Dcm_SupportRet_t Dcm_GetSupportOfIndex(
      Dcm_DIDIndexType_tst*         idxDidIndexType_st
   ,  Dcm_Direction_t               direction
   ,  Dcm_NegativeResponseCodeType* dataNegRespCode_u8
){
   uint32 dataSessionMask_u32=0u;
   uint32 dataSecurityMask_u32=0u;
   Dcm_SupportRet_t                            dataRetVal_u8 = DCM_SUPPORT_OK;
   Std_ReturnType                              dataCondChkRetVal_u8;
   Std_ReturnType                              dataModeChkRetval_u8;
   boolean                                     flgModeRetVal_b;
   const Type_CfgSwcServiceDcm_stDid*          ptrDidConfig        = &CfgSwcServiceDcm_astListDid[idxDidIndexType_st->idxIndex_u16];
   const Dcm_DataInfoConfig_tst*               ptrSigConfig        = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
   const Type_CfgSwcServiceDcm_stInfoDidWrite* ptrControlSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
   void*                                       ptrDIDFnc           = NULL_PTR;
   const Type_CfgSwcServiceDcm_stDidExtended*  pcstDidExtended     = ptrDidConfig->pcstDidExtended;
   uint16                                      dataDid_u16         = ptrDidConfig->dataDid_u16;
   Dcm_NegativeResponseCodeType                dataNrc_u8          = 0x0;
   *dataNegRespCode_u8     = 0x00;
   if(direction == DCM_SUPPORT_READ){
      dataSessionMask_u32  = pcstDidExtended->dataAllowedSessRead_u32;
      dataSecurityMask_u32 = pcstDidExtended->dataAllowedSecRead_u32;
   }
   else{
      dataSessionMask_u32  = pcstDidExtended->dataAllowedSessWrite_u32;
      dataSecurityMask_u32 = pcstDidExtended->dataAllowedSecWrite_u32;
   }
   if(
      ((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL)
   ){
      if((Dcm_DsldGetActiveSecurityMask_u32 () & dataSecurityMask_u32) != 0x0uL){
         dataCondChkRetVal_u8 = E_OK;
         flgModeRetVal_b=TRUE;
         if(direction == DCM_SUPPORT_READ){
            if(pcstDidExtended->adrUserReadModeRule_pfct!=NULL_PTR){
               dataModeChkRetval_u8 = (*pcstDidExtended->adrUserReadModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
            }
            else{
               dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
            }
            if(dataModeChkRetval_u8!=E_OK){
               if(dataNrc_u8==0x00){
                  dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
               }
               flgModeRetVal_b = FALSE;
            }
            else{
               dataNrc_u8 =0x00;
            }
            if(FALSE != flgModeRetVal_b){
               if(FALSE == idxDidIndexType_st->dataRange_b){
                  while((Dcm_DidSignalIdx_u16<ptrDidConfig->nrSig_u16)&&(dataCondChkRetVal_u8==E_OK)){
                     ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                     ptrControlSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
                     if(
                           (ptrSigConfig->usePort_u8 != USE_BLOCK_ID)
                        && (USE_DATA_ELEMENT_SPECIFIC_INTERFACES == ptrDidConfig->didUsePort_u8)
                     ){
                        if(
                              (ptrSigConfig->adrReadFnc_cpv != NULL_PTR)
                           || (
                                 (TRUE == ptrDidConfig->AtomicorNewSRCommunication_b)
                              && (ptrDidConfig->pcstSignalDid[Dcm_DidSignalIdx_u16].fptrSenderReceiverRead != NULL_PTR)
                           )
                        ){
                           if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR){
                              ptrDIDFnc=ptrControlSigConfig->adrCondChkRdFnc_cpv;
                              if(
                                    (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)
                                 || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                              ){
                                 dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrDIDFnc))(dataNegRespCode_u8);
                              }
                              else{
                                 if(
                                    (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
                                    (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                                 ){
                                    dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, dataNegRespCode_u8);
                                    if(dataCondChkRetVal_u8 == E_OK){
                                       idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                                    }
                                 }
                              }
                              if(
                                    (Dcm_IsInfrastructureErrorPresent_b(dataCondChkRetVal_u8) != FALSE)
                                 && (
                                       (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                                    || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                                 )
                              ){
                                 *dataNegRespCode_u8 =0;
                              }
                              if(dataCondChkRetVal_u8!=E_OK){
                                 break;
                              }
                              else{
                                 *dataNegRespCode_u8=0x00;
                              }
                           }
                        }
                        else{
                           *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                           DCM_DET_ERROR(DCM_RDBI_ID, DCM_E_PARAM_POINTER)
                        }
                     }
                     Dcm_DidSignalIdx_u16++;
                  }
               }
            }
            else{
               *dataNegRespCode_u8 = dataNrc_u8;
            }
         }
         else if(direction == DCM_SUPPORT_WRITE){
            if(pcstDidExtended->adrUserWriteModeRule_pfct!=NULL_PTR){
               dataModeChkRetval_u8 = (*pcstDidExtended->adrUserWriteModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
            }
            else{
               dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
            }
            if(dataModeChkRetval_u8!=E_OK){
               if(dataNrc_u8==0x00){
                  dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
               }
               flgModeRetVal_b = FALSE;
            }
            else{
               dataNrc_u8=0x00;
            }
            if(FALSE == flgModeRetVal_b){
               *dataNegRespCode_u8 = dataNrc_u8;
            }
         }
         if((dataCondChkRetVal_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00)){
            Dcm_DidSignalIdx_u16 = 0x0;
            idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
         }
         else if(dataCondChkRetVal_u8 == DCM_E_PENDING){
            *dataNegRespCode_u8=0x00;
            dataRetVal_u8 = DCM_SUPPORT_CONDITION_PENDING;
            idxDidIndexType_st->dataopstatus_b = DCM_PENDING;
         }
         else{
            if(*dataNegRespCode_u8==0x00){
               *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
            dataRetVal_u8       = DCM_SUPPORT_CONDITION_VIOLATED;
            Dcm_DidSignalIdx_u16 = 0x0;
            idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
         }
      }
      else{
         *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
         dataRetVal_u8       = DCM_SUPPORT_SECURITY_VIOLATED;
      }
   }
   else{
      *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
      dataRetVal_u8       = DCM_SUPPORT_SESSION_VIOLATED;
   }
   return dataRetVal_u8;
}
#endif

#if((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
Std_ReturnType Dcm_GetDIDData(
      Dcm_DIDIndexType_tst* idxDidIndexType_st
   ,  uint8*                targetBuffer
){
   const Type_CfgSwcServiceDcm_stDid* ptrDidConfig  = &CfgSwcServiceDcm_astListDid[idxDidIndexType_st->idxIndex_u16];
   void*                              ptrDIDFnc     = NULL_PTR;
   boolean                            FixedLength_b = TRUE;
   const Dcm_DataInfoConfig_tst*      ptrSigConfig;
   uint32                             posnTargetSig_u32;
   if(targetBuffer!= NULL_PTR){
      if(idxDidIndexType_st->dataRange_b == FALSE){
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
            for(
            ;
            ((idxDidIndexType_st->nrNumofSignalsRead_u16) < (ptrDidConfig->nrSig_u16));
            idxDidIndexType_st->nrNumofSignalsRead_u16++
            ){
               ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[idxDidIndexType_st->nrNumofSignalsRead_u16].idxDcmDspDatainfo_u16];
               posnTargetSig_u32 = (idxDidIndexType_st->dataSignalLengthInfo_u32);
               if(
               ((s_dataLengthFnc_retVal_u8==E_OK)&&(s_dataRetVal_u8==E_OK))||(s_dataLengthFnc_retVal_u8==DCM_E_PENDING)
               ){
                  if(FALSE != FixedLength_b){
                     posnTargetSig_u32 =(uint32)(ptrDidConfig->pcstSignalDid[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16);
                     s_datasignallength_u32 = (uint32)((ptrSigConfig->dataSize_u16) + posnTargetSig_u32);
                     s_dataLengthFnc_retVal_u8 = E_OK;
                  }
                  else{
                     s_datasignallength_u32 = (uint32)(s_datasignallength_u32 + idxDidIndexType_st->dataSignalLengthInfo_u32);
                  }
               }
               if(
                     (ptrSigConfig->adrReadFnc_cpv != NULL_PTR)
                  || (
                           (TRUE == ptrDidConfig->AtomicorNewSRCommunication_b)
                        && (ptrDidConfig->pcstSignalDid[idxDidIndexType_st->nrNumofSignalsRead_u16].fptrSenderReceiverRead != NULL_PTR)
                     )
               ){
                  ptrDIDFnc=ptrSigConfig->adrReadFnc_cpv;
                  if(
                        (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)
                     || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                  ){
                  }
#if((DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED!= DCM_CFG_OFF))
                  else if(
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
                     || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                  ){
                     s_dataRetVal_u8 = (*(ReadFunc2_ptr)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &targetBuffer[posnTargetSig_u32]);
                     if(s_dataRetVal_u8==E_OK){
                        idxDidIndexType_st->dataopstatus_b=DCM_INITIAL;
                     }
                  }
#endif
                  else{
                  }
                  if(
                        (Dcm_IsInfrastructureErrorPresent_b(s_dataRetVal_u8) != FALSE)
                     && (
                           (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                        || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                        || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)
                        || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE)
                     )
                  ){
                     s_dataRetVal_u8 =E_NOT_OK;
                  }
                  if(s_dataRetVal_u8 != E_OK){
                     break;
                  }
                  else{
                     if(
                           (ptrSigConfig->dataType_u8==DCM_BOOLEAN)
                        && (
                                 (idxDidIndexType_st->nrNumofSignalsRead_u16 == ptrDidConfig->nrSig_u16-1u)
                              || (
                                    ptrDidConfig->pcstSignalDid[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16
                                 != ptrDidConfig->pcstSignalDid[idxDidIndexType_st->nrNumofSignalsRead_u16+1].posnSigBit_u16
                              )
                           )
                     ){
                        idxDidIndexType_st->dataSignalLengthInfo_u32+=1u;
                     }
                     else{
                        idxDidIndexType_st->dataSignalLengthInfo_u32 = s_datasignallength_u32;
                     }
                  }
               }
               else{
               }
            }
#endif
      }
      else{
      }
      if(s_dataRetVal_u8 != DCM_E_PENDING){
         idxDidIndexType_st->nrNumofSignalsRead_u16=0x0;
         idxDidIndexType_st->dataSignalLengthInfo_u32=0x0;
      }
   }
   else{
      s_dataRetVal_u8 = E_NOT_OK;
   }
   return s_dataRetVal_u8;
}
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
Std_ReturnType Dcm_GetActiveDid(uint16* dataDid_u16){
   Std_ReturnType dataRetVal_u8 = E_NOT_OK;
   if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER){
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
      dataRetVal_u8 = Dcm_GetActiveRDBIDid(dataDid_u16);
#endif
   }
   else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER){
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
      dataRetVal_u8 = Dcm_GetActiveWDBIDid(dataDid_u16);
#endif
   }
   else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER){
   }
   else{
   }
   return dataRetVal_u8;
}
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)      ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)     ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)                     ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
Std_ReturnType Dcm_GetIndexOfDID(
      uint16                did
   ,  Dcm_DIDIndexType_tst* idxDidIndexType_st
){
   Std_ReturnType result = E_NOT_OK;
   Dcm_ResetDIDIndexstruct(idxDidIndexType_st);
   result = Dcm_Lok_GetIndexOfDID(did, idxDidIndexType_st);
   if(result == E_OK){
      (*idxDidIndexType_st).dataopstatus_b=DCM_INITIAL;
   }
   return result;
}
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

