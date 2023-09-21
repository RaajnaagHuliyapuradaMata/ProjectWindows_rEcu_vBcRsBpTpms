#include "Std_Types.hpp"

#include "DcmDspUds_Uds_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR (uint32, DCM_VAR) s_datasignallength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspDataOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR (uint16       ,DCM_VAR)         Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)	|| \
(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

static VAR (Std_ReturnType, DCM_VAR) s_dataRetVal_u8;
#endif
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
static VAR (Std_ReturnType, DCM_VAR) s_dataLengthFnc_retVal_u8;
#endif
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
VAR (boolean,DCM_VAR) Dcm_PeriodicSchedulerRunning_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
VAR (boolean   ,DCM_VAR) Dcm_flgDspDidRangePending_b;
#endif

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
   static VAR (boolean ,DCM_VAR) s_DcmReadDataLengthRteCallPlaced_b;
   static VAR (boolean ,DCM_VAR) s_DcmReadDataConditionsRteCallPlaced_b;
   static VAR (boolean ,DCM_VAR) s_DcmReadDataRteCallPlaced_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)

FUNC (void,DCM_CODE) Dcm_ResetAsynchFlags(void){

     s_DcmReadDataLengthRteCallPlaced_b = FALSE;
     s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
     s_DcmReadDataRteCallPlaced_b = FALSE;
}
#endif

FUNC(void,DCM_CODE) Dcm_ConvBitsToBytes(P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)DataLenInBits)
{
   VAR(uint32,AUTOMATIC) dataLen_u32;

    dataLen_u32 = (uint32)(*DataLenInBits/8u);
   if((*DataLenInBits%8u) != 0u)
   {
        *DataLenInBits = (uint16)(dataLen_u32+1u);
   }
   else{
        *DataLenInBits = dataLen_u32;
   }
}

