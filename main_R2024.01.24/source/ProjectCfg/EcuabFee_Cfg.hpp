

#ifndef ECUABFEE_CFG_H_PUBLIC
#define ECUABFEE_CFG_H_PUBLIC

#ifndef FEE_USE_DUMMY_FUNCTIONS
#define FEE_USE_DUMMY_FUNCTIONS STD_OFF
#endif
#ifndef FEE_USE_DUMMY_STATEMENT
#define FEE_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef FEE_DUMMY_STATEMENT
#define FEE_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef FEE_DUMMY_STATEMENT_CONST
#define FEE_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef FEE_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define FEE_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON
#endif
#ifndef FEE_ATOMIC_VARIABLE_ACCESS
#define FEE_ATOMIC_VARIABLE_ACCESS 32U
#endif
#ifndef FEE_PROCESSOR_CANOEEMU
#define FEE_PROCESSOR_CANOEEMU
#endif
#ifndef FEE_COMP_
#define FEE_COMP_
#endif
#ifndef FEE_GEN_GENERATOR_MSR
#define FEE_GEN_GENERATOR_MSR
#endif
#ifndef FEE_CPUTYPE_BITORDER_LSB2MSB
#define FEE_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef FEE_CONFIGURATION_VARIANT_PRECOMPILE
#define FEE_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef FEE_CONFIGURATION_VARIANT_LINKTIME
#define FEE_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef FEE_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define FEE_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef FEE_CONFIGURATION_VARIANT
#define FEE_CONFIGURATION_VARIANT FEE_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef FEE_POSTBUILD_VARIANT_SUPPORT
#define FEE_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define ECUABFEE_CFG_MAJOR_VERSION    (2u)
#define ECUABFEE_CFG_MINOR_VERSION    (0u)

#define ECUABFEE_DEV_ERROR_DETECT	(STD_OFF)
#define ECUABFEE_DEV_ERROR_REPORT	(STD_OFF)

#define ECUABFEE_VERSION_INFO_API STD_OFF

#define FeeConf_FeeBlockConfiguration_FeeConfigBlock                           2U
#define FeeConf_FeeBlockConfiguration_FeeBlock_FBL_Data                        4U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT01              6U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT02              8U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT03              10U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT04              12U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT05              14U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT06              16U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT07              18U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT08              20U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT09              22U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_CAT10              24U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdDemGenericNvData       26U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc0              28U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc1              30U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc2              32U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc3              34U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc4              36U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc5              38U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc6              40U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc7              42U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc8              44U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvMemLoc9              46U
#define FeeConf_FeeBlockConfiguration_FeeBlock_DemNvm_IdEvStatusByte           48U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_ECUM_CFG_NVM_BLOCK 50U
#define FeeConf_FeeBlockConfiguration_FeeBlock_BSW_Data                        52U

typedef uint32 EcuabFee_AddressType;

#ifdef ECUABFEE_IMPLEMENTATION_SOURCE

# include "Fls.hpp"

#define ECUABFEE_LAYER_ONE_INDEX             (0x00U)
#define ECUABFEE_LAYER_TWO_INDEX             (0x01U)
#define ECUABFEE_LAYER_THREE_INDEX           (0x02U)

#define ECUABFEE_NUMBER_OF_FLS_DEVICES       (1U)

#define ECUABFEE_FLS_POLLING_MODE            (STD_OFF)
#define ECUABFEE_CORRECT_SINGLE_BIT_FLIPS    (STD_OFF)
#define ECUABFEE_MANAGEMENT_SIZE             (1U)
#define ECUABFEE_MAX_BLOCKS_PER_PARTITION    (13U)
#define ECUABFEE_NUMBER_OF_PARTITIONS        (3U)
#define ECUABFEE_NUMBER_OF_BLOCKS            (26U)
#define ECUABFEE_MAX_WRITE_ALIGNMENT         (8U)
#define ECUABFEE_MAX_READ_SIZE               (24U)

#define ECUABFEE_STATIC_PATTERN              (0xAAU)

#define ECUABFEE_NVM_POLLING_MODE            (STD_OFF)

