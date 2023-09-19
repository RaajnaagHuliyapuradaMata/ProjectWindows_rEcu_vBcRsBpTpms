#include "Std_Types.hpp"

#include "DcmDspUds_Uds_Inf.hpp"

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8,DCM_VAR) Dcm_VInData_au8[DCM_VIN_DATALEN] = {0};
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_VinReceived_b = FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DIDIndexType_tst s_Dcm_idxRdbiDidIndexType_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static boolean s_VIN_DcmReadDataConditionsRteCallPlaced_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetVin (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
    Std_ReturnType dataStatusReturn_u8 = E_NOT_OK;
   uint8 indexVinBuff = 0;

   if((Dcm_VinReceived_b != FALSE) && (Data != NULL_PTR))
   {

       for(indexVinBuff = 0;indexVinBuff < DCM_VIN_DATALEN ;indexVinBuff++)
       {
          *(Data) = Dcm_VInData_au8[indexVinBuff];
   	  Data++;
       }

       if(indexVinBuff == DCM_VIN_DATALEN)
       {

           dataStatusReturn_u8 = E_OK;
       }
   }
    return dataStatusReturn_u8;
}

FUNC(Std_ReturnType ,DCM_CODE) Dcm_VinBuffer_Init(void){

    Std_ReturnType dataStatusReturn_u8;
    Dcm_DIDIndexType_tst idxVinDidIndexType_st;
    Std_ReturnType dataCondChkRetVal_u8;
   uint16 idxVinDidSignal_u16;
    Dcm_NegativeResponseCodeType dataNegRespCode_u8;
   const Dcm_DIDConfig_tst *ptrDidConfig;
   const Dcm_DataInfoConfig_tst *ptrSigConfig;
   const Dcm_SignalDIDSubStructConfig_tst *ptrControlSigConfig;
   idxVinDidSignal_u16=0;
    dataCondChkRetVal_u8 = E_OK;

    dataStatusReturn_u8 = Dcm_GetIndexOfDID(DCM_CFG_VIN_DID,&idxVinDidIndexType_st);
    ptrDidConfig = &Dcm_DIDConfig[idxVinDidIndexType_st.idxIndex_u16];

    dataNegRespCode_u8=0;
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

   if((idxVinDidIndexType_st.dataRange_b ==FALSE) && (*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR))
   {
        if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))(DCM_CFG_VIN_DID)!=E_OK)
        {
            dataStatusReturn_u8 = E_NOT_OK;
        }
   }
#endif

   if(dataStatusReturn_u8 == E_OK)
   {
        for(idxVinDidSignal_u16=0;((idxVinDidSignal_u16<ptrDidConfig->nrSig_u16)&&(dataNegRespCode_u8==0x0)&&(dataCondChkRetVal_u8==E_OK));idxVinDidSignal_u16++)
        {
            ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxVinDidSignal_u16].idxDcmDspDatainfo_u16];
            ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
            if((ptrSigConfig->adrReadFnc_cpv)!= NULL_PTR)
            {
                if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
                {
                    if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||
                            (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                    {

                        dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(&dataNegRespCode_u8);
                    }
                    else
                    {
                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC) ||
#endif
                                (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                        {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                            {
                                if(!s_VIN_DcmReadDataConditionsRteCallPlaced_b)
                                {
                                    dataCondChkRetVal_u8 = (*(CondChkReadFunc3_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b);
                                    if(dataCondChkRetVal_u8 == E_OK)
                                    {
                                        s_VIN_DcmReadDataConditionsRteCallPlaced_b = TRUE;
                                        dataCondChkRetVal_u8 = DCM_E_PENDING;
                                    }
                                }
                                else
                                {
                                    dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrControlSigConfig->adrCondChkRdFncResults_cpv))(&dataNegRespCode_u8);
                                    if(dataCondChkRetVal_u8 == RTE_E_NO_DATA)
                                    {
                                        dataCondChkRetVal_u8 = DCM_E_PENDING;
                                    }
                                    else
                                    {
                                        s_VIN_DcmReadDataConditionsRteCallPlaced_b = FALSE;
                                    }
                                }
                            }
                            else
#endif
                            {

                                dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b, &dataNegRespCode_u8);
                            }
                        }
                    }
                }
            }
        }
        if(dataCondChkRetVal_u8==DCM_E_PENDING)
        {
            dataStatusReturn_u8=DCM_E_PENDING;
            s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b=DCM_PENDING;
        }

        else if(dataCondChkRetVal_u8==E_OK)
        {
            s_Dcm_idxRdbiDidIndexType_st.dataopstatus_b=DCM_INITIAL;
            dataStatusReturn_u8=Dcm_GetDIDData(&idxVinDidIndexType_st,&Dcm_VInData_au8[0]);
        }
        else{
            dataStatusReturn_u8=E_NOT_OK;
        }
        if(dataStatusReturn_u8 == E_OK)
        {

            Dcm_VinReceived_b = TRUE;
        }
   }
    return dataStatusReturn_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
