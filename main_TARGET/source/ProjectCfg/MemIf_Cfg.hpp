#if !defined (MEMIF_CFG_H)
#define MEMIF_CFG_H

#ifndef MEMIF_USE_DUMMY_FUNCTIONS
#define MEMIF_USE_DUMMY_FUNCTIONS STD_OFF
#endif
#ifndef MEMIF_USE_DUMMY_STATEMENT
#define MEMIF_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef MEMIF_DUMMY_STATEMENT
#define MEMIF_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef MEMIF_DUMMY_STATEMENT_CONST
#define MEMIF_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef MEMIF_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define MEMIF_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON
#endif
#ifndef MEMIF_ATOMIC_VARIABLE_ACCESS
#define MEMIF_ATOMIC_VARIABLE_ACCESS 32U
#endif
#ifndef MEMIF_PROCESSOR_CANOEEMU
#define MEMIF_PROCESSOR_CANOEEMU
#endif
#ifndef MEMIF_COMP_
#define MEMIF_COMP_
#endif
#ifndef MEMIF_GEN_GENERATOR_MSR
#define MEMIF_GEN_GENERATOR_MSR
#endif
#ifndef MEMIF_CPUTYPE_BITORDER_LSB2MSB
#define MEMIF_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef MEMIF_CONFIGURATION_VARIANT_PRECOMPILE
#define MEMIF_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef MEMIF_CONFIGURATION_VARIANT_LINKTIME
#define MEMIF_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef MEMIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define MEMIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef MEMIF_CONFIGURATION_VARIANT
#define MEMIF_CONFIGURATION_VARIANT MEMIF_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef MEMIF_POSTBUILD_VARIANT_SUPPORT
#define MEMIF_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define MEMIF_CFG_MAJOR_VERSION	(5u)
#define MEMIF_CFG_MINOR_VERSION	(2u)
#define MEMIF_DEV_ERROR_DETECT       (STD_OFF)
#define MEMIF_DEV_ERROR_REPORT       (STD_OFF)
#define MEMIF_VERSION_INFO_API  (STD_OFF)
#define MEMIF_Fee_30_SmallSector (0U)
#define MEMIF_NUMBER_OF_DEVICES      (1U)

typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiReadType) (uint16 BlockNumber, uint16 BlockOffset, MemIf_DataPtr_pu8 DataBufferPtr, uint16 Length);
typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiWriteType) (uint16 BlockNumber, MemIf_DataPtr_pu8 DataBufferPtr);
typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiEraseImmediateBlockType) (uint16 BlockNumber);
typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiInvalidateBlockType) (uint16 BlockNumber);
typedef P2FUNC (void, MEMIF_CODE, MemIf_ApiCancelType)(void);
typedef P2FUNC (MemIf_StatusType, MEMIF_CODE, MemIf_ApiGetStatusType)(void);
typedef P2FUNC (MemIf_JobResultType, MEMIF_CODE, MemIf_ApiGetJobResultType)(void);
typedef P2FUNC (void, MEMIF_CODE, MemIf_ApiSetModeType)(MemIf_ModeType Mode);

typedef struct{
   MemIf_ApiReadType                   Read;
   MemIf_ApiWriteType                  Write;
   MemIf_ApiEraseImmediateBlockType    EraseImmediateBlock;
   MemIf_ApiInvalidateBlockType        InvalidateBlock;
   MemIf_ApiCancelType                 Cancel;
   MemIf_ApiGetStatusType              GetStatus;
   MemIf_ApiGetJobResultType           GetJobResult;
   MemIf_ApiSetModeType                SetMode;
}MemIf_MemHwAApi_Type;

extern CONST(uint8, MEMIF_CONST) MemIf_NumberOfDevices;
extern CONST(MemIf_MemHwAApi_Type, MEMIF_CONST) MemIf_MemHwaApis[MEMIF_NUMBER_OF_DEVICES];

#endif

