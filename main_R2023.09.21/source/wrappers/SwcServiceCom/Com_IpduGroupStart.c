#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

FUNC(void, COM_CODE) Com_TxIPduStart(
      VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId
   ,  VAR(boolean,                       AUTOMATIC) Initialize
);

FUNC(void, COM_CODE) Com_Lok_ProcessIPduGroupVector(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
);

FUNC(void, COM_CODE) Com_Lok_UpdateBitAndFilter(
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId
);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_IpduGroupControl(
      VAR(Com_IpduGroupVector, AUTOMATIC) ipduGroupVector
   ,  VAR(boolean,             AUTOMATIC) initialize
){
   Com_RxIpduRamPtrType            RxIPduRamPtr;
   Com_TxIpduRamPtrType            TxIPduRamPtr;
   VAR(uint16_least,AUTOMATIC)     Index_u16;
   Com_ReceptionDMControl(ipduGroupVector);
   Com_Lok_ProcessIPduGroupVector((P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))ipduGroupVector);
   RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);
   for(
      Index_u16 = 0;
      Index_u16 < CfgSwcServiceCom_dNumIPduRx;
      Index_u16 ++
   ){
      if(
            COM_GET_IPDUCOUNTER_S(Index_u16)
         >  0
      ){
         if(
               Com_GetRamValue(
                     RXIPDU
                  ,  _PDUSTATUS
                  ,  RxIPduRamPtr->RxFlags
               )
            == COM_STOP
         ){
            Com_SetRamValue(
                  RXIPDU
               ,  _PDUSTATUS
               ,  RxIPduRamPtr->RxFlags
               ,  COM_START
            );
         }
      }
      else{
         if(
            Com_GetRamValue(
                  RXIPDU
               ,  _PDUSTATUS
               ,  RxIPduRamPtr->RxFlags
            )
         ){
            Com_SetRamValue(
                  RXIPDU
               ,  _INDICATION
               ,  RxIPduRamPtr->RxFlags
               ,  COM_FALSE
            );
            Com_SetRamValue(
                  RXIPDU
               ,  _PDUSTATUS
               ,  RxIPduRamPtr->RxFlags
               ,  COM_STOP
            );
            Com_SetRamValue(
                  RXIPDU
               ,  _LARGEDATAINPROG
               ,  RxIPduRamPtr->RxFlags
               ,  COM_FALSE
            );
         }
      }
      RxIPduRamPtr++;
   }
   TxIPduRamPtr = &COM_GET_TXPDURAM_S(0);
   for(
      Index_u16 = 0;
      Index_u16 < CfgSwcServiceCom_dNumIPduTx;
      Index_u16 ++
   ){
      if(
            COM_GET_IPDUCOUNTER_S(Index_u16 + CfgSwcServiceCom_dNumIPduRx)
         >  0
      ){
         if(
               Com_GetRamValue(
                     TXIPDU
                  ,  _PDUSTATUS
                  ,  TxIPduRamPtr->Com_TxFlags
               )
            == COM_STOP
         ){
            Com_TxIPduStart(
                  (Type_CfgSwcServiceCom_tIdIPdu)Index_u16
               ,  initialize
            );
            Com_SetRamValue(
                  TXIPDU
               ,  _PDUSTATUS
               ,  TxIPduRamPtr->Com_TxFlags
               ,  COM_START
            );
            Com_SetRamValue(
                  TXIPDU
               ,  _LARGEDATAINPROG
               ,  TxIPduRamPtr->Com_TxFlags
               ,  COM_FALSE
            );
         }
      }
      else{
         if(
            Com_GetRamValue(
                  TXIPDU
               ,  _PDUSTATUS
               ,  TxIPduRamPtr->Com_TxFlags
            )
         ){
            Com_SetRamValue(
                  TXIPDU
               ,  _PDUSTATUS
               ,  TxIPduRamPtr->Com_TxFlags
               ,  COM_STOP
            );
            Com_TxIPduStop(
               (Type_CfgSwcServiceCom_tIdIPdu)Index_u16
            );
         }
      }
      TxIPduRamPtr++;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_ProcessIPduGroupVector(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ipduGroupVector
){
   P2CONST(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC, COM_APPL_CONST) IPduRefPtr;
       VAR(uint16,                        AUTOMATIC                ) Index_u16;
       VAR(uint16,                        AUTOMATIC                ) NoOfPdus_u16;
       VAR(Com_IpduGroupIdType,           AUTOMATIC                ) IpduGrpId_u16;
       VAR(uint8,                         AUTOMATIC                ) ByteVal_u8;
       VAR(uint8,                         AUTOMATIC                ) BitOffset_u8;
       VAR(uint8,                         AUTOMATIC                ) PduCounterVal;
           Com_IPduGrpConstPtrType                                   IPduGrpConstPtr;
   for(
      Index_u16 = 0;
      Index_u16 < COM_NUM_ARR_IPDUGRPVECT;
      Index_u16 ++
   ){
      if(
            Com_IpduGrpVector[Index_u16]
         != ipduGroupVector[Index_u16]
      ){
         ByteVal_u8   = (uint8)(Com_IpduGrpVector[Index_u16] ^ ipduGroupVector[Index_u16]);
         BitOffset_u8 = 0u;
         do{
            if(
                  COM_RESET
               != (ByteVal_u8 & 1u)
            ){
               IpduGrpId_u16   = (8u * Index_u16) + BitOffset_u8;
               IpduGrpId_u16   = COM_GET_IPDUGRP_ID(IpduGrpId_u16);
               PduCounterVal   = ((((ipduGroupVector[Index_u16] >> BitOffset_u8) & 1u) != 0u) ? (0x1u) : (0xFFu));
               IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);
               IPduRefPtr      = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);
               NoOfPdus_u16    = (
                     IpduGrpId_u16
                  != (COM_GET_NUM_TOTAL_IPDU_GRP - 1u)
               )
               ?  ((IPduGrpConstPtr + 1)->FirstIpdu_Index - IPduGrpConstPtr->FirstIpdu_Index)
               :  (COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP)
               ;
               while(
                     NoOfPdus_u16
                  >  0u
               ){
                  COM_GET_IPDUCOUNTER_S(*IPduRefPtr) = (uint8)(
                        COM_GET_IPDUCOUNTER_S(*IPduRefPtr)
                     +  PduCounterVal
                  );
                  IPduRefPtr++;
                  NoOfPdus_u16--;
               }
            }
            BitOffset_u8++;
            ByteVal_u8 >>= 1u;
         }while(
               ByteVal_u8
            >  0u
         );
         Com_IpduGrpVector[Index_u16] = ipduGroupVector[Index_u16];
      }
   }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_ClearIpduGroupVector(
   VAR(Com_IpduGroupVector, AUTOMATIC) ipduGroupVector
){
   VAR(uint16, AUTOMATIC) Index_u16;
   for(
      Index_u16 = 0u;
      Index_u16 < COM_NUM_ARR_IPDUGRPVECT;
      Index_u16 ++
   ){
      ipduGroupVector[Index_u16] = (uint8)0;
   }
}

