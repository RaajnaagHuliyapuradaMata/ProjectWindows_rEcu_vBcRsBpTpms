

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
#if(COM_ENABLE_INTER_MODULE_CHECKS)

# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
# error "AUTOSAR major version undefined or mismatched"
# endif
# if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
# error "AUTOSAR minor version undefined or mismatched"
# endif
#endif
#endif

#ifdef COM_ARSRVLIB_SUPPORT
#include "Bfx.h"
#if(COM_ENABLE_INTER_MODULE_CHECKS)

# if (!defined(BFX_AR_RELEASE_MAJOR_VERSION) || (BFX_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
# error "AUTOSAR major version undefined or mismatched"
# endif
# if (!defined(BFX_AR_RELEASE_MINOR_VERSION) || (BFX_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
# error "AUTOSAR minor version undefined or mismatched"
# endif
#endif
#endif

#define COM_BOOL_TO_UNSIGNED(BoolValue)                 ((BoolValue) ? (COM_SET) : (COM_RESET))

#define COM_F32_SIZE_IN_BYTES                           (4u)

#define COM_F64_SIZE_IN_BYTES                           (8u)

#define COM_LITTLEENDIAN                                (0u)

#define COM_BIGENDIAN                                   (1u)

#define COM_OPAQUE                                      (0u)

#define COM_IMMEDIATE                                   (FALSE)

#define COM_DEFERRED                                    (TRUE)

#define COM_TRIGGERED_ON_CHANGE                         (0u)

#define COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION      (1u)

#define COM_PENDING                                     (2u)

#define COM_TRIGGERED_WITHOUT_REPETITION                (3u)

#define COM_TRIGGERED                                   (4u)

#define COM_SIG_TP_IS_TRIGGERED(TransProp)              ((TransProp) > COM_PENDING)

#define COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TransProp)    ((TransProp) < COM_PENDING)

#define COM_SIG_TP_IS_WITHOUT_REPETITION(TransProp)     (((TransProp) & 0x1u) != 0u)

#define COM_RESET                                       (0u)

#define COM_SET                                         (1u)

#define COM_REPLACE_TO_INIT                             (2u)

#define COM_STOP                                        (FALSE)

#define COM_START                                       (TRUE)

#define COM_ACCEPT                                      (TRUE)

#define COM_REJECT                                      (FALSE)

#define COM_TXMODE_DIRECT                               (0x00u)

#define COM_TXMODE_MIXED                                (0x01u)

#define COM_TXMODE_NONE                                 (0x02u)

#define COM_TXMODE_PERIODIC                             (0x03u)

#define COM_CLRUPDATEBIT_TRANSMIT                       (1u)

#define COM_CLRUPDATEBIT_TRIGGERTRANSMIT                (2u)

#define COM_CLRUPDATEBIT_CONFIRMATION                   (3u)

#define COM_CLRUPDATEBIT_NONE                           (0u)

#define COM_TRUE                                        (TRUE)

#define COM_FALSE                                       (FALSE)

#define COM_NONE                                        (0u)

#define COM_REPLACE                                     (1u)

#define COM_NOTIFY                                      (2u)

#define COM_NOT_USED                                    (0u)

#define COM_MAXIMUM_GWSYNC_REPITIONS                    (2u)

#define COM_ZERO                                        (0u)

#define COM_ONE                                         (1u)

#define COM_TWO                                         (2u)

#define COM_UINT8                                       (0x00u)

#define COM_SINT8                                       (0x01u)

#define COM_UINT16                                      (0x02u)

#define COM_SINT16                                      (0x03u)

#define COM_UINT32                                      (0x04u)

#define COM_SINT32                                      (0x05u)

#define COM_UINT64                                      (0x10u)

#define COM_SINT64                                      (0x11u)

#define COM_BOOLEAN                                     (0x06u)

#define COM_UNDEFTYPE                                   (0x07)

#define COM_UINT8_N                                     (0x08u)

#define COM_UINT8_DYN                                   (0x0Au)

#define COM_FLOAT32                                     (0x0Cu)

#define COM_FLOAT64                                     (0x0Eu)

#define COM_ALWAYS                                      (0u)

#define COM_NEVER                                       (1u)

#define COM_MASKED_NEW_EQUALS_X                         (2u)

#define COM_MASKED_NEW_DIFFERS_X                        (3u)

#define COM_MASKED_NEW_DIFFERS_MASKED_OLD               (4u)

#define COM_NEW_IS_WITHIN_POS                           (5u)

#define COM_NEW_IS_WITHIN_NEG                           (6u)

#define COM_NEW_IS_OUTSIDE_POS                          (7u)

#define COM_NEW_IS_OUTSIDE_NEG                          (8u)

#define COM_ONE_EVERY_N                                 (9u)

#define COM_NOTCONFIGURED                               (10u)

#define COM_MODE_VALID                                  (0u)

#define COM_TRUEMODE_VALID                              (1u)

#define COM_FALSEMODE_VALID                             (2u)

#define COM_CLEAR_SENDIPDU_FLAGS                        {0u,0u,0u,0u,0u,0u}

#define COM_UPDATEBIT_NOT_APPLICABLE                    (0x00u)

#define COM_UPDATEBIT_APPLICABLE                        (0x01u)

#define COM_UPDATEBIT_SET                               (0x02u)

#define COM_GET_BASE_2_POWER_X(BIT_SIZE)                (((uint16)1u) << ((uint16)(BIT_SIZE)))

#define COM_MAX_U_VALUE_OF_X_BITS(BIT_SIZE)             (COM_GET_BASE_2_POWER_X(BIT_SIZE) - 1u)

#define COM_TX_MODE_IS_CYCLIC(TX_MODE)                  (((TX_MODE) & 0x1u) > COM_ZERO)

#define COM_TX_MODE_IS_EVENT(TX_MODE)                   ((TX_MODE) < COM_TXMODE_NONE)

#define COM_MEMCOPY   (xDest_pv,  xSrc_pcv,  numBytes_u32)              \
             (void)rba_BswSrv_MemCopy((void*)(xDest_pv),     (const void*)(xSrc_pcv),  (numBytes_u32))

