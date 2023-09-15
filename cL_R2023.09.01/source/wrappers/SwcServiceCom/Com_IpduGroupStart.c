

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

LOCAL_INLINE void Com_RxIPduStart(Com_IpduIdType IpduId, boolean Initialize);

LOCAL_INLINE void Com_TxIPduStart(Com_IpduIdType IpduId, boolean Initialize);

LOCAL_INLINE void Com_Lok_ProcessIPduGroupVector(const uint8 * ipduGroupVector);

#if defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit) || (defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))
LOCAL_INLINE void Com_Lok_UpdateBitAndFilter(Com_IpduIdType IpduId);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize)
{
   Com_RxIpduRamPtrType        RxIpduRamPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   uint16_least                idx_IpduId_u16;

# if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr((ipduGroupVector == NULL_PTR), COMServiceId_IpduGroupControl))
# endif
   {

        Com_ReceptionDMControl(ipduGroupVector);

        Com_Lok_ProcessIPduGroupVector((const uint8 * )ipduGroupVector);

        RxIpduRamPtr     = &COM_GET_RXPDURAM_S(0);

        for(idx_IpduId_u16 = COM_ZERO; idx_IpduId_u16 < COM_GET_NUM_RX_IPDU; idx_IpduId_u16++)
        {

            if(COM_GET_IPDUCOUNTER_S(idx_IpduId_u16) > COM_ZERO)
            {

                if(Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIpduRamPtr->RxFlags) == COM_STOP)
                {
                    Com_RxIPduStart((Com_IpduIdType)idx_IpduId_u16,initialize);

                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIpduRamPtr->RxFlags,COM_START);
                }
            }
            else{

                if(Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIpduRamPtr->RxFlags))
                {
                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIpduRamPtr->RxFlags,COM_STOP);

#ifdef COM_RX_MAINFUNCTION_PROC
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);
#endif

#ifdef COM_TP_IPDUTYPE
                    Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIpduRamPtr->RxFlags,COM_FALSE);
