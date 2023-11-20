#include "Std_Types.hpp"

#include "DcmDspUds_Rdbi_Inf.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_StRdbi_ten       ,DCM_VAR) Dcm_stRdbi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16             ,DCM_VAR) Dcm_RdbiReqDidNb_u16;
VAR (uint16             ,DCM_VAR) Dcm_NumOfIndices_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint32            ,DCM_VAR) Dcm_TotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspReadDidOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxRdbiDidIndexType_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_LenCalc_ten, DCM_VAR) Dcm_StLenCalc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
P2VAR (uint8,DCM_VAR,DCM_INTERN_DATA) Dcm_IdxList_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint32 ,DCM_VAR)  Dcm_NumberOfBytesInResponse_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16 ,DCM_VAR)  Dcm_NumberOfProcessedDIDs_u16;
VAR (uint16 ,DCM_VAR)  Dcm_NumberOfAcceptedDIDs_u16;

static VAR (uint16,  DCM_VAR) s_dataDID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_GetData_ten, DCM_VAR) Dcm_GetDataState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR (Std_ReturnType, DCM_VAR) s_dataLengthFnc_retVal_u8;

static VAR (Std_ReturnType, DCM_VAR) s_dataReadIfcVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16 ,DCM_VAR)  Dcm_GetDataNumOfIndex_u16;

static VAR (uint16, DCM_VAR) s_dataID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint32 ,DCM_VAR)  Dcm_GetDataTotalLength_u32;

static VAR (uint32,DCM_VAR) s_posnTargetSig_u32;

static VAR (uint32,DCM_VAR) s_datalengthinfo_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"


#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (void,DCM_CODE) Dcm_Dsp_RdbiIni (void){
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataCondChkRetVal_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataReadIfcRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;

   dataCondChkRetVal_u8 = E_OK;
   dataReadIfcRetVal_u8 = E_OK;
   dataNegResCode_u8 = 0x0;
   ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
   ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
   ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

   if((Dcm_DspReadDidOpStatus_u8 == DCM_PENDING) && (Dcm_flgDspDidRangePending_b == FALSE)){
        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)    ||
                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)){
            {
            if((Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH) && (ptrControlSigConfig->adrCondChkRdFnc_cpv != NULL_PTR)){
                dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(DCM_CANCEL, &dataNegResCode_u8);
            }
            if((Dcm_stRdbi_en == DCM_RDBI_GET_DATA)&&       \
                    (ptrSigConfig->adrReadFnc_cpv != NULL_PTR)){
                    dataReadIfcRetVal_u8 = (*(ReadFunc2_ptr)(ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL,NULL_PTR);
                }
            }
        }
   }
   Dcm_stRdbi_en         = DCM_RDBI_IDLE;
   Dcm_StLenCalc_en      = DCM_LENCALC_STATUS_INIT;
   Dcm_GetDataState_en      = DCM_GETDATA_STATUS_INIT;
   Dcm_DidSignalIdx_u16 = 0x0;
   Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
   Dcm_flgDspDidRangePending_b=FALSE;
   Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);
   Dcm_PeriodicSchedulerRunning_b=FALSE;
   (void)dataCondChkRetVal_u8;
   (void)dataReadIfcRetVal_u8;
   (void)dataNegResCode_u8;
   (void)ptrDidConfig;
   (void)ptrSigConfig;
   (void)ptrControlSigConfig;
}

