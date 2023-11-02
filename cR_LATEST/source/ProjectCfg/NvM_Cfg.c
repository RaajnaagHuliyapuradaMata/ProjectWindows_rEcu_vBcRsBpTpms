#define NVM_CFG_SOURCE
#define NVM_H_

#include "Std_Types.hpp"

#include "NvM_Cfg.hpp"
#include "NvM_PrivateCfg.hpp"
#include "SchM_NvM.hpp"

#define NVM_SIZE_STANDARD_JOB_QUEUE  (12U)
#define NVM_SIZE_IMMEDIATE_JOB_QUEUE (12U)

#define NVM_START_SEC_CONST_8
#include "MemMap.hpp"
CONST(uint8, NVM_PRIVATE_CONST) NvM_NoOfWrAttempts_u8 = 1U;
#define NVM_STOP_SEC_CONST_8
#include "MemMap.hpp"

#define NVM_START_SEC_CONST_16
#include "MemMap.hpp"
CONST(uint16, NVM_CONFIG_CONST) NvM_NoOfCrcBytes_u16 = 64U;
CONST(uint16, NVM_PRIVATE_CONST) NvM_CrcQueueSize_u16 = NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;
#define NVM_STOP_SEC_CONST_16
#include "MemMap.hpp"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"
CONST(NvM_QueueSizesType, NVM_PRIVATE_CONST) NvM_QueueSizes_t =
{
    (NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE) - 1u
   ,   NVM_SIZE_STANDARD_JOB_QUEUE
};
#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"

#define NVM_START_SEC_VAR_NOINIT_8
#include "MemMap.hpp"
static VAR(uint8, NVM_PRIVATE_DATA) NvMConfigBlock_RamBlock_au8[4U];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT01_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT02_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT03_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT04_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT05_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT06_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT07_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT08_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT09_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_CAT10_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) NvMBlock_BSW_Data_Crc_au8[2UL];
static VAR(uint8, NVM_PRIVATE_DATA) ECUM_CFG_NVM_BLOCK_Crc_au8[2UL];

VAR(uint8, NVM_PRIVATE_DATA) NvM_InternalBuffer_au8[NVM_INTERNAL_BUFFER_LENGTH];
VAR(uint8, NVM_PRIVATE_DATA) NvM_TestBuffer_u8;
#define NVM_STOP_SEC_VAR_NOINIT_8
#include "MemMap.hpp"

#define NVM_START_SEC_CONST_DESCRIPTOR_TABLE
#include "MemMap.hpp"
CONST(NvM_BlockIdType, NVM_PUBLIC_CONST) NvM_NoOfBlockIds_t = NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;
CONST(NvM_CompiledConfigIdType, NVM_PUBLIC_CONST) NvM_CompiledConfigId_t = {(uint16)NVM_COMPILED_CONFIG_ID};

CONST(NvM_BlockDescriptorType, NVM_CONFIG_CONST) NvM_BlockDescriptorTable_at[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS] =
   {
      {
        NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     0x0001U  
   ,     0  
   ,     0U  
   ,     255U  
   ,     0u  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_USE_CRC_OFF  
   ,     0u  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)NvMConfigBlock_RamBlock_au8  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     0x0002U  
   ,     2U  
   ,     2U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_REDUNDANT  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_OFF |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT01  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT01  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT01  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT01_Crc_au8  
   ,     0x0006U  
   ,     52U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT02  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT02  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT02  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT02_Crc_au8  
   ,     0x0008U  
   ,     52U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT03  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT03  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT03  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT03_Crc_au8  
   ,     0x000AU  
   ,     96U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT04  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT04  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT04  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT04_Crc_au8  
   ,     0x000CU  
   ,     20U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT05  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT05  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT05  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT05_Crc_au8  
   ,     0x000EU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT06  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT06  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT06  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT06_Crc_au8  
   ,     0x0010U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT07  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT07  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT07  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT07_Crc_au8  
   ,     0x0012U  
   ,     24U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT08  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT08  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT08  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT08_Crc_au8  
   ,     0x0014U  
   ,     24U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT09  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT09  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT09  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT09_Crc_au8  
   ,     0x0016U  
   ,     32U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_CAT10  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_CAT10  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_CAT10  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_CAT10_Crc_au8  
   ,     0x0018U  
   ,     4U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_NvMBlock_BSW_Data  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_BSW_Data  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_BSW_Data  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NvMBlock_BSW_Data_Crc_au8  
   ,     0x0034U  
   ,     64U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        (NvM_RamAddressType)&Ram_ECUM_CFG_NVM_BLOCK  
   ,     (NvM_RomAddressType)&Rom_ECUM_CFG_NVM_BLOCK  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_ECUM_CFG_NVM_BLOCK  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     ECUM_CFG_NVM_BLOCK_Crc_au8  
   ,     0x0032U  
   ,     20U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvStatusByte  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvStatusByte  
   ,     Dem_EventStatusByteReadRamBlockFromNvCallback  
   ,     Dem_EventStatusByteWriteRamBlockToNvCallback  
   ,     NULL_PTR  
   ,     0x0030U  
   ,     42U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc0  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc0  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback0  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback0  
   ,     NULL_PTR  
   ,     0x001CU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc1  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc1  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback1  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback1  
   ,     NULL_PTR  
   ,     0x001EU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc2  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc2  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback2  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback2  
   ,     NULL_PTR  
   ,     0x0020U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc3  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc3  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback3  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback3  
   ,     NULL_PTR  
   ,     0x0022U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc4  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc4  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback4  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback4  
   ,     NULL_PTR  
   ,     0x0024U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc5  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc5  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback5  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback5  
   ,     NULL_PTR  
   ,     0x0026U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc6  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc6  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback6  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback6  
   ,     NULL_PTR  
   ,     0x0028U  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc7  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc7  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback7  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback7  
   ,     NULL_PTR  
   ,     0x002AU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc8  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc8  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback8  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback8  
   ,     NULL_PTR  
   ,     0x002CU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdEvMemLoc9  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdEvMemLoc9  
   ,     Dem_EvMemNvmReadRamBlockFromNvCallback9  
   ,     Dem_EvMemNvMWriteRamBlockToNvCallback9  
   ,     NULL_PTR  
   ,     0x002EU  
   ,     48U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     (NvM_RomAddressType)&Rom_NvMBlock_DemNvm_IdDemGenericNvData  
   ,     NULL_PTR  
   ,     Appl_JobEndCallback_DemNvm_IdDemGenericNvData  
   ,     Dem_GenericNVDataReadRamBlockFromNvCallback  
   ,     Dem_GenericNVDataWriteRamBlockToNvCallback  
   ,     NULL_PTR  
   ,     0x001AU  
   ,     18U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_CRC_16_ON  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_OFF |
NVM_SELECT_BLOCK_FOR_READALL_ON |
NVM_SELECT_BLOCK_FOR_WRITEALL_ON |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   ,     {
        NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     NULL_PTR  
   ,     0x0004U  
   ,     130U  
   ,     1U  
   ,     127U  
   ,     MEMIF_Fee_30_SmallSector  
   ,     NVM_BLOCK_NATIVE  
   ,     NVM_BLOCK_USE_CRC_OFF  
   ,     (
NVM_CALC_RAM_BLOCK_CRC_OFF |
NVM_BLOCK_WRITE_PROT_OFF |
NVM_BLOCK_WRITE_BLOCK_ONCE_OFF |
NVM_RESISTANT_TO_CHANGED_SW_ON |
NVM_SELECT_BLOCK_FOR_READALL_OFF |
NVM_SELECT_BLOCK_FOR_WRITEALL_OFF |
NVM_CBK_DURING_READALL_ON |
NVM_CRC_COMP_MECHANISM_OFF
)  
   ,     STD_OFF
      }
   };

