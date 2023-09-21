#include "Std_Types.hpp"

#include "DcmDspUds_Rdbi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
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

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

static VAR(boolean , DCM_VAR) s_DcmReadDataLengthRteCallPlaced_b ;

static VAR (boolean, DCM_VAR) s_DcmReadDataRteCallPlaced_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_RDBIPAGEDBUFFERSUPPORT == DCM_CFG_OFF)))
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean      ,DCM_VAR) Dcm_flgNvmReadPending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)||(DCM_CFG_LIMITRDBIRESPTOBUFSIZE != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_MsgLenType,     DCM_VAR)  Dcm_DspRdbiMaxRespLen_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif

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

#if((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)||(DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF))

   if((Dcm_DspReadDidOpStatus_u8 == DCM_PENDING) && (Dcm_flgDspDidRangePending_b == FALSE))
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)    ||
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)         ||
#endif
                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
        {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
            {

            if((Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH) && (ptrControlSigConfig->adrCondChkRdFnc_cpv!=NULL_PTR))
                {

                    dataCondChkRetVal_u8 = (*(CondChkReadFunc3_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(DCM_CANCEL);
                }

                if((Dcm_stRdbi_en == DCM_RDBI_GET_DATA)&&       \
                        (ptrSigConfig->adrReadFnc_cpv!=NULL_PTR))
                {

                    dataReadIfcRetVal_u8 = (*(ReadFunc11_ptr)(ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL);
                }
            }
            else
#endif
            {

                if((Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH) && (ptrControlSigConfig->adrCondChkRdFnc_cpv!=NULL_PTR))
                {

                dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(DCM_CANCEL, &dataNegResCode_u8);
            }

            if((Dcm_stRdbi_en == DCM_RDBI_GET_DATA)&&       \
                    (ptrSigConfig->adrReadFnc_cpv!=NULL_PTR))
            {
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                if(ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
                {

                    dataReadIfcRetVal_u8 = (*(ReadFunc9_ptr)(ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL,NULL_PTR,NULL_PTR,&dataNegResCode_u8);
                }
                else
#endif
                {

                    dataReadIfcRetVal_u8 = (*(ReadFunc2_ptr)(ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL,NULL_PTR);
                }

                }
            }
        }
#endif
   }
#endif

#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

   if((Dcm_DspReadDidOpStatus_u8 == DCM_PENDING) && (Dcm_flgDspDidRangePending_b!=FALSE))
   {
        dataReadIfcRetVal_u8 = (Dcm_DIDRangeConfig_cast[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16].adrReadFnc_pfct) (s_Dcm_idxRdbiDidIndexType_st.dataRangeDid_16,NULL_PTR,DCM_CANCEL,NULL_PTR,&dataNegResCode_u8);
   }
#endif
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
   s_DcmReadDataLengthRteCallPlaced_b  = FALSE;
   s_DcmReadDataRteCallPlaced_b = FALSE;
#endif

    Dcm_stRdbi_en         = DCM_RDBI_IDLE;
    Dcm_StLenCalc_en      = DCM_LENCALC_STATUS_INIT;
    Dcm_GetDataState_en      = DCM_GETDATA_STATUS_INIT;
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;

    Dcm_flgDspDidRangePending_b=FALSE;
#if((DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_RDBIPAGEDBUFFERSUPPORT == DCM_CFG_OFF)))

    Dcm_flgNvmReadPending_b = FALSE;
#endif

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
    Dcm_ResetAsynchFlags();
#endif
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

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (Dcm_LenCalcRet_ten,DCM_CODE) Dcm_DspGetTotalLengthOfDIDs_en (P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrSourceIds_pu8
   ,     VAR (uint16,AUTOMATIC) nrDids_u16
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) adrNumOfIndices_pu16
   ,     P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrTotalLength_pu32
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (Dcm_LenCalcRet_ten, AUTOMATIC) dataRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
   VAR (boolean, AUTOMATIC) flagRdbi_PgdPort_b;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
#endif
    dataRetVal_u8 = DCM_LENCALC_RETVAL_OK;
    ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

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

            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;

            s_dataDID_u16 = (uint16)(((uint16)(adrSourceIds_pu8[Dcm_NumberOfProcessedDIDs_u16 * 2]))<<8u)+
                    (uint16)((uint16)(adrSourceIds_pu8[(Dcm_NumberOfProcessedDIDs_u16 * 2)+1]));

            dataFuncRetVal_en = Dcm_GetIndexOfDID(s_dataDID_u16, &s_Dcm_idxRdbiDidIndexType_st);

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

            if((dataFuncRetVal_en == E_OK) && (s_Dcm_idxRdbiDidIndexType_st.dataRange_b == FALSE))
            {
                ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

                if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
                {
                    if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))(s_dataDID_u16)!=E_OK)
                    {
                        dataFuncRetVal_en = E_NOT_OK;
                    }
                }
            }
#endif

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
            VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_st;

            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
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
            VAR (uint32,AUTOMATIC) dataLength_u32;
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

            flagRdbi_PgdPort_b = FALSE;
#endif
            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

            dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex(&s_Dcm_idxRdbiDidIndexType_st,&dataLength_u32,s_dataDID_u16);

            if(dataFuncRetVal_en==E_OK )
            {
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

                ptrSigConfig= &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[0].idxDcmDspDatainfo_u16];
                if(ptrSigConfig->usePort_u8==USE_DATA_RDBI_PAGED_FNC)
                {

                    flagRdbi_PgdPort_b=TRUE;
                }
#endif

                if(dataLength_u32>0u)
                {
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

                    if(((dataLength_u32 + DCM_RDBI_SIZE_DID) <= Dcm_DspRdbiMaxRespLen_u32)||(TRUE==flagRdbi_PgdPort_b))
                    {
#endif
#if(DCM_CFG_LIMITRDBIRESPTOBUFSIZE != DCM_CFG_OFF)
                        if(((Dcm_NumberOfBytesInResponse_u32 + dataLength_u32 + 2u) > Dcm_DspRdbiMaxRespLen_u32) && (Dcm_NumberOfAcceptedDIDs_u16 == 0u))
                        {

                            *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                            dataRetVal_u8 = DCM_LENCALC_RETVAL_ERROR;
                            Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                        }
                        else if((Dcm_NumberOfBytesInResponse_u32 + dataLength_u32 + ((Dcm_NumberOfAcceptedDIDs_u16 + 1) *2 )) > Dcm_DspRdbiMaxRespLen_u32)
                        {

                            dataRetVal_u8 = DCM_LENCALC_RETVAL_OK;
                            break;
                        }
                        else
#endif
                        {

                            Dcm_NumberOfBytesInResponse_u32 = (uint32)(Dcm_NumberOfBytesInResponse_u32 + dataLength_u32);

                            Dcm_NumberOfAcceptedDIDs_u16 ++;
                            Dcm_NumberOfProcessedDIDs_u16++;

                            *Dcm_IdxList_pu8= (uint8)(s_dataDID_u16>>8u);

                            Dcm_IdxList_pu8++;
                            *Dcm_IdxList_pu8= (uint8)s_dataDID_u16;

                            Dcm_IdxList_pu8++;

                            Dcm_StLenCalc_en = DCM_LENCALC_STATUS_GETINDEX;
                        }
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                    }
                    else
                    {
                        *dataNegRespCode_u8    = DCM_E_RESPONSETOOLONG;
                        dataRetVal_u8          = DCM_LENCALC_RETVAL_ERROR;
                        Dcm_StLenCalc_en = DCM_LENCALC_STATUS_INIT;
                    }
#endif
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

    (void )ptrDidConfig;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    (void )ptrSigConfig;
#endif
    return (dataRetVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_MsgType,     DCM_VAR)  Dcm_DspRdbiRespBufPtr_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_MsgLenType,     DCM_VAR)  s_Dcm_FilledLengthCurrentPage_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR (Std_ReturnType, DCM_VAR) s_dataReadRetVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_SEPARATEBUFFERFORTXANDRX_ENABLED == DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(uint8,     DCM_VAR)  Dcm_DspRdbiDidBuffer_au8[DCM_CFG_RDBIREQUESTBUFFERSIZE];

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,     DCM_VAR)  Dcm_RdbiFirstPageSent_b;
static VAR(boolean,     DCM_VAR)  s_Dcm_PagedDid_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(void,DCM_CODE) Dcm_Dsp_RDBIUpdatePage(
        VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr
   ,     VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
);

static FUNC(void,DCM_CODE) Dcm_Dsp_RDBIUpdatePage(
        VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr
   ,     VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
)
{

    Dcm_DspRdbiMaxRespLen_u32 = PageLen;
    Dcm_DspRdbiRespBufPtr_u8  = PageBufPtr;
}

static FUNC(Dcm_GetDataRet_ten,DCM_CODE) Dcm_Dsp_RDBITriggerProcessPage(VAR(Dcm_MsgLenType,AUTOMATIC) PageLen);
static FUNC(Dcm_GetDataRet_ten,DCM_CODE) Dcm_Dsp_RDBITriggerProcessPage(VAR(Dcm_MsgLenType,AUTOMATIC) PageLen)
{

   if(Dcm_RdbiFirstPageSent_b == FALSE)
   {

        Dcm_RdbiFirstPageSent_b = TRUE;
   }

    Dcm_ProcessPage(PageLen);

   s_Dcm_FilledLengthCurrentPage_u32 = 0x0;

    return DCM_GETDATA_PAGED_BUFFER_TX;
}

static FUNC(void,DCM_CODE) Dcm_Dsp_RDBICancelPagebufferHandling(void);
static FUNC(void,DCM_CODE) Dcm_Dsp_RDBICancelPagebufferHandling(void){

   if(Dcm_RdbiFirstPageSent_b == FALSE)
   {

        s_Dcm_FilledLengthCurrentPage_u32 = 0x0;

   }

   else{

        Dcm_ProcessPage(0);

        s_Dcm_FilledLengthCurrentPage_u32 = 0x0;

        DCM_DET_ERROR(DCM_RDBI_ID , DCM_E_WRONG_STATUSVALUE)

        Dcm_GetDataState_en=DCM_GETDATA_STATUS_INIT;
   }
}

static FUNC(void,DCM_CODE) Dcm_Dsp_RDBIClearbuffer(P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8,VAR (uint32,DCM_INTERN_DATA) adrTotalLength_u32);
static FUNC(void,DCM_CODE) Dcm_Dsp_RDBIClearbuffer(P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8,VAR (uint32,DCM_INTERN_DATA) adrTotalLength_u32)
{

    DCM_MEMSET(adrTargetBuffer_pu8, (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, adrTotalLength_u32);
}

static FUNC(void,DCM_CODE) Dcm_GetTypeofDID(P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st)
{
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;

   if(TRUE != idxDidIndexType_st->dataRange_b)
   {
        ptrDidConfig =&Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
        ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[0].idxDcmDspDatainfo_u16];
        if(ptrSigConfig->usePort_u8==USE_DATA_RDBI_PAGED_FNC)
        {

            idxDidIndexType_st->flagPageddid_b=TRUE;

            s_Dcm_PagedDid_b=TRUE;
        }
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetPagedDIDData(P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetPagedDIDData(P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8)
{
   VAR (uint32,DCM_INTERN_DATA) databufferSize_u32;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
    ptrDidConfig =&Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[0].idxDcmDspDatainfo_u16];

   if(s_Dcm_PagedDid_b==TRUE)
   {

        databufferSize_u32 = (Dcm_DspRdbiMaxRespLen_u32-s_Dcm_FilledLengthCurrentPage_u32-2uL);
   }
   else{

        databufferSize_u32 = (Dcm_DspRdbiMaxRespLen_u32-s_Dcm_FilledLengthCurrentPage_u32);
   }

   if(s_dataReadRetVal_u8 != DCM_E_PENDING)
   {

        Dcm_Dsp_RDBIClearbuffer(&adrTargetBuffer_pu8[0],databufferSize_u32);
   }

   if(NULL_PTR != ptrSigConfig->adrReadFnc_cpv)
   {

        s_dataReadRetVal_u8 = (*(ReadFunc9_ptr)(ptrSigConfig->adrReadFnc_cpv))(Dcm_DspReadDidOpStatus_u8, &adrTargetBuffer_pu8[0],&databufferSize_u32,&idxDidIndexType_st->dataNegRespCode_u8);

        idxDidIndexType_st->dataSignalLengthInfo_u32 = databufferSize_u32;
   }
   else{
        s_dataReadRetVal_u8=E_NOT_OK;
   }

   if(DCM_E_RDBI_DATA_PENDING==s_dataReadRetVal_u8)
   {
        if((databufferSize_u32==0x0uL)|| (databufferSize_u32 < 0x8uL) || (databufferSize_u32 > Dcm_DspRdbiMaxRespLen_u32))
        {

            s_dataReadRetVal_u8 = E_NOT_OK;

            idxDidIndexType_st->dataSignalLengthInfo_u32 = 0;
        }
   }
   else if(DCM_E_PENDING==s_dataReadRetVal_u8)
   {
        s_dataReadRetVal_u8 = DCM_E_PENDING;
   }
   else if(E_OK==s_dataReadRetVal_u8)
   {
        if(databufferSize_u32==0x0uL)
        {

            s_dataReadRetVal_u8 = E_NOT_OK;

            idxDidIndexType_st->dataSignalLengthInfo_u32 = 0;
        }
   }
   else{
        s_dataReadRetVal_u8 = E_NOT_OK;

        idxDidIndexType_st->dataSignalLengthInfo_u32 = 0;
   }

    return s_dataReadRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_GetData_ten, DCM_VAR) Dcm_GetDataState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR (Std_ReturnType, DCM_VAR)        s_dataReadIfcRetVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16 ,DCM_VAR)  Dcm_GetDataNumOfIndex_u16;

static VAR (uint16, DCM_VAR)        s_dataDynamicID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint32 ,DCM_VAR)  Dcm_GetDataTotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en (P2CONST (uint8, AUTOMATIC,DCM_INTERN_CONST) adrIdBuffer_pcu8
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8
   ,     VAR (uint16,DCM_INTERN_DATA) nrIndex_u16
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
)
{

#if(DCM_SEPARATEBUFFERFORTXANDRX_ENABLED == DCM_CFG_OFF)
   VAR (uint16, AUTOMATIC) idxLoop_u16;
#endif

   VAR (Std_ReturnType,AUTOMATIC) dataNrcRetval_u8;
   VAR (Dcm_GetDataRet_ten, AUTOMATIC) dataRetVal_u8;
   static VAR (uint32 ,DCM_VAR)  Dcm_GetDataLengthOfCurrentData_u32;
   static VAR (boolean ,DCM_VAR)  Dcm_Pending_DIDData_b;

    dataRetVal_u8  = DCM_GETDATA_RETVAL_OK;
    dataNrcRetval_u8 = E_OK;
    *dataNegRespCode_u8 = 0x0;

   if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_INIT)
   {

        Dcm_GetDataNumOfIndex_u16  = 0;
        Dcm_GetDataState_en            = DCM_GETDATA_STATUS_GETLENGTH;
        Dcm_GetDataLengthOfCurrentData_u32 = 0x0;
        s_Dcm_FilledLengthCurrentPage_u32 = 0x0;
        s_dataReadIfcRetVal_u8 = E_OK;

#if(DCM_SEPARATEBUFFERFORTXANDRX_ENABLED == DCM_CFG_OFF)

        for(idxLoop_u16=0;idxLoop_u16 < (nrIndex_u16 * 2);idxLoop_u16++)
        {
            Dcm_DspRdbiDidBuffer_au8[idxLoop_u16] = adrIdBuffer_pcu8[idxLoop_u16];
        }
#endif
   }

   while((Dcm_GetDataNumOfIndex_u16 < nrIndex_u16) &&
            ((Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETDATA) ||
                    (Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETLENGTH)) &&
                    (dataRetVal_u8          == DCM_GETDATA_RETVAL_OK))
   {

        VAR (uint32,AUTOMATIC) posnTarget_u32;
        posnTarget_u32 = 0x0;

        if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETLENGTH)
        {
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;

#if(DCM_SEPARATEBUFFERFORTXANDRX_ENABLED == DCM_CFG_OFF)

            s_dataDynamicID_u16 = (uint16)((Dcm_DspRdbiDidBuffer_au8[((Dcm_GetDataNumOfIndex_u16)*2u)]<<(uint8)8u) + (Dcm_DspRdbiDidBuffer_au8[((Dcm_GetDataNumOfIndex_u16)*2u)+1u]));
#else

            s_dataDynamicID_u16 = (uint16)((adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16)*2u)]<<(uint8)8u) +  (adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16)*2u)+1u]));