#endif
                }
            }

            RxIpduRamPtr++;
        }

        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

        for(idx_IpduId_u16 = COM_ZERO; idx_IpduId_u16 < COM_GET_NUM_TX_IPDU; idx_IpduId_u16++)
        {

            if(COM_GET_IPDUCOUNTER_S(idx_IpduId_u16 + COM_GET_NUM_RX_IPDU) > COM_ZERO)
            {

                if(Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags) == COM_STOP)
                {

                    Com_TxIPduStart((Com_IpduIdType)idx_IpduId_u16,initialize);

                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags,COM_START);
                }
            }
            else{

                if(Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags))
                {

                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags,COM_STOP);

                    Com_TxIPduStop((Com_IpduIdType)idx_IpduId_u16);
                }
            }

            TxIpduRamPtr++;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE void Com_Lok_ProcessIPduGroupVector(const uint8 * ipduGroupVector)
{
   const Com_IpduIdType *      IPduRefPtr;
   Com_IPduGrpConstPtrType     IPduGrpConstPtr;
   uint16_least                index_u16;
   uint16_least                numOfPdus_u16;
   Com_IpduGroupIdType         IpduGrpId_u16;
   uint8                       ByteVal_u8;
   uint8                       BitOffset_u8;
   uint8                       PduCounterVal;

   for(index_u16 = COM_ZERO; index_u16 < COM_NUM_ARR_IPDUGRPVECT; index_u16++)
   {
        if(Com_IpduGrpVector[index_u16] != ipduGroupVector[index_u16])
        {

            ByteVal_u8   = (uint8)(Com_IpduGrpVector[index_u16] ^ ipduGroupVector[index_u16]);
            BitOffset_u8 = COM_ZERO;

            do
            {

                if(COM_RESET != (ByteVal_u8 & COM_ONE))
                {

                    IpduGrpId_u16   = (8u * (uint16)index_u16) + BitOffset_u8;

                    IpduGrpId_u16   = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                    PduCounterVal   = ((((ipduGroupVector[index_u16] >> BitOffset_u8) & COM_ONE) != COM_ZERO) ?
                                                                                            (0x01u) : (0xFFu));

                    IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);
                    IPduRefPtr      = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);

                    if(IpduGrpId_u16 != (COM_GET_NUM_TOTAL_IPDU_GRP - COM_ONE))
                    {

                        numOfPdus_u16 = (IPduGrpConstPtr + COM_ONE)->FirstIpdu_Index - IPduGrpConstPtr->FirstIpdu_Index;
                    }
                    else
                    {

                        numOfPdus_u16 = COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP;
                    }

                    while(numOfPdus_u16 > COM_ZERO)
                    {

                         COM_GET_IPDUCOUNTER_S(*IPduRefPtr) = (uint8)
                        (COM_GET_IPDUCOUNTER_S(*IPduRefPtr) + PduCounterVal);

                        IPduRefPtr++;
                        numOfPdus_u16--;

                    }

                }

                BitOffset_u8++;
                ByteVal_u8 >>= COM_ONE;

            }while(ByteVal_u8 > COM_ZERO);

            Com_IpduGrpVector[index_u16] = ipduGroupVector[index_u16];

        }

   }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector)
{
# if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr( (ipduGroupVector == NULL_PTR), COMServiceId_ClearIpduGroupVector ))
# endif
   {
        uint16_least   index_u16;

        for(index_u16 = COM_ZERO; index_u16 < COM_NUM_ARR_IPDUGRPVECT; index_u16++)
        {
            ipduGroupVector[index_u16] = COM_ZERO;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType IpduGroupId, boolean bitval)
{
# if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr( (IpduGroupId >= COM_GET_NUM_TOTAL_IPDU_GRP),(ipduGroupVector == NULL_PTR)
   ,                                    COMServiceId_SetIpduGroup))
# endif
   {
        uint16      index_u16;
        uint8       BitOffset_u8;

        index_u16     = (uint16)(IpduGroupId >> 3u);
        BitOffset_u8  = (uint8) (IpduGroupId % 8u);

        if(bitval)
        {
            ipduGroupVector[index_u16] |= ((uint8)(COM_ONE << BitOffset_u8));
        }
        else{
            ipduGroupVector[index_u16] &= ((uint8)(~(COM_ONE << BitOffset_u8)));
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE void Com_TxIPduStart(Com_IpduIdType IpduId, boolean Initialize)
{
#if defined(COM_TxIPduTimeOut) || defined(COM_TX_IPDUCOUNTER)
   Com_TxIpduConstPtrType      TxIpduConstPtr;
#endif
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   uint8                       LatestTransMode_u8;

#if defined(COM_TxIPduTimeOut) || defined(COM_TX_IPDUCOUNTER)
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
#endif
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

   if(Initialize != COM_FALSE)
   {
#if defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit) || (defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))

        Com_Lok_UpdateBitAndFilter(IpduId);
#endif

        Com_TxChangeMode(IpduId);

        LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);

        Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

        if( COM_TX_MODE_IS_CYCLIC(LatestTransMode_u8) )
        {

            TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEOFFSET(IpduId, TxIpduRamPtr->CurrentTxModePtr);
        }

        TxIpduRamPtr->Com_MinDelayTick = COM_ZERO;

#ifdef COM_TxIPduTimeOut
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIpduConstPtr->txIPduFields))
        {

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIpduConstPtr->Timeout_Fact;
        }
        else
#endif
        {
#ifdef COM_TxIPduTimeOut

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

            TxIpduRamPtr->Com_TickTxTimeout = COM_ZERO;
#endif
            Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
   }
   else{

        Com_TxChangeMode((Com_IpduIdType)IpduId);

#ifdef COM_TxIPduTimeOut
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIpduConstPtr->txIPduFields))
        {
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIpduConstPtr->Timeout_Fact;
        }
#endif
   }

#ifdef COM_TX_IPDUCOUNTER

   if(TxIpduConstPtr->TxIpduCntr_Index != COM_TXIPDU_CNTR_INV_IDX)
   {

        SchM_Enter_Com_TxIpduProtArea(IPDUGROUPSTART);

        Com_Lok_TxIpduInitializeCounter( (PduIdType)IpduId );

        SchM_Exit_Com_TxIpduProtArea(IPDUGROUPSTART);
   }
   else{

   }
#endif

#ifdef COM_TP_IPDUTYPE

   Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif
}

