#ifndef COM_PRV_H
#define COM_PRV_H

#include "Com.hpp"
#include "Com_Cfg_Internal.hpp"
#include "Com_Cfg_SchM.hpp"
#include "Com_Lok_Types.hpp"
#include "rba_BswSrv.hpp"
#include "Com_PBcfg.hpp"
#include "Det.hpp"
#include "Bfx.hpp"

#define COM_BOOL_TO_UNSIGNED(BoolValue)  ((BoolValue) ? (COM_SET) : (COM_RESET))
#define COM_LITTLEENDIAN                                                      0u
#define COM_BIGENDIAN                                                         1u
#define COM_OPAQUE                                              COM_LITTLEENDIAN
#define COM_CPU_ENDIANNESS                                      COM_LITTLEENDIAN
#define COM_IMMEDIATE                                                      FALSE
#define COM_DEFERRED                                                        TRUE
#define COM_TRIGGERED_ON_CHANGE                                               0u
#define COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION                            1u
#define COM_PENDING                                                           2u
#define COM_TRIGGERED_WITHOUT_REPETITION                                      3u
#define COM_TRIGGERED                                                         4u
#define COM_SIG_TP_IS_TRIGGERED(TransProp)             (TransProp > COM_PENDING)
#define COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TransProp)   (TransProp < COM_PENDING)
#define COM_SIG_TP_IS_WITHOUT_REPETITION(TransProp)   ((TransProp & 0x1u) != 0u)
#define COM_RESET                                                             0u
#define COM_SET                                                               1u
#define COM_REPLACE_TO_INIT                                                   2u
#define COM_STOP                                                           FALSE
#define COM_START                                                           TRUE
#define COM_TXMODE_DIRECT                                                  0x00u
#define COM_TXMODE_MIXED                                                   0x01u
#define COM_TXMODE_NONE                                                    0x02u
#define COM_TXMODE_PERIODIC                                                0x03u
#define COM_CLRUPDATEBIT_TRANSMIT                                             1u
#define COM_CLRUPDATEBIT_TRIGGERTRANSMIT                                      2u
#define COM_CLRUPDATEBIT_CONFIRMATION                                         3u
#define COM_CLRUPDATEBIT_NONE                                                 0u
#define COM_TRUE                                                            TRUE
#define COM_FALSE                                                          FALSE
#define COM_NONE                                                              0u
#define COM_REPLACE                                                           1u
#define COM_NOTIFY                                                            2u
#define COM_NOT_USED                                                          0u
#define COM_MAXIMUM_GWSYNC_REPITIONS                                           2
#define COM_ZERO                                                              0u
#define COM_ONE                                                               1u
#define COM_TWO                                                               2u
#define COM_UINT8                                                          0x00u
#define COM_SINT8                                                          0x01u
#define COM_UINT16                                                         0x02u
#define COM_SINT16                                                         0x03u
#define COM_UINT32                                                         0x04u
#define COM_SINT32                                                         0x05u
#define COM_UINT64                                                         0x10u
#define COM_SINT64                                                         0x11u
#define COM_BOOLEAN                                                        0x06u
#define COM_UNDEFTYPE                                                      0x07u
#define COM_UINT8_N                                                        0x08u
#define COM_UINT8_DYN                                                      0x0Au
#define COM_FLOAT32                                                        0x0Cu
#define COM_FLOAT64                                                        0x0Eu
#define COM_ALWAYS                                                            0u
#define COM_NEVER                                                             1u
#define COM_MASKED_NEW_EQUALS_X                                               2u
#define COM_MASKED_NEW_DIFFERS_X                                              3u
#define COM_MASKED_NEW_DIFFERS_MASKED_OLD                                     4u
#define COM_NEW_IS_WITHIN_POS                                                 5u
#define COM_NEW_IS_WITHIN_NEG                                                 6u
#define COM_NEW_IS_OUTSIDE_POS                                                7u
#define COM_NEW_IS_OUTSIDE_NEG                                                8u
#define COM_ONE_EVERY_N                                                       9u
#define COM_NOTCONFIGURED                                                    10u
#define COM_MODE_VALID                                                        0u
#define COM_TRUEMODE_VALID                                                    1u
#define COM_FALSEMODE_VALID                                                   2u
#define COM_CLEAR_SENDIPDU_FLAGS                                 {0,0,0,0,0,0,0}
#define UPDATEBIT_NOT_APPLICABLE                                           0x00u
#define UPDATEBIT_APPLICABLE                                               0x01u
#define UPDATEBIT_SET                                                      0x02u
#define COM_DET_NO_ERROR                                                   0xFFu
#define COM_REPORT_ERROR_CHECK(API, ERROR)   (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, (API), (ERROR))
#define Com_PerformSignExtension(Value,Size)    (Value) | (COM_SIGN_EXT_MASK << ((Size) - 1))
#define Com_SetRamValue_TXIPDU_PDUSTATUS(ByteValue,BitVal)           Bfx_PutBit_u16u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_PDUSTATUS(ByteValue)                  Bfx_GetBit_u16u8_u8((ByteValue),0)
#define Com_SetRamValue_TXIPDU_CONFIR(ByteValue,BitVal)              Bfx_PutBit_u16u8u8(&(ByteValue),1,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_CONFIR(ByteValue)                     Bfx_GetBit_u16u8_u8((ByteValue),1)
#define Com_SetRamValue_TXIPDU_TICKTXTO(ByteValue,BitVal)            Bfx_PutBit_u16u8u8(&(ByteValue),2,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_TICKTXTO(ByteValue)                   Bfx_GetBit_u16u8_u8((ByteValue),2)
#define Com_SetRamValue_TXIPDU_MDT(ByteValue,BitVal)                 Bfx_PutBit_u16u8u8(&(ByteValue),3,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_MDT(ByteValue)                        Bfx_GetBit_u16u8_u8((ByteValue),3)
#define Com_SetRamValue_TXIPDU_EVENTTRIG(ByteValue,BitVal)           Bfx_PutBit_u16u8u8(&(ByteValue),4,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_EVENTTRIG(ByteValue)                  Bfx_GetBit_u16u8_u8((ByteValue),4)
#define Com_SetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),5,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue)                Bfx_GetBit_u16u8_u8((ByteValue),5)
#define Com_SetRamValue_TXIPDU_ISTOENABLED(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),6,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_ISTOENABLED(ByteValue)                Bfx_GetBit_u16u8_u8((ByteValue),6)
#define Com_SetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue,BitVal)     Bfx_PutBit_u16u8u8(&(ByteValue),7,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue)            Bfx_GetBit_u16u8_u8((ByteValue),7)
#define Com_SetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue,BitVal)    Bfx_PutBit_u16u8u8(&(ByteValue),8,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue)           Bfx_GetBit_u16u8_u8((ByteValue),8)
#define Com_SetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue,BitVal)    Bfx_PutBit_u16u8u8(&(ByteValue),9,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue)           Bfx_GetBit_u16u8_u8((ByteValue),9)
#define Com_SetRamValue_RXIPDU_PDUSTATUS(ByteValue,BitVal)           Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_RXIPDU_PDUSTATUS(ByteValue)                  Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_RXIPDU_DMSTATUS(ByteValue,BitVal)            Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#define Com_GetRamValue_RXIPDU_DMSTATUS(ByteValue)                   Bfx_GetBit_u8u8_u8((ByteValue),1)
#define Com_SetRamValue_RXIPDU_INDICATION(ByteValue,BitVal)          Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#define Com_GetRamValue_RXIPDU_INDICATION(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),2)
#define Com_SetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue,BitVal) Bfx_PutBit_u8u8u8(&(ByteValue),3,(boolean)(BitVal))
#define Com_GetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue)        Bfx_GetBit_u8u8_u8((ByteValue),3)
#define Com_SetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue,BitVal)     Bfx_PutBit_u8u8u8(&(ByteValue),4,(boolean)(BitVal))
#define Com_GetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue)            Bfx_GetBit_u8u8_u8((ByteValue),4)
#define Com_SetRamValue_TXIPDU_LATESTMODE(ByteValue,BitVal)          Bfx_PutBits_u8u8u8u8(&(ByteValue),0,2,(BitVal))
#define Com_GetRamValue_TXIPDU_LATESTMODE(ByteValue)                 Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#define Com_SetRamValue_TXIPDU_TXMODESTATE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2,(BitVal))
#define Com_GetRamValue_TXIPDU_TXMODESTATE(ByteValue)                Bfx_GetBit_u8u8_u8((ByteValue),2)
#define Com_SetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue,BitVal)     Bfx_PutBit_u8u8u8(&(ByteValue),3,(boolean)(BitVal))
#define Com_GetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue)            Bfx_GetBit_u8u8_u8((ByteValue),3)
#define Com_SetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue,BitVal)        Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue)               Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#define Com_GetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue)                Bfx_GetBit_u8u8_u8((ByteValue),1)
#define Com_SetRamValue_RXSIGGRP_SIGNOTIF(ByteValue,BitVal)          Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_RXSIGGRP_SIGNOTIF(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue,BitVal)     Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#define Com_GetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue)            Bfx_GetBit_u8u8_u8((ByteValue),1)
#define Com_SetRamValue_RXSIGGRP_DMFILTERING(ByteValue,BitVal)       Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#define Com_GetRamValue_RXSIGGRP_DMFILTERING(ByteValue)              Bfx_GetBit_u8u8_u8((ByteValue),2)
#define Com_SetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue,BitVal)       Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue)              Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_TXSIG_SIGCHNGMODE(ByteValue,BitVal)          Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_TXSIG_SIGCHNGMODE(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_RXSIG_SIGNOTIF(ByteValue,BitVal)             Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#define Com_GetRamValue_RXSIG_SIGNOTIF(ByteValue)                    Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_SetRamValue_RXSIG_SIGNALFILLBIT(ByteValue,BitVal)        Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#define Com_GetRamValue_RXSIG_SIGNALFILLBIT(ByteValue)               Bfx_GetBit_u8u8_u8((ByteValue),1)
#define Com_SetRamValue_RXSIG_DMFILTERING(ByteValue,BitVal)          Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#define Com_GetRamValue_RXSIG_DMFILTERING(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),2)
#define Com_GetValue_TXIPDU_SIGPROC(ByteValue)                       Bfx_GetBit_u16u8_u8((ByteValue),0)
#define Com_GetValue_TXIPDU_TMS(ByteValue)                           Bfx_GetBits_u16u8u8_u16((ByteValue),1,2)
#define Com_GetValue_TXIPDU_NONETOSTATUS(ByteValue)                  Bfx_GetBit_u16u8_u8((ByteValue),3)
#define Com_GetValue_TXIPDU_CLRUPDBIT(ByteValue)                     Bfx_GetBits_u16u8u8_u16((ByteValue),4,2)
#define Com_GetValue_TXIPDU_FILTEREVALREQ(ByteValue)                 Bfx_GetBit_u16u8_u8((ByteValue),6)
#define Com_GetRamValue_TXIPDU_ISDYNIPDU(ByteValue)                  Bfx_GetBit_u16u8_u8((ByteValue),7)
#define Com_GetValue_TXIPDU_ISGWPDU(ByteValue)                       Bfx_GetBit_u16u8_u8((ByteValue),8)
#define Com_GetValue_TXIPDU_ISCALLOUTFRMTRIGTRANS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),9)
#define Com_GetValue_TXIPDU_ISLARGEDATAPDU(ByteValue)                Bfx_GetBit_u16u8_u8((ByteValue),10)
#define Com_GetValue_TXIPDU_ISCANCELTRANSMITSUPPORTED(ByteValue)     Bfx_GetBit_u16u8_u8((ByteValue),11)
#define Com_GetValue_TXIPDU_DEFAULTTMSSTATUS(ByteValue)              Bfx_GetBit_u16u8_u8( ( ByteValue ), 13 )
#define Com_GetValue_TXIPDU_PDUWITHPDUGRP(ByteValue)                 Bfx_GetBit_u16u8_u8( ( ByteValue ), 14 )
#define Com_GetValue_RXIPDU_SIGPROC(ByteValue)                       Bfx_GetBit_u8u8_u8((ByteValue),0)
#define Com_GetValue_RXIPDU_NOTIFCBK(ByteValue)                      Bfx_GetBit_u8u8_u8((ByteValue),1)
#define Com_GetValue_RXSIG_INVACTION(ByteValue)                      Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#define Com_GetValue_RXSIG_FILTRALG(ByteValue)                       Bfx_GetBits_u8u8u8_u8((ByteValue),2,4)
#define Com_GetValue_RXSIG_TOACTION(ByteValue)                       Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_GetValue_RXSIG_ISGWSIG(ByteValue)                        Bfx_GetBit_u8u8_u8((ByteValue),7)
#define Com_GetValue_TXSIG_TP(ByteValue)                             Bfx_GetBits_u16u8u8_u16((ByteValue),0,3)
#define Com_GetValue_TXSIG_FILTRALG(ByteValue)                       Bfx_GetBits_u16u8u8_u16((ByteValue),3,4)
#define Com_GetValue_TXSIG_INVACTION(ByteValue)                      Bfx_GetBit_u16u8_u8((ByteValue),7)
#define Com_GetValue_TXSIG_TOENABLED(ByteValue)                      Bfx_GetBit_u16u8_u8((ByteValue),8)
#define Com_GetValue_TXSIGGRP_TP(ByteValue)                          Bfx_GetBits_u8u8u8_u8((ByteValue),0,3)
#define Com_GetValue_TXSIGGRP_TOENABLED(ByteValue)                   Bfx_GetBit_u8u8_u8((ByteValue),3)
#define Com_GetValue_TXSIGGRP_FILTEREVALREQ(ByteValue)               Bfx_GetBit_u8u8_u8((ByteValue),4)
#define Com_GetValue_TXSIGGRP_UPDBITCONF(ByteValue)                  Bfx_GetBit_u8u8_u8((ByteValue),5)
#define Com_GetValue_TXSIGGRP_ARRAYACCESS(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_GetValue_RXSIGGRP_INVACTION(ByteValue)                   Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#define Com_GetValue_RXSIGGRP_TOACTION(ByteValue)                    Bfx_GetBit_u8u8_u8((ByteValue),2)
#define Com_GetValue_RXSIGGRP_ISGWSIGGRP(ByteValue)                  Bfx_GetBit_u8u8_u8((ByteValue),3)
#define Com_GetValue_RXSIGGRP_UPDBITCONF(ByteValue)                  Bfx_GetBit_u8u8_u8((ByteValue),4)
#define Com_GetValue_RXSIGGRP_ARRAYACCESS(ByteValue)                 Bfx_GetBit_u8u8_u8((ByteValue),5)
#define Com_GetValue_RXSIGGRP_FILTEREVALREQ(ByteValue)               Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_GetValue_GEN_TYPE(ByteValue)                             Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#define Com_GetValue_GEN_ENDIANESS(ByteValue)                        (Bfx_GetBit_u8u8_u8((ByteValue),5) ? COM_BIGENDIAN : COM_LITTLEENDIAN)
#define Com_GetValue_GEN_UPDBITCONF(ByteValue)                       Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_GetValue_TXGRPSIG_TYPE(ByteValue)                        Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#define Com_GetValue_TXGRPSIG_ENDIANESS(ByteValue)                   (Bfx_GetBit_u8u8_u8((ByteValue),5) ? COM_BIGENDIAN : COM_LITTLEENDIAN)
#define Com_GetValue_TXGRPSIG_TP(ByteValue)                          Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_GetValue_TXGRPSIG_INVACTION(ByteValue)                   Bfx_GetBit_u8u8_u8((ByteValue),7)
#define Com_GetValue_RXGRPSIG_TYPE(ByteValue)                        Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#define Com_GetValue_RXGRPSIG_ENDIANESS(ByteValue)                   (Bfx_GetBit_u8u8_u8((ByteValue),5) ? COM_BIGENDIAN : COM_LITTLEENDIAN)
#define Com_GetValue_RXGRPSIG_INVACTION(ByteValue)                   Bfx_GetBit_u8u8_u8((ByteValue),6)
#define Com_SetUpdateBitValue(PduPtr,UpdBitPos,ByteNo)               Com_Setbit((uint8 *)((PduPtr)->BuffPtr + (ByteNo)),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)));
#define Com_ClearUpdateBitValue(PduPtr,UpdBitPos,ByteNo)             Com_Clearbit((uint8 *)((PduPtr)->BuffPtr + (ByteNo)),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)));
#define Com_GetUpdateBitValue(dataPtr,UpdBitPos,ByteNo)              Com_Getbit(*((uint8 *)((dataPtr) + (ByteNo))),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)))
#define Com_Clearbit(ByteValue, Bitpos)                              Bfx_ClrBit_u8u8(ByteValue,Bitpos)
#define Com_Setbit(ByteValue, Bitpos)                                Bfx_SetBit_u8u8(ByteValue,Bitpos)
#define Com_Getbit(ByteValue, Bitpos)                                Bfx_GetBit_u8u8_u8(ByteValue,Bitpos)
#define Com_GetValue(ELEMENTTYPE,PROP,ByteValue)                     Com_GetValue_##ELEMENTTYPE##PROP(ByteValue)
#define Com_GetRamValue(ELEMENTTYPE,PROP,ByteValue)                  Com_GetRamValue_##ELEMENTTYPE##PROP(ByteValue)
#define Com_SetRamValue(ELEMENTTYPE,PROP,ByteValue,Value)            Com_SetRamValue_##ELEMENTTYPE##PROP(ByteValue,Value)
#define COM_CheckRxIPduDMStatus(IpduId)                              (Com_GetRamValue(RXIPDU,_DMSTATUS,COM_GET_RXPDURAM_S(IpduId).RxFlags) != COM_STOP)