#endif

            Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);

            dataFuncRetVal_en = Dcm_GetIndexOfDID(s_dataDynamicID_u16, &s_Dcm_idxRdbiDidIndexType_st);

            if(E_OK == dataFuncRetVal_en)
            {

                dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex (&s_Dcm_idxRdbiDidIndexType_st,&Dcm_GetDataLengthOfCurrentData_u32,s_dataDynamicID_u16);

                if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b!= FALSE)
                {

                    s_Dcm_idxRdbiDidIndexType_st.dataSignalLengthInfo_u32 = Dcm_GetDataLengthOfCurrentData_u32;
                }

            }

            switch(dataFuncRetVal_en)
            {

                case (Std_ReturnType)E_OK:
                        Dcm_GetDataState_en = DCM_GETDATA_STATUS_GETDATA;

                Dcm_GetTypeofDID(&s_Dcm_idxRdbiDidIndexType_st);

                Dcm_DidSignalIdx_u16 = 0x0;
                break;
                case (Std_ReturnType)DCM_E_PENDING:
                        dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                break;
                case (Std_ReturnType)E_NOT_OK:

                case (Std_ReturnType)DCM_INFRASTRUCTURE_ERROR:
                default:
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;

                    Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);
                    break;
            }
        }

        if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETDATA)
        {

            s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b = Dcm_DspReadDidOpStatus_u8;

            if(s_Dcm_idxRdbiDidIndexType_st.flagPageddid_b!= TRUE)
            {
                if(Dcm_DsldPduInfo_st.SduLength != 0u)
                {
                    if(Dcm_Pending_DIDData_b == FALSE )
                    {
                        s_Dcm_FilledLengthCurrentPage_u32 = s_Dcm_FilledLengthCurrentPage_u32 + Dcm_DsldPduInfo_st.SduLength;
                        Dcm_Pending_DIDData_b = TRUE;
                    }
                    posnTarget_u32 = s_Dcm_FilledLengthCurrentPage_u32  + 2u ;
                }
                else{

                    posnTarget_u32 = s_Dcm_FilledLengthCurrentPage_u32 + 2uL;
                }

                s_dataReadIfcRetVal_u8 = Dcm_GetDIDData(&s_Dcm_idxRdbiDidIndexType_st,&adrTargetBuffer_pu8[posnTarget_u32]);
            }
            else{

                if(s_Dcm_PagedDid_b==TRUE)
                {
                    if(Dcm_Pending_DIDData_b==FALSE)
                    {
                        s_Dcm_FilledLengthCurrentPage_u32 += Dcm_DsldPduInfo_st.SduLength;
                        Dcm_Pending_DIDData_b=TRUE;
                    }
                    posnTarget_u32 = s_Dcm_FilledLengthCurrentPage_u32 + 2uL;
                }
                else{
                    posnTarget_u32 = 0x0;
                    if(Dcm_DsldPduInfo_st.SduLength != 0u )
                      {
                        if(Dcm_Pending_DIDData_b == FALSE)
                        {
                            s_Dcm_FilledLengthCurrentPage_u32 = Dcm_DsldPduInfo_st.SduLength;
                            posnTarget_u32 = Dcm_DsldPduInfo_st.SduLength;
                            Dcm_Pending_DIDData_b = TRUE;
                        }
                      }
                }

                s_dataReadIfcRetVal_u8 = Dcm_GetPagedDIDData(&s_Dcm_idxRdbiDidIndexType_st,&adrTargetBuffer_pu8[posnTarget_u32]);
            }

            switch(s_dataReadIfcRetVal_u8)
            {
                case (Std_ReturnType)E_OK:
                    {
                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_GETLENGTH;

                    s_Dcm_idxRdbiDidIndexType_st.dataNegRespCode_u8 = 0x0;

                        if(s_Dcm_idxRdbiDidIndexType_st.flagPageddid_b != TRUE)
                        {

                            posnTarget_u32=(posnTarget_u32-2u);
                            adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((s_dataDynamicID_u16)>>8u);
                            adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((s_dataDynamicID_u16));

                            s_Dcm_FilledLengthCurrentPage_u32 = s_Dcm_FilledLengthCurrentPage_u32 + Dcm_GetDataLengthOfCurrentData_u32 + 2u;
                        }
                        else
                        {

                            if(s_Dcm_PagedDid_b==TRUE)
                            {

                                posnTarget_u32=(posnTarget_u32-2u);
                                adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((s_dataDynamicID_u16)>>8u);
                                adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((s_dataDynamicID_u16));
                                s_Dcm_FilledLengthCurrentPage_u32 += 2u;

                                s_Dcm_PagedDid_b=FALSE;
                            }
                            s_Dcm_FilledLengthCurrentPage_u32 = ((s_Dcm_FilledLengthCurrentPage_u32) + (s_Dcm_idxRdbiDidIndexType_st.dataSignalLengthInfo_u32));
                        }

                        Dcm_GetDataNumOfIndex_u16++;

                        if(((s_Dcm_FilledLengthCurrentPage_u32 ) >= 7u)||(Dcm_GetDataNumOfIndex_u16==nrIndex_u16))
                        {
                            Dcm_Pending_DIDData_b = FALSE;
                            dataRetVal_u8=Dcm_Dsp_RDBITriggerProcessPage((s_Dcm_FilledLengthCurrentPage_u32 ));
                        }
                        else
                        {
                            Dcm_Pending_DIDData_b = TRUE;

                        }

                        Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;

                    Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);
                    break;
                    }
                case (Std_ReturnType)DCM_E_RDBI_DATA_PENDING:
                    {

                    s_Dcm_idxRdbiDidIndexType_st.dataNegRespCode_u8 = 0x0;

                        if(s_Dcm_PagedDid_b==TRUE)
                        {

                            posnTarget_u32=(posnTarget_u32-2u);
                            adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((s_dataDynamicID_u16)>>8u);
                            adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((s_dataDynamicID_u16));
                            s_Dcm_FilledLengthCurrentPage_u32 += 2u;

                            s_Dcm_PagedDid_b=FALSE;
                        }
                        s_Dcm_FilledLengthCurrentPage_u32 = ((s_Dcm_FilledLengthCurrentPage_u32) + (s_Dcm_idxRdbiDidIndexType_st.dataSignalLengthInfo_u32));

                        if((s_Dcm_FilledLengthCurrentPage_u32) >= 7u)
                        {
                            Dcm_Pending_DIDData_b = FALSE;
                            dataRetVal_u8=Dcm_Dsp_RDBITriggerProcessPage((s_Dcm_FilledLengthCurrentPage_u32));
                        }
                        else
                        {
                            Dcm_Pending_DIDData_b = TRUE;
                        }

                        Dcm_DspReadDidOpStatus_u8 = DCM_PENDING;

                    break;
                    }
                case (Std_ReturnType)DCM_E_PENDING:
                    {
                    Dcm_Pending_DIDData_b=TRUE;
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                    break;
                    }
                case (Std_ReturnType)DCM_E_REQUEST_ENV_NOK:
                    {
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;

                    Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);

                    break;
                    }
                case (Std_ReturnType)E_NOT_OK:
                    {
                    Dcm_Pending_DIDData_b = FALSE;
                    if(s_Dcm_idxRdbiDidIndexType_st.dataNegRespCode_u8 == 0x0)
                    {

                        dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataDynamicID_u16,posnTarget_u32,dataNegRespCode_u8);

                        if(dataNrcRetval_u8!=E_OK)
                        {

                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                        }
                    }
                    else
                    {

                        *dataNegRespCode_u8 = s_Dcm_idxRdbiDidIndexType_st.dataNegRespCode_u8;
                    }

                    }

                default:
                {

                    Dcm_Dsp_RDBICancelPagebufferHandling();
                    dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                    Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;

                    Dcm_ResetDIDIndexstruct(&s_Dcm_idxRdbiDidIndexType_st);

                    break;
                }
            }
        }
   }
   if(dataRetVal_u8 == DCM_GETDATA_RETVAL_OK)
   {
        Dcm_GetDataState_en=DCM_GETDATA_STATUS_INIT;
   }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#else

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
FUNC (Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en (P2CONST (uint8, AUTOMATIC,DCM_INTERN_CONST) adrIdBuffer_pcu8
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8
   ,     VAR (uint16,DCM_INTERN_DATA) nrIndex_u16
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR (uint32,DCM_INTERN_DATA) adrTotalLength_pu32
)
{

   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrRDBIFnc;

#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
   VAR (uint16,AUTOMATIC) dataLength_u16;
#endif

#if(DCM_CFG_DSP_READ_SR_ENABLED!=DCM_CFG_OFF)
   VAR (uint16, AUTOMATIC) nrElements_u16;
   VAR (uint16, AUTOMATIC) idxLoop_u16;
   VAR (uint32, AUTOMATIC) dataSignal_u32;
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
   VAR (uint16, AUTOMATIC) dataSignal_u16;
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
   VAR (sint16, AUTOMATIC) dataSignal_s16;
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
   VAR (sint32, AUTOMATIC) dataSignal_s32;
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
   VAR (sint8,  AUTOMATIC) dataSignal_s8;
#endif
#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
   VAR (boolean,AUTOMATIC) dataSignal_b;
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
   VAR (uint8,  AUTOMATIC) dataSignal_u8;
#endif

   VAR (Std_ReturnType,AUTOMATIC) dataNrcRetval_u8;
   VAR (Dcm_GetDataRet_ten, AUTOMATIC) dataRetVal_u8;
   static VAR(uint32 ,DCM_VAR)  Dcm_GetDataLengthOfCurrentData_u32;

#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_b   = FALSE;
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u8  = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u16 = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u32 = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s8  = 0x0;
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s16 = 0x0;
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s32 = 0x0;
#endif

    dataRetVal_u8     = DCM_GETDATA_RETVAL_OK;
    dataNrcRetval_u8 = E_OK;
    *dataNegRespCode_u8 = 0x0;

   if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_INIT)
   {

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
                    (dataRetVal_u8          == DCM_GETDATA_RETVAL_OK))
   {
        if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETLENGTH)
        {
            VAR (Std_ReturnType, AUTOMATIC) dataFuncRetVal_en;

            s_dataID_u16 = (uint16)((uint16)((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1)*2u)]<<(uint8)8) +
                    ((uint16)adrIdBuffer_pcu8[((Dcm_GetDataNumOfIndex_u16-1u)*2u)+1u]));

            dataFuncRetVal_en = Dcm_GetIndexOfDID(s_dataID_u16, &s_Dcm_idxRdbiDidIndexType_st);
            if(dataFuncRetVal_en ==  E_OK)
            {

                dataFuncRetVal_en=Dcm_GetLengthOfDIDIndex (&s_Dcm_idxRdbiDidIndexType_st,&Dcm_GetDataLengthOfCurrentData_u32,s_dataID_u16);
            }

            switch(dataFuncRetVal_en)
            {

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
        if(Dcm_GetDataState_en == DCM_GETDATA_STATUS_GETDATA)
        {

#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
            VAR (Std_ReturnType, AUTOMATIC) dataNvmGetErrorRetVal_u8;
            VAR (Std_ReturnType, AUTOMATIC) dataNvmReadBlockRetVal_u8;
            VAR (NvM_RequestResultType, AUTOMATIC) dataRequestResult_u8;
#endif
            VAR (uint32,AUTOMATIC) posnTarget_u32= (Dcm_GetDataTotalLength_u32 - Dcm_GetDataLengthOfCurrentData_u32);
#if(DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF)
            VAR (uint16, AUTOMATIC) dataSignallength_u16;
            VAR(boolean, AUTOMATIC) rtn_infrastructurefcVal;
#endif
            VAR (uint32, AUTOMATIC) dataSignallength_u32;

            ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];
#if(DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF)
            dataSignallength_u16 = 0x0;
#endif
            dataSignallength_u32 = 0x0;

            if(s_dataReadIfcVal_u8 !=DCM_E_PENDING)
            {

                DCM_MEMSET(&adrTargetBuffer_pu8[posnTarget_u32], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, Dcm_GetDataLengthOfCurrentData_u32);
            }

            if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b == FALSE)
            {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

                while(Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16)
                {
                    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
                    if(((s_dataLengthFnc_retVal_u8==E_OK)&&(s_dataReadIfcVal_u8==E_OK)) || (s_dataLengthFnc_retVal_u8==DCM_E_PENDING))
                    {

                        if(FALSE != ptrSigConfig->dataFixedLength_b)
                        {

                            s_posnTargetSig_u32 = (posnTarget_u32+(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8));

                            if((ptrSigConfig->dataType_u8==DCM_BOOLEAN) &&         \
                                    (((Dcm_DidSignalIdx_u16==(ptrDidConfig->nrSig_u16-1)))   ||                                      \
                                            (((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8) !=              \
                                                    (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16+1].posnSigBit_u16/8)))))

                            {
                                s_datalengthinfo_u32+=1u;
                            }
                            else if(ptrSigConfig->dataType_u8!=DCM_BOOLEAN)
                            {
                                s_datalengthinfo_u32  = ((ptrSigConfig->dataSize_u16/8) + (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8));
                            }
                            else
                            {

                            }
                            s_dataLengthFnc_retVal_u8 = E_OK;
                        }
                        else
                        {
#if(DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF)

                            if(FALSE==ptrDidConfig->dataDynamicDid_b)
                            {

                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                                {
                                    s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&dataSignallength_u16);
                                }
                                else
                                {
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                    || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                                    )
                                    {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                                        if( (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {
                                            if(!s_DcmReadDataLengthRteCallPlaced_b)
                                            {

                                                s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc6_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b);
                                                if(s_dataLengthFnc_retVal_u8 == E_OK)
                                                {
                                                    s_DcmReadDataLengthRteCallPlaced_b = TRUE;
                                                    s_dataLengthFnc_retVal_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {

                                                    s_dataLengthFnc_retVal_u8 = E_NOT_OK;
                                                }
                                            }
                                            else
                                            {

                                                s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFncResults_pfct))(&dataSignallength_u16);
                                                if(s_dataLengthFnc_retVal_u8 == E_OK)
                                                {
                                                    s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                                }
                                                else if(s_dataLengthFnc_retVal_u8 == RTE_E_NO_DATA)
                                                {
                                                    s_dataLengthFnc_retVal_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {
                                                    s_DcmReadDataLengthRteCallPlaced_b = FALSE;

                                                    s_dataLengthFnc_retVal_u8 = E_NOT_OK;
                                                }
                                            }
                                        }
                                        else
#endif
                                        {

                                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b,&dataSignallength_u16);
                                        }
                                    }
                                }
                                dataSignallength_u32 = (uint32)dataSignallength_u16;
                            }
                            else
                            {

                                s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc2_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&(dataSignallength_u32));
                            }

                            if(E_OK==s_dataLengthFnc_retVal_u8)
                            {
   							Dcm_DspReadDidOpStatus_u8=DCM_INITIAL;

#if(DCM_CFG_READDATALENGTH_BITS!=DCM_CFG_OFF)

                                if((ptrDidConfig->dataDynamicDid_b == FALSE) &&  \
                                        ((dataSignallength_u32 > ptrSigConfig->dataSize_u16) ||(dataSignallength_u32==0u)))
#else

                                    if(((ptrDidConfig->dataDynamicDid_b) == FALSE) &&  \
                                            (((dataSignallength_u32*8u) > (ptrSigConfig->dataSize_u16)) ||(dataSignallength_u32==0u)))
#endif
                                    {
                                        s_dataReadIfcVal_u8 = E_NOT_OK;

                                        break;
                                    }
                            }
                            else
                            {
                                rtn_infrastructurefcVal=Dcm_IsInfrastructureErrorPresent_b(s_dataLengthFnc_retVal_u8);

                                if(((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)) &&(rtn_infrastructurefcVal != FALSE))
                                   {

                                     s_dataReadIfcVal_u8 = DCM_INFRASTRUCTURE_ERROR;

                                   }
                                else if(DCM_E_PENDING==s_dataLengthFnc_retVal_u8)
                                {
                                    s_dataReadIfcVal_u8 = DCM_E_PENDING;
                                    s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b=DCM_PENDING;
                                }
                                else
                                {
                                    s_dataReadIfcVal_u8 = E_NOT_OK;
                                }

                                break;
                            }

                            if(FALSE == ptrDidConfig->dataDynamicDid_b)
                            {
#if(DCM_CFG_READDATALENGTH_BITS!=DCM_CFG_OFF)
                                Dcm_ConvBitsToBytes(&dataSignallength_u32);
#endif
                            }
                            s_posnTargetSig_u32 = (uint32)(posnTarget_u32+s_datalengthinfo_u32);
                            s_datalengthinfo_u32 = (uint32)(s_datalengthinfo_u32+dataSignallength_u32);