#define COM_MEMCOMPARE(xSrc1_pcv, xSrc2_pcv, numBytes_u32)              \
             rba_BswSrv_MemCompare((const void*)(xSrc1_pcv), (const void*)(xSrc2_pcv), (numBytes_u32))

#ifndef COM_ARSRVLIB_SUPPORT

# define COM_UNPACK_CNTR_FROM_IPDU_BUFF(Data, StartPos, Size)             \
             (uint8)(((uint8)Data >> (uint8)StartPos) & ((uint8)COM_MAX_U_VALUE_OF_X_BITS(Size)))

#else
# define COM_UNPACK_CNTR_FROM_IPDU_BUFF(Data, StartPos, Size)             \
             Bfx_GetBits_u8u8u8_u8(Data, StartPos, Size)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
# define COM_PACK_CNTR_INTO_IPDU_BUFF(DataPtr, StartPos, Size, Counter)   \
            *((uint8 *)DataPtr) = \
            ((*((uint8 *)DataPtr) & (uint8)(~((uint8)((uint8)COM_MAX_U_VALUE_OF_X_BITS(Size)) << (uint8)StartPos))) |\
            (uint8)((uint8)Counter << (uint8)StartPos))

#else
# define COM_PACK_CNTR_INTO_IPDU_BUFF(DataPtr, StartPos, Size, Counter)   \
            Bfx_PutBits_u8u8u8u8(DataPtr, StartPos, Size, Counter)
#endif

#define COM_GET_CNTR_WRAP_AROUND_VALUE(Counter, MaxValue_u16)    (uint8)(((uint16)(Counter)) % ((uint16)(MaxValue_u16)))

#if(COM_CONFIGURATION_USE_DET == STD_ON)

#define COM_DET_NO_ERROR                    (0xFFu)

#define COM_REPORT_ERROR_CHECK(API, ERROR)  (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, (API), (ERROR));
#endif

#define Com_PerformSignExtension(Value,Size)    (Value) | (COM_SIGN_EXT_MASK << ((Size) - 1u))

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_PDUSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFEu)) | (uint16)(BitVal))

#else

#define Com_SetRamValue_TXIPDU_PDUSTATUS(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_PDUSTATUS(ByteValue)         ((uint16)(ByteValue) & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_PDUSTATUS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_CONFIR(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFDu)) | (uint16)((BitVal)<<1u))
#else

#define Com_SetRamValue_TXIPDU_CONFIR(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),1u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_CONFIR(ByteValue)         ((uint16)((ByteValue)>>1u) & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_CONFIR(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),1u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_TICKTXTO(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFFBu)) | (uint16)((BitVal)<<2u))
#else

#define Com_SetRamValue_TXIPDU_TICKTXTO(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),2u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_TICKTXTO(ByteValue)         ((uint16)((ByteValue) >> 2u) & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_TICKTXTO(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_MDT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFF7u)) | (uint16)((BitVal)<<3u))
#else

#define Com_SetRamValue_TXIPDU_MDT(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),3u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_MDT(ByteValue)         ((uint16)((ByteValue) >> 3u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_MDT(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_EVENTTRIG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFEFu)) | (uint16)((BitVal)<<4u))
#else

#define Com_SetRamValue_TXIPDU_EVENTTRIG(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),4u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_EVENTTRIG(ByteValue)         ((uint16)((ByteValue) >> 4u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_EVENTTRIG(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFDFu)) | (uint16)((BitVal)<<5u))
#else

#define Com_SetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),5u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue)         ((uint16)((ByteValue) >> 5u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_ISGWTRIGGRD(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_ISTOENABLED(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFFBFu)) | (uint16)((BitVal)<<6u))
#else

#define Com_SetRamValue_TXIPDU_ISTOENABLED(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),6u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_ISTOENABLED(ByteValue)         ((uint16)((ByteValue) >> 6u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_ISTOENABLED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint16)0xFF7Fu)) | (uint16)((BitVal) << 7u))
#else

#define Com_SetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue,BitVal)         Bfx_PutBit_u16u8u8(&(ByteValue),7u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue)        ((uint16)((ByteValue) >> 7u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_LARGEDATAINPROG(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue,BitVal)  (ByteValue) = (((ByteValue) & ((uint16)0xFEFF)) | \
                                                                                               (uint16)((BitVal) << 8u))
#else

#define Com_SetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue,BitVal)  Bfx_PutBit_u16u8u8(&(ByteValue),8u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue)         ((uint16)((ByteValue) >> 8u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_GWIPDUTMSCHANGED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue,BitVal)  (ByteValue) = (((ByteValue) & ((uint16)0xFDFFu)) | \
                                                                                              (uint16)((BitVal) << 9u))
#else

#define Com_SetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue,BitVal)  Bfx_PutBit_u16u8u8(&(ByteValue),9u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue)         ((uint16)((ByteValue) >> 9u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_RETRYFAILEDTXREQ(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),9u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_METADATA_REQUEST(ByteValue,BitVal) (ByteValue) = (((ByteValue) & ((uint16)0xFBFF)) | \
                                                                                          (uint16)((BitVal) << 10u))
#else

#define Com_SetRamValue_TXIPDU_METADATA_REQUEST(ByteValue,BitVal) Bfx_PutBit_u16u8u8(&(ByteValue),10u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_METADATA_REQUEST(ByteValue)        ((uint16)((ByteValue) >> 10u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_METADATA_REQUEST(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),10u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_MDTLOAD(ByteValue,BitVal) (ByteValue) = (((ByteValue) & ((uint16)0xF7FF)) | \
                                                                                          (uint16)((BitVal) << 11u))
#else

#define Com_SetRamValue_TXIPDU_MDTLOAD(ByteValue,BitVal) Bfx_PutBit_u16u8u8(&(ByteValue),11u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_MDTLOAD(ByteValue)        ((uint16)((ByteValue) >> 11u)  & (uint16)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_MDTLOAD(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),11u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_PDUSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXIPDU_PDUSTATUS(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_PDUSTATUS(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_PDUSTATUS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_DMSTATUS(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFDu)) | (uint8)((BitVal)<<1u))
#else

