
#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_DisableRouting( VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id,
        VAR(boolean, AUTOMATIC) initialize)
{

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

    if ((id != 0) && (id <= PDUR_GET_RPGID_MAX))
    {

        SchM_Enter_PduR_LockDisableRoutingNoNest();

        if((PDUR_RPG_ENROUTING_INFO(id)) == TRUE)
        {

            (PDUR_RPG_ENROUTING_INFO(id)) = FALSE;

            if (PDUR_RPG_CONFIG_INFO[id].targetInfo != NULL_PTR)
            {
                PduR_FifoDynIfPtr       dyn_If;
                PduR_TpSessDynPtr       dyn_Tp;
                P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR)  buffPtr;
                P2CONST( PduR_TargetInfoType, AUTOMATIC, PDUR_CONST ) targetInfo;
                VAR(uint8, AUTOMATIC)   cntDest;
                VAR(uint8, AUTOMATIC)   index;

                targetInfo = PDUR_RPG_CONFIG_INFO[id].targetInfo;
                cntDest = PDUR_RPG_CONFIG_INFO[id].cntDestOfTypeFIFO;

                for(index=0;index < cntDest;index++)
                {

                    switch(targetInfo->pathType)
                    {
                        case PDUR_FIFO_IF:

                                        dyn_If = (PduR_FifoDynIfPtr)targetInfo->destInfo;
                                        dyn_If->used           = 0;
                                        dyn_If->txConfPending  = 0;
                                        dyn_If->writePtr       = dyn_If->readPtr;

                            break;

                        case PDUR_UCSEB_TP:

                                        buffPtr = (P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR))targetInfo->destInfo;
                                        buffPtr->bufferLock = 0;
                            break;

                        case PDUR_MCSEB_TP:

                                        buffPtr = (P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR))targetInfo->destInfo;

                                        buffPtr->lowerLayers = buffPtr->lowerLayers - 1;

                            break;

                        case PDUR_UCFIFO_TP:

                                        dyn_Tp = (PduR_TpSessDynPtr)targetInfo->destInfo;

                                        dyn_Tp->writePtr =  dyn_Tp->readPtr;
                                        dyn_Tp->numRxLength = 0;
                                        dyn_Tp->numTxLength = 0;
                                        dyn_Tp->SduLength = 0;
                            break;

                        default:
                               {

                               }
                            break;
                    }
                    targetInfo++;

                }

            }
#if defined(PDUR_DEFAULT_VALUE_SUPPORT) && (PDUR_DEFAULT_VALUE_SUPPORT != 0)
            else if((initialize == TRUE) && (PDUR_RPG_CONFIG_INFO[id].defaultValue_info != NULL_PTR) )
            {
                P2CONST( PduR_DefaultValue_Info, AUTOMATIC, PDUR_CONST ) defaultValueInfo;
                P2CONST( PduR_DefaultValues_fixed, AUTOMATIC, PDUR_CONST ) destDfaltVals;
                P2VAR( uint8, TYPEDEF, PDUR_VAR )       buffAddr;
                VAR(uint8, AUTOMATIC)   dfltValDestCnt;
                VAR(uint8, AUTOMATIC)   counter;
                VAR(uint8, AUTOMATIC)   index;
                VAR(uint8, AUTOMATIC)   bytePosition;

                defaultValueInfo = PDUR_RPG_CONFIG_INFO[id].defaultValue_info;
                destDfaltVals = defaultValueInfo->defaultValueElement;
                dfltValDestCnt = PDUR_RPG_CONFIG_INFO[id].cntOfDestWithDefValue;
                buffAddr = defaultValueInfo->begin;
                counter = 0;

                while(counter < dfltValDestCnt)
                {

                    for(index = 0; index < defaultValueInfo->defaultValueSize; index++)
                    {

                        bytePosition = destDfaltVals[index].bytePosition;
                        buffAddr[bytePosition] = destDfaltVals[index].byteDefaultValue;
                    }

                    defaultValueInfo++;

                    counter++;
                }

            }

            else
			{

            }
#endif
        }
        SchM_Exit_PduR_LockDisableRoutingNoNest();

    }
    else
    {

        PDUR_REPORT_ERROR(PDUR_SID_DISABLEROUTING, PDUR_E_ROUTING_TABLE_ID_INVALID);
    }

   #else
        (void)id;
        (void)initialize;
   #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_EnableRouting( VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id)
{

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

     if ((id != 0) && (id <= PDUR_GET_RPGID_MAX))
     {

         SchM_Enter_PduR_LockEnableRoutingNoNest();

         if ((PDUR_RPG_ENROUTING_INFO(id)) == FALSE)
         {
             (PDUR_RPG_ENROUTING_INFO(id)) = TRUE;

            if (PDUR_RPG_CONFIG_INFO[id].targetInfo != NULL_PTR)
            {
                PduR_TpSessDynPtr       dyn_Tp;
                P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR) buffPtr;
                const PduR_TargetInfoType     *targetInfo;
                VAR(uint8, AUTOMATIC)   cntDest;
                VAR(uint8, AUTOMATIC)   index;

                targetInfo = PDUR_RPG_CONFIG_INFO[id].targetInfo;
                cntDest = PDUR_RPG_CONFIG_INFO[id].cntDestOfTypeFIFO;
                for(index=0;index < cntDest;index++)
                {
                    switch(targetInfo->pathType)
                    {
                            case PDUR_MCSEB_TP:

                                        buffPtr = (PduR_BuffLockType*)targetInfo->destInfo;

                                        buffPtr->lowerLayers = buffPtr->lowerLayers + 1;

                                 break;
                            case PDUR_UCSEB_TP:

                                        buffPtr = (PduR_BuffLockType*)targetInfo->destInfo;

                                        buffPtr->lowerLayers = 1;
                                        buffPtr->bufferLock = 0;

                                 break;
                            case PDUR_UCFIFO_TP:

                                        dyn_Tp = (PduR_TpSessDynPtr)targetInfo->destInfo;

                                        dyn_Tp->writePtr =  dyn_Tp->readPtr;
                                        dyn_Tp->numRxLength = 0;
                                        dyn_Tp->numTxLength = 0;
                                        dyn_Tp->SduLength = 0;
                                 break;
                            default:
                                   {

                                   }
                                 break;

                    }

                    targetInfo++;

                }

            }
         }

         SchM_Exit_PduR_LockEnableRoutingNoNest();

     }
     else
     {

        PDUR_REPORT_ERROR(PDUR_SID_ENABLEROUTING, PDUR_E_ROUTING_TABLE_ID_INVALID);
     }

   #else
      (void)id;
   #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

