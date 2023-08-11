#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef FDL_CFG_H
#define FDL_CFG_H

#include "Fls.h"
#include "SchM_Fls.h"

  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    #define FDL_CRITICAL_SECTION_BEGIN     FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
    #define FDL_CRITICAL_SECTION_END       FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
  #endif
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_OFF)
    #define FDL_CRITICAL_SECTION_BEGIN
    #define FDL_CRITICAL_SECTION_END
  #endif

    #define R_FDL_DEVICE_SPECIFIC_INIT                              \
            *(volatile uint32_t *)0xFFA08000UL = 0xFFFFFFFFUL;          \
            *(volatile uint32_t *)0xFFA08004UL = 0xFFFFFFFFUL;          \
            *(volatile uint32_t *)0xFFA08008UL = 0xFFFFFFFFUL;          \
            *(volatile uint32_t *)0xFFA0800CUL = 0xFFFFFFFFUL;

#define R_FDL_F1L_PATCH_DF_OVERSIZE

#endif