#define Com_SetRamValue_RXIPDU_DMSTATUS(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_DMSTATUS(ByteValue)         ((uint8)((ByteValue) >>1u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_DMSTATUS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),1u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_INDICATION(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFBu)) | (uint8)((BitVal)<<2u))
#else

#define Com_SetRamValue_RXIPDU_INDICATION(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_INDICATION(ByteValue)         ((uint8)((ByteValue) >>2u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_INDICATION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xF7u)) | (uint8)((BitVal)<<3u))
#else

#define Com_SetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),3u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue)         ((uint8)((ByteValue) >>3u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_GWPDU_TOBEPROCESSED(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue,BitVal)        (ByteValue) = (((ByteValue) & ((uint8)0xEFu)) | (uint8)((BitVal)<<4u))
#else

#define Com_SetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue,BitVal)        Bfx_PutBit_u8u8u8(&(ByteValue),4u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue)       ((uint8)((ByteValue) >>4u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_LARGEDATAINPROG(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_IS_FIRST_RECEPTION(ByteValue,BitVal)    (ByteValue) = (((ByteValue) & ((uint8)0xDFu)) | (uint8)((BitVal) << 5u))
#else

#define Com_SetRamValue_RXIPDU_IS_FIRST_RECEPTION(ByteValue,BitVal)    Bfx_PutBit_u8u8u8(&(ByteValue),5u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_IS_FIRST_RECEPTION(ByteValue)    ((uint8)((ByteValue) >> 5u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_IS_FIRST_RECEPTION(ByteValue)    Bfx_GetBit_u8u8_u8((ByteValue),5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_IS_INVALID(ByteValue,BitVal)    (ByteValue) = (((ByteValue) & ((uint8)0xBFu)) | (uint8)((BitVal) << 6u))
#else

#define Com_SetRamValue_RXIPDU_IS_INVALID(ByteValue,BitVal)    Bfx_PutBit_u8u8u8(&(ByteValue),6u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_IS_INVALID(ByteValue)    ((uint8)((ByteValue) >> 6u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_IS_INVALID(ByteValue)    Bfx_GetBit_u8u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXIPDU_RELOAD_RXTICKS(ByteValue,BitVal)    \
                                        (ByteValue) = (((ByteValue) & ((uint8)0x7Fu)) | (uint8)((BitVal) << 7u))
#else

#define Com_SetRamValue_RXIPDU_RELOAD_RXTICKS(ByteValue,BitVal)    Bfx_PutBit_u8u8u8(&(ByteValue),7u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXIPDU_RELOAD_RXTICKS(ByteValue)    ((uint8)((ByteValue) >> 7u)  & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXIPDU_RELOAD_RXTICKS(ByteValue)    Bfx_GetBit_u8u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_LATESTMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFCu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXIPDU_LATESTMODE(ByteValue,BitVal)         Bfx_PutBits_u8u8u8u8(&(ByteValue),0u,2u,(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_LATESTMODE(ByteValue)         ((uint8)((ByteValue)) & (uint8)(0x03u))
#else

#define Com_GetRamValue_TXIPDU_LATESTMODE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_TXMODESTATE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFBu)) | (uint8)((BitVal) << 2u))
#else

#define Com_SetRamValue_TXIPDU_TXMODESTATE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2u,(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_TXMODESTATE(ByteValue)         ((uint8)((ByteValue) >> 2u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_TXMODESTATE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xF7u)) | (uint8)((BitVal)<<3u))
#else

#define Com_SetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),3u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue)         ((uint8)((ByteValue) >> 3u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXIPDU_MIXEDPHASESHIFT(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXSIGGRP_TRIGONCHNG(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue,BitVal)       (ByteValue) = (((ByteValue) & ((uint8)0xFDu)) | (uint8)((BitVal)<<1u))
#else

#define Com_SetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue,BitVal)       Bfx_PutBit_u8u8u8(&(ByteValue),1u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue)      ((uint8)((ByteValue) >> 1u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXSIGGRP_ISGWUPDTD(ByteValue)      Bfx_GetBit_u8u8_u8((ByteValue),1u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_SIGNOTIF(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXSIGGRP_SIGNOTIF(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_SIGNOTIF(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIGGRP_SIGNOTIF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFDu)) | (uint8)(BitVal<<1u))
#else

#define Com_SetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue)        ((uint8)((ByteValue)>>1u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIGGRP_SIGNALFILLBIT(ByteValue)        Bfx_GetBit_u8u8_u8((ByteValue),1u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIGGRP_DMFILTERING(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFBu)) | (uint8)(BitVal<<2u))
#else

#define Com_SetRamValue_RXSIGGRP_DMFILTERING(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIGGRP_DMFILTERING(ByteValue)         ((uint8)((ByteValue)>>2u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIGGRP_DMFILTERING(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXGRPSIG_SIGCHNGMODE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_TXSIG_SIGCHNGMODE(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_TXSIG_SIGCHNGMODE(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_TXSIG_SIGCHNGMODE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_TXSIG_SIGCHNGMODE(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_SIGNOTIF(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFEu)) | (uint8)(BitVal))
#else

#define Com_SetRamValue_RXSIG_SIGNOTIF(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),0u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_SIGNOTIF(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIG_SIGNOTIF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_SIGNALFILLBIT(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFDu)) | (uint8)(BitVal<<1u))
#else

#define Com_SetRamValue_RXSIG_SIGNALFILLBIT(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),1u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_SIGNALFILLBIT(ByteValue)         ((uint8)((ByteValue)>>1u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIG_SIGNALFILLBIT(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),1u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_SetRamValue_RXSIG_DMFILTERING(ByteValue,BitVal)         (ByteValue) = (((ByteValue) & ((uint8)0xFBu)) | (uint8)(BitVal<<2u))
#else

