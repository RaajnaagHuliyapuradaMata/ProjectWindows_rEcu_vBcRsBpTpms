#ifndef OS_CFG_H
#define OS_CFG_H

#define OS_TARGET_RH850GHS
#define OS_NUM_APPMODES (2U)
#define OS_NUM_APPLICATIONS (1U)
#define OS_NUM_SPINLOCKS (0U)
#define OS_NUM_TRUSTED_FUNCTIONS (0U)
#define OS_NUM_IOC_CALLBACK_FUNCTIONS (Os_const_ioc_function_count)
#define OS_NUM_EVENTS (0U)
#define OS_NUM_TASKS (7U)
#define OS_NUM_ISRS (13U)
#define OS_NUM_RESOURCES (0U)
#define OS_NUM_ALARMS (4U)
#define OS_NUM_SCHEDULETABLES (0U)
#define OS_NUM_TRACEPOINTS (1U)
#define OS_NUM_TASKTRACEPOINTS (0U)
#define OS_NUM_INTERVALS (0U)
#define OS_NUM_TRACECATEGORIES (0U)
#define OS_TRACE_CATEGORY_ALWAYS ((Os_TraceCategoriesType)(0x80000000UL))
#define OS_TRACE_CATEGORY_NEVER  ((Os_TraceCategoriesType)(0x00000000UL))
#define OS_NUM_COUNTERS (1U)
#define OSCYCLEDURATION (12.5)
#define OSCYCLESPERSECOND (80000000U)
#define OSSWTICKDURATION (25)
#define OSSWTICKSPERSECOND (40000000U)
#define OS_TICKS2NS_OneMillisecondCounter(ticks) ((PhysicalTimeType)((ticks) * 1000000U))
#define OS_TICKS2US_OneMillisecondCounter(ticks) ((PhysicalTimeType)((ticks) * 1000U))
#define OS_TICKS2MS_OneMillisecondCounter(ticks) ((PhysicalTimeType)((ticks) * 1U))
#define OS_TICKS2SEC_OneMillisecondCounter(ticks) ((PhysicalTimeType)((ticks) / 1000U))
#define OSMAXALLOWEDVALUE_OneMillisecondCounter (65535U)
#define OSTICKSPERBASE_OneMillisecondCounter (1U)
#define OSTICKDURATION_OneMillisecondCounter OS_TICKS2NS_OneMillisecondCounter(1U)
#define OSMINCYCLE_OneMillisecondCounter (1U)
#define OSMAXALLOWEDVALUE OSMAXALLOWEDVALUE_SystemCounter
#define OSTICKSPERBASE OSTICKSPERBASE_SystemCounter
#define OSMINCYCLE OSMINCYCLE_SystemCounter
#define OSTICKDURATION OSTICKDURATION_SystemCounter
#define OS_NUM_CORES (1U)
#define OS_NUM_OS_CORES (1U)
#define OS_CORE_ID_MASTER (0U)

