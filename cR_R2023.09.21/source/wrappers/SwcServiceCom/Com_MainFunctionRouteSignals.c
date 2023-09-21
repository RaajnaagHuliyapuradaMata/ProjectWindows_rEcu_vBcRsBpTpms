#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
static INLINE FUNC(Std_ReturnType, COM_CODE) Com_ReadSigGwReceiveQueue(Type_SwcServiceCom_tIdPdu*             ComRxPduId
   ,     Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux);

LOCAL_INLINE FUNC(void,COM_CODE)    Com_Lok_PrepareTxIpdu(void);

LOCAL_INLINE FUNC(void, COM_CODE)   Com_Lok_ReadRxQueueAndProcess(void);

#ifdef COM_SIGNALGATEWAY
LOCAL_INLINE FUNC(void, COM_CODE)   Com_Lok_ProcessRxSignalGateway(Com_RxIpduConstPtrType RxIPduConstPtr);
#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
LOCAL_INLINE FUNC(void, COM_CODE)   Com_Lok_ProcessRxSigGrpGateway(Com_RxIpduConstPtrType RxIPduConstPtr);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void)
{

   if(
#if(COM_CONFIGURATION_USE_DET == STD_ON)

        Com_Lok_DETCheck_Void(COMServiceId_MainFunctionRouteSignals)
#else
        (Com_Uninit_Flag == COM_INIT)
#endif
    )
   {

        Com_Lok_ReadRxQueueAndProcess();

        Com_Lok_PrepareTxIpdu();
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(Std_ReturnType, COM_CODE) Com_WriteSigGwReceiveQueue( Type_SwcServiceCom_tIdPdu ComRxPduId)
{

   Com_RxGwQueuePtrType l_RxGwQueuePtr_struc;
   uint8 Status;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    Status = E_OK;

    l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux] = ComRxPduId;

    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = ( Com_RxGwQueueIndexType )
                                                  ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux + 1 ) %
                                                    ( COM_GET_NUM_GWSRC_IPDUS + 1u ) );

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(COM_FALSE == (Com_Lok_DETCheck_Param_Only((
                      ((l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux) % (COM_GET_NUM_GWSRC_IPDUS+1u)) ==
                       (l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)), COMServiceId_MainFunctionRouteSignals)))
   {

        Status = E_NOT_OK;
   }
#endif

    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

static INLINE FUNC(Std_ReturnType, COM_CODE) Com_ReadSigGwReceiveQueue( Type_SwcServiceCom_tIdPdu*             ComRxPduId
   ,     Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux)
{
   Com_RxGwQueuePtrType l_RxGwQueuePtr_struc;
    Std_ReturnType       retVal_uo;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    retVal_uo            = E_NOT_OK;

   if(l_Com_RxGwQueueWrite_ux != l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)
   {

        *ComRxPduId = l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux];

        l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux = ( Com_RxGwQueueIndexType )
                                                     ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux + 1 ) %
                                                       ( COM_GET_NUM_GWSRC_IPDUS + 1u ) );
        retVal_uo = E_OK;
   }

    return(retVal_uo);
}

LOCAL_INLINE FUNC(void,COM_CODE) Com_Lok_PrepareTxIpdu(void){

   Com_TxIpduConstPtrType       TxIPduConstPtr;
   Com_TxIpduRamPtrType         TxIpduRamPtr;
   VAR(uint16_least, AUTOMATIC) Index_ui;
#if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP)
   Com_TxSigGrpRamPtrType       TxSigGrpRamPtr;
   VAR(uint16_least, AUTOMATIC) Idx_SigGrp_ui;
   VAR(uint16_least, AUTOMATIC) limit_siggrp_ui;
#endif
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

   for(Index_ui = COM_ZERO; Index_ui < CfgSwcServiceCom_dNumIPduTx; Index_ui++)
   {

        if((Com_GetValue(TXIPDU,_ISGWPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE) &&
           (Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)Index_ui)))
        {

#if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP)
            limit_siggrp_ui  = (uint32)TxIPduConstPtr->FirstTxSigGrp_Index +
                               (uint32)TxIPduConstPtr->No_Of_SigGrp_Ref;

            TxSigGrpRamPtr   = &COM_GET_TXSIGGRPFLAG(TxIPduConstPtr->FirstTxSigGrp_Index);

            for( Idx_SigGrp_ui = (uint32)TxIPduConstPtr->FirstTxSigGrp_Index;
                 Idx_SigGrp_ui < limit_siggrp_ui;
                 Idx_SigGrp_ui++)
            {

                if(Com_GetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr ->txSigGrpRAMFields) == COM_TRUE)
                {

                    Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr ->txSigGrpRAMFields,COM_FALSE);

                    (void)Com_InternalSendSignalGroup( (Com_SignalGroupIdType)Idx_SigGrp_ui );
                }
                TxSigGrpRamPtr++;
            }