FUNC(void, COM_CODE) Com_ByteCopy(
        P2VAR(uint8,  AUTOMATIC, COM_APPL_DATA) dest
   ,  P2CONST(uint8,  AUTOMATIC, COM_APPL_DATA) src
   ,      VAR(uint32, AUTOMATIC               ) Len
);

FUNC(void, COM_CODE) Com_ByteCopyInit(
      P2VAR(uint8,  AUTOMATIC, COM_APPL_DATA) dest
   ,    VAR(uint32, AUTOMATIC               ) Init_Val
   ,    VAR(uint32, AUTOMATIC               ) Len
);

FUNC(void, COM_CODE) Com_PackSignal( VAR(uint8, AUTOMATIC)                  Endianess
   ,     VAR(Com_BitpositionType, AUTOMATIC)    Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)        Bitsize
   ,     VAR(Com_SigMaxType, AUTOMATIC)         Src_Buf
   ,     P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf
);

FUNC(Com_SigMaxType, COM_CODE) Com_UnpackSignal( VAR(uint8, AUTOMATIC)                    Endianess
   ,     VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)          Bitsize
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf
   ,     VAR(boolean, AUTOMATIC)                  IsSigned
);


FUNC(uint32, COM_CODE) Com_UnpackOpaqueSignal( VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)          SignalLength
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf
);