typedef P2VAR(uint8, AUTOMATIC, ECUABFEE_APPL_DATA) EcuabFee_DataPtr;
typedef P2CONST(uint8, AUTOMATIC, ECUABFEE_APPL_DATA) EcuabFee_ConstDataPtr;

typedef P2FUNC(Std_ReturnType, ECUABFEE_PRIVATE_CODE, EcuabFee_ReadPtrType)(Fls_AddressType FlsAddress, EcuabFee_DataPtr TargetAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, ECUABFEE_PRIVATE_CODE, EcuabFee_WritePtrType)(Fls_AddressType FlsAddress, EcuabFee_ConstDataPtr SourceAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, ECUABFEE_PRIVATE_CODE, EcuabFee_ComparePtrType)(Fls_AddressType FlsAddress, EcuabFee_ConstDataPtr DataBufferPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, ECUABFEE_PRIVATE_CODE, EcuabFee_ErasePtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, ECUABFEE_PRIVATE_CODE, EcuabFee_BlankCheckPtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(MemIf_StatusType, ECUABFEE_PRIVATE_CODE, EcuabFee_GetStatusPtrType)(void);
typedef P2FUNC(MemIf_JobResultType, ECUABFEE_PRIVATE_CODE, EcuabFee_GetJobResultPtrType)(void);

typedef struct{
   EcuabFee_ReadPtrType Read;
   EcuabFee_WritePtrType Write;
   EcuabFee_ComparePtrType Compare;
   EcuabFee_ErasePtrType Erase;
   EcuabFee_BlankCheckPtrType BlankCheck;
   EcuabFee_GetStatusPtrType GetStatus;
   EcuabFee_GetJobResultPtrType GetJobResult;
}EcuabFee_FlsApiType;

typedef P2CONST(EcuabFee_FlsApiType, AUTOMATIC, ECUABFEE_APPL_DATA) EcuabFee_FlsApiPtrType;

typedef struct{
    EcuabFee_AddressType PartitionStartAddress;
   uint16 PartitionAddressAlignment;
   uint16 PartitionWriteAlignment;
   uint16 PartitionReadAlignment;
   uint16 FlsDeviceIndex;
    EcuabFee_FlsApiPtrType FlsApiPtr;
   uint8 FlsEraseValue;
   boolean BlankCheckApiEnabled;
   uint16 BlockNumberList[ECUABFEE_MAX_BLOCKS_PER_PARTITION];
}EcuabFee_PartitionConfigType;

typedef struct{
    EcuabFee_AddressType BlockStartAddress;
   uint16 DataLength;
   uint8 NumberOfInstances;
   uint8 NumberOfDatasets;
   boolean IsImmediateData;
   boolean HasVerificationEnabled;
}EcuabFee_BlockConfigType;

typedef P2FUNC(void, ECUABFEE_NVM_CODE, EcuabFee_CbkJobEndNotificationType)(void);
typedef P2FUNC(void, ECUABFEE_NVM_CODE, EcuabFee_CbkJobErrorNotificationType)(void);

#define ECUABFEE_START_SEC_CONST_8BIT
#include "MemMap.hpp"

extern CONST(uint8, ECUABFEE_PRIVATE_CONST) EcuabFee_DatasetSelectionBits;

#define ECUABFEE_STOP_SEC_CONST_8BIT
#include "MemMap.hpp"

#define ECUABFEE_START_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"

extern CONST(EcuabFee_PartitionConfigType, ECUABFEE_PRIVATE_CONST) EcuabFee_PartitionConfigList[ECUABFEE_NUMBER_OF_PARTITIONS];
extern CONST(EcuabFee_BlockConfigType, ECUABFEE_PRIVATE_CONST) EcuabFee_BlockConfigList[ECUABFEE_NUMBER_OF_BLOCKS];
extern CONST(EcuabFee_FlsApiType, ECUABFEE_PRIVATE_CONST) EcuabFee_FlsApi0;

extern CONST(EcuabFee_CbkJobEndNotificationType, ECUABFEE_PRIVATE_CONST) EcuabFee_CbkJobEndNotification;
extern CONST(EcuabFee_CbkJobErrorNotificationType, ECUABFEE_PRIVATE_CONST) EcuabFee_CbkJobErrorNotification;

#define ECUABFEE_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"

#endif

#endif