FUNC(void,DCM_CODE) Dcm_ResetDIDIndexstruct (P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st)
{
   idxDidIndexType_st->dataNegRespCode_u8=0x0;

   idxDidIndexType_st->dataRange_b = FALSE;
   idxDidIndexType_st->idxIndex_u16 = 0x0;
   idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
   idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

   idxDidIndexType_st->flagPageddid_b = FALSE;
#endif
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
   idxDidIndexType_st->dataRangeDid_16= 0x00u;
#endif

   idxDidIndexType_st->flgNvmReadPending_b = FALSE;
}

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetLengthOfDIDIndex (P2VAR   (Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA)idxDidIndexType_st
   ,     P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)    length_u32
   ,     VAR   (uint16,AUTOMATIC) did_u16)
{
   VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;
   VAR (uint32, AUTOMATIC) dataSigLength_u32;
   VAR (uint16, AUTOMATIC) dataSigLength_u16;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;

#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
   VAR (uint16, AUTOMATIC) idxSig_u16;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
#endif

#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
   P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrDIDRangeConfig;
#endif

    dataRetVal_u8 = E_NOT_OK;

    dataSigLength_u32 = 0x0u;
    dataSigLength_u16 = 0x0u;
   if(length_u32!= NULL_PTR)
   {
        *length_u32 = 0x0u;

        if(idxDidIndexType_st->dataRange_b == FALSE)
        {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

            (void)did_u16;
            (void)dataSigLength_u32;
            (void)dataSigLength_u16;
            ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];

            if(ptrDidConfig->dataFixedLength_b != FALSE)
            {
                *length_u32 = ptrDidConfig->dataMaxDidLen_u16;
                dataRetVal_u8 = E_OK;
            }
            else{

#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))

                for(idxSig_u16=0;idxSig_u16<ptrDidConfig->nrSig_u16;idxSig_u16++)
                {
                    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

                    if(((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)           ||
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)          ||
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)      ||
#endif
                        (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)     ||
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)) &&
                        (ptrControlSigConfig->adrReadDataLengthFnc_pfct != NULL_PTR))

                    {
                        ptrDIDFnc=ptrControlSigConfig->adrReadDataLengthFnc_pfct;

                        if(FALSE==Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16].dataDynamicDid_b)
                        {

                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                                    )
                            {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)

                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                {
                                    if(!s_DcmReadDataLengthRteCallPlaced_b)
                                    {

                                        dataRetVal_u8 = (*(ReadDataLengthFnc6_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(idxDidIndexType_st->dataopstatus_b);
                                        if(dataRetVal_u8 == E_OK)
                                        {

                                            s_DcmReadDataLengthRteCallPlaced_b = TRUE;
                                            dataRetVal_u8 = DCM_E_PENDING;
                                        }
                                    }
                                    else
                                    {

                                        dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFncResults_pfct))(&dataSigLength_u16);
                                        if(dataRetVal_u8 == E_OK)
                                        {
                                            s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                        }
                                        else if(dataRetVal_u8 == RTE_E_NO_DATA)
                                        {

                                            dataRetVal_u8 = DCM_E_PENDING;
                                        }
                                        else
                                        {

                                            s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                        }
                                    }
                                }
                                else
#endif
                                {

                                    dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &dataSigLength_u16);
                                }
                            }
                            else
   						{
   							if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                            	{

                            		dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrDIDFnc))(&dataSigLength_u16);
                            	}
   						}
                            dataSigLength_u32 = (uint32)dataSigLength_u16;
                        }
                        else
                        {

                            dataRetVal_u8 = (*(ReadDataLengthFnc2_pf)(ptrDIDFnc))(&dataSigLength_u32);
                        }

                        if(dataRetVal_u8==E_OK)
                        {
                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                                    )
                            {
                                idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                            }

                            if((((dataSigLength_u32*8u) > ptrSigConfig->dataSize_u16) ||(dataSigLength_u32==0u)) &&    \
                                    (ptrDidConfig->dataDynamicDid_b == FALSE))

                            {
                                dataRetVal_u8 = E_NOT_OK;
                                break;
                            }
                            else
                            {

                                if(FALSE==ptrDidConfig->dataDynamicDid_b)
                                {

                                    *length_u32+=dataSigLength_u32;

                                }
                                else
                                {
                                    *length_u32+=dataSigLength_u32;
                                }
                            }
                        }
                        else if((dataRetVal_u8==DCM_E_PENDING) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                        ))
                        {
                            idxDidIndexType_st->dataopstatus_b = DCM_PENDING;

                            break;
                        }
                        else
                        {
                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                                    )
                            {
                                idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                            }
                            if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                            {
                                if(Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE)
                                {
                                    dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
                                }
                            }

                            break;
                        }
                    }
                    else
                    {
                        if((ptrSigConfig->dataType_u8!=DCM_BOOLEAN))
                        {
                            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].idxDcmDspDatainfo_u16];

                            if(ptrSigConfig->dataFixedLength_b == FALSE)
                            {
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                                dataSigLength_u32 = (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8)+(ptrSigConfig->dataSize_u16/8);
                            }
                            else
                            {
                                dataSigLength_u32 =0x00;
                            }
                        }
                        else
                        {

                            if((idxSig_u16==(ptrDidConfig->nrSig_u16-1))||                                          \
                                ((ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8) !=            \
                                 (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].posnSigBit_u16/8)))
                            {
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].idxDcmDspDatainfo_u16];

                                if(ptrSigConfig->dataFixedLength_b == FALSE)
                                {
                                    dataSigLength_u32 = (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8)+1;
                                }
                                else
                                {
                                    dataSigLength_u32 =0x00;
                                }
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                            }
                        }
                        *length_u32 += dataSigLength_u32;
                        dataRetVal_u8 = E_OK;
                    }
                }
#endif
            }
#endif
        }
        else{
#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
            ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxDidIndexType_st->idxIndex_u16];

            if(ptrDIDRangeConfig->adrReadDataLengthFnc_pfct != NULL_PTR)
            {

                dataRetVal_u8 = (*(ReaddatalengthFnc3_pf)(ptrDIDRangeConfig->adrReadDataLengthFnc_pfct))(did_u16,idxDidIndexType_st->dataopstatus_b,&dataSigLength_u16);
                if((dataSigLength_u16 > ptrDIDRangeConfig->dataMaxDidLen_u16)||(dataRetVal_u8==E_NOT_OK))
                {
                    dataRetVal_u8 = E_NOT_OK;
                    idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                }
                else if(dataRetVal_u8 == DCM_E_PENDING)
                {
                    idxDidIndexType_st->dataopstatus_b = DCM_PENDING;
                }
                else{
                    *length_u32 = (uint32)dataSigLength_u16;
                    idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                }
            }
