

#ifndef __CPU_H__
#define __CPU_H__

#ifdef __ghs
  #pragma ghs startnomisra
  #define _INLINE_ __inline

  //#include <..\include\v800\v800_ghs.h>
  #include "v800_ghs.h"

#else

    #include <something else>
    #define _INLINE_ inline
#endif

#ifndef u32_T
#define u32_T unsigned long
#endif

typedef union {
    u32_T     psw;
    struct {
        u32_T   Z:1,
                S:1,
                OV:1,
                CY:1,
                SAT:1,
                ID:1,
                EP:1,
                NP:1,
                rsvd1:1,
                DBG:3,
                rsvd2:3,
                EBV:1,
                CU0:1,
                CU1:1,
                CU2:1,
                rsvd3:11,
                UM:1,
                rsvd4:1;
    };
} PSW_T;

typedef struct {
    u32_T   ctpsw;
    struct {
        u32_T   Z:1,
                S:1,
                OV:1,
                CY:1,
                SAT:1;
    };
} CTPSW_T;

typedef struct {
    const u32_T htcfg0;
    struct {
        const u32_T rsvd1:16,
                    PEID:3,
                    rsvd2:13;
    };
} HTCFG0_T;

typedef struct {
    u32_T   asid;
    struct {
        u32_T  ASID:10,
               rsvd1:22;
    };
} ASID_T;

typedef struct {
    u32_T   mei;
    struct {
        u32_T   RW:1,
                ITYPE:5,
                rsvd1:2,
                U:1,
                DS:2,
                rsvd2:5,
                REG:5,
                rsvd3:11;
    };
} MEI_T;

typedef union {
    u32_T     pid;
    struct {
        u32_T   VID:8,
                MPU:1,
                SFPU:1,
                DFPU:1;
    };
} PID_T;

typedef union {
    u32_T     mctl;
    struct {
       u32_T  UIC:1,
              MA:1;
    };
} MCTL_T;

typedef union {
    u32_T mcfg0;
    struct {
        u32_T HVTE:1,
              HVCE:1,
              HVP:1,
              rsvd1:13,
              SPID:8,
              rsvd2:8;
    };
} MCFG0_T;

typedef union {
    u32_T   sccfg;
    struct {
        u32_T   SIZE:8,
                rsvd1:24;
    };
} SCCFG_T;

typedef union {
    u32_T    ispr;
    struct {
        u32_T     ISP:16,
                  rsvd1:16;
    };
} ISPR_T;

typedef union {
    u32_T   mpm;
    struct {
        u32_T   MPE:1,
                SVP:1,
                rsvd1:6,
                DR:1,
                DW:1,
                DX:1,
                rsvd2:21;
    };
} MPM_T;

typedef union {
    u32_T   mprc;
    struct {
        u32_T   E0:1,
                E1:1,
                E2:1,
                E3:1,
                E4:1,
                E5:1,
                E6:1,
                E7:1,
                E8:1,
                E9:1,
                E10:1,
                E11:1,
                E12:1,
                E13:1,
                E14:1,
                E15:1;
    };
} MPRC_T;

typedef union {
    u32_T   fpsr;
    struct {
        u32_T   XPI:1,
                XPU:1,
                XPO:1,
                XPZ:1,
                XPV:1,

                XEI:1,
                XEU:1,
                XEO:1,
                XEZ:1,
                XEV:1,

                XCI:1,
                XCU:1,
                XCO:1,
                XCZ:1,
                XCV:1,

                rsvd1:1,
                FS:1,
                RM:2,
                rsvd2:1,
                PEM:1,
                IF:1,
                FN:1,
                CC:8;
    };
} FPSR_T;

typedef union {
    u32_T   ictagl;
    struct {
        u32_T    V:1,
                 rsvd1:1,
                 Lock:1,
                 rsvd2:1,
                 LRU:2,
                 rsvd3:4,
                 LPN:22;
    };
} ICCTAGL_T;

typedef union {
    u32_T   ictagh;
    struct {
        u32_T    rsvd1:8,
                 TAGECC:8,
                 DATAECC:8,
                 rsvd2:4,
                 PT:1,
                 WT:1,
                 PD:1,
                 WD:1;
    };
} ICCTAGH_T;

