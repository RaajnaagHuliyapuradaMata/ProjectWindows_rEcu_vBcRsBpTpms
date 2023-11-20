#ifndef OS_H
#define OS_H

#define OS_MODULE_ID (1U)
#define OS_VENDOR_ID (11U)
#define OS_AR_MAJOR_VERSION (4U)
#define OS_AR_MINOR_VERSION (2U)
#define OS_AR_PATCH_VERSION (2U)
#define OS_AR_RELEASE_MAJOR_VERSION (4U)
#define OS_AR_RELEASE_MINOR_VERSION (2U)
#define OS_AR_RELEASE_REVISION_VERSION (2U)
#define OS_SW_MAJOR_VERSION (5U)
#define OS_SW_MINOR_VERSION (5U)
#define OS_SW_PATCH_VERSION (11U)
#define OS_TARGET_PORT "RH850GHS"
#define OS_TARGET_PORT_RH850GHS
#define OS_TARGET_MAJOR_VERSION (5U)
#define OS_TARGET_MINOR_VERSION (0U)
#define OS_TARGET_PATCH_VERSION (20U)

#include "Types_SwcServiceOs.hpp"

#ifndef STD_TYPES_H
  #error "STD_TYPES_H is not defined. This should appear in Std_Types.h (AUTOSAR requirement STD014). Is Std_Types.h in the include path? (try --samples:[Includes]overwrite -ISamples\Includes)"
#endif
#ifndef OS_APPL_CODE
#define OS_APPL_CODE
#endif
#ifndef OS_CALLOUT_CODE
#define OS_CALLOUT_CODE OS_APPL_CODE
#endif
#ifndef OS_VAR_CLEARED
#define OS_VAR_CLEARED OS_VAR_POWER_ON_INIT
#endif
#ifndef OS_VAR_NO_INIT
#define OS_VAR_NO_INIT OS_VAR_NOINIT
#endif

#ifdef _lint

#define Os_trap()
#else
#define Os_trap() {OS_BARRIER(); OS_TRAP(0U); OS_SYNCE(); OS_BARRIER();}
#endif
#define CAT1_ISR(x) void x(void)
extern void __DI(void);
extern void __EI(void);
extern void __SNOOZE(void);
extern void __SYNCE(void);
extern void __SYNCI(void);
extern void __SYNCM(void);
extern void __SYNCP(void);
extern void __memory_changed(void);
#ifdef _lint
  extern void __CLR1(volatile char *addr, uint32 bitnum);
  extern void __DBTAG(uint32 val);
  extern sint32 __LDL_W(sint32 *addr);
  extern void __LDSR(sint32 regID, sint32 selID, uint32 val);
  extern uint32 __SCH0L(uint32 val);
  extern uint32 __SCH1L(uint32 val);
  extern void __SET1(volatile char *addr, uint32 bitnum);
  extern sint32 __STC_W(sint32 val, sint32 *addr);
  extern uint32 __STSR(sint32 regID, sint32 selID);

#define OS_CLR(addr, bit) __CLR1(addr, (uint32)bit)
#define OS_DBTAG(value) __DBTAG((uint32)value)
#define OS_LDSR(reg, bank, val) __LDSR((sint32)reg, (sint32)bank, val)
#define OS_STSR(reg, bank) __STSR((sint32)reg, (sint32)bank)
#define OS_SCH1L(value) __SCH1L((uint32)value)
#define OS_SCH0L(value) __SCH0L((uint32)value)
#define OS_SET(addr, bit) __SET1(addr, (uint32)bit)
  extern void os_trap(uint32 value);
  extern void os_nop(void);
  extern void Os_memclr(uint8 *dest, uint32 len);
#else
  extern void __CLR1(volatile char *addr, __ghs_c_int__ bitnum);
  extern void __DBTAG(int val);
  extern int __LDL_W(int *addr);
  extern void __LDSR(int regID, int selID, unsigned int val);
  extern void __SET1(volatile char *addr, __ghs_c_int__ bitnum);
#if(__GHS_VERSION_NUMBER == 201355)
  extern int __SCH0L(int val);
  extern int __SCH1L(int val);
#else
  extern unsigned int __SCH0L(unsigned int val);
  extern unsigned int __SCH1L(unsigned int val);
#endif
  extern int __STC_W(int val, int *addr);
  extern unsigned int __STSR(int regID, int selID);

#define OS_CLR(addr, bit) __CLR1(addr, (int)bit)
#define OS_DBTAG(value) __DBTAG((int)value)
#define OS_LDSR(reg, bank, val) __LDSR((int)reg, (int)bank, val)
#define OS_SCH1L(value) __SCH1L((unsigned int)value)
#define OS_SCH0L(value) __SCH0L((unsigned int)value)
#define OS_SET(addr, bit) __SET1(addr, (int)bit)
#define OS_STSR(reg, bank) __STSR((int)reg, (int)bank)

  void os_trap(uint32 value);
__asmleaf void os_trap(uint32 value)
{
%con value;
  trap value
%error
  Macro has not expanded so it should result in error
}

  void os_nop(void);
__asmleaf void os_nop(void){
  nop
}
#endif
#define OS_BARRIER() __memory_changed()
#define OS_DI() __DI()
#define OS_EI() __EI()
#define OS_LDL_W(addr) __LDL_W(addr)
#define OS_NOP() os_nop()
#define OS_SNOOZE() __SNOOZE()
#define OS_STC_W(val, addr) __STC_W(val, addr)
#define OS_SYNCE() __SYNCE()
#define OS_SYNCI() __SYNCI()
#define OS_SYNCM() __SYNCM()
#define OS_SYNCP() __SYNCP()
#define OS_TRAP(val) os_trap(val)
#ifdef _lint
#else
#pragma asm
#if(__V800_registermode==22)
    .set  regframe, 16
#endif
#if(__V800_registermode==26)
    .set  regframe, 18
#endif
#if(__V800_registermode==32)
    .set  regframe, 21
#endif

    .set  framesize, regframe*4
#pragma endasm

