
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#if defined RBA_BSWSRV_START_SEC_ENVRAM_32
    #undef  RBA_BSWSRV_START_SEC_ENVRAM_32

    #pragma section ".bss.envram.a4" awB
#elif defined RBA_BSWSRV_STOP_SEC_ENVRAM_32
    #undef    RBA_BSWSRV_STOP_SEC_ENVRAM_32
    #pragma section

#elif defined RBA_BSWSRV_START_SEC_VAR_CLEARED_32
    #undef    RBA_BSWSRV_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_DEFAULT_RAM0_CLEARED_32
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_VAR_CLEARED_32
    #undef    RBA_BSWSRV_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_32
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_RAMALL_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_RAMALL_CLEARED_UNSPECIFIED

    #if (MCU_RB_MACHINE_FAM == MCU_RB_IFX_UC1)
    #  pragma section ".zbss.ram_all.a4" awBz
    #else
    #  pragma section ".sbss.ram_all.a4" awBs
    #endif
#elif defined RBA_BSWSRV_STOP_SEC_RAMALL_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_RAMALL_CLEARED_UNSPECIFIED
    #pragma section

#elif defined RBA_BSWSRV_START_SEC_CONST_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CONST_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_CODE
    #undef    RBA_BSWSRV_START_SEC_CODE
    #define  BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE
    #undef    RBA_BSWSRV_STOP_SEC_CODE
    #define  BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_CODE_FAST
    #undef    RBA_BSWSRV_START_SEC_CODE_FAST
    #define  BSW_START_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_FAST
    #undef    RBA_BSWSRV_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_CODE_NONEST
    #undef    RBA_BSWSRV_START_SEC_CODE_NONEST
    #define  BSW_START_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_NONEST
    #undef    RBA_BSWSRV_STOP_SEC_CODE_NONEST
    #define  BSW_STOP_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_CODE_LOW_PRIO
    #undef    RBA_BSWSRV_START_SEC_CODE_LOW_PRIO
    #define  BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_LOW_PRIO
    #undef    RBA_BSWSRV_STOP_SEC_CODE_LOW_PRIO
    #define  BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"

#else
    #error "unknown MemMap define"
#endif

