
#include "DcmDspUds_Uds_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_VInData_au8[DCM_VIN_DATALEN] = {0};
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_VinReceived_b = FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DIDIndexType_tst s_Dcm_idxRdbiDidIndexType_GetVIN_st;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_GetvinConditionCheckRead = FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
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

Std_ReturnType Dcm_GetVin (uint8 * Data)
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

Std_ReturnType Dcm_VinBuffer_Init(void){

    Std_ReturnType dataStatusReturn_u8;
    Std_ReturnType dataCondChkRetVal_u8;

    Dcm_NegativeResponseCodeType dataNegRespCode_u8;
   const Type_CfgSwcServiceDcm_stDid *ptrDidConfig;
   const Dcm_DataInfoConfig_tst *ptrSigConfig;
   const Type_CfgSwcServiceDcm_stInfoDidWrite *ptrControlSigConfig;
   static uint16 idxVinDidSignal_u16 =0x00u;
    dataCondChkRetVal_u8 = E_OK;

    dataStatusReturn_u8 = Dcm_Lok_GetIndexOfDID(DCM_CFG_VIN_DID,&s_Dcm_idxRdbiDidIndexType_GetVIN_st);
    ptrDidConfig = &CfgSwcServiceDcm_astListDid[s_Dcm_idxRdbiDidIndexType_GetVIN_st.idxIndex_u16];

    dataNegRespCode_u8=0;
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

   if((s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataRange_b ==FALSE) && (*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR))
   {
        if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))(DCM_CFG_VIN_DID)!=E_OK)
        {
            dataStatusReturn_u8 = E_NOT_OK;
        }
   }
#endif

   if(dataStatusReturn_u8 == E_OK)
   {

        if(Dcm_GetvinConditionCheckRead == FALSE)
        {
        while(((idxVinDidSignal_u16<ptrDidConfig->nrSig_u16)&&(dataNegRespCode_u8==0x0)&&(dataCondChkRetVal_u8==E_OK)))
        {
            ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->pcstSignalDid[idxVinDidSignal_u16].idxDcmDspDatainfo_u16];
            ptrControlSigConfig = &CfgSwcServiceDcm_castListInfoDidWrite[ptrSigConfig->idxDcmDspControlInfo_u16];
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

                                    dataCondChkRetVal_u8 = (*(CondChkReadFunc3_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b);
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

                                dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b, &dataNegRespCode_u8);
                            }
                        }
                    }
                }
            }

            if(dataCondChkRetVal_u8==E_OK)
            {
                s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b=DCM_INITIAL;
            }
            if(dataCondChkRetVal_u8 != DCM_E_PENDING)
            {
                idxVinDidSignal_u16++;
            }
        }

        }
        if(dataCondChkRetVal_u8==DCM_E_PENDING)
        {
            dataStatusReturn_u8=DCM_E_PENDING;
            s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b=DCM_PENDING;
        }

        else{

            idxVinDidSignal_u16 =0x00;
            if(dataCondChkRetVal_u8==E_OK)
            {
                Dcm_GetvinConditionCheckRead=TRUE;
                dataStatusReturn_u8=Dcm_GetDIDData(&s_Dcm_idxRdbiDidIndexType_GetVIN_st,&Dcm_VInData_au8[0]);

                if(dataStatusReturn_u8==DCM_E_PENDING)
                {
                    s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b=DCM_PENDING;

                }

            }
            else{

                dataStatusReturn_u8=E_NOT_OK;
            }
        }
        if(dataStatusReturn_u8 == E_OK)
        {

            Dcm_VinReceived_b = TRUE;
            Dcm_GetvinConditionCheckRead=FALSE;
            s_Dcm_idxRdbiDidIndexType_GetVIN_st.dataopstatus_b=DCM_INITIAL;

        }
   }

    return dataStatusReturn_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
