
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#if defined CRC_START_SEC_CODE
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef CRC_START_SEC_CODE

#elif defined CRC_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef CRC_STOP_SEC_CODE

#elif defined CRC_START_SEC_CONST_64
#define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef CRC_START_SEC_CONST_64
#elif defined CRC_STOP_SEC_CONST_64
#define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef CRC_STOP_SEC_CONST_64

#elif defined CRC_START_SEC_CONST_32
#define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef CRC_START_SEC_CONST_32
#elif defined CRC_STOP_SEC_CONST_32
#define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef CRC_STOP_SEC_CONST_32

#elif defined CRC_START_SEC_CONST_16
#define BSW_START_SEC_CONST_16
    #include "Bsw_MemMap.hpp"
    #undef CRC_START_SEC_CONST_16
#elif defined CRC_STOP_SEC_CONST_16
#define BSW_STOP_SEC_CONST_16
    #include "Bsw_MemMap.hpp"
    #undef CRC_STOP_SEC_CONST_16

#elif defined CRC_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CRC_START_SEC_CONST_8
#elif defined CRC_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CRC_STOP_SEC_CONST_8
#elif defined TESTCD_CRC_START_SEC_CODE
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef TESTCD_CRC_START_SEC_CODE
#elif defined TESTCD_CRC_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef TESTCD_CRC_STOP_SEC_CODE

#else
    #error "No valid memmap constant defined before including Crc_MemMap.hpp"
#endif