FUNC(void, COM_CODE) Com_SetIpduGroup(
      VAR(Com_IpduGroupVector, AUTOMATIC) ipduGroupVector
   ,  VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGroupId
   ,  VAR(boolean,             AUTOMATIC) bitval
){
   VAR(uint16, AUTOMATIC) Index_u16    = (uint16)(IpduGroupId >> 3u);
   VAR(uint8,  AUTOMATIC) BitOffset_u8 = (uint8 )(IpduGroupId % 8u);
   if(
      bitval
   ){
      ipduGroupVector[Index_u16] |= ((uint8)(1u << BitOffset_u8));
   }
   else{
      ipduGroupVector[Index_u16] &= ((uint8)(~(1u << BitOffset_u8)));
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_TxIPduStart(
      VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId
   ,  VAR(boolean,                       AUTOMATIC) Initialize
){
   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;
   VAR(uint8, AUTOMATIC)   LatestTransMode_u8;
   if(
         Initialize
      != COM_FALSE
   ){
      TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
      TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);
      Com_Lok_UpdateBitAndFilter(
         IpduId
      );
      Com_TxChangeMode(
         IpduId
      );
      LatestTransMode_u8 = Com_GetRamValue(
            TXIPDU
         ,  _LATESTMODE
         ,  TxIpduRamPtr->Com_TransMode
      );
      Com_SetRamValue(
            TXIPDU
         ,  _GWIPDUTMSCHANGED
         ,  TxIpduRamPtr->Com_TxFlags
         ,  COM_FALSE
      );
      if(
            COM_RESET
         != (
                  LatestTransMode_u8
               &  COM_TXMODE_MIXED
            )
      ){
         TxIpduRamPtr->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimeOffsetFact;
      }
      TxIpduRamPtr->Com_MinDelayTick = 0;
      Com_SetRamValue(
            TXIPDU
         ,  _TICKTXTO
         ,  TxIpduRamPtr->Com_TxFlags
         ,  COM_STOP
      );
      if(
         Com_GetValue(
               TXIPDU
            ,  _NONETOSTATUS
            ,  TxIPduConstPtr->txIPduFields
         )
      ){
         Com_SetRamValue(
               TXIPDU
            ,  _TICKTXTO
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_START
         );
         TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
      }
      else{
         TxIpduRamPtr->Com_TickTxTimeout = 0;
         Com_SetRamValue(
               TXIPDU
            ,  _CONFIR
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_FALSE
         );
      }
   }
   else{
      TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
      TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);
      Com_TxChangeMode(
         (Type_CfgSwcServiceCom_tIdIPdu)IpduId
      );
      if(
         Com_GetValue(
               TXIPDU
            ,  _NONETOSTATUS
            ,  TxIPduConstPtr->txIPduFields
         )
      ){
         Com_SetRamValue(
               TXIPDU
            ,  _TICKTXTO
            ,  TxIpduRamPtr->Com_TxFlags
            ,  COM_START
         );
         TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
      }
   }
}

FUNC(void, COM_CODE) Com_Lok_UpdateBitAndFilter(
   VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId
){
   VAR(uint16_least, AUTOMATIC) Index_Sig_ui;
       Com_TxIpduConstPtrType   TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
       Com_TxSigConstPtrType    TxSigConstPtr  = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);
   for(
      Index_Sig_ui = TxIPduConstPtr->No_Of_Sig_Ref;
      Index_Sig_ui != 0u;
      Index_Sig_ui --
   ){
      TxSigConstPtr++;
   }
}

