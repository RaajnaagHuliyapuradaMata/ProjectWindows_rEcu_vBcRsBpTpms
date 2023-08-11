

#if !defined (WRAPNV_CFG_H)
# define WRAPNV_CFG_H

#include "fbl_def.h"

#define FBL_BHSENS_NVM

#define cMETADATA_APP 0
#define cMETADATA_FBL 1

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
#ifdef FBL_ENABLE_EEPMGR
#else
#define NV_ENABLE_ADDRESS_LOOKUP
#endif

#define kEepSizeProgReqFlag                  0x01u
#define kEepSizeResetResponseFlag            0x01u
#define kEepSizeApplValidity                 0x01u
#define kEepSizeValidityFlags                0x01u
#define kEepSizeSecAccessDelayFlag           0x01u
#define kEepSizeSecAccessInvalidCount        0x01u
#define kEepSizeDcmDslRxTesterSourceAddr     0x02u
#define kEepSizeMaxProgAttemptsCounter       0x01u
#define kEepSizeProgAttemptsCounter          0x01u
#define kEepSizeApplicationSignature         0x10u
#define kEepSizeFaultFlag                    0x01u
#define kEepSizeSecKey_AES_SYMMETRIC_KEY     0x20u
#define kEepSizeSecKey_AES_INITIAL_VECTOR    0x10u
#define kEepSizeEcuInstallationDate          0x06u
#define kEepSizeCustomerSpecificData         (kEepSizeMaxProgAttemptsCounter + kEepSizeProgAttemptsCounter + kEepSizeApplicationSignature + kEepSizeFaultFlag + kEepSizeSecKey_AES_SYMMETRIC_KEY + kEepSizeSecKey_AES_INITIAL_VECTOR + kEepSizeEcuInstallationDate)
#define kEepSizeProgCounter                  0x02u
#define kEepSizeProgAttempts                 0x02u
#define kEepSizeProgrammingAttempts          (kEepSizeProgCounter + kEepSizeProgAttempts)
#define kEepSizeFingerprint                  0x1Au
#define kEepSizeProgrammingDate              0x06u
#define kEepSizeTesterSerialNumber           0x14u

#ifdef FBL_ENABLE_EEPMGR
#else
#ifdef FBL_BHSENS_NVM
  #define kEepFblBaseAddress                   0x0  //RST info: for use with NVM
#else
  #define kEepFblBaseAddress                   0xFEDFA800uL //for use with RAM (FblStart() feature)
#endif
#define kEepStartAddress                     kEepFblBaseAddress
#define kEepAddressProgReqFlag               kEepStartAddress
#define kEepAddressResetResponseFlag         (kEepAddressProgReqFlag + kEepSizeProgReqFlag)
#define kEepAddressApplValidity              (kEepAddressResetResponseFlag + kEepSizeResetResponseFlag)
#define kEepAddressValidityFlags             (kEepAddressApplValidity + kEepSizeApplValidity)
#define kEepAddressSecAccessDelayFlag        (kEepAddressValidityFlags + kEepSizeValidityFlags)
#define kEepAddressSecAccessInvalidCount     (kEepAddressSecAccessDelayFlag + kEepSizeSecAccessDelayFlag)
#define kEepAddressDcmDslRxTesterSourceAddr  (kEepAddressSecAccessInvalidCount + kEepSizeSecAccessInvalidCount)
#define kEepAddressCustomerSpecificData      (kEepAddressDcmDslRxTesterSourceAddr + kEepSizeDcmDslRxTesterSourceAddr)
#define kEepAddressMaxProgAttemptsCounter    kEepAddressCustomerSpecificData
#define kEepAddressProgAttemptsCounter       (kEepAddressMaxProgAttemptsCounter + kEepSizeMaxProgAttemptsCounter)
#define kEepAddressApplicationSignature      (kEepAddressProgAttemptsCounter + kEepSizeProgAttemptsCounter)
#define kEepAddressFaultFlag                 (kEepAddressApplicationSignature + kEepSizeApplicationSignature)
#define kEepAddressSecKey_AES_SYMMETRIC_KEY  (kEepAddressFaultFlag + kEepSizeFaultFlag)
#define kEepAddressSecKey_AES_INITIAL_VECTOR (kEepAddressSecKey_AES_SYMMETRIC_KEY + kEepSizeSecKey_AES_SYMMETRIC_KEY)
#define kEepAddressEcuInstallationDate       (kEepAddressSecKey_AES_INITIAL_VECTOR + kEepSizeSecKey_AES_INITIAL_VECTOR)
#define kEepAddressProgrammingAttempts       (kEepAddressCustomerSpecificData + kEepSizeCustomerSpecificData)
#define kEepAddressProgCounter               kEepAddressProgrammingAttempts
#define kEepAddressProgAttempts              (kEepAddressProgCounter + kEepSizeProgCounter)
#define kEepAddressFingerprint               (kEepAddressProgrammingAttempts + kEepSizeProgrammingAttempts)
#define kEepAddressProgrammingDate           (kEepAddressFingerprint + kEepSizeFingerprint)
#define kEepAddressTesterSerialNumber        (kEepAddressProgrammingDate + kEepSizeProgrammingDate)
#define kEepEndAddress                       (kEepAddressTesterSerialNumber + kEepSizeTesterSerialNumber - 1)
#define kEepSizeOfEeprom                     (kEepEndAddress - kEepStartAddress + 1)

