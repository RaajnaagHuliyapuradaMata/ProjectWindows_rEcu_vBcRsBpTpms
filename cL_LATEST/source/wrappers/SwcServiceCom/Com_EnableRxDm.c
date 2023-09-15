

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if(COM_ENABLE_JITTERFLITER == STD_ON)
#define COM_RXTIMER_MAX_DUALCYCLE              (COM_RXTIMER_MAX - 2u)
#else
#define COM_RXTIMER_MAX_DUALCYCLE              (COM_RXTIMER_MAX - 1u)
#endif

#if(((COM_CONFIGURATION_VARIANT == COM_VARIANT_PRE_COMPILE) && (COM_NUM_TOTAL_IPDU_GRP % 8u != 0)) || \
     (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE))
#define COM_ENABLE_CLEAR_UNUSED_BITS
#endif

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

LOCAL_INLINE void Com_Lok_ProcessRxDMIPduGroupVector(const uint8 * ipduGroupVector);

#endif

#ifdef COM_ENABLE_CLEAR_UNUSED_BITS
LOCAL_INLINE void Com_Lok_ClearUnusedBits(Com_IpduGroupVector ipduGroupVector);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector)
{

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
   Com_RxIpduRamPtrType        RxIpduRamPtr;
   uint16_least                idx_IpduId_u16;
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr( (ipduGroupVector == NULL_PTR), COMServiceId_ReceptionDMControl ))
#endif
   {
#ifdef COM_ENABLE_CLEAR_UNUSED_BITS
        Com_Lok_ClearUnusedBits((uint8 *) (ipduGroupVector));
#endif

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

        Com_Lok_ProcessRxDMIPduGroupVector((const uint8 * )(ipduGroupVector));

        RxIpduRamPtr   = &COM_GET_RXPDURAM_S(0);

        for(idx_IpduId_u16 = COM_ZERO; idx_IpduId_u16 < COM_GET_NUM_RX_IPDU; idx_IpduId_u16++)
        {
            if(COM_GET_IPDUCOUNTER_DM(idx_IpduId_u16) > COM_ZERO)
            {

                if((Com_GetRamValue(RXIPDU,_DMSTATUS,RxIpduRamPtr->RxFlags)) == COM_STOP)
                {
                    if(Com_Lok_EnableRxDeadlineMonitoring((Com_IpduIdType)idx_IpduId_u16))
                    {
                        Com_SetRamValue(RXIPDU,_DMSTATUS,RxIpduRamPtr->RxFlags, COM_START);
                    }
                }
            }
            else{
                if(Com_GetRamValue(RXIPDU,_DMSTATUS,RxIpduRamPtr->RxFlags))
                {
                    Com_SetRamValue(RXIPDU,_DMSTATUS,RxIpduRamPtr->RxFlags, COM_STOP);
                }
            }
            RxIpduRamPtr++;
        }
#endif
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_ENABLE_CLEAR_UNUSED_BITS
LOCAL_INLINE void Com_Lok_ClearUnusedBits(Com_IpduGroupVector ipduGroupVector)
{

   uint16  ByteNo_u16;
    ByteNo_u16 = ( uint16 )( COM_GET_NUM_TOTAL_IPDU_GRP / 8u );

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
   if( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
#endif
   {
        ipduGroupVector[ ByteNo_u16 ] &= ( ( uint8 )( 0xFFu ) >> ( 8u - ( COM_GET_NUM_TOTAL_IPDU_GRP % 8u ) ) );

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)

        ByteNo_u16++;
        while( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
        {
            ipduGroupVector[ ByteNo_u16 ] = COM_ZERO;
            ByteNo_u16++;
        }
#endif
   }
}
#endif

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

LOCAL_INLINE void Com_Lok_ProcessRxDMIPduGroupVector(const uint8 * ipduGroupVector)
{

   const Com_IpduIdType *      IPduRefPtr;

   Com_IPduGrpConstPtrType     IPduGrpConstPtr;
   uint16_least                index_u16;
   uint16_least                numOfRxIpdus_u16;
   Com_IpduGroupIdType         IpduGrpId_u16;
   uint8                       ByteVal_u8;
   uint8                       BitOffset_u8;
   uint8                       PduCounterVal;

   for(index_u16 = COM_ZERO; index_u16 < COM_NUM_ARR_IPDUGRPVECT; index_u16++)
   {
        if(Com_IpduGrpVector_DM[index_u16] != ipduGroupVector[index_u16] )
        {

            ByteVal_u8 = (uint8)((Com_IpduGrpVector_DM[index_u16]) ^ (ipduGroupVector[index_u16]));
            BitOffset_u8 = COM_ZERO;

            do
            {

                if(COM_RESET != (ByteVal_u8 & COM_ONE))
                {

                    IpduGrpId_u16   = (Com_IpduGroupIdType)(8u * index_u16)+ BitOffset_u8 ;

                    IpduGrpId_u16   = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                    PduCounterVal   = ((((ipduGroupVector[index_u16] >> BitOffset_u8) & COM_ONE) != COM_ZERO) ?
                                                                                                   (COM_ONE) : (0xFFu));

                    IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);

                    IPduRefPtr      = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);

                    numOfRxIpdus_u16 = IPduGrpConstPtr->NoOfRxPdus;

                    while(numOfRxIpdus_u16 > COM_ZERO)
                    {

                         COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) = (uint8)
                        (COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) + PduCounterVal);

                        IPduRefPtr++;
                        numOfRxIpdus_u16--;
                    }
                }

                BitOffset_u8 ++;
                ByteVal_u8 >>= COM_ONE;

            }while(ByteVal_u8 > COM_ZERO);

            Com_IpduGrpVector_DM[index_u16] = ipduGroupVector[index_u16] ;
        }

   }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