FUNC(void, COM_CODE) Com_Lok_SendIpdu( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC) sendIpduFlag_u16
);

FUNC(void,COM_CODE) Com_TxChangeMode(VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) TxIpduId);

FUNC(void, COM_CODE) Com_Lok_ProcessSignal(
                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)                       RxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
);

FUNC(void, COM_CODE) Com_TxIPduStop(VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId);
FUNC (void,COM_CODE) Com_Lok_ClearUpdateBits( Com_TxIpduConstPtrType TxIPduConstPtr);
FUNC(Std_ReturnType, COM_CODE) Com_WriteSigGwReceiveQueue(Type_SwcServiceCom_tIdPdu ComRxPduId);
FUNC(void, COM_CODE) Com_Lok_PackRxSignalGwBufferData(Com_RxSigConstPtrType RxSigConstPtr,Com_SignalIdType l_TxGwDestId);
FUNC(void, COM_CODE) Com_InternalProcessTxConfirmation(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId);

extern FUNC(uint8, COM_CODE)    Com_InternalSendSignal( VAR(Com_SignalIdType, AUTOMATIC)        SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);

extern FUNC(uint8, COM_CODE) Com_InternalSendSignalGroup        (VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
extern FUNC(void,  COM_CODE) Com_InternalInvalidateShadowSignal (VAR(Com_SignalIdType,      AUTOMATIC) SignalId);
extern FUNC(void,  COM_CODE) Com_InternalMainFunctionRx         (VAR(Com_MainFuncType,      AUTOMATIC) RxMainFuncId);
extern FUNC(void,  COM_CODE) Com_InternalMainFunctionTx         (VAR(Com_MainFuncType,      AUTOMATIC) TxMainFuncId);

extern     VAR(Com_StatusType,                        COM_VAR                  ) Com_Uninit_Flag;
extern     VAR(Com_RxIpduRamData,                     COM_VAR                  ) Com_RxIpduRam_s[];
extern     VAR(Com_TxIpduRamData,                     COM_VAR                  ) Com_TxIpduRam_s[];
extern     VAR(Com_TxSignalFlagType,                  COM_VAR                  ) Com_TxSignalFlag[];
extern     VAR(Com_RxSignalFlagType,                  COM_VAR                  ) Com_RxSignalFlag[];
extern     VAR(uint8,                                 COM_VAR                  ) Com_IpduCounter_s[];
extern     VAR(uint8,                                 COM_VAR                  ) Com_IpduCounter_DM[];
extern     VAR(Com_IpduGroupVector,                   COM_VAR                  ) Com_IpduGrpVector;
extern     VAR(Com_IpduGroupVector,                   COM_VAR                  ) Com_IpduGrpVector_DM;
extern     VAR(uint16,                                COM_VAR                  ) Com_ReducedPeriod_u16;
extern     VAR(Type_SwcServiceCom_tIdPdu,             COM_VAR                  ) Com_RxGwQueue_aux[];
extern     VAR(Com_RxGwQueueRAMType,                  COM_VAR                  ) Com_RxGwQueue_S;
extern P2CONST(Com_ConfigData_tst,                    AUTOMATIC, COM_APPL_CONST) Com_Lok_Config_pcst;
extern   CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST                ) Com_NONE_TransModeInfo;
extern   CONST(Type_CfgSwcServiceCom_stInfoSignalTx,  COM_CONST                ) CfgSwcServiceCom_castListInfoSignalTx[];
extern   CONST(Type_CfgSwcServiceCom_stInfoSignalRx,  COM_CONST                ) CfgSwcServiceCom_castListInfoSignalRx[];
extern   CONST(Type_CfgSwcServiceCom_stInfoIpduTx,    COM_CONST                ) CfgSwcServiceCom_castListInfoIpduTx[];
extern   CONST(Type_CfgSwcServiceCom_stInfoIpduRx,    COM_CONST                ) CfgSwcServiceCom_castListInfoIpduRx[];
extern   CONST(Type_CfgSwcServiceCom_stInfoIpduGrp,   COM_CONST                ) CfgSwcServiceCom_castListInfoIpduGrp[];
extern   CONST(Com_ConfigData_tst,                    COM_APPL_CONST           ) Com_Lok_Config_cst;
extern   CONST(Type_CfgSwcServiceCom_tIdIPdu,         COM_CONST                ) CfgSwcServiceCom_catListIdIPdu[];
extern   CONST(Type_CfgSwcServiceCom_stMainFunction,  COM_CONST                ) Com_MainFunctionCfg[];
extern   CONST(Type_CfgSwcServiceCom_stBufferRamRx,   COM_CONST                ) Com_Lok_xRxRamBuf_acst[];

