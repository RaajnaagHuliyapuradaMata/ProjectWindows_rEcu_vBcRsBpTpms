

//#include "BrsHw.h"

#if !defined (BRS_COMP_GHS)
#define BRS_COMP_GHS
#endif

#if defined (BRS_COMP_GHS)
  #define ___asm(c)               __asm_(c)
  #define __asm_(c)               asm(" " #c);
  #define __as1(c, d)             __as1_(c, d)
  #define __as1_(c, d)            asm(" " #c " , " #d);
  #define __as2(c, d, e)          __as2_(c, d, e)
  #define __as2_(c, d, e)         asm(" " #c " , " #d " , " #e);
  #define BRS_ISR_BASE_ENTRY(x)   ___asm(jr x)
  #define BRS_ISR_ALIGNMENT       ___asm(nop)___asm(nop)___asm(nop)___asm(nop)___asm(nop)___asm(nop)
  #define BRS_ISR_ENTRY(x)        ___asm(.word x)
  #define BRS_ISR_KEYWORD         __interrupt
  #define BRS_ISR_DEFINE(x)       _##x

#else
  #error: "Compiler not yet supported"
#endif

___asm(.globl __APPLENTRY)
___asm(__APPLENTRY:)
___asm(jr __usr_init)

___asm(;)
___asm(;)
___asm(;)

___asm(;)
___asm(.globl __usr_init)

#if defined (BRS_COMP_GHS)
___asm(.section ".text")
#endif

___asm(;)
___asm(;)
___asm(;)
___asm(;)
___asm(;)
___asm(;)
___asm(;)

___asm(;)
___asm(__usr_init:)

___asm(;)
___asm(;)
___asm(;)
#if defined (BRS_COMP_GHS)
  ___asm(;)
  __as2(movhi hi(__gp), zero, gp)
  __as2(movea lo(__gp), gp, gp)

  ___asm(;)
  __as2(movhi hi(__tp), zero, tp)
  __as2(movea lo(__tp), tp, tp)

  ___asm(;)
  __as2(movhi hi(___ghsend_stack-4), zero, sp)
  __as2(movea lo(___ghsend_stack-4), sp, sp)

#endif

___asm(;)
__as1(mov   _VECTORTABLE_START_ADDR, r6;)
__as2(ldsr  r6, 4, 1;)
__as2(stsr  4, r6, 1;)

___asm(;)
__as1(mov   _EXCEPTIONTABLE_START_ADDR, r6)
__as2(ldsr  r6,3,1)
__as2(stsr  3, r6, 1)
__as1(mov   zero, r6)

___asm(;)
__as2(stsr  5, r1, 0)
__as1(mov   0x8000, r2)
__as1(or    r2, r1)
__as2(ldsr  r1, 5, 0)

#define LOC_RAM_START_ADR	0xFEDFC000
//#define LOC_RAM_SIZE		0x0000C000
#define LOC_RAM_SIZE		0x0000BC00    // RST: length of standard RAM is 1k smaller, the last 1k is reserved
                                      // as real retention ram (for standstill monitoring) and MUST NOT be initialized on startup!!

___asm(;)
___asm(;)
___asm(;)
__as1(mov  LOC_RAM_START_ADR, r11 ; )
__as1(mov  LOC_RAM_START_ADR + LOC_RAM_SIZE *1024-1, r12 ; )

___asm(;)
___asm(_zero_init_local1:)
__as1(st.w  r0, 0[r11])
__as2(addi  4, r11, r11)
__as1(cmp   r11, r12)
___asm(bh    _zero_init_local1)

#if defined (BRS_COMP_GHS)
  ___asm(;)
  ___asm(jr __start)
#endif

___asm(;)
