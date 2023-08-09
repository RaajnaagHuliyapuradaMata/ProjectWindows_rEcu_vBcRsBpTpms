

#ifndef COM_PRV_H
#define COM_PRV_H

#include "Com.h"
#include "Com_Cfg_Internal.h"
#include "Com_Cfg_SchM.h"
#include "Com_Lok_Types.h"
#include "rba_BswSrv.h"

#if (COM_CONFIGURATION_VARIANT == COM_VARIANT_PRE_COMPILE)
#include "Com_PBcfg.h"
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)
#include "Det.h"

#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#ifdef COM_ARSRVLIB_SUPPORT
#include "Bfx.h"

#if (!defined(BFX_AR_RELEASE_MAJOR_VERSION) || (BFX_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BFX_AR_RELEASE_MINOR_VERSION) || (BFX_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#ifdef COM_ENABLE_READRXIPDULENGTH

#define COMServiceId_ReadRxIPduLength                                   (0x95)
#endif

#define COM_BOOL_TO_UNSIGNED(BoolValue) ((BoolValue) ? (COM_SET) : (COM_RESET))

#define COM_LITTLEENDIAN    0u

#define COM_BIGENDIAN       1u

#define COM_OPAQUE          COM_LITTLEENDIAN

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#define COM_CPU_ENDIANNESS COM_LITTLEENDIAN
#else
#define COM_CPU_ENDIANNESS COM_BIGENDIAN
#endif

#define COM_IMMEDIATE   FALSE

#define COM_DEFERRED    TRUE

#define COM_TRIGGERED_ON_CHANGE                     0u

#define COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION  1u

#define COM_PENDING                                 2u

#define COM_TRIGGERED_WITHOUT_REPETITION            3u

#define COM_TRIGGERED                               4u

#define COM_SIG_TP_IS_TRIGGERED(TransProp)             (TransProp > COM_PENDING)

#define COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TransProp)   (TransProp < COM_PENDING)

#define COM_SIG_TP_IS_WITHOUT_REPETITION(TransProp)    ((TransProp & 0x1u) != 0u)

#define COM_RESET       0u

#define COM_SET         1u

#define COM_REPLACE_TO_INIT  2u

#define COM_STOP        FALSE

#define COM_START       TRUE

#define COM_TXMODE_DIRECT      0x00u

#define COM_TXMODE_MIXED       0x01u

#define COM_TXMODE_NONE        0x02u

#define COM_TXMODE_PERIODIC    0x03u

#define     COM_CLRUPDATEBIT_TRANSMIT           1u

#define     COM_CLRUPDATEBIT_TRIGGERTRANSMIT    2u

#define     COM_CLRUPDATEBIT_CONFIRMATION       3u

#define     COM_CLRUPDATEBIT_NONE               0u

#define COM_TRUE        TRUE

#define COM_FALSE       FALSE

#define COM_NONE        0u

#define COM_REPLACE     1u

#define COM_NOTIFY      2u

#define COM_NOT_USED    0u

#define COM_MAXIMUM_GWSYNC_REPITIONS 2

#define COM_ZERO       0u

#define COM_ONE        1u

#define COM_TWO        2u

#define COM_UINT8                           0x00u

#define COM_SINT8                           0x01u

#define COM_UINT16                          0x02u

#define COM_SINT16                          0x03u

#define COM_UINT32                          0x04u

#define COM_SINT32                          0x05u

#define COM_UINT64                          0x10u

#define COM_SINT64                          0x11u

#define COM_BOOLEAN                         0x06u

#define COM_UNDEFTYPE                       0x07

#define COM_UINT8_N                         0x08u

#define COM_UINT8_DYN                       0x0Au

#define COM_FLOAT32                         0x0Cu

#define COM_FLOAT64                         0x0Eu

#define COM_ALWAYS                          0u

#define COM_NEVER                           1u

#define COM_MASKED_NEW_EQUALS_X             2u

#define COM_MASKED_NEW_DIFFERS_X            3u

#define COM_MASKED_NEW_DIFFERS_MASKED_OLD   4u

#define COM_NEW_IS_WITHIN_POS               5u

#define COM_NEW_IS_WITHIN_NEG               6u

#define COM_NEW_IS_OUTSIDE_POS              7u

#define COM_NEW_IS_OUTSIDE_NEG              8u

#define COM_ONE_EVERY_N                     9u

#define COM_NOTCONFIGURED                   10u

#define COM_MODE_VALID                      0u

#define COM_TRUEMODE_VALID                  1u

#define COM_FALSEMODE_VALID                 2u

#define COM_CLEAR_SENDIPDU_FLAGS            {0,0,0,0,0,0,0}

#define UPDATEBIT_NOT_APPLICABLE    0x00u

#define UPDATEBIT_APPLICABLE        0x01u
#define UPDATEBIT_SET               0x02u

#if(COM_CONFIGURATION_USE_DET == STD_ON)

#define COM_DET_NO_ERROR  0xFFu

#define COM_REPORT_ERROR_CHECK(API, ERROR)   (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, (API), (ERROR))
#endif

#define Com_PerformSignExtension(Value,Size)    (Value) | (COM_SIGN_EXT_MASK << ((Size) - 1))

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_PDUSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFE)) | (uint16)(BitVal))

#else

#define Com_SetRamValue_TXIPDU_PDUSTATUS(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_PDUSTATUS(ByteValue)         ((uint16)(ByteValue) & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_PDUSTATUS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_CONFIR(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFD)) | (uint16)((BitVal)<<1))
#else

#define Com_SetRamValue_TXIPDU_CONFIR(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),1,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_CONFIR(ByteValue)         ((uint16)((ByteValue)>>1) & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_CONFIR(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),1)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_TICKTXTO(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFB)) | (uint16)((BitVal)<<2))
#else

#define Com_SetRamValue_TXIPDU_TICKTXTO(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),2,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_TICKTXTO(ByteValue)         ((uint16)((ByteValue) >> 2) & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_TICKTXTO(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_MDT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFF7)) | (uint16)((BitVal)<<3))
#else

#define Com_SetRamValue_TXIPDU_MDT(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),3,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_MDT(ByteValue)         ((uint16)((ByteValue) >> 3)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_MDT(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_EVENTTRIG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFEF)) | (uint16)((BitVal)<<4))
#else

#define Com_SetRamValue_TXIPDU_EVENTTRIG(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),4,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_EVENTTRIG(ByteValue)         ((uint16)((ByteValue) >> 4)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_EVENTTRIG(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),4)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFDF)) | (uint16)((BitVal)<<5))
#else

#define Com_SetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),5,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue)         ((uint16)((ByteValue) >> 5)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),5)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_ISTOENABLED(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFBF)) | (uint16)((BitVal)<<6))
#else

#define Com_SetRamValue_TXIPDU_ISTOENABLED(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),6,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_ISTOENABLED(ByteValue)         ((uint16)((ByteValue) >> 6)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_ISTOENABLED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFF7F)) | (uint16)((BitVal) << 7))
#else

#define Com_SetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),7,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue)        ((uint16)((ByteValue) >> 7)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),7)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue,BitVal)  (ByteValue) = (((ByteValue) & ((uint16)0xFEFF)) | \
                                                                                               (uint16)((BitVal) << 8))
#else

#define Com_SetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue,BitVal)  Bfx_PutBit_u16u8u8(&(ByteValue),8,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue)         ((uint16)((ByteValue) >> 8)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue,BitVal)  (ByteValue) = (((ByteValue) & ((uint16)0xFDFF)) | \
                                                                                              (uint16)((BitVal) << 9))
#else

#define Com_SetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue,BitVal)  Bfx_PutBit_u16u8u8(&(ByteValue),9,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue)         ((uint16)((ByteValue) >> 9)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),9)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_PDUSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXIPDU_PDUSTATUS(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_PDUSTATUS(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXIPDU_PDUSTATUS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_DMSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFD)) | (uint8)((BitVal)<<1))
#else