LOCAL_INLINE void Com_RxIPduStart(Com_IpduIdType IpduId, boolean Initialize)
{
#if(defined(COM_RxFilters) && defined(COM_F_ONEEVERYN))
   Com_RxIpduConstPtrType          RxIpduConstPtr;
   Com_RxSigConstPtrType           RxSigConstPtr;
   uint16_least                    index_u16;
# ifdef COM_RX_SIGNALGROUP
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   uint16_least                    idx_GrpSig_u16;
# endif

    RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(IpduId);

# ifdef COM_RX_SIGNALGROUP
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIpduConstPtr->FirstRxSigGrp_Index);

   for(index_u16 = RxIpduConstPtr->No_Of_SigGrp_Ref; index_u16 != COM_ZERO; index_u16--)
   {
        if(Com_GetValue(RXSIGGRP,_FILTEREVALREQ,RxSigGrpConstPtr->rxSignalGrpFields))
        {
            RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

            for(idx_GrpSig_u16 = RxSigGrpConstPtr->No_Of_GrpSig; idx_GrpSig_u16 != COM_ZERO; idx_GrpSig_u16--)
            {
                if(RxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N)
                {

                    COM_GET_ONEEVERYN(RxGrpSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
                }
                RxGrpSigConstPtr++;
            }
        }
        RxSigGrpConstPtr++;
   }
# endif

    RxSigConstPtr  = COM_GET_RXSIG_CONSTDATA(RxIpduConstPtr->RxSigId_Index);

   for(index_u16 = RxIpduConstPtr->No_Of_Sig_Ref; index_u16 != COM_ZERO; index_u16--)
   {
        if(Com_GetValue(RXSIG,_FILTRALG,RxSigConstPtr->rxSignalFields) == (uint8)COM_ONE_EVERY_N)
        {

            COM_GET_ONEEVERYN(RxSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
        }
        RxSigConstPtr++;
   }

#else

    (void)IpduId;
#endif

    (void)Initialize;

#ifdef COM_RX_IPDUCOUNTER

   Com_SetRamValue(RXIPDU,_IS_FIRST_RECEPTION,COM_GET_RXPDURAM_S(IpduId).RxFlags,COM_TRUE);
#endif
}

#if defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit) || (defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))

LOCAL_INLINE void Com_Lok_UpdateBitAndFilter(Com_IpduIdType IpduId)
{

   Com_TxIpduConstPtrType          TxIpduConstPtr;
#if defined(COM_TxSigUpdateBit) || (defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))
   Com_TxSigConstPtrType           TxSigConstPtr;
#endif

#if defined(COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined(COM_F_ONEEVERYN)
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
#endif

#if defined(COM_TxSigGrpUpdateBit) || \
    (defined(COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
   uint16_least                    idx_SigGrp_u16;
#endif

   uint16_least                    idx_Sig_u16;

#if defined (COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
   PduLengthType                   ByteNo_uo;
#endif

    TxIpduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(IpduId);

#if defined(COM_TxSigUpdateBit) || (defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))

    TxSigConstPtr    = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);

   for(idx_Sig_u16 = TxIpduConstPtr->No_Of_Sig_Ref; idx_Sig_u16 > COM_ZERO; idx_Sig_u16--)
   {

# ifdef COM_TxSigUpdateBit

        if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
        {

            ByteNo_uo = (PduLengthType)((TxSigConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_uo)
        }
# endif

# if defined(COM_TxFilters) && defined(COM_F_ONEEVERYN)

        if(Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields) == (uint16)COM_ONE_EVERY_N)
        {
            COM_GET_ONEEVERYN(TxSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
        }
# endif

        TxSigConstPtr++;
   }

#endif

#if defined(COM_TxSigGrpUpdateBit) || \
    (defined(COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))

    TxSigGrpConstPtr   = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);

   for(idx_SigGrp_u16 = TxIpduConstPtr->No_Of_SigGrp_Ref; idx_SigGrp_u16 > COM_ZERO; idx_SigGrp_u16--)
   {

# if(defined(COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined(COM_F_ONEEVERYN))

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

        for(idx_Sig_u16 = TxSigGrpConstPtr->No_Of_GrpSig; idx_Sig_u16 > COM_ZERO; idx_Sig_u16--)
        {

            if(TxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N)
            {
                COM_GET_ONEEVERYN(TxGrpSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
            }
            TxGrpSigConstPtr++;
        }
# endif

# ifdef COM_TxSigGrpUpdateBit

        if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
        {

            ByteNo_uo = (PduLengthType)((TxSigGrpConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr,TxSigGrpConstPtr->Update_Bit_Pos,ByteNo_uo)
        }
# endif

        TxSigGrpConstPtr++;
   }
#endif
}

#endif