#endif
                        }
                    }

                    if((ptrSigConfig->adrReadFnc_cpv)!= NULL_PTR)
                    {
                        ptrRDBIFnc=ptrSigConfig->adrReadFnc_cpv;

                        if((ptrSigConfig->usePort_u8 ==USE_DATA_SYNCH_FNC) ||          \
                                (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                        {
#if(DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED != DCM_CFG_OFF)
                            if(FALSE==ptrDidConfig->dataDynamicDid_b)
                            {

                                s_dataReadIfcVal_u8 = (*(ReadFunc1_pfct)(ptrRDBIFnc))(&adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                            }
                            else
                            {

                                s_dataReadIfcVal_u8 = (*(ReadFunc10_pfct)(ptrRDBIFnc))(&adrTargetBuffer_pu8[s_posnTargetSig_u32],dataNegRespCode_u8);
                            }
#endif
                        }

#if(DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)

                        else if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
                                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                        {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                            if( (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                            {
                                if(!s_DcmReadDataRteCallPlaced_b)
                                {

                                    s_dataReadIfcVal_u8 = (*(ReadFunc11_ptr)(ptrRDBIFnc))(Dcm_DspReadDidOpStatus_u8);
                                    if(s_dataReadIfcVal_u8 == E_OK)
                                    {
                                        s_DcmReadDataRteCallPlaced_b = TRUE;
                                        s_dataReadIfcVal_u8 = DCM_E_PENDING;
                                    }
                                    else
                                    {

                                        s_dataReadIfcVal_u8 = E_NOT_OK;
                                    }
                                }
                                else
                                {

                                    s_dataReadIfcVal_u8 = (*(ReadFunc1_pfct)(ptrSigConfig->adrReadFncResults_cpv))(&adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                                    if(s_dataReadIfcVal_u8 == E_OK)
                                    {
                                        s_DcmReadDataRteCallPlaced_b = FALSE;
                                    }
                                    else if(s_dataReadIfcVal_u8 == RTE_E_NO_DATA)
                                    {
                                        s_dataReadIfcVal_u8 = DCM_E_PENDING;
                                    }
                                    else
                                    {
                                        s_DcmReadDataRteCallPlaced_b = FALSE;

                                        s_dataReadIfcVal_u8 = E_NOT_OK;
                                    }
                                 }
                             }
                             else
#endif
                             {

                                s_dataReadIfcVal_u8 = (*(ReadFunc2_ptr)(ptrRDBIFnc))(Dcm_DspReadDidOpStatus_u8, &adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                             }
                        }
#endif
                        else
                        {
#if(DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)

                            if(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)
                            {

                                switch(ptrSigConfig->dataType_u8)
                                {
#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_BOOLEAN:
                                    {

                                        s_dataReadIfcVal_u8 = (*(ReadFunc3_pfct)(ptrRDBIFnc))(&dataSignal_b);

                                        dataSignal_u32 = 0x0u;

                                        if(dataSignal_b != FALSE)
                                        {
                                            dataSignal_u32 = 0x01u;
                                        }

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16)
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT8:
                                    {
                                        nrElements_u16 = (uint16)((uint32)ptrSigConfig->dataSize_u16/8u);

                                        if(ptrSigConfig->dataSize_u16 == 8)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc1_pfct)(ptrRDBIFnc))(&dataSignal_u8);
                                            Dcm_DspArraySignal_au8[0] = dataSignal_u8;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc1_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_au8);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = (uint32)Dcm_DspArraySignal_au8[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT16:
                                    {
                                        nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);

                                        if(ptrSigConfig->dataSize_u16 == 16)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc4_pfct)(ptrRDBIFnc))(&dataSignal_u16);
                                            Dcm_DspArraySignal_au16[0] = dataSignal_u16;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc4_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_au16);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = (uint32)Dcm_DspArraySignal_au16[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint32)(idxLoop_u16*16u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_UINT32_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT32:
                                    {
                                        nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);

                                        if(ptrSigConfig->dataSize_u16 == 32)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc5_pfct)(ptrRDBIFnc))(&dataSignal_u32);
                                            Dcm_DspArraySignal_au32[0] = dataSignal_u32;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc5_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_au32);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = Dcm_DspArraySignal_au32[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT8:
                                    {
                                        nrElements_u16 = (uint16)((uint32)ptrSigConfig->dataSize_u16/8u);

                                        if(ptrSigConfig->dataSize_u16 == 8)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc6_pfct)(ptrRDBIFnc))(&dataSignal_s8);
                                            Dcm_DspArraySignal_as8[0] = dataSignal_s8;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc6_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_as8);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = (uint32)Dcm_DspArraySignal_as8[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint32)(idxLoop_u16*8u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT16:
                                    {
                                        nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);

                                        if(ptrSigConfig->dataSize_u16 == 16)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc7_pfct)(ptrRDBIFnc))(&dataSignal_s16);
                                            Dcm_DspArraySignal_as16[0] = dataSignal_s16;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc7_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_as16);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = (uint32)Dcm_DspArraySignal_as16[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT32:
                                    {
                                        nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);

                                        if(ptrSigConfig->dataSize_u16 == 32)
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc8_pfct)(ptrRDBIFnc))(&dataSignal_s32);
                                            Dcm_DspArraySignal_as32[0] = dataSignal_s32;
                                        }
                                        else
                                        {

                                            s_dataReadIfcVal_u8 = (*(ReadFunc8_pfct)(ptrRDBIFnc))(Dcm_DspArraySignal_as32);
                                        }

                                        for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataReadIfcVal_u8 == E_OK)); idxLoop_u16++)
                                        {
                                            dataSignal_u32 = (uint32)Dcm_DspArraySignal_as32[idxLoop_u16];

                                            Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32u)))
   ,     &adrTargetBuffer_pu8[posnTarget_u32], dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                        }
                                        break;
                                    }
