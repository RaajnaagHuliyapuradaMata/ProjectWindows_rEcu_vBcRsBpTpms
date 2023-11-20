#if !defined (WRAPNV_CFG_H)
#define WRAPNV_CFG_H

#include "fbl_def.hpp"

#define FBL_BHSENS_NVM

#ifndef WRAPNV_USE_DUMMY_STATEMENT
#define WRAPNV_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef WRAPNV_DUMMY_STATEMENT
#define WRAPNV_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef WRAPNV_DUMMY_STATEMENT_CONST
#define WRAPNV_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef WRAPNV_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define WRAPNV_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF
#endif
#ifndef WRAPNV_ATOMIC_VARIABLE_ACCESS
#define WRAPNV_ATOMIC_VARIABLE_ACCESS 32u
#endif
#ifndef WRAPNV_PROCESSOR_RH850_1013
#define WRAPNV_PROCESSOR_RH850_1013
#endif
#ifndef WRAPNV_COMP_GREENHILLS
#define WRAPNV_COMP_GREENHILLS
#endif
#ifndef WRAPNV_GEN_GENERATOR_MSR
#define WRAPNV_GEN_GENERATOR_MSR
#endif
#ifndef WRAPNV_CPUTYPE_BITORDER_LSB2MSB
#define WRAPNV_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef WRAPNV_CONFIGURATION_VARIANT_PRECOMPILE
#define WRAPNV_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef WRAPNV_CONFIGURATION_VARIANT_LINKTIME
#define WRAPNV_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef WRAPNV_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define WRAPNV_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef WRAPNV_CONFIGURATION_VARIANT
#define WRAPNV_CONFIGURATION_VARIANT WRAPNV_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef WRAPNV_POSTBUILD_VARIANT_SUPPORT
#define WRAPNV_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define WRAPNV_MODULE_NVM                STD_OFF
#define WRAPNV_MODULE_FEE                STD_OFF
#define WRAPNV_MODULE_FLS                STD_OFF
#define WRAPNV_MODULE_EA                 STD_OFF
#define WRAPNV_MODULE_EEP                STD_OFF
#define WRAPNV_USECASE_DRVEEP
#define FBL_DISABLE_EEPMGR
#define NV_ENABLE_ADDRESS_LOOKUP
#define kEepSizeProgReqFlag                  0x01u
#define kEepSizeResetResponseFlag            0x01u
#define kEepSizeApplValidity                 0x01u
#define kEepSizeValidityFlags                0x01u
#define kEepSizeSecAccessDelayFlag           0x01u
#define kEepSizeSecAccessInvalidCount        0x01u
#define kEepSizeDcmDslRxTesterSourceAddr     0x02u
#define kEepSizeSecKey_UDSBOOTKEY            0x10u
#define kEepSizeSecKey_UDSMSGKEY             0x10u
#define kEepSizeSecKey_UDSAPPKEY             0x10u
#define kEepSizeMaxProgAttemptsCounter       0x01u
#define kEepSizeProgAttemptsCounter          0x01u
#define kEepSizeApplicationSignature         0x10u
#define kEepSizeFaultFlag                    0x01u
#define kEepSizeCustomerSpecificData         (kEepSizeSecKey_UDSBOOTKEY + kEepSizeSecKey_UDSMSGKEY + kEepSizeSecKey_UDSAPPKEY + kEepSizeMaxProgAttemptsCounter + kEepSizeProgAttemptsCounter + kEepSizeApplicationSignature + kEepSizeFaultFlag)
#define kEepSizeProgCounter                  0x02u
#define kEepSizeProgAttempts                 0x02u
#define kEepSizeProgrammingAttempts          (kEepSizeProgCounter + kEepSizeProgAttempts)
#define kEepSizeProgrammingDate              0x03u
#define kEepSizeTesterSerialNumber           0x14u
#define kEepSizeFingerprint                  (kEepSizeProgrammingDate + kEepSizeTesterSerialNumber)