#endif

            if(((Com_GetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags) != COM_FALSE) &&
                (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) <= COM_TXMODE_MIXED))
#ifdef COM_TxFilters
                || (Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags) != COM_FALSE)
#endif
            )
            {

                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                sendIpduFlag_u16.sigTransProp =
                      COM_BOOL_TO_UNSIGNED(Com_GetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags));

                Com_SetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxFilters
                sendIpduFlag_u16.isModeChangd =
                            COM_BOOL_TO_UNSIGNED(Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags));

                Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

                sendIpduFlag_u16.isEventTrig      = COM_SET;

                sendIpduFlag_u16.isGwIpduSend     = COM_SET;

#ifdef COM_TxIPduTimeOut

                if(Com_GetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags)== COM_TRUE)
                {
                    sendIpduFlag_u16.isTimeoutReq = COM_SET;

                    Com_SetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                }
#endif

                Com_Lok_SendIpdu((Type_SwcServiceCom_tIdPdu)Index_ui, sendIpduFlag_u16);
            }
        }

        TxIPduConstPtr++;
        TxIpduRamPtr++;
   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ReadRxQueueAndProcess(void){

   Com_RxGwQueuePtrType    RxGwQueuePtr_l;
   Com_RxGwQueueIndexType  l_Com_RxGwQueueWrite_ux;
   Type_SwcServiceCom_tIdPdu               l_Ipduid;
   uint8                   l_IpduSyncCounter;

    RxGwQueuePtr_l          = COM_GET_RXGWQUEUE_S;

    l_Com_RxGwQueueWrite_ux = RxGwQueuePtr_l->Com_RxGwQueueWrite_ux;
   {

        while(Com_ReadSigGwReceiveQueue(&l_Ipduid,l_Com_RxGwQueueWrite_ux) == (Std_ReturnType)E_OK)
        {

            l_IpduSyncCounter = COM_ZERO;

            do
            {
                Com_RxIpduConstPtrType RxIPduConstPtr;

                SchM_Enter_Com_RxSigGwQueueProtArea();

                Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(l_Ipduid).RxFlags,COM_FALSE);
                SchM_Exit_Com_RxSigGwQueueProtArea();

                RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(l_Ipduid);
#ifdef COM_SIGNALGATEWAY
                if(RxIPduConstPtr->numOfGwSrcSignals > COM_ZERO)
                {

                    Com_Lok_ProcessRxSignalGateway(RxIPduConstPtr);
                }
#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
                if(RxIPduConstPtr->numOfGwSrcSignalGrps > COM_ZERO)
                {

                    Com_Lok_ProcessRxSigGrpGateway(RxIPduConstPtr);
                }
#endif

                l_IpduSyncCounter =
                 ((Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(l_Ipduid).RxFlags) == COM_TRUE) ?
                         ((l_IpduSyncCounter+1) % (COM_MAXIMUM_GWSYNC_REPITIONS+1)) : (COM_ZERO));
            }while(l_IpduSyncCounter != COM_ZERO);
        }
   }
}