#endif
                                    default:
                                    {
                                        break;
                                    }
                                }
                            }
#endif
                        }
                        if(s_dataReadIfcVal_u8!=E_OK)
                        {

                            break;
                        }
#if(DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED != DCM_CFG_OFF)
                        else if(FALSE != ptrDidConfig->dataDynamicDid_b)
                        {
                            *dataNegRespCode_u8=0;
                        }
#endif
                        else
                        {

                            Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                        }

                    }
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                    else if(ptrSigConfig->usePort_u8 == USE_BLOCK_ID)

                    {

                        if(Dcm_flgNvmReadPending_b== FALSE)
                        {

                            dataNvmReadBlockRetVal_u8=NvM_ReadBlock(ptrSigConfig->dataNvmBlockId_u16,&adrTargetBuffer_pu8[s_posnTargetSig_u32]);
                            if(dataNvmReadBlockRetVal_u8 != E_OK)
                            {
                                Dcm_flgNvmReadPending_b= FALSE;
                                s_dataReadIfcVal_u8 =E_NOT_OK;
                            }
                            else
                            {

                                Dcm_flgNvmReadPending_b= TRUE;
                                s_dataReadIfcVal_u8 =DCM_E_PENDING;
                            }

                            break;
                        }
                        else
                        {
                            dataNvmGetErrorRetVal_u8= NvM_GetErrorStatus(ptrSigConfig->dataNvmBlockId_u16,&dataRequestResult_u8);

                            Dcm_flgNvmReadPending_b =FALSE;
                            if(dataNvmGetErrorRetVal_u8 != E_OK)
                            {
                                s_dataReadIfcVal_u8 =E_NOT_OK;

                                break;
                            }
                            else
                            {
                                if((dataRequestResult_u8 == NVM_REQ_INTEGRITY_FAILED) || (dataRequestResult_u8 == NVM_REQ_NV_INVALIDATED) ||
                                        (dataRequestResult_u8 == NVM_REQ_CANCELED) || (dataRequestResult_u8 == NVM_REQ_REDUNDANCY_FAILED) ||
                                        (dataRequestResult_u8 == NVM_REQ_RESTORED_FROM_ROM) || (dataRequestResult_u8 == NVM_REQ_NOT_OK))
                                {
                                    s_dataReadIfcVal_u8 =DCM_E_REQUEST_ENV_NOK;
                                }
                                else if(dataRequestResult_u8 == NVM_REQ_PENDING)
                                {

                                    Dcm_flgNvmReadPending_b =TRUE;
                                    s_dataReadIfcVal_u8 = DCM_E_PENDING;
                                }
                                else if(dataRequestResult_u8==NVM_REQ_OK)
                                {
                                    s_dataReadIfcVal_u8 =E_OK;
                                }
                                else
                                {
                                    s_dataReadIfcVal_u8 =E_NOT_OK;
                                }
                                if(dataRequestResult_u8!=NVM_REQ_OK)
                                {

                                    break;
                                }
                            }
                        }
                    }