FUNC (Dcm_LenCalcRet_ten,DCM_CODE) Dcm_DspGetTotalLengthOfDIDs_en (P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrSourceIds_pu8
   ,     VAR (uint16,AUTOMATIC) nrDids_u16
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) adrNumOfIndices_pu16
   ,     P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrTotalLength_pu32
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (Dcm_LenCalcRet_ten, AUTOMATIC) dataRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
    dataRetVal_u8 = DCM_LENCALC_RETVAL_OK;
    ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

   if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_INIT){
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
                    (Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETSUPPORT))){
      if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETINDEX){
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;
            s_dataDID_u16 = (uint16)(((uint16)(adrSourceIds_pu8[Dcm_NumberOfProcessedDIDs_u16 * 2]))<<8u)+
                    (uint16)((uint16)(adrSourceIds_pu8[(Dcm_NumberOfProcessedDIDs_u16 * 2)+1]));

            dataFuncRetVal_en = Dcm_GetIndexOfDID(s_dataDID_u16, &s_Dcm_idxRdbiDidIndexType_st);
         if(dataFuncRetVal_en == E_OK){
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETSUPPORT;
                Dcm_DidSignalIdx_u16 = 0x0;
            }
         else if(dataFuncRetVal_en == DCM_E_PENDING){
                dataRetVal_u8=DCM_LENCALC_RETVAL_PENDING;
            }
            else{
                Dcm_NumberOfProcessedDIDs_u16++;
            }
        }
      if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETSUPPORT){
            VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_st;
            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataSupportInfo_st=Dcm_GetSupportOfIndex (&s_Dcm_idxRdbiDidIndexType_st, DCM_SUPPORT_READ,dataNegRespCode_u8 );
         switch(dataSupportInfo_st){
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
      if(Dcm_StLenCalc_en == DCM_LENCALC_STATUS_GETLENGTH){
            VAR (uint32,AUTOMATIC) dataLength_u32;
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;
            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex(&s_Dcm_idxRdbiDidIndexType_st,&dataLength_u32,s_dataDID_u16);
         if(dataFuncRetVal_en == E_OK){
            if(dataLength_u32 > 0u){
                            Dcm_NumberOfBytesInResponse_u32 = (uint32)(Dcm_NumberOfBytesInResponse_u32 + dataLength_u32);
                            Dcm_NumberOfAcceptedDIDs_u16 ++;
                            Dcm_NumberOfProcessedDIDs_u16++;
                            *Dcm_IdxList_pu8= (uint8)(s_dataDID_u16>>8u);
                            Dcm_IdxList_pu8++;
                            *Dcm_IdxList_pu8= (uint8)s_dataDID_u16;
                            Dcm_IdxList_pu8++;
                            Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                }
                else{
                    Dcm_NumberOfProcessedDIDs_u16++;
                    Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                }
            }
         else if(dataFuncRetVal_en == DCM_INFRASTRUCTURE_ERROR){
                *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
            }
         else if(dataFuncRetVal_en == E_NOT_OK){
                *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
            }
         else if(dataFuncRetVal_en == DCM_E_PENDING){
                dataRetVal_u8 = DCM_LENCALC_RETVAL_PENDING;
            }
            else{
            if(*dataNegRespCode_u8 == 0x00){
                    *dataNegRespCode_u8    = DCM_E_GENERALREJECT;
                }
                Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
            }
        }
   }
   if(dataRetVal_u8 == DCM_LENCALC_RETVAL_OK){
        *adrTotalLength_pu32    = Dcm_NumberOfBytesInResponse_u32;
        *adrNumOfIndices_pu16   = Dcm_NumberOfAcceptedDIDs_u16;
        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
   }
    (void )ptrDidConfig;
    return (dataRetVal_u8);
}

