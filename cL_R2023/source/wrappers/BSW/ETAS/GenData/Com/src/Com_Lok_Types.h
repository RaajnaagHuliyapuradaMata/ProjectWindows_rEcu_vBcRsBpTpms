

#ifndef COM_PRV_TYPES_H
#define COM_PRV_TYPES_H

typedef struct{
    unsigned int isEventTrig        : 1;
    unsigned int isModeChangd       : 1;
    unsigned int isSigTriggered     : 1;
    unsigned int isTimeoutReq       : 1;
    unsigned int ignoreRepetitions  : 1;
    unsigned int isSwtIpduTxMode    : 1;
} Com_SendIpduInfo;

typedef struct{
    uint16                                          TimePeriodFact;
    uint16                                          TimeOffsetFact;
    uint16                                          RepetitionPeriodFact;
    uint8                                           NumOfRepetitions;

#ifdef COM_MIXEDPHASESHIFT
    uint8                                           Mode;
    boolean                                         MixedPhaseShift;
#else

    uint8                                           Mode;

#endif
}Com_TransModeInfo;

typedef const Com_TransModeInfo * Com_TMConstPtrType;

typedef struct{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification

    void (*Notification_Cbk) (void);
#endif

#ifdef COM_ERRORNOTIFICATION

    void (*NotificationError_Cbk) (void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    void (*TimeOutNotification_Cbk) (void);
#endif
#endif
#ifdef COM_TxInvalid
    uint32                                          DataInvalid_Val;
#endif
    uint32                                          Init_Val;

    uint16                                          txSignalFields;

#ifdef COM_TxSigUpdateBit
    Com_BitpositionType                             Update_Bit_Pos;
#endif

    Com_BitpositionType                             Bit_Pos;

    Com_BitsizeType                                 BitSize;

#ifdef COM_TxFilters
    Com_FilterType                                  Filter_Index;
#endif

#ifdef COM_EffectiveSigTOC
    Com_OldValType                                  OldValue_Index;
#endif

    Com_IpduIdType                                  IpduRef;

    uint8                                           General;
}Com_Lok_xTxSigCfg_tst;

typedef const Com_Lok_xTxSigCfg_tst * Com_TxSigConstPtrType;

typedef struct{
#ifdef COM_RxSignalNotify

    void (*Notification_Cbk) (void);
#endif
#ifdef COM_RxSigInvalidNotify
    void (*Sig_DataInvalid_Indication_Cbk) (void);
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify

    void (*TimeOutNotification_Cbk) (void);
#endif
#endif
#ifdef COM_RxSigInvalid
    uint32                                          DataInvalid_Val;
#endif
    uint32                                          Init_Val;
#ifdef COM_RxSigUpdateBit
    Com_BitpositionType                             Update_Bit_Pos;
#endif
    Com_BitpositionType                             Bit_Pos;
    Com_SigBuffIndexType                            SigBuff_Index;
    Com_BitsizeType                                 BitSize;
#ifdef COM_RxFilters

    Com_FilterType                                  Filter_Index;
#endif

    Com_IpduIdType                                  IpduRef;

    uint8                                           General;

    uint8                                           rxSignalFields;
}Com_Lok_xRxSigCfg_tst;

typedef const Com_Lok_xRxSigCfg_tst * Com_RxSigConstPtrType;

#ifdef COM_TX_SIGNALGROUP

# ifdef COM_TX_SIGNALGROUP_ARRAY
typedef struct{
    PduLengthType                                   FirstByteNo;
    PduLengthType                                   Length;
} Com_Lok_xTxSigGrpArrayCfg_tst;

typedef const Com_Lok_xTxSigGrpArrayCfg_tst * Com_TxSigGrpArrayConstPtrType;

# endif

typedef struct{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification

    void (*Notification_Cbk) (void);
#endif

#ifdef COM_ERRORNOTIFICATION

    void (*NotificationError_Cbk) (void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    void (*TimeOutNotification_Cbk) (void);
#endif
#endif

#ifdef COM_TxSigGrpUpdateBit
    Com_BitpositionType                             Update_Bit_Pos;
#endif
    Com_IpduIdType                                  IpduRef;
    Com_TxIntGrpSignalIdType                        FirstGrpSig_Index;
    Com_NoOfTxGrpSignalType                         No_Of_GrpSig;

#ifdef COM_TX_SIGNALGROUP_ARRAY
    Com_TxSigGrpArrayIndexType                      SigGrpArray_Index;
#endif

    uint8                                           txSignalGrpFields;
}Com_Lok_xTxSigGrpCfg_tst;

typedef const Com_Lok_xTxSigGrpCfg_tst * Com_TxSigGrpConstPtrType;

#endif

#ifdef COM_RX_SIGNALGROUP

# ifdef COM_RX_SIGNALGROUP_ARRAY
typedef struct{
    PduLengthType                                   FirstByteNo;
    Com_RxSigGrpBuffIndexType                       RxSigGrpBuf_Index;
} Com_Lok_xRxSigGrpArrayCfg_tst;

typedef const Com_Lok_xRxSigGrpArrayCfg_tst * Com_RxSigGrpArrayConstPtrType;

# endif

typedef struct{
#ifdef COM_RxSignalGrpNotify

    void (*Notification_Cbk) (void);
#endif
#ifdef COM_RxSigGrpInvalidNotify
    void (*DataInvalid_Indication_Cbk) (void);
#endif
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify

    void (*TimeOutNotification_Cbk) (void);
#endif
#endif
#ifdef COM_RxSigGrpUpdateBit
    Com_BitpositionType                             Update_Bit_Pos;
#endif
    Com_IpduIdType                                  IpduRef;

    Com_RxIntGrpSignalIdType                        FirstGrpSig_Index;

    Com_NoOfRxGrpSignalType                         No_Of_GrpSig;
#ifdef COM_SIGNALGROUPGATEWAY
    uint16                                          numOfGwSrcGrpSignals;
#endif

    PduLengthType                                   lastByte_u8;

#ifdef COM_RX_SIGNALGROUP_ARRAY
    Com_RxSigGrpArrayIndexType                      SigGrpArray_Index;
#endif

    uint8                                           rxSignalGrpFields;
}Com_Lok_xRxSigGrpCfg_tst;

typedef const Com_Lok_xRxSigGrpCfg_tst * Com_RxSigGrpConstPtrType;

#endif

#ifdef COM_TX_SIGNALGROUP

typedef struct{

#ifdef COM_TxGrpSigInvalid
    uint32                                          DataInvalid_Val;
#endif
    uint32                                          Init_Val;
    Com_BitpositionType                             Bit_Pos;
    Com_TxGrpSigBuffIndexType                       TxGrpSigBuff_Index;

    Com_TxIntSignalGroupIdType                      SigGrpRef;

    Com_BitsizeType                                 BitSize;
#ifdef COM_TxFilters

    Com_FilterType                                  Filter_Index;
    uint8                                           Filter_Algo;
#endif

#ifdef COM_EffectiveSigGrpTOC
    Com_OldValType                                  OldValue_Index;
#endif

    uint8                                           txGrpSigFields;
}Com_Lok_xTxGrpSigCfg_tst;

typedef const Com_Lok_xTxGrpSigCfg_tst * Com_TxGrpSigConstPtrType;
#endif

#ifdef COM_RX_SIGNALGROUP

typedef struct{
#ifdef COM_RxSigGrpInvalid
    uint32                                          DataInvalid_Val;
#endif
    uint32                                          Init_Val;
    Com_BitpositionType                             Bit_Pos;
    Com_RxGrpSigBuffIndexType                       RxGrpSigBuff_Index;

    Com_RxIntSignalGroupIdType                      SigGrpRef;

    Com_BitsizeType                                 BitSize;
#ifdef COM_RxFilters

    Com_FilterType                                  Filter_Index;
    uint8                                           Filter_Algo;
#endif

    uint8                                           rxGrpSigFields;
}Com_Lok_xRxGrpSigCfg_tst;

typedef const Com_Lok_xRxGrpSigCfg_tst * Com_RxGrpSigConstPtrType;
#endif

#ifdef COM_TX_IPDUCOUNTER

typedef struct{
    Com_BitpositionType                             CntrBitPos;
    uint8                                           CntrBitSize;
} Com_Lok_xTxIpduCntrCfg_tst;

typedef const Com_Lok_xTxIpduCntrCfg_tst * Com_TxIpduCntrConstPtrType;

#endif

typedef struct{
    uint8 *                                         BuffPtr;

    const Com_TransModeInfo *                       Com_TMConstPtr;
#ifdef COM_TxIPduCallOuts

    boolean (*CallOut) (PduIdType id, PduInfoType * ptr);
#endif
#ifdef COM_TxIPduNotification

    void (*Notification_Cbk) (void);
#endif

#ifdef COM_ERRORNOTIFICATION

    void (*NotificationError_Cbk) (void);
#endif

#ifdef COM_TxIPduTimeOutNotify

    void (*TimeOutNotification_Cbk) (void);
#endif

#ifdef COM_METADATA_SUPPORT
    Com_MetaDataInfoPtr                             MetaDataPtr;
#endif

    PduLengthType                                   Size;

#ifdef COM_TxIPduTimeOut
    uint16                                          Timeout_Fact;
#endif

    uint16                                          Min_Delay_Time_Fact;

    uint16                                          No_Of_Sig_Ref;
#ifdef COM_TX_SIGNALGROUP
    uint16                                          No_Of_SigGrp_Ref;
#endif
    PduIdType                                       PdurId;
    Com_TxIntSignalIdType                           TxSigId_Index;
#ifdef COM_TX_SIGNALGROUP
    Com_TxIntSignalGroupIdType                      FirstTxSigGrp_Index;
#endif

    uint16                                          txIPduFields;
#ifdef COM_TX_IPDUCOUNTER
    Com_TxCntrIdxType                               TxIpduCntr_Index;
#endif
    Com_MainFuncType                                MainFunctionRef;
    uint8                                           PaddingByte;
} Com_Lok_xTxIpduInfoCfg_tst;

typedef const Com_Lok_xTxIpduInfoCfg_tst * Com_TxIpduConstPtrType;

#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))

typedef struct{

#ifdef COM_RxUpdateTimeoutNotify
    void (*TimeOutNotification_Cbk) (void);
#endif
    uint16                                          First_Timeout;
    uint16                                          Timeout;
    uint16                                          SigId;
}Com_SignalTimeoutInfo;

typedef struct{

    const Com_SignalTimeoutInfo *                   TimeoutInfo_Ref;
    uint16 *                                        TimeoutTicks_p;
    uint8                                           numWithUpdateBit;
}Com_UpdatebitTimeoutInfo;

#endif

#ifdef COM_RX_IPDUCOUNTER
typedef struct{
    void (*CntrErrNotif_Cbk) (PduIdType Id, uint8 ExpCntr, uint8 RxCntr);
    Com_BitpositionType                             CntrBitPos;
    uint8                                           CntrBitSize;
    uint8                                           CntrThreshold;
} Com_Lok_xRxIpduCntrCfg_tst;

typedef const Com_Lok_xRxIpduCntrCfg_tst * Com_RxIpduCntrConstPtrType;

#endif

typedef struct{
    uint8 *                                         BuffPtr;

#ifdef  COM_RxSigUpdateTimeout
    const Com_UpdatebitTimeoutInfo *                SignalTimeout_Ref;
#endif

#ifdef  COM_RxSigGrpUpdateTimeout
    const Com_UpdatebitTimeoutInfo *                SignalGrpTimeout_Ref;
#endif

#ifdef COM_RxIPduCallOuts
    boolean (*CallOut) (PduIdType id, const PduInfoType * ptr);
#endif

#ifdef COM_RxIPduTimeoutNotify
    void (*TimeOutNotification_Cbk) (void);
#endif

#ifdef COM_RxIPduNotification
    void (*RxNotification_Cbk) (void);
#endif

    PduLengthType                                   Size;
#ifdef COM_RxIPduTimeout
    uint16                                          FirstTimeout_Factor;
    uint16                                          Timeout_Fact;
#endif
    uint16                                          No_Of_Sig_Ref;
#ifdef COM_RX_SIGNALGROUP
    uint16                                          No_Of_SigGrp_Ref;
#endif
    Com_RxIntSignalIdType                           RxSigId_Index;
#ifdef COM_RX_SIGNALGROUP
    Com_RxIntSignalGroupIdType                      FirstRxSigGrp_Index;
#endif
#ifdef COM_SIGNALGATEWAY
    uint16                                          numOfGwSrcSignals;
#endif
#ifdef COM_SIGNALGROUPGATEWAY
    uint16                                          numOfGwSrcSignalGrps;
#endif

#ifdef COM_RX_IPDUCOUNTER
    Com_RxCntrIdxType                               RxIpduCntr_Index;
#endif

    Com_MainFuncType                                MainFunctionRef;

    uint8                                           rxIPduFields;
} Com_Lok_xRxIpduInfoCfg_tst;

typedef const Com_Lok_xRxIpduInfoCfg_tst * Com_RxIpduConstPtrType;

typedef struct{
    uint16                                          FirstIpdu_Index;
    uint16                                          NoOfRxPdus;
} Com_Lok_xIpduGrpInfoCfg_tst;

typedef const Com_Lok_xIpduGrpInfoCfg_tst * Com_IPduGrpConstPtrType;

typedef struct{
    uint8                                           txSigRAMFields;
}Com_TxSignalFlagType;

typedef Com_TxSignalFlagType * Com_TxSigRamPtrType;

#ifdef COM_TX_SIGNALGROUP

typedef struct{
    uint8                                           txGrpSigRAMFields;
}Com_TxGrpSignalFlagType;

typedef Com_TxGrpSignalFlagType * Com_TxGrpSigRamPtrType;

#endif

typedef struct{
    uint8                                           rxSigRAMFields;
}Com_RxSignalFlagType;

typedef Com_RxSignalFlagType * Com_RxSigRamPtrType;

#ifdef COM_RX_SIGNALGROUP

typedef struct{
    uint8                                           rxSigGrpRAMFields;
}Com_RxSignalGrpFlagType;

typedef Com_RxSignalGrpFlagType * Com_RxSigGrpRamPtrType;
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

typedef struct{
    uint8                                           txSigGrpRAMFields;
}Com_TxSignalGrpFlagType;

typedef Com_TxSignalGrpFlagType * Com_TxSigGrpRamPtrType;
#endif
#endif

typedef struct{
    Com_TMConstPtrType                              CurrentTxModePtr;
#ifdef COM_TP_IPDUTYPE
    PduLengthType                                   TxTPIPduLength;
#endif
    uint16                                          Com_MinDelayTick;
    uint16                                          Com_Tick_Tx;
#ifdef COM_TxFilters
    uint16                                          Com_TMSTrueCounter_u16;
#endif
    uint16                                          Com_n_Tick_Tx;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    uint16                                          Com_DynLength;
#endif
#ifdef COM_TxIPduTimeOut
    uint16                                          Com_TickTxTimeout;
#endif

    uint16                                          Com_TxFlags;
    uint8                                           Com_n;

    uint8                                           Com_TransMode;
} Com_TxIpduRamData;

typedef Com_TxIpduRamData * Com_TxIpduRamPtrType;

typedef struct{
    PduLengthType                                   RxIPduLength;
#ifdef COM_TP_IPDUTYPE
    PduLengthType                                   RxTPIPduLength;
#endif
#ifdef COM_RxIPduTimeout
    uint16                                          RxTicks_u16;
# ifdef COM_RX_DUAL_CYCLE_SUPPPORT
    uint16                                          RxDualCycTicks_u16;
# endif
#endif

    uint8                                           RxFlags;
} Com_RxIpduRamData;

typedef Com_RxIpduRamData * Com_RxIpduRamPtrType;

typedef struct{
    PduIdType *                                     RxGwQueuePtr;
    Com_RxGwQueueIndexType                          Com_RxGwQueueWrite_ux;
    Com_RxGwQueueIndexType                          Com_RxGwQueueRead_ux;
}Com_RxGwQueueRAMType;

typedef Com_RxGwQueueRAMType * Com_RxGwQueuePtrType;

typedef struct{
    Com_SignalIdType                                indexGwMapSigDestIdArray;
    uint8                                           destCount;
}Com_Lok_xGwMapSigCfg_tst;

typedef const Com_Lok_xGwMapSigCfg_tst * Com_GwMapSigConfPtrType;

typedef struct{
    Com_SignalIdType                                GwMap_DestId;
}Com_Lok_xGwMapSigIdCfg_tst;

typedef const Com_Lok_xGwMapSigIdCfg_tst * Com_GwMapSigIdConfPtrType;

#ifdef COM_TX_SIGNALGROUP
typedef struct{
    Com_TxIntGrpSignalIdType                        indexGwMapGrpSigDestIdArray;
    uint8                                           destCount;
}Com_Lok_xGwMapGrpSigCfg_tst;

typedef const Com_Lok_xGwMapGrpSigCfg_tst * Com_GwMapGrpSigConfPtrType;

typedef struct{
    Com_TxIntGrpSignalIdType                        GwMap_DestGrpSigId;
}Com_Lok_xGwMapGrpSigIdCfg_tst;

typedef const Com_Lok_xGwMapGrpSigIdCfg_tst * Com_GwMapGrpSigIdConfPtrType;
#endif

typedef struct{
    Com_IpduIdType                                  StartIPduId;
    Com_NumOfIpdusType                              NumOfIpdus;
    Com_TimeBaseType                                TimeBaseInMs;
} Com_MainFunctionCfgType;

typedef struct{
    uint8 *                                         Com_SigType_pu8;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
    uint8 *                                         Com_SigType_dyn_pu8;
#endif

    uint16 *                                        Com_SigType_pu16;

    uint32 *                                        Com_SigType_pu32;

#ifdef COM_RXSIG_INT64
    uint64 *                                        Com_SigType_pu64;
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
    float64 *                                       Com_SigType_pf64;
#endif

#ifdef COM_RX_SIGNALGROUP
    uint8 *                                         Com_RxGrpSigType_pu8;

    uint16 *                                        Com_RxGrpSigType_pu16;

    uint32 *                                        Com_RxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    uint64 *                                        Com_RxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    float64 *                                       Com_RxGrpSigType_pf64;
#endif

    uint8 *                                         Com_SecondRxGrpSigType_pu8;

    uint16 *                                        Com_SecondRxGrpSigType_pu16;

    uint32 *                                        Com_SecondRxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    uint64 *                                        Com_SecondRxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    float64 *                                       Com_SecondRxGrpSigType_pf64;
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY
    uint8 *                                         Com_RxSigGrpArrayBuf_pu8;
#endif

#endif

#ifdef COM_RxIPduDeferredProcessing
    uint8 *                                         Com_DeferredBuffer_pu8;
#endif
} Com_Lok_xRxRamBuf_tst;

#ifdef COM_TX_SIGNALGROUP
typedef struct{
    uint8 *                                         Com_TxGrpSigType_pu8;

    uint16 *                                        Com_TxGrpSigType_pu16;

    uint32 *                                        Com_TxGrpSigType_pu32;

#ifdef COM_TXGRPSIG_INT64
    uint64 *                                        Com_TxGrpSigType_pu64;
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
    float64 *                                       Com_TxGrpSigType_pf64;
#endif
} Com_Lok_xTxSigGrpRamBuf_tst;
#endif

typedef struct{
    const Com_Lok_xTxSigCfg_tst *                   Com_TxSig_pcst;

    const Com_SignalIdType *                        Com_TxSignalMapping_pct;

    const Com_Lok_xRxSigCfg_tst *                   Com_RxSig_pcst;

    const Com_SignalIdType *                        Com_RxSignalMapping_pct;

#ifdef COM_TX_SIGNALGROUP
    const Com_Lok_xTxSigGrpCfg_tst *                Com_TxSigGrp_pcst;

    const Com_SignalGroupIdType *                   Com_TxSignalGrpMapping_pct;

#endif

#ifdef  COM_RX_SIGNALGROUP
    const Com_Lok_xRxSigGrpCfg_tst *                Com_RxSigGrp_pcst;

    const Com_SignalGroupIdType *                   Com_RxSignalGrpMapping_pct;

#endif

#ifdef COM_TX_SIGNALGROUP
    const Com_Lok_xTxGrpSigCfg_tst *                Com_TxGrpSig_pcst;

    const Com_SignalIdType *                        Com_TxGrpSignalMapping_pct;
#endif

#ifdef COM_RX_SIGNALGROUP
    const Com_Lok_xRxGrpSigCfg_tst *                Com_RxGrpSig_pcst;

    const Com_SignalIdType *                        Com_RxGrpSignalMapping_pct;
#endif

    const Com_Lok_xTxIpduInfoCfg_tst *              Com_TxIpdu_pcst;

    const PduIdType *                               Com_TxIpduMapping_pcst;

    const Com_Lok_xRxIpduInfoCfg_tst *              Com_RxIpdu_pcst;

    const PduIdType *                               Com_RxIpduMapping_pcst;

    const Com_Lok_xIpduGrpInfoCfg_tst *             Com_IpduGrp_pcst;

    const uint16 *                                  Com_IpduGrpMapping_pcu16;

#ifdef COM_SIGNALGATEWAY
    const Com_Lok_xGwMapSigCfg_tst *                Com_GwSig_pcst;

    const Com_Lok_xGwMapSigIdCfg_tst *              Com_GwSigIdMapping_pcst;
#endif

#ifdef COM_SIGNALGROUPGATEWAY
    const Com_Lok_xGwMapGrpSigCfg_tst *             Com_GwGrpSig_pcst;

    const Com_Lok_xGwMapGrpSigIdCfg_tst *           Com_GwGrpSigIdMapping_pcst;
#endif

    const Com_IpduIdType *                          Com_IPduGrp_IpduRef_pcst;

#if defined ( COM_TX_SIGNALGROUP_ARRAY )
    Com_TxSigGrpArrayConstPtrType                   Com_TxSigGrpArray_pcst;
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )
    Com_RxSigGrpArrayConstPtrType                   Com_RxSigGrpArray_pcst;
#endif

#if defined(COM_TXSIG_FLOAT64SUPP ) || defined(COM_TXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXSIG_FLOAT64SUPP)
    const float64 *                                 floatValArray_pcaf64;
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)
    const Com_MaskXType *                           Com_MaskX_pcst;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    const uint32 *                                  Com_Mask_pu32;
#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
    const Com_POSMinMaxType *                       Com_POSMinMax_pcst;
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
    const Com_NEGMinMaxType *                       Com_NEGMinMax_pcst;
#endif

    const Com_MainFunctionCfgType *                 Com_MainFunctionCfg_pcst;

    const Com_Lok_xRxRamBuf_tst *                   Com_RxRamBuf_pcst;

#ifdef COM_TX_SIGNALGROUP
    const Com_Lok_xTxSigGrpRamBuf_tst *             Com_TxSigGrpRamBuf_pcst;
#endif

#ifdef COM_TX_IPDUCOUNTER
    const Com_Lok_xTxIpduCntrCfg_tst *              Com_TxIpduCntr_pcst;
#endif

#ifdef COM_RX_IPDUCOUNTER
    const Com_Lok_xRxIpduCntrCfg_tst *              Com_RxIpduCntr_pcst;
#endif

#ifdef COM_F_ONEEVERYN
    const Com_OneEveryNType *                       Com_OneEveryN_Const_pcst;

    Com_OneEveryNType *                             Com_OneEveryN_pe;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    uint32 *                                        Com_F_OldVal_pu32;
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)
    Com_OldValTrigOnChngType *                      Com_OldValTrigOnChng_puo;
