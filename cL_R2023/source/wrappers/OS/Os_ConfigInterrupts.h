

#ifndef OS_CONFIGINTERRUPTS_H
#define OS_CONFIGINTERRUPTS_H

void __SET1(volatile char *addr, __ghs_c_int__ bitnum);
void __CLR1(volatile char *addr, __ghs_c_int__ bitnum);
#define OS_SET1(addr, bit) __SET1(addr, bit)
#define OS_CLR1(addr, bit) __CLR1(addr, bit)

#define OS_ICR_INTERRUPT_CLEARED ((uint16)(0x1000U))
#define OS_ICR_EIMK 7U

#define Os_IntChannel_INTADCA0I0 (10U)
#define Os_IntChannel_CAT2ISR_VoltageMonitor (10U)
#define Os_EIC10 ((*(volatile uint16 *) (0xFFFF9014UL)))
#define Os_Disable_EI_Channel_10() OS_SET1((volatile char *)&Os_EIC10, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_10() OS_CLR1((volatile char *)&Os_EIC10, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_10() Os_EIC10 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_VoltageMonitor() Os_Disable_EI_Channel_10()
#define Os_Enable_CAT2ISR_VoltageMonitor() Os_Enable_EI_Channel_10()
#define Os_Clear_CAT2ISR_VoltageMonitor() Os_Clear_EI_Channel_10()

#define Os_IntChannel_INTRCANGERR (14U)
#define Os_IntChannel_CAT2ISR_CanGlobalStatus (14U)
#define Os_EIC14 ((*(volatile uint16 *) (0xFFFF901CUL)))
#define Os_Disable_EI_Channel_14() OS_SET1((volatile char *)&Os_EIC14, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_14() OS_CLR1((volatile char *)&Os_EIC14, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_14() Os_EIC14 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_CanGlobalStatus() Os_Disable_EI_Channel_14()
#define Os_Enable_CAT2ISR_CanGlobalStatus() Os_Enable_EI_Channel_14()
#define Os_Clear_CAT2ISR_CanGlobalStatus() Os_Clear_EI_Channel_14()

#define Os_IntChannel_INTRCANGRECC (15U)
#define Os_IntChannel_CAT2ISR_Can0Receive (15U)
#define Os_EIC15 ((*(volatile uint16 *) (0xFFFF901EUL)))
#define Os_Disable_EI_Channel_15() OS_SET1((volatile char *)&Os_EIC15, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_15() OS_CLR1((volatile char *)&Os_EIC15, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_15() Os_EIC15 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Can0Receive() Os_Disable_EI_Channel_15()
#define Os_Enable_CAT2ISR_Can0Receive() Os_Enable_EI_Channel_15()
#define Os_Clear_CAT2ISR_Can0Receive() Os_Clear_EI_Channel_15()

#define Os_IntChannel_INTRCAN0ERR (16U)
#define Os_IntChannel_CAT2ISR_Can0Status (16U)
#define Os_EIC16 ((*(volatile uint16 *) (0xFFFF9020UL)))
#define Os_Disable_EI_Channel_16() OS_SET1((volatile char *)&Os_EIC16, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_16() OS_CLR1((volatile char *)&Os_EIC16, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_16() Os_EIC16 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Can0Status() Os_Disable_EI_Channel_16()
#define Os_Enable_CAT2ISR_Can0Status() Os_Enable_EI_Channel_16()
#define Os_Clear_CAT2ISR_Can0Status() Os_Clear_EI_Channel_16()

#define Os_IntChannel_INTRCAN0TRX (18U)
#define Os_IntChannel_CAT2ISR_Can0Transmit (18U)
#define Os_EIC18 ((*(volatile uint16 *) (0xFFFF9024UL)))
#define Os_Disable_EI_Channel_18() OS_SET1((volatile char *)&Os_EIC18, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_18() OS_CLR1((volatile char *)&Os_EIC18, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_18() Os_EIC18 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Can0Transmit() Os_Disable_EI_Channel_18()
#define Os_Enable_CAT2ISR_Can0Transmit() Os_Enable_EI_Channel_18()
#define Os_Clear_CAT2ISR_Can0Transmit() Os_Clear_EI_Channel_18()