FUNC (Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en (P2CONST (uint8, AUTOMATIC,DCM_INTERN_CONST) adrIdBuffer_pcu8
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8
   ,     VAR (uint16,DCM_INTERN_DATA) nrIndex_u16
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR (uint32,DCM_INTERN_DATA) adrTotalLength_pu32
){
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrRDBIFnc;
   VAR (Std_ReturnType,AUTOMATIC) dataNrcRetval_u8;
   VAR (Dcm_GetDataRet_ten, AUTOMATIC) dataRetVal_u8;
   static VAR(uint32 ,DCM_VAR)  Dcm_GetDataLengthOfCurrentData_u32;
    dataRetVal_u8     = DCM_GETDATA_RETVAL_OK;
    dataNrcRetval_u8 = E_OK;
    *dataNegRespCode_u8 = 0x0;
   if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_INIT){

        Dcm_GetDataNumOfIndex_u16  = nrIndex_u16;
        Dcm_GetDataTotalLength_u32 = adrTotalLength_pu32;
        Dcm_GetDataState_en            = DCM_GETDATA_STATUS_GETLENGTH;
        s_dataReadIfcVal_u8    = E_OK;
        s_dataLengthFnc_retVal_u8 = E_OK;
        s_datalengthinfo_u32 = 0;

   }
   while((Dcm_GetDataNumOfIndex_u16>0) &&
            ((Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETDATA) ||
                    (Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETLENGTH)) &&
                    (dataRetVal_u8 == DCM_GETDATA_RETVAL_OK)){
      if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETLENGTH){
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;
            s_dataID_u16 = (uint16)((uint16)((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1)*2u)]<<(uint8)8) +
                    ((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1u)*2u)+1u]));
            dataFuncRetVal_en = Dcm_GetIndexOfDID(s_dataID_u16, &s_Dcm_idxRdbiDidIndexType_st);
         if(dataFuncRetVal_en == E_OK){
                dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex (&s_Dcm_idxRdbiDidIndexType_st,&Dcm_GetDataLengthOfCurrentData_u32,s_dataID_u16);
            }

         switch(dataFuncRetVal_en){
                case E_OK:
                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_GETDATA;
                    Dcm_DidSignalIdx_u16 = 0x0u;
                    s_datalengthinfo_u32 = 0x0u;
   				Dcm_DspReadDidOpStatus_u8=DCM_INITIAL;
                    break;

                case DCM_E_PENDING:
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                    break;

                case E_NOT_OK:
                case DCM_INFRASTRUCTURE_ERROR:
                default:
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                    break;
            }
        }
      if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETDATA){
            VAR (uint32,AUTOMATIC) posnTarget_u32= (Dcm_GetDataTotalLength_u32 - Dcm_GetDataLengthOfCurrentData_u32);
            VAR (uint32, AUTOMATIC) dataSignallength_u32;
            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
            dataSignallength_u32 = 0x0;
         if(s_dataReadIfcVal_u8 != DCM_E_PENDING){
                DCM_MEMSET(&adrTargetBuffer_pu8[posnTarget_u32], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, Dcm_GetDataLengthOfCurrentData_u32);
            }
         if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b == FALSE){
            while(Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16){
                    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
               if(((s_dataLengthFnc_retVal_u8 == E_OK) && (s_dataReadIfcVal_u8 == E_OK)) || (s_dataLengthFnc_retVal_u8 == DCM_E_PENDING)){
                  if(FALSE != ptrSigConfig->dataFixedLength_b){
                            s_posnTargetSig_u32 = (posnTarget_u32+(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8));
                            if((ptrSigConfig->dataType_u8==DCM_BOOLEAN) &&         \
                                    (((Dcm_DidSignalIdx_u16==(ptrDidConfig->nrSig_u16-1)))   ||                                      \
                                            (((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8) !=              \
                                                    (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16 + 1].posnSigBit_u16 / 8))))){
                                s_datalengthinfo_u32+=1u;
                            }
                     else if(ptrSigConfig->dataType_u8 != DCM_BOOLEAN){
                                s_datalengthinfo_u32  = ((ptrSigConfig->dataSize_u16/8) + (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8));
                            }
                     else{
                            }
                            s_dataLengthFnc_retVal_u8 = E_OK;
                        }
                  else{
                        }
                    }
               if((ptrSigConfig->adrReadFnc_cpv) != NULL_PTR){
                        ptrRDBIFnc=ptrSigConfig->adrReadFnc_cpv;
                        if((ptrSigConfig->usePort_u8 ==USE_DATA_SYNCH_FNC) ||          \
                                (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)){
                        }
                        else if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
                                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)){
                                s_dataReadIfcVal_u8 = (*(ReadFunc2_ptr)(ptrRDBIFnc))(Dcm_DspReadDidOpStatus_u8, &adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                        }
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
               case E_OK: {
                            posnTarget_u32=(posnTarget_u32-2u);
                            adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((ptrDidConfig->dataDid_u16)>>8u);
                            adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((ptrDidConfig->dataDid_u16));
                            Dcm_GetDataTotalLength_u32 = (Dcm_GetDataTotalLength_u32 - (Dcm_GetDataLengthOfCurrentData_u32 + 2u));
                            Dcm_GetDataNumOfIndex_u16--;
                            Dcm_GetDataState_en=DCM_GETDATA_STATUS_GETLENGTH;
                            break;
                        }

               case DCM_E_PENDING: {
                        *dataNegRespCode_u8=0x00;
                        dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                        break;
                    }

               case DCM_E_REQUEST_ENV_NOK: {
                  if(E_OK == s_dataLengthFnc_retVal_u8){
                                dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,s_posnTargetSig_u32,dataNegRespCode_u8);
                            }
                  if(dataNrcRetval_u8 != E_OK){
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            }
                            dataRetVal_u8 =DCM_GETDATA_RETVAL_INVALIDCONDITIONS;
                            Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                            Dcm_DidSignalIdx_u16 = 0x0;
                            break;
                        }

               case E_NOT_OK: {
                  if(E_OK == s_dataLengthFnc_retVal_u8){
                                dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,s_posnTargetSig_u32,dataNegRespCode_u8);
                            }
                  if(dataNrcRetval_u8 != E_OK){
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            }
                        }

               default: {
                            dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;
                            Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                            Dcm_DidSignalIdx_u16 = 0x0;
                            break;
                        }
                    }
            }
            else{
            }
            (void)dataSignallength_u32;
        }
   }
   if(dataRetVal_u8 == DCM_GETDATA_RETVAL_OK){
        Dcm_GetDataState_en=DCM_GETDATA_STATUS_INIT;
   }
    (void )ptrDidConfig;
    (void )ptrSigConfig;
    (void )ptrControlSigConfig;
    return dataRetVal_u8;
}