#define kEepFblBaseAddress                   0x0
#define kEepStartAddress                     kEepFblBaseAddress
#define kEepAddressProgReqFlag               kEepStartAddress
#define kEepAddressResetResponseFlag         (kEepAddressProgReqFlag + kEepSizeProgReqFlag)
#define kEepAddressApplValidity              (kEepAddressResetResponseFlag + kEepSizeResetResponseFlag)
#define kEepAddressValidityFlags             (kEepAddressApplValidity + kEepSizeApplValidity)
#define kEepAddressSecAccessDelayFlag        (kEepAddressValidityFlags + kEepSizeValidityFlags)
#define kEepAddressSecAccessInvalidCount     (kEepAddressSecAccessDelayFlag + kEepSizeSecAccessDelayFlag)
#define kEepAddressDcmDslRxTesterSourceAddr  (kEepAddressSecAccessInvalidCount + kEepSizeSecAccessInvalidCount)
#define kEepAddressCustomerSpecificData      (kEepAddressDcmDslRxTesterSourceAddr + kEepSizeDcmDslRxTesterSourceAddr)
#define kEepAddressSecKey_UDSBOOTKEY         kEepAddressCustomerSpecificData
#define kEepAddressSecKey_UDSMSGKEY          (kEepAddressSecKey_UDSBOOTKEY + kEepSizeSecKey_UDSBOOTKEY)
#define kEepAddressSecKey_UDSAPPKEY          (kEepAddressSecKey_UDSMSGKEY + kEepSizeSecKey_UDSMSGKEY)
#define kEepAddressMaxProgAttemptsCounter    (kEepAddressSecKey_UDSAPPKEY + kEepSizeSecKey_UDSAPPKEY)
#define kEepAddressProgAttemptsCounter       (kEepAddressMaxProgAttemptsCounter + kEepSizeMaxProgAttemptsCounter)
#define kEepAddressApplicationSignature      (kEepAddressProgAttemptsCounter + kEepSizeProgAttemptsCounter)
#define kEepAddressFaultFlag                 (kEepAddressApplicationSignature + kEepSizeApplicationSignature)
#define kEepAddressProgrammingAttempts       (kEepAddressCustomerSpecificData + kEepSizeCustomerSpecificData)
#define kEepAddressProgCounter               kEepAddressProgrammingAttempts
#define kEepAddressProgAttempts              (kEepAddressProgCounter + kEepSizeProgCounter)
#define kEepAddressFingerprint               (kEepAddressProgrammingAttempts + kEepSizeProgrammingAttempts)
#define kEepAddressProgrammingDate           kEepAddressFingerprint
#define kEepAddressTesterSerialNumber        (kEepAddressProgrammingDate + kEepSizeProgrammingDate)
#define kEepEndAddress                       (kEepAddressFingerprint + kEepSizeFingerprint * 2 - 1)
#define kEepSizeOfEeprom                     (kEepEndAddress - kEepStartAddress + 1)
#define kNvNoOfStructs                       0x03u
#define kNvSizeStructs                       {kEepSizeCustomerSpecificData, kEepSizeProgrammingAttempts, kEepSizeFingerprint}