#endif

#ifdef COM_TP_IPDUTYPE

    PduLengthType *                                 Com_TpTxIpduLength_pauo;
#endif

    Com_TxIpduRamData *                             Com_TxIpduRam_ps;

    Com_RxIpduRamData *                             Com_RxIpduRam_ps;

    Com_TxSignalFlagType *                          Com_TxSignalFlag_ps;

    Com_RxSignalFlagType *                          Com_RxSignalFlag_ps;

    uint8 *                                         Com_IpduCounter_ps;

# if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
    uint8 *                                         Com_IpduCounter_DM_ps;
# endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    PduIdType *                                     Com_RxGwQueue_paux;

    Com_RxGwQueueRAMType *                          Com_RxGwQueue_ps;
#endif

#ifdef COM_RX_SIGNALGROUP
    Com_RxSignalGrpFlagType *                       Com_RxSignalGrpFlag_ps;
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)
    Com_TxSignalGrpFlagType *                       Com_TxSignalGrpFlag_ps;
#endif

    Com_TxGrpSignalFlagType *                       Com_TxGrpSignalFlag_ps;
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    boolean *                                       Com_IsGwSignalsUpdated_pab;
#endif

#ifdef COM_TX_IPDUCOUNTER
    uint8 *                                         Com_TxIpduCntrVal_pau8;
#endif

#ifdef COM_RX_IPDUCOUNTER
    uint8 *                                         Com_RxIpduLastCntrVal_pau8;
#endif

    const uint16                                    noOfIpduGroup;

    const Com_IpduIdType                            noOfIpdusInLastIpduGrp;

    const Com_SignalIdType                          noOfTxSignals;

    const Com_SignalIdType                          noOfRxSignals;

    const Com_SignalGroupIdType                     noOfTxSignalGroup;

    const Com_SignalGroupIdType                     noOfRxSignalGroup;

    const Com_GrpSignalIdType                       noOfTxGroupSignal;

    const Com_GrpSignalIdType                       noOfRxGroupSignal;

    const Com_IpduIdType                            noOfTxIpdu;

    const Com_IpduIdType                            noOfRxIpdu;

    const Com_SignalIdType                          noOfGwSrcSignals;

    const Com_GrpSignalIdType                       noOfGwSrcGrpSignals;

    const Com_IpduIdType                            noOfGwSrcIpdu;

    const Com_GrpSignalIdType                       noOfGrpSigNoGw;

#ifdef COM_F_ONEEVERYN
    const uint8                                     noOfOneEveryNSigAndGrpSig;
#endif
} Com_ConfigData_tst;

#endif

