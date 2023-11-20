#if(!defined NVM_CFG_H_PUBLIC)
#define NVM_CFG_H_PUBLIC

#define NVM_CFG_MAJOR_VERSION    (5u)
#define NVM_CFG_MINOR_VERSION    (7u)
#define NVM_CFG_PATCH_VERSION    (0u)

#include "Rte_NvM_Type.hpp"
#include "NvM_Types.hpp"

typedef union{
   uint16 Word_u16;
   uint8  Bytes_au8[2u];
}NvM_CompiledConfigIdType;

#define NVM_DEV_ERROR_DETECT                  (STD_OFF)
#define NVM_DYNAMIC_CONFIGURATION             (STD_ON)
#define NVM_API_CONFIG_CLASS_1                (1u)
#define NVM_API_CONFIG_CLASS_2                (3u)
#define NVM_API_CONFIG_CLASS_3                (7u)
#define NVM_API_CONFIG_CLASS                  (NVM_API_CONFIG_CLASS_3)
#define NVM_JOB_PRIORISATION                  STD_OFF
#define NVM_COMPILED_CONFIG_ID                (2U)
#define NVM_DRV_MODE_SWITCH                   (STD_ON)
#define NVM_POLLING_MODE                      (STD_OFF)
#define NVM_CRC_INT_BUFFER                    (STD_ON)
#define NVM_TOTAL_NUM_OF_NVRAM_BLOCKS         (27UL)
#define NVM_INTERNAL_BUFFER_LENGTH            130UL
#define NVM_VERSION_INFO_API                  (STD_ON)
#define NVM_SET_RAM_BLOCK_STATUS_API          (STD_ON)
#define NVM_KILL_WRITEALL_API                 (STD_ON)
#define NVM_REPAIR_REDUNDANT_BLOCKS_API       (STD_OFF)
#define NVM_DATASET_SELECTION_BITS            (1U)
#define NVM_DCM_BLOCK_OFFSET                  0x8000u
#define NvM_GetDcmBlockId(MyApplBlockId)      ((MyApplBlockId) | NVM_DCM_BLOCK_OFFSET)
#define NvMConf___MultiBlockRequest (0U)
#define NvMConf_NvMBlockDescriptor_NvMConfigBlock (1UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT01 (2UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT02 (3UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT03 (4UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT04 (5UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT05 (6UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT06 (7UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT07 (8UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT08 (9UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT09 (10UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_CAT10 (11UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_BSW_Data (12UL)
#define NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK (13UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvStatusByte (14UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc0 (15UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc1 (16UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc2 (17UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc3 (18UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc4 (19UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc5 (20UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc6 (21UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc7 (22UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc8 (23UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc9 (24UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdDemGenericNvData (25UL)
#define NvMConf_NvMBlockDescriptor_NvMBlock_FBL_Data (26UL)

extern CONST(uint16, NVM_PUBLIC_CONST) NvM_NoOfBlockIds_t;
extern CONST(NvM_CompiledConfigIdType, NVM_PUBLIC_CONST) NvM_CompiledConfigId_t;

#ifndef NVM_USE_DUMMY_FUNCTIONS
#define NVM_USE_DUMMY_FUNCTIONS STD_OFF
#endif
#ifndef NVM_USE_DUMMY_STATEMENT
#define NVM_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef NVM_DUMMY_STATEMENT
#define NVM_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef NVM_DUMMY_STATEMENT_CONST
#define NVM_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef NVM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define NVM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON
#endif
#ifndef NVM_ATOMIC_VARIABLE_ACCESS
#define NVM_ATOMIC_VARIABLE_ACCESS 32U
#endif
#ifndef NVM_PROCESSOR_CANOEEMU
#define NVM_PROCESSOR_CANOEEMU
#endif
#ifndef NVM_COMP_
#define NVM_COMP_
#endif
#ifndef NVM_GEN_GENERATOR_MSR
#define NVM_GEN_GENERATOR_MSR
#endif
#ifndef NVM_CPUTYPE_BITORDER_LSB2MSB
#define NVM_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef NVM_CONFIGURATION_VARIANT_PRECOMPILE
#define NVM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef NVM_CONFIGURATION_VARIANT_LINKTIME
#define NVM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef NVM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define NVM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef NVM_CONFIGURATION_VARIANT
#define NVM_CONFIGURATION_VARIANT NVM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef NVM_POSTBUILD_VARIANT_SUPPORT
#define NVM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#endif

