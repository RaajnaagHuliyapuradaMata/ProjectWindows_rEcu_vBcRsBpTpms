#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

static INLINE FUNC(void, COM_CODE) Com_RxIPduStart( VAR(Com_IpduIdType, AUTOMATIC)  IpduId
   ,     VAR(boolean, AUTOMATIC)         Initialize );

static INLINE FUNC(void, COM_CODE) Com_TxIPduStart( VAR(Com_IpduIdType, AUTOMATIC)  IpduId
   ,     VAR(boolean, AUTOMATIC)         Initialize );

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessIPduGroupVector(
                                                    P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
                                                            );

LOCAL_INLINE FUNC(void, COM_CODE)  Com_Lok_UpdateBitAndFilter(VAR(Com_IpduIdType, AUTOMATIC) IpduId);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_IpduGroupControl(
                                VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector
   ,     VAR(boolean, AUTOMATIC)              initialize
                                         )
{
   Com_RxIpduRamPtrType            RxIPduRamPtr;
   Com_TxIpduRamPtrType            TxIPduRamPtr;
   VAR(uint16_least,AUTOMATIC)     Index_u16;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr((ipduGroupVector == NULL_PTR), COMServiceId_IpduGroupControl))
#endif
   {

        Com_ReceptionDMControl(ipduGroupVector);

        Com_Lok_ProcessIPduGroupVector((P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))ipduGroupVector);

        RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);
        for(Index_u16 = 0; Index_u16 < COM_GET_NUM_RX_IPDU; Index_u16++)
        {

            if(COM_GET_IPDUCOUNTER_S(Index_u16) > 0)
            {

                if(Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags) == COM_STOP)
                {
                    Com_RxIPduStart((Com_IpduIdType)Index_u16,initialize);

                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags,COM_START);
                }
            }
            else{

                if(Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags))
                {
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr->RxFlags,COM_FALSE);

                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags,COM_STOP);

                    Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr->RxFlags,COM_FALSE);
                }
            }

            RxIPduRamPtr++;
        }

        TxIPduRamPtr   = &COM_GET_TXPDURAM_S(0);
        for(Index_u16 = 0; Index_u16 < COM_GET_NUM_TX_IPDU; Index_u16++)
        {

            if(COM_GET_IPDUCOUNTER_S(Index_u16 + COM_GET_NUM_RX_IPDU) > 0)
            {

                if(Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr->Com_TxFlags) == COM_STOP)
                {

                    Com_TxIPduStart((Com_IpduIdType)Index_u16,initialize);

                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr->Com_TxFlags,COM_START);

                    Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr->Com_TxFlags,COM_FALSE);
                }
            }
            else{

                if(Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr->Com_TxFlags))
                {

                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr->Com_TxFlags,COM_STOP);
                    Com_TxIPduStop((Com_IpduIdType)Index_u16);
                }
            }

            TxIPduRamPtr++;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessIPduGroupVector(
                                            P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
                                                            )
{
   P2CONST(Com_IpduIdType,AUTOMATIC,COM_APPL_CONST)    IPduRefPtr;
   Com_IPduGrpConstPtrType                             IPduGrpConstPtr;
   VAR(uint16,AUTOMATIC)                               Index_u16;
   VAR(uint16,AUTOMATIC)                               NoOfPdus_u16;
   VAR(Com_IpduGroupIdType,AUTOMATIC)                  IpduGrpId_u16;
   VAR(uint8,AUTOMATIC)                                ByteVal_u8;
   VAR(uint8,AUTOMATIC)                                BitOffset_u8;
   VAR(uint8,AUTOMATIC)                                PduCounterVal;

   for(Index_u16 = 0; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
   {
        if(Com_IpduGrpVector[Index_u16] != ipduGroupVector[Index_u16])
        {

            ByteVal_u8   = (uint8)(Com_IpduGrpVector[Index_u16] ^ ipduGroupVector[Index_u16]);
            BitOffset_u8 = 0u;

            do
            {

                if(COM_RESET != (ByteVal_u8 & 1u))
                {

                    IpduGrpId_u16   = (8u * Index_u16) + BitOffset_u8;

                    IpduGrpId_u16   = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                    PduCounterVal   = ((((ipduGroupVector[Index_u16] >> BitOffset_u8) & 1u) != 0u) ? (0x1u) : (0xFFu));

                    IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);
                    IPduRefPtr      = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);

                    NoOfPdus_u16 =  (IpduGrpId_u16 != (COM_GET_NUM_TOTAL_IPDU_GRP - 1u)) ?
                                    ((IPduGrpConstPtr + 1)->FirstIpdu_Index - IPduGrpConstPtr->FirstIpdu_Index) :
                                    (COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP);

                    while(NoOfPdus_u16 > 0u)
                    {

                         COM_GET_IPDUCOUNTER_S(*IPduRefPtr) = (uint8)
                        (COM_GET_IPDUCOUNTER_S(*IPduRefPtr) + PduCounterVal);

                        IPduRefPtr++;
                        NoOfPdus_u16--;

                    }

                }

                BitOffset_u8++;
                ByteVal_u8 >>= 1u;

            }while(ByteVal_u8 > 0u);

            Com_IpduGrpVector[Index_u16] = ipduGroupVector[Index_u16];

        }

   }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_ClearIpduGroupVector( VAR(Com_IpduGroupVector, AUTOMATIC) ipduGroupVector )
{
#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr( (ipduGroupVector == NULL_PTR), COMServiceId_ClearIpduGroupVector ))
#endif
   {
        VAR(uint16, AUTOMATIC) Index_u16;

        for(Index_u16 = 0u; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
        {
            ipduGroupVector[Index_u16] = (uint8)0;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_SetIpduGroup(
                            VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector
   ,     VAR(Com_IpduGroupIdType, AUTOMATIC)  IpduGroupId
   ,     VAR(boolean, AUTOMATIC)              bitval
                                     )
{
#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr( (IpduGroupId >= COM_GET_NUM_TOTAL_IPDU_GRP),(ipduGroupVector == NULL_PTR)
   ,     COMServiceId_SetIpduGroup))
#endif
   {
        VAR(uint16, AUTOMATIC)   Index_u16;
        VAR(uint8, AUTOMATIC)    BitOffset_u8;

        Index_u16     = (uint16)(IpduGroupId >> 3u);
        BitOffset_u8  = (uint8) (IpduGroupId % 8u);

        if(bitval)
        {
            ipduGroupVector[Index_u16] |= ((uint8)(1u << BitOffset_u8));
        }
        else{
            ipduGroupVector[Index_u16] &= ((uint8)(~(1u << BitOffset_u8)));
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

static INLINE FUNC(void, COM_CODE) Com_TxIPduStart(VAR(Com_IpduIdType, AUTOMATIC) IpduId
   ,     VAR(boolean, AUTOMATIC) Initialize)
{

   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;

   VAR(uint8, AUTOMATIC)   LatestTransMode_u8;

   if(Initialize != COM_FALSE)
   {
        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

        Com_Lok_UpdateBitAndFilter(IpduId);

        Com_TxChangeMode(IpduId);

        LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);

        Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

        if( COM_RESET != ( LatestTransMode_u8 & COM_TXMODE_MIXED ) )
        {

#ifdef COM_TXPDU_TIMEOFFSET_VIA_CALIBRATION
            TxIpduRamPtr->Com_Tick_Tx = Com_GetTxIPduTimeOffsetCalibration((Type_SwcServiceCom_tIdPdu)IpduId);
#else

            TxIpduRamPtr->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimeOffsetFact;

#endif

        }

        TxIpduRamPtr->Com_MinDelayTick = 0;

        Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

#ifdef COM_TxIPduTimeOut
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIPduConstPtr->txIPduFields))
        {
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
        }
        else
#endif
        {

#ifdef COM_TxIPduTimeOut
            TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif
            Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
   }
   else{

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

#ifdef COM_TxIPduTimeOut
        TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId);
#endif

        Com_TxChangeMode((Com_IpduIdType)IpduId);

#ifdef COM_TxIPduTimeOut
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIPduConstPtr->txIPduFields))
        {
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
        }
#endif
   }
}