typedef union {
    u32_T   icctrl;
    struct {
        u32_T    ICHEN:1,
                 ICHEMK:1,
                 ICHEIV:1,
                 rsvd1:5,
                 ICHCLR:1,
                 rsvd2:7,
                 rsvd3:1,
                 D1EV:1,
                 rsvd4:14;
    };
} ICCTRL_T;

typedef union {
    u32_T   iccfg;
    struct {
        u32_T    ICHWAY:4,

                 ICHLINE:4,

                 ICHSIZE:7,

                 rsvd1:1,
                 rsvd2:1,
                 rsvd3:15;
    };
} ICCFG_T;

typedef union {
    u32_T   icerr;
    struct {
        u32_T    ICHERR:1,
                 rsvd1:1,
                 ICHET:1,
                 ICHED:1,
                 ICHERQ:1,
                 ICHEIX:8,
                 ICHEWY:2,
                 rsvd2:1,

                 ERMDE:1,
                 ERMDC:1,
                 ERMTE2:1,
                 ERMTE1:1,
                 ERMPBSE:1,
                 ERMMH:1,

                 rsvd3:2,

                 ESDE:1,
                 ESDC:1,
                 ESTE2:1,
                 ESTE1:1,
                 ESPBSE:1,
                 ESMH:1,
                 rsvd4:2,
                 CISTW:1;
    };
} ICERR_T;

typedef union {
    u32_T   cdbcr;
    struct {
        u32_T   CDBEN:1,

                CDBCLR:1,
                rsvd1:30;
    };
} CDBCR_T;

typedef union {
    u32_T   mpat;
    struct  {
        u32_T   UR:1,
                UW:1,
                UX:1,
                SR:1,
                SW:1,
                SX:1,
                G:1,

                E:1,
                rsvd1:8,
                ASID:10,

                rsvd2:6;
    };
} MPAT_T;

#define EIPC         0, 0
#define EIPSW        1, 0
#define FEPC         2, 0
#define FEPSW        3, 0
#define PSW          5, 0
#define EIIC        13, 0
#define FEIC        14, 0
#define CTPC        16, 0
#define CTPSW       17, 0
#define CTBP        20, 0
#define EIWR        28, 0
#define FEWR        29, 0
#define BSEL        31, 0

#define MCFG0        0, 1
#define RBASE        2, 1
#define EBASE        3, 1
#define INTBP        4, 1
#define MCTL         5, 1
#define PID          6, 1
#define SCCFG       11, 1
#define SCBP        12, 1

#define HTCFG0       0, 2
#define MEA          6, 2
#define ASID         7, 2
#define MEI          8, 2
#define ISPR        10, 2
#define PMR         11, 2
#define ICSR        12, 2
#define INTCFG      13, 2

#define MPM          0, 5
#define MPRC         1, 5
#define MPBRGN       4, 5
#define MPTRGN       5, 5
#define MCA          8, 5
#define MCS          9, 5
#define MCC         10, 5
#define MCR         11, 5

#define MPLA0        0, 6
#define MPUA0        1, 6
#define MPAT0        2, 6
#define MPLA1        4, 6
#define MPUA1        5, 6
#define MPAT1        6, 6
#define MPLA2        8, 6
#define MPUA2        9, 6
#define MPAT2       10, 6
#define MPLA3       12, 6
#define MPUA3       13, 6
#define MPAT3       14, 6
#define MPLA4       16, 6
#define MPUA4       17, 6
#define MPAT4       18, 6
#define MPLA5       20, 6
#define MPUA5       21, 6
#define MPAT5       22, 6
#define MPLA6       24, 6
#define MPUA6       25, 6
#define MPAT6       26, 6
#define MLUA7       28, 6
#define MPUA7       29, 6
#define MPAT7       30, 6
#define MPLA8        0, 7
#define MPUA8        1, 7
#define MPAT8        2, 7
#define MPLA9        4, 7
#define MPUA9        5, 7
#define MPAT9        6, 7
#define MPLA10       8, 7
#define MPUA10       9, 7
#define MPAT10      10, 7
#define MPLA11      12, 7
#define MPUA11      13, 7
#define MPAT11      14, 7
#define MPLA12      16, 7
#define MPUA12      17, 7
#define MPAT12      18, 7
#define MPLA13      20, 7
#define MPUA13      21, 7
#define MPAT13      22, 7
#define MPLA14      24, 7
#define MPUA14      25, 7
#define MPAT14      26, 7
#define MPLA15      28, 7
#define MPUA15      29, 7
#define MPAT15      30, 7