void OS_FETRAP_ENTRY(void);
asm void OS_FETRAP_ENTRY(void){
    -- isr prolog
    -- 22 reg mode: save 15 registers + FEPSW + FEPC
    -- 26 reg mode: save 17 registers + FEPSW + FEPC
    -- 32 reg mode: save 20 registers + FEPSW + FEPC
    prepare   {ep-lp}, regframe, sp
   sst.w     r1,  (framesize-4)[ep]

   stsr      FEPSW, r1, 0
   sst.w     r1,  (framesize-8)[ep]

   stsr      FEPC, r1, 0
   sst.w     r1,  (framesize-12)[ep]

   sst.w     r2,  (framesize-16)[ep]
   sst.w     gp,  (framesize-20)[ep]
   sst.w     r5,  (framesize-24)[ep]
   sst.w     r6,  (framesize-28)[ep]
   sst.w     r7,  (framesize-32)[ep]
   sst.w     r8,  (framesize-36)[ep]
   sst.w     r9,  (framesize-40)[ep]
   sst.w     r10, (framesize-44)[ep]
   sst.w     r11, (framesize-48)[ep]
   sst.w     r12, (framesize-52)[ep]
   sst.w     r13, (framesize-56)[ep]
   sst.w     r14, (framesize-60)[ep]
#if(__V800_registermode==26)
   sst.w     r15, (framesize-64)[ep]
   sst.w     r16, (framesize-68)[ep]
#endif
#if(__V800_registermode==32)
   sst.w     r15, (framesize-64)[ep]
   sst.w     r16, (framesize-68)[ep]
   sst.w     r17, (framesize-72)[ep]
   sst.w     r18, (framesize-76)[ep]
   sst.w     r19, (framesize-80)[ep]
#endif
}

void OS_FETRAP_LEAVE(void);
asm void OS_FETRAP_LEAVE(void){
    mov       sp, ep
#if(__V800_registermode==32)
   sld.w     (framesize-80)[ep], r19
   sld.w     (framesize-76)[ep], r18
   sld.w     (framesize-72)[ep], r17
   sld.w     (framesize-68)[ep], r16
   sld.w     (framesize-64)[ep], r15
#endif
#if(__V800_registermode==26)
   sld.w     (framesize-68)[ep], r16
   sld.w     (framesize-64)[ep], r15
#endif
   sld.w     (framesize-60)[ep], r14
   sld.w     (framesize-56)[ep], r13
   sld.w     (framesize-52)[ep], r12
   sld.w     (framesize-48)[ep], r11
   sld.w     (framesize-44)[ep], r10
   sld.w     (framesize-40)[ep], r9
   sld.w     (framesize-36)[ep], r8
   sld.w     (framesize-32)[ep], r7
   sld.w     (framesize-28)[ep], r6
   sld.w     (framesize-24)[ep], r5
   sld.w     (framesize-20)[ep], gp
   sld.w     (framesize-16)[ep], r2

    di
   sld.w     (framesize-12)[ep], r1
    ldsr      r1, FEPC, 0

   sld.w     (framesize-8)[ep], r1
    ldsr      r1, FEPSW, 0

   sld.w     (framesize-4)[ep], r1
    dispose   regframe, {ep-lp}
    feret
 }

#define OS_PRAGMA(x) _Pragma(#x)
#endif
#ifdef _lint
#define OS_FETRAP_EXCEPTION(name, isr)
#else
#define OS_FETRAP_EXCEPTION(name, isr)   OS_PRAGMA( ghs noprologue)   void name( void) {     OS_FETRAP_ENTRY();     isr();     OS_FETRAP_LEAVE();   }
#endif

#define OS_START_SEC_CODE_LIB
#include "Os_MemMap.hpp"

extern FUNC(void, OS_CODE) Os_InitializeVectorTable(void);
extern FUNC(uint32, OS_CODE) Os_CPUMode(void);

#define OS_STOP_SEC_CODE_LIB
#include "Os_MemMap.hpp"

#ifndef OS_VOLATILE
#define OS_VOLATILE volatile
#endif
#ifdef _lint
typedef sint32 Os_jmp_buf[13];
#else
#if(__V800_registermode==22)
typedef sint32 Os_jmp_buf[11];
#endif
#if(__V800_registermode==26)
typedef sint32 Os_jmp_buf[13];
#endif
#if(__V800_registermode==32)
typedef sint32 Os_jmp_buf[16];
#endif
#endif
extern __attribute__((noinline,noreturn)) void Os_longjmp(Os_jmp_buf env);
extern sint32 Os_setjmp(Os_jmp_buf env);

#ifndef OS_CONST
  #error "OS_CONST is not defined. This normally appears in Compiler_Cfg.h or Os_Compiler_Cfg.hpp"
#endif
#ifndef OS_CONST_FAST
#define OS_CONST_FAST OS_CONST
#endif

#define OS_MEMMAP_DECLARATIONS (TRUE)
#define OS_MEMMAP_DEFINITIONS  (TRUE)

typedef unsigned long Os_ResourceCountType;
typedef uint32 Os_StackTraceType;
typedef uint32 Os_StackValueType;
typedef uint32 Os_StackSizeType;
#ifdef _lint
extern Os_StackValueType Os_GetSP(void);
#else
Os_StackValueType Os_GetSP(void);
__asmleaf Os_StackValueType Os_GetSP(void){
%reg
  mov  r3, r10
%con
  mov  r3, r10
%mem
  mov  r3, r10
}
#endif

typedef void (*Os_VoidVoidFunctionType)(void);
typedef Os_VoidVoidFunctionType Os_TaskEntryFunctionType;
typedef Os_VoidVoidFunctionType Os_IsrEntryFunctionType;

typedef enum{OS_BUDGET = 0U, OS_ECC_START, OS_ECC_RESUME, OS_ECC_WAIT}Os_StackOverrunType;

#define OS_EXTENDED_STATUS
#define OS_NON_ORTI_BUILD
#define OS_SCALABILITY_CLASS_1

typedef unsigned long ApplicationType;
#define INVALID_OSAPPLICATION ((ApplicationType)0U)

typedef void (*Os_AppErrorHookFunctionType)(StatusType e);
#define OS_PSW (5U)
#define OS_SELID_0 (0U)
typedef uint32 Os_tmaskType;
typedef struct Os_ApplicationConfigurationType_s {
  ApplicationType app_id;
  Os_AppErrorHookFunctionType errorhook;
}Os_ApplicationConfigurationType;

typedef unsigned long TickType;
typedef signed long SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType;
typedef uint32 PhysicalTimeType;
typedef unsigned long Os_StopwatchTickType;
typedef P2VAR(Os_StopwatchTickType, TYPEDEF, OS_VAR) Os_StopwatchTickRefType;
typedef signed long Os_TimeLimitType;

typedef enum{PRO_IGNORE = 0U, PRO_TERMINATETASKISR, PRO_TERMINATEAPPL, PRO_TERMINATEAPPL_RESTART, PRO_SHUTDOWN}ProtectionReturnType;

typedef uint32 IdleModeType;
#define IDLE_NO_HALT ((IdleModeType)0U)
#define OS_CURRENT_IDLEMODE Os_CurrentIdleMode
typedef uint16 CoreIdType;
typedef uint16 SpinlockIdType;
#define INVALID_SPINLOCK ((SpinlockIdType)0)
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
  typedef unsigned char StatusType;
