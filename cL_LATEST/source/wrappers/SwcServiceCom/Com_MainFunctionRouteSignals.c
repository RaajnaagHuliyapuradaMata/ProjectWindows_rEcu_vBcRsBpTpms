

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

LOCAL_INLINE Std_ReturnType Com_ReadSigGwReceiveQueue(
                                                   Type_SwcServiceCom_tIdPdu *            ComRxPduId
   ,                                                  Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux
                                                      );

LOCAL_INLINE void Com_Lok_PrepareTxIpdu(void);

LOCAL_INLINE void Com_Lok_ReadRxQueueAndProcess(void);

#ifdef COM_SIGNALGATEWAY

LOCAL_INLINE void Com_Lok_ProcessRxSignalGateway(Com_RxIpduConstPtrType RxIpduConstPtr);

#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))

LOCAL_INLINE void Com_Lok_ProcessRxSigGrpGateway(Com_RxIpduConstPtrType RxIpduConstPtr);

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_MainFunctionRouteSignals(void)
{

   if(Com_Uninit_Flag == COM_INIT)
   {

        Com_Lok_ReadRxQueueAndProcess();

        Com_Lok_PrepareTxIpdu();
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
Std_ReturnType Com_WriteSigGwReceiveQueue(Type_SwcServiceCom_tIdPdu ComRxPduId)
{

   Com_RxGwQueuePtrType        l_RxGwQueuePtr_struc;
   uint8                       Status;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    Status = E_OK;

    l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux] = ComRxPduId;

    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = ( Com_RxGwQueueIndexType )
                                                  ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux + COM_ONE ) %
                                                    ( COM_GET_NUM_GWSRC_IPDUS + COM_ONE ) );

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(COM_FALSE == (Com_Lok_DETCheck_Param_Only((
                      ((l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux) % (COM_GET_NUM_GWSRC_IPDUS+COM_ONE)) ==
                       (l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)), COMServiceId_MainFunctionRouteSignals)))
   {

        Status = E_NOT_OK;
   }
#endif

    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE Std_ReturnType Com_ReadSigGwReceiveQueue(
                                                   Type_SwcServiceCom_tIdPdu *            ComRxPduId
   ,                                                  Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux
                                                      )
{
   Com_RxGwQueuePtrType        l_RxGwQueuePtr_struc;
    Std_ReturnType              retVal_uo;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    retVal_uo            = E_NOT_OK;

   if(l_Com_RxGwQueueWrite_ux != l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)
   {

        *ComRxPduId = l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux];

        l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux = ( Com_RxGwQueueIndexType )
                                                     ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux + COM_ONE ) %
                                                       ( COM_GET_NUM_GWSRC_IPDUS + COM_ONE ) );
        retVal_uo = E_OK;
   }

    return(retVal_uo);
}

LOCAL_INLINE void Com_Lok_PrepareTxIpdu(void){

   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   uint16_least                idx_TxIpduId_u16;
   uint16_least                numOfIpdus;
#if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP)
   Com_TxSigGrpRamPtrType      TxSigGrpRamPtr;
   uint16_least                idx_TxSigGrpId_u16;
   uint16_least                maxTxSigGrpId_u16;
#endif
   boolean                     isTriggered_b;
#ifdef COM_TxFilters
   boolean                     isTMSChanged_b;
#endif
#ifdef COM_TxIPduTimeOut
   boolean                     isTimeoutReq_b;
#endif

    numOfIpdus     = COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)ComMainFunction_Internal_MainFunctionTx).NumOfIpdus;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

   for(idx_TxIpduId_u16 = COM_ZERO; idx_TxIpduId_u16 < numOfIpdus; idx_TxIpduId_u16++)
   {

        if((Com_GetValue(TXIPDU,_ISGWPDU,TxIpduConstPtr->txIPduFields)) &&
           (Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)idx_TxIpduId_u16)))
        {

#if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP)

            idx_TxSigGrpId_u16  = TxIpduConstPtr->FirstTxSigGrp_Index;
            maxTxSigGrpId_u16   = idx_TxSigGrpId_u16 + TxIpduConstPtr->No_Of_SigGrp_Ref;

            TxSigGrpRamPtr      = &COM_GET_TXSIGGRPFLAG(idx_TxSigGrpId_u16);

            for( ; idx_TxSigGrpId_u16 < maxTxSigGrpId_u16; idx_TxSigGrpId_u16++ )
            {
                if(Com_GetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr->txSigGrpRAMFields))
                {
                    Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr->txSigGrpRAMFields,COM_FALSE);

                    (void)Com_InternalSendSignalGroup( (Com_SignalGroupIdType)idx_TxSigGrpId_u16 );
                }
                TxSigGrpRamPtr++;
            }