#endif
        }
   }
   else{

   }
    return dataRetVal_u8;
}
#endif
#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF )
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetDIDRangeStatus (
                                        VAR (uint16,AUTOMATIC) did
   ,     P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
                                      )
{
   P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrDIDRangeConfig;
   VAR (Std_ReturnType, AUTOMATIC) dataDIDExists_u8;
   VAR (uint16,AUTOMATIC) idxRange_u16;
   VAR (Dcm_DidSupportedType, AUTOMATIC) isDIDAvailable_u8;
   VAR (boolean, AUTOMATIC) isInfrastructureErrorPresent_b = FALSE;

   isDIDAvailable_u8 = DCM_DID_NOT_SUPPORTED;

    dataDIDExists_u8 = E_NOT_OK;
   if(idxDidIndexType_st != NULL_PTR)
   {

        idxDidIndexType_st->dataRange_b = FALSE;

        for(idxRange_u16=0;idxRange_u16<DCM_CFG_NUMOFDIDRANGES;idxRange_u16++)
        {
            ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxRange_u16];
            if((did >= ptrDIDRangeConfig->nrDidRangeLowerLimit_u16) && ( did <= ptrDIDRangeConfig->nrDidRangeUpperLimit_u16))
            {
                isDIDAvailable_u8 = DCM_DID_SUPPORTED;
                dataDIDExists_u8 = E_OK;

                if(FALSE != ptrDIDRangeConfig->dataRangeHasGaps_b )
                {
                    dataDIDExists_u8 = (*(ptrDIDRangeConfig->adrDIDAvailableFnc_pfct))(did,idxDidIndexType_st->dataopstatus_b,&isDIDAvailable_u8);

                    isInfrastructureErrorPresent_b = Dcm_IsInfrastructureErrorPresent_b(dataDIDExists_u8);
                    if((ptrDIDRangeConfig->nrRangeUsePort_b != FALSE) &&  (isInfrastructureErrorPresent_b != FALSE))
                    {
                        dataDIDExists_u8 = DCM_INFRASTRUCTURE_ERROR;
                    }
                }
                break;
            }
        }

        if((isDIDAvailable_u8 != DCM_DID_NOT_SUPPORTED) && (dataDIDExists_u8==E_OK))
        {

            idxDidIndexType_st->dataRange_b = TRUE;
            idxDidIndexType_st->idxIndex_u16 = idxRange_u16;
            idxDidIndexType_st->dataRangeDid_16 = did;
        }
   }
   else{

   }
    return(dataDIDExists_u8);
}
#endif
#endif

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfDID (
                                                VAR (uint16,AUTOMATIC) did
   ,     P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
                                                  )
{
   VAR (uint32,     AUTOMATIC) posnDid_u32;
   VAR (uint32,     AUTOMATIC) posnStart_u32;
   VAR (uint32,     AUTOMATIC) posnEnd_u32;
   VAR (uint32,     AUTOMATIC) dataSize_u32;
   VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;

#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

        dataRetVal_u8 = Dcm_GetDIDRangeStatus(did, idxDidIndexType_st);
        if(dataRetVal_u8==E_OK)
        {

        }

        else if(dataRetVal_u8==DCM_E_PENDING)
        {

        }
        else
#endif
        {
            dataSize_u32 = Dcm_DIDcalculateTableSize_u16();
            posnStart_u32 = 0;
            posnEnd_u32 = dataSize_u32 -1u;
            posnDid_u32 = posnEnd_u32/2u;
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

            if(Dcm_DIDConfig[posnStart_u32].dataDid_u16 == did)
            {
                idxDidIndexType_st->idxIndex_u16 = (uint16)posnStart_u32;

                idxDidIndexType_st->dataRange_b = FALSE;
                idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8=E_OK;
            }

            else if(Dcm_DIDConfig[posnEnd_u32].dataDid_u16 == did)
            {
                idxDidIndexType_st->idxIndex_u16=(uint16)posnEnd_u32;

                idxDidIndexType_st->dataRange_b = FALSE;
                idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8=E_OK;
            }
            else{
                while(posnDid_u32 > 0u)
                {
                    posnDid_u32 += posnStart_u32;
                    if(Dcm_DIDConfig[posnDid_u32].dataDid_u16 == did)
                    {
                        idxDidIndexType_st->idxIndex_u16=(uint16)posnDid_u32;

                        idxDidIndexType_st->dataRange_b = FALSE;
                        idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                        idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                        dataRetVal_u8=E_OK;
                        break;
                    }
                    else if(Dcm_DIDConfig[posnDid_u32].dataDid_u16 > did)
                    {
                        posnEnd_u32 = posnDid_u32;
                    }
                    else
                    {
                        posnStart_u32 = posnDid_u32;
                    }
                    posnDid_u32 = (posnEnd_u32-posnStart_u32)/2u ;
                }
            }
#endif
        }

    return (dataRetVal_u8);
}

#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