#define E_OK ((StatusType)0U)
#endif
#define E_OS_ACCESS ((StatusType)1U)
#define E_OS_CALLEVEL ((StatusType)2U)
#define E_OS_ID ((StatusType)3U)
#define E_OS_LIMIT ((StatusType)4U)
#define E_OS_NOFUNC ((StatusType)5U)
#define E_OS_RESOURCE ((StatusType)6U)
#define E_OS_STATE ((StatusType)7U)
#define E_OS_VALUE ((StatusType)8U)
#define E_OS_SERVICEID ((StatusType)9U)
#define E_OS_ILLEGAL_ADDRESS ((StatusType)10U)
#define E_OS_MISSINGEND ((StatusType)11U)
#define E_OS_DISABLEDINT ((StatusType)12U)
#define E_OS_STACKFAULT ((StatusType)13U)
#define E_OS_PROTECTION_MEMORY ((StatusType)14U)
#define E_OS_PROTECTION_TIME ((StatusType)15U)
#define E_OS_PROTECTION_ARRIVAL ((StatusType)16U)
#define E_OS_PROTECTION_LOCKED ((StatusType)17U)
#define E_OS_PROTECTION_EXCEPTION ((StatusType)18U)
#define E_OS_CORE ((StatusType)19U)
#define E_OS_SPINLOCK ((StatusType)20U)
#define E_OS_INTERFERENCE_DEADLOCK ((StatusType)21U)
#define E_OS_NESTING_DEADLOCK ((StatusType)22U)
#define E_OS_SYS_NO_RESTART ((StatusType)23U)
#define E_OS_SYS_RESTART ((StatusType)24U)
#define E_OS_SYS_OVERRUN ((StatusType)25U)
#define E_OS_XCORE_QFULL ((StatusType)26U)
typedef P2VAR(StatusType, TYPEDEF, OS_VAR) Os_StatusRefType;

typedef unsigned long AccessType;
#define OS_ACCESS_READ    (1U)
#define OS_ACCESS_WRITE   (2U)
#define OS_ACCESS_EXECUTE (4U)
#define OS_ACCESS_STACK   (8U)
#define OSMEMORY_IS_READABLE(x)   (0U != ((x) & OS_ACCESS_READ))
#define OSMEMORY_IS_WRITEABLE(x)  (0U != ((x) & OS_ACCESS_WRITE))
#define OSMEMORY_IS_EXECUTABLE(x) (0U != ((x) & OS_ACCESS_EXECUTE))
#define OSMEMORY_IS_STACKSPACE(x) (0U != ((x) & OS_ACCESS_STACK))
typedef P2CONST(uint8, TYPEDEF, OS_VAR) MemoryStartAddressType;
typedef unsigned long MemorySizeType;
typedef enum{RESTART = 1U, NO_RESTART}RestartType;
typedef enum{APPLICATION_ACCESSIBLE = 0U, APPLICATION_RESTARTING, APPLICATION_TERMINATED}ApplicationStateType;
typedef P2VAR(ApplicationStateType, TYPEDEF, OS_VAR) ApplicationStateRefType;
typedef enum{ACCESS = 0U, NO_ACCESS}ObjectAccessType;
typedef enum{OBJECT_TASK = 0U, OBJECT_ISR, OBJECT_ALARM, OBJECT_RESOURCE, OBJECT_COUNTER, OBJECT_SCHEDULETABLE}ObjectTypeType;
typedef CONSTP2CONST(void, TYPEDEF, OS_VAR) Os_AnyType;

typedef unsigned long TrustedFunctionIndexType;
typedef P2VAR(void, TYPEDEF, OS_VAR) TrustedFunctionParameterRefType;
#define INVALID_FUNCTION ((TrustedFunctionIndexType)-1)
typedef void (*Os_FunctionEntryType)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
typedef struct Os_TrustedFunctionType_s {
  Os_FunctionEntryType function;
  CONSTP2CONST(Os_ApplicationConfigurationType, OS_CONST, OS_CONST) application;
}Os_TrustedFunctionType;

typedef unsigned long Os_IdleType;
#define OS_CORE_CURRENT (255U)

typedef struct Os_MeterInfoType_s {
  Os_StackValueType stackbase;
  Os_StackSizeType stackusage;
  Os_StackSizeType stackmax;
  Os_StackSizeType stackbudget;
}Os_MeterInfoType;
typedef P2VAR(Os_MeterInfoType, TYPEDEF, OS_VAR) Os_MeterInfoRefType;
#define DeclareEvent(x)
typedef uint8 EventMaskType;
typedef P2VAR(EventMaskType, TYPEDEF, OS_VAR) EventMaskRefType;
typedef uint32 Os_imaskType;
#define OS_PMR (11U)
#define OS_SELID_2 (2U)
typedef struct Os_ISRDynType_s {
  Os_MeterInfoType meter;
}Os_ISRDynType;
typedef struct Os_ISRType_s {
  Os_VoidVoidFunctionType entry_function;
  CONSTP2VAR(Os_ISRDynType, OS_VAR, OS_CONST) dynamic;
  Os_imaskType imask;
  Os_StackSizeType stackbudget;
}Os_ISRType;
typedef P2CONST(Os_ISRType, TYPEDEF, OS_VAR) ISRType;
#define INVALID_ISR ((ISRType)0)

#define OS_ISRTYPE_TO_INDEX(isrtype) (isrtype - &Os_const_isrs[0])

#define OS_INDEX_TO_ISRTYPE(index) ((ISRType)&Os_const_isrs[index])
typedef P2VAR(ISRType, TYPEDEF, OS_VAR) ISRRefType;

#define ISR(x) void Os_Entry_##x(void)
#define DeclareISR(x)
#define OS_IPL (8U)
typedef unsigned long Os_bitmask;
typedef Os_bitmask Os_pset0Type;
typedef union {
  Os_pset0Type p0;
}Os_psetType;
typedef union {
  Os_bitmask t0;
}Os_tpmaskType;
typedef unsigned long Os_ActivationCountType;

typedef struct Os_TaskDynType_s {
  VAR(Os_jmp_buf, OS_VAR_NOINIT) terminate_jump_buf;
  Os_MeterInfoType meter;
  Os_ActivationCountType activation_count;
}Os_TaskDynType;

typedef struct Os_TaskType_s {
  CONSTP2VAR(Os_TaskDynType, OS_VAR, OS_CONST) dynamic;
  Os_VoidVoidFunctionType entry_function;
  Os_psetType pset;
  Os_tpmaskType base_tpmask;
  Os_tpmaskType tpmask;
  Os_StackSizeType stackbudget;
  Os_ActivationCountType activation_count;
}Os_TaskType;
typedef P2CONST(Os_TaskType, TYPEDEF, OS_VAR) TaskType;
#define INVALID_TASK  (TaskType)0
#define OS_INVALID_TPL (0xFFFFU)

#define OS_TASKTYPE_TO_INDEX(tasktype) (tasktype - &Os_const_tasks0[0])

