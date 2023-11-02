#ifndef FEE_30_SMALLSECTOR_CFG_H_PUBLIC
#define FEE_30_SMALLSECTOR_CFG_H_PUBLIC

#define FEE_USE_DUMMY_FUNCTIONS STD_OFF
#define FEE_USE_DUMMY_STATEMENT STD_ON
#define FEE_DUMMY_STATEMENT(v) (v)=(v)
#define FEE_DUMMY_STATEMENT_CONST(v) (void)(v)
#define FEE_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON
#define FEE_ATOMIC_VARIABLE_ACCESS 32U
#define FEE_PROCESSOR_CANOEEMU
#define FEE_COMP_
#define FEE_GEN_GENERATOR_MSR
#define FEE_CPUTYPE_BITORDER_LSB2MSB
#define FEE_CONFIGURATION_VARIANT_PRECOMPILE 1
#define FEE_CONFIGURATION_VARIANT_LINKTIME 2
#define FEE_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#define FEE_CONFIGURATION_VARIANT FEE_CONFIGURATION_VARIANT_PRECOMPILE
#define FEE_POSTBUILD_VARIANT_SUPPORT STD_OFF
#define FEE_30_SMALLSECTOR_CFG_MAJOR_VERSION    (2u)
#define FEE_30_SMALLSECTOR_CFG_MINOR_VERSION    (0u)
#define FEE_30_SMALLSECTOR_DEV_ERROR_DETECT	(STD_OFF)
#define FEE_30_SMALLSECTOR_DEV_ERROR_REPORT	(STD_OFF)
#define FEE_30_SMALLSECTOR_VERSION_INFO_API STD_OFF
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

typedef uint32 Fee_30_SmallSector_AddressType;

#include "Fls.hpp"

#define FEE_30_SMALLSECTOR_LAYER_ONE_INDEX             (0x00U)
#define FEE_30_SMALLSECTOR_LAYER_TWO_INDEX             (0x01U)
#define FEE_30_SMALLSECTOR_LAYER_THREE_INDEX           (0x02U)
#define FEE_30_SMALLSECTOR_NUMBER_OF_FLS_DEVICES       (1U)
#define FEE_30_SMALLSECTOR_FLS_POLLING_MODE            (STD_OFF)
#define FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS    (STD_OFF)
#define FEE_30_SMALLSECTOR_MANAGEMENT_SIZE             (1U)
#define FEE_30_SMALLSECTOR_MAX_BLOCKS_PER_PARTITION    (13U)
#define FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS        (3U)
#define FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS            (26U)
#define FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT         (8U)
#define FEE_30_SMALLSECTOR_MAX_READ_SIZE               (24U)
#define FEE_30_SMALLSECTOR_STATIC_PATTERN              (0xAAU)
#define FEE_30_SMALLSECTOR_NVM_POLLING_MODE            (STD_OFF)

typedef P2VAR(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_DataPtr;
typedef P2CONST(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_ConstDataPtr;
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ReadPtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_DataPtr TargetAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_WritePtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_ConstDataPtr SourceAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ComparePtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_ConstDataPtr DataBufferPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ErasePtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_BlankCheckPtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_GetStatusPtrType)(void);
typedef P2FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_GetJobResultPtrType)(void);

typedef struct{
   Fee_30_SmallSector_ReadPtrType Read;
   Fee_30_SmallSector_WritePtrType Write;
   Fee_30_SmallSector_ComparePtrType Compare;
   Fee_30_SmallSector_ErasePtrType Erase;
   Fee_30_SmallSector_BlankCheckPtrType BlankCheck;
   Fee_30_SmallSector_GetStatusPtrType GetStatus;
   Fee_30_SmallSector_GetJobResultPtrType GetJobResult;
}Fee_30_SmallSector_FlsApiType;

typedef P2CONST(Fee_30_SmallSector_FlsApiType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_FlsApiPtrType;

typedef struct{
    Fee_30_SmallSector_AddressType PartitionStartAddress;
   uint16 PartitionAddressAlignment;
   uint16 PartitionWriteAlignment;
   uint16 PartitionReadAlignment;
   uint16 FlsDeviceIndex;
    Fee_30_SmallSector_FlsApiPtrType FlsApiPtr;
   uint8 FlsEraseValue;
   boolean BlankCheckApiEnabled;
   uint16 BlockNumberList[FEE_30_SMALLSECTOR_MAX_BLOCKS_PER_PARTITION];
}Fee_30_SmallSector_PartitionConfigType;

typedef struct{
    Fee_30_SmallSector_AddressType BlockStartAddress;
   uint16 DataLength;
   uint8 NumberOfInstances;
   uint8 NumberOfDatasets;
   boolean IsImmediateData;
   boolean HasVerificationEnabled;
}Fee_30_SmallSector_BlockConfigType;

typedef P2FUNC(void, FEE_30_SMALLSECTOR_NVM_CODE, Fee_30_SmallSector_CbkJobEndNotificationType)(void);
typedef P2FUNC(void, FEE_30_SMALLSECTOR_NVM_CODE, Fee_30_SmallSector_CbkJobErrorNotificationType)(void);

extern CONST(uint8, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_DatasetSelectionBits;
extern CONST(Fee_30_SmallSector_PartitionConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_PartitionConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS];
extern CONST(Fee_30_SmallSector_BlockConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_BlockConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS];
extern CONST(Fee_30_SmallSector_FlsApiType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_FlsApi0;
extern CONST(Fee_30_SmallSector_CbkJobEndNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobEndNotification;
extern CONST(Fee_30_SmallSector_CbkJobErrorNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobErrorNotification;

#endif