FUNC (Dcm_SupportRet_t,DCM_CODE) Dcm_GetSupportOfIndex( P2VAR   (Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA)   idxDidIndexType_st
   ,     VAR (Dcm_Direction_t,AUTOMATIC) direction
   ,     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR (uint32,AUTOMATIC) dataSessionMask_u32;
   VAR (uint32,AUTOMATIC) dataSecurityMask_u32;
   VAR (uint16, AUTOMATIC) dataDid_u16;
   P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst;
   VAR (Dcm_SupportRet_t, AUTOMATIC) dataRetVal_u8;
   VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
   VAR (Std_ReturnType,   AUTOMATIC) dataModeChkRetval_u8;
#endif
   VAR (boolean,   AUTOMATIC) flgModeRetVal_b;
   VAR (Dcm_NegativeResponseCodeType,   AUTOMATIC) dataNrc_u8;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;

    dataRetVal_u8 = DCM_SUPPORT_OK;
    ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
    ptrDIDFnc=NULL_PTR;

#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

   if(idxDidIndexType_st->dataRange_b == FALSE)
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        adrExtendedConfig_pcst = ptrDidConfig->adrExtendedConfig_pcst;
        dataDid_u16 = ptrDidConfig->dataDid_u16;
#endif
   }
   else{
        adrExtendedConfig_pcst = Dcm_DIDRangeConfig_cast[idxDidIndexType_st->idxIndex_u16].adrExtendedConfig_pcst;
        dataDid_u16 = idxDidIndexType_st->dataRangeDid_16;
   }
#else
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        adrExtendedConfig_pcst = ptrDidConfig->adrExtendedConfig_pcst;
        dataDid_u16 = ptrDidConfig->dataDid_u16;
#endif
#endif
    *dataNegRespCode_u8     = 0x00;
    dataNrc_u8 = 0x0;

   if(direction == DCM_SUPPORT_READ)
   {
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;
#endif
   }
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

   else{
        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessWrite_u32;
        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecWrite_u32;
   }
#endif

   if(((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL)
#if((DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
         &&
         ((ptrDidConfig->dataConfigMask_u8 & Dcm_ActiveConfiguration_u8) != 0)
#endif
        )
   {

        if((Dcm_DsldGetActiveSecurityMask_u32 () & dataSecurityMask_u32) != 0x0uL)
        {
            dataCondChkRetVal_u8 = E_OK;
            flgModeRetVal_b=TRUE;

            if(direction == DCM_SUPPORT_READ)
            {
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
                if(adrExtendedConfig_pcst->adrUserReadModeRule_pfct!=NULL_PTR)
                {
                    dataModeChkRetval_u8 = (*adrExtendedConfig_pcst->adrUserReadModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
                }
                else{
                    dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
                }
                if(dataModeChkRetval_u8!=E_OK)
                {
                    if(dataNrc_u8==0x00)
                    {
                        dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }

                    flgModeRetVal_b = FALSE;
                }
                else{
                    dataNrc_u8 =0x00;
                }

#if(DCM_CFG_DSP_MODERULEFORDIDREAD != DCM_CFG_OFF)
                if((dataNrc_u8==0x00)&& (NULL_PTR != adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))
                {
                    flgModeRetVal_b = (*(adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                }
#endif

                if(FALSE != flgModeRetVal_b)
#endif
                {

                    if(FALSE == idxDidIndexType_st->dataRange_b)
                    {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                        while((Dcm_DidSignalIdx_u16<ptrDidConfig->nrSig_u16)&&(dataCondChkRetVal_u8==E_OK))
                        {
                            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                            ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

                            if(ptrSigConfig->usePort_u8 != USE_BLOCK_ID)
                            {
                                if((ptrSigConfig->adrReadFnc_cpv)!= NULL_PTR)
                                {
                                    if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
                                    {
                                        ptrDIDFnc=ptrControlSigConfig->adrCondChkRdFnc_cpv;

                                        if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||             \
                                            (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                                        {
                                            if(ptrDidConfig->dataDynamicDid_b != FALSE)
                                            {
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
                                                Dcm_DspDataOpstatus_u8  = idxDidIndexType_st->dataopstatus_b;
#endif
                                            }

                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrDIDFnc))(dataNegRespCode_u8);
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
                                        if(!s_DcmReadDataConditionsRteCallPlaced_b)
                                        {

                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc3_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(idxDidIndexType_st->dataopstatus_b);
                                            if(dataCondChkRetVal_u8 == E_OK)
                                            {
                                                s_DcmReadDataConditionsRteCallPlaced_b = TRUE;

                                                dataCondChkRetVal_u8 = DCM_E_PENDING;
                                            }
                                        }
                                        else
                                        {

                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrControlSigConfig->adrCondChkRdFncResults_cpv))(dataNegRespCode_u8);
                                            if(dataCondChkRetVal_u8 == E_OK)
                                            {
                                                s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataCondChkRetVal_u8 == RTE_E_NO_DATA)
                                            {

                                                dataCondChkRetVal_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                                s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
                                            }
                                        }
                                    }
                                    else
#endif
                                        {

                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, dataNegRespCode_u8);
                                        }
                                     }
                                   }

                                        if((Dcm_IsInfrastructureErrorPresent_b(dataCondChkRetVal_u8) != FALSE)&&((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)))
                                        {

                                            *dataNegRespCode_u8 =0;
                                        }

                                        if(dataCondChkRetVal_u8!=E_OK)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            *dataNegRespCode_u8=0x00;
                                        }
                                    }
                                }
                                else
                                {
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

                                    DCM_DET_ERROR(DCM_RDBI_ID, DCM_E_PARAM_POINTER)
                                }
                            }
   					Dcm_DidSignalIdx_u16++;
                        }
#endif
                    }
                }
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
                else{
                    *dataNegRespCode_u8 = dataNrc_u8;
                }