#define OS_INDEX_TO_TASKTYPE(index) ((TaskType)(Os_const_tasks[index]))
typedef P2VAR(TaskType, TYPEDEF, OS_VAR) TaskRefType;
enum Os_TaskStateType {SUSPENDED = 0U, READY, WAITING, RUNNING};
typedef enum Os_TaskStateType TaskStateType;
typedef P2VAR(TaskStateType, TYPEDEF, OS_VAR) TaskStateRefType;

#define TASK(x) void Os_Entry_##x(void)
#define DeclareTask(x)

typedef struct Os_ResourceDynType_s {
  Os_ResourceCountType access_count;
  union {
    Os_tpmaskType tpmask;
  }saved_priority;
}Os_ResourceDynType;

typedef struct Os_ResourceType_s {
  CONSTP2VAR(Os_ResourceDynType, OS_VAR, OS_CONST) dynamic;
  Os_tpmaskType tpmask;
}Os_ResourceType;

typedef P2CONST(Os_ResourceType, TYPEDEF, OS_CONST) ResourceType;

#define DeclareResource(x)

typedef struct{
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
}AlarmBaseType;

typedef P2VAR(AlarmBaseType, TYPEDEF, OS_VAR) AlarmBaseRefType;

typedef struct Os_AlarmDynType_s {
  boolean running;
  TickType match;
  TickType period;
}Os_AlarmDynType;

typedef struct Os_AlarmType_s {
  uint8 config;
}Os_AlarmType;

typedef unsigned long AlarmType;

#define DeclareAlarm(x)

typedef void (*Os_AlarmCallbackType)(void);

#define ALARMCALLBACK(x) FUNC(void, OS_CODE) Os_Cbk_Alarm_##x(void)

typedef struct{
  boolean Running;
  boolean Pending;
  TickType Delay;
}Os_CounterStatusType;
typedef P2VAR(Os_CounterStatusType, TYPEDEF, OS_VAR) Os_CounterStatusRefType;

typedef TickType (*Os_HwCounterNowType)(void);
typedef void (*Os_HwCounterSetType)(TickType Value);
typedef void (*Os_HwCounterStateType)(Os_CounterStatusRefType State);
typedef void (*Os_HwCounterCancelType)(void);
typedef StatusType (*Os_CounterIncrAdvType)(void);
typedef FUNC(void, OS_CODE) (*Os_CounterStartType)(Os_AnyType ctr, TickType requested, TickType relative, TickRefType match_value);

typedef struct Os_CounterDynType_s {
  union {
   struct s_swd {
      TickType count;
   }sw;
  }type_dependent;
}Os_CounterDynType;

typedef struct Os_CounterType_s {
  CONSTP2VAR(Os_CounterDynType, OS_VAR, OS_CONST) dynamic;
  Os_CounterIncrAdvType advincr;
  AlarmBaseType base;
}Os_CounterType;
typedef P2CONST(Os_CounterType, TYPEDEF, OS_CONST) CounterType;

#define DeclareCounter(x)

enum Os_ScheduleTableStatusType {SCHEDULETABLE_STOPPED = 0U, SCHEDULETABLE_NEXT, SCHEDULETABLE_WAITING, SCHEDULETABLE_RUNNING, SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS};

typedef enum Os_ScheduleTableStatusType ScheduleTableStatusType;
typedef P2VAR(ScheduleTableStatusType, TYPEDEF, OS_VAR) ScheduleTableStatusRefType;
typedef enum{OS_SYNC_NONE, OS_SYNC_IMPLICIT, OS_SYNC_EXPLICIT}Os_ScheduleTableSyncType;
typedef enum{OS_SYNC_ASYNC, OS_SYNC_ADVANCING, OS_SYNC_RETARDING, OS_SYNC_INSYNC}Os_ScheduleTableSyncStateType;

struct Os_ScheduleTableDynType_s;

typedef struct Os_ScheduleTableType_s {
  CONSTP2VAR(struct Os_ScheduleTableDynType_s, OS_VAR, OS_CONST) dynamic;
  CounterType counter;
  boolean repeat;
  uint8 config;
  uint8 initial;
}Os_ScheduleTableType;

typedef P2CONST(Os_ScheduleTableType, TYPEDEF, OS_CONST) ScheduleTableType;
typedef P2VAR(ScheduleTableType, TYPEDEF, OS_VAR) ScheduleTableRefType;

typedef struct Os_ScheduleTableDynType_s {
  TickType match;
  ScheduleTableType next;
  ScheduleTableStatusType state;
  uint8 config;
}Os_ScheduleTableDynType;

#define DeclareScheduleTable(x)

typedef unsigned long OSServiceIdType;