#endif
                    else
                    {

                    }
   			Dcm_DidSignalIdx_u16++;
                }

                    switch(s_dataReadIfcVal_u8)
                    {

                        case E_OK:
                        {
                            posnTarget_u32=(posnTarget_u32-2u);
                            adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)((ptrDidConfig->dataDid_u16)>>8u);
                            adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)((ptrDidConfig->dataDid_u16));

                            Dcm_GetDataTotalLength_u32 = (Dcm_GetDataTotalLength_u32 - (Dcm_GetDataLengthOfCurrentData_u32 + 2u));

                            Dcm_GetDataNumOfIndex_u16--;
                            Dcm_GetDataState_en=DCM_GETDATA_STATUS_GETLENGTH;
                            break;
                        }
                        case DCM_E_PENDING:
                    {
                        *dataNegRespCode_u8=0x00;
                        dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                        break;
                    }

                        case DCM_E_REQUEST_ENV_NOK:
                        {
                            if(E_OK == s_dataLengthFnc_retVal_u8)
                            {
                                dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,s_posnTargetSig_u32,dataNegRespCode_u8);
                            }

                            if(dataNrcRetval_u8!=E_OK)
                            {
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            }

                            dataRetVal_u8 =DCM_GETDATA_RETVAL_INVALIDCONDITIONS;

                            Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                            Dcm_DidSignalIdx_u16 = 0x0;
                            break;
                        }

                        case E_NOT_OK:
                        {

                            if(E_OK == s_dataLengthFnc_retVal_u8)
                            {
                                dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,s_posnTargetSig_u32,dataNegRespCode_u8);
                            }

                            if(dataNrcRetval_u8!=E_OK)
                            {
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            }
                        }

                        default:
                        {

                            dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                            Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                            Dcm_DidSignalIdx_u16 = 0x0;
                            break;
                        }
                    }