#endif
            }
#if( DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
            else if(direction == DCM_SUPPORT_WRITE)
            {
                if(adrExtendedConfig_pcst->adrUserWriteModeRule_pfct!=NULL_PTR)
                {

                    dataModeChkRetval_u8 = (*adrExtendedConfig_pcst->adrUserWriteModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
                }
                else{

                    dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
                }

                if(dataModeChkRetval_u8!=E_OK)
                {
                    if(dataNrc_u8==0x00)
                    {
                        dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }

                    flgModeRetVal_b = FALSE;
                }
                else{
                    dataNrc_u8=0x00;
                }

#if(DCM_CFG_DSP_MODERULEFORDIDWRITE !=DCM_CFG_OFF)
                if((dataNrc_u8==0x00)&&(NULL_PTR != adrExtendedConfig_pcst->adrWdbiModeRuleChkFnc_pfct))
                {
                    flgModeRetVal_b = (*(adrExtendedConfig_pcst->adrWdbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                }
#endif

                if(FALSE == flgModeRetVal_b)
                {
                    *dataNegRespCode_u8 = dataNrc_u8;
                }

            }
            else{

            }
#endif

                if((dataCondChkRetVal_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00))
                {

                    Dcm_DidSignalIdx_u16 = 0x0;
                    idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                }
                else if(dataCondChkRetVal_u8 == DCM_E_PENDING)
                {
                    *dataNegRespCode_u8=0x00;
                    dataRetVal_u8 = DCM_SUPPORT_CONDITION_PENDING;
                    idxDidIndexType_st->dataopstatus_b = DCM_PENDING;
                }
                else{
                    if(*dataNegRespCode_u8==0x00)
                    {
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

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetDIDData (P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
   ,     P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) targetBuffer)
{
#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
   VAR (uint16, AUTOMATIC) datasignallength_u16;
#endif
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
VAR(uint16,DCM_VAR) idxRange_u16;
#endif

   VAR (uint32, AUTOMATIC) posnTargetSig_u32;

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

   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
#endif
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
   P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrDIDRangeConfig;
#endif

#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
   VAR (Std_ReturnType, AUTOMATIC) dataNvmGetErrorRetVal_u8;
   VAR (Std_ReturnType, AUTOMATIC) dataNvmReadBlockRetVal_u8;
   VAR (NvM_RequestResultType, AUTOMATIC) dataRequestResult_u8;
#endif

#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
    datasignallength_u16 = 0x0u;
#endif

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

    ptrDidConfig =&Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    ptrDIDFnc=NULL_PTR;
#if(DCM_CFG_DSP_READ_SR_ENABLED!=DCM_CFG_OFF)
    nrElements_u16=0x0u;
   idxLoop_u16=0x0u;
#endif

   if(targetBuffer!= NULL_PTR)
   {

        if(idxDidIndexType_st->dataRange_b == FALSE)
        {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

            if(s_dataRetVal_u8 != DCM_E_PENDING)
            {

                DCM_MEMSET(targetBuffer, (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, ptrDidConfig->dataMaxDidLen_u16);
            }

            for(;((idxDidIndexType_st->nrNumofSignalsRead_u16) < (ptrDidConfig->nrSig_u16));idxDidIndexType_st->nrNumofSignalsRead_u16++)
            {
                ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].idxDcmDspDatainfo_u16];
                posnTargetSig_u32 = (idxDidIndexType_st->dataSignalLengthInfo_u32);

                if(((s_dataLengthFnc_retVal_u8==E_OK)&&(s_dataRetVal_u8==E_OK))||(s_dataLengthFnc_retVal_u8==DCM_E_PENDING))
                {

                    if(FALSE != ptrSigConfig->dataFixedLength_b)
                    {

                        posnTargetSig_u32 =(uint32)(ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16/8);
                        s_datasignallength_u32 = (uint32)((ptrSigConfig->dataSize_u16/8) + posnTargetSig_u32);
                        s_dataLengthFnc_retVal_u8 = E_OK;
                    }
                    else
                    {
#if((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
                        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

                        if(FALSE==ptrDidConfig->dataDynamicDid_b)
                        {

                            if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                            {
                                s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&datasignallength_u16);
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

                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        if(!s_DcmReadDataLengthRteCallPlaced_b)
                                        {

                                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc6_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(idxDidIndexType_st->dataopstatus_b);
                                            if(s_dataLengthFnc_retVal_u8 == E_OK)
                                            {

                                                s_DcmReadDataLengthRteCallPlaced_b = TRUE;
                                                s_dataLengthFnc_retVal_u8 = DCM_E_PENDING;
   										}
                                        }
                                        else
                                        {

                                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFncResults_pfct))(&datasignallength_u16);
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
                                            }
                                        }
                                    }
                                    else
#endif
                                    {

                                        s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(idxDidIndexType_st->dataopstatus_b,&datasignallength_u16);
                                    }
                                }
                            }
                            s_datasignallength_u32 = (uint32)datasignallength_u16;
                        }
                        else
                        {

                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc2_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&(s_datasignallength_u32));
                        }

                        if(E_OK==s_dataLengthFnc_retVal_u8)
                        {

                            if(   (ptrDidConfig->dataDynamicDid_b == FALSE)
                                &&(   ((s_datasignallength_u32*8u) > (ptrSigConfig->dataSize_u16))
                                    ||(s_datasignallength_u32==0u)
                                  )
                              )
                            {
                                s_dataLengthFnc_retVal_u8 = E_NOT_OK;

                                break;
                            }
                            idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                        }
                        else
                        {

                            if(    (Dcm_IsInfrastructureErrorPresent_b(s_dataLengthFnc_retVal_u8) != FALSE)
                                && (   (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                                     ||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                                   )
                              )
                            {
                                s_dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
                            }
                            else if(DCM_E_PENDING==s_dataLengthFnc_retVal_u8)
                            {
                                s_dataRetVal_u8 = DCM_E_PENDING;
                                idxDidIndexType_st->dataopstatus_b = DCM_PENDING;
                            }
                            else
                            {
                                s_dataRetVal_u8 = E_NOT_OK;
                            }

                            break;
                        }

#endif
                        s_datasignallength_u32 = (uint32)(s_datasignallength_u32 + idxDidIndexType_st->dataSignalLengthInfo_u32);
                    }
                }

                if(ptrSigConfig->adrReadFnc_cpv != NULL_PTR)
                {
                    ptrDIDFnc=ptrSigConfig->adrReadFnc_cpv;

                    if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||
                    (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                    {
#if((DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED!=DCM_CFG_OFF))

                        if(FALSE == ptrDidConfig->dataDynamicDid_b)
                        {

                            s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(&targetBuffer[posnTargetSig_u32]);
                        }
                        else
                        {

                            s_dataRetVal_u8 = (*(ReadFunc10_pfct)(ptrDIDFnc))(&targetBuffer[posnTargetSig_u32],&(idxDidIndexType_st->dataNegRespCode_u8));
                            if(idxDidIndexType_st->dataNegRespCode_u8!=0)
                            {
                                s_dataRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif
                    }

#if((DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED!= DCM_CFG_OFF))

                    else if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)||
                    (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                    {
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                        {
                            if(!s_DcmReadDataRteCallPlaced_b)
                            {

                                s_dataRetVal_u8 = (*(ReadFunc11_ptr)(ptrSigConfig->adrReadFnc_cpv))(idxDidIndexType_st->dataopstatus_b);
                                if(s_dataRetVal_u8 == E_OK)
                                {
                                    s_DcmReadDataRteCallPlaced_b = TRUE;
                                    s_dataRetVal_u8 = DCM_E_PENDING;
                                }
                            }
                            else
                            {

                                s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrSigConfig->adrReadFncResults_cpv))(&targetBuffer[posnTargetSig_u32]);
                                if(s_dataRetVal_u8 == E_OK)
                                {
                                    s_DcmReadDataRteCallPlaced_b = FALSE;
                                }
                                else if(s_dataRetVal_u8 == RTE_E_NO_DATA)
                                {

                                    s_dataRetVal_u8 = DCM_E_PENDING;
                                }
                                else
                                {
                                    s_DcmReadDataRteCallPlaced_b=FALSE;
                                }
                            }
                        }
                        else
#endif
                        {

                            s_dataRetVal_u8 = (*(ReadFunc2_ptr)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &targetBuffer[posnTargetSig_u32]);
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

                                    s_dataRetVal_u8 = (*(ReadFunc3_pfct)(ptrDIDFnc))(&dataSignal_b);

                                    dataSignal_u32 = 0x0;

                                    (void)nrElements_u16;
                                    (void)idxLoop_u16;

                                    if(dataSignal_b != (boolean)0x00u)
                                    {
                                        dataSignal_u32 = 0x01;
                                    }

                                    Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16
   ,     targetBuffer, dataSignal_u32
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

                                        s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(&dataSignal_u8);
                                        Dcm_DspArraySignal_au8[0] = dataSignal_u8;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au8);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_au8[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8)))
   ,     targetBuffer, dataSignal_u32
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

                                        s_dataRetVal_u8 = (*(ReadFunc4_pfct)(ptrDIDFnc))(&dataSignal_u16);
                                        Dcm_DspArraySignal_au16[0] = dataSignal_u16;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc4_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au16);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_au16[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16)))
   ,     targetBuffer, dataSignal_u32
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

                                        s_dataRetVal_u8 = (*(ReadFunc5_pfct)(ptrDIDFnc))(&dataSignal_u32);
                                        Dcm_DspArraySignal_au32[0] = dataSignal_u32;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc5_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au32);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = Dcm_DspArraySignal_au32[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)))
   ,     targetBuffer, dataSignal_u32
   ,     ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_SINT8:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/8u);
                                    if(ptrSigConfig->dataSize_u16 == 8)
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc6_pfct)(ptrDIDFnc))(&dataSignal_s8);
                                        Dcm_DspArraySignal_as8[0] = dataSignal_s8;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc6_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as8);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as8[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8)))
   ,     targetBuffer, dataSignal_u32
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

                                        s_dataRetVal_u8 = (*(ReadFunc7_pfct)(ptrDIDFnc))(&dataSignal_s16);
                                        Dcm_DspArraySignal_as16[0] = dataSignal_s16;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc7_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as16);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as16[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16)))
   ,     targetBuffer, dataSignal_u32
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

                                        s_dataRetVal_u8 = (*(ReadFunc8_pfct)(ptrDIDFnc))(&dataSignal_s32);
                                        Dcm_DspArraySignal_as32[0] = dataSignal_s32;
                                    }
                                    else
                                    {

                                        s_dataRetVal_u8 = (*(ReadFunc8_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as32);
                                    }

                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as32[idxLoop_u16];

                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8
   ,     (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)))
   ,     targetBuffer, dataSignal_u32
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

                    if(     (Dcm_IsInfrastructureErrorPresent_b(s_dataRetVal_u8) != FALSE)
                         && (   (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                              ||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                              ||(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)
                            )
                      )
                    {
                        s_dataRetVal_u8 =E_NOT_OK;
                    }
                    if(s_dataRetVal_u8 != E_OK)
                    {

                        break;
                    }
                    else
                    {
                        if(     (ptrSigConfig->dataType_u8==DCM_BOOLEAN)
                             && (    ( (idxDidIndexType_st->nrNumofSignalsRead_u16) == (ptrDidConfig->nrSig_u16-1u) )
                                   ||
                                     (    (ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16/8u)
                                       != (ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16+1].posnSigBit_u16/8u)
                                     )
                                )
                          )
                        {
                            idxDidIndexType_st->dataSignalLengthInfo_u32+=1u;
                        }
                        else
                        {
                            idxDidIndexType_st->dataSignalLengthInfo_u32 = s_datasignallength_u32;
                        }
                    }
                }
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                else if(ptrSigConfig->usePort_u8 == USE_BLOCK_ID)
                {

                    if(idxDidIndexType_st->flgNvmReadPending_b== FALSE)
                    {

                        dataNvmReadBlockRetVal_u8=NvM_ReadBlock(Dcm_DspDataInfo_st[Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16].adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].idxDcmDspDatainfo_u16].dataNvmBlockId_u16,&targetBuffer[posnTargetSig_u32]);
                        if(dataNvmReadBlockRetVal_u8 != E_OK)
                        {

                            idxDidIndexType_st->flgNvmReadPending_b = FALSE;
                            s_dataRetVal_u8 =E_NOT_OK;
                        }
                        else
                        {

                            idxDidIndexType_st->flgNvmReadPending_b = TRUE;
                            s_dataRetVal_u8 =DCM_E_PENDING;
                        }
                    }
                    else
                    {
                        dataNvmGetErrorRetVal_u8= NvM_GetErrorStatus(ptrSigConfig->dataNvmBlockId_u16,&dataRequestResult_u8);

                        idxDidIndexType_st->flgNvmReadPending_b =FALSE;
                        if(dataNvmGetErrorRetVal_u8 != E_OK)
                        {
                            s_dataRetVal_u8 =E_NOT_OK;
                        }
                        else
                        {
                            if((dataRequestResult_u8 == NVM_REQ_INTEGRITY_FAILED) || (dataRequestResult_u8 == NVM_REQ_NV_INVALIDATED) ||
                            (dataRequestResult_u8 == NVM_REQ_CANCELED) || (dataRequestResult_u8 == NVM_REQ_REDUNDANCY_FAILED) ||
                            (dataRequestResult_u8 == NVM_REQ_RESTORED_FROM_ROM) || (dataRequestResult_u8 == NVM_REQ_NOT_OK))
                            {
                                s_dataRetVal_u8 =DCM_E_REQUEST_ENV_NOK;
                            }
                            else if(dataRequestResult_u8 == NVM_REQ_PENDING)
                            {

                                idxDidIndexType_st->flgNvmReadPending_b = TRUE;
                                s_dataRetVal_u8 = DCM_E_PENDING;
                            }
                            else if(dataRequestResult_u8==NVM_REQ_OK)
                            {
                                s_dataRetVal_u8 =E_OK;
                            }
                            else
                            {
                                s_dataRetVal_u8 =E_NOT_OK;
                            }
                        }
                    }
                }
                else{

                }
                if(s_dataRetVal_u8 != E_OK)
                {

                    break;
                }
