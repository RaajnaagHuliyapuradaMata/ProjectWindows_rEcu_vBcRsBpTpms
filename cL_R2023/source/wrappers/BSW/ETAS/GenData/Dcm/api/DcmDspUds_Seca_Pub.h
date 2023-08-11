

#ifndef DCMDSPUDS_SECA_PUB_H
#define DCMDSPUDS_SECA_PUB_H

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)

#define DCM_PRV_REQUEST_SEED 0
#define DCM_PRV_SEND_KEY    1

#ifndef     DCM_REQUEST_SEED
#define     DCM_REQUEST_SEED            DCM_PRV_REQUEST_SEED
#endif
#ifndef     DCM_SEND_KEY
#define     DCM_SEND_KEY                DCM_PRV_SEND_KEY
#endif

typedef struct{
#if (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    uint8 SeedBuff[DCM_CFG_SECA_MAXSEEDSIZE];
#endif
    uint32  Residual_delay_u32;
    uint8  FailedAtm_cnt_u8;
}Dcm_Dsp_SecaType;

#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

typedef Std_ReturnType (*Dcm_GetSecurityAttemptCounter_pfct) (
                Dcm_OpStatusType OpStatus,
                uint8 * AttemptCounter
         );

typedef Std_ReturnType (*Dcm_SetSecurityAttemptCounter_pfct) (
                Dcm_OpStatusType OpStatus,
                uint8 AttemptCounter
         );

#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
typedef Std_ReturnType (*Dcm_SetSecurityAttemptCounter_pfct1) (void);
typedef Std_ReturnType (*Dcm_GetSecurityAttemptCounter1_pfct) (
                Dcm_OpStatusType OpStatus
         );
typedef Std_ReturnType (*Dcm_GetSecurityAttemptCounter2_pfct) (
                uint8 * AttemptCounter
         );
#endif

#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)

typedef Std_ReturnType (*Dcm_GetSeed_ptr) (
                const uint8 * SecurityAccessDataRecord,
                Dcm_OpStatusType OpStatus,
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr1) (
                uint32* SeedLength_u32,
                const uint8 * SecurityAccessDataRecord,
                Dcm_OpStatusType OpStatus,
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr3) (
                Dcm_OpStatusType OpStatus,
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr9) (
                uint32* SeedLength_u32,
                Dcm_OpStatusType OpStatus,
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_CompareKey_ptr1) (
                const uint8 * Key,
                Dcm_OpStatusType OpStatus,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*Dcm_GetSeed_ptr5) (
                const uint8 * SecurityAccessDataRecord,
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr10) (
                uint32 SeedLength_u32,
                const uint8 * SecurityAccessDataRecord,
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr6) (
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr11) (
                uint32 SeedLength_u32,
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr7) (
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr12) (
                uint32* SeedLength_u32,
                uint8 * Seed,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_CompareKey_ptr4) (
                const uint8 * Key,
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_CompareKey_ptr6) (
                uint32 KeyLength_u32,
                const uint8 * Key,
                Dcm_OpStatusType OpStatus
        );

typedef Std_ReturnType (*Dcm_CompareKey_ptr5) (
                Dcm_NegativeResponseCodeType * ErrorCode
        );

#endif

#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)

typedef Std_ReturnType (*Dcm_GetSeed_ptr4) (
                Dcm_SecLevelType SecLevel_u8,
                uint32 Seedlen_u32,
                uint32 AccDataRecsize_u32,
                uint8 * SecurityAccessDataRecord,
                uint8 * Seed,
                Dcm_OpStatusType OpStatus,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_GetSeed_ptr8) (
                Dcm_SecLevelType SecLevel_u8,
                uint32* Seedlen_u32,
                uint32 AccDataRecsize_u32,
                uint8 * SecurityAccessDataRecord,
                uint8 * Seed,
                Dcm_OpStatusType OpStatus,
                Dcm_NegativeResponseCodeType * ErrorCode
        );

typedef Std_ReturnType (*Dcm_CompareKey_ptr3) (
                uint32 Key_size_u32,
                uint8 * Key,
                Dcm_OpStatusType OpStatus,
                Dcm_NegativeResponseCodeType * ErrorCode
        );
#endif

typedef enum
{
    USE_ASYNCH_CLIENT_SERVER,
    USE_ASYNCH_FNC
}DcmDspSecurityUsePort;

typedef struct{
    uint32              PowerOnDelay_u32;
    uint32              DelayTime_u32;

    void* const         Dsp_GetSeed_fp;
    void* const         Dsp_CompareKey_fp;
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER != DCM_CFG_OFF)
    void* const         Dsp_GetAttempCounter_fp;
    void* const         Dsp_SetAttempCounter_fp;
#endif
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
    void* const Dsp_GetSeed_ResultFp;
    void* const Dsp_CompareKey_ResultFp;
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER != DCM_CFG_OFF)
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
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)

    boolean   UseAsynchronousServerCallPoint_b;
#endif
    boolean UseFlexibleLength;
}Dcm_Dsp_Security_t;

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

extern uint32 Dcm_Dsp_SecaGlobaltimer_u32;

#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_Dsp_SecaPowerOnDelayIni(void);

extern void Dcm_Dsp_SecaSessIni(void);
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

extern void Dcm_Dsp_RestoreDelayCount(void);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

extern Dcm_Dsp_SecaType Dcm_Dsp_Seca[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

extern const Dcm_Dsp_Security_t Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#endif
