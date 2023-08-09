

#ifndef COM_PRV_TYPES_H
#define COM_PRV_TYPES_H

typedef struct
{
    unsigned int isEventTrig                   : 1;
    unsigned int isTriggerIpduSendWithMetadata : 1;
    unsigned int isGwIpduSend                  : 1;
    unsigned int isModeChangd                  : 1;
    unsigned int sigTransProp                  : 1;
    unsigned int isTimeoutReq                  : 1;
    unsigned int ignoreRepetitions             : 1;
} Com_SendIpduInfo;

typedef struct
{
    uint16              TimePeriodFact;
    uint16              TimeOffsetFact;
    uint16              RepetitionPeriodFact;
    uint8               NumOfRepetitions;

#ifdef COM_MIXEDPHASESHIFT
    uint8               Mode;
    boolean             MixedPhaseShift;
#else

    uint8               Mode;

#endif

}Com_TransModeInfo;

typedef P2CONST( Com_TransModeInfo, AUTOMATIC, COM_APPL_CONST)  Com_TMConstPtrType;

typedef struct
{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification

        P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif

#ifdef COM_ERRORNOTIFICATION

    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif
#ifdef COM_TxInvalid
    uint32                  DataInvalid_Val;
#endif
    uint32                  Init_Val;

    uint16                  txSignalFields;

#ifdef COM_TxSigUpdateBit
    Com_BitpositionType     Update_Bit_Pos;
#endif

    Com_BitpositionType     Bit_Pos;

    Com_BitsizeType         BitSize;

#ifdef COM_TxFilters

    Com_FilterType          Filter_Index;
#endif

#ifdef COM_EffectiveSigTOC
    Com_OldValType          OldValue_Index;
#endif

    Com_IpduIdType          IpduRef;

    uint8         General;

}Com_Lok_xTxSigCfg_tst;

