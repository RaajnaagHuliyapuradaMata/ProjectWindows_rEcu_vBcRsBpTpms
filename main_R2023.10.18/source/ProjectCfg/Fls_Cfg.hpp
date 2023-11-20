#ifndef FLS_CFG_H
#define FLS_CFG_H

#include "MemIf_Types.hpp"

#define FLS_CFG_AR_MAJOR_VERSION  2U
#define FLS_CFG_AR_MINOR_VERSION  4U
#define FLS_CFG_SW_MAJOR_VERSION  1U
#define FLS_CFG_SW_MINOR_VERSION  3U
#define FLS_AR_MAJOR_VERSION_VALUE  2U
#define FLS_AR_MINOR_VERSION_VALUE  4U
#define FLS_AR_PATCH_VERSION_VALUE  0U
#define FLS_SW_MAJOR_VERSION_VALUE  1U
#define FLS_SW_MINOR_VERSION_VALUE  3U
#define FLS_SW_PATCH_VERSION_VALUE  4U
#define FLS_VENDOR_ID_VALUE  59U
#define FLS_MODULE_ID_VALUE  92U
#define FLS_INSTANCE_ID_VALUE             0U
#define FLS_AR_VERSION                    FLS_AR_LOWER_VERSION
#define FLS_FLASH_ACCESS                  FLS_DATAFLASH_ACCESS
#define FLS_DEV_ERROR_DETECT              STD_OFF
#define FLS_VERSION_INFO_API              STD_OFF
#define FLS_CANCEL_API                    STD_ON
#define FLS_COMPARE_API                   STD_ON
#define FLS_SET_MODE_API                  STD_OFF
#define FLS_GET_STATUS_API                STD_ON
#define FLS_GET_JOB_RESULT_API            STD_ON
#define FLS_VERSION_CHECK_EXT_MODULES     STD_ON
#define FLS_CRITICAL_SECTION_PROTECTION   STD_ON
#define FLS_ERASED_VALUE                  0xffffffffUL
#define FLS_JOB_NOTIF_CONFIG              STD_ON
#define FLS_CF_OFFSET_VALUE               32768UL
#define FLS_TIMEOUT_MONITORING            STD_OFF
#define FLS_BLANKCHECK_API                STD_ON
#define FLS_READIMMEDIATE_API             STD_OFF
#define FLS_INTERRUPT_MODE                STD_OFF
#define FLS_FLENDNM_ISR_API               STD_OFF
#define FLS_SUSPEND_API                   STD_OFF
#define FLS_RESUME_API                    STD_OFF
#define FLS_DF_TOTAL_SIZE                 32768U
#define FLS_DF_SECTOR_START_ADDRESS       4280287232UL
#define FLS_PAGE_SIZE                     (uint8)4
#define FLS_BLANK_CHECK                   FDL_SUPPORTED
#define FLS_DF_BLOCK_SIZE                 64U
#define FLS_DF_TOTAL_BLOCKS               512U
#define FLS_DF_BASE_ADDRESS               4280287232UL
#define FLS_FHVE_REGS               NOT_SUPPORTED
#define FLS_FLMD_REGS                     SUPPORTED
#define FLS_FLMDCNT                   (*((volatile uint8 *)(0xFFA00000UL)))
#define FLS_FLMDPCMD                  (*((volatile uint8 *)(0xFFA00004UL)))
#define FLS_NUMBER_OF_SECTORS_0           FLS_DF_TOTAL_BLOCKS
#define FLS_SECTOR_START_ADDRESS_0        FLS_DF_BASE_ADDRESS
#define FlS_SECTOR_SIZE_0                 FLS_DF_BLOCK_SIZE
#define FLS_FLMD0_P_ON_WAIT_CONSTANT            15000U
#define FLS_FLMD0_P_OFF_WAIT_CONSTANT           15000U
#define FlsConfigSet (&Fls_GstConfiguration[0])

#endif