#ifdef COM_SIGNALGATEWAY

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessRxSignalGateway(Com_RxIpduConstPtrType RxIPduConstPtr)
{

   Com_GwMapSigConfPtrType          ComGwMapSigConfPtr;
   Com_GwMapSigIdConfPtrType        ComGwMapSigIdConfPtr;
   Com_RxSigRamPtrType              RxSigRamPtr;
   Com_RxSigConstPtrType            RxSigConstPtr;
   Com_SignalIdType                 l_TxGwDestId;
   VAR(Com_SignalIdType, AUTOMATIC) SigId_u32;
   VAR(uint16_least, AUTOMATIC)     limit_ui;
   VAR(uint16_least, AUTOMATIC)     loopIndex_ui;

    limit_ui      = (uint32)RxIPduConstPtr->RxSigId_Index + (uint32)RxIPduConstPtr->numOfGwSrcSignals;
    RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

   for(SigId_u32 = RxIPduConstPtr->RxSigId_Index; SigId_u32 < limit_ui; SigId_u32++)
   {

        if(Com_GetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields) != COM_FALSE)
        {
            ComGwMapSigConfPtr   = COM_GET_GWSIG_CONSTDATA(SigId_u32);
            ComGwMapSigIdConfPtr = COM_GET_GWSIGIDMAP_CONSTDATA(ComGwMapSigConfPtr->indexGwMapSigDestIdArray);

            for(loopIndex_ui = COM_ZERO; loopIndex_ui < ComGwMapSigConfPtr->destCount; loopIndex_ui++)
            {
                l_TxGwDestId = ComGwMapSigIdConfPtr->GwMap_DestId;

                Com_Lok_PackRxSignalGwBufferData(RxSigConstPtr,l_TxGwDestId);

                ComGwMapSigIdConfPtr++;
            }

            Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_FALSE);
        }
        RxSigRamPtr++;
        RxSigConstPtr++;
   }
}

#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessRxSigGrpGateway(Com_RxIpduConstPtrType RxIPduConstPtr)
{

   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   Com_GwMapGrpSigConfPtrType      GwMapGrpSigConfigPtr;
   Com_GwMapGrpSigIdConfPtrType    GwMapGrpSigIdConfigPtr;
   Com_TxIntGrpSignalIdType        l_TxGwDestId;
   VAR(Com_TxIntGrpSignalIdType, AUTOMATIC) SigGrp_u32;
   VAR(uint16_least, AUTOMATIC)    Idx_GrpSig_ui;
   VAR(uint16_least, AUTOMATIC)    limit_grpsig_ui;
   VAR(uint16_least, AUTOMATIC)    limit_ui;
   VAR(uint16_least, AUTOMATIC)    loopIndex_ui;

    RxSigGrpConstPtr    = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

    RxSigGrpRamPtr      =  &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
    limit_ui            = (uint32)RxIPduConstPtr->FirstRxSigGrp_Index +(uint32)RxIPduConstPtr->numOfGwSrcSignalGrps;

   for(SigGrp_u32 = RxIPduConstPtr->FirstRxSigGrp_Index; SigGrp_u32 < limit_ui; SigGrp_u32++)
   {

        if(Com_GetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr ->rxSigGrpRAMFields) != COM_FALSE)
        {

            RxGrpSigConstPtr    = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

            limit_grpsig_ui     = RxSigGrpConstPtr->FirstGrpSig_Index + RxSigGrpConstPtr->numOfGwSrcGrpSignals;

            for(Idx_GrpSig_ui = (uint32)RxSigGrpConstPtr->FirstGrpSig_Index;Idx_GrpSig_ui < limit_grpsig_ui;Idx_GrpSig_ui++)
            {

                GwMapGrpSigConfigPtr = COM_GET_GWGRPSIG_CONSTDATA((Idx_GrpSig_ui - COM_GET_NUM_GRPSIG_NOGW));
                GwMapGrpSigIdConfigPtr =
                             COM_GET_GWGRPSIGIDMAP_CONSTDATA(GwMapGrpSigConfigPtr->indexGwMapGrpSigDestIdArray);

                for(loopIndex_ui = COM_ZERO; loopIndex_ui < GwMapGrpSigConfigPtr->destCount; loopIndex_ui++)
                {
                    l_TxGwDestId = GwMapGrpSigIdConfigPtr->GwMap_DestGrpSigId;

                    SchM_Enter_Com_RxSigGwMcLockProtArea();
                    Com_Lok_PackRxGrpSigGwBufferData(RxGrpSigConstPtr,l_TxGwDestId);
                    SchM_Exit_Com_RxSigGwMcLockProtArea();
                    GwMapGrpSigIdConfigPtr++;
                }
                RxGrpSigConstPtr++;
            }

            Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);
        }
        RxSigGrpConstPtr++;
        RxSigGrpRamPtr++;
   }
}

#endif

#endif