#endif
            }
            else{
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
                if((Dcm_DIDRangeConfig_cast[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16].adrReadFnc_pfct)!= NULL_PTR)
                {
                    *dataNegRespCode_u8=0x0;
                    s_dataReadIfcVal_u8 = (*(Dcm_DIDRangeConfig_cast[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16].adrReadFnc_pfct))
                                                                                                    (s_dataID_u16,&adrTargetBuffer_pu8[posnTarget_u32],Dcm_DspReadDidOpStatus_u8,&dataLength_u16,dataNegRespCode_u8);

                    switch(s_dataReadIfcVal_u8)
                    {
                        case E_OK:
                        {
                            posnTarget_u32=(posnTarget_u32-2u);
                            adrTargetBuffer_pu8[posnTarget_u32]   = (uint8)(s_dataID_u16>>8u);
                            adrTargetBuffer_pu8[posnTarget_u32+1u] = (uint8)(s_dataID_u16);

                            Dcm_GetDataTotalLength_u32 = (Dcm_GetDataTotalLength_u32 - (Dcm_GetDataLengthOfCurrentData_u32 + 2u));

                            Dcm_GetDataNumOfIndex_u16--;
                            Dcm_GetDataState_en=DCM_GETDATA_STATUS_GETLENGTH;
                            Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                            break;
                        }
                        case DCM_E_PENDING:
                        {

                            Dcm_flgDspDidRangePending_b = TRUE;
                            dataRetVal_u8 = DCM_GETDATA_RETVAL_PENDING;
                            break;
                        }
                        case E_NOT_OK:
                        {

                            dataNrcRetval_u8 = DcmAppl_DcmReadDataNRC(s_dataID_u16,0x0,dataNegRespCode_u8);
                            if(dataNrcRetval_u8!=E_OK)
                            {
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            }
                        }

                        default:
                        {

                            dataRetVal_u8 = DCM_GETDATA_RETVAL_INTERNALERROR;

                            Dcm_GetDataState_en = DCM_GETDATA_STATUS_INIT;
                            Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                            break;
                        }
                    }
                }
#endif
            }