FUNC (Std_ReturnType,DCM_CODE) SwcServiceDcm_tReadDataByIdentifier(
   VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
   P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
   VAR(Std_ReturnType,AUTOMATIC)  dataRetVal_u8;
    *dataNegRespCode_u8   = 0x0u;
    dataRetVal_u8=DCM_E_PENDING;
   if(OpStatus == DCM_CANCEL){
        Dcm_Dsp_RdbiIni();
        dataRetVal_u8 = E_OK;
   }
   else{
      if(Dcm_stRdbi_en == DCM_RDBI_IDLE){
            if((pMsgContext->reqDataLen < DCM_RDBI_SIZE_DID) ||
                    ((pMsgContext->reqDataLen & 0x0001u) != 0uL)){
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
            }
            else{
                Dcm_RdbiReqDidNb_u16 = (uint16)(pMsgContext->reqDataLen / DCM_RDBI_SIZE_DID);
                if((DCM_CFG_MAXDIDTOREAD != 0u) &&
                        (Dcm_RdbiReqDidNb_u16 > DCM_CFG_MAXDIDTOREAD)){
                    *dataNegRespCode_u8  = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                }
                else{
                    Dcm_stRdbi_en = DCM_RDBI_GET_LENGTH;
                }
            }
        }
      if(Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH){
            VAR (Dcm_LenCalcRet_ten, AUTOMATIC) dataFuncRetVal_en;
            dataFuncRetVal_en = Dcm_DspGetTotalLengthOfDIDs_en (&pMsgContext->reqData[0]
   ,     Dcm_RdbiReqDidNb_u16
   ,     &Dcm_NumOfIndices_u16
   ,     &Dcm_TotalLength_u32
   ,     dataNegRespCode_u8);
         switch(dataFuncRetVal_en){
                case DCM_LENCALC_RETVAL_OK:
                    Dcm_TotalLength_u32 = (uint32)(Dcm_TotalLength_u32 + (2 * Dcm_NumOfIndices_u16));
                    pMsgContext->resDataLen = (Dcm_MsgLenType)Dcm_TotalLength_u32;
               if(Dcm_TotalLength_u32 <= pMsgContext->resMaxDataLen){
                        Dcm_stRdbi_en = DCM_RDBI_GET_DATA;
                    }
               else{
                        *dataNegRespCode_u8  = DCM_E_RESPONSETOOLONG;
                        Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                    }
               if((Dcm_RdbiReqDidNb_u16 > 1) && (Dcm_NumOfIndices_u16 != 0) && (Dcm_stRdbi_en == DCM_RDBI_GET_DATA)){
                        VAR (Std_ReturnType, AUTOMATIC) dataCheckLenRetVal_u8;
                        dataCheckLenRetVal_u8 = DcmAppl_DcmCheckRdbiResponseLength(Dcm_TotalLength_u32,Dcm_NumOfIndices_u16,dataNegRespCode_u8);
                  if((*dataNegRespCode_u8 == 0) && (dataCheckLenRetVal_u8 != E_OK)){
                            *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                        }
                  else if((*dataNegRespCode_u8 != 0) && (dataCheckLenRetVal_u8 != E_OK)){
                            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                        }
                  else{
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
         if(Dcm_NumOfIndices_u16 == 0){
                *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
                Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
            }
            else{
                VAR (Dcm_GetDataRet_ten, AUTOMATIC) dataFuncRetVal_en;
        dataFuncRetVal_en= Dcm_GetData_en(&pMsgContext->reqData[0]
   ,     pMsgContext->resData
   ,     Dcm_NumOfIndices_u16
   ,     dataNegRespCode_u8
   ,     Dcm_TotalLength_u32
        );
            switch(dataFuncRetVal_en){
                case DCM_GETDATA_RETVAL_OK:
                    pMsgContext->resDataLen =  Dcm_TotalLength_u32;
                    Dcm_DidSignalIdx_u16 = 0x0;
                    dataRetVal_u8=E_OK;
                    Dcm_stRdbi_en = DCM_RDBI_IDLE;
                    Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                    break;

                case DCM_GETDATA_RETVAL_PENDING:
                    Dcm_DspReadDidOpStatus_u8 = DCM_PENDING;
                    dataRetVal_u8=DCM_E_PENDING;
                    break;

                case DCM_GETDATA_RETVAL_INVALIDCONDITIONS:
                    *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                    Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                    Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                    break;

                case DCM_GETDATA_RETVAL_INTERNALERROR:
                default:
                  if(0x0 == *dataNegRespCode_u8){
                        *dataNegRespCode_u8  = DCM_E_GENERALREJECT;
                    }
                  else{
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

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRDBIDid(
   P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16){
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
    ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
    dataRetVal_u8 = E_NOT_OK;
   if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b == FALSE){
        *dataDid_u16 = ptrDidConfig->dataDid_u16;
        dataRetVal_u8 = E_OK;
   }
   else{
   }
    return (dataRetVal_u8);
}

FUNC(void, DCM_CODE) Dcm_Lok_DspRdbiConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  status_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