typedef unsigned int NvM_LengthCheck;

#define SizeOfRamBlockGreaterThanConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) > (blockLength)) ? -1 : 1)
#define SizeOfRamBlockDoesNotMatchConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) != (blockLength)) ? -1 : 1)
#define SizeOfRamBlockLessThanConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) < (blockLength)) ? -1 : 1)
#define SizeOfRomBlockLessThanSizeOfRamBlock(romBlock, ramBlock) ((sizeof(romBlock) < sizeof(ramBlock)) ? -1 : 1)
#define SizeOfRomBlockDoesNotMatchConfiguredLength(romBlock, blockLength) ((sizeof(romBlock) != (blockLength)) ? -1 : 1)
#define SizeOfRomBlockLessThanConfiguredLength(romBlock, blockLength) ((sizeof(romBlock) < (blockLength)) ? -1 : 1)
#define NVM_STOP_SEC_CONST_DESCRIPTOR_TABLE
#include "MemMap.hpp"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"
VAR(NvM_QueueEntryType, NVM_PRIVATE_DATA) NvM_JobQueue_at[NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE];
#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

#define NVM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.hpp"
VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_BlockMngmtArea_at[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_DcmBlockMngmt_t;
#define NVM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.hpp"

#define NVM_START_SEC_CODE
#include "MemMap.hpp"
FUNC(void, NVM_PRIVATE_CODE) NvM_EnterCriticalSection(void){
    SchM_Enter_NvM_NVM_EXCLUSIVE_AREA_0();
}

FUNC(void, NVM_PRIVATE_CODE) NvM_ExitCriticalSection(void){
    SchM_Exit_NvM_NVM_EXCLUSIVE_AREA_0();
}

#define NvM_invokeMultiBlockMode(serv, res)
#define NvM_invokeMultiCbk(serv, res)

FUNC(void, NVM_PRIVATE_CODE) NvM_MultiBlockCbk(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{
    NvM_invokeMultiBlockMode(ServiceId, JobResult);
   if(JobResult != NVM_REQ_PENDING)
   {
        NvM_invokeMultiCbk(ServiceId, JobResult);
   }
}

#define NvM_invokeCbk(descr, serv, res) (descr)->CallbackFunc_pt((serv), (res))
#define NvM_invokeCurrentBlockMode(id, res)

void NvM_BlockNotification(NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{
   const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(BlockId);
   const NvM_BlockDescrPtrType blockDescriptorPtr = &NvM_BlockDescriptorTable_at[orgBlockId];
   if(orgBlockId == BlockId)
   {
        if((blockDescriptorPtr->CallbackFunc_pt != NULL_PTR) && (JobResult != NVM_REQ_PENDING) &&
            (ServiceId != NVM_WRITE_ALL) &&
            (!((ServiceId == NVM_READ_ALL) && ((blockDescriptorPtr->Flags_u8 & NVM_CBK_DURING_READALL_ON) != NVM_CBK_DURING_READALL_ON))))
        {
            NvM_invokeCbk(blockDescriptorPtr, ServiceId, JobResult);
        }
        if(blockDescriptorPtr->NotifyBswM == TRUE)
        {
            NvM_invokeCurrentBlockMode(BlockId, JobResult);
        }
   }
}

#define NVM_STOP_SEC_CODE
#include "MemMap.hpp"