#if(DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF)
            (void)dataSignallength_u16;
#endif
            (void)dataSignallength_u32;
        }
   }
   if(dataRetVal_u8 == DCM_GETDATA_RETVAL_OK)
   {
        Dcm_GetDataState_en=DCM_GETDATA_STATUS_INIT;
   }

    (void )ptrDidConfig;
    (void )ptrSigConfig;
    (void )ptrControlSigConfig;
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (Std_ReturnType,DCM_CODE) SwcServiceDcm_tReadDataByIdentifier (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Std_ReturnType,AUTOMATIC)  dataRetVal_u8;

    *dataNegRespCode_u8   = 0x0u;
    dataRetVal_u8=DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RdbiIni();

        dataRetVal_u8 = E_OK;
   }
   else{

        if(Dcm_stRdbi_en == DCM_RDBI_IDLE)
        {

            if((pMsgContext->reqDataLen < DCM_RDBI_SIZE_DID) ||
                    ((pMsgContext->reqDataLen & 0x0001u) != 0uL))
            {

                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
            }

            else{

                Dcm_RdbiReqDidNb_u16 = (uint16)(pMsgContext->reqDataLen / DCM_RDBI_SIZE_DID);

                if((DCM_CFG_MAXDIDTOREAD != 0u) &&
                        (Dcm_RdbiReqDidNb_u16 > DCM_CFG_MAXDIDTOREAD))
                {

                    *dataNegRespCode_u8  = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                }
                else{
                    Dcm_stRdbi_en = DCM_RDBI_GET_LENGTH;
                }
            }
        }
        if(Dcm_stRdbi_en == DCM_RDBI_GET_LENGTH)
        {

            VAR (Dcm_LenCalcRet_ten, AUTOMATIC) dataFuncRetVal_en;
#if((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)||(DCM_CFG_LIMITRDBIRESPTOBUFSIZE != DCM_CFG_OFF))
            Dcm_DspRdbiMaxRespLen_u32 = (pMsgContext->resMaxDataLen);
#endif

            dataFuncRetVal_en = Dcm_DspGetTotalLengthOfDIDs_en (&pMsgContext->reqData[0]
   ,     Dcm_RdbiReqDidNb_u16
   ,     &Dcm_NumOfIndices_u16
   ,     &Dcm_TotalLength_u32
   ,     dataNegRespCode_u8);
            switch(dataFuncRetVal_en)
            {
                case DCM_LENCALC_RETVAL_OK:

                    Dcm_TotalLength_u32 = (uint32)(Dcm_TotalLength_u32 + (2 * Dcm_NumOfIndices_u16));

                    pMsgContext->resDataLen = (Dcm_MsgLenType)Dcm_TotalLength_u32;

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

                    if(Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen) != FALSE)
                    {

                        s_Dcm_FilledLengthCurrentPage_u32 = 0x0;

                        Dcm_RdbiFirstPageSent_b = FALSE;

                        Dcm_stRdbi_en = DCM_RDBI_GET_DATA;

                        Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDBIUpdatePage;

                        Dcm_StartPagedProcessing(pMsgContext);
                    }
                    else
                    {

                        *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                        Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                    }
#else

                    if(Dcm_TotalLength_u32<= pMsgContext->resMaxDataLen)
                    {
                        Dcm_stRdbi_en = DCM_RDBI_GET_DATA;
                    }

                    else
                    {

                        *dataNegRespCode_u8  = DCM_E_RESPONSETOOLONG;
                        Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                    }
#endif

                    if((Dcm_RdbiReqDidNb_u16 > 1)&&(Dcm_NumOfIndices_u16!=0)&&(Dcm_stRdbi_en == DCM_RDBI_GET_DATA))
                    {
                        VAR (Std_ReturnType, AUTOMATIC) dataCheckLenRetVal_u8;

                        dataCheckLenRetVal_u8 = DcmAppl_DcmCheckRdbiResponseLength(Dcm_TotalLength_u32,Dcm_NumOfIndices_u16,dataNegRespCode_u8);
                        if((*dataNegRespCode_u8==0) && (dataCheckLenRetVal_u8 != E_OK))
                        {
                            *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                        }
                        else if((*dataNegRespCode_u8 !=0)&&(dataCheckLenRetVal_u8 != E_OK) )
                        {
                            Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                        }
                        else
                        {

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
        if(Dcm_stRdbi_en == DCM_RDBI_GET_DATA)
        {

            if(Dcm_NumOfIndices_u16==0)
            {

                *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
                Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
            }
            else{
                VAR (Dcm_GetDataRet_ten, AUTOMATIC) dataFuncRetVal_en;

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                dataFuncRetVal_en= Dcm_GetData_en(&pMsgContext->reqData[0]
   ,     Dcm_DspRdbiRespBufPtr_u8
   ,     Dcm_NumOfIndices_u16
   ,     dataNegRespCode_u8
                );
#else
        dataFuncRetVal_en= Dcm_GetData_en(&pMsgContext->reqData[0]
   ,     pMsgContext->resData
   ,     Dcm_NumOfIndices_u16
   ,     dataNegRespCode_u8
   ,     Dcm_TotalLength_u32
        );
#endif

            switch(dataFuncRetVal_en)
            {
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
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                case DCM_GETDATA_PAGED_BUFFER_TX:

                    dataRetVal_u8=DCM_E_PENDING;
                    break;
#endif
                case DCM_GETDATA_RETVAL_INTERNALERROR:
                default:

                    if(0x0 == *dataNegRespCode_u8)
                    {
                        *dataNegRespCode_u8  = DCM_E_GENERALREJECT;
                    }
                    else
                    {

                    }
                    Dcm_stRdbi_en = DCM_RDBI_NEG_RESP;
                    Dcm_DspReadDidOpStatus_u8 = DCM_INITIAL;
                    break;
                }
            }
        }

        if(Dcm_stRdbi_en == DCM_RDBI_NEG_RESP)
        {

            Dcm_DidSignalIdx_u16 = 0x0;
            dataRetVal_u8=E_NOT_OK;

            Dcm_stRdbi_en = DCM_RDBI_IDLE;
        }
   }
    return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
    ptrDidConfig =&Dcm_DIDConfig[s_Dcm_idxRdbiDidIndexType_st.idxIndex_u16];

    dataRetVal_u8 = E_NOT_OK;

   if(s_Dcm_idxRdbiDidIndexType_st.dataRange_b==FALSE)
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )

        *dataDid_u16 = ptrDidConfig->dataDid_u16;
#endif

        dataRetVal_u8 = E_OK;
   }
   else{
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

        *dataDid_u16 = s_Dcm_idxRdbiDidIndexType_st.dataRangeDid_16;

        dataRetVal_u8 = E_OK;
#endif
   }
    return (dataRetVal_u8);
}

FUNC(void, DCM_CODE) Dcm_Lok_DspRdbiConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

   		Dcm_Dsp_RdbiIni();
#endif
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