#define Os_IntChannel_INTP1_INTCSIH2IRE_1 (30U)
#define Os_IntChannel_CAT2ISR_Wakeup (30U)
#define Os_EIC30 ((*(volatile uint16 *) (0xFFFF903CUL)))
#define Os_Disable_EI_Channel_30() OS_SET1((volatile char *)&Os_EIC30, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_30() OS_CLR1((volatile char *)&Os_EIC30, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_30() Os_EIC30 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Wakeup() Os_Disable_EI_Channel_30()
#define Os_Enable_CAT2ISR_Wakeup() Os_Enable_EI_Channel_30()
#define Os_Clear_CAT2ISR_Wakeup() Os_Clear_EI_Channel_30()

#define Os_IntChannel_INTP11 (38U)
#define Os_IntChannel_CAT2ISR_TelRec (38U)
#define Os_EIC38 ((*(volatile uint16 *) (0xFFFFA04CUL)))
#define Os_Disable_EI_Channel_38() OS_SET1((volatile char *)&Os_EIC38, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_38() OS_CLR1((volatile char *)&Os_EIC38, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_38() Os_EIC38 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_TelRec() Os_Disable_EI_Channel_38()
#define Os_Enable_CAT2ISR_TelRec() Os_Enable_EI_Channel_38()
#define Os_Clear_CAT2ISR_TelRec() Os_Clear_EI_Channel_38()

#define Os_IntChannel_INTTAUJ0I0 (72U)
#define Os_IntChannel_CAT2ISR_Timer0 (72U)
#define Os_EIC72 ((*(volatile uint16 *) (0xFFFFA090UL)))
#define Os_Disable_EI_Channel_72() OS_SET1((volatile char *)&Os_EIC72, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_72() OS_CLR1((volatile char *)&Os_EIC72, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_72() Os_EIC72 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Timer0() Os_Disable_EI_Channel_72()
#define Os_Enable_CAT2ISR_Timer0() Os_Enable_EI_Channel_72()
#define Os_Clear_CAT2ISR_Timer0() Os_Clear_EI_Channel_72()

#define Os_IntChannel_INTTAUJ0I1 (73U)
#define Os_IntChannel_CAT2ISR_Timer1 (73U)
#define Os_EIC73 ((*(volatile uint16 *) (0xFFFFA092UL)))
#define Os_Disable_EI_Channel_73() OS_SET1((volatile char *)&Os_EIC73, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_73() OS_CLR1((volatile char *)&Os_EIC73, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_73() Os_EIC73 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Timer1() Os_Disable_EI_Channel_73()
#define Os_Enable_CAT2ISR_Timer1() Os_Enable_EI_Channel_73()
#define Os_Clear_CAT2ISR_Timer1() Os_Clear_EI_Channel_73()

#define Os_IntChannel_INTTAUJ0I2 (74U)
#define Os_IntChannel_CAT2ISR_Timer2 (74U)
#define Os_EIC74 ((*(volatile uint16 *) (0xFFFFA094UL)))
#define Os_Disable_EI_Channel_74() OS_SET1((volatile char *)&Os_EIC74, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_74() OS_CLR1((volatile char *)&Os_EIC74, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_74() Os_EIC74 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Timer2() Os_Disable_EI_Channel_74()
#define Os_Enable_CAT2ISR_Timer2() Os_Enable_EI_Channel_74()
#define Os_Clear_CAT2ISR_Timer2() Os_Clear_EI_Channel_74()

