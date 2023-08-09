

#include "PduR_Prv.h"
#include "PduR_Mc.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_UpToLo(P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                 VAR(PduIdType, AUTOMATIC) mcId,
                                                 P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{

    PduR_GT_TpPtr      gt;

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;

    PduR_TpSessDynPtr  SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
    VAR(Std_ReturnType, AUTOMATIC) rtn = E_NOT_OK;

#if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)
    boolean flg = FALSE;
#endif

    if(upToLoTable != NULL_PTR)
    {

            while(tablePtr->upId < mcId)
            {
                tablePtr++;
            }

            while (tablePtr->upId == mcId)
            {
                #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

                if ((tablePtr->routingCntrl_Idx == PDUR_RPGID_NULL)   ||
                    ((PDUR_RPG_ENROUTING_INFO(tablePtr->routingCntrl_Idx)) != FALSE ))
                #endif
                {
                    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                    rtn = PDUR_BASE_RPTBL(loTxTablePtr)[tablePtr->upToLo.loTransmitID].PduR_loTransmitFunc (tablePtr->upToLo.loId, info);
                    #else
                    rtn = PduR_loTransmitTable[tablePtr->upToLo.loTransmitID].PduR_loTransmitFunc (tablePtr->upToLo.loId, info);
                    #endif
                    if (rtn == E_OK)
                    {
                    #if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)

                        flg = TRUE;
                    #endif

                        if((tablePtr->isTpModule) && (tablePtr->upSrcLayerName == PDUR_NULL_BSWMODNAME))
                        {
                            gt = PDUR_GW_TP_BASE;
                            while(gt->loId != mcId)
                            {
                                gt++;
                            }

                            fifo = (gt->buffer);
                            ConnectionPtr = fifo->connectionTable;

                            SessionPtr = ConnectionPtr->primarySession;

                            SessionPtr->Tx_E_OK_Count++;
                        }

                       rtn = E_OK;
                    }

                }
                tablePtr++;
            }
#if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)
            if(flg == TRUE)
            {
                tablePtr--;
                PduR_MC_SetTxConfirmationFlag(tablePtr->upLayerSymName ,tablePtr->upSrcLayerName);
            }
#endif
    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_CancelTransmit_UpToLo(P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                 VAR(PduIdType, AUTOMATIC) mcId)
{
    P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
    VAR(Std_ReturnType, AUTOMATIC) rtn = E_NOT_OK;
    VAR(uint8, AUTOMATIC) cnt_Not_Ok = 0;

    if(upToLoTable != NULL_PTR)
    {

            while(tablePtr->upId < mcId)
            {
                tablePtr++;
            }
            while (tablePtr->upId == mcId)
            {
                #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

                if ((tablePtr->routingCntrl_Idx == PDUR_RPGID_NULL)   ||
                    ((PDUR_RPG_ENROUTING_INFO(tablePtr->routingCntrl_Idx)) != FALSE ))
                #endif
                {
                    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                    rtn = PDUR_BASE_RPTBL(loCnclTxTablePtr)[tablePtr->upToLo.loCancelTransmitID].PduR_loCancelTransmitFunc(tablePtr->upToLo.loId);
                    #else
                    rtn = PduR_loCancelTransmitTable[tablePtr->upToLo.loCancelTransmitID].PduR_loCancelTransmitFunc(tablePtr->upToLo.loId);
                    #endif
                    if (rtn != E_OK)
                    {
                        cnt_Not_Ok++;
                    }
                }
                tablePtr++;
            }

            if (cnt_Not_Ok > 0)
            {
                rtn = E_NOT_OK;
            }
    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