_INLINE_ void SET_PSW_USERMODE( void)
{
    PSW_T p;
    p.psw= __STSR( PSW);
    p.UM= 1;
    __LDSR( PSW, p.psw);
    __SYNCI();
}

_INLINE_ void SET_PSW_SVMODE( void)
{
    PSW_T p;
    p.psw= __STSR( PSW);
    p.UM= 0;
    __LDSR( PSW, p.psw);
    __SYNCI();
}

_INLINE_ void SET_MCFG0_SPID( u32_T v)
{
    MCFG0_T p;
    p.mcfg0= __STSR( MCFG0);
    p.SPID= v;
    __LDSR( MCFG0, p.mcfg0);
    __SYNCI();
}

_INLINE_ void SET_SCCFG( u32_T emax)
{
    SCCFG_T p;
    p.sccfg= __STSR( SCCFG);
    p.SIZE= emax;
    __LDSR( SCCFG, p.sccfg);
    __SYNCP();
}

_INLINE_ void SET_ASID( u32_T v)   { __LDSR( ASID  , v); __SYNCP();}

_INLINE_ void SET_MPM   (u32_T v)  { __LDSR( MPM   , v); __SYNCI();}
_INLINE_ void SET_MPRC  (u32_T v)  { __LDSR( MPRC  , v); __SYNCI();}
_INLINE_ void SET_MPBRGN(u32_T v)  { __LDSR( MPBRGN, v); __SYNCI();}
_INLINE_ void SET_MPTRGN(u32_T v)  { __LDSR( MPTRGN, v); __SYNCI();}
_INLINE_ void SET_MCA   (u32_T v)  { __LDSR( MCA   , v); __SYNCI();}
_INLINE_ void SET_MCS   (u32_T v)  { __LDSR( MCS   , v); __SYNCI();}
_INLINE_ void SET_MCC   (u32_T v)  { __LDSR( MCC   , v); __SYNCI();}
_INLINE_ void SET_MCR   (u32_T v)  { __LDSR( MCR   , v); __SYNCI();}