#define Os_IntChannel_INTTAUJ0I3 (75U)
#define Os_IntChannel_CAT2ISR_Timer3 (75U)
#define Os_EIC75 ((*(volatile uint16 *) (0xFFFFA096UL)))
#define Os_Disable_EI_Channel_75() OS_SET1((volatile char *)&Os_EIC75, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_75() OS_CLR1((volatile char *)&Os_EIC75, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_75() Os_EIC75 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_Timer3() Os_Disable_EI_Channel_75()
#define Os_Enable_CAT2ISR_Timer3() Os_Enable_EI_Channel_75()
#define Os_Clear_CAT2ISR_Timer3() Os_Clear_EI_Channel_75()

#define Os_IntChannel_INTOSTM0 (76U)
#define Os_IntChannel_CAT2ISR_OneMillisecond (76U)
#define Os_EIC76 ((*(volatile uint16 *) (0xFFFFA098UL)))
#define Os_Disable_EI_Channel_76() OS_SET1((volatile char *)&Os_EIC76, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_76() OS_CLR1((volatile char *)&Os_EIC76, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_76() Os_EIC76 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_CAT2ISR_OneMillisecond() Os_Disable_EI_Channel_76()
#define Os_Enable_CAT2ISR_OneMillisecond() Os_Enable_EI_Channel_76()
#define Os_Clear_CAT2ISR_OneMillisecond() Os_Clear_EI_Channel_76()

#define Os_IntChannel_INTFLENDNM (103U)
#define Os_IntChannel_FLS_FLENDNM_CAT2_ISR (103U)
#define Os_EIC103 ((*(volatile uint16 *) (0xFFFFA0CEUL)))
#define Os_Disable_EI_Channel_103() OS_SET1((volatile char *)&Os_EIC103, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_103() OS_CLR1((volatile char *)&Os_EIC103, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_103() Os_EIC103 &= ((uint16)~(OS_ICR_INTERRUPT_CLEARED))
#define Os_Disable_FLS_FLENDNM_CAT2_ISR() Os_Disable_EI_Channel_103()
#define Os_Enable_FLS_FLENDNM_CAT2_ISR() Os_Enable_EI_Channel_103()
#define Os_Clear_FLS_FLENDNM_CAT2_ISR() Os_Clear_EI_Channel_103()

#define Os_DisableAllConfiguredInterrupts() \
  Os_Disable_CAT2ISR_VoltageMonitor(); \
  Os_Disable_CAT2ISR_CanGlobalStatus(); \
  Os_Disable_CAT2ISR_Can0Receive(); \
  Os_Disable_CAT2ISR_Can0Status(); \
  Os_Disable_CAT2ISR_Can0Transmit(); \
  Os_Disable_CAT2ISR_Wakeup(); \
  Os_Disable_CAT2ISR_TelRec(); \
  Os_Disable_CAT2ISR_Timer0(); \
  Os_Disable_CAT2ISR_Timer1(); \
  Os_Disable_CAT2ISR_Timer2(); \
  Os_Disable_CAT2ISR_Timer3(); \
  Os_Disable_CAT2ISR_OneMillisecond(); \
  Os_Disable_FLS_FLENDNM_CAT2_ISR();

#define Os_EnableAllConfiguredInterrupts() \
  Os_Enable_CAT2ISR_VoltageMonitor(); \
  Os_Enable_CAT2ISR_CanGlobalStatus(); \
  Os_Enable_CAT2ISR_Can0Receive(); \
  Os_Enable_CAT2ISR_Can0Status(); \
  Os_Enable_CAT2ISR_Can0Transmit(); \
  Os_Enable_CAT2ISR_Wakeup(); \
  Os_Enable_CAT2ISR_TelRec(); \
  Os_Enable_CAT2ISR_Timer0(); \
  Os_Enable_CAT2ISR_Timer1(); \
  Os_Enable_CAT2ISR_Timer2(); \
  Os_Enable_CAT2ISR_Timer3(); \
  Os_Enable_CAT2ISR_OneMillisecond(); \
  Os_Enable_FLS_FLENDNM_CAT2_ISR();

#endif
