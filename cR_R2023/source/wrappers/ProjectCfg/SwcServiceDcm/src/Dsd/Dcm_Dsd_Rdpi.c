

#include "DcmCore_DslDsd_Inf.h"
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_PeriodicInfoType_tst,DCM_CODE) Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,       DCM_VAR)      Dcm_NumOfActivePeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxDidIndexType_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean,DCM_VAR) s_isTxPduIdBusy_b =  FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Rdpi2MesContext_st;

VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Rdpi2ResponseType_en;

VAR(PduInfoType,DCM_VAR) Dcm_DsldRdpi2pduinfo_ast[DCM_CFG_NUM_RDPITYPE2_TXPDU];

static VAR(uint8,DCM_VAR) s_idxRdpi2TxPduId_u8;

P2CONST(Dcm_ProtocolExtendedInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRdpi2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

static FUNC(void,DCM_CODE) Dcm_RdpiPriorityInversion(VAR(uint16,AUTOMATIC) idxSchedulerIndexLoop_u16)
{
#if (DCM_CFG_MAX_DID_SCHEDULER > 1u)
    VAR(uint16,AUTOMATIC) idxIndex_u16;
#endif
    VAR(Dcm_PeriodicInfoType_tst,DCM_CODE) Temp_PeriodicInfo_st;

    Temp_PeriodicInfo_st.cntrTime_u32         = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32;
    Temp_PeriodicInfo_st.dataId_u16           = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataId_u16;
    Temp_PeriodicInfo_st.idxPeriodicId_u16    = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].idxPeriodicId_u16;
    Temp_PeriodicInfo_st.dataOverflowValue_en = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataOverflowValue_en;
    Temp_PeriodicInfo_st.dataRange_b          = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataRange_b;

#if (DCM_CFG_MAX_DID_SCHEDULER > 1u)
    for(idxIndex_u16 = idxSchedulerIndexLoop_u16 ; idxIndex_u16 < (DCM_CFG_MAX_DID_SCHEDULER-1u) ; idxIndex_u16++)
    {

        Dcm_PeriodicInfo_st[idxIndex_u16].cntrTime_u32         = Dcm_PeriodicInfo_st[idxIndex_u16+1].cntrTime_u32;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataId_u16           = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataId_u16;
        Dcm_PeriodicInfo_st[idxIndex_u16].idxPeriodicId_u16    = Dcm_PeriodicInfo_st[idxIndex_u16+1].idxPeriodicId_u16;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataOverflowValue_en = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataOverflowValue_en;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataRange_b          = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataRange_b;
    }
#endif

        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].cntrTime_u32         = Temp_PeriodicInfo_st.cntrTime_u32;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataId_u16           = Temp_PeriodicInfo_st.dataId_u16;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].idxPeriodicId_u16    = Temp_PeriodicInfo_st.idxPeriodicId_u16;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataOverflowValue_en = Temp_PeriodicInfo_st.dataOverflowValue_en;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataRange_b          = Temp_PeriodicInfo_st.dataRange_b;
}