#define Com_SetRamValue_RXIPDU_DMSTATUS(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_DMSTATUS(ByteValue)         ((uint8)((ByteValue) >>1) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXIPDU_DMSTATUS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),1)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_INDICATION(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFB)) | (uint8)((BitVal)<<2))
#else

#define Com_SetRamValue_RXIPDU_INDICATION(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_INDICATION(ByteValue)         ((uint8)((ByteValue) >>2)  & (uint8)(0x01))
#else

#define Com_GetRamValue_RXIPDU_INDICATION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xF7)) | (uint8)((BitVal)<<3))
#else

#define Com_SetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),3,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue)         ((uint8)((ByteValue) >>3)  & (uint8)(0x01))
#else

#define Com_GetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue,BitVal)        (ByteValue) = (((ByteValue) & ((uint8)0xEF)) | (uint8)((BitVal)<<4))
#else

#define Com_SetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue,BitVal)        Bfx_PutBit_u8u8u8(&(ByteValue),4,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue)       ((uint8)((ByteValue) >>4)  & (uint8)(0x01))
#else

#define Com_GetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),4)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_LATESTMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFC)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXIPDU_LATESTMODE(ByteValue,BitVal)         Bfx_PutBits_u8u8u8u8(&(ByteValue),0,2,(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_LATESTMODE(ByteValue)         ((uint8)((ByteValue)) & (uint8)(0x03))
#else

#define Com_GetRamValue_TXIPDU_LATESTMODE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_TXMODESTATE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFB)) | (uint8)((BitVal) << 2))
#else

#define Com_SetRamValue_TXIPDU_TXMODESTATE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2,(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_TXMODESTATE(ByteValue)         ((uint8)((ByteValue) >> 2) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXIPDU_TXMODESTATE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xF7)) | (uint8)((BitVal)<<3))
#else

#define Com_SetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),3,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue)         ((uint8)((ByteValue) >> 3) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue,BitVal)       (ByteValue) = (((ByteValue) & ((uint8)0xFD)) | (uint8)((BitVal)<<1))
#else

#define Com_SetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue,BitVal)       Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue)      ((uint8)((ByteValue) >> 1) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue)      Bfx_GetBit_u8u8_u8((ByteValue),1)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_SIGNOTIF(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXSIGGRP_SIGNOTIF(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_SIGNOTIF(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIGGRP_SIGNOTIF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFD)) | (uint8)(BitVal<<1))
#else

#define Com_SetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue)        ((uint8)((ByteValue)>>1) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue)        Bfx_GetBit_u8u8_u8((ByteValue),1)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_DMFILTERING(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFB)) | (uint8)(BitVal<<2))
#else

#define Com_SetRamValue_RXSIGGRP_DMFILTERING(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_DMFILTERING(ByteValue)         ((uint8)((ByteValue)>>2) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIGGRP_DMFILTERING(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIG_SIGCHNGMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXSIG_SIGCHNGMODE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIG_SIGCHNGMODE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_TXSIG_SIGCHNGMODE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_SIGNOTIF(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFE)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXSIG_SIGNOTIF(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_SIGNOTIF(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIG_SIGNOTIF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_SIGNALFILLBIT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFD)) | (uint8)(BitVal<<1))
#else

#define Com_SetRamValue_RXSIG_SIGNALFILLBIT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_SIGNALFILLBIT(ByteValue)         ((uint8)((ByteValue)>>1) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIG_SIGNALFILLBIT(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),1)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_DMFILTERING(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFB)) | (uint8)(BitVal<<2))
#else

#define Com_SetRamValue_RXSIG_DMFILTERING(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_DMFILTERING(ByteValue)         ((uint8)((ByteValue)>>2) & (uint8)(0x01))
#else

#define Com_GetRamValue_RXSIG_DMFILTERING(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_SIGPROC(ByteValue)         ((uint16)(ByteValue) & ((uint16)0x01))
#else

#define Com_GetValue_TXIPDU_SIGPROC(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_TMS(ByteValue)         ((uint16)((ByteValue) >>1) & ((uint16)0x03))
#else

#define Com_GetValue_TXIPDU_TMS(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),1,2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_NONETOSTATUS(ByteValue)         ((uint16)((ByteValue) >>3) & ((uint16)0x01))
#else

#define Com_GetValue_TXIPDU_NONETOSTATUS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_CLRUPDBIT(ByteValue)         ((uint16)((ByteValue) >>4) & ((uint16)0x03))
#else

#define Com_GetValue_TXIPDU_CLRUPDBIT(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),4,2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_FILTEREVALREQ(ByteValue)         ((uint16)((ByteValue) >>6) & ((uint16)0x01))
#else

#define Com_GetValue_TXIPDU_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_ISDYNIPDU(ByteValue)         ((uint16)((ByteValue) >>7)  & (uint16)(0x01))
#else

#define Com_GetRamValue_TXIPDU_ISDYNIPDU(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),7)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISGWPDU(ByteValue)         ((uint16)((ByteValue) >>8)  & (uint16)(0x01))
#else

#define Com_GetValue_TXIPDU_ISGWPDU(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISCALLOUTFRMTRIGTRANS(ByteValue)         ((uint16)((ByteValue) >>9)  & (uint16)(0x01))
#else

#define Com_GetValue_TXIPDU_ISCALLOUTFRMTRIGTRANS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),9)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISLARGEDATAPDU(ByteValue)        ((uint16)((ByteValue) >>10)  & (uint16)(0x01))
#else

#define Com_GetValue_TXIPDU_ISLARGEDATAPDU(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),10)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISCANCELTRANSMITSUPPORTED(ByteValue)        ((uint16)((ByteValue) >>11)  & (uint16)(0x01))
#else

#define Com_GetValue_TXIPDU_ISCANCELTRANSMITSUPPORTED(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),11)
#endif

#ifdef COM_METADATA_SUPPORT

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_TXIPDU_ISMETADATASUPPORTED(ByteValue)  ( ( uint16 )( ( ByteValue ) >> 12 ) & ( ( uint16 )0x01 ) )
# else

#  define Com_GetValue_TXIPDU_ISMETADATASUPPORTED(ByteValue)  Bfx_GetBit_u16u8_u8( ( ByteValue ), 12 )
# endif
#endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_TXIPDU_DEFAULTTMSSTATUS(ByteValue)  ( ( uint16 )( ( ByteValue ) >> 13 ) & ( ( uint16 )0x01 ) )
# else

#  define Com_GetValue_TXIPDU_DEFAULTTMSSTATUS(ByteValue)  Bfx_GetBit_u16u8_u8( ( ByteValue ), 13 )
# endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_TXIPDU_PDUWITHPDUGRP(ByteValue)  ( ( uint16 )( ( ByteValue ) >> 14 ) & ( ( uint16 )0x01 ) )
# else

#  define Com_GetValue_TXIPDU_PDUWITHPDUGRP(ByteValue)  Bfx_GetBit_u16u8_u8( ( ByteValue ), 14 )
# endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXIPDU_SIGPROC(ByteValue)         ((uint8)(ByteValue) & ((uint8)0x01))
#else

#define Com_GetValue_RXIPDU_SIGPROC(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXIPDU_NOTIFCBK(ByteValue)         ((uint8)((ByteValue) >> 1) & ((uint8)0x01))
#else

#define Com_GetValue_RXIPDU_NOTIFCBK(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),1)
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXIPDU_ISGWPDU(ByteValue)        ((uint8)((ByteValue) >> 2)  & (uint8)(0x01))
#else

#  define Com_GetValue_RXIPDU_ISGWPDU(ByteValue)        Bfx_GetBit_u8u8_u8((ByteValue),2)
# endif
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_INVACTION(ByteValue)         (((uint8)(ByteValue)) & ((uint8)0x03))
#else

