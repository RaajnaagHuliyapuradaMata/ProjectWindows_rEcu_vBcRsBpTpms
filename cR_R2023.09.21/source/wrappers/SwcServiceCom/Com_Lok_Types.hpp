#ifndef COM_PRV_TYPES_H
#define COM_PRV_TYPES_H

typedef struct{
   unsigned int isEventTrig                   : 1;
   unsigned int isTriggerIpduSendWithMetadata : 1;
   unsigned int isGwIpduSend                  : 1;
   unsigned int isModeChangd                  : 1;
   unsigned int sigTransProp                  : 1;
   unsigned int isTimeoutReq                  : 1;
   unsigned int ignoreRepetitions             : 1;
}Com_SendIpduInfo;

typedef struct{
   uint16              TimePeriodFact;
   uint16              TimeOffsetFact;
   uint16              RepetitionPeriodFact;
   uint8               NumOfRepetitions;
   uint8               Mode;
}Type_CfgSwcServiceCom_stInfoModeTrans;

typedef P2CONST(Type_CfgSwcServiceCom_stInfoModeTrans, AUTOMATIC, COM_APPL_CONST)  Com_TMConstPtrType;

typedef struct{
   uint32                  Init_Val;
   uint16                  txSignalFields;
   Com_BitpositionType     Bit_Pos;
   Com_BitsizeType         BitSize;
   Type_CfgSwcServiceCom_tIdIPdu          IpduRef;
   uint8         General;
}Type_CfgSwcServiceCom_stInfoSignalTx;

typedef P2CONST (Type_CfgSwcServiceCom_stInfoSignalTx, AUTOMATIC, COM_APPL_CONST) Com_TxSigConstPtrType;

typedef struct{
   uint32                  Init_Val;
   Com_BitpositionType     Bit_Pos;
   Com_SigBuffIndexType    SigBuff_Index;
   Com_BitsizeType         BitSize;
   Type_CfgSwcServiceCom_tIdIPdu          IpduRef;
   uint8         General;
   uint8         rxSignalFields;
}Type_CfgSwcServiceCom_stInfoSignalRx;

typedef P2CONST (Type_CfgSwcServiceCom_stInfoSignalRx, AUTOMATIC, COM_APPL_CONST) Com_RxSigConstPtrType;

typedef struct{
     P2VAR(uint8,                                 TYPEDEF,       COM_APPL_DATA   ) BuffPtr;
   P2CONST(Type_CfgSwcServiceCom_stInfoModeTrans, TYPEDEF,       COM_APPL_CONST  ) Com_TMConstPtr;
    P2FUNC(boolean,                               COM_APPL_CODE, CallOut         )(Type_SwcServiceCom_tIdPdu, P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, COM_APPL_DATA));
    P2FUNC(void,                                  COM_APPL_CODE, Notification_Cbk)(void);
           Type_SwcServiceCom_tLengthPdu                                           Size;
           uint16                                                                  Timeout_Fact;
           uint16                                                                  Min_Delay_Time_Fact;
           uint16                                                                  No_Of_Sig_Ref;
           Type_SwcServiceCom_tIdPdu                                               PdurId;
           Com_TxIntSignalIdType                                                   TxSigId_Index;
           uint16                                                                  txIPduFields;
           Com_MainFuncType                                                        MainFunctionRef;
           uint8                                                                   PaddingByte;
}Type_CfgSwcServiceCom_stInfoIpduTx;

typedef P2CONST(Type_CfgSwcServiceCom_stInfoIpduTx, AUTOMATIC, COM_APPL_CONST) Com_TxIpduConstPtrType;

typedef struct{
   P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                        BuffPtr;
   P2FUNC(boolean, COM_APPL_CODE, CallOut)(Type_SwcServiceCom_tIdPdu, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, COM_APPL_CONST));
   Type_SwcServiceCom_tLengthPdu                   Size;
   uint16                          No_Of_Sig_Ref;
   Com_RxIntSignalIdType           RxSigId_Index;
   Com_MainFuncType                MainFunctionRef;
   uint8                           rxIPduFields;
}Type_CfgSwcServiceCom_stInfoIpduRx;

typedef P2CONST(Type_CfgSwcServiceCom_stInfoIpduRx, AUTOMATIC, COM_APPL_CONST) Com_RxIpduConstPtrType;

typedef struct{
   uint16 FirstIpdu_Index;
   uint16 NoOfRxPdus;
}Type_CfgSwcServiceCom_stInfoIpduGrp;

typedef P2CONST(Type_CfgSwcServiceCom_stInfoIpduGrp, AUTOMATIC, COM_APPL_CONST) Com_IPduGrpConstPtrType;

typedef struct{
   uint8 txSigRAMFields;
}Com_TxSignalFlagType;