#define kNvNoOfStructs                       0x02u
#define kNvSizeStructs                       {kEepSizeCustomerSpecificData, kEepSizeProgrammingAttempts}
#endif

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
#define kEepMgrHandle_MaxProgAttemptsCounter 0
#define kEepMgrHandle_ProgAttemptsCounter    (kEepMgrHandle_MaxProgAttemptsCounter + 1)
#define kEepMgrHandle_ApplicationSignature   (kEepMgrHandle_ProgAttemptsCounter + 1)
#define kEepMgrHandle_FaultFlag              (kEepMgrHandle_ApplicationSignature + 1)
#define kEepMgrHandle_SecKey_AES_SYMMETRIC_KEY (kEepMgrHandle_FaultFlag + 1)
#define kEepMgrHandle_SecKey_AES_INITIAL_VECTOR (kEepMgrHandle_SecKey_AES_SYMMETRIC_KEY + 1)
#define kEepMgrHandle_EcuInstallationDate    (kEepMgrHandle_SecKey_AES_INITIAL_VECTOR + 1)
#define kEepMgrNrOfCustomerSpecificDataHdls  (kEepMgrHandle_EcuInstallationDate + 1)
#define kNvHandleStruct1                     0x01u
#define kEepMgrHandle_ProgrammingAttempts    (NV_MK_STRUCT_ID(kNvHandleStruct1, NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrNrOfCustomerSpecificDataHdls))
#define kEepMgrHandle_ProgCounter            0
#define kEepMgrHandle_ProgAttempts           (kEepMgrHandle_ProgCounter + 1)
#define kEepMgrNrOfProgrammingAttemptsHdls   (kEepMgrHandle_ProgAttempts + 1)
#define kEepMgrHandle_Fingerprint            (NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrNrOfProgrammingAttemptsHdls)
#define kEepMgrHandle_ProgrammingDate        (kEepMgrHandle_Fingerprint + 1)
#define kEepMgrHandle_TesterSerialNumber     (kEepMgrHandle_ProgrammingDate + 1)
#define kEepMgrLastHandle                    (kEepMgrHandle_TesterSerialNumber + 1 - 1)
#define kEepMgrNumberOfHandles               (kEepMgrLastHandle - kEepMgrFirstHandle + 1)
#ifdef FBL_ENABLE_EEPMGR