#define Com_SetRamValue_RXSIG_DMFILTERING(ByteValue,BitVal)         Bfx_PutBit_u8u8u8(&(ByteValue),2u,(boolean)(BitVal))
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetRamValue_RXSIG_DMFILTERING(ByteValue)         ((uint8)((ByteValue)>>2u) & (uint8)(0x01u))
#else

#define Com_GetRamValue_RXSIG_DMFILTERING(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_SIGPROC(ByteValue)         ((uint16)(ByteValue) & ((uint16)0x01u))
#else

#define Com_GetValue_TXIPDU_SIGPROC(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_TMS(ByteValue)         ((uint16)((ByteValue) >>1u) & ((uint16)0x03u))
#else

#define Com_GetValue_TXIPDU_TMS(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),1u,2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_NONETOSTATUS(ByteValue)         ((uint16)((ByteValue) >>3u) & ((uint16)0x01u))
#else

#define Com_GetValue_TXIPDU_NONETOSTATUS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_CLRUPDBIT(ByteValue)         ((uint16)((ByteValue) >>4u) & ((uint16)0x03u))
#else

#define Com_GetValue_TXIPDU_CLRUPDBIT(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),4u,2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_FILTEREVALREQ(ByteValue)         ((uint16)((ByteValue) >>6u) & ((uint16)0x01u))
#else

#define Com_GetValue_TXIPDU_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISDYNIPDU(ByteValue)         ((uint16)((ByteValue) >>7u)  & (uint16)(0x01u))
#else

#define Com_GetValue_TXIPDU_ISDYNIPDU(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISGWPDU(ByteValue)         ((uint16)((ByteValue) >>8u)  & (uint16)(0x01u))
#else

#define Com_GetValue_TXIPDU_ISGWPDU(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISCALLOUTFRMTRIGTRANS(ByteValue)         ((uint16)((ByteValue) >>9u)  & (uint16)(0x01u))
#else

#define Com_GetValue_TXIPDU_ISCALLOUTFRMTRIGTRANS(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),9u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISLARGEDATAPDU(ByteValue)        ((uint16)((ByteValue) >>10u)  & (uint16)(0x01u))
#else

#define Com_GetValue_TXIPDU_ISLARGEDATAPDU(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),10u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXIPDU_ISCANCELTRANSMITSUPPORTED(ByteValue)        ((uint16)((ByteValue) >>11u)  & (uint16)(0x01u))
#else

#define Com_GetValue_TXIPDU_ISCANCELTRANSMITSUPPORTED(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),11u)
#endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_TXIPDU_PDUWITHPDUGRP(ByteValue)  ( ( uint16 )( ( ByteValue ) >> 12u ) & ( ( uint16 )0x01u ) )
# else

#  define Com_GetValue_TXIPDU_PDUWITHPDUGRP(ByteValue)  Bfx_GetBit_u16u8_u8( ( ByteValue ), 12u )
# endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_TXIPDU_DEFAULTTMSSTATUS(ByteValue)  ( ( uint16 )( ( ByteValue ) >> 13u ) & ( ( uint16 )0x01u ) )
# else

#  define Com_GetValue_TXIPDU_DEFAULTTMSSTATUS(ByteValue)  Bfx_GetBit_u16u8_u8( ( ByteValue ), 13u )
# endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXIPDU_SIGPROC(ByteValue)              ((uint8)(ByteValue) & ((uint8)0x01u))
#else

#define Com_GetValue_RXIPDU_SIGPROC(ByteValue)              Bfx_GetBit_u8u8_u8((ByteValue),0u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXIPDU_NOTIFCBK(ByteValue)             ((uint8)((ByteValue) >> 1u) & ((uint8)0x01u))
#else

#define Com_GetValue_RXIPDU_NOTIFCBK(ByteValue)             Bfx_GetBit_u8u8_u8((ByteValue),1u)
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXIPDU_ISGWPDU(ByteValue)            ((uint8)((ByteValue) >> 2u)  & (uint8)(0x01u))
# else

#  define Com_GetValue_RXIPDU_ISGWPDU(ByteValue)            Bfx_GetBit_u8u8_u8((ByteValue),2u)
# endif
#endif

#ifndef COM_ARSRVLIB_SUPPORT
# define Com_GetValue_RXIPDU_PDUWITHPDUGRP(ByteValue)       ((uint8)((ByteValue) >> 3u) & ((uint8)0x01u))
#else

# define Com_GetValue_RXIPDU_PDUWITHPDUGRP(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
# define Com_GetValue_RXIPDU_IS_TP_TYPE(ByteValue)          ((uint8)((ByteValue) >> 4u) & ((uint8)0x01u))
#else

# define Com_GetValue_RXIPDU_IS_TP_TYPE(ByteValue)          Bfx_GetBit_u8u8_u8((ByteValue),4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
# define Com_GetValue_RXIPDU_TP_INV_CFG(ByteValue)         ((uint8)((ByteValue) >> 5u) & ((uint8)0x01u))
#else

# define Com_GetValue_RXIPDU_TP_INV_CFG(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_INVACTION(ByteValue)         (((uint8)(ByteValue)) & ((uint8)0x03u))
#else

#define Com_GetValue_RXSIG_INVACTION(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_FILTRALG(ByteValue)         ((uint8)((ByteValue) >> 2u) & (uint8)(0x0Fu))
#else

#define Com_GetValue_RXSIG_FILTRALG(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),2u,4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_TOACTION(ByteValue)         (((uint8)((ByteValue) >> 6u)) & ((uint8)0x01u))
#else

#define Com_GetValue_RXSIG_TOACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIG_ISGWSIG(ByteValue)         (((uint8)((ByteValue) >> 7u)) & ((uint8)0x01u))
#else

#define Com_GetValue_RXSIG_ISGWSIG(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_TP(ByteValue)         ((uint16)(ByteValue) & (uint16)(0x07u))
#else

#define Com_GetValue_TXSIG_TP(ByteValue)          Bfx_GetBits_u16u8u8_u16((ByteValue),0u,3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_FILTRALG(ByteValue)         ((uint16)((ByteValue) >> 3u) & (uint16)(0x0Fu))
#else