_INLINE_ void SET_MPLA0(u32_T v)   { __LDSR( MPLA0 , v); __SYNCP();}
_INLINE_ void SET_MPUA0(u32_T v)   { __LDSR( MPUA0 , v); __SYNCP();}
_INLINE_ void SET_MPAT0(u32_T v)   { __LDSR( MPAT0 , v); __SYNCP();}
_INLINE_ void SET_MPLA1(u32_T v)   { __LDSR( MPLA1 , v); __SYNCP();}
_INLINE_ void SET_MPUA1(u32_T v)   { __LDSR( MPUA1 , v); __SYNCP();}
_INLINE_ void SET_MPAT1(u32_T v)   { __LDSR( MPAT1 , v); __SYNCP();}
_INLINE_ void SET_MPLA2(u32_T v)   { __LDSR( MPLA2 , v); __SYNCP();}
_INLINE_ void SET_MPUA2(u32_T v)   { __LDSR( MPUA2 , v); __SYNCP();}
_INLINE_ void SET_MPAT2(u32_T v)   { __LDSR( MPAT2 , v); __SYNCP();}
_INLINE_ void SET_MPLA3(u32_T v)   { __LDSR( MPLA3 , v); __SYNCP();}
_INLINE_ void SET_MPUA3(u32_T v)   { __LDSR( MPUA3 , v); __SYNCP();}
_INLINE_ void SET_MPAT3(u32_T v)   { __LDSR( MPAT3 , v); __SYNCP();}
_INLINE_ void SET_MPLA4(u32_T v)   { __LDSR( MPLA4 , v); __SYNCP();}
_INLINE_ void SET_MPUA4(u32_T v)   { __LDSR( MPUA4 , v); __SYNCP();}
_INLINE_ void SET_MPAT4(u32_T v)   { __LDSR( MPAT4 , v); __SYNCP();}
_INLINE_ void SET_MPLA5(u32_T v)   { __LDSR( MPLA5 , v); __SYNCP();}
_INLINE_ void SET_MPUA5(u32_T v)   { __LDSR( MPUA5 , v); __SYNCP();}
_INLINE_ void SET_MPAT5(u32_T v)   { __LDSR( MPAT5 , v); __SYNCP();}
_INLINE_ void SET_MPLA6(u32_T v)   { __LDSR( MPLA6 , v); __SYNCP();}
_INLINE_ void SET_MPUA6(u32_T v)   { __LDSR( MPUA6 , v); __SYNCP();}
_INLINE_ void SET_MPAT6(u32_T v)   { __LDSR( MPAT6 , v); __SYNCP();}
_INLINE_ void SET_MLUA7(u32_T v)   { __LDSR( MLUA7 , v); __SYNCP();}
_INLINE_ void SET_MPUA7(u32_T v)   { __LDSR( MPUA7 , v); __SYNCP();}
_INLINE_ void SET_MPAT7(u32_T v)   { __LDSR( MPAT7 , v); __SYNCP();}
_INLINE_ void SET_MPLA8(u32_T v)   { __LDSR( MPLA8 , v); __SYNCP();}
_INLINE_ void SET_MPUA8(u32_T v)   { __LDSR( MPUA8 , v); __SYNCP();}
_INLINE_ void SET_MPAT8(u32_T v)   { __LDSR( MPAT8 , v); __SYNCP();}
_INLINE_ void SET_MPLA9(u32_T v)   { __LDSR( MPLA9 , v); __SYNCP();}
_INLINE_ void SET_MPUA9(u32_T v)   { __LDSR( MPUA9 , v); __SYNCP();}
_INLINE_ void SET_MPAT9(u32_T v)   { __LDSR( MPAT9 , v); __SYNCP();}
_INLINE_ void SET_MPLA10(u32_T v)  { __LDSR( MPLA10, v); __SYNCP();}
_INLINE_ void SET_MPUA10(u32_T v)  { __LDSR( MPUA10, v); __SYNCP();}
_INLINE_ void SET_MPAT10(u32_T v)  { __LDSR( MPAT10, v); __SYNCP();}
_INLINE_ void SET_MPLA11(u32_T v)  { __LDSR( MPLA11, v); __SYNCP();}
_INLINE_ void SET_MPUA11(u32_T v)  { __LDSR( MPUA11, v); __SYNCP();}
_INLINE_ void SET_MPAT11(u32_T v)  { __LDSR( MPAT11, v); __SYNCP();}
_INLINE_ void SET_MPLA12(u32_T v)  { __LDSR( MPLA12, v); __SYNCP();}
_INLINE_ void SET_MPUA12(u32_T v)  { __LDSR( MPUA12, v); __SYNCP();}
_INLINE_ void SET_MPAT12(u32_T v)  { __LDSR( MPAT12, v); __SYNCP();}
_INLINE_ void SET_MPLA13(u32_T v)  { __LDSR( MPLA13, v); __SYNCP();}
_INLINE_ void SET_MPUA13(u32_T v)  { __LDSR( MPUA13, v); __SYNCP();}
_INLINE_ void SET_MPAT13(u32_T v)  { __LDSR( MPAT13, v); __SYNCP();}
_INLINE_ void SET_MPLA14(u32_T v)  { __LDSR( MPLA14, v); __SYNCP();}
_INLINE_ void SET_MPUA14(u32_T v)  { __LDSR( MPUA14, v); __SYNCP();}
_INLINE_ void SET_MPAT14(u32_T v)  { __LDSR( MPAT14, v); __SYNCP();}
_INLINE_ void SET_MPLA15(u32_T v)  { __LDSR( MPLA15, v); __SYNCP();}
_INLINE_ void SET_MPUA15(u32_T v)  { __LDSR( MPUA15, v); __SYNCP();}
_INLINE_ void SET_MPAT15(u32_T v)  { __LDSR( MPAT15, v); __SYNCP();}

_INLINE_ u32_T GET_ASID( void )    { return __STSR( ASID  ); }