extern FUNC(StatusType, OS_CODE) Os_IncrementCounter_OneMillisecondCounter(void);
extern FUNC(void, OS_CODE) Os_Entry_CyclicTask1sec(void);
extern FUNC(void, OS_CODE) Os_Entry_CyclicTask50ms(void);
extern FUNC(void, OS_CODE) Os_Entry_CyclicTask200ms(void);
extern FUNC(void, OS_CODE) Os_Entry_CyclicTask10ms(void);
extern FUNC(void, OS_CODE) Os_Entry_CanRecTask(void);
extern FUNC(void, OS_CODE) Os_Entry_TelRecTask(void);
extern FUNC(void, OS_CODE) Os_Entry_InitTask(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Timer0(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Timer1(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Timer2(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Timer3(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_VoltageMonitor(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Wakeup(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Can0Status(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_CanGlobalStatus(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Can0Transmit(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_Can0Receive(void);
extern FUNC(void, OS_CODE) Os_Entry_FLS_FLENDNM_CAT2_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_OneMillisecond(void);
extern FUNC(void, OS_CODE) Os_Entry_CAT2ISR_TelRec(void);
extern FUNC(void, OS_ERRORHOOK_HUFTPMS_CODE) ErrorHook_HufTpms(StatusType Error) ;
extern FUNC(void, OS_OS_CBK_ALARM_CB_ALARM10MS_CODE) Os_Cbk_Alarm_CB_Alarm10ms(void);
extern FUNC(void, OS_OS_CBK_ALARM_CB_ALARM200MS_CODE) Os_Cbk_Alarm_CB_Alarm200ms(void);
extern FUNC(void, OS_OS_CBK_ALARM_CB_ALARM50MS_CODE) Os_Cbk_Alarm_CB_Alarm50ms(void);
extern FUNC(void, OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE) Os_Cbk_Alarm_CB_AlarmOneSecond(void);
extern FUNC(void, OS_SHUTDOWNHOOK_HUFTPMS_CODE) ShutdownHook_HufTpms(StatusType Error) ;
extern FUNC(void, OS_STARTUPHOOK_HUFTPMS_CODE) StartupHook_HufTpms(void) ;

#define OS_STACK_MONITORING
#define HufTpms ((ApplicationType)1U)

#define CyclicTask1sec (&Os_const_tasks0[0])
#define OS_TPL_FOR_CyclicTask1sec (0U)
#define OS_IMASK_FOR_CyclicTask1sec (0x00U)
DeclareTask(CyclicTask1sec)
#define CyclicTask50ms (&Os_const_tasks0[1])
#define OS_TPL_FOR_CyclicTask50ms (1U)
#define OS_IMASK_FOR_CyclicTask50ms (0x00U)
DeclareTask(CyclicTask50ms)
#define CyclicTask200ms (&Os_const_tasks0[2])
#define OS_TPL_FOR_CyclicTask200ms (2U)
#define OS_IMASK_FOR_CyclicTask200ms (0x00U)
DeclareTask(CyclicTask200ms)
#define CyclicTask10ms (&Os_const_tasks0[3])
#define OS_TPL_FOR_CyclicTask10ms (3U)
#define OS_IMASK_FOR_CyclicTask10ms (0x00U)
DeclareTask(CyclicTask10ms)
#define CanRecTask (&Os_const_tasks0[4])
#define OS_TPL_FOR_CanRecTask (4U)
#define OS_IMASK_FOR_CanRecTask (0x00U)
DeclareTask(CanRecTask)
#define TelRecTask (&Os_const_tasks0[5])
#define OS_TPL_FOR_TelRecTask (5U)
#define OS_IMASK_FOR_TelRecTask (0x00U)
DeclareTask(TelRecTask)
#define InitTask (&Os_const_tasks0[6])
#define OS_TPL_FOR_InitTask (6U)
#define OS_IMASK_FOR_InitTask (0x00U)
DeclareTask(InitTask)

#define OS_TPL_FOR_TASK(n) OS_TPL_FOR_##n

#define OS_IMASK_FOR_TASK(n) OS_IMASK_FOR_##n

#define CAT2ISR_Timer0 (&Os_const_isrs[0U])
#define OS_IMASK_FOR_CAT2ISR_Timer0 (0x80U)
DeclareISR(CAT2ISR_Timer0)
#define CAT2ISR_Timer1 (&Os_const_isrs[1U])
#define OS_IMASK_FOR_CAT2ISR_Timer1 (0x80U)
DeclareISR(CAT2ISR_Timer1)
#define CAT2ISR_Timer2 (&Os_const_isrs[2U])
#define OS_IMASK_FOR_CAT2ISR_Timer2 (0x80U)
DeclareISR(CAT2ISR_Timer2)
#define CAT2ISR_Timer3 (&Os_const_isrs[3U])
#define OS_IMASK_FOR_CAT2ISR_Timer3 (0x80U)
DeclareISR(CAT2ISR_Timer3)
#define CAT2ISR_VoltageMonitor (&Os_const_isrs[4U])
#define OS_IMASK_FOR_CAT2ISR_VoltageMonitor (0x80U)
DeclareISR(CAT2ISR_VoltageMonitor)
#define CAT2ISR_Wakeup (&Os_const_isrs[5U])
#define OS_IMASK_FOR_CAT2ISR_Wakeup (0xC0U)
DeclareISR(CAT2ISR_Wakeup)
#define CAT2ISR_Can0Status (&Os_const_isrs[6U])
#define OS_IMASK_FOR_CAT2ISR_Can0Status (0xE0U)
DeclareISR(CAT2ISR_Can0Status)
#define CAT2ISR_CanGlobalStatus (&Os_const_isrs[7U])
#define OS_IMASK_FOR_CAT2ISR_CanGlobalStatus (0xF0U)
DeclareISR(CAT2ISR_CanGlobalStatus)
#define CAT2ISR_Can0Transmit (&Os_const_isrs[8U])
#define OS_IMASK_FOR_CAT2ISR_Can0Transmit (0xF8U)
DeclareISR(CAT2ISR_Can0Transmit)
#define CAT2ISR_Can0Receive (&Os_const_isrs[9U])
#define OS_IMASK_FOR_CAT2ISR_Can0Receive (0xFCU)
DeclareISR(CAT2ISR_Can0Receive)
#define FLS_FLENDNM_CAT2_ISR (&Os_const_isrs[10U])
#define OS_IMASK_FOR_FLS_FLENDNM_CAT2_ISR (0xFCU)
DeclareISR(FLS_FLENDNM_CAT2_ISR)
#define CAT2ISR_OneMillisecond (&Os_const_isrs[11U])
#define OS_IMASK_FOR_CAT2ISR_OneMillisecond (0xFEU)
DeclareISR(CAT2ISR_OneMillisecond)
#define CAT2ISR_TelRec (&Os_const_isrs[12U])
#define OS_IMASK_FOR_CAT2ISR_TelRec (0xFFU)
DeclareISR(CAT2ISR_TelRec)

#define OS_IMASK_FOR_ISR(n) OS_IMASK_FOR_##n

#define OneMillisecondCounter (&Os_const_counters[0U])
DeclareCounter(OneMillisecondCounter)

#define Alarm10ms (0U)
DeclareAlarm(Alarm10ms)
#define Alarm1sec (1U)
DeclareAlarm(Alarm1sec)
#define Alarm200ms (2U)
DeclareAlarm(Alarm200ms)
#define Alarm50ms (3U)
DeclareAlarm(Alarm50ms)

#define OSApp_HufTpms (1U)
#define Os_LogTracepoint(TpointID,Category)
#define Os_LogTracepointValue(TpointID,Value,Category)
#define Os_LogTracepointData(TpointID,Data,Length,Category)
#define Os_LogTaskTracepoint(TTpointID,Category)
#define Os_LogTaskTracepointValue(TTpointID,Value,Category)
#define Os_LogTaskTracepointData(TTpointID,Data,Length,Category)
#define Os_LogIntervalStart(IntervalID,Category)
#define Os_LogIntervalStartValue(IntervalID,Value,Category)
#define Os_LogIntervalStartData(IntervalID,Data,Length,Category)
#define Os_LogIntervalEnd(IntervalID,Category)
#define Os_LogIntervalEndValue(IntervalID,Value,Category)
#define Os_LogIntervalEndData(IntervalID,Data,Length,Category)
#ifndef OS_TRACE_NAMESPACE_PURE
#define LogTracepoint(TpointID,Category) Os_LogTracepoint(TpointID,Category)
#define LogTracepointValue(TpointID,Value,Category) Os_LogTracepointValue(TpointID,Value,Category)
#define LogTracepointData(TpointID,Data,Length,Category) Os_LogTracepointData(TpointID,Data,Length,Category)
#define LogTaskTracepoint(TTpointID,Category) Os_LogTaskTracepoint(TTpointID,Category)
#define LogTaskTracepointValue(TTpointID,Value,Category) Os_LogTaskTracepointValue(TTpointID,Value,Category)
#define LogTaskTracepointData(TTpointID,Data,Length,Category) Os_LogTaskTracepointData(TTpointID,Data,Length,Category)
#define LogIntervalStart(IntervalID,Category) Os_LogIntervalStart(IntervalID,Category)
#define LogIntervalStartValue(IntervalID,Value,Category) Os_LogIntervalStartValue(IntervalID,Value,Category)
#define LogIntervalStartData(IntervalID,Data,Length,Category) Os_LogIntervalStartData(IntervalID,Data,Length,Category)
#define LogIntervalEnd(IntervalID,Category) Os_LogIntervalEnd(IntervalID,Category)
#define LogIntervalEndValue(IntervalID,Value,Category) Os_LogIntervalEndValue(IntervalID,Value,Category)
#define LogIntervalEndData(IntervalID,Data,Length,Category) Os_LogIntervalEndData(IntervalID,Data,Length,Category)
#endif

#endif
