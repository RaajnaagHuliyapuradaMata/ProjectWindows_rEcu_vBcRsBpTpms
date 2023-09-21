#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessRxDMIPduGroupVector(
                                                            P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
                                                                    );

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_EnableRxDeadlineMonitoring(VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId);

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_ReceptionDMControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector)
{
#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

   Com_RxIpduRamPtrType            RxIPduRamPtr;
   VAR(uint16_least, AUTOMATIC)    Index_u16;
#endif
   VAR(uint16,AUTOMATIC)           ByteNo_u16;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Ptr( (ipduGroupVector == NULL_PTR), COMServiceId_ReceptionDMControl ))
#endif
   {

        ByteNo_u16 = ( uint16 )( COM_GET_NUM_TOTAL_IPDU_GRP / 8u );
        if( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
        {
            ipduGroupVector[ ByteNo_u16 ] &= ( ( uint8 )( 0xFF ) >> ( 8u - ( COM_GET_NUM_TOTAL_IPDU_GRP % 8u ) ) );
            ByteNo_u16++;

            while( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
            {
                ipduGroupVector[ ByteNo_u16 ] = ( uint8 )0;
                ByteNo_u16++;
            }
        }

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

        Com_Lok_ProcessRxDMIPduGroupVector((P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))(ipduGroupVector));

        RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);

        for(Index_u16 = 0; Index_u16 < CfgSwcServiceCom_dNumIPduRx; Index_u16++)
        {
            if(COM_GET_IPDUCOUNTER_DM(Index_u16) >0 )
            {

                if((Com_GetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags)) == COM_STOP)
                {
                    Com_Lok_EnableRxDeadlineMonitoring((Type_CfgSwcServiceCom_tIdIPdu)Index_u16);

                    Com_SetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags, COM_START);
                }
            }
            else{

                if(Com_GetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags))
                {

                    Com_SetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags, COM_STOP);
                }
            }
            RxIPduRamPtr++;
        }
#endif
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessRxDMIPduGroupVector(
                                            P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
                                                                    )
{

   P2CONST(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC, COM_APPL_CONST)  IPduRefPtr;

   Com_IPduGrpConstPtrType                             IPduGrpConstPtr;
   VAR(uint16_least,AUTOMATIC)                         Index_u16;
   VAR(uint16_least,AUTOMATIC)                         NoOfPdus_u16;
   VAR(Com_IpduGroupIdType, AUTOMATIC)                 IpduGrpId_u16;
   VAR(uint8, AUTOMATIC)                               ByteVal_u8;
   VAR(uint8,AUTOMATIC)                                BitOffset_u8;
   VAR(uint8,AUTOMATIC)                                PduCounterVal;

   for(Index_u16 = 0; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
   {
        if(Com_IpduGrpVector_DM[Index_u16] != ipduGroupVector[Index_u16] )
        {

            ByteVal_u8 = (uint8)((Com_IpduGrpVector_DM[Index_u16]) ^ (ipduGroupVector[Index_u16]));
            BitOffset_u8 = 0u;

            do
            {

                if(COM_RESET != (ByteVal_u8 & 1u))
                {

                    IpduGrpId_u16   = (Com_IpduGroupIdType)(8u * Index_u16)+ BitOffset_u8 ;

                    IpduGrpId_u16   = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                    PduCounterVal   = ((((ipduGroupVector[Index_u16] >> BitOffset_u8) & 1u) != 0u) ? (0x1u) : (0xFFu));

                    IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);

                    IPduRefPtr      = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);

                    NoOfPdus_u16    = IPduGrpConstPtr->NoOfRxPdus;

                    while(NoOfPdus_u16 > 0u)
                    {

                         COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) = (uint8)
                        (COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) + PduCounterVal);

                        IPduRefPtr++;
                        NoOfPdus_u16--;
                    }
                }

                BitOffset_u8 ++;
                ByteVal_u8 >>= 1u;

            }while(ByteVal_u8 > 0u);

            Com_IpduGrpVector_DM[Index_u16] = ipduGroupVector[Index_u16] ;
        }

   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_EnableRxDeadlineMonitoring(VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId)
{
   Com_RxIpduConstPtrType                                      RxIPduConstPtr;
#ifdef COM_RxIPduTimeout
   Com_RxIpduRamPtrType                                        RxIPduRamPtr;
#endif
#if(defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
   P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST)   SigTimeOutConfigPtr;
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)                     SigTimeOutTicksPtr;
   VAR(uint16_least, AUTOMATIC)                                Idx_Sig_ui;
   VAR(uint16_least, AUTOMATIC)                                NoOfSigOrSigGrp_ui;
#endif

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);

#ifdef COM_RxIPduTimeout
    RxIPduRamPtr   = &COM_GET_RXPDURAM_S(IpduId);

    RxIPduRamPtr->RxTicks_u16 = (RxIPduConstPtr->FirstTimeout_Factor == 0) ? COM_RXTIMER_MAX :
                                                                             RxIPduConstPtr->FirstTimeout_Factor;
#endif

#ifdef COM_RxSigUpdateTimeout

   if(RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR)
   {

        NoOfSigOrSigGrp_ui  = RxIPduConstPtr->SignalTimeout_Ref->numWithUpdateBit;

        SigTimeOutConfigPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;

        SigTimeOutTicksPtr  = RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;

        SchM_Enter_Com_RxSigToTicks();

        for(Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
        {

            (*SigTimeOutTicksPtr) = (SigTimeOutConfigPtr->First_Timeout == 0) ? COM_RXTIMER_MAX :
                                                                                SigTimeOutConfigPtr->First_Timeout;

            SigTimeOutTicksPtr++;
            SigTimeOutConfigPtr++;

        }

        SchM_Exit_Com_RxSigToTicks();
   }
#endif

#ifdef COM_RxSigGrpUpdateTimeout

   if(RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
   {

        NoOfSigOrSigGrp_ui  = RxIPduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit;

        SigTimeOutConfigPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;

        SigTimeOutTicksPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;

        SchM_Enter_Com_RxSigGrpToTicks();

        for(Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
        {

            (*SigTimeOutTicksPtr) = (SigTimeOutConfigPtr->First_Timeout == 0) ? COM_RXTIMER_MAX :
                                                                                SigTimeOutConfigPtr->First_Timeout;

            SigTimeOutConfigPtr++;
            SigTimeOutTicksPtr++;
        }

        SchM_Exit_Com_RxSigGrpToTicks();
   }
#endif
}
#endif