#define OSServiceId_None ((OSServiceIdType)0U)
#define OSServiceId_ActivateTask ((OSServiceIdType)1)
#define OSServiceId_Os_AdvanceCounter ((OSServiceIdType)2)
#define OSServiceId_CancelAlarm ((OSServiceIdType)3)
#define OSServiceId_CallTrustedFunction ((OSServiceIdType)4)
#define OSServiceId_CheckISRMemoryAccess ((OSServiceIdType)5)
#define OSServiceId_CheckObjectAccess ((OSServiceIdType)6)
#define OSServiceId_CheckObjectOwnership ((OSServiceIdType)7)
#define OSServiceId_CheckTaskMemoryAccess ((OSServiceIdType)8)
#define OSServiceId_ChainTask ((OSServiceIdType)9)
#define OSServiceId_ClearEvent ((OSServiceIdType)10)
#define OSServiceId_ControlIdle ((OSServiceIdType)11)
#define OSServiceId_DisableAllInterrupts ((OSServiceIdType)12)
#define OSServiceId_EnableAllInterrupts ((OSServiceIdType)13)
#define OSServiceId_GetActiveApplicationMode ((OSServiceIdType)14)
#define OSServiceId_GetAlarm ((OSServiceIdType)15)
#define OSServiceId_GetAlarmBase ((OSServiceIdType)16)
#define OSServiceId_GetApplicationID ((OSServiceIdType)17)
#define OSServiceId_GetCurrentApplicationID ((OSServiceIdType)18)
#define OSServiceId_GetCounterValue ((OSServiceIdType)19)
#define OSServiceId_GetElapsedCounterValue ((OSServiceIdType)20)
#define OSServiceId_GetEvent ((OSServiceIdType)21)
#define OSServiceId_GetISRID ((OSServiceIdType)22)
#define OSServiceId_GetResource ((OSServiceIdType)23)
#define OSServiceId_GetScheduleTableStatus ((OSServiceIdType)24)
#define OSServiceId_GetTaskID ((OSServiceIdType)25)
#define OSServiceId_GetTaskState ((OSServiceIdType)26)
#define OSServiceId_GetVersionInfo ((OSServiceIdType)27)
#define OSServiceId_IncrementCounter ((OSServiceIdType)28)
#define OSServiceId_NextScheduleTable ((OSServiceIdType)29)
#define OSServiceId_Os_GetExecutionTime ((OSServiceIdType)30)
#define OSServiceId_Os_GetISRMaxExecutionTime ((OSServiceIdType)31)
#define OSServiceId_Os_GetTaskActivationTime ((OSServiceIdType)32)
#define OSServiceId_Os_GetTaskMaxExecutionTime ((OSServiceIdType)33)
#define OSServiceId_Os_ResetISRMaxExecutionTime ((OSServiceIdType)34)
#define OSServiceId_Os_ResetTaskMaxExecutionTime ((OSServiceIdType)35)
#define OSServiceId_Os_GetElapsedTime ((OSServiceIdType)36)
#define OSServiceId_Os_GetTaskElapsedTime ((OSServiceIdType)37)
#define OSServiceId_Os_GetISRElapsedTime ((OSServiceIdType)38)
#define OSServiceId_Os_GetIdleElapsedTime ((OSServiceIdType)39)
#define OSServiceId_Os_ResetTaskElapsedTime ((OSServiceIdType)40)
#define OSServiceId_Os_ResetISRElapsedTime ((OSServiceIdType)41)
#define OSServiceId_Os_ResetIdleElapsedTime ((OSServiceIdType)42)
#define OSServiceId_Os_GetStackSize ((OSServiceIdType)43)
#define OSServiceId_Os_GetStackUsage ((OSServiceIdType)44)
#define OSServiceId_Os_GetStackValue ((OSServiceIdType)45)
#define OSServiceId_Os_GetISRMaxStackUsage ((OSServiceIdType)46)
#define OSServiceId_Os_GetTaskMaxStackUsage ((OSServiceIdType)47)
#define OSServiceId_Os_ResetISRMaxStackUsage ((OSServiceIdType)48)
#define OSServiceId_Os_ResetTaskMaxStackUsage ((OSServiceIdType)49)
#define OSServiceId_ReleaseResource ((OSServiceIdType)50)
#define OSServiceId_Restart ((OSServiceIdType)51)
#define OSServiceId_ResumeAllInterrupts ((OSServiceIdType)52)
#define OSServiceId_ResumeOSInterrupts ((OSServiceIdType)53)
#define OSServiceId_Schedule ((OSServiceIdType)54)
#define OSServiceId_SetEvent ((OSServiceIdType)55)
#define OSServiceId_SetAbsAlarm ((OSServiceIdType)56)
#define OSServiceId_SetRelAlarm ((OSServiceIdType)57)
#define OSServiceId_SetRestartPoint ((OSServiceIdType)58)
#define OSServiceId_ShutdownOS ((OSServiceIdType)59)
#define OSServiceId_StartOS ((OSServiceIdType)60)
#define OSServiceId_StartScheduleTableAbs ((OSServiceIdType)61)
#define OSServiceId_StartScheduleTableRel ((OSServiceIdType)62)
#define OSServiceId_StartScheduleTableSynchron ((OSServiceIdType)63)
#define OSServiceId_SyncScheduleTable ((OSServiceIdType)64)
#define OSServiceId_SyncScheduleTableRel ((OSServiceIdType)65)
#define OSServiceId_SetScheduleTableAsync ((OSServiceIdType)66)
#define OSServiceId_StopScheduleTable ((OSServiceIdType)67)
#define OSServiceId_SuspendAllInterrupts ((OSServiceIdType)68)
#define OSServiceId_SuspendOSInterrupts ((OSServiceIdType)69)
#define OSServiceId_TerminateApplication ((OSServiceIdType)70)
#define OSServiceId_TerminateTask ((OSServiceIdType)71)
#define OSServiceId_WaitEvent ((OSServiceIdType)72)
#define OSServiceId_AllowAccess ((OSServiceIdType)73)
#define OSServiceId_GetApplicationState ((OSServiceIdType)74)

typedef unsigned int Os_BiggestType;

#ifndef OS_NAMESPACE_PURE
#define GetExecutionTime Os_GetExecutionTime
#define GetTaskMaxExecutionTime Os_GetTaskMaxExecutionTime
#define GetISRMaxExecutionTime Os_GetISRMaxExecutionTime
#define ResetTaskMaxExecutionTime Os_ResetTaskMaxExecutionTime
#define ResetISRMaxExecutionTime Os_ResetISRMaxExecutionTime
#define GetStackUsage Os_GetStackUsage
#define GetTaskMaxStackUsage Os_GetTaskMaxStackUsage
#define GetISRMaxStackUsage Os_GetISRMaxStackUsage
#define ResetTaskMaxStackUsage Os_ResetTaskMaxStackUsage
#define ResetISRMaxStackUsage Os_ResetISRMaxStackUsage
#define GetStackValue Os_GetStackValue
#define GetStackSize Os_GetStackSize
#define AdvanceCounter Os_AdvanceCounter
#define Restart Os_Restart
#define SetRestartPoint Os_SetRestartPoint
#endif

#define ActivateTask Os_ActivateTask
#define GetTaskID Os_GetTaskID
#define GetTaskState Os_GetTaskState
#define Schedule() Os_Schedule()
#define ChainTask Os_ChainTask
#define TerminateTask Os_TerminateTask
#define SetEvent   Os_SetEvent
#define ClearEvent Os_ClearEvent
#define GetEvent   Os_GetEvent
#define WaitEvent  Os_WaitEvent
#define GetResource  Os_GetResource
#define ReleaseResource  Os_ReleaseResource
#define DisableAllInterrupts Os_DisableAllInterrupts
#define EnableAllInterrupts Os_EnableAllInterrupts
#define SuspendAllInterrupts Os_SuspendAllInterrupts
#define ResumeAllInterrupts Os_ResumeAllInterrupts
#define SuspendOSInterrupts Os_SuspendOSInterrupts
#define ResumeOSInterrupts Os_ResumeOSInterrupts
#define GetISRID Os_GetISRID
#define GetActiveApplicationMode Os_GetActiveApplicationMode
#define CheckObjectOwnership(x,y) Os_CheckObjectOwnership(x,(Os_AnyType)y)
#define CheckObjectAccess(x,y,z) Os_CheckObjectAccess(x,y,(Os_AnyType)z)
#define GetApplicationID Os_GetApplicationID
#define GetCurrentApplicationID Os_GetCurrentApplicationID
#define CallTrustedFunction Os_CallTrustedFunction
#define GetApplicationState Os_GetApplicationState
#define AllowAccess Os_AllowAccess
#define CheckTaskMemoryAccess(x,y,z) Os_CheckTaskMemoryAccess(x,(MemoryStartAddressType)y,z)
#define CheckISRMemoryAccess(x,y,z) Os_CheckISRMemoryAccess(x,(MemoryStartAddressType)y,z)
#define GetCounterValue Os_GetCounterValue
#define GetElapsedCounterValue Os_GetElapsedCounterValue
#define GetElapsedValue Os_GetElapsedCounterValue
#define IncrementCounter Os_IncrementCounter
#define GetAlarmBase Os_GetAlarmBase
#define CancelAlarm Os_CancelAlarm
#define GetAlarm Os_GetAlarm
#define SetRelAlarm Os_SetRelAlarm
#define SetAbsAlarm Os_SetAbsAlarm
#define StopScheduleTable Os_StopScheduleTable
#define StartScheduleTableRel Os_StartScheduleTableRel
#define StartScheduleTableAbs Os_StartScheduleTableAbs
#define StartScheduleTableSynchron Os_StartScheduleTableSynchron
#define SyncScheduleTable Os_SyncScheduleTable
#define SetScheduleTableAsync Os_SetScheduleTableAsync
#define GetScheduleTableStatus Os_GetScheduleTableStatus
#define NextScheduleTable Os_NextScheduleTable
#define Os_SetRestartPoint() ( (OS_NOAPPMODE == Os_CurrentAppMode) ? (Os_setjmp(Os_RestartJumpBuf), Os_Restartable = TRUE, E_OK) : E_OS_SYS_NO_RESTART)
#define StartOS(x) {Os_StackBase = Os_GetSP(); if(Os_StartOS(x)) {while(Os_Cbk_Idle()) {}; while((1)) {}}}
#define ShutdownOS Os_ShutdownOS
#define ControlIdle Os_ControlIdle