#define kNvNoOfStructs                       0x02u
#define kNvSizeStructs                       {kEepMgrNrOfCustomerSpecificDataHdls, kEepMgrNrOfProgrammingAttemptsHdls}
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgReqFlag(buf)        ((EepMgrRead(kEepMgrHandle_ProgReqFlag, buf, kEepSizeProgReqFlag) == kEepSizeProgReqFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((EepMgrWrite(kEepMgrHandle_ProgReqFlag, buf, kEepSizeProgReqFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadProgReqFlag(buf)        ((ApplFblNvReadProcessData(kEepAddressProgReqFlag, buf, kEepSizeProgReqFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((ApplFblNvWriteProcessData(kEepAddressProgReqFlag, buf, kEepSizeProgReqFlag) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgReqFlag(buf)        ((EepromDriver_RReadSync(buf, kEepSizeProgReqFlag, kEepAddressProgReqFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((EepromDriver_RWriteSync(buf, kEepSizeProgReqFlag, kEepAddressProgReqFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadResetResponseFlag(buf)  ((EepMgrRead(kEepMgrHandle_ResetResponseFlag, buf, kEepSizeResetResponseFlag) == kEepSizeResetResponseFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((EepMgrWrite(kEepMgrHandle_ResetResponseFlag, buf, kEepSizeResetResponseFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadResetResponseFlag(buf)  ((ApplFblNvReadProcessData(kEepAddressResetResponseFlag, buf, kEepSizeResetResponseFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((ApplFblNvWriteProcessData(kEepAddressResetResponseFlag, buf, kEepSizeResetResponseFlag) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadResetResponseFlag(buf)  ((EepromDriver_RReadSync(buf, kEepSizeResetResponseFlag, kEepAddressResetResponseFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((EepromDriver_RWriteSync(buf, kEepSizeResetResponseFlag, kEepAddressResetResponseFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadApplValidity(buf)       ((EepMgrRead(kEepMgrHandle_ApplValidity, buf, kEepSizeApplValidity) == kEepSizeApplValidity) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((EepMgrWrite(kEepMgrHandle_ApplValidity, buf, kEepSizeApplValidity) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadApplValidity(buf)       ((ApplFblNvReadProcessData(kEepAddressApplValidity, buf, kEepSizeApplValidity) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((ApplFblNvWriteProcessData(kEepAddressApplValidity, buf, kEepSizeApplValidity) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadApplValidity(buf)       ((EepromDriver_RReadSync(buf, kEepSizeApplValidity, kEepAddressApplValidity) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((EepromDriver_RWriteSync(buf, kEepSizeApplValidity, kEepAddressApplValidity) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadValidityFlags(buf)      ((EepMgrRead(kEepMgrHandle_ValidityFlags, buf, kEepSizeValidityFlags) == kEepSizeValidityFlags) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((EepMgrWrite(kEepMgrHandle_ValidityFlags, buf, kEepSizeValidityFlags) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadValidityFlags(buf)      ((ApplFblNvReadProcessData(kEepAddressValidityFlags, buf, kEepSizeValidityFlags) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((ApplFblNvWriteProcessData(kEepAddressValidityFlags, buf, kEepSizeValidityFlags) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadValidityFlags(buf)      ((EepromDriver_RReadSync(buf, kEepSizeValidityFlags, kEepAddressValidityFlags) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((EepromDriver_RWriteSync(buf, kEepSizeValidityFlags, kEepAddressValidityFlags) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSecAccessDelayFlag(buf) ((EepMgrRead(kEepMgrHandle_SecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kEepSizeSecAccessDelayFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessDelayFlag(buf) ((EepMgrWrite(kEepMgrHandle_SecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadSecAccessDelayFlag(buf)  ((ApplFblNvReadProcessData(kEepAddressSecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessDelayFlag(buf) ((ApplFblNvWriteProcessData(kEepAddressSecAccessDelayFlag, buf, kEepSizeSecAccessDelayFlag) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSecAccessDelayFlag(buf) ((EepromDriver_RReadSync(buf, kEepSizeSecAccessDelayFlag, kEepAddressSecAccessDelayFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessDelayFlag(buf) ((EepromDriver_RWriteSync(buf, kEepSizeSecAccessDelayFlag, kEepAddressSecAccessDelayFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSecAccessInvalidCount(buf) ((EepMgrRead(kEepMgrHandle_SecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kEepSizeSecAccessInvalidCount) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessInvalidCount(buf) ((EepMgrWrite(kEepMgrHandle_SecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadSecAccessInvalidCount(buf)  ((ApplFblNvReadProcessData(kEepAddressSecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessInvalidCount(buf) ((ApplFblNvWriteProcessData(kEepAddressSecAccessInvalidCount, buf, kEepSizeSecAccessInvalidCount) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSecAccessInvalidCount(buf) ((EepromDriver_RReadSync(buf, kEepSizeSecAccessInvalidCount, kEepAddressSecAccessInvalidCount) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecAccessInvalidCount(buf) ((EepromDriver_RWriteSync(buf, kEepSizeSecAccessInvalidCount, kEepAddressSecAccessInvalidCount) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadDcmDslRxTesterSourceAddr(buf) ((EepMgrRead(kEepMgrHandle_DcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kEepSizeDcmDslRxTesterSourceAddr) ? kFblOk : kFblFailed)
#define ApplFblNvWriteDcmDslRxTesterSourceAddr(buf) ((EepMgrWrite(kEepMgrHandle_DcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadDcmDslRxTesterSourceAddr(buf)  ((ApplFblNvReadProcessData(kEepAddressDcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteDcmDslRxTesterSourceAddr(buf) ((ApplFblNvWriteProcessData(kEepAddressDcmDslRxTesterSourceAddr, buf, kEepSizeDcmDslRxTesterSourceAddr) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadDcmDslRxTesterSourceAddr(buf) ((EepromDriver_RReadSync(buf, kEepSizeDcmDslRxTesterSourceAddr, kEepAddressDcmDslRxTesterSourceAddr) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteDcmDslRxTesterSourceAddr(buf) ((EepromDriver_RWriteSync(buf, kEepSizeDcmDslRxTesterSourceAddr, kEepAddressDcmDslRxTesterSourceAddr) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadMaxProgAttemptsCounter(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_MaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kEepSizeMaxProgAttemptsCounter) ? kFblOk : kFblFailed)
#define ApplFblNvWriteMaxProgAttemptsCounter(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_MaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadMaxProgAttemptsCounter(buf)  ((ApplFblNvReadProcessData(kEepAddressMaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteMaxProgAttemptsCounter(buf) ((ApplFblNvWriteProcessData(kEepAddressMaxProgAttemptsCounter, buf, kEepSizeMaxProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadMaxProgAttemptsCounter(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeMaxProgAttemptsCounter, kEepAddressMaxProgAttemptsCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteMaxProgAttemptsCounter(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeMaxProgAttemptsCounter, kEepAddressMaxProgAttemptsCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgAttemptsCounter(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_ProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kEepSizeProgAttemptsCounter) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttemptsCounter(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_ProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadProgAttemptsCounter(buf)  ((ApplFblNvReadProcessData(kEepAddressProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttemptsCounter(buf) ((ApplFblNvWriteProcessData(kEepAddressProgAttemptsCounter, buf, kEepSizeProgAttemptsCounter) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgAttemptsCounter(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeProgAttemptsCounter, kEepAddressProgAttemptsCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttemptsCounter(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeProgAttemptsCounter, kEepAddressProgAttemptsCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadApplicationSignature(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_ApplicationSignature, buf, kEepSizeApplicationSignature) == kEepSizeApplicationSignature) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplicationSignature(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_ApplicationSignature, buf, kEepSizeApplicationSignature) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadApplicationSignature(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressApplicationSignature + (idx * kEepSizeApplicationSignature), buf, kEepSizeApplicationSignature) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplicationSignature(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressApplicationSignature + (idx * kEepSizeApplicationSignature), buf, kEepSizeApplicationSignature) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadApplicationSignature(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeApplicationSignature, kEepAddressApplicationSignature) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplicationSignature(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeApplicationSignature, kEepAddressApplicationSignature) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadFaultFlag(idx, buf)     ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_FaultFlag, buf, kEepSizeFaultFlag) == kEepSizeFaultFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFaultFlag(idx, buf)    ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_FaultFlag, buf, kEepSizeFaultFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadFaultFlag(buf)          ((ApplFblNvReadProcessData(kEepAddressFaultFlag, buf, kEepSizeFaultFlag) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFaultFlag(buf)         ((ApplFblNvWriteProcessData(kEepAddressFaultFlag, buf, kEepSizeFaultFlag) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadFaultFlag(idx, buf)     ((EepromDriver_RReadSync(buf, kEepSizeFaultFlag, kEepAddressFaultFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFaultFlag(idx, buf)    ((EepromDriver_RWriteSync(buf, kEepSizeFaultFlag, kEepAddressFaultFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSecKey_AES_SYMMETRIC_KEY(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_SecKey_AES_SYMMETRIC_KEY, buf, kEepSizeSecKey_AES_SYMMETRIC_KEY) == kEepSizeSecKey_AES_SYMMETRIC_KEY) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_SYMMETRIC_KEY(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_SecKey_AES_SYMMETRIC_KEY, buf, kEepSizeSecKey_AES_SYMMETRIC_KEY) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadSecKey_AES_SYMMETRIC_KEY(buf)     ((ApplFblNvReadProcessData(kEepAddressSecKey_AES_SYMMETRIC_KEY, buf, kEepSizeSecKey_AES_SYMMETRIC_KEY) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_SYMMETRIC_KEY(buf)    ((ApplFblNvWriteProcessData(kEepAddressSecKey_AES_SYMMETRIC_KEY, buf, kEepSizeSecKey_AES_SYMMETRIC_KEY) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSecKey_AES_SYMMETRIC_KEY(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeSecKey_AES_SYMMETRIC_KEY, kEepAddressSecKey_AES_SYMMETRIC_KEY) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_SYMMETRIC_KEY(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeSecKey_AES_SYMMETRIC_KEY, kEepAddressSecKey_AES_SYMMETRIC_KEY) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSecKey_AES_INITIAL_VECTOR(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_SecKey_AES_INITIAL_VECTOR, buf, kEepSizeSecKey_AES_INITIAL_VECTOR) == kEepSizeSecKey_AES_INITIAL_VECTOR) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_INITIAL_VECTOR(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_SecKey_AES_INITIAL_VECTOR, buf, kEepSizeSecKey_AES_INITIAL_VECTOR) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadSecKey_AES_INITIAL_VECTOR(buf)     ((ApplFblNvReadProcessData(kEepAddressSecKey_AES_INITIAL_VECTOR, buf, kEepSizeSecKey_AES_INITIAL_VECTOR) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_INITIAL_VECTOR(buf)    ((ApplFblNvWriteProcessData(kEepAddressSecKey_AES_INITIAL_VECTOR, buf, kEepSizeSecKey_AES_INITIAL_VECTOR) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSecKey_AES_INITIAL_VECTOR(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeSecKey_AES_INITIAL_VECTOR, kEepAddressSecKey_AES_INITIAL_VECTOR) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSecKey_AES_INITIAL_VECTOR(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeSecKey_AES_INITIAL_VECTOR, kEepAddressSecKey_AES_INITIAL_VECTOR) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadEcuInstallationDate(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_EcuInstallationDate, buf, kEepSizeEcuInstallationDate) == kEepSizeEcuInstallationDate) ? kFblOk : kFblFailed)
#define ApplFblNvWriteEcuInstallationDate(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_CustomerSpecificData) + kEepMgrHandle_EcuInstallationDate, buf, kEepSizeEcuInstallationDate) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadEcuInstallationDate(buf)     ((ApplFblNvReadProcessData(kEepAddressEcuInstallationDate, buf, kEepSizeEcuInstallationDate) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteEcuInstallationDate(buf)    ((ApplFblNvWriteProcessData(kEepAddressEcuInstallationDate, buf, kEepSizeEcuInstallationDate) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadEcuInstallationDate(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeEcuInstallationDate, kEepAddressEcuInstallationDate) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteEcuInstallationDate(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeEcuInstallationDate, kEepAddressEcuInstallationDate) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgCounter(idx, buf)   ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrHandle_ProgCounter, buf, kEepSizeProgCounter) == kEepSizeProgCounter) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrHandle_ProgCounter, buf, kEepSizeProgCounter) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadProgCounter(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressProgCounter + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgCounter) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressProgCounter + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgCounter) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgCounter(idx, buf)   ((EepromDriver_RReadSync(buf, kEepSizeProgCounter, kEepAddressProgCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((EepromDriver_RWriteSync(buf, kEepSizeProgCounter, kEepAddressProgCounter) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgAttempts(idx, buf)  ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrHandle_ProgAttempts, buf, kEepSizeProgAttempts) == kEepSizeProgAttempts) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProgrammingAttempts) + kEepMgrHandle_ProgAttempts, buf, kEepSizeProgAttempts) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadProgAttempts(idx, buf)   ((ApplFblNvReadMetaData(0, kEepAddressProgAttempts + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgAttempts) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf)  ((ApplFblNvWriteMetaData(0, kEepAddressProgAttempts + (idx * kEepSizeProgrammingAttempts), buf, kEepSizeProgAttempts) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgAttempts(idx, buf)  ((EepromDriver_RReadSync(buf, kEepSizeProgAttempts, kEepAddressProgAttempts) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeProgAttempts, kEepAddressProgAttempts) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadFingerprint(buf)        ((EepMgrRead(kEepMgrHandle_Fingerprint, buf, kEepSizeFingerprint) == kEepSizeFingerprint) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFingerprint(buf)       ((EepMgrWrite(kEepMgrHandle_Fingerprint, buf, kEepSizeFingerprint) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadFingerprint(buf)       ((ApplFblNvReadProcessData(kEepAddressFingerprint, buf, kEepSizeFingerprint) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFingerprint(buf)      ((ApplFblNvWriteProcessData(kEepAddressFingerprint, buf, kEepSizeFingerprint) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadFingerprint(buf)        ((EepromDriver_RReadSync(buf, kEepSizeFingerprint, kEepAddressFingerprint) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteFingerprint(buf)       ((EepromDriver_RWriteSync(buf, kEepSizeFingerprint, kEepAddressFingerprint) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgrammingDate(buf)    ((EepMgrRead(kEepMgrHandle_ProgrammingDate, buf, kEepSizeProgrammingDate) == kEepSizeProgrammingDate) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(buf)   ((EepMgrWrite(kEepMgrHandle_ProgrammingDate, buf, kEepSizeProgrammingDate) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadProgrammingDate(buf)       ((ApplFblNvReadProcessData(kEepAddressProgrammingDate, buf, kEepSizeProgrammingDate) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(buf)      ((ApplFblNvWriteProcessData(kEepAddressProgrammingDate, buf, kEepSizeProgrammingDate) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgrammingDate(buf)    ((EepromDriver_RReadSync(buf, kEepSizeProgrammingDate, kEepAddressProgrammingDate) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(buf)   ((EepromDriver_RWriteSync(buf, kEepSizeProgrammingDate, kEepAddressProgrammingDate) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadTesterSerialNumber(buf) ((EepMgrRead(kEepMgrHandle_TesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kEepSizeTesterSerialNumber) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(buf) ((EepMgrWrite(kEepMgrHandle_TesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kEepMgrOk) ? kFblOk : kFblFailed)
#elif defined FBL_BHSENS_NVM
#define ApplFblNvReadTesterSerialNumber(buf)       ((ApplFblNvReadProcessData(kEepAddressTesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kFblOk) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(buf)      ((ApplFblNvWriteProcessData(kEepAddressTesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kFblOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadTesterSerialNumber(buf) ((EepromDriver_RReadSync(buf, kEepSizeTesterSerialNumber, kEepAddressTesterSerialNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(buf) ((EepromDriver_RWriteSync(buf, kEepSizeTesterSerialNumber, kEepAddressTesterSerialNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#else
#define ApplFblIsValidEepAddress(i)          ((i >= kEepStartAddress) && (i <= kEepEndAddress))
#endif
#define ApplFblIsValidEepMgrHandle(i)        ((i >= kEepMgrFirstHandle) && (i <= kEepMgrLastHandle))

extern tFblResult ApplFblNvInit( void );

extern tFblResult ApplFblNvWriteProcessData( vuint16 blockOffset,
                                             const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer,
                                             vuint16 length );
extern tFblResult ApplFblNvReadProcessData( vuint16 blockOffset,
                                            V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer,
                                            vuint16 length );

extern tFblResult ApplFblNvWriteMetaData( vuintx index,
                                          vuint16 blockOffset,
                                          const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer,
                                          vuint16 length );
extern tFblResult ApplFblNvReadMetaData( vuintx index,
                                         vuint16 blockOffset,
                                         V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer,
                                         vuint16 length );

#endif