#endif

            SchM_Enter_Com_TxIpduProtArea(MAINFUNCTION_ROUTE_SIGNALS);

            isTriggered_b = Com_GetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags);
            Com_SetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxFilters
            isTMSChanged_b = Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags);
            Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

#ifdef COM_TxIPduTimeOut
            isTimeoutReq_b = Com_GetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags);
            Com_SetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif
            SchM_Exit_Com_TxIpduProtArea(MAINFUNCTION_ROUTE_SIGNALS);

            if(((isTriggered_b) &&
                (COM_TX_MODE_IS_EVENT(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))))
#ifdef COM_TxFilters
                || (isTMSChanged_b)
#endif
               )
            {

                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                sendIpduFlag_u16.isEventTrig      = COM_SET;

                sendIpduFlag_u16.isSigTriggered   = COM_BOOL_TO_UNSIGNED(isTriggered_b);

#ifdef COM_TxFilters
                sendIpduFlag_u16.isModeChangd     = COM_BOOL_TO_UNSIGNED(isTMSChanged_b);
#endif

#ifdef COM_TxIPduTimeOut
                sendIpduFlag_u16.isTimeoutReq     = COM_BOOL_TO_UNSIGNED(isTimeoutReq_b);
#endif

                Com_Lok_SendIpdu((Type_SwcServiceCom_tIdPdu)idx_TxIpduId_u16, sendIpduFlag_u16);
            }

        }

        TxIpduConstPtr++;
        TxIpduRamPtr++;
   }
}

LOCAL_INLINE void Com_Lok_ReadRxQueueAndProcess(void){

   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
   Com_RxGwQueuePtrType        RxGwQueuePtr_l;
   Com_RxGwQueueIndexType      l_Com_RxGwQueueWrite_ux;
   Type_SwcServiceCom_tIdPdu                   l_Ipduid;
   uint8                       l_IpduSyncCounter;

    RxGwQueuePtr_l          = COM_GET_RXGWQUEUE_S;

    l_Com_RxGwQueueWrite_ux = RxGwQueuePtr_l->Com_RxGwQueueWrite_ux;
   {

        while(Com_ReadSigGwReceiveQueue(&l_Ipduid,l_Com_RxGwQueueWrite_ux) == (Std_ReturnType)E_OK)
        {
            RxIpduConstPtr    = COM_GET_RX_IPDU_CONSTDATA(l_Ipduid);
            RxIpduRamPtr      = &COM_GET_RXPDURAM_S(l_Ipduid);

            l_IpduSyncCounter = COM_ZERO;

            do
            {
                Com_Get_SchM_Enter_Com_RxGateway
                Com_Get_SchM_Enter_Com_RxPduBuffer

                Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags,COM_FALSE);
                Com_Get_SchM_Exit_Com_RxPduBuffer

#ifdef COM_SIGNALGATEWAY
                if(RxIpduConstPtr->numOfGwSrcSignals > COM_ZERO)
                {

                    Com_Lok_ProcessRxSignalGateway(RxIpduConstPtr);
                }
#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
                if(RxIpduConstPtr->numOfGwSrcSignalGrps > COM_ZERO)
                {

                    Com_Lok_ProcessRxSigGrpGateway(RxIpduConstPtr);
                }
#endif

                l_IpduSyncCounter =
                         ((Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags) == COM_TRUE) ?
                         ((l_IpduSyncCounter + COM_ONE) % (COM_MAXIMUM_GWSYNC_REPITIONS + COM_ONE)) : (COM_ZERO));

                Com_Get_SchM_Exit_Com_RxGateway

            }while(l_IpduSyncCounter != COM_ZERO);
        }
   }
}

#ifdef COM_SIGNALGATEWAY