FUNC(void,DCM_CODE) Dcm_DsldPeriodicSchedulerIni(void)
{
	VAR(uint16,AUTOMATIC) idxIndex_u16;
	for(idxIndex_u16=0;idxIndex_u16<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u16++)
	{
		Dcm_PeriodicInfo_st[idxIndex_u16].dataId_u16=0x00;
		Dcm_PeriodicInfo_st[idxIndex_u16].idxPeriodicId_u16=0x00;
		Dcm_PeriodicInfo_st[idxIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
		Dcm_PeriodicInfo_st[idxIndex_u16].cntrTime_u32=0x00;
		
		Dcm_PeriodicInfo_st[idxIndex_u16].dataRange_b = FALSE;

	}
	Dcm_NumOfActivePeriodicId_u8 = 0x00;
	Dcm_PeriodicSchedulerRunning_b=FALSE;
	s_idxRdpi2TxPduId_u8=0;
	Dcm_ResetDIDIndexstruct(&s_Dcm_idxDidIndexType_st);		
}

static FUNC(void,DCM_CODE) Dcm_SetRdpicounter(VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16)
{
    if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en==DCM_RDPI_SLOW_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_SLOWRATE;
     }
     else if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en==DCM_RDPI_MEDIUM_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_MEDIUMRATE;
     }
     else if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en== DCM_RDPI_FAST_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_FASTRATE;
     }
     else
     {

     }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_InitializeRdpiParameters(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpiType2_pu8)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
    VAR (Std_ReturnType,   AUTOMATIC) idxIndex_u8;
    VAR (uint8,   AUTOMATIC) ConnectionTxpduOffset_u8;
    VAR (uint8,   AUTOMATIC) ConnectionNumberofTxpdus_u8;
    idxIndex_u8=0;
    ConnectionTxpduOffset_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].ConnectionIndex_u8;
    ConnectionNumberofTxpdus_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].NumberOfTxpdu_u8;
    dataCondChkRetVal_u8=E_NOT_OK;
    (void)idxRdpiType2_pu8;
    Dcm_DsldRdpi2_pcst = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs;

    Dcm_Rdpi2ResponseType_en = DCM_DSLD_POS_RESPONSE;

    Dcm_Rdpi2MesContext_st.resDataLen = 0x0u;

    Dcm_Rdpi2MesContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
    for(idxIndex_u8 = ConnectionTxpduOffset_u8; idxIndex_u8 < (ConnectionTxpduOffset_u8 + ConnectionNumberofTxpdus_u8); idxIndex_u8++)
    {

        if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy==FALSE)
        {
            Dcm_Rdpi2MesContext_st.resData = &Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txbuffer_ptr[0];
            break;
        }
    }

    if(idxIndex_u8<(ConnectionTxpduOffset_u8 + ConnectionNumberofTxpdus_u8))
    {

        Dcm_Rdpi2MesContext_st.resMaxDataLen = Dcm_DsldRdpi2_pcst->txbuffer_length_u32 - 1uL;

        Dcm_Rdpi2MesContext_st.msgAddInfo.sourceofRequest = DCM_RDPI_SOURCE;

        Dcm_Rdpi2MesContext_st.msgAddInfo.suppressPosResponse = FALSE;

        *idxRdpiType2_pu8=idxIndex_u8;
        s_idxRdpi2TxPduId_u8=idxIndex_u8;

        dataCondChkRetVal_u8=E_OK;
        s_isTxPduIdBusy_b = FALSE;
    }
    else
    {
        dataCondChkRetVal_u8=E_NOT_OK;
        s_isTxPduIdBusy_b = TRUE;
    }
    return dataCondChkRetVal_u8;
}

FUNC(void,DCM_CODE) Dcm_GetRdpiType2Index(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpi2TxPduId_u8)
{
    *idxRdpi2TxPduId_u8=s_idxRdpi2TxPduId_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_FrameRdpiresponse(VAR(uint32, AUTOMATIC) dataLength_u32,VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataReaddataRetVal_u8;
    VAR (uint8,   AUTOMATIC) idxRdpiType2_u8;
    idxRdpiType2_u8=0xFF;
    dataReaddataRetVal_u8=E_NOT_OK;

    dataReaddataRetVal_u8=Dcm_InitializeRdpiParameters(&idxRdpiType2_u8);

    if(E_OK==dataReaddataRetVal_u8)
    {

        dataReaddataRetVal_u8 = Dcm_GetDIDData (&s_Dcm_idxDidIndexType_st,&Dcm_Rdpi2MesContext_st.resData[1]);

        if(s_Dcm_idxDidIndexType_st.dataNegRespCode_u8==0x00)
        {

            if(E_OK==dataReaddataRetVal_u8)
            {

               Dcm_Rdpi2MesContext_st.resDataLen=dataLength_u32+1uL;

               Dcm_Rdpi2MesContext_st.resData[0]=(uint8)(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataId_u16);

               Dcm_ProcessingDone(&Dcm_Rdpi2MesContext_st);

               s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
               s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;

            }
            else
            {
                s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
                s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
                dataReaddataRetVal_u8=E_NOT_OK;
            }
        }
        else
        {
            s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;
            s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;
            dataReaddataRetVal_u8=E_NOT_OK;
        }
    }
    else
    {
        dataReaddataRetVal_u8=E_NOT_OK;
    }

    return dataReaddataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_VerifyLengthRdpiType(VAR(uint32,AUTOMATIC) dataLength_u32)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
    dataCondChkRetVal_u8=E_NOT_OK;

    if((dataLength_u32+1uL)<=Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs->txbuffer_length_u32)
    {
        dataCondChkRetVal_u8=E_OK;
    }

    return dataCondChkRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiCheckPIDSupportConditions(VAR(uint16,AUTOMATIC) idxPeriodicIndex_u16)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
    VAR (uint32,AUTOMATIC) dataSessionMask_u32;
    VAR (uint32,AUTOMATIC) dataSecurityMask_u32;
    VAR(uint32,                      AUTOMATIC) dataLength_u32;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst;

    dataLength_u32=0x0;
    dataSessionMask_u32=0;
    dataSecurityMask_u32=0;

    s_Dcm_idxDidIndexType_st.idxIndex_u16 = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].idxPeriodicId_u16;
    s_Dcm_idxDidIndexType_st.dataRange_b = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataRange_b;
    dataCondChkRetVal_u8=E_NOT_OK;
    adrExtendedConfig_pcst=NULL_PTR;

    if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
    {
        adrExtendedConfig_pcst=Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
    }
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

    else
    {
        s_Dcm_idxDidIndexType_st.dataRangeDid_16 = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataId_u16;
        adrExtendedConfig_pcst=Dcm_DIDRangeConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
    }
#endif

    dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;

    dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;

    if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
    {

        if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
        {

            dataCondChkRetVal_u8=Dcm_RdpiIsDidCondtionChkReadSupported(&s_Dcm_idxDidIndexType_st);
            if (dataCondChkRetVal_u8 == E_OK)
            {

               if(E_OK==Dcm_GetLengthOfDIDIndex(&s_Dcm_idxDidIndexType_st, &dataLength_u32,(uint16)(Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataId_u16|0xF200u)))
               {

                   if(E_OK==Dcm_VerifyLengthRdpiType(dataLength_u32))
                   {

                       dataCondChkRetVal_u8=Dcm_FrameRdpiresponse(dataLength_u32,idxPeriodicIndex_u16);
                   }
                   else
                   {
                     Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                   }
               }
               else
               {
                 Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
               }
            }
            else
            {
                Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
            }
        }
        else
        {
            Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
        }
    }
    else
    {
        Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
    }

    return dataCondChkRetVal_u8;
}

