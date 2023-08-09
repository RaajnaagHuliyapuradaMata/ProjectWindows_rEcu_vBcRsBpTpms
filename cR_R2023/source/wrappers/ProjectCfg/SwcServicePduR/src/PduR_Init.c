
#include "PduR_Prv.h"
#include "Dem.h"
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
#include "rba_BswSrv.h"
#endif
#include "PduR_BufferPool.h"
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_Init( P2CONST( Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr )
{
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
    #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
        PduR_dInit(ConfigPtr);
    #else
        PduR_iInit(ConfigPtr);
    #endif
#endif
}

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
FUNC( void, PDUR_CODE ) PduR_dInit( P2CONST( Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr )
{

    if (PduR_State != PDUR_UNINIT)
    {
        PDUR_REPORT_ERROR(PDUR_SID_INIT,PDUR_E_INVALID_REQUEST);
    }
    else
    {
#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        if( !ConfigPtr )
        {

            PDUR_REPORT_ERROR(PDUR_SID_INIT,PDUR_E_CONFIG_PTR_INVALID);
        }
        else
        {

            PduR_iInit( ConfigPtr );
        }
#else
        PduR_iInit( ConfigPtr );
#endif
    }
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

LOCAL_INLINE uint8 PduR_CompareVersionInfo(P2CONST(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_CONST) srcVersionInfo,
        P2CONST(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_CONST) destVersionInfo)
{
    uint8 stEqual = 1;

    if (
            ((srcVersionInfo->vendorID) == (destVersionInfo->vendorID)) &&
            ((srcVersionInfo->moduleID) == (destVersionInfo->moduleID)) &&
            ((srcVersionInfo->sw_major_version) == (destVersionInfo->sw_major_version)) &&
            ((srcVersionInfo->sw_minor_version) == (destVersionInfo->sw_minor_version)) &&
            ((srcVersionInfo->sw_patch_version) == (destVersionInfo->sw_patch_version))
    )
    {
        stEqual = 0;
    }

    return stEqual;

}
#endif

FUNC( void, PDUR_CODE ) PduR_iInit( P2CONST( Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr)
{
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
    uint16 index;
#endif
#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    Std_VersionInfoType versionInfo;
    Std_VersionInfoType ModuleversionInfo;
    uint8 flag = 0;
#endif

    if (PduR_State == PDUR_UNINIT)
    {

            #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
              Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_PASSED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_PASSED;
             PduR_DsmReInitStruct.instanceLostErrorFlag = FALSE;
            #endif
            #endif

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        if( !ConfigPtr )
        {
            #if defined(PDUR_DEM_INIT_FAILED) && (PDUR_DEM_INIT_FAILED != 0)
             Dem_ReportErrorStatus( PDUR_E_INIT_FAILED, DEM_EVENT_STATUS_FAILED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.initFailedErrorStatus =  DEM_EVENT_STATUS_FAILED;
            #endif
            #endif
        }
        else
#endif
        {
            PduR_State = PDUR_REDUCED;

            #if defined(PDUR_DEM_INIT_FAILED) && (PDUR_DEM_INIT_FAILED != 0)
              Dem_ReportErrorStatus( PDUR_E_INIT_FAILED, DEM_EVENT_STATUS_PASSED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.initFailedErrorStatus =  DEM_EVENT_STATUS_PASSED;
             PduR_DsmReInitStruct.initFailedErrorFlag = FALSE;
            #endif
            #endif

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

            PduR_Base = (P2CONST(PduR_PBConfigType, PDUR_CONST, PDUR_APPL_CONST))ConfigPtr->PduR_ConfigDataPtr;

            PduR_FunctionPtrs = (P2CONST( PduR_RPTablesType, PDUR_CONST, PDUR_APPL_CONST ))PduR_Base->PduR_RPTablesPtr;

            PduR_GetVersionInfo(&versionInfo);
            ModuleversionInfo = (*ConfigPtr->PduR_VersionInfoPtr);
            flag = PduR_CompareVersionInfo(&versionInfo, &ModuleversionInfo);
            if (flag != 0)
            {

                PduRAppl_IncompatibleGenerator();
                return;
            }
#else
            (void)ConfigPtr;
            PduR_Base = &PduR_GlobalPBConfig;
#endif

            #if (PDUR_DISABLE_MULTICAST_SUPPORT == 0)
            if (PDUR_LOTP_TX_STATE_BASE)
            {
                PduIdType i;
                for(i=0; i<PDUR_NR_VALID_IDS(loTpTxToUpMc); i++)
                {
                    PduR_iInit_multicast(PDUR_LOTP_TX_STATE_BASE+i);
                }
            }
            #endif

            #if defined(PDUR_BUFFERPOOL_SUPPORT)
                PduR_BufferPoolInit(&PduR_BufferPool_Config);
            #endif

            #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
                for(index = 0; index <= (PduR_Base->rpg_NrEntries) ; index++)
                {
                    PduR_Base->pduR_Rpg_Status[index] = (PduR_Base->rpg_EnRoutingInfo[index]);
                }
            #endif

                 #if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
                    {

                    PduR_GT_TpPtr gwTpTablePtr;
                    PduR_GwTp_SessionListPtr gwTpSessionPtr_L;
                    PduR_TpConnDynPtr ConnectionPtr;
                    uint16 sessionIndex = 0;
                    uint16 TpIndex_u16;

                    for(TpIndex_u16 = 0; TpIndex_u16 < (PduR_Base->totalNoOfGwTpRps) ; TpIndex_u16++)
                        {
                            gwTpTablePtr = PDUR_GW_TP_BASE+TpIndex_u16;
                            ConnectionPtr =(PduR_TpConnDynPtr)(gwTpTablePtr->buffer->connectionTable);
                            gwTpSessionPtr_L = PduR_Base->gwTp_SessionListPtr;

                            ConnectionPtr->primarySession = gwTpSessionPtr_L[sessionIndex].GwTpSessionPtr;

                            PduR_InitilizePduR_Gw_Tp_Session(gwTpSessionPtr_L[sessionIndex].GwTpSessionPtr);

                            sessionIndex++;
                            #ifdef PDUR_QUEUEING_SUPPORT
                            if(gwTpTablePtr->TpGwQueueSize == 2u)
                            {

                                ConnectionPtr->secondarySession = gwTpSessionPtr_L[sessionIndex].GwTpSessionPtr;

                                PduR_InitilizePduR_Gw_Tp_Session(gwTpSessionPtr_L[sessionIndex].GwTpSessionPtr);

                                sessionIndex++;
                            }
                            else{

                                ConnectionPtr->secondarySession = NULL_PTR;
                            }
                            ConnectionPtr->activeSessionCount = 0;
                            #endif

                        }
                    }
                   #endif

                #if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
                    {
                        P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gwIfTablePtr;
                        P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )       dyn;
                        P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA )  infoBuf;
                        PduR_FifoType        fifo;
                        PduR_FifoDynIfPtr    dyn_buf;
                        uint16 IfIndex_u16;
                        for(IfIndex_u16 = 0; IfIndex_u16 < (PduR_Base->totalNoOfGwIfRps) ; IfIndex_u16++)
                        {
                            gwIfTablePtr = PDUR_GW_IF_BASE + IfIndex_u16;

                            if(gwIfTablePtr->isFifoType) {

                                fifo = (PduR_FifoType)(gwIfTablePtr->buffer);
                                dyn_buf = (PduR_FifoDynIfPtr)(fifo->dyn);
                                PduR_InitilizePduR_Gw_If_DynStruct(dyn_buf, fifo);
                            }
                            else {

                                 dyn = (P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )) gwIfTablePtr->buffer;
                                 infoBuf = dyn->gwBuf;
                                 infoBuf->SduDataPtr = dyn->begin;
                                 infoBuf->SduLength = dyn->confLen;

#if defined(PDUR_DEFAULT_VALUE_SUPPORT) && (PDUR_DEFAULT_VALUE_SUPPORT != 0)
                                 {
                                     P2CONST( PduR_DefaultValues_fixed, AUTOMATIC, PDUR_CONST ) defaultValues;
                                     uint8 IfIndexu_8;
                                     uint8 BytePosition;
                                     if(dyn->defaultValueElement != NULL_PTR)
                                     {
                                         defaultValues = dyn->defaultValueElement;
                                         for(IfIndexu_8 = 0; IfIndexu_8 < dyn->defaultValueSize ; IfIndexu_8++)
                                         {

                                             BytePosition = defaultValues[IfIndexu_8].bytePosition;
                                             dyn->begin[BytePosition] = defaultValues[IfIndexu_8].byteDefaultValue;
                                         }
                                     }
                                 }

#endif
                            }
                        }
                    }
                 #endif

            PduR_State = PDUR_ONLINE;
        }
    }
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_iInit_multicast(P2VAR( PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state)
{
    state->pduPtr     = NULL_PTR;
    state->allocError = BUFREQ_OK;
    state->txFailure  = E_OK;
    state->txConf     = 0;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

