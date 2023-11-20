

#ifndef DCMDSPUDS_SECA_PUB_H
#define DCMDSPUDS_SECA_PUB_H

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)

#define DCM_PRV_REQUEST_SEED 0
#define DCM_PRV_SEND_KEY    1

#ifndef     DCM_REQUEST_SEED
#define DCM_REQUEST_SEED            DCM_PRV_REQUEST_SEED
#endif
#ifndef     DCM_SEND_KEY
#define DCM_SEND_KEY                DCM_PRV_SEND_KEY
#endif

typedef struct{
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
   uint8 SeedBuff[DCM_CFG_SECA_MAXSEEDSIZE];
#endif
   uint32  Residual_delay_u32;
   uint8  FailedAtm_cnt_u8;
}Dcm_Dsp_SecaType;

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSecurityAttemptCounter_pfct)
        (
                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) AttemptCounter
         );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_SetSecurityAttemptCounter_pfct)
        (
                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) AttemptCounter
         );

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_SetSecurityAttemptCounter_pfct1)(void);
typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSecurityAttemptCounter1_pfct)
        (
                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
         );
typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSecurityAttemptCounter2_pfct)
        (
                P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) AttemptCounter
         );
#endif

#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr)
        (
                P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr3)
        (
                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_CompareKey_ptr1)
        (
                P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Key
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr5)
        (
                P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr6)
        (
                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr7)
        (
                P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_CompareKey_ptr4)
        (
                P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Key
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_CompareKey_ptr5)
        (
                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

#endif

#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_GetSeed_ptr4)
        (
                VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8
   ,     VAR(uint32,AUTOMATIC) Seedlen_u32
   ,     VAR(uint32,AUTOMATIC) AccDataRecsize_u32
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_CompareKey_ptr3)
        (
                VAR(uint32,AUTOMATIC) Key_size_u32
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Key
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
        );
#endif

typedef enum{
    USE_ASYNCH_CLIENT_SERVER
   ,   USE_ASYNCH_FNC
}DcmDspSecurityUsePort;

typedef struct{
   uint32              PowerOnDelay_u32;
   uint32              DelayTime_u32;

   void* const         Dsp_GetSeed_fp;
   void* const         Dsp_CompareKey_fp;
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER != DCM_CFG_OFF)
   void* const         Dsp_GetAttempCounter_fp;
   void* const         Dsp_SetAttempCounter_fp;
#endif
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
   void* const Dsp_GetSeed_ResultFp;
   void* const Dsp_CompareKey_ResultFp;
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER != DCM_CFG_OFF)
   void* const Dsp_GetAttempCounter_Resultfp;
   void* const Dsp_SetAttempCounter_Resultfp;
#endif
#endif
    Dcm_SecLevelType    Security_level_u8;
   uint32               Seed_size_u32;
   uint32               Key_size_u32;
   uint8               NumAttDelay_u8;
   uint8               NumAttLock_u8;
   uint32               AccDataRecsize_u32;
    DcmDspSecurityUsePort    usePort;
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

   boolean   UseAsynchronousServerCallPoint_b;
#endif
}Dcm_Dsp_Security_t;

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

extern VAR( uint32, DCM_VAR) Dcm_Dsp_SecaGlobaltimer_u32;

#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_Dsp_SecaPowerOnDelayIni(void);

extern FUNC(void,DCM_CODE) Dcm_Dsp_SecaSessIni(void);
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

extern FUNC(void,DCM_CODE) Dcm_Dsp_RestoreDelayCount(void);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern VAR(Dcm_Dsp_SecaType,  DCM_VAR) Dcm_Dsp_Seca[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsp_Security_t, DCM_CONST) Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