typedef P2CONST (Com_Lok_xTxSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigConstPtrType;

typedef struct
{
#ifdef COM_RxSignalNotify

    P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif
#ifdef COM_RxSigInvalidNotify
    P2FUNC(void, COM_APPL_CODE, Sig_DataInvalid_Indication_Cbk)(void);
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify

    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif
#ifdef COM_RxSigInvalid
    uint32                  DataInvalid_Val;
#endif
    uint32                  Init_Val;
#ifdef COM_RxSigUpdateBit
    Com_BitpositionType     Update_Bit_Pos;
#endif
    Com_BitpositionType     Bit_Pos;
    Com_SigBuffIndexType    SigBuff_Index;
    Com_BitsizeType         BitSize;
#ifdef COM_RxFilters

    Com_FilterType          Filter_Index;
#endif

    Com_IpduIdType          IpduRef;

    uint8         General;

    uint8         rxSignalFields;

}Com_Lok_xRxSigCfg_tst;

typedef P2CONST (Com_Lok_xRxSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigConstPtrType;

#ifdef COM_TX_SIGNALGROUP

# ifdef COM_TX_SIGNALGROUP_ARRAY
typedef struct
{
    PduLengthType    FirstByteNo;
    PduLengthType    Length;

} Com_Lok_xTxSigGrpArrayCfg_tst;

typedef P2CONST(Com_Lok_xTxSigGrpArrayCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigGrpArrayConstPtrType;

# endif

typedef struct
{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification

    P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif

#ifdef COM_ERRORNOTIFICATION

    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif

#ifdef COM_TxSigGrpUpdateBit
    Com_BitpositionType         Update_Bit_Pos;
#endif
    Com_IpduIdType              IpduRef;
    Com_TxIntGrpSignalIdType    FirstGrpSig_Index;
    Com_NoOfTxGrpSignalType     No_Of_GrpSig;

#ifdef COM_TX_SIGNALGROUP_ARRAY
    Com_TxSigGrpArrayIndexType  SigGrpArray_Index;
#endif

    uint8                       txSignalGrpFields;

}Com_Lok_xTxSigGrpCfg_tst;

typedef P2CONST (Com_Lok_xTxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigGrpConstPtrType;

#endif

#ifdef COM_RX_SIGNALGROUP

# ifdef COM_RX_SIGNALGROUP_ARRAY
typedef struct
{
    PduLengthType               FirstByteNo;
    Com_RxSigGrpBuffIndexType   RxSigGrpBuf_Index;

} Com_Lok_xRxSigGrpArrayCfg_tst;

typedef P2CONST(Com_Lok_xRxSigGrpArrayCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigGrpArrayConstPtrType;

# endif

typedef struct
{
#ifdef COM_RxSignalGrpNotify

     P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif
#ifdef COM_RxSigGrpInvalidNotify
    P2FUNC(void, COM_APPL_CODE, DataInvalid_Indication_Cbk)(void);
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify

    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif
#ifdef COM_RxSigGrpUpdateBit
    Com_BitpositionType         Update_Bit_Pos;
#endif
    Com_IpduIdType              IpduRef;

    Com_RxIntGrpSignalIdType    FirstGrpSig_Index;

    Com_NoOfRxGrpSignalType     No_Of_GrpSig;
#ifdef COM_SIGNALGROUPGATEWAY
    uint16                      numOfGwSrcGrpSignals;
#endif

    PduLengthType               lastByte_u8;

#ifdef COM_RX_SIGNALGROUP_ARRAY
    Com_RxSigGrpArrayIndexType  SigGrpArray_Index;
#endif

    uint8                       rxSignalGrpFields;

}Com_Lok_xRxSigGrpCfg_tst;

typedef P2CONST (Com_Lok_xRxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigGrpConstPtrType;
#endif

#ifdef COM_TX_SIGNALGROUP

typedef struct
{

#ifdef COM_TxGrpSigInvalid
    uint32                      DataInvalid_Val;
#endif
    uint32                      Init_Val;
    Com_BitpositionType         Bit_Pos;
    Com_TxGrpSigBuffIndexType   TxGrpSigBuff_Index;

    Com_TxIntSignalGroupIdType  SigGrpRef;

    Com_BitsizeType             BitSize;
#ifdef COM_TxFilters

    Com_FilterType          Filter_Index;
    uint8                   Filter_Algo;
#endif

#ifdef COM_EffectiveSigGrpTOC
    Com_OldValType          OldValue_Index;
#endif

    uint8    txGrpSigFields;

}Com_Lok_xTxGrpSigCfg_tst;

typedef P2CONST (Com_Lok_xTxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxGrpSigConstPtrType;
#endif

#ifdef COM_RX_SIGNALGROUP

typedef struct
{
#ifdef COM_RxSigGrpInvalid
    uint32                      DataInvalid_Val;
#endif
    uint32                      Init_Val;
    Com_BitpositionType         Bit_Pos;
    Com_RxGrpSigBuffIndexType   RxGrpSigBuff_Index;

    Com_RxIntSignalGroupIdType  SigGrpRef;

    Com_BitsizeType             BitSize;
#ifdef COM_RxFilters

    Com_FilterType              Filter_Index;
    uint8                       Filter_Algo;
#endif

    uint8     rxGrpSigFields;
}Com_Lok_xRxGrpSigCfg_tst;

typedef P2CONST (Com_Lok_xRxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxGrpSigConstPtrType;
#endif

typedef struct
{
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) BuffPtr;

    P2CONST(Com_TransModeInfo, TYPEDEF,COM_APPL_CONST) Com_TMConstPtr;
#ifdef COM_TxIPduCallOuts

    P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2VAR(PduInfoType, TYPEDEF, COM_APPL_DATA));
#endif
#ifdef COM_TxIPduNotification

        P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif

#ifdef COM_ERRORNOTIFICATION

    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif

#ifdef COM_METADATA_SUPPORT
    Com_MetaDataInfoPtr         MetaDataPtr;
#endif

    PduLengthType               Size;

#ifdef COM_TxIPduTimeOut
    uint16                      Timeout_Fact;
#endif

    uint16                      Min_Delay_Time_Fact;

    uint16                      No_Of_Sig_Ref;
#ifdef COM_TX_SIGNALGROUP
    uint16                      No_Of_SigGrp_Ref;
#endif
    PduIdType                   PdurId;
    Com_TxIntSignalIdType       TxSigId_Index;
#ifdef COM_TX_SIGNALGROUP
    Com_TxIntSignalGroupIdType  FirstTxSigGrp_Index;
#endif

    uint16                      txIPduFields;
    Com_MainFuncType            MainFunctionRef;
    uint8                       PaddingByte;

} Com_Lok_xTxIpduInfoCfg_tst;

typedef P2CONST(Com_Lok_xTxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxIpduConstPtrType;

#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))

typedef struct
{

#ifdef COM_RxUpdateTimeoutNotify
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
    uint16          First_Timeout;
    uint16          Timeout;
    uint16          SigId;
}Com_SignalTimeoutInfo;

typedef struct
{

    P2CONST(Com_SignalTimeoutInfo, TYPEDEF, COM_APPL_CONST) TimeoutInfo_Ref;
    P2VAR(uint16,TYPEDEF, COM_APPL_DATA) TimeoutTicks_p;
    uint8           numWithUpdateBit;
}Com_UpdatebitTimeoutInfo;

#endif

typedef struct
{
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                        BuffPtr;

#ifdef  COM_RxSigUpdateTimeout
    P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST)  SignalTimeout_Ref;
#endif

#ifdef  COM_RxSigGrpUpdateTimeout
    P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST)  SignalGrpTimeout_Ref;
#endif

#ifdef COM_RxIPduCallOuts
    P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2CONST(PduInfoType, TYPEDEF, COM_APPL_CONST));
#endif

#ifdef COM_RxIPduTimeoutNotify
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif

#ifdef COM_RxIPduNotification
    P2FUNC(void, COM_APPL_CODE, RxNotification_Cbk)(void);
#endif

    PduLengthType                   Size;
#ifdef COM_RxIPduTimeout
    uint16                          FirstTimeout_Factor;
    uint16                          Timeout_Fact;
#endif
    uint16                          No_Of_Sig_Ref;
#ifdef COM_RX_SIGNALGROUP
    uint16                          No_Of_SigGrp_Ref;
#endif
    Com_RxIntSignalIdType           RxSigId_Index;
#ifdef COM_RX_SIGNALGROUP
    Com_RxIntSignalGroupIdType      FirstRxSigGrp_Index;
#endif
#ifdef COM_SIGNALGATEWAY
    uint16                          numOfGwSrcSignals;
#endif
#ifdef COM_SIGNALGROUPGATEWAY
    uint16                          numOfGwSrcSignalGrps;
#endif

    Com_MainFuncType                MainFunctionRef;

    uint8                           rxIPduFields;

} Com_Lok_xRxIpduInfoCfg_tst;

typedef P2CONST(Com_Lok_xRxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxIpduConstPtrType;

typedef struct
{
    uint16 FirstIpdu_Index;
    uint16 NoOfRxPdus;

} Com_Lok_xIpduGrpInfoCfg_tst;

typedef P2CONST(Com_Lok_xIpduGrpInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_IPduGrpConstPtrType;

typedef struct
{
    uint8 txSigRAMFields;

}Com_TxSignalFlagType;

typedef P2VAR( Com_TxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxSigRamPtrType;

#ifdef COM_TX_SIGNALGROUP

typedef struct
{
    uint8 txGrpSigRAMFields;

}Com_TxGrpSignalFlagType;

typedef P2VAR( Com_TxGrpSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxGrpSigRamPtrType;

#endif

typedef struct
{
    uint8 rxSigRAMFields;

}Com_RxSignalFlagType;

typedef P2VAR( Com_RxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_RxSigRamPtrType;

#ifdef COM_RX_SIGNALGROUP

typedef struct
{
    uint8 rxSigGrpRAMFields;

}Com_RxSignalGrpFlagType;

typedef P2VAR( Com_RxSignalGrpFlagType, AUTOMATIC, COM_APPL_DATA)  Com_RxSigGrpRamPtrType;
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

typedef struct
{
    uint8 txSigGrpRAMFields;

}Com_TxSignalGrpFlagType;

typedef P2VAR( Com_TxSignalGrpFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxSigGrpRamPtrType;
#endif
#endif

typedef struct
{
    Com_TMConstPtrType  CurrentTxModePtr;
#ifdef COM_TP_IPDUTYPE
    PduLengthType       TxTPIPduLength;
#endif
    uint16              Com_MinDelayTick;
    uint16              Com_Tick_Tx;
#ifdef COM_TxFilters
    uint16              Com_TMSTrueCounter_u8;
#endif
    uint16              Com_n_Tick_Tx;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    uint16              Com_DynLength;
#endif
#ifdef COM_TxIPduTimeOut
    uint16              Com_TickTxTimeout;
#endif

    uint16              Com_TxFlags;
    uint8               Com_n;

    uint8               Com_TransMode;

} Com_TxIpduRamData;

typedef P2VAR( Com_TxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_TxIpduRamPtrType;

typedef struct
{
    PduLengthType   RxIPduLength;
#ifdef COM_TP_IPDUTYPE
    PduLengthType   RxTPIPduLength;
#endif
#ifdef COM_RxIPduTimeout
    uint16          RxTicks_u16;
#endif

    uint8  RxFlags;

}Com_RxIpduRamData;

typedef P2VAR( Com_RxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_RxIpduRamPtrType;

typedef struct
{
    P2VAR(PduIdType, TYPEDEF, COM_APPL_DATA) RxGwQueuePtr;
    VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueWrite_ux;
    VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueRead_ux;
}Com_RxGwQueueRAMType;

typedef P2VAR( Com_RxGwQueueRAMType, AUTOMATIC, COM_APPL_DATA)  Com_RxGwQueuePtrType;

typedef struct
{
    Com_SignalIdType indexGwMapSigDestIdArray;
    uint8            destCount;
}Com_Lok_xGwMapSigCfg_tst;

typedef P2CONST( Com_Lok_xGwMapSigCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigConfPtrType;

typedef struct
{
    Com_SignalIdType GwMap_DestId;
}Com_Lok_xGwMapSigIdCfg_tst;

typedef P2CONST( Com_Lok_xGwMapSigIdCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigIdConfPtrType;

#ifdef COM_TX_SIGNALGROUP
typedef struct
{
    Com_TxIntGrpSignalIdType indexGwMapGrpSigDestIdArray;
    uint8                    destCount;
}Com_Lok_xGwMapGrpSigCfg_tst;

typedef P2CONST( Com_Lok_xGwMapGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapGrpSigConfPtrType;

typedef struct
{
    Com_TxIntGrpSignalIdType GwMap_DestGrpSigId;
}Com_Lok_xGwMapGrpSigIdCfg_tst;

typedef P2CONST( Com_Lok_xGwMapGrpSigIdCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapGrpSigIdConfPtrType;
#endif

typedef struct
{
    Com_IpduIdType          StartIPduId;
    Com_NumOfIpdusType      NumOfIpdus;
    Com_TimeBaseType        TimeBaseInMs;
} Com_MainFunctionCfgType;

typedef struct
{
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SigType_pu8;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SigType_dyn_pu8;
#endif

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu32;

#ifdef COM_RXSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu64;
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_SigType_pf64;
#endif

#ifdef COM_RX_SIGNALGROUP
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_RxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_RxGrpSigType_pf64;
#endif

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SecondRxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_SecondRxGrpSigType_pf64;
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_RxSigGrpArrayBuf_pu8;
#endif

#endif

#ifdef COM_RxIPduDeferredProcessing
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_DeferredBuffer_pu8;
#endif

} Com_Lok_xRxRamBuf_tst;

#ifdef COM_TX_SIGNALGROUP
typedef struct
{
    P2VAR(uint8,  TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu32;

#ifdef COM_TXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu64;
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_TxGrpSigType_pf64;
#endif

} Com_Lok_xTxSigGrpRamBuf_tst;
#endif

typedef struct
{
    P2CONST(Com_Lok_xTxSigCfg_tst, COM_CONST, COM_APPL_CONST)             Com_TxSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_TxSignalMapping_pct;

    P2CONST(Com_Lok_xRxSigCfg_tst, COM_CONST, COM_APPL_CONST)             Com_RxSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_RxSignalMapping_pct;

#ifdef COM_TX_SIGNALGROUP
    P2CONST(Com_Lok_xTxSigGrpCfg_tst, COM_CONST, COM_APPL_CONST)          Com_TxSigGrp_pcst;

    P2CONST(Com_SignalGroupIdType, COM_CONST, COM_APPL_CONST)             Com_TxSignalGrpMapping_pct;

#endif

#ifdef  COM_RX_SIGNALGROUP
    P2CONST(Com_Lok_xRxSigGrpCfg_tst, COM_CONST, COM_APPL_CONST)          Com_RxSigGrp_pcst;

    P2CONST(Com_SignalGroupIdType, COM_CONST, COM_APPL_CONST)             Com_RxSignalGrpMapping_pct;

#endif

#ifdef COM_TX_SIGNALGROUP
    P2CONST(Com_Lok_xTxGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_TxGrpSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_TxGrpSignalMapping_pct;
#endif

#ifdef COM_RX_SIGNALGROUP
    P2CONST(Com_Lok_xRxGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_RxGrpSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_RxGrpSignalMapping_pct;
#endif

    P2CONST(Com_Lok_xTxIpduInfoCfg_tst, COM_CONST, COM_APPL_CONST)        Com_TxIpdu_pcst;

    P2CONST(PduIdType, COM_CONST, COM_APPL_CONST)                         Com_TxIpduMapping_pcst;

    P2CONST(Com_Lok_xRxIpduInfoCfg_tst, COM_CONST, COM_APPL_CONST)        Com_RxIpdu_pcst;

    P2CONST(PduIdType, COM_CONST, COM_APPL_CONST)                         Com_RxIpduMapping_pcst;

    P2CONST(Com_Lok_xIpduGrpInfoCfg_tst, COM_CONST, COM_APPL_CONST)       Com_IpduGrp_pcst;

    P2CONST(uint16, COM_CONST, COM_APPL_CONST)                            Com_IpduGrpMapping_pcu16;

#ifdef COM_SIGNALGATEWAY
    P2CONST(Com_Lok_xGwMapSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_GwSig_pcst;

    P2CONST(Com_Lok_xGwMapSigIdCfg_tst, COM_CONST, COM_APPL_CONST)        Com_GwSigIdMapping_pcst;
#endif

#ifdef COM_SIGNALGROUPGATEWAY
    P2CONST(Com_Lok_xGwMapGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)       Com_GwGrpSig_pcst;

    P2CONST(Com_Lok_xGwMapGrpSigIdCfg_tst, COM_CONST, COM_APPL_CONST)     Com_GwGrpSigIdMapping_pcst;
#endif

    P2CONST(Com_IpduIdType, COM_CONST, COM_APPL_CONST)                    Com_IPduGrp_IpduRef_pcst;

#if defined ( COM_TX_SIGNALGROUP_ARRAY )
    Com_TxSigGrpArrayConstPtrType                                         Com_TxSigGrpArray_pcst;
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )
    Com_RxSigGrpArrayConstPtrType                                         Com_RxSigGrpArray_pcst;
#endif

#if defined(COM_TXSIG_FLOAT64SUPP ) || defined(COM_TXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXSIG_FLOAT64SUPP)
    P2CONST(float64, COM_CONST, COM_APPL_CONST)                           floatValArray_pcaf64;
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)
    P2CONST(Com_MaskXType, COM_CONST, COM_APPL_CONST)                     Com_MaskX_pcst;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    P2CONST(uint32, COM_CONST, COM_APPL_CONST)                            Com_Mask_pu32;
#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
    P2CONST(Com_POSMinMaxType, COM_CONST, COM_APPL_CONST)                 Com_POSMinMax_pcst;
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
    P2CONST(Com_NEGMinMaxType, COM_CONST, COM_APPL_CONST)                 Com_NEGMinMax_pcst;
#endif

    P2CONST(Com_MainFunctionCfgType, COM_CONST, COM_APPL_CONST)           Com_MainFunctionCfg_pcst;

    P2CONST(Com_Lok_xRxRamBuf_tst, COM_CONST, COM_APPL_CONST)             Com_RxRamBuf_pcst;

#ifdef COM_TX_SIGNALGROUP
    P2CONST(Com_Lok_xTxSigGrpRamBuf_tst, COM_CONST, COM_APPL_CONST)       Com_TxSigGrpRamBuf_pcst;
#endif

#ifdef COM_F_ONEEVERYN
    P2CONST(Com_OneEveryNType, COM_CONST, COM_APPL_CONST)                 Com_OneEveryN_Const_pcst;

    P2VAR(Com_OneEveryNType, TYPEDEF, COM_APPL_DATA)                      Com_OneEveryN_pe;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_F_OldVal_pu32;
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)
    P2VAR(Com_OldValTrigOnChngType, TYPEDEF, COM_APPL_DATA)               Com_OldValTrigOnChng_puo;
#endif

#ifdef COM_TP_IPDUTYPE

    P2VAR(PduLengthType, TYPEDEF, COM_APPL_DATA)                          Com_TpTxIpduLength_pauo;
#endif

    P2VAR(Com_TxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_TxIpduRam_ps;

    P2VAR(Com_RxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_RxIpduRam_ps;

    P2VAR(Com_TxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_TxSignalFlag_ps;

    P2VAR(Com_RxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_RxSignalFlag_ps;

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_ps;

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_DM_ps;

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    P2VAR(PduIdType, TYPEDEF, COM_APPL_DATA)                              Com_RxGwQueue_paux;

    P2VAR(Com_RxGwQueueRAMType, TYPEDEF, COM_APPL_DATA)                   Com_RxGwQueue_ps;
#endif

#ifdef COM_RX_SIGNALGROUP
    P2VAR(Com_RxSignalGrpFlagType, TYPEDEF, COM_APPL_DATA)                Com_RxSignalGrpFlag_ps;
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)
    P2VAR(Com_TxSignalGrpFlagType, TYPEDEF, COM_APPL_DATA)                Com_TxSignalGrpFlag_ps;
#endif

    P2VAR(Com_TxGrpSignalFlagType, TYPEDEF, COM_APPL_DATA)                Com_TxGrpSignalFlag_ps;
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    P2VAR(boolean, TYPEDEF, COM_APPL_DATA)                                Com_IsGwSignalsUpdated_pab;
#endif

    CONST(uint16, COM_CONST)                                              noOfIpduGroup;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfIpdusInLastIpduGrp;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfTxSignals;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfRxSignals;

    CONST(Com_SignalGroupIdType, COM_CONST)                               noOfTxSignalGroup;

    CONST(Com_SignalGroupIdType, COM_CONST)                               noOfRxSignalGroup;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfTxGroupSignal;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfRxGroupSignal;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfTxIpdu;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfRxIpdu;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfGwSrcSignals;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGwSrcGrpSignals;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfGwSrcIpdu;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGrpSigNoGw;

#ifdef COM_F_ONEEVERYN
    CONST(uint8, COM_CONST)                                               noOfOneEveryNSigAndGrpSig;
#endif

} Com_ConfigData_tst;

#endif