#define Com_GetValue_RXSIG_INVACTION(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_FILTRALG(ByteValue)         ((uint8)((ByteValue) >> 2) & (uint8)(0x0F))
#else

#define Com_GetValue_RXSIG_FILTRALG(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),2,4)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_TOACTION(ByteValue)         (((uint8)((ByteValue) >> 6)) & ((uint8)0x01))
#else

#define Com_GetValue_RXSIG_TOACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_ISGWSIG(ByteValue)         (((uint8)((ByteValue) >> 7)) & ((uint8)0x01))
#else

#define Com_GetValue_RXSIG_ISGWSIG(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),7)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_TP(ByteValue)         ((uint16)(ByteValue) & (uint16)(0x07))
#else

#define Com_GetValue_TXSIG_TP(ByteValue)          Bfx_GetBits_u16u8u8_u16((ByteValue),0,3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_FILTRALG(ByteValue)         ((uint16)((ByteValue) >> 3) & (uint16)(0x0F))
#else

#define Com_GetValue_TXSIG_FILTRALG(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),3,4)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_INVACTION(ByteValue)         ((uint16)((ByteValue) >> 7) & ((uint16)0x01))
#else

#define Com_GetValue_TXSIG_INVACTION(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),7)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_TOENABLED(ByteValue)         (((uint16)((ByteValue) >> 8)) & ((uint16)0x01))
#else

#define Com_GetValue_TXSIG_TOENABLED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_TP(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x07))
#else

#define Com_GetValue_TXSIGGRP_TP(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_TOENABLED(ByteValue)         (((uint8)((ByteValue) >> 3)) & ((uint8)0x01))
#else

#define Com_GetValue_TXSIGGRP_TOENABLED(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_FILTEREVALREQ(ByteValue)         (((uint8)((ByteValue) >> 4)) & ((uint8)0x01))
#else

#define Com_GetValue_TXSIGGRP_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),4)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_UPDBITCONF(ByteValue)         (((uint8)((ByteValue) >> 5)) & ((uint8)0x01))
#else

#define Com_GetValue_TXSIGGRP_UPDBITCONF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),5)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_ARRAYACCESS(ByteValue)         (((uint8)((ByteValue) >> 6)) & ((uint8)0x01))
#else

#define Com_GetValue_TXSIGGRP_ARRAYACCESS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_INVACTION(ByteValue)         (((uint8)(ByteValue)) & ((uint8)0x03))
#else

#define Com_GetValue_RXSIGGRP_INVACTION(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_TOACTION(ByteValue)         (((uint8)((ByteValue) >> 2)) & ((uint8)0x01))
#else

#define Com_GetValue_RXSIGGRP_TOACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_ISGWSIGGRP(ByteValue)       (((uint8)((ByteValue) >> 3)) & ((uint8)0x01))
#else

#define Com_GetValue_RXSIGGRP_ISGWSIGGRP(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),3)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_UPDBITCONF(ByteValue)       (((uint8)((ByteValue) >> 4)) & ((uint8)0x01))
#else

#define Com_GetValue_RXSIGGRP_UPDBITCONF(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),4)
#endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXSIGGRP_ARRAYACCESS(ByteValue)       (((uint8)((ByteValue) >> 5)) & ((uint8)0x01))
# else

#  define Com_GetValue_RXSIGGRP_ARRAYACCESS(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),5)
# endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXSIGGRP_FILTEREVALREQ(ByteValue)         (((uint8)((ByteValue) >> 6)) & ((uint8)0x01))
# else

#  define Com_GetValue_RXSIGGRP_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
# endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1F))
#else

#define Com_GetValue_GEN_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5) & (uint8)(0x01))
#else

#define Com_GetValue_GEN_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5) ? \
                                                       COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_UPDBITCONF(ByteValue)         ((uint8)((ByteValue) >> 6) & (uint8)(0x01))
#else

#define Com_GetValue_GEN_UPDBITCONF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1F))
#else

#define Com_GetValue_TXGRPSIG_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5) & (uint8)(0x01))
#else

#define Com_GetValue_TXGRPSIG_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5) ? \
                                                            COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_TP(ByteValue)         ((uint8)((ByteValue) >> 6) & (uint8)(0x01))
#else

#define Com_GetValue_TXGRPSIG_TP(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_INVACTION(ByteValue)         ((uint8)((ByteValue) >> 7) & ((uint8)0x01))
#else

#define Com_GetValue_TXGRPSIG_INVACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),7)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1F))
#else

#define Com_GetValue_RXGRPSIG_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0,5)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5) & (uint8)(0x01))
#else

#define Com_GetValue_RXGRPSIG_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5) ? \
                                                            COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_INVACTION(ByteValue)         ((uint8)((ByteValue) >> 6) & ((uint8)0x01))
#else

#define Com_GetValue_RXGRPSIG_INVACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6)
#endif

#define Com_SetUpdateBitValue(PduPtr,UpdBitPos,ByteNo)                                                          \
                                                                                                           \
        Com_Setbit((uint8 *)((PduPtr)->BuffPtr + (ByteNo)),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)));

#define Com_ClearUpdateBitValue(PduPtr,UpdBitPos,ByteNo)                                                        \
                                                                                                           \
        Com_Clearbit((uint8 *)((PduPtr)->BuffPtr + (ByteNo)),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)));

#define Com_GetUpdateBitValue(dataPtr,UpdBitPos,ByteNo)                                                         \
                                                                                                       \
        Com_Getbit(*((uint8 *)((dataPtr) + (ByteNo))),(uint8)((UpdBitPos) - (Com_BitpositionType)((ByteNo) * 8u)))

#ifdef COM_ARSRVLIB_SUPPORT
#define Com_Clearbit(ByteValue, Bitpos) Bfx_ClrBit_u8u8(ByteValue,Bitpos)
#else
#define Com_Clearbit(ByteValue, Bitpos) (*ByteValue) = ((uint8)(*ByteValue) & (~((uint8)(1u<<(Bitpos)))))
#endif

#ifdef COM_ARSRVLIB_SUPPORT
#define Com_Setbit(ByteValue, Bitpos) Bfx_SetBit_u8u8(ByteValue,Bitpos)
#else
#define Com_Setbit(ByteValue, Bitpos) (*ByteValue) = ((uint8)(*ByteValue) | ((uint8)(1u<<(Bitpos))))
#endif

#ifdef COM_ARSRVLIB_SUPPORT
#define Com_Getbit(ByteValue, Bitpos) Bfx_GetBit_u8u8_u8(ByteValue,Bitpos)
#else
#define Com_Getbit(ByteValue, Bitpos) (((ByteValue) & ((uint8)(1u << (Bitpos)))) != 0)
#endif

#define     Com_GetValue(ELEMENTTYPE,PROP,ByteValue)            Com_GetValue_##ELEMENTTYPE##PROP(ByteValue)

#define     Com_GetRamValue(ELEMENTTYPE,PROP,ByteValue)         Com_GetRamValue_##ELEMENTTYPE##PROP(ByteValue)

#define     Com_SetRamValue(ELEMENTTYPE,PROP,ByteValue,Value)   Com_SetRamValue_##ELEMENTTYPE##PROP(ByteValue,Value)

#define COM_CheckRxIPduDMStatus(IpduId) \
                         (Com_GetRamValue(RXIPDU,_DMSTATUS,COM_GET_RXPDURAM_S(IpduId).RxFlags) != COM_STOP)