#endif
                else{

                }

            }
#endif
        }
        else{
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
            VAR(uint16,AUTOMATIC) dataSignallength_u16;

            for(idxRange_u16=0;idxRange_u16<DCM_CFG_NUMOFDIDRANGES;idxRange_u16++)
            {
                ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxRange_u16];
                if(    ((idxDidIndexType_st->dataRangeDid_16) >= (ptrDIDRangeConfig->nrDidRangeLowerLimit_u16))
                    && ((idxDidIndexType_st->dataRangeDid_16) <= (ptrDIDRangeConfig->nrDidRangeUpperLimit_u16))
                  )
                {
                    break;
                }
            }

            if(idxRange_u16 < DCM_CFG_NUMOFDIDRANGES)
            {
                if((ptrDIDRangeConfig->adrReadFnc_pfct)!= NULL_PTR)
                {

                    dataSignallength_u16 = (uint16)(idxDidIndexType_st->dataSignalLengthInfo_u32);

                    s_dataRetVal_u8 = (*(ptrDIDRangeConfig->adrReadFnc_pfct))
                    (idxDidIndexType_st->dataRangeDid_16,targetBuffer,idxDidIndexType_st->dataopstatus_b,&(dataSignallength_u16),&(idxDidIndexType_st->dataNegRespCode_u8));

                    if((Dcm_IsInfrastructureErrorPresent_b(s_dataRetVal_u8) != FALSE) && (ptrDIDRangeConfig->nrRangeUsePort_b != FALSE) && (&(idxDidIndexType_st->dataNegRespCode_u8) != NULL_PTR))
                    {
                        idxDidIndexType_st->dataNegRespCode_u8 = 0x00;
                    }
                    if((idxDidIndexType_st->dataNegRespCode_u8 != 0x00) && (&(idxDidIndexType_st->dataNegRespCode_u8) != NULL_PTR))
                    {
                        s_dataRetVal_u8=E_NOT_OK;
                    }
                }
            }
            else{

                s_dataRetVal_u8 = E_NOT_OK;
            }
#endif
        }
        if(s_dataRetVal_u8 != DCM_E_PENDING)

        {
            idxDidIndexType_st->nrNumofSignalsRead_u16=0x0;
            idxDidIndexType_st->dataSignalLengthInfo_u32=0x0;
        }
   }
   else{
        s_dataRetVal_u8 = E_NOT_OK;
   }
    return (s_dataRetVal_u8);
}

#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    dataRetVal_u8 = E_NOT_OK;

   if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER)
   {
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveRDBIDid(dataDid_u16);
#endif
   }

   else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)
   {
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveWDBIDid(dataDid_u16);
#endif
   }

   else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)
   {
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
         dataRetVal_u8 = Dcm_GetActiveDDDid(dataDid_u16);
#endif
     }

   else{
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveIOCBIDid(dataDid_u16);
#endif

   }

    return (dataRetVal_u8);
}
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