LOCAL_INLINE void Com_Lok_ProcessRxSignalGateway(Com_RxIpduConstPtrType RxIpduConstPtr)
{

   Com_GwMapSigConfPtrType         ComGwMapSigConfPtr;
   Com_GwMapSigIdConfPtrType       ComGwMapSigIdConfPtr;
   Com_RxSigRamPtrType             RxSigRamPtr;
   Com_RxSigConstPtrType           RxSigConstPtr;
   Com_SignalIdType                l_TxGwDestId;
   uint16_least                    idx_RxSigId_u16;
   uint16_least                    maxRxSigId_u16;
   uint16_least                    index_u16;

   idx_RxSigId_u16  = RxIpduConstPtr->RxSigId_Index;
    maxRxSigId_u16   = idx_RxSigId_u16 + RxIpduConstPtr->numOfGwSrcSignals;

    RxSigConstPtr    = COM_GET_RXSIG_CONSTDATA(idx_RxSigId_u16);
    RxSigRamPtr      = &COM_GET_RXSIGNALFLAG(idx_RxSigId_u16);

   for( ; idx_RxSigId_u16 < maxRxSigId_u16; idx_RxSigId_u16++)
   {

        if(Com_GetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields) != COM_FALSE)
        {

            Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_FALSE);

            ComGwMapSigConfPtr   = COM_GET_GWSIG_CONSTDATA(idx_RxSigId_u16);
            ComGwMapSigIdConfPtr = COM_GET_GWSIGIDMAP_CONSTDATA(ComGwMapSigConfPtr->indexGwMapSigDestIdArray);

            for(index_u16 = ComGwMapSigConfPtr->destCount; index_u16 > COM_ZERO; index_u16--)
            {
                l_TxGwDestId = ComGwMapSigIdConfPtr->GwMap_DestId;

                Com_Lok_PackRxSignalGwBufferData(RxSigConstPtr,l_TxGwDestId);

                ComGwMapSigIdConfPtr++;
            }
        }
        RxSigRamPtr++;
        RxSigConstPtr++;
   }
}

#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))

LOCAL_INLINE void Com_Lok_ProcessRxSigGrpGateway(Com_RxIpduConstPtrType RxIpduConstPtr)
{

   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;
   Com_RxSigGrpRamPtrType              RxSigGrpRamPtr;
   Com_RxGrpSigConstPtrType            RxGrpSigConstPtr;
   Com_GwMapGrpSigConfPtrType          GwMapGrpSigConfigPtr;
   Com_GwMapGrpSigIdConfPtrType        GwMapGrpSigIdConfigPtr;
   Com_TxIntGrpSignalIdType            l_TxGwDestId;
   uint16_least                        idx_RxSigGrpId_u16;
   uint16_least                        maxRxSigGrpId_u16;
   uint16_least                        idx_RxGrpSigId_u16;
   uint16_least                        maxRxGrpSigId_u16;
   uint16_least                        index_u16;

   idx_RxSigGrpId_u16 = RxIpduConstPtr->FirstRxSigGrp_Index;
    maxRxSigGrpId_u16  = idx_RxSigGrpId_u16 + RxIpduConstPtr->numOfGwSrcSignalGrps;

    RxSigGrpConstPtr   = COM_GET_RXSIGGRP_CONSTDATA(idx_RxSigGrpId_u16);
    RxSigGrpRamPtr     = &COM_GET_RXSIGGRPFLAG(idx_RxSigGrpId_u16);

   for( ; idx_RxSigGrpId_u16 < maxRxSigGrpId_u16; idx_RxSigGrpId_u16++)
   {

        if(Com_GetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields))
        {

            Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);

            idx_RxGrpSigId_u16 = RxSigGrpConstPtr->FirstGrpSig_Index;
            maxRxGrpSigId_u16  = idx_RxGrpSigId_u16 + RxSigGrpConstPtr->numOfGwSrcGrpSignals;

            RxGrpSigConstPtr   = COM_GET_RXGRPSIG_CONSTDATA(idx_RxGrpSigId_u16);

            for( ; idx_RxGrpSigId_u16 < maxRxGrpSigId_u16; idx_RxGrpSigId_u16++ )
            {
                GwMapGrpSigConfigPtr   = COM_GET_GWGRPSIG_CONSTDATA((idx_RxGrpSigId_u16 - COM_GET_NUM_GRPSIG_NOGW));
                GwMapGrpSigIdConfigPtr =
                             COM_GET_GWGRPSIGIDMAP_CONSTDATA(GwMapGrpSigConfigPtr->indexGwMapGrpSigDestIdArray);

                for(index_u16 = GwMapGrpSigConfigPtr->destCount; index_u16 > COM_ZERO; index_u16--)
                {
                    l_TxGwDestId = GwMapGrpSigIdConfigPtr->GwMap_DestGrpSigId;

                    Com_Get_SchM_Enter_Com_RxSigGwMcLockProtArea

                    Com_Lok_PackRxGrpSigGwBufferData(RxGrpSigConstPtr,l_TxGwDestId);

                    Com_Get_SchM_Exit_Com_RxSigGwMcLockProtArea
                    GwMapGrpSigIdConfigPtr++;
                }
                RxGrpSigConstPtr++;
            }
        }
        RxSigGrpConstPtr++;
        RxSigGrpRamPtr++;
   }
}

#endif

#endif