#define Com_GetValue_TXSIG_FILTRALG(ByteValue)         Bfx_GetBits_u16u8u8_u16((ByteValue),3u,4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_INVACTION(ByteValue)         ((uint16)((ByteValue) >> 7u) & ((uint16)0x01u))
#else

#define Com_GetValue_TXSIG_INVACTION(ByteValue)        Bfx_GetBit_u16u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIG_TOENABLED(ByteValue)         (((uint16)((ByteValue) >> 8u)) & ((uint16)0x01u))
#else

#define Com_GetValue_TXSIG_TOENABLED(ByteValue)         Bfx_GetBit_u16u8_u8((ByteValue),8u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_TP(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x07u))
#else

#define Com_GetValue_TXSIGGRP_TP(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_TOENABLED(ByteValue)         (((uint8)((ByteValue) >> 3u)) & ((uint8)0x01u))
#else

#define Com_GetValue_TXSIGGRP_TOENABLED(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_FILTEREVALREQ(ByteValue)         (((uint8)((ByteValue) >> 4u)) & ((uint8)0x01u))
#else

#define Com_GetValue_TXSIGGRP_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),4u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_UPDBITCONF(ByteValue)         (((uint8)((ByteValue) >> 5u)) & ((uint8)0x01u))
#else

#define Com_GetValue_TXSIGGRP_UPDBITCONF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXSIGGRP_ARRAYACCESS(ByteValue)         (((uint8)((ByteValue) >> 6u)) & ((uint8)0x01u))
#else

#define Com_GetValue_TXSIGGRP_ARRAYACCESS(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_INVACTION(ByteValue)         (((uint8)(ByteValue)) & ((uint8)0x03u))
#else

#define Com_GetValue_RXSIGGRP_INVACTION(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_TOACTION(ByteValue)         (((uint8)((ByteValue) >> 2u)) & ((uint8)0x01u))
#else

#define Com_GetValue_RXSIGGRP_TOACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),2u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_ISGWSIGGRP(ByteValue)       (((uint8)((ByteValue) >> 3u)) & ((uint8)0x01u))
#else

#define Com_GetValue_RXSIGGRP_ISGWSIGGRP(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),3u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXSIGGRP_UPDBITCONF(ByteValue)       (((uint8)((ByteValue) >> 4u)) & ((uint8)0x01u))
#else

#define Com_GetValue_RXSIGGRP_UPDBITCONF(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),4u)
#endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXSIGGRP_ARRAYACCESS(ByteValue)       (((uint8)((ByteValue) >> 5u)) & ((uint8)0x01u))
# else

#  define Com_GetValue_RXSIGGRP_ARRAYACCESS(ByteValue)       Bfx_GetBit_u8u8_u8((ByteValue),5u)
# endif

# ifndef COM_ARSRVLIB_SUPPORT
#  define Com_GetValue_RXSIGGRP_FILTEREVALREQ(ByteValue)         (((uint8)((ByteValue) >> 6u)) & ((uint8)0x01u))
# else

#  define Com_GetValue_RXSIGGRP_FILTEREVALREQ(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
# endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1Fu))
#else

#define Com_GetValue_GEN_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5u) & (uint8)(0x01u))
#else

#define Com_GetValue_GEN_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5u) ? \
                                                       COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_GEN_UPDBITCONF(ByteValue)         ((uint8)((ByteValue) >> 6u) & (uint8)(0x01u))
#else

#define Com_GetValue_GEN_UPDBITCONF(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1Fu))
#else

#define Com_GetValue_TXGRPSIG_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5u) & (uint8)(0x01u))
#else

#define Com_GetValue_TXGRPSIG_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5u) ? \
                                                            COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_TP(ByteValue)         ((uint8)((ByteValue) >> 6u) & (uint8)(0x01u))
#else

#define Com_GetValue_TXGRPSIG_TP(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_TXGRPSIG_INVACTION(ByteValue)         ((uint8)((ByteValue) >> 7u) & ((uint8)0x01u))
#else

#define Com_GetValue_TXGRPSIG_INVACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),7u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_TYPE(ByteValue)         ((uint8)(ByteValue) & (uint8)(0x1Fu))
#else

#define Com_GetValue_RXGRPSIG_TYPE(ByteValue)         Bfx_GetBits_u8u8u8_u8((ByteValue),0u,5u)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_ENDIANESS(ByteValue)         ((uint8)((ByteValue) >> 5u) & (uint8)(0x01u))
#else

#define Com_GetValue_RXGRPSIG_ENDIANESS(ByteValue)         (Bfx_GetBit_u8u8_u8((ByteValue),5u) ? \
                                                            COM_BIGENDIAN : COM_LITTLEENDIAN)
#endif

#ifndef COM_ARSRVLIB_SUPPORT
#define Com_GetValue_RXGRPSIG_INVACTION(ByteValue)         ((uint8)((ByteValue) >> 6u) & ((uint8)0x01u))
#else

#define Com_GetValue_RXGRPSIG_INVACTION(ByteValue)         Bfx_GetBit_u8u8_u8((ByteValue),6u)
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
#define Com_Getbit(ByteValue, Bitpos) (((ByteValue) & ((uint8)(1u << (Bitpos)))) != 0u)
#endif

#define     Com_GetValue(ELEMENTTYPE,PROP,ByteValue)            Com_GetValue_##ELEMENTTYPE##PROP(ByteValue)

#define     Com_GetRamValue(ELEMENTTYPE,PROP,ByteValue)         Com_GetRamValue_##ELEMENTTYPE##PROP(ByteValue)

#define     Com_SetRamValue(ELEMENTTYPE,PROP,ByteValue,Value)   Com_SetRamValue_##ELEMENTTYPE##PROP(ByteValue,Value)

#define COM_CheckRxIPduDMStatus(IpduId) \
                         (Com_GetRamValue(RXIPDU,_DMSTATUS,COM_GET_RXPDURAM_S(IpduId).RxFlags) != COM_STOP)