typedef P2VAR(Com_TxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxSigRamPtrType;

typedef struct{
   uint8 rxSigRAMFields;
}Com_RxSignalFlagType;

typedef P2VAR(Com_RxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_RxSigRamPtrType;

typedef struct{
   Com_TMConstPtrType  CurrentTxModePtr;
   uint16              Com_MinDelayTick;
   uint16              Com_Tick_Tx;
   uint16              Com_n_Tick_Tx;
   uint16              Com_TickTxTimeout;
   uint16              Com_TxFlags;
   uint8               Com_n;
   uint8               Com_TransMode;
}Com_TxIpduRamData;

typedef P2VAR(Com_TxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_TxIpduRamPtrType;

typedef struct{
   Type_SwcServiceCom_tLengthPdu   RxIPduLength;
   uint8  RxFlags;
}Com_RxIpduRamData;

typedef P2VAR(Com_RxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_RxIpduRamPtrType;

typedef struct{
   P2VAR(Type_SwcServiceCom_tIdPdu, TYPEDEF, COM_APPL_DATA) RxGwQueuePtr;
   VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueWrite_ux;
   VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueRead_ux;
}Com_RxGwQueueRAMType;

typedef P2VAR(Com_RxGwQueueRAMType, AUTOMATIC, COM_APPL_DATA)  Com_RxGwQueuePtrType;

typedef struct{
   Com_SignalIdType indexGwMapSigDestIdArray;
   uint8            destCount;
}Com_Lok_xGwMapSigCfg_tst;

typedef P2CONST(Com_Lok_xGwMapSigCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigConfPtrType;

typedef struct{
   Com_SignalIdType GwMap_DestId;
}Com_Lok_xGwMapSigIdCfg_tst;

typedef P2CONST(Com_Lok_xGwMapSigIdCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigIdConfPtrType;

typedef struct{
   Type_CfgSwcServiceCom_tIdIPdu          StartIPduId;
   Com_NumOfIpdusType      NumOfIpdus;
   Com_TimeBaseType        TimeBaseInMs;
}Type_CfgSwcServiceCom_stMainFunction;

typedef struct{
   P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SigType_pu8;
   P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu16;
   P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu32;
}Type_CfgSwcServiceCom_stBufferRamRx;

typedef struct{
   P2CONST(Type_CfgSwcServiceCom_stInfoSignalTx, COM_CONST, COM_APPL_CONST)             Com_TxSig_pcst;
   P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_TxSignalMapping_pct;
   P2CONST(Type_CfgSwcServiceCom_stInfoSignalRx, COM_CONST, COM_APPL_CONST)             Com_RxSig_pcst;
   P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_RxSignalMapping_pct;
   P2CONST(Type_CfgSwcServiceCom_stInfoIpduTx, COM_CONST, COM_APPL_CONST)        Com_TxIpdu_pcst;
   P2CONST(Type_SwcServiceCom_tIdPdu, COM_CONST, COM_APPL_CONST)                         Com_TxIpduMapping_pcst;
   P2CONST(Type_CfgSwcServiceCom_stInfoIpduRx, COM_CONST, COM_APPL_CONST)        Com_RxIpdu_pcst;
   P2CONST(Type_SwcServiceCom_tIdPdu, COM_CONST, COM_APPL_CONST)                         Com_RxIpduMapping_pcst;
   P2CONST(Type_CfgSwcServiceCom_stInfoIpduGrp, COM_CONST, COM_APPL_CONST)       Com_IpduGrp_pcst;
   P2CONST(uint16, COM_CONST, COM_APPL_CONST)                            Com_IpduGrpMapping_pcu16;
   P2CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST, COM_APPL_CONST)                    Com_IPduGrp_IpduRef_pcst;
   P2CONST(Type_CfgSwcServiceCom_stMainFunction, COM_CONST, COM_APPL_CONST)           Com_MainFunctionCfg_pcst;
   P2CONST(Type_CfgSwcServiceCom_stBufferRamRx, COM_CONST, COM_APPL_CONST)             Com_RxRamBuf_pcst;
   P2VAR(Com_TxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_TxIpduRam_ps;
   P2VAR(Com_RxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_RxIpduRam_ps;
   P2VAR(Com_TxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_TxSignalFlag_ps;
   P2VAR(Com_RxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_RxSignalFlag_ps;
   P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_ps;
   P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_DM_ps;
   CONST(uint16, COM_CONST)                                              noOfIpduGroup;
   CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST)                                      noOfIpdusInLastIpduGrp;
   CONST(Com_SignalIdType, COM_CONST)                                    noOfTxSignals;
   CONST(Com_SignalIdType, COM_CONST)                                    noOfRxSignals;
   CONST(Com_SignalGroupIdType, COM_CONST)                               noOfTxSignalGroup;
   CONST(Com_SignalGroupIdType, COM_CONST)                               noOfRxSignalGroup;
   CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfTxGroupSignal;
   CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfRxGroupSignal;
   CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST)                                      noOfTxIpdu;
   CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST)                                      noOfRxIpdu;
   CONST(Com_SignalIdType, COM_CONST)                                    noOfGwSrcSignals;
   CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGwSrcGrpSignals;
   CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST)                                      noOfGwSrcIpdu;
   CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGrpSigNoGw;
}Com_ConfigData_tst;

#endif