FUNC(void,DCM_CODE) Dcm_RdpiMainFunction(void)
{
    VAR(uint16, AUTOMATIC) idxSchedulerIndexLoop_u16 = 0u;
    VAR(uint16, AUTOMATIC) idxPriorityInversion_u16 = 0u;
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8;
    VAR (Std_ReturnType,   AUTOMATIC) idxIndex_u8;
    idxIndex_u8=0;
    idxSchedulerIndexLoop_u16=0x0u;
    dataCondChkRetVal_u8=E_NOT_OK;

    if(Dcm_NumOfActivePeriodicId_u8>0u)
    {

        for( idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU;idxIndex_u8++)
        {
            if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy!=FALSE)
            {
                if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8!=0)
                {

                    Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8--;

                    if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8==0)
                    {

                        Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy=FALSE;
                        s_isTxPduIdBusy_b = FALSE;

                        Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8=DCM_CFG_RDPITYPE2FREETXPDUCOUNTER;
                    }
                }
            }
        }

        for (idxSchedulerIndexLoop_u16=0;idxSchedulerIndexLoop_u16<DCM_CFG_MAX_DID_SCHEDULER;idxSchedulerIndexLoop_u16++)
        {
            if (Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION)
            {

               if(Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32>0uL)
               {

                   Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32--;
               }
            }
        }

        if((DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8))&&(NULL_PTR != Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs))
        {
            for (idxSchedulerIndexLoop_u16=0;idxSchedulerIndexLoop_u16<DCM_CFG_MAX_DID_SCHEDULER;idxSchedulerIndexLoop_u16++)
            {
                if ((Dcm_PeriodicInfo_st[idxPriorityInversion_u16].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION) && \
                        (Dcm_PeriodicInfo_st[idxPriorityInversion_u16].cntrTime_u32 == 0uL))
                {
                   dataCondChkRetVal_u8=Dcm_RdpiCheckPIDSupportConditions(idxPriorityInversion_u16);

                   if((s_isTxPduIdBusy_b != TRUE) || (dataCondChkRetVal_u8 != E_NOT_OK))
                   {
                      Dcm_SetRdpicounter(idxPriorityInversion_u16);
                      Dcm_RdpiPriorityInversion(idxPriorityInversion_u16);
                   }
                }
                else
                {

                    idxPriorityInversion_u16++;
                }
            }
        }
    }
}

FUNC(void,DCM_CODE) Dcm_DsldResetRDPI(void)
{
    Dcm_DsldPeriodicSchedulerIni();
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