typedef StatusType   Os_TraceStatusType;

#ifndef OS_TRACE
#define Os_EnableTraceClasses(x)
#define Os_DisableTraceClasses(x)
#define Os_EnableTraceCategories(x)
#define Os_DisableTraceCategories(x)
#define Os_StartFreeRunningTrace()
#define Os_StartBurstingTrace()
#define Os_StartTriggeringTrace()
#define Os_StopTrace()
#define Os_CheckTraceOutput()
#define Os_SetTraceRepeat(x)
#define Os_TraceCommInit()
#define Os_UploadTraceData()
#define Os_TraceDumpAsync(x)
#define Os_SetTriggerConditions(x,y)
#define Os_SetTriggerConditionsN(x,y)
#define Os_SetTriggerConditionsTII(x,y)
#define Os_SetTriggerWindow(x,y)
#define Os_TriggerNow()
#endif

#define Os_ClearTrigger()              Os_SetTriggerConditions(OS_TRACE_TRIGGER, 0)
#define OS_TRACE_TRIGGER_ANY (&Os_TraceDummy)
#define Os_Cat1_OS_TRACE_TRIGGER_ANY (0)
#define Os_Tr_OS_TRACE_TRIGGER_ANY (0)
#define Os_TriggerOnActivation(x)      Os_SetTriggerConditions(OS_TRACE_ACTIVATION,     (x)->id)
#define Os_TriggerOnChain(x)           Os_SetTriggerConditions(OS_TRACE_CHAINACTIVATION,(x)->id)
#define Os_TriggerOnTaskStart(x)       Os_SetTriggerConditions(OS_TRACE_TASKSTART,     (x)->id)
#define Os_TriggerOnTaskStop(x)        Os_SetTriggerConditions(OS_TRACE_TASKEND,     (x)->id)
#define Os_TriggerOnCat1ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,(Os_Cat1_##x))
#define Os_TriggerOnCat1ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,  (Os_Cat1_##x))
#define Os_TriggerOnCat2ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,     (x)->id)
#define Os_TriggerOnCat2ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,     (x)->id)
#define Os_TriggerOnGetResource(x)     Os_SetTriggerConditions(OS_TRACE_GETRESOURCE,    (x)->id)
#define Os_TriggerOnReleaseResource(x) Os_SetTriggerConditions(OS_TRACE_RELEASERESOURCE,(x)->id)
#define Os_TriggerOnSetEvent(x)        Os_SetTriggerConditions(OS_TRACE_SETEVENT,     (x)->id)
#define Os_TriggerOnTracepoint(x)      Os_SetTriggerConditionsTII(OS_TRACE_POINT,     (x))
#define Os_TriggerOnTaskTracepoint(x,y) Os_SetTriggerConditions(OS_TRACE_TASKPOINT+(x),(y)->id)
#define Os_TriggerOnIntervalStart(x)   Os_SetTriggerConditionsTII(OS_TRACE_STARTINTERVAL,(x))
#define Os_TriggerOnIntervalEnd(x)     Os_SetTriggerConditionsTII(OS_TRACE_ENDINTERVAL,  (x))
#define Os_TriggerOnIntervalStop(x)    Os_TriggerOnIntervalEnd(x)
#define Os_TriggerOnAlarmExpiry(x)     Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x))
#define Os_TriggerOnError(x)           Os_SetTriggerConditionsN(OS_TRACE_ERROR, (x))
#define Os_TriggerOnShutdown(x)        Os_SetTriggerConditionsN(OS_TRACE_SHUTDOWN, (x))
#define Os_TriggerOnScheduleTableExpiry(x) Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x))
#define Os_TriggerOnIncrementCounter(x) Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x))
#define Os_TriggerOnAdvanceCounter(x)   Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x))

#ifndef OS_TRACE_NAMESPACE_PURE
#define EnableTraceClasses Os_EnableTraceClasses
#define DisableTraceClasses Os_DisableTraceClasses
#define EnableTraceCategories Os_EnableTraceCategories
#define DisableTraceCategories Os_DisableTraceCategories
#define StartFreeRunningTrace Os_StartFreeRunningTrace
#define StartBurstingTrace Os_StartBurstingTrace
#define StartTriggeringTrace Os_StartTriggeringTrace
#define StopTrace Os_StopTrace
#define CheckTraceOutput Os_CheckTraceOutput
#define SetTraceRepeat Os_SetTraceRepeat
#define SetTriggerConditions Os_SetTriggerConditions
#define TraceCommInit Os_TraceCommInit
#define TraceCommInitTarget Os_Cbk_TraceCommInitTarget
#define TraceCommDataReady Os_Cbk_TraceCommDataReady
#define UploadTraceData Os_UploadTraceData
#define SetTriggerWindow Os_SetTriggerWindow
#define ClearTrigger Os_ClearTrigger
#define TriggerNow  Os_TriggerNow
#define TriggerOnActivation Os_TriggerOnActivation
#define TriggerOnChain Os_TriggerOnChain
#define TriggerOnTaskStart Os_TriggerOnTaskStart
#define TriggerOnTaskStop Os_TriggerOnTaskStop
#define TriggerOnCat1ISRStart Os_TriggerOnCat1ISRStart
#define TriggerOnCat1ISRStop Os_TriggerOnCat1ISRStop
#define TriggerOnCat2ISRStart Os_TriggerOnCat2ISRStart
#define TriggerOnCat2ISRStop Os_TriggerOnCat2ISRStop
#define TriggerOnGetResource Os_TriggerOnGetResource
#define TriggerOnReleaseResource Os_TriggerOnReleaseResource
#define TriggerOnSetEvent Os_TriggerOnSetEvent
#define TriggerOnTracepoint Os_TriggerOnTracepoint
#define TriggerOnIntervalStart Os_TriggerOnIntervalStart
#define TriggerOnIntervalEnd Os_TriggerOnIntervalEnd
#define TriggerOnIntervalStop Os_TriggerOnIntervalStop
#define TriggerOnTaskTracepoint Os_TriggerOnTaskTracepoint
#define TriggerOnAlarmExpiry Os_TriggerOnAlarmExpiry
#define TriggerOnScheduleTableExpiry Os_TriggerOnScheduleTableExpiry
#define TriggerOnIncrementCounter Os_TriggerOnIncrementCounter
#define TriggerOnAdvanceCounter Os_TriggerOnAdvanceCounter
#define TriggerOnError Os_TriggerOnError
#define TriggerOnShutdown Os_TriggerOnShutdown
#endif