boolean Com_Lok_EnableRxDeadlineMonitoring(Com_IpduIdType IpduId)
{
   Com_RxIpduConstPtrType               RxIpduConstPtr;
#ifdef COM_RxIPduTimeout
   Com_RxIpduRamPtrType                 RxIpduRamPtr;
#endif
#if(defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
   const Com_SignalTimeoutInfo *        SigTimeOutConstPtr;
   uint16 *                             SigTimeOutRamPtr;
   uint16_least                         index_u16;
   uint16_least                         numOfSigWithUpdateBit;
#endif
   boolean                              isRxIpduDmReq_b;

   isRxIpduDmReq_b = COM_FALSE;

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);

#ifdef COM_RxIPduTimeout
    RxIpduRamPtr   = &COM_GET_RXPDURAM_S(IpduId);

   if(RxIpduConstPtr->Timeout_Fact != COM_ZERO)
   {
        isRxIpduDmReq_b = COM_TRUE;
   }

    RxIpduRamPtr->RxTicks_u16 = (RxIpduConstPtr->FirstTimeout_Factor == COM_ZERO) ?
            COM_RXTIMER_MAX : (RxIpduConstPtr->FirstTimeout_Factor + COM_ONE);

#endif

#ifdef COM_RxSigUpdateTimeout

   if(RxIpduConstPtr->SignalTimeout_Ref != NULL_PTR)
   {
        isRxIpduDmReq_b = COM_TRUE;

        numOfSigWithUpdateBit = RxIpduConstPtr->SignalTimeout_Ref->numWithUpdateBit;

        SigTimeOutConstPtr    = RxIpduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;

        SigTimeOutRamPtr      = RxIpduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;

        SchM_Enter_Com_RxSigToTicks();

        for(index_u16 = numOfSigWithUpdateBit; index_u16 != COM_ZERO; index_u16--)
        {

            (*SigTimeOutRamPtr) = (SigTimeOutConstPtr->First_Timeout == COM_ZERO) ?
                    COM_RXTIMER_MAX : (SigTimeOutConstPtr->First_Timeout + COM_ONE);

            SigTimeOutConstPtr++;
            SigTimeOutRamPtr++;

        }

        SchM_Exit_Com_RxSigToTicks();
   }
#endif

#ifdef COM_RxSigGrpUpdateTimeout

   if(RxIpduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
   {
        isRxIpduDmReq_b = COM_TRUE;

        numOfSigWithUpdateBit = RxIpduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit;

        SigTimeOutConstPtr    = RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;

        SigTimeOutRamPtr      = RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;

        SchM_Enter_Com_RxSigGrpToTicks();

        for(index_u16 = numOfSigWithUpdateBit; index_u16 != COM_ZERO; index_u16--)
        {

            (*SigTimeOutRamPtr) = (SigTimeOutConstPtr->First_Timeout == COM_ZERO) ?
                    COM_RXTIMER_MAX : (SigTimeOutConstPtr->First_Timeout + COM_ONE);

            SigTimeOutConstPtr++;
            SigTimeOutRamPtr++;
        }

        SchM_Exit_Com_RxSigGrpToTicks();
   }
#endif

    return isRxIpduDmReq_b;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

#ifdef COM_RX_DUAL_CYCLE_SUPPPORT

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
Std_ReturnType Com_SetRxIPduTimeoutTicks(Type_SwcServiceCom_tIdPdu rxPduId_uo, uint16 timeoutTicks_u16)
{

# ifdef COM_RxIPduTimeout

   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
    Std_ReturnType              retValue_uo;

    retValue_uo = E_NOT_OK;

   if((COM_UNINIT != Com_Uninit_Flag) &&
        (rxPduId_uo < COM_GET_NUM_RX_IPDU) &&
        (timeoutTicks_u16 < COM_RXTIMER_MAX_DUALCYCLE))
   {

        rxPduId_uo      = COM_GET_RX_IPDU_ID(rxPduId_uo);

        RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(rxPduId_uo);
        RxIpduRamPtr    = &COM_GET_RXPDURAM_S(rxPduId_uo);

        if(RxIpduConstPtr->Timeout_Fact != COM_ZERO)
        {
            retValue_uo = E_OK;

            if(RxIpduRamPtr->RxDualCycTicks_u16 != timeoutTicks_u16)
            {
                RxIpduRamPtr->RxDualCycTicks_u16 = timeoutTicks_u16;

                SchM_Enter_Com_RxPduBuffer();

                Com_SetRamValue(RXIPDU,_RELOAD_RXTICKS, RxIpduRamPtr->RxFlags, COM_TRUE);

                SchM_Exit_Com_RxPduBuffer();
            }
        }
   }

    return retValue_uo;
# else

    (void)rxPduId_uo;
    (void)timeoutTicks_u16;

    return E_NOT_OK;

# endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