#define kEepMgrFirstHandle                   1
#define kEepMgrHandle_ProgReqFlag            kEepMgrFirstHandle
#define kEepMgrHandle_ResetResponseFlag      (kEepMgrHandle_ProgReqFlag + 1)
#define kEepMgrHandle_ApplValidity           (kEepMgrHandle_ResetResponseFlag + 1)
#define kEepMgrHandle_ValidityFlags          (kEepMgrHandle_ApplValidity + 1)
#define kEepMgrHandle_SecAccessDelayFlag     (kEepMgrHandle_ValidityFlags + 1)
#define kEepMgrHandle_SecAccessInvalidCount  (kEepMgrHandle_SecAccessDelayFlag + 1)
#define kEepMgrHandle_DcmDslRxTesterSourceAddr (kEepMgrHandle_SecAccessInvalidCount + 1)
#define kNvHandleStruct0                     0x00u
#define kEepMgrHandle_CustomerSpecificData   (NV_MK_STRUCT_ID(kNvHandleStruct0, kEepMgrHandle_DcmDslRxTesterSourceAddr + 1))
#define kEepMgrHandle_SecKey_UDSBOOTKEY      0
#define kEepMgrHandle_SecKey_UDSMSGKEY       (kEepMgrHandle_SecKey_UDSBOOTKEY + 1)
#define kEepMgrHandle_SecKey_UDSAPPKEY       (kEepMgrHandle_SecKey_UDSMSGKEY + 1)
#define kEepMgrHandle_MaxProgAttemptsCounter (kEepMgrHandle_SecKey_UDSAPPKEY + 1)
#define kEepMgrHandle_ProgAttemptsCounter    (kEepMgrHandle_MaxProgAttemptsCounter + 1)
#define kEepMgrHandle_ApplicationSignature   (kEepMgrHandle_ProgAttemptsCounter + 1)
#define kEepMgrHandle_FaultFlag              (kEepMgrHandle_ApplicationSignature + 1)
#define kEepMgrNrOfCustomerSpecificDataHdls  (kEepMgrHandle_FaultFlag + 1)
#define kNvHandleStruct1                     0x01u
#define kEepMgrHandle_ProgrammingAttempts    (NV_MK_STRUCT_ID(kNvHandleStruct1, NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrNrOfCustomerSpecificDataHdls))
#define kEepMgrHandle_ProgCounter            0
#define kEepMgrHandle_ProgAttempts           (kEepMgrHandle_ProgCounter + 1)
#define kEepMgrNrOfProgrammingAttemptsHdls   (kEepMgrHandle_ProgAttempts + 1)
#define kNvHandleStruct2                     0x02u
#define kEepMgrHandle_Fingerprint            (NV_MK_STRUCT_ID(kNvHandleStruct2, NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrNrOfProgrammingAttemptsHdls))
#define kEepMgrHandle_ProgrammingDate        0
#define kEepMgrHandle_TesterSerialNumber     (kEepMgrHandle_ProgrammingDate + 1)
#define kEepMgrNrOfFingerprintHdls           (kEepMgrHandle_TesterSerialNumber + 1)
#define kEepMgrLastHandle                    (NV_GET_STRUCT_ID(kEepMgrHandle_Fingerprint) + kEepMgrNrOfFingerprintHdls * 2 - 1)
#define kEepMgrNumberOfHandles               (kEepMgrLastHandle - kEepMgrFirstHandle + 1)
#define ApplFblNvReadProgReqFlag(buf)        ((ApplFblNvReadProcessData(kEepAddressProgReqFlag, buf, kEepSizeProgReqFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((ApplFblNvWriteProcessData(kEepAddressProgReqFlag, buf, kEepSizeProgReqFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadResetResponseFlag(buf)  ((ApplFblNvReadProcessData(kEepAddressResetResponseFlag, buf, kEepSizeResetResponseFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((ApplFblNvWriteProcessData(kEepAddressResetResponseFlag, buf, kEepSizeResetResponseFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadApplValidity(buf)       ((ApplFblNvReadProcessData(kEepAddressApplValidity, buf, kEepSizeApplValidity) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((ApplFblNvWriteProcessData(kEepAddressApplValidity, buf, kEepSizeApplValidity) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadValidityFlags(buf)      ((ApplFblNvReadProcessData(kEepAddressValidityFlags, buf, kEepSizeValidityFlags) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((ApplFblNvWriteProcessData(kEepAddressValidityFlags, buf, kEepSizeValidityFlags) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadSecAccessDelayFlag(buf)  ((ApplFblNvReadProcessData(kEepAddressSecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessDelayFlag(buf) ((ApplFblNvWriteProcessData(kEepAddressSecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadSecAccessInvalidCount(buf)  ((ApplFblNvReadProcessData(kEepAddressSecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessInvalidCount(buf) ((ApplFblNvWriteProcessData(kEepAddressSecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadDcmDslRxTesterSourceAddr(buf)  ((ApplFblNvReadProcessData(kEepAddressDcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteDcmDslRxTesterSourceAddr(buf) ((ApplFblNvWriteProcessData(kEepAddressDcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadMaxProgAttemptsCounter(buf)  ((ApplFblNvReadProcessData(kEepAddressMaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteMaxProgAttemptsCounter(buf) ((ApplFblNvWriteProcessData(kEepAddressMaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadProgAttemptsCounter(buf)  ((ApplFblNvReadProcessData(kEepAddressProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttemptsCounter(buf) ((ApplFblNvWriteProcessData(kEepAddressProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadFaultFlag(buf)          ((ApplFblNvReadProcessData(kEepAddressFaultFlag, buf, kEepSizeFaultFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFaultFlag(buf)         ((ApplFblNvWriteProcessData(kEepAddressFaultFlag, buf, kEepSizeFaultFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadProgCounter(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressProgCounter + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressProgCounter + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadProgAttempts(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressProgAttempts + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgAttempts) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressProgAttempts + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgAttempts) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadSecKey_UDSBOOTKEY(buf)    ((ApplFblNvReadProcessData(kEepAddressSecKey_UDSBOOTKEY, buf, kEepSizeSecKey_UDSBOOTKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_UDSBOOTKEY(buf)   ((ApplFblNvWriteProcessData(kEepAddressSecKey_UDSBOOTKEY, buf, kEepSizeSecKey_UDSBOOTKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadSecKey_UDSMSGKEY(buf)     ((ApplFblNvReadProcessData(kEepAddressSecKey_UDSMSGKEY, buf, kEepSizeSecKey_UDSMSGKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_UDSMSGKEY(buf)    ((ApplFblNvWriteProcessData(kEepAddressSecKey_UDSMSGKEY, buf, kEepSizeSecKey_UDSMSGKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadSecKey_UDSAPPKEY(buf)     ((ApplFblNvReadProcessData(kEepAddressSecKey_UDSAPPKEY, buf, kEepSizeSecKey_UDSAPPKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_UDSAPPKEY(buf)    ((ApplFblNvWriteProcessData(kEepAddressSecKey_UDSAPPKEY, buf, kEepSizeSecKey_UDSAPPKEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadApplicationSignature(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressApplicationSignature + (idx * kEepSizeApplicationSignature), buf, kEepSizeApplicationSignature) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplicationSignature(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressApplicationSignature + (idx * kEepSizeApplicationSignature), buf, kEepSizeApplicationSignature) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadProgrammingDate(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressProgrammingDate + (idx * kEepSizeProgrammingDate), buf, kEepSizeProgrammingDate) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressProgrammingDate + (idx * kEepSizeProgrammingDate), buf, kEepSizeProgrammingDate) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvReadTesterSerialNumber(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressTesterSerialNumber + (idx * kEepSizeTesterSerialNumber), buf, kEepSizeTesterSerialNumber) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressTesterSerialNumber + (idx * kEepSizeTesterSerialNumber), buf, kEepSizeTesterSerialNumber) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblIsValidEepAddress(i)          ((i >= kEepStartAddress) && (i <= kEepEndAddress))
#define ApplFblIsValidEepMgrHandle(i)        ((i >= kEepMgrFirstHandle) && (i <= kEepMgrLastHandle))

extern tFblResult ApplFblNvInit(void);

extern tFblResult ApplFblNvWriteProcessData( vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );
extern tFblResult ApplFblNvReadProcessData( vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );

extern tFblResult ApplFblNvWriteMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );
extern tFblResult ApplFblNvReadMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );

#endif