#define COM_GET_TX_IPDU_CONSTDATA(COMPDUID)                          (&CfgSwcServiceCom_castListInfoIpduTx[COMPDUID])
#define COM_GET_RX_IPDU_CONSTDATA(COMPDUID)                          (&CfgSwcServiceCom_castListInfoIpduRx[COMPDUID])
#define COM_GET_IPDUGRP_CONSTDATA(COMPDUID)                          (&CfgSwcServiceCom_castListInfoIpduGrp[COMPDUID])
#define COM_GET_IPDUGRP_ID(COMPDUID)                                 (COMPDUID)
#define COM_GET_IPDUGRP_IPDUREF_CONSTDATA(COMPDUID)                  (&CfgSwcServiceCom_catListIdIPdu[COMPDUID])
#define COM_GET_RXSIG_CONSTDATA(COMSIGID)                            (&CfgSwcServiceCom_castListInfoSignalRx[COMSIGID])
#define COM_GET_RXSIGNAL_ID(COMSIGID)                                (COMSIGID)
#define COM_GET_TXSIG_CONSTDATA(COMSIGID)                            (&CfgSwcServiceCom_castListInfoSignalTx[COMSIGID])
#define COM_GET_TXSIGNAL_ID(COMSIGID)                                (COMSIGID)
#define COM_GET_TXSIGGRP_CONSTDATA(COMSIGGRPID)                      (&Com_Lok_xTxSigGrpCfg_acst[COMSIGGRPID])
#define COM_GET_TXSIGNALGRP_ID(COMSIGGRPID)                          (COMSIGGRPID)
#define COM_GET_RXSIGGRP_CONSTDATA(COMSIGGRPID)                      (&Com_Lok_xRxSigGrpCfg_acst[COMSIGGRPID])
#define COM_GET_RXSIGNALGRP_ID(COMSIGID)                             (COMSIGID)
#define COM_GET_TXGRPSIG_CONSTDATA(COMGRPSIGID)                      (&Com_Lok_xTxGrpSigCfg_acst[COMGRPSIGID])
#define COM_GET_TXGRPSIGNAL_ID(COMGRPSIGID)                          (COMGRPSIGID)
#define COM_GET_RXGRPSIG_CONSTDATA(COMGRPSIGID)                      (&Com_Lok_xRxGrpSigCfg_acst[COMGRPSIGID])
#define COM_GET_RXGRPSIGNAL_ID(COMGRPSIGID)                          (COMGRPSIGID)
#define COM_GET_GWSIG_CONSTDATA(COMGWID)                             (&Com_Lok_xGwMapSigCfg_acst[COMGWID])
#define COM_GET_GWSIGIDMAP_CONSTDATA(COMGWID)                        (&Com_Lok_xGwMapSigIdCfg_acst[COMGWID])
#define COM_GET_GWGRPSIG_CONSTDATA(COMGWGRPSIGID)                    (&Com_Lok_xGwMapGrpSigCfg_acst[COMGWGRPSIGID])
#define COM_GET_GWGRPSIGIDMAP_CONSTDATA(COMGWGRPSIGID)               (&Com_Lok_xGwMapGrpSigIdCfg_acst[COMGWGRPSIGID])
#define COM_GET_NUM_TOTAL_IPDU_GRP                                   COM_NUM_TOTAL_IPDU_GRP
#define COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP                            COM_NUM_IPDUS_IN_LAST_IPDUGRP
#define COM_GET_SIGTYPEUINT8_BUFF(MF_ID,SIGNAL_INDEX)                (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu8[SIGNAL_INDEX])
#define COM_GET_SIGTYPEUINT16_BUFF(MF_ID,SIGNAL_INDEX)               (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu16[SIGNAL_INDEX])
#define COM_GET_SIGTYPEUINT32_BUFF(MF_ID,SIGNAL_INDEX)               (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu32[SIGNAL_INDEX])
#define COM_GET_TXPDURAM_S(COMTXIPDUID)                              (Com_TxIpduRam_s[COMTXIPDUID])
#define COM_GET_RXPDURAM_S(COMRXIPDUID)                              (Com_RxIpduRam_s[COMRXIPDUID])
#define COM_GET_TXSIGNALFLAG(COMTXSIGID)                             (Com_TxSignalFlag[COMTXSIGID])
#define COM_GET_RXSIGNALFLAG(COMRXSIGID)                             (Com_RxSignalFlag[COMRXSIGID])
#define COM_GET_IPDUCOUNTER_S(COMPDUID)                              (Com_IpduCounter_s[COMPDUID])
#define COM_GET_IPDUCOUNTER_DM(COMPDUID)                             (Com_IpduCounter_DM[COMPDUID])
#define COM_GET_NUM_RX_SIGNALS                                       (CfgSwcServiceCom_dNumSignalsRx)
#define COM_GET_NUM_TX_SIGNALS                                       (CfgSwcServiceCom_dNumSignalsTx)
#define COM_GET_NUM_TX_SIGNALGRP                                     (COM_NUM_TX_SIGNALGRP)
#define COM_GET_NUM_RX_SIGNALGRP                                     (COM_NUM_RX_SIGNALGRP)
#define COM_GET_NUM_TX_GRPSIGNALS                                    (COM_NUM_TX_GRPSIGNALS)
#define COM_GET_NUM_RX_GRPSIGNALS                                    (COM_NUM_RX_GRPSIGNALS)
#define COM_GET_NUM_GWSRC_SIGNALS                                    (COM_NUM_GWSRC_SIGNALS)
#define COM_GET_NUM_GWSRC_GRPSIGNALS                                 (COM_NUM_GWSRC_GRPSIGNALS)
#define COM_GET_NUM_GWSRC_IPDUS                                      (COM_NUM_GWSRC_IPDUS)
#define COM_GET_NUM_GRPSIG_NOGW                                      (COM_NUM_GRPSIG_NOGW)
#define COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, CurrentTxModePtr)      (CurrentTxModePtr->TimeOffsetFact)
#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)      ((CurrentTxModePtr)->TimePeriodFact)
#define COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, CurrentTxModePtr) (CurrentTxModePtr->NumOfRepetitions)

#endif