#ifdef COM_RX_IPDUCONTROL_VIA_CALIBRATION

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
 FUNC(boolean, COM_CODE) COM_CheckRxIPduCalibrationVarStatus(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_TX_IPDUCONTROL_VIA_CALIBRATION

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
 FUNC(boolean, COM_CODE) COM_CheckTxIPduCalibrationVarStatus(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint16, COM_CODE)  COM_getTxIPduCyclePeriod(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint16, COM_CODE)  Com_GetRxIPduTimeoutCalibration(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TXPDU_TIMEOFFSET_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint16, COM_CODE)  Com_GetTxIPduTimeOffsetCalibration(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TXPDU_NUMOFREPETITION_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE)  Com_GetTxIPduNumberOfRepetitionCalibration(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
 FUNC(boolean, COM_CODE)  Com_CheckTxIPduControlViaRbaNdsEcuVariant(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
 FUNC(boolean, COM_CODE)  Com_CheckRxIPduControlViaRbaNdsEcuVariant(VAR(PduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ByteCopy( P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)   dest,
                                   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) src,
                                   VAR(uint32, AUTOMATIC)                   Len );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ByteCopyInit( P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)   dest,
                                       VAR(uint32, AUTOMATIC)                   Init_Val,
                                       VAR(uint32, AUTOMATIC)                   Len );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_PackSignal( VAR(uint8, AUTOMATIC)                  Endianess,
                                     VAR(Com_BitpositionType, AUTOMATIC)    Bit_Pos,
                                     VAR(Com_BitsizeType, AUTOMATIC)        Bitsize,
                                     VAR(Com_SigMaxType, AUTOMATIC)         Src_Buf,
                                     P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if (defined(COM_TXSIG_FLOAT64SUPP) || defined(COM_TXGRPSIG_FLOAT64SUPP) ||\
    (defined(COM_RX_SIGNALGROUP_ARRAY) && defined(COM_RXGRPSIG_FLOAT64SUPP)))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_PackFloatSignal( VAR(uint8, AUTOMATIC)                  Endianess,
                                          VAR(Com_BitpositionType, AUTOMATIC)    Bit_Pos,
                                          VAR(float64,AUTOMATIC)                 Src,
                                          P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Com_SigMaxType, COM_CODE) Com_UnpackSignal( VAR(uint8, AUTOMATIC)                    Endianess,
                                                 VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos,
                                                 VAR(Com_BitsizeType, AUTOMATIC)          Bitsize,
                                                 P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf,
                                                 VAR(boolean, AUTOMATIC)                  IsSigned );

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined (COM_RXSIG_FLOAT64SUPP ) || defined(COM_RXGRPSIG_FLOAT64SUPP)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(float64, COM_CODE) Com_UnPackFloatSignal( VAR(uint8, AUTOMATIC)                    Endianess,
                                               VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos,
                                               P2CONST(uint8,AUTOMATIC,COM_APPL_DATA)   Src_Buf);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint32, COM_CODE) Com_UnpackOpaqueSignal( VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos,
                                               VAR(Com_BitsizeType, AUTOMATIC)          SignalLength,
                                               P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Lok_SendIpdu( VAR(PduIdType, AUTOMATIC) ComTxPduId,
                                       VAR(Com_SendIpduInfo, AUTOMATIC) sendIpduFlag_u16 );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_TxChangeMode(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxFilters

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_Lok_SigTxChangeMode(VAR(Com_SignalIdType, AUTOMATIC) SignalId,
                                                                VAR(uint32, AUTOMATIC) TxNewVal);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_Lok_SigGrpTxChangeMode(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Lok_ProcessSignal(
                                VAR(PduIdType, AUTOMATIC)                       RxPduId,
                                P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
                                          );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Lok_ProcessSignalGroup(
                                VAR(PduIdType, AUTOMATIC)                       RxPduId,
                                P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
                                               );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_TxIPduStop(VAR(Com_IpduIdType, AUTOMATIC) IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
    FUNC(void, COM_CODE) Com_ShadowBuffToIpduBuff(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGrpId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#if (defined(COM_TxFilters) || defined(COM_RxFilters))

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean, COM_CODE) Com_Filter( VAR(uint32, AUTOMATIC) NewVal, VAR(uint8, AUTOMATIC) Algorithm,
                                    VAR(Com_FilterType, AUTOMATIC) FilterIndex, VAR(boolean,AUTOMATIC) CallContext_b);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ProcessRxIPdu(
                                VAR(PduIdType, AUTOMATIC)                       RxPduId,
                                P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
                                      );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC (void,COM_CODE) Com_Lok_ClearUpdateBits( Com_TxIpduConstPtrType TxIPduConstPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_WriteSigGwReceiveQueue(PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Lok_PackRxSignalGwBufferData(Com_RxSigConstPtrType RxSigConstPtr,Com_SignalIdType l_TxGwDestId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Lok_PackRxGrpSigGwBufferData(Com_RxGrpSigConstPtrType RxGrpSigConstPtr,Com_TxIntGrpSignalIdType l_TxGwDestId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_InternalProcessTxConfirmation(VAR(PduIdType, AUTOMATIC) TxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

extern FUNC(void, COM_CODE)     ComAppl_IncompatibleGenerator(void);
extern FUNC(uint8, COM_CODE)    Com_InternalSendSignal( VAR(Com_SignalIdType, AUTOMATIC)        SignalId,
                                                        P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr );
extern FUNC(uint8, COM_CODE)    Com_InternalSendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
extern FUNC(void, COM_CODE)     Com_InternalInvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId);
extern FUNC(void, COM_CODE)     Com_InternalMainFunctionRx( VAR(Com_MainFuncType,AUTOMATIC) RxMainFuncId );
extern FUNC(void, COM_CODE)     Com_InternalMainFunctionTx( VAR(Com_MainFuncType,AUTOMATIC) TxMainFuncId );

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_StatusType,COM_VAR)          Com_Uninit_Flag;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(PduLengthType,COM_VAR)           Com_TpTxIpduLength_auo[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_RxSignalGrpFlagType,COM_VAR) Com_RxSignalGrpFlag[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif
#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_TxSignalGrpFlagType,COM_VAR) Com_TxSignalGrpFlag[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_TxGrpSignalFlagType,COM_VAR) Com_TxGrpSignalFlag[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_RxIpduRamData,COM_VAR)    Com_RxIpduRam_s[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_TxIpduRamData,COM_VAR)    Com_TxIpduRam_s[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_TxSignalFlagType,COM_VAR)   Com_TxSignalFlag[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_RxSignalFlagType,COM_VAR)   Com_RxSignalFlag[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
extern VAR(uint8,COM_VAR)    Com_IpduCounter_s[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
extern VAR(uint8,COM_VAR)    Com_IpduCounter_DM[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#if (COM_COMMON_TX_PERIOD == STD_ON)

#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
extern VAR(uint16,COM_VAR) Com_ReducedPeriod_u16;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(PduIdType,COM_VAR)    Com_RxGwQueue_aux[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_RxGwQueueRAMType, COM_VAR) Com_RxGwQueue_S;
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST) Com_Lok_Config_pcst;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_TransModeInfo ,COM_CONST) Com_NONE_TransModeInfo;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
# define COM_START_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
# include "Com_MemMap.h"
    extern VAR(boolean, AUTOMATIC) Com_IsGwSignalsUpdated_ab[ ];
# define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
# include "Com_MemMap.h"
#endif

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_SIGNALGATEWAY

extern CONST(Com_Lok_xGwMapSigCfg_tst ,COM_CONST) Com_Lok_xGwMapSigCfg_acst[];

extern CONST(Com_Lok_xGwMapSigIdCfg_tst ,COM_CONST) Com_Lok_xGwMapSigIdCfg_acst[];
#endif

#ifdef COM_SIGNALGROUPGATEWAY

extern CONST(Com_Lok_xGwMapGrpSigCfg_tst ,COM_CONST) Com_Lok_xGwMapGrpSigCfg_acst[];

extern CONST(Com_Lok_xGwMapGrpSigIdCfg_tst ,COM_CONST) Com_Lok_xGwMapGrpSigIdCfg_acst[];
#endif

extern CONST(Com_Lok_xTxSigCfg_tst,COM_CONST)         Com_Lok_xTxSigCfg_acst[];

extern CONST(Com_Lok_xRxSigCfg_tst,COM_CONST)         Com_Lok_xRxSigCfg_acst[];

extern CONST(Com_Lok_xTxIpduInfoCfg_tst,COM_CONST)      Com_Lok_xTxIpduCfg_acst[];

extern CONST(Com_Lok_xRxIpduInfoCfg_tst,COM_CONST)      Com_Lok_xRxIpduCfg_acst[];

extern CONST(Com_Lok_xIpduGrpInfoCfg_tst,COM_CONST)     Com_Lok_xIpduGrpCfg_acst[];

extern CONST(Com_ConfigData_tst,COM_APPL_CONST) Com_Lok_Config_cst;

extern CONST(Com_IpduIdType ,COM_CONST) Com_Lok_xIPduGrp_IpduRefCfg_au8[];

#ifdef COM_TX_SIGNALGROUP

extern CONST(Com_Lok_xTxSigGrpCfg_tst,COM_CONST)  Com_Lok_xTxSigGrpCfg_acst[];

#ifdef COM_TX_SIGNALGROUP_ARRAY

extern CONST(Com_Lok_xTxSigGrpArrayCfg_tst, COM_CONST) Com_Lok_xTxSigGrpArrayCfg_acst[];

#endif

#endif

#ifdef COM_RX_SIGNALGROUP

extern CONST(Com_Lok_xRxSigGrpCfg_tst,COM_CONST)  Com_Lok_xRxSigGrpCfg_acst[];

#ifdef COM_RX_SIGNALGROUP_ARRAY

extern CONST(Com_Lok_xRxSigGrpArrayCfg_tst, COM_CONST) Com_Lok_xRxSigGrpArrayCfg_acst[];
#endif

#endif

#ifdef COM_TX_SIGNALGROUP

extern CONST(Com_Lok_xTxGrpSigCfg_tst,COM_CONST)  Com_Lok_xTxGrpSigCfg_acst[];
#endif

#ifdef COM_RX_SIGNALGROUP

extern CONST(Com_Lok_xRxGrpSigCfg_tst,COM_CONST)  Com_Lok_xRxGrpSigCfg_acst[];
#endif

extern CONST(Com_MainFunctionCfgType, COM_CONST) Com_MainFunctionCfg[];

extern CONST(Com_Lok_xRxRamBuf_tst, COM_CONST) Com_Lok_xRxRamBuf_acst[];

#ifdef COM_TX_SIGNALGROUP

extern CONST(Com_Lok_xTxSigGrpRamBuf_tst, COM_CONST) Com_Lok_xTxSigGrpRamBuf_acst[];

#endif

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)

#define COM_GET_TX_IPDU_CONSTDATA(COMPDUID)                &(Com_Lok_Config_pcst->Com_TxIpdu_pcst[COMPDUID])

#define COM_GET_TX_IPDU_ID(COMPDUID)                       (Com_Lok_Config_pcst->Com_TxIpduMapping_pcst[COMPDUID])

#define COM_GET_RX_IPDU_CONSTDATA(COMPDUID)                &(Com_Lok_Config_pcst->Com_RxIpdu_pcst[COMPDUID])

#define COM_GET_RX_IPDU_ID(COMPDUID)                       (Com_Lok_Config_pcst->Com_RxIpduMapping_pcst[COMPDUID])

#define COM_GET_IPDUGRP_CONSTDATA(COMPDUID)                &(Com_Lok_Config_pcst->Com_IpduGrp_pcst[COMPDUID])

#define COM_GET_IPDUGRP_ID(COMPDUID)                       (Com_Lok_Config_pcst->Com_IpduGrpMapping_pcu16[COMPDUID])

#define COM_GET_IPDUGRP_IPDUREF_CONSTDATA(COMPDUID)        &(Com_Lok_Config_pcst->Com_IPduGrp_IpduRef_pcst[COMPDUID])

#define COM_GET_RXSIG_CONSTDATA(COMSIGID)                  &(Com_Lok_Config_pcst->Com_RxSig_pcst[COMSIGID])

#define COM_GET_RXSIGNAL_ID(COMSIGID)                      (Com_Lok_Config_pcst->Com_RxSignalMapping_pct[COMSIGID])

#define COM_GET_TXSIG_CONSTDATA(COMSIGID)                  &(Com_Lok_Config_pcst->Com_TxSig_pcst[COMSIGID])

#define COM_GET_TXSIGNAL_ID(COMSIGID)                      (Com_Lok_Config_pcst->Com_TxSignalMapping_pct[COMSIGID])

#define COM_GET_TXSIGGRP_CONSTDATA(COMSIGGRPID)            &(Com_Lok_Config_pcst->Com_TxSigGrp_pcst[COMSIGGRPID])

#define COM_GET_TXSIGNALGRP_ID(COMSIGGRPID)                (Com_Lok_Config_pcst->Com_TxSignalGrpMapping_pct[COMSIGGRPID])

#define COM_GET_RXSIGGRP_CONSTDATA(COMSIGGRPID)            &(Com_Lok_Config_pcst->Com_RxSigGrp_pcst[COMSIGGRPID])

#define COM_GET_RXSIGNALGRP_ID(COMSIGGRPID)                (Com_Lok_Config_pcst->Com_RxSignalGrpMapping_pct[COMSIGGRPID])

#define COM_GET_TXGRPSIG_CONSTDATA(COMGRPSIGID)            &(Com_Lok_Config_pcst->Com_TxGrpSig_pcst[COMGRPSIGID])

#define COM_GET_TXGRPSIGNAL_ID(COMGRPSIGID)                (Com_Lok_Config_pcst->Com_TxGrpSignalMapping_pct[COMGRPSIGID])

#define COM_GET_RXGRPSIG_CONSTDATA(COMGRPSIGID)            &(Com_Lok_Config_pcst->Com_RxGrpSig_pcst[COMGRPSIGID])

#define COM_GET_RXGRPSIGNAL_ID(COMGRPSIGID)                (Com_Lok_Config_pcst->Com_RxGrpSignalMapping_pct[COMGRPSIGID])

#define COM_GET_GWSIG_CONSTDATA(COMGWID)                   &(Com_Lok_Config_pcst->Com_GwSig_pcst[COMGWID])

#define COM_GET_GWSIGIDMAP_CONSTDATA(COMGWID)              &(Com_Lok_Config_pcst->Com_GwSigIdMapping_pcst[COMGWID])

#define COM_GET_GWGRPSIG_CONSTDATA(COMGWGRPSIGID)          &(Com_Lok_Config_pcst->Com_GwGrpSig_pcst[COMGWGRPSIGID])

#define COM_GET_GWGRPSIGIDMAP_CONSTDATA(COMGWGRPSIGID)     &(Com_Lok_Config_pcst->Com_GwGrpSigIdMapping_pcst[COMGWGRPSIGID])

#define COM_GET_NUM_TOTAL_IPDU_GRP                         (Com_Lok_Config_pcst->noOfIpduGroup)

#define COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP                  (Com_Lok_Config_pcst->noOfIpdusInLastIpduGrp)

#if defined ( COM_TX_SIGNALGROUP_ARRAY )

# define COM_GET_TXSIGGRP_ARRAY_CONSTDATA(SIGGRP_INDEX)    &(Com_Lok_Config_pcst->Com_TxSigGrpArray_pcst[(SIGGRP_INDEX)])
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )

# define COM_GET_RXSIGGRP_ARRAY_CONSTDATA(SIGGRP_INDEX)    &(Com_Lok_Config_pcst->Com_RxSigGrpArray_pcst[(SIGGRP_INDEX)])
#endif

#if defined(COM_TXSIG_FLOAT64SUPP ) || defined(COM_TXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXSIG_FLOAT64SUPP)

#define COM_GET_FLOAT_ARRAY_VALUE(val)                ((Com_Lok_Config_pcst->floatValArray_pcaf64)[(val)])
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)

#define COM_GET_MASK_X(FilterIndex)                   (Com_Lok_Config_pcst->Com_MaskX_pcst[FilterIndex])
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_GET_MASK(FilterIndex)                     (Com_Lok_Config_pcst->Com_Mask_pu32[FilterIndex])
#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)

#define COM_GET_POSMINMAX(FilterIndex)                (Com_Lok_Config_pcst->Com_POSMinMax_pcst[FilterIndex])
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

#define COM_GET_NEGMINMAX(FilterIndex)                (Com_Lok_Config_pcst->Com_NEGMinMax_pcst[FilterIndex])
#endif

#define COM_GET_MAINFUNCTION_CFG(MF_ID)          (Com_Lok_Config_pcst->Com_MainFunctionCfg_pcst[ MF_ID ])

#ifdef COM_F_ONEEVERYN

#define COM_GET_ONEEVERYN_CONST(FILTER_INDEX)              (Com_Lok_Config_pcst->Com_OneEveryN_Const_pcst[FILTER_INDEX])

#define COM_GET_ONEEVERYN(FILTER_INDEX)                    (Com_Lok_Config_pcst->Com_OneEveryN_pe[FILTER_INDEX])
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_GET_F_OLDVALUE(FILTER_INDEX)                   (Com_Lok_Config_pcst->Com_F_OldVal_pu32[FILTER_INDEX])
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)

#define COM_GET_OLDVALTRIGONCHANGE(OLDVAL_INDEX)           (Com_Lok_Config_pcst->Com_OldValTrigOnChng_puo[OLDVAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT8_BUFF(MF_ID,SIGNAL_INDEX)            (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu8[SIGNAL_INDEX])
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

#define COM_GET_SIGTYPEUINT8DYN_BUFF(MF_ID,SIGNAL_INDEX)         (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_dyn_pu8[SIGNAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT16_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu16[SIGNAL_INDEX])

#define COM_GET_SIGTYPEUINT32_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu32[SIGNAL_INDEX])

#ifdef COM_RXSIG_INT64

#define COM_GET_SIGTYPEUINT64_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu64[SIGNAL_INDEX])
#endif

#ifdef COM_RXSIG_FLOAT64SUPP

#define COM_GET_SIGTYPEFLOAT64_BUFF(MF_ID,SIGNAL_INDEX)          (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pf64[SIGNAL_INDEX])
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_GET_RXGRPSIGTYPEUINT8_BUFF(MF_ID,GRPSIGNAL_INDEX)    (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_RXGRPSIGTYPEUINT16_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_RXGRPSIGTYPEUINT32_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_RXGRPSIG_INT64

#define COM_GET_RXGRPSIGTYPEUINT64_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP

#define COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX)  (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#define COM_GET_SECRXGRPSIGTYPEU8_BUFF(MF_ID,GRPSIGNAL_INDEX)    (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SecondRxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_SECRXGRPSIGTYPEU16_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SecondRxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_SECRXGRPSIGTYPEU32_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SecondRxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_RXGRPSIG_INT64

#define COM_GET_SECRXGRPSIGTYPEU64_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SecondRxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP

#define COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX) (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SecondRxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY

# define COM_GET_RXSIGGRP_ARRAY_BUFF(MF_ID,SIGGRP_INDEX)        (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_RxSigGrpArrayBuf_pu8[(SIGGRP_INDEX)])
#endif

#endif

#ifdef COM_TX_SIGNALGROUP

#define COM_GET_TXGRPSIGTYPEU8_BUFF(MF_ID,GRPSIGNAL_INDEX)       \
        (Com_Lok_Config_pcst->Com_TxSigGrpRamBuf_pcst[MF_ID].Com_TxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_TXGRPSIGTYPEU16_BUFF(MF_ID,GRPSIGNAL_INDEX)      \
        (Com_Lok_Config_pcst->Com_TxSigGrpRamBuf_pcst[MF_ID].Com_TxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_TXGRPSIGTYPEU32_BUFF(MF_ID,GRPSIGNAL_INDEX)      \
        (Com_Lok_Config_pcst->Com_TxSigGrpRamBuf_pcst[MF_ID].Com_TxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_TXGRPSIG_INT64

#define COM_GET_TXGRPSIGTYPEU64_BUFF(MF_ID,GRPSIGNAL_INDEX)      \
        (Com_Lok_Config_pcst->Com_TxSigGrpRamBuf_pcst[MF_ID].Com_TxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP

#define COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX)  \
        (Com_Lok_Config_pcst->Com_TxSigGrpRamBuf_pcst[MF_ID].Com_TxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#endif

#ifdef COM_TP_IPDUTYPE

#define COM_GET_TPTXIPDULENGTH_AUO(COMTXIPDUID)            (Com_Lok_Config_pcst->Com_TpTxIpduLength_pauo[COMTXIPDUID])
#endif

#define COM_GET_TXPDURAM_S(COMTXIPDUID)                    (Com_Lok_Config_pcst->Com_TxIpduRam_ps[COMTXIPDUID])

#define COM_GET_RXPDURAM_S(COMRXIPDUID)                    (Com_Lok_Config_pcst->Com_RxIpduRam_ps[COMRXIPDUID])

#define COM_GET_TXSIGNALFLAG(COMTXSIGID)                    (Com_Lok_Config_pcst->Com_TxSignalFlag_ps[COMTXSIGID])

#define COM_GET_RXSIGNALFLAG(COMRXSIGID)                    (Com_Lok_Config_pcst->Com_RxSignalFlag_ps[COMRXSIGID])

#define COM_GET_IPDUCOUNTER_S(COMPDUID)                    (Com_Lok_Config_pcst->Com_IpduCounter_ps[COMPDUID])

#define COM_GET_IPDUCOUNTER_DM(COMPDUID)                    (Com_Lok_Config_pcst->Com_IpduCounter_DM_ps[COMPDUID])

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_GET_RXGWQUEUE_AUX(COMPDUID)                    (Com_Lok_Config_pcst->Com_RxGwQueue_paux[COMPDUID])

#define COM_GET_RXGWQUEUE_S                                (Com_Lok_Config_pcst->Com_RxGwQueue_ps)
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_GET_RXSIGGRPFLAG(COMSIGGRPID)                  (Com_Lok_Config_pcst->Com_RxSignalGrpFlag_ps[COMSIGGRPID])
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

#define COM_GET_TXSIGGRPFLAG(COMSIGGRPID)                  (Com_Lok_Config_pcst->Com_TxSignalGrpFlag_ps[COMSIGGRPID])
#endif

#define COM_GET_TXGRPSIGFLAG(COMGRPSIGID)                  (Com_Lok_Config_pcst->Com_TxGrpSignalFlag_ps[COMGRPSIGID])
#endif

#ifdef COM_RxIPduDeferredProcessing

#define COM_GET_DEFERREDBUFFER(MF_ID)                    (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_DeferredBuffer_pu8)
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_GET_IS_GWSIG_UPDATED(RXPDU_ID)                 (Com_Lok_Config_pcst->Com_IsGwSignalsUpdated_pab[(RXPDU_ID)])
#endif

#define COM_GET_NUM_RX_SIGNALS                             (Com_Lok_Config_pcst->noOfRxSignals)

#define COM_GET_NUM_TX_SIGNALS                             (Com_Lok_Config_pcst->noOfTxSignals)

#define COM_GET_NUM_TX_SIGNALGRP                           (Com_Lok_Config_pcst->noOfTxSignalGroup)

#define COM_GET_NUM_RX_SIGNALGRP                           (Com_Lok_Config_pcst->noOfRxSignalGroup)

#define COM_GET_NUM_TX_GRPSIGNALS                          (Com_Lok_Config_pcst->noOfTxGroupSignal)

#define COM_GET_NUM_RX_GRPSIGNALS                          (Com_Lok_Config_pcst->noOfRxGroupSignal)

#define COM_GET_NUM_TX_IPDU                                (Com_Lok_Config_pcst->noOfTxIpdu)

#define COM_GET_NUM_RX_IPDU                                (Com_Lok_Config_pcst->noOfRxIpdu)

#define COM_GET_NUM_GWSRC_SIGNALS                          (Com_Lok_Config_pcst->noOfGwSrcSignals)

#define COM_GET_NUM_GWSRC_GRPSIGNALS                       (Com_Lok_Config_pcst->noOfGwSrcGrpSignals)

#define COM_GET_NUM_GWSRC_IPDUS                            (Com_Lok_Config_pcst->noOfGwSrcIpdu)

#define COM_GET_NUM_GRPSIG_NOGW                            (Com_Lok_Config_pcst->noOfGrpSigNoGw)

#ifdef COM_F_ONEEVERYN
#define COM_GET_NUM_SIG_GRPSIG_WITH_ONE_EVERY_N_FILTER     (Com_Lok_Config_pcst->noOfOneEveryNSigAndGrpSig)
#endif

#else

#define COM_GET_TX_IPDU_CONSTDATA(COMPDUID)                (&Com_Lok_xTxIpduCfg_acst[COMPDUID])

#define COM_GET_TX_IPDU_ID(COMPDUID)                       (COMPDUID)

#define COM_GET_RX_IPDU_CONSTDATA(COMPDUID)                (&Com_Lok_xRxIpduCfg_acst[COMPDUID])

#define COM_GET_RX_IPDU_ID(COMPDUID)                       (COMPDUID)

#define COM_GET_IPDUGRP_CONSTDATA(COMPDUID)                (&Com_Lok_xIpduGrpCfg_acst[COMPDUID])

#define COM_GET_IPDUGRP_ID(COMPDUID)                       (COMPDUID)

#define COM_GET_IPDUGRP_IPDUREF_CONSTDATA(COMPDUID)        (&Com_Lok_xIPduGrp_IpduRefCfg_au8[COMPDUID])

#define COM_GET_RXSIG_CONSTDATA(COMSIGID)                  (&Com_Lok_xRxSigCfg_acst[COMSIGID])

 #define COM_GET_RXSIGNAL_ID(COMSIGID)                     (COMSIGID)

#define COM_GET_TXSIG_CONSTDATA(COMSIGID)                  (&Com_Lok_xTxSigCfg_acst[COMSIGID])

#define COM_GET_TXSIGNAL_ID(COMSIGID)                      (COMSIGID)

#define COM_GET_TXSIGGRP_CONSTDATA(COMSIGGRPID)            (&Com_Lok_xTxSigGrpCfg_acst[COMSIGGRPID])

#define COM_GET_TXSIGNALGRP_ID(COMSIGGRPID)                (COMSIGGRPID)

#define COM_GET_RXSIGGRP_CONSTDATA(COMSIGGRPID)            (&Com_Lok_xRxSigGrpCfg_acst[COMSIGGRPID])

#define COM_GET_RXSIGNALGRP_ID(COMSIGID)                   (COMSIGID)

#define COM_GET_TXGRPSIG_CONSTDATA(COMGRPSIGID)            (&Com_Lok_xTxGrpSigCfg_acst[COMGRPSIGID])

#define COM_GET_TXGRPSIGNAL_ID(COMGRPSIGID)                (COMGRPSIGID)

#define COM_GET_RXGRPSIG_CONSTDATA(COMGRPSIGID)            (&Com_Lok_xRxGrpSigCfg_acst[COMGRPSIGID])

#define COM_GET_RXGRPSIGNAL_ID(COMGRPSIGID)                (COMGRPSIGID)

#define COM_GET_GWSIG_CONSTDATA(COMGWID)                   (&Com_Lok_xGwMapSigCfg_acst[COMGWID])

#define COM_GET_GWSIGIDMAP_CONSTDATA(COMGWID)              (&Com_Lok_xGwMapSigIdCfg_acst[COMGWID])

#define COM_GET_GWGRPSIG_CONSTDATA(COMGWGRPSIGID)          (&Com_Lok_xGwMapGrpSigCfg_acst[COMGWGRPSIGID])

#define COM_GET_GWGRPSIGIDMAP_CONSTDATA(COMGWGRPSIGID)     (&Com_Lok_xGwMapGrpSigIdCfg_acst[COMGWGRPSIGID])

#define COM_GET_NUM_TOTAL_IPDU_GRP                         COM_NUM_TOTAL_IPDU_GRP

#define COM_GET_NUM_IPDUS_IN_LAST_IPDUGRP                  COM_NUM_IPDUS_IN_LAST_IPDUGRP

#if defined ( COM_TX_SIGNALGROUP_ARRAY )

# define COM_GET_TXSIGGRP_ARRAY_CONSTDATA(SIGGRP_INDEX)    (&Com_Lok_xTxSigGrpArrayCfg_acst[(SIGGRP_INDEX)])
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )

# define COM_GET_RXSIGGRP_ARRAY_CONSTDATA(SIGGRP_INDEX)    (&Com_Lok_xRxSigGrpArrayCfg_acst[(SIGGRP_INDEX)])
#endif

#if defined(COM_TXSIG_FLOAT64SUPP ) || defined(COM_TXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXSIG_FLOAT64SUPP)

#define COM_GET_FLOAT_ARRAY_VALUE(val)                     (Com_FloatValArray[(val)])
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)

#define COM_GET_MASK_X(FilterIndex)                        (Com_MaskX[FilterIndex])
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_GET_MASK(FilterIndex)                          (Com_Mask[FilterIndex])
#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)

#define COM_GET_POSMINMAX(FilterIndex)                     (Com_POSMinMax[FilterIndex])
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

#define COM_GET_NEGMINMAX(FilterIndex)                     (Com_NEGMinMax[FilterIndex])
#endif

#define COM_GET_MAINFUNCTION_CFG( MF_ID )                  (Com_MainFunctionCfg[ MF_ID ])

#ifdef COM_F_ONEEVERYN

#define COM_GET_ONEEVERYN_CONST(FILTER_INDEX)              (Com_OneEveryN_Const[FILTER_INDEX])

#define COM_GET_ONEEVERYN(FILTER_INDEX)                    (Com_OneEveryN[FILTER_INDEX])
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_GET_F_OLDVALUE(FILTER_INDEX)                   (Com_F_OldVal[FILTER_INDEX])
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)

#define COM_GET_OLDVALTRIGONCHANGE(OLDVAL_INDEX)           (Com_OldValTrigOnChng[OLDVAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT8_BUFF(MF_ID,SIGNAL_INDEX)            (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu8[SIGNAL_INDEX])
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

#define COM_GET_SIGTYPEUINT8DYN_BUFF(MF_ID,SIGNAL_INDEX)         (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_dyn_pu8[SIGNAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT16_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu16[SIGNAL_INDEX])

#define COM_GET_SIGTYPEUINT32_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu32[SIGNAL_INDEX])

#ifdef COM_RXSIG_INT64

#define COM_GET_SIGTYPEUINT64_BUFF(MF_ID,SIGNAL_INDEX)           (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pu64[SIGNAL_INDEX])
#endif

#ifdef COM_RXSIG_FLOAT64SUPP

#define COM_GET_SIGTYPEFLOAT64_BUFF(MF_ID,SIGNAL_INDEX)          (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SigType_pf64[SIGNAL_INDEX])
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_GET_RXGRPSIGTYPEUINT8_BUFF(MF_ID,GRPSIGNAL_INDEX)    (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_RXGRPSIGTYPEUINT16_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_RXGRPSIGTYPEUINT32_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_RXGRPSIG_INT64

#define COM_GET_RXGRPSIGTYPEUINT64_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP

#define COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX)  (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#define COM_GET_SECRXGRPSIGTYPEU8_BUFF(MF_ID,GRPSIGNAL_INDEX)    (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SecondRxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_SECRXGRPSIGTYPEU16_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SecondRxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_SECRXGRPSIGTYPEU32_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SecondRxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_RXGRPSIG_INT64

#define COM_GET_SECRXGRPSIGTYPEU64_BUFF(MF_ID,GRPSIGNAL_INDEX)   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SecondRxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP

#define COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX) (Com_Lok_xRxRamBuf_acst[MF_ID].Com_SecondRxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY

# define COM_GET_RXSIGGRP_ARRAY_BUFF(MF_ID,SIGGRP_INDEX)           (Com_Lok_xRxRamBuf_acst[MF_ID].Com_RxSigGrpArrayBuf_pu8[SIGGRP_INDEX])
#endif

#endif

#ifdef COM_TX_SIGNALGROUP

#define COM_GET_TXGRPSIGTYPEU8_BUFF(MF_ID,GRPSIGNAL_INDEX)              \
        (Com_Lok_xTxSigGrpRamBuf_acst[MF_ID].Com_TxGrpSigType_pu8[GRPSIGNAL_INDEX])

#define COM_GET_TXGRPSIGTYPEU16_BUFF(MF_ID,GRPSIGNAL_INDEX)             \
        (Com_Lok_xTxSigGrpRamBuf_acst[MF_ID].Com_TxGrpSigType_pu16[GRPSIGNAL_INDEX])

#define COM_GET_TXGRPSIGTYPEU32_BUFF(MF_ID,GRPSIGNAL_INDEX)             \
        (Com_Lok_xTxSigGrpRamBuf_acst[MF_ID].Com_TxGrpSigType_pu32[GRPSIGNAL_INDEX])

#ifdef COM_TXGRPSIG_INT64

#define COM_GET_TXGRPSIGTYPEU64_BUFF(MF_ID,GRPSIGNAL_INDEX)             \
        (Com_Lok_xTxSigGrpRamBuf_acst[MF_ID].Com_TxGrpSigType_pu64[GRPSIGNAL_INDEX])
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP

#define COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(MF_ID,GRPSIGNAL_INDEX)         \
        (Com_Lok_xTxSigGrpRamBuf_acst[MF_ID].Com_TxGrpSigType_pf64[GRPSIGNAL_INDEX])
#endif

#endif

#ifdef COM_TP_IPDUTYPE

#define COM_GET_TPTXIPDULENGTH_AUO(COMTXIPDUID)            (Com_TpTxIpduLength_auo[COMTXIPDUID])
#endif

#define COM_GET_TXPDURAM_S(COMTXIPDUID)                    (Com_TxIpduRam_s[COMTXIPDUID])

#define COM_GET_RXPDURAM_S(COMRXIPDUID)                    (Com_RxIpduRam_s[COMRXIPDUID])

#define COM_GET_TXSIGNALFLAG(COMTXSIGID)                    (Com_TxSignalFlag[COMTXSIGID])

#define COM_GET_RXSIGNALFLAG(COMRXSIGID)                    (Com_RxSignalFlag[COMRXSIGID])

#define COM_GET_IPDUCOUNTER_S(COMPDUID)                    (Com_IpduCounter_s[COMPDUID])

#define COM_GET_IPDUCOUNTER_DM(COMPDUID)                    (Com_IpduCounter_DM[COMPDUID])

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_GET_RXGWQUEUE_AUX(COMPDUID)                    (Com_RxGwQueue_aux[COMPDUID])

#define COM_GET_RXGWQUEUE_S                                &(Com_RxGwQueue_S)
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_GET_RXSIGGRPFLAG(COMSIGGRPID)                  (Com_RxSignalGrpFlag[COMSIGGRPID])
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

#define COM_GET_TXSIGGRPFLAG(COMSIGGRPID)                  (Com_TxSignalGrpFlag[COMSIGGRPID])
#endif

#define COM_GET_TXGRPSIGFLAG(COMGRPSIGID)                  (Com_TxGrpSignalFlag[COMGRPSIGID])
#endif

#ifdef COM_RxIPduDeferredProcessing

#define COM_GET_DEFERREDBUFFER(MF_ID)                   (Com_Lok_xRxRamBuf_acst[MF_ID].Com_DeferredBuffer_pu8)
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_GET_IS_GWSIG_UPDATED(RXIPDU_ID)                (Com_IsGwSignalsUpdated_ab[(RXIPDU_ID)])
#endif

#define COM_GET_NUM_RX_SIGNALS                             (COM_NUM_RX_SIGNALS)

#define COM_GET_NUM_TX_SIGNALS                             (COM_NUM_TX_SIGNALS)

#define COM_GET_NUM_TX_SIGNALGRP                           (COM_NUM_TX_SIGNALGRP)

#define COM_GET_NUM_RX_SIGNALGRP                           (COM_NUM_RX_SIGNALGRP)

#define COM_GET_NUM_TX_GRPSIGNALS                          (COM_NUM_TX_GRPSIGNALS)

#define COM_GET_NUM_RX_GRPSIGNALS                          (COM_NUM_RX_GRPSIGNALS)

#define COM_GET_NUM_TX_IPDU                                (COM_NUM_TX_IPDU)

#define COM_GET_NUM_RX_IPDU                                (COM_NUM_RX_IPDU)

#define COM_GET_NUM_GWSRC_SIGNALS                          (COM_NUM_GWSRC_SIGNALS)

#define COM_GET_NUM_GWSRC_GRPSIGNALS                       (COM_NUM_GWSRC_GRPSIGNALS)

#define COM_GET_NUM_GWSRC_IPDUS                            (COM_NUM_GWSRC_IPDUS)

#define COM_GET_NUM_GRPSIG_NOGW                            (COM_NUM_GRPSIG_NOGW)

#ifdef COM_F_ONEEVERYN
#define COM_GET_NUM_SIG_GRPSIG_WITH_ONE_EVERY_N_FILTER     (COM_NUM_OF_SIG_GRPSIG_WITH_ONE_EVERY_N)
#endif

#endif

#ifdef COM_RxIPduTimeout

#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION

#define COM_GET_RXIPDU_TIMEOUT(ComRxPduId, RxIPduConstPtr)             Com_GetRxIPduTimeoutCalibration((PduIdType)ComRxPduId)
#else

#define COM_GET_RXIPDU_TIMEOUT(ComRxPduId, RxIPduConstPtr)             (RxIPduConstPtr->Timeout_Fact)

#endif

#endif

#ifdef COM_TXPDU_TIMEOFFSET_VIA_CALIBRATION

#define COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, CurrentTxModePtr)        Com_GetTxIPduTimeOffsetCalibration((PduIdType)ComTxPduId)
#else

#define COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, CurrentTxModePtr)        (CurrentTxModePtr->TimeOffsetFact)

#endif

#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        COM_getTxIPduCyclePeriod((PduIdType)ComTxPduId)
#elif (COM_COMMON_TX_PERIOD == STD_ON)

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        ((Com_ReducedPeriod_u16 == 0)? \
                                                                       ((CurrentTxModePtr)->TimePeriodFact) : Com_ReducedPeriod_u16)
#else

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        ((CurrentTxModePtr)->TimePeriodFact)

#endif

#ifdef COM_TXPDU_NUMOFREPETITION_VIA_CALIBRATION

#define COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, CurrentTxModePtr)   Com_GetTxIPduNumberOfRepetitionCalibration((PduIdType)ComTxPduId)
#else

#define COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, CurrentTxModePtr)   (CurrentTxModePtr->NumOfRepetitions)

#endif

#endif