#define OS_START_SEC_OS_CBK_TRACECOMMDATAREADY_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_TRACECOMMDATAREADY_CODE) Os_Cbk_TraceCommDataReady(void) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMDATAREADY_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TRACECOMMINITTARGET_CODE
#include "Os_MemMap.hpp"
extern FUNC(Os_TraceStatusType, OS_OS_CBK_TRACECOMMINITTARGET_CODE) Os_Cbk_TraceCommInitTarget(void) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMINITTARGET_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TRACECOMMTXBYTE_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_TRACECOMMTXBYTE_CODE) Os_Cbk_TraceCommTxByte(uint8 val) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXBYTE_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TRACECOMMTXEND_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_TRACECOMMTXEND_CODE) Os_Cbk_TraceCommTxEnd(void) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXEND_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TRACECOMMTXREADY_CODE
#include "Os_MemMap.hpp"
extern FUNC(boolean, OS_OS_CBK_TRACECOMMTXREADY_CODE) Os_Cbk_TraceCommTxReady(void) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXREADY_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TRACECOMMTXSTART_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_TRACECOMMTXSTART_CODE) Os_Cbk_TraceCommTxStart(void) ;
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXSTART_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_CODE_LIB
#include "Os_MemMap.hpp"
extern FUNC(void, OS_CODE) Os_GetVersionInfo(Std_VersionInfoType *versioninfo) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetExecutionTime(void) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskMaxExecutionTime(TaskType TaskID) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRMaxExecutionTime(ISRType ISRID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxExecutionTime(TaskType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxExecutionTime(ISRType ISRID) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetElapsedTime(void) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskElapsedTime(TaskType TaskID) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRElapsedTime(ISRType ISRID) ;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetIdleElapsedTime(Os_IdleType IdleID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskElapsedTime(TaskType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetISRElapsedTime(ISRType ISRID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetIdleElapsedTime(Os_IdleType IdleID) ;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackUsage(void) ;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetTaskMaxStackUsage(TaskType TaskID) ;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetISRMaxStackUsage(ISRType ISRID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxStackUsage(TaskType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxStackUsage(ISRType ISRID) ;
extern FUNC(Os_StackValueType, OS_CODE) Os_GetStackValue(void) ;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackSize(Os_StackValueType Base, Os_StackValueType Sample) ;
extern FUNC(StatusType, OS_CODE) Os_ActivateTask(TaskType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_GetTaskID(TaskRefType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_GetTaskState(TaskType TaskID, TaskStateRefType State) ;
extern FUNC(StatusType, OS_CODE) Os_Schedule(void) ;
extern FUNC(StatusType, OS_CODE) Os_SetEvent(TaskType TaskID, EventMaskType Mask) ;
extern FUNC(StatusType, OS_CODE) Os_ClearEvent(EventMaskType Mask) ;
extern FUNC(StatusType, OS_CODE) Os_GetEvent(TaskType TaskID, EventMaskRefType Mask) ;
extern FUNC(StatusType, OS_CODE) Os_WaitEvent(EventMaskType Mask) ;
extern FUNC(StatusType, OS_CODE) Os_GetResource(ResourceType ResID) ;
extern FUNC(StatusType, OS_CODE) Os_ReleaseResource(ResourceType ResID) ;
extern FUNC(void, OS_CODE) Os_DisableAllInterrupts(void) ;
extern FUNC(void, OS_CODE) Os_EnableAllInterrupts(void) ;
extern FUNC(void, OS_CODE) Os_SuspendAllInterrupts(void) ;
extern FUNC(void, OS_CODE) Os_ResumeAllInterrupts(void) ;
extern FUNC(void, OS_CODE) Os_SuspendOSInterrupts(void) ;
extern FUNC(void, OS_CODE) Os_ResumeOSInterrupts(void) ;
extern FUNC(ISRType, OS_CODE) Os_GetISRID(void) ;
extern FUNC(Type_SwcServiceOs_tModeApp, OS_CODE) Os_GetActiveApplicationMode(void) ;
extern FUNC(ApplicationType, OS_CODE) Os_CheckObjectOwnership(ObjectTypeType ObjectType, Os_AnyType Object) ;
extern FUNC(ObjectAccessType, OS_CODE) Os_CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, Os_AnyType Object) ;
extern FUNC(ApplicationType, OS_CODE) Os_GetApplicationID(void) ;
extern FUNC(ApplicationType, OS_CODE) Os_GetCurrentApplicationID(void) ;
extern FUNC(StatusType, OS_CODE) Os_TerminateTask(void) ;
extern FUNC(AccessType, OS_CODE) Os_CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size) ;
extern FUNC(AccessType, OS_CODE) Os_CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size) ;
extern FUNC(StatusType, OS_CODE) Os_GetCounterValue(CounterType CounterID, TickRefType Value) ;
extern FUNC(StatusType, OS_CODE) Os_GetElapsedCounterValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue) ;
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter(CounterType CounterID) ;
extern FUNC(StatusType, OS_CODE) Os_AdvanceCounter(CounterType CounterID) ;
extern FUNC(StatusType, OS_CODE) Os_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info) ;
extern FUNC(StatusType, OS_CODE) Os_CancelAlarm(AlarmType AlarmID) ;
extern FUNC(StatusType, OS_CODE) Os_GetAlarm(AlarmType AlarmID, TickRefType Tick) ;
extern FUNC(StatusType, OS_CODE) Os_SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle) ;
extern FUNC(StatusType, OS_CODE) Os_SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle) ;
extern FUNC(StatusType, OS_CODE) Os_StopScheduleTable(ScheduleTableType ScheduleTableID) ;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset) ;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start) ;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableSynchron(ScheduleTableType ScheduleTableID) ;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value) ;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTableRel(ScheduleTableType ScheduleTableID, SignedTickType RelativeValue) ;
extern FUNC(StatusType, OS_CODE) Os_SetScheduleTableAsync(ScheduleTableType ScheduleTableID) ;
extern FUNC(StatusType, OS_CODE) Os_GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus) ;
extern FUNC(StatusType, OS_CODE) Os_NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To) ;
extern FUNC(boolean, OS_CODE) Os_StartOS(Type_SwcServiceOs_tModeApp Mode) ;
extern FUNC(void, OS_CODE) Os_ShutdownOS(StatusType Error) ;
extern FUNC(void, OS_CODE) Os_ProtectionLog(StatusType os_status);
extern FUNC(StatusType, OS_CODE) Os_ControlIdle(CoreIdType CoreID, IdleModeType IdleMode) ;
extern FUNC(IdleModeType, OS_CODE) Os_CurrentIdleMode(void);
extern FUNC(uint32, OS_CODE) Os_GetCurrentTPL(void) ;
extern FUNC(Os_imaskType, OS_CODE) Os_GetCurrentIMask(void) ;
extern FUNC(StatusType, OS_CODE) Os_Restart(void) ;
extern FUNC(StatusType, OS_CODE) Os_ChainTask(TaskType TaskID) ;
extern FUNC(StatusType, OS_CODE) Os_GetApplicationState(ApplicationType Application, ApplicationStateRefType Value) ;
extern FUNC(StatusType, OS_CODE) Os_AllowAccess(void) ;
extern FUNC(StatusType, OS_CODE) Os_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams) ;
#define OS_STOP_SEC_CODE_LIB
#include "Os_MemMap.hpp"