_INLINE_ u32_T GET_MPM   (void )   { return __STSR( MPM   ); }
_INLINE_ u32_T GET_MPRC  (void )   { return __STSR( MPRC  ); }
_INLINE_ u32_T GET_MPBRGN(void )   { return __STSR( MPBRGN); }
_INLINE_ u32_T GET_MPTRGN(void )   { return __STSR( MPTRGN); }
_INLINE_ u32_T GET_MCA   (void )   { return __STSR( MCA   ); }
_INLINE_ u32_T GET_MCS   (void )   { return __STSR( MCS   ); }
_INLINE_ u32_T GET_MCC   (void )   { return __STSR( MCC   ); }
_INLINE_ u32_T GET_MCR   (void )   { return __STSR( MCR   ); }

_INLINE_ u32_T GET_MPLA0(void )    { return __STSR( MPLA0 ); }
_INLINE_ u32_T GET_MPUA0(void )    { return __STSR( MPUA0 ); }
_INLINE_ u32_T GET_MPAT0(void )    { return __STSR( MPAT0 ); }
_INLINE_ u32_T GET_MPLA1(void )    { return __STSR( MPLA1 ); }
_INLINE_ u32_T GET_MPUA1(void )    { return __STSR( MPUA1 ); }
_INLINE_ u32_T GET_MPAT1(void )    { return __STSR( MPAT1 ); }
_INLINE_ u32_T GET_MPLA2(void )    { return __STSR( MPLA2 ); }
_INLINE_ u32_T GET_MPUA2(void )    { return __STSR( MPUA2 ); }
_INLINE_ u32_T GET_MPAT2(void )    { return __STSR( MPAT2 ); }
_INLINE_ u32_T GET_MPLA3(void )    { return __STSR( MPLA3 ); }
_INLINE_ u32_T GET_MPUA3(void )    { return __STSR( MPUA3 ); }
_INLINE_ u32_T GET_MPAT3(void )    { return __STSR( MPAT3 ); }
_INLINE_ u32_T GET_MPLA4(void )    { return __STSR( MPLA4 ); }
_INLINE_ u32_T GET_MPUA4(void )    { return __STSR( MPUA4 ); }
_INLINE_ u32_T GET_MPAT4(void )    { return __STSR( MPAT4 ); }
_INLINE_ u32_T GET_MPLA5(void )    { return __STSR( MPLA5 ); }
_INLINE_ u32_T GET_MPUA5(void )    { return __STSR( MPUA5 ); }
_INLINE_ u32_T GET_MPAT5(void )    { return __STSR( MPAT5 ); }
_INLINE_ u32_T GET_MPLA6(void )    { return __STSR( MPLA6 ); }
_INLINE_ u32_T GET_MPUA6(void )    { return __STSR( MPUA6 ); }
_INLINE_ u32_T GET_MPAT6(void )    { return __STSR( MPAT6 ); }
_INLINE_ u32_T GET_MLUA7(void )    { return __STSR( MLUA7 ); }
_INLINE_ u32_T GET_MPUA7(void )    { return __STSR( MPUA7 ); }
_INLINE_ u32_T GET_MPAT7(void )    { return __STSR( MPAT7 ); }
_INLINE_ u32_T GET_MPLA8(void )    { return __STSR( MPLA8 ); }
_INLINE_ u32_T GET_MPUA8(void )    { return __STSR( MPUA8 ); }
_INLINE_ u32_T GET_MPAT8(void )    { return __STSR( MPAT8 ); }
_INLINE_ u32_T GET_MPLA9(void )    { return __STSR( MPLA9 ); }
_INLINE_ u32_T GET_MPUA9(void )    { return __STSR( MPUA9 ); }
_INLINE_ u32_T GET_MPAT9(void )    { return __STSR( MPAT9 ); }
_INLINE_ u32_T GET_MPLA10(void )   { return __STSR( MPLA10); }
_INLINE_ u32_T GET_MPUA10(void )   { return __STSR( MPUA10); }
_INLINE_ u32_T GET_MPAT10(void )   { return __STSR( MPAT10); }
_INLINE_ u32_T GET_MPLA11(void )   { return __STSR( MPLA11); }
_INLINE_ u32_T GET_MPUA11(void )   { return __STSR( MPUA11); }
_INLINE_ u32_T GET_MPAT11(void )   { return __STSR( MPAT11); }
_INLINE_ u32_T GET_MPLA12(void )   { return __STSR( MPLA12); }
_INLINE_ u32_T GET_MPUA12(void )   { return __STSR( MPUA12); }
_INLINE_ u32_T GET_MPAT12(void )   { return __STSR( MPAT12); }
_INLINE_ u32_T GET_MPLA13(void )   { return __STSR( MPLA13); }
_INLINE_ u32_T GET_MPUA13(void )   { return __STSR( MPUA13); }
_INLINE_ u32_T GET_MPAT13(void )   { return __STSR( MPAT13); }
_INLINE_ u32_T GET_MPLA14(void )   { return __STSR( MPLA14); }
_INLINE_ u32_T GET_MPUA14(void )   { return __STSR( MPUA14); }
_INLINE_ u32_T GET_MPAT14(void )   { return __STSR( MPAT14); }
_INLINE_ u32_T GET_MPLA15(void )   { return __STSR( MPLA15); }
_INLINE_ u32_T GET_MPUA15(void )   { return __STSR( MPUA15); }
_INLINE_ u32_T GET_MPAT15(void )   { return __STSR( MPAT15); }