static INLINE FUNC(void, COM_CODE) Com_RxIPduStart(
                                            VAR(Com_IpduIdType, AUTOMATIC)  IpduId
   ,     VAR(boolean, AUTOMATIC)         Initialize
                                                  )
{
#if(defined(COM_RxFilters) && defined(COM_F_ONEEVERYN))
   Com_RxIpduConstPtrType           RxIPduConstPtr;
   Com_RxSigConstPtrType            RxSigConstPtr;
   VAR(uint16_least, AUTOMATIC)     Idx_Sig_Grp_ui;
# ifdef COM_RX_SIGNALGROUP
   Com_RxSigGrpConstPtrType         RxSigGrpConstPtr;
   Com_RxGrpSigConstPtrType         RxGrpSigConstPtr;
   VAR(uint16_least, AUTOMATIC)     Idx_GrpSig_ui;
# endif

    RxIPduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(IpduId);

# ifdef COM_RX_SIGNALGROUP
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

   for(Idx_Sig_Grp_ui = (uint16_least)RxIPduConstPtr->No_Of_SigGrp_Ref; Idx_Sig_Grp_ui != 0u; Idx_Sig_Grp_ui--)
   {
        if(Com_GetValue(RXSIGGRP,_FILTEREVALREQ,RxSigGrpConstPtr->rxSignalGrpFields))
        {
            RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

            for(Idx_GrpSig_ui = (uint16_least)RxSigGrpConstPtr->No_Of_GrpSig; Idx_GrpSig_ui != 0u; Idx_GrpSig_ui--)
            {
                if(RxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N)
                {

                    COM_GET_ONEEVERYN(RxGrpSigConstPtr->Filter_Index).Occurrence = 0;
                }
                RxGrpSigConstPtr++;
            }
        }
        RxSigGrpConstPtr++;
   }
# endif

    RxSigConstPtr    = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

   for(Idx_Sig_Grp_ui = (uint16_least)RxIPduConstPtr->No_Of_Sig_Ref; Idx_Sig_Grp_ui != 0u; Idx_Sig_Grp_ui--)
   {
        if(Com_GetValue(RXSIG,_FILTRALG,RxSigConstPtr->rxSignalFields) == (uint8)COM_ONE_EVERY_N)
        {

            COM_GET_ONEEVERYN(RxSigConstPtr->Filter_Index).Occurrence = 0;
        }
        RxSigConstPtr++;
   }

#else

    (void)IpduId;
#endif

    (void)Initialize;
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_UpdateBitAndFilter(VAR(Com_IpduIdType, AUTOMATIC) IpduId)
{

   Com_TxSigConstPtrType   TxSigConstPtr;
   Com_TxIpduConstPtrType  TxIPduConstPtr;

   VAR(uint16_least, AUTOMATIC) Index_Sig_ui;
#ifdef COM_TX_SIGNALGROUP
   Com_TxSigGrpConstPtrType     TxSigGrpConstPtr;
   VAR(uint16_least, AUTOMATIC) Index_SigGrp_ui;
#endif

#if defined (COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined (COM_F_ONEEVERYN)
   Com_TxGrpSigConstPtrType      TxGrpSigConstPtr;
#endif

#if defined (COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo_u8;
   VAR(uint8, AUTOMATIC)         ConstByteValue_u8;
#endif

    TxIPduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

   for(Index_Sig_ui = TxIPduConstPtr->No_Of_Sig_Ref;Index_Sig_ui != 0u;Index_Sig_ui--)
   {

#ifdef COM_TxSigUpdateBit

        ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;

        if((Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE) &&
           (Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General)))
        {

            ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)((TxSigConstPtr->Update_Bit_Pos)>>3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)
        }
#endif

#ifdef COM_TxFilters
        # ifdef COM_F_ONEEVERYN
        if(Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields) == (uint16)COM_ONE_EVERY_N)
        {
            COM_GET_ONEEVERYN(TxSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
        }
        # endif
#endif

        TxSigConstPtr++;
   }

#ifdef COM_TX_SIGNALGROUP

    TxSigGrpConstPtr   = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

   for(Index_SigGrp_ui=(uint16_least)TxIPduConstPtr ->No_Of_SigGrp_Ref;Index_SigGrp_ui != 0u;Index_SigGrp_ui--)
   {

        # if defined(COM_TxFilters) && defined (COM_F_ONEEVERYN)

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr ->FirstGrpSig_Index);

        for(Index_Sig_ui = TxSigGrpConstPtr ->No_Of_GrpSig;Index_Sig_ui !=0u;Index_Sig_ui--)
        {

            if( TxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N)
            {
                COM_GET_ONEEVERYN(TxGrpSigConstPtr->Filter_Index).Occurrence = COM_ZERO;
            }
            TxGrpSigConstPtr++;
        }
        # endif

        # ifdef COM_TxSigGrpUpdateBit

        ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;

        if((Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE) &&
           (Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields)))
        {

            ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)((TxSigGrpConstPtr ->Update_Bit_Pos)>>3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigGrpConstPtr ->Update_Bit_Pos,ByteNo_u8)
        }
        # endif

        TxSigGrpConstPtr++;
   }
#endif
}