#define OS_START_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.hpp"
extern CONST(CoreIdType, OS_CONST_FAST) TotalNumberOfCores;
extern CONST(Os_ApplicationConfigurationType, OS_CONST_FAST) Os_const_applications[];
extern CONST(Os_ISRType, OS_CONST_FAST) Os_const_isrs[];
extern CONST(TaskType, OS_CONST_FAST) Os_const_tasks[];
extern CONST(Os_AlarmType, OS_CONST_FAST) Os_const_alarms[];
extern CONST(Os_CounterType, OS_CONST_FAST) Os_const_counters[];
extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks0[];
#define OS_STOP_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.hpp"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.hpp"
extern CONST(Os_AlarmCallbackType, OS_CONST) Os_const_counter_callbacks[];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.hpp"

#define OS_START_SEC_ERRORHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error) ;
#define OS_STOP_SEC_ERRORHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_CHECKMEMORYACCESS_CODE
#include "Os_MemMap.hpp"
extern FUNC(AccessType, OS_OS_CBK_CHECKMEMORYACCESS_CODE) Os_Cbk_CheckMemoryAccess(ApplicationType Application, TaskType TaskID, ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
#define OS_STOP_SEC_OS_CBK_CHECKMEMORYACCESS_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_CHECKSTACKDEPTH_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_CHECKSTACKDEPTH_CODE) Os_Cbk_CheckStackDepth(CoreIdType Core_id, Os_StackSizeType Depth, Os_StackSizeType CurrentPos);
#define OS_STOP_SEC_OS_CBK_CHECKSTACKDEPTH_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_GETSTOPWATCH_CODE
#include "Os_MemMap.hpp"
#ifndef Os_Cbk_GetStopwatch
 extern FUNC(Os_StopwatchTickType, OS_OS_CBK_GETSTOPWATCH_CODE) Os_Cbk_GetStopwatch(void) ;
#endif
#define OS_STOP_SEC_OS_CBK_GETSTOPWATCH_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.hpp"
extern FUNC(boolean, OS_OS_CBK_IDLE_CODE) Os_Cbk_Idle(void) ;
#define OS_STOP_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_INSHUTDOWN_CODE) Os_Cbk_InShutdown(void) ;
#define OS_STOP_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_STACKOVERRUNHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_STACKOVERRUNHOOK_CODE) Os_Cbk_StackOverrunHook(Os_StackSizeType Overrun, Os_StackOverrunType Reason);
#define OS_STOP_SEC_OS_CBK_STACKOVERRUNHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_OS_CBK_TIMEOVERRUNHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_OS_CBK_TIMEOVERRUNHOOK_CODE) Os_Cbk_TimeOverrunHook(Os_StopwatchTickType Overrun) ;
#define OS_STOP_SEC_OS_CBK_TIMEOVERRUNHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_POSTTASKHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_POSTTASKHOOK_CODE) PostTaskHook(void) ;
#define OS_STOP_SEC_POSTTASKHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_PRETASKHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_PRETASKHOOK_CODE) PreTaskHook(void) ;
#define OS_STOP_SEC_PRETASKHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_PROTECTIONHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(ProtectionReturnType, OS_PROTECTIONHOOK_CODE) ProtectionHook(StatusType FatalError) ;
#define OS_STOP_SEC_PROTECTIONHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Error) ;
#define OS_STOP_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.hpp"
extern FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void) ;
#define OS_STOP_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.hpp"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.hpp"
extern VAR(uint32, OS_VAR_CLEARED) Os_DisableAllCount;
extern VAR(uint32, OS_VAR_CLEARED) Os_SuspendAllCount;
extern VAR(uint32, OS_VAR_CLEARED) Os_SuspendOSCount;
extern VAR(boolean, OS_VAR_CLEARED) Os_Restartable;
extern OS_VOLATILE VAR(Type_SwcServiceOs_tModeApp, OS_VAR_CLEARED) Os_CurrentAppMode;
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.hpp"

#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.hpp"
extern OS_VOLATILE VAR(Os_psetType, OS_VAR_NO_INIT) Os_ReadyTasks ;
extern OS_VOLATILE VAR(ISRType, OS_VAR_NO_INIT) Os_RunningISR;
extern OS_VOLATILE VAR(TaskType, OS_VAR_NO_INIT) Os_RunningTask;
extern OS_VOLATILE VAR(Os_tpmaskType, OS_VAR_NO_INIT) Os_RunningTPMask ;
extern VAR(Os_MeterInfoRefType, OS_VAR_NO_INIT) Os_CurrentMeteredObject;
extern VAR(Os_MeterInfoType, OS_VAR_NO_INIT) Os_IdleMeter;
extern OS_VOLATILE VAR(ApplicationType, OS_VAR_NO_INIT) Os_AppOverride;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_DisableAllImask;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_SuspendAllImask;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_SuspendOSImask;
extern VAR(Os_jmp_buf, OS_VAR_NO_INIT) Os_RestartJumpBuf;
extern VAR(Os_StackValueType, OS_VAR_NO_INIT) Os_StackBase;
extern VAR(ApplicationStateType, OS_VAR_NO_INIT) Os_dyn_appstate[];
extern VAR(Os_TaskDynType, OS_VAR_NO_INIT) Os_dyn_tasks[];
extern VAR(Os_ISRDynType, OS_VAR_NO_INIT) Os_dyn_isrs[];
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.hpp"

#include "Os_Cfg.hpp"
#endif