#ifdef COM_RX_IPDUCONTROL_VIA_CALIBRATION

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_CheckRxIPduCalibrationVarStatus(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_TX_IPDUCONTROL_VIA_CALIBRATION

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_CheckTxIPduCalibrationVarStatus(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint16 Com_GetTxIPduCyclePeriod(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint16 Com_GetRxIPduTimeoutCalibration(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TXPDU_TIMEOFFSET_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint16 Com_GetTxIPduTimeOffsetCalibration(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TXPDU_NUMOFREPETITION_VIA_CALIBRATION
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint8 Com_GetTxIPduNumberOfRepetitionCalibration(PduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ByteCopy( uint8 * dest, const uint8 * src, uint32 Len );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ByteCopyInit(uint8 * dest, uint32 Init_Val, uint32 Length);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_PackSignal( uint8 Endianess, Com_BitpositionType  Bit_Pos, Com_BitsizeType Bitsize, Com_SigMaxType Src_Buf,
                                                                                                   uint8 * Dest_Buf );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if (defined(COM_TXSIG_FLOAT64SUPP) || defined(COM_TXGRPSIG_FLOAT64SUPP) ||\
    (defined(COM_RX_SIGNALGROUP_ARRAY) && defined(COM_RXGRPSIG_FLOAT64SUPP)))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_PackFloatSignal( uint8 Endianess, Com_BitpositionType Bit_Pos, float64 Src, uint8 * Dest_Buf );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
Com_SigMaxType Com_UnpackSignal(
                            uint8                       Endianess,
                            Com_BitpositionType         Bit_Pos,
                            Com_BitsizeType             Bitsize,
                            const uint8 *               Src_Buf,
                            boolean                     IsSigned
                               );

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined (COM_RXSIG_FLOAT64SUPP ) || defined(COM_RXGRPSIG_FLOAT64SUPP)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
float64 Com_UnPackFloatSignal(uint8 Endianess, Com_BitpositionType Bit_Pos, const uint8 * Src_Buf);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint32 Com_UnpackOpaqueSignal(Com_BitpositionType Bit_Pos, Com_BitsizeType SignalLength, const uint8 * Src_Buf);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_SendIpdu(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_TxChangeMode(Com_IpduIdType TxIpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxFilters

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_Lok_SigTxChangeMode(Com_SignalIdType SignalId, uint32 TxNewVal);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_Lok_SigGrpTxChangeMode(Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_ProcessSignal(PduIdType RxPduId, const PduInfoType * PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_ProcessSignalGroup(PduIdType RxPduId, const PduInfoType * PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_TxIPduStop(Com_IpduIdType IpduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
    void Com_ShadowBuffToIpduBuff(Com_SignalGroupIdType SignalGrpId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_FILTERS

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_Filter(uint32 NewVal, uint8 Algorithm, Com_FilterType FilterIndex, boolean CallContext_b);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ProcessRxIPdu(PduIdType RxPduId, const PduInfoType * PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_ClearUpdateBits(Com_TxIpduConstPtrType TxIpduConstPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
Std_ReturnType Com_WriteSigGwReceiveQueue(PduIdType ComRxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_PackRxSignalGwBufferData(Com_RxSigConstPtrType RxSigConstPtr, Com_SignalIdType l_TxGwDestId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_Lok_PackRxGrpSigGwBufferData(Com_RxGrpSigConstPtrType RxGrpSigConstPtr, Com_TxIntGrpSignalIdType l_TxGwDestId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_InternalTxConfirmation(PduIdType TxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
extern void ComAppl_IncompatibleGenerator(void);
#endif

extern uint8 Com_InternalSendSignal(Com_SignalIdType SignalId, const void * SignalDataPtr );
extern uint8 Com_InternalSendSignalGroup(Com_SignalGroupIdType SignalGroupId);
extern void Com_InternalInvalidateShadowSignal(Com_SignalIdType SignalId);

#ifdef COM_RX_MAINFUNCTION_PROC
extern void Com_InternalMainFunctionRx(Com_MainFuncType RxMainFuncId );
#endif

extern void Com_InternalMainFunctionTx(Com_MainFuncType TxMainFuncId );

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)
extern boolean Com_Lok_EnableRxDeadlineMonitoring(Com_IpduIdType IpduId);
#endif

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)
extern void Com_InvokeRxNotifications( PduIdType RxPduId );
#endif

#if defined(COM_RxIPduCallOuts) || defined(COM_RX_IPDUCOUNTER)
extern boolean Com_IsValidRxIpdu(PduIdType PduId, const PduInfoType * PduInfoPtr);
#endif

#ifdef COM_RXIPDU_TP_INVALIDATION
extern void Com_ExecuteRxInvalidActions(PduIdType PduId);
#endif

#if defined(COM_RxSigInvalid) || defined (COM_RxFilters)
extern boolean Com_Lok_ValidateRxSignal(Com_SignalIdType SignalId, Com_SigMaxType * RxNewValPtr);
#endif

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern Com_StatusType Com_Uninit_Flag;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern Com_IpduGroupVector Com_IpduGrpVector;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern Com_IpduGroupVector Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if (COM_COMMON_TX_PERIOD == STD_ON)

#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
extern uint16 Com_ReducedPeriod_u16;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
#endif

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
extern const Com_ConfigData_tst * Com_Lok_Config_pcst;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"
extern const Com_TransModeInfo Com_NONE_TransModeInfo;
#define COM_STOP_SEC_CONST_UNSPECIFIED
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

#define COM_GET_POSMINMAX(FilterIndex)                      (Com_Lok_Config_pcst->Com_POSMinMax_pcst[FilterIndex])
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

#define COM_GET_NEGMINMAX(FilterIndex)                      (Com_Lok_Config_pcst->Com_NEGMinMax_pcst[FilterIndex])
#endif

#define COM_GET_MAINFUNCTION_CFG(MF_ID)                     (Com_Lok_Config_pcst->Com_MainFunctionCfg_pcst[ MF_ID ])

#ifdef COM_TX_IPDUCOUNTER

#define COM_GET_TX_IPDU_CNTR_CONSTDATA(INDEX)               &(Com_Lok_Config_pcst->Com_TxIpduCntr_pcst[(INDEX)])
#endif

#ifdef COM_RX_IPDUCOUNTER

#define COM_GET_RX_IPDU_CNTR_CONSTDATA(INDEX)               &(Com_Lok_Config_pcst->Com_RxIpduCntr_pcst[(INDEX)])
#endif

#ifdef COM_F_ONEEVERYN

#define COM_GET_ONEEVERYN_CONST(FILTER_INDEX)               (Com_Lok_Config_pcst->Com_OneEveryN_Const_pcst[FILTER_INDEX])

#define COM_GET_ONEEVERYN(FILTER_INDEX)                     (Com_Lok_Config_pcst->Com_OneEveryN_pe[FILTER_INDEX])
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_GET_F_OLDVALUE(FILTER_INDEX)                    (Com_Lok_Config_pcst->Com_F_OldVal_pu32[FILTER_INDEX])
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)

#define COM_GET_OLDVALTRIGONCHANGE(OLDVAL_INDEX)            (Com_Lok_Config_pcst->Com_OldValTrigOnChng_puo[OLDVAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT8_BUFF(MF_ID,SIGNAL_INDEX)       (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu8[SIGNAL_INDEX])
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

#define COM_GET_SIGTYPEUINT8DYN_BUFF(MF_ID,SIGNAL_INDEX)    (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_dyn_pu8[SIGNAL_INDEX])
#endif

#define COM_GET_SIGTYPEUINT16_BUFF(MF_ID,SIGNAL_INDEX)      (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu16[SIGNAL_INDEX])

#define COM_GET_SIGTYPEUINT32_BUFF(MF_ID,SIGNAL_INDEX)      (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu32[SIGNAL_INDEX])

#ifdef COM_RXSIG_INT64

#define COM_GET_SIGTYPEUINT64_BUFF(MF_ID,SIGNAL_INDEX)      (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pu64[SIGNAL_INDEX])
#endif

#ifdef COM_RXSIG_FLOAT64SUPP

#define COM_GET_SIGTYPEFLOAT64_BUFF(MF_ID,SIGNAL_INDEX)     (Com_Lok_Config_pcst->Com_RxRamBuf_pcst[MF_ID].Com_SigType_pf64[SIGNAL_INDEX])
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

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

#define COM_GET_IPDUCOUNTER_DM(COMPDUID)                    (Com_Lok_Config_pcst->Com_IpduCounter_DM_ps[COMPDUID])
#endif

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

#ifdef COM_TX_IPDUCOUNTER

#define COM_GET_TXIPDU_CNTR_VAL(TX_CNTR_IDX)             (Com_Lok_Config_pcst->Com_TxIpduCntrVal_pau8[(TX_CNTR_IDX)])
#endif

#ifdef COM_RX_IPDUCOUNTER

#define COM_GET_RXIPDU_LAST_CNTR_VAL(RX_CNTR_IDX)        (Com_Lok_Config_pcst->Com_RxIpduLastCntrVal_pau8[(RX_CNTR_IDX)])
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

#ifdef COM_TX_IPDUCOUNTER

#define COM_GET_TX_IPDU_CNTR_CONSTDATA(TX_CNTR_IDX)        &(Com_Lok_xTxIpduCntrCfg_acst[(TX_CNTR_IDX)])
#endif

#ifdef COM_RX_IPDUCOUNTER

#define COM_GET_RX_IPDU_CNTR_CONSTDATA(RX_CNTR_IDX)        &(Com_Lok_xRxIpduCntrCfg_acst[(RX_CNTR_IDX)])
#endif

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

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

#define COM_GET_IPDUCOUNTER_DM(COMPDUID)                    (Com_IpduCounter_DM[COMPDUID])
#endif

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

#define COM_GET_DEFERREDBUFFER(MF_ID)                      (Com_Lok_xRxRamBuf_acst[MF_ID].Com_DeferredBuffer_pu8)
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_GET_IS_GWSIG_UPDATED(RXIPDU_ID)                (Com_IsGwSignalsUpdated_ab[(RXIPDU_ID)])
#endif

#ifdef COM_TX_IPDUCOUNTER

#define COM_GET_TXIPDU_CNTR_VAL(TX_CNTR_IDX)               (Com_TxIpduCntrValue_au8[(TX_CNTR_IDX)])
#endif

#ifdef COM_RX_IPDUCOUNTER

#define COM_GET_RXIPDU_LAST_CNTR_VAL(RX_CNTR_IDX)          (Com_RxIpduLastCntrValue_au8[(RX_CNTR_IDX)])
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

#ifdef COM_PDUBASEDLOCKSENABLED

#define Com_Get_SchM_Enter_Com_RxGateway                 SchM_Enter_Com_RxGateway();
#define Com_Get_SchM_Exit_Com_RxGateway                  SchM_Exit_Com_RxGateway();

#define Com_Get_SchM_Enter_Com_RxIPduProcess             SchM_Enter_Com_RxIPduProcess();
#define Com_Get_SchM_Exit_Com_RxIPduProcess              SchM_Exit_Com_RxIPduProcess();

#define Com_Get_SchM_Enter_Com_RxIndication              SchM_Enter_Com_RxIndication();
#define Com_Get_SchM_Exit_Com_RxIndication               SchM_Exit_Com_RxIndication();

#define Com_Get_SchM_Enter_Com_TxIPdu                    SchM_Enter_Com_TxIPdu();
#define Com_Get_SchM_Exit_Com_TxIPdu                     SchM_Exit_Com_TxIPdu();

#define Com_Get_SchM_Enter_Com_RxSigGwMcLockProtArea
#define Com_Get_SchM_Exit_Com_RxSigGwMcLockProtArea

#define Com_Get_SchM_Enter_Com_RxPduBuffer
#define Com_Get_SchM_Exit_Com_RxPduBuffer

#define Com_Get_SchM_Enter_Com_RxSigBuff(APINAME)
#define Com_Get_SchM_Exit_Com_RxSigBuff(APINAME)

#ifdef COM_RX_SIGNALGROUP_ARRAY
#define Com_Get_SchM_Enter_Com_RxSigGrpArrayBuff
#define Com_Get_SchM_Exit_Com_RxSigGrpArrayBuff
#endif

#define Com_Get_SchM_Enter_Com_RxGrpSigSecBuff
#define Com_Get_SchM_Exit_Com_RxGrpSigSecBuff

#define Com_Get_SchM_Enter_Com_RxSigToTicks
#define Com_Get_SchM_Exit_Com_RxSigToTicks

#define Com_Get_SchM_Enter_Com_RxSigGrpToTicks
#define Com_Get_SchM_Exit_Com_RxSigGrpToTicks

#define Com_Get_SchM_Enter_Com_RxSigDynBuff
#define Com_Get_SchM_Exit_Com_RxSigDynBuff

#define Com_Get_SchM_Enter_Com_TxIpduProtArea(APINAME)
#define Com_Get_SchM_Exit_Com_TxIpduProtArea(APINAME)

#define Com_Get_SchM_Enter_Com_TxGrpSigBuffer
#define Com_Get_SchM_Exit_Com_TxGrpSigBuffer
#else

#define Com_Get_SchM_Enter_Com_RxGateway
#define Com_Get_SchM_Exit_Com_RxGateway

#define Com_Get_SchM_Enter_Com_RxIPduProcess
#define Com_Get_SchM_Exit_Com_RxIPduProcess

#define Com_Get_SchM_Enter_Com_RxIndication
#define Com_Get_SchM_Exit_Com_RxIndication

#define Com_Get_SchM_Enter_Com_TxIPdu
#define Com_Get_SchM_Exit_Com_TxIPdu

#define Com_Get_SchM_Enter_Com_RxSigGwMcLockProtArea     SchM_Enter_Com_RxSigGwMcLockProtArea();
#define Com_Get_SchM_Exit_Com_RxSigGwMcLockProtArea      SchM_Exit_Com_RxSigGwMcLockProtArea();

#define Com_Get_SchM_Enter_Com_RxPduBuffer               SchM_Enter_Com_RxPduBuffer();
#define Com_Get_SchM_Exit_Com_RxPduBuffer                SchM_Exit_Com_RxPduBuffer();

#define Com_Get_SchM_Enter_Com_RxSigBuff(APINAME)        SchM_Enter_Com_RxSigBuff(APINAME);
#define Com_Get_SchM_Exit_Com_RxSigBuff(APINAME)         SchM_Exit_Com_RxSigBuff(APINAME);

#ifdef COM_RX_SIGNALGROUP_ARRAY
#define Com_Get_SchM_Enter_Com_RxSigGrpArrayBuff         SchM_Enter_Com_RxSigGrpArrayBuff();
#define Com_Get_SchM_Exit_Com_RxSigGrpArrayBuff          SchM_Exit_Com_RxSigGrpArrayBuff();
#endif

#define Com_Get_SchM_Enter_Com_RxGrpSigSecBuff           SchM_Enter_Com_RxGrpSigSecBuff();
#define Com_Get_SchM_Exit_Com_RxGrpSigSecBuff            SchM_Exit_Com_RxGrpSigSecBuff();

#define Com_Get_SchM_Enter_Com_RxSigToTicks              SchM_Enter_Com_RxSigToTicks();
#define Com_Get_SchM_Exit_Com_RxSigToTicks               SchM_Exit_Com_RxSigToTicks();

#define Com_Get_SchM_Enter_Com_RxSigGrpToTicks           SchM_Enter_Com_RxSigGrpToTicks();
#define Com_Get_SchM_Exit_Com_RxSigGrpToTicks            SchM_Exit_Com_RxSigGrpToTicks();

#define Com_Get_SchM_Enter_Com_RxSigDynBuff              SchM_Enter_Com_RxSigDynBuff();
#define Com_Get_SchM_Exit_Com_RxSigDynBuff               SchM_Exit_Com_RxSigDynBuff();

#define Com_Get_SchM_Enter_Com_TxIpduProtArea(APINAME)   SchM_Enter_Com_TxIpduProtArea(APINAME);
#define Com_Get_SchM_Exit_Com_TxIpduProtArea(APINAME)    SchM_Exit_Com_TxIpduProtArea(APINAME);

#define Com_Get_SchM_Enter_Com_TxGrpSigBuffer            SchM_Enter_Com_TxGrpSigBuffer();
#define Com_Get_SchM_Exit_Com_TxGrpSigBuffer             SchM_Exit_Com_TxGrpSigBuffer();

#endif

#ifdef COM_RxIPduTimeout

#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION

#define COM_GET_RXIPDU_TIMEOUT(ComRxPduId, RxIpduConstPtr)             Com_GetRxIPduTimeoutCalibration((PduIdType)(ComRxPduId))
#else

#define COM_GET_RXIPDU_TIMEOUT(ComRxPduId, RxIpduConstPtr)             ((RxIpduConstPtr)->Timeout_Fact)

#endif

#endif

#ifdef COM_TXPDU_TIMEOFFSET_VIA_CALIBRATION

#define COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, CurrentTxModePtr)        Com_GetTxIPduTimeOffsetCalibration((PduIdType)(ComTxPduId))
#else

#define COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, CurrentTxModePtr)        ((CurrentTxModePtr)->TimeOffsetFact)

#endif

#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        Com_GetTxIPduCyclePeriod((PduIdType)(ComTxPduId))
#elif (COM_COMMON_TX_PERIOD == STD_ON)

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        ((Com_ReducedPeriod_u16 == COM_ZERO)? \
                                                                       ((CurrentTxModePtr)->TimePeriodFact) : Com_ReducedPeriod_u16)
#else

#define COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, CurrentTxModePtr)        ((CurrentTxModePtr)->TimePeriodFact)

#endif

#ifdef COM_TXPDU_NUMOFREPETITION_VIA_CALIBRATION

#define COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, CurrentTxModePtr)   Com_GetTxIPduNumberOfRepetitionCalibration((PduIdType)(ComTxPduId))
#else

#define COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, CurrentTxModePtr)   ((CurrentTxModePtr)->NumOfRepetitions)

#endif

#endif