_INLINE_ void SET_PSW_EBV( void)
{
    PSW_T p;
    __DI() ;
    p.psw= __STSR( PSW);
    p.EBV= 1;
    __LDSR( PSW, p.psw);
}

_INLINE_ void SET_MCTL_MA( u32_T v)
{
    MCTL_T p;
    p.mctl= __STSR( MCTL);
    p.MA=!!v;
    __LDSR( MCTL, p.mctl);
    __SYNCP();
}

_INLINE_ void SET_MCTL_UIC( u32_T v)
{
    MCTL_T p;
    p.mctl= __STSR( MCTL);
    p.UIC=!!v;
    __LDSR( MCTL, p.mctl);
    __SYNCP();
}

_INLINE_ void SET_EBASE( u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( EBASE, v);
    __RIR( __t);
}

_INLINE_ void SET_INTBP( u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( INTBP, v);
    __RIR( __t);
}

_INLINE_ void SET_ISPR(u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( ISPR, v);
    __RIR( __t);
}

_INLINE_ void SET_PMR(u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( PMR, v);
    __RIR( __t);
}

_INLINE_ void SET_ICSR( u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( ICSR, v);
    __RIR( __t);
}

_INLINE_ void SET_INTCFG( u32_T v)
{
    u32_T __t=__DIR();
    __LDSR( INTCFG, v);
    __RIR( __t);
}

#ifdef __RH850G3M__

#define FPSR         6, 0
#define FPEPC        7, 0
#define FPST         8, 0
#define FPCC         9, 0
#define FPCFG       10, 0
#define FPEC        11, 0

#define ICTAGL      16, 4
#define ICTAGH      17, 4
#define ICDATL      18, 4
#define ICDATH      19, 4
#define ICCTRL      24, 4
#define ICCFG       26, 4
#define ICERR       28, 4

#define CDBCR       24,13

_INLINE_ void SET_FPSR(u32_T v) { __LDSR( FPSR ,v); __SYNCP();}
_INLINE_ void SET_FPEP(u32_T v) { __LDSR( FPEPC,v); __SYNCP();}
_INLINE_ void SET_FPST(u32_T v) { __LDSR( FPST ,v); __SYNCP();}
_INLINE_ void SET_FPCC(u32_T v) { __LDSR( FPCC ,v); __SYNCP();}
_INLINE_ void SET_FPCF(u32_T v) { __LDSR( FPCFG,v); __SYNCP();}
_INLINE_ void SET_FPEC(u32_T v) { __LDSR( FPEC ,v); __SYNCP();}

_INLINE_ void SET_PSW_ENABLEFPU( void)
{
    PSW_T p;
    p.psw= __STSR( PSW);
    p.CU0= 1;
    __LDSR( PSW, p.psw);
    __SYNCI();
}

_INLINE_ void SET_FPSR_PEM( void)
{
    FPSR_T p;
    __SYNCP();
    p.fpsr= __STSR( FPSR);
    p.PEM= 1;
    __LDSR( FPSR, p.fpsr);
    __SYNCP();
}

#endif
#ifdef __ghs
#pragma ghs endnomisra
#endif
#endif
