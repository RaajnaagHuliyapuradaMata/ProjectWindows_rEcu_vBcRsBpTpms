

#ifndef __R7F701013xAFPIODEFINE_HEADER__
#define __R7F701013xAFPIODEFINE_HEADER__

#include "Platform_Types.h"    //RST -> mehrfache Typdefinitionen eliminiert. Alles nur noch in Platform_Types.h
//#ifndef _IODEF_AUTOSAR_TYPEDEF_
//#define _IODEF_AUTOSAR_TYPEDEF_
//typedef unsigned char   uint8;
//typedef unsigned short  uint16;
//typedef unsigned long   uint32;
//#endif
//
//typedef unsigned char     u08_T;
//typedef unsigned short    u16_T;
//typedef unsigned long     u32_T;
//typedef  signed char    s08_T;
//typedef  signed short   s16_T;
//typedef  signed int     s32_T;

#ifndef _GHS_PRAGMA_IO_TYPEDEF_
  #define _GHS_PRAGMA_IO_TYPEDEF_
  #define PRAGMA(x) _Pragma(#x)
  #define __READ volatile const
  #define __WRITE volatile
  #define __READ_WRITE volatile

  #define __IOREG(reg, addr, attrib, type) PRAGMA(ghs io reg addr) \
  extern attrib type reg;

  #define __IOREGARRAY(reg, array, addr, attrib, type) PRAGMA(ghs io reg addr) \
  extern attrib type reg[array];
#endif

typedef struct{
    uint8 bit00:1;
    uint8 bit01:1;
    uint8 bit02:1;
    uint8 bit03:1;
    uint8 bit04:1;
    uint8 bit05:1;
    uint8 bit06:1;
    uint8 bit07:1;
} __bitf_T;

#define  L 0
#define  H 1
#define LL 0
#define LH 1
#define HL 2
#define HH 3

typedef struct{
    uint8  BWCBUFCLR:1;
    uint8  :7;
} __type0;
typedef struct{
    uint8  AAS0:1;
    uint8  AAS1:1;
    uint8  AAS2:1;
    uint8  GCA:1;
    uint8  :1;
    uint8  DID:1;
    uint8  :2;
    uint8  :8;
    uint8  :8;
    uint8  :8;
} __type1;
typedef struct{
    uint8  TMOF:1;
    uint8  AL:1;
    uint8  START:1;
    uint8  STOP:1;
    uint8  NACKF:1;
    uint8  RDRF:1;
    uint8  TEND:1;
    uint8  TDRE:1;
    uint8  :8;
    uint8  :8;
    uint8  :8;
} __type2;
typedef struct{
    uint8  MBS:1;
    uint8  JOBE:1;
    uint8  :3;
    uint8  RXE:1;
    uint8  TXE:1;
    uint8  PWR:1;
} __type3;
typedef struct{
    uint8  :7;
    uint8  SVSDIS:1;
} __type4;
typedef struct{
    uint8  :5;
    uint8  RXE:1;
    uint8  TXE:1;
    uint8  PWR:1;
} __type5;
typedef struct{
    uint8  SCE:1;
    uint8  :7;
} __type6;
typedef struct{
    uint8  KRM0:1;
    uint8  KRM1:1;
    uint8  KRM2:1;
    uint8  KRM3:1;
    uint8  KRM4:1;
    uint8  KRM5:1;
    uint8  KRM6:1;
    uint8  KRM7:1;
} __type7;
typedef union
{
    uint8  UINT8;
    __type0 BIT;
} __type8;
typedef union
{
    uint32 UINT32;
    uint16 UINT16[2];
    uint8  UINT8[4];
} __type9;
typedef union
{
    uint32 UINT32;
    uint16 UINT16[2];
    uint8  UINT8[4];
    __type1 BIT;
} __type10;
typedef union
{
    uint32 UINT32;
    uint16 UINT16[2];
    uint8  UINT8[4];
    __type2 BIT;
} __type11;
typedef union
{
    uint16 UINT16;
    uint8  UINT8[2];
    struct
    {
        union
        {
            uint8  UINT8;
        } LBRP0;
        union
        {
            uint8  UINT8;
        } LBRP1;
    } REGS8;
} __type12;
typedef union
{
    uint16 UINT16;
    uint8  UINT8[2];
} __type13;
typedef union
{
    uint16 UINT16;
    uint8  UINT8[2];
} __type14;
typedef union
{
    uint16 UINT16;
    uint8  UINT8[2];
} __type15;
typedef union
{
    uint32 UINT32;
    uint16 UINT16[2];
} __type16;
typedef union
{
    uint8  UINT8;
    __type3 BIT;
} __type17;
typedef union
{
    uint8  UINT8;
    __type4 BIT;
} __type18;
typedef union
{
    uint8  UINT8;
    __type5 BIT;
} __type19;
typedef union
{
    uint8  UINT8;
    __type6 BIT;
} __type20;
typedef union
{
    uint8  UINT8;
    __type7 BIT;
} __type21;

typedef struct{
    uint32 ID0;
    uint32 ID1;
    uint32 ID2;
    uint32 ID3;
    const uint32 IDST;
} __type22;
typedef struct{
    const uint8  FPMON;
    uint8  dummy0[15];
    uint8  FASTAT;
    uint8  dummy1[3];
    uint8  FAEINT;
    uint8  dummy2[11];
    uint16 FAREASELC;
    uint8  dummy3[14];
    uint32 FSADDR;
    uint32 FEADDR;
    uint8  dummy4[28];
    uint16 FCURAME;
    uint8  dummy5[42];
    const uint32 FSTATR;
    uint16 FENTRYR;
    uint8  dummy6[2];
    uint16 FPROTR;
    uint8  dummy7[2];
    uint16 FSUINITR;
    uint8  dummy8[2];
    const uint8  FLKSTAT;
    uint8  dummy9[3];
    const uint32 FRFSTEADR;
    const uint8  FRTSTAT;
    uint8  dummy10[3];
    uint8  FRTEINT;
    uint8  dummy11[3];
    const uint16 FCMDR;
    uint8  dummy12[14];
    uint16 FRAMECCR;
    uint8  dummy13[14];
    const uint16 FPESTAT;
    uint8  dummy14[14];
    uint8  FBCCNT;
    uint8  dummy15[3];
    const uint8  FBCSTAT;
    uint8  dummy16[3];
    const uint32 FPSADDR;
    uint8  dummy17[4];
    uint16 FCPSR;
    uint8  dummy18[2];
    uint16 FPCKAR;
    uint8  dummy19[10];
    uint8  FLEMU;
    uint8  dummy20[3];
    uint32 FLEAD;
    uint8  dummy21[8];
    const uint16 FECCEMON;
    uint8  dummy22[2];
    uint16 FECCTMD;
    uint8  dummy23[2];
    uint16 FDMYECC;
} __type23;
typedef struct{
    __type8 BWCBUFEN;
} __type24;
typedef struct{
    uint8  FCUFAREA;
} __type25;
typedef struct{
    __type9 CR1;
    __type9 CR2;
    __type9 MR1;
    __type9 MR2;
    __type9 MR3;
    __type9 FER;
    __type9 SER;
    __type9 IER;
    __type10 SR1;
    __type11 SR2;
    __type9 SAR0;
    __type9 SAR1;
    __type9 SAR2;
    __type9 BRL;
    __type9 BRH;
    __type9 DRT;
    const __type9 DRR;
} __type26;
typedef struct{
    uint32 PRDNAME1;
    uint32 PRDNAME2;
    uint32 PRDNAME3;
} __type27;
typedef struct{
    uint8  dummy24[1];
    uint8  GLWBR;
    uint8  GLBRP0;
    uint8  GLBRP1;
    uint8  GLSTC;
} __type28;
typedef struct{
    uint8  L0MD;
    uint8  L0BFC;
    uint8  L0SC;
    uint8  L0WUP;
    uint8  L0IE;
    uint8  L0EDE;
    uint8  L0CUC;
    uint8  dummy25[1];
    uint8  L0TRC;
    const uint8  L0MST;
    uint8  L0ST;
    uint8  L0EST;
    uint8  L0DFC;
    uint8  L0IDB;
    uint8  L0CBR;
    uint8  dummy26[1];
    uint8  L0DBR1;
    uint8  L0DBR2;
    uint8  L0DBR3;
    uint8  L0DBR4;
    uint8  L0DBR5;
    uint8  L0DBR6;
    uint8  L0DBR7;
    uint8  L0DBR8;
} __type29;
typedef struct{
    uint8  L1MD;
    uint8  L1BFC;
    uint8  L1SC;
    uint8  L1WUP;
    uint8  L1IE;
    uint8  L1EDE;
    uint8  L1CUC;
    uint8  dummy27[1];
    uint8  L1TRC;
    const uint8  L1MST;
    uint8  L1ST;
    uint8  L1EST;
    uint8  L1DFC;
    uint8  L1IDB;
    uint8  L1CBR;
    uint8  dummy28[1];
    uint8  L1DBR1;
    uint8  L1DBR2;
    uint8  L1DBR3;
    uint8  L1DBR4;
    uint8  L1DBR5;
    uint8  L1DBR6;
    uint8  L1DBR7;
    uint8  L1DBR8;
} __type30;
typedef struct{
    uint8  dummy29[1];
    uint8  LWBR;
    __type12 LBRP01;
    uint8  LSTC;
    uint8  dummy30[3];
    uint8  LMD;
    uint8  LBFC;
    uint8  LSC;
    uint8  LWUP;
    uint8  LIE;
    uint8  LEDE;
    uint8  LCUC;
    uint8  dummy31[1];
    uint8  LTRC;
    const uint8  LMST;
    uint8  LST;
    uint8  LEST;
    uint8  LDFC;
    uint8  LIDB;
    uint8  LCBR;
    uint8  LUDB0;
    uint8  LDBR1;
    uint8  LDBR2;
    uint8  LDBR3;
    uint8  LDBR4;
    uint8  LDBR5;
    uint8  LDBR6;
    uint8  LDBR7;
    uint8  LDBR8;
    uint8  LUOER;
    uint8  LUOR1;
    uint8  dummy32[2];
    __type13 LUTDR;
    const __type14 LURDR;
    __type15 LUWTDR;
    uint8  dummy33[22];
} __type31;
typedef struct{
    __type9 C0CFG;
    __type9 C0CTR;
    const __type9 C0STS;
    __type9 C0ERFL;
    __type9 C1CFG;
    __type9 C1CTR;
    const __type9 C1STS;
    __type9 C1ERFL;
    __type9 C2CFG;
    __type9 C2CTR;
    const __type9 C2STS;
    __type9 C2ERFL;
    uint8  dummy34[84];
    __type9 GCFG;
    __type9 GCTR;
    const __type9 GSTS;
    __type9 GERFL;
    const __type16 GTSC;
    __type9 GAFLECTR;
    __type9 GAFLCFG0;
    uint8  dummy35[4];
    __type9 RMNB;
    __type9 RMND0;
    __type9 RMND1;
    uint8  dummy36[8];
    __type9 RFCC0;
    __type9 RFCC1;
    __type9 RFCC2;
    __type9 RFCC3;
    __type9 RFCC4;
    __type9 RFCC5;
    __type9 RFCC6;
    __type9 RFCC7;
    __type9 RFSTS0;
    __type9 RFSTS1;
    __type9 RFSTS2;
    __type9 RFSTS3;
    __type9 RFSTS4;
    __type9 RFSTS5;
    __type9 RFSTS6;
    __type9 RFSTS7;
    __type9 RFPCTR0;
    __type9 RFPCTR1;
    __type9 RFPCTR2;
    __type9 RFPCTR3;
    __type9 RFPCTR4;
    __type9 RFPCTR5;
    __type9 RFPCTR6;
    __type9 RFPCTR7;
    __type9 CFCC0;
    __type9 CFCC1;
    __type9 CFCC2;
    __type9 CFCC3;
    __type9 CFCC4;
    __type9 CFCC5;
    __type9 CFCC6;
    __type9 CFCC7;
    __type9 CFCC8;
    uint8  dummy37[60];
    __type9 CFSTS0;
    __type9 CFSTS1;
    __type9 CFSTS2;
    __type9 CFSTS3;
    __type9 CFSTS4;
    __type9 CFSTS5;
    __type9 CFSTS6;
    __type9 CFSTS7;
    __type9 CFSTS8;
    uint8  dummy38[60];
    __type9 CFPCTR0;
    __type9 CFPCTR1;
    __type9 CFPCTR2;
    __type9 CFPCTR3;
    __type9 CFPCTR4;
    __type9 CFPCTR5;
    __type9 CFPCTR6;
    __type9 CFPCTR7;
    __type9 CFPCTR8;
    uint8  dummy39[60];
    const __type9 FESTS;
    const __type9 FFSTS;
    const __type9 FMSTS;
    const __type9 RFISTS;
    const __type9 CFRISTS;
    const __type9 CFTISTS;
    uint8  TMC0;
    uint8  TMC1;
    uint8  TMC2;
    uint8  TMC3;
    uint8  TMC4;
    uint8  TMC5;
    uint8  TMC6;
    uint8  TMC7;
    uint8  TMC8;
    uint8  TMC9;
    uint8  TMC10;
    uint8  TMC11;
    uint8  TMC12;
    uint8  TMC13;
    uint8  TMC14;
    uint8  TMC15;
    uint8  TMC16;
    uint8  TMC17;
    uint8  TMC18;
    uint8  TMC19;
    uint8  TMC20;
    uint8  TMC21;
    uint8  TMC22;
    uint8  TMC23;
    uint8  TMC24;
    uint8  TMC25;
    uint8  TMC26;
    uint8  TMC27;
    uint8  TMC28;
    uint8  TMC29;
    uint8  TMC30;
    uint8  TMC31;
    uint8  TMC32;
    uint8  TMC33;
    uint8  TMC34;
    uint8  TMC35;
    uint8  TMC36;
    uint8  TMC37;
    uint8  TMC38;
    uint8  TMC39;
    uint8  TMC40;
    uint8  TMC41;
    uint8  TMC42;
    uint8  TMC43;
    uint8  TMC44;
    uint8  TMC45;
    uint8  TMC46;
    uint8  TMC47;
    uint8  dummy40[80];
    uint8  TMSTS0;
    uint8  TMSTS1;
    uint8  TMSTS2;
    uint8  TMSTS3;
    uint8  TMSTS4;
    uint8  TMSTS5;
    uint8  TMSTS6;
    uint8  TMSTS7;
    uint8  TMSTS8;
    uint8  TMSTS9;
    uint8  TMSTS10;
    uint8  TMSTS11;
    uint8  TMSTS12;
    uint8  TMSTS13;
    uint8  TMSTS14;
    uint8  TMSTS15;
    uint8  TMSTS16;
    uint8  TMSTS17;
    uint8  TMSTS18;
    uint8  TMSTS19;
    uint8  TMSTS20;
    uint8  TMSTS21;
    uint8  TMSTS22;
    uint8  TMSTS23;
    uint8  TMSTS24;
    uint8  TMSTS25;
    uint8  TMSTS26;
    uint8  TMSTS27;
    uint8  TMSTS28;
    uint8  TMSTS29;
    uint8  TMSTS30;
    uint8  TMSTS31;
    uint8  TMSTS32;
    uint8  TMSTS33;
    uint8  TMSTS34;
    uint8  TMSTS35;
    uint8  TMSTS36;
    uint8  TMSTS37;
    uint8  TMSTS38;
    uint8  TMSTS39;
    uint8  TMSTS40;
    uint8  TMSTS41;
    uint8  TMSTS42;
    uint8  TMSTS43;
    uint8  TMSTS44;
    uint8  TMSTS45;
    uint8  TMSTS46;
    uint8  TMSTS47;
    uint8  dummy41[80];
    const __type9 TMTRSTS0;
    const __type9 TMTRSTS1;
    uint8  dummy42[8];
    const __type9 TMTARSTS0;
    const __type9 TMTARSTS1;
    uint8  dummy43[8];
    const __type9 TMTCSTS0;
    const __type9 TMTCSTS1;
    uint8  dummy44[8];
    const __type9 TMTASTS0;
    const __type9 TMTASTS1;
    uint8  dummy45[8];
    __type9 TMIEC0;
    __type9 TMIEC1;
    uint8  dummy46[8];
    __type9 TXQCC0;
    __type9 TXQCC1;
    __type9 TXQCC2;
    uint8  dummy47[20];
    __type9 TXQSTS0;
    __type9 TXQSTS1;
    __type9 TXQSTS2;
    uint8  dummy48[20];
    __type9 TXQPCTR0;
    __type9 TXQPCTR1;
    __type9 TXQPCTR2;
    uint8  dummy49[20];
    __type9 THLCC0;
    __type9 THLCC1;
    __type9 THLCC2;
    uint8  dummy50[20];
    __type9 THLSTS0;
    __type9 THLSTS1;
    __type9 THLSTS2;
    uint8  dummy51[20];
    __type9 THLPCTR0;
    __type9 THLPCTR1;
    __type9 THLPCTR2;
    uint8  dummy52[20];
    const __type9 GTINTSTS0;
    uint8  dummy53[4];
    __type9 GTSTCFG;
    __type9 GTSTCTR;
    uint8  dummy54[12];
    __type16 GLOCKK;
    uint8  dummy55[128];
    __type9 GAFLID0;
    __type9 GAFLM0;
    __type9 GAFLP00;
    __type9 GAFLP10;
    __type9 GAFLID1;
    __type9 GAFLM1;
    __type9 GAFLP01;
    __type9 GAFLP11;
    __type9 GAFLID2;
    __type9 GAFLM2;
    __type9 GAFLP02;
    __type9 GAFLP12;
    __type9 GAFLID3;
    __type9 GAFLM3;
    __type9 GAFLP03;
    __type9 GAFLP13;
    __type9 GAFLID4;
    __type9 GAFLM4;
    __type9 GAFLP04;
    __type9 GAFLP14;
    __type9 GAFLID5;
    __type9 GAFLM5;
    __type9 GAFLP05;
    __type9 GAFLP15;
    __type9 GAFLID6;
    __type9 GAFLM6;
    __type9 GAFLP06;
    __type9 GAFLP16;
    __type9 GAFLID7;
    __type9 GAFLM7;
    __type9 GAFLP07;
    __type9 GAFLP17;
    __type9 GAFLID8;
    __type9 GAFLM8;
    __type9 GAFLP08;
    __type9 GAFLP18;
    __type9 GAFLID9;
    __type9 GAFLM9;
    __type9 GAFLP09;
    __type9 GAFLP19;
    __type9 GAFLID10;
    __type9 GAFLM10;
    __type9 GAFLP010;
    __type9 GAFLP110;
    __type9 GAFLID11;
    __type9 GAFLM11;
    __type9 GAFLP011;
    __type9 GAFLP111;
    __type9 GAFLID12;
    __type9 GAFLM12;
    __type9 GAFLP012;
    __type9 GAFLP112;
    __type9 GAFLID13;
    __type9 GAFLM13;
    __type9 GAFLP013;
    __type9 GAFLP113;
    __type9 GAFLID14;
    __type9 GAFLM14;
    __type9 GAFLP014;
    __type9 GAFLP114;
    __type9 GAFLID15;
    __type9 GAFLM15;
    __type9 GAFLP015;
    __type9 GAFLP115;
    const __type9 RMID0;
    const __type9 RMPTR0;
    const __type9 RMDF00;
    const __type9 RMDF10;
    const __type9 RMID1;
    const __type9 RMPTR1;
    const __type9 RMDF01;
    const __type9 RMDF11;
    const __type9 RMID2;
    const __type9 RMPTR2;
    const __type9 RMDF02;
    const __type9 RMDF12;
    const __type9 RMID3;
    const __type9 RMPTR3;
    const __type9 RMDF03;
    const __type9 RMDF13;
    const __type9 RMID4;
    const __type9 RMPTR4;
    const __type9 RMDF04;
    const __type9 RMDF14;
    const __type9 RMID5;
    const __type9 RMPTR5;
    const __type9 RMDF05;
    const __type9 RMDF15;
    const __type9 RMID6;
    const __type9 RMPTR6;
    const __type9 RMDF06;
    const __type9 RMDF16;
    const __type9 RMID7;
    const __type9 RMPTR7;
    const __type9 RMDF07;
    const __type9 RMDF17;
    const __type9 RMID8;
    const __type9 RMPTR8;
    const __type9 RMDF08;
    const __type9 RMDF18;
    const __type9 RMID9;
    const __type9 RMPTR9;
    const __type9 RMDF09;
    const __type9 RMDF19;
    const __type9 RMID10;
    const __type9 RMPTR10;
    const __type9 RMDF010;
    const __type9 RMDF110;
    const __type9 RMID11;
    const __type9 RMPTR11;
    const __type9 RMDF011;
    const __type9 RMDF111;
    const __type9 RMID12;
    const __type9 RMPTR12;
    const __type9 RMDF012;
    const __type9 RMDF112;
    const __type9 RMID13;
    const __type9 RMPTR13;
    const __type9 RMDF013;
    const __type9 RMDF113;
    const __type9 RMID14;
    const __type9 RMPTR14;
    const __type9 RMDF014;
    const __type9 RMDF114;
    const __type9 RMID15;
    const __type9 RMPTR15;
    const __type9 RMDF015;
    const __type9 RMDF115;
    const __type9 RMID16;
    const __type9 RMPTR16;
    const __type9 RMDF016;
    const __type9 RMDF116;
    const __type9 RMID17;
    const __type9 RMPTR17;
    const __type9 RMDF017;
    const __type9 RMDF117;
    const __type9 RMID18;
    const __type9 RMPTR18;
    const __type9 RMDF018;
    const __type9 RMDF118;
    const __type9 RMID19;
    const __type9 RMPTR19;
    const __type9 RMDF019;
    const __type9 RMDF119;
    const __type9 RMID20;
    const __type9 RMPTR20;
    const __type9 RMDF020;
    const __type9 RMDF120;
    const __type9 RMID21;
    const __type9 RMPTR21;
    const __type9 RMDF021;
    const __type9 RMDF121;
    const __type9 RMID22;
    const __type9 RMPTR22;
    const __type9 RMDF022;
    const __type9 RMDF122;
    const __type9 RMID23;
    const __type9 RMPTR23;
    const __type9 RMDF023;
    const __type9 RMDF123;
    const __type9 RMID24;
    const __type9 RMPTR24;
    const __type9 RMDF024;
    const __type9 RMDF124;
    const __type9 RMID25;
    const __type9 RMPTR25;
    const __type9 RMDF025;
    const __type9 RMDF125;
    const __type9 RMID26;
    const __type9 RMPTR26;
    const __type9 RMDF026;
    const __type9 RMDF126;
    const __type9 RMID27;
    const __type9 RMPTR27;
    const __type9 RMDF027;
    const __type9 RMDF127;
    const __type9 RMID28;
    const __type9 RMPTR28;
    const __type9 RMDF028;
    const __type9 RMDF128;
    const __type9 RMID29;
    const __type9 RMPTR29;
    const __type9 RMDF029;
    const __type9 RMDF129;
    const __type9 RMID30;
    const __type9 RMPTR30;
    const __type9 RMDF030;
    const __type9 RMDF130;
    const __type9 RMID31;
    const __type9 RMPTR31;
    const __type9 RMDF031;
    const __type9 RMDF131;
    const __type9 RMID32;
    const __type9 RMPTR32;
    const __type9 RMDF032;
    const __type9 RMDF132;
    const __type9 RMID33;
    const __type9 RMPTR33;
    const __type9 RMDF033;
    const __type9 RMDF133;
    const __type9 RMID34;
    const __type9 RMPTR34;
    const __type9 RMDF034;
    const __type9 RMDF134;
    const __type9 RMID35;
    const __type9 RMPTR35;
    const __type9 RMDF035;
    const __type9 RMDF135;
    const __type9 RMID36;
    const __type9 RMPTR36;
    const __type9 RMDF036;
    const __type9 RMDF136;
    const __type9 RMID37;
    const __type9 RMPTR37;
    const __type9 RMDF037;
    const __type9 RMDF137;
    const __type9 RMID38;
    const __type9 RMPTR38;
    const __type9 RMDF038;
    const __type9 RMDF138;
    const __type9 RMID39;
    const __type9 RMPTR39;
    const __type9 RMDF039;
    const __type9 RMDF139;
    const __type9 RMID40;
    const __type9 RMPTR40;
    const __type9 RMDF040;
    const __type9 RMDF140;
    const __type9 RMID41;
    const __type9 RMPTR41;
    const __type9 RMDF041;
    const __type9 RMDF141;
    const __type9 RMID42;
    const __type9 RMPTR42;
    const __type9 RMDF042;
    const __type9 RMDF142;
    const __type9 RMID43;
    const __type9 RMPTR43;
    const __type9 RMDF043;
    const __type9 RMDF143;
    const __type9 RMID44;
    const __type9 RMPTR44;
    const __type9 RMDF044;
    const __type9 RMDF144;
    const __type9 RMID45;
    const __type9 RMPTR45;
    const __type9 RMDF045;
    const __type9 RMDF145;
    const __type9 RMID46;
    const __type9 RMPTR46;
    const __type9 RMDF046;
    const __type9 RMDF146;
    const __type9 RMID47;
    const __type9 RMPTR47;
    const __type9 RMDF047;
    const __type9 RMDF147;
    uint8  dummy56[1280];
    const __type9 RFID0;
    const __type9 RFPTR0;
    const __type9 RFDF00;
    const __type9 RFDF10;
    const __type9 RFID1;
    const __type9 RFPTR1;
    const __type9 RFDF01;
    const __type9 RFDF11;
    const __type9 RFID2;
    const __type9 RFPTR2;
    const __type9 RFDF02;
    const __type9 RFDF12;
    const __type9 RFID3;
    const __type9 RFPTR3;
    const __type9 RFDF03;
    const __type9 RFDF13;
    const __type9 RFID4;
    const __type9 RFPTR4;
    const __type9 RFDF04;
    const __type9 RFDF14;
    const __type9 RFID5;
    const __type9 RFPTR5;
    const __type9 RFDF05;
    const __type9 RFDF15;
    const __type9 RFID6;
    const __type9 RFPTR6;
    const __type9 RFDF06;
    const __type9 RFDF16;
    const __type9 RFID7;
    const __type9 RFPTR7;
    const __type9 RFDF07;
    const __type9 RFDF17;
    __type9 CFID0;
    __type9 CFPTR0;
    __type9 CFDF00;
    __type9 CFDF10;
    __type9 CFID1;
    __type9 CFPTR1;
    __type9 CFDF01;
    __type9 CFDF11;
    __type9 CFID2;
    __type9 CFPTR2;
    __type9 CFDF02;
    __type9 CFDF12;
    __type9 CFID3;
    __type9 CFPTR3;
    __type9 CFDF03;
    __type9 CFDF13;
    __type9 CFID4;
    __type9 CFPTR4;
    __type9 CFDF04;
    __type9 CFDF14;
    __type9 CFID5;
    __type9 CFPTR5;
    __type9 CFDF05;
    __type9 CFDF15;
    __type9 CFID6;
    __type9 CFPTR6;
    __type9 CFDF06;
    __type9 CFDF16;
    __type9 CFID7;
    __type9 CFPTR7;
    __type9 CFDF07;
    __type9 CFDF17;
    __type9 CFID8;
    __type9 CFPTR8;
    __type9 CFDF08;
    __type9 CFDF18;
    uint8  dummy57[240];
    __type9 TMID0;
    __type9 TMPTR0;
    __type9 TMDF00;
    __type9 TMDF10;
    __type9 TMID1;
    __type9 TMPTR1;
    __type9 TMDF01;
    __type9 TMDF11;
    __type9 TMID2;
    __type9 TMPTR2;
    __type9 TMDF02;
    __type9 TMDF12;
    __type9 TMID3;
    __type9 TMPTR3;
    __type9 TMDF03;
    __type9 TMDF13;
    __type9 TMID4;
    __type9 TMPTR4;
    __type9 TMDF04;
    __type9 TMDF14;
    __type9 TMID5;
    __type9 TMPTR5;
    __type9 TMDF05;
    __type9 TMDF15;
    __type9 TMID6;
    __type9 TMPTR6;
    __type9 TMDF06;
    __type9 TMDF16;
    __type9 TMID7;
    __type9 TMPTR7;
    __type9 TMDF07;
    __type9 TMDF17;
    __type9 TMID8;
    __type9 TMPTR8;
    __type9 TMDF08;
    __type9 TMDF18;
    __type9 TMID9;
    __type9 TMPTR9;
    __type9 TMDF09;
    __type9 TMDF19;
    __type9 TMID10;
    __type9 TMPTR10;
    __type9 TMDF010;
    __type9 TMDF110;
    __type9 TMID11;
    __type9 TMPTR11;
    __type9 TMDF011;
    __type9 TMDF111;
    __type9 TMID12;
    __type9 TMPTR12;
    __type9 TMDF012;
    __type9 TMDF112;
    __type9 TMID13;
    __type9 TMPTR13;
    __type9 TMDF013;
    __type9 TMDF113;
    __type9 TMID14;
    __type9 TMPTR14;
    __type9 TMDF014;
    __type9 TMDF114;
    __type9 TMID15;
    __type9 TMPTR15;
    __type9 TMDF015;
    __type9 TMDF115;
    __type9 TMID16;
    __type9 TMPTR16;
    __type9 TMDF016;
    __type9 TMDF116;
    __type9 TMID17;
    __type9 TMPTR17;
    __type9 TMDF017;
    __type9 TMDF117;
    __type9 TMID18;
    __type9 TMPTR18;
    __type9 TMDF018;
    __type9 TMDF118;
    __type9 TMID19;
    __type9 TMPTR19;
    __type9 TMDF019;
    __type9 TMDF119;
    __type9 TMID20;
    __type9 TMPTR20;
    __type9 TMDF020;
    __type9 TMDF120;
    __type9 TMID21;
    __type9 TMPTR21;
    __type9 TMDF021;
    __type9 TMDF121;
    __type9 TMID22;
    __type9 TMPTR22;
    __type9 TMDF022;
    __type9 TMDF122;
    __type9 TMID23;
    __type9 TMPTR23;
    __type9 TMDF023;
    __type9 TMDF123;
    __type9 TMID24;
    __type9 TMPTR24;
    __type9 TMDF024;
    __type9 TMDF124;
    __type9 TMID25;
    __type9 TMPTR25;
    __type9 TMDF025;
    __type9 TMDF125;
    __type9 TMID26;
    __type9 TMPTR26;
    __type9 TMDF026;
    __type9 TMDF126;
    __type9 TMID27;
    __type9 TMPTR27;
    __type9 TMDF027;
    __type9 TMDF127;
    __type9 TMID28;
    __type9 TMPTR28;
    __type9 TMDF028;
    __type9 TMDF128;
    __type9 TMID29;
    __type9 TMPTR29;
    __type9 TMDF029;
    __type9 TMDF129;
    __type9 TMID30;
    __type9 TMPTR30;
    __type9 TMDF030;
    __type9 TMDF130;
    __type9 TMID31;
    __type9 TMPTR31;
    __type9 TMDF031;
    __type9 TMDF131;
    __type9 TMID32;
    __type9 TMPTR32;
    __type9 TMDF032;
    __type9 TMDF132;
    __type9 TMID33;
    __type9 TMPTR33;
    __type9 TMDF033;
    __type9 TMDF133;
    __type9 TMID34;
    __type9 TMPTR34;
    __type9 TMDF034;
    __type9 TMDF134;
    __type9 TMID35;
    __type9 TMPTR35;
    __type9 TMDF035;
    __type9 TMDF135;
    __type9 TMID36;
    __type9 TMPTR36;
    __type9 TMDF036;
    __type9 TMDF136;
    __type9 TMID37;
    __type9 TMPTR37;
    __type9 TMDF037;
    __type9 TMDF137;
    __type9 TMID38;
    __type9 TMPTR38;
    __type9 TMDF038;
    __type9 TMDF138;
    __type9 TMID39;
    __type9 TMPTR39;
    __type9 TMDF039;
    __type9 TMDF139;
    __type9 TMID40;
    __type9 TMPTR40;
    __type9 TMDF040;
    __type9 TMDF140;
    __type9 TMID41;
    __type9 TMPTR41;
    __type9 TMDF041;
    __type9 TMDF141;
    __type9 TMID42;
    __type9 TMPTR42;
    __type9 TMDF042;
    __type9 TMDF142;
    __type9 TMID43;
    __type9 TMPTR43;
    __type9 TMDF043;
    __type9 TMDF143;
    __type9 TMID44;
    __type9 TMPTR44;
    __type9 TMDF044;
    __type9 TMDF144;
    __type9 TMID45;
    __type9 TMPTR45;
    __type9 TMDF045;
    __type9 TMDF145;
    __type9 TMID46;
    __type9 TMPTR46;
    __type9 TMDF046;
    __type9 TMDF146;
    __type9 TMID47;
    __type9 TMPTR47;
    __type9 TMDF047;
    __type9 TMDF147;
    uint8  dummy58[1280];
    const __type9 THLACC0;
    const __type9 THLACC1;
    const __type9 THLACC2;
    uint8  dummy59[244];
    __type9 RPGACC0;
    __type9 RPGACC1;
    __type9 RPGACC2;
    __type9 RPGACC3;
    __type9 RPGACC4;
    __type9 RPGACC5;
    __type9 RPGACC6;
    __type9 RPGACC7;
    __type9 RPGACC8;
    __type9 RPGACC9;
    __type9 RPGACC10;
    __type9 RPGACC11;
    __type9 RPGACC12;
    __type9 RPGACC13;
    __type9 RPGACC14;
    __type9 RPGACC15;
    __type9 RPGACC16;
    __type9 RPGACC17;
    __type9 RPGACC18;
    __type9 RPGACC19;
    __type9 RPGACC20;
    __type9 RPGACC21;
    __type9 RPGACC22;
    __type9 RPGACC23;
    __type9 RPGACC24;
    __type9 RPGACC25;
    __type9 RPGACC26;
    __type9 RPGACC27;
    __type9 RPGACC28;
    __type9 RPGACC29;
    __type9 RPGACC30;
    __type9 RPGACC31;
    __type9 RPGACC32;
    __type9 RPGACC33;
    __type9 RPGACC34;
    __type9 RPGACC35;
    __type9 RPGACC36;
    __type9 RPGACC37;
    __type9 RPGACC38;
    __type9 RPGACC39;
    __type9 RPGACC40;
    __type9 RPGACC41;
    __type9 RPGACC42;
    __type9 RPGACC43;
    __type9 RPGACC44;
    __type9 RPGACC45;
    __type9 RPGACC46;
    __type9 RPGACC47;
    __type9 RPGACC48;
    __type9 RPGACC49;
    __type9 RPGACC50;
    __type9 RPGACC51;
    __type9 RPGACC52;
    __type9 RPGACC53;
    __type9 RPGACC54;
    __type9 RPGACC55;
    __type9 RPGACC56;
    __type9 RPGACC57;
    __type9 RPGACC58;
    __type9 RPGACC59;
    __type9 RPGACC60;
    __type9 RPGACC61;
    __type9 RPGACC62;
    __type9 RPGACC63;
} __type32;
typedef struct{
    __type17 CTL0;
    uint8  dummy60[3];
    const uint32 STR0;
    uint16 STCR0;
    uint8  dummy61[6];
    uint32 CTL1;
    uint16 CTL2;
    uint8  dummy62[2];
    __type18 EMU;
    uint8  dummy63[4071];
    uint32 MCTL1;
    uint32 MCTL2;
    uint32 TX0W;
    uint16 TX0H;
    uint8  dummy64[2];
    const uint32 RX0W;
    const uint16 RX0H;
    uint8  dummy65[2];
    uint32 MRWP0;
    uint8  dummy66[36];
    uint16 MCTL0;
    uint8  dummy67[2];
    uint32 CFG0;
    uint32 CFG1;
    uint32 CFG2;
    uint32 CFG3;
    uint8  dummy68[20];
    uint16 BRS0;
    uint8  dummy69[2];
    uint16 BRS1;
    uint8  dummy70[2];
    uint16 BRS2;
    uint8  dummy71[2];
    uint16 BRS3;
} __type33;
typedef struct{
    __type19 CTL0;
    uint8  dummy72[3];
    const uint32 STR0;
    uint16 STCR0;
    uint8  dummy73[6];
    uint32 CTL1;
    uint16 CTL2;
    uint8  dummy74[2];
    __type18 EMU;
    uint8  dummy75[4071];
    __type20 BCTL0;
    uint8  dummy76[3];
    uint32 TX0W;
    uint16 TX0H;
    uint8  dummy77[2];
    const uint16 RX0;
    uint8  dummy78[2];
    uint32 CFG0;
} __type34;
typedef struct{
    uint8  SST;
    uint8  dummy79[11];
    uint16 SSER0;
    uint8  dummy80[6];
    uint16 SSER2;
    uint8  dummy81[102];
    uint8  HIZCEN0;
    uint8  dummy82[15];
    uint16 ADTEN400;
    uint8  dummy83[2];
    uint16 ADTEN401;
    uint8  dummy84[2];
    uint16 ADTEN402;
    uint8  dummy85[38];
    uint32 REG200;
    uint32 REG201;
    uint32 REG202;
    uint32 REG203;
    uint8  dummy86[24];
    uint32 REG30;
    uint32 REG31;
} __type35;
typedef struct{
    uint16 CDR0;
    uint8  dummy87[2];
    uint16 CDR1;
    uint8  dummy88[2];
    uint16 CDR2;
    uint8  dummy89[2];
    uint16 CDR3;
    uint8  dummy90[2];
    uint16 CDR4;
    uint8  dummy91[2];
    uint16 CDR5;
    uint8  dummy92[2];
    uint16 CDR6;
    uint8  dummy93[2];
    uint16 CDR7;
    uint8  dummy94[2];
    uint16 CDR8;
    uint8  dummy95[2];
    uint16 CDR9;
    uint8  dummy96[2];
    uint16 CDR10;
    uint8  dummy97[2];
    uint16 CDR11;
    uint8  dummy98[2];
    uint16 CDR12;
    uint8  dummy99[2];
    uint16 CDR13;
    uint8  dummy100[2];
    uint16 CDR14;
    uint8  dummy101[2];
    uint16 CDR15;
    uint8  dummy102[2];
    uint16 TOL;
    uint8  dummy103[2];
    uint16 RDT;
    uint8  dummy104[2];
    const uint16 RSF;
    uint8  dummy105[2];
    uint16 TRO;
    uint8  dummy106[2];
    uint16 TME;
    uint8  dummy107[2];
    uint16 TDL;
    uint8  dummy108[2];
    uint16 TO;
    uint8  dummy109[2];
    uint16 TOE;
    uint8  dummy110[34];
    const uint16 CNT0;
    uint8  dummy111[2];
    const uint16 CNT1;
    uint8  dummy112[2];
    const uint16 CNT2;
    uint8  dummy113[2];
    const uint16 CNT3;
    uint8  dummy114[2];
    const uint16 CNT4;
    uint8  dummy115[2];
    const uint16 CNT5;
    uint8  dummy116[2];
    const uint16 CNT6;
    uint8  dummy117[2];
    const uint16 CNT7;
    uint8  dummy118[2];
    const uint16 CNT8;
    uint8  dummy119[2];
    const uint16 CNT9;
    uint8  dummy120[2];
    const uint16 CNT10;
    uint8  dummy121[2];
    const uint16 CNT11;
    uint8  dummy122[2];
    const uint16 CNT12;
    uint8  dummy123[2];
    const uint16 CNT13;
    uint8  dummy124[2];
    const uint16 CNT14;
    uint8  dummy125[2];
    const uint16 CNT15;
    uint8  dummy126[2];
    uint8  CMUR0;
    uint8  dummy127[3];
    uint8  CMUR1;
    uint8  dummy128[3];
    uint8  CMUR2;
    uint8  dummy129[3];
    uint8  CMUR3;
    uint8  dummy130[3];
    uint8  CMUR4;
    uint8  dummy131[3];
    uint8  CMUR5;
    uint8  dummy132[3];
    uint8  CMUR6;
    uint8  dummy133[3];
    uint8  CMUR7;
    uint8  dummy134[3];
    uint8  CMUR8;
    uint8  dummy135[3];
    uint8  CMUR9;
    uint8  dummy136[3];
    uint8  CMUR10;
    uint8  dummy137[3];
    uint8  CMUR11;
    uint8  dummy138[3];
    uint8  CMUR12;
    uint8  dummy139[3];
    uint8  CMUR13;
    uint8  dummy140[3];
    uint8  CMUR14;
    uint8  dummy141[3];
    uint8  CMUR15;
    uint8  dummy142[67];
    const uint8  CSR0;
    uint8  dummy143[3];
    const uint8  CSR1;
    uint8  dummy144[3];
    const uint8  CSR2;
    uint8  dummy145[3];
    const uint8  CSR3;
    uint8  dummy146[3];
    const uint8  CSR4;
    uint8  dummy147[3];
    const uint8  CSR5;
    uint8  dummy148[3];
    const uint8  CSR6;
    uint8  dummy149[3];
    const uint8  CSR7;
    uint8  dummy150[3];
    const uint8  CSR8;
    uint8  dummy151[3];
    const uint8  CSR9;
    uint8  dummy152[3];
    const uint8  CSR10;
    uint8  dummy153[3];
    const uint8  CSR11;
    uint8  dummy154[3];
    const uint8  CSR12;
    uint8  dummy155[3];
    const uint8  CSR13;
    uint8  dummy156[3];
    const uint8  CSR14;
    uint8  dummy157[3];
    const uint8  CSR15;
    uint8  dummy158[3];
    uint8  CSC0;
    uint8  dummy159[3];
    uint8  CSC1;
    uint8  dummy160[3];
    uint8  CSC2;
    uint8  dummy161[3];
    uint8  CSC3;
    uint8  dummy162[3];
    uint8  CSC4;
    uint8  dummy163[3];
    uint8  CSC5;
    uint8  dummy164[3];
    uint8  CSC6;
    uint8  dummy165[3];
    uint8  CSC7;
    uint8  dummy166[3];
    uint8  CSC8;
    uint8  dummy167[3];
    uint8  CSC9;
    uint8  dummy168[3];
    uint8  CSC10;
    uint8  dummy169[3];
    uint8  CSC11;
    uint8  dummy170[3];
    uint8  CSC12;
    uint8  dummy171[3];
    uint8  CSC13;
    uint8  dummy172[3];
    uint8  CSC14;
    uint8  dummy173[3];
    uint8  CSC15;
    uint8  dummy174[3];
    const uint16 TE;
    uint8  dummy175[2];
    uint16 TS;
    uint8  dummy176[2];
    uint16 TT;
    uint8  dummy177[54];
    uint16 CMOR0;
    uint8  dummy178[2];
    uint16 CMOR1;
    uint8  dummy179[2];
    uint16 CMOR2;
    uint8  dummy180[2];
    uint16 CMOR3;
    uint8  dummy181[2];
    uint16 CMOR4;
    uint8  dummy182[2];
    uint16 CMOR5;
    uint8  dummy183[2];
    uint16 CMOR6;
    uint8  dummy184[2];
    uint16 CMOR7;
    uint8  dummy185[2];
    uint16 CMOR8;
    uint8  dummy186[2];
    uint16 CMOR9;
    uint8  dummy187[2];
    uint16 CMOR10;
    uint8  dummy188[2];
    uint16 CMOR11;
    uint8  dummy189[2];
    uint16 CMOR12;
    uint8  dummy190[2];
    uint16 CMOR13;
    uint8  dummy191[2];
    uint16 CMOR14;
    uint8  dummy192[2];
    uint16 CMOR15;
    uint8  dummy193[2];
    uint16 TPS;
    uint8  dummy194[2];
    uint8  BRS;
    uint8  dummy195[3];
    uint16 TOM;
    uint8  dummy196[2];
    uint16 TOC;
    uint8  dummy197[2];
    uint16 TDE;
    uint8  dummy198[2];
    uint16 TDM;
    uint8  dummy199[2];
    uint16 TRE;
    uint8  dummy200[2];
    uint16 TRC;
    uint8  dummy201[2];
    uint16 RDE;
    uint8  dummy202[2];
    uint16 RDM;
    uint8  dummy203[2];
    uint16 RDS;
    uint8  dummy204[2];
    uint16 RDC;
    uint8  dummy205[34];
    uint8  EMU;
} __type36;
typedef struct{
    uint32 CDR0;
    uint32 CDR1;
    uint32 CDR2;
    uint32 CDR3;
    const uint32 CNT0;
    const uint32 CNT1;
    const uint32 CNT2;
    const uint32 CNT3;
    uint8  CMUR0;
    uint8  dummy206[3];
    uint8  CMUR1;
    uint8  dummy207[3];
    uint8  CMUR2;
    uint8  dummy208[3];
    uint8  CMUR3;
    uint8  dummy209[3];
    const uint8  CSR0;
    uint8  dummy210[3];
    const uint8  CSR1;
    uint8  dummy211[3];
    const uint8  CSR2;
    uint8  dummy212[3];
    const uint8  CSR3;
    uint8  dummy213[3];
    uint8  CSC0;
    uint8  dummy214[3];
    uint8  CSC1;
    uint8  dummy215[3];
    uint8  CSC2;
    uint8  dummy216[3];
    uint8  CSC3;
    uint8  dummy217[3];
    const uint8  TE;
    uint8  dummy218[3];
    uint8  TS;
    uint8  dummy219[3];
    uint8  TT;
    uint8  dummy220[3];
    uint8  TO;
    uint8  dummy221[3];
    uint8  TOE;
    uint8  dummy222[3];
    uint8  TOL;
    uint8  dummy223[3];
    uint8  RDT;
    uint8  dummy224[3];
    const uint8  RSF;
    uint8  dummy225[19];
    uint16 CMOR0;
    uint8  dummy226[2];
    uint16 CMOR1;
    uint8  dummy227[2];
    uint16 CMOR2;
    uint8  dummy228[2];
    uint16 CMOR3;
    uint8  dummy229[2];
    uint16 TPS;
    uint8  dummy230[2];
    uint8  BRS;
    uint8  dummy231[3];
    uint8  TOM;
    uint8  dummy232[3];
    uint8  TOC;
    uint8  dummy233[3];
    uint8  RDE;
    uint8  dummy234[3];
    uint8  RDM;
    uint8  dummy235[3];
    uint8  EMU;
} __type37;
typedef struct{
    uint8  CTL;
    uint8  dummy236[3];
    const uint8  STR;
    uint8  dummy237[3];
    uint8  STC;
    uint8  dummy238[3];
    uint8  EMU;
    uint8  dummy239[19];
    const uint8  QUE0;
    uint8  dummy240[3];
    const uint8  QUE1;
    uint8  dummy241[3];
    const uint8  QUE2;
    uint8  dummy242[3];
    const uint8  QUE3;
    uint8  dummy243[3];
    const uint8  QUE4;
    uint8  dummy244[3];
    const uint8  QUE5;
    uint8  dummy245[3];
    const uint8  QUE6;
    uint8  dummy246[3];
    const uint8  QUE7;
    uint8  dummy247[3];
    uint32 PVCR00_01;
    uint32 PVCR02_03;
    uint32 PVCR04_05;
    uint32 PVCR06_07;
    uint32 PVCR08_09;
    uint32 PVCR10_11;
    uint32 PVCR12_13;
    uint32 PVCR14_15;
    uint32 PVCR16_17;
    uint32 PVCR18_19;
    uint32 PVCR20_21;
    uint32 PVCR22_23;
} __type38;
typedef struct{
    uint16 CSDR;
    uint8  dummy248[2];
    uint16 CRDR;
    uint8  dummy249[2];
    uint16 CTDR;
    uint8  dummy250[2];
    uint8  RDT;
    uint8  dummy251[3];
    const uint8  RSF;
    uint8  dummy252[3];
    const uint16 CNT;
    uint8  dummy253[10];
    uint8  CTL;
    uint8  dummy254[3];
    const uint16 CSBR;
    uint8  dummy255[2];
    const uint16 CRBR;
    uint8  dummy256[2];
    const uint16 CTBR;
    uint8  dummy257[18];
} __type39;
typedef struct{
    uint16 BRS0;
    uint8  dummy258[2];
    uint16 BRS1;
    uint8  dummy259[2];
    uint16 BRS2;
    uint8  dummy260[2];
    uint16 BRS3;
    uint8  dummy261[2];
    const uint8  TE;
    uint8  dummy262[3];
    uint8  TS;
    uint8  dummy263[3];
    uint8  TT;
    uint8  dummy264[3];
    uint8  EMU;
} __type40;
typedef struct{
    uint16 CCR0;
    uint8  dummy265[2];
    uint16 CCR1;
    uint8  dummy266[2];
    uint16 CNT;
    uint8  dummy267[2];
    const uint8  FLG;
    uint8  dummy268[3];
    uint8  FGC;
    uint8  dummy269[3];
    const uint8  TE;
    uint8  dummy270[3];
    uint8  TS;
    uint8  dummy271[3];
    uint8  TT;
    uint8  dummy272[3];
    uint8  IOC0;
    uint8  dummy273[31];
    uint16 CTL;
    uint8  dummy274[2];
    uint8  IOC1;
    uint8  dummy275[3];
    uint8  EMU;
} __type41;
typedef struct{
    const uint16 FLG;
    uint8  dummy276[2];
    uint8  ACWE;
    uint8  dummy277[3];
    uint8  ACTS;
    uint8  dummy278[3];
    uint8  ACTT;
    uint8  dummy279[7];
    uint8  OPHS;
    uint8  dummy280[3];
    uint8  OPHT;
    uint8  dummy281[7];
    uint16 CTL0;
    uint8  dummy282[2];
    uint8  CTL1;
    uint8  dummy283[3];
    uint8  EMU;
} __type42;
typedef struct{
    uint32 CMP;
    const uint32 CNT;
    uint8  dummy284[8];
    const uint8  TE;
    uint8  dummy285[3];
    uint8  TS;
    uint8  dummy286[3];
    uint8  TT;
    uint8  dummy287[7];
    uint8  CTL;
    uint8  dummy288[3];
    uint8  EMU;
} __type43;
typedef struct{
    uint8  WDTE;
    uint8  dummy289[3];
    uint8  EVAC;
    uint8  dummy290[3];
    const uint8  REF;
    uint8  dummy291[3];
    uint8  MD;
    uint8  dummy292[4083];
} __type44;
typedef struct{
    __type9 VCR00;
    __type9 VCR01;
    __type9 VCR02;
    __type9 VCR03;
    __type9 VCR04;
    __type9 VCR05;
    __type9 VCR06;
    __type9 VCR07;
    __type9 VCR08;
    __type9 VCR09;
    __type9 VCR10;
    __type9 VCR11;
    __type9 VCR12;
    __type9 VCR13;
    __type9 VCR14;
    __type9 VCR15;
    __type9 VCR16;
    __type9 VCR17;
    __type9 VCR18;
    __type9 VCR19;
    __type9 VCR20;
    __type9 VCR21;
    __type9 VCR22;
    __type9 VCR23;
    __type9 VCR24;
    __type9 VCR25;
    __type9 VCR26;
    __type9 VCR27;
    __type9 VCR28;
    uint8  dummy293[128];
    const __type9 PWDVCR;
    uint8  dummy294[8];
    const __type16 DR00;
    const __type16 DR02;
    const __type16 DR04;
    const __type16 DR06;
    const __type16 DR08;
    const __type16 DR10;
    const __type16 DR12;
    const __type16 DR14;
    const __type16 DR16;
    const __type16 DR18;
    const __type16 DR20;
    const __type16 DR22;
    const __type16 DR24;
    const __type16 DR26;
    const __type16 DR28;
    uint8  dummy295[60];
    const __type16 PWDTSNDR;
    uint8  dummy296[132];
    const uint32 DIR00;
    const uint32 DIR01;
    const uint32 DIR02;
    const uint32 DIR03;
    const uint32 DIR04;
    const uint32 DIR05;
    const uint32 DIR06;
    const uint32 DIR07;
    const uint32 DIR08;
    const uint32 DIR09;
    const uint32 DIR10;
    const uint32 DIR11;
    const uint32 DIR12;
    const uint32 DIR13;
    const uint32 DIR14;
    const uint32 DIR15;
    const uint32 DIR16;
    const uint32 DIR17;
    const uint32 DIR18;
    const uint32 DIR19;
    const uint32 DIR20;
    const uint32 DIR21;
    const uint32 DIR22;
    const uint32 DIR23;
    const uint32 DIR24;
    const uint32 DIR25;
    const uint32 DIR26;
    const uint32 DIR27;
    const uint32 DIR28;
    uint8  dummy297[128];
    const uint32 PWDDIR;
    uint8  dummy298[8];
    __type9 ADHALTR;
    __type9 ADCR;
    const __type16 SGSTR;
    const __type9 MPXCURR;
    uint8  dummy299[4];
    __type9 THSMPSTCR;
    __type9 THCR;
    __type9 THAHLDSTCR;
    __type9 THBHLDSTCR;
    __type9 THACR;
    __type9 THBCR;
    __type9 THER;
    __type9 THGSR;
    __type9 SFTCR;
    __type16 ULLMTBR0;
    __type16 ULLMTBR1;
    __type16 ULLMTBR2;
    __type9 ECR;
    const __type9 ULER;
    const __type9 OWER;
    __type9 DGCTL0;
    __type16 DGCTL1;
    __type16 PDCTL1;
    __type9 PDCTL2;
    uint8  dummy300[32];
    __type9 SMPCR;
    uint8  dummy301[4];
    uint8  EMU;
    uint8  dummy302[183];
    __type9 SGSTCR1;
    uint8  dummy303[4];
    __type9 SGCR1;
    __type9 SGVCSP1;
    __type9 SGVCEP1;
    __type9 SGMCYCR1;
    __type9 SGSEFCR1;
    __type16 SGTSEL1;
    uint8  dummy304[32];
    __type9 SGSTCR2;
    uint8  dummy305[4];
    __type9 SGCR2;
    __type9 SGVCSP2;
    __type9 SGVCEP2;
    __type9 SGMCYCR2;
    __type9 SGSEFCR2;
    __type16 SGTSEL2;
    uint8  dummy306[32];
    __type9 SGSTCR3;
    uint8  dummy307[4];
    __type9 SGCR3;
    __type9 SGVCSP3;
    __type9 SGVCEP3;
    __type9 SGMCYCR3;
    __type9 SGSEFCR3;
    __type16 SGTSEL3;
    uint8  dummy308[40];
    __type9 PWDSGCR;
    uint8  dummy309[12];
    __type9 PWDSGSEFCR;
} __type45;
typedef struct{
    uint32 CIN;
    uint32 COUT;
    uint8  dummy310[24];
    uint8  CTL;
} __type46;
typedef struct{
    __type21 KRM;
} __type47;
typedef struct{
    uint8  CTL0;
    uint8  dummy311[7];
    uint16 CMPL;
    uint8  dummy312[2];
    uint16 CMPH;
    uint8  dummy313[2];
    uint8  PCMD;
    uint8  dummy314[3];
    const uint8  PS;
    uint8  dummy315[3];
    uint8  EMU0;
} __type48;
typedef struct{
    uint32 TEST;
    const uint32 TESTS;
} __type49;

__IOREG(FLMDCNT, 0xFFA00000, __READ_WRITE, uint32);
__IOREG(FLMDPCMD, 0xFFA00004, __READ_WRITE, uint32);
__IOREG(FLMDPS, 0xFFA00008, __READ, uint32);
__IOREG(SELB_TAUD0I, 0xFFBC0200, __READ_WRITE, uint16);
__IOREG(SELB_INTC2, 0xFFBC0304, __READ_WRITE, uint16);
__IOREG(SELB_READTEST, 0xFFBC0600, __READ_WRITE, uint8);
__IOREG(SLPWGA0, 0xFFBC1000, __READ_WRITE, uint32);
__IOREG(SCTLR, 0xFFBC2000, __READ_WRITE, uint32);
__IOREG(EVFR, 0xFFBC2004, __READ_WRITE, uint32);
__IOREG(DPSELR0, 0xFFBC2008, __READ_WRITE, uint32);
__IOREG(DPSELRM, 0xFFBC200C, __READ_WRITE, uint32);
__IOREG(DPSELRML, 0xFFBC200C, __READ_WRITE, uint16);
__IOREG(DPSELR1, 0xFFBC200C, __READ_WRITE, uint8);
__IOREG(DPSELR2, 0xFFBC200D, __READ_WRITE, uint8);
__IOREG(DPSELRMH, 0xFFBC200E, __READ_WRITE, uint16);
__IOREG(DPSELR3, 0xFFBC200E, __READ_WRITE, uint8);
__IOREG(DPSELR4, 0xFFBC200F, __READ_WRITE, uint8);
__IOREG(DPSELRH, 0xFFBC2010, __READ_WRITE, uint32);
__IOREG(DPSELRHL, 0xFFBC2010, __READ_WRITE, uint16);
__IOREG(DPSELR5, 0xFFBC2010, __READ_WRITE, uint8);
__IOREG(DPSELR6, 0xFFBC2011, __READ_WRITE, uint8);
__IOREG(DPSELRHH, 0xFFBC2012, __READ_WRITE, uint16);
__IOREG(DPSELR7, 0xFFBC2012, __READ_WRITE, uint8);
__IOREG(DPDSR0, 0xFFBC2014, __READ_WRITE, uint32);
__IOREG(DPDSRM, 0xFFBC2018, __READ_WRITE, uint32);
__IOREG(DPDSRML, 0xFFBC2018, __READ_WRITE, uint16);
__IOREG(DPDSR1, 0xFFBC2018, __READ_WRITE, uint8);
__IOREG(DPDSR2, 0xFFBC2019, __READ_WRITE, uint8);
__IOREG(DPDSRMH, 0xFFBC201A, __READ_WRITE, uint16);
__IOREG(DPDSR3, 0xFFBC201A, __READ_WRITE, uint8);
__IOREG(DPDSR4, 0xFFBC201B, __READ_WRITE, uint8);
__IOREG(DPDSRH, 0xFFBC201C, __READ_WRITE, uint32);
__IOREG(DPDSRHL, 0xFFBC201C, __READ_WRITE, uint16);
__IOREG(DPDSR5, 0xFFBC201C, __READ_WRITE, uint8);
__IOREG(DPDSR6, 0xFFBC201D, __READ_WRITE, uint8);
__IOREG(DPDSRHH, 0xFFBC201E, __READ_WRITE, uint16);
__IOREG(DPDSR7, 0xFFBC201E, __READ_WRITE, uint8);
__IOREG(DPDIMR0, 0xFFBC2020, __READ, uint32);
__IOREG(DPDIMR1, 0xFFBC2024, __READ, uint8);
__IOREG(DPDIMR2, 0xFFBC2028, __READ, uint8);
__IOREG(DPDIMR3, 0xFFBC202C, __READ, uint8);
__IOREG(DPDIMR4, 0xFFBC2030, __READ, uint8);
__IOREG(DPDIMR5, 0xFFBC2034, __READ, uint8);
__IOREG(DPDIMR6, 0xFFBC2038, __READ, uint8);
__IOREG(DPDIMR7, 0xFFBC203C, __READ, uint8);
__IOREG(CNTVAL, 0xFFBC2040, __READ_WRITE, uint16);
__IOREG(SOSTR, 0xFFBC2044, __READ, uint8);
__IOREG(P0, 0xFFC10000, __READ_WRITE, uint16);
__IOREG(P8, 0xFFC10020, __READ_WRITE, uint16);
__IOREG(P9, 0xFFC10024, __READ_WRITE, uint16);
__IOREG(P10, 0xFFC10028, __READ_WRITE, uint16);
__IOREG(AP0, 0xFFC100C8, __READ_WRITE, uint16);
__IOREG(PSR0, 0xFFC10100, __READ_WRITE, uint32);
__IOREG(PSR8, 0xFFC10120, __READ_WRITE, uint32);
__IOREG(PSR9, 0xFFC10124, __READ_WRITE, uint32);
__IOREG(PSR10, 0xFFC10128, __READ_WRITE, uint32);
__IOREG(APSR0, 0xFFC101C8, __READ_WRITE, uint32);
__IOREG(PPR0, 0xFFC10200, __READ, uint16);
__IOREG(PPR8, 0xFFC10220, __READ, uint16);
__IOREG(PPR9, 0xFFC10224, __READ, uint16);
__IOREG(PPR10, 0xFFC10228, __READ, uint16);
__IOREG(APPR0, 0xFFC102C8, __READ, uint16);
__IOREG(PM0, 0xFFC10300, __READ_WRITE, uint16);
__IOREG(PM8, 0xFFC10320, __READ_WRITE, uint16);
__IOREG(PM9, 0xFFC10324, __READ_WRITE, uint16);
__IOREG(PM10, 0xFFC10328, __READ_WRITE, uint16);
__IOREG(APM0, 0xFFC103C8, __READ_WRITE, uint16);
__IOREG(PMC0, 0xFFC10400, __READ_WRITE, uint16);
__IOREG(PMC8, 0xFFC10420, __READ_WRITE, uint16);
__IOREG(PMC9, 0xFFC10424, __READ_WRITE, uint16);
__IOREG(PMC10, 0xFFC10428, __READ_WRITE, uint16);
__IOREG(PFC0, 0xFFC10500, __READ_WRITE, uint16);
__IOREG(PFC8, 0xFFC10520, __READ_WRITE, uint16);
__IOREG(PFC9, 0xFFC10524, __READ_WRITE, uint16);
__IOREG(PFC10, 0xFFC10528, __READ_WRITE, uint16);
__IOREG(PFCE0, 0xFFC10600, __READ_WRITE, uint16);
__IOREG(PFCE8, 0xFFC10620, __READ_WRITE, uint16);
__IOREG(PFCE9, 0xFFC10624, __READ_WRITE, uint16);
__IOREG(PFCE10, 0xFFC10628, __READ_WRITE, uint16);
__IOREG(PNOT0, 0xFFC10700, __READ_WRITE, uint16);
__IOREG(PNOT8, 0xFFC10720, __READ_WRITE, uint16);
__IOREG(PNOT9, 0xFFC10724, __READ_WRITE, uint16);
__IOREG(PNOT10, 0xFFC10728, __READ_WRITE, uint16);
__IOREG(APNOT0, 0xFFC107C8, __READ_WRITE, uint16);
__IOREG(PMSR0, 0xFFC10800, __READ_WRITE, uint32);
__IOREG(PMSR8, 0xFFC10820, __READ_WRITE, uint32);
__IOREG(PMSR9, 0xFFC10824, __READ_WRITE, uint32);
__IOREG(PMSR10, 0xFFC10828, __READ_WRITE, uint32);
__IOREG(APMSR0, 0xFFC108C8, __READ_WRITE, uint32);
__IOREG(PMCSR0, 0xFFC10900, __READ_WRITE, uint32);
__IOREG(PMCSR8, 0xFFC10920, __READ_WRITE, uint32);
__IOREG(PMCSR9, 0xFFC10924, __READ_WRITE, uint32);
__IOREG(PMCSR10, 0xFFC10928, __READ_WRITE, uint32);
__IOREG(PFCAE0, 0xFFC10A00, __READ_WRITE, uint16);
__IOREG(PFCAE10, 0xFFC10A28, __READ_WRITE, uint16);
__IOREG(PIBC0, 0xFFC14000, __READ_WRITE, uint16);
__IOREG(PIBC8, 0xFFC14020, __READ_WRITE, uint16);
__IOREG(PIBC9, 0xFFC14024, __READ_WRITE, uint16);
__IOREG(PIBC10, 0xFFC14028, __READ_WRITE, uint16);
__IOREG(APIBC0, 0xFFC140C8, __READ_WRITE, uint16);
__IOREG(PBDC0, 0xFFC14100, __READ_WRITE, uint16);
__IOREG(PBDC8, 0xFFC14120, __READ_WRITE, uint16);
__IOREG(PBDC9, 0xFFC14124, __READ_WRITE, uint16);
__IOREG(PBDC10, 0xFFC14128, __READ_WRITE, uint16);
__IOREG(APBDC0, 0xFFC141C8, __READ_WRITE, uint16);
__IOREG(PIPC0, 0xFFC14200, __READ_WRITE, uint16);
__IOREG(PIPC10, 0xFFC14228, __READ_WRITE, uint16);
__IOREG(PU0, 0xFFC14300, __READ_WRITE, uint16);
__IOREG(PU8, 0xFFC14320, __READ_WRITE, uint16);
__IOREG(PU9, 0xFFC14324, __READ_WRITE, uint16);
__IOREG(PU10, 0xFFC14328, __READ_WRITE, uint16);
__IOREG(PD0, 0xFFC14400, __READ_WRITE, uint16);
__IOREG(PD8, 0xFFC14420, __READ_WRITE, uint16);
__IOREG(PD9, 0xFFC14424, __READ_WRITE, uint16);
__IOREG(PD10, 0xFFC14428, __READ_WRITE, uint16);
__IOREG(PODC0, 0xFFC14500, __READ_WRITE, uint32);
__IOREG(PODC8, 0xFFC14520, __READ_WRITE, uint32);
__IOREG(PODC9, 0xFFC14524, __READ_WRITE, uint32);
__IOREG(PODC10, 0xFFC14528, __READ_WRITE, uint32);
__IOREG(PDSC0, 0xFFC14600, __READ_WRITE, uint32);
__IOREG(PDSC10, 0xFFC14628, __READ_WRITE, uint32);
__IOREG(PIS0, 0xFFC14700, __READ_WRITE, uint16);
__IOREG(PIS10, 0xFFC14728, __READ_WRITE, uint16);
__IOREG(PPROTS0, 0xFFC14B00, __READ, uint32);
__IOREG(PPROTS8, 0xFFC14B20, __READ, uint32);
__IOREG(PPROTS9, 0xFFC14B24, __READ, uint32);
__IOREG(PPROTS10, 0xFFC14B28, __READ, uint32);
__IOREG(PPCMD0, 0xFFC14C00, __READ_WRITE, uint32);
__IOREG(PPCMD8, 0xFFC14C20, __READ_WRITE, uint32);
__IOREG(PPCMD9, 0xFFC14C24, __READ_WRITE, uint32);
__IOREG(PPCMD10, 0xFFC14C28, __READ_WRITE, uint32);
__IOREG(JP0, 0xFFC20000, __READ_WRITE, uint8);
__IOREG(JPSR0, 0xFFC20010, __READ_WRITE, uint32);
__IOREG(JPPR0, 0xFFC20020, __READ, uint8);
__IOREG(JPM0, 0xFFC20030, __READ_WRITE, uint8);
__IOREG(JPMC0, 0xFFC20040, __READ_WRITE, uint8);
__IOREG(JPFC0, 0xFFC20050, __READ_WRITE, uint8);
__IOREG(JPNOT0, 0xFFC20070, __READ_WRITE, uint8);
__IOREG(JPMSR0, 0xFFC20080, __READ_WRITE, uint32);
__IOREG(JPMCSR0, 0xFFC20090, __READ_WRITE, uint32);
__IOREG(JPIBC0, 0xFFC20400, __READ_WRITE, uint8);
__IOREG(JPBDC0, 0xFFC20410, __READ_WRITE, uint8);
__IOREG(JPU0, 0xFFC20430, __READ_WRITE, uint8);
__IOREG(JPD0, 0xFFC20440, __READ_WRITE, uint8);
__IOREG(JPODC0, 0xFFC20450, __READ_WRITE, uint32);
__IOREG(JPPROTS0, 0xFFC204B0, __READ, uint32);
__IOREG(JPPCMD0, 0xFFC204C0, __READ_WRITE, uint32);
__IOREG(DNFATAUD0ICTL, 0xFFC30000, __READ_WRITE, uint8);
__IOREG(DNFATAUD0IEN, 0xFFC30004, __READ_WRITE, uint16);
__IOREG(DNFATAUD0IENH, 0xFFC30008, __READ_WRITE, uint8);
#define DNFATAUD0IENH0     (((volatile __bitf_T *)0xFFC30008)->bit00)
#define DNFATAUD0IENH1     (((volatile __bitf_T *)0xFFC30008)->bit01)
#define DNFATAUD0IENH2     (((volatile __bitf_T *)0xFFC30008)->bit02)
#define DNFATAUD0IENH3     (((volatile __bitf_T *)0xFFC30008)->bit03)
#define DNFATAUD0IENH4     (((volatile __bitf_T *)0xFFC30008)->bit04)
#define DNFATAUD0IENH5     (((volatile __bitf_T *)0xFFC30008)->bit05)
#define DNFATAUD0IENH6     (((volatile __bitf_T *)0xFFC30008)->bit06)
#define DNFATAUD0IENH7     (((volatile __bitf_T *)0xFFC30008)->bit07)
__IOREG(DNFATAUD0IENL, 0xFFC3000C, __READ_WRITE, uint8);
#define DNFATAUD0IENL0     (((volatile __bitf_T *)0xFFC3000C)->bit00)
#define DNFATAUD0IENL1     (((volatile __bitf_T *)0xFFC3000C)->bit01)
#define DNFATAUD0IENL2     (((volatile __bitf_T *)0xFFC3000C)->bit02)
#define DNFATAUD0IENL3     (((volatile __bitf_T *)0xFFC3000C)->bit03)
#define DNFATAUD0IENL4     (((volatile __bitf_T *)0xFFC3000C)->bit04)
#define DNFATAUD0IENL5     (((volatile __bitf_T *)0xFFC3000C)->bit05)
#define DNFATAUD0IENL6     (((volatile __bitf_T *)0xFFC3000C)->bit06)
#define DNFATAUD0IENL7     (((volatile __bitf_T *)0xFFC3000C)->bit07)
__IOREG(DNFAENCA0ICTL, 0xFFC30060, __READ_WRITE, uint8);
__IOREG(DNFAENCA0IEN, 0xFFC30064, __READ_WRITE, uint16);
__IOREG(DNFAENCA0IENL, 0xFFC3006C, __READ_WRITE, uint8);
#define DNFAENCA0IENL0     (((volatile __bitf_T *)0xFFC3006C)->bit00)
#define DNFAENCA0IENL1     (((volatile __bitf_T *)0xFFC3006C)->bit01)
#define DNFAENCA0IENL2     (((volatile __bitf_T *)0xFFC3006C)->bit02)
#define DNFAENCA0IENL3     (((volatile __bitf_T *)0xFFC3006C)->bit03)
#define DNFAENCA0IENL4     (((volatile __bitf_T *)0xFFC3006C)->bit04)
__IOREG(DNFAADCTL0CTL, 0xFFC300A0, __READ_WRITE, uint8);
__IOREG(DNFAADCTL0EN, 0xFFC300A4, __READ_WRITE, uint16);
__IOREG(DNFAADCTL0ENL, 0xFFC300AC, __READ_WRITE, uint8);
#define DNFAADCTL0ENL0     (((volatile __bitf_T *)0xFFC300AC)->bit00)
#define DNFAADCTL0ENL1     (((volatile __bitf_T *)0xFFC300AC)->bit01)
#define DNFAADCTL0ENL2     (((volatile __bitf_T *)0xFFC300AC)->bit02)
__IOREG(FCLA0CTL0_NMI, 0xFFC34000, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_INTPL, 0xFFC34020, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_INTPL, 0xFFC34024, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_INTPL, 0xFFC34028, __READ_WRITE, uint8);
__IOREG(FCLA0CTL3_INTPL, 0xFFC3402C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL4_INTPL, 0xFFC34030, __READ_WRITE, uint8);
__IOREG(FCLA0CTL5_INTPL, 0xFFC34034, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_INTPH, 0xFFC34048, __READ_WRITE, uint8);
__IOREG(FCLA0CTL3_INTPH, 0xFFC3404C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_ADC0, 0xFFC34060, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_ADC0, 0xFFC34064, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_ADC0, 0xFFC34068, __READ_WRITE, uint8);
__IOREG(EEPRDCYCL, 0xFFC5A010, __READ_WRITE, uint8);
__IOREG(CFECCCTL, 0xFFC62000, __READ_WRITE, uint16);
__IOREG(CFFSTERSTR, 0xFFC62004, __READ, uint32);
__IOREG(CFFSTSTC, 0xFFC62024, __READ_WRITE, uint8);
__IOREG(CFOVFSTR, 0xFFC62028, __READ, uint8);
__IOREG(CFOVFSTC, 0xFFC6202C, __READ_WRITE, uint8);
__IOREG(CFERRINT, 0xFFC62030, __READ_WRITE, uint8);
__IOREG(CFFSTEADR, 0xFFC62034, __READ, uint32);
__IOREG(CFTSTCTL, 0xFFC62054, __READ_WRITE, uint16);
__IOREG(LRECCCTL, 0xFFC63000, __READ_WRITE, uint16);
__IOREG(LRFSTERSTR, 0xFFC63004, __READ, uint32);
__IOREG(LRSTCLR, 0xFFC63024, __READ_WRITE, uint8);
__IOREG(LROVFSTR, 0xFFC63028, __READ, uint8);
__IOREG(LROVFSTC, 0xFFC6302C, __READ_WRITE, uint8);
__IOREG(LRFSTEADR0, 0xFFC63030, __READ, uint32);
__IOREG(LRERRINT, 0xFFC630B0, __READ_WRITE, uint8);
__IOREG(LRTSTCTL, 0xFFC630B4, __READ_WRITE, uint16);
__IOREG(LRTDATBF0, 0xFFC630B8, __READ, uint32);
__IOREG(DFECCCTL, 0xFFC66000, __READ_WRITE, uint16);
__IOREG(DFERSTR, 0xFFC66004, __READ, uint32);
__IOREG(DFERSTC, 0xFFC66008, __READ_WRITE, uint8);
__IOREG(DFERRINT, 0xFFC66014, __READ_WRITE, uint8);
__IOREG(DFTSTCTL, 0xFFC6601C, __READ_WRITE, uint16);
__IOREG(ECCCSIH0CTL, 0xFFC70000, __READ_WRITE, uint16);
__IOREG(ECCCSIH0TMC, 0xFFC70004, __READ_WRITE, uint16);
__IOREG(ECCCSIH0TRC, 0xFFC70008, __READ_WRITE, uint32);
__IOREG(ECCCSIH0ERDB, 0xFFC70008, __READ_WRITE, uint8);
__IOREG(ECCCSIH0ECRD, 0xFFC70009, __READ, uint8);
__IOREG(ECCCSIH0HORD, 0xFFC7000A, __READ, uint8);
__IOREG(ECCCSIH0SYND, 0xFFC7000B, __READ, uint8);
__IOREG(ECCCSIH0TED, 0xFFC7000C, __READ_WRITE, uint32);
__IOREG(ECCRCAN0CTL, 0xFFC71000, __READ_WRITE, uint16);
__IOREG(ECCRCAN0TMC, 0xFFC71004, __READ_WRITE, uint16);
__IOREG(ECCRCAN0TRC, 0xFFC71008, __READ_WRITE, uint32);
__IOREG(ECCRCAN0ERDB, 0xFFC71008, __READ_WRITE, uint8);
__IOREG(ECCRCAN0ECRD, 0xFFC71009, __READ, uint8);
__IOREG(ECCRCAN0HORD, 0xFFC7100A, __READ, uint8);
__IOREG(ECCRCAN0SYND, 0xFFC7100B, __READ, uint8);
__IOREG(ECCRCAN0TED, 0xFFC7100C, __READ_WRITE, uint32);
__IOREG(CVMF, 0xFFF50000, __READ_WRITE, uint32);
__IOREG(CVMDE, 0xFFF50004, __READ, uint32);
__IOREG(CVMDIAG, 0xFFF50014, __READ_WRITE, uint32);
__IOREG(PROTCMDCVM, 0xFFF50100, __READ_WRITE, uint32);
__IOREG(PROTSCVM, 0xFFF50104, __READ, uint32);
__IOREG(PROTCMD0, 0xFFF80000, __READ_WRITE, uint32);
__IOREG(PROTS0, 0xFFF80004, __READ, uint32);
__IOREG(STBC0PSC, 0xFFF80100, __READ_WRITE, uint32);
__IOREG(STBC0STPT, 0xFFF80110, __READ_WRITE, uint32);
__IOREG(WDTNMIF, 0xFFF80200, __READ, uint32);
__IOREG(WDTNMIFC, 0xFFF80208, __READ_WRITE, uint32);
__IOREG(FEINTF, 0xFFF80300, __READ, uint32);
__IOREG(FEINTFMSK, 0xFFF80304, __READ_WRITE, uint32);
__IOREG(FEINTFC, 0xFFF80308, __READ_WRITE, uint32);
__IOREG(WUF0, 0xFFF80400, __READ, uint32);
__IOREG(WUFMSK0, 0xFFF80404, __READ_WRITE, uint32);
__IOREG(WUFC0, 0xFFF80408, __READ_WRITE, uint32);
__IOREG(WUF20, 0xFFF80520, __READ, uint32);
__IOREG(WUFMSK20, 0xFFF80524, __READ_WRITE, uint32);
__IOREG(WUFC20, 0xFFF80528, __READ_WRITE, uint32);
__IOREG(RESF, 0xFFF80760, __READ, uint32);
__IOREG(RESFC, 0xFFF80768, __READ_WRITE, uint32);
__IOREG(RESFR, 0xFFF80860, __READ, uint32);
__IOREG(RESFCR, 0xFFF80868, __READ_WRITE, uint32);
__IOREG(VLVF, 0xFFF80980, __READ, uint32);
__IOREG(VLVFC, 0xFFF80988, __READ_WRITE, uint32);
__IOREG(LVICNT, 0xFFF80A00, __READ_WRITE, uint32);
__IOREG(SWRESA, 0xFFF80A04, __READ_WRITE, uint32);
__IOREG(IOHOLD, 0xFFF80B00, __READ_WRITE, uint32);
__IOREG(ROSCE, 0xFFF81000, __READ_WRITE, uint32);
__IOREG(ROSCS, 0xFFF81004, __READ, uint32);
__IOREG(ROSCSTPM, 0xFFF81018, __READ_WRITE, uint32);
__IOREG(MOSCE, 0xFFF81100, __READ_WRITE, uint32);
__IOREG(MOSCS, 0xFFF81104, __READ, uint32);
__IOREG(MOSCC, 0xFFF81108, __READ_WRITE, uint32);
__IOREG(MOSCST, 0xFFF8110C, __READ_WRITE, uint32);
__IOREG(MOSCSTPM, 0xFFF81118, __READ_WRITE, uint32);
__IOREG(CKSC_AWDTAD_CTL, 0xFFF82000, __READ_WRITE, uint32);
__IOREG(CKSC_AWDTAD_ACT, 0xFFF82008, __READ, uint32);
__IOREG(CKSC_AWDTAD_STPM, 0xFFF82018, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJS_CTL, 0xFFF82100, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJS_ACT, 0xFFF82108, __READ, uint32);
__IOREG(CKSC_ATAUJD_CTL, 0xFFF82200, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJD_ACT, 0xFFF82208, __READ, uint32);
__IOREG(CKSC_ATAUJD_STPM, 0xFFF82218, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAS_CTL, 0xFFF82500, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAS_ACT, 0xFFF82508, __READ, uint32);
__IOREG(CKSC_AADCAD_CTL, 0xFFF82600, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAD_ACT, 0xFFF82608, __READ, uint32);
__IOREG(CKSC_AADCAD_STPM, 0xFFF82618, __READ_WRITE, uint32);
__IOREG(CKSC_AFOUTS_CTL, 0xFFF82700, __READ_WRITE, uint32);
__IOREG(CKSC_AFOUTS_ACT, 0xFFF82708, __READ, uint32);
__IOREG(CKSC_AFOUTS_STPM, 0xFFF82718, __READ_WRITE, uint32);
__IOREG(FOUTDIV, 0xFFF82800, __READ_WRITE, uint32);
__IOREG(FOUTSTAT, 0xFFF82804, __READ, uint32);
__IOREG(PROTCMD1, 0xFFF88000, __READ_WRITE, uint32);
__IOREG(PROTS1, 0xFFF88004, __READ, uint32);
__IOREG(WUF_ISO0, 0xFFF88110, __READ, uint32);
__IOREG(WUFMSK_ISO0, 0xFFF88114, __READ_WRITE, uint32);
__IOREG(WUFC_ISO0, 0xFFF88118, __READ_WRITE, uint32);
__IOREG(PLLE, 0xFFF89000, __READ_WRITE, uint32);
__IOREG(PLLS, 0xFFF89004, __READ, uint32);
__IOREG(PLLC, 0xFFF89008, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKS_CTL, 0xFFF8A000, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKS_ACT, 0xFFF8A008, __READ, uint32);
__IOREG(CKSC_CPUCLKD_CTL, 0xFFF8A100, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKD_ACT, 0xFFF8A108, __READ, uint32);
__IOREG(CKSC_IPERI1S_CTL, 0xFFF8A200, __READ_WRITE, uint32);
__IOREG(CKSC_IPERI1S_ACT, 0xFFF8A208, __READ, uint32);
__IOREG(CKSC_IPERI2S_CTL, 0xFFF8A300, __READ_WRITE, uint32);
__IOREG(CKSC_IPERI2S_ACT, 0xFFF8A308, __READ, uint32);
__IOREG(CKSC_ILINS_CTL, 0xFFF8A400, __READ_WRITE, uint32);
__IOREG(CKSC_ILINS_ACT, 0xFFF8A408, __READ, uint32);
__IOREG(CKSC_ILIND_CTL, 0xFFF8A800, __READ_WRITE, uint32);
__IOREG(CKSC_ILIND_ACT, 0xFFF8A808, __READ, uint32);
__IOREG(CKSC_ILIND_STPM, 0xFFF8A818, __READ_WRITE, uint32);
__IOREG(CKSC_ICANS_CTL, 0xFFF8A900, __READ_WRITE, uint32);
__IOREG(CKSC_ICANS_ACT, 0xFFF8A908, __READ, uint32);
__IOREG(CKSC_ICANS_STPM, 0xFFF8A918, __READ_WRITE, uint32);
__IOREG(CKSC_ICANOSCD_CTL, 0xFFF8AA00, __READ_WRITE, uint32);
__IOREG(CKSC_ICANOSCD_ACT, 0xFFF8AA08, __READ, uint32);
__IOREG(CKSC_ICANOSCD_STPM, 0xFFF8AA18, __READ_WRITE, uint32);
__IOREG(CKSC_ICSIS_CTL, 0xFFF8AB00, __READ_WRITE, uint32);
__IOREG(CKSC_ICSIS_ACT, 0xFFF8AB08, __READ, uint32);
__IOREG(PROTCMDCLMA, 0xFFF8C200, __READ_WRITE, uint32);
__IOREG(PROTSCLMA, 0xFFF8C204, __READ, uint32);
__IOREG(DTRC0, 0xFFFF8300, __READ_WRITE, uint8);
#define DTRC0ADS           (((volatile __bitf_T *)0xFFFF8300)->bit00)
#define DTRC0ERR           (((volatile __bitf_T *)0xFFFF8300)->bit07)
__IOREG(DMCM0, 0xFFFF8304, __READ_WRITE, uint16);
__IOREG(DSA0, 0xFFFF8314, __READ_WRITE, uint32);
__IOREG(DSA0L, 0xFFFF8314, __READ_WRITE, uint16);
__IOREG(DSA0H, 0xFFFF8316, __READ_WRITE, uint16);
__IOREG(DDA0, 0xFFFF8324, __READ_WRITE, uint32);
__IOREG(DDA0L, 0xFFFF8324, __READ_WRITE, uint16);
__IOREG(DDA0H, 0xFFFF8326, __READ_WRITE, uint16);
__IOREG(DTC0, 0xFFFF8332, __READ_WRITE, uint16);
__IOREG(DTCT0, 0xFFFF8338, __READ_WRITE, uint16);
__IOREG(DTS0, 0xFFFF833A, __READ_WRITE, uint8);
#define DTS0DTE            (((volatile __bitf_T *)0xFFFF833A)->bit00)
#define DTS0SR             (((volatile __bitf_T *)0xFFFF833A)->bit01)
#define DTS0DR             (((const volatile __bitf_T *)0xFFFF833A)->bit02)
#define DTS0ER             (((const volatile __bitf_T *)0xFFFF833A)->bit03)
#define DTS0DT             (((volatile __bitf_T *)0xFFFF833A)->bit06)
#define DTS0TC             (((volatile __bitf_T *)0xFFFF833A)->bit07)
__IOREG(DSA1, 0xFFFF8344, __READ_WRITE, uint32);
__IOREG(DSA1L, 0xFFFF8344, __READ_WRITE, uint16);
__IOREG(DSA1H, 0xFFFF8346, __READ_WRITE, uint16);
__IOREG(DDA1, 0xFFFF8354, __READ_WRITE, uint32);
__IOREG(DDA1L, 0xFFFF8354, __READ_WRITE, uint16);
__IOREG(DDA1H, 0xFFFF8356, __READ_WRITE, uint16);
__IOREG(DTC1, 0xFFFF8362, __READ_WRITE, uint16);
__IOREG(DTCT1, 0xFFFF8368, __READ_WRITE, uint16);
__IOREG(DTS1, 0xFFFF836A, __READ_WRITE, uint8);
#define DTS1DTE            (((volatile __bitf_T *)0xFFFF836A)->bit00)
#define DTS1SR             (((volatile __bitf_T *)0xFFFF836A)->bit01)
#define DTS1DR             (((const volatile __bitf_T *)0xFFFF836A)->bit02)
#define DTS1ER             (((const volatile __bitf_T *)0xFFFF836A)->bit03)
#define DTS1DT             (((volatile __bitf_T *)0xFFFF836A)->bit06)
#define DTS1TC             (((volatile __bitf_T *)0xFFFF836A)->bit07)
__IOREG(DSA2, 0xFFFF8374, __READ_WRITE, uint32);
__IOREG(DSA2L, 0xFFFF8374, __READ_WRITE, uint16);
__IOREG(DSA2H, 0xFFFF8376, __READ_WRITE, uint16);
__IOREG(DDA2, 0xFFFF8384, __READ_WRITE, uint32);
__IOREG(DDA2L, 0xFFFF8384, __READ_WRITE, uint16);
__IOREG(DDA2H, 0xFFFF8386, __READ_WRITE, uint16);
__IOREG(DTC2, 0xFFFF8392, __READ_WRITE, uint16);
__IOREG(DTCT2, 0xFFFF8398, __READ_WRITE, uint16);
__IOREG(DTS2, 0xFFFF839A, __READ_WRITE, uint8);
#define DTS2DTE            (((volatile __bitf_T *)0xFFFF839A)->bit00)
#define DTS2SR             (((volatile __bitf_T *)0xFFFF839A)->bit01)
#define DTS2DR             (((const volatile __bitf_T *)0xFFFF839A)->bit02)
#define DTS2ER             (((const volatile __bitf_T *)0xFFFF839A)->bit03)
#define DTS2DT             (((volatile __bitf_T *)0xFFFF839A)->bit06)
#define DTS2TC             (((volatile __bitf_T *)0xFFFF839A)->bit07)
__IOREG(DSA3, 0xFFFF83A4, __READ_WRITE, uint32);
__IOREG(DSA3L, 0xFFFF83A4, __READ_WRITE, uint16);
__IOREG(DSA3H, 0xFFFF83A6, __READ_WRITE, uint16);
__IOREG(DDA3, 0xFFFF83B4, __READ_WRITE, uint32);
__IOREG(DDA3L, 0xFFFF83B4, __READ_WRITE, uint16);
__IOREG(DDA3H, 0xFFFF83B6, __READ_WRITE, uint16);
__IOREG(DTC3, 0xFFFF83C2, __READ_WRITE, uint16);
__IOREG(DTCT3, 0xFFFF83C8, __READ_WRITE, uint16);
__IOREG(DTS3, 0xFFFF83CA, __READ_WRITE, uint8);
#define DTS3DTE            (((volatile __bitf_T *)0xFFFF83CA)->bit00)
#define DTS3SR             (((volatile __bitf_T *)0xFFFF83CA)->bit01)
#define DTS3DR             (((const volatile __bitf_T *)0xFFFF83CA)->bit02)
#define DTS3ER             (((const volatile __bitf_T *)0xFFFF83CA)->bit03)
#define DTS3DT             (((volatile __bitf_T *)0xFFFF83CA)->bit06)
#define DTS3TC             (((volatile __bitf_T *)0xFFFF83CA)->bit07)
__IOREG(DSA4, 0xFFFF83D4, __READ_WRITE, uint32);
__IOREG(DSA4L, 0xFFFF83D4, __READ_WRITE, uint16);
__IOREG(DSA4H, 0xFFFF83D6, __READ_WRITE, uint16);
__IOREG(DDA4, 0xFFFF83E4, __READ_WRITE, uint32);
__IOREG(DDA4L, 0xFFFF83E4, __READ_WRITE, uint16);
__IOREG(DDA4H, 0xFFFF83E6, __READ_WRITE, uint16);
__IOREG(DTC4, 0xFFFF83F2, __READ_WRITE, uint16);
__IOREG(DTCT4, 0xFFFF83F8, __READ_WRITE, uint16);
__IOREG(DTS4, 0xFFFF83FA, __READ_WRITE, uint8);
#define DTS4DTE            (((volatile __bitf_T *)0xFFFF83FA)->bit00)
#define DTS4SR             (((volatile __bitf_T *)0xFFFF83FA)->bit01)
#define DTS4DR             (((const volatile __bitf_T *)0xFFFF83FA)->bit02)
#define DTS4ER             (((const volatile __bitf_T *)0xFFFF83FA)->bit03)
#define DTS4DT             (((volatile __bitf_T *)0xFFFF83FA)->bit06)
#define DTS4TC             (((volatile __bitf_T *)0xFFFF83FA)->bit07)
__IOREG(DSA5, 0xFFFF8404, __READ_WRITE, uint32);
__IOREG(DSA5L, 0xFFFF8404, __READ_WRITE, uint16);
__IOREG(DSA5H, 0xFFFF8406, __READ_WRITE, uint16);
__IOREG(DDA5, 0xFFFF8414, __READ_WRITE, uint32);
__IOREG(DDA5L, 0xFFFF8414, __READ_WRITE, uint16);
__IOREG(DDA5H, 0xFFFF8416, __READ_WRITE, uint16);
__IOREG(DTC5, 0xFFFF8422, __READ_WRITE, uint16);
__IOREG(DTCT5, 0xFFFF8428, __READ_WRITE, uint16);
__IOREG(DTS5, 0xFFFF842A, __READ_WRITE, uint8);
#define DTS5DTE            (((volatile __bitf_T *)0xFFFF842A)->bit00)
#define DTS5SR             (((volatile __bitf_T *)0xFFFF842A)->bit01)
#define DTS5DR             (((const volatile __bitf_T *)0xFFFF842A)->bit02)
#define DTS5ER             (((const volatile __bitf_T *)0xFFFF842A)->bit03)
#define DTS5DT             (((volatile __bitf_T *)0xFFFF842A)->bit06)
#define DTS5TC             (((volatile __bitf_T *)0xFFFF842A)->bit07)
__IOREG(DSA6, 0xFFFF8434, __READ_WRITE, uint32);
__IOREG(DSA6L, 0xFFFF8434, __READ_WRITE, uint16);
__IOREG(DSA6H, 0xFFFF8436, __READ_WRITE, uint16);
__IOREG(DDA6, 0xFFFF8444, __READ_WRITE, uint32);
__IOREG(DDA6L, 0xFFFF8444, __READ_WRITE, uint16);
__IOREG(DDA6H, 0xFFFF8446, __READ_WRITE, uint16);
__IOREG(DTC6, 0xFFFF8452, __READ_WRITE, uint16);
__IOREG(DTCT6, 0xFFFF8458, __READ_WRITE, uint16);
__IOREG(DTS6, 0xFFFF845A, __READ_WRITE, uint8);
#define DTS6DTE            (((volatile __bitf_T *)0xFFFF845A)->bit00)
#define DTS6SR             (((volatile __bitf_T *)0xFFFF845A)->bit01)
#define DTS6DR             (((const volatile __bitf_T *)0xFFFF845A)->bit02)
#define DTS6ER             (((const volatile __bitf_T *)0xFFFF845A)->bit03)
#define DTS6DT             (((volatile __bitf_T *)0xFFFF845A)->bit06)
#define DTS6TC             (((volatile __bitf_T *)0xFFFF845A)->bit07)
__IOREG(DSA7, 0xFFFF8464, __READ_WRITE, uint32);
__IOREG(DSA7L, 0xFFFF8464, __READ_WRITE, uint16);
__IOREG(DSA7H, 0xFFFF8466, __READ_WRITE, uint16);
__IOREG(DDA7, 0xFFFF8474, __READ_WRITE, uint32);
__IOREG(DDA7L, 0xFFFF8474, __READ_WRITE, uint16);
__IOREG(DDA7H, 0xFFFF8476, __READ_WRITE, uint16);
__IOREG(DTC7, 0xFFFF8482, __READ_WRITE, uint16);
__IOREG(DTCT7, 0xFFFF8488, __READ_WRITE, uint16);
__IOREG(DTS7, 0xFFFF848A, __READ_WRITE, uint8);
#define DTS7DTE            (((volatile __bitf_T *)0xFFFF848A)->bit00)
#define DTS7SR             (((volatile __bitf_T *)0xFFFF848A)->bit01)
#define DTS7DR             (((const volatile __bitf_T *)0xFFFF848A)->bit02)
#define DTS7ER             (((const volatile __bitf_T *)0xFFFF848A)->bit03)
#define DTS7DT             (((volatile __bitf_T *)0xFFFF848A)->bit06)
#define DTS7TC             (((volatile __bitf_T *)0xFFFF848A)->bit07)
__IOREG(DSA8, 0xFFFF8514, __READ_WRITE, uint32);
__IOREG(DSA8L, 0xFFFF8514, __READ_WRITE, uint16);
__IOREG(DSA8H, 0xFFFF8516, __READ_WRITE, uint16);
__IOREG(DDA8, 0xFFFF8524, __READ_WRITE, uint32);
__IOREG(DDA8L, 0xFFFF8524, __READ_WRITE, uint16);
__IOREG(DDA8H, 0xFFFF8526, __READ_WRITE, uint16);
__IOREG(DTC8, 0xFFFF8532, __READ_WRITE, uint16);
__IOREG(DTCT8, 0xFFFF8538, __READ_WRITE, uint16);
__IOREG(DTS8, 0xFFFF853A, __READ_WRITE, uint8);
#define DTS8DTE            (((volatile __bitf_T *)0xFFFF853A)->bit00)
#define DTS8SR             (((volatile __bitf_T *)0xFFFF853A)->bit01)
#define DTS8DR             (((const volatile __bitf_T *)0xFFFF853A)->bit02)
#define DTS8ER             (((const volatile __bitf_T *)0xFFFF853A)->bit03)
#define DTS8DT             (((volatile __bitf_T *)0xFFFF853A)->bit06)
#define DTS8TC             (((volatile __bitf_T *)0xFFFF853A)->bit07)
__IOREG(DSA9, 0xFFFF8544, __READ_WRITE, uint32);
__IOREG(DSA9L, 0xFFFF8544, __READ_WRITE, uint16);
__IOREG(DSA9H, 0xFFFF8546, __READ_WRITE, uint16);
__IOREG(DDA9, 0xFFFF8554, __READ_WRITE, uint32);
__IOREG(DDA9L, 0xFFFF8554, __READ_WRITE, uint16);
__IOREG(DDA9H, 0xFFFF8556, __READ_WRITE, uint16);
__IOREG(DTC9, 0xFFFF8562, __READ_WRITE, uint16);
__IOREG(DTCT9, 0xFFFF8568, __READ_WRITE, uint16);
__IOREG(DTS9, 0xFFFF856A, __READ_WRITE, uint8);
#define DTS9DTE            (((volatile __bitf_T *)0xFFFF856A)->bit00)
#define DTS9SR             (((volatile __bitf_T *)0xFFFF856A)->bit01)
#define DTS9DR             (((const volatile __bitf_T *)0xFFFF856A)->bit02)
#define DTS9ER             (((const volatile __bitf_T *)0xFFFF856A)->bit03)
#define DTS9DT             (((volatile __bitf_T *)0xFFFF856A)->bit06)
#define DTS9TC             (((volatile __bitf_T *)0xFFFF856A)->bit07)
__IOREG(DSA10, 0xFFFF8574, __READ_WRITE, uint32);
__IOREG(DSA10L, 0xFFFF8574, __READ_WRITE, uint16);
__IOREG(DSA10H, 0xFFFF8576, __READ_WRITE, uint16);
__IOREG(DDA10, 0xFFFF8584, __READ_WRITE, uint32);
__IOREG(DDA10L, 0xFFFF8584, __READ_WRITE, uint16);
__IOREG(DDA10H, 0xFFFF8586, __READ_WRITE, uint16);
__IOREG(DTC10, 0xFFFF8592, __READ_WRITE, uint16);
__IOREG(DTCT10, 0xFFFF8598, __READ_WRITE, uint16);
__IOREG(DTS10, 0xFFFF859A, __READ_WRITE, uint8);
#define DTS10DTE           (((volatile __bitf_T *)0xFFFF859A)->bit00)
#define DTS10SR            (((volatile __bitf_T *)0xFFFF859A)->bit01)
#define DTS10DR            (((const volatile __bitf_T *)0xFFFF859A)->bit02)
#define DTS10ER            (((const volatile __bitf_T *)0xFFFF859A)->bit03)
#define DTS10DT            (((volatile __bitf_T *)0xFFFF859A)->bit06)
#define DTS10TC            (((volatile __bitf_T *)0xFFFF859A)->bit07)
__IOREG(DSA11, 0xFFFF85A4, __READ_WRITE, uint32);
__IOREG(DSA11L, 0xFFFF85A4, __READ_WRITE, uint16);
__IOREG(DSA11H, 0xFFFF85A6, __READ_WRITE, uint16);
__IOREG(DDA11, 0xFFFF85B4, __READ_WRITE, uint32);
__IOREG(DDA11L, 0xFFFF85B4, __READ_WRITE, uint16);
__IOREG(DDA11H, 0xFFFF85B6, __READ_WRITE, uint16);
__IOREG(DTC11, 0xFFFF85C2, __READ_WRITE, uint16);
__IOREG(DTCT11, 0xFFFF85C8, __READ_WRITE, uint16);
__IOREG(DTS11, 0xFFFF85CA, __READ_WRITE, uint8);
#define DTS11DTE           (((volatile __bitf_T *)0xFFFF85CA)->bit00)
#define DTS11SR            (((volatile __bitf_T *)0xFFFF85CA)->bit01)
#define DTS11DR            (((const volatile __bitf_T *)0xFFFF85CA)->bit02)
#define DTS11ER            (((const volatile __bitf_T *)0xFFFF85CA)->bit03)
#define DTS11DT            (((volatile __bitf_T *)0xFFFF85CA)->bit06)
#define DTS11TC            (((volatile __bitf_T *)0xFFFF85CA)->bit07)
__IOREG(DSA12, 0xFFFF85D4, __READ_WRITE, uint32);
__IOREG(DSA12L, 0xFFFF85D4, __READ_WRITE, uint16);
__IOREG(DSA12H, 0xFFFF85D6, __READ_WRITE, uint16);
__IOREG(DDA12, 0xFFFF85E4, __READ_WRITE, uint32);
__IOREG(DDA12L, 0xFFFF85E4, __READ_WRITE, uint16);
__IOREG(DDA12H, 0xFFFF85E6, __READ_WRITE, uint16);
__IOREG(DTC12, 0xFFFF85F2, __READ_WRITE, uint16);
__IOREG(DTCT12, 0xFFFF85F8, __READ_WRITE, uint16);
__IOREG(DTS12, 0xFFFF85FA, __READ_WRITE, uint8);
#define DTS12DTE           (((volatile __bitf_T *)0xFFFF85FA)->bit00)
#define DTS12SR            (((volatile __bitf_T *)0xFFFF85FA)->bit01)
#define DTS12DR            (((const volatile __bitf_T *)0xFFFF85FA)->bit02)
#define DTS12ER            (((const volatile __bitf_T *)0xFFFF85FA)->bit03)
#define DTS12DT            (((volatile __bitf_T *)0xFFFF85FA)->bit06)
#define DTS12TC            (((volatile __bitf_T *)0xFFFF85FA)->bit07)
__IOREG(DSA13, 0xFFFF8604, __READ_WRITE, uint32);
__IOREG(DSA13L, 0xFFFF8604, __READ_WRITE, uint16);
__IOREG(DSA13H, 0xFFFF8606, __READ_WRITE, uint16);
__IOREG(DDA13, 0xFFFF8614, __READ_WRITE, uint32);
__IOREG(DDA13L, 0xFFFF8614, __READ_WRITE, uint16);
__IOREG(DDA13H, 0xFFFF8616, __READ_WRITE, uint16);
__IOREG(DTC13, 0xFFFF8622, __READ_WRITE, uint16);
__IOREG(DTCT13, 0xFFFF8628, __READ_WRITE, uint16);
__IOREG(DTS13, 0xFFFF862A, __READ_WRITE, uint8);
#define DTS13DTE           (((volatile __bitf_T *)0xFFFF862A)->bit00)
#define DTS13SR            (((volatile __bitf_T *)0xFFFF862A)->bit01)
#define DTS13DR            (((const volatile __bitf_T *)0xFFFF862A)->bit02)
#define DTS13ER            (((const volatile __bitf_T *)0xFFFF862A)->bit03)
#define DTS13DT            (((volatile __bitf_T *)0xFFFF862A)->bit06)
#define DTS13TC            (((volatile __bitf_T *)0xFFFF862A)->bit07)
__IOREG(DSA14, 0xFFFF8634, __READ_WRITE, uint32);
__IOREG(DSA14L, 0xFFFF8634, __READ_WRITE, uint16);
__IOREG(DSA14H, 0xFFFF8636, __READ_WRITE, uint16);
__IOREG(DDA14, 0xFFFF8644, __READ_WRITE, uint32);
__IOREG(DDA14L, 0xFFFF8644, __READ_WRITE, uint16);
__IOREG(DDA14H, 0xFFFF8646, __READ_WRITE, uint16);
__IOREG(DTC14, 0xFFFF8652, __READ_WRITE, uint16);
__IOREG(DTCT14, 0xFFFF8658, __READ_WRITE, uint16);
__IOREG(DTS14, 0xFFFF865A, __READ_WRITE, uint8);
#define DTS14DTE           (((volatile __bitf_T *)0xFFFF865A)->bit00)
#define DTS14SR            (((volatile __bitf_T *)0xFFFF865A)->bit01)
#define DTS14DR            (((const volatile __bitf_T *)0xFFFF865A)->bit02)
#define DTS14ER            (((const volatile __bitf_T *)0xFFFF865A)->bit03)
#define DTS14DT            (((volatile __bitf_T *)0xFFFF865A)->bit06)
#define DTS14TC            (((volatile __bitf_T *)0xFFFF865A)->bit07)
__IOREG(DSA15, 0xFFFF8664, __READ_WRITE, uint32);
__IOREG(DSA15L, 0xFFFF8664, __READ_WRITE, uint16);
__IOREG(DSA15H, 0xFFFF8666, __READ_WRITE, uint16);
__IOREG(DDA15, 0xFFFF8674, __READ_WRITE, uint32);
__IOREG(DDA15L, 0xFFFF8674, __READ_WRITE, uint16);
__IOREG(DDA15H, 0xFFFF8676, __READ_WRITE, uint16);
__IOREG(DTC15, 0xFFFF8682, __READ_WRITE, uint16);
__IOREG(DTCT15, 0xFFFF8688, __READ_WRITE, uint16);
__IOREG(DTS15, 0xFFFF868A, __READ_WRITE, uint8);
#define DTS15DTE           (((volatile __bitf_T *)0xFFFF868A)->bit00)
#define DTS15SR            (((volatile __bitf_T *)0xFFFF868A)->bit01)
#define DTS15DR            (((const volatile __bitf_T *)0xFFFF868A)->bit02)
#define DTS15ER            (((const volatile __bitf_T *)0xFFFF868A)->bit03)
#define DTS15DT            (((volatile __bitf_T *)0xFFFF868A)->bit06)
#define DTS15TC            (((volatile __bitf_T *)0xFFFF868A)->bit07)
__IOREG(DTFR0, 0xFFFF8B00, __READ_WRITE, uint16);
__IOREG(DTFR1, 0xFFFF8B02, __READ_WRITE, uint16);
__IOREG(DTFR2, 0xFFFF8B04, __READ_WRITE, uint16);
__IOREG(DTFR3, 0xFFFF8B06, __READ_WRITE, uint16);
__IOREG(DTFR4, 0xFFFF8B08, __READ_WRITE, uint16);
__IOREG(DTFR5, 0xFFFF8B0A, __READ_WRITE, uint16);
__IOREG(DTFR6, 0xFFFF8B0C, __READ_WRITE, uint16);
__IOREG(DTFR7, 0xFFFF8B0E, __READ_WRITE, uint16);
__IOREG(DTFR8, 0xFFFF8B10, __READ_WRITE, uint16);
__IOREG(DTFR9, 0xFFFF8B12, __READ_WRITE, uint16);
__IOREG(DTFR10, 0xFFFF8B14, __READ_WRITE, uint16);
__IOREG(DTFR11, 0xFFFF8B16, __READ_WRITE, uint16);
__IOREG(DTFR12, 0xFFFF8B18, __READ_WRITE, uint16);
__IOREG(DTFR13, 0xFFFF8B1A, __READ_WRITE, uint16);
__IOREG(DTFR14, 0xFFFF8B1C, __READ_WRITE, uint16);
__IOREG(DTFR15, 0xFFFF8B1E, __READ_WRITE, uint16);
__IOREG(DRQCLR, 0xFFFF8B40, __READ_WRITE, uint16);
__IOREG(DRQSTR, 0xFFFF8B44, __READ, uint16);
__IOREG(SEG_CONT, 0xFFFF8C00, __READ_WRITE, uint16);
__IOREG(SEG_CONTL, 0xFFFF8C00, __READ_WRITE, uint8);
#define SEG_CONTROME       (((volatile __bitf_T *)0xFFFF8C00)->bit01)
#define SEG_CONTRAME       (((volatile __bitf_T *)0xFFFF8C00)->bit04)
#define SEG_CONTRMWE       (((volatile __bitf_T *)0xFFFF8C00)->bit06)
#define SEG_CONTDMAE       (((volatile __bitf_T *)0xFFFF8C00)->bit07)
__IOREG(SEG_FLAG, 0xFFFF8C02, __READ_WRITE, uint16);
__IOREG(SEG_FLAGL, 0xFFFF8C02, __READ_WRITE, uint8);
#define SEG_FLAGROMF       (((volatile __bitf_T *)0xFFFF8C02)->bit01)
#define SEG_FLAGRAMF       (((volatile __bitf_T *)0xFFFF8C02)->bit04)
#define SEG_FLAGRMWF       (((volatile __bitf_T *)0xFFFF8C02)->bit06)
#define SEG_FLAGDMAF       (((volatile __bitf_T *)0xFFFF8C02)->bit07)
__IOREG(ICTAUD0I0, 0xFFFF9000, __READ_WRITE, uint16);
__IOREG(ICTAUD0I0L, 0xFFFF9000, __READ_WRITE, uint8);
__IOREG(ICTAUD0I0H, 0xFFFF9001, __READ_WRITE, uint8);
#define P0TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit00)
#define P1TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit01)
#define P2TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit02)
#define TBTAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit06)
#define MKTAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit07)
#define RFTAUD0I0          (((volatile __bitf_T *)0xFFFF9001)->bit04)
#define CTTAUD0I0          (((const volatile __bitf_T *)0xFFFF9001)->bit07)
__IOREG(ICTAUD0I2, 0xFFFF9002, __READ_WRITE, uint16);
__IOREG(ICTAUD0I2L, 0xFFFF9002, __READ_WRITE, uint8);
__IOREG(ICTAUD0I2H, 0xFFFF9003, __READ_WRITE, uint8);
#define P0TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit00)
#define P1TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit01)
#define P2TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit02)
#define TBTAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit06)
#define MKTAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit07)
#define RFTAUD0I2          (((volatile __bitf_T *)0xFFFF9003)->bit04)
#define CTTAUD0I2          (((const volatile __bitf_T *)0xFFFF9003)->bit07)
__IOREG(ICTAUD0I4, 0xFFFF9004, __READ_WRITE, uint16);
__IOREG(ICTAUD0I4L, 0xFFFF9004, __READ_WRITE, uint8);
__IOREG(ICTAUD0I4H, 0xFFFF9005, __READ_WRITE, uint8);
#define P0TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit00)
#define P1TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit01)
#define P2TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit02)
#define TBTAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit06)
#define MKTAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit07)
#define RFTAUD0I4          (((volatile __bitf_T *)0xFFFF9005)->bit04)
#define CTTAUD0I4          (((const volatile __bitf_T *)0xFFFF9005)->bit07)
__IOREG(ICTAUD0I6, 0xFFFF9006, __READ_WRITE, uint16);
__IOREG(ICTAUD0I6L, 0xFFFF9006, __READ_WRITE, uint8);
__IOREG(ICTAUD0I6H, 0xFFFF9007, __READ_WRITE, uint8);
#define P0TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit00)
#define P1TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit01)
#define P2TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit02)
#define TBTAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit06)
#define MKTAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit07)
#define RFTAUD0I6          (((volatile __bitf_T *)0xFFFF9007)->bit04)
#define CTTAUD0I6          (((const volatile __bitf_T *)0xFFFF9007)->bit07)
__IOREG(ICTAUD0I8, 0xFFFF9008, __READ_WRITE, uint16);
__IOREG(ICTAUD0I8L, 0xFFFF9008, __READ_WRITE, uint8);
__IOREG(ICTAUD0I8H, 0xFFFF9009, __READ_WRITE, uint8);
#define P0TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit00)
#define P1TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit01)
#define P2TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit02)
#define TBTAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit06)
#define MKTAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit07)
#define RFTAUD0I8          (((volatile __bitf_T *)0xFFFF9009)->bit04)
#define CTTAUD0I8          (((const volatile __bitf_T *)0xFFFF9009)->bit07)
__IOREG(ICTAUD0I10, 0xFFFF900A, __READ_WRITE, uint16);
__IOREG(ICTAUD0I10L, 0xFFFF900A, __READ_WRITE, uint8);
__IOREG(ICTAUD0I10H, 0xFFFF900B, __READ_WRITE, uint8);
#define P0TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit00)
#define P1TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit01)
#define P2TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit02)
#define TBTAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit06)
#define MKTAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit07)
#define RFTAUD0I10         (((volatile __bitf_T *)0xFFFF900B)->bit04)
#define CTTAUD0I10         (((const volatile __bitf_T *)0xFFFF900B)->bit07)
__IOREG(ICTAUD0I12, 0xFFFF900C, __READ_WRITE, uint16);
__IOREG(ICTAUD0I12L, 0xFFFF900C, __READ_WRITE, uint8);
__IOREG(ICTAUD0I12H, 0xFFFF900D, __READ_WRITE, uint8);
#define P0TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit00)
#define P1TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit01)
#define P2TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit02)
#define TBTAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit06)
#define MKTAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit07)
#define RFTAUD0I12         (((volatile __bitf_T *)0xFFFF900D)->bit04)
#define CTTAUD0I12         (((const volatile __bitf_T *)0xFFFF900D)->bit07)
__IOREG(ICTAUD0I14, 0xFFFF900E, __READ_WRITE, uint16);
__IOREG(ICTAUD0I14L, 0xFFFF900E, __READ_WRITE, uint8);
__IOREG(ICTAUD0I14H, 0xFFFF900F, __READ_WRITE, uint8);
#define P0TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit00)
#define P1TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit01)
#define P2TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit02)
#define TBTAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit06)
#define MKTAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit07)
#define RFTAUD0I14         (((volatile __bitf_T *)0xFFFF900F)->bit04)
#define CTTAUD0I14         (((const volatile __bitf_T *)0xFFFF900F)->bit07)
__IOREG(ICTAPA0IPEK0, 0xFFFF9010, __READ_WRITE, uint16);
__IOREG(ICTAPA0IPEK0L, 0xFFFF9010, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0H, 0xFFFF9011, __READ_WRITE, uint8);
#define P0TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit00)
#define P1TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit01)
#define P2TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit02)
#define TBTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit06)
#define MKTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit07)
#define RFTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9011)->bit04)
#define CTTAPA0IPEK0       (((const volatile __bitf_T *)0xFFFF9011)->bit07)
__IOREG(ICTAPA0IVLY0, 0xFFFF9012, __READ_WRITE, uint16);
__IOREG(ICTAPA0IVLY0L, 0xFFFF9012, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0H, 0xFFFF9013, __READ_WRITE, uint8);
#define P0TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit00)
#define P1TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit01)
#define P2TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit02)
#define TBTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit06)
#define MKTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit07)
#define RFTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9013)->bit04)
#define CTTAPA0IVLY0       (((const volatile __bitf_T *)0xFFFF9013)->bit07)
__IOREG(ICADCA0I0, 0xFFFF9014, __READ_WRITE, uint16);
__IOREG(ICADCA0I0L, 0xFFFF9014, __READ_WRITE, uint8);
__IOREG(ICADCA0I0H, 0xFFFF9015, __READ_WRITE, uint8);
#define P0ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit00)
#define P1ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit01)
#define P2ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit02)
#define TBADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit06)
#define MKADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit07)
#define RFADCA0I0          (((volatile __bitf_T *)0xFFFF9015)->bit04)
#define CTADCA0I0          (((const volatile __bitf_T *)0xFFFF9015)->bit07)
__IOREG(ICADCA0I1, 0xFFFF9016, __READ_WRITE, uint16);
__IOREG(ICADCA0I1L, 0xFFFF9016, __READ_WRITE, uint8);
__IOREG(ICADCA0I1H, 0xFFFF9017, __READ_WRITE, uint8);
#define P0ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit00)
#define P1ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit01)
#define P2ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit02)
#define TBADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit06)
#define MKADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit07)
#define RFADCA0I1          (((volatile __bitf_T *)0xFFFF9017)->bit04)
#define CTADCA0I1          (((const volatile __bitf_T *)0xFFFF9017)->bit07)
__IOREG(ICADCA0I2, 0xFFFF9018, __READ_WRITE, uint16);
__IOREG(ICADCA0I2L, 0xFFFF9018, __READ_WRITE, uint8);
__IOREG(ICADCA0I2H, 0xFFFF9019, __READ_WRITE, uint8);
#define P0ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit00)
#define P1ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit01)
#define P2ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit02)
#define TBADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit06)
#define MKADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit07)
#define RFADCA0I2          (((volatile __bitf_T *)0xFFFF9019)->bit04)
#define CTADCA0I2          (((const volatile __bitf_T *)0xFFFF9019)->bit07)
__IOREG(ICDCUTDI, 0xFFFF901A, __READ_WRITE, uint16);
__IOREG(ICDCUTDIL, 0xFFFF901A, __READ_WRITE, uint8);
__IOREG(ICDCUTDIH, 0xFFFF901B, __READ_WRITE, uint8);
#define P0DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit00)
#define P1DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit01)
#define P2DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit02)
#define TBDCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit06)
#define MKDCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit07)
#define RFDCUTDI           (((volatile __bitf_T *)0xFFFF901B)->bit04)
#define CTDCUTDI           (((const volatile __bitf_T *)0xFFFF901B)->bit07)
__IOREG(ICRCANGERR, 0xFFFF901C, __READ_WRITE, uint16);
__IOREG(ICRCANGERRL, 0xFFFF901C, __READ_WRITE, uint8);
__IOREG(ICRCANGERRH, 0xFFFF901D, __READ_WRITE, uint8);
#define P0RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit00)
#define P1RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit01)
#define P2RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit02)
#define TBRCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit06)
#define MKRCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit07)
#define RFRCANGERR         (((volatile __bitf_T *)0xFFFF901D)->bit04)
#define CTRCANGERR         (((const volatile __bitf_T *)0xFFFF901D)->bit07)
__IOREG(ICRCANGRECC, 0xFFFF901E, __READ_WRITE, uint16);
__IOREG(ICRCANGRECCL, 0xFFFF901E, __READ_WRITE, uint8);
__IOREG(ICRCANGRECCH, 0xFFFF901F, __READ_WRITE, uint8);
#define P0RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit00)
#define P1RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit01)
#define P2RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit02)
#define TBRCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit06)
#define MKRCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit07)
#define RFRCANGRECC        (((volatile __bitf_T *)0xFFFF901F)->bit04)
#define CTRCANGRECC        (((const volatile __bitf_T *)0xFFFF901F)->bit07)
__IOREG(ICRCAN0ERR, 0xFFFF9020, __READ_WRITE, uint16);
__IOREG(ICRCAN0ERRL, 0xFFFF9020, __READ_WRITE, uint8);
__IOREG(ICRCAN0ERRH, 0xFFFF9021, __READ_WRITE, uint8);
#define P0RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit00)
#define P1RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit01)
#define P2RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit02)
#define TBRCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit06)
#define MKRCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit07)
#define RFRCAN0ERR         (((volatile __bitf_T *)0xFFFF9021)->bit04)
#define CTRCAN0ERR         (((const volatile __bitf_T *)0xFFFF9021)->bit07)
__IOREG(ICRCAN0REC, 0xFFFF9022, __READ_WRITE, uint16);
__IOREG(ICRCAN0RECL, 0xFFFF9022, __READ_WRITE, uint8);
__IOREG(ICRCAN0RECH, 0xFFFF9023, __READ_WRITE, uint8);
#define P0RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit00)
#define P1RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit01)
#define P2RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit02)
#define TBRCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit06)
#define MKRCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit07)
#define RFRCAN0REC         (((volatile __bitf_T *)0xFFFF9023)->bit04)
#define CTRCAN0REC         (((const volatile __bitf_T *)0xFFFF9023)->bit07)
__IOREG(ICRCAN0TRX, 0xFFFF9024, __READ_WRITE, uint16);
__IOREG(ICRCAN0TRXL, 0xFFFF9024, __READ_WRITE, uint8);
__IOREG(ICRCAN0TRXH, 0xFFFF9025, __READ_WRITE, uint8);
#define P0RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit00)
#define P1RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit01)
#define P2RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit02)
#define TBRCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit06)
#define MKRCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit07)
#define RFRCAN0TRX         (((volatile __bitf_T *)0xFFFF9025)->bit04)
#define CTRCAN0TRX         (((const volatile __bitf_T *)0xFFFF9025)->bit07)
__IOREG(ICCSIG0IC, 0xFFFF9026, __READ_WRITE, uint16);
__IOREG(ICCSIG0ICL, 0xFFFF9026, __READ_WRITE, uint8);
__IOREG(ICCSIG0ICH, 0xFFFF9027, __READ_WRITE, uint8);
#define P0CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit00)
#define P1CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit01)
#define P2CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit02)
#define TBCSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit06)
#define MKCSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit07)
#define RFCSIG0IC          (((volatile __bitf_T *)0xFFFF9027)->bit04)
#define CTCSIG0IC          (((const volatile __bitf_T *)0xFFFF9027)->bit07)
__IOREG(ICCSIG0IR, 0xFFFF9028, __READ_WRITE, uint16);
__IOREG(ICCSIG0IRL, 0xFFFF9028, __READ_WRITE, uint8);
__IOREG(ICCSIG0IRH, 0xFFFF9029, __READ_WRITE, uint8);
#define P0CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit00)
#define P1CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit01)
#define P2CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit02)
#define TBCSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit06)
#define MKCSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit07)
#define RFCSIG0IR          (((volatile __bitf_T *)0xFFFF9029)->bit04)
#define CTCSIG0IR          (((const volatile __bitf_T *)0xFFFF9029)->bit07)
__IOREG(ICCSIH0IC, 0xFFFF902A, __READ_WRITE, uint16);
__IOREG(ICCSIH0ICL, 0xFFFF902A, __READ_WRITE, uint8);
__IOREG(ICCSIH0ICH, 0xFFFF902B, __READ_WRITE, uint8);
#define P0CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit00)
#define P1CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit01)
#define P2CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit02)
#define TBCSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit06)
#define MKCSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit07)
#define RFCSIH0IC          (((volatile __bitf_T *)0xFFFF902B)->bit04)
#define CTCSIH0IC          (((const volatile __bitf_T *)0xFFFF902B)->bit07)
__IOREG(ICCSIH0IR, 0xFFFF902C, __READ_WRITE, uint16);
__IOREG(ICCSIH0IRL, 0xFFFF902C, __READ_WRITE, uint8);
__IOREG(ICCSIH0IRH, 0xFFFF902D, __READ_WRITE, uint8);
#define P0CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit00)
#define P1CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit01)
#define P2CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit02)
#define TBCSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit06)
#define MKCSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit07)
#define RFCSIH0IR          (((volatile __bitf_T *)0xFFFF902D)->bit04)
#define CTCSIH0IR          (((const volatile __bitf_T *)0xFFFF902D)->bit07)
__IOREG(ICCSIH0IRE, 0xFFFF902E, __READ_WRITE, uint16);
__IOREG(ICCSIH0IREL, 0xFFFF902E, __READ_WRITE, uint8);
__IOREG(ICCSIH0IREH, 0xFFFF902F, __READ_WRITE, uint8);
#define P0CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit00)
#define P1CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit01)
#define P2CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit02)
#define TBCSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit06)
#define MKCSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit07)
#define RFCSIH0IRE         (((volatile __bitf_T *)0xFFFF902F)->bit04)
#define CTCSIH0IRE         (((const volatile __bitf_T *)0xFFFF902F)->bit07)
__IOREG(ICCSIH0IJC, 0xFFFF9030, __READ_WRITE, uint16);
__IOREG(ICCSIH0IJCL, 0xFFFF9030, __READ_WRITE, uint8);
__IOREG(ICCSIH0IJCH, 0xFFFF9031, __READ_WRITE, uint8);
#define P0CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit00)
#define P1CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit01)
#define P2CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit02)
#define TBCSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit06)
#define MKCSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit07)
#define RFCSIH0IJC         (((volatile __bitf_T *)0xFFFF9031)->bit04)
#define CTCSIH0IJC         (((const volatile __bitf_T *)0xFFFF9031)->bit07)
__IOREG(ICRLIN30, 0xFFFF9032, __READ_WRITE, uint16);
__IOREG(ICRLIN30L, 0xFFFF9032, __READ_WRITE, uint8);
__IOREG(ICRLIN30H, 0xFFFF9033, __READ_WRITE, uint8);
#define P0RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit00)
#define P1RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit01)
#define P2RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit02)
#define TBRLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit06)
#define MKRLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit07)
#define RFRLIN30           (((volatile __bitf_T *)0xFFFF9033)->bit04)
#define CTRLIN30           (((const volatile __bitf_T *)0xFFFF9033)->bit07)
__IOREG(ICRLIN30UR0, 0xFFFF9034, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR0L, 0xFFFF9034, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR0H, 0xFFFF9035, __READ_WRITE, uint8);
#define P0RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit00)
#define P1RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit01)
#define P2RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit02)
#define TBRLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit06)
#define MKRLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit07)
#define RFRLIN30UR0        (((volatile __bitf_T *)0xFFFF9035)->bit04)
#define CTRLIN30UR0        (((const volatile __bitf_T *)0xFFFF9035)->bit07)
__IOREG(ICRLIN30UR1, 0xFFFF9036, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR1L, 0xFFFF9036, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR1H, 0xFFFF9037, __READ_WRITE, uint8);
#define P0RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit00)
#define P1RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit01)
#define P2RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit02)
#define TBRLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit06)
#define MKRLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit07)
#define RFRLIN30UR1        (((volatile __bitf_T *)0xFFFF9037)->bit04)
#define CTRLIN30UR1        (((const volatile __bitf_T *)0xFFFF9037)->bit07)
__IOREG(ICRLIN30UR2, 0xFFFF9038, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR2L, 0xFFFF9038, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR2H, 0xFFFF9039, __READ_WRITE, uint8);
#define P0RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit00)
#define P1RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit01)
#define P2RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit02)
#define TBRLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit06)
#define MKRLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit07)
#define RFRLIN30UR2        (((volatile __bitf_T *)0xFFFF9039)->bit04)
#define CTRLIN30UR2        (((const volatile __bitf_T *)0xFFFF9039)->bit07)
__IOREG(ICP0, 0xFFFF903A, __READ_WRITE, uint16);
__IOREG(ICP0L, 0xFFFF903A, __READ_WRITE, uint8);
__IOREG(ICP0H, 0xFFFF903B, __READ_WRITE, uint8);
#define P0P0               (((volatile __bitf_T *)0xFFFF903A)->bit00)
#define P1P0               (((volatile __bitf_T *)0xFFFF903A)->bit01)
#define P2P0               (((volatile __bitf_T *)0xFFFF903A)->bit02)
#define TBP0               (((volatile __bitf_T *)0xFFFF903A)->bit06)
#define MKP0               (((volatile __bitf_T *)0xFFFF903A)->bit07)
#define RFP0               (((volatile __bitf_T *)0xFFFF903B)->bit04)
#define CTP0               (((const volatile __bitf_T *)0xFFFF903B)->bit07)
__IOREG(ICP1, 0xFFFF903C, __READ_WRITE, uint16);
__IOREG(ICP1L, 0xFFFF903C, __READ_WRITE, uint8);
__IOREG(ICP1H, 0xFFFF903D, __READ_WRITE, uint8);
#define P0P1               (((volatile __bitf_T *)0xFFFF903C)->bit00)
#define P1P1               (((volatile __bitf_T *)0xFFFF903C)->bit01)
#define P2P1               (((volatile __bitf_T *)0xFFFF903C)->bit02)
#define TBP1               (((volatile __bitf_T *)0xFFFF903C)->bit06)
#define MKP1               (((volatile __bitf_T *)0xFFFF903C)->bit07)
#define RFP1               (((volatile __bitf_T *)0xFFFF903D)->bit04)
#define CTP1               (((const volatile __bitf_T *)0xFFFF903D)->bit07)
__IOREG(ICP2, 0xFFFF903E, __READ_WRITE, uint16);
__IOREG(ICP2L, 0xFFFF903E, __READ_WRITE, uint8);
__IOREG(ICP2H, 0xFFFF903F, __READ_WRITE, uint8);
#define P0P2               (((volatile __bitf_T *)0xFFFF903E)->bit00)
#define P1P2               (((volatile __bitf_T *)0xFFFF903E)->bit01)
#define P2P2               (((volatile __bitf_T *)0xFFFF903E)->bit02)
#define TBP2               (((volatile __bitf_T *)0xFFFF903E)->bit06)
#define MKP2               (((volatile __bitf_T *)0xFFFF903E)->bit07)
#define RFP2               (((volatile __bitf_T *)0xFFFF903F)->bit04)
#define CTP2               (((const volatile __bitf_T *)0xFFFF903F)->bit07)
__IOREG(FNC, 0xFFFF9078, __READ, uint16);
__IOREG(FNCH, 0xFFFF9079, __READ, uint8);
#define FNRF               (((const volatile __bitf_T *)0xFFFF9079)->bit04)
__IOREG(FIC, 0xFFFF907A, __READ, uint16);
__IOREG(FICH, 0xFFFF907B, __READ, uint8);
#define FIRF               (((const volatile __bitf_T *)0xFFFF907B)->bit04)
__IOREG(IMR0, 0xFFFF90F0, __READ_WRITE, uint32);
__IOREG(IMR0L, 0xFFFF90F0, __READ_WRITE, uint16);
__IOREG(IMR0LL, 0xFFFF90F0, __READ_WRITE, uint8);
__IOREG(IMR0LH, 0xFFFF90F1, __READ_WRITE, uint8);
__IOREG(IMR0H, 0xFFFF90F2, __READ_WRITE, uint16);
__IOREG(IMR0HL, 0xFFFF90F2, __READ_WRITE, uint8);
__IOREG(IMR0HH, 0xFFFF90F3, __READ_WRITE, uint8);
#define IMR0EIMK0          (((volatile __bitf_T *)0xFFFF90F0)->bit00)
#define IMR0EIMK1          (((volatile __bitf_T *)0xFFFF90F0)->bit01)
#define IMR0EIMK2          (((volatile __bitf_T *)0xFFFF90F0)->bit02)
#define IMR0EIMK3          (((volatile __bitf_T *)0xFFFF90F0)->bit03)
#define IMR0EIMK4          (((volatile __bitf_T *)0xFFFF90F0)->bit04)
#define IMR0EIMK5          (((volatile __bitf_T *)0xFFFF90F0)->bit05)
#define IMR0EIMK6          (((volatile __bitf_T *)0xFFFF90F0)->bit06)
#define IMR0EIMK7          (((volatile __bitf_T *)0xFFFF90F0)->bit07)
#define IMR0EIMK8          (((volatile __bitf_T *)0xFFFF90F1)->bit00)
#define IMR0EIMK9          (((volatile __bitf_T *)0xFFFF90F1)->bit01)
#define IMR0EIMK10         (((volatile __bitf_T *)0xFFFF90F1)->bit02)
#define IMR0EIMK11         (((volatile __bitf_T *)0xFFFF90F1)->bit03)
#define IMR0EIMK12         (((volatile __bitf_T *)0xFFFF90F1)->bit04)
#define IMR0EIMK14         (((volatile __bitf_T *)0xFFFF90F1)->bit06)
#define IMR0EIMK15         (((volatile __bitf_T *)0xFFFF90F1)->bit07)
#define IMR0EIMK16         (((volatile __bitf_T *)0xFFFF90F2)->bit00)
#define IMR0EIMK17         (((volatile __bitf_T *)0xFFFF90F2)->bit01)
#define IMR0EIMK18         (((volatile __bitf_T *)0xFFFF90F2)->bit02)
#define IMR0EIMK19         (((volatile __bitf_T *)0xFFFF90F2)->bit03)
#define IMR0EIMK20         (((volatile __bitf_T *)0xFFFF90F2)->bit04)
#define IMR0EIMK21         (((volatile __bitf_T *)0xFFFF90F2)->bit05)
#define IMR0EIMK22         (((volatile __bitf_T *)0xFFFF90F2)->bit06)
#define IMR0EIMK23         (((volatile __bitf_T *)0xFFFF90F2)->bit07)
#define IMR0EIMK24         (((volatile __bitf_T *)0xFFFF90F3)->bit00)
#define IMR0EIMK25         (((volatile __bitf_T *)0xFFFF90F3)->bit01)
#define IMR0EIMK26         (((volatile __bitf_T *)0xFFFF90F3)->bit02)
#define IMR0EIMK27         (((volatile __bitf_T *)0xFFFF90F3)->bit03)
#define IMR0EIMK28         (((volatile __bitf_T *)0xFFFF90F3)->bit04)
#define IMR0EIMK29         (((volatile __bitf_T *)0xFFFF90F3)->bit05)
#define IMR0EIMK30         (((volatile __bitf_T *)0xFFFF90F3)->bit06)
#define IMR0EIMK31         (((volatile __bitf_T *)0xFFFF90F3)->bit07)
__IOREG(ICWDTA0, 0xFFFFA040, __READ_WRITE, uint16);
__IOREG(ICWDTA0L, 0xFFFFA040, __READ_WRITE, uint8);
__IOREG(ICWDTA0H, 0xFFFFA041, __READ_WRITE, uint8);
#define P0WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit00)
#define P1WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit01)
#define P2WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit02)
#define TBWDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit06)
#define MKWDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit07)
#define RFWDTA0            (((volatile __bitf_T *)0xFFFFA041)->bit04)
#define CTWDTA0            (((const volatile __bitf_T *)0xFFFFA041)->bit07)
__IOREG(ICWDTA1, 0xFFFFA042, __READ_WRITE, uint16);
__IOREG(ICWDTA1L, 0xFFFFA042, __READ_WRITE, uint8);
__IOREG(ICWDTA1H, 0xFFFFA043, __READ_WRITE, uint8);
#define P0WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit00)
#define P1WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit01)
#define P2WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit02)
#define TBWDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit06)
#define MKWDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit07)
#define RFWDTA1            (((volatile __bitf_T *)0xFFFFA043)->bit04)
#define CTWDTA1            (((const volatile __bitf_T *)0xFFFFA043)->bit07)
__IOREG(ICP3, 0xFFFFA044, __READ_WRITE, uint16);
__IOREG(ICP3L, 0xFFFFA044, __READ_WRITE, uint8);
__IOREG(ICP3H, 0xFFFFA045, __READ_WRITE, uint8);
#define P0P3               (((volatile __bitf_T *)0xFFFFA044)->bit00)
#define P1P3               (((volatile __bitf_T *)0xFFFFA044)->bit01)
#define P2P3               (((volatile __bitf_T *)0xFFFFA044)->bit02)
#define TBP3               (((volatile __bitf_T *)0xFFFFA044)->bit06)
#define MKP3               (((volatile __bitf_T *)0xFFFFA044)->bit07)
#define RFP3               (((volatile __bitf_T *)0xFFFFA045)->bit04)
#define CTP3               (((const volatile __bitf_T *)0xFFFFA045)->bit07)
__IOREG(ICP4, 0xFFFFA046, __READ_WRITE, uint16);
__IOREG(ICP4L, 0xFFFFA046, __READ_WRITE, uint8);
__IOREG(ICP4H, 0xFFFFA047, __READ_WRITE, uint8);
#define P0P4               (((volatile __bitf_T *)0xFFFFA046)->bit00)
#define P1P4               (((volatile __bitf_T *)0xFFFFA046)->bit01)
#define P2P4               (((volatile __bitf_T *)0xFFFFA046)->bit02)
#define TBP4               (((volatile __bitf_T *)0xFFFFA046)->bit06)
#define MKP4               (((volatile __bitf_T *)0xFFFFA046)->bit07)
#define RFP4               (((volatile __bitf_T *)0xFFFFA047)->bit04)
#define CTP4               (((const volatile __bitf_T *)0xFFFFA047)->bit07)
__IOREG(ICP5, 0xFFFFA048, __READ_WRITE, uint16);
__IOREG(ICP5L, 0xFFFFA048, __READ_WRITE, uint8);
__IOREG(ICP5H, 0xFFFFA049, __READ_WRITE, uint8);
#define P0P5               (((volatile __bitf_T *)0xFFFFA048)->bit00)
#define P1P5               (((volatile __bitf_T *)0xFFFFA048)->bit01)
#define P2P5               (((volatile __bitf_T *)0xFFFFA048)->bit02)
#define TBP5               (((volatile __bitf_T *)0xFFFFA048)->bit06)
#define MKP5               (((volatile __bitf_T *)0xFFFFA048)->bit07)
#define RFP5               (((volatile __bitf_T *)0xFFFFA049)->bit04)
#define CTP5               (((const volatile __bitf_T *)0xFFFFA049)->bit07)
__IOREG(ICP10, 0xFFFFA04A, __READ_WRITE, uint16);
__IOREG(ICP10L, 0xFFFFA04A, __READ_WRITE, uint8);
__IOREG(ICP10H, 0xFFFFA04B, __READ_WRITE, uint8);
#define P0P10              (((volatile __bitf_T *)0xFFFFA04A)->bit00)
#define P1P10              (((volatile __bitf_T *)0xFFFFA04A)->bit01)
#define P2P10              (((volatile __bitf_T *)0xFFFFA04A)->bit02)
#define TBP10              (((volatile __bitf_T *)0xFFFFA04A)->bit06)
#define MKP10              (((volatile __bitf_T *)0xFFFFA04A)->bit07)
#define RFP10              (((volatile __bitf_T *)0xFFFFA04B)->bit04)
#define CTP10              (((const volatile __bitf_T *)0xFFFFA04B)->bit07)
__IOREG(ICP11, 0xFFFFA04C, __READ_WRITE, uint16);
__IOREG(ICP11L, 0xFFFFA04C, __READ_WRITE, uint8);
__IOREG(ICP11H, 0xFFFFA04D, __READ_WRITE, uint8);
#define P0P11              (((volatile __bitf_T *)0xFFFFA04C)->bit00)
#define P1P11              (((volatile __bitf_T *)0xFFFFA04C)->bit01)
#define P2P11              (((volatile __bitf_T *)0xFFFFA04C)->bit02)
#define TBP11              (((volatile __bitf_T *)0xFFFFA04C)->bit06)
#define MKP11              (((volatile __bitf_T *)0xFFFFA04C)->bit07)
#define RFP11              (((volatile __bitf_T *)0xFFFFA04D)->bit04)
#define CTP11              (((const volatile __bitf_T *)0xFFFFA04D)->bit07)
__IOREG(ICTAUD0I1, 0xFFFFA04E, __READ_WRITE, uint16);
__IOREG(ICTAUD0I1L, 0xFFFFA04E, __READ_WRITE, uint8);
__IOREG(ICTAUD0I1H, 0xFFFFA04F, __READ_WRITE, uint8);
#define P0TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit00)
#define P1TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit01)
#define P2TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit02)
#define TBTAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit06)
#define MKTAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit07)
#define RFTAUD0I1          (((volatile __bitf_T *)0xFFFFA04F)->bit04)
#define CTTAUD0I1          (((const volatile __bitf_T *)0xFFFFA04F)->bit07)
__IOREG(ICTAUD0I3, 0xFFFFA050, __READ_WRITE, uint16);
__IOREG(ICTAUD0I3L, 0xFFFFA050, __READ_WRITE, uint8);
__IOREG(ICTAUD0I3H, 0xFFFFA051, __READ_WRITE, uint8);
#define P0TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit00)
#define P1TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit01)
#define P2TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit02)
#define TBTAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit06)
#define MKTAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit07)
#define RFTAUD0I3          (((volatile __bitf_T *)0xFFFFA051)->bit04)
#define CTTAUD0I3          (((const volatile __bitf_T *)0xFFFFA051)->bit07)
__IOREG(ICTAUD0I5, 0xFFFFA052, __READ_WRITE, uint16);
__IOREG(ICTAUD0I5L, 0xFFFFA052, __READ_WRITE, uint8);
__IOREG(ICTAUD0I5H, 0xFFFFA053, __READ_WRITE, uint8);
#define P0TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit00)
#define P1TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit01)
#define P2TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit02)
#define TBTAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit06)
#define MKTAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit07)
#define RFTAUD0I5          (((volatile __bitf_T *)0xFFFFA053)->bit04)
#define CTTAUD0I5          (((const volatile __bitf_T *)0xFFFFA053)->bit07)
__IOREG(ICTAUD0I7, 0xFFFFA054, __READ_WRITE, uint16);
__IOREG(ICTAUD0I7L, 0xFFFFA054, __READ_WRITE, uint8);
__IOREG(ICTAUD0I7H, 0xFFFFA055, __READ_WRITE, uint8);
#define P0TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit00)
#define P1TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit01)
#define P2TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit02)
#define TBTAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit06)
#define MKTAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit07)
#define RFTAUD0I7          (((volatile __bitf_T *)0xFFFFA055)->bit04)
#define CTTAUD0I7          (((const volatile __bitf_T *)0xFFFFA055)->bit07)
__IOREG(ICTAUD0I9, 0xFFFFA056, __READ_WRITE, uint16);
__IOREG(ICTAUD0I9L, 0xFFFFA056, __READ_WRITE, uint8);
__IOREG(ICTAUD0I9H, 0xFFFFA057, __READ_WRITE, uint8);
#define P0TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit00)
#define P1TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit01)
#define P2TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit02)
#define TBTAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit06)
#define MKTAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit07)
#define RFTAUD0I9          (((volatile __bitf_T *)0xFFFFA057)->bit04)
#define CTTAUD0I9          (((const volatile __bitf_T *)0xFFFFA057)->bit07)
__IOREG(ICTAUD0I11, 0xFFFFA058, __READ_WRITE, uint16);
__IOREG(ICTAUD0I11L, 0xFFFFA058, __READ_WRITE, uint8);
__IOREG(ICTAUD0I11H, 0xFFFFA059, __READ_WRITE, uint8);
#define P0TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit00)
#define P1TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit01)
#define P2TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit02)
#define TBTAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit06)
#define MKTAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit07)
#define RFTAUD0I11         (((volatile __bitf_T *)0xFFFFA059)->bit04)
#define CTTAUD0I11         (((const volatile __bitf_T *)0xFFFFA059)->bit07)
__IOREG(ICTAUD0I13, 0xFFFFA05A, __READ_WRITE, uint16);
__IOREG(ICTAUD0I13L, 0xFFFFA05A, __READ_WRITE, uint8);
__IOREG(ICTAUD0I13H, 0xFFFFA05B, __READ_WRITE, uint8);
#define P0TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit00)
#define P1TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit01)
#define P2TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit02)
#define TBTAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit06)
#define MKTAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit07)
#define RFTAUD0I13         (((volatile __bitf_T *)0xFFFFA05B)->bit04)
#define CTTAUD0I13         (((const volatile __bitf_T *)0xFFFFA05B)->bit07)
__IOREG(ICTAUD0I15, 0xFFFFA05C, __READ_WRITE, uint16);
__IOREG(ICTAUD0I15L, 0xFFFFA05C, __READ_WRITE, uint8);
__IOREG(ICTAUD0I15H, 0xFFFFA05D, __READ_WRITE, uint8);
#define P0TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit00)
#define P1TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit01)
#define P2TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit02)
#define TBTAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit06)
#define MKTAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit07)
#define RFTAUD0I15         (((volatile __bitf_T *)0xFFFFA05D)->bit04)
#define CTTAUD0I15         (((const volatile __bitf_T *)0xFFFFA05D)->bit07)
__IOREG(ICADCA0ERR, 0xFFFFA05E, __READ_WRITE, uint16);
__IOREG(ICADCA0ERRL, 0xFFFFA05E, __READ_WRITE, uint8);
__IOREG(ICADCA0ERRH, 0xFFFFA05F, __READ_WRITE, uint8);
#define P0ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit00)
#define P1ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit01)
#define P2ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit02)
#define TBADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit06)
#define MKADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit07)
#define RFADCA0ERR         (((volatile __bitf_T *)0xFFFFA05F)->bit04)
#define CTADCA0ERR         (((const volatile __bitf_T *)0xFFFFA05F)->bit07)
__IOREG(ICCSIG0IRE, 0xFFFFA062, __READ_WRITE, uint16);
__IOREG(ICCSIG0IREL, 0xFFFFA062, __READ_WRITE, uint8);
__IOREG(ICCSIG0IREH, 0xFFFFA063, __READ_WRITE, uint8);
#define P0CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit00)
#define P1CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit01)
#define P2CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit02)
#define TBCSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit06)
#define MKCSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit07)
#define RFCSIG0IRE         (((volatile __bitf_T *)0xFFFFA063)->bit04)
#define CTCSIG0IRE         (((const volatile __bitf_T *)0xFFFFA063)->bit07)
__IOREG(ICRLIN20, 0xFFFFA064, __READ_WRITE, uint16);
__IOREG(ICRLIN20L, 0xFFFFA064, __READ_WRITE, uint8);
__IOREG(ICRLIN20H, 0xFFFFA065, __READ_WRITE, uint8);
#define P0RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit00)
#define P1RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit01)
#define P2RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit02)
#define TBRLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit06)
#define MKRLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit07)
#define RFRLIN20           (((volatile __bitf_T *)0xFFFFA065)->bit04)
#define CTRLIN20           (((const volatile __bitf_T *)0xFFFFA065)->bit07)
__IOREG(ICRLIN21, 0xFFFFA066, __READ_WRITE, uint16);
__IOREG(ICRLIN21L, 0xFFFFA066, __READ_WRITE, uint8);
__IOREG(ICRLIN21H, 0xFFFFA067, __READ_WRITE, uint8);
#define P0RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit00)
#define P1RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit01)
#define P2RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit02)
#define TBRLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit06)
#define MKRLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit07)
#define RFRLIN21           (((volatile __bitf_T *)0xFFFFA067)->bit04)
#define CTRLIN21           (((const volatile __bitf_T *)0xFFFFA067)->bit07)
__IOREG(ICDMA0, 0xFFFFA068, __READ_WRITE, uint16);
__IOREG(ICDMA0L, 0xFFFFA068, __READ_WRITE, uint8);
__IOREG(ICDMA0H, 0xFFFFA069, __READ_WRITE, uint8);
#define P0DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit00)
#define P1DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit01)
#define P2DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit02)
#define TBDMA0             (((volatile __bitf_T *)0xFFFFA068)->bit06)
#define MKDMA0             (((volatile __bitf_T *)0xFFFFA068)->bit07)
#define RFDMA0             (((volatile __bitf_T *)0xFFFFA069)->bit04)
#define CTDMA0             (((const volatile __bitf_T *)0xFFFFA069)->bit07)
__IOREG(ICDMA1, 0xFFFFA06A, __READ_WRITE, uint16);
__IOREG(ICDMA1L, 0xFFFFA06A, __READ_WRITE, uint8);
__IOREG(ICDMA1H, 0xFFFFA06B, __READ_WRITE, uint8);
#define P0DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit00)
#define P1DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit01)
#define P2DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit02)
#define TBDMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit06)
#define MKDMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit07)
#define RFDMA1             (((volatile __bitf_T *)0xFFFFA06B)->bit04)
#define CTDMA1             (((const volatile __bitf_T *)0xFFFFA06B)->bit07)
__IOREG(ICDMA2, 0xFFFFA06C, __READ_WRITE, uint16);
__IOREG(ICDMA2L, 0xFFFFA06C, __READ_WRITE, uint8);
__IOREG(ICDMA2H, 0xFFFFA06D, __READ_WRITE, uint8);
#define P0DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit00)
#define P1DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit01)
#define P2DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit02)
#define TBDMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit06)
#define MKDMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit07)
#define RFDMA2             (((volatile __bitf_T *)0xFFFFA06D)->bit04)
#define CTDMA2             (((const volatile __bitf_T *)0xFFFFA06D)->bit07)
__IOREG(ICDMA3, 0xFFFFA06E, __READ_WRITE, uint16);
__IOREG(ICDMA3L, 0xFFFFA06E, __READ_WRITE, uint8);
__IOREG(ICDMA3H, 0xFFFFA06F, __READ_WRITE, uint8);
#define P0DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit00)
#define P1DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit01)
#define P2DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit02)
#define TBDMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit06)
#define MKDMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit07)
#define RFDMA3             (((volatile __bitf_T *)0xFFFFA06F)->bit04)
#define CTDMA3             (((const volatile __bitf_T *)0xFFFFA06F)->bit07)
__IOREG(ICDMA4, 0xFFFFA070, __READ_WRITE, uint16);
__IOREG(ICDMA4L, 0xFFFFA070, __READ_WRITE, uint8);
__IOREG(ICDMA4H, 0xFFFFA071, __READ_WRITE, uint8);
#define P0DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit00)
#define P1DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit01)
#define P2DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit02)
#define TBDMA4             (((volatile __bitf_T *)0xFFFFA070)->bit06)
#define MKDMA4             (((volatile __bitf_T *)0xFFFFA070)->bit07)
#define RFDMA4             (((volatile __bitf_T *)0xFFFFA071)->bit04)
#define CTDMA4             (((const volatile __bitf_T *)0xFFFFA071)->bit07)
__IOREG(ICDMA5, 0xFFFFA072, __READ_WRITE, uint16);
__IOREG(ICDMA5L, 0xFFFFA072, __READ_WRITE, uint8);
__IOREG(ICDMA5H, 0xFFFFA073, __READ_WRITE, uint8);
#define P0DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit00)
#define P1DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit01)
#define P2DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit02)
#define TBDMA5             (((volatile __bitf_T *)0xFFFFA072)->bit06)
#define MKDMA5             (((volatile __bitf_T *)0xFFFFA072)->bit07)
#define RFDMA5             (((volatile __bitf_T *)0xFFFFA073)->bit04)
#define CTDMA5             (((const volatile __bitf_T *)0xFFFFA073)->bit07)
__IOREG(ICDMA6, 0xFFFFA074, __READ_WRITE, uint16);
__IOREG(ICDMA6L, 0xFFFFA074, __READ_WRITE, uint8);
__IOREG(ICDMA6H, 0xFFFFA075, __READ_WRITE, uint8);
#define P0DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit00)
#define P1DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit01)
#define P2DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit02)
#define TBDMA6             (((volatile __bitf_T *)0xFFFFA074)->bit06)
#define MKDMA6             (((volatile __bitf_T *)0xFFFFA074)->bit07)
#define RFDMA6             (((volatile __bitf_T *)0xFFFFA075)->bit04)
#define CTDMA6             (((const volatile __bitf_T *)0xFFFFA075)->bit07)
__IOREG(ICDMA7, 0xFFFFA076, __READ_WRITE, uint16);
__IOREG(ICDMA7L, 0xFFFFA076, __READ_WRITE, uint8);
__IOREG(ICDMA7H, 0xFFFFA077, __READ_WRITE, uint8);
#define P0DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit00)
#define P1DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit01)
#define P2DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit02)
#define TBDMA7             (((volatile __bitf_T *)0xFFFFA076)->bit06)
#define MKDMA7             (((volatile __bitf_T *)0xFFFFA076)->bit07)
#define RFDMA7             (((volatile __bitf_T *)0xFFFFA077)->bit04)
#define CTDMA7             (((const volatile __bitf_T *)0xFFFFA077)->bit07)
__IOREG(ICDMA8, 0xFFFFA078, __READ_WRITE, uint16);
__IOREG(ICDMA8L, 0xFFFFA078, __READ_WRITE, uint8);
__IOREG(ICDMA8H, 0xFFFFA079, __READ_WRITE, uint8);
#define P0DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit00)
#define P1DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit01)
#define P2DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit02)
#define TBDMA8             (((volatile __bitf_T *)0xFFFFA078)->bit06)
#define MKDMA8             (((volatile __bitf_T *)0xFFFFA078)->bit07)
#define RFDMA8             (((volatile __bitf_T *)0xFFFFA079)->bit04)
#define CTDMA8             (((const volatile __bitf_T *)0xFFFFA079)->bit07)
__IOREG(ICDMA9, 0xFFFFA07A, __READ_WRITE, uint16);
__IOREG(ICDMA9L, 0xFFFFA07A, __READ_WRITE, uint8);
__IOREG(ICDMA9H, 0xFFFFA07B, __READ_WRITE, uint8);
#define P0DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit00)
#define P1DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit01)
#define P2DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit02)
#define TBDMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit06)
#define MKDMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit07)
#define RFDMA9             (((volatile __bitf_T *)0xFFFFA07B)->bit04)
#define CTDMA9             (((const volatile __bitf_T *)0xFFFFA07B)->bit07)
__IOREG(ICDMA10, 0xFFFFA07C, __READ_WRITE, uint16);
__IOREG(ICDMA10L, 0xFFFFA07C, __READ_WRITE, uint8);
__IOREG(ICDMA10H, 0xFFFFA07D, __READ_WRITE, uint8);
#define P0DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit00)
#define P1DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit01)
#define P2DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit02)
#define TBDMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit06)
#define MKDMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit07)
#define RFDMA10            (((volatile __bitf_T *)0xFFFFA07D)->bit04)
#define CTDMA10            (((const volatile __bitf_T *)0xFFFFA07D)->bit07)
__IOREG(ICDMA11, 0xFFFFA07E, __READ_WRITE, uint16);
__IOREG(ICDMA11L, 0xFFFFA07E, __READ_WRITE, uint8);
__IOREG(ICDMA11H, 0xFFFFA07F, __READ_WRITE, uint8);
#define P0DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit00)
#define P1DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit01)
#define P2DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit02)
#define TBDMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit06)
#define MKDMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit07)
#define RFDMA11            (((volatile __bitf_T *)0xFFFFA07F)->bit04)
#define CTDMA11            (((const volatile __bitf_T *)0xFFFFA07F)->bit07)
__IOREG(ICDMA12, 0xFFFFA080, __READ_WRITE, uint16);
__IOREG(ICDMA12L, 0xFFFFA080, __READ_WRITE, uint8);
__IOREG(ICDMA12H, 0xFFFFA081, __READ_WRITE, uint8);
#define P0DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit00)
#define P1DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit01)
#define P2DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit02)
#define TBDMA12            (((volatile __bitf_T *)0xFFFFA080)->bit06)
#define MKDMA12            (((volatile __bitf_T *)0xFFFFA080)->bit07)
#define RFDMA12            (((volatile __bitf_T *)0xFFFFA081)->bit04)
#define CTDMA12            (((const volatile __bitf_T *)0xFFFFA081)->bit07)
__IOREG(ICDMA13, 0xFFFFA082, __READ_WRITE, uint16);
__IOREG(ICDMA13L, 0xFFFFA082, __READ_WRITE, uint8);
__IOREG(ICDMA13H, 0xFFFFA083, __READ_WRITE, uint8);
#define P0DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit00)
#define P1DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit01)
#define P2DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit02)
#define TBDMA13            (((volatile __bitf_T *)0xFFFFA082)->bit06)
#define MKDMA13            (((volatile __bitf_T *)0xFFFFA082)->bit07)
#define RFDMA13            (((volatile __bitf_T *)0xFFFFA083)->bit04)
#define CTDMA13            (((const volatile __bitf_T *)0xFFFFA083)->bit07)
__IOREG(ICDMA14, 0xFFFFA084, __READ_WRITE, uint16);
__IOREG(ICDMA14L, 0xFFFFA084, __READ_WRITE, uint8);
__IOREG(ICDMA14H, 0xFFFFA085, __READ_WRITE, uint8);
#define P0DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit00)
#define P1DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit01)
#define P2DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit02)
#define TBDMA14            (((volatile __bitf_T *)0xFFFFA084)->bit06)
#define MKDMA14            (((volatile __bitf_T *)0xFFFFA084)->bit07)
#define RFDMA14            (((volatile __bitf_T *)0xFFFFA085)->bit04)
#define CTDMA14            (((const volatile __bitf_T *)0xFFFFA085)->bit07)
__IOREG(ICDMA15, 0xFFFFA086, __READ_WRITE, uint16);
__IOREG(ICDMA15L, 0xFFFFA086, __READ_WRITE, uint8);
__IOREG(ICDMA15H, 0xFFFFA087, __READ_WRITE, uint8);
#define P0DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit00)
#define P1DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit01)
#define P2DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit02)
#define TBDMA15            (((volatile __bitf_T *)0xFFFFA086)->bit06)
#define MKDMA15            (((volatile __bitf_T *)0xFFFFA086)->bit07)
#define RFDMA15            (((volatile __bitf_T *)0xFFFFA087)->bit04)
#define CTDMA15            (((const volatile __bitf_T *)0xFFFFA087)->bit07)
__IOREG(ICRIIC0TI, 0xFFFFA088, __READ_WRITE, uint16);
__IOREG(ICRIIC0TIL, 0xFFFFA088, __READ_WRITE, uint8);
__IOREG(ICRIIC0TIH, 0xFFFFA089, __READ_WRITE, uint8);
#define P0RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit00)
#define P1RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit01)
#define P2RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit02)
#define TBRIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit06)
#define MKRIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit07)
#define RFRIIC0TI          (((volatile __bitf_T *)0xFFFFA089)->bit04)
#define CTRIIC0TI          (((const volatile __bitf_T *)0xFFFFA089)->bit07)
__IOREG(ICRIIC0TEI, 0xFFFFA08A, __READ_WRITE, uint16);
__IOREG(ICRIIC0TEIL, 0xFFFFA08A, __READ_WRITE, uint8);
__IOREG(ICRIIC0TEIH, 0xFFFFA08B, __READ_WRITE, uint8);
#define P0RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit00)
#define P1RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit01)
#define P2RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit02)
#define TBRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit06)
#define MKRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit07)
#define RFRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08B)->bit04)
#define CTRIIC0TEI         (((const volatile __bitf_T *)0xFFFFA08B)->bit07)
__IOREG(ICRIIC0RI, 0xFFFFA08C, __READ_WRITE, uint16);
__IOREG(ICRIIC0RIL, 0xFFFFA08C, __READ_WRITE, uint8);
__IOREG(ICRIIC0RIH, 0xFFFFA08D, __READ_WRITE, uint8);
#define P0RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit00)
#define P1RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit01)
#define P2RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit02)
#define TBRIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit06)
#define MKRIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit07)
#define RFRIIC0RI          (((volatile __bitf_T *)0xFFFFA08D)->bit04)
#define CTRIIC0RI          (((const volatile __bitf_T *)0xFFFFA08D)->bit07)
__IOREG(ICRIIC0EE, 0xFFFFA08E, __READ_WRITE, uint16);
__IOREG(ICRIIC0EEL, 0xFFFFA08E, __READ_WRITE, uint8);
__IOREG(ICRIIC0EEH, 0xFFFFA08F, __READ_WRITE, uint8);
#define P0RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit00)
#define P1RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit01)
#define P2RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit02)
#define TBRIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit06)
#define MKRIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit07)
#define RFRIIC0EE          (((volatile __bitf_T *)0xFFFFA08F)->bit04)
#define CTRIIC0EE          (((const volatile __bitf_T *)0xFFFFA08F)->bit07)
__IOREG(ICTAUJ0I0, 0xFFFFA090, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I0L, 0xFFFFA090, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I0H, 0xFFFFA091, __READ_WRITE, uint8);
#define P0TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit00)
#define P1TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit01)
#define P2TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit02)
#define TBTAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit06)
#define MKTAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit07)
#define RFTAUJ0I0          (((volatile __bitf_T *)0xFFFFA091)->bit04)
#define CTTAUJ0I0          (((const volatile __bitf_T *)0xFFFFA091)->bit07)
__IOREG(ICTAUJ0I1, 0xFFFFA092, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I1L, 0xFFFFA092, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I1H, 0xFFFFA093, __READ_WRITE, uint8);
#define P0TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit00)
#define P1TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit01)
#define P2TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit02)
#define TBTAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit06)
#define MKTAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit07)
#define RFTAUJ0I1          (((volatile __bitf_T *)0xFFFFA093)->bit04)
#define CTTAUJ0I1          (((const volatile __bitf_T *)0xFFFFA093)->bit07)
__IOREG(ICTAUJ0I2, 0xFFFFA094, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I2L, 0xFFFFA094, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I2H, 0xFFFFA095, __READ_WRITE, uint8);
#define P0TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit00)
#define P1TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit01)
#define P2TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit02)
#define TBTAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit06)
#define MKTAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit07)
#define RFTAUJ0I2          (((volatile __bitf_T *)0xFFFFA095)->bit04)
#define CTTAUJ0I2          (((const volatile __bitf_T *)0xFFFFA095)->bit07)
__IOREG(ICTAUJ0I3, 0xFFFFA096, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I3L, 0xFFFFA096, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I3H, 0xFFFFA097, __READ_WRITE, uint8);
#define P0TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit00)
#define P1TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit01)
#define P2TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit02)
#define TBTAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit06)
#define MKTAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit07)
#define RFTAUJ0I3          (((volatile __bitf_T *)0xFFFFA097)->bit04)
#define CTTAUJ0I3          (((const volatile __bitf_T *)0xFFFFA097)->bit07)
__IOREG(ICOSTM0, 0xFFFFA098, __READ_WRITE, uint16);
__IOREG(ICOSTM0L, 0xFFFFA098, __READ_WRITE, uint8);
__IOREG(ICOSTM0H, 0xFFFFA099, __READ_WRITE, uint8);
#define P0OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit00)
#define P1OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit01)
#define P2OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit02)
#define TBOSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit06)
#define MKOSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit07)
#define RFOSTM0            (((volatile __bitf_T *)0xFFFFA099)->bit04)
#define CTOSTM0            (((const volatile __bitf_T *)0xFFFFA099)->bit07)
__IOREG(ICENCA0IOV, 0xFFFFA09A, __READ_WRITE, uint16);
__IOREG(ICPWGA4, 0xFFFFA09A, __READ_WRITE, uint16);
__IOREG(ICENCA0IOVL, 0xFFFFA09A, __READ_WRITE, uint8);
__IOREG(ICPWGA4L, 0xFFFFA09A, __READ_WRITE, uint8);
__IOREG(ICENCA0IOVH, 0xFFFFA09B, __READ_WRITE, uint8);
__IOREG(ICPWGA4H, 0xFFFFA09B, __READ_WRITE, uint8);
#define P0ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit00)
#define P0PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit00)
#define P1ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit01)
#define P1PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit01)
#define P2ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit02)
#define P2PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit02)
#define TBENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit06)
#define TBPWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit06)
#define MKENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit07)
#define MKPWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit07)
#define RFENCA0IOV         (((volatile __bitf_T *)0xFFFFA09B)->bit04)
#define RFPWGA4            (((volatile __bitf_T *)0xFFFFA09B)->bit04)
#define CTENCA0IOV         (((const volatile __bitf_T *)0xFFFFA09B)->bit07)
#define CTPWGA4            (((const volatile __bitf_T *)0xFFFFA09B)->bit07)
__IOREG(ICENCA0IUD, 0xFFFFA09C, __READ_WRITE, uint16);
__IOREG(ICPWGA5, 0xFFFFA09C, __READ_WRITE, uint16);
__IOREG(ICENCA0IUDL, 0xFFFFA09C, __READ_WRITE, uint8);
__IOREG(ICPWGA5L, 0xFFFFA09C, __READ_WRITE, uint8);
__IOREG(ICENCA0IUDH, 0xFFFFA09D, __READ_WRITE, uint8);
__IOREG(ICPWGA5H, 0xFFFFA09D, __READ_WRITE, uint8);
#define P0ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit00)
#define P0PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit00)
#define P1ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit01)
#define P1PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit01)
#define P2ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit02)
#define P2PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit02)
#define TBENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit06)
#define TBPWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit06)
#define MKENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit07)
#define MKPWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit07)
#define RFENCA0IUD         (((volatile __bitf_T *)0xFFFFA09D)->bit04)
#define RFPWGA5            (((volatile __bitf_T *)0xFFFFA09D)->bit04)
#define CTENCA0IUD         (((const volatile __bitf_T *)0xFFFFA09D)->bit07)
#define CTPWGA5            (((const volatile __bitf_T *)0xFFFFA09D)->bit07)
__IOREG(ICENCA0I0, 0xFFFFA09E, __READ_WRITE, uint16);
__IOREG(ICPWGA6, 0xFFFFA09E, __READ_WRITE, uint16);
__IOREG(ICENCA0I0L, 0xFFFFA09E, __READ_WRITE, uint8);
__IOREG(ICPWGA6L, 0xFFFFA09E, __READ_WRITE, uint8);
__IOREG(ICENCA0I0H, 0xFFFFA09F, __READ_WRITE, uint8);
__IOREG(ICPWGA6H, 0xFFFFA09F, __READ_WRITE, uint8);
#define P0ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit00)
#define P0PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit00)
#define P1ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit01)
#define P1PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit01)
#define P2ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit02)
#define P2PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit02)
#define TBENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit06)
#define TBPWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit06)
#define MKENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit07)
#define MKPWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit07)
#define RFENCA0I0          (((volatile __bitf_T *)0xFFFFA09F)->bit04)
#define RFPWGA6            (((volatile __bitf_T *)0xFFFFA09F)->bit04)
#define CTENCA0I0          (((const volatile __bitf_T *)0xFFFFA09F)->bit07)
#define CTPWGA6            (((const volatile __bitf_T *)0xFFFFA09F)->bit07)
__IOREG(ICENCA0I1, 0xFFFFA0A0, __READ_WRITE, uint16);
__IOREG(ICPWGA7, 0xFFFFA0A0, __READ_WRITE, uint16);
__IOREG(ICENCA0I1L, 0xFFFFA0A0, __READ_WRITE, uint8);
__IOREG(ICPWGA7L, 0xFFFFA0A0, __READ_WRITE, uint8);
__IOREG(ICENCA0I1H, 0xFFFFA0A1, __READ_WRITE, uint8);
__IOREG(ICPWGA7H, 0xFFFFA0A1, __READ_WRITE, uint8);
#define P0ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit00)
#define P0PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit00)
#define P1ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit01)
#define P1PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit01)
#define P2ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit02)
#define P2PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit02)
#define TBENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit06)
#define TBPWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit06)
#define MKENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit07)
#define MKPWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit07)
#define RFENCA0I1          (((volatile __bitf_T *)0xFFFFA0A1)->bit04)
#define RFPWGA7            (((volatile __bitf_T *)0xFFFFA0A1)->bit04)
#define CTENCA0I1          (((const volatile __bitf_T *)0xFFFFA0A1)->bit07)
#define CTPWGA7            (((const volatile __bitf_T *)0xFFFFA0A1)->bit07)
__IOREG(ICENCA0IEC, 0xFFFFA0A2, __READ_WRITE, uint16);
__IOREG(ICENCA0IECL, 0xFFFFA0A2, __READ_WRITE, uint8);
__IOREG(ICENCA0IECH, 0xFFFFA0A3, __READ_WRITE, uint8);
#define P0ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit00)
#define P1ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit01)
#define P2ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit02)
#define TBENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit06)
#define MKENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit07)
#define RFENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A3)->bit04)
#define CTENCA0IEC         (((const volatile __bitf_T *)0xFFFFA0A3)->bit07)
__IOREG(ICKR0, 0xFFFFA0A4, __READ_WRITE, uint16);
__IOREG(ICKR0L, 0xFFFFA0A4, __READ_WRITE, uint8);
__IOREG(ICKR0H, 0xFFFFA0A5, __READ_WRITE, uint8);
#define P0KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit00)
#define P1KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit01)
#define P2KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit02)
#define TBKR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit06)
#define MKKR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit07)
#define RFKR0              (((volatile __bitf_T *)0xFFFFA0A5)->bit04)
#define CTKR0              (((const volatile __bitf_T *)0xFFFFA0A5)->bit07)
__IOREG(ICQFULL, 0xFFFFA0A6, __READ_WRITE, uint16);
__IOREG(ICQFULLL, 0xFFFFA0A6, __READ_WRITE, uint8);
__IOREG(ICQFULLH, 0xFFFFA0A7, __READ_WRITE, uint8);
#define P0QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit00)
#define P1QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit01)
#define P2QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit02)
#define TBQFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit06)
#define MKQFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit07)
#define RFQFULL            (((volatile __bitf_T *)0xFFFFA0A7)->bit04)
#define CTQFULL            (((const volatile __bitf_T *)0xFFFFA0A7)->bit07)
__IOREG(ICPWGA0, 0xFFFFA0A8, __READ_WRITE, uint16);
__IOREG(ICPWGA0L, 0xFFFFA0A8, __READ_WRITE, uint8);
__IOREG(ICPWGA0H, 0xFFFFA0A9, __READ_WRITE, uint8);
#define P0PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit00)
#define P1PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit01)
#define P2PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit02)
#define TBPWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit06)
#define MKPWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit07)
#define RFPWGA0            (((volatile __bitf_T *)0xFFFFA0A9)->bit04)
#define CTPWGA0            (((const volatile __bitf_T *)0xFFFFA0A9)->bit07)
__IOREG(ICPWGA1, 0xFFFFA0AA, __READ_WRITE, uint16);
__IOREG(ICPWGA1L, 0xFFFFA0AA, __READ_WRITE, uint8);
__IOREG(ICPWGA1H, 0xFFFFA0AB, __READ_WRITE, uint8);
#define P0PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit00)
#define P1PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit01)
#define P2PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit02)
#define TBPWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit06)
#define MKPWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit07)
#define RFPWGA1            (((volatile __bitf_T *)0xFFFFA0AB)->bit04)
#define CTPWGA1            (((const volatile __bitf_T *)0xFFFFA0AB)->bit07)
__IOREG(ICPWGA2, 0xFFFFA0AC, __READ_WRITE, uint16);
__IOREG(ICPWGA2L, 0xFFFFA0AC, __READ_WRITE, uint8);
__IOREG(ICPWGA2H, 0xFFFFA0AD, __READ_WRITE, uint8);
#define P0PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit00)
#define P1PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit01)
#define P2PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit02)
#define TBPWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit06)
#define MKPWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit07)
#define RFPWGA2            (((volatile __bitf_T *)0xFFFFA0AD)->bit04)
#define CTPWGA2            (((const volatile __bitf_T *)0xFFFFA0AD)->bit07)
__IOREG(ICPWGA3, 0xFFFFA0AE, __READ_WRITE, uint16);
__IOREG(ICPWGA3L, 0xFFFFA0AE, __READ_WRITE, uint8);
__IOREG(ICPWGA3H, 0xFFFFA0AF, __READ_WRITE, uint8);
#define P0PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit00)
#define P1PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit01)
#define P2PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit02)
#define TBPWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit06)
#define MKPWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit07)
#define RFPWGA3            (((volatile __bitf_T *)0xFFFFA0AF)->bit04)
#define CTPWGA3            (((const volatile __bitf_T *)0xFFFFA0AF)->bit07)
__IOREG(ICPWGA8, 0xFFFFA0B0, __READ_WRITE, uint16);
__IOREG(ICPWGA8L, 0xFFFFA0B0, __READ_WRITE, uint8);
__IOREG(ICPWGA8H, 0xFFFFA0B1, __READ_WRITE, uint8);
#define P0PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit00)
#define P1PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit01)
#define P2PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit02)
#define TBPWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit06)
#define MKPWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit07)
#define RFPWGA8            (((volatile __bitf_T *)0xFFFFA0B1)->bit04)
#define CTPWGA8            (((const volatile __bitf_T *)0xFFFFA0B1)->bit07)
__IOREG(ICPWGA9, 0xFFFFA0B2, __READ_WRITE, uint16);
__IOREG(ICPWGA9L, 0xFFFFA0B2, __READ_WRITE, uint8);
__IOREG(ICPWGA9H, 0xFFFFA0B3, __READ_WRITE, uint8);
#define P0PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit00)
#define P1PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit01)
#define P2PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit02)
#define TBPWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit06)
#define MKPWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit07)
#define RFPWGA9            (((volatile __bitf_T *)0xFFFFA0B3)->bit04)
#define CTPWGA9            (((const volatile __bitf_T *)0xFFFFA0B3)->bit07)
__IOREG(ICPWGA10, 0xFFFFA0B4, __READ_WRITE, uint16);
__IOREG(ICPWGA10L, 0xFFFFA0B4, __READ_WRITE, uint8);
__IOREG(ICPWGA10H, 0xFFFFA0B5, __READ_WRITE, uint8);
#define P0PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit00)
#define P1PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit01)
#define P2PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit02)
#define TBPWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit06)
#define MKPWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit07)
#define RFPWGA10           (((volatile __bitf_T *)0xFFFFA0B5)->bit04)
#define CTPWGA10           (((const volatile __bitf_T *)0xFFFFA0B5)->bit07)
__IOREG(ICPWGA11, 0xFFFFA0B6, __READ_WRITE, uint16);
__IOREG(ICPWGA11L, 0xFFFFA0B6, __READ_WRITE, uint8);
__IOREG(ICPWGA11H, 0xFFFFA0B7, __READ_WRITE, uint8);
#define P0PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit00)
#define P1PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit01)
#define P2PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit02)
#define TBPWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit06)
#define MKPWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit07)
#define RFPWGA11           (((volatile __bitf_T *)0xFFFFA0B7)->bit04)
#define CTPWGA11           (((const volatile __bitf_T *)0xFFFFA0B7)->bit07)
__IOREG(ICPWGA12, 0xFFFFA0B8, __READ_WRITE, uint16);
__IOREG(ICPWGA12L, 0xFFFFA0B8, __READ_WRITE, uint8);
__IOREG(ICPWGA12H, 0xFFFFA0B9, __READ_WRITE, uint8);
#define P0PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit00)
#define P1PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit01)
#define P2PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit02)
#define TBPWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit06)
#define MKPWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit07)
#define RFPWGA12           (((volatile __bitf_T *)0xFFFFA0B9)->bit04)
#define CTPWGA12           (((const volatile __bitf_T *)0xFFFFA0B9)->bit07)
__IOREG(ICPWGA13, 0xFFFFA0BA, __READ_WRITE, uint16);
__IOREG(ICPWGA13L, 0xFFFFA0BA, __READ_WRITE, uint8);
__IOREG(ICPWGA13H, 0xFFFFA0BB, __READ_WRITE, uint8);
#define P0PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit00)
#define P1PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit01)
#define P2PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit02)
#define TBPWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit06)
#define MKPWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit07)
#define RFPWGA13           (((volatile __bitf_T *)0xFFFFA0BB)->bit04)
#define CTPWGA13           (((const volatile __bitf_T *)0xFFFFA0BB)->bit07)
__IOREG(ICPWGA14, 0xFFFFA0BC, __READ_WRITE, uint16);
__IOREG(ICPWGA14L, 0xFFFFA0BC, __READ_WRITE, uint8);
__IOREG(ICPWGA14H, 0xFFFFA0BD, __READ_WRITE, uint8);
#define P0PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit00)
#define P1PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit01)
#define P2PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit02)
#define TBPWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit06)
#define MKPWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit07)
#define RFPWGA14           (((volatile __bitf_T *)0xFFFFA0BD)->bit04)
#define CTPWGA14           (((const volatile __bitf_T *)0xFFFFA0BD)->bit07)
__IOREG(ICPWGA15, 0xFFFFA0BE, __READ_WRITE, uint16);
__IOREG(ICPWGA15L, 0xFFFFA0BE, __READ_WRITE, uint8);
__IOREG(ICPWGA15H, 0xFFFFA0BF, __READ_WRITE, uint8);
#define P0PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit00)
#define P1PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit01)
#define P2PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit02)
#define TBPWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit06)
#define MKPWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit07)
#define RFPWGA15           (((volatile __bitf_T *)0xFFFFA0BF)->bit04)
#define CTPWGA15           (((const volatile __bitf_T *)0xFFFFA0BF)->bit07)
__IOREG(ICFLERR, 0xFFFFA0CC, __READ_WRITE, uint16);
__IOREG(ICFLERRL, 0xFFFFA0CC, __READ_WRITE, uint8);
__IOREG(ICFLERRH, 0xFFFFA0CD, __READ_WRITE, uint8);
#define P0FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit00)
#define P1FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit01)
#define P2FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit02)
#define TBFLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit06)
#define MKFLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit07)
#define RFFLERR            (((volatile __bitf_T *)0xFFFFA0CD)->bit04)
#define CTFLERR            (((const volatile __bitf_T *)0xFFFFA0CD)->bit07)
__IOREG(ICFLENDNM, 0xFFFFA0CE, __READ_WRITE, uint16);
__IOREG(ICFLENDNML, 0xFFFFA0CE, __READ_WRITE, uint8);
__IOREG(ICFLENDNMH, 0xFFFFA0CF, __READ_WRITE, uint8);
#define P0FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit00)
#define P1FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit01)
#define P2FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit02)
#define TBFLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit06)
#define MKFLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit07)
#define RFFLENDNM          (((volatile __bitf_T *)0xFFFFA0CF)->bit04)
#define CTFLENDNM          (((const volatile __bitf_T *)0xFFFFA0CF)->bit07)
__IOREG(ICCWEND, 0xFFFFA0D0, __READ_WRITE, uint16);
__IOREG(ICCWENDL, 0xFFFFA0D0, __READ_WRITE, uint8);
__IOREG(ICCWENDH, 0xFFFFA0D1, __READ_WRITE, uint8);
#define P0CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit00)
#define P1CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit01)
#define P2CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit02)
#define TBCWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit06)
#define MKCWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit07)
#define RFCWEND            (((volatile __bitf_T *)0xFFFFA0D1)->bit04)
#define CTCWEND            (((const volatile __bitf_T *)0xFFFFA0D1)->bit07)
__IOREG(ICRCAN1ERR, 0xFFFFA0D2, __READ_WRITE, uint16);
__IOREG(ICRCAN1ERRL, 0xFFFFA0D2, __READ_WRITE, uint8);
__IOREG(ICRCAN1ERRH, 0xFFFFA0D3, __READ_WRITE, uint8);
#define P0RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit00)
#define P1RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit01)
#define P2RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit02)
#define TBRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit06)
#define MKRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit07)
#define RFRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D3)->bit04)
#define CTRCAN1ERR         (((const volatile __bitf_T *)0xFFFFA0D3)->bit07)
__IOREG(ICRCAN1REC, 0xFFFFA0D4, __READ_WRITE, uint16);
__IOREG(ICRCAN1RECL, 0xFFFFA0D4, __READ_WRITE, uint8);
__IOREG(ICRCAN1RECH, 0xFFFFA0D5, __READ_WRITE, uint8);
#define P0RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit00)
#define P1RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit01)
#define P2RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit02)
#define TBRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit06)
#define MKRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit07)
#define RFRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D5)->bit04)
#define CTRCAN1REC         (((const volatile __bitf_T *)0xFFFFA0D5)->bit07)
__IOREG(ICRCAN1TRX, 0xFFFFA0D6, __READ_WRITE, uint16);
__IOREG(ICRCAN1TRXL, 0xFFFFA0D6, __READ_WRITE, uint8);
__IOREG(ICRCAN1TRXH, 0xFFFFA0D7, __READ_WRITE, uint8);
#define P0RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit00)
#define P1RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit01)
#define P2RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit02)
#define TBRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit06)
#define MKRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit07)
#define RFRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D7)->bit04)
#define CTRCAN1TRX         (((const volatile __bitf_T *)0xFFFFA0D7)->bit07)
__IOREG(ICTAPA0IPEK0_2, 0xFFFFA0D8, __READ_WRITE, uint16);
__IOREG(ICTAPA0IPEK0L_2, 0xFFFFA0D8, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0H_2, 0xFFFFA0D9, __READ_WRITE, uint8);
#define P0TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit00)
#define P1TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit01)
#define P2TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit02)
#define TBTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit06)
#define MKTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit07)
#define RFTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D9)->bit04)
#define CTTAPA0IPEK0_2     (((const volatile __bitf_T *)0xFFFFA0D9)->bit07)
__IOREG(ICTAPA0IVLY0_2, 0xFFFFA0DA, __READ_WRITE, uint16);
__IOREG(ICTAPA0IVLY0L_2, 0xFFFFA0DA, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0H_2, 0xFFFFA0DB, __READ_WRITE, uint8);
#define P0TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit00)
#define P1TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit01)
#define P2TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit02)
#define TBTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit06)
#define MKTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit07)
#define RFTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DB)->bit04)
#define CTTAPA0IVLY0_2     (((const volatile __bitf_T *)0xFFFFA0DB)->bit07)
__IOREG(ICCSIG0IC_2, 0xFFFFA0DC, __READ_WRITE, uint16);
__IOREG(ICCSIG0ICL_2, 0xFFFFA0DC, __READ_WRITE, uint8);
__IOREG(ICCSIG0ICH_2, 0xFFFFA0DD, __READ_WRITE, uint8);
#define P0CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit00)
#define P1CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit01)
#define P2CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit02)
#define TBCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit06)
#define MKCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit07)
#define RFCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DD)->bit04)
#define CTCSIG0IC_2        (((const volatile __bitf_T *)0xFFFFA0DD)->bit07)
__IOREG(ICCSIG0IR_2, 0xFFFFA0DE, __READ_WRITE, uint16);
__IOREG(ICCSIG0IRL_2, 0xFFFFA0DE, __READ_WRITE, uint8);
__IOREG(ICCSIG0IRH_2, 0xFFFFA0DF, __READ_WRITE, uint8);
#define P0CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit00)
#define P1CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit01)
#define P2CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit02)
#define TBCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit06)
#define MKCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit07)
#define RFCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DF)->bit04)
#define CTCSIG0IR_2        (((const volatile __bitf_T *)0xFFFFA0DF)->bit07)
__IOREG(ICRLIN31, 0xFFFFA0E0, __READ_WRITE, uint16);
__IOREG(ICRLIN31L, 0xFFFFA0E0, __READ_WRITE, uint8);
__IOREG(ICRLIN31H, 0xFFFFA0E1, __READ_WRITE, uint8);
#define P0RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit00)
#define P1RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit01)
#define P2RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit02)
#define TBRLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit06)
#define MKRLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit07)
#define RFRLIN31           (((volatile __bitf_T *)0xFFFFA0E1)->bit04)
#define CTRLIN31           (((const volatile __bitf_T *)0xFFFFA0E1)->bit07)
__IOREG(ICRLIN31UR0, 0xFFFFA0E2, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR0L, 0xFFFFA0E2, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR0H, 0xFFFFA0E3, __READ_WRITE, uint8);
#define P0RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit00)
#define P1RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit01)
#define P2RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit02)
#define TBRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit06)
#define MKRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit07)
#define RFRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E3)->bit04)
#define CTRLIN31UR0        (((const volatile __bitf_T *)0xFFFFA0E3)->bit07)
__IOREG(ICRLIN31UR1, 0xFFFFA0E4, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR1L, 0xFFFFA0E4, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR1H, 0xFFFFA0E5, __READ_WRITE, uint8);
#define P0RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit00)
#define P1RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit01)
#define P2RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit02)
#define TBRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit06)
#define MKRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit07)
#define RFRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E5)->bit04)
#define CTRLIN31UR1        (((const volatile __bitf_T *)0xFFFFA0E5)->bit07)
__IOREG(ICRLIN31UR2, 0xFFFFA0E6, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR2L, 0xFFFFA0E6, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR2H, 0xFFFFA0E7, __READ_WRITE, uint8);
#define P0RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit00)
#define P1RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit01)
#define P2RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit02)
#define TBRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit06)
#define MKRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit07)
#define RFRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E7)->bit04)
#define CTRLIN31UR2        (((const volatile __bitf_T *)0xFFFFA0E7)->bit07)
__IOREG(ICPWGA20, 0xFFFFA0E8, __READ_WRITE, uint16);
__IOREG(ICPWGA20L, 0xFFFFA0E8, __READ_WRITE, uint8);
__IOREG(ICPWGA20H, 0xFFFFA0E9, __READ_WRITE, uint8);
#define P0PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit00)
#define P1PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit01)
#define P2PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit02)
#define TBPWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit06)
#define MKPWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit07)
#define RFPWGA20           (((volatile __bitf_T *)0xFFFFA0E9)->bit04)
#define CTPWGA20           (((const volatile __bitf_T *)0xFFFFA0E9)->bit07)
__IOREG(ICPWGA21, 0xFFFFA0EA, __READ_WRITE, uint16);
__IOREG(ICPWGA21L, 0xFFFFA0EA, __READ_WRITE, uint8);
__IOREG(ICPWGA21H, 0xFFFFA0EB, __READ_WRITE, uint8);
#define P0PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit00)
#define P1PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit01)
#define P2PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit02)
#define TBPWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit06)
#define MKPWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit07)
#define RFPWGA21           (((volatile __bitf_T *)0xFFFFA0EB)->bit04)
#define CTPWGA21           (((const volatile __bitf_T *)0xFFFFA0EB)->bit07)
__IOREG(ICPWGA22, 0xFFFFA0EC, __READ_WRITE, uint16);
__IOREG(ICPWGA22L, 0xFFFFA0EC, __READ_WRITE, uint8);
__IOREG(ICPWGA22H, 0xFFFFA0ED, __READ_WRITE, uint8);
#define P0PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit00)
#define P1PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit01)
#define P2PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit02)
#define TBPWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit06)
#define MKPWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit07)
#define RFPWGA22           (((volatile __bitf_T *)0xFFFFA0ED)->bit04)
#define CTPWGA22           (((const volatile __bitf_T *)0xFFFFA0ED)->bit07)
__IOREG(ICPWGA23, 0xFFFFA0EE, __READ_WRITE, uint16);
__IOREG(ICPWGA23L, 0xFFFFA0EE, __READ_WRITE, uint8);
__IOREG(ICPWGA23H, 0xFFFFA0EF, __READ_WRITE, uint8);
#define P0PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit00)
#define P1PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit01)
#define P2PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit02)
#define TBPWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit06)
#define MKPWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit07)
#define RFPWGA23           (((volatile __bitf_T *)0xFFFFA0EF)->bit04)
#define CTPWGA23           (((const volatile __bitf_T *)0xFFFFA0EF)->bit07)
__IOREG(ICPWGA16, 0xFFFFA112, __READ_WRITE, uint16);
__IOREG(ICPWGA16L, 0xFFFFA112, __READ_WRITE, uint8);
__IOREG(ICPWGA16H, 0xFFFFA113, __READ_WRITE, uint8);
#define P0PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit00)
#define P1PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit01)
#define P2PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit02)
#define TBPWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit06)
#define MKPWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit07)
#define RFPWGA16           (((volatile __bitf_T *)0xFFFFA113)->bit04)
#define CTPWGA16           (((const volatile __bitf_T *)0xFFFFA113)->bit07)
__IOREG(ICPWGA17, 0xFFFFA116, __READ_WRITE, uint16);
__IOREG(ICPWGA17L, 0xFFFFA116, __READ_WRITE, uint8);
__IOREG(ICPWGA17H, 0xFFFFA117, __READ_WRITE, uint8);
#define P0PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit00)
#define P1PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit01)
#define P2PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit02)
#define TBPWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit06)
#define MKPWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit07)
#define RFPWGA17           (((volatile __bitf_T *)0xFFFFA117)->bit04)
#define CTPWGA17           (((const volatile __bitf_T *)0xFFFFA117)->bit07)
__IOREG(ICPWGA18, 0xFFFFA11A, __READ_WRITE, uint16);
__IOREG(ICPWGA18L, 0xFFFFA11A, __READ_WRITE, uint8);
__IOREG(ICPWGA18H, 0xFFFFA11B, __READ_WRITE, uint8);
#define P0PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit00)
#define P1PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit01)
#define P2PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit02)
#define TBPWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit06)
#define MKPWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit07)
#define RFPWGA18           (((volatile __bitf_T *)0xFFFFA11B)->bit04)
#define CTPWGA18           (((const volatile __bitf_T *)0xFFFFA11B)->bit07)
__IOREG(ICPWGA19, 0xFFFFA11E, __READ_WRITE, uint16);
__IOREG(ICPWGA19L, 0xFFFFA11E, __READ_WRITE, uint8);
__IOREG(ICPWGA19H, 0xFFFFA11F, __READ_WRITE, uint8);
#define P0PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit00)
#define P1PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit01)
#define P2PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit02)
#define TBPWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit06)
#define MKPWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit07)
#define RFPWGA19           (((volatile __bitf_T *)0xFFFFA11F)->bit04)
#define CTPWGA19           (((const volatile __bitf_T *)0xFFFFA11F)->bit07)
__IOREG(ICRCAN2ERR, 0xFFFFA1A2, __READ_WRITE, uint16);
__IOREG(ICRCAN2ERRL, 0xFFFFA1A2, __READ_WRITE, uint8);
__IOREG(ICRCAN2ERRH, 0xFFFFA1A3, __READ_WRITE, uint8);
#define P0RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit00)
#define P1RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit01)
#define P2RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit02)
#define TBRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit06)
#define MKRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit07)
#define RFRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A3)->bit04)
#define CTRCAN2ERR         (((const volatile __bitf_T *)0xFFFFA1A3)->bit07)
__IOREG(ICRCAN2REC, 0xFFFFA1A4, __READ_WRITE, uint16);
__IOREG(ICRCAN2RECL, 0xFFFFA1A4, __READ_WRITE, uint8);
__IOREG(ICRCAN2RECH, 0xFFFFA1A5, __READ_WRITE, uint8);
#define P0RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit00)
#define P1RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit01)
#define P2RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit02)
#define TBRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit06)
#define MKRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit07)
#define RFRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A5)->bit04)
#define CTRCAN2REC         (((const volatile __bitf_T *)0xFFFFA1A5)->bit07)
__IOREG(ICRCAN2TRX, 0xFFFFA1A6, __READ_WRITE, uint16);
__IOREG(ICRCAN2TRXL, 0xFFFFA1A6, __READ_WRITE, uint8);
__IOREG(ICRCAN2TRXH, 0xFFFFA1A7, __READ_WRITE, uint8);
#define P0RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit00)
#define P1RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit01)
#define P2RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit02)
#define TBRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit06)
#define MKRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit07)
#define RFRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A7)->bit04)
#define CTRCAN2TRX         (((const volatile __bitf_T *)0xFFFFA1A7)->bit07)
__IOREG(IMR1, 0xFFFFA404, __READ_WRITE, uint32);
__IOREG(IMR1L, 0xFFFFA404, __READ_WRITE, uint16);
__IOREG(IMR1LL, 0xFFFFA404, __READ_WRITE, uint8);
__IOREG(IMR1LH, 0xFFFFA405, __READ_WRITE, uint8);
__IOREG(IMR1H, 0xFFFFA406, __READ_WRITE, uint16);
__IOREG(IMR1HL, 0xFFFFA406, __READ_WRITE, uint8);
__IOREG(IMR1HH, 0xFFFFA407, __READ_WRITE, uint8);
#define IMR1EIMK32         (((volatile __bitf_T *)0xFFFFA404)->bit00)
#define IMR1EIMK33         (((volatile __bitf_T *)0xFFFFA404)->bit01)
#define IMR1EIMK34         (((volatile __bitf_T *)0xFFFFA404)->bit02)
#define IMR1EIMK35         (((volatile __bitf_T *)0xFFFFA404)->bit03)
#define IMR1EIMK36         (((volatile __bitf_T *)0xFFFFA404)->bit04)
#define IMR1EIMK37         (((volatile __bitf_T *)0xFFFFA404)->bit05)
#define IMR1EIMK38         (((volatile __bitf_T *)0xFFFFA404)->bit06)
#define IMR1EIMK39         (((volatile __bitf_T *)0xFFFFA404)->bit07)
#define IMR1EIMK40         (((volatile __bitf_T *)0xFFFFA405)->bit00)
#define IMR1EIMK41         (((volatile __bitf_T *)0xFFFFA405)->bit01)
#define IMR1EIMK42         (((volatile __bitf_T *)0xFFFFA405)->bit02)
#define IMR1EIMK43         (((volatile __bitf_T *)0xFFFFA405)->bit03)
#define IMR1EIMK44         (((volatile __bitf_T *)0xFFFFA405)->bit04)
#define IMR1EIMK45         (((volatile __bitf_T *)0xFFFFA405)->bit05)
#define IMR1EIMK46         (((volatile __bitf_T *)0xFFFFA405)->bit06)
#define IMR1EIMK47         (((volatile __bitf_T *)0xFFFFA405)->bit07)
#define IMR1EIMK49         (((volatile __bitf_T *)0xFFFFA406)->bit01)
#define IMR1EIMK50         (((volatile __bitf_T *)0xFFFFA406)->bit02)
#define IMR1EIMK51         (((volatile __bitf_T *)0xFFFFA406)->bit03)
#define IMR1EIMK52         (((volatile __bitf_T *)0xFFFFA406)->bit04)
#define IMR1EIMK53         (((volatile __bitf_T *)0xFFFFA406)->bit05)
#define IMR1EIMK54         (((volatile __bitf_T *)0xFFFFA406)->bit06)
#define IMR1EIMK55         (((volatile __bitf_T *)0xFFFFA406)->bit07)
#define IMR1EIMK56         (((volatile __bitf_T *)0xFFFFA407)->bit00)
#define IMR1EIMK57         (((volatile __bitf_T *)0xFFFFA407)->bit01)
#define IMR1EIMK58         (((volatile __bitf_T *)0xFFFFA407)->bit02)
#define IMR1EIMK59         (((volatile __bitf_T *)0xFFFFA407)->bit03)
#define IMR1EIMK60         (((volatile __bitf_T *)0xFFFFA407)->bit04)
#define IMR1EIMK61         (((volatile __bitf_T *)0xFFFFA407)->bit05)
#define IMR1EIMK62         (((volatile __bitf_T *)0xFFFFA407)->bit06)
#define IMR1EIMK63         (((volatile __bitf_T *)0xFFFFA407)->bit07)
__IOREG(IMR2, 0xFFFFA408, __READ_WRITE, uint32);
__IOREG(IMR2L, 0xFFFFA408, __READ_WRITE, uint16);
__IOREG(IMR2LL, 0xFFFFA408, __READ_WRITE, uint8);
__IOREG(IMR2LH, 0xFFFFA409, __READ_WRITE, uint8);
__IOREG(IMR2H, 0xFFFFA40A, __READ_WRITE, uint16);
__IOREG(IMR2HL, 0xFFFFA40A, __READ_WRITE, uint8);
__IOREG(IMR2HH, 0xFFFFA40B, __READ_WRITE, uint8);
#define IMR2EIMK64         (((volatile __bitf_T *)0xFFFFA408)->bit00)
#define IMR2EIMK65         (((volatile __bitf_T *)0xFFFFA408)->bit01)
#define IMR2EIMK66         (((volatile __bitf_T *)0xFFFFA408)->bit02)
#define IMR2EIMK67         (((volatile __bitf_T *)0xFFFFA408)->bit03)
#define IMR2EIMK68         (((volatile __bitf_T *)0xFFFFA408)->bit04)
#define IMR2EIMK69         (((volatile __bitf_T *)0xFFFFA408)->bit05)
#define IMR2EIMK70         (((volatile __bitf_T *)0xFFFFA408)->bit06)
#define IMR2EIMK71         (((volatile __bitf_T *)0xFFFFA408)->bit07)
#define IMR2EIMK72         (((volatile __bitf_T *)0xFFFFA409)->bit00)
#define IMR2EIMK73         (((volatile __bitf_T *)0xFFFFA409)->bit01)
#define IMR2EIMK74         (((volatile __bitf_T *)0xFFFFA409)->bit02)
#define IMR2EIMK75         (((volatile __bitf_T *)0xFFFFA409)->bit03)
#define IMR2EIMK76         (((volatile __bitf_T *)0xFFFFA409)->bit04)
#define IMR2EIMK77         (((volatile __bitf_T *)0xFFFFA409)->bit05)
#define IMR2EIMK78         (((volatile __bitf_T *)0xFFFFA409)->bit06)
#define IMR2EIMK79         (((volatile __bitf_T *)0xFFFFA409)->bit07)
#define IMR2EIMK80         (((volatile __bitf_T *)0xFFFFA40A)->bit00)
#define IMR2EIMK81         (((volatile __bitf_T *)0xFFFFA40A)->bit01)
#define IMR2EIMK82         (((volatile __bitf_T *)0xFFFFA40A)->bit02)
#define IMR2EIMK83         (((volatile __bitf_T *)0xFFFFA40A)->bit03)
#define IMR2EIMK84         (((volatile __bitf_T *)0xFFFFA40A)->bit04)
#define IMR2EIMK85         (((volatile __bitf_T *)0xFFFFA40A)->bit05)
#define IMR2EIMK86         (((volatile __bitf_T *)0xFFFFA40A)->bit06)
#define IMR2EIMK87         (((volatile __bitf_T *)0xFFFFA40A)->bit07)
#define IMR2EIMK88         (((volatile __bitf_T *)0xFFFFA40B)->bit00)
#define IMR2EIMK89         (((volatile __bitf_T *)0xFFFFA40B)->bit01)
#define IMR2EIMK90         (((volatile __bitf_T *)0xFFFFA40B)->bit02)
#define IMR2EIMK91         (((volatile __bitf_T *)0xFFFFA40B)->bit03)
#define IMR2EIMK92         (((volatile __bitf_T *)0xFFFFA40B)->bit04)
#define IMR2EIMK93         (((volatile __bitf_T *)0xFFFFA40B)->bit05)
#define IMR2EIMK94         (((volatile __bitf_T *)0xFFFFA40B)->bit06)
#define IMR2EIMK95         (((volatile __bitf_T *)0xFFFFA40B)->bit07)
__IOREG(IMR3, 0xFFFFA40C, __READ_WRITE, uint32);
__IOREG(IMR3L, 0xFFFFA40C, __READ_WRITE, uint16);
__IOREG(IMR3LL, 0xFFFFA40C, __READ_WRITE, uint8);
__IOREG(IMR3LH, 0xFFFFA40D, __READ_WRITE, uint8);
__IOREG(IMR3H, 0xFFFFA40E, __READ_WRITE, uint16);
__IOREG(IMR3HL, 0xFFFFA40E, __READ_WRITE, uint8);
#define IMR3EIMK102        (((volatile __bitf_T *)0xFFFFA40C)->bit06)
#define IMR3EIMK103        (((volatile __bitf_T *)0xFFFFA40C)->bit07)
#define IMR3EIMK104        (((volatile __bitf_T *)0xFFFFA40D)->bit00)
#define IMR3EIMK105        (((volatile __bitf_T *)0xFFFFA40D)->bit01)
#define IMR3EIMK106        (((volatile __bitf_T *)0xFFFFA40D)->bit02)
#define IMR3EIMK107        (((volatile __bitf_T *)0xFFFFA40D)->bit03)
#define IMR3EIMK108        (((volatile __bitf_T *)0xFFFFA40D)->bit04)
#define IMR3EIMK109        (((volatile __bitf_T *)0xFFFFA40D)->bit05)
#define IMR3EIMK110        (((volatile __bitf_T *)0xFFFFA40D)->bit06)
#define IMR3EIMK111        (((volatile __bitf_T *)0xFFFFA40D)->bit07)
#define IMR3EIMK112        (((volatile __bitf_T *)0xFFFFA40E)->bit00)
#define IMR3EIMK113        (((volatile __bitf_T *)0xFFFFA40E)->bit01)
#define IMR3EIMK114        (((volatile __bitf_T *)0xFFFFA40E)->bit02)
#define IMR3EIMK115        (((volatile __bitf_T *)0xFFFFA40E)->bit03)
#define IMR3EIMK116        (((volatile __bitf_T *)0xFFFFA40E)->bit04)
#define IMR3EIMK117        (((volatile __bitf_T *)0xFFFFA40E)->bit05)
#define IMR3EIMK118        (((volatile __bitf_T *)0xFFFFA40E)->bit06)
#define IMR3EIMK119        (((volatile __bitf_T *)0xFFFFA40E)->bit07)
__IOREG(IMR4, 0xFFFFA410, __READ_WRITE, uint32);
__IOREG(IMR4L, 0xFFFFA410, __READ_WRITE, uint16);
__IOREG(IMR4LH, 0xFFFFA411, __READ_WRITE, uint8);
#define IMR4EIMK137        (((volatile __bitf_T *)0xFFFFA411)->bit01)
#define IMR4EIMK139        (((volatile __bitf_T *)0xFFFFA411)->bit03)
#define IMR4EIMK141        (((volatile __bitf_T *)0xFFFFA411)->bit05)
#define IMR4EIMK143        (((volatile __bitf_T *)0xFFFFA411)->bit07)
__IOREG(IMR6, 0xFFFFA418, __READ_WRITE, uint32);
__IOREG(IMR6H, 0xFFFFA41A, __READ_WRITE, uint16);
__IOREG(IMR6HL, 0xFFFFA41A, __READ_WRITE, uint8);
#define IMR6EIMK209        (((volatile __bitf_T *)0xFFFFA41A)->bit01)
#define IMR6EIMK210        (((volatile __bitf_T *)0xFFFFA41A)->bit02)
#define IMR6EIMK211        (((volatile __bitf_T *)0xFFFFA41A)->bit03)

__IOREG(SELF, 0xFFA08000, __READ_WRITE, __type22);
__IOREG(FACI, 0xFFA10000, __READ_WRITE, __type23);
__IOREG(PFSS, 0xFFBC0700, __READ_WRITE, __type24);
__IOREG(CCIB, 0xFFC59008, __READ_WRITE, __type25);
__IOREG(RIIC0, 0xFFCA0000, __READ_WRITE, __type26);
__IOREG(SCDS, 0xFFCD00D0, __READ_WRITE, __type27);
__IOREG(RLN240, 0xFFCE0000, __READ_WRITE, __type28);
__IOREG(RLN2400, 0xFFCE0008, __READ_WRITE, __type29);
__IOREG(RLN2401, 0xFFCE0028, __READ_WRITE, __type30);
__IOREG(RLN30, 0xFFCF0000, __READ_WRITE, __type31);
__IOREG(RLN31, 0xFFCF0040, __READ_WRITE, __type31);
__IOREG(RSCAN0, 0xFFD00000, __READ_WRITE, __type32);
__IOREG(CSIH0, 0xFFD80000, __READ_WRITE, __type33);
__IOREG(CSIG0, 0xFFDB0000, __READ_WRITE, __type34);
__IOREG(PIC0, 0xFFDD0004, __READ_WRITE, __type35);
__IOREG(TAUD0, 0xFFE20000, __READ_WRITE, __type36);
__IOREG(TAUJ0, 0xFFE50000, __READ_WRITE, __type37);
__IOREG(PWSA0, 0xFFE70000, __READ_WRITE, __type38);
__IOREG(PWGA0, 0xFFE71000, __READ_WRITE, __type39);
__IOREG(PWGA1, 0xFFE71040, __READ_WRITE, __type39);
__IOREG(PWGA2, 0xFFE71080, __READ_WRITE, __type39);
__IOREG(PWGA3, 0xFFE710C0, __READ_WRITE, __type39);
__IOREG(PWGA4, 0xFFE71100, __READ_WRITE, __type39);
__IOREG(PWGA5, 0xFFE71140, __READ_WRITE, __type39);
__IOREG(PWGA6, 0xFFE71180, __READ_WRITE, __type39);
__IOREG(PWGA7, 0xFFE711C0, __READ_WRITE, __type39);
__IOREG(PWGA8, 0xFFE71200, __READ_WRITE, __type39);
__IOREG(PWGA9, 0xFFE71240, __READ_WRITE, __type39);
__IOREG(PWGA10, 0xFFE71280, __READ_WRITE, __type39);
__IOREG(PWGA11, 0xFFE712C0, __READ_WRITE, __type39);
__IOREG(PWGA12, 0xFFE71300, __READ_WRITE, __type39);
__IOREG(PWGA13, 0xFFE71340, __READ_WRITE, __type39);
__IOREG(PWGA14, 0xFFE71380, __READ_WRITE, __type39);
__IOREG(PWGA15, 0xFFE713C0, __READ_WRITE, __type39);
__IOREG(PWGA16, 0xFFE71400, __READ_WRITE, __type39);
__IOREG(PWGA17, 0xFFE71440, __READ_WRITE, __type39);
__IOREG(PWGA18, 0xFFE71480, __READ_WRITE, __type39);
__IOREG(PWGA19, 0xFFE714C0, __READ_WRITE, __type39);
__IOREG(PWGA20, 0xFFE71500, __READ_WRITE, __type39);
__IOREG(PWGA21, 0xFFE71540, __READ_WRITE, __type39);
__IOREG(PWGA22, 0xFFE71580, __READ_WRITE, __type39);
__IOREG(PWGA23, 0xFFE715C0, __READ_WRITE, __type39);
__IOREG(PWBA0, 0xFFE72800, __READ_WRITE, __type40);
__IOREG(ENCA0, 0xFFE80000, __READ_WRITE, __type41);
__IOREG(TAPA0, 0xFFE90000, __READ_WRITE, __type42);
__IOREG(OSTM0, 0xFFEC0000, __READ_WRITE, __type43);
__IOREG(WDTA0, 0xFFED0000, __READ_WRITE, __type44);
__IOREG(WDTA1, 0xFFED1000, __READ_WRITE, __type44);
__IOREG(ADCA0, 0xFFF20000, __READ_WRITE, __type45);
__IOREG(DCRA0, 0xFFF70000, __READ_WRITE, __type46);
__IOREG(KR0, 0xFFF78000, __READ_WRITE, __type47);
__IOREG(CLMA0, 0xFFF8C000, __READ_WRITE, __type48);
__IOREG(CLMA, 0xFFF8C100, __READ_WRITE, __type49);
__IOREG(CLMA1, 0xFFF8D000, __READ_WRITE, __type48);
__IOREG(CLMA2, 0xFFF8E000, __READ_WRITE, __type48);

__IOREGARRAY(PWGA, 24, 0xFFE71000, __READ_WRITE, __type39);
__IOREGARRAY(WDTA, 2, 0xFFED0000, __READ_WRITE, __type44);
__IOREGARRAY(RLN3, 2, 0xFFCF0000, __READ_WRITE, __type31);

#define SELFID0 SELF.ID0
#define SELFID1 SELF.ID1
#define SELFID2 SELF.ID2
#define SELFID3 SELF.ID3
#define SELFIDST SELF.IDST
#define FACIFPMON FACI.FPMON
#define FACIFASTAT FACI.FASTAT
#define FACIFAEINT FACI.FAEINT
#define FACIFAREASELC FACI.FAREASELC
#define FACIFSADDR FACI.FSADDR
#define FACIFEADDR FACI.FEADDR
#define FACIFCURAME FACI.FCURAME
#define FACIFSTATR FACI.FSTATR
#define FACIFENTRYR FACI.FENTRYR
#define FACIFPROTR FACI.FPROTR
#define FACIFSUINITR FACI.FSUINITR
#define FACIFLKSTAT FACI.FLKSTAT
#define FACIFRFSTEADR FACI.FRFSTEADR
#define FACIFRTSTAT FACI.FRTSTAT
#define FACIFRTEINT FACI.FRTEINT
#define FACIFCMDR FACI.FCMDR
#define FACIFRAMECCR FACI.FRAMECCR
#define FACIFPESTAT FACI.FPESTAT
#define FACIFBCCNT FACI.FBCCNT
#define FACIFBCSTAT FACI.FBCSTAT
#define FACIFPSADDR FACI.FPSADDR
#define FACIFCPSR FACI.FCPSR
#define FACIFPCKAR FACI.FPCKAR
#define FACIFLEMU FACI.FLEMU
#define FACIFLEAD FACI.FLEAD
#define FACIFECCEMON FACI.FECCEMON
#define FACIFECCTMD FACI.FECCTMD
#define FACIFDMYECC FACI.FDMYECC
#define PFSSBWCBUFEN PFSS.BWCBUFEN.UINT8
#define PFSSBWCBUFCLR PFSS.BWCBUFEN.BIT.BWCBUFCLR
#define CCIBFCUFAREA CCIB.FCUFAREA
#define RIIC0CR1 RIIC0.CR1.UINT32
#define RIIC0CR1L RIIC0.CR1.UINT16[L]
#define RIIC0CR1LL RIIC0.CR1.UINT8[LL]
#define RIIC0CR1LH RIIC0.CR1.UINT8[LH]
#define RIIC0CR1H RIIC0.CR1.UINT16[H]
#define RIIC0CR1HL RIIC0.CR1.UINT8[HL]
#define RIIC0CR1HH RIIC0.CR1.UINT8[HH]
#define RIIC0CR2 RIIC0.CR2.UINT32
#define RIIC0CR2L RIIC0.CR2.UINT16[L]
#define RIIC0CR2LL RIIC0.CR2.UINT8[LL]
#define RIIC0CR2LH RIIC0.CR2.UINT8[LH]
#define RIIC0CR2H RIIC0.CR2.UINT16[H]
#define RIIC0CR2HL RIIC0.CR2.UINT8[HL]
#define RIIC0CR2HH RIIC0.CR2.UINT8[HH]
#define RIIC0MR1 RIIC0.MR1.UINT32
#define RIIC0MR1L RIIC0.MR1.UINT16[L]
#define RIIC0MR1LL RIIC0.MR1.UINT8[LL]
#define RIIC0MR1LH RIIC0.MR1.UINT8[LH]
#define RIIC0MR1H RIIC0.MR1.UINT16[H]
#define RIIC0MR1HL RIIC0.MR1.UINT8[HL]
#define RIIC0MR1HH RIIC0.MR1.UINT8[HH]
#define RIIC0MR2 RIIC0.MR2.UINT32
#define RIIC0MR2L RIIC0.MR2.UINT16[L]
#define RIIC0MR2LL RIIC0.MR2.UINT8[LL]
#define RIIC0MR2LH RIIC0.MR2.UINT8[LH]
#define RIIC0MR2H RIIC0.MR2.UINT16[H]
#define RIIC0MR2HL RIIC0.MR2.UINT8[HL]
#define RIIC0MR2HH RIIC0.MR2.UINT8[HH]
#define RIIC0MR3 RIIC0.MR3.UINT32
#define RIIC0MR3L RIIC0.MR3.UINT16[L]
#define RIIC0MR3LL RIIC0.MR3.UINT8[LL]
#define RIIC0MR3LH RIIC0.MR3.UINT8[LH]
#define RIIC0MR3H RIIC0.MR3.UINT16[H]
#define RIIC0MR3HL RIIC0.MR3.UINT8[HL]
#define RIIC0MR3HH RIIC0.MR3.UINT8[HH]
#define RIIC0FER RIIC0.FER.UINT32
#define RIIC0FERL RIIC0.FER.UINT16[L]
#define RIIC0FERLL RIIC0.FER.UINT8[LL]
#define RIIC0FERLH RIIC0.FER.UINT8[LH]
#define RIIC0FERH RIIC0.FER.UINT16[H]
#define RIIC0FERHL RIIC0.FER.UINT8[HL]
#define RIIC0FERHH RIIC0.FER.UINT8[HH]
#define RIIC0SER RIIC0.SER.UINT32
#define RIIC0SERL RIIC0.SER.UINT16[L]
#define RIIC0SERLL RIIC0.SER.UINT8[LL]
#define RIIC0SERLH RIIC0.SER.UINT8[LH]
#define RIIC0SERH RIIC0.SER.UINT16[H]
#define RIIC0SERHL RIIC0.SER.UINT8[HL]
#define RIIC0SERHH RIIC0.SER.UINT8[HH]
#define RIIC0IER RIIC0.IER.UINT32
#define RIIC0IERL RIIC0.IER.UINT16[L]
#define RIIC0IERLL RIIC0.IER.UINT8[LL]
#define RIIC0IERLH RIIC0.IER.UINT8[LH]
#define RIIC0IERH RIIC0.IER.UINT16[H]
#define RIIC0IERHL RIIC0.IER.UINT8[HL]
#define RIIC0IERHH RIIC0.IER.UINT8[HH]
#define RIIC0SR1 RIIC0.SR1.UINT32
#define RIIC0SR1L RIIC0.SR1.UINT16[L]
#define RIIC0SR1LL RIIC0.SR1.UINT8[LL]
#define RIIC0SR1LH RIIC0.SR1.UINT8[LH]
#define RIIC0SR1H RIIC0.SR1.UINT16[H]
#define RIIC0SR1HL RIIC0.SR1.UINT8[HL]
#define RIIC0SR1HH RIIC0.SR1.UINT8[HH]
#define RIIC0AAS0 RIIC0.SR1.BIT.AAS0
#define RIIC0AAS1 RIIC0.SR1.BIT.AAS1
#define RIIC0AAS2 RIIC0.SR1.BIT.AAS2
#define RIIC0GCA RIIC0.SR1.BIT.GCA
#define RIIC0DID RIIC0.SR1.BIT.DID
#define RIIC0SR2 RIIC0.SR2.UINT32
#define RIIC0SR2L RIIC0.SR2.UINT16[L]
#define RIIC0SR2LL RIIC0.SR2.UINT8[LL]
#define RIIC0SR2LH RIIC0.SR2.UINT8[LH]
#define RIIC0SR2H RIIC0.SR2.UINT16[H]
#define RIIC0SR2HL RIIC0.SR2.UINT8[HL]
#define RIIC0SR2HH RIIC0.SR2.UINT8[HH]
#define RIIC0TMOF RIIC0.SR2.BIT.TMOF
#define RIIC0AL RIIC0.SR2.BIT.AL
#define RIIC0START RIIC0.SR2.BIT.START
#define RIIC0STOP RIIC0.SR2.BIT.STOP
#define RIIC0NACKF RIIC0.SR2.BIT.NACKF
#define RIIC0RDRF RIIC0.SR2.BIT.RDRF
#define RIIC0TEND RIIC0.SR2.BIT.TEND
#define RIIC0TDRE RIIC0.SR2.BIT.TDRE
#define RIIC0SAR0 RIIC0.SAR0.UINT32
#define RIIC0SAR0L RIIC0.SAR0.UINT16[L]
#define RIIC0SAR0LL RIIC0.SAR0.UINT8[LL]
#define RIIC0SAR0LH RIIC0.SAR0.UINT8[LH]
#define RIIC0SAR0H RIIC0.SAR0.UINT16[H]
#define RIIC0SAR0HL RIIC0.SAR0.UINT8[HL]
#define RIIC0SAR0HH RIIC0.SAR0.UINT8[HH]
#define RIIC0SAR1 RIIC0.SAR1.UINT32
#define RIIC0SAR1L RIIC0.SAR1.UINT16[L]
#define RIIC0SAR1LL RIIC0.SAR1.UINT8[LL]
#define RIIC0SAR1LH RIIC0.SAR1.UINT8[LH]
#define RIIC0SAR1H RIIC0.SAR1.UINT16[H]
#define RIIC0SAR1HL RIIC0.SAR1.UINT8[HL]
#define RIIC0SAR1HH RIIC0.SAR1.UINT8[HH]
#define RIIC0SAR2 RIIC0.SAR2.UINT32
#define RIIC0SAR2L RIIC0.SAR2.UINT16[L]
#define RIIC0SAR2LL RIIC0.SAR2.UINT8[LL]
#define RIIC0SAR2LH RIIC0.SAR2.UINT8[LH]
#define RIIC0SAR2H RIIC0.SAR2.UINT16[H]
#define RIIC0SAR2HL RIIC0.SAR2.UINT8[HL]
#define RIIC0SAR2HH RIIC0.SAR2.UINT8[HH]
#define RIIC0BRL RIIC0.BRL.UINT32
#define RIIC0BRLL RIIC0.BRL.UINT16[L]
#define RIIC0BRLLL RIIC0.BRL.UINT8[LL]
#define RIIC0BRLLH RIIC0.BRL.UINT8[LH]
#define RIIC0BRLH RIIC0.BRL.UINT16[H]
#define RIIC0BRLHL RIIC0.BRL.UINT8[HL]
#define RIIC0BRLHH RIIC0.BRL.UINT8[HH]
#define RIIC0BRH RIIC0.BRH.UINT32
#define RIIC0BRHL RIIC0.BRH.UINT16[L]
#define RIIC0BRHLL RIIC0.BRH.UINT8[LL]
#define RIIC0BRHLH RIIC0.BRH.UINT8[LH]
#define RIIC0BRHH RIIC0.BRH.UINT16[H]
#define RIIC0BRHHL RIIC0.BRH.UINT8[HL]
#define RIIC0BRHHH RIIC0.BRH.UINT8[HH]
#define RIIC0DRT RIIC0.DRT.UINT32
#define RIIC0DRTL RIIC0.DRT.UINT16[L]
#define RIIC0DRTLL RIIC0.DRT.UINT8[LL]
#define RIIC0DRTLH RIIC0.DRT.UINT8[LH]
#define RIIC0DRTH RIIC0.DRT.UINT16[H]
#define RIIC0DRTHL RIIC0.DRT.UINT8[HL]
#define RIIC0DRTHH RIIC0.DRT.UINT8[HH]
#define RIIC0DRR RIIC0.DRR.UINT32
#define RIIC0DRRL RIIC0.DRR.UINT16[L]
#define RIIC0DRRLL RIIC0.DRR.UINT8[LL]
#define RIIC0DRRLH RIIC0.DRR.UINT8[LH]
#define RIIC0DRRH RIIC0.DRR.UINT16[H]
#define RIIC0DRRHL RIIC0.DRR.UINT8[HL]
#define RIIC0DRRHH RIIC0.DRR.UINT8[HH]
#define SCDSPRDNAME1 SCDS.PRDNAME1
#define SCDSPRDNAME2 SCDS.PRDNAME2
#define SCDSPRDNAME3 SCDS.PRDNAME3
#define RLN240GLWBR RLN240.GLWBR
#define RLN240GLBRP0 RLN240.GLBRP0
#define RLN240GLBRP1 RLN240.GLBRP1
#define RLN240GLSTC RLN240.GLSTC
#define RLN2400L0MD RLN2400.L0MD
#define RLN2400L0BFC RLN2400.L0BFC
#define RLN2400L0SC RLN2400.L0SC
#define RLN2400L0WUP RLN2400.L0WUP
#define RLN2400L0IE RLN2400.L0IE
#define RLN2400L0EDE RLN2400.L0EDE
#define RLN2400L0CUC RLN2400.L0CUC
#define RLN2400L0TRC RLN2400.L0TRC
#define RLN2400L0MST RLN2400.L0MST
#define RLN2400L0ST RLN2400.L0ST
#define RLN2400L0EST RLN2400.L0EST
#define RLN2400L0DFC RLN2400.L0DFC
#define RLN2400L0IDB RLN2400.L0IDB
#define RLN2400L0CBR RLN2400.L0CBR
#define RLN2400L0DBR1 RLN2400.L0DBR1
#define RLN2400L0DBR2 RLN2400.L0DBR2
#define RLN2400L0DBR3 RLN2400.L0DBR3
#define RLN2400L0DBR4 RLN2400.L0DBR4
#define RLN2400L0DBR5 RLN2400.L0DBR5
#define RLN2400L0DBR6 RLN2400.L0DBR6
#define RLN2400L0DBR7 RLN2400.L0DBR7
#define RLN2400L0DBR8 RLN2400.L0DBR8
#define RLN2401L1MD RLN2401.L1MD
#define RLN2401L1BFC RLN2401.L1BFC
#define RLN2401L1SC RLN2401.L1SC
#define RLN2401L1WUP RLN2401.L1WUP
#define RLN2401L1IE RLN2401.L1IE
#define RLN2401L1EDE RLN2401.L1EDE
#define RLN2401L1CUC RLN2401.L1CUC
#define RLN2401L1TRC RLN2401.L1TRC
#define RLN2401L1MST RLN2401.L1MST
#define RLN2401L1ST RLN2401.L1ST
#define RLN2401L1EST RLN2401.L1EST
#define RLN2401L1DFC RLN2401.L1DFC
#define RLN2401L1IDB RLN2401.L1IDB
#define RLN2401L1CBR RLN2401.L1CBR
#define RLN2401L1DBR1 RLN2401.L1DBR1
#define RLN2401L1DBR2 RLN2401.L1DBR2
#define RLN2401L1DBR3 RLN2401.L1DBR3
#define RLN2401L1DBR4 RLN2401.L1DBR4
#define RLN2401L1DBR5 RLN2401.L1DBR5
#define RLN2401L1DBR6 RLN2401.L1DBR6
#define RLN2401L1DBR7 RLN2401.L1DBR7
#define RLN2401L1DBR8 RLN2401.L1DBR8
#define RLN30LWBR RLN30.LWBR
#define RLN30LBRP01 RLN30.LBRP01.UINT16
#define RLN30LBRP0 RLN30.LBRP01.UINT8[L]
#define RLN30LBRP1 RLN30.LBRP01.UINT8[H]
#define RLN30LSTC RLN30.LSTC
#define RLN30LMD RLN30.LMD
#define RLN30LBFC RLN30.LBFC
#define RLN30LSC RLN30.LSC
#define RLN30LWUP RLN30.LWUP
#define RLN30LIE RLN30.LIE
#define RLN30LEDE RLN30.LEDE
#define RLN30LCUC RLN30.LCUC
#define RLN30LTRC RLN30.LTRC
#define RLN30LMST RLN30.LMST
#define RLN30LST RLN30.LST
#define RLN30LEST RLN30.LEST
#define RLN30LDFC RLN30.LDFC
#define RLN30LIDB RLN30.LIDB
#define RLN30LCBR RLN30.LCBR
#define RLN30LUDB0 RLN30.LUDB0
#define RLN30LDBR1 RLN30.LDBR1
#define RLN30LDBR2 RLN30.LDBR2
#define RLN30LDBR3 RLN30.LDBR3
#define RLN30LDBR4 RLN30.LDBR4
#define RLN30LDBR5 RLN30.LDBR5
#define RLN30LDBR6 RLN30.LDBR6
#define RLN30LDBR7 RLN30.LDBR7
#define RLN30LDBR8 RLN30.LDBR8
#define RLN30LUOER RLN30.LUOER
#define RLN30LUOR1 RLN30.LUOR1
#define RLN30LUTDR RLN30.LUTDR.UINT16
#define RLN30LUTDRL RLN30.LUTDR.UINT8[L]
#define RLN30LUTDRH RLN30.LUTDR.UINT8[H]
#define RLN30LURDR RLN30.LURDR.UINT16
#define RLN30LURDRL RLN30.LURDR.UINT8[L]
#define RLN30LURDRH RLN30.LURDR.UINT8[H]
#define RLN30LUWTDR RLN30.LUWTDR.UINT16
#define RLN30LUWTDRL RLN30.LUWTDR.UINT8[L]
#define RLN30LUWTDRH RLN30.LUWTDR.UINT8[H]
#define RLN31LWBR RLN31.LWBR
#define RLN31LBRP01 RLN31.LBRP01.UINT16
#define RLN31LBRP0 RLN31.LBRP01.UINT8[L]
#define RLN31LBRP1 RLN31.LBRP01.UINT8[H]
#define RLN31LSTC RLN31.LSTC
#define RLN31LMD RLN31.LMD
#define RLN31LBFC RLN31.LBFC
#define RLN31LSC RLN31.LSC
#define RLN31LWUP RLN31.LWUP
#define RLN31LIE RLN31.LIE
#define RLN31LEDE RLN31.LEDE
#define RLN31LCUC RLN31.LCUC
#define RLN31LTRC RLN31.LTRC
#define RLN31LMST RLN31.LMST
#define RLN31LST RLN31.LST
#define RLN31LEST RLN31.LEST
#define RLN31LDFC RLN31.LDFC
#define RLN31LIDB RLN31.LIDB
#define RLN31LCBR RLN31.LCBR
#define RLN31LUDB0 RLN31.LUDB0
#define RLN31LDBR1 RLN31.LDBR1
#define RLN31LDBR2 RLN31.LDBR2
#define RLN31LDBR3 RLN31.LDBR3
#define RLN31LDBR4 RLN31.LDBR4
#define RLN31LDBR5 RLN31.LDBR5
#define RLN31LDBR6 RLN31.LDBR6
#define RLN31LDBR7 RLN31.LDBR7
#define RLN31LDBR8 RLN31.LDBR8
#define RLN31LUOER RLN31.LUOER
#define RLN31LUOR1 RLN31.LUOR1
#define RLN31LUTDR RLN31.LUTDR.UINT16
#define RLN31LUTDRL RLN31.LUTDR.UINT8[L]
#define RLN31LUTDRH RLN31.LUTDR.UINT8[H]
#define RLN31LURDR RLN31.LURDR.UINT16
#define RLN31LURDRL RLN31.LURDR.UINT8[L]
#define RLN31LURDRH RLN31.LURDR.UINT8[H]
#define RLN31LUWTDR RLN31.LUWTDR.UINT16
#define RLN31LUWTDRL RLN31.LUWTDR.UINT8[L]
#define RLN31LUWTDRH RLN31.LUWTDR.UINT8[H]
#define RSCAN0C0CFG RSCAN0.C0CFG.UINT32
#define RSCAN0C0CFGL RSCAN0.C0CFG.UINT16[L]
#define RSCAN0C0CFGLL RSCAN0.C0CFG.UINT8[LL]
#define RSCAN0C0CFGLH RSCAN0.C0CFG.UINT8[LH]
#define RSCAN0C0CFGH RSCAN0.C0CFG.UINT16[H]
#define RSCAN0C0CFGHL RSCAN0.C0CFG.UINT8[HL]
#define RSCAN0C0CFGHH RSCAN0.C0CFG.UINT8[HH]
#define RSCAN0C0CTR RSCAN0.C0CTR.UINT32
#define RSCAN0C0CTRL RSCAN0.C0CTR.UINT16[L]
#define RSCAN0C0CTRLL RSCAN0.C0CTR.UINT8[LL]
#define RSCAN0C0CTRLH RSCAN0.C0CTR.UINT8[LH]
#define RSCAN0C0CTRH RSCAN0.C0CTR.UINT16[H]
#define RSCAN0C0CTRHL RSCAN0.C0CTR.UINT8[HL]
#define RSCAN0C0CTRHH RSCAN0.C0CTR.UINT8[HH]
#define RSCAN0C0STS RSCAN0.C0STS.UINT32
#define RSCAN0C0STSL RSCAN0.C0STS.UINT16[L]
#define RSCAN0C0STSLL RSCAN0.C0STS.UINT8[LL]
#define RSCAN0C0STSLH RSCAN0.C0STS.UINT8[LH]
#define RSCAN0C0STSH RSCAN0.C0STS.UINT16[H]
#define RSCAN0C0STSHL RSCAN0.C0STS.UINT8[HL]
#define RSCAN0C0STSHH RSCAN0.C0STS.UINT8[HH]
#define RSCAN0C0ERFL RSCAN0.C0ERFL.UINT32
#define RSCAN0C0ERFLL RSCAN0.C0ERFL.UINT16[L]
#define RSCAN0C0ERFLLL RSCAN0.C0ERFL.UINT8[LL]
#define RSCAN0C0ERFLLH RSCAN0.C0ERFL.UINT8[LH]
#define RSCAN0C0ERFLH RSCAN0.C0ERFL.UINT16[H]
#define RSCAN0C0ERFLHL RSCAN0.C0ERFL.UINT8[HL]
#define RSCAN0C0ERFLHH RSCAN0.C0ERFL.UINT8[HH]
#define RSCAN0C1CFG RSCAN0.C1CFG.UINT32
#define RSCAN0C1CFGL RSCAN0.C1CFG.UINT16[L]
#define RSCAN0C1CFGLL RSCAN0.C1CFG.UINT8[LL]
#define RSCAN0C1CFGLH RSCAN0.C1CFG.UINT8[LH]
#define RSCAN0C1CFGH RSCAN0.C1CFG.UINT16[H]
#define RSCAN0C1CFGHL RSCAN0.C1CFG.UINT8[HL]
#define RSCAN0C1CFGHH RSCAN0.C1CFG.UINT8[HH]
#define RSCAN0C1CTR RSCAN0.C1CTR.UINT32
#define RSCAN0C1CTRL RSCAN0.C1CTR.UINT16[L]
#define RSCAN0C1CTRLL RSCAN0.C1CTR.UINT8[LL]
#define RSCAN0C1CTRLH RSCAN0.C1CTR.UINT8[LH]
#define RSCAN0C1CTRH RSCAN0.C1CTR.UINT16[H]
#define RSCAN0C1CTRHL RSCAN0.C1CTR.UINT8[HL]
#define RSCAN0C1CTRHH RSCAN0.C1CTR.UINT8[HH]
#define RSCAN0C1STS RSCAN0.C1STS.UINT32
#define RSCAN0C1STSL RSCAN0.C1STS.UINT16[L]
#define RSCAN0C1STSLL RSCAN0.C1STS.UINT8[LL]
#define RSCAN0C1STSLH RSCAN0.C1STS.UINT8[LH]
#define RSCAN0C1STSH RSCAN0.C1STS.UINT16[H]
#define RSCAN0C1STSHL RSCAN0.C1STS.UINT8[HL]
#define RSCAN0C1STSHH RSCAN0.C1STS.UINT8[HH]
#define RSCAN0C1ERFL RSCAN0.C1ERFL.UINT32
#define RSCAN0C1ERFLL RSCAN0.C1ERFL.UINT16[L]
#define RSCAN0C1ERFLLL RSCAN0.C1ERFL.UINT8[LL]
#define RSCAN0C1ERFLLH RSCAN0.C1ERFL.UINT8[LH]
#define RSCAN0C1ERFLH RSCAN0.C1ERFL.UINT16[H]
#define RSCAN0C1ERFLHL RSCAN0.C1ERFL.UINT8[HL]
#define RSCAN0C1ERFLHH RSCAN0.C1ERFL.UINT8[HH]
#define RSCAN0C2CFG RSCAN0.C2CFG.UINT32
#define RSCAN0C2CFGL RSCAN0.C2CFG.UINT16[L]
#define RSCAN0C2CFGLL RSCAN0.C2CFG.UINT8[LL]
#define RSCAN0C2CFGLH RSCAN0.C2CFG.UINT8[LH]
#define RSCAN0C2CFGH RSCAN0.C2CFG.UINT16[H]
#define RSCAN0C2CFGHL RSCAN0.C2CFG.UINT8[HL]
#define RSCAN0C2CFGHH RSCAN0.C2CFG.UINT8[HH]
#define RSCAN0C2CTR RSCAN0.C2CTR.UINT32
#define RSCAN0C2CTRL RSCAN0.C2CTR.UINT16[L]
#define RSCAN0C2CTRLL RSCAN0.C2CTR.UINT8[LL]
#define RSCAN0C2CTRLH RSCAN0.C2CTR.UINT8[LH]
#define RSCAN0C2CTRH RSCAN0.C2CTR.UINT16[H]
#define RSCAN0C2CTRHL RSCAN0.C2CTR.UINT8[HL]
#define RSCAN0C2CTRHH RSCAN0.C2CTR.UINT8[HH]
#define RSCAN0C2STS RSCAN0.C2STS.UINT32
#define RSCAN0C2STSL RSCAN0.C2STS.UINT16[L]
#define RSCAN0C2STSLL RSCAN0.C2STS.UINT8[LL]
#define RSCAN0C2STSLH RSCAN0.C2STS.UINT8[LH]
#define RSCAN0C2STSH RSCAN0.C2STS.UINT16[H]
#define RSCAN0C2STSHL RSCAN0.C2STS.UINT8[HL]
#define RSCAN0C2STSHH RSCAN0.C2STS.UINT8[HH]
#define RSCAN0C2ERFL RSCAN0.C2ERFL.UINT32
#define RSCAN0C2ERFLL RSCAN0.C2ERFL.UINT16[L]
#define RSCAN0C2ERFLLL RSCAN0.C2ERFL.UINT8[LL]
#define RSCAN0C2ERFLLH RSCAN0.C2ERFL.UINT8[LH]
#define RSCAN0C2ERFLH RSCAN0.C2ERFL.UINT16[H]
#define RSCAN0C2ERFLHL RSCAN0.C2ERFL.UINT8[HL]
#define RSCAN0C2ERFLHH RSCAN0.C2ERFL.UINT8[HH]
#define RSCAN0GCFG RSCAN0.GCFG.UINT32
#define RSCAN0GCFGL RSCAN0.GCFG.UINT16[L]
#define RSCAN0GCFGLL RSCAN0.GCFG.UINT8[LL]
#define RSCAN0GCFGLH RSCAN0.GCFG.UINT8[LH]
#define RSCAN0GCFGH RSCAN0.GCFG.UINT16[H]
#define RSCAN0GCFGHL RSCAN0.GCFG.UINT8[HL]
#define RSCAN0GCFGHH RSCAN0.GCFG.UINT8[HH]
#define RSCAN0GCTR RSCAN0.GCTR.UINT32
#define RSCAN0GCTRL RSCAN0.GCTR.UINT16[L]
#define RSCAN0GCTRLL RSCAN0.GCTR.UINT8[LL]
#define RSCAN0GCTRLH RSCAN0.GCTR.UINT8[LH]
#define RSCAN0GCTRH RSCAN0.GCTR.UINT16[H]
#define RSCAN0GCTRHL RSCAN0.GCTR.UINT8[HL]
#define RSCAN0GCTRHH RSCAN0.GCTR.UINT8[HH]
#define RSCAN0GSTS RSCAN0.GSTS.UINT32
#define RSCAN0GSTSL RSCAN0.GSTS.UINT16[L]
#define RSCAN0GSTSLL RSCAN0.GSTS.UINT8[LL]
#define RSCAN0GSTSLH RSCAN0.GSTS.UINT8[LH]
#define RSCAN0GSTSH RSCAN0.GSTS.UINT16[H]
#define RSCAN0GSTSHL RSCAN0.GSTS.UINT8[HL]
#define RSCAN0GSTSHH RSCAN0.GSTS.UINT8[HH]
#define RSCAN0GERFL RSCAN0.GERFL.UINT32
#define RSCAN0GERFLL RSCAN0.GERFL.UINT16[L]
#define RSCAN0GERFLLL RSCAN0.GERFL.UINT8[LL]
#define RSCAN0GERFLLH RSCAN0.GERFL.UINT8[LH]
#define RSCAN0GERFLH RSCAN0.GERFL.UINT16[H]
#define RSCAN0GERFLHL RSCAN0.GERFL.UINT8[HL]
#define RSCAN0GERFLHH RSCAN0.GERFL.UINT8[HH]
#define RSCAN0GTSC RSCAN0.GTSC.UINT32
#define RSCAN0GTSCL RSCAN0.GTSC.UINT16[L]
#define RSCAN0GTSCH RSCAN0.GTSC.UINT16[H]
#define RSCAN0GAFLECTR RSCAN0.GAFLECTR.UINT32
#define RSCAN0GAFLECTRL RSCAN0.GAFLECTR.UINT16[L]
#define RSCAN0GAFLECTRLL RSCAN0.GAFLECTR.UINT8[LL]
#define RSCAN0GAFLECTRLH RSCAN0.GAFLECTR.UINT8[LH]
#define RSCAN0GAFLECTRH RSCAN0.GAFLECTR.UINT16[H]
#define RSCAN0GAFLECTRHL RSCAN0.GAFLECTR.UINT8[HL]
#define RSCAN0GAFLECTRHH RSCAN0.GAFLECTR.UINT8[HH]
#define RSCAN0GAFLCFG0 RSCAN0.GAFLCFG0.UINT32
#define RSCAN0GAFLCFG0L RSCAN0.GAFLCFG0.UINT16[L]
#define RSCAN0GAFLCFG0LH RSCAN0.GAFLCFG0.UINT8[LH]
#define RSCAN0GAFLCFG0H RSCAN0.GAFLCFG0.UINT16[H]
#define RSCAN0GAFLCFG0HL RSCAN0.GAFLCFG0.UINT8[HL]
#define RSCAN0GAFLCFG0HH RSCAN0.GAFLCFG0.UINT8[HH]
#define RSCAN0RMNB RSCAN0.RMNB.UINT32
#define RSCAN0RMNBL RSCAN0.RMNB.UINT16[L]
#define RSCAN0RMNBLL RSCAN0.RMNB.UINT8[LL]
#define RSCAN0RMNBLH RSCAN0.RMNB.UINT8[LH]
#define RSCAN0RMNBH RSCAN0.RMNB.UINT16[H]
#define RSCAN0RMNBHL RSCAN0.RMNB.UINT8[HL]
#define RSCAN0RMNBHH RSCAN0.RMNB.UINT8[HH]
#define RSCAN0RMND0 RSCAN0.RMND0.UINT32
#define RSCAN0RMND0L RSCAN0.RMND0.UINT16[L]
#define RSCAN0RMND0LL RSCAN0.RMND0.UINT8[LL]
#define RSCAN0RMND0LH RSCAN0.RMND0.UINT8[LH]
#define RSCAN0RMND0H RSCAN0.RMND0.UINT16[H]
#define RSCAN0RMND0HL RSCAN0.RMND0.UINT8[HL]
#define RSCAN0RMND0HH RSCAN0.RMND0.UINT8[HH]
#define RSCAN0RMND1 RSCAN0.RMND1.UINT32
#define RSCAN0RMND1L RSCAN0.RMND1.UINT16[L]
#define RSCAN0RMND1LL RSCAN0.RMND1.UINT8[LL]
#define RSCAN0RMND1LH RSCAN0.RMND1.UINT8[LH]
#define RSCAN0RFCC0 RSCAN0.RFCC0.UINT32
#define RSCAN0RFCC0L RSCAN0.RFCC0.UINT16[L]
#define RSCAN0RFCC0LL RSCAN0.RFCC0.UINT8[LL]
#define RSCAN0RFCC0LH RSCAN0.RFCC0.UINT8[LH]
#define RSCAN0RFCC0H RSCAN0.RFCC0.UINT16[H]
#define RSCAN0RFCC0HL RSCAN0.RFCC0.UINT8[HL]
#define RSCAN0RFCC0HH RSCAN0.RFCC0.UINT8[HH]
#define RSCAN0RFCC1 RSCAN0.RFCC1.UINT32
#define RSCAN0RFCC1L RSCAN0.RFCC1.UINT16[L]
#define RSCAN0RFCC1LL RSCAN0.RFCC1.UINT8[LL]
#define RSCAN0RFCC1LH RSCAN0.RFCC1.UINT8[LH]
#define RSCAN0RFCC1H RSCAN0.RFCC1.UINT16[H]
#define RSCAN0RFCC1HL RSCAN0.RFCC1.UINT8[HL]
#define RSCAN0RFCC1HH RSCAN0.RFCC1.UINT8[HH]
#define RSCAN0RFCC2 RSCAN0.RFCC2.UINT32
#define RSCAN0RFCC2L RSCAN0.RFCC2.UINT16[L]
#define RSCAN0RFCC2LL RSCAN0.RFCC2.UINT8[LL]
#define RSCAN0RFCC2LH RSCAN0.RFCC2.UINT8[LH]
#define RSCAN0RFCC2H RSCAN0.RFCC2.UINT16[H]
#define RSCAN0RFCC2HL RSCAN0.RFCC2.UINT8[HL]
#define RSCAN0RFCC2HH RSCAN0.RFCC2.UINT8[HH]
#define RSCAN0RFCC3 RSCAN0.RFCC3.UINT32
#define RSCAN0RFCC3L RSCAN0.RFCC3.UINT16[L]
#define RSCAN0RFCC3LL RSCAN0.RFCC3.UINT8[LL]
#define RSCAN0RFCC3LH RSCAN0.RFCC3.UINT8[LH]
#define RSCAN0RFCC3H RSCAN0.RFCC3.UINT16[H]
#define RSCAN0RFCC3HL RSCAN0.RFCC3.UINT8[HL]
#define RSCAN0RFCC3HH RSCAN0.RFCC3.UINT8[HH]
#define RSCAN0RFCC4 RSCAN0.RFCC4.UINT32
#define RSCAN0RFCC4L RSCAN0.RFCC4.UINT16[L]
#define RSCAN0RFCC4LL RSCAN0.RFCC4.UINT8[LL]
#define RSCAN0RFCC4LH RSCAN0.RFCC4.UINT8[LH]
#define RSCAN0RFCC4H RSCAN0.RFCC4.UINT16[H]
#define RSCAN0RFCC4HL RSCAN0.RFCC4.UINT8[HL]
#define RSCAN0RFCC4HH RSCAN0.RFCC4.UINT8[HH]
#define RSCAN0RFCC5 RSCAN0.RFCC5.UINT32
#define RSCAN0RFCC5L RSCAN0.RFCC5.UINT16[L]
#define RSCAN0RFCC5LL RSCAN0.RFCC5.UINT8[LL]
#define RSCAN0RFCC5LH RSCAN0.RFCC5.UINT8[LH]
#define RSCAN0RFCC5H RSCAN0.RFCC5.UINT16[H]
#define RSCAN0RFCC5HL RSCAN0.RFCC5.UINT8[HL]
#define RSCAN0RFCC5HH RSCAN0.RFCC5.UINT8[HH]
#define RSCAN0RFCC6 RSCAN0.RFCC6.UINT32
#define RSCAN0RFCC6L RSCAN0.RFCC6.UINT16[L]
#define RSCAN0RFCC6LL RSCAN0.RFCC6.UINT8[LL]
#define RSCAN0RFCC6LH RSCAN0.RFCC6.UINT8[LH]
#define RSCAN0RFCC6H RSCAN0.RFCC6.UINT16[H]
#define RSCAN0RFCC6HL RSCAN0.RFCC6.UINT8[HL]
#define RSCAN0RFCC6HH RSCAN0.RFCC6.UINT8[HH]
#define RSCAN0RFCC7 RSCAN0.RFCC7.UINT32
#define RSCAN0RFCC7L RSCAN0.RFCC7.UINT16[L]
#define RSCAN0RFCC7LL RSCAN0.RFCC7.UINT8[LL]
#define RSCAN0RFCC7LH RSCAN0.RFCC7.UINT8[LH]
#define RSCAN0RFCC7H RSCAN0.RFCC7.UINT16[H]
#define RSCAN0RFCC7HL RSCAN0.RFCC7.UINT8[HL]
#define RSCAN0RFCC7HH RSCAN0.RFCC7.UINT8[HH]
#define RSCAN0RFSTS0 RSCAN0.RFSTS0.UINT32
#define RSCAN0RFSTS0L RSCAN0.RFSTS0.UINT16[L]
#define RSCAN0RFSTS0LL RSCAN0.RFSTS0.UINT8[LL]
#define RSCAN0RFSTS0LH RSCAN0.RFSTS0.UINT8[LH]
#define RSCAN0RFSTS0H RSCAN0.RFSTS0.UINT16[H]
#define RSCAN0RFSTS0HL RSCAN0.RFSTS0.UINT8[HL]
#define RSCAN0RFSTS0HH RSCAN0.RFSTS0.UINT8[HH]
#define RSCAN0RFSTS1 RSCAN0.RFSTS1.UINT32
#define RSCAN0RFSTS1L RSCAN0.RFSTS1.UINT16[L]
#define RSCAN0RFSTS1LL RSCAN0.RFSTS1.UINT8[LL]
#define RSCAN0RFSTS1LH RSCAN0.RFSTS1.UINT8[LH]
#define RSCAN0RFSTS1H RSCAN0.RFSTS1.UINT16[H]
#define RSCAN0RFSTS1HL RSCAN0.RFSTS1.UINT8[HL]
#define RSCAN0RFSTS1HH RSCAN0.RFSTS1.UINT8[HH]
#define RSCAN0RFSTS2 RSCAN0.RFSTS2.UINT32
#define RSCAN0RFSTS2L RSCAN0.RFSTS2.UINT16[L]
#define RSCAN0RFSTS2LL RSCAN0.RFSTS2.UINT8[LL]
#define RSCAN0RFSTS2LH RSCAN0.RFSTS2.UINT8[LH]
#define RSCAN0RFSTS2H RSCAN0.RFSTS2.UINT16[H]
#define RSCAN0RFSTS2HL RSCAN0.RFSTS2.UINT8[HL]
#define RSCAN0RFSTS2HH RSCAN0.RFSTS2.UINT8[HH]
#define RSCAN0RFSTS3 RSCAN0.RFSTS3.UINT32
#define RSCAN0RFSTS3L RSCAN0.RFSTS3.UINT16[L]
#define RSCAN0RFSTS3LL RSCAN0.RFSTS3.UINT8[LL]
#define RSCAN0RFSTS3LH RSCAN0.RFSTS3.UINT8[LH]
#define RSCAN0RFSTS3H RSCAN0.RFSTS3.UINT16[H]
#define RSCAN0RFSTS3HL RSCAN0.RFSTS3.UINT8[HL]
#define RSCAN0RFSTS3HH RSCAN0.RFSTS3.UINT8[HH]
#define RSCAN0RFSTS4 RSCAN0.RFSTS4.UINT32
#define RSCAN0RFSTS4L RSCAN0.RFSTS4.UINT16[L]
#define RSCAN0RFSTS4LL RSCAN0.RFSTS4.UINT8[LL]
#define RSCAN0RFSTS4LH RSCAN0.RFSTS4.UINT8[LH]
#define RSCAN0RFSTS4H RSCAN0.RFSTS4.UINT16[H]
#define RSCAN0RFSTS4HL RSCAN0.RFSTS4.UINT8[HL]
#define RSCAN0RFSTS4HH RSCAN0.RFSTS4.UINT8[HH]
#define RSCAN0RFSTS5 RSCAN0.RFSTS5.UINT32
#define RSCAN0RFSTS5L RSCAN0.RFSTS5.UINT16[L]
#define RSCAN0RFSTS5LL RSCAN0.RFSTS5.UINT8[LL]
#define RSCAN0RFSTS5LH RSCAN0.RFSTS5.UINT8[LH]
#define RSCAN0RFSTS5H RSCAN0.RFSTS5.UINT16[H]
#define RSCAN0RFSTS5HL RSCAN0.RFSTS5.UINT8[HL]
#define RSCAN0RFSTS5HH RSCAN0.RFSTS5.UINT8[HH]
#define RSCAN0RFSTS6 RSCAN0.RFSTS6.UINT32
#define RSCAN0RFSTS6L RSCAN0.RFSTS6.UINT16[L]
#define RSCAN0RFSTS6LL RSCAN0.RFSTS6.UINT8[LL]
#define RSCAN0RFSTS6LH RSCAN0.RFSTS6.UINT8[LH]
#define RSCAN0RFSTS6H RSCAN0.RFSTS6.UINT16[H]
#define RSCAN0RFSTS6HL RSCAN0.RFSTS6.UINT8[HL]
#define RSCAN0RFSTS6HH RSCAN0.RFSTS6.UINT8[HH]
#define RSCAN0RFSTS7 RSCAN0.RFSTS7.UINT32
#define RSCAN0RFSTS7L RSCAN0.RFSTS7.UINT16[L]
#define RSCAN0RFSTS7LL RSCAN0.RFSTS7.UINT8[LL]
#define RSCAN0RFSTS7LH RSCAN0.RFSTS7.UINT8[LH]
#define RSCAN0RFSTS7H RSCAN0.RFSTS7.UINT16[H]
#define RSCAN0RFSTS7HL RSCAN0.RFSTS7.UINT8[HL]
#define RSCAN0RFSTS7HH RSCAN0.RFSTS7.UINT8[HH]
#define RSCAN0RFPCTR0 RSCAN0.RFPCTR0.UINT32
#define RSCAN0RFPCTR0L RSCAN0.RFPCTR0.UINT16[L]
#define RSCAN0RFPCTR0LL RSCAN0.RFPCTR0.UINT8[LL]
#define RSCAN0RFPCTR0LH RSCAN0.RFPCTR0.UINT8[LH]
#define RSCAN0RFPCTR0H RSCAN0.RFPCTR0.UINT16[H]
#define RSCAN0RFPCTR0HL RSCAN0.RFPCTR0.UINT8[HL]
#define RSCAN0RFPCTR0HH RSCAN0.RFPCTR0.UINT8[HH]
#define RSCAN0RFPCTR1 RSCAN0.RFPCTR1.UINT32
#define RSCAN0RFPCTR1L RSCAN0.RFPCTR1.UINT16[L]
#define RSCAN0RFPCTR1LL RSCAN0.RFPCTR1.UINT8[LL]
#define RSCAN0RFPCTR1LH RSCAN0.RFPCTR1.UINT8[LH]
#define RSCAN0RFPCTR1H RSCAN0.RFPCTR1.UINT16[H]
#define RSCAN0RFPCTR1HL RSCAN0.RFPCTR1.UINT8[HL]
#define RSCAN0RFPCTR1HH RSCAN0.RFPCTR1.UINT8[HH]
#define RSCAN0RFPCTR2 RSCAN0.RFPCTR2.UINT32
#define RSCAN0RFPCTR2L RSCAN0.RFPCTR2.UINT16[L]
#define RSCAN0RFPCTR2LL RSCAN0.RFPCTR2.UINT8[LL]
#define RSCAN0RFPCTR2LH RSCAN0.RFPCTR2.UINT8[LH]
#define RSCAN0RFPCTR2H RSCAN0.RFPCTR2.UINT16[H]
#define RSCAN0RFPCTR2HL RSCAN0.RFPCTR2.UINT8[HL]
#define RSCAN0RFPCTR2HH RSCAN0.RFPCTR2.UINT8[HH]
#define RSCAN0RFPCTR3 RSCAN0.RFPCTR3.UINT32
#define RSCAN0RFPCTR3L RSCAN0.RFPCTR3.UINT16[L]
#define RSCAN0RFPCTR3LL RSCAN0.RFPCTR3.UINT8[LL]
#define RSCAN0RFPCTR3LH RSCAN0.RFPCTR3.UINT8[LH]
#define RSCAN0RFPCTR3H RSCAN0.RFPCTR3.UINT16[H]
#define RSCAN0RFPCTR3HL RSCAN0.RFPCTR3.UINT8[HL]
#define RSCAN0RFPCTR3HH RSCAN0.RFPCTR3.UINT8[HH]
#define RSCAN0RFPCTR4 RSCAN0.RFPCTR4.UINT32
#define RSCAN0RFPCTR4L RSCAN0.RFPCTR4.UINT16[L]
#define RSCAN0RFPCTR4LL RSCAN0.RFPCTR4.UINT8[LL]
#define RSCAN0RFPCTR4LH RSCAN0.RFPCTR4.UINT8[LH]
#define RSCAN0RFPCTR4H RSCAN0.RFPCTR4.UINT16[H]
#define RSCAN0RFPCTR4HL RSCAN0.RFPCTR4.UINT8[HL]
#define RSCAN0RFPCTR4HH RSCAN0.RFPCTR4.UINT8[HH]
#define RSCAN0RFPCTR5 RSCAN0.RFPCTR5.UINT32
#define RSCAN0RFPCTR5L RSCAN0.RFPCTR5.UINT16[L]
#define RSCAN0RFPCTR5LL RSCAN0.RFPCTR5.UINT8[LL]
#define RSCAN0RFPCTR5LH RSCAN0.RFPCTR5.UINT8[LH]
#define RSCAN0RFPCTR5H RSCAN0.RFPCTR5.UINT16[H]
#define RSCAN0RFPCTR5HL RSCAN0.RFPCTR5.UINT8[HL]
#define RSCAN0RFPCTR5HH RSCAN0.RFPCTR5.UINT8[HH]
#define RSCAN0RFPCTR6 RSCAN0.RFPCTR6.UINT32
#define RSCAN0RFPCTR6L RSCAN0.RFPCTR6.UINT16[L]
#define RSCAN0RFPCTR6LL RSCAN0.RFPCTR6.UINT8[LL]
#define RSCAN0RFPCTR6LH RSCAN0.RFPCTR6.UINT8[LH]
#define RSCAN0RFPCTR6H RSCAN0.RFPCTR6.UINT16[H]
#define RSCAN0RFPCTR6HL RSCAN0.RFPCTR6.UINT8[HL]
#define RSCAN0RFPCTR6HH RSCAN0.RFPCTR6.UINT8[HH]
#define RSCAN0RFPCTR7 RSCAN0.RFPCTR7.UINT32
#define RSCAN0RFPCTR7L RSCAN0.RFPCTR7.UINT16[L]
#define RSCAN0RFPCTR7LL RSCAN0.RFPCTR7.UINT8[LL]
#define RSCAN0RFPCTR7LH RSCAN0.RFPCTR7.UINT8[LH]
#define RSCAN0RFPCTR7H RSCAN0.RFPCTR7.UINT16[H]
#define RSCAN0RFPCTR7HL RSCAN0.RFPCTR7.UINT8[HL]
#define RSCAN0RFPCTR7HH RSCAN0.RFPCTR7.UINT8[HH]
#define RSCAN0CFCC0 RSCAN0.CFCC0.UINT32
#define RSCAN0CFCC0L RSCAN0.CFCC0.UINT16[L]
#define RSCAN0CFCC0LL RSCAN0.CFCC0.UINT8[LL]
#define RSCAN0CFCC0LH RSCAN0.CFCC0.UINT8[LH]
#define RSCAN0CFCC0H RSCAN0.CFCC0.UINT16[H]
#define RSCAN0CFCC0HL RSCAN0.CFCC0.UINT8[HL]
#define RSCAN0CFCC0HH RSCAN0.CFCC0.UINT8[HH]
#define RSCAN0CFCC1 RSCAN0.CFCC1.UINT32
#define RSCAN0CFCC1L RSCAN0.CFCC1.UINT16[L]
#define RSCAN0CFCC1LL RSCAN0.CFCC1.UINT8[LL]
#define RSCAN0CFCC1LH RSCAN0.CFCC1.UINT8[LH]
#define RSCAN0CFCC1H RSCAN0.CFCC1.UINT16[H]
#define RSCAN0CFCC1HL RSCAN0.CFCC1.UINT8[HL]
#define RSCAN0CFCC1HH RSCAN0.CFCC1.UINT8[HH]
#define RSCAN0CFCC2 RSCAN0.CFCC2.UINT32
#define RSCAN0CFCC2L RSCAN0.CFCC2.UINT16[L]
#define RSCAN0CFCC2LL RSCAN0.CFCC2.UINT8[LL]
#define RSCAN0CFCC2LH RSCAN0.CFCC2.UINT8[LH]
#define RSCAN0CFCC2H RSCAN0.CFCC2.UINT16[H]
#define RSCAN0CFCC2HL RSCAN0.CFCC2.UINT8[HL]
#define RSCAN0CFCC2HH RSCAN0.CFCC2.UINT8[HH]
#define RSCAN0CFCC3 RSCAN0.CFCC3.UINT32
#define RSCAN0CFCC3L RSCAN0.CFCC3.UINT16[L]
#define RSCAN0CFCC3LL RSCAN0.CFCC3.UINT8[LL]
#define RSCAN0CFCC3LH RSCAN0.CFCC3.UINT8[LH]
#define RSCAN0CFCC3H RSCAN0.CFCC3.UINT16[H]
#define RSCAN0CFCC3HL RSCAN0.CFCC3.UINT8[HL]
#define RSCAN0CFCC3HH RSCAN0.CFCC3.UINT8[HH]
#define RSCAN0CFCC4 RSCAN0.CFCC4.UINT32
#define RSCAN0CFCC4L RSCAN0.CFCC4.UINT16[L]
#define RSCAN0CFCC4LL RSCAN0.CFCC4.UINT8[LL]
#define RSCAN0CFCC4LH RSCAN0.CFCC4.UINT8[LH]
#define RSCAN0CFCC4H RSCAN0.CFCC4.UINT16[H]
#define RSCAN0CFCC4HL RSCAN0.CFCC4.UINT8[HL]
#define RSCAN0CFCC4HH RSCAN0.CFCC4.UINT8[HH]
#define RSCAN0CFCC5 RSCAN0.CFCC5.UINT32
#define RSCAN0CFCC5L RSCAN0.CFCC5.UINT16[L]
#define RSCAN0CFCC5LL RSCAN0.CFCC5.UINT8[LL]
#define RSCAN0CFCC5LH RSCAN0.CFCC5.UINT8[LH]
#define RSCAN0CFCC5H RSCAN0.CFCC5.UINT16[H]
#define RSCAN0CFCC5HL RSCAN0.CFCC5.UINT8[HL]
#define RSCAN0CFCC5HH RSCAN0.CFCC5.UINT8[HH]
#define RSCAN0CFCC6 RSCAN0.CFCC6.UINT32
#define RSCAN0CFCC6L RSCAN0.CFCC6.UINT16[L]
#define RSCAN0CFCC6LL RSCAN0.CFCC6.UINT8[LL]
#define RSCAN0CFCC6LH RSCAN0.CFCC6.UINT8[LH]
#define RSCAN0CFCC6H RSCAN0.CFCC6.UINT16[H]
#define RSCAN0CFCC6HL RSCAN0.CFCC6.UINT8[HL]
#define RSCAN0CFCC6HH RSCAN0.CFCC6.UINT8[HH]
#define RSCAN0CFCC7 RSCAN0.CFCC7.UINT32
#define RSCAN0CFCC7L RSCAN0.CFCC7.UINT16[L]
#define RSCAN0CFCC7LL RSCAN0.CFCC7.UINT8[LL]
#define RSCAN0CFCC7LH RSCAN0.CFCC7.UINT8[LH]
#define RSCAN0CFCC7H RSCAN0.CFCC7.UINT16[H]
#define RSCAN0CFCC7HL RSCAN0.CFCC7.UINT8[HL]
#define RSCAN0CFCC7HH RSCAN0.CFCC7.UINT8[HH]
#define RSCAN0CFCC8 RSCAN0.CFCC8.UINT32
#define RSCAN0CFCC8L RSCAN0.CFCC8.UINT16[L]
#define RSCAN0CFCC8LL RSCAN0.CFCC8.UINT8[LL]
#define RSCAN0CFCC8LH RSCAN0.CFCC8.UINT8[LH]
#define RSCAN0CFCC8H RSCAN0.CFCC8.UINT16[H]
#define RSCAN0CFCC8HL RSCAN0.CFCC8.UINT8[HL]
#define RSCAN0CFCC8HH RSCAN0.CFCC8.UINT8[HH]
#define RSCAN0CFSTS0 RSCAN0.CFSTS0.UINT32
#define RSCAN0CFSTS0L RSCAN0.CFSTS0.UINT16[L]
#define RSCAN0CFSTS0LL RSCAN0.CFSTS0.UINT8[LL]
#define RSCAN0CFSTS0LH RSCAN0.CFSTS0.UINT8[LH]
#define RSCAN0CFSTS0H RSCAN0.CFSTS0.UINT16[H]
#define RSCAN0CFSTS0HL RSCAN0.CFSTS0.UINT8[HL]
#define RSCAN0CFSTS0HH RSCAN0.CFSTS0.UINT8[HH]
#define RSCAN0CFSTS1 RSCAN0.CFSTS1.UINT32
#define RSCAN0CFSTS1L RSCAN0.CFSTS1.UINT16[L]
#define RSCAN0CFSTS1LL RSCAN0.CFSTS1.UINT8[LL]
#define RSCAN0CFSTS1LH RSCAN0.CFSTS1.UINT8[LH]
#define RSCAN0CFSTS1H RSCAN0.CFSTS1.UINT16[H]
#define RSCAN0CFSTS1HL RSCAN0.CFSTS1.UINT8[HL]
#define RSCAN0CFSTS1HH RSCAN0.CFSTS1.UINT8[HH]
#define RSCAN0CFSTS2 RSCAN0.CFSTS2.UINT32
#define RSCAN0CFSTS2L RSCAN0.CFSTS2.UINT16[L]
#define RSCAN0CFSTS2LL RSCAN0.CFSTS2.UINT8[LL]
#define RSCAN0CFSTS2LH RSCAN0.CFSTS2.UINT8[LH]
#define RSCAN0CFSTS2H RSCAN0.CFSTS2.UINT16[H]
#define RSCAN0CFSTS2HL RSCAN0.CFSTS2.UINT8[HL]
#define RSCAN0CFSTS2HH RSCAN0.CFSTS2.UINT8[HH]
#define RSCAN0CFSTS3 RSCAN0.CFSTS3.UINT32
#define RSCAN0CFSTS3L RSCAN0.CFSTS3.UINT16[L]
#define RSCAN0CFSTS3LL RSCAN0.CFSTS3.UINT8[LL]
#define RSCAN0CFSTS3LH RSCAN0.CFSTS3.UINT8[LH]
#define RSCAN0CFSTS3H RSCAN0.CFSTS3.UINT16[H]
#define RSCAN0CFSTS3HL RSCAN0.CFSTS3.UINT8[HL]
#define RSCAN0CFSTS3HH RSCAN0.CFSTS3.UINT8[HH]
#define RSCAN0CFSTS4 RSCAN0.CFSTS4.UINT32
#define RSCAN0CFSTS4L RSCAN0.CFSTS4.UINT16[L]
#define RSCAN0CFSTS4LL RSCAN0.CFSTS4.UINT8[LL]
#define RSCAN0CFSTS4LH RSCAN0.CFSTS4.UINT8[LH]
#define RSCAN0CFSTS4H RSCAN0.CFSTS4.UINT16[H]
#define RSCAN0CFSTS4HL RSCAN0.CFSTS4.UINT8[HL]
#define RSCAN0CFSTS4HH RSCAN0.CFSTS4.UINT8[HH]
#define RSCAN0CFSTS5 RSCAN0.CFSTS5.UINT32
#define RSCAN0CFSTS5L RSCAN0.CFSTS5.UINT16[L]
#define RSCAN0CFSTS5LL RSCAN0.CFSTS5.UINT8[LL]
#define RSCAN0CFSTS5LH RSCAN0.CFSTS5.UINT8[LH]
#define RSCAN0CFSTS5H RSCAN0.CFSTS5.UINT16[H]
#define RSCAN0CFSTS5HL RSCAN0.CFSTS5.UINT8[HL]
#define RSCAN0CFSTS5HH RSCAN0.CFSTS5.UINT8[HH]
#define RSCAN0CFSTS6 RSCAN0.CFSTS6.UINT32
#define RSCAN0CFSTS6L RSCAN0.CFSTS6.UINT16[L]
#define RSCAN0CFSTS6LL RSCAN0.CFSTS6.UINT8[LL]
#define RSCAN0CFSTS6LH RSCAN0.CFSTS6.UINT8[LH]
#define RSCAN0CFSTS6H RSCAN0.CFSTS6.UINT16[H]
#define RSCAN0CFSTS6HL RSCAN0.CFSTS6.UINT8[HL]
#define RSCAN0CFSTS6HH RSCAN0.CFSTS6.UINT8[HH]
#define RSCAN0CFSTS7 RSCAN0.CFSTS7.UINT32
#define RSCAN0CFSTS7L RSCAN0.CFSTS7.UINT16[L]
#define RSCAN0CFSTS7LL RSCAN0.CFSTS7.UINT8[LL]
#define RSCAN0CFSTS7LH RSCAN0.CFSTS7.UINT8[LH]
#define RSCAN0CFSTS7H RSCAN0.CFSTS7.UINT16[H]
#define RSCAN0CFSTS7HL RSCAN0.CFSTS7.UINT8[HL]
#define RSCAN0CFSTS7HH RSCAN0.CFSTS7.UINT8[HH]
#define RSCAN0CFSTS8 RSCAN0.CFSTS8.UINT32
#define RSCAN0CFSTS8L RSCAN0.CFSTS8.UINT16[L]
#define RSCAN0CFSTS8LL RSCAN0.CFSTS8.UINT8[LL]
#define RSCAN0CFSTS8LH RSCAN0.CFSTS8.UINT8[LH]
#define RSCAN0CFSTS8H RSCAN0.CFSTS8.UINT16[H]
#define RSCAN0CFSTS8HL RSCAN0.CFSTS8.UINT8[HL]
#define RSCAN0CFSTS8HH RSCAN0.CFSTS8.UINT8[HH]
#define RSCAN0CFPCTR0 RSCAN0.CFPCTR0.UINT32
#define RSCAN0CFPCTR0L RSCAN0.CFPCTR0.UINT16[L]
#define RSCAN0CFPCTR0LL RSCAN0.CFPCTR0.UINT8[LL]
#define RSCAN0CFPCTR0LH RSCAN0.CFPCTR0.UINT8[LH]
#define RSCAN0CFPCTR0H RSCAN0.CFPCTR0.UINT16[H]
#define RSCAN0CFPCTR0HL RSCAN0.CFPCTR0.UINT8[HL]
#define RSCAN0CFPCTR0HH RSCAN0.CFPCTR0.UINT8[HH]
#define RSCAN0CFPCTR1 RSCAN0.CFPCTR1.UINT32
#define RSCAN0CFPCTR1L RSCAN0.CFPCTR1.UINT16[L]
#define RSCAN0CFPCTR1LL RSCAN0.CFPCTR1.UINT8[LL]
#define RSCAN0CFPCTR1LH RSCAN0.CFPCTR1.UINT8[LH]
#define RSCAN0CFPCTR1H RSCAN0.CFPCTR1.UINT16[H]
#define RSCAN0CFPCTR1HL RSCAN0.CFPCTR1.UINT8[HL]
#define RSCAN0CFPCTR1HH RSCAN0.CFPCTR1.UINT8[HH]
#define RSCAN0CFPCTR2 RSCAN0.CFPCTR2.UINT32
#define RSCAN0CFPCTR2L RSCAN0.CFPCTR2.UINT16[L]
#define RSCAN0CFPCTR2LL RSCAN0.CFPCTR2.UINT8[LL]
#define RSCAN0CFPCTR2LH RSCAN0.CFPCTR2.UINT8[LH]
#define RSCAN0CFPCTR2H RSCAN0.CFPCTR2.UINT16[H]
#define RSCAN0CFPCTR2HL RSCAN0.CFPCTR2.UINT8[HL]
#define RSCAN0CFPCTR2HH RSCAN0.CFPCTR2.UINT8[HH]
#define RSCAN0CFPCTR3 RSCAN0.CFPCTR3.UINT32
#define RSCAN0CFPCTR3L RSCAN0.CFPCTR3.UINT16[L]
#define RSCAN0CFPCTR3LL RSCAN0.CFPCTR3.UINT8[LL]
#define RSCAN0CFPCTR3LH RSCAN0.CFPCTR3.UINT8[LH]
#define RSCAN0CFPCTR3H RSCAN0.CFPCTR3.UINT16[H]
#define RSCAN0CFPCTR3HL RSCAN0.CFPCTR3.UINT8[HL]
#define RSCAN0CFPCTR3HH RSCAN0.CFPCTR3.UINT8[HH]
#define RSCAN0CFPCTR4 RSCAN0.CFPCTR4.UINT32
#define RSCAN0CFPCTR4L RSCAN0.CFPCTR4.UINT16[L]
#define RSCAN0CFPCTR4LL RSCAN0.CFPCTR4.UINT8[LL]
#define RSCAN0CFPCTR4LH RSCAN0.CFPCTR4.UINT8[LH]
#define RSCAN0CFPCTR4H RSCAN0.CFPCTR4.UINT16[H]
#define RSCAN0CFPCTR4HL RSCAN0.CFPCTR4.UINT8[HL]
#define RSCAN0CFPCTR4HH RSCAN0.CFPCTR4.UINT8[HH]
#define RSCAN0CFPCTR5 RSCAN0.CFPCTR5.UINT32
#define RSCAN0CFPCTR5L RSCAN0.CFPCTR5.UINT16[L]
#define RSCAN0CFPCTR5LL RSCAN0.CFPCTR5.UINT8[LL]
#define RSCAN0CFPCTR5LH RSCAN0.CFPCTR5.UINT8[LH]
#define RSCAN0CFPCTR5H RSCAN0.CFPCTR5.UINT16[H]
#define RSCAN0CFPCTR5HL RSCAN0.CFPCTR5.UINT8[HL]
#define RSCAN0CFPCTR5HH RSCAN0.CFPCTR5.UINT8[HH]
#define RSCAN0CFPCTR6 RSCAN0.CFPCTR6.UINT32
#define RSCAN0CFPCTR6L RSCAN0.CFPCTR6.UINT16[L]
#define RSCAN0CFPCTR6LL RSCAN0.CFPCTR6.UINT8[LL]
#define RSCAN0CFPCTR6LH RSCAN0.CFPCTR6.UINT8[LH]
#define RSCAN0CFPCTR6H RSCAN0.CFPCTR6.UINT16[H]
#define RSCAN0CFPCTR6HL RSCAN0.CFPCTR6.UINT8[HL]
#define RSCAN0CFPCTR6HH RSCAN0.CFPCTR6.UINT8[HH]
#define RSCAN0CFPCTR7 RSCAN0.CFPCTR7.UINT32
#define RSCAN0CFPCTR7L RSCAN0.CFPCTR7.UINT16[L]
#define RSCAN0CFPCTR7LL RSCAN0.CFPCTR7.UINT8[LL]
#define RSCAN0CFPCTR7LH RSCAN0.CFPCTR7.UINT8[LH]
#define RSCAN0CFPCTR7H RSCAN0.CFPCTR7.UINT16[H]
#define RSCAN0CFPCTR7HL RSCAN0.CFPCTR7.UINT8[HL]
#define RSCAN0CFPCTR7HH RSCAN0.CFPCTR7.UINT8[HH]
#define RSCAN0CFPCTR8 RSCAN0.CFPCTR8.UINT32
#define RSCAN0CFPCTR8L RSCAN0.CFPCTR8.UINT16[L]
#define RSCAN0CFPCTR8LL RSCAN0.CFPCTR8.UINT8[LL]
#define RSCAN0CFPCTR8LH RSCAN0.CFPCTR8.UINT8[LH]
#define RSCAN0CFPCTR8H RSCAN0.CFPCTR8.UINT16[H]
#define RSCAN0CFPCTR8HL RSCAN0.CFPCTR8.UINT8[HL]
#define RSCAN0CFPCTR8HH RSCAN0.CFPCTR8.UINT8[HH]
#define RSCAN0FESTS RSCAN0.FESTS.UINT32
#define RSCAN0FESTSL RSCAN0.FESTS.UINT16[L]
#define RSCAN0FESTSLL RSCAN0.FESTS.UINT8[LL]
#define RSCAN0FESTSLH RSCAN0.FESTS.UINT8[LH]
#define RSCAN0FESTSH RSCAN0.FESTS.UINT16[H]
#define RSCAN0FESTSHL RSCAN0.FESTS.UINT8[HL]
#define RSCAN0FFSTS RSCAN0.FFSTS.UINT32
#define RSCAN0FFSTSL RSCAN0.FFSTS.UINT16[L]
#define RSCAN0FFSTSLL RSCAN0.FFSTS.UINT8[LL]
#define RSCAN0FFSTSLH RSCAN0.FFSTS.UINT8[LH]
#define RSCAN0FFSTSH RSCAN0.FFSTS.UINT16[H]
#define RSCAN0FFSTSHL RSCAN0.FFSTS.UINT8[HL]
#define RSCAN0FMSTS RSCAN0.FMSTS.UINT32
#define RSCAN0FMSTSL RSCAN0.FMSTS.UINT16[L]
#define RSCAN0FMSTSLL RSCAN0.FMSTS.UINT8[LL]
#define RSCAN0FMSTSLH RSCAN0.FMSTS.UINT8[LH]
#define RSCAN0FMSTSH RSCAN0.FMSTS.UINT16[H]
#define RSCAN0FMSTSHL RSCAN0.FMSTS.UINT8[HL]
#define RSCAN0RFISTS RSCAN0.RFISTS.UINT32
#define RSCAN0RFISTSL RSCAN0.RFISTS.UINT16[L]
#define RSCAN0RFISTSLL RSCAN0.RFISTS.UINT8[LL]
#define RSCAN0RFISTSLH RSCAN0.RFISTS.UINT8[LH]
#define RSCAN0RFISTSH RSCAN0.RFISTS.UINT16[H]
#define RSCAN0RFISTSHL RSCAN0.RFISTS.UINT8[HL]
#define RSCAN0RFISTSHH RSCAN0.RFISTS.UINT8[HH]
#define RSCAN0CFRISTS RSCAN0.CFRISTS.UINT32
#define RSCAN0CFRISTSL RSCAN0.CFRISTS.UINT16[L]
#define RSCAN0CFRISTSLL RSCAN0.CFRISTS.UINT8[LL]
#define RSCAN0CFRISTSLH RSCAN0.CFRISTS.UINT8[LH]
#define RSCAN0CFRISTSH RSCAN0.CFRISTS.UINT16[H]
#define RSCAN0CFRISTSHL RSCAN0.CFRISTS.UINT8[HL]
#define RSCAN0CFRISTSHH RSCAN0.CFRISTS.UINT8[HH]
#define RSCAN0CFTISTS RSCAN0.CFTISTS.UINT32
#define RSCAN0CFTISTSL RSCAN0.CFTISTS.UINT16[L]
#define RSCAN0CFTISTSLL RSCAN0.CFTISTS.UINT8[LL]
#define RSCAN0CFTISTSLH RSCAN0.CFTISTS.UINT8[LH]
#define RSCAN0TMC0 RSCAN0.TMC0
#define RSCAN0TMC1 RSCAN0.TMC1
#define RSCAN0TMC2 RSCAN0.TMC2
#define RSCAN0TMC3 RSCAN0.TMC3
#define RSCAN0TMC4 RSCAN0.TMC4
#define RSCAN0TMC5 RSCAN0.TMC5
#define RSCAN0TMC6 RSCAN0.TMC6
#define RSCAN0TMC7 RSCAN0.TMC7
#define RSCAN0TMC8 RSCAN0.TMC8
#define RSCAN0TMC9 RSCAN0.TMC9
#define RSCAN0TMC10 RSCAN0.TMC10
#define RSCAN0TMC11 RSCAN0.TMC11
#define RSCAN0TMC12 RSCAN0.TMC12
#define RSCAN0TMC13 RSCAN0.TMC13
#define RSCAN0TMC14 RSCAN0.TMC14
#define RSCAN0TMC15 RSCAN0.TMC15
#define RSCAN0TMC16 RSCAN0.TMC16
#define RSCAN0TMC17 RSCAN0.TMC17
#define RSCAN0TMC18 RSCAN0.TMC18
#define RSCAN0TMC19 RSCAN0.TMC19
#define RSCAN0TMC20 RSCAN0.TMC20
#define RSCAN0TMC21 RSCAN0.TMC21
#define RSCAN0TMC22 RSCAN0.TMC22
#define RSCAN0TMC23 RSCAN0.TMC23
#define RSCAN0TMC24 RSCAN0.TMC24
#define RSCAN0TMC25 RSCAN0.TMC25
#define RSCAN0TMC26 RSCAN0.TMC26
#define RSCAN0TMC27 RSCAN0.TMC27
#define RSCAN0TMC28 RSCAN0.TMC28
#define RSCAN0TMC29 RSCAN0.TMC29
#define RSCAN0TMC30 RSCAN0.TMC30
#define RSCAN0TMC31 RSCAN0.TMC31
#define RSCAN0TMC32 RSCAN0.TMC32
#define RSCAN0TMC33 RSCAN0.TMC33
#define RSCAN0TMC34 RSCAN0.TMC34
#define RSCAN0TMC35 RSCAN0.TMC35
#define RSCAN0TMC36 RSCAN0.TMC36
#define RSCAN0TMC37 RSCAN0.TMC37
#define RSCAN0TMC38 RSCAN0.TMC38
#define RSCAN0TMC39 RSCAN0.TMC39
#define RSCAN0TMC40 RSCAN0.TMC40
#define RSCAN0TMC41 RSCAN0.TMC41
#define RSCAN0TMC42 RSCAN0.TMC42
#define RSCAN0TMC43 RSCAN0.TMC43
#define RSCAN0TMC44 RSCAN0.TMC44
#define RSCAN0TMC45 RSCAN0.TMC45
#define RSCAN0TMC46 RSCAN0.TMC46
#define RSCAN0TMC47 RSCAN0.TMC47
#define RSCAN0TMSTS0 RSCAN0.TMSTS0
#define RSCAN0TMSTS1 RSCAN0.TMSTS1
#define RSCAN0TMSTS2 RSCAN0.TMSTS2
#define RSCAN0TMSTS3 RSCAN0.TMSTS3
#define RSCAN0TMSTS4 RSCAN0.TMSTS4
#define RSCAN0TMSTS5 RSCAN0.TMSTS5
#define RSCAN0TMSTS6 RSCAN0.TMSTS6
#define RSCAN0TMSTS7 RSCAN0.TMSTS7
#define RSCAN0TMSTS8 RSCAN0.TMSTS8
#define RSCAN0TMSTS9 RSCAN0.TMSTS9
#define RSCAN0TMSTS10 RSCAN0.TMSTS10
#define RSCAN0TMSTS11 RSCAN0.TMSTS11
#define RSCAN0TMSTS12 RSCAN0.TMSTS12
#define RSCAN0TMSTS13 RSCAN0.TMSTS13
#define RSCAN0TMSTS14 RSCAN0.TMSTS14
#define RSCAN0TMSTS15 RSCAN0.TMSTS15
#define RSCAN0TMSTS16 RSCAN0.TMSTS16
#define RSCAN0TMSTS17 RSCAN0.TMSTS17
#define RSCAN0TMSTS18 RSCAN0.TMSTS18
#define RSCAN0TMSTS19 RSCAN0.TMSTS19
#define RSCAN0TMSTS20 RSCAN0.TMSTS20
#define RSCAN0TMSTS21 RSCAN0.TMSTS21
#define RSCAN0TMSTS22 RSCAN0.TMSTS22
#define RSCAN0TMSTS23 RSCAN0.TMSTS23
#define RSCAN0TMSTS24 RSCAN0.TMSTS24
#define RSCAN0TMSTS25 RSCAN0.TMSTS25
#define RSCAN0TMSTS26 RSCAN0.TMSTS26
#define RSCAN0TMSTS27 RSCAN0.TMSTS27
#define RSCAN0TMSTS28 RSCAN0.TMSTS28
#define RSCAN0TMSTS29 RSCAN0.TMSTS29
#define RSCAN0TMSTS30 RSCAN0.TMSTS30
#define RSCAN0TMSTS31 RSCAN0.TMSTS31
#define RSCAN0TMSTS32 RSCAN0.TMSTS32
#define RSCAN0TMSTS33 RSCAN0.TMSTS33
#define RSCAN0TMSTS34 RSCAN0.TMSTS34
#define RSCAN0TMSTS35 RSCAN0.TMSTS35
#define RSCAN0TMSTS36 RSCAN0.TMSTS36
#define RSCAN0TMSTS37 RSCAN0.TMSTS37
#define RSCAN0TMSTS38 RSCAN0.TMSTS38
#define RSCAN0TMSTS39 RSCAN0.TMSTS39
#define RSCAN0TMSTS40 RSCAN0.TMSTS40
#define RSCAN0TMSTS41 RSCAN0.TMSTS41
#define RSCAN0TMSTS42 RSCAN0.TMSTS42
#define RSCAN0TMSTS43 RSCAN0.TMSTS43
#define RSCAN0TMSTS44 RSCAN0.TMSTS44
#define RSCAN0TMSTS45 RSCAN0.TMSTS45
#define RSCAN0TMSTS46 RSCAN0.TMSTS46
#define RSCAN0TMSTS47 RSCAN0.TMSTS47
#define RSCAN0TMTRSTS0 RSCAN0.TMTRSTS0.UINT32
#define RSCAN0TMTRSTS0L RSCAN0.TMTRSTS0.UINT16[L]
#define RSCAN0TMTRSTS0LL RSCAN0.TMTRSTS0.UINT8[LL]
#define RSCAN0TMTRSTS0LH RSCAN0.TMTRSTS0.UINT8[LH]
#define RSCAN0TMTRSTS0H RSCAN0.TMTRSTS0.UINT16[H]
#define RSCAN0TMTRSTS0HL RSCAN0.TMTRSTS0.UINT8[HL]
#define RSCAN0TMTRSTS0HH RSCAN0.TMTRSTS0.UINT8[HH]
#define RSCAN0TMTRSTS1 RSCAN0.TMTRSTS1.UINT32
#define RSCAN0TMTRSTS1L RSCAN0.TMTRSTS1.UINT16[L]
#define RSCAN0TMTRSTS1LL RSCAN0.TMTRSTS1.UINT8[LL]
#define RSCAN0TMTRSTS1LH RSCAN0.TMTRSTS1.UINT8[LH]
#define RSCAN0TMTARSTS0 RSCAN0.TMTARSTS0.UINT32
#define RSCAN0TMTARSTS0L RSCAN0.TMTARSTS0.UINT16[L]
#define RSCAN0TMTARSTS0LL RSCAN0.TMTARSTS0.UINT8[LL]
#define RSCAN0TMTARSTS0LH RSCAN0.TMTARSTS0.UINT8[LH]
#define RSCAN0TMTARSTS0H RSCAN0.TMTARSTS0.UINT16[H]
#define RSCAN0TMTARSTS0HL RSCAN0.TMTARSTS0.UINT8[HL]
#define RSCAN0TMTARSTS0HH RSCAN0.TMTARSTS0.UINT8[HH]
#define RSCAN0TMTARSTS1 RSCAN0.TMTARSTS1.UINT32
#define RSCAN0TMTARSTS1L RSCAN0.TMTARSTS1.UINT16[L]
#define RSCAN0TMTARSTS1LL RSCAN0.TMTARSTS1.UINT8[LL]
#define RSCAN0TMTARSTS1LH RSCAN0.TMTARSTS1.UINT8[LH]
#define RSCAN0TMTCSTS0 RSCAN0.TMTCSTS0.UINT32
#define RSCAN0TMTCSTS0L RSCAN0.TMTCSTS0.UINT16[L]
#define RSCAN0TMTCSTS0LL RSCAN0.TMTCSTS0.UINT8[LL]
#define RSCAN0TMTCSTS0LH RSCAN0.TMTCSTS0.UINT8[LH]
#define RSCAN0TMTCSTS0H RSCAN0.TMTCSTS0.UINT16[H]
#define RSCAN0TMTCSTS0HL RSCAN0.TMTCSTS0.UINT8[HL]
#define RSCAN0TMTCSTS0HH RSCAN0.TMTCSTS0.UINT8[HH]
#define RSCAN0TMTCSTS1 RSCAN0.TMTCSTS1.UINT32
#define RSCAN0TMTCSTS1L RSCAN0.TMTCSTS1.UINT16[L]
#define RSCAN0TMTCSTS1LL RSCAN0.TMTCSTS1.UINT8[LL]
#define RSCAN0TMTCSTS1LH RSCAN0.TMTCSTS1.UINT8[LH]
#define RSCAN0TMTASTS0 RSCAN0.TMTASTS0.UINT32
#define RSCAN0TMTASTS0L RSCAN0.TMTASTS0.UINT16[L]
#define RSCAN0TMTASTS0LL RSCAN0.TMTASTS0.UINT8[LL]
#define RSCAN0TMTASTS0LH RSCAN0.TMTASTS0.UINT8[LH]
#define RSCAN0TMTASTS0H RSCAN0.TMTASTS0.UINT16[H]
#define RSCAN0TMTASTS0HL RSCAN0.TMTASTS0.UINT8[HL]
#define RSCAN0TMTASTS0HH RSCAN0.TMTASTS0.UINT8[HH]
#define RSCAN0TMTASTS1 RSCAN0.TMTASTS1.UINT32
#define RSCAN0TMTASTS1L RSCAN0.TMTASTS1.UINT16[L]
#define RSCAN0TMTASTS1LL RSCAN0.TMTASTS1.UINT8[LL]
#define RSCAN0TMTASTS1LH RSCAN0.TMTASTS1.UINT8[LH]
#define RSCAN0TMIEC0 RSCAN0.TMIEC0.UINT32
#define RSCAN0TMIEC0L RSCAN0.TMIEC0.UINT16[L]
#define RSCAN0TMIEC0LL RSCAN0.TMIEC0.UINT8[LL]
#define RSCAN0TMIEC0LH RSCAN0.TMIEC0.UINT8[LH]
#define RSCAN0TMIEC0H RSCAN0.TMIEC0.UINT16[H]
#define RSCAN0TMIEC0HL RSCAN0.TMIEC0.UINT8[HL]
#define RSCAN0TMIEC0HH RSCAN0.TMIEC0.UINT8[HH]
#define RSCAN0TMIEC1 RSCAN0.TMIEC1.UINT32
#define RSCAN0TMIEC1L RSCAN0.TMIEC1.UINT16[L]
#define RSCAN0TMIEC1LL RSCAN0.TMIEC1.UINT8[LL]
#define RSCAN0TMIEC1LH RSCAN0.TMIEC1.UINT8[LH]
#define RSCAN0TXQCC0 RSCAN0.TXQCC0.UINT32
#define RSCAN0TXQCC0L RSCAN0.TXQCC0.UINT16[L]
#define RSCAN0TXQCC0LL RSCAN0.TXQCC0.UINT8[LL]
#define RSCAN0TXQCC0LH RSCAN0.TXQCC0.UINT8[LH]
#define RSCAN0TXQCC0H RSCAN0.TXQCC0.UINT16[H]
#define RSCAN0TXQCC0HL RSCAN0.TXQCC0.UINT8[HL]
#define RSCAN0TXQCC0HH RSCAN0.TXQCC0.UINT8[HH]
#define RSCAN0TXQCC1 RSCAN0.TXQCC1.UINT32
#define RSCAN0TXQCC1L RSCAN0.TXQCC1.UINT16[L]
#define RSCAN0TXQCC1LL RSCAN0.TXQCC1.UINT8[LL]
#define RSCAN0TXQCC1LH RSCAN0.TXQCC1.UINT8[LH]
#define RSCAN0TXQCC1H RSCAN0.TXQCC1.UINT16[H]
#define RSCAN0TXQCC1HL RSCAN0.TXQCC1.UINT8[HL]
#define RSCAN0TXQCC1HH RSCAN0.TXQCC1.UINT8[HH]
#define RSCAN0TXQCC2 RSCAN0.TXQCC2.UINT32
#define RSCAN0TXQCC2L RSCAN0.TXQCC2.UINT16[L]
#define RSCAN0TXQCC2LL RSCAN0.TXQCC2.UINT8[LL]
#define RSCAN0TXQCC2LH RSCAN0.TXQCC2.UINT8[LH]
#define RSCAN0TXQCC2H RSCAN0.TXQCC2.UINT16[H]
#define RSCAN0TXQCC2HL RSCAN0.TXQCC2.UINT8[HL]
#define RSCAN0TXQCC2HH RSCAN0.TXQCC2.UINT8[HH]
#define RSCAN0TXQSTS0 RSCAN0.TXQSTS0.UINT32
#define RSCAN0TXQSTS0L RSCAN0.TXQSTS0.UINT16[L]
#define RSCAN0TXQSTS0LL RSCAN0.TXQSTS0.UINT8[LL]
#define RSCAN0TXQSTS0LH RSCAN0.TXQSTS0.UINT8[LH]
#define RSCAN0TXQSTS0H RSCAN0.TXQSTS0.UINT16[H]
#define RSCAN0TXQSTS0HL RSCAN0.TXQSTS0.UINT8[HL]
#define RSCAN0TXQSTS0HH RSCAN0.TXQSTS0.UINT8[HH]
#define RSCAN0TXQSTS1 RSCAN0.TXQSTS1.UINT32
#define RSCAN0TXQSTS1L RSCAN0.TXQSTS1.UINT16[L]
#define RSCAN0TXQSTS1LL RSCAN0.TXQSTS1.UINT8[LL]
#define RSCAN0TXQSTS1LH RSCAN0.TXQSTS1.UINT8[LH]
#define RSCAN0TXQSTS1H RSCAN0.TXQSTS1.UINT16[H]
#define RSCAN0TXQSTS1HL RSCAN0.TXQSTS1.UINT8[HL]
#define RSCAN0TXQSTS1HH RSCAN0.TXQSTS1.UINT8[HH]
#define RSCAN0TXQSTS2 RSCAN0.TXQSTS2.UINT32
#define RSCAN0TXQSTS2L RSCAN0.TXQSTS2.UINT16[L]
#define RSCAN0TXQSTS2LL RSCAN0.TXQSTS2.UINT8[LL]
#define RSCAN0TXQSTS2LH RSCAN0.TXQSTS2.UINT8[LH]
#define RSCAN0TXQSTS2H RSCAN0.TXQSTS2.UINT16[H]
#define RSCAN0TXQSTS2HL RSCAN0.TXQSTS2.UINT8[HL]
#define RSCAN0TXQSTS2HH RSCAN0.TXQSTS2.UINT8[HH]
#define RSCAN0TXQPCTR0 RSCAN0.TXQPCTR0.UINT32
#define RSCAN0TXQPCTR0L RSCAN0.TXQPCTR0.UINT16[L]
#define RSCAN0TXQPCTR0LL RSCAN0.TXQPCTR0.UINT8[LL]
#define RSCAN0TXQPCTR0LH RSCAN0.TXQPCTR0.UINT8[LH]
#define RSCAN0TXQPCTR0H RSCAN0.TXQPCTR0.UINT16[H]
#define RSCAN0TXQPCTR0HL RSCAN0.TXQPCTR0.UINT8[HL]
#define RSCAN0TXQPCTR0HH RSCAN0.TXQPCTR0.UINT8[HH]
#define RSCAN0TXQPCTR1 RSCAN0.TXQPCTR1.UINT32
#define RSCAN0TXQPCTR1L RSCAN0.TXQPCTR1.UINT16[L]
#define RSCAN0TXQPCTR1LL RSCAN0.TXQPCTR1.UINT8[LL]
#define RSCAN0TXQPCTR1LH RSCAN0.TXQPCTR1.UINT8[LH]
#define RSCAN0TXQPCTR1H RSCAN0.TXQPCTR1.UINT16[H]
#define RSCAN0TXQPCTR1HL RSCAN0.TXQPCTR1.UINT8[HL]
#define RSCAN0TXQPCTR1HH RSCAN0.TXQPCTR1.UINT8[HH]
#define RSCAN0TXQPCTR2 RSCAN0.TXQPCTR2.UINT32
#define RSCAN0TXQPCTR2L RSCAN0.TXQPCTR2.UINT16[L]
#define RSCAN0TXQPCTR2LL RSCAN0.TXQPCTR2.UINT8[LL]
#define RSCAN0TXQPCTR2LH RSCAN0.TXQPCTR2.UINT8[LH]
#define RSCAN0TXQPCTR2H RSCAN0.TXQPCTR2.UINT16[H]
#define RSCAN0TXQPCTR2HL RSCAN0.TXQPCTR2.UINT8[HL]
#define RSCAN0TXQPCTR2HH RSCAN0.TXQPCTR2.UINT8[HH]
#define RSCAN0THLCC0 RSCAN0.THLCC0.UINT32
#define RSCAN0THLCC0L RSCAN0.THLCC0.UINT16[L]
#define RSCAN0THLCC0LL RSCAN0.THLCC0.UINT8[LL]
#define RSCAN0THLCC0LH RSCAN0.THLCC0.UINT8[LH]
#define RSCAN0THLCC0H RSCAN0.THLCC0.UINT16[H]
#define RSCAN0THLCC0HL RSCAN0.THLCC0.UINT8[HL]
#define RSCAN0THLCC0HH RSCAN0.THLCC0.UINT8[HH]
#define RSCAN0THLCC1 RSCAN0.THLCC1.UINT32
#define RSCAN0THLCC1L RSCAN0.THLCC1.UINT16[L]
#define RSCAN0THLCC1LL RSCAN0.THLCC1.UINT8[LL]
#define RSCAN0THLCC1LH RSCAN0.THLCC1.UINT8[LH]
#define RSCAN0THLCC1H RSCAN0.THLCC1.UINT16[H]
#define RSCAN0THLCC1HL RSCAN0.THLCC1.UINT8[HL]
#define RSCAN0THLCC1HH RSCAN0.THLCC1.UINT8[HH]
#define RSCAN0THLCC2 RSCAN0.THLCC2.UINT32
#define RSCAN0THLCC2L RSCAN0.THLCC2.UINT16[L]
#define RSCAN0THLCC2LL RSCAN0.THLCC2.UINT8[LL]
#define RSCAN0THLCC2LH RSCAN0.THLCC2.UINT8[LH]
#define RSCAN0THLCC2H RSCAN0.THLCC2.UINT16[H]
#define RSCAN0THLCC2HL RSCAN0.THLCC2.UINT8[HL]
#define RSCAN0THLCC2HH RSCAN0.THLCC2.UINT8[HH]
#define RSCAN0THLSTS0 RSCAN0.THLSTS0.UINT32
#define RSCAN0THLSTS0L RSCAN0.THLSTS0.UINT16[L]
#define RSCAN0THLSTS0LL RSCAN0.THLSTS0.UINT8[LL]
#define RSCAN0THLSTS0LH RSCAN0.THLSTS0.UINT8[LH]
#define RSCAN0THLSTS0H RSCAN0.THLSTS0.UINT16[H]
#define RSCAN0THLSTS0HL RSCAN0.THLSTS0.UINT8[HL]
#define RSCAN0THLSTS0HH RSCAN0.THLSTS0.UINT8[HH]
#define RSCAN0THLSTS1 RSCAN0.THLSTS1.UINT32
#define RSCAN0THLSTS1L RSCAN0.THLSTS1.UINT16[L]
#define RSCAN0THLSTS1LL RSCAN0.THLSTS1.UINT8[LL]
#define RSCAN0THLSTS1LH RSCAN0.THLSTS1.UINT8[LH]
#define RSCAN0THLSTS1H RSCAN0.THLSTS1.UINT16[H]
#define RSCAN0THLSTS1HL RSCAN0.THLSTS1.UINT8[HL]
#define RSCAN0THLSTS1HH RSCAN0.THLSTS1.UINT8[HH]
#define RSCAN0THLSTS2 RSCAN0.THLSTS2.UINT32
#define RSCAN0THLSTS2L RSCAN0.THLSTS2.UINT16[L]
#define RSCAN0THLSTS2LL RSCAN0.THLSTS2.UINT8[LL]
#define RSCAN0THLSTS2LH RSCAN0.THLSTS2.UINT8[LH]
#define RSCAN0THLSTS2H RSCAN0.THLSTS2.UINT16[H]
#define RSCAN0THLSTS2HL RSCAN0.THLSTS2.UINT8[HL]
#define RSCAN0THLSTS2HH RSCAN0.THLSTS2.UINT8[HH]
#define RSCAN0THLPCTR0 RSCAN0.THLPCTR0.UINT32
#define RSCAN0THLPCTR0L RSCAN0.THLPCTR0.UINT16[L]
#define RSCAN0THLPCTR0LL RSCAN0.THLPCTR0.UINT8[LL]
#define RSCAN0THLPCTR0LH RSCAN0.THLPCTR0.UINT8[LH]
#define RSCAN0THLPCTR0H RSCAN0.THLPCTR0.UINT16[H]
#define RSCAN0THLPCTR0HL RSCAN0.THLPCTR0.UINT8[HL]
#define RSCAN0THLPCTR0HH RSCAN0.THLPCTR0.UINT8[HH]
#define RSCAN0THLPCTR1 RSCAN0.THLPCTR1.UINT32
#define RSCAN0THLPCTR1L RSCAN0.THLPCTR1.UINT16[L]
#define RSCAN0THLPCTR1LL RSCAN0.THLPCTR1.UINT8[LL]
#define RSCAN0THLPCTR1LH RSCAN0.THLPCTR1.UINT8[LH]
#define RSCAN0THLPCTR1H RSCAN0.THLPCTR1.UINT16[H]
#define RSCAN0THLPCTR1HL RSCAN0.THLPCTR1.UINT8[HL]
#define RSCAN0THLPCTR1HH RSCAN0.THLPCTR1.UINT8[HH]
#define RSCAN0THLPCTR2 RSCAN0.THLPCTR2.UINT32
#define RSCAN0THLPCTR2L RSCAN0.THLPCTR2.UINT16[L]
#define RSCAN0THLPCTR2LL RSCAN0.THLPCTR2.UINT8[LL]
#define RSCAN0THLPCTR2LH RSCAN0.THLPCTR2.UINT8[LH]
#define RSCAN0THLPCTR2H RSCAN0.THLPCTR2.UINT16[H]
#define RSCAN0THLPCTR2HL RSCAN0.THLPCTR2.UINT8[HL]
#define RSCAN0THLPCTR2HH RSCAN0.THLPCTR2.UINT8[HH]
#define RSCAN0GTINTSTS0 RSCAN0.GTINTSTS0.UINT32
#define RSCAN0GTINTSTS0L RSCAN0.GTINTSTS0.UINT16[L]
#define RSCAN0GTINTSTS0LL RSCAN0.GTINTSTS0.UINT8[LL]
#define RSCAN0GTINTSTS0LH RSCAN0.GTINTSTS0.UINT8[LH]
#define RSCAN0GTINTSTS0H RSCAN0.GTINTSTS0.UINT16[H]
#define RSCAN0GTINTSTS0HL RSCAN0.GTINTSTS0.UINT8[HL]
#define RSCAN0GTSTCFG RSCAN0.GTSTCFG.UINT32
#define RSCAN0GTSTCFGL RSCAN0.GTSTCFG.UINT16[L]
#define RSCAN0GTSTCFGLL RSCAN0.GTSTCFG.UINT8[LL]
#define RSCAN0GTSTCFGLH RSCAN0.GTSTCFG.UINT8[LH]
#define RSCAN0GTSTCFGH RSCAN0.GTSTCFG.UINT16[H]
#define RSCAN0GTSTCFGHL RSCAN0.GTSTCFG.UINT8[HL]
#define RSCAN0GTSTCFGHH RSCAN0.GTSTCFG.UINT8[HH]
#define RSCAN0GTSTCTR RSCAN0.GTSTCTR.UINT32
#define RSCAN0GTSTCTRL RSCAN0.GTSTCTR.UINT16[L]
#define RSCAN0GTSTCTRLL RSCAN0.GTSTCTR.UINT8[LL]
#define RSCAN0GTSTCTRLH RSCAN0.GTSTCTR.UINT8[LH]
#define RSCAN0GTSTCTRH RSCAN0.GTSTCTR.UINT16[H]
#define RSCAN0GTSTCTRHL RSCAN0.GTSTCTR.UINT8[HL]
#define RSCAN0GTSTCTRHH RSCAN0.GTSTCTR.UINT8[HH]
#define RSCAN0GLOCKK RSCAN0.GLOCKK.UINT32
#define RSCAN0GLOCKKL RSCAN0.GLOCKK.UINT16[L]
#define RSCAN0GLOCKKH RSCAN0.GLOCKK.UINT16[H]
#define RSCAN0GAFLID0 RSCAN0.GAFLID0.UINT32
#define RSCAN0GAFLID0L RSCAN0.GAFLID0.UINT16[L]
#define RSCAN0GAFLID0LL RSCAN0.GAFLID0.UINT8[LL]
#define RSCAN0GAFLID0LH RSCAN0.GAFLID0.UINT8[LH]
#define RSCAN0GAFLID0H RSCAN0.GAFLID0.UINT16[H]
#define RSCAN0GAFLID0HL RSCAN0.GAFLID0.UINT8[HL]
#define RSCAN0GAFLID0HH RSCAN0.GAFLID0.UINT8[HH]
#define RSCAN0GAFLM0 RSCAN0.GAFLM0.UINT32
#define RSCAN0GAFLM0L RSCAN0.GAFLM0.UINT16[L]
#define RSCAN0GAFLM0LL RSCAN0.GAFLM0.UINT8[LL]
#define RSCAN0GAFLM0LH RSCAN0.GAFLM0.UINT8[LH]
#define RSCAN0GAFLM0H RSCAN0.GAFLM0.UINT16[H]
#define RSCAN0GAFLM0HL RSCAN0.GAFLM0.UINT8[HL]
#define RSCAN0GAFLM0HH RSCAN0.GAFLM0.UINT8[HH]
#define RSCAN0GAFLP00 RSCAN0.GAFLP00.UINT32
#define RSCAN0GAFLP00L RSCAN0.GAFLP00.UINT16[L]
#define RSCAN0GAFLP00LL RSCAN0.GAFLP00.UINT8[LL]
#define RSCAN0GAFLP00LH RSCAN0.GAFLP00.UINT8[LH]
#define RSCAN0GAFLP00H RSCAN0.GAFLP00.UINT16[H]
#define RSCAN0GAFLP00HL RSCAN0.GAFLP00.UINT8[HL]
#define RSCAN0GAFLP00HH RSCAN0.GAFLP00.UINT8[HH]
#define RSCAN0GAFLP10 RSCAN0.GAFLP10.UINT32
#define RSCAN0GAFLP10L RSCAN0.GAFLP10.UINT16[L]
#define RSCAN0GAFLP10LL RSCAN0.GAFLP10.UINT8[LL]
#define RSCAN0GAFLP10LH RSCAN0.GAFLP10.UINT8[LH]
#define RSCAN0GAFLP10H RSCAN0.GAFLP10.UINT16[H]
#define RSCAN0GAFLP10HL RSCAN0.GAFLP10.UINT8[HL]
#define RSCAN0GAFLID1 RSCAN0.GAFLID1.UINT32
#define RSCAN0GAFLID1L RSCAN0.GAFLID1.UINT16[L]
#define RSCAN0GAFLID1LL RSCAN0.GAFLID1.UINT8[LL]
#define RSCAN0GAFLID1LH RSCAN0.GAFLID1.UINT8[LH]
#define RSCAN0GAFLID1H RSCAN0.GAFLID1.UINT16[H]
#define RSCAN0GAFLID1HL RSCAN0.GAFLID1.UINT8[HL]
#define RSCAN0GAFLID1HH RSCAN0.GAFLID1.UINT8[HH]
#define RSCAN0GAFLM1 RSCAN0.GAFLM1.UINT32
#define RSCAN0GAFLM1L RSCAN0.GAFLM1.UINT16[L]
#define RSCAN0GAFLM1LL RSCAN0.GAFLM1.UINT8[LL]
#define RSCAN0GAFLM1LH RSCAN0.GAFLM1.UINT8[LH]
#define RSCAN0GAFLM1H RSCAN0.GAFLM1.UINT16[H]
#define RSCAN0GAFLM1HL RSCAN0.GAFLM1.UINT8[HL]
#define RSCAN0GAFLM1HH RSCAN0.GAFLM1.UINT8[HH]
#define RSCAN0GAFLP01 RSCAN0.GAFLP01.UINT32
#define RSCAN0GAFLP01L RSCAN0.GAFLP01.UINT16[L]
#define RSCAN0GAFLP01LL RSCAN0.GAFLP01.UINT8[LL]
#define RSCAN0GAFLP01LH RSCAN0.GAFLP01.UINT8[LH]
#define RSCAN0GAFLP01H RSCAN0.GAFLP01.UINT16[H]
#define RSCAN0GAFLP01HL RSCAN0.GAFLP01.UINT8[HL]
#define RSCAN0GAFLP01HH RSCAN0.GAFLP01.UINT8[HH]
#define RSCAN0GAFLP11 RSCAN0.GAFLP11.UINT32
#define RSCAN0GAFLP11L RSCAN0.GAFLP11.UINT16[L]
#define RSCAN0GAFLP11LL RSCAN0.GAFLP11.UINT8[LL]
#define RSCAN0GAFLP11LH RSCAN0.GAFLP11.UINT8[LH]
#define RSCAN0GAFLP11H RSCAN0.GAFLP11.UINT16[H]
#define RSCAN0GAFLP11HL RSCAN0.GAFLP11.UINT8[HL]
#define RSCAN0GAFLID2 RSCAN0.GAFLID2.UINT32
#define RSCAN0GAFLID2L RSCAN0.GAFLID2.UINT16[L]
#define RSCAN0GAFLID2LL RSCAN0.GAFLID2.UINT8[LL]
#define RSCAN0GAFLID2LH RSCAN0.GAFLID2.UINT8[LH]
#define RSCAN0GAFLID2H RSCAN0.GAFLID2.UINT16[H]
#define RSCAN0GAFLID2HL RSCAN0.GAFLID2.UINT8[HL]
#define RSCAN0GAFLID2HH RSCAN0.GAFLID2.UINT8[HH]
#define RSCAN0GAFLM2 RSCAN0.GAFLM2.UINT32
#define RSCAN0GAFLM2L RSCAN0.GAFLM2.UINT16[L]
#define RSCAN0GAFLM2LL RSCAN0.GAFLM2.UINT8[LL]
#define RSCAN0GAFLM2LH RSCAN0.GAFLM2.UINT8[LH]
#define RSCAN0GAFLM2H RSCAN0.GAFLM2.UINT16[H]
#define RSCAN0GAFLM2HL RSCAN0.GAFLM2.UINT8[HL]
#define RSCAN0GAFLM2HH RSCAN0.GAFLM2.UINT8[HH]
#define RSCAN0GAFLP02 RSCAN0.GAFLP02.UINT32
#define RSCAN0GAFLP02L RSCAN0.GAFLP02.UINT16[L]
#define RSCAN0GAFLP02LL RSCAN0.GAFLP02.UINT8[LL]
#define RSCAN0GAFLP02LH RSCAN0.GAFLP02.UINT8[LH]
#define RSCAN0GAFLP02H RSCAN0.GAFLP02.UINT16[H]
#define RSCAN0GAFLP02HL RSCAN0.GAFLP02.UINT8[HL]
#define RSCAN0GAFLP02HH RSCAN0.GAFLP02.UINT8[HH]
#define RSCAN0GAFLP12 RSCAN0.GAFLP12.UINT32
#define RSCAN0GAFLP12L RSCAN0.GAFLP12.UINT16[L]
#define RSCAN0GAFLP12LL RSCAN0.GAFLP12.UINT8[LL]
#define RSCAN0GAFLP12LH RSCAN0.GAFLP12.UINT8[LH]
#define RSCAN0GAFLP12H RSCAN0.GAFLP12.UINT16[H]
#define RSCAN0GAFLP12HL RSCAN0.GAFLP12.UINT8[HL]
#define RSCAN0GAFLID3 RSCAN0.GAFLID3.UINT32
#define RSCAN0GAFLID3L RSCAN0.GAFLID3.UINT16[L]
#define RSCAN0GAFLID3LL RSCAN0.GAFLID3.UINT8[LL]
#define RSCAN0GAFLID3LH RSCAN0.GAFLID3.UINT8[LH]
#define RSCAN0GAFLID3H RSCAN0.GAFLID3.UINT16[H]
#define RSCAN0GAFLID3HL RSCAN0.GAFLID3.UINT8[HL]
#define RSCAN0GAFLID3HH RSCAN0.GAFLID3.UINT8[HH]
#define RSCAN0GAFLM3 RSCAN0.GAFLM3.UINT32
#define RSCAN0GAFLM3L RSCAN0.GAFLM3.UINT16[L]
#define RSCAN0GAFLM3LL RSCAN0.GAFLM3.UINT8[LL]
#define RSCAN0GAFLM3LH RSCAN0.GAFLM3.UINT8[LH]
#define RSCAN0GAFLM3H RSCAN0.GAFLM3.UINT16[H]
#define RSCAN0GAFLM3HL RSCAN0.GAFLM3.UINT8[HL]
#define RSCAN0GAFLM3HH RSCAN0.GAFLM3.UINT8[HH]
#define RSCAN0GAFLP03 RSCAN0.GAFLP03.UINT32
#define RSCAN0GAFLP03L RSCAN0.GAFLP03.UINT16[L]
#define RSCAN0GAFLP03LL RSCAN0.GAFLP03.UINT8[LL]
#define RSCAN0GAFLP03LH RSCAN0.GAFLP03.UINT8[LH]
#define RSCAN0GAFLP03H RSCAN0.GAFLP03.UINT16[H]
#define RSCAN0GAFLP03HL RSCAN0.GAFLP03.UINT8[HL]
#define RSCAN0GAFLP03HH RSCAN0.GAFLP03.UINT8[HH]
#define RSCAN0GAFLP13 RSCAN0.GAFLP13.UINT32
#define RSCAN0GAFLP13L RSCAN0.GAFLP13.UINT16[L]
#define RSCAN0GAFLP13LL RSCAN0.GAFLP13.UINT8[LL]
#define RSCAN0GAFLP13LH RSCAN0.GAFLP13.UINT8[LH]
#define RSCAN0GAFLP13H RSCAN0.GAFLP13.UINT16[H]
#define RSCAN0GAFLP13HL RSCAN0.GAFLP13.UINT8[HL]
#define RSCAN0GAFLID4 RSCAN0.GAFLID4.UINT32
#define RSCAN0GAFLID4L RSCAN0.GAFLID4.UINT16[L]
#define RSCAN0GAFLID4LL RSCAN0.GAFLID4.UINT8[LL]
#define RSCAN0GAFLID4LH RSCAN0.GAFLID4.UINT8[LH]
#define RSCAN0GAFLID4H RSCAN0.GAFLID4.UINT16[H]
#define RSCAN0GAFLID4HL RSCAN0.GAFLID4.UINT8[HL]
#define RSCAN0GAFLID4HH RSCAN0.GAFLID4.UINT8[HH]
#define RSCAN0GAFLM4 RSCAN0.GAFLM4.UINT32
#define RSCAN0GAFLM4L RSCAN0.GAFLM4.UINT16[L]
#define RSCAN0GAFLM4LL RSCAN0.GAFLM4.UINT8[LL]
#define RSCAN0GAFLM4LH RSCAN0.GAFLM4.UINT8[LH]
#define RSCAN0GAFLM4H RSCAN0.GAFLM4.UINT16[H]
#define RSCAN0GAFLM4HL RSCAN0.GAFLM4.UINT8[HL]
#define RSCAN0GAFLM4HH RSCAN0.GAFLM4.UINT8[HH]
#define RSCAN0GAFLP04 RSCAN0.GAFLP04.UINT32
#define RSCAN0GAFLP04L RSCAN0.GAFLP04.UINT16[L]
#define RSCAN0GAFLP04LL RSCAN0.GAFLP04.UINT8[LL]
#define RSCAN0GAFLP04LH RSCAN0.GAFLP04.UINT8[LH]
#define RSCAN0GAFLP04H RSCAN0.GAFLP04.UINT16[H]
#define RSCAN0GAFLP04HL RSCAN0.GAFLP04.UINT8[HL]
#define RSCAN0GAFLP04HH RSCAN0.GAFLP04.UINT8[HH]
#define RSCAN0GAFLP14 RSCAN0.GAFLP14.UINT32
#define RSCAN0GAFLP14L RSCAN0.GAFLP14.UINT16[L]
#define RSCAN0GAFLP14LL RSCAN0.GAFLP14.UINT8[LL]
#define RSCAN0GAFLP14LH RSCAN0.GAFLP14.UINT8[LH]
#define RSCAN0GAFLP14H RSCAN0.GAFLP14.UINT16[H]
#define RSCAN0GAFLP14HL RSCAN0.GAFLP14.UINT8[HL]
#define RSCAN0GAFLID5 RSCAN0.GAFLID5.UINT32
#define RSCAN0GAFLID5L RSCAN0.GAFLID5.UINT16[L]
#define RSCAN0GAFLID5LL RSCAN0.GAFLID5.UINT8[LL]
#define RSCAN0GAFLID5LH RSCAN0.GAFLID5.UINT8[LH]
#define RSCAN0GAFLID5H RSCAN0.GAFLID5.UINT16[H]
#define RSCAN0GAFLID5HL RSCAN0.GAFLID5.UINT8[HL]
#define RSCAN0GAFLID5HH RSCAN0.GAFLID5.UINT8[HH]
#define RSCAN0GAFLM5 RSCAN0.GAFLM5.UINT32
#define RSCAN0GAFLM5L RSCAN0.GAFLM5.UINT16[L]
#define RSCAN0GAFLM5LL RSCAN0.GAFLM5.UINT8[LL]
#define RSCAN0GAFLM5LH RSCAN0.GAFLM5.UINT8[LH]
#define RSCAN0GAFLM5H RSCAN0.GAFLM5.UINT16[H]
#define RSCAN0GAFLM5HL RSCAN0.GAFLM5.UINT8[HL]
#define RSCAN0GAFLM5HH RSCAN0.GAFLM5.UINT8[HH]
#define RSCAN0GAFLP05 RSCAN0.GAFLP05.UINT32
#define RSCAN0GAFLP05L RSCAN0.GAFLP05.UINT16[L]
#define RSCAN0GAFLP05LL RSCAN0.GAFLP05.UINT8[LL]
#define RSCAN0GAFLP05LH RSCAN0.GAFLP05.UINT8[LH]
#define RSCAN0GAFLP05H RSCAN0.GAFLP05.UINT16[H]
#define RSCAN0GAFLP05HL RSCAN0.GAFLP05.UINT8[HL]
#define RSCAN0GAFLP05HH RSCAN0.GAFLP05.UINT8[HH]
#define RSCAN0GAFLP15 RSCAN0.GAFLP15.UINT32
#define RSCAN0GAFLP15L RSCAN0.GAFLP15.UINT16[L]
#define RSCAN0GAFLP15LL RSCAN0.GAFLP15.UINT8[LL]
#define RSCAN0GAFLP15LH RSCAN0.GAFLP15.UINT8[LH]
#define RSCAN0GAFLP15H RSCAN0.GAFLP15.UINT16[H]
#define RSCAN0GAFLP15HL RSCAN0.GAFLP15.UINT8[HL]
#define RSCAN0GAFLID6 RSCAN0.GAFLID6.UINT32
#define RSCAN0GAFLID6L RSCAN0.GAFLID6.UINT16[L]
#define RSCAN0GAFLID6LL RSCAN0.GAFLID6.UINT8[LL]
#define RSCAN0GAFLID6LH RSCAN0.GAFLID6.UINT8[LH]
#define RSCAN0GAFLID6H RSCAN0.GAFLID6.UINT16[H]
#define RSCAN0GAFLID6HL RSCAN0.GAFLID6.UINT8[HL]
#define RSCAN0GAFLID6HH RSCAN0.GAFLID6.UINT8[HH]
#define RSCAN0GAFLM6 RSCAN0.GAFLM6.UINT32
#define RSCAN0GAFLM6L RSCAN0.GAFLM6.UINT16[L]
#define RSCAN0GAFLM6LL RSCAN0.GAFLM6.UINT8[LL]
#define RSCAN0GAFLM6LH RSCAN0.GAFLM6.UINT8[LH]
#define RSCAN0GAFLM6H RSCAN0.GAFLM6.UINT16[H]
#define RSCAN0GAFLM6HL RSCAN0.GAFLM6.UINT8[HL]
#define RSCAN0GAFLM6HH RSCAN0.GAFLM6.UINT8[HH]
#define RSCAN0GAFLP06 RSCAN0.GAFLP06.UINT32
#define RSCAN0GAFLP06L RSCAN0.GAFLP06.UINT16[L]
#define RSCAN0GAFLP06LL RSCAN0.GAFLP06.UINT8[LL]
#define RSCAN0GAFLP06LH RSCAN0.GAFLP06.UINT8[LH]
#define RSCAN0GAFLP06H RSCAN0.GAFLP06.UINT16[H]
#define RSCAN0GAFLP06HL RSCAN0.GAFLP06.UINT8[HL]
#define RSCAN0GAFLP06HH RSCAN0.GAFLP06.UINT8[HH]
#define RSCAN0GAFLP16 RSCAN0.GAFLP16.UINT32
#define RSCAN0GAFLP16L RSCAN0.GAFLP16.UINT16[L]
#define RSCAN0GAFLP16LL RSCAN0.GAFLP16.UINT8[LL]
#define RSCAN0GAFLP16LH RSCAN0.GAFLP16.UINT8[LH]
#define RSCAN0GAFLP16H RSCAN0.GAFLP16.UINT16[H]
#define RSCAN0GAFLP16HL RSCAN0.GAFLP16.UINT8[HL]
#define RSCAN0GAFLID7 RSCAN0.GAFLID7.UINT32
#define RSCAN0GAFLID7L RSCAN0.GAFLID7.UINT16[L]
#define RSCAN0GAFLID7LL RSCAN0.GAFLID7.UINT8[LL]
#define RSCAN0GAFLID7LH RSCAN0.GAFLID7.UINT8[LH]
#define RSCAN0GAFLID7H RSCAN0.GAFLID7.UINT16[H]
#define RSCAN0GAFLID7HL RSCAN0.GAFLID7.UINT8[HL]
#define RSCAN0GAFLID7HH RSCAN0.GAFLID7.UINT8[HH]
#define RSCAN0GAFLM7 RSCAN0.GAFLM7.UINT32
#define RSCAN0GAFLM7L RSCAN0.GAFLM7.UINT16[L]
#define RSCAN0GAFLM7LL RSCAN0.GAFLM7.UINT8[LL]
#define RSCAN0GAFLM7LH RSCAN0.GAFLM7.UINT8[LH]
#define RSCAN0GAFLM7H RSCAN0.GAFLM7.UINT16[H]
#define RSCAN0GAFLM7HL RSCAN0.GAFLM7.UINT8[HL]
#define RSCAN0GAFLM7HH RSCAN0.GAFLM7.UINT8[HH]
#define RSCAN0GAFLP07 RSCAN0.GAFLP07.UINT32
#define RSCAN0GAFLP07L RSCAN0.GAFLP07.UINT16[L]
#define RSCAN0GAFLP07LL RSCAN0.GAFLP07.UINT8[LL]
#define RSCAN0GAFLP07LH RSCAN0.GAFLP07.UINT8[LH]
#define RSCAN0GAFLP07H RSCAN0.GAFLP07.UINT16[H]
#define RSCAN0GAFLP07HL RSCAN0.GAFLP07.UINT8[HL]
#define RSCAN0GAFLP07HH RSCAN0.GAFLP07.UINT8[HH]
#define RSCAN0GAFLP17 RSCAN0.GAFLP17.UINT32
#define RSCAN0GAFLP17L RSCAN0.GAFLP17.UINT16[L]
#define RSCAN0GAFLP17LL RSCAN0.GAFLP17.UINT8[LL]
#define RSCAN0GAFLP17LH RSCAN0.GAFLP17.UINT8[LH]
#define RSCAN0GAFLP17H RSCAN0.GAFLP17.UINT16[H]
#define RSCAN0GAFLP17HL RSCAN0.GAFLP17.UINT8[HL]
#define RSCAN0GAFLID8 RSCAN0.GAFLID8.UINT32
#define RSCAN0GAFLID8L RSCAN0.GAFLID8.UINT16[L]
#define RSCAN0GAFLID8LL RSCAN0.GAFLID8.UINT8[LL]
#define RSCAN0GAFLID8LH RSCAN0.GAFLID8.UINT8[LH]
#define RSCAN0GAFLID8H RSCAN0.GAFLID8.UINT16[H]
#define RSCAN0GAFLID8HL RSCAN0.GAFLID8.UINT8[HL]
#define RSCAN0GAFLID8HH RSCAN0.GAFLID8.UINT8[HH]
#define RSCAN0GAFLM8 RSCAN0.GAFLM8.UINT32
#define RSCAN0GAFLM8L RSCAN0.GAFLM8.UINT16[L]
#define RSCAN0GAFLM8LL RSCAN0.GAFLM8.UINT8[LL]
#define RSCAN0GAFLM8LH RSCAN0.GAFLM8.UINT8[LH]
#define RSCAN0GAFLM8H RSCAN0.GAFLM8.UINT16[H]
#define RSCAN0GAFLM8HL RSCAN0.GAFLM8.UINT8[HL]
#define RSCAN0GAFLM8HH RSCAN0.GAFLM8.UINT8[HH]
#define RSCAN0GAFLP08 RSCAN0.GAFLP08.UINT32
#define RSCAN0GAFLP08L RSCAN0.GAFLP08.UINT16[L]
#define RSCAN0GAFLP08LL RSCAN0.GAFLP08.UINT8[LL]
#define RSCAN0GAFLP08LH RSCAN0.GAFLP08.UINT8[LH]
#define RSCAN0GAFLP08H RSCAN0.GAFLP08.UINT16[H]
#define RSCAN0GAFLP08HL RSCAN0.GAFLP08.UINT8[HL]
#define RSCAN0GAFLP08HH RSCAN0.GAFLP08.UINT8[HH]
#define RSCAN0GAFLP18 RSCAN0.GAFLP18.UINT32
#define RSCAN0GAFLP18L RSCAN0.GAFLP18.UINT16[L]
#define RSCAN0GAFLP18LL RSCAN0.GAFLP18.UINT8[LL]
#define RSCAN0GAFLP18LH RSCAN0.GAFLP18.UINT8[LH]
#define RSCAN0GAFLP18H RSCAN0.GAFLP18.UINT16[H]
#define RSCAN0GAFLP18HL RSCAN0.GAFLP18.UINT8[HL]
#define RSCAN0GAFLID9 RSCAN0.GAFLID9.UINT32
#define RSCAN0GAFLID9L RSCAN0.GAFLID9.UINT16[L]
#define RSCAN0GAFLID9LL RSCAN0.GAFLID9.UINT8[LL]
#define RSCAN0GAFLID9LH RSCAN0.GAFLID9.UINT8[LH]
#define RSCAN0GAFLID9H RSCAN0.GAFLID9.UINT16[H]
#define RSCAN0GAFLID9HL RSCAN0.GAFLID9.UINT8[HL]
#define RSCAN0GAFLID9HH RSCAN0.GAFLID9.UINT8[HH]
#define RSCAN0GAFLM9 RSCAN0.GAFLM9.UINT32
#define RSCAN0GAFLM9L RSCAN0.GAFLM9.UINT16[L]
#define RSCAN0GAFLM9LL RSCAN0.GAFLM9.UINT8[LL]
#define RSCAN0GAFLM9LH RSCAN0.GAFLM9.UINT8[LH]
#define RSCAN0GAFLM9H RSCAN0.GAFLM9.UINT16[H]
#define RSCAN0GAFLM9HL RSCAN0.GAFLM9.UINT8[HL]
#define RSCAN0GAFLM9HH RSCAN0.GAFLM9.UINT8[HH]
#define RSCAN0GAFLP09 RSCAN0.GAFLP09.UINT32
#define RSCAN0GAFLP09L RSCAN0.GAFLP09.UINT16[L]
#define RSCAN0GAFLP09LL RSCAN0.GAFLP09.UINT8[LL]
#define RSCAN0GAFLP09LH RSCAN0.GAFLP09.UINT8[LH]
#define RSCAN0GAFLP09H RSCAN0.GAFLP09.UINT16[H]
#define RSCAN0GAFLP09HL RSCAN0.GAFLP09.UINT8[HL]
#define RSCAN0GAFLP09HH RSCAN0.GAFLP09.UINT8[HH]
#define RSCAN0GAFLP19 RSCAN0.GAFLP19.UINT32
#define RSCAN0GAFLP19L RSCAN0.GAFLP19.UINT16[L]
#define RSCAN0GAFLP19LL RSCAN0.GAFLP19.UINT8[LL]
#define RSCAN0GAFLP19LH RSCAN0.GAFLP19.UINT8[LH]
#define RSCAN0GAFLP19H RSCAN0.GAFLP19.UINT16[H]
#define RSCAN0GAFLP19HL RSCAN0.GAFLP19.UINT8[HL]
#define RSCAN0GAFLID10 RSCAN0.GAFLID10.UINT32
#define RSCAN0GAFLID10L RSCAN0.GAFLID10.UINT16[L]
#define RSCAN0GAFLID10LL RSCAN0.GAFLID10.UINT8[LL]
#define RSCAN0GAFLID10LH RSCAN0.GAFLID10.UINT8[LH]
#define RSCAN0GAFLID10H RSCAN0.GAFLID10.UINT16[H]
#define RSCAN0GAFLID10HL RSCAN0.GAFLID10.UINT8[HL]
#define RSCAN0GAFLID10HH RSCAN0.GAFLID10.UINT8[HH]
#define RSCAN0GAFLM10 RSCAN0.GAFLM10.UINT32
#define RSCAN0GAFLM10L RSCAN0.GAFLM10.UINT16[L]
#define RSCAN0GAFLM10LL RSCAN0.GAFLM10.UINT8[LL]
#define RSCAN0GAFLM10LH RSCAN0.GAFLM10.UINT8[LH]
#define RSCAN0GAFLM10H RSCAN0.GAFLM10.UINT16[H]
#define RSCAN0GAFLM10HL RSCAN0.GAFLM10.UINT8[HL]
#define RSCAN0GAFLM10HH RSCAN0.GAFLM10.UINT8[HH]
#define RSCAN0GAFLP010 RSCAN0.GAFLP010.UINT32
#define RSCAN0GAFLP010L RSCAN0.GAFLP010.UINT16[L]
#define RSCAN0GAFLP010LL RSCAN0.GAFLP010.UINT8[LL]
#define RSCAN0GAFLP010LH RSCAN0.GAFLP010.UINT8[LH]
#define RSCAN0GAFLP010H RSCAN0.GAFLP010.UINT16[H]
#define RSCAN0GAFLP010HL RSCAN0.GAFLP010.UINT8[HL]
#define RSCAN0GAFLP010HH RSCAN0.GAFLP010.UINT8[HH]
#define RSCAN0GAFLP110 RSCAN0.GAFLP110.UINT32
#define RSCAN0GAFLP110L RSCAN0.GAFLP110.UINT16[L]
#define RSCAN0GAFLP110LL RSCAN0.GAFLP110.UINT8[LL]
#define RSCAN0GAFLP110LH RSCAN0.GAFLP110.UINT8[LH]
#define RSCAN0GAFLP110H RSCAN0.GAFLP110.UINT16[H]
#define RSCAN0GAFLP110HL RSCAN0.GAFLP110.UINT8[HL]
#define RSCAN0GAFLID11 RSCAN0.GAFLID11.UINT32
#define RSCAN0GAFLID11L RSCAN0.GAFLID11.UINT16[L]
#define RSCAN0GAFLID11LL RSCAN0.GAFLID11.UINT8[LL]
#define RSCAN0GAFLID11LH RSCAN0.GAFLID11.UINT8[LH]
#define RSCAN0GAFLID11H RSCAN0.GAFLID11.UINT16[H]
#define RSCAN0GAFLID11HL RSCAN0.GAFLID11.UINT8[HL]
#define RSCAN0GAFLID11HH RSCAN0.GAFLID11.UINT8[HH]
#define RSCAN0GAFLM11 RSCAN0.GAFLM11.UINT32
#define RSCAN0GAFLM11L RSCAN0.GAFLM11.UINT16[L]
#define RSCAN0GAFLM11LL RSCAN0.GAFLM11.UINT8[LL]
#define RSCAN0GAFLM11LH RSCAN0.GAFLM11.UINT8[LH]
#define RSCAN0GAFLM11H RSCAN0.GAFLM11.UINT16[H]
#define RSCAN0GAFLM11HL RSCAN0.GAFLM11.UINT8[HL]
#define RSCAN0GAFLM11HH RSCAN0.GAFLM11.UINT8[HH]
#define RSCAN0GAFLP011 RSCAN0.GAFLP011.UINT32
#define RSCAN0GAFLP011L RSCAN0.GAFLP011.UINT16[L]
#define RSCAN0GAFLP011LL RSCAN0.GAFLP011.UINT8[LL]
#define RSCAN0GAFLP011LH RSCAN0.GAFLP011.UINT8[LH]
#define RSCAN0GAFLP011H RSCAN0.GAFLP011.UINT16[H]
#define RSCAN0GAFLP011HL RSCAN0.GAFLP011.UINT8[HL]
#define RSCAN0GAFLP011HH RSCAN0.GAFLP011.UINT8[HH]
#define RSCAN0GAFLP111 RSCAN0.GAFLP111.UINT32
#define RSCAN0GAFLP111L RSCAN0.GAFLP111.UINT16[L]
#define RSCAN0GAFLP111LL RSCAN0.GAFLP111.UINT8[LL]
#define RSCAN0GAFLP111LH RSCAN0.GAFLP111.UINT8[LH]
#define RSCAN0GAFLP111H RSCAN0.GAFLP111.UINT16[H]
#define RSCAN0GAFLP111HL RSCAN0.GAFLP111.UINT8[HL]
#define RSCAN0GAFLID12 RSCAN0.GAFLID12.UINT32
#define RSCAN0GAFLID12L RSCAN0.GAFLID12.UINT16[L]
#define RSCAN0GAFLID12LL RSCAN0.GAFLID12.UINT8[LL]
#define RSCAN0GAFLID12LH RSCAN0.GAFLID12.UINT8[LH]
#define RSCAN0GAFLID12H RSCAN0.GAFLID12.UINT16[H]
#define RSCAN0GAFLID12HL RSCAN0.GAFLID12.UINT8[HL]
#define RSCAN0GAFLID12HH RSCAN0.GAFLID12.UINT8[HH]
#define RSCAN0GAFLM12 RSCAN0.GAFLM12.UINT32
#define RSCAN0GAFLM12L RSCAN0.GAFLM12.UINT16[L]
#define RSCAN0GAFLM12LL RSCAN0.GAFLM12.UINT8[LL]
#define RSCAN0GAFLM12LH RSCAN0.GAFLM12.UINT8[LH]
#define RSCAN0GAFLM12H RSCAN0.GAFLM12.UINT16[H]
#define RSCAN0GAFLM12HL RSCAN0.GAFLM12.UINT8[HL]
#define RSCAN0GAFLM12HH RSCAN0.GAFLM12.UINT8[HH]
#define RSCAN0GAFLP012 RSCAN0.GAFLP012.UINT32
#define RSCAN0GAFLP012L RSCAN0.GAFLP012.UINT16[L]
#define RSCAN0GAFLP012LL RSCAN0.GAFLP012.UINT8[LL]
#define RSCAN0GAFLP012LH RSCAN0.GAFLP012.UINT8[LH]
#define RSCAN0GAFLP012H RSCAN0.GAFLP012.UINT16[H]
#define RSCAN0GAFLP012HL RSCAN0.GAFLP012.UINT8[HL]
#define RSCAN0GAFLP012HH RSCAN0.GAFLP012.UINT8[HH]
#define RSCAN0GAFLP112 RSCAN0.GAFLP112.UINT32
#define RSCAN0GAFLP112L RSCAN0.GAFLP112.UINT16[L]
#define RSCAN0GAFLP112LL RSCAN0.GAFLP112.UINT8[LL]
#define RSCAN0GAFLP112LH RSCAN0.GAFLP112.UINT8[LH]
#define RSCAN0GAFLP112H RSCAN0.GAFLP112.UINT16[H]
#define RSCAN0GAFLP112HL RSCAN0.GAFLP112.UINT8[HL]
#define RSCAN0GAFLID13 RSCAN0.GAFLID13.UINT32
#define RSCAN0GAFLID13L RSCAN0.GAFLID13.UINT16[L]
#define RSCAN0GAFLID13LL RSCAN0.GAFLID13.UINT8[LL]
#define RSCAN0GAFLID13LH RSCAN0.GAFLID13.UINT8[LH]
#define RSCAN0GAFLID13H RSCAN0.GAFLID13.UINT16[H]
#define RSCAN0GAFLID13HL RSCAN0.GAFLID13.UINT8[HL]
#define RSCAN0GAFLID13HH RSCAN0.GAFLID13.UINT8[HH]
#define RSCAN0GAFLM13 RSCAN0.GAFLM13.UINT32
#define RSCAN0GAFLM13L RSCAN0.GAFLM13.UINT16[L]
#define RSCAN0GAFLM13LL RSCAN0.GAFLM13.UINT8[LL]
#define RSCAN0GAFLM13LH RSCAN0.GAFLM13.UINT8[LH]
#define RSCAN0GAFLM13H RSCAN0.GAFLM13.UINT16[H]
#define RSCAN0GAFLM13HL RSCAN0.GAFLM13.UINT8[HL]
#define RSCAN0GAFLM13HH RSCAN0.GAFLM13.UINT8[HH]
#define RSCAN0GAFLP013 RSCAN0.GAFLP013.UINT32
#define RSCAN0GAFLP013L RSCAN0.GAFLP013.UINT16[L]
#define RSCAN0GAFLP013LL RSCAN0.GAFLP013.UINT8[LL]
#define RSCAN0GAFLP013LH RSCAN0.GAFLP013.UINT8[LH]
#define RSCAN0GAFLP013H RSCAN0.GAFLP013.UINT16[H]
#define RSCAN0GAFLP013HL RSCAN0.GAFLP013.UINT8[HL]
#define RSCAN0GAFLP013HH RSCAN0.GAFLP013.UINT8[HH]
#define RSCAN0GAFLP113 RSCAN0.GAFLP113.UINT32
#define RSCAN0GAFLP113L RSCAN0.GAFLP113.UINT16[L]
#define RSCAN0GAFLP113LL RSCAN0.GAFLP113.UINT8[LL]
#define RSCAN0GAFLP113LH RSCAN0.GAFLP113.UINT8[LH]
#define RSCAN0GAFLP113H RSCAN0.GAFLP113.UINT16[H]
#define RSCAN0GAFLP113HL RSCAN0.GAFLP113.UINT8[HL]
#define RSCAN0GAFLID14 RSCAN0.GAFLID14.UINT32
#define RSCAN0GAFLID14L RSCAN0.GAFLID14.UINT16[L]
#define RSCAN0GAFLID14LL RSCAN0.GAFLID14.UINT8[LL]
#define RSCAN0GAFLID14LH RSCAN0.GAFLID14.UINT8[LH]
#define RSCAN0GAFLID14H RSCAN0.GAFLID14.UINT16[H]
#define RSCAN0GAFLID14HL RSCAN0.GAFLID14.UINT8[HL]
#define RSCAN0GAFLID14HH RSCAN0.GAFLID14.UINT8[HH]
#define RSCAN0GAFLM14 RSCAN0.GAFLM14.UINT32
#define RSCAN0GAFLM14L RSCAN0.GAFLM14.UINT16[L]
#define RSCAN0GAFLM14LL RSCAN0.GAFLM14.UINT8[LL]
#define RSCAN0GAFLM14LH RSCAN0.GAFLM14.UINT8[LH]
#define RSCAN0GAFLM14H RSCAN0.GAFLM14.UINT16[H]
#define RSCAN0GAFLM14HL RSCAN0.GAFLM14.UINT8[HL]
#define RSCAN0GAFLM14HH RSCAN0.GAFLM14.UINT8[HH]
#define RSCAN0GAFLP014 RSCAN0.GAFLP014.UINT32
#define RSCAN0GAFLP014L RSCAN0.GAFLP014.UINT16[L]
#define RSCAN0GAFLP014LL RSCAN0.GAFLP014.UINT8[LL]
#define RSCAN0GAFLP014LH RSCAN0.GAFLP014.UINT8[LH]
#define RSCAN0GAFLP014H RSCAN0.GAFLP014.UINT16[H]
#define RSCAN0GAFLP014HL RSCAN0.GAFLP014.UINT8[HL]
#define RSCAN0GAFLP014HH RSCAN0.GAFLP014.UINT8[HH]
#define RSCAN0GAFLP114 RSCAN0.GAFLP114.UINT32
#define RSCAN0GAFLP114L RSCAN0.GAFLP114.UINT16[L]
#define RSCAN0GAFLP114LL RSCAN0.GAFLP114.UINT8[LL]
#define RSCAN0GAFLP114LH RSCAN0.GAFLP114.UINT8[LH]
#define RSCAN0GAFLP114H RSCAN0.GAFLP114.UINT16[H]
#define RSCAN0GAFLP114HL RSCAN0.GAFLP114.UINT8[HL]
#define RSCAN0GAFLID15 RSCAN0.GAFLID15.UINT32
#define RSCAN0GAFLID15L RSCAN0.GAFLID15.UINT16[L]
#define RSCAN0GAFLID15LL RSCAN0.GAFLID15.UINT8[LL]
#define RSCAN0GAFLID15LH RSCAN0.GAFLID15.UINT8[LH]
#define RSCAN0GAFLID15H RSCAN0.GAFLID15.UINT16[H]
#define RSCAN0GAFLID15HL RSCAN0.GAFLID15.UINT8[HL]
#define RSCAN0GAFLID15HH RSCAN0.GAFLID15.UINT8[HH]
#define RSCAN0GAFLM15 RSCAN0.GAFLM15.UINT32
#define RSCAN0GAFLM15L RSCAN0.GAFLM15.UINT16[L]
#define RSCAN0GAFLM15LL RSCAN0.GAFLM15.UINT8[LL]
#define RSCAN0GAFLM15LH RSCAN0.GAFLM15.UINT8[LH]
#define RSCAN0GAFLM15H RSCAN0.GAFLM15.UINT16[H]
#define RSCAN0GAFLM15HL RSCAN0.GAFLM15.UINT8[HL]
#define RSCAN0GAFLM15HH RSCAN0.GAFLM15.UINT8[HH]
#define RSCAN0GAFLP015 RSCAN0.GAFLP015.UINT32
#define RSCAN0GAFLP015L RSCAN0.GAFLP015.UINT16[L]
#define RSCAN0GAFLP015LL RSCAN0.GAFLP015.UINT8[LL]
#define RSCAN0GAFLP015LH RSCAN0.GAFLP015.UINT8[LH]
#define RSCAN0GAFLP015H RSCAN0.GAFLP015.UINT16[H]
#define RSCAN0GAFLP015HL RSCAN0.GAFLP015.UINT8[HL]
#define RSCAN0GAFLP015HH RSCAN0.GAFLP015.UINT8[HH]
#define RSCAN0GAFLP115 RSCAN0.GAFLP115.UINT32
#define RSCAN0GAFLP115L RSCAN0.GAFLP115.UINT16[L]
#define RSCAN0GAFLP115LL RSCAN0.GAFLP115.UINT8[LL]
#define RSCAN0GAFLP115LH RSCAN0.GAFLP115.UINT8[LH]
#define RSCAN0GAFLP115H RSCAN0.GAFLP115.UINT16[H]
#define RSCAN0GAFLP115HL RSCAN0.GAFLP115.UINT8[HL]
#define RSCAN0RMID0 RSCAN0.RMID0.UINT32
#define RSCAN0RMID0L RSCAN0.RMID0.UINT16[L]
#define RSCAN0RMID0LL RSCAN0.RMID0.UINT8[LL]
#define RSCAN0RMID0LH RSCAN0.RMID0.UINT8[LH]
#define RSCAN0RMID0H RSCAN0.RMID0.UINT16[H]
#define RSCAN0RMID0HL RSCAN0.RMID0.UINT8[HL]
#define RSCAN0RMID0HH RSCAN0.RMID0.UINT8[HH]
#define RSCAN0RMPTR0 RSCAN0.RMPTR0.UINT32
#define RSCAN0RMPTR0L RSCAN0.RMPTR0.UINT16[L]
#define RSCAN0RMPTR0LL RSCAN0.RMPTR0.UINT8[LL]
#define RSCAN0RMPTR0LH RSCAN0.RMPTR0.UINT8[LH]
#define RSCAN0RMPTR0H RSCAN0.RMPTR0.UINT16[H]
#define RSCAN0RMPTR0HL RSCAN0.RMPTR0.UINT8[HL]
#define RSCAN0RMPTR0HH RSCAN0.RMPTR0.UINT8[HH]
#define RSCAN0RMDF00 RSCAN0.RMDF00.UINT32
#define RSCAN0RMDF00L RSCAN0.RMDF00.UINT16[L]
#define RSCAN0RMDF00LL RSCAN0.RMDF00.UINT8[LL]
#define RSCAN0RMDF00LH RSCAN0.RMDF00.UINT8[LH]
#define RSCAN0RMDF00H RSCAN0.RMDF00.UINT16[H]
#define RSCAN0RMDF00HL RSCAN0.RMDF00.UINT8[HL]
#define RSCAN0RMDF00HH RSCAN0.RMDF00.UINT8[HH]
#define RSCAN0RMDF10 RSCAN0.RMDF10.UINT32
#define RSCAN0RMDF10L RSCAN0.RMDF10.UINT16[L]
#define RSCAN0RMDF10LL RSCAN0.RMDF10.UINT8[LL]
#define RSCAN0RMDF10LH RSCAN0.RMDF10.UINT8[LH]
#define RSCAN0RMDF10H RSCAN0.RMDF10.UINT16[H]
#define RSCAN0RMDF10HL RSCAN0.RMDF10.UINT8[HL]
#define RSCAN0RMDF10HH RSCAN0.RMDF10.UINT8[HH]
#define RSCAN0RMID1 RSCAN0.RMID1.UINT32
#define RSCAN0RMID1L RSCAN0.RMID1.UINT16[L]
#define RSCAN0RMID1LL RSCAN0.RMID1.UINT8[LL]
#define RSCAN0RMID1LH RSCAN0.RMID1.UINT8[LH]
#define RSCAN0RMID1H RSCAN0.RMID1.UINT16[H]
#define RSCAN0RMID1HL RSCAN0.RMID1.UINT8[HL]
#define RSCAN0RMID1HH RSCAN0.RMID1.UINT8[HH]
#define RSCAN0RMPTR1 RSCAN0.RMPTR1.UINT32
#define RSCAN0RMPTR1L RSCAN0.RMPTR1.UINT16[L]
#define RSCAN0RMPTR1LL RSCAN0.RMPTR1.UINT8[LL]
#define RSCAN0RMPTR1LH RSCAN0.RMPTR1.UINT8[LH]
#define RSCAN0RMPTR1H RSCAN0.RMPTR1.UINT16[H]
#define RSCAN0RMPTR1HL RSCAN0.RMPTR1.UINT8[HL]
#define RSCAN0RMPTR1HH RSCAN0.RMPTR1.UINT8[HH]
#define RSCAN0RMDF01 RSCAN0.RMDF01.UINT32
#define RSCAN0RMDF01L RSCAN0.RMDF01.UINT16[L]
#define RSCAN0RMDF01LL RSCAN0.RMDF01.UINT8[LL]
#define RSCAN0RMDF01LH RSCAN0.RMDF01.UINT8[LH]
#define RSCAN0RMDF01H RSCAN0.RMDF01.UINT16[H]
#define RSCAN0RMDF01HL RSCAN0.RMDF01.UINT8[HL]
#define RSCAN0RMDF01HH RSCAN0.RMDF01.UINT8[HH]
#define RSCAN0RMDF11 RSCAN0.RMDF11.UINT32
#define RSCAN0RMDF11L RSCAN0.RMDF11.UINT16[L]
#define RSCAN0RMDF11LL RSCAN0.RMDF11.UINT8[LL]
#define RSCAN0RMDF11LH RSCAN0.RMDF11.UINT8[LH]
#define RSCAN0RMDF11H RSCAN0.RMDF11.UINT16[H]
#define RSCAN0RMDF11HL RSCAN0.RMDF11.UINT8[HL]
#define RSCAN0RMDF11HH RSCAN0.RMDF11.UINT8[HH]
#define RSCAN0RMID2 RSCAN0.RMID2.UINT32
#define RSCAN0RMID2L RSCAN0.RMID2.UINT16[L]
#define RSCAN0RMID2LL RSCAN0.RMID2.UINT8[LL]
#define RSCAN0RMID2LH RSCAN0.RMID2.UINT8[LH]
#define RSCAN0RMID2H RSCAN0.RMID2.UINT16[H]
#define RSCAN0RMID2HL RSCAN0.RMID2.UINT8[HL]
#define RSCAN0RMID2HH RSCAN0.RMID2.UINT8[HH]
#define RSCAN0RMPTR2 RSCAN0.RMPTR2.UINT32
#define RSCAN0RMPTR2L RSCAN0.RMPTR2.UINT16[L]
#define RSCAN0RMPTR2LL RSCAN0.RMPTR2.UINT8[LL]
#define RSCAN0RMPTR2LH RSCAN0.RMPTR2.UINT8[LH]
#define RSCAN0RMPTR2H RSCAN0.RMPTR2.UINT16[H]
#define RSCAN0RMPTR2HL RSCAN0.RMPTR2.UINT8[HL]
#define RSCAN0RMPTR2HH RSCAN0.RMPTR2.UINT8[HH]
#define RSCAN0RMDF02 RSCAN0.RMDF02.UINT32
#define RSCAN0RMDF02L RSCAN0.RMDF02.UINT16[L]
#define RSCAN0RMDF02LL RSCAN0.RMDF02.UINT8[LL]
#define RSCAN0RMDF02LH RSCAN0.RMDF02.UINT8[LH]
#define RSCAN0RMDF02H RSCAN0.RMDF02.UINT16[H]
#define RSCAN0RMDF02HL RSCAN0.RMDF02.UINT8[HL]
#define RSCAN0RMDF02HH RSCAN0.RMDF02.UINT8[HH]
#define RSCAN0RMDF12 RSCAN0.RMDF12.UINT32
#define RSCAN0RMDF12L RSCAN0.RMDF12.UINT16[L]
#define RSCAN0RMDF12LL RSCAN0.RMDF12.UINT8[LL]
#define RSCAN0RMDF12LH RSCAN0.RMDF12.UINT8[LH]
#define RSCAN0RMDF12H RSCAN0.RMDF12.UINT16[H]
#define RSCAN0RMDF12HL RSCAN0.RMDF12.UINT8[HL]
#define RSCAN0RMDF12HH RSCAN0.RMDF12.UINT8[HH]
#define RSCAN0RMID3 RSCAN0.RMID3.UINT32
#define RSCAN0RMID3L RSCAN0.RMID3.UINT16[L]
#define RSCAN0RMID3LL RSCAN0.RMID3.UINT8[LL]
#define RSCAN0RMID3LH RSCAN0.RMID3.UINT8[LH]
#define RSCAN0RMID3H RSCAN0.RMID3.UINT16[H]
#define RSCAN0RMID3HL RSCAN0.RMID3.UINT8[HL]
#define RSCAN0RMID3HH RSCAN0.RMID3.UINT8[HH]
#define RSCAN0RMPTR3 RSCAN0.RMPTR3.UINT32
#define RSCAN0RMPTR3L RSCAN0.RMPTR3.UINT16[L]
#define RSCAN0RMPTR3LL RSCAN0.RMPTR3.UINT8[LL]
#define RSCAN0RMPTR3LH RSCAN0.RMPTR3.UINT8[LH]
#define RSCAN0RMPTR3H RSCAN0.RMPTR3.UINT16[H]
#define RSCAN0RMPTR3HL RSCAN0.RMPTR3.UINT8[HL]
#define RSCAN0RMPTR3HH RSCAN0.RMPTR3.UINT8[HH]
#define RSCAN0RMDF03 RSCAN0.RMDF03.UINT32
#define RSCAN0RMDF03L RSCAN0.RMDF03.UINT16[L]
#define RSCAN0RMDF03LL RSCAN0.RMDF03.UINT8[LL]
#define RSCAN0RMDF03LH RSCAN0.RMDF03.UINT8[LH]
#define RSCAN0RMDF03H RSCAN0.RMDF03.UINT16[H]
#define RSCAN0RMDF03HL RSCAN0.RMDF03.UINT8[HL]
#define RSCAN0RMDF03HH RSCAN0.RMDF03.UINT8[HH]
#define RSCAN0RMDF13 RSCAN0.RMDF13.UINT32
#define RSCAN0RMDF13L RSCAN0.RMDF13.UINT16[L]
#define RSCAN0RMDF13LL RSCAN0.RMDF13.UINT8[LL]
#define RSCAN0RMDF13LH RSCAN0.RMDF13.UINT8[LH]
#define RSCAN0RMDF13H RSCAN0.RMDF13.UINT16[H]
#define RSCAN0RMDF13HL RSCAN0.RMDF13.UINT8[HL]
#define RSCAN0RMDF13HH RSCAN0.RMDF13.UINT8[HH]
#define RSCAN0RMID4 RSCAN0.RMID4.UINT32
#define RSCAN0RMID4L RSCAN0.RMID4.UINT16[L]
#define RSCAN0RMID4LL RSCAN0.RMID4.UINT8[LL]
#define RSCAN0RMID4LH RSCAN0.RMID4.UINT8[LH]
#define RSCAN0RMID4H RSCAN0.RMID4.UINT16[H]
#define RSCAN0RMID4HL RSCAN0.RMID4.UINT8[HL]
#define RSCAN0RMID4HH RSCAN0.RMID4.UINT8[HH]
#define RSCAN0RMPTR4 RSCAN0.RMPTR4.UINT32
#define RSCAN0RMPTR4L RSCAN0.RMPTR4.UINT16[L]
#define RSCAN0RMPTR4LL RSCAN0.RMPTR4.UINT8[LL]
#define RSCAN0RMPTR4LH RSCAN0.RMPTR4.UINT8[LH]
#define RSCAN0RMPTR4H RSCAN0.RMPTR4.UINT16[H]
#define RSCAN0RMPTR4HL RSCAN0.RMPTR4.UINT8[HL]
#define RSCAN0RMPTR4HH RSCAN0.RMPTR4.UINT8[HH]
#define RSCAN0RMDF04 RSCAN0.RMDF04.UINT32
#define RSCAN0RMDF04L RSCAN0.RMDF04.UINT16[L]
#define RSCAN0RMDF04LL RSCAN0.RMDF04.UINT8[LL]
#define RSCAN0RMDF04LH RSCAN0.RMDF04.UINT8[LH]
#define RSCAN0RMDF04H RSCAN0.RMDF04.UINT16[H]
#define RSCAN0RMDF04HL RSCAN0.RMDF04.UINT8[HL]
#define RSCAN0RMDF04HH RSCAN0.RMDF04.UINT8[HH]
#define RSCAN0RMDF14 RSCAN0.RMDF14.UINT32
#define RSCAN0RMDF14L RSCAN0.RMDF14.UINT16[L]
#define RSCAN0RMDF14LL RSCAN0.RMDF14.UINT8[LL]
#define RSCAN0RMDF14LH RSCAN0.RMDF14.UINT8[LH]
#define RSCAN0RMDF14H RSCAN0.RMDF14.UINT16[H]
#define RSCAN0RMDF14HL RSCAN0.RMDF14.UINT8[HL]
#define RSCAN0RMDF14HH RSCAN0.RMDF14.UINT8[HH]
#define RSCAN0RMID5 RSCAN0.RMID5.UINT32
#define RSCAN0RMID5L RSCAN0.RMID5.UINT16[L]
#define RSCAN0RMID5LL RSCAN0.RMID5.UINT8[LL]
#define RSCAN0RMID5LH RSCAN0.RMID5.UINT8[LH]
#define RSCAN0RMID5H RSCAN0.RMID5.UINT16[H]
#define RSCAN0RMID5HL RSCAN0.RMID5.UINT8[HL]
#define RSCAN0RMID5HH RSCAN0.RMID5.UINT8[HH]
#define RSCAN0RMPTR5 RSCAN0.RMPTR5.UINT32
#define RSCAN0RMPTR5L RSCAN0.RMPTR5.UINT16[L]
#define RSCAN0RMPTR5LL RSCAN0.RMPTR5.UINT8[LL]
#define RSCAN0RMPTR5LH RSCAN0.RMPTR5.UINT8[LH]
#define RSCAN0RMPTR5H RSCAN0.RMPTR5.UINT16[H]
#define RSCAN0RMPTR5HL RSCAN0.RMPTR5.UINT8[HL]
#define RSCAN0RMPTR5HH RSCAN0.RMPTR5.UINT8[HH]
#define RSCAN0RMDF05 RSCAN0.RMDF05.UINT32
#define RSCAN0RMDF05L RSCAN0.RMDF05.UINT16[L]
#define RSCAN0RMDF05LL RSCAN0.RMDF05.UINT8[LL]
#define RSCAN0RMDF05LH RSCAN0.RMDF05.UINT8[LH]
#define RSCAN0RMDF05H RSCAN0.RMDF05.UINT16[H]
#define RSCAN0RMDF05HL RSCAN0.RMDF05.UINT8[HL]
#define RSCAN0RMDF05HH RSCAN0.RMDF05.UINT8[HH]
#define RSCAN0RMDF15 RSCAN0.RMDF15.UINT32
#define RSCAN0RMDF15L RSCAN0.RMDF15.UINT16[L]
#define RSCAN0RMDF15LL RSCAN0.RMDF15.UINT8[LL]
#define RSCAN0RMDF15LH RSCAN0.RMDF15.UINT8[LH]
#define RSCAN0RMDF15H RSCAN0.RMDF15.UINT16[H]
#define RSCAN0RMDF15HL RSCAN0.RMDF15.UINT8[HL]
#define RSCAN0RMDF15HH RSCAN0.RMDF15.UINT8[HH]
#define RSCAN0RMID6 RSCAN0.RMID6.UINT32
#define RSCAN0RMID6L RSCAN0.RMID6.UINT16[L]
#define RSCAN0RMID6LL RSCAN0.RMID6.UINT8[LL]
#define RSCAN0RMID6LH RSCAN0.RMID6.UINT8[LH]
#define RSCAN0RMID6H RSCAN0.RMID6.UINT16[H]
#define RSCAN0RMID6HL RSCAN0.RMID6.UINT8[HL]
#define RSCAN0RMID6HH RSCAN0.RMID6.UINT8[HH]
#define RSCAN0RMPTR6 RSCAN0.RMPTR6.UINT32
#define RSCAN0RMPTR6L RSCAN0.RMPTR6.UINT16[L]
#define RSCAN0RMPTR6LL RSCAN0.RMPTR6.UINT8[LL]
#define RSCAN0RMPTR6LH RSCAN0.RMPTR6.UINT8[LH]
#define RSCAN0RMPTR6H RSCAN0.RMPTR6.UINT16[H]
#define RSCAN0RMPTR6HL RSCAN0.RMPTR6.UINT8[HL]
#define RSCAN0RMPTR6HH RSCAN0.RMPTR6.UINT8[HH]
#define RSCAN0RMDF06 RSCAN0.RMDF06.UINT32
#define RSCAN0RMDF06L RSCAN0.RMDF06.UINT16[L]
#define RSCAN0RMDF06LL RSCAN0.RMDF06.UINT8[LL]
#define RSCAN0RMDF06LH RSCAN0.RMDF06.UINT8[LH]
#define RSCAN0RMDF06H RSCAN0.RMDF06.UINT16[H]
#define RSCAN0RMDF06HL RSCAN0.RMDF06.UINT8[HL]
#define RSCAN0RMDF06HH RSCAN0.RMDF06.UINT8[HH]
#define RSCAN0RMDF16 RSCAN0.RMDF16.UINT32
#define RSCAN0RMDF16L RSCAN0.RMDF16.UINT16[L]
#define RSCAN0RMDF16LL RSCAN0.RMDF16.UINT8[LL]
#define RSCAN0RMDF16LH RSCAN0.RMDF16.UINT8[LH]
#define RSCAN0RMDF16H RSCAN0.RMDF16.UINT16[H]
#define RSCAN0RMDF16HL RSCAN0.RMDF16.UINT8[HL]
#define RSCAN0RMDF16HH RSCAN0.RMDF16.UINT8[HH]
#define RSCAN0RMID7 RSCAN0.RMID7.UINT32
#define RSCAN0RMID7L RSCAN0.RMID7.UINT16[L]
#define RSCAN0RMID7LL RSCAN0.RMID7.UINT8[LL]
#define RSCAN0RMID7LH RSCAN0.RMID7.UINT8[LH]
#define RSCAN0RMID7H RSCAN0.RMID7.UINT16[H]
#define RSCAN0RMID7HL RSCAN0.RMID7.UINT8[HL]
#define RSCAN0RMID7HH RSCAN0.RMID7.UINT8[HH]
#define RSCAN0RMPTR7 RSCAN0.RMPTR7.UINT32
#define RSCAN0RMPTR7L RSCAN0.RMPTR7.UINT16[L]
#define RSCAN0RMPTR7LL RSCAN0.RMPTR7.UINT8[LL]
#define RSCAN0RMPTR7LH RSCAN0.RMPTR7.UINT8[LH]
#define RSCAN0RMPTR7H RSCAN0.RMPTR7.UINT16[H]
#define RSCAN0RMPTR7HL RSCAN0.RMPTR7.UINT8[HL]
#define RSCAN0RMPTR7HH RSCAN0.RMPTR7.UINT8[HH]
#define RSCAN0RMDF07 RSCAN0.RMDF07.UINT32
#define RSCAN0RMDF07L RSCAN0.RMDF07.UINT16[L]
#define RSCAN0RMDF07LL RSCAN0.RMDF07.UINT8[LL]
#define RSCAN0RMDF07LH RSCAN0.RMDF07.UINT8[LH]
#define RSCAN0RMDF07H RSCAN0.RMDF07.UINT16[H]
#define RSCAN0RMDF07HL RSCAN0.RMDF07.UINT8[HL]
#define RSCAN0RMDF07HH RSCAN0.RMDF07.UINT8[HH]
#define RSCAN0RMDF17 RSCAN0.RMDF17.UINT32
#define RSCAN0RMDF17L RSCAN0.RMDF17.UINT16[L]
#define RSCAN0RMDF17LL RSCAN0.RMDF17.UINT8[LL]
#define RSCAN0RMDF17LH RSCAN0.RMDF17.UINT8[LH]
#define RSCAN0RMDF17H RSCAN0.RMDF17.UINT16[H]
#define RSCAN0RMDF17HL RSCAN0.RMDF17.UINT8[HL]
#define RSCAN0RMDF17HH RSCAN0.RMDF17.UINT8[HH]
#define RSCAN0RMID8 RSCAN0.RMID8.UINT32
#define RSCAN0RMID8L RSCAN0.RMID8.UINT16[L]
#define RSCAN0RMID8LL RSCAN0.RMID8.UINT8[LL]
#define RSCAN0RMID8LH RSCAN0.RMID8.UINT8[LH]
#define RSCAN0RMID8H RSCAN0.RMID8.UINT16[H]
#define RSCAN0RMID8HL RSCAN0.RMID8.UINT8[HL]
#define RSCAN0RMID8HH RSCAN0.RMID8.UINT8[HH]
#define RSCAN0RMPTR8 RSCAN0.RMPTR8.UINT32
#define RSCAN0RMPTR8L RSCAN0.RMPTR8.UINT16[L]
#define RSCAN0RMPTR8LL RSCAN0.RMPTR8.UINT8[LL]
#define RSCAN0RMPTR8LH RSCAN0.RMPTR8.UINT8[LH]
#define RSCAN0RMPTR8H RSCAN0.RMPTR8.UINT16[H]
#define RSCAN0RMPTR8HL RSCAN0.RMPTR8.UINT8[HL]
#define RSCAN0RMPTR8HH RSCAN0.RMPTR8.UINT8[HH]
#define RSCAN0RMDF08 RSCAN0.RMDF08.UINT32
#define RSCAN0RMDF08L RSCAN0.RMDF08.UINT16[L]
#define RSCAN0RMDF08LL RSCAN0.RMDF08.UINT8[LL]
#define RSCAN0RMDF08LH RSCAN0.RMDF08.UINT8[LH]
#define RSCAN0RMDF08H RSCAN0.RMDF08.UINT16[H]
#define RSCAN0RMDF08HL RSCAN0.RMDF08.UINT8[HL]
#define RSCAN0RMDF08HH RSCAN0.RMDF08.UINT8[HH]
#define RSCAN0RMDF18 RSCAN0.RMDF18.UINT32
#define RSCAN0RMDF18L RSCAN0.RMDF18.UINT16[L]
#define RSCAN0RMDF18LL RSCAN0.RMDF18.UINT8[LL]
#define RSCAN0RMDF18LH RSCAN0.RMDF18.UINT8[LH]
#define RSCAN0RMDF18H RSCAN0.RMDF18.UINT16[H]
#define RSCAN0RMDF18HL RSCAN0.RMDF18.UINT8[HL]
#define RSCAN0RMDF18HH RSCAN0.RMDF18.UINT8[HH]
#define RSCAN0RMID9 RSCAN0.RMID9.UINT32
#define RSCAN0RMID9L RSCAN0.RMID9.UINT16[L]
#define RSCAN0RMID9LL RSCAN0.RMID9.UINT8[LL]
#define RSCAN0RMID9LH RSCAN0.RMID9.UINT8[LH]
#define RSCAN0RMID9H RSCAN0.RMID9.UINT16[H]
#define RSCAN0RMID9HL RSCAN0.RMID9.UINT8[HL]
#define RSCAN0RMID9HH RSCAN0.RMID9.UINT8[HH]
#define RSCAN0RMPTR9 RSCAN0.RMPTR9.UINT32
#define RSCAN0RMPTR9L RSCAN0.RMPTR9.UINT16[L]
#define RSCAN0RMPTR9LL RSCAN0.RMPTR9.UINT8[LL]
#define RSCAN0RMPTR9LH RSCAN0.RMPTR9.UINT8[LH]
#define RSCAN0RMPTR9H RSCAN0.RMPTR9.UINT16[H]
#define RSCAN0RMPTR9HL RSCAN0.RMPTR9.UINT8[HL]
#define RSCAN0RMPTR9HH RSCAN0.RMPTR9.UINT8[HH]
#define RSCAN0RMDF09 RSCAN0.RMDF09.UINT32
#define RSCAN0RMDF09L RSCAN0.RMDF09.UINT16[L]
#define RSCAN0RMDF09LL RSCAN0.RMDF09.UINT8[LL]
#define RSCAN0RMDF09LH RSCAN0.RMDF09.UINT8[LH]
#define RSCAN0RMDF09H RSCAN0.RMDF09.UINT16[H]
#define RSCAN0RMDF09HL RSCAN0.RMDF09.UINT8[HL]
#define RSCAN0RMDF09HH RSCAN0.RMDF09.UINT8[HH]
#define RSCAN0RMDF19 RSCAN0.RMDF19.UINT32
#define RSCAN0RMDF19L RSCAN0.RMDF19.UINT16[L]
#define RSCAN0RMDF19LL RSCAN0.RMDF19.UINT8[LL]
#define RSCAN0RMDF19LH RSCAN0.RMDF19.UINT8[LH]
#define RSCAN0RMDF19H RSCAN0.RMDF19.UINT16[H]
#define RSCAN0RMDF19HL RSCAN0.RMDF19.UINT8[HL]
#define RSCAN0RMDF19HH RSCAN0.RMDF19.UINT8[HH]
#define RSCAN0RMID10 RSCAN0.RMID10.UINT32
#define RSCAN0RMID10L RSCAN0.RMID10.UINT16[L]
#define RSCAN0RMID10LL RSCAN0.RMID10.UINT8[LL]
#define RSCAN0RMID10LH RSCAN0.RMID10.UINT8[LH]
#define RSCAN0RMID10H RSCAN0.RMID10.UINT16[H]
#define RSCAN0RMID10HL RSCAN0.RMID10.UINT8[HL]
#define RSCAN0RMID10HH RSCAN0.RMID10.UINT8[HH]
#define RSCAN0RMPTR10 RSCAN0.RMPTR10.UINT32
#define RSCAN0RMPTR10L RSCAN0.RMPTR10.UINT16[L]
#define RSCAN0RMPTR10LL RSCAN0.RMPTR10.UINT8[LL]
#define RSCAN0RMPTR10LH RSCAN0.RMPTR10.UINT8[LH]
#define RSCAN0RMPTR10H RSCAN0.RMPTR10.UINT16[H]
#define RSCAN0RMPTR10HL RSCAN0.RMPTR10.UINT8[HL]
#define RSCAN0RMPTR10HH RSCAN0.RMPTR10.UINT8[HH]
#define RSCAN0RMDF010 RSCAN0.RMDF010.UINT32
#define RSCAN0RMDF010L RSCAN0.RMDF010.UINT16[L]
#define RSCAN0RMDF010LL RSCAN0.RMDF010.UINT8[LL]
#define RSCAN0RMDF010LH RSCAN0.RMDF010.UINT8[LH]
#define RSCAN0RMDF010H RSCAN0.RMDF010.UINT16[H]
#define RSCAN0RMDF010HL RSCAN0.RMDF010.UINT8[HL]
#define RSCAN0RMDF010HH RSCAN0.RMDF010.UINT8[HH]
#define RSCAN0RMDF110 RSCAN0.RMDF110.UINT32
#define RSCAN0RMDF110L RSCAN0.RMDF110.UINT16[L]
#define RSCAN0RMDF110LL RSCAN0.RMDF110.UINT8[LL]
#define RSCAN0RMDF110LH RSCAN0.RMDF110.UINT8[LH]
#define RSCAN0RMDF110H RSCAN0.RMDF110.UINT16[H]
#define RSCAN0RMDF110HL RSCAN0.RMDF110.UINT8[HL]
#define RSCAN0RMDF110HH RSCAN0.RMDF110.UINT8[HH]
#define RSCAN0RMID11 RSCAN0.RMID11.UINT32
#define RSCAN0RMID11L RSCAN0.RMID11.UINT16[L]
#define RSCAN0RMID11LL RSCAN0.RMID11.UINT8[LL]
#define RSCAN0RMID11LH RSCAN0.RMID11.UINT8[LH]
#define RSCAN0RMID11H RSCAN0.RMID11.UINT16[H]
#define RSCAN0RMID11HL RSCAN0.RMID11.UINT8[HL]
#define RSCAN0RMID11HH RSCAN0.RMID11.UINT8[HH]
#define RSCAN0RMPTR11 RSCAN0.RMPTR11.UINT32
#define RSCAN0RMPTR11L RSCAN0.RMPTR11.UINT16[L]
#define RSCAN0RMPTR11LL RSCAN0.RMPTR11.UINT8[LL]
#define RSCAN0RMPTR11LH RSCAN0.RMPTR11.UINT8[LH]
#define RSCAN0RMPTR11H RSCAN0.RMPTR11.UINT16[H]
#define RSCAN0RMPTR11HL RSCAN0.RMPTR11.UINT8[HL]
#define RSCAN0RMPTR11HH RSCAN0.RMPTR11.UINT8[HH]
#define RSCAN0RMDF011 RSCAN0.RMDF011.UINT32
#define RSCAN0RMDF011L RSCAN0.RMDF011.UINT16[L]
#define RSCAN0RMDF011LL RSCAN0.RMDF011.UINT8[LL]
#define RSCAN0RMDF011LH RSCAN0.RMDF011.UINT8[LH]
#define RSCAN0RMDF011H RSCAN0.RMDF011.UINT16[H]
#define RSCAN0RMDF011HL RSCAN0.RMDF011.UINT8[HL]
#define RSCAN0RMDF011HH RSCAN0.RMDF011.UINT8[HH]
#define RSCAN0RMDF111 RSCAN0.RMDF111.UINT32
#define RSCAN0RMDF111L RSCAN0.RMDF111.UINT16[L]
#define RSCAN0RMDF111LL RSCAN0.RMDF111.UINT8[LL]
#define RSCAN0RMDF111LH RSCAN0.RMDF111.UINT8[LH]
#define RSCAN0RMDF111H RSCAN0.RMDF111.UINT16[H]
#define RSCAN0RMDF111HL RSCAN0.RMDF111.UINT8[HL]
#define RSCAN0RMDF111HH RSCAN0.RMDF111.UINT8[HH]
#define RSCAN0RMID12 RSCAN0.RMID12.UINT32
#define RSCAN0RMID12L RSCAN0.RMID12.UINT16[L]
#define RSCAN0RMID12LL RSCAN0.RMID12.UINT8[LL]
#define RSCAN0RMID12LH RSCAN0.RMID12.UINT8[LH]
#define RSCAN0RMID12H RSCAN0.RMID12.UINT16[H]
#define RSCAN0RMID12HL RSCAN0.RMID12.UINT8[HL]
#define RSCAN0RMID12HH RSCAN0.RMID12.UINT8[HH]
#define RSCAN0RMPTR12 RSCAN0.RMPTR12.UINT32
#define RSCAN0RMPTR12L RSCAN0.RMPTR12.UINT16[L]
#define RSCAN0RMPTR12LL RSCAN0.RMPTR12.UINT8[LL]
#define RSCAN0RMPTR12LH RSCAN0.RMPTR12.UINT8[LH]
#define RSCAN0RMPTR12H RSCAN0.RMPTR12.UINT16[H]
#define RSCAN0RMPTR12HL RSCAN0.RMPTR12.UINT8[HL]
#define RSCAN0RMPTR12HH RSCAN0.RMPTR12.UINT8[HH]
#define RSCAN0RMDF012 RSCAN0.RMDF012.UINT32
#define RSCAN0RMDF012L RSCAN0.RMDF012.UINT16[L]
#define RSCAN0RMDF012LL RSCAN0.RMDF012.UINT8[LL]
#define RSCAN0RMDF012LH RSCAN0.RMDF012.UINT8[LH]
#define RSCAN0RMDF012H RSCAN0.RMDF012.UINT16[H]
#define RSCAN0RMDF012HL RSCAN0.RMDF012.UINT8[HL]
#define RSCAN0RMDF012HH RSCAN0.RMDF012.UINT8[HH]
#define RSCAN0RMDF112 RSCAN0.RMDF112.UINT32
#define RSCAN0RMDF112L RSCAN0.RMDF112.UINT16[L]
#define RSCAN0RMDF112LL RSCAN0.RMDF112.UINT8[LL]
#define RSCAN0RMDF112LH RSCAN0.RMDF112.UINT8[LH]
#define RSCAN0RMDF112H RSCAN0.RMDF112.UINT16[H]
#define RSCAN0RMDF112HL RSCAN0.RMDF112.UINT8[HL]
#define RSCAN0RMDF112HH RSCAN0.RMDF112.UINT8[HH]
#define RSCAN0RMID13 RSCAN0.RMID13.UINT32
#define RSCAN0RMID13L RSCAN0.RMID13.UINT16[L]
#define RSCAN0RMID13LL RSCAN0.RMID13.UINT8[LL]
#define RSCAN0RMID13LH RSCAN0.RMID13.UINT8[LH]
#define RSCAN0RMID13H RSCAN0.RMID13.UINT16[H]
#define RSCAN0RMID13HL RSCAN0.RMID13.UINT8[HL]
#define RSCAN0RMID13HH RSCAN0.RMID13.UINT8[HH]
#define RSCAN0RMPTR13 RSCAN0.RMPTR13.UINT32
#define RSCAN0RMPTR13L RSCAN0.RMPTR13.UINT16[L]
#define RSCAN0RMPTR13LL RSCAN0.RMPTR13.UINT8[LL]
#define RSCAN0RMPTR13LH RSCAN0.RMPTR13.UINT8[LH]
#define RSCAN0RMPTR13H RSCAN0.RMPTR13.UINT16[H]
#define RSCAN0RMPTR13HL RSCAN0.RMPTR13.UINT8[HL]
#define RSCAN0RMPTR13HH RSCAN0.RMPTR13.UINT8[HH]
#define RSCAN0RMDF013 RSCAN0.RMDF013.UINT32
#define RSCAN0RMDF013L RSCAN0.RMDF013.UINT16[L]
#define RSCAN0RMDF013LL RSCAN0.RMDF013.UINT8[LL]
#define RSCAN0RMDF013LH RSCAN0.RMDF013.UINT8[LH]
#define RSCAN0RMDF013H RSCAN0.RMDF013.UINT16[H]
#define RSCAN0RMDF013HL RSCAN0.RMDF013.UINT8[HL]
#define RSCAN0RMDF013HH RSCAN0.RMDF013.UINT8[HH]
#define RSCAN0RMDF113 RSCAN0.RMDF113.UINT32
#define RSCAN0RMDF113L RSCAN0.RMDF113.UINT16[L]
#define RSCAN0RMDF113LL RSCAN0.RMDF113.UINT8[LL]
#define RSCAN0RMDF113LH RSCAN0.RMDF113.UINT8[LH]
#define RSCAN0RMDF113H RSCAN0.RMDF113.UINT16[H]
#define RSCAN0RMDF113HL RSCAN0.RMDF113.UINT8[HL]
#define RSCAN0RMDF113HH RSCAN0.RMDF113.UINT8[HH]
#define RSCAN0RMID14 RSCAN0.RMID14.UINT32
#define RSCAN0RMID14L RSCAN0.RMID14.UINT16[L]
#define RSCAN0RMID14LL RSCAN0.RMID14.UINT8[LL]
#define RSCAN0RMID14LH RSCAN0.RMID14.UINT8[LH]
#define RSCAN0RMID14H RSCAN0.RMID14.UINT16[H]
#define RSCAN0RMID14HL RSCAN0.RMID14.UINT8[HL]
#define RSCAN0RMID14HH RSCAN0.RMID14.UINT8[HH]
#define RSCAN0RMPTR14 RSCAN0.RMPTR14.UINT32
#define RSCAN0RMPTR14L RSCAN0.RMPTR14.UINT16[L]
#define RSCAN0RMPTR14LL RSCAN0.RMPTR14.UINT8[LL]
#define RSCAN0RMPTR14LH RSCAN0.RMPTR14.UINT8[LH]
#define RSCAN0RMPTR14H RSCAN0.RMPTR14.UINT16[H]
#define RSCAN0RMPTR14HL RSCAN0.RMPTR14.UINT8[HL]
#define RSCAN0RMPTR14HH RSCAN0.RMPTR14.UINT8[HH]
#define RSCAN0RMDF014 RSCAN0.RMDF014.UINT32
#define RSCAN0RMDF014L RSCAN0.RMDF014.UINT16[L]
#define RSCAN0RMDF014LL RSCAN0.RMDF014.UINT8[LL]
#define RSCAN0RMDF014LH RSCAN0.RMDF014.UINT8[LH]
#define RSCAN0RMDF014H RSCAN0.RMDF014.UINT16[H]
#define RSCAN0RMDF014HL RSCAN0.RMDF014.UINT8[HL]
#define RSCAN0RMDF014HH RSCAN0.RMDF014.UINT8[HH]
#define RSCAN0RMDF114 RSCAN0.RMDF114.UINT32
#define RSCAN0RMDF114L RSCAN0.RMDF114.UINT16[L]
#define RSCAN0RMDF114LL RSCAN0.RMDF114.UINT8[LL]
#define RSCAN0RMDF114LH RSCAN0.RMDF114.UINT8[LH]
#define RSCAN0RMDF114H RSCAN0.RMDF114.UINT16[H]
#define RSCAN0RMDF114HL RSCAN0.RMDF114.UINT8[HL]
#define RSCAN0RMDF114HH RSCAN0.RMDF114.UINT8[HH]
#define RSCAN0RMID15 RSCAN0.RMID15.UINT32
#define RSCAN0RMID15L RSCAN0.RMID15.UINT16[L]
#define RSCAN0RMID15LL RSCAN0.RMID15.UINT8[LL]
#define RSCAN0RMID15LH RSCAN0.RMID15.UINT8[LH]
#define RSCAN0RMID15H RSCAN0.RMID15.UINT16[H]
#define RSCAN0RMID15HL RSCAN0.RMID15.UINT8[HL]
#define RSCAN0RMID15HH RSCAN0.RMID15.UINT8[HH]
#define RSCAN0RMPTR15 RSCAN0.RMPTR15.UINT32
#define RSCAN0RMPTR15L RSCAN0.RMPTR15.UINT16[L]
#define RSCAN0RMPTR15LL RSCAN0.RMPTR15.UINT8[LL]
#define RSCAN0RMPTR15LH RSCAN0.RMPTR15.UINT8[LH]
#define RSCAN0RMPTR15H RSCAN0.RMPTR15.UINT16[H]
#define RSCAN0RMPTR15HL RSCAN0.RMPTR15.UINT8[HL]
#define RSCAN0RMPTR15HH RSCAN0.RMPTR15.UINT8[HH]
#define RSCAN0RMDF015 RSCAN0.RMDF015.UINT32
#define RSCAN0RMDF015L RSCAN0.RMDF015.UINT16[L]
#define RSCAN0RMDF015LL RSCAN0.RMDF015.UINT8[LL]
#define RSCAN0RMDF015LH RSCAN0.RMDF015.UINT8[LH]
#define RSCAN0RMDF015H RSCAN0.RMDF015.UINT16[H]
#define RSCAN0RMDF015HL RSCAN0.RMDF015.UINT8[HL]
#define RSCAN0RMDF015HH RSCAN0.RMDF015.UINT8[HH]
#define RSCAN0RMDF115 RSCAN0.RMDF115.UINT32
#define RSCAN0RMDF115L RSCAN0.RMDF115.UINT16[L]
#define RSCAN0RMDF115LL RSCAN0.RMDF115.UINT8[LL]
#define RSCAN0RMDF115LH RSCAN0.RMDF115.UINT8[LH]
#define RSCAN0RMDF115H RSCAN0.RMDF115.UINT16[H]
#define RSCAN0RMDF115HL RSCAN0.RMDF115.UINT8[HL]
#define RSCAN0RMDF115HH RSCAN0.RMDF115.UINT8[HH]
#define RSCAN0RMID16 RSCAN0.RMID16.UINT32
#define RSCAN0RMID16L RSCAN0.RMID16.UINT16[L]
#define RSCAN0RMID16LL RSCAN0.RMID16.UINT8[LL]
#define RSCAN0RMID16LH RSCAN0.RMID16.UINT8[LH]
#define RSCAN0RMID16H RSCAN0.RMID16.UINT16[H]
#define RSCAN0RMID16HL RSCAN0.RMID16.UINT8[HL]
#define RSCAN0RMID16HH RSCAN0.RMID16.UINT8[HH]
#define RSCAN0RMPTR16 RSCAN0.RMPTR16.UINT32
#define RSCAN0RMPTR16L RSCAN0.RMPTR16.UINT16[L]
#define RSCAN0RMPTR16LL RSCAN0.RMPTR16.UINT8[LL]
#define RSCAN0RMPTR16LH RSCAN0.RMPTR16.UINT8[LH]
#define RSCAN0RMPTR16H RSCAN0.RMPTR16.UINT16[H]
#define RSCAN0RMPTR16HL RSCAN0.RMPTR16.UINT8[HL]
#define RSCAN0RMPTR16HH RSCAN0.RMPTR16.UINT8[HH]
#define RSCAN0RMDF016 RSCAN0.RMDF016.UINT32
#define RSCAN0RMDF016L RSCAN0.RMDF016.UINT16[L]
#define RSCAN0RMDF016LL RSCAN0.RMDF016.UINT8[LL]
#define RSCAN0RMDF016LH RSCAN0.RMDF016.UINT8[LH]
#define RSCAN0RMDF016H RSCAN0.RMDF016.UINT16[H]
#define RSCAN0RMDF016HL RSCAN0.RMDF016.UINT8[HL]
#define RSCAN0RMDF016HH RSCAN0.RMDF016.UINT8[HH]
#define RSCAN0RMDF116 RSCAN0.RMDF116.UINT32
#define RSCAN0RMDF116L RSCAN0.RMDF116.UINT16[L]
#define RSCAN0RMDF116LL RSCAN0.RMDF116.UINT8[LL]
#define RSCAN0RMDF116LH RSCAN0.RMDF116.UINT8[LH]
#define RSCAN0RMDF116H RSCAN0.RMDF116.UINT16[H]
#define RSCAN0RMDF116HL RSCAN0.RMDF116.UINT8[HL]
#define RSCAN0RMDF116HH RSCAN0.RMDF116.UINT8[HH]
#define RSCAN0RMID17 RSCAN0.RMID17.UINT32
#define RSCAN0RMID17L RSCAN0.RMID17.UINT16[L]
#define RSCAN0RMID17LL RSCAN0.RMID17.UINT8[LL]
#define RSCAN0RMID17LH RSCAN0.RMID17.UINT8[LH]
#define RSCAN0RMID17H RSCAN0.RMID17.UINT16[H]
#define RSCAN0RMID17HL RSCAN0.RMID17.UINT8[HL]
#define RSCAN0RMID17HH RSCAN0.RMID17.UINT8[HH]
#define RSCAN0RMPTR17 RSCAN0.RMPTR17.UINT32
#define RSCAN0RMPTR17L RSCAN0.RMPTR17.UINT16[L]
#define RSCAN0RMPTR17LL RSCAN0.RMPTR17.UINT8[LL]
#define RSCAN0RMPTR17LH RSCAN0.RMPTR17.UINT8[LH]
#define RSCAN0RMPTR17H RSCAN0.RMPTR17.UINT16[H]
#define RSCAN0RMPTR17HL RSCAN0.RMPTR17.UINT8[HL]
#define RSCAN0RMPTR17HH RSCAN0.RMPTR17.UINT8[HH]
#define RSCAN0RMDF017 RSCAN0.RMDF017.UINT32
#define RSCAN0RMDF017L RSCAN0.RMDF017.UINT16[L]
#define RSCAN0RMDF017LL RSCAN0.RMDF017.UINT8[LL]
#define RSCAN0RMDF017LH RSCAN0.RMDF017.UINT8[LH]
#define RSCAN0RMDF017H RSCAN0.RMDF017.UINT16[H]
#define RSCAN0RMDF017HL RSCAN0.RMDF017.UINT8[HL]
#define RSCAN0RMDF017HH RSCAN0.RMDF017.UINT8[HH]
#define RSCAN0RMDF117 RSCAN0.RMDF117.UINT32
#define RSCAN0RMDF117L RSCAN0.RMDF117.UINT16[L]
#define RSCAN0RMDF117LL RSCAN0.RMDF117.UINT8[LL]
#define RSCAN0RMDF117LH RSCAN0.RMDF117.UINT8[LH]
#define RSCAN0RMDF117H RSCAN0.RMDF117.UINT16[H]
#define RSCAN0RMDF117HL RSCAN0.RMDF117.UINT8[HL]
#define RSCAN0RMDF117HH RSCAN0.RMDF117.UINT8[HH]
#define RSCAN0RMID18 RSCAN0.RMID18.UINT32
#define RSCAN0RMID18L RSCAN0.RMID18.UINT16[L]
#define RSCAN0RMID18LL RSCAN0.RMID18.UINT8[LL]
#define RSCAN0RMID18LH RSCAN0.RMID18.UINT8[LH]
#define RSCAN0RMID18H RSCAN0.RMID18.UINT16[H]
#define RSCAN0RMID18HL RSCAN0.RMID18.UINT8[HL]
#define RSCAN0RMID18HH RSCAN0.RMID18.UINT8[HH]
#define RSCAN0RMPTR18 RSCAN0.RMPTR18.UINT32
#define RSCAN0RMPTR18L RSCAN0.RMPTR18.UINT16[L]
#define RSCAN0RMPTR18LL RSCAN0.RMPTR18.UINT8[LL]
#define RSCAN0RMPTR18LH RSCAN0.RMPTR18.UINT8[LH]
#define RSCAN0RMPTR18H RSCAN0.RMPTR18.UINT16[H]
#define RSCAN0RMPTR18HL RSCAN0.RMPTR18.UINT8[HL]
#define RSCAN0RMPTR18HH RSCAN0.RMPTR18.UINT8[HH]
#define RSCAN0RMDF018 RSCAN0.RMDF018.UINT32
#define RSCAN0RMDF018L RSCAN0.RMDF018.UINT16[L]
#define RSCAN0RMDF018LL RSCAN0.RMDF018.UINT8[LL]
#define RSCAN0RMDF018LH RSCAN0.RMDF018.UINT8[LH]
#define RSCAN0RMDF018H RSCAN0.RMDF018.UINT16[H]
#define RSCAN0RMDF018HL RSCAN0.RMDF018.UINT8[HL]
#define RSCAN0RMDF018HH RSCAN0.RMDF018.UINT8[HH]
#define RSCAN0RMDF118 RSCAN0.RMDF118.UINT32
#define RSCAN0RMDF118L RSCAN0.RMDF118.UINT16[L]
#define RSCAN0RMDF118LL RSCAN0.RMDF118.UINT8[LL]
#define RSCAN0RMDF118LH RSCAN0.RMDF118.UINT8[LH]
#define RSCAN0RMDF118H RSCAN0.RMDF118.UINT16[H]
#define RSCAN0RMDF118HL RSCAN0.RMDF118.UINT8[HL]
#define RSCAN0RMDF118HH RSCAN0.RMDF118.UINT8[HH]
#define RSCAN0RMID19 RSCAN0.RMID19.UINT32
#define RSCAN0RMID19L RSCAN0.RMID19.UINT16[L]
#define RSCAN0RMID19LL RSCAN0.RMID19.UINT8[LL]
#define RSCAN0RMID19LH RSCAN0.RMID19.UINT8[LH]
#define RSCAN0RMID19H RSCAN0.RMID19.UINT16[H]
#define RSCAN0RMID19HL RSCAN0.RMID19.UINT8[HL]
#define RSCAN0RMID19HH RSCAN0.RMID19.UINT8[HH]
#define RSCAN0RMPTR19 RSCAN0.RMPTR19.UINT32
#define RSCAN0RMPTR19L RSCAN0.RMPTR19.UINT16[L]
#define RSCAN0RMPTR19LL RSCAN0.RMPTR19.UINT8[LL]
#define RSCAN0RMPTR19LH RSCAN0.RMPTR19.UINT8[LH]
#define RSCAN0RMPTR19H RSCAN0.RMPTR19.UINT16[H]
#define RSCAN0RMPTR19HL RSCAN0.RMPTR19.UINT8[HL]
#define RSCAN0RMPTR19HH RSCAN0.RMPTR19.UINT8[HH]
#define RSCAN0RMDF019 RSCAN0.RMDF019.UINT32
#define RSCAN0RMDF019L RSCAN0.RMDF019.UINT16[L]
#define RSCAN0RMDF019LL RSCAN0.RMDF019.UINT8[LL]
#define RSCAN0RMDF019LH RSCAN0.RMDF019.UINT8[LH]
#define RSCAN0RMDF019H RSCAN0.RMDF019.UINT16[H]
#define RSCAN0RMDF019HL RSCAN0.RMDF019.UINT8[HL]
#define RSCAN0RMDF019HH RSCAN0.RMDF019.UINT8[HH]
#define RSCAN0RMDF119 RSCAN0.RMDF119.UINT32
#define RSCAN0RMDF119L RSCAN0.RMDF119.UINT16[L]
#define RSCAN0RMDF119LL RSCAN0.RMDF119.UINT8[LL]
#define RSCAN0RMDF119LH RSCAN0.RMDF119.UINT8[LH]
#define RSCAN0RMDF119H RSCAN0.RMDF119.UINT16[H]
#define RSCAN0RMDF119HL RSCAN0.RMDF119.UINT8[HL]
#define RSCAN0RMDF119HH RSCAN0.RMDF119.UINT8[HH]
#define RSCAN0RMID20 RSCAN0.RMID20.UINT32
#define RSCAN0RMID20L RSCAN0.RMID20.UINT16[L]
#define RSCAN0RMID20LL RSCAN0.RMID20.UINT8[LL]
#define RSCAN0RMID20LH RSCAN0.RMID20.UINT8[LH]
#define RSCAN0RMID20H RSCAN0.RMID20.UINT16[H]
#define RSCAN0RMID20HL RSCAN0.RMID20.UINT8[HL]
#define RSCAN0RMID20HH RSCAN0.RMID20.UINT8[HH]
#define RSCAN0RMPTR20 RSCAN0.RMPTR20.UINT32
#define RSCAN0RMPTR20L RSCAN0.RMPTR20.UINT16[L]
#define RSCAN0RMPTR20LL RSCAN0.RMPTR20.UINT8[LL]
#define RSCAN0RMPTR20LH RSCAN0.RMPTR20.UINT8[LH]
#define RSCAN0RMPTR20H RSCAN0.RMPTR20.UINT16[H]
#define RSCAN0RMPTR20HL RSCAN0.RMPTR20.UINT8[HL]
#define RSCAN0RMPTR20HH RSCAN0.RMPTR20.UINT8[HH]
#define RSCAN0RMDF020 RSCAN0.RMDF020.UINT32
#define RSCAN0RMDF020L RSCAN0.RMDF020.UINT16[L]
#define RSCAN0RMDF020LL RSCAN0.RMDF020.UINT8[LL]
#define RSCAN0RMDF020LH RSCAN0.RMDF020.UINT8[LH]
#define RSCAN0RMDF020H RSCAN0.RMDF020.UINT16[H]
#define RSCAN0RMDF020HL RSCAN0.RMDF020.UINT8[HL]
#define RSCAN0RMDF020HH RSCAN0.RMDF020.UINT8[HH]
#define RSCAN0RMDF120 RSCAN0.RMDF120.UINT32
#define RSCAN0RMDF120L RSCAN0.RMDF120.UINT16[L]
#define RSCAN0RMDF120LL RSCAN0.RMDF120.UINT8[LL]
#define RSCAN0RMDF120LH RSCAN0.RMDF120.UINT8[LH]
#define RSCAN0RMDF120H RSCAN0.RMDF120.UINT16[H]
#define RSCAN0RMDF120HL RSCAN0.RMDF120.UINT8[HL]
#define RSCAN0RMDF120HH RSCAN0.RMDF120.UINT8[HH]
#define RSCAN0RMID21 RSCAN0.RMID21.UINT32
#define RSCAN0RMID21L RSCAN0.RMID21.UINT16[L]
#define RSCAN0RMID21LL RSCAN0.RMID21.UINT8[LL]
#define RSCAN0RMID21LH RSCAN0.RMID21.UINT8[LH]
#define RSCAN0RMID21H RSCAN0.RMID21.UINT16[H]
#define RSCAN0RMID21HL RSCAN0.RMID21.UINT8[HL]
#define RSCAN0RMID21HH RSCAN0.RMID21.UINT8[HH]
#define RSCAN0RMPTR21 RSCAN0.RMPTR21.UINT32
#define RSCAN0RMPTR21L RSCAN0.RMPTR21.UINT16[L]
#define RSCAN0RMPTR21LL RSCAN0.RMPTR21.UINT8[LL]
#define RSCAN0RMPTR21LH RSCAN0.RMPTR21.UINT8[LH]
#define RSCAN0RMPTR21H RSCAN0.RMPTR21.UINT16[H]
#define RSCAN0RMPTR21HL RSCAN0.RMPTR21.UINT8[HL]
#define RSCAN0RMPTR21HH RSCAN0.RMPTR21.UINT8[HH]
#define RSCAN0RMDF021 RSCAN0.RMDF021.UINT32
#define RSCAN0RMDF021L RSCAN0.RMDF021.UINT16[L]
#define RSCAN0RMDF021LL RSCAN0.RMDF021.UINT8[LL]
#define RSCAN0RMDF021LH RSCAN0.RMDF021.UINT8[LH]
#define RSCAN0RMDF021H RSCAN0.RMDF021.UINT16[H]
#define RSCAN0RMDF021HL RSCAN0.RMDF021.UINT8[HL]
#define RSCAN0RMDF021HH RSCAN0.RMDF021.UINT8[HH]
#define RSCAN0RMDF121 RSCAN0.RMDF121.UINT32
#define RSCAN0RMDF121L RSCAN0.RMDF121.UINT16[L]
#define RSCAN0RMDF121LL RSCAN0.RMDF121.UINT8[LL]
#define RSCAN0RMDF121LH RSCAN0.RMDF121.UINT8[LH]
#define RSCAN0RMDF121H RSCAN0.RMDF121.UINT16[H]
#define RSCAN0RMDF121HL RSCAN0.RMDF121.UINT8[HL]
#define RSCAN0RMDF121HH RSCAN0.RMDF121.UINT8[HH]
#define RSCAN0RMID22 RSCAN0.RMID22.UINT32
#define RSCAN0RMID22L RSCAN0.RMID22.UINT16[L]
#define RSCAN0RMID22LL RSCAN0.RMID22.UINT8[LL]
#define RSCAN0RMID22LH RSCAN0.RMID22.UINT8[LH]
#define RSCAN0RMID22H RSCAN0.RMID22.UINT16[H]
#define RSCAN0RMID22HL RSCAN0.RMID22.UINT8[HL]
#define RSCAN0RMID22HH RSCAN0.RMID22.UINT8[HH]
#define RSCAN0RMPTR22 RSCAN0.RMPTR22.UINT32
#define RSCAN0RMPTR22L RSCAN0.RMPTR22.UINT16[L]
#define RSCAN0RMPTR22LL RSCAN0.RMPTR22.UINT8[LL]
#define RSCAN0RMPTR22LH RSCAN0.RMPTR22.UINT8[LH]
#define RSCAN0RMPTR22H RSCAN0.RMPTR22.UINT16[H]
#define RSCAN0RMPTR22HL RSCAN0.RMPTR22.UINT8[HL]
#define RSCAN0RMPTR22HH RSCAN0.RMPTR22.UINT8[HH]
#define RSCAN0RMDF022 RSCAN0.RMDF022.UINT32
#define RSCAN0RMDF022L RSCAN0.RMDF022.UINT16[L]
#define RSCAN0RMDF022LL RSCAN0.RMDF022.UINT8[LL]
#define RSCAN0RMDF022LH RSCAN0.RMDF022.UINT8[LH]
#define RSCAN0RMDF022H RSCAN0.RMDF022.UINT16[H]
#define RSCAN0RMDF022HL RSCAN0.RMDF022.UINT8[HL]
#define RSCAN0RMDF022HH RSCAN0.RMDF022.UINT8[HH]
#define RSCAN0RMDF122 RSCAN0.RMDF122.UINT32
#define RSCAN0RMDF122L RSCAN0.RMDF122.UINT16[L]
#define RSCAN0RMDF122LL RSCAN0.RMDF122.UINT8[LL]
#define RSCAN0RMDF122LH RSCAN0.RMDF122.UINT8[LH]
#define RSCAN0RMDF122H RSCAN0.RMDF122.UINT16[H]
#define RSCAN0RMDF122HL RSCAN0.RMDF122.UINT8[HL]
#define RSCAN0RMDF122HH RSCAN0.RMDF122.UINT8[HH]
#define RSCAN0RMID23 RSCAN0.RMID23.UINT32
#define RSCAN0RMID23L RSCAN0.RMID23.UINT16[L]
#define RSCAN0RMID23LL RSCAN0.RMID23.UINT8[LL]
#define RSCAN0RMID23LH RSCAN0.RMID23.UINT8[LH]
#define RSCAN0RMID23H RSCAN0.RMID23.UINT16[H]
#define RSCAN0RMID23HL RSCAN0.RMID23.UINT8[HL]
#define RSCAN0RMID23HH RSCAN0.RMID23.UINT8[HH]
#define RSCAN0RMPTR23 RSCAN0.RMPTR23.UINT32
#define RSCAN0RMPTR23L RSCAN0.RMPTR23.UINT16[L]
#define RSCAN0RMPTR23LL RSCAN0.RMPTR23.UINT8[LL]
#define RSCAN0RMPTR23LH RSCAN0.RMPTR23.UINT8[LH]
#define RSCAN0RMPTR23H RSCAN0.RMPTR23.UINT16[H]
#define RSCAN0RMPTR23HL RSCAN0.RMPTR23.UINT8[HL]
#define RSCAN0RMPTR23HH RSCAN0.RMPTR23.UINT8[HH]
#define RSCAN0RMDF023 RSCAN0.RMDF023.UINT32
#define RSCAN0RMDF023L RSCAN0.RMDF023.UINT16[L]
#define RSCAN0RMDF023LL RSCAN0.RMDF023.UINT8[LL]
#define RSCAN0RMDF023LH RSCAN0.RMDF023.UINT8[LH]
#define RSCAN0RMDF023H RSCAN0.RMDF023.UINT16[H]
#define RSCAN0RMDF023HL RSCAN0.RMDF023.UINT8[HL]
#define RSCAN0RMDF023HH RSCAN0.RMDF023.UINT8[HH]
#define RSCAN0RMDF123 RSCAN0.RMDF123.UINT32
#define RSCAN0RMDF123L RSCAN0.RMDF123.UINT16[L]
#define RSCAN0RMDF123LL RSCAN0.RMDF123.UINT8[LL]
#define RSCAN0RMDF123LH RSCAN0.RMDF123.UINT8[LH]
#define RSCAN0RMDF123H RSCAN0.RMDF123.UINT16[H]
#define RSCAN0RMDF123HL RSCAN0.RMDF123.UINT8[HL]
#define RSCAN0RMDF123HH RSCAN0.RMDF123.UINT8[HH]
#define RSCAN0RMID24 RSCAN0.RMID24.UINT32
#define RSCAN0RMID24L RSCAN0.RMID24.UINT16[L]
#define RSCAN0RMID24LL RSCAN0.RMID24.UINT8[LL]
#define RSCAN0RMID24LH RSCAN0.RMID24.UINT8[LH]
#define RSCAN0RMID24H RSCAN0.RMID24.UINT16[H]
#define RSCAN0RMID24HL RSCAN0.RMID24.UINT8[HL]
#define RSCAN0RMID24HH RSCAN0.RMID24.UINT8[HH]
#define RSCAN0RMPTR24 RSCAN0.RMPTR24.UINT32
#define RSCAN0RMPTR24L RSCAN0.RMPTR24.UINT16[L]
#define RSCAN0RMPTR24LL RSCAN0.RMPTR24.UINT8[LL]
#define RSCAN0RMPTR24LH RSCAN0.RMPTR24.UINT8[LH]
#define RSCAN0RMPTR24H RSCAN0.RMPTR24.UINT16[H]
#define RSCAN0RMPTR24HL RSCAN0.RMPTR24.UINT8[HL]
#define RSCAN0RMPTR24HH RSCAN0.RMPTR24.UINT8[HH]
#define RSCAN0RMDF024 RSCAN0.RMDF024.UINT32
#define RSCAN0RMDF024L RSCAN0.RMDF024.UINT16[L]
#define RSCAN0RMDF024LL RSCAN0.RMDF024.UINT8[LL]
#define RSCAN0RMDF024LH RSCAN0.RMDF024.UINT8[LH]
#define RSCAN0RMDF024H RSCAN0.RMDF024.UINT16[H]
#define RSCAN0RMDF024HL RSCAN0.RMDF024.UINT8[HL]
#define RSCAN0RMDF024HH RSCAN0.RMDF024.UINT8[HH]
#define RSCAN0RMDF124 RSCAN0.RMDF124.UINT32
#define RSCAN0RMDF124L RSCAN0.RMDF124.UINT16[L]
#define RSCAN0RMDF124LL RSCAN0.RMDF124.UINT8[LL]
#define RSCAN0RMDF124LH RSCAN0.RMDF124.UINT8[LH]
#define RSCAN0RMDF124H RSCAN0.RMDF124.UINT16[H]
#define RSCAN0RMDF124HL RSCAN0.RMDF124.UINT8[HL]
#define RSCAN0RMDF124HH RSCAN0.RMDF124.UINT8[HH]
#define RSCAN0RMID25 RSCAN0.RMID25.UINT32
#define RSCAN0RMID25L RSCAN0.RMID25.UINT16[L]
#define RSCAN0RMID25LL RSCAN0.RMID25.UINT8[LL]
#define RSCAN0RMID25LH RSCAN0.RMID25.UINT8[LH]
#define RSCAN0RMID25H RSCAN0.RMID25.UINT16[H]
#define RSCAN0RMID25HL RSCAN0.RMID25.UINT8[HL]
#define RSCAN0RMID25HH RSCAN0.RMID25.UINT8[HH]
#define RSCAN0RMPTR25 RSCAN0.RMPTR25.UINT32
#define RSCAN0RMPTR25L RSCAN0.RMPTR25.UINT16[L]
#define RSCAN0RMPTR25LL RSCAN0.RMPTR25.UINT8[LL]
#define RSCAN0RMPTR25LH RSCAN0.RMPTR25.UINT8[LH]
#define RSCAN0RMPTR25H RSCAN0.RMPTR25.UINT16[H]
#define RSCAN0RMPTR25HL RSCAN0.RMPTR25.UINT8[HL]
#define RSCAN0RMPTR25HH RSCAN0.RMPTR25.UINT8[HH]
#define RSCAN0RMDF025 RSCAN0.RMDF025.UINT32
#define RSCAN0RMDF025L RSCAN0.RMDF025.UINT16[L]
#define RSCAN0RMDF025LL RSCAN0.RMDF025.UINT8[LL]
#define RSCAN0RMDF025LH RSCAN0.RMDF025.UINT8[LH]
#define RSCAN0RMDF025H RSCAN0.RMDF025.UINT16[H]
#define RSCAN0RMDF025HL RSCAN0.RMDF025.UINT8[HL]
#define RSCAN0RMDF025HH RSCAN0.RMDF025.UINT8[HH]
#define RSCAN0RMDF125 RSCAN0.RMDF125.UINT32
#define RSCAN0RMDF125L RSCAN0.RMDF125.UINT16[L]
#define RSCAN0RMDF125LL RSCAN0.RMDF125.UINT8[LL]
#define RSCAN0RMDF125LH RSCAN0.RMDF125.UINT8[LH]
#define RSCAN0RMDF125H RSCAN0.RMDF125.UINT16[H]
#define RSCAN0RMDF125HL RSCAN0.RMDF125.UINT8[HL]
#define RSCAN0RMDF125HH RSCAN0.RMDF125.UINT8[HH]
#define RSCAN0RMID26 RSCAN0.RMID26.UINT32
#define RSCAN0RMID26L RSCAN0.RMID26.UINT16[L]
#define RSCAN0RMID26LL RSCAN0.RMID26.UINT8[LL]
#define RSCAN0RMID26LH RSCAN0.RMID26.UINT8[LH]
#define RSCAN0RMID26H RSCAN0.RMID26.UINT16[H]
#define RSCAN0RMID26HL RSCAN0.RMID26.UINT8[HL]
#define RSCAN0RMID26HH RSCAN0.RMID26.UINT8[HH]
#define RSCAN0RMPTR26 RSCAN0.RMPTR26.UINT32
#define RSCAN0RMPTR26L RSCAN0.RMPTR26.UINT16[L]
#define RSCAN0RMPTR26LL RSCAN0.RMPTR26.UINT8[LL]
#define RSCAN0RMPTR26LH RSCAN0.RMPTR26.UINT8[LH]
#define RSCAN0RMPTR26H RSCAN0.RMPTR26.UINT16[H]
#define RSCAN0RMPTR26HL RSCAN0.RMPTR26.UINT8[HL]
#define RSCAN0RMPTR26HH RSCAN0.RMPTR26.UINT8[HH]
#define RSCAN0RMDF026 RSCAN0.RMDF026.UINT32
#define RSCAN0RMDF026L RSCAN0.RMDF026.UINT16[L]
#define RSCAN0RMDF026LL RSCAN0.RMDF026.UINT8[LL]
#define RSCAN0RMDF026LH RSCAN0.RMDF026.UINT8[LH]
#define RSCAN0RMDF026H RSCAN0.RMDF026.UINT16[H]
#define RSCAN0RMDF026HL RSCAN0.RMDF026.UINT8[HL]
#define RSCAN0RMDF026HH RSCAN0.RMDF026.UINT8[HH]
#define RSCAN0RMDF126 RSCAN0.RMDF126.UINT32
#define RSCAN0RMDF126L RSCAN0.RMDF126.UINT16[L]
#define RSCAN0RMDF126LL RSCAN0.RMDF126.UINT8[LL]
#define RSCAN0RMDF126LH RSCAN0.RMDF126.UINT8[LH]
#define RSCAN0RMDF126H RSCAN0.RMDF126.UINT16[H]
#define RSCAN0RMDF126HL RSCAN0.RMDF126.UINT8[HL]
#define RSCAN0RMDF126HH RSCAN0.RMDF126.UINT8[HH]
#define RSCAN0RMID27 RSCAN0.RMID27.UINT32
#define RSCAN0RMID27L RSCAN0.RMID27.UINT16[L]
#define RSCAN0RMID27LL RSCAN0.RMID27.UINT8[LL]
#define RSCAN0RMID27LH RSCAN0.RMID27.UINT8[LH]
#define RSCAN0RMID27H RSCAN0.RMID27.UINT16[H]
#define RSCAN0RMID27HL RSCAN0.RMID27.UINT8[HL]
#define RSCAN0RMID27HH RSCAN0.RMID27.UINT8[HH]
#define RSCAN0RMPTR27 RSCAN0.RMPTR27.UINT32
#define RSCAN0RMPTR27L RSCAN0.RMPTR27.UINT16[L]
#define RSCAN0RMPTR27LL RSCAN0.RMPTR27.UINT8[LL]
#define RSCAN0RMPTR27LH RSCAN0.RMPTR27.UINT8[LH]
#define RSCAN0RMPTR27H RSCAN0.RMPTR27.UINT16[H]
#define RSCAN0RMPTR27HL RSCAN0.RMPTR27.UINT8[HL]
#define RSCAN0RMPTR27HH RSCAN0.RMPTR27.UINT8[HH]
#define RSCAN0RMDF027 RSCAN0.RMDF027.UINT32
#define RSCAN0RMDF027L RSCAN0.RMDF027.UINT16[L]
#define RSCAN0RMDF027LL RSCAN0.RMDF027.UINT8[LL]
#define RSCAN0RMDF027LH RSCAN0.RMDF027.UINT8[LH]
#define RSCAN0RMDF027H RSCAN0.RMDF027.UINT16[H]
#define RSCAN0RMDF027HL RSCAN0.RMDF027.UINT8[HL]
#define RSCAN0RMDF027HH RSCAN0.RMDF027.UINT8[HH]
#define RSCAN0RMDF127 RSCAN0.RMDF127.UINT32
#define RSCAN0RMDF127L RSCAN0.RMDF127.UINT16[L]
#define RSCAN0RMDF127LL RSCAN0.RMDF127.UINT8[LL]
#define RSCAN0RMDF127LH RSCAN0.RMDF127.UINT8[LH]
#define RSCAN0RMDF127H RSCAN0.RMDF127.UINT16[H]
#define RSCAN0RMDF127HL RSCAN0.RMDF127.UINT8[HL]
#define RSCAN0RMDF127HH RSCAN0.RMDF127.UINT8[HH]
#define RSCAN0RMID28 RSCAN0.RMID28.UINT32
#define RSCAN0RMID28L RSCAN0.RMID28.UINT16[L]
#define RSCAN0RMID28LL RSCAN0.RMID28.UINT8[LL]
#define RSCAN0RMID28LH RSCAN0.RMID28.UINT8[LH]
#define RSCAN0RMID28H RSCAN0.RMID28.UINT16[H]
#define RSCAN0RMID28HL RSCAN0.RMID28.UINT8[HL]
#define RSCAN0RMID28HH RSCAN0.RMID28.UINT8[HH]
#define RSCAN0RMPTR28 RSCAN0.RMPTR28.UINT32
#define RSCAN0RMPTR28L RSCAN0.RMPTR28.UINT16[L]
#define RSCAN0RMPTR28LL RSCAN0.RMPTR28.UINT8[LL]
#define RSCAN0RMPTR28LH RSCAN0.RMPTR28.UINT8[LH]
#define RSCAN0RMPTR28H RSCAN0.RMPTR28.UINT16[H]
#define RSCAN0RMPTR28HL RSCAN0.RMPTR28.UINT8[HL]
#define RSCAN0RMPTR28HH RSCAN0.RMPTR28.UINT8[HH]
#define RSCAN0RMDF028 RSCAN0.RMDF028.UINT32
#define RSCAN0RMDF028L RSCAN0.RMDF028.UINT16[L]
#define RSCAN0RMDF028LL RSCAN0.RMDF028.UINT8[LL]
#define RSCAN0RMDF028LH RSCAN0.RMDF028.UINT8[LH]
#define RSCAN0RMDF028H RSCAN0.RMDF028.UINT16[H]
#define RSCAN0RMDF028HL RSCAN0.RMDF028.UINT8[HL]
#define RSCAN0RMDF028HH RSCAN0.RMDF028.UINT8[HH]
#define RSCAN0RMDF128 RSCAN0.RMDF128.UINT32
#define RSCAN0RMDF128L RSCAN0.RMDF128.UINT16[L]
#define RSCAN0RMDF128LL RSCAN0.RMDF128.UINT8[LL]
#define RSCAN0RMDF128LH RSCAN0.RMDF128.UINT8[LH]
#define RSCAN0RMDF128H RSCAN0.RMDF128.UINT16[H]
#define RSCAN0RMDF128HL RSCAN0.RMDF128.UINT8[HL]
#define RSCAN0RMDF128HH RSCAN0.RMDF128.UINT8[HH]
#define RSCAN0RMID29 RSCAN0.RMID29.UINT32
#define RSCAN0RMID29L RSCAN0.RMID29.UINT16[L]
#define RSCAN0RMID29LL RSCAN0.RMID29.UINT8[LL]
#define RSCAN0RMID29LH RSCAN0.RMID29.UINT8[LH]
#define RSCAN0RMID29H RSCAN0.RMID29.UINT16[H]
#define RSCAN0RMID29HL RSCAN0.RMID29.UINT8[HL]
#define RSCAN0RMID29HH RSCAN0.RMID29.UINT8[HH]
#define RSCAN0RMPTR29 RSCAN0.RMPTR29.UINT32
#define RSCAN0RMPTR29L RSCAN0.RMPTR29.UINT16[L]
#define RSCAN0RMPTR29LL RSCAN0.RMPTR29.UINT8[LL]
#define RSCAN0RMPTR29LH RSCAN0.RMPTR29.UINT8[LH]
#define RSCAN0RMPTR29H RSCAN0.RMPTR29.UINT16[H]
#define RSCAN0RMPTR29HL RSCAN0.RMPTR29.UINT8[HL]
#define RSCAN0RMPTR29HH RSCAN0.RMPTR29.UINT8[HH]
#define RSCAN0RMDF029 RSCAN0.RMDF029.UINT32
#define RSCAN0RMDF029L RSCAN0.RMDF029.UINT16[L]
#define RSCAN0RMDF029LL RSCAN0.RMDF029.UINT8[LL]
#define RSCAN0RMDF029LH RSCAN0.RMDF029.UINT8[LH]
#define RSCAN0RMDF029H RSCAN0.RMDF029.UINT16[H]
#define RSCAN0RMDF029HL RSCAN0.RMDF029.UINT8[HL]
#define RSCAN0RMDF029HH RSCAN0.RMDF029.UINT8[HH]
#define RSCAN0RMDF129 RSCAN0.RMDF129.UINT32
#define RSCAN0RMDF129L RSCAN0.RMDF129.UINT16[L]
#define RSCAN0RMDF129LL RSCAN0.RMDF129.UINT8[LL]
#define RSCAN0RMDF129LH RSCAN0.RMDF129.UINT8[LH]
#define RSCAN0RMDF129H RSCAN0.RMDF129.UINT16[H]
#define RSCAN0RMDF129HL RSCAN0.RMDF129.UINT8[HL]
#define RSCAN0RMDF129HH RSCAN0.RMDF129.UINT8[HH]
#define RSCAN0RMID30 RSCAN0.RMID30.UINT32
#define RSCAN0RMID30L RSCAN0.RMID30.UINT16[L]
#define RSCAN0RMID30LL RSCAN0.RMID30.UINT8[LL]
#define RSCAN0RMID30LH RSCAN0.RMID30.UINT8[LH]
#define RSCAN0RMID30H RSCAN0.RMID30.UINT16[H]
#define RSCAN0RMID30HL RSCAN0.RMID30.UINT8[HL]
#define RSCAN0RMID30HH RSCAN0.RMID30.UINT8[HH]
#define RSCAN0RMPTR30 RSCAN0.RMPTR30.UINT32
#define RSCAN0RMPTR30L RSCAN0.RMPTR30.UINT16[L]
#define RSCAN0RMPTR30LL RSCAN0.RMPTR30.UINT8[LL]
#define RSCAN0RMPTR30LH RSCAN0.RMPTR30.UINT8[LH]
#define RSCAN0RMPTR30H RSCAN0.RMPTR30.UINT16[H]
#define RSCAN0RMPTR30HL RSCAN0.RMPTR30.UINT8[HL]
#define RSCAN0RMPTR30HH RSCAN0.RMPTR30.UINT8[HH]
#define RSCAN0RMDF030 RSCAN0.RMDF030.UINT32
#define RSCAN0RMDF030L RSCAN0.RMDF030.UINT16[L]
#define RSCAN0RMDF030LL RSCAN0.RMDF030.UINT8[LL]
#define RSCAN0RMDF030LH RSCAN0.RMDF030.UINT8[LH]
#define RSCAN0RMDF030H RSCAN0.RMDF030.UINT16[H]
#define RSCAN0RMDF030HL RSCAN0.RMDF030.UINT8[HL]
#define RSCAN0RMDF030HH RSCAN0.RMDF030.UINT8[HH]
#define RSCAN0RMDF130 RSCAN0.RMDF130.UINT32
#define RSCAN0RMDF130L RSCAN0.RMDF130.UINT16[L]
#define RSCAN0RMDF130LL RSCAN0.RMDF130.UINT8[LL]
#define RSCAN0RMDF130LH RSCAN0.RMDF130.UINT8[LH]
#define RSCAN0RMDF130H RSCAN0.RMDF130.UINT16[H]
#define RSCAN0RMDF130HL RSCAN0.RMDF130.UINT8[HL]
#define RSCAN0RMDF130HH RSCAN0.RMDF130.UINT8[HH]
#define RSCAN0RMID31 RSCAN0.RMID31.UINT32
#define RSCAN0RMID31L RSCAN0.RMID31.UINT16[L]
#define RSCAN0RMID31LL RSCAN0.RMID31.UINT8[LL]
#define RSCAN0RMID31LH RSCAN0.RMID31.UINT8[LH]
#define RSCAN0RMID31H RSCAN0.RMID31.UINT16[H]
#define RSCAN0RMID31HL RSCAN0.RMID31.UINT8[HL]
#define RSCAN0RMID31HH RSCAN0.RMID31.UINT8[HH]
#define RSCAN0RMPTR31 RSCAN0.RMPTR31.UINT32
#define RSCAN0RMPTR31L RSCAN0.RMPTR31.UINT16[L]
#define RSCAN0RMPTR31LL RSCAN0.RMPTR31.UINT8[LL]
#define RSCAN0RMPTR31LH RSCAN0.RMPTR31.UINT8[LH]
#define RSCAN0RMPTR31H RSCAN0.RMPTR31.UINT16[H]
#define RSCAN0RMPTR31HL RSCAN0.RMPTR31.UINT8[HL]
#define RSCAN0RMPTR31HH RSCAN0.RMPTR31.UINT8[HH]
#define RSCAN0RMDF031 RSCAN0.RMDF031.UINT32
#define RSCAN0RMDF031L RSCAN0.RMDF031.UINT16[L]
#define RSCAN0RMDF031LL RSCAN0.RMDF031.UINT8[LL]
#define RSCAN0RMDF031LH RSCAN0.RMDF031.UINT8[LH]
#define RSCAN0RMDF031H RSCAN0.RMDF031.UINT16[H]
#define RSCAN0RMDF031HL RSCAN0.RMDF031.UINT8[HL]
#define RSCAN0RMDF031HH RSCAN0.RMDF031.UINT8[HH]
#define RSCAN0RMDF131 RSCAN0.RMDF131.UINT32
#define RSCAN0RMDF131L RSCAN0.RMDF131.UINT16[L]
#define RSCAN0RMDF131LL RSCAN0.RMDF131.UINT8[LL]
#define RSCAN0RMDF131LH RSCAN0.RMDF131.UINT8[LH]
#define RSCAN0RMDF131H RSCAN0.RMDF131.UINT16[H]
#define RSCAN0RMDF131HL RSCAN0.RMDF131.UINT8[HL]
#define RSCAN0RMDF131HH RSCAN0.RMDF131.UINT8[HH]
#define RSCAN0RMID32 RSCAN0.RMID32.UINT32
#define RSCAN0RMID32L RSCAN0.RMID32.UINT16[L]
#define RSCAN0RMID32LL RSCAN0.RMID32.UINT8[LL]
#define RSCAN0RMID32LH RSCAN0.RMID32.UINT8[LH]
#define RSCAN0RMID32H RSCAN0.RMID32.UINT16[H]
#define RSCAN0RMID32HL RSCAN0.RMID32.UINT8[HL]
#define RSCAN0RMID32HH RSCAN0.RMID32.UINT8[HH]
#define RSCAN0RMPTR32 RSCAN0.RMPTR32.UINT32
#define RSCAN0RMPTR32L RSCAN0.RMPTR32.UINT16[L]
#define RSCAN0RMPTR32LL RSCAN0.RMPTR32.UINT8[LL]
#define RSCAN0RMPTR32LH RSCAN0.RMPTR32.UINT8[LH]
#define RSCAN0RMPTR32H RSCAN0.RMPTR32.UINT16[H]
#define RSCAN0RMPTR32HL RSCAN0.RMPTR32.UINT8[HL]
#define RSCAN0RMPTR32HH RSCAN0.RMPTR32.UINT8[HH]
#define RSCAN0RMDF032 RSCAN0.RMDF032.UINT32
#define RSCAN0RMDF032L RSCAN0.RMDF032.UINT16[L]
#define RSCAN0RMDF032LL RSCAN0.RMDF032.UINT8[LL]
#define RSCAN0RMDF032LH RSCAN0.RMDF032.UINT8[LH]
#define RSCAN0RMDF032H RSCAN0.RMDF032.UINT16[H]
#define RSCAN0RMDF032HL RSCAN0.RMDF032.UINT8[HL]
#define RSCAN0RMDF032HH RSCAN0.RMDF032.UINT8[HH]
#define RSCAN0RMDF132 RSCAN0.RMDF132.UINT32
#define RSCAN0RMDF132L RSCAN0.RMDF132.UINT16[L]
#define RSCAN0RMDF132LL RSCAN0.RMDF132.UINT8[LL]
#define RSCAN0RMDF132LH RSCAN0.RMDF132.UINT8[LH]
#define RSCAN0RMDF132H RSCAN0.RMDF132.UINT16[H]
#define RSCAN0RMDF132HL RSCAN0.RMDF132.UINT8[HL]
#define RSCAN0RMDF132HH RSCAN0.RMDF132.UINT8[HH]
#define RSCAN0RMID33 RSCAN0.RMID33.UINT32
#define RSCAN0RMID33L RSCAN0.RMID33.UINT16[L]
#define RSCAN0RMID33LL RSCAN0.RMID33.UINT8[LL]
#define RSCAN0RMID33LH RSCAN0.RMID33.UINT8[LH]
#define RSCAN0RMID33H RSCAN0.RMID33.UINT16[H]
#define RSCAN0RMID33HL RSCAN0.RMID33.UINT8[HL]
#define RSCAN0RMID33HH RSCAN0.RMID33.UINT8[HH]
#define RSCAN0RMPTR33 RSCAN0.RMPTR33.UINT32
#define RSCAN0RMPTR33L RSCAN0.RMPTR33.UINT16[L]
#define RSCAN0RMPTR33LL RSCAN0.RMPTR33.UINT8[LL]
#define RSCAN0RMPTR33LH RSCAN0.RMPTR33.UINT8[LH]
#define RSCAN0RMPTR33H RSCAN0.RMPTR33.UINT16[H]
#define RSCAN0RMPTR33HL RSCAN0.RMPTR33.UINT8[HL]
#define RSCAN0RMPTR33HH RSCAN0.RMPTR33.UINT8[HH]
#define RSCAN0RMDF033 RSCAN0.RMDF033.UINT32
#define RSCAN0RMDF033L RSCAN0.RMDF033.UINT16[L]
#define RSCAN0RMDF033LL RSCAN0.RMDF033.UINT8[LL]
#define RSCAN0RMDF033LH RSCAN0.RMDF033.UINT8[LH]
#define RSCAN0RMDF033H RSCAN0.RMDF033.UINT16[H]
#define RSCAN0RMDF033HL RSCAN0.RMDF033.UINT8[HL]
#define RSCAN0RMDF033HH RSCAN0.RMDF033.UINT8[HH]
#define RSCAN0RMDF133 RSCAN0.RMDF133.UINT32
#define RSCAN0RMDF133L RSCAN0.RMDF133.UINT16[L]
#define RSCAN0RMDF133LL RSCAN0.RMDF133.UINT8[LL]
#define RSCAN0RMDF133LH RSCAN0.RMDF133.UINT8[LH]
#define RSCAN0RMDF133H RSCAN0.RMDF133.UINT16[H]
#define RSCAN0RMDF133HL RSCAN0.RMDF133.UINT8[HL]
#define RSCAN0RMDF133HH RSCAN0.RMDF133.UINT8[HH]
#define RSCAN0RMID34 RSCAN0.RMID34.UINT32
#define RSCAN0RMID34L RSCAN0.RMID34.UINT16[L]
#define RSCAN0RMID34LL RSCAN0.RMID34.UINT8[LL]
#define RSCAN0RMID34LH RSCAN0.RMID34.UINT8[LH]
#define RSCAN0RMID34H RSCAN0.RMID34.UINT16[H]
#define RSCAN0RMID34HL RSCAN0.RMID34.UINT8[HL]
#define RSCAN0RMID34HH RSCAN0.RMID34.UINT8[HH]
#define RSCAN0RMPTR34 RSCAN0.RMPTR34.UINT32
#define RSCAN0RMPTR34L RSCAN0.RMPTR34.UINT16[L]
#define RSCAN0RMPTR34LL RSCAN0.RMPTR34.UINT8[LL]
#define RSCAN0RMPTR34LH RSCAN0.RMPTR34.UINT8[LH]
#define RSCAN0RMPTR34H RSCAN0.RMPTR34.UINT16[H]
#define RSCAN0RMPTR34HL RSCAN0.RMPTR34.UINT8[HL]
#define RSCAN0RMPTR34HH RSCAN0.RMPTR34.UINT8[HH]
#define RSCAN0RMDF034 RSCAN0.RMDF034.UINT32
#define RSCAN0RMDF034L RSCAN0.RMDF034.UINT16[L]
#define RSCAN0RMDF034LL RSCAN0.RMDF034.UINT8[LL]
#define RSCAN0RMDF034LH RSCAN0.RMDF034.UINT8[LH]
#define RSCAN0RMDF034H RSCAN0.RMDF034.UINT16[H]
#define RSCAN0RMDF034HL RSCAN0.RMDF034.UINT8[HL]
#define RSCAN0RMDF034HH RSCAN0.RMDF034.UINT8[HH]
#define RSCAN0RMDF134 RSCAN0.RMDF134.UINT32
#define RSCAN0RMDF134L RSCAN0.RMDF134.UINT16[L]
#define RSCAN0RMDF134LL RSCAN0.RMDF134.UINT8[LL]
#define RSCAN0RMDF134LH RSCAN0.RMDF134.UINT8[LH]
#define RSCAN0RMDF134H RSCAN0.RMDF134.UINT16[H]
#define RSCAN0RMDF134HL RSCAN0.RMDF134.UINT8[HL]
#define RSCAN0RMDF134HH RSCAN0.RMDF134.UINT8[HH]
#define RSCAN0RMID35 RSCAN0.RMID35.UINT32
#define RSCAN0RMID35L RSCAN0.RMID35.UINT16[L]
#define RSCAN0RMID35LL RSCAN0.RMID35.UINT8[LL]
#define RSCAN0RMID35LH RSCAN0.RMID35.UINT8[LH]
#define RSCAN0RMID35H RSCAN0.RMID35.UINT16[H]
#define RSCAN0RMID35HL RSCAN0.RMID35.UINT8[HL]
#define RSCAN0RMID35HH RSCAN0.RMID35.UINT8[HH]
#define RSCAN0RMPTR35 RSCAN0.RMPTR35.UINT32
#define RSCAN0RMPTR35L RSCAN0.RMPTR35.UINT16[L]
#define RSCAN0RMPTR35LL RSCAN0.RMPTR35.UINT8[LL]
#define RSCAN0RMPTR35LH RSCAN0.RMPTR35.UINT8[LH]
#define RSCAN0RMPTR35H RSCAN0.RMPTR35.UINT16[H]
#define RSCAN0RMPTR35HL RSCAN0.RMPTR35.UINT8[HL]
#define RSCAN0RMPTR35HH RSCAN0.RMPTR35.UINT8[HH]
#define RSCAN0RMDF035 RSCAN0.RMDF035.UINT32
#define RSCAN0RMDF035L RSCAN0.RMDF035.UINT16[L]
#define RSCAN0RMDF035LL RSCAN0.RMDF035.UINT8[LL]
#define RSCAN0RMDF035LH RSCAN0.RMDF035.UINT8[LH]
#define RSCAN0RMDF035H RSCAN0.RMDF035.UINT16[H]
#define RSCAN0RMDF035HL RSCAN0.RMDF035.UINT8[HL]
#define RSCAN0RMDF035HH RSCAN0.RMDF035.UINT8[HH]
#define RSCAN0RMDF135 RSCAN0.RMDF135.UINT32
#define RSCAN0RMDF135L RSCAN0.RMDF135.UINT16[L]
#define RSCAN0RMDF135LL RSCAN0.RMDF135.UINT8[LL]
#define RSCAN0RMDF135LH RSCAN0.RMDF135.UINT8[LH]
#define RSCAN0RMDF135H RSCAN0.RMDF135.UINT16[H]
#define RSCAN0RMDF135HL RSCAN0.RMDF135.UINT8[HL]
#define RSCAN0RMDF135HH RSCAN0.RMDF135.UINT8[HH]
#define RSCAN0RMID36 RSCAN0.RMID36.UINT32
#define RSCAN0RMID36L RSCAN0.RMID36.UINT16[L]
#define RSCAN0RMID36LL RSCAN0.RMID36.UINT8[LL]
#define RSCAN0RMID36LH RSCAN0.RMID36.UINT8[LH]
#define RSCAN0RMID36H RSCAN0.RMID36.UINT16[H]
#define RSCAN0RMID36HL RSCAN0.RMID36.UINT8[HL]
#define RSCAN0RMID36HH RSCAN0.RMID36.UINT8[HH]
#define RSCAN0RMPTR36 RSCAN0.RMPTR36.UINT32
#define RSCAN0RMPTR36L RSCAN0.RMPTR36.UINT16[L]
#define RSCAN0RMPTR36LL RSCAN0.RMPTR36.UINT8[LL]
#define RSCAN0RMPTR36LH RSCAN0.RMPTR36.UINT8[LH]
#define RSCAN0RMPTR36H RSCAN0.RMPTR36.UINT16[H]
#define RSCAN0RMPTR36HL RSCAN0.RMPTR36.UINT8[HL]
#define RSCAN0RMPTR36HH RSCAN0.RMPTR36.UINT8[HH]
#define RSCAN0RMDF036 RSCAN0.RMDF036.UINT32
#define RSCAN0RMDF036L RSCAN0.RMDF036.UINT16[L]
#define RSCAN0RMDF036LL RSCAN0.RMDF036.UINT8[LL]
#define RSCAN0RMDF036LH RSCAN0.RMDF036.UINT8[LH]
#define RSCAN0RMDF036H RSCAN0.RMDF036.UINT16[H]
#define RSCAN0RMDF036HL RSCAN0.RMDF036.UINT8[HL]
#define RSCAN0RMDF036HH RSCAN0.RMDF036.UINT8[HH]
#define RSCAN0RMDF136 RSCAN0.RMDF136.UINT32
#define RSCAN0RMDF136L RSCAN0.RMDF136.UINT16[L]
#define RSCAN0RMDF136LL RSCAN0.RMDF136.UINT8[LL]
#define RSCAN0RMDF136LH RSCAN0.RMDF136.UINT8[LH]
#define RSCAN0RMDF136H RSCAN0.RMDF136.UINT16[H]
#define RSCAN0RMDF136HL RSCAN0.RMDF136.UINT8[HL]
#define RSCAN0RMDF136HH RSCAN0.RMDF136.UINT8[HH]
#define RSCAN0RMID37 RSCAN0.RMID37.UINT32
#define RSCAN0RMID37L RSCAN0.RMID37.UINT16[L]
#define RSCAN0RMID37LL RSCAN0.RMID37.UINT8[LL]
#define RSCAN0RMID37LH RSCAN0.RMID37.UINT8[LH]
#define RSCAN0RMID37H RSCAN0.RMID37.UINT16[H]
#define RSCAN0RMID37HL RSCAN0.RMID37.UINT8[HL]
#define RSCAN0RMID37HH RSCAN0.RMID37.UINT8[HH]
#define RSCAN0RMPTR37 RSCAN0.RMPTR37.UINT32
#define RSCAN0RMPTR37L RSCAN0.RMPTR37.UINT16[L]
#define RSCAN0RMPTR37LL RSCAN0.RMPTR37.UINT8[LL]
#define RSCAN0RMPTR37LH RSCAN0.RMPTR37.UINT8[LH]
#define RSCAN0RMPTR37H RSCAN0.RMPTR37.UINT16[H]
#define RSCAN0RMPTR37HL RSCAN0.RMPTR37.UINT8[HL]
#define RSCAN0RMPTR37HH RSCAN0.RMPTR37.UINT8[HH]
#define RSCAN0RMDF037 RSCAN0.RMDF037.UINT32
#define RSCAN0RMDF037L RSCAN0.RMDF037.UINT16[L]
#define RSCAN0RMDF037LL RSCAN0.RMDF037.UINT8[LL]
#define RSCAN0RMDF037LH RSCAN0.RMDF037.UINT8[LH]
#define RSCAN0RMDF037H RSCAN0.RMDF037.UINT16[H]
#define RSCAN0RMDF037HL RSCAN0.RMDF037.UINT8[HL]
#define RSCAN0RMDF037HH RSCAN0.RMDF037.UINT8[HH]
#define RSCAN0RMDF137 RSCAN0.RMDF137.UINT32
#define RSCAN0RMDF137L RSCAN0.RMDF137.UINT16[L]
#define RSCAN0RMDF137LL RSCAN0.RMDF137.UINT8[LL]
#define RSCAN0RMDF137LH RSCAN0.RMDF137.UINT8[LH]
#define RSCAN0RMDF137H RSCAN0.RMDF137.UINT16[H]
#define RSCAN0RMDF137HL RSCAN0.RMDF137.UINT8[HL]
#define RSCAN0RMDF137HH RSCAN0.RMDF137.UINT8[HH]
#define RSCAN0RMID38 RSCAN0.RMID38.UINT32
#define RSCAN0RMID38L RSCAN0.RMID38.UINT16[L]
#define RSCAN0RMID38LL RSCAN0.RMID38.UINT8[LL]
#define RSCAN0RMID38LH RSCAN0.RMID38.UINT8[LH]
#define RSCAN0RMID38H RSCAN0.RMID38.UINT16[H]
#define RSCAN0RMID38HL RSCAN0.RMID38.UINT8[HL]
#define RSCAN0RMID38HH RSCAN0.RMID38.UINT8[HH]
#define RSCAN0RMPTR38 RSCAN0.RMPTR38.UINT32
#define RSCAN0RMPTR38L RSCAN0.RMPTR38.UINT16[L]
#define RSCAN0RMPTR38LL RSCAN0.RMPTR38.UINT8[LL]
#define RSCAN0RMPTR38LH RSCAN0.RMPTR38.UINT8[LH]
#define RSCAN0RMPTR38H RSCAN0.RMPTR38.UINT16[H]
#define RSCAN0RMPTR38HL RSCAN0.RMPTR38.UINT8[HL]
#define RSCAN0RMPTR38HH RSCAN0.RMPTR38.UINT8[HH]
#define RSCAN0RMDF038 RSCAN0.RMDF038.UINT32
#define RSCAN0RMDF038L RSCAN0.RMDF038.UINT16[L]
#define RSCAN0RMDF038LL RSCAN0.RMDF038.UINT8[LL]
#define RSCAN0RMDF038LH RSCAN0.RMDF038.UINT8[LH]
#define RSCAN0RMDF038H RSCAN0.RMDF038.UINT16[H]
#define RSCAN0RMDF038HL RSCAN0.RMDF038.UINT8[HL]
#define RSCAN0RMDF038HH RSCAN0.RMDF038.UINT8[HH]
#define RSCAN0RMDF138 RSCAN0.RMDF138.UINT32
#define RSCAN0RMDF138L RSCAN0.RMDF138.UINT16[L]
#define RSCAN0RMDF138LL RSCAN0.RMDF138.UINT8[LL]
#define RSCAN0RMDF138LH RSCAN0.RMDF138.UINT8[LH]
#define RSCAN0RMDF138H RSCAN0.RMDF138.UINT16[H]
#define RSCAN0RMDF138HL RSCAN0.RMDF138.UINT8[HL]
#define RSCAN0RMDF138HH RSCAN0.RMDF138.UINT8[HH]
#define RSCAN0RMID39 RSCAN0.RMID39.UINT32
#define RSCAN0RMID39L RSCAN0.RMID39.UINT16[L]
#define RSCAN0RMID39LL RSCAN0.RMID39.UINT8[LL]
#define RSCAN0RMID39LH RSCAN0.RMID39.UINT8[LH]
#define RSCAN0RMID39H RSCAN0.RMID39.UINT16[H]
#define RSCAN0RMID39HL RSCAN0.RMID39.UINT8[HL]
#define RSCAN0RMID39HH RSCAN0.RMID39.UINT8[HH]
#define RSCAN0RMPTR39 RSCAN0.RMPTR39.UINT32
#define RSCAN0RMPTR39L RSCAN0.RMPTR39.UINT16[L]
#define RSCAN0RMPTR39LL RSCAN0.RMPTR39.UINT8[LL]
#define RSCAN0RMPTR39LH RSCAN0.RMPTR39.UINT8[LH]
#define RSCAN0RMPTR39H RSCAN0.RMPTR39.UINT16[H]
#define RSCAN0RMPTR39HL RSCAN0.RMPTR39.UINT8[HL]
#define RSCAN0RMPTR39HH RSCAN0.RMPTR39.UINT8[HH]
#define RSCAN0RMDF039 RSCAN0.RMDF039.UINT32
#define RSCAN0RMDF039L RSCAN0.RMDF039.UINT16[L]
#define RSCAN0RMDF039LL RSCAN0.RMDF039.UINT8[LL]
#define RSCAN0RMDF039LH RSCAN0.RMDF039.UINT8[LH]
#define RSCAN0RMDF039H RSCAN0.RMDF039.UINT16[H]
#define RSCAN0RMDF039HL RSCAN0.RMDF039.UINT8[HL]
#define RSCAN0RMDF039HH RSCAN0.RMDF039.UINT8[HH]
#define RSCAN0RMDF139 RSCAN0.RMDF139.UINT32
#define RSCAN0RMDF139L RSCAN0.RMDF139.UINT16[L]
#define RSCAN0RMDF139LL RSCAN0.RMDF139.UINT8[LL]
#define RSCAN0RMDF139LH RSCAN0.RMDF139.UINT8[LH]
#define RSCAN0RMDF139H RSCAN0.RMDF139.UINT16[H]
#define RSCAN0RMDF139HL RSCAN0.RMDF139.UINT8[HL]
#define RSCAN0RMDF139HH RSCAN0.RMDF139.UINT8[HH]
#define RSCAN0RMID40 RSCAN0.RMID40.UINT32
#define RSCAN0RMID40L RSCAN0.RMID40.UINT16[L]
#define RSCAN0RMID40LL RSCAN0.RMID40.UINT8[LL]
#define RSCAN0RMID40LH RSCAN0.RMID40.UINT8[LH]
#define RSCAN0RMID40H RSCAN0.RMID40.UINT16[H]
#define RSCAN0RMID40HL RSCAN0.RMID40.UINT8[HL]
#define RSCAN0RMID40HH RSCAN0.RMID40.UINT8[HH]
#define RSCAN0RMPTR40 RSCAN0.RMPTR40.UINT32
#define RSCAN0RMPTR40L RSCAN0.RMPTR40.UINT16[L]
#define RSCAN0RMPTR40LL RSCAN0.RMPTR40.UINT8[LL]
#define RSCAN0RMPTR40LH RSCAN0.RMPTR40.UINT8[LH]
#define RSCAN0RMPTR40H RSCAN0.RMPTR40.UINT16[H]
#define RSCAN0RMPTR40HL RSCAN0.RMPTR40.UINT8[HL]
#define RSCAN0RMPTR40HH RSCAN0.RMPTR40.UINT8[HH]
#define RSCAN0RMDF040 RSCAN0.RMDF040.UINT32
#define RSCAN0RMDF040L RSCAN0.RMDF040.UINT16[L]
#define RSCAN0RMDF040LL RSCAN0.RMDF040.UINT8[LL]
#define RSCAN0RMDF040LH RSCAN0.RMDF040.UINT8[LH]
#define RSCAN0RMDF040H RSCAN0.RMDF040.UINT16[H]
#define RSCAN0RMDF040HL RSCAN0.RMDF040.UINT8[HL]
#define RSCAN0RMDF040HH RSCAN0.RMDF040.UINT8[HH]
#define RSCAN0RMDF140 RSCAN0.RMDF140.UINT32
#define RSCAN0RMDF140L RSCAN0.RMDF140.UINT16[L]
#define RSCAN0RMDF140LL RSCAN0.RMDF140.UINT8[LL]
#define RSCAN0RMDF140LH RSCAN0.RMDF140.UINT8[LH]
#define RSCAN0RMDF140H RSCAN0.RMDF140.UINT16[H]
#define RSCAN0RMDF140HL RSCAN0.RMDF140.UINT8[HL]
#define RSCAN0RMDF140HH RSCAN0.RMDF140.UINT8[HH]
#define RSCAN0RMID41 RSCAN0.RMID41.UINT32
#define RSCAN0RMID41L RSCAN0.RMID41.UINT16[L]
#define RSCAN0RMID41LL RSCAN0.RMID41.UINT8[LL]
#define RSCAN0RMID41LH RSCAN0.RMID41.UINT8[LH]
#define RSCAN0RMID41H RSCAN0.RMID41.UINT16[H]
#define RSCAN0RMID41HL RSCAN0.RMID41.UINT8[HL]
#define RSCAN0RMID41HH RSCAN0.RMID41.UINT8[HH]
#define RSCAN0RMPTR41 RSCAN0.RMPTR41.UINT32
#define RSCAN0RMPTR41L RSCAN0.RMPTR41.UINT16[L]
#define RSCAN0RMPTR41LL RSCAN0.RMPTR41.UINT8[LL]
#define RSCAN0RMPTR41LH RSCAN0.RMPTR41.UINT8[LH]
#define RSCAN0RMPTR41H RSCAN0.RMPTR41.UINT16[H]
#define RSCAN0RMPTR41HL RSCAN0.RMPTR41.UINT8[HL]
#define RSCAN0RMPTR41HH RSCAN0.RMPTR41.UINT8[HH]
#define RSCAN0RMDF041 RSCAN0.RMDF041.UINT32
#define RSCAN0RMDF041L RSCAN0.RMDF041.UINT16[L]
#define RSCAN0RMDF041LL RSCAN0.RMDF041.UINT8[LL]
#define RSCAN0RMDF041LH RSCAN0.RMDF041.UINT8[LH]
#define RSCAN0RMDF041H RSCAN0.RMDF041.UINT16[H]
#define RSCAN0RMDF041HL RSCAN0.RMDF041.UINT8[HL]
#define RSCAN0RMDF041HH RSCAN0.RMDF041.UINT8[HH]
#define RSCAN0RMDF141 RSCAN0.RMDF141.UINT32
#define RSCAN0RMDF141L RSCAN0.RMDF141.UINT16[L]
#define RSCAN0RMDF141LL RSCAN0.RMDF141.UINT8[LL]
#define RSCAN0RMDF141LH RSCAN0.RMDF141.UINT8[LH]
#define RSCAN0RMDF141H RSCAN0.RMDF141.UINT16[H]
#define RSCAN0RMDF141HL RSCAN0.RMDF141.UINT8[HL]
#define RSCAN0RMDF141HH RSCAN0.RMDF141.UINT8[HH]
#define RSCAN0RMID42 RSCAN0.RMID42.UINT32
#define RSCAN0RMID42L RSCAN0.RMID42.UINT16[L]
#define RSCAN0RMID42LL RSCAN0.RMID42.UINT8[LL]
#define RSCAN0RMID42LH RSCAN0.RMID42.UINT8[LH]
#define RSCAN0RMID42H RSCAN0.RMID42.UINT16[H]
#define RSCAN0RMID42HL RSCAN0.RMID42.UINT8[HL]
#define RSCAN0RMID42HH RSCAN0.RMID42.UINT8[HH]
#define RSCAN0RMPTR42 RSCAN0.RMPTR42.UINT32
#define RSCAN0RMPTR42L RSCAN0.RMPTR42.UINT16[L]
#define RSCAN0RMPTR42LL RSCAN0.RMPTR42.UINT8[LL]
#define RSCAN0RMPTR42LH RSCAN0.RMPTR42.UINT8[LH]
#define RSCAN0RMPTR42H RSCAN0.RMPTR42.UINT16[H]
#define RSCAN0RMPTR42HL RSCAN0.RMPTR42.UINT8[HL]
#define RSCAN0RMPTR42HH RSCAN0.RMPTR42.UINT8[HH]
#define RSCAN0RMDF042 RSCAN0.RMDF042.UINT32
#define RSCAN0RMDF042L RSCAN0.RMDF042.UINT16[L]
#define RSCAN0RMDF042LL RSCAN0.RMDF042.UINT8[LL]
#define RSCAN0RMDF042LH RSCAN0.RMDF042.UINT8[LH]
#define RSCAN0RMDF042H RSCAN0.RMDF042.UINT16[H]
#define RSCAN0RMDF042HL RSCAN0.RMDF042.UINT8[HL]
#define RSCAN0RMDF042HH RSCAN0.RMDF042.UINT8[HH]
#define RSCAN0RMDF142 RSCAN0.RMDF142.UINT32
#define RSCAN0RMDF142L RSCAN0.RMDF142.UINT16[L]
#define RSCAN0RMDF142LL RSCAN0.RMDF142.UINT8[LL]
#define RSCAN0RMDF142LH RSCAN0.RMDF142.UINT8[LH]
#define RSCAN0RMDF142H RSCAN0.RMDF142.UINT16[H]
#define RSCAN0RMDF142HL RSCAN0.RMDF142.UINT8[HL]
#define RSCAN0RMDF142HH RSCAN0.RMDF142.UINT8[HH]
#define RSCAN0RMID43 RSCAN0.RMID43.UINT32
#define RSCAN0RMID43L RSCAN0.RMID43.UINT16[L]
#define RSCAN0RMID43LL RSCAN0.RMID43.UINT8[LL]
#define RSCAN0RMID43LH RSCAN0.RMID43.UINT8[LH]
#define RSCAN0RMID43H RSCAN0.RMID43.UINT16[H]
#define RSCAN0RMID43HL RSCAN0.RMID43.UINT8[HL]
#define RSCAN0RMID43HH RSCAN0.RMID43.UINT8[HH]
#define RSCAN0RMPTR43 RSCAN0.RMPTR43.UINT32
#define RSCAN0RMPTR43L RSCAN0.RMPTR43.UINT16[L]
#define RSCAN0RMPTR43LL RSCAN0.RMPTR43.UINT8[LL]
#define RSCAN0RMPTR43LH RSCAN0.RMPTR43.UINT8[LH]
#define RSCAN0RMPTR43H RSCAN0.RMPTR43.UINT16[H]
#define RSCAN0RMPTR43HL RSCAN0.RMPTR43.UINT8[HL]
#define RSCAN0RMPTR43HH RSCAN0.RMPTR43.UINT8[HH]
#define RSCAN0RMDF043 RSCAN0.RMDF043.UINT32
#define RSCAN0RMDF043L RSCAN0.RMDF043.UINT16[L]
#define RSCAN0RMDF043LL RSCAN0.RMDF043.UINT8[LL]
#define RSCAN0RMDF043LH RSCAN0.RMDF043.UINT8[LH]
#define RSCAN0RMDF043H RSCAN0.RMDF043.UINT16[H]
#define RSCAN0RMDF043HL RSCAN0.RMDF043.UINT8[HL]
#define RSCAN0RMDF043HH RSCAN0.RMDF043.UINT8[HH]
#define RSCAN0RMDF143 RSCAN0.RMDF143.UINT32
#define RSCAN0RMDF143L RSCAN0.RMDF143.UINT16[L]
#define RSCAN0RMDF143LL RSCAN0.RMDF143.UINT8[LL]
#define RSCAN0RMDF143LH RSCAN0.RMDF143.UINT8[LH]
#define RSCAN0RMDF143H RSCAN0.RMDF143.UINT16[H]
#define RSCAN0RMDF143HL RSCAN0.RMDF143.UINT8[HL]
#define RSCAN0RMDF143HH RSCAN0.RMDF143.UINT8[HH]
#define RSCAN0RMID44 RSCAN0.RMID44.UINT32
#define RSCAN0RMID44L RSCAN0.RMID44.UINT16[L]
#define RSCAN0RMID44LL RSCAN0.RMID44.UINT8[LL]
#define RSCAN0RMID44LH RSCAN0.RMID44.UINT8[LH]
#define RSCAN0RMID44H RSCAN0.RMID44.UINT16[H]
#define RSCAN0RMID44HL RSCAN0.RMID44.UINT8[HL]
#define RSCAN0RMID44HH RSCAN0.RMID44.UINT8[HH]
#define RSCAN0RMPTR44 RSCAN0.RMPTR44.UINT32
#define RSCAN0RMPTR44L RSCAN0.RMPTR44.UINT16[L]
#define RSCAN0RMPTR44LL RSCAN0.RMPTR44.UINT8[LL]
#define RSCAN0RMPTR44LH RSCAN0.RMPTR44.UINT8[LH]
#define RSCAN0RMPTR44H RSCAN0.RMPTR44.UINT16[H]
#define RSCAN0RMPTR44HL RSCAN0.RMPTR44.UINT8[HL]
#define RSCAN0RMPTR44HH RSCAN0.RMPTR44.UINT8[HH]
#define RSCAN0RMDF044 RSCAN0.RMDF044.UINT32
#define RSCAN0RMDF044L RSCAN0.RMDF044.UINT16[L]
#define RSCAN0RMDF044LL RSCAN0.RMDF044.UINT8[LL]
#define RSCAN0RMDF044LH RSCAN0.RMDF044.UINT8[LH]
#define RSCAN0RMDF044H RSCAN0.RMDF044.UINT16[H]
#define RSCAN0RMDF044HL RSCAN0.RMDF044.UINT8[HL]
#define RSCAN0RMDF044HH RSCAN0.RMDF044.UINT8[HH]
#define RSCAN0RMDF144 RSCAN0.RMDF144.UINT32
#define RSCAN0RMDF144L RSCAN0.RMDF144.UINT16[L]
#define RSCAN0RMDF144LL RSCAN0.RMDF144.UINT8[LL]
#define RSCAN0RMDF144LH RSCAN0.RMDF144.UINT8[LH]
#define RSCAN0RMDF144H RSCAN0.RMDF144.UINT16[H]
#define RSCAN0RMDF144HL RSCAN0.RMDF144.UINT8[HL]
#define RSCAN0RMDF144HH RSCAN0.RMDF144.UINT8[HH]
#define RSCAN0RMID45 RSCAN0.RMID45.UINT32
#define RSCAN0RMID45L RSCAN0.RMID45.UINT16[L]
#define RSCAN0RMID45LL RSCAN0.RMID45.UINT8[LL]
#define RSCAN0RMID45LH RSCAN0.RMID45.UINT8[LH]
#define RSCAN0RMID45H RSCAN0.RMID45.UINT16[H]
#define RSCAN0RMID45HL RSCAN0.RMID45.UINT8[HL]
#define RSCAN0RMID45HH RSCAN0.RMID45.UINT8[HH]
#define RSCAN0RMPTR45 RSCAN0.RMPTR45.UINT32
#define RSCAN0RMPTR45L RSCAN0.RMPTR45.UINT16[L]
#define RSCAN0RMPTR45LL RSCAN0.RMPTR45.UINT8[LL]
#define RSCAN0RMPTR45LH RSCAN0.RMPTR45.UINT8[LH]
#define RSCAN0RMPTR45H RSCAN0.RMPTR45.UINT16[H]
#define RSCAN0RMPTR45HL RSCAN0.RMPTR45.UINT8[HL]
#define RSCAN0RMPTR45HH RSCAN0.RMPTR45.UINT8[HH]
#define RSCAN0RMDF045 RSCAN0.RMDF045.UINT32
#define RSCAN0RMDF045L RSCAN0.RMDF045.UINT16[L]
#define RSCAN0RMDF045LL RSCAN0.RMDF045.UINT8[LL]
#define RSCAN0RMDF045LH RSCAN0.RMDF045.UINT8[LH]
#define RSCAN0RMDF045H RSCAN0.RMDF045.UINT16[H]
#define RSCAN0RMDF045HL RSCAN0.RMDF045.UINT8[HL]
#define RSCAN0RMDF045HH RSCAN0.RMDF045.UINT8[HH]
#define RSCAN0RMDF145 RSCAN0.RMDF145.UINT32
#define RSCAN0RMDF145L RSCAN0.RMDF145.UINT16[L]
#define RSCAN0RMDF145LL RSCAN0.RMDF145.UINT8[LL]
#define RSCAN0RMDF145LH RSCAN0.RMDF145.UINT8[LH]
#define RSCAN0RMDF145H RSCAN0.RMDF145.UINT16[H]
#define RSCAN0RMDF145HL RSCAN0.RMDF145.UINT8[HL]
#define RSCAN0RMDF145HH RSCAN0.RMDF145.UINT8[HH]
#define RSCAN0RMID46 RSCAN0.RMID46.UINT32
#define RSCAN0RMID46L RSCAN0.RMID46.UINT16[L]
#define RSCAN0RMID46LL RSCAN0.RMID46.UINT8[LL]
#define RSCAN0RMID46LH RSCAN0.RMID46.UINT8[LH]
#define RSCAN0RMID46H RSCAN0.RMID46.UINT16[H]
#define RSCAN0RMID46HL RSCAN0.RMID46.UINT8[HL]
#define RSCAN0RMID46HH RSCAN0.RMID46.UINT8[HH]
#define RSCAN0RMPTR46 RSCAN0.RMPTR46.UINT32
#define RSCAN0RMPTR46L RSCAN0.RMPTR46.UINT16[L]
#define RSCAN0RMPTR46LL RSCAN0.RMPTR46.UINT8[LL]
#define RSCAN0RMPTR46LH RSCAN0.RMPTR46.UINT8[LH]
#define RSCAN0RMPTR46H RSCAN0.RMPTR46.UINT16[H]
#define RSCAN0RMPTR46HL RSCAN0.RMPTR46.UINT8[HL]
#define RSCAN0RMPTR46HH RSCAN0.RMPTR46.UINT8[HH]
#define RSCAN0RMDF046 RSCAN0.RMDF046.UINT32
#define RSCAN0RMDF046L RSCAN0.RMDF046.UINT16[L]
#define RSCAN0RMDF046LL RSCAN0.RMDF046.UINT8[LL]
#define RSCAN0RMDF046LH RSCAN0.RMDF046.UINT8[LH]
#define RSCAN0RMDF046H RSCAN0.RMDF046.UINT16[H]
#define RSCAN0RMDF046HL RSCAN0.RMDF046.UINT8[HL]
#define RSCAN0RMDF046HH RSCAN0.RMDF046.UINT8[HH]
#define RSCAN0RMDF146 RSCAN0.RMDF146.UINT32
#define RSCAN0RMDF146L RSCAN0.RMDF146.UINT16[L]
#define RSCAN0RMDF146LL RSCAN0.RMDF146.UINT8[LL]
#define RSCAN0RMDF146LH RSCAN0.RMDF146.UINT8[LH]
#define RSCAN0RMDF146H RSCAN0.RMDF146.UINT16[H]
#define RSCAN0RMDF146HL RSCAN0.RMDF146.UINT8[HL]
#define RSCAN0RMDF146HH RSCAN0.RMDF146.UINT8[HH]
#define RSCAN0RMID47 RSCAN0.RMID47.UINT32
#define RSCAN0RMID47L RSCAN0.RMID47.UINT16[L]
#define RSCAN0RMID47LL RSCAN0.RMID47.UINT8[LL]
#define RSCAN0RMID47LH RSCAN0.RMID47.UINT8[LH]
#define RSCAN0RMID47H RSCAN0.RMID47.UINT16[H]
#define RSCAN0RMID47HL RSCAN0.RMID47.UINT8[HL]
#define RSCAN0RMID47HH RSCAN0.RMID47.UINT8[HH]
#define RSCAN0RMPTR47 RSCAN0.RMPTR47.UINT32
#define RSCAN0RMPTR47L RSCAN0.RMPTR47.UINT16[L]
#define RSCAN0RMPTR47LL RSCAN0.RMPTR47.UINT8[LL]
#define RSCAN0RMPTR47LH RSCAN0.RMPTR47.UINT8[LH]
#define RSCAN0RMPTR47H RSCAN0.RMPTR47.UINT16[H]
#define RSCAN0RMPTR47HL RSCAN0.RMPTR47.UINT8[HL]
#define RSCAN0RMPTR47HH RSCAN0.RMPTR47.UINT8[HH]
#define RSCAN0RMDF047 RSCAN0.RMDF047.UINT32
#define RSCAN0RMDF047L RSCAN0.RMDF047.UINT16[L]
#define RSCAN0RMDF047LL RSCAN0.RMDF047.UINT8[LL]
#define RSCAN0RMDF047LH RSCAN0.RMDF047.UINT8[LH]
#define RSCAN0RMDF047H RSCAN0.RMDF047.UINT16[H]
#define RSCAN0RMDF047HL RSCAN0.RMDF047.UINT8[HL]
#define RSCAN0RMDF047HH RSCAN0.RMDF047.UINT8[HH]
#define RSCAN0RMDF147 RSCAN0.RMDF147.UINT32
#define RSCAN0RMDF147L RSCAN0.RMDF147.UINT16[L]
#define RSCAN0RMDF147LL RSCAN0.RMDF147.UINT8[LL]
#define RSCAN0RMDF147LH RSCAN0.RMDF147.UINT8[LH]
#define RSCAN0RMDF147H RSCAN0.RMDF147.UINT16[H]
#define RSCAN0RMDF147HL RSCAN0.RMDF147.UINT8[HL]
#define RSCAN0RMDF147HH RSCAN0.RMDF147.UINT8[HH]
#define RSCAN0RFID0 RSCAN0.RFID0.UINT32
#define RSCAN0RFID0L RSCAN0.RFID0.UINT16[L]
#define RSCAN0RFID0LL RSCAN0.RFID0.UINT8[LL]
#define RSCAN0RFID0LH RSCAN0.RFID0.UINT8[LH]
#define RSCAN0RFID0H RSCAN0.RFID0.UINT16[H]
#define RSCAN0RFID0HL RSCAN0.RFID0.UINT8[HL]
#define RSCAN0RFID0HH RSCAN0.RFID0.UINT8[HH]
#define RSCAN0RFPTR0 RSCAN0.RFPTR0.UINT32
#define RSCAN0RFPTR0L RSCAN0.RFPTR0.UINT16[L]
#define RSCAN0RFPTR0LL RSCAN0.RFPTR0.UINT8[LL]
#define RSCAN0RFPTR0LH RSCAN0.RFPTR0.UINT8[LH]
#define RSCAN0RFPTR0H RSCAN0.RFPTR0.UINT16[H]
#define RSCAN0RFPTR0HL RSCAN0.RFPTR0.UINT8[HL]
#define RSCAN0RFPTR0HH RSCAN0.RFPTR0.UINT8[HH]
#define RSCAN0RFDF00 RSCAN0.RFDF00.UINT32
#define RSCAN0RFDF00L RSCAN0.RFDF00.UINT16[L]
#define RSCAN0RFDF00LL RSCAN0.RFDF00.UINT8[LL]
#define RSCAN0RFDF00LH RSCAN0.RFDF00.UINT8[LH]
#define RSCAN0RFDF00H RSCAN0.RFDF00.UINT16[H]
#define RSCAN0RFDF00HL RSCAN0.RFDF00.UINT8[HL]
#define RSCAN0RFDF00HH RSCAN0.RFDF00.UINT8[HH]
#define RSCAN0RFDF10 RSCAN0.RFDF10.UINT32
#define RSCAN0RFDF10L RSCAN0.RFDF10.UINT16[L]
#define RSCAN0RFDF10LL RSCAN0.RFDF10.UINT8[LL]
#define RSCAN0RFDF10LH RSCAN0.RFDF10.UINT8[LH]
#define RSCAN0RFDF10H RSCAN0.RFDF10.UINT16[H]
#define RSCAN0RFDF10HL RSCAN0.RFDF10.UINT8[HL]
#define RSCAN0RFDF10HH RSCAN0.RFDF10.UINT8[HH]
#define RSCAN0RFID1 RSCAN0.RFID1.UINT32
#define RSCAN0RFID1L RSCAN0.RFID1.UINT16[L]
#define RSCAN0RFID1LL RSCAN0.RFID1.UINT8[LL]
#define RSCAN0RFID1LH RSCAN0.RFID1.UINT8[LH]
#define RSCAN0RFID1H RSCAN0.RFID1.UINT16[H]
#define RSCAN0RFID1HL RSCAN0.RFID1.UINT8[HL]
#define RSCAN0RFID1HH RSCAN0.RFID1.UINT8[HH]
#define RSCAN0RFPTR1 RSCAN0.RFPTR1.UINT32
#define RSCAN0RFPTR1L RSCAN0.RFPTR1.UINT16[L]
#define RSCAN0RFPTR1LL RSCAN0.RFPTR1.UINT8[LL]
#define RSCAN0RFPTR1LH RSCAN0.RFPTR1.UINT8[LH]
#define RSCAN0RFPTR1H RSCAN0.RFPTR1.UINT16[H]
#define RSCAN0RFPTR1HL RSCAN0.RFPTR1.UINT8[HL]
#define RSCAN0RFPTR1HH RSCAN0.RFPTR1.UINT8[HH]
#define RSCAN0RFDF01 RSCAN0.RFDF01.UINT32
#define RSCAN0RFDF01L RSCAN0.RFDF01.UINT16[L]
#define RSCAN0RFDF01LL RSCAN0.RFDF01.UINT8[LL]
#define RSCAN0RFDF01LH RSCAN0.RFDF01.UINT8[LH]
#define RSCAN0RFDF01H RSCAN0.RFDF01.UINT16[H]
#define RSCAN0RFDF01HL RSCAN0.RFDF01.UINT8[HL]
#define RSCAN0RFDF01HH RSCAN0.RFDF01.UINT8[HH]
#define RSCAN0RFDF11 RSCAN0.RFDF11.UINT32
#define RSCAN0RFDF11L RSCAN0.RFDF11.UINT16[L]
#define RSCAN0RFDF11LL RSCAN0.RFDF11.UINT8[LL]
#define RSCAN0RFDF11LH RSCAN0.RFDF11.UINT8[LH]
#define RSCAN0RFDF11H RSCAN0.RFDF11.UINT16[H]
#define RSCAN0RFDF11HL RSCAN0.RFDF11.UINT8[HL]
#define RSCAN0RFDF11HH RSCAN0.RFDF11.UINT8[HH]
#define RSCAN0RFID2 RSCAN0.RFID2.UINT32
#define RSCAN0RFID2L RSCAN0.RFID2.UINT16[L]
#define RSCAN0RFID2LL RSCAN0.RFID2.UINT8[LL]
#define RSCAN0RFID2LH RSCAN0.RFID2.UINT8[LH]
#define RSCAN0RFID2H RSCAN0.RFID2.UINT16[H]
#define RSCAN0RFID2HL RSCAN0.RFID2.UINT8[HL]
#define RSCAN0RFID2HH RSCAN0.RFID2.UINT8[HH]
#define RSCAN0RFPTR2 RSCAN0.RFPTR2.UINT32
#define RSCAN0RFPTR2L RSCAN0.RFPTR2.UINT16[L]
#define RSCAN0RFPTR2LL RSCAN0.RFPTR2.UINT8[LL]
#define RSCAN0RFPTR2LH RSCAN0.RFPTR2.UINT8[LH]
#define RSCAN0RFPTR2H RSCAN0.RFPTR2.UINT16[H]
#define RSCAN0RFPTR2HL RSCAN0.RFPTR2.UINT8[HL]
#define RSCAN0RFPTR2HH RSCAN0.RFPTR2.UINT8[HH]
#define RSCAN0RFDF02 RSCAN0.RFDF02.UINT32
#define RSCAN0RFDF02L RSCAN0.RFDF02.UINT16[L]
#define RSCAN0RFDF02LL RSCAN0.RFDF02.UINT8[LL]
#define RSCAN0RFDF02LH RSCAN0.RFDF02.UINT8[LH]
#define RSCAN0RFDF02H RSCAN0.RFDF02.UINT16[H]
#define RSCAN0RFDF02HL RSCAN0.RFDF02.UINT8[HL]
#define RSCAN0RFDF02HH RSCAN0.RFDF02.UINT8[HH]
#define RSCAN0RFDF12 RSCAN0.RFDF12.UINT32
#define RSCAN0RFDF12L RSCAN0.RFDF12.UINT16[L]
#define RSCAN0RFDF12LL RSCAN0.RFDF12.UINT8[LL]
#define RSCAN0RFDF12LH RSCAN0.RFDF12.UINT8[LH]
#define RSCAN0RFDF12H RSCAN0.RFDF12.UINT16[H]
#define RSCAN0RFDF12HL RSCAN0.RFDF12.UINT8[HL]
#define RSCAN0RFDF12HH RSCAN0.RFDF12.UINT8[HH]
#define RSCAN0RFID3 RSCAN0.RFID3.UINT32
#define RSCAN0RFID3L RSCAN0.RFID3.UINT16[L]
#define RSCAN0RFID3LL RSCAN0.RFID3.UINT8[LL]
#define RSCAN0RFID3LH RSCAN0.RFID3.UINT8[LH]
#define RSCAN0RFID3H RSCAN0.RFID3.UINT16[H]
#define RSCAN0RFID3HL RSCAN0.RFID3.UINT8[HL]
#define RSCAN0RFID3HH RSCAN0.RFID3.UINT8[HH]
#define RSCAN0RFPTR3 RSCAN0.RFPTR3.UINT32
#define RSCAN0RFPTR3L RSCAN0.RFPTR3.UINT16[L]
#define RSCAN0RFPTR3LL RSCAN0.RFPTR3.UINT8[LL]
#define RSCAN0RFPTR3LH RSCAN0.RFPTR3.UINT8[LH]
#define RSCAN0RFPTR3H RSCAN0.RFPTR3.UINT16[H]
#define RSCAN0RFPTR3HL RSCAN0.RFPTR3.UINT8[HL]
#define RSCAN0RFPTR3HH RSCAN0.RFPTR3.UINT8[HH]
#define RSCAN0RFDF03 RSCAN0.RFDF03.UINT32
#define RSCAN0RFDF03L RSCAN0.RFDF03.UINT16[L]
#define RSCAN0RFDF03LL RSCAN0.RFDF03.UINT8[LL]
#define RSCAN0RFDF03LH RSCAN0.RFDF03.UINT8[LH]
#define RSCAN0RFDF03H RSCAN0.RFDF03.UINT16[H]
#define RSCAN0RFDF03HL RSCAN0.RFDF03.UINT8[HL]
#define RSCAN0RFDF03HH RSCAN0.RFDF03.UINT8[HH]
#define RSCAN0RFDF13 RSCAN0.RFDF13.UINT32
#define RSCAN0RFDF13L RSCAN0.RFDF13.UINT16[L]
#define RSCAN0RFDF13LL RSCAN0.RFDF13.UINT8[LL]
#define RSCAN0RFDF13LH RSCAN0.RFDF13.UINT8[LH]
#define RSCAN0RFDF13H RSCAN0.RFDF13.UINT16[H]
#define RSCAN0RFDF13HL RSCAN0.RFDF13.UINT8[HL]
#define RSCAN0RFDF13HH RSCAN0.RFDF13.UINT8[HH]
#define RSCAN0RFID4 RSCAN0.RFID4.UINT32
#define RSCAN0RFID4L RSCAN0.RFID4.UINT16[L]
#define RSCAN0RFID4LL RSCAN0.RFID4.UINT8[LL]
#define RSCAN0RFID4LH RSCAN0.RFID4.UINT8[LH]
#define RSCAN0RFID4H RSCAN0.RFID4.UINT16[H]
#define RSCAN0RFID4HL RSCAN0.RFID4.UINT8[HL]
#define RSCAN0RFID4HH RSCAN0.RFID4.UINT8[HH]
#define RSCAN0RFPTR4 RSCAN0.RFPTR4.UINT32
#define RSCAN0RFPTR4L RSCAN0.RFPTR4.UINT16[L]
#define RSCAN0RFPTR4LL RSCAN0.RFPTR4.UINT8[LL]
#define RSCAN0RFPTR4LH RSCAN0.RFPTR4.UINT8[LH]
#define RSCAN0RFPTR4H RSCAN0.RFPTR4.UINT16[H]
#define RSCAN0RFPTR4HL RSCAN0.RFPTR4.UINT8[HL]
#define RSCAN0RFPTR4HH RSCAN0.RFPTR4.UINT8[HH]
#define RSCAN0RFDF04 RSCAN0.RFDF04.UINT32
#define RSCAN0RFDF04L RSCAN0.RFDF04.UINT16[L]
#define RSCAN0RFDF04LL RSCAN0.RFDF04.UINT8[LL]
#define RSCAN0RFDF04LH RSCAN0.RFDF04.UINT8[LH]
#define RSCAN0RFDF04H RSCAN0.RFDF04.UINT16[H]
#define RSCAN0RFDF04HL RSCAN0.RFDF04.UINT8[HL]
#define RSCAN0RFDF04HH RSCAN0.RFDF04.UINT8[HH]
#define RSCAN0RFDF14 RSCAN0.RFDF14.UINT32
#define RSCAN0RFDF14L RSCAN0.RFDF14.UINT16[L]
#define RSCAN0RFDF14LL RSCAN0.RFDF14.UINT8[LL]
#define RSCAN0RFDF14LH RSCAN0.RFDF14.UINT8[LH]
#define RSCAN0RFDF14H RSCAN0.RFDF14.UINT16[H]
#define RSCAN0RFDF14HL RSCAN0.RFDF14.UINT8[HL]
#define RSCAN0RFDF14HH RSCAN0.RFDF14.UINT8[HH]
#define RSCAN0RFID5 RSCAN0.RFID5.UINT32
#define RSCAN0RFID5L RSCAN0.RFID5.UINT16[L]
#define RSCAN0RFID5LL RSCAN0.RFID5.UINT8[LL]
#define RSCAN0RFID5LH RSCAN0.RFID5.UINT8[LH]
#define RSCAN0RFID5H RSCAN0.RFID5.UINT16[H]
#define RSCAN0RFID5HL RSCAN0.RFID5.UINT8[HL]
#define RSCAN0RFID5HH RSCAN0.RFID5.UINT8[HH]
#define RSCAN0RFPTR5 RSCAN0.RFPTR5.UINT32
#define RSCAN0RFPTR5L RSCAN0.RFPTR5.UINT16[L]
#define RSCAN0RFPTR5LL RSCAN0.RFPTR5.UINT8[LL]
#define RSCAN0RFPTR5LH RSCAN0.RFPTR5.UINT8[LH]
#define RSCAN0RFPTR5H RSCAN0.RFPTR5.UINT16[H]
#define RSCAN0RFPTR5HL RSCAN0.RFPTR5.UINT8[HL]
#define RSCAN0RFPTR5HH RSCAN0.RFPTR5.UINT8[HH]
#define RSCAN0RFDF05 RSCAN0.RFDF05.UINT32
#define RSCAN0RFDF05L RSCAN0.RFDF05.UINT16[L]
#define RSCAN0RFDF05LL RSCAN0.RFDF05.UINT8[LL]
#define RSCAN0RFDF05LH RSCAN0.RFDF05.UINT8[LH]
#define RSCAN0RFDF05H RSCAN0.RFDF05.UINT16[H]
#define RSCAN0RFDF05HL RSCAN0.RFDF05.UINT8[HL]
#define RSCAN0RFDF05HH RSCAN0.RFDF05.UINT8[HH]
#define RSCAN0RFDF15 RSCAN0.RFDF15.UINT32
#define RSCAN0RFDF15L RSCAN0.RFDF15.UINT16[L]
#define RSCAN0RFDF15LL RSCAN0.RFDF15.UINT8[LL]
#define RSCAN0RFDF15LH RSCAN0.RFDF15.UINT8[LH]
#define RSCAN0RFDF15H RSCAN0.RFDF15.UINT16[H]
#define RSCAN0RFDF15HL RSCAN0.RFDF15.UINT8[HL]
#define RSCAN0RFDF15HH RSCAN0.RFDF15.UINT8[HH]
#define RSCAN0RFID6 RSCAN0.RFID6.UINT32
#define RSCAN0RFID6L RSCAN0.RFID6.UINT16[L]
#define RSCAN0RFID6LL RSCAN0.RFID6.UINT8[LL]
#define RSCAN0RFID6LH RSCAN0.RFID6.UINT8[LH]
#define RSCAN0RFID6H RSCAN0.RFID6.UINT16[H]
#define RSCAN0RFID6HL RSCAN0.RFID6.UINT8[HL]
#define RSCAN0RFID6HH RSCAN0.RFID6.UINT8[HH]
#define RSCAN0RFPTR6 RSCAN0.RFPTR6.UINT32
#define RSCAN0RFPTR6L RSCAN0.RFPTR6.UINT16[L]
#define RSCAN0RFPTR6LL RSCAN0.RFPTR6.UINT8[LL]
#define RSCAN0RFPTR6LH RSCAN0.RFPTR6.UINT8[LH]
#define RSCAN0RFPTR6H RSCAN0.RFPTR6.UINT16[H]
#define RSCAN0RFPTR6HL RSCAN0.RFPTR6.UINT8[HL]
#define RSCAN0RFPTR6HH RSCAN0.RFPTR6.UINT8[HH]
#define RSCAN0RFDF06 RSCAN0.RFDF06.UINT32
#define RSCAN0RFDF06L RSCAN0.RFDF06.UINT16[L]
#define RSCAN0RFDF06LL RSCAN0.RFDF06.UINT8[LL]
#define RSCAN0RFDF06LH RSCAN0.RFDF06.UINT8[LH]
#define RSCAN0RFDF06H RSCAN0.RFDF06.UINT16[H]
#define RSCAN0RFDF06HL RSCAN0.RFDF06.UINT8[HL]
#define RSCAN0RFDF06HH RSCAN0.RFDF06.UINT8[HH]
#define RSCAN0RFDF16 RSCAN0.RFDF16.UINT32
#define RSCAN0RFDF16L RSCAN0.RFDF16.UINT16[L]
#define RSCAN0RFDF16LL RSCAN0.RFDF16.UINT8[LL]
#define RSCAN0RFDF16LH RSCAN0.RFDF16.UINT8[LH]
#define RSCAN0RFDF16H RSCAN0.RFDF16.UINT16[H]
#define RSCAN0RFDF16HL RSCAN0.RFDF16.UINT8[HL]
#define RSCAN0RFDF16HH RSCAN0.RFDF16.UINT8[HH]
#define RSCAN0RFID7 RSCAN0.RFID7.UINT32
#define RSCAN0RFID7L RSCAN0.RFID7.UINT16[L]
#define RSCAN0RFID7LL RSCAN0.RFID7.UINT8[LL]
#define RSCAN0RFID7LH RSCAN0.RFID7.UINT8[LH]
#define RSCAN0RFID7H RSCAN0.RFID7.UINT16[H]
#define RSCAN0RFID7HL RSCAN0.RFID7.UINT8[HL]
#define RSCAN0RFID7HH RSCAN0.RFID7.UINT8[HH]
#define RSCAN0RFPTR7 RSCAN0.RFPTR7.UINT32
#define RSCAN0RFPTR7L RSCAN0.RFPTR7.UINT16[L]
#define RSCAN0RFPTR7LL RSCAN0.RFPTR7.UINT8[LL]
#define RSCAN0RFPTR7LH RSCAN0.RFPTR7.UINT8[LH]
#define RSCAN0RFPTR7H RSCAN0.RFPTR7.UINT16[H]
#define RSCAN0RFPTR7HL RSCAN0.RFPTR7.UINT8[HL]
#define RSCAN0RFPTR7HH RSCAN0.RFPTR7.UINT8[HH]
#define RSCAN0RFDF07 RSCAN0.RFDF07.UINT32
#define RSCAN0RFDF07L RSCAN0.RFDF07.UINT16[L]
#define RSCAN0RFDF07LL RSCAN0.RFDF07.UINT8[LL]
#define RSCAN0RFDF07LH RSCAN0.RFDF07.UINT8[LH]
#define RSCAN0RFDF07H RSCAN0.RFDF07.UINT16[H]
#define RSCAN0RFDF07HL RSCAN0.RFDF07.UINT8[HL]
#define RSCAN0RFDF07HH RSCAN0.RFDF07.UINT8[HH]
#define RSCAN0RFDF17 RSCAN0.RFDF17.UINT32
#define RSCAN0RFDF17L RSCAN0.RFDF17.UINT16[L]
#define RSCAN0RFDF17LL RSCAN0.RFDF17.UINT8[LL]
#define RSCAN0RFDF17LH RSCAN0.RFDF17.UINT8[LH]
#define RSCAN0RFDF17H RSCAN0.RFDF17.UINT16[H]
#define RSCAN0RFDF17HL RSCAN0.RFDF17.UINT8[HL]
#define RSCAN0RFDF17HH RSCAN0.RFDF17.UINT8[HH]
#define RSCAN0CFID0 RSCAN0.CFID0.UINT32
#define RSCAN0CFID0L RSCAN0.CFID0.UINT16[L]
#define RSCAN0CFID0LL RSCAN0.CFID0.UINT8[LL]
#define RSCAN0CFID0LH RSCAN0.CFID0.UINT8[LH]
#define RSCAN0CFID0H RSCAN0.CFID0.UINT16[H]
#define RSCAN0CFID0HL RSCAN0.CFID0.UINT8[HL]
#define RSCAN0CFID0HH RSCAN0.CFID0.UINT8[HH]
#define RSCAN0CFPTR0 RSCAN0.CFPTR0.UINT32
#define RSCAN0CFPTR0L RSCAN0.CFPTR0.UINT16[L]
#define RSCAN0CFPTR0LL RSCAN0.CFPTR0.UINT8[LL]
#define RSCAN0CFPTR0LH RSCAN0.CFPTR0.UINT8[LH]
#define RSCAN0CFPTR0H RSCAN0.CFPTR0.UINT16[H]
#define RSCAN0CFPTR0HL RSCAN0.CFPTR0.UINT8[HL]
#define RSCAN0CFPTR0HH RSCAN0.CFPTR0.UINT8[HH]
#define RSCAN0CFDF00 RSCAN0.CFDF00.UINT32
#define RSCAN0CFDF00L RSCAN0.CFDF00.UINT16[L]
#define RSCAN0CFDF00LL RSCAN0.CFDF00.UINT8[LL]
#define RSCAN0CFDF00LH RSCAN0.CFDF00.UINT8[LH]
#define RSCAN0CFDF00H RSCAN0.CFDF00.UINT16[H]
#define RSCAN0CFDF00HL RSCAN0.CFDF00.UINT8[HL]
#define RSCAN0CFDF00HH RSCAN0.CFDF00.UINT8[HH]
#define RSCAN0CFDF10 RSCAN0.CFDF10.UINT32
#define RSCAN0CFDF10L RSCAN0.CFDF10.UINT16[L]
#define RSCAN0CFDF10LL RSCAN0.CFDF10.UINT8[LL]
#define RSCAN0CFDF10LH RSCAN0.CFDF10.UINT8[LH]
#define RSCAN0CFDF10H RSCAN0.CFDF10.UINT16[H]
#define RSCAN0CFDF10HL RSCAN0.CFDF10.UINT8[HL]
#define RSCAN0CFDF10HH RSCAN0.CFDF10.UINT8[HH]
#define RSCAN0CFID1 RSCAN0.CFID1.UINT32
#define RSCAN0CFID1L RSCAN0.CFID1.UINT16[L]
#define RSCAN0CFID1LL RSCAN0.CFID1.UINT8[LL]
#define RSCAN0CFID1LH RSCAN0.CFID1.UINT8[LH]
#define RSCAN0CFID1H RSCAN0.CFID1.UINT16[H]
#define RSCAN0CFID1HL RSCAN0.CFID1.UINT8[HL]
#define RSCAN0CFID1HH RSCAN0.CFID1.UINT8[HH]
#define RSCAN0CFPTR1 RSCAN0.CFPTR1.UINT32
#define RSCAN0CFPTR1L RSCAN0.CFPTR1.UINT16[L]
#define RSCAN0CFPTR1LL RSCAN0.CFPTR1.UINT8[LL]
#define RSCAN0CFPTR1LH RSCAN0.CFPTR1.UINT8[LH]
#define RSCAN0CFPTR1H RSCAN0.CFPTR1.UINT16[H]
#define RSCAN0CFPTR1HL RSCAN0.CFPTR1.UINT8[HL]
#define RSCAN0CFPTR1HH RSCAN0.CFPTR1.UINT8[HH]
#define RSCAN0CFDF01 RSCAN0.CFDF01.UINT32
#define RSCAN0CFDF01L RSCAN0.CFDF01.UINT16[L]
#define RSCAN0CFDF01LL RSCAN0.CFDF01.UINT8[LL]
#define RSCAN0CFDF01LH RSCAN0.CFDF01.UINT8[LH]
#define RSCAN0CFDF01H RSCAN0.CFDF01.UINT16[H]
#define RSCAN0CFDF01HL RSCAN0.CFDF01.UINT8[HL]
#define RSCAN0CFDF01HH RSCAN0.CFDF01.UINT8[HH]
#define RSCAN0CFDF11 RSCAN0.CFDF11.UINT32
#define RSCAN0CFDF11L RSCAN0.CFDF11.UINT16[L]
#define RSCAN0CFDF11LL RSCAN0.CFDF11.UINT8[LL]
#define RSCAN0CFDF11LH RSCAN0.CFDF11.UINT8[LH]
#define RSCAN0CFDF11H RSCAN0.CFDF11.UINT16[H]
#define RSCAN0CFDF11HL RSCAN0.CFDF11.UINT8[HL]
#define RSCAN0CFDF11HH RSCAN0.CFDF11.UINT8[HH]
#define RSCAN0CFID2 RSCAN0.CFID2.UINT32
#define RSCAN0CFID2L RSCAN0.CFID2.UINT16[L]
#define RSCAN0CFID2LL RSCAN0.CFID2.UINT8[LL]
#define RSCAN0CFID2LH RSCAN0.CFID2.UINT8[LH]
#define RSCAN0CFID2H RSCAN0.CFID2.UINT16[H]
#define RSCAN0CFID2HL RSCAN0.CFID2.UINT8[HL]
#define RSCAN0CFID2HH RSCAN0.CFID2.UINT8[HH]
#define RSCAN0CFPTR2 RSCAN0.CFPTR2.UINT32
#define RSCAN0CFPTR2L RSCAN0.CFPTR2.UINT16[L]
#define RSCAN0CFPTR2LL RSCAN0.CFPTR2.UINT8[LL]
#define RSCAN0CFPTR2LH RSCAN0.CFPTR2.UINT8[LH]
#define RSCAN0CFPTR2H RSCAN0.CFPTR2.UINT16[H]
#define RSCAN0CFPTR2HL RSCAN0.CFPTR2.UINT8[HL]
#define RSCAN0CFPTR2HH RSCAN0.CFPTR2.UINT8[HH]
#define RSCAN0CFDF02 RSCAN0.CFDF02.UINT32
#define RSCAN0CFDF02L RSCAN0.CFDF02.UINT16[L]
#define RSCAN0CFDF02LL RSCAN0.CFDF02.UINT8[LL]
#define RSCAN0CFDF02LH RSCAN0.CFDF02.UINT8[LH]
#define RSCAN0CFDF02H RSCAN0.CFDF02.UINT16[H]
#define RSCAN0CFDF02HL RSCAN0.CFDF02.UINT8[HL]
#define RSCAN0CFDF02HH RSCAN0.CFDF02.UINT8[HH]
#define RSCAN0CFDF12 RSCAN0.CFDF12.UINT32
#define RSCAN0CFDF12L RSCAN0.CFDF12.UINT16[L]
#define RSCAN0CFDF12LL RSCAN0.CFDF12.UINT8[LL]
#define RSCAN0CFDF12LH RSCAN0.CFDF12.UINT8[LH]
#define RSCAN0CFDF12H RSCAN0.CFDF12.UINT16[H]
#define RSCAN0CFDF12HL RSCAN0.CFDF12.UINT8[HL]
#define RSCAN0CFDF12HH RSCAN0.CFDF12.UINT8[HH]
#define RSCAN0CFID3 RSCAN0.CFID3.UINT32
#define RSCAN0CFID3L RSCAN0.CFID3.UINT16[L]
#define RSCAN0CFID3LL RSCAN0.CFID3.UINT8[LL]
#define RSCAN0CFID3LH RSCAN0.CFID3.UINT8[LH]
#define RSCAN0CFID3H RSCAN0.CFID3.UINT16[H]
#define RSCAN0CFID3HL RSCAN0.CFID3.UINT8[HL]
#define RSCAN0CFID3HH RSCAN0.CFID3.UINT8[HH]
#define RSCAN0CFPTR3 RSCAN0.CFPTR3.UINT32
#define RSCAN0CFPTR3L RSCAN0.CFPTR3.UINT16[L]
#define RSCAN0CFPTR3LL RSCAN0.CFPTR3.UINT8[LL]
#define RSCAN0CFPTR3LH RSCAN0.CFPTR3.UINT8[LH]
#define RSCAN0CFPTR3H RSCAN0.CFPTR3.UINT16[H]
#define RSCAN0CFPTR3HL RSCAN0.CFPTR3.UINT8[HL]
#define RSCAN0CFPTR3HH RSCAN0.CFPTR3.UINT8[HH]
#define RSCAN0CFDF03 RSCAN0.CFDF03.UINT32
#define RSCAN0CFDF03L RSCAN0.CFDF03.UINT16[L]
#define RSCAN0CFDF03LL RSCAN0.CFDF03.UINT8[LL]
#define RSCAN0CFDF03LH RSCAN0.CFDF03.UINT8[LH]
#define RSCAN0CFDF03H RSCAN0.CFDF03.UINT16[H]
#define RSCAN0CFDF03HL RSCAN0.CFDF03.UINT8[HL]
#define RSCAN0CFDF03HH RSCAN0.CFDF03.UINT8[HH]
#define RSCAN0CFDF13 RSCAN0.CFDF13.UINT32
#define RSCAN0CFDF13L RSCAN0.CFDF13.UINT16[L]
#define RSCAN0CFDF13LL RSCAN0.CFDF13.UINT8[LL]
#define RSCAN0CFDF13LH RSCAN0.CFDF13.UINT8[LH]
#define RSCAN0CFDF13H RSCAN0.CFDF13.UINT16[H]
#define RSCAN0CFDF13HL RSCAN0.CFDF13.UINT8[HL]
#define RSCAN0CFDF13HH RSCAN0.CFDF13.UINT8[HH]
#define RSCAN0CFID4 RSCAN0.CFID4.UINT32
#define RSCAN0CFID4L RSCAN0.CFID4.UINT16[L]
#define RSCAN0CFID4LL RSCAN0.CFID4.UINT8[LL]
#define RSCAN0CFID4LH RSCAN0.CFID4.UINT8[LH]
#define RSCAN0CFID4H RSCAN0.CFID4.UINT16[H]
#define RSCAN0CFID4HL RSCAN0.CFID4.UINT8[HL]
#define RSCAN0CFID4HH RSCAN0.CFID4.UINT8[HH]
#define RSCAN0CFPTR4 RSCAN0.CFPTR4.UINT32
#define RSCAN0CFPTR4L RSCAN0.CFPTR4.UINT16[L]
#define RSCAN0CFPTR4LL RSCAN0.CFPTR4.UINT8[LL]
#define RSCAN0CFPTR4LH RSCAN0.CFPTR4.UINT8[LH]
#define RSCAN0CFPTR4H RSCAN0.CFPTR4.UINT16[H]
#define RSCAN0CFPTR4HL RSCAN0.CFPTR4.UINT8[HL]
#define RSCAN0CFPTR4HH RSCAN0.CFPTR4.UINT8[HH]
#define RSCAN0CFDF04 RSCAN0.CFDF04.UINT32
#define RSCAN0CFDF04L RSCAN0.CFDF04.UINT16[L]
#define RSCAN0CFDF04LL RSCAN0.CFDF04.UINT8[LL]
#define RSCAN0CFDF04LH RSCAN0.CFDF04.UINT8[LH]
#define RSCAN0CFDF04H RSCAN0.CFDF04.UINT16[H]
#define RSCAN0CFDF04HL RSCAN0.CFDF04.UINT8[HL]
#define RSCAN0CFDF04HH RSCAN0.CFDF04.UINT8[HH]
#define RSCAN0CFDF14 RSCAN0.CFDF14.UINT32
#define RSCAN0CFDF14L RSCAN0.CFDF14.UINT16[L]
#define RSCAN0CFDF14LL RSCAN0.CFDF14.UINT8[LL]
#define RSCAN0CFDF14LH RSCAN0.CFDF14.UINT8[LH]
#define RSCAN0CFDF14H RSCAN0.CFDF14.UINT16[H]
#define RSCAN0CFDF14HL RSCAN0.CFDF14.UINT8[HL]
#define RSCAN0CFDF14HH RSCAN0.CFDF14.UINT8[HH]
#define RSCAN0CFID5 RSCAN0.CFID5.UINT32
#define RSCAN0CFID5L RSCAN0.CFID5.UINT16[L]
#define RSCAN0CFID5LL RSCAN0.CFID5.UINT8[LL]
#define RSCAN0CFID5LH RSCAN0.CFID5.UINT8[LH]
#define RSCAN0CFID5H RSCAN0.CFID5.UINT16[H]
#define RSCAN0CFID5HL RSCAN0.CFID5.UINT8[HL]
#define RSCAN0CFID5HH RSCAN0.CFID5.UINT8[HH]
#define RSCAN0CFPTR5 RSCAN0.CFPTR5.UINT32
#define RSCAN0CFPTR5L RSCAN0.CFPTR5.UINT16[L]
#define RSCAN0CFPTR5LL RSCAN0.CFPTR5.UINT8[LL]
#define RSCAN0CFPTR5LH RSCAN0.CFPTR5.UINT8[LH]
#define RSCAN0CFPTR5H RSCAN0.CFPTR5.UINT16[H]
#define RSCAN0CFPTR5HL RSCAN0.CFPTR5.UINT8[HL]
#define RSCAN0CFPTR5HH RSCAN0.CFPTR5.UINT8[HH]
#define RSCAN0CFDF05 RSCAN0.CFDF05.UINT32
#define RSCAN0CFDF05L RSCAN0.CFDF05.UINT16[L]
#define RSCAN0CFDF05LL RSCAN0.CFDF05.UINT8[LL]
#define RSCAN0CFDF05LH RSCAN0.CFDF05.UINT8[LH]
#define RSCAN0CFDF05H RSCAN0.CFDF05.UINT16[H]
#define RSCAN0CFDF05HL RSCAN0.CFDF05.UINT8[HL]
#define RSCAN0CFDF05HH RSCAN0.CFDF05.UINT8[HH]
#define RSCAN0CFDF15 RSCAN0.CFDF15.UINT32
#define RSCAN0CFDF15L RSCAN0.CFDF15.UINT16[L]
#define RSCAN0CFDF15LL RSCAN0.CFDF15.UINT8[LL]
#define RSCAN0CFDF15LH RSCAN0.CFDF15.UINT8[LH]
#define RSCAN0CFDF15H RSCAN0.CFDF15.UINT16[H]
#define RSCAN0CFDF15HL RSCAN0.CFDF15.UINT8[HL]
#define RSCAN0CFDF15HH RSCAN0.CFDF15.UINT8[HH]
#define RSCAN0CFID6 RSCAN0.CFID6.UINT32
#define RSCAN0CFID6L RSCAN0.CFID6.UINT16[L]
#define RSCAN0CFID6LL RSCAN0.CFID6.UINT8[LL]
#define RSCAN0CFID6LH RSCAN0.CFID6.UINT8[LH]
#define RSCAN0CFID6H RSCAN0.CFID6.UINT16[H]
#define RSCAN0CFID6HL RSCAN0.CFID6.UINT8[HL]
#define RSCAN0CFID6HH RSCAN0.CFID6.UINT8[HH]
#define RSCAN0CFPTR6 RSCAN0.CFPTR6.UINT32
#define RSCAN0CFPTR6L RSCAN0.CFPTR6.UINT16[L]
#define RSCAN0CFPTR6LL RSCAN0.CFPTR6.UINT8[LL]
#define RSCAN0CFPTR6LH RSCAN0.CFPTR6.UINT8[LH]
#define RSCAN0CFPTR6H RSCAN0.CFPTR6.UINT16[H]
#define RSCAN0CFPTR6HL RSCAN0.CFPTR6.UINT8[HL]
#define RSCAN0CFPTR6HH RSCAN0.CFPTR6.UINT8[HH]
#define RSCAN0CFDF06 RSCAN0.CFDF06.UINT32
#define RSCAN0CFDF06L RSCAN0.CFDF06.UINT16[L]
#define RSCAN0CFDF06LL RSCAN0.CFDF06.UINT8[LL]
#define RSCAN0CFDF06LH RSCAN0.CFDF06.UINT8[LH]
#define RSCAN0CFDF06H RSCAN0.CFDF06.UINT16[H]
#define RSCAN0CFDF06HL RSCAN0.CFDF06.UINT8[HL]
#define RSCAN0CFDF06HH RSCAN0.CFDF06.UINT8[HH]
#define RSCAN0CFDF16 RSCAN0.CFDF16.UINT32
#define RSCAN0CFDF16L RSCAN0.CFDF16.UINT16[L]
#define RSCAN0CFDF16LL RSCAN0.CFDF16.UINT8[LL]
#define RSCAN0CFDF16LH RSCAN0.CFDF16.UINT8[LH]
#define RSCAN0CFDF16H RSCAN0.CFDF16.UINT16[H]
#define RSCAN0CFDF16HL RSCAN0.CFDF16.UINT8[HL]
#define RSCAN0CFDF16HH RSCAN0.CFDF16.UINT8[HH]
#define RSCAN0CFID7 RSCAN0.CFID7.UINT32
#define RSCAN0CFID7L RSCAN0.CFID7.UINT16[L]
#define RSCAN0CFID7LL RSCAN0.CFID7.UINT8[LL]
#define RSCAN0CFID7LH RSCAN0.CFID7.UINT8[LH]
#define RSCAN0CFID7H RSCAN0.CFID7.UINT16[H]
#define RSCAN0CFID7HL RSCAN0.CFID7.UINT8[HL]
#define RSCAN0CFID7HH RSCAN0.CFID7.UINT8[HH]
#define RSCAN0CFPTR7 RSCAN0.CFPTR7.UINT32
#define RSCAN0CFPTR7L RSCAN0.CFPTR7.UINT16[L]
#define RSCAN0CFPTR7LL RSCAN0.CFPTR7.UINT8[LL]
#define RSCAN0CFPTR7LH RSCAN0.CFPTR7.UINT8[LH]
#define RSCAN0CFPTR7H RSCAN0.CFPTR7.UINT16[H]
#define RSCAN0CFPTR7HL RSCAN0.CFPTR7.UINT8[HL]
#define RSCAN0CFPTR7HH RSCAN0.CFPTR7.UINT8[HH]
#define RSCAN0CFDF07 RSCAN0.CFDF07.UINT32
#define RSCAN0CFDF07L RSCAN0.CFDF07.UINT16[L]
#define RSCAN0CFDF07LL RSCAN0.CFDF07.UINT8[LL]
#define RSCAN0CFDF07LH RSCAN0.CFDF07.UINT8[LH]
#define RSCAN0CFDF07H RSCAN0.CFDF07.UINT16[H]
#define RSCAN0CFDF07HL RSCAN0.CFDF07.UINT8[HL]
#define RSCAN0CFDF07HH RSCAN0.CFDF07.UINT8[HH]
#define RSCAN0CFDF17 RSCAN0.CFDF17.UINT32
#define RSCAN0CFDF17L RSCAN0.CFDF17.UINT16[L]
#define RSCAN0CFDF17LL RSCAN0.CFDF17.UINT8[LL]
#define RSCAN0CFDF17LH RSCAN0.CFDF17.UINT8[LH]
#define RSCAN0CFDF17H RSCAN0.CFDF17.UINT16[H]
#define RSCAN0CFDF17HL RSCAN0.CFDF17.UINT8[HL]
#define RSCAN0CFDF17HH RSCAN0.CFDF17.UINT8[HH]
#define RSCAN0CFID8 RSCAN0.CFID8.UINT32
#define RSCAN0CFID8L RSCAN0.CFID8.UINT16[L]
#define RSCAN0CFID8LL RSCAN0.CFID8.UINT8[LL]
#define RSCAN0CFID8LH RSCAN0.CFID8.UINT8[LH]
#define RSCAN0CFID8H RSCAN0.CFID8.UINT16[H]
#define RSCAN0CFID8HL RSCAN0.CFID8.UINT8[HL]
#define RSCAN0CFID8HH RSCAN0.CFID8.UINT8[HH]
#define RSCAN0CFPTR8 RSCAN0.CFPTR8.UINT32
#define RSCAN0CFPTR8L RSCAN0.CFPTR8.UINT16[L]
#define RSCAN0CFPTR8LL RSCAN0.CFPTR8.UINT8[LL]
#define RSCAN0CFPTR8LH RSCAN0.CFPTR8.UINT8[LH]
#define RSCAN0CFPTR8H RSCAN0.CFPTR8.UINT16[H]
#define RSCAN0CFPTR8HL RSCAN0.CFPTR8.UINT8[HL]
#define RSCAN0CFPTR8HH RSCAN0.CFPTR8.UINT8[HH]
#define RSCAN0CFDF08 RSCAN0.CFDF08.UINT32
#define RSCAN0CFDF08L RSCAN0.CFDF08.UINT16[L]
#define RSCAN0CFDF08LL RSCAN0.CFDF08.UINT8[LL]
#define RSCAN0CFDF08LH RSCAN0.CFDF08.UINT8[LH]
#define RSCAN0CFDF08H RSCAN0.CFDF08.UINT16[H]
#define RSCAN0CFDF08HL RSCAN0.CFDF08.UINT8[HL]
#define RSCAN0CFDF08HH RSCAN0.CFDF08.UINT8[HH]
#define RSCAN0CFDF18 RSCAN0.CFDF18.UINT32
#define RSCAN0CFDF18L RSCAN0.CFDF18.UINT16[L]
#define RSCAN0CFDF18LL RSCAN0.CFDF18.UINT8[LL]
#define RSCAN0CFDF18LH RSCAN0.CFDF18.UINT8[LH]
#define RSCAN0CFDF18H RSCAN0.CFDF18.UINT16[H]
#define RSCAN0CFDF18HL RSCAN0.CFDF18.UINT8[HL]
#define RSCAN0CFDF18HH RSCAN0.CFDF18.UINT8[HH]
#define RSCAN0TMID0 RSCAN0.TMID0.UINT32
#define RSCAN0TMID0L RSCAN0.TMID0.UINT16[L]
#define RSCAN0TMID0LL RSCAN0.TMID0.UINT8[LL]
#define RSCAN0TMID0LH RSCAN0.TMID0.UINT8[LH]
#define RSCAN0TMID0H RSCAN0.TMID0.UINT16[H]
#define RSCAN0TMID0HL RSCAN0.TMID0.UINT8[HL]
#define RSCAN0TMID0HH RSCAN0.TMID0.UINT8[HH]
#define RSCAN0TMPTR0 RSCAN0.TMPTR0.UINT32
#define RSCAN0TMPTR0L RSCAN0.TMPTR0.UINT16[L]
#define RSCAN0TMPTR0LL RSCAN0.TMPTR0.UINT8[LL]
#define RSCAN0TMPTR0LH RSCAN0.TMPTR0.UINT8[LH]
#define RSCAN0TMPTR0H RSCAN0.TMPTR0.UINT16[H]
#define RSCAN0TMPTR0HL RSCAN0.TMPTR0.UINT8[HL]
#define RSCAN0TMPTR0HH RSCAN0.TMPTR0.UINT8[HH]
#define RSCAN0TMDF00 RSCAN0.TMDF00.UINT32
#define RSCAN0TMDF00L RSCAN0.TMDF00.UINT16[L]
#define RSCAN0TMDF00LL RSCAN0.TMDF00.UINT8[LL]
#define RSCAN0TMDF00LH RSCAN0.TMDF00.UINT8[LH]
#define RSCAN0TMDF00H RSCAN0.TMDF00.UINT16[H]
#define RSCAN0TMDF00HL RSCAN0.TMDF00.UINT8[HL]
#define RSCAN0TMDF00HH RSCAN0.TMDF00.UINT8[HH]
#define RSCAN0TMDF10 RSCAN0.TMDF10.UINT32
#define RSCAN0TMDF10L RSCAN0.TMDF10.UINT16[L]
#define RSCAN0TMDF10LL RSCAN0.TMDF10.UINT8[LL]
#define RSCAN0TMDF10LH RSCAN0.TMDF10.UINT8[LH]
#define RSCAN0TMDF10H RSCAN0.TMDF10.UINT16[H]
#define RSCAN0TMDF10HL RSCAN0.TMDF10.UINT8[HL]
#define RSCAN0TMDF10HH RSCAN0.TMDF10.UINT8[HH]
#define RSCAN0TMID1 RSCAN0.TMID1.UINT32
#define RSCAN0TMID1L RSCAN0.TMID1.UINT16[L]
#define RSCAN0TMID1LL RSCAN0.TMID1.UINT8[LL]
#define RSCAN0TMID1LH RSCAN0.TMID1.UINT8[LH]
#define RSCAN0TMID1H RSCAN0.TMID1.UINT16[H]
#define RSCAN0TMID1HL RSCAN0.TMID1.UINT8[HL]
#define RSCAN0TMID1HH RSCAN0.TMID1.UINT8[HH]
#define RSCAN0TMPTR1 RSCAN0.TMPTR1.UINT32
#define RSCAN0TMPTR1L RSCAN0.TMPTR1.UINT16[L]
#define RSCAN0TMPTR1LL RSCAN0.TMPTR1.UINT8[LL]
#define RSCAN0TMPTR1LH RSCAN0.TMPTR1.UINT8[LH]
#define RSCAN0TMPTR1H RSCAN0.TMPTR1.UINT16[H]
#define RSCAN0TMPTR1HL RSCAN0.TMPTR1.UINT8[HL]
#define RSCAN0TMPTR1HH RSCAN0.TMPTR1.UINT8[HH]
#define RSCAN0TMDF01 RSCAN0.TMDF01.UINT32
#define RSCAN0TMDF01L RSCAN0.TMDF01.UINT16[L]
#define RSCAN0TMDF01LL RSCAN0.TMDF01.UINT8[LL]
#define RSCAN0TMDF01LH RSCAN0.TMDF01.UINT8[LH]
#define RSCAN0TMDF01H RSCAN0.TMDF01.UINT16[H]
#define RSCAN0TMDF01HL RSCAN0.TMDF01.UINT8[HL]
#define RSCAN0TMDF01HH RSCAN0.TMDF01.UINT8[HH]
#define RSCAN0TMDF11 RSCAN0.TMDF11.UINT32
#define RSCAN0TMDF11L RSCAN0.TMDF11.UINT16[L]
#define RSCAN0TMDF11LL RSCAN0.TMDF11.UINT8[LL]
#define RSCAN0TMDF11LH RSCAN0.TMDF11.UINT8[LH]
#define RSCAN0TMDF11H RSCAN0.TMDF11.UINT16[H]
#define RSCAN0TMDF11HL RSCAN0.TMDF11.UINT8[HL]
#define RSCAN0TMDF11HH RSCAN0.TMDF11.UINT8[HH]
#define RSCAN0TMID2 RSCAN0.TMID2.UINT32
#define RSCAN0TMID2L RSCAN0.TMID2.UINT16[L]
#define RSCAN0TMID2LL RSCAN0.TMID2.UINT8[LL]
#define RSCAN0TMID2LH RSCAN0.TMID2.UINT8[LH]
#define RSCAN0TMID2H RSCAN0.TMID2.UINT16[H]
#define RSCAN0TMID2HL RSCAN0.TMID2.UINT8[HL]
#define RSCAN0TMID2HH RSCAN0.TMID2.UINT8[HH]
#define RSCAN0TMPTR2 RSCAN0.TMPTR2.UINT32
#define RSCAN0TMPTR2L RSCAN0.TMPTR2.UINT16[L]
#define RSCAN0TMPTR2LL RSCAN0.TMPTR2.UINT8[LL]
#define RSCAN0TMPTR2LH RSCAN0.TMPTR2.UINT8[LH]
#define RSCAN0TMPTR2H RSCAN0.TMPTR2.UINT16[H]
#define RSCAN0TMPTR2HL RSCAN0.TMPTR2.UINT8[HL]
#define RSCAN0TMPTR2HH RSCAN0.TMPTR2.UINT8[HH]
#define RSCAN0TMDF02 RSCAN0.TMDF02.UINT32
#define RSCAN0TMDF02L RSCAN0.TMDF02.UINT16[L]
#define RSCAN0TMDF02LL RSCAN0.TMDF02.UINT8[LL]
#define RSCAN0TMDF02LH RSCAN0.TMDF02.UINT8[LH]
#define RSCAN0TMDF02H RSCAN0.TMDF02.UINT16[H]
#define RSCAN0TMDF02HL RSCAN0.TMDF02.UINT8[HL]
#define RSCAN0TMDF02HH RSCAN0.TMDF02.UINT8[HH]
#define RSCAN0TMDF12 RSCAN0.TMDF12.UINT32
#define RSCAN0TMDF12L RSCAN0.TMDF12.UINT16[L]
#define RSCAN0TMDF12LL RSCAN0.TMDF12.UINT8[LL]
#define RSCAN0TMDF12LH RSCAN0.TMDF12.UINT8[LH]
#define RSCAN0TMDF12H RSCAN0.TMDF12.UINT16[H]
#define RSCAN0TMDF12HL RSCAN0.TMDF12.UINT8[HL]
#define RSCAN0TMDF12HH RSCAN0.TMDF12.UINT8[HH]
#define RSCAN0TMID3 RSCAN0.TMID3.UINT32
#define RSCAN0TMID3L RSCAN0.TMID3.UINT16[L]
#define RSCAN0TMID3LL RSCAN0.TMID3.UINT8[LL]
#define RSCAN0TMID3LH RSCAN0.TMID3.UINT8[LH]
#define RSCAN0TMID3H RSCAN0.TMID3.UINT16[H]
#define RSCAN0TMID3HL RSCAN0.TMID3.UINT8[HL]
#define RSCAN0TMID3HH RSCAN0.TMID3.UINT8[HH]
#define RSCAN0TMPTR3 RSCAN0.TMPTR3.UINT32
#define RSCAN0TMPTR3L RSCAN0.TMPTR3.UINT16[L]
#define RSCAN0TMPTR3LL RSCAN0.TMPTR3.UINT8[LL]
#define RSCAN0TMPTR3LH RSCAN0.TMPTR3.UINT8[LH]
#define RSCAN0TMPTR3H RSCAN0.TMPTR3.UINT16[H]
#define RSCAN0TMPTR3HL RSCAN0.TMPTR3.UINT8[HL]
#define RSCAN0TMPTR3HH RSCAN0.TMPTR3.UINT8[HH]
#define RSCAN0TMDF03 RSCAN0.TMDF03.UINT32
#define RSCAN0TMDF03L RSCAN0.TMDF03.UINT16[L]
#define RSCAN0TMDF03LL RSCAN0.TMDF03.UINT8[LL]
#define RSCAN0TMDF03LH RSCAN0.TMDF03.UINT8[LH]
#define RSCAN0TMDF03H RSCAN0.TMDF03.UINT16[H]
#define RSCAN0TMDF03HL RSCAN0.TMDF03.UINT8[HL]
#define RSCAN0TMDF03HH RSCAN0.TMDF03.UINT8[HH]
#define RSCAN0TMDF13 RSCAN0.TMDF13.UINT32
#define RSCAN0TMDF13L RSCAN0.TMDF13.UINT16[L]
#define RSCAN0TMDF13LL RSCAN0.TMDF13.UINT8[LL]
#define RSCAN0TMDF13LH RSCAN0.TMDF13.UINT8[LH]
#define RSCAN0TMDF13H RSCAN0.TMDF13.UINT16[H]
#define RSCAN0TMDF13HL RSCAN0.TMDF13.UINT8[HL]
#define RSCAN0TMDF13HH RSCAN0.TMDF13.UINT8[HH]
#define RSCAN0TMID4 RSCAN0.TMID4.UINT32
#define RSCAN0TMID4L RSCAN0.TMID4.UINT16[L]
#define RSCAN0TMID4LL RSCAN0.TMID4.UINT8[LL]
#define RSCAN0TMID4LH RSCAN0.TMID4.UINT8[LH]
#define RSCAN0TMID4H RSCAN0.TMID4.UINT16[H]
#define RSCAN0TMID4HL RSCAN0.TMID4.UINT8[HL]
#define RSCAN0TMID4HH RSCAN0.TMID4.UINT8[HH]
#define RSCAN0TMPTR4 RSCAN0.TMPTR4.UINT32
#define RSCAN0TMPTR4L RSCAN0.TMPTR4.UINT16[L]
#define RSCAN0TMPTR4LL RSCAN0.TMPTR4.UINT8[LL]
#define RSCAN0TMPTR4LH RSCAN0.TMPTR4.UINT8[LH]
#define RSCAN0TMPTR4H RSCAN0.TMPTR4.UINT16[H]
#define RSCAN0TMPTR4HL RSCAN0.TMPTR4.UINT8[HL]
#define RSCAN0TMPTR4HH RSCAN0.TMPTR4.UINT8[HH]
#define RSCAN0TMDF04 RSCAN0.TMDF04.UINT32
#define RSCAN0TMDF04L RSCAN0.TMDF04.UINT16[L]
#define RSCAN0TMDF04LL RSCAN0.TMDF04.UINT8[LL]
#define RSCAN0TMDF04LH RSCAN0.TMDF04.UINT8[LH]
#define RSCAN0TMDF04H RSCAN0.TMDF04.UINT16[H]
#define RSCAN0TMDF04HL RSCAN0.TMDF04.UINT8[HL]
#define RSCAN0TMDF04HH RSCAN0.TMDF04.UINT8[HH]
#define RSCAN0TMDF14 RSCAN0.TMDF14.UINT32
#define RSCAN0TMDF14L RSCAN0.TMDF14.UINT16[L]
#define RSCAN0TMDF14LL RSCAN0.TMDF14.UINT8[LL]
#define RSCAN0TMDF14LH RSCAN0.TMDF14.UINT8[LH]
#define RSCAN0TMDF14H RSCAN0.TMDF14.UINT16[H]
#define RSCAN0TMDF14HL RSCAN0.TMDF14.UINT8[HL]
#define RSCAN0TMDF14HH RSCAN0.TMDF14.UINT8[HH]
#define RSCAN0TMID5 RSCAN0.TMID5.UINT32
#define RSCAN0TMID5L RSCAN0.TMID5.UINT16[L]
#define RSCAN0TMID5LL RSCAN0.TMID5.UINT8[LL]
#define RSCAN0TMID5LH RSCAN0.TMID5.UINT8[LH]
#define RSCAN0TMID5H RSCAN0.TMID5.UINT16[H]
#define RSCAN0TMID5HL RSCAN0.TMID5.UINT8[HL]
#define RSCAN0TMID5HH RSCAN0.TMID5.UINT8[HH]
#define RSCAN0TMPTR5 RSCAN0.TMPTR5.UINT32
#define RSCAN0TMPTR5L RSCAN0.TMPTR5.UINT16[L]
#define RSCAN0TMPTR5LL RSCAN0.TMPTR5.UINT8[LL]
#define RSCAN0TMPTR5LH RSCAN0.TMPTR5.UINT8[LH]
#define RSCAN0TMPTR5H RSCAN0.TMPTR5.UINT16[H]
#define RSCAN0TMPTR5HL RSCAN0.TMPTR5.UINT8[HL]
#define RSCAN0TMPTR5HH RSCAN0.TMPTR5.UINT8[HH]
#define RSCAN0TMDF05 RSCAN0.TMDF05.UINT32
#define RSCAN0TMDF05L RSCAN0.TMDF05.UINT16[L]
#define RSCAN0TMDF05LL RSCAN0.TMDF05.UINT8[LL]
#define RSCAN0TMDF05LH RSCAN0.TMDF05.UINT8[LH]
#define RSCAN0TMDF05H RSCAN0.TMDF05.UINT16[H]
#define RSCAN0TMDF05HL RSCAN0.TMDF05.UINT8[HL]
#define RSCAN0TMDF05HH RSCAN0.TMDF05.UINT8[HH]
#define RSCAN0TMDF15 RSCAN0.TMDF15.UINT32
#define RSCAN0TMDF15L RSCAN0.TMDF15.UINT16[L]
#define RSCAN0TMDF15LL RSCAN0.TMDF15.UINT8[LL]
#define RSCAN0TMDF15LH RSCAN0.TMDF15.UINT8[LH]
#define RSCAN0TMDF15H RSCAN0.TMDF15.UINT16[H]
#define RSCAN0TMDF15HL RSCAN0.TMDF15.UINT8[HL]
#define RSCAN0TMDF15HH RSCAN0.TMDF15.UINT8[HH]
#define RSCAN0TMID6 RSCAN0.TMID6.UINT32
#define RSCAN0TMID6L RSCAN0.TMID6.UINT16[L]
#define RSCAN0TMID6LL RSCAN0.TMID6.UINT8[LL]
#define RSCAN0TMID6LH RSCAN0.TMID6.UINT8[LH]
#define RSCAN0TMID6H RSCAN0.TMID6.UINT16[H]
#define RSCAN0TMID6HL RSCAN0.TMID6.UINT8[HL]
#define RSCAN0TMID6HH RSCAN0.TMID6.UINT8[HH]
#define RSCAN0TMPTR6 RSCAN0.TMPTR6.UINT32
#define RSCAN0TMPTR6L RSCAN0.TMPTR6.UINT16[L]
#define RSCAN0TMPTR6LL RSCAN0.TMPTR6.UINT8[LL]
#define RSCAN0TMPTR6LH RSCAN0.TMPTR6.UINT8[LH]
#define RSCAN0TMPTR6H RSCAN0.TMPTR6.UINT16[H]
#define RSCAN0TMPTR6HL RSCAN0.TMPTR6.UINT8[HL]
#define RSCAN0TMPTR6HH RSCAN0.TMPTR6.UINT8[HH]
#define RSCAN0TMDF06 RSCAN0.TMDF06.UINT32
#define RSCAN0TMDF06L RSCAN0.TMDF06.UINT16[L]
#define RSCAN0TMDF06LL RSCAN0.TMDF06.UINT8[LL]
#define RSCAN0TMDF06LH RSCAN0.TMDF06.UINT8[LH]
#define RSCAN0TMDF06H RSCAN0.TMDF06.UINT16[H]
#define RSCAN0TMDF06HL RSCAN0.TMDF06.UINT8[HL]
#define RSCAN0TMDF06HH RSCAN0.TMDF06.UINT8[HH]
#define RSCAN0TMDF16 RSCAN0.TMDF16.UINT32
#define RSCAN0TMDF16L RSCAN0.TMDF16.UINT16[L]
#define RSCAN0TMDF16LL RSCAN0.TMDF16.UINT8[LL]
#define RSCAN0TMDF16LH RSCAN0.TMDF16.UINT8[LH]
#define RSCAN0TMDF16H RSCAN0.TMDF16.UINT16[H]
#define RSCAN0TMDF16HL RSCAN0.TMDF16.UINT8[HL]
#define RSCAN0TMDF16HH RSCAN0.TMDF16.UINT8[HH]
#define RSCAN0TMID7 RSCAN0.TMID7.UINT32
#define RSCAN0TMID7L RSCAN0.TMID7.UINT16[L]
#define RSCAN0TMID7LL RSCAN0.TMID7.UINT8[LL]
#define RSCAN0TMID7LH RSCAN0.TMID7.UINT8[LH]
#define RSCAN0TMID7H RSCAN0.TMID7.UINT16[H]
#define RSCAN0TMID7HL RSCAN0.TMID7.UINT8[HL]
#define RSCAN0TMID7HH RSCAN0.TMID7.UINT8[HH]
#define RSCAN0TMPTR7 RSCAN0.TMPTR7.UINT32
#define RSCAN0TMPTR7L RSCAN0.TMPTR7.UINT16[L]
#define RSCAN0TMPTR7LL RSCAN0.TMPTR7.UINT8[LL]
#define RSCAN0TMPTR7LH RSCAN0.TMPTR7.UINT8[LH]
#define RSCAN0TMPTR7H RSCAN0.TMPTR7.UINT16[H]
#define RSCAN0TMPTR7HL RSCAN0.TMPTR7.UINT8[HL]
#define RSCAN0TMPTR7HH RSCAN0.TMPTR7.UINT8[HH]
#define RSCAN0TMDF07 RSCAN0.TMDF07.UINT32
#define RSCAN0TMDF07L RSCAN0.TMDF07.UINT16[L]
#define RSCAN0TMDF07LL RSCAN0.TMDF07.UINT8[LL]
#define RSCAN0TMDF07LH RSCAN0.TMDF07.UINT8[LH]
#define RSCAN0TMDF07H RSCAN0.TMDF07.UINT16[H]
#define RSCAN0TMDF07HL RSCAN0.TMDF07.UINT8[HL]
#define RSCAN0TMDF07HH RSCAN0.TMDF07.UINT8[HH]
#define RSCAN0TMDF17 RSCAN0.TMDF17.UINT32
#define RSCAN0TMDF17L RSCAN0.TMDF17.UINT16[L]
#define RSCAN0TMDF17LL RSCAN0.TMDF17.UINT8[LL]
#define RSCAN0TMDF17LH RSCAN0.TMDF17.UINT8[LH]
#define RSCAN0TMDF17H RSCAN0.TMDF17.UINT16[H]
#define RSCAN0TMDF17HL RSCAN0.TMDF17.UINT8[HL]
#define RSCAN0TMDF17HH RSCAN0.TMDF17.UINT8[HH]
#define RSCAN0TMID8 RSCAN0.TMID8.UINT32
#define RSCAN0TMID8L RSCAN0.TMID8.UINT16[L]
#define RSCAN0TMID8LL RSCAN0.TMID8.UINT8[LL]
#define RSCAN0TMID8LH RSCAN0.TMID8.UINT8[LH]
#define RSCAN0TMID8H RSCAN0.TMID8.UINT16[H]
#define RSCAN0TMID8HL RSCAN0.TMID8.UINT8[HL]
#define RSCAN0TMID8HH RSCAN0.TMID8.UINT8[HH]
#define RSCAN0TMPTR8 RSCAN0.TMPTR8.UINT32
#define RSCAN0TMPTR8L RSCAN0.TMPTR8.UINT16[L]
#define RSCAN0TMPTR8LL RSCAN0.TMPTR8.UINT8[LL]
#define RSCAN0TMPTR8LH RSCAN0.TMPTR8.UINT8[LH]
#define RSCAN0TMPTR8H RSCAN0.TMPTR8.UINT16[H]
#define RSCAN0TMPTR8HL RSCAN0.TMPTR8.UINT8[HL]
#define RSCAN0TMPTR8HH RSCAN0.TMPTR8.UINT8[HH]
#define RSCAN0TMDF08 RSCAN0.TMDF08.UINT32
#define RSCAN0TMDF08L RSCAN0.TMDF08.UINT16[L]
#define RSCAN0TMDF08LL RSCAN0.TMDF08.UINT8[LL]
#define RSCAN0TMDF08LH RSCAN0.TMDF08.UINT8[LH]
#define RSCAN0TMDF08H RSCAN0.TMDF08.UINT16[H]
#define RSCAN0TMDF08HL RSCAN0.TMDF08.UINT8[HL]
#define RSCAN0TMDF08HH RSCAN0.TMDF08.UINT8[HH]
#define RSCAN0TMDF18 RSCAN0.TMDF18.UINT32
#define RSCAN0TMDF18L RSCAN0.TMDF18.UINT16[L]
#define RSCAN0TMDF18LL RSCAN0.TMDF18.UINT8[LL]
#define RSCAN0TMDF18LH RSCAN0.TMDF18.UINT8[LH]
#define RSCAN0TMDF18H RSCAN0.TMDF18.UINT16[H]
#define RSCAN0TMDF18HL RSCAN0.TMDF18.UINT8[HL]
#define RSCAN0TMDF18HH RSCAN0.TMDF18.UINT8[HH]
#define RSCAN0TMID9 RSCAN0.TMID9.UINT32
#define RSCAN0TMID9L RSCAN0.TMID9.UINT16[L]
#define RSCAN0TMID9LL RSCAN0.TMID9.UINT8[LL]
#define RSCAN0TMID9LH RSCAN0.TMID9.UINT8[LH]
#define RSCAN0TMID9H RSCAN0.TMID9.UINT16[H]
#define RSCAN0TMID9HL RSCAN0.TMID9.UINT8[HL]
#define RSCAN0TMID9HH RSCAN0.TMID9.UINT8[HH]
#define RSCAN0TMPTR9 RSCAN0.TMPTR9.UINT32
#define RSCAN0TMPTR9L RSCAN0.TMPTR9.UINT16[L]
#define RSCAN0TMPTR9LL RSCAN0.TMPTR9.UINT8[LL]
#define RSCAN0TMPTR9LH RSCAN0.TMPTR9.UINT8[LH]
#define RSCAN0TMPTR9H RSCAN0.TMPTR9.UINT16[H]
#define RSCAN0TMPTR9HL RSCAN0.TMPTR9.UINT8[HL]
#define RSCAN0TMPTR9HH RSCAN0.TMPTR9.UINT8[HH]
#define RSCAN0TMDF09 RSCAN0.TMDF09.UINT32
#define RSCAN0TMDF09L RSCAN0.TMDF09.UINT16[L]
#define RSCAN0TMDF09LL RSCAN0.TMDF09.UINT8[LL]
#define RSCAN0TMDF09LH RSCAN0.TMDF09.UINT8[LH]
#define RSCAN0TMDF09H RSCAN0.TMDF09.UINT16[H]
#define RSCAN0TMDF09HL RSCAN0.TMDF09.UINT8[HL]
#define RSCAN0TMDF09HH RSCAN0.TMDF09.UINT8[HH]
#define RSCAN0TMDF19 RSCAN0.TMDF19.UINT32
#define RSCAN0TMDF19L RSCAN0.TMDF19.UINT16[L]
#define RSCAN0TMDF19LL RSCAN0.TMDF19.UINT8[LL]
#define RSCAN0TMDF19LH RSCAN0.TMDF19.UINT8[LH]
#define RSCAN0TMDF19H RSCAN0.TMDF19.UINT16[H]
#define RSCAN0TMDF19HL RSCAN0.TMDF19.UINT8[HL]
#define RSCAN0TMDF19HH RSCAN0.TMDF19.UINT8[HH]
#define RSCAN0TMID10 RSCAN0.TMID10.UINT32
#define RSCAN0TMID10L RSCAN0.TMID10.UINT16[L]
#define RSCAN0TMID10LL RSCAN0.TMID10.UINT8[LL]
#define RSCAN0TMID10LH RSCAN0.TMID10.UINT8[LH]
#define RSCAN0TMID10H RSCAN0.TMID10.UINT16[H]
#define RSCAN0TMID10HL RSCAN0.TMID10.UINT8[HL]
#define RSCAN0TMID10HH RSCAN0.TMID10.UINT8[HH]
#define RSCAN0TMPTR10 RSCAN0.TMPTR10.UINT32
#define RSCAN0TMPTR10L RSCAN0.TMPTR10.UINT16[L]
#define RSCAN0TMPTR10LL RSCAN0.TMPTR10.UINT8[LL]
#define RSCAN0TMPTR10LH RSCAN0.TMPTR10.UINT8[LH]
#define RSCAN0TMPTR10H RSCAN0.TMPTR10.UINT16[H]
#define RSCAN0TMPTR10HL RSCAN0.TMPTR10.UINT8[HL]
#define RSCAN0TMPTR10HH RSCAN0.TMPTR10.UINT8[HH]
#define RSCAN0TMDF010 RSCAN0.TMDF010.UINT32
#define RSCAN0TMDF010L RSCAN0.TMDF010.UINT16[L]
#define RSCAN0TMDF010LL RSCAN0.TMDF010.UINT8[LL]
#define RSCAN0TMDF010LH RSCAN0.TMDF010.UINT8[LH]
#define RSCAN0TMDF010H RSCAN0.TMDF010.UINT16[H]
#define RSCAN0TMDF010HL RSCAN0.TMDF010.UINT8[HL]
#define RSCAN0TMDF010HH RSCAN0.TMDF010.UINT8[HH]
#define RSCAN0TMDF110 RSCAN0.TMDF110.UINT32
#define RSCAN0TMDF110L RSCAN0.TMDF110.UINT16[L]
#define RSCAN0TMDF110LL RSCAN0.TMDF110.UINT8[LL]
#define RSCAN0TMDF110LH RSCAN0.TMDF110.UINT8[LH]
#define RSCAN0TMDF110H RSCAN0.TMDF110.UINT16[H]
#define RSCAN0TMDF110HL RSCAN0.TMDF110.UINT8[HL]
#define RSCAN0TMDF110HH RSCAN0.TMDF110.UINT8[HH]
#define RSCAN0TMID11 RSCAN0.TMID11.UINT32
#define RSCAN0TMID11L RSCAN0.TMID11.UINT16[L]
#define RSCAN0TMID11LL RSCAN0.TMID11.UINT8[LL]
#define RSCAN0TMID11LH RSCAN0.TMID11.UINT8[LH]
#define RSCAN0TMID11H RSCAN0.TMID11.UINT16[H]
#define RSCAN0TMID11HL RSCAN0.TMID11.UINT8[HL]
#define RSCAN0TMID11HH RSCAN0.TMID11.UINT8[HH]
#define RSCAN0TMPTR11 RSCAN0.TMPTR11.UINT32
#define RSCAN0TMPTR11L RSCAN0.TMPTR11.UINT16[L]
#define RSCAN0TMPTR11LL RSCAN0.TMPTR11.UINT8[LL]
#define RSCAN0TMPTR11LH RSCAN0.TMPTR11.UINT8[LH]
#define RSCAN0TMPTR11H RSCAN0.TMPTR11.UINT16[H]
#define RSCAN0TMPTR11HL RSCAN0.TMPTR11.UINT8[HL]
#define RSCAN0TMPTR11HH RSCAN0.TMPTR11.UINT8[HH]
#define RSCAN0TMDF011 RSCAN0.TMDF011.UINT32
#define RSCAN0TMDF011L RSCAN0.TMDF011.UINT16[L]
#define RSCAN0TMDF011LL RSCAN0.TMDF011.UINT8[LL]
#define RSCAN0TMDF011LH RSCAN0.TMDF011.UINT8[LH]
#define RSCAN0TMDF011H RSCAN0.TMDF011.UINT16[H]
#define RSCAN0TMDF011HL RSCAN0.TMDF011.UINT8[HL]
#define RSCAN0TMDF011HH RSCAN0.TMDF011.UINT8[HH]
#define RSCAN0TMDF111 RSCAN0.TMDF111.UINT32
#define RSCAN0TMDF111L RSCAN0.TMDF111.UINT16[L]
#define RSCAN0TMDF111LL RSCAN0.TMDF111.UINT8[LL]
#define RSCAN0TMDF111LH RSCAN0.TMDF111.UINT8[LH]
#define RSCAN0TMDF111H RSCAN0.TMDF111.UINT16[H]
#define RSCAN0TMDF111HL RSCAN0.TMDF111.UINT8[HL]
#define RSCAN0TMDF111HH RSCAN0.TMDF111.UINT8[HH]
#define RSCAN0TMID12 RSCAN0.TMID12.UINT32
#define RSCAN0TMID12L RSCAN0.TMID12.UINT16[L]
#define RSCAN0TMID12LL RSCAN0.TMID12.UINT8[LL]
#define RSCAN0TMID12LH RSCAN0.TMID12.UINT8[LH]
#define RSCAN0TMID12H RSCAN0.TMID12.UINT16[H]
#define RSCAN0TMID12HL RSCAN0.TMID12.UINT8[HL]
#define RSCAN0TMID12HH RSCAN0.TMID12.UINT8[HH]
#define RSCAN0TMPTR12 RSCAN0.TMPTR12.UINT32
#define RSCAN0TMPTR12L RSCAN0.TMPTR12.UINT16[L]
#define RSCAN0TMPTR12LL RSCAN0.TMPTR12.UINT8[LL]
#define RSCAN0TMPTR12LH RSCAN0.TMPTR12.UINT8[LH]
#define RSCAN0TMPTR12H RSCAN0.TMPTR12.UINT16[H]
#define RSCAN0TMPTR12HL RSCAN0.TMPTR12.UINT8[HL]
#define RSCAN0TMPTR12HH RSCAN0.TMPTR12.UINT8[HH]
#define RSCAN0TMDF012 RSCAN0.TMDF012.UINT32
#define RSCAN0TMDF012L RSCAN0.TMDF012.UINT16[L]
#define RSCAN0TMDF012LL RSCAN0.TMDF012.UINT8[LL]
#define RSCAN0TMDF012LH RSCAN0.TMDF012.UINT8[LH]
#define RSCAN0TMDF012H RSCAN0.TMDF012.UINT16[H]
#define RSCAN0TMDF012HL RSCAN0.TMDF012.UINT8[HL]
#define RSCAN0TMDF012HH RSCAN0.TMDF012.UINT8[HH]
#define RSCAN0TMDF112 RSCAN0.TMDF112.UINT32
#define RSCAN0TMDF112L RSCAN0.TMDF112.UINT16[L]
#define RSCAN0TMDF112LL RSCAN0.TMDF112.UINT8[LL]
#define RSCAN0TMDF112LH RSCAN0.TMDF112.UINT8[LH]
#define RSCAN0TMDF112H RSCAN0.TMDF112.UINT16[H]
#define RSCAN0TMDF112HL RSCAN0.TMDF112.UINT8[HL]
#define RSCAN0TMDF112HH RSCAN0.TMDF112.UINT8[HH]
#define RSCAN0TMID13 RSCAN0.TMID13.UINT32
#define RSCAN0TMID13L RSCAN0.TMID13.UINT16[L]
#define RSCAN0TMID13LL RSCAN0.TMID13.UINT8[LL]
#define RSCAN0TMID13LH RSCAN0.TMID13.UINT8[LH]
#define RSCAN0TMID13H RSCAN0.TMID13.UINT16[H]
#define RSCAN0TMID13HL RSCAN0.TMID13.UINT8[HL]
#define RSCAN0TMID13HH RSCAN0.TMID13.UINT8[HH]
#define RSCAN0TMPTR13 RSCAN0.TMPTR13.UINT32
#define RSCAN0TMPTR13L RSCAN0.TMPTR13.UINT16[L]
#define RSCAN0TMPTR13LL RSCAN0.TMPTR13.UINT8[LL]
#define RSCAN0TMPTR13LH RSCAN0.TMPTR13.UINT8[LH]
#define RSCAN0TMPTR13H RSCAN0.TMPTR13.UINT16[H]
#define RSCAN0TMPTR13HL RSCAN0.TMPTR13.UINT8[HL]
#define RSCAN0TMPTR13HH RSCAN0.TMPTR13.UINT8[HH]
#define RSCAN0TMDF013 RSCAN0.TMDF013.UINT32
#define RSCAN0TMDF013L RSCAN0.TMDF013.UINT16[L]
#define RSCAN0TMDF013LL RSCAN0.TMDF013.UINT8[LL]
#define RSCAN0TMDF013LH RSCAN0.TMDF013.UINT8[LH]
#define RSCAN0TMDF013H RSCAN0.TMDF013.UINT16[H]
#define RSCAN0TMDF013HL RSCAN0.TMDF013.UINT8[HL]
#define RSCAN0TMDF013HH RSCAN0.TMDF013.UINT8[HH]
#define RSCAN0TMDF113 RSCAN0.TMDF113.UINT32
#define RSCAN0TMDF113L RSCAN0.TMDF113.UINT16[L]
#define RSCAN0TMDF113LL RSCAN0.TMDF113.UINT8[LL]
#define RSCAN0TMDF113LH RSCAN0.TMDF113.UINT8[LH]
#define RSCAN0TMDF113H RSCAN0.TMDF113.UINT16[H]
#define RSCAN0TMDF113HL RSCAN0.TMDF113.UINT8[HL]
#define RSCAN0TMDF113HH RSCAN0.TMDF113.UINT8[HH]
#define RSCAN0TMID14 RSCAN0.TMID14.UINT32
#define RSCAN0TMID14L RSCAN0.TMID14.UINT16[L]
#define RSCAN0TMID14LL RSCAN0.TMID14.UINT8[LL]
#define RSCAN0TMID14LH RSCAN0.TMID14.UINT8[LH]
#define RSCAN0TMID14H RSCAN0.TMID14.UINT16[H]
#define RSCAN0TMID14HL RSCAN0.TMID14.UINT8[HL]
#define RSCAN0TMID14HH RSCAN0.TMID14.UINT8[HH]
#define RSCAN0TMPTR14 RSCAN0.TMPTR14.UINT32
#define RSCAN0TMPTR14L RSCAN0.TMPTR14.UINT16[L]
#define RSCAN0TMPTR14LL RSCAN0.TMPTR14.UINT8[LL]
#define RSCAN0TMPTR14LH RSCAN0.TMPTR14.UINT8[LH]
#define RSCAN0TMPTR14H RSCAN0.TMPTR14.UINT16[H]
#define RSCAN0TMPTR14HL RSCAN0.TMPTR14.UINT8[HL]
#define RSCAN0TMPTR14HH RSCAN0.TMPTR14.UINT8[HH]
#define RSCAN0TMDF014 RSCAN0.TMDF014.UINT32
#define RSCAN0TMDF014L RSCAN0.TMDF014.UINT16[L]
#define RSCAN0TMDF014LL RSCAN0.TMDF014.UINT8[LL]
#define RSCAN0TMDF014LH RSCAN0.TMDF014.UINT8[LH]
#define RSCAN0TMDF014H RSCAN0.TMDF014.UINT16[H]
#define RSCAN0TMDF014HL RSCAN0.TMDF014.UINT8[HL]
#define RSCAN0TMDF014HH RSCAN0.TMDF014.UINT8[HH]
#define RSCAN0TMDF114 RSCAN0.TMDF114.UINT32
#define RSCAN0TMDF114L RSCAN0.TMDF114.UINT16[L]
#define RSCAN0TMDF114LL RSCAN0.TMDF114.UINT8[LL]
#define RSCAN0TMDF114LH RSCAN0.TMDF114.UINT8[LH]
#define RSCAN0TMDF114H RSCAN0.TMDF114.UINT16[H]
#define RSCAN0TMDF114HL RSCAN0.TMDF114.UINT8[HL]
#define RSCAN0TMDF114HH RSCAN0.TMDF114.UINT8[HH]
#define RSCAN0TMID15 RSCAN0.TMID15.UINT32
#define RSCAN0TMID15L RSCAN0.TMID15.UINT16[L]
#define RSCAN0TMID15LL RSCAN0.TMID15.UINT8[LL]
#define RSCAN0TMID15LH RSCAN0.TMID15.UINT8[LH]
#define RSCAN0TMID15H RSCAN0.TMID15.UINT16[H]
#define RSCAN0TMID15HL RSCAN0.TMID15.UINT8[HL]
#define RSCAN0TMID15HH RSCAN0.TMID15.UINT8[HH]
#define RSCAN0TMPTR15 RSCAN0.TMPTR15.UINT32
#define RSCAN0TMPTR15L RSCAN0.TMPTR15.UINT16[L]
#define RSCAN0TMPTR15LL RSCAN0.TMPTR15.UINT8[LL]
#define RSCAN0TMPTR15LH RSCAN0.TMPTR15.UINT8[LH]
#define RSCAN0TMPTR15H RSCAN0.TMPTR15.UINT16[H]
#define RSCAN0TMPTR15HL RSCAN0.TMPTR15.UINT8[HL]
#define RSCAN0TMPTR15HH RSCAN0.TMPTR15.UINT8[HH]
#define RSCAN0TMDF015 RSCAN0.TMDF015.UINT32
#define RSCAN0TMDF015L RSCAN0.TMDF015.UINT16[L]
#define RSCAN0TMDF015LL RSCAN0.TMDF015.UINT8[LL]
#define RSCAN0TMDF015LH RSCAN0.TMDF015.UINT8[LH]
#define RSCAN0TMDF015H RSCAN0.TMDF015.UINT16[H]
#define RSCAN0TMDF015HL RSCAN0.TMDF015.UINT8[HL]
#define RSCAN0TMDF015HH RSCAN0.TMDF015.UINT8[HH]
#define RSCAN0TMDF115 RSCAN0.TMDF115.UINT32
#define RSCAN0TMDF115L RSCAN0.TMDF115.UINT16[L]
#define RSCAN0TMDF115LL RSCAN0.TMDF115.UINT8[LL]
#define RSCAN0TMDF115LH RSCAN0.TMDF115.UINT8[LH]
#define RSCAN0TMDF115H RSCAN0.TMDF115.UINT16[H]
#define RSCAN0TMDF115HL RSCAN0.TMDF115.UINT8[HL]
#define RSCAN0TMDF115HH RSCAN0.TMDF115.UINT8[HH]
#define RSCAN0TMID16 RSCAN0.TMID16.UINT32
#define RSCAN0TMID16L RSCAN0.TMID16.UINT16[L]
#define RSCAN0TMID16LL RSCAN0.TMID16.UINT8[LL]
#define RSCAN0TMID16LH RSCAN0.TMID16.UINT8[LH]
#define RSCAN0TMID16H RSCAN0.TMID16.UINT16[H]
#define RSCAN0TMID16HL RSCAN0.TMID16.UINT8[HL]
#define RSCAN0TMID16HH RSCAN0.TMID16.UINT8[HH]
#define RSCAN0TMPTR16 RSCAN0.TMPTR16.UINT32
#define RSCAN0TMPTR16L RSCAN0.TMPTR16.UINT16[L]
#define RSCAN0TMPTR16LL RSCAN0.TMPTR16.UINT8[LL]
#define RSCAN0TMPTR16LH RSCAN0.TMPTR16.UINT8[LH]
#define RSCAN0TMPTR16H RSCAN0.TMPTR16.UINT16[H]
#define RSCAN0TMPTR16HL RSCAN0.TMPTR16.UINT8[HL]
#define RSCAN0TMPTR16HH RSCAN0.TMPTR16.UINT8[HH]
#define RSCAN0TMDF016 RSCAN0.TMDF016.UINT32
#define RSCAN0TMDF016L RSCAN0.TMDF016.UINT16[L]
#define RSCAN0TMDF016LL RSCAN0.TMDF016.UINT8[LL]
#define RSCAN0TMDF016LH RSCAN0.TMDF016.UINT8[LH]
#define RSCAN0TMDF016H RSCAN0.TMDF016.UINT16[H]
#define RSCAN0TMDF016HL RSCAN0.TMDF016.UINT8[HL]
#define RSCAN0TMDF016HH RSCAN0.TMDF016.UINT8[HH]
#define RSCAN0TMDF116 RSCAN0.TMDF116.UINT32
#define RSCAN0TMDF116L RSCAN0.TMDF116.UINT16[L]
#define RSCAN0TMDF116LL RSCAN0.TMDF116.UINT8[LL]
#define RSCAN0TMDF116LH RSCAN0.TMDF116.UINT8[LH]
#define RSCAN0TMDF116H RSCAN0.TMDF116.UINT16[H]
#define RSCAN0TMDF116HL RSCAN0.TMDF116.UINT8[HL]
#define RSCAN0TMDF116HH RSCAN0.TMDF116.UINT8[HH]
#define RSCAN0TMID17 RSCAN0.TMID17.UINT32
#define RSCAN0TMID17L RSCAN0.TMID17.UINT16[L]
#define RSCAN0TMID17LL RSCAN0.TMID17.UINT8[LL]
#define RSCAN0TMID17LH RSCAN0.TMID17.UINT8[LH]
#define RSCAN0TMID17H RSCAN0.TMID17.UINT16[H]
#define RSCAN0TMID17HL RSCAN0.TMID17.UINT8[HL]
#define RSCAN0TMID17HH RSCAN0.TMID17.UINT8[HH]
#define RSCAN0TMPTR17 RSCAN0.TMPTR17.UINT32
#define RSCAN0TMPTR17L RSCAN0.TMPTR17.UINT16[L]
#define RSCAN0TMPTR17LL RSCAN0.TMPTR17.UINT8[LL]
#define RSCAN0TMPTR17LH RSCAN0.TMPTR17.UINT8[LH]
#define RSCAN0TMPTR17H RSCAN0.TMPTR17.UINT16[H]
#define RSCAN0TMPTR17HL RSCAN0.TMPTR17.UINT8[HL]
#define RSCAN0TMPTR17HH RSCAN0.TMPTR17.UINT8[HH]
#define RSCAN0TMDF017 RSCAN0.TMDF017.UINT32
#define RSCAN0TMDF017L RSCAN0.TMDF017.UINT16[L]
#define RSCAN0TMDF017LL RSCAN0.TMDF017.UINT8[LL]
#define RSCAN0TMDF017LH RSCAN0.TMDF017.UINT8[LH]
#define RSCAN0TMDF017H RSCAN0.TMDF017.UINT16[H]
#define RSCAN0TMDF017HL RSCAN0.TMDF017.UINT8[HL]
#define RSCAN0TMDF017HH RSCAN0.TMDF017.UINT8[HH]
#define RSCAN0TMDF117 RSCAN0.TMDF117.UINT32
#define RSCAN0TMDF117L RSCAN0.TMDF117.UINT16[L]
#define RSCAN0TMDF117LL RSCAN0.TMDF117.UINT8[LL]
#define RSCAN0TMDF117LH RSCAN0.TMDF117.UINT8[LH]
#define RSCAN0TMDF117H RSCAN0.TMDF117.UINT16[H]
#define RSCAN0TMDF117HL RSCAN0.TMDF117.UINT8[HL]
#define RSCAN0TMDF117HH RSCAN0.TMDF117.UINT8[HH]
#define RSCAN0TMID18 RSCAN0.TMID18.UINT32
#define RSCAN0TMID18L RSCAN0.TMID18.UINT16[L]
#define RSCAN0TMID18LL RSCAN0.TMID18.UINT8[LL]
#define RSCAN0TMID18LH RSCAN0.TMID18.UINT8[LH]
#define RSCAN0TMID18H RSCAN0.TMID18.UINT16[H]
#define RSCAN0TMID18HL RSCAN0.TMID18.UINT8[HL]
#define RSCAN0TMID18HH RSCAN0.TMID18.UINT8[HH]
#define RSCAN0TMPTR18 RSCAN0.TMPTR18.UINT32
#define RSCAN0TMPTR18L RSCAN0.TMPTR18.UINT16[L]
#define RSCAN0TMPTR18LL RSCAN0.TMPTR18.UINT8[LL]
#define RSCAN0TMPTR18LH RSCAN0.TMPTR18.UINT8[LH]
#define RSCAN0TMPTR18H RSCAN0.TMPTR18.UINT16[H]
#define RSCAN0TMPTR18HL RSCAN0.TMPTR18.UINT8[HL]
#define RSCAN0TMPTR18HH RSCAN0.TMPTR18.UINT8[HH]
#define RSCAN0TMDF018 RSCAN0.TMDF018.UINT32
#define RSCAN0TMDF018L RSCAN0.TMDF018.UINT16[L]
#define RSCAN0TMDF018LL RSCAN0.TMDF018.UINT8[LL]
#define RSCAN0TMDF018LH RSCAN0.TMDF018.UINT8[LH]
#define RSCAN0TMDF018H RSCAN0.TMDF018.UINT16[H]
#define RSCAN0TMDF018HL RSCAN0.TMDF018.UINT8[HL]
#define RSCAN0TMDF018HH RSCAN0.TMDF018.UINT8[HH]
#define RSCAN0TMDF118 RSCAN0.TMDF118.UINT32
#define RSCAN0TMDF118L RSCAN0.TMDF118.UINT16[L]
#define RSCAN0TMDF118LL RSCAN0.TMDF118.UINT8[LL]
#define RSCAN0TMDF118LH RSCAN0.TMDF118.UINT8[LH]
#define RSCAN0TMDF118H RSCAN0.TMDF118.UINT16[H]
#define RSCAN0TMDF118HL RSCAN0.TMDF118.UINT8[HL]
#define RSCAN0TMDF118HH RSCAN0.TMDF118.UINT8[HH]
#define RSCAN0TMID19 RSCAN0.TMID19.UINT32
#define RSCAN0TMID19L RSCAN0.TMID19.UINT16[L]
#define RSCAN0TMID19LL RSCAN0.TMID19.UINT8[LL]
#define RSCAN0TMID19LH RSCAN0.TMID19.UINT8[LH]
#define RSCAN0TMID19H RSCAN0.TMID19.UINT16[H]
#define RSCAN0TMID19HL RSCAN0.TMID19.UINT8[HL]
#define RSCAN0TMID19HH RSCAN0.TMID19.UINT8[HH]
#define RSCAN0TMPTR19 RSCAN0.TMPTR19.UINT32
#define RSCAN0TMPTR19L RSCAN0.TMPTR19.UINT16[L]
#define RSCAN0TMPTR19LL RSCAN0.TMPTR19.UINT8[LL]
#define RSCAN0TMPTR19LH RSCAN0.TMPTR19.UINT8[LH]
#define RSCAN0TMPTR19H RSCAN0.TMPTR19.UINT16[H]
#define RSCAN0TMPTR19HL RSCAN0.TMPTR19.UINT8[HL]
#define RSCAN0TMPTR19HH RSCAN0.TMPTR19.UINT8[HH]
#define RSCAN0TMDF019 RSCAN0.TMDF019.UINT32
#define RSCAN0TMDF019L RSCAN0.TMDF019.UINT16[L]
#define RSCAN0TMDF019LL RSCAN0.TMDF019.UINT8[LL]
#define RSCAN0TMDF019LH RSCAN0.TMDF019.UINT8[LH]
#define RSCAN0TMDF019H RSCAN0.TMDF019.UINT16[H]
#define RSCAN0TMDF019HL RSCAN0.TMDF019.UINT8[HL]
#define RSCAN0TMDF019HH RSCAN0.TMDF019.UINT8[HH]
#define RSCAN0TMDF119 RSCAN0.TMDF119.UINT32
#define RSCAN0TMDF119L RSCAN0.TMDF119.UINT16[L]
#define RSCAN0TMDF119LL RSCAN0.TMDF119.UINT8[LL]
#define RSCAN0TMDF119LH RSCAN0.TMDF119.UINT8[LH]
#define RSCAN0TMDF119H RSCAN0.TMDF119.UINT16[H]
#define RSCAN0TMDF119HL RSCAN0.TMDF119.UINT8[HL]
#define RSCAN0TMDF119HH RSCAN0.TMDF119.UINT8[HH]
#define RSCAN0TMID20 RSCAN0.TMID20.UINT32
#define RSCAN0TMID20L RSCAN0.TMID20.UINT16[L]
#define RSCAN0TMID20LL RSCAN0.TMID20.UINT8[LL]
#define RSCAN0TMID20LH RSCAN0.TMID20.UINT8[LH]
#define RSCAN0TMID20H RSCAN0.TMID20.UINT16[H]
#define RSCAN0TMID20HL RSCAN0.TMID20.UINT8[HL]
#define RSCAN0TMID20HH RSCAN0.TMID20.UINT8[HH]
#define RSCAN0TMPTR20 RSCAN0.TMPTR20.UINT32
#define RSCAN0TMPTR20L RSCAN0.TMPTR20.UINT16[L]
#define RSCAN0TMPTR20LL RSCAN0.TMPTR20.UINT8[LL]
#define RSCAN0TMPTR20LH RSCAN0.TMPTR20.UINT8[LH]
#define RSCAN0TMPTR20H RSCAN0.TMPTR20.UINT16[H]
#define RSCAN0TMPTR20HL RSCAN0.TMPTR20.UINT8[HL]
#define RSCAN0TMPTR20HH RSCAN0.TMPTR20.UINT8[HH]
#define RSCAN0TMDF020 RSCAN0.TMDF020.UINT32
#define RSCAN0TMDF020L RSCAN0.TMDF020.UINT16[L]
#define RSCAN0TMDF020LL RSCAN0.TMDF020.UINT8[LL]
#define RSCAN0TMDF020LH RSCAN0.TMDF020.UINT8[LH]
#define RSCAN0TMDF020H RSCAN0.TMDF020.UINT16[H]
#define RSCAN0TMDF020HL RSCAN0.TMDF020.UINT8[HL]
#define RSCAN0TMDF020HH RSCAN0.TMDF020.UINT8[HH]
#define RSCAN0TMDF120 RSCAN0.TMDF120.UINT32
#define RSCAN0TMDF120L RSCAN0.TMDF120.UINT16[L]
#define RSCAN0TMDF120LL RSCAN0.TMDF120.UINT8[LL]
#define RSCAN0TMDF120LH RSCAN0.TMDF120.UINT8[LH]
#define RSCAN0TMDF120H RSCAN0.TMDF120.UINT16[H]
#define RSCAN0TMDF120HL RSCAN0.TMDF120.UINT8[HL]
#define RSCAN0TMDF120HH RSCAN0.TMDF120.UINT8[HH]
#define RSCAN0TMID21 RSCAN0.TMID21.UINT32
#define RSCAN0TMID21L RSCAN0.TMID21.UINT16[L]
#define RSCAN0TMID21LL RSCAN0.TMID21.UINT8[LL]
#define RSCAN0TMID21LH RSCAN0.TMID21.UINT8[LH]
#define RSCAN0TMID21H RSCAN0.TMID21.UINT16[H]
#define RSCAN0TMID21HL RSCAN0.TMID21.UINT8[HL]
#define RSCAN0TMID21HH RSCAN0.TMID21.UINT8[HH]
#define RSCAN0TMPTR21 RSCAN0.TMPTR21.UINT32
#define RSCAN0TMPTR21L RSCAN0.TMPTR21.UINT16[L]
#define RSCAN0TMPTR21LL RSCAN0.TMPTR21.UINT8[LL]
#define RSCAN0TMPTR21LH RSCAN0.TMPTR21.UINT8[LH]
#define RSCAN0TMPTR21H RSCAN0.TMPTR21.UINT16[H]
#define RSCAN0TMPTR21HL RSCAN0.TMPTR21.UINT8[HL]
#define RSCAN0TMPTR21HH RSCAN0.TMPTR21.UINT8[HH]
#define RSCAN0TMDF021 RSCAN0.TMDF021.UINT32
#define RSCAN0TMDF021L RSCAN0.TMDF021.UINT16[L]
#define RSCAN0TMDF021LL RSCAN0.TMDF021.UINT8[LL]
#define RSCAN0TMDF021LH RSCAN0.TMDF021.UINT8[LH]
#define RSCAN0TMDF021H RSCAN0.TMDF021.UINT16[H]
#define RSCAN0TMDF021HL RSCAN0.TMDF021.UINT8[HL]
#define RSCAN0TMDF021HH RSCAN0.TMDF021.UINT8[HH]
#define RSCAN0TMDF121 RSCAN0.TMDF121.UINT32
#define RSCAN0TMDF121L RSCAN0.TMDF121.UINT16[L]
#define RSCAN0TMDF121LL RSCAN0.TMDF121.UINT8[LL]
#define RSCAN0TMDF121LH RSCAN0.TMDF121.UINT8[LH]
#define RSCAN0TMDF121H RSCAN0.TMDF121.UINT16[H]
#define RSCAN0TMDF121HL RSCAN0.TMDF121.UINT8[HL]
#define RSCAN0TMDF121HH RSCAN0.TMDF121.UINT8[HH]
#define RSCAN0TMID22 RSCAN0.TMID22.UINT32
#define RSCAN0TMID22L RSCAN0.TMID22.UINT16[L]
#define RSCAN0TMID22LL RSCAN0.TMID22.UINT8[LL]
#define RSCAN0TMID22LH RSCAN0.TMID22.UINT8[LH]
#define RSCAN0TMID22H RSCAN0.TMID22.UINT16[H]
#define RSCAN0TMID22HL RSCAN0.TMID22.UINT8[HL]
#define RSCAN0TMID22HH RSCAN0.TMID22.UINT8[HH]
#define RSCAN0TMPTR22 RSCAN0.TMPTR22.UINT32
#define RSCAN0TMPTR22L RSCAN0.TMPTR22.UINT16[L]
#define RSCAN0TMPTR22LL RSCAN0.TMPTR22.UINT8[LL]
#define RSCAN0TMPTR22LH RSCAN0.TMPTR22.UINT8[LH]
#define RSCAN0TMPTR22H RSCAN0.TMPTR22.UINT16[H]
#define RSCAN0TMPTR22HL RSCAN0.TMPTR22.UINT8[HL]
#define RSCAN0TMPTR22HH RSCAN0.TMPTR22.UINT8[HH]
#define RSCAN0TMDF022 RSCAN0.TMDF022.UINT32
#define RSCAN0TMDF022L RSCAN0.TMDF022.UINT16[L]
#define RSCAN0TMDF022LL RSCAN0.TMDF022.UINT8[LL]
#define RSCAN0TMDF022LH RSCAN0.TMDF022.UINT8[LH]
#define RSCAN0TMDF022H RSCAN0.TMDF022.UINT16[H]
#define RSCAN0TMDF022HL RSCAN0.TMDF022.UINT8[HL]
#define RSCAN0TMDF022HH RSCAN0.TMDF022.UINT8[HH]
#define RSCAN0TMDF122 RSCAN0.TMDF122.UINT32
#define RSCAN0TMDF122L RSCAN0.TMDF122.UINT16[L]
#define RSCAN0TMDF122LL RSCAN0.TMDF122.UINT8[LL]
#define RSCAN0TMDF122LH RSCAN0.TMDF122.UINT8[LH]
#define RSCAN0TMDF122H RSCAN0.TMDF122.UINT16[H]
#define RSCAN0TMDF122HL RSCAN0.TMDF122.UINT8[HL]
#define RSCAN0TMDF122HH RSCAN0.TMDF122.UINT8[HH]
#define RSCAN0TMID23 RSCAN0.TMID23.UINT32
#define RSCAN0TMID23L RSCAN0.TMID23.UINT16[L]
#define RSCAN0TMID23LL RSCAN0.TMID23.UINT8[LL]
#define RSCAN0TMID23LH RSCAN0.TMID23.UINT8[LH]
#define RSCAN0TMID23H RSCAN0.TMID23.UINT16[H]
#define RSCAN0TMID23HL RSCAN0.TMID23.UINT8[HL]
#define RSCAN0TMID23HH RSCAN0.TMID23.UINT8[HH]
#define RSCAN0TMPTR23 RSCAN0.TMPTR23.UINT32
#define RSCAN0TMPTR23L RSCAN0.TMPTR23.UINT16[L]
#define RSCAN0TMPTR23LL RSCAN0.TMPTR23.UINT8[LL]
#define RSCAN0TMPTR23LH RSCAN0.TMPTR23.UINT8[LH]
#define RSCAN0TMPTR23H RSCAN0.TMPTR23.UINT16[H]
#define RSCAN0TMPTR23HL RSCAN0.TMPTR23.UINT8[HL]
#define RSCAN0TMPTR23HH RSCAN0.TMPTR23.UINT8[HH]
#define RSCAN0TMDF023 RSCAN0.TMDF023.UINT32
#define RSCAN0TMDF023L RSCAN0.TMDF023.UINT16[L]
#define RSCAN0TMDF023LL RSCAN0.TMDF023.UINT8[LL]
#define RSCAN0TMDF023LH RSCAN0.TMDF023.UINT8[LH]
#define RSCAN0TMDF023H RSCAN0.TMDF023.UINT16[H]
#define RSCAN0TMDF023HL RSCAN0.TMDF023.UINT8[HL]
#define RSCAN0TMDF023HH RSCAN0.TMDF023.UINT8[HH]
#define RSCAN0TMDF123 RSCAN0.TMDF123.UINT32
#define RSCAN0TMDF123L RSCAN0.TMDF123.UINT16[L]
#define RSCAN0TMDF123LL RSCAN0.TMDF123.UINT8[LL]
#define RSCAN0TMDF123LH RSCAN0.TMDF123.UINT8[LH]
#define RSCAN0TMDF123H RSCAN0.TMDF123.UINT16[H]
#define RSCAN0TMDF123HL RSCAN0.TMDF123.UINT8[HL]
#define RSCAN0TMDF123HH RSCAN0.TMDF123.UINT8[HH]
#define RSCAN0TMID24 RSCAN0.TMID24.UINT32
#define RSCAN0TMID24L RSCAN0.TMID24.UINT16[L]
#define RSCAN0TMID24LL RSCAN0.TMID24.UINT8[LL]
#define RSCAN0TMID24LH RSCAN0.TMID24.UINT8[LH]
#define RSCAN0TMID24H RSCAN0.TMID24.UINT16[H]
#define RSCAN0TMID24HL RSCAN0.TMID24.UINT8[HL]
#define RSCAN0TMID24HH RSCAN0.TMID24.UINT8[HH]
#define RSCAN0TMPTR24 RSCAN0.TMPTR24.UINT32
#define RSCAN0TMPTR24L RSCAN0.TMPTR24.UINT16[L]
#define RSCAN0TMPTR24LL RSCAN0.TMPTR24.UINT8[LL]
#define RSCAN0TMPTR24LH RSCAN0.TMPTR24.UINT8[LH]
#define RSCAN0TMPTR24H RSCAN0.TMPTR24.UINT16[H]
#define RSCAN0TMPTR24HL RSCAN0.TMPTR24.UINT8[HL]
#define RSCAN0TMPTR24HH RSCAN0.TMPTR24.UINT8[HH]
#define RSCAN0TMDF024 RSCAN0.TMDF024.UINT32
#define RSCAN0TMDF024L RSCAN0.TMDF024.UINT16[L]
#define RSCAN0TMDF024LL RSCAN0.TMDF024.UINT8[LL]
#define RSCAN0TMDF024LH RSCAN0.TMDF024.UINT8[LH]
#define RSCAN0TMDF024H RSCAN0.TMDF024.UINT16[H]
#define RSCAN0TMDF024HL RSCAN0.TMDF024.UINT8[HL]
#define RSCAN0TMDF024HH RSCAN0.TMDF024.UINT8[HH]
#define RSCAN0TMDF124 RSCAN0.TMDF124.UINT32
#define RSCAN0TMDF124L RSCAN0.TMDF124.UINT16[L]
#define RSCAN0TMDF124LL RSCAN0.TMDF124.UINT8[LL]
#define RSCAN0TMDF124LH RSCAN0.TMDF124.UINT8[LH]
#define RSCAN0TMDF124H RSCAN0.TMDF124.UINT16[H]
#define RSCAN0TMDF124HL RSCAN0.TMDF124.UINT8[HL]
#define RSCAN0TMDF124HH RSCAN0.TMDF124.UINT8[HH]
#define RSCAN0TMID25 RSCAN0.TMID25.UINT32
#define RSCAN0TMID25L RSCAN0.TMID25.UINT16[L]
#define RSCAN0TMID25LL RSCAN0.TMID25.UINT8[LL]
#define RSCAN0TMID25LH RSCAN0.TMID25.UINT8[LH]
#define RSCAN0TMID25H RSCAN0.TMID25.UINT16[H]
#define RSCAN0TMID25HL RSCAN0.TMID25.UINT8[HL]
#define RSCAN0TMID25HH RSCAN0.TMID25.UINT8[HH]
#define RSCAN0TMPTR25 RSCAN0.TMPTR25.UINT32
#define RSCAN0TMPTR25L RSCAN0.TMPTR25.UINT16[L]
#define RSCAN0TMPTR25LL RSCAN0.TMPTR25.UINT8[LL]
#define RSCAN0TMPTR25LH RSCAN0.TMPTR25.UINT8[LH]
#define RSCAN0TMPTR25H RSCAN0.TMPTR25.UINT16[H]
#define RSCAN0TMPTR25HL RSCAN0.TMPTR25.UINT8[HL]
#define RSCAN0TMPTR25HH RSCAN0.TMPTR25.UINT8[HH]
#define RSCAN0TMDF025 RSCAN0.TMDF025.UINT32
#define RSCAN0TMDF025L RSCAN0.TMDF025.UINT16[L]
#define RSCAN0TMDF025LL RSCAN0.TMDF025.UINT8[LL]
#define RSCAN0TMDF025LH RSCAN0.TMDF025.UINT8[LH]
#define RSCAN0TMDF025H RSCAN0.TMDF025.UINT16[H]
#define RSCAN0TMDF025HL RSCAN0.TMDF025.UINT8[HL]
#define RSCAN0TMDF025HH RSCAN0.TMDF025.UINT8[HH]
#define RSCAN0TMDF125 RSCAN0.TMDF125.UINT32
#define RSCAN0TMDF125L RSCAN0.TMDF125.UINT16[L]
#define RSCAN0TMDF125LL RSCAN0.TMDF125.UINT8[LL]
#define RSCAN0TMDF125LH RSCAN0.TMDF125.UINT8[LH]
#define RSCAN0TMDF125H RSCAN0.TMDF125.UINT16[H]
#define RSCAN0TMDF125HL RSCAN0.TMDF125.UINT8[HL]
#define RSCAN0TMDF125HH RSCAN0.TMDF125.UINT8[HH]
#define RSCAN0TMID26 RSCAN0.TMID26.UINT32
#define RSCAN0TMID26L RSCAN0.TMID26.UINT16[L]
#define RSCAN0TMID26LL RSCAN0.TMID26.UINT8[LL]
#define RSCAN0TMID26LH RSCAN0.TMID26.UINT8[LH]
#define RSCAN0TMID26H RSCAN0.TMID26.UINT16[H]
#define RSCAN0TMID26HL RSCAN0.TMID26.UINT8[HL]
#define RSCAN0TMID26HH RSCAN0.TMID26.UINT8[HH]
#define RSCAN0TMPTR26 RSCAN0.TMPTR26.UINT32
#define RSCAN0TMPTR26L RSCAN0.TMPTR26.UINT16[L]
#define RSCAN0TMPTR26LL RSCAN0.TMPTR26.UINT8[LL]
#define RSCAN0TMPTR26LH RSCAN0.TMPTR26.UINT8[LH]
#define RSCAN0TMPTR26H RSCAN0.TMPTR26.UINT16[H]
#define RSCAN0TMPTR26HL RSCAN0.TMPTR26.UINT8[HL]
#define RSCAN0TMPTR26HH RSCAN0.TMPTR26.UINT8[HH]
#define RSCAN0TMDF026 RSCAN0.TMDF026.UINT32
#define RSCAN0TMDF026L RSCAN0.TMDF026.UINT16[L]
#define RSCAN0TMDF026LL RSCAN0.TMDF026.UINT8[LL]
#define RSCAN0TMDF026LH RSCAN0.TMDF026.UINT8[LH]
#define RSCAN0TMDF026H RSCAN0.TMDF026.UINT16[H]
#define RSCAN0TMDF026HL RSCAN0.TMDF026.UINT8[HL]
#define RSCAN0TMDF026HH RSCAN0.TMDF026.UINT8[HH]
#define RSCAN0TMDF126 RSCAN0.TMDF126.UINT32
#define RSCAN0TMDF126L RSCAN0.TMDF126.UINT16[L]
#define RSCAN0TMDF126LL RSCAN0.TMDF126.UINT8[LL]
#define RSCAN0TMDF126LH RSCAN0.TMDF126.UINT8[LH]
#define RSCAN0TMDF126H RSCAN0.TMDF126.UINT16[H]
#define RSCAN0TMDF126HL RSCAN0.TMDF126.UINT8[HL]
#define RSCAN0TMDF126HH RSCAN0.TMDF126.UINT8[HH]
#define RSCAN0TMID27 RSCAN0.TMID27.UINT32
#define RSCAN0TMID27L RSCAN0.TMID27.UINT16[L]
#define RSCAN0TMID27LL RSCAN0.TMID27.UINT8[LL]
#define RSCAN0TMID27LH RSCAN0.TMID27.UINT8[LH]
#define RSCAN0TMID27H RSCAN0.TMID27.UINT16[H]
#define RSCAN0TMID27HL RSCAN0.TMID27.UINT8[HL]
#define RSCAN0TMID27HH RSCAN0.TMID27.UINT8[HH]
#define RSCAN0TMPTR27 RSCAN0.TMPTR27.UINT32
#define RSCAN0TMPTR27L RSCAN0.TMPTR27.UINT16[L]
#define RSCAN0TMPTR27LL RSCAN0.TMPTR27.UINT8[LL]
#define RSCAN0TMPTR27LH RSCAN0.TMPTR27.UINT8[LH]
#define RSCAN0TMPTR27H RSCAN0.TMPTR27.UINT16[H]
#define RSCAN0TMPTR27HL RSCAN0.TMPTR27.UINT8[HL]
#define RSCAN0TMPTR27HH RSCAN0.TMPTR27.UINT8[HH]
#define RSCAN0TMDF027 RSCAN0.TMDF027.UINT32
#define RSCAN0TMDF027L RSCAN0.TMDF027.UINT16[L]
#define RSCAN0TMDF027LL RSCAN0.TMDF027.UINT8[LL]
#define RSCAN0TMDF027LH RSCAN0.TMDF027.UINT8[LH]
#define RSCAN0TMDF027H RSCAN0.TMDF027.UINT16[H]
#define RSCAN0TMDF027HL RSCAN0.TMDF027.UINT8[HL]
#define RSCAN0TMDF027HH RSCAN0.TMDF027.UINT8[HH]
#define RSCAN0TMDF127 RSCAN0.TMDF127.UINT32
#define RSCAN0TMDF127L RSCAN0.TMDF127.UINT16[L]
#define RSCAN0TMDF127LL RSCAN0.TMDF127.UINT8[LL]
#define RSCAN0TMDF127LH RSCAN0.TMDF127.UINT8[LH]
#define RSCAN0TMDF127H RSCAN0.TMDF127.UINT16[H]
#define RSCAN0TMDF127HL RSCAN0.TMDF127.UINT8[HL]
#define RSCAN0TMDF127HH RSCAN0.TMDF127.UINT8[HH]
#define RSCAN0TMID28 RSCAN0.TMID28.UINT32
#define RSCAN0TMID28L RSCAN0.TMID28.UINT16[L]
#define RSCAN0TMID28LL RSCAN0.TMID28.UINT8[LL]
#define RSCAN0TMID28LH RSCAN0.TMID28.UINT8[LH]
#define RSCAN0TMID28H RSCAN0.TMID28.UINT16[H]
#define RSCAN0TMID28HL RSCAN0.TMID28.UINT8[HL]
#define RSCAN0TMID28HH RSCAN0.TMID28.UINT8[HH]
#define RSCAN0TMPTR28 RSCAN0.TMPTR28.UINT32
#define RSCAN0TMPTR28L RSCAN0.TMPTR28.UINT16[L]
#define RSCAN0TMPTR28LL RSCAN0.TMPTR28.UINT8[LL]
#define RSCAN0TMPTR28LH RSCAN0.TMPTR28.UINT8[LH]
#define RSCAN0TMPTR28H RSCAN0.TMPTR28.UINT16[H]
#define RSCAN0TMPTR28HL RSCAN0.TMPTR28.UINT8[HL]
#define RSCAN0TMPTR28HH RSCAN0.TMPTR28.UINT8[HH]
#define RSCAN0TMDF028 RSCAN0.TMDF028.UINT32
#define RSCAN0TMDF028L RSCAN0.TMDF028.UINT16[L]
#define RSCAN0TMDF028LL RSCAN0.TMDF028.UINT8[LL]
#define RSCAN0TMDF028LH RSCAN0.TMDF028.UINT8[LH]
#define RSCAN0TMDF028H RSCAN0.TMDF028.UINT16[H]
#define RSCAN0TMDF028HL RSCAN0.TMDF028.UINT8[HL]
#define RSCAN0TMDF028HH RSCAN0.TMDF028.UINT8[HH]
#define RSCAN0TMDF128 RSCAN0.TMDF128.UINT32
#define RSCAN0TMDF128L RSCAN0.TMDF128.UINT16[L]
#define RSCAN0TMDF128LL RSCAN0.TMDF128.UINT8[LL]
#define RSCAN0TMDF128LH RSCAN0.TMDF128.UINT8[LH]
#define RSCAN0TMDF128H RSCAN0.TMDF128.UINT16[H]
#define RSCAN0TMDF128HL RSCAN0.TMDF128.UINT8[HL]
#define RSCAN0TMDF128HH RSCAN0.TMDF128.UINT8[HH]
#define RSCAN0TMID29 RSCAN0.TMID29.UINT32
#define RSCAN0TMID29L RSCAN0.TMID29.UINT16[L]
#define RSCAN0TMID29LL RSCAN0.TMID29.UINT8[LL]
#define RSCAN0TMID29LH RSCAN0.TMID29.UINT8[LH]
#define RSCAN0TMID29H RSCAN0.TMID29.UINT16[H]
#define RSCAN0TMID29HL RSCAN0.TMID29.UINT8[HL]
#define RSCAN0TMID29HH RSCAN0.TMID29.UINT8[HH]
#define RSCAN0TMPTR29 RSCAN0.TMPTR29.UINT32
#define RSCAN0TMPTR29L RSCAN0.TMPTR29.UINT16[L]
#define RSCAN0TMPTR29LL RSCAN0.TMPTR29.UINT8[LL]
#define RSCAN0TMPTR29LH RSCAN0.TMPTR29.UINT8[LH]
#define RSCAN0TMPTR29H RSCAN0.TMPTR29.UINT16[H]
#define RSCAN0TMPTR29HL RSCAN0.TMPTR29.UINT8[HL]
#define RSCAN0TMPTR29HH RSCAN0.TMPTR29.UINT8[HH]
#define RSCAN0TMDF029 RSCAN0.TMDF029.UINT32
#define RSCAN0TMDF029L RSCAN0.TMDF029.UINT16[L]
#define RSCAN0TMDF029LL RSCAN0.TMDF029.UINT8[LL]
#define RSCAN0TMDF029LH RSCAN0.TMDF029.UINT8[LH]
#define RSCAN0TMDF029H RSCAN0.TMDF029.UINT16[H]
#define RSCAN0TMDF029HL RSCAN0.TMDF029.UINT8[HL]
#define RSCAN0TMDF029HH RSCAN0.TMDF029.UINT8[HH]
#define RSCAN0TMDF129 RSCAN0.TMDF129.UINT32
#define RSCAN0TMDF129L RSCAN0.TMDF129.UINT16[L]
#define RSCAN0TMDF129LL RSCAN0.TMDF129.UINT8[LL]
#define RSCAN0TMDF129LH RSCAN0.TMDF129.UINT8[LH]
#define RSCAN0TMDF129H RSCAN0.TMDF129.UINT16[H]
#define RSCAN0TMDF129HL RSCAN0.TMDF129.UINT8[HL]
#define RSCAN0TMDF129HH RSCAN0.TMDF129.UINT8[HH]
#define RSCAN0TMID30 RSCAN0.TMID30.UINT32
#define RSCAN0TMID30L RSCAN0.TMID30.UINT16[L]
#define RSCAN0TMID30LL RSCAN0.TMID30.UINT8[LL]
#define RSCAN0TMID30LH RSCAN0.TMID30.UINT8[LH]
#define RSCAN0TMID30H RSCAN0.TMID30.UINT16[H]
#define RSCAN0TMID30HL RSCAN0.TMID30.UINT8[HL]
#define RSCAN0TMID30HH RSCAN0.TMID30.UINT8[HH]
#define RSCAN0TMPTR30 RSCAN0.TMPTR30.UINT32
#define RSCAN0TMPTR30L RSCAN0.TMPTR30.UINT16[L]
#define RSCAN0TMPTR30LL RSCAN0.TMPTR30.UINT8[LL]
#define RSCAN0TMPTR30LH RSCAN0.TMPTR30.UINT8[LH]
#define RSCAN0TMPTR30H RSCAN0.TMPTR30.UINT16[H]
#define RSCAN0TMPTR30HL RSCAN0.TMPTR30.UINT8[HL]
#define RSCAN0TMPTR30HH RSCAN0.TMPTR30.UINT8[HH]
#define RSCAN0TMDF030 RSCAN0.TMDF030.UINT32
#define RSCAN0TMDF030L RSCAN0.TMDF030.UINT16[L]
#define RSCAN0TMDF030LL RSCAN0.TMDF030.UINT8[LL]
#define RSCAN0TMDF030LH RSCAN0.TMDF030.UINT8[LH]
#define RSCAN0TMDF030H RSCAN0.TMDF030.UINT16[H]
#define RSCAN0TMDF030HL RSCAN0.TMDF030.UINT8[HL]
#define RSCAN0TMDF030HH RSCAN0.TMDF030.UINT8[HH]
#define RSCAN0TMDF130 RSCAN0.TMDF130.UINT32
#define RSCAN0TMDF130L RSCAN0.TMDF130.UINT16[L]
#define RSCAN0TMDF130LL RSCAN0.TMDF130.UINT8[LL]
#define RSCAN0TMDF130LH RSCAN0.TMDF130.UINT8[LH]
#define RSCAN0TMDF130H RSCAN0.TMDF130.UINT16[H]
#define RSCAN0TMDF130HL RSCAN0.TMDF130.UINT8[HL]
#define RSCAN0TMDF130HH RSCAN0.TMDF130.UINT8[HH]
#define RSCAN0TMID31 RSCAN0.TMID31.UINT32
#define RSCAN0TMID31L RSCAN0.TMID31.UINT16[L]
#define RSCAN0TMID31LL RSCAN0.TMID31.UINT8[LL]
#define RSCAN0TMID31LH RSCAN0.TMID31.UINT8[LH]
#define RSCAN0TMID31H RSCAN0.TMID31.UINT16[H]
#define RSCAN0TMID31HL RSCAN0.TMID31.UINT8[HL]
#define RSCAN0TMID31HH RSCAN0.TMID31.UINT8[HH]
#define RSCAN0TMPTR31 RSCAN0.TMPTR31.UINT32
#define RSCAN0TMPTR31L RSCAN0.TMPTR31.UINT16[L]
#define RSCAN0TMPTR31LL RSCAN0.TMPTR31.UINT8[LL]
#define RSCAN0TMPTR31LH RSCAN0.TMPTR31.UINT8[LH]
#define RSCAN0TMPTR31H RSCAN0.TMPTR31.UINT16[H]
#define RSCAN0TMPTR31HL RSCAN0.TMPTR31.UINT8[HL]
#define RSCAN0TMPTR31HH RSCAN0.TMPTR31.UINT8[HH]
#define RSCAN0TMDF031 RSCAN0.TMDF031.UINT32
#define RSCAN0TMDF031L RSCAN0.TMDF031.UINT16[L]
#define RSCAN0TMDF031LL RSCAN0.TMDF031.UINT8[LL]
#define RSCAN0TMDF031LH RSCAN0.TMDF031.UINT8[LH]
#define RSCAN0TMDF031H RSCAN0.TMDF031.UINT16[H]
#define RSCAN0TMDF031HL RSCAN0.TMDF031.UINT8[HL]
#define RSCAN0TMDF031HH RSCAN0.TMDF031.UINT8[HH]
#define RSCAN0TMDF131 RSCAN0.TMDF131.UINT32
#define RSCAN0TMDF131L RSCAN0.TMDF131.UINT16[L]
#define RSCAN0TMDF131LL RSCAN0.TMDF131.UINT8[LL]
#define RSCAN0TMDF131LH RSCAN0.TMDF131.UINT8[LH]
#define RSCAN0TMDF131H RSCAN0.TMDF131.UINT16[H]
#define RSCAN0TMDF131HL RSCAN0.TMDF131.UINT8[HL]
#define RSCAN0TMDF131HH RSCAN0.TMDF131.UINT8[HH]
#define RSCAN0TMID32 RSCAN0.TMID32.UINT32
#define RSCAN0TMID32L RSCAN0.TMID32.UINT16[L]
#define RSCAN0TMID32LL RSCAN0.TMID32.UINT8[LL]
#define RSCAN0TMID32LH RSCAN0.TMID32.UINT8[LH]
#define RSCAN0TMID32H RSCAN0.TMID32.UINT16[H]
#define RSCAN0TMID32HL RSCAN0.TMID32.UINT8[HL]
#define RSCAN0TMID32HH RSCAN0.TMID32.UINT8[HH]
#define RSCAN0TMPTR32 RSCAN0.TMPTR32.UINT32
#define RSCAN0TMPTR32L RSCAN0.TMPTR32.UINT16[L]
#define RSCAN0TMPTR32LL RSCAN0.TMPTR32.UINT8[LL]
#define RSCAN0TMPTR32LH RSCAN0.TMPTR32.UINT8[LH]
#define RSCAN0TMPTR32H RSCAN0.TMPTR32.UINT16[H]
#define RSCAN0TMPTR32HL RSCAN0.TMPTR32.UINT8[HL]
#define RSCAN0TMPTR32HH RSCAN0.TMPTR32.UINT8[HH]
#define RSCAN0TMDF032 RSCAN0.TMDF032.UINT32
#define RSCAN0TMDF032L RSCAN0.TMDF032.UINT16[L]
#define RSCAN0TMDF032LL RSCAN0.TMDF032.UINT8[LL]
#define RSCAN0TMDF032LH RSCAN0.TMDF032.UINT8[LH]
#define RSCAN0TMDF032H RSCAN0.TMDF032.UINT16[H]
#define RSCAN0TMDF032HL RSCAN0.TMDF032.UINT8[HL]
#define RSCAN0TMDF032HH RSCAN0.TMDF032.UINT8[HH]
#define RSCAN0TMDF132 RSCAN0.TMDF132.UINT32
#define RSCAN0TMDF132L RSCAN0.TMDF132.UINT16[L]
#define RSCAN0TMDF132LL RSCAN0.TMDF132.UINT8[LL]
#define RSCAN0TMDF132LH RSCAN0.TMDF132.UINT8[LH]
#define RSCAN0TMDF132H RSCAN0.TMDF132.UINT16[H]
#define RSCAN0TMDF132HL RSCAN0.TMDF132.UINT8[HL]
#define RSCAN0TMDF132HH RSCAN0.TMDF132.UINT8[HH]
#define RSCAN0TMID33 RSCAN0.TMID33.UINT32
#define RSCAN0TMID33L RSCAN0.TMID33.UINT16[L]
#define RSCAN0TMID33LL RSCAN0.TMID33.UINT8[LL]
#define RSCAN0TMID33LH RSCAN0.TMID33.UINT8[LH]
#define RSCAN0TMID33H RSCAN0.TMID33.UINT16[H]
#define RSCAN0TMID33HL RSCAN0.TMID33.UINT8[HL]
#define RSCAN0TMID33HH RSCAN0.TMID33.UINT8[HH]
#define RSCAN0TMPTR33 RSCAN0.TMPTR33.UINT32
#define RSCAN0TMPTR33L RSCAN0.TMPTR33.UINT16[L]
#define RSCAN0TMPTR33LL RSCAN0.TMPTR33.UINT8[LL]
#define RSCAN0TMPTR33LH RSCAN0.TMPTR33.UINT8[LH]
#define RSCAN0TMPTR33H RSCAN0.TMPTR33.UINT16[H]
#define RSCAN0TMPTR33HL RSCAN0.TMPTR33.UINT8[HL]
#define RSCAN0TMPTR33HH RSCAN0.TMPTR33.UINT8[HH]
#define RSCAN0TMDF033 RSCAN0.TMDF033.UINT32
#define RSCAN0TMDF033L RSCAN0.TMDF033.UINT16[L]
#define RSCAN0TMDF033LL RSCAN0.TMDF033.UINT8[LL]
#define RSCAN0TMDF033LH RSCAN0.TMDF033.UINT8[LH]
#define RSCAN0TMDF033H RSCAN0.TMDF033.UINT16[H]
#define RSCAN0TMDF033HL RSCAN0.TMDF033.UINT8[HL]
#define RSCAN0TMDF033HH RSCAN0.TMDF033.UINT8[HH]
#define RSCAN0TMDF133 RSCAN0.TMDF133.UINT32
#define RSCAN0TMDF133L RSCAN0.TMDF133.UINT16[L]
#define RSCAN0TMDF133LL RSCAN0.TMDF133.UINT8[LL]
#define RSCAN0TMDF133LH RSCAN0.TMDF133.UINT8[LH]
#define RSCAN0TMDF133H RSCAN0.TMDF133.UINT16[H]
#define RSCAN0TMDF133HL RSCAN0.TMDF133.UINT8[HL]
#define RSCAN0TMDF133HH RSCAN0.TMDF133.UINT8[HH]
#define RSCAN0TMID34 RSCAN0.TMID34.UINT32
#define RSCAN0TMID34L RSCAN0.TMID34.UINT16[L]
#define RSCAN0TMID34LL RSCAN0.TMID34.UINT8[LL]
#define RSCAN0TMID34LH RSCAN0.TMID34.UINT8[LH]
#define RSCAN0TMID34H RSCAN0.TMID34.UINT16[H]
#define RSCAN0TMID34HL RSCAN0.TMID34.UINT8[HL]
#define RSCAN0TMID34HH RSCAN0.TMID34.UINT8[HH]
#define RSCAN0TMPTR34 RSCAN0.TMPTR34.UINT32
#define RSCAN0TMPTR34L RSCAN0.TMPTR34.UINT16[L]
#define RSCAN0TMPTR34LL RSCAN0.TMPTR34.UINT8[LL]
#define RSCAN0TMPTR34LH RSCAN0.TMPTR34.UINT8[LH]
#define RSCAN0TMPTR34H RSCAN0.TMPTR34.UINT16[H]
#define RSCAN0TMPTR34HL RSCAN0.TMPTR34.UINT8[HL]
#define RSCAN0TMPTR34HH RSCAN0.TMPTR34.UINT8[HH]
#define RSCAN0TMDF034 RSCAN0.TMDF034.UINT32
#define RSCAN0TMDF034L RSCAN0.TMDF034.UINT16[L]
#define RSCAN0TMDF034LL RSCAN0.TMDF034.UINT8[LL]
#define RSCAN0TMDF034LH RSCAN0.TMDF034.UINT8[LH]
#define RSCAN0TMDF034H RSCAN0.TMDF034.UINT16[H]
#define RSCAN0TMDF034HL RSCAN0.TMDF034.UINT8[HL]
#define RSCAN0TMDF034HH RSCAN0.TMDF034.UINT8[HH]
#define RSCAN0TMDF134 RSCAN0.TMDF134.UINT32
#define RSCAN0TMDF134L RSCAN0.TMDF134.UINT16[L]
#define RSCAN0TMDF134LL RSCAN0.TMDF134.UINT8[LL]
#define RSCAN0TMDF134LH RSCAN0.TMDF134.UINT8[LH]
#define RSCAN0TMDF134H RSCAN0.TMDF134.UINT16[H]
#define RSCAN0TMDF134HL RSCAN0.TMDF134.UINT8[HL]
#define RSCAN0TMDF134HH RSCAN0.TMDF134.UINT8[HH]
#define RSCAN0TMID35 RSCAN0.TMID35.UINT32
#define RSCAN0TMID35L RSCAN0.TMID35.UINT16[L]
#define RSCAN0TMID35LL RSCAN0.TMID35.UINT8[LL]
#define RSCAN0TMID35LH RSCAN0.TMID35.UINT8[LH]
#define RSCAN0TMID35H RSCAN0.TMID35.UINT16[H]
#define RSCAN0TMID35HL RSCAN0.TMID35.UINT8[HL]
#define RSCAN0TMID35HH RSCAN0.TMID35.UINT8[HH]
#define RSCAN0TMPTR35 RSCAN0.TMPTR35.UINT32
#define RSCAN0TMPTR35L RSCAN0.TMPTR35.UINT16[L]
#define RSCAN0TMPTR35LL RSCAN0.TMPTR35.UINT8[LL]
#define RSCAN0TMPTR35LH RSCAN0.TMPTR35.UINT8[LH]
#define RSCAN0TMPTR35H RSCAN0.TMPTR35.UINT16[H]
#define RSCAN0TMPTR35HL RSCAN0.TMPTR35.UINT8[HL]
#define RSCAN0TMPTR35HH RSCAN0.TMPTR35.UINT8[HH]
#define RSCAN0TMDF035 RSCAN0.TMDF035.UINT32
#define RSCAN0TMDF035L RSCAN0.TMDF035.UINT16[L]
#define RSCAN0TMDF035LL RSCAN0.TMDF035.UINT8[LL]
#define RSCAN0TMDF035LH RSCAN0.TMDF035.UINT8[LH]
#define RSCAN0TMDF035H RSCAN0.TMDF035.UINT16[H]
#define RSCAN0TMDF035HL RSCAN0.TMDF035.UINT8[HL]
#define RSCAN0TMDF035HH RSCAN0.TMDF035.UINT8[HH]
#define RSCAN0TMDF135 RSCAN0.TMDF135.UINT32
#define RSCAN0TMDF135L RSCAN0.TMDF135.UINT16[L]
#define RSCAN0TMDF135LL RSCAN0.TMDF135.UINT8[LL]
#define RSCAN0TMDF135LH RSCAN0.TMDF135.UINT8[LH]
#define RSCAN0TMDF135H RSCAN0.TMDF135.UINT16[H]
#define RSCAN0TMDF135HL RSCAN0.TMDF135.UINT8[HL]
#define RSCAN0TMDF135HH RSCAN0.TMDF135.UINT8[HH]
#define RSCAN0TMID36 RSCAN0.TMID36.UINT32
#define RSCAN0TMID36L RSCAN0.TMID36.UINT16[L]
#define RSCAN0TMID36LL RSCAN0.TMID36.UINT8[LL]
#define RSCAN0TMID36LH RSCAN0.TMID36.UINT8[LH]
#define RSCAN0TMID36H RSCAN0.TMID36.UINT16[H]
#define RSCAN0TMID36HL RSCAN0.TMID36.UINT8[HL]
#define RSCAN0TMID36HH RSCAN0.TMID36.UINT8[HH]
#define RSCAN0TMPTR36 RSCAN0.TMPTR36.UINT32
#define RSCAN0TMPTR36L RSCAN0.TMPTR36.UINT16[L]
#define RSCAN0TMPTR36LL RSCAN0.TMPTR36.UINT8[LL]
#define RSCAN0TMPTR36LH RSCAN0.TMPTR36.UINT8[LH]
#define RSCAN0TMPTR36H RSCAN0.TMPTR36.UINT16[H]
#define RSCAN0TMPTR36HL RSCAN0.TMPTR36.UINT8[HL]
#define RSCAN0TMPTR36HH RSCAN0.TMPTR36.UINT8[HH]
#define RSCAN0TMDF036 RSCAN0.TMDF036.UINT32
#define RSCAN0TMDF036L RSCAN0.TMDF036.UINT16[L]
#define RSCAN0TMDF036LL RSCAN0.TMDF036.UINT8[LL]
#define RSCAN0TMDF036LH RSCAN0.TMDF036.UINT8[LH]
#define RSCAN0TMDF036H RSCAN0.TMDF036.UINT16[H]
#define RSCAN0TMDF036HL RSCAN0.TMDF036.UINT8[HL]
#define RSCAN0TMDF036HH RSCAN0.TMDF036.UINT8[HH]
#define RSCAN0TMDF136 RSCAN0.TMDF136.UINT32
#define RSCAN0TMDF136L RSCAN0.TMDF136.UINT16[L]
#define RSCAN0TMDF136LL RSCAN0.TMDF136.UINT8[LL]
#define RSCAN0TMDF136LH RSCAN0.TMDF136.UINT8[LH]
#define RSCAN0TMDF136H RSCAN0.TMDF136.UINT16[H]
#define RSCAN0TMDF136HL RSCAN0.TMDF136.UINT8[HL]
#define RSCAN0TMDF136HH RSCAN0.TMDF136.UINT8[HH]
#define RSCAN0TMID37 RSCAN0.TMID37.UINT32
#define RSCAN0TMID37L RSCAN0.TMID37.UINT16[L]
#define RSCAN0TMID37LL RSCAN0.TMID37.UINT8[LL]
#define RSCAN0TMID37LH RSCAN0.TMID37.UINT8[LH]
#define RSCAN0TMID37H RSCAN0.TMID37.UINT16[H]
#define RSCAN0TMID37HL RSCAN0.TMID37.UINT8[HL]
#define RSCAN0TMID37HH RSCAN0.TMID37.UINT8[HH]
#define RSCAN0TMPTR37 RSCAN0.TMPTR37.UINT32
#define RSCAN0TMPTR37L RSCAN0.TMPTR37.UINT16[L]
#define RSCAN0TMPTR37LL RSCAN0.TMPTR37.UINT8[LL]
#define RSCAN0TMPTR37LH RSCAN0.TMPTR37.UINT8[LH]
#define RSCAN0TMPTR37H RSCAN0.TMPTR37.UINT16[H]
#define RSCAN0TMPTR37HL RSCAN0.TMPTR37.UINT8[HL]
#define RSCAN0TMPTR37HH RSCAN0.TMPTR37.UINT8[HH]
#define RSCAN0TMDF037 RSCAN0.TMDF037.UINT32
#define RSCAN0TMDF037L RSCAN0.TMDF037.UINT16[L]
#define RSCAN0TMDF037LL RSCAN0.TMDF037.UINT8[LL]
#define RSCAN0TMDF037LH RSCAN0.TMDF037.UINT8[LH]
#define RSCAN0TMDF037H RSCAN0.TMDF037.UINT16[H]
#define RSCAN0TMDF037HL RSCAN0.TMDF037.UINT8[HL]
#define RSCAN0TMDF037HH RSCAN0.TMDF037.UINT8[HH]
#define RSCAN0TMDF137 RSCAN0.TMDF137.UINT32
#define RSCAN0TMDF137L RSCAN0.TMDF137.UINT16[L]
#define RSCAN0TMDF137LL RSCAN0.TMDF137.UINT8[LL]
#define RSCAN0TMDF137LH RSCAN0.TMDF137.UINT8[LH]
#define RSCAN0TMDF137H RSCAN0.TMDF137.UINT16[H]
#define RSCAN0TMDF137HL RSCAN0.TMDF137.UINT8[HL]
#define RSCAN0TMDF137HH RSCAN0.TMDF137.UINT8[HH]
#define RSCAN0TMID38 RSCAN0.TMID38.UINT32
#define RSCAN0TMID38L RSCAN0.TMID38.UINT16[L]
#define RSCAN0TMID38LL RSCAN0.TMID38.UINT8[LL]
#define RSCAN0TMID38LH RSCAN0.TMID38.UINT8[LH]
#define RSCAN0TMID38H RSCAN0.TMID38.UINT16[H]
#define RSCAN0TMID38HL RSCAN0.TMID38.UINT8[HL]
#define RSCAN0TMID38HH RSCAN0.TMID38.UINT8[HH]
#define RSCAN0TMPTR38 RSCAN0.TMPTR38.UINT32
#define RSCAN0TMPTR38L RSCAN0.TMPTR38.UINT16[L]
#define RSCAN0TMPTR38LL RSCAN0.TMPTR38.UINT8[LL]
#define RSCAN0TMPTR38LH RSCAN0.TMPTR38.UINT8[LH]
#define RSCAN0TMPTR38H RSCAN0.TMPTR38.UINT16[H]
#define RSCAN0TMPTR38HL RSCAN0.TMPTR38.UINT8[HL]
#define RSCAN0TMPTR38HH RSCAN0.TMPTR38.UINT8[HH]
#define RSCAN0TMDF038 RSCAN0.TMDF038.UINT32
#define RSCAN0TMDF038L RSCAN0.TMDF038.UINT16[L]
#define RSCAN0TMDF038LL RSCAN0.TMDF038.UINT8[LL]
#define RSCAN0TMDF038LH RSCAN0.TMDF038.UINT8[LH]
#define RSCAN0TMDF038H RSCAN0.TMDF038.UINT16[H]
#define RSCAN0TMDF038HL RSCAN0.TMDF038.UINT8[HL]
#define RSCAN0TMDF038HH RSCAN0.TMDF038.UINT8[HH]
#define RSCAN0TMDF138 RSCAN0.TMDF138.UINT32
#define RSCAN0TMDF138L RSCAN0.TMDF138.UINT16[L]
#define RSCAN0TMDF138LL RSCAN0.TMDF138.UINT8[LL]
#define RSCAN0TMDF138LH RSCAN0.TMDF138.UINT8[LH]
#define RSCAN0TMDF138H RSCAN0.TMDF138.UINT16[H]
#define RSCAN0TMDF138HL RSCAN0.TMDF138.UINT8[HL]
#define RSCAN0TMDF138HH RSCAN0.TMDF138.UINT8[HH]
#define RSCAN0TMID39 RSCAN0.TMID39.UINT32
#define RSCAN0TMID39L RSCAN0.TMID39.UINT16[L]
#define RSCAN0TMID39LL RSCAN0.TMID39.UINT8[LL]
#define RSCAN0TMID39LH RSCAN0.TMID39.UINT8[LH]
#define RSCAN0TMID39H RSCAN0.TMID39.UINT16[H]
#define RSCAN0TMID39HL RSCAN0.TMID39.UINT8[HL]
#define RSCAN0TMID39HH RSCAN0.TMID39.UINT8[HH]
#define RSCAN0TMPTR39 RSCAN0.TMPTR39.UINT32
#define RSCAN0TMPTR39L RSCAN0.TMPTR39.UINT16[L]
#define RSCAN0TMPTR39LL RSCAN0.TMPTR39.UINT8[LL]
#define RSCAN0TMPTR39LH RSCAN0.TMPTR39.UINT8[LH]
#define RSCAN0TMPTR39H RSCAN0.TMPTR39.UINT16[H]
#define RSCAN0TMPTR39HL RSCAN0.TMPTR39.UINT8[HL]
#define RSCAN0TMPTR39HH RSCAN0.TMPTR39.UINT8[HH]
#define RSCAN0TMDF039 RSCAN0.TMDF039.UINT32
#define RSCAN0TMDF039L RSCAN0.TMDF039.UINT16[L]
#define RSCAN0TMDF039LL RSCAN0.TMDF039.UINT8[LL]
#define RSCAN0TMDF039LH RSCAN0.TMDF039.UINT8[LH]
#define RSCAN0TMDF039H RSCAN0.TMDF039.UINT16[H]
#define RSCAN0TMDF039HL RSCAN0.TMDF039.UINT8[HL]
#define RSCAN0TMDF039HH RSCAN0.TMDF039.UINT8[HH]
#define RSCAN0TMDF139 RSCAN0.TMDF139.UINT32
#define RSCAN0TMDF139L RSCAN0.TMDF139.UINT16[L]
#define RSCAN0TMDF139LL RSCAN0.TMDF139.UINT8[LL]
#define RSCAN0TMDF139LH RSCAN0.TMDF139.UINT8[LH]
#define RSCAN0TMDF139H RSCAN0.TMDF139.UINT16[H]
#define RSCAN0TMDF139HL RSCAN0.TMDF139.UINT8[HL]
#define RSCAN0TMDF139HH RSCAN0.TMDF139.UINT8[HH]
#define RSCAN0TMID40 RSCAN0.TMID40.UINT32
#define RSCAN0TMID40L RSCAN0.TMID40.UINT16[L]
#define RSCAN0TMID40LL RSCAN0.TMID40.UINT8[LL]
#define RSCAN0TMID40LH RSCAN0.TMID40.UINT8[LH]
#define RSCAN0TMID40H RSCAN0.TMID40.UINT16[H]
#define RSCAN0TMID40HL RSCAN0.TMID40.UINT8[HL]
#define RSCAN0TMID40HH RSCAN0.TMID40.UINT8[HH]
#define RSCAN0TMPTR40 RSCAN0.TMPTR40.UINT32
#define RSCAN0TMPTR40L RSCAN0.TMPTR40.UINT16[L]
#define RSCAN0TMPTR40LL RSCAN0.TMPTR40.UINT8[LL]
#define RSCAN0TMPTR40LH RSCAN0.TMPTR40.UINT8[LH]
#define RSCAN0TMPTR40H RSCAN0.TMPTR40.UINT16[H]
#define RSCAN0TMPTR40HL RSCAN0.TMPTR40.UINT8[HL]
#define RSCAN0TMPTR40HH RSCAN0.TMPTR40.UINT8[HH]
#define RSCAN0TMDF040 RSCAN0.TMDF040.UINT32
#define RSCAN0TMDF040L RSCAN0.TMDF040.UINT16[L]
#define RSCAN0TMDF040LL RSCAN0.TMDF040.UINT8[LL]
#define RSCAN0TMDF040LH RSCAN0.TMDF040.UINT8[LH]
#define RSCAN0TMDF040H RSCAN0.TMDF040.UINT16[H]
#define RSCAN0TMDF040HL RSCAN0.TMDF040.UINT8[HL]
#define RSCAN0TMDF040HH RSCAN0.TMDF040.UINT8[HH]
#define RSCAN0TMDF140 RSCAN0.TMDF140.UINT32
#define RSCAN0TMDF140L RSCAN0.TMDF140.UINT16[L]
#define RSCAN0TMDF140LL RSCAN0.TMDF140.UINT8[LL]
#define RSCAN0TMDF140LH RSCAN0.TMDF140.UINT8[LH]
#define RSCAN0TMDF140H RSCAN0.TMDF140.UINT16[H]
#define RSCAN0TMDF140HL RSCAN0.TMDF140.UINT8[HL]
#define RSCAN0TMDF140HH RSCAN0.TMDF140.UINT8[HH]
#define RSCAN0TMID41 RSCAN0.TMID41.UINT32
#define RSCAN0TMID41L RSCAN0.TMID41.UINT16[L]
#define RSCAN0TMID41LL RSCAN0.TMID41.UINT8[LL]
#define RSCAN0TMID41LH RSCAN0.TMID41.UINT8[LH]
#define RSCAN0TMID41H RSCAN0.TMID41.UINT16[H]
#define RSCAN0TMID41HL RSCAN0.TMID41.UINT8[HL]
#define RSCAN0TMID41HH RSCAN0.TMID41.UINT8[HH]
#define RSCAN0TMPTR41 RSCAN0.TMPTR41.UINT32
#define RSCAN0TMPTR41L RSCAN0.TMPTR41.UINT16[L]
#define RSCAN0TMPTR41LL RSCAN0.TMPTR41.UINT8[LL]
#define RSCAN0TMPTR41LH RSCAN0.TMPTR41.UINT8[LH]
#define RSCAN0TMPTR41H RSCAN0.TMPTR41.UINT16[H]
#define RSCAN0TMPTR41HL RSCAN0.TMPTR41.UINT8[HL]
#define RSCAN0TMPTR41HH RSCAN0.TMPTR41.UINT8[HH]
#define RSCAN0TMDF041 RSCAN0.TMDF041.UINT32
#define RSCAN0TMDF041L RSCAN0.TMDF041.UINT16[L]
#define RSCAN0TMDF041LL RSCAN0.TMDF041.UINT8[LL]
#define RSCAN0TMDF041LH RSCAN0.TMDF041.UINT8[LH]
#define RSCAN0TMDF041H RSCAN0.TMDF041.UINT16[H]
#define RSCAN0TMDF041HL RSCAN0.TMDF041.UINT8[HL]
#define RSCAN0TMDF041HH RSCAN0.TMDF041.UINT8[HH]
#define RSCAN0TMDF141 RSCAN0.TMDF141.UINT32
#define RSCAN0TMDF141L RSCAN0.TMDF141.UINT16[L]
#define RSCAN0TMDF141LL RSCAN0.TMDF141.UINT8[LL]
#define RSCAN0TMDF141LH RSCAN0.TMDF141.UINT8[LH]
#define RSCAN0TMDF141H RSCAN0.TMDF141.UINT16[H]
#define RSCAN0TMDF141HL RSCAN0.TMDF141.UINT8[HL]
#define RSCAN0TMDF141HH RSCAN0.TMDF141.UINT8[HH]
#define RSCAN0TMID42 RSCAN0.TMID42.UINT32
#define RSCAN0TMID42L RSCAN0.TMID42.UINT16[L]
#define RSCAN0TMID42LL RSCAN0.TMID42.UINT8[LL]
#define RSCAN0TMID42LH RSCAN0.TMID42.UINT8[LH]
#define RSCAN0TMID42H RSCAN0.TMID42.UINT16[H]
#define RSCAN0TMID42HL RSCAN0.TMID42.UINT8[HL]
#define RSCAN0TMID42HH RSCAN0.TMID42.UINT8[HH]
#define RSCAN0TMPTR42 RSCAN0.TMPTR42.UINT32
#define RSCAN0TMPTR42L RSCAN0.TMPTR42.UINT16[L]
#define RSCAN0TMPTR42LL RSCAN0.TMPTR42.UINT8[LL]
#define RSCAN0TMPTR42LH RSCAN0.TMPTR42.UINT8[LH]
#define RSCAN0TMPTR42H RSCAN0.TMPTR42.UINT16[H]
#define RSCAN0TMPTR42HL RSCAN0.TMPTR42.UINT8[HL]
#define RSCAN0TMPTR42HH RSCAN0.TMPTR42.UINT8[HH]
#define RSCAN0TMDF042 RSCAN0.TMDF042.UINT32
#define RSCAN0TMDF042L RSCAN0.TMDF042.UINT16[L]
#define RSCAN0TMDF042LL RSCAN0.TMDF042.UINT8[LL]
#define RSCAN0TMDF042LH RSCAN0.TMDF042.UINT8[LH]
#define RSCAN0TMDF042H RSCAN0.TMDF042.UINT16[H]
#define RSCAN0TMDF042HL RSCAN0.TMDF042.UINT8[HL]
#define RSCAN0TMDF042HH RSCAN0.TMDF042.UINT8[HH]
#define RSCAN0TMDF142 RSCAN0.TMDF142.UINT32
#define RSCAN0TMDF142L RSCAN0.TMDF142.UINT16[L]
#define RSCAN0TMDF142LL RSCAN0.TMDF142.UINT8[LL]
#define RSCAN0TMDF142LH RSCAN0.TMDF142.UINT8[LH]
#define RSCAN0TMDF142H RSCAN0.TMDF142.UINT16[H]
#define RSCAN0TMDF142HL RSCAN0.TMDF142.UINT8[HL]
#define RSCAN0TMDF142HH RSCAN0.TMDF142.UINT8[HH]
#define RSCAN0TMID43 RSCAN0.TMID43.UINT32
#define RSCAN0TMID43L RSCAN0.TMID43.UINT16[L]
#define RSCAN0TMID43LL RSCAN0.TMID43.UINT8[LL]
#define RSCAN0TMID43LH RSCAN0.TMID43.UINT8[LH]
#define RSCAN0TMID43H RSCAN0.TMID43.UINT16[H]
#define RSCAN0TMID43HL RSCAN0.TMID43.UINT8[HL]
#define RSCAN0TMID43HH RSCAN0.TMID43.UINT8[HH]
#define RSCAN0TMPTR43 RSCAN0.TMPTR43.UINT32
#define RSCAN0TMPTR43L RSCAN0.TMPTR43.UINT16[L]
#define RSCAN0TMPTR43LL RSCAN0.TMPTR43.UINT8[LL]
#define RSCAN0TMPTR43LH RSCAN0.TMPTR43.UINT8[LH]
#define RSCAN0TMPTR43H RSCAN0.TMPTR43.UINT16[H]
#define RSCAN0TMPTR43HL RSCAN0.TMPTR43.UINT8[HL]
#define RSCAN0TMPTR43HH RSCAN0.TMPTR43.UINT8[HH]
#define RSCAN0TMDF043 RSCAN0.TMDF043.UINT32
#define RSCAN0TMDF043L RSCAN0.TMDF043.UINT16[L]
#define RSCAN0TMDF043LL RSCAN0.TMDF043.UINT8[LL]
#define RSCAN0TMDF043LH RSCAN0.TMDF043.UINT8[LH]
#define RSCAN0TMDF043H RSCAN0.TMDF043.UINT16[H]
#define RSCAN0TMDF043HL RSCAN0.TMDF043.UINT8[HL]
#define RSCAN0TMDF043HH RSCAN0.TMDF043.UINT8[HH]
#define RSCAN0TMDF143 RSCAN0.TMDF143.UINT32
#define RSCAN0TMDF143L RSCAN0.TMDF143.UINT16[L]
#define RSCAN0TMDF143LL RSCAN0.TMDF143.UINT8[LL]
#define RSCAN0TMDF143LH RSCAN0.TMDF143.UINT8[LH]
#define RSCAN0TMDF143H RSCAN0.TMDF143.UINT16[H]
#define RSCAN0TMDF143HL RSCAN0.TMDF143.UINT8[HL]
#define RSCAN0TMDF143HH RSCAN0.TMDF143.UINT8[HH]
#define RSCAN0TMID44 RSCAN0.TMID44.UINT32
#define RSCAN0TMID44L RSCAN0.TMID44.UINT16[L]
#define RSCAN0TMID44LL RSCAN0.TMID44.UINT8[LL]
#define RSCAN0TMID44LH RSCAN0.TMID44.UINT8[LH]
#define RSCAN0TMID44H RSCAN0.TMID44.UINT16[H]
#define RSCAN0TMID44HL RSCAN0.TMID44.UINT8[HL]
#define RSCAN0TMID44HH RSCAN0.TMID44.UINT8[HH]
#define RSCAN0TMPTR44 RSCAN0.TMPTR44.UINT32
#define RSCAN0TMPTR44L RSCAN0.TMPTR44.UINT16[L]
#define RSCAN0TMPTR44LL RSCAN0.TMPTR44.UINT8[LL]
#define RSCAN0TMPTR44LH RSCAN0.TMPTR44.UINT8[LH]
#define RSCAN0TMPTR44H RSCAN0.TMPTR44.UINT16[H]
#define RSCAN0TMPTR44HL RSCAN0.TMPTR44.UINT8[HL]
#define RSCAN0TMPTR44HH RSCAN0.TMPTR44.UINT8[HH]
#define RSCAN0TMDF044 RSCAN0.TMDF044.UINT32
#define RSCAN0TMDF044L RSCAN0.TMDF044.UINT16[L]
#define RSCAN0TMDF044LL RSCAN0.TMDF044.UINT8[LL]
#define RSCAN0TMDF044LH RSCAN0.TMDF044.UINT8[LH]
#define RSCAN0TMDF044H RSCAN0.TMDF044.UINT16[H]
#define RSCAN0TMDF044HL RSCAN0.TMDF044.UINT8[HL]
#define RSCAN0TMDF044HH RSCAN0.TMDF044.UINT8[HH]
#define RSCAN0TMDF144 RSCAN0.TMDF144.UINT32
#define RSCAN0TMDF144L RSCAN0.TMDF144.UINT16[L]
#define RSCAN0TMDF144LL RSCAN0.TMDF144.UINT8[LL]
#define RSCAN0TMDF144LH RSCAN0.TMDF144.UINT8[LH]
#define RSCAN0TMDF144H RSCAN0.TMDF144.UINT16[H]
#define RSCAN0TMDF144HL RSCAN0.TMDF144.UINT8[HL]
#define RSCAN0TMDF144HH RSCAN0.TMDF144.UINT8[HH]
#define RSCAN0TMID45 RSCAN0.TMID45.UINT32
#define RSCAN0TMID45L RSCAN0.TMID45.UINT16[L]
#define RSCAN0TMID45LL RSCAN0.TMID45.UINT8[LL]
#define RSCAN0TMID45LH RSCAN0.TMID45.UINT8[LH]
#define RSCAN0TMID45H RSCAN0.TMID45.UINT16[H]
#define RSCAN0TMID45HL RSCAN0.TMID45.UINT8[HL]
#define RSCAN0TMID45HH RSCAN0.TMID45.UINT8[HH]
#define RSCAN0TMPTR45 RSCAN0.TMPTR45.UINT32
#define RSCAN0TMPTR45L RSCAN0.TMPTR45.UINT16[L]
#define RSCAN0TMPTR45LL RSCAN0.TMPTR45.UINT8[LL]
#define RSCAN0TMPTR45LH RSCAN0.TMPTR45.UINT8[LH]
#define RSCAN0TMPTR45H RSCAN0.TMPTR45.UINT16[H]
#define RSCAN0TMPTR45HL RSCAN0.TMPTR45.UINT8[HL]
#define RSCAN0TMPTR45HH RSCAN0.TMPTR45.UINT8[HH]
#define RSCAN0TMDF045 RSCAN0.TMDF045.UINT32
#define RSCAN0TMDF045L RSCAN0.TMDF045.UINT16[L]
#define RSCAN0TMDF045LL RSCAN0.TMDF045.UINT8[LL]
#define RSCAN0TMDF045LH RSCAN0.TMDF045.UINT8[LH]
#define RSCAN0TMDF045H RSCAN0.TMDF045.UINT16[H]
#define RSCAN0TMDF045HL RSCAN0.TMDF045.UINT8[HL]
#define RSCAN0TMDF045HH RSCAN0.TMDF045.UINT8[HH]
#define RSCAN0TMDF145 RSCAN0.TMDF145.UINT32
#define RSCAN0TMDF145L RSCAN0.TMDF145.UINT16[L]
#define RSCAN0TMDF145LL RSCAN0.TMDF145.UINT8[LL]
#define RSCAN0TMDF145LH RSCAN0.TMDF145.UINT8[LH]
#define RSCAN0TMDF145H RSCAN0.TMDF145.UINT16[H]
#define RSCAN0TMDF145HL RSCAN0.TMDF145.UINT8[HL]
#define RSCAN0TMDF145HH RSCAN0.TMDF145.UINT8[HH]
#define RSCAN0TMID46 RSCAN0.TMID46.UINT32
#define RSCAN0TMID46L RSCAN0.TMID46.UINT16[L]
#define RSCAN0TMID46LL RSCAN0.TMID46.UINT8[LL]
#define RSCAN0TMID46LH RSCAN0.TMID46.UINT8[LH]
#define RSCAN0TMID46H RSCAN0.TMID46.UINT16[H]
#define RSCAN0TMID46HL RSCAN0.TMID46.UINT8[HL]
#define RSCAN0TMID46HH RSCAN0.TMID46.UINT8[HH]
#define RSCAN0TMPTR46 RSCAN0.TMPTR46.UINT32
#define RSCAN0TMPTR46L RSCAN0.TMPTR46.UINT16[L]
#define RSCAN0TMPTR46LL RSCAN0.TMPTR46.UINT8[LL]
#define RSCAN0TMPTR46LH RSCAN0.TMPTR46.UINT8[LH]
#define RSCAN0TMPTR46H RSCAN0.TMPTR46.UINT16[H]
#define RSCAN0TMPTR46HL RSCAN0.TMPTR46.UINT8[HL]
#define RSCAN0TMPTR46HH RSCAN0.TMPTR46.UINT8[HH]
#define RSCAN0TMDF046 RSCAN0.TMDF046.UINT32
#define RSCAN0TMDF046L RSCAN0.TMDF046.UINT16[L]
#define RSCAN0TMDF046LL RSCAN0.TMDF046.UINT8[LL]
#define RSCAN0TMDF046LH RSCAN0.TMDF046.UINT8[LH]
#define RSCAN0TMDF046H RSCAN0.TMDF046.UINT16[H]
#define RSCAN0TMDF046HL RSCAN0.TMDF046.UINT8[HL]
#define RSCAN0TMDF046HH RSCAN0.TMDF046.UINT8[HH]
#define RSCAN0TMDF146 RSCAN0.TMDF146.UINT32
#define RSCAN0TMDF146L RSCAN0.TMDF146.UINT16[L]
#define RSCAN0TMDF146LL RSCAN0.TMDF146.UINT8[LL]
#define RSCAN0TMDF146LH RSCAN0.TMDF146.UINT8[LH]
#define RSCAN0TMDF146H RSCAN0.TMDF146.UINT16[H]
#define RSCAN0TMDF146HL RSCAN0.TMDF146.UINT8[HL]
#define RSCAN0TMDF146HH RSCAN0.TMDF146.UINT8[HH]
#define RSCAN0TMID47 RSCAN0.TMID47.UINT32
#define RSCAN0TMID47L RSCAN0.TMID47.UINT16[L]
#define RSCAN0TMID47LL RSCAN0.TMID47.UINT8[LL]
#define RSCAN0TMID47LH RSCAN0.TMID47.UINT8[LH]
#define RSCAN0TMID47H RSCAN0.TMID47.UINT16[H]
#define RSCAN0TMID47HL RSCAN0.TMID47.UINT8[HL]
#define RSCAN0TMID47HH RSCAN0.TMID47.UINT8[HH]
#define RSCAN0TMPTR47 RSCAN0.TMPTR47.UINT32
#define RSCAN0TMPTR47L RSCAN0.TMPTR47.UINT16[L]
#define RSCAN0TMPTR47LL RSCAN0.TMPTR47.UINT8[LL]
#define RSCAN0TMPTR47LH RSCAN0.TMPTR47.UINT8[LH]
#define RSCAN0TMPTR47H RSCAN0.TMPTR47.UINT16[H]
#define RSCAN0TMPTR47HL RSCAN0.TMPTR47.UINT8[HL]
#define RSCAN0TMPTR47HH RSCAN0.TMPTR47.UINT8[HH]
#define RSCAN0TMDF047 RSCAN0.TMDF047.UINT32
#define RSCAN0TMDF047L RSCAN0.TMDF047.UINT16[L]
#define RSCAN0TMDF047LL RSCAN0.TMDF047.UINT8[LL]
#define RSCAN0TMDF047LH RSCAN0.TMDF047.UINT8[LH]
#define RSCAN0TMDF047H RSCAN0.TMDF047.UINT16[H]
#define RSCAN0TMDF047HL RSCAN0.TMDF047.UINT8[HL]
#define RSCAN0TMDF047HH RSCAN0.TMDF047.UINT8[HH]
#define RSCAN0TMDF147 RSCAN0.TMDF147.UINT32
#define RSCAN0TMDF147L RSCAN0.TMDF147.UINT16[L]
#define RSCAN0TMDF147LL RSCAN0.TMDF147.UINT8[LL]
#define RSCAN0TMDF147LH RSCAN0.TMDF147.UINT8[LH]
#define RSCAN0TMDF147H RSCAN0.TMDF147.UINT16[H]
#define RSCAN0TMDF147HL RSCAN0.TMDF147.UINT8[HL]
#define RSCAN0TMDF147HH RSCAN0.TMDF147.UINT8[HH]
#define RSCAN0THLACC0 RSCAN0.THLACC0.UINT32
#define RSCAN0THLACC0L RSCAN0.THLACC0.UINT16[L]
#define RSCAN0THLACC0LL RSCAN0.THLACC0.UINT8[LL]
#define RSCAN0THLACC0LH RSCAN0.THLACC0.UINT8[LH]
#define RSCAN0THLACC0H RSCAN0.THLACC0.UINT16[H]
#define RSCAN0THLACC0HL RSCAN0.THLACC0.UINT8[HL]
#define RSCAN0THLACC0HH RSCAN0.THLACC0.UINT8[HH]
#define RSCAN0THLACC1 RSCAN0.THLACC1.UINT32
#define RSCAN0THLACC1L RSCAN0.THLACC1.UINT16[L]
#define RSCAN0THLACC1LL RSCAN0.THLACC1.UINT8[LL]
#define RSCAN0THLACC1LH RSCAN0.THLACC1.UINT8[LH]
#define RSCAN0THLACC1H RSCAN0.THLACC1.UINT16[H]
#define RSCAN0THLACC1HL RSCAN0.THLACC1.UINT8[HL]
#define RSCAN0THLACC1HH RSCAN0.THLACC1.UINT8[HH]
#define RSCAN0THLACC2 RSCAN0.THLACC2.UINT32
#define RSCAN0THLACC2L RSCAN0.THLACC2.UINT16[L]
#define RSCAN0THLACC2LL RSCAN0.THLACC2.UINT8[LL]
#define RSCAN0THLACC2LH RSCAN0.THLACC2.UINT8[LH]
#define RSCAN0THLACC2H RSCAN0.THLACC2.UINT16[H]
#define RSCAN0THLACC2HL RSCAN0.THLACC2.UINT8[HL]
#define RSCAN0THLACC2HH RSCAN0.THLACC2.UINT8[HH]
#define RSCAN0RPGACC0 RSCAN0.RPGACC0.UINT32
#define RSCAN0RPGACC0L RSCAN0.RPGACC0.UINT16[L]
#define RSCAN0RPGACC0LL RSCAN0.RPGACC0.UINT8[LL]
#define RSCAN0RPGACC0LH RSCAN0.RPGACC0.UINT8[LH]
#define RSCAN0RPGACC0H RSCAN0.RPGACC0.UINT16[H]
#define RSCAN0RPGACC0HL RSCAN0.RPGACC0.UINT8[HL]
#define RSCAN0RPGACC0HH RSCAN0.RPGACC0.UINT8[HH]
#define RSCAN0RPGACC1 RSCAN0.RPGACC1.UINT32
#define RSCAN0RPGACC1L RSCAN0.RPGACC1.UINT16[L]
#define RSCAN0RPGACC1LL RSCAN0.RPGACC1.UINT8[LL]
#define RSCAN0RPGACC1LH RSCAN0.RPGACC1.UINT8[LH]
#define RSCAN0RPGACC1H RSCAN0.RPGACC1.UINT16[H]
#define RSCAN0RPGACC1HL RSCAN0.RPGACC1.UINT8[HL]
#define RSCAN0RPGACC1HH RSCAN0.RPGACC1.UINT8[HH]
#define RSCAN0RPGACC2 RSCAN0.RPGACC2.UINT32
#define RSCAN0RPGACC2L RSCAN0.RPGACC2.UINT16[L]
#define RSCAN0RPGACC2LL RSCAN0.RPGACC2.UINT8[LL]
#define RSCAN0RPGACC2LH RSCAN0.RPGACC2.UINT8[LH]
#define RSCAN0RPGACC2H RSCAN0.RPGACC2.UINT16[H]
#define RSCAN0RPGACC2HL RSCAN0.RPGACC2.UINT8[HL]
#define RSCAN0RPGACC2HH RSCAN0.RPGACC2.UINT8[HH]
#define RSCAN0RPGACC3 RSCAN0.RPGACC3.UINT32
#define RSCAN0RPGACC3L RSCAN0.RPGACC3.UINT16[L]
#define RSCAN0RPGACC3LL RSCAN0.RPGACC3.UINT8[LL]
#define RSCAN0RPGACC3LH RSCAN0.RPGACC3.UINT8[LH]
#define RSCAN0RPGACC3H RSCAN0.RPGACC3.UINT16[H]
#define RSCAN0RPGACC3HL RSCAN0.RPGACC3.UINT8[HL]
#define RSCAN0RPGACC3HH RSCAN0.RPGACC3.UINT8[HH]
#define RSCAN0RPGACC4 RSCAN0.RPGACC4.UINT32
#define RSCAN0RPGACC4L RSCAN0.RPGACC4.UINT16[L]
#define RSCAN0RPGACC4LL RSCAN0.RPGACC4.UINT8[LL]
#define RSCAN0RPGACC4LH RSCAN0.RPGACC4.UINT8[LH]
#define RSCAN0RPGACC4H RSCAN0.RPGACC4.UINT16[H]
#define RSCAN0RPGACC4HL RSCAN0.RPGACC4.UINT8[HL]
#define RSCAN0RPGACC4HH RSCAN0.RPGACC4.UINT8[HH]
#define RSCAN0RPGACC5 RSCAN0.RPGACC5.UINT32
#define RSCAN0RPGACC5L RSCAN0.RPGACC5.UINT16[L]
#define RSCAN0RPGACC5LL RSCAN0.RPGACC5.UINT8[LL]
#define RSCAN0RPGACC5LH RSCAN0.RPGACC5.UINT8[LH]
#define RSCAN0RPGACC5H RSCAN0.RPGACC5.UINT16[H]
#define RSCAN0RPGACC5HL RSCAN0.RPGACC5.UINT8[HL]
#define RSCAN0RPGACC5HH RSCAN0.RPGACC5.UINT8[HH]
#define RSCAN0RPGACC6 RSCAN0.RPGACC6.UINT32
#define RSCAN0RPGACC6L RSCAN0.RPGACC6.UINT16[L]
#define RSCAN0RPGACC6LL RSCAN0.RPGACC6.UINT8[LL]
#define RSCAN0RPGACC6LH RSCAN0.RPGACC6.UINT8[LH]
#define RSCAN0RPGACC6H RSCAN0.RPGACC6.UINT16[H]
#define RSCAN0RPGACC6HL RSCAN0.RPGACC6.UINT8[HL]
#define RSCAN0RPGACC6HH RSCAN0.RPGACC6.UINT8[HH]
#define RSCAN0RPGACC7 RSCAN0.RPGACC7.UINT32
#define RSCAN0RPGACC7L RSCAN0.RPGACC7.UINT16[L]
#define RSCAN0RPGACC7LL RSCAN0.RPGACC7.UINT8[LL]
#define RSCAN0RPGACC7LH RSCAN0.RPGACC7.UINT8[LH]
#define RSCAN0RPGACC7H RSCAN0.RPGACC7.UINT16[H]
#define RSCAN0RPGACC7HL RSCAN0.RPGACC7.UINT8[HL]
#define RSCAN0RPGACC7HH RSCAN0.RPGACC7.UINT8[HH]
#define RSCAN0RPGACC8 RSCAN0.RPGACC8.UINT32
#define RSCAN0RPGACC8L RSCAN0.RPGACC8.UINT16[L]
#define RSCAN0RPGACC8LL RSCAN0.RPGACC8.UINT8[LL]
#define RSCAN0RPGACC8LH RSCAN0.RPGACC8.UINT8[LH]
#define RSCAN0RPGACC8H RSCAN0.RPGACC8.UINT16[H]
#define RSCAN0RPGACC8HL RSCAN0.RPGACC8.UINT8[HL]
#define RSCAN0RPGACC8HH RSCAN0.RPGACC8.UINT8[HH]
#define RSCAN0RPGACC9 RSCAN0.RPGACC9.UINT32
#define RSCAN0RPGACC9L RSCAN0.RPGACC9.UINT16[L]
#define RSCAN0RPGACC9LL RSCAN0.RPGACC9.UINT8[LL]
#define RSCAN0RPGACC9LH RSCAN0.RPGACC9.UINT8[LH]
#define RSCAN0RPGACC9H RSCAN0.RPGACC9.UINT16[H]
#define RSCAN0RPGACC9HL RSCAN0.RPGACC9.UINT8[HL]
#define RSCAN0RPGACC9HH RSCAN0.RPGACC9.UINT8[HH]
#define RSCAN0RPGACC10 RSCAN0.RPGACC10.UINT32
#define RSCAN0RPGACC10L RSCAN0.RPGACC10.UINT16[L]
#define RSCAN0RPGACC10LL RSCAN0.RPGACC10.UINT8[LL]
#define RSCAN0RPGACC10LH RSCAN0.RPGACC10.UINT8[LH]
#define RSCAN0RPGACC10H RSCAN0.RPGACC10.UINT16[H]
#define RSCAN0RPGACC10HL RSCAN0.RPGACC10.UINT8[HL]
#define RSCAN0RPGACC10HH RSCAN0.RPGACC10.UINT8[HH]
#define RSCAN0RPGACC11 RSCAN0.RPGACC11.UINT32
#define RSCAN0RPGACC11L RSCAN0.RPGACC11.UINT16[L]
#define RSCAN0RPGACC11LL RSCAN0.RPGACC11.UINT8[LL]
#define RSCAN0RPGACC11LH RSCAN0.RPGACC11.UINT8[LH]
#define RSCAN0RPGACC11H RSCAN0.RPGACC11.UINT16[H]
#define RSCAN0RPGACC11HL RSCAN0.RPGACC11.UINT8[HL]
#define RSCAN0RPGACC11HH RSCAN0.RPGACC11.UINT8[HH]
#define RSCAN0RPGACC12 RSCAN0.RPGACC12.UINT32
#define RSCAN0RPGACC12L RSCAN0.RPGACC12.UINT16[L]
#define RSCAN0RPGACC12LL RSCAN0.RPGACC12.UINT8[LL]
#define RSCAN0RPGACC12LH RSCAN0.RPGACC12.UINT8[LH]
#define RSCAN0RPGACC12H RSCAN0.RPGACC12.UINT16[H]
#define RSCAN0RPGACC12HL RSCAN0.RPGACC12.UINT8[HL]
#define RSCAN0RPGACC12HH RSCAN0.RPGACC12.UINT8[HH]
#define RSCAN0RPGACC13 RSCAN0.RPGACC13.UINT32
#define RSCAN0RPGACC13L RSCAN0.RPGACC13.UINT16[L]
#define RSCAN0RPGACC13LL RSCAN0.RPGACC13.UINT8[LL]
#define RSCAN0RPGACC13LH RSCAN0.RPGACC13.UINT8[LH]
#define RSCAN0RPGACC13H RSCAN0.RPGACC13.UINT16[H]
#define RSCAN0RPGACC13HL RSCAN0.RPGACC13.UINT8[HL]
#define RSCAN0RPGACC13HH RSCAN0.RPGACC13.UINT8[HH]
#define RSCAN0RPGACC14 RSCAN0.RPGACC14.UINT32
#define RSCAN0RPGACC14L RSCAN0.RPGACC14.UINT16[L]
#define RSCAN0RPGACC14LL RSCAN0.RPGACC14.UINT8[LL]
#define RSCAN0RPGACC14LH RSCAN0.RPGACC14.UINT8[LH]
#define RSCAN0RPGACC14H RSCAN0.RPGACC14.UINT16[H]
#define RSCAN0RPGACC14HL RSCAN0.RPGACC14.UINT8[HL]
#define RSCAN0RPGACC14HH RSCAN0.RPGACC14.UINT8[HH]
#define RSCAN0RPGACC15 RSCAN0.RPGACC15.UINT32
#define RSCAN0RPGACC15L RSCAN0.RPGACC15.UINT16[L]
#define RSCAN0RPGACC15LL RSCAN0.RPGACC15.UINT8[LL]
#define RSCAN0RPGACC15LH RSCAN0.RPGACC15.UINT8[LH]
#define RSCAN0RPGACC15H RSCAN0.RPGACC15.UINT16[H]
#define RSCAN0RPGACC15HL RSCAN0.RPGACC15.UINT8[HL]
#define RSCAN0RPGACC15HH RSCAN0.RPGACC15.UINT8[HH]
#define RSCAN0RPGACC16 RSCAN0.RPGACC16.UINT32
#define RSCAN0RPGACC16L RSCAN0.RPGACC16.UINT16[L]
#define RSCAN0RPGACC16LL RSCAN0.RPGACC16.UINT8[LL]
#define RSCAN0RPGACC16LH RSCAN0.RPGACC16.UINT8[LH]
#define RSCAN0RPGACC16H RSCAN0.RPGACC16.UINT16[H]
#define RSCAN0RPGACC16HL RSCAN0.RPGACC16.UINT8[HL]
#define RSCAN0RPGACC16HH RSCAN0.RPGACC16.UINT8[HH]
#define RSCAN0RPGACC17 RSCAN0.RPGACC17.UINT32
#define RSCAN0RPGACC17L RSCAN0.RPGACC17.UINT16[L]
#define RSCAN0RPGACC17LL RSCAN0.RPGACC17.UINT8[LL]
#define RSCAN0RPGACC17LH RSCAN0.RPGACC17.UINT8[LH]
#define RSCAN0RPGACC17H RSCAN0.RPGACC17.UINT16[H]
#define RSCAN0RPGACC17HL RSCAN0.RPGACC17.UINT8[HL]
#define RSCAN0RPGACC17HH RSCAN0.RPGACC17.UINT8[HH]
#define RSCAN0RPGACC18 RSCAN0.RPGACC18.UINT32
#define RSCAN0RPGACC18L RSCAN0.RPGACC18.UINT16[L]
#define RSCAN0RPGACC18LL RSCAN0.RPGACC18.UINT8[LL]
#define RSCAN0RPGACC18LH RSCAN0.RPGACC18.UINT8[LH]
#define RSCAN0RPGACC18H RSCAN0.RPGACC18.UINT16[H]
#define RSCAN0RPGACC18HL RSCAN0.RPGACC18.UINT8[HL]
#define RSCAN0RPGACC18HH RSCAN0.RPGACC18.UINT8[HH]
#define RSCAN0RPGACC19 RSCAN0.RPGACC19.UINT32
#define RSCAN0RPGACC19L RSCAN0.RPGACC19.UINT16[L]
#define RSCAN0RPGACC19LL RSCAN0.RPGACC19.UINT8[LL]
#define RSCAN0RPGACC19LH RSCAN0.RPGACC19.UINT8[LH]
#define RSCAN0RPGACC19H RSCAN0.RPGACC19.UINT16[H]
#define RSCAN0RPGACC19HL RSCAN0.RPGACC19.UINT8[HL]
#define RSCAN0RPGACC19HH RSCAN0.RPGACC19.UINT8[HH]
#define RSCAN0RPGACC20 RSCAN0.RPGACC20.UINT32
#define RSCAN0RPGACC20L RSCAN0.RPGACC20.UINT16[L]
#define RSCAN0RPGACC20LL RSCAN0.RPGACC20.UINT8[LL]
#define RSCAN0RPGACC20LH RSCAN0.RPGACC20.UINT8[LH]
#define RSCAN0RPGACC20H RSCAN0.RPGACC20.UINT16[H]
#define RSCAN0RPGACC20HL RSCAN0.RPGACC20.UINT8[HL]
#define RSCAN0RPGACC20HH RSCAN0.RPGACC20.UINT8[HH]
#define RSCAN0RPGACC21 RSCAN0.RPGACC21.UINT32
#define RSCAN0RPGACC21L RSCAN0.RPGACC21.UINT16[L]
#define RSCAN0RPGACC21LL RSCAN0.RPGACC21.UINT8[LL]
#define RSCAN0RPGACC21LH RSCAN0.RPGACC21.UINT8[LH]
#define RSCAN0RPGACC21H RSCAN0.RPGACC21.UINT16[H]
#define RSCAN0RPGACC21HL RSCAN0.RPGACC21.UINT8[HL]
#define RSCAN0RPGACC21HH RSCAN0.RPGACC21.UINT8[HH]
#define RSCAN0RPGACC22 RSCAN0.RPGACC22.UINT32
#define RSCAN0RPGACC22L RSCAN0.RPGACC22.UINT16[L]
#define RSCAN0RPGACC22LL RSCAN0.RPGACC22.UINT8[LL]
#define RSCAN0RPGACC22LH RSCAN0.RPGACC22.UINT8[LH]
#define RSCAN0RPGACC22H RSCAN0.RPGACC22.UINT16[H]
#define RSCAN0RPGACC22HL RSCAN0.RPGACC22.UINT8[HL]
#define RSCAN0RPGACC22HH RSCAN0.RPGACC22.UINT8[HH]
#define RSCAN0RPGACC23 RSCAN0.RPGACC23.UINT32
#define RSCAN0RPGACC23L RSCAN0.RPGACC23.UINT16[L]
#define RSCAN0RPGACC23LL RSCAN0.RPGACC23.UINT8[LL]
#define RSCAN0RPGACC23LH RSCAN0.RPGACC23.UINT8[LH]
#define RSCAN0RPGACC23H RSCAN0.RPGACC23.UINT16[H]
#define RSCAN0RPGACC23HL RSCAN0.RPGACC23.UINT8[HL]
#define RSCAN0RPGACC23HH RSCAN0.RPGACC23.UINT8[HH]
#define RSCAN0RPGACC24 RSCAN0.RPGACC24.UINT32
#define RSCAN0RPGACC24L RSCAN0.RPGACC24.UINT16[L]
#define RSCAN0RPGACC24LL RSCAN0.RPGACC24.UINT8[LL]
#define RSCAN0RPGACC24LH RSCAN0.RPGACC24.UINT8[LH]
#define RSCAN0RPGACC24H RSCAN0.RPGACC24.UINT16[H]
#define RSCAN0RPGACC24HL RSCAN0.RPGACC24.UINT8[HL]
#define RSCAN0RPGACC24HH RSCAN0.RPGACC24.UINT8[HH]
#define RSCAN0RPGACC25 RSCAN0.RPGACC25.UINT32
#define RSCAN0RPGACC25L RSCAN0.RPGACC25.UINT16[L]
#define RSCAN0RPGACC25LL RSCAN0.RPGACC25.UINT8[LL]
#define RSCAN0RPGACC25LH RSCAN0.RPGACC25.UINT8[LH]
#define RSCAN0RPGACC25H RSCAN0.RPGACC25.UINT16[H]
#define RSCAN0RPGACC25HL RSCAN0.RPGACC25.UINT8[HL]
#define RSCAN0RPGACC25HH RSCAN0.RPGACC25.UINT8[HH]
#define RSCAN0RPGACC26 RSCAN0.RPGACC26.UINT32
#define RSCAN0RPGACC26L RSCAN0.RPGACC26.UINT16[L]
#define RSCAN0RPGACC26LL RSCAN0.RPGACC26.UINT8[LL]
#define RSCAN0RPGACC26LH RSCAN0.RPGACC26.UINT8[LH]
#define RSCAN0RPGACC26H RSCAN0.RPGACC26.UINT16[H]
#define RSCAN0RPGACC26HL RSCAN0.RPGACC26.UINT8[HL]
#define RSCAN0RPGACC26HH RSCAN0.RPGACC26.UINT8[HH]
#define RSCAN0RPGACC27 RSCAN0.RPGACC27.UINT32
#define RSCAN0RPGACC27L RSCAN0.RPGACC27.UINT16[L]
#define RSCAN0RPGACC27LL RSCAN0.RPGACC27.UINT8[LL]
#define RSCAN0RPGACC27LH RSCAN0.RPGACC27.UINT8[LH]
#define RSCAN0RPGACC27H RSCAN0.RPGACC27.UINT16[H]
#define RSCAN0RPGACC27HL RSCAN0.RPGACC27.UINT8[HL]
#define RSCAN0RPGACC27HH RSCAN0.RPGACC27.UINT8[HH]
#define RSCAN0RPGACC28 RSCAN0.RPGACC28.UINT32
#define RSCAN0RPGACC28L RSCAN0.RPGACC28.UINT16[L]
#define RSCAN0RPGACC28LL RSCAN0.RPGACC28.UINT8[LL]
#define RSCAN0RPGACC28LH RSCAN0.RPGACC28.UINT8[LH]
#define RSCAN0RPGACC28H RSCAN0.RPGACC28.UINT16[H]
#define RSCAN0RPGACC28HL RSCAN0.RPGACC28.UINT8[HL]
#define RSCAN0RPGACC28HH RSCAN0.RPGACC28.UINT8[HH]
#define RSCAN0RPGACC29 RSCAN0.RPGACC29.UINT32
#define RSCAN0RPGACC29L RSCAN0.RPGACC29.UINT16[L]
#define RSCAN0RPGACC29LL RSCAN0.RPGACC29.UINT8[LL]
#define RSCAN0RPGACC29LH RSCAN0.RPGACC29.UINT8[LH]
#define RSCAN0RPGACC29H RSCAN0.RPGACC29.UINT16[H]
#define RSCAN0RPGACC29HL RSCAN0.RPGACC29.UINT8[HL]
#define RSCAN0RPGACC29HH RSCAN0.RPGACC29.UINT8[HH]
#define RSCAN0RPGACC30 RSCAN0.RPGACC30.UINT32
#define RSCAN0RPGACC30L RSCAN0.RPGACC30.UINT16[L]
#define RSCAN0RPGACC30LL RSCAN0.RPGACC30.UINT8[LL]
#define RSCAN0RPGACC30LH RSCAN0.RPGACC30.UINT8[LH]
#define RSCAN0RPGACC30H RSCAN0.RPGACC30.UINT16[H]
#define RSCAN0RPGACC30HL RSCAN0.RPGACC30.UINT8[HL]
#define RSCAN0RPGACC30HH RSCAN0.RPGACC30.UINT8[HH]
#define RSCAN0RPGACC31 RSCAN0.RPGACC31.UINT32
#define RSCAN0RPGACC31L RSCAN0.RPGACC31.UINT16[L]
#define RSCAN0RPGACC31LL RSCAN0.RPGACC31.UINT8[LL]
#define RSCAN0RPGACC31LH RSCAN0.RPGACC31.UINT8[LH]
#define RSCAN0RPGACC31H RSCAN0.RPGACC31.UINT16[H]
#define RSCAN0RPGACC31HL RSCAN0.RPGACC31.UINT8[HL]
#define RSCAN0RPGACC31HH RSCAN0.RPGACC31.UINT8[HH]
#define RSCAN0RPGACC32 RSCAN0.RPGACC32.UINT32
#define RSCAN0RPGACC32L RSCAN0.RPGACC32.UINT16[L]
#define RSCAN0RPGACC32LL RSCAN0.RPGACC32.UINT8[LL]
#define RSCAN0RPGACC32LH RSCAN0.RPGACC32.UINT8[LH]
#define RSCAN0RPGACC32H RSCAN0.RPGACC32.UINT16[H]
#define RSCAN0RPGACC32HL RSCAN0.RPGACC32.UINT8[HL]
#define RSCAN0RPGACC32HH RSCAN0.RPGACC32.UINT8[HH]
#define RSCAN0RPGACC33 RSCAN0.RPGACC33.UINT32
#define RSCAN0RPGACC33L RSCAN0.RPGACC33.UINT16[L]
#define RSCAN0RPGACC33LL RSCAN0.RPGACC33.UINT8[LL]
#define RSCAN0RPGACC33LH RSCAN0.RPGACC33.UINT8[LH]
#define RSCAN0RPGACC33H RSCAN0.RPGACC33.UINT16[H]
#define RSCAN0RPGACC33HL RSCAN0.RPGACC33.UINT8[HL]
#define RSCAN0RPGACC33HH RSCAN0.RPGACC33.UINT8[HH]
#define RSCAN0RPGACC34 RSCAN0.RPGACC34.UINT32
#define RSCAN0RPGACC34L RSCAN0.RPGACC34.UINT16[L]
#define RSCAN0RPGACC34LL RSCAN0.RPGACC34.UINT8[LL]
#define RSCAN0RPGACC34LH RSCAN0.RPGACC34.UINT8[LH]
#define RSCAN0RPGACC34H RSCAN0.RPGACC34.UINT16[H]
#define RSCAN0RPGACC34HL RSCAN0.RPGACC34.UINT8[HL]
#define RSCAN0RPGACC34HH RSCAN0.RPGACC34.UINT8[HH]
#define RSCAN0RPGACC35 RSCAN0.RPGACC35.UINT32
#define RSCAN0RPGACC35L RSCAN0.RPGACC35.UINT16[L]
#define RSCAN0RPGACC35LL RSCAN0.RPGACC35.UINT8[LL]
#define RSCAN0RPGACC35LH RSCAN0.RPGACC35.UINT8[LH]
#define RSCAN0RPGACC35H RSCAN0.RPGACC35.UINT16[H]
#define RSCAN0RPGACC35HL RSCAN0.RPGACC35.UINT8[HL]
#define RSCAN0RPGACC35HH RSCAN0.RPGACC35.UINT8[HH]
#define RSCAN0RPGACC36 RSCAN0.RPGACC36.UINT32
#define RSCAN0RPGACC36L RSCAN0.RPGACC36.UINT16[L]
#define RSCAN0RPGACC36LL RSCAN0.RPGACC36.UINT8[LL]
#define RSCAN0RPGACC36LH RSCAN0.RPGACC36.UINT8[LH]
#define RSCAN0RPGACC36H RSCAN0.RPGACC36.UINT16[H]
#define RSCAN0RPGACC36HL RSCAN0.RPGACC36.UINT8[HL]
#define RSCAN0RPGACC36HH RSCAN0.RPGACC36.UINT8[HH]
#define RSCAN0RPGACC37 RSCAN0.RPGACC37.UINT32
#define RSCAN0RPGACC37L RSCAN0.RPGACC37.UINT16[L]
#define RSCAN0RPGACC37LL RSCAN0.RPGACC37.UINT8[LL]
#define RSCAN0RPGACC37LH RSCAN0.RPGACC37.UINT8[LH]
#define RSCAN0RPGACC37H RSCAN0.RPGACC37.UINT16[H]
#define RSCAN0RPGACC37HL RSCAN0.RPGACC37.UINT8[HL]
#define RSCAN0RPGACC37HH RSCAN0.RPGACC37.UINT8[HH]
#define RSCAN0RPGACC38 RSCAN0.RPGACC38.UINT32
#define RSCAN0RPGACC38L RSCAN0.RPGACC38.UINT16[L]
#define RSCAN0RPGACC38LL RSCAN0.RPGACC38.UINT8[LL]
#define RSCAN0RPGACC38LH RSCAN0.RPGACC38.UINT8[LH]
#define RSCAN0RPGACC38H RSCAN0.RPGACC38.UINT16[H]
#define RSCAN0RPGACC38HL RSCAN0.RPGACC38.UINT8[HL]
#define RSCAN0RPGACC38HH RSCAN0.RPGACC38.UINT8[HH]
#define RSCAN0RPGACC39 RSCAN0.RPGACC39.UINT32
#define RSCAN0RPGACC39L RSCAN0.RPGACC39.UINT16[L]
#define RSCAN0RPGACC39LL RSCAN0.RPGACC39.UINT8[LL]
#define RSCAN0RPGACC39LH RSCAN0.RPGACC39.UINT8[LH]
#define RSCAN0RPGACC39H RSCAN0.RPGACC39.UINT16[H]
#define RSCAN0RPGACC39HL RSCAN0.RPGACC39.UINT8[HL]
#define RSCAN0RPGACC39HH RSCAN0.RPGACC39.UINT8[HH]
#define RSCAN0RPGACC40 RSCAN0.RPGACC40.UINT32
#define RSCAN0RPGACC40L RSCAN0.RPGACC40.UINT16[L]
#define RSCAN0RPGACC40LL RSCAN0.RPGACC40.UINT8[LL]
#define RSCAN0RPGACC40LH RSCAN0.RPGACC40.UINT8[LH]
#define RSCAN0RPGACC40H RSCAN0.RPGACC40.UINT16[H]
#define RSCAN0RPGACC40HL RSCAN0.RPGACC40.UINT8[HL]
#define RSCAN0RPGACC40HH RSCAN0.RPGACC40.UINT8[HH]
#define RSCAN0RPGACC41 RSCAN0.RPGACC41.UINT32
#define RSCAN0RPGACC41L RSCAN0.RPGACC41.UINT16[L]
#define RSCAN0RPGACC41LL RSCAN0.RPGACC41.UINT8[LL]
#define RSCAN0RPGACC41LH RSCAN0.RPGACC41.UINT8[LH]
#define RSCAN0RPGACC41H RSCAN0.RPGACC41.UINT16[H]
#define RSCAN0RPGACC41HL RSCAN0.RPGACC41.UINT8[HL]
#define RSCAN0RPGACC41HH RSCAN0.RPGACC41.UINT8[HH]
#define RSCAN0RPGACC42 RSCAN0.RPGACC42.UINT32
#define RSCAN0RPGACC42L RSCAN0.RPGACC42.UINT16[L]
#define RSCAN0RPGACC42LL RSCAN0.RPGACC42.UINT8[LL]
#define RSCAN0RPGACC42LH RSCAN0.RPGACC42.UINT8[LH]
#define RSCAN0RPGACC42H RSCAN0.RPGACC42.UINT16[H]
#define RSCAN0RPGACC42HL RSCAN0.RPGACC42.UINT8[HL]
#define RSCAN0RPGACC42HH RSCAN0.RPGACC42.UINT8[HH]
#define RSCAN0RPGACC43 RSCAN0.RPGACC43.UINT32
#define RSCAN0RPGACC43L RSCAN0.RPGACC43.UINT16[L]
#define RSCAN0RPGACC43LL RSCAN0.RPGACC43.UINT8[LL]
#define RSCAN0RPGACC43LH RSCAN0.RPGACC43.UINT8[LH]
#define RSCAN0RPGACC43H RSCAN0.RPGACC43.UINT16[H]
#define RSCAN0RPGACC43HL RSCAN0.RPGACC43.UINT8[HL]
#define RSCAN0RPGACC43HH RSCAN0.RPGACC43.UINT8[HH]
#define RSCAN0RPGACC44 RSCAN0.RPGACC44.UINT32
#define RSCAN0RPGACC44L RSCAN0.RPGACC44.UINT16[L]
#define RSCAN0RPGACC44LL RSCAN0.RPGACC44.UINT8[LL]
#define RSCAN0RPGACC44LH RSCAN0.RPGACC44.UINT8[LH]
#define RSCAN0RPGACC44H RSCAN0.RPGACC44.UINT16[H]
#define RSCAN0RPGACC44HL RSCAN0.RPGACC44.UINT8[HL]
#define RSCAN0RPGACC44HH RSCAN0.RPGACC44.UINT8[HH]
#define RSCAN0RPGACC45 RSCAN0.RPGACC45.UINT32
#define RSCAN0RPGACC45L RSCAN0.RPGACC45.UINT16[L]
#define RSCAN0RPGACC45LL RSCAN0.RPGACC45.UINT8[LL]
#define RSCAN0RPGACC45LH RSCAN0.RPGACC45.UINT8[LH]
#define RSCAN0RPGACC45H RSCAN0.RPGACC45.UINT16[H]
#define RSCAN0RPGACC45HL RSCAN0.RPGACC45.UINT8[HL]
#define RSCAN0RPGACC45HH RSCAN0.RPGACC45.UINT8[HH]
#define RSCAN0RPGACC46 RSCAN0.RPGACC46.UINT32
#define RSCAN0RPGACC46L RSCAN0.RPGACC46.UINT16[L]
#define RSCAN0RPGACC46LL RSCAN0.RPGACC46.UINT8[LL]
#define RSCAN0RPGACC46LH RSCAN0.RPGACC46.UINT8[LH]
#define RSCAN0RPGACC46H RSCAN0.RPGACC46.UINT16[H]
#define RSCAN0RPGACC46HL RSCAN0.RPGACC46.UINT8[HL]
#define RSCAN0RPGACC46HH RSCAN0.RPGACC46.UINT8[HH]
#define RSCAN0RPGACC47 RSCAN0.RPGACC47.UINT32
#define RSCAN0RPGACC47L RSCAN0.RPGACC47.UINT16[L]
#define RSCAN0RPGACC47LL RSCAN0.RPGACC47.UINT8[LL]
#define RSCAN0RPGACC47LH RSCAN0.RPGACC47.UINT8[LH]
#define RSCAN0RPGACC47H RSCAN0.RPGACC47.UINT16[H]
#define RSCAN0RPGACC47HL RSCAN0.RPGACC47.UINT8[HL]
#define RSCAN0RPGACC47HH RSCAN0.RPGACC47.UINT8[HH]
#define RSCAN0RPGACC48 RSCAN0.RPGACC48.UINT32
#define RSCAN0RPGACC48L RSCAN0.RPGACC48.UINT16[L]
#define RSCAN0RPGACC48LL RSCAN0.RPGACC48.UINT8[LL]
#define RSCAN0RPGACC48LH RSCAN0.RPGACC48.UINT8[LH]
#define RSCAN0RPGACC48H RSCAN0.RPGACC48.UINT16[H]
#define RSCAN0RPGACC48HL RSCAN0.RPGACC48.UINT8[HL]
#define RSCAN0RPGACC48HH RSCAN0.RPGACC48.UINT8[HH]
#define RSCAN0RPGACC49 RSCAN0.RPGACC49.UINT32
#define RSCAN0RPGACC49L RSCAN0.RPGACC49.UINT16[L]
#define RSCAN0RPGACC49LL RSCAN0.RPGACC49.UINT8[LL]
#define RSCAN0RPGACC49LH RSCAN0.RPGACC49.UINT8[LH]
#define RSCAN0RPGACC49H RSCAN0.RPGACC49.UINT16[H]
#define RSCAN0RPGACC49HL RSCAN0.RPGACC49.UINT8[HL]
#define RSCAN0RPGACC49HH RSCAN0.RPGACC49.UINT8[HH]
#define RSCAN0RPGACC50 RSCAN0.RPGACC50.UINT32
#define RSCAN0RPGACC50L RSCAN0.RPGACC50.UINT16[L]
#define RSCAN0RPGACC50LL RSCAN0.RPGACC50.UINT8[LL]
#define RSCAN0RPGACC50LH RSCAN0.RPGACC50.UINT8[LH]
#define RSCAN0RPGACC50H RSCAN0.RPGACC50.UINT16[H]
#define RSCAN0RPGACC50HL RSCAN0.RPGACC50.UINT8[HL]
#define RSCAN0RPGACC50HH RSCAN0.RPGACC50.UINT8[HH]
#define RSCAN0RPGACC51 RSCAN0.RPGACC51.UINT32
#define RSCAN0RPGACC51L RSCAN0.RPGACC51.UINT16[L]
#define RSCAN0RPGACC51LL RSCAN0.RPGACC51.UINT8[LL]
#define RSCAN0RPGACC51LH RSCAN0.RPGACC51.UINT8[LH]
#define RSCAN0RPGACC51H RSCAN0.RPGACC51.UINT16[H]
#define RSCAN0RPGACC51HL RSCAN0.RPGACC51.UINT8[HL]
#define RSCAN0RPGACC51HH RSCAN0.RPGACC51.UINT8[HH]
#define RSCAN0RPGACC52 RSCAN0.RPGACC52.UINT32
#define RSCAN0RPGACC52L RSCAN0.RPGACC52.UINT16[L]
#define RSCAN0RPGACC52LL RSCAN0.RPGACC52.UINT8[LL]
#define RSCAN0RPGACC52LH RSCAN0.RPGACC52.UINT8[LH]
#define RSCAN0RPGACC52H RSCAN0.RPGACC52.UINT16[H]
#define RSCAN0RPGACC52HL RSCAN0.RPGACC52.UINT8[HL]
#define RSCAN0RPGACC52HH RSCAN0.RPGACC52.UINT8[HH]
#define RSCAN0RPGACC53 RSCAN0.RPGACC53.UINT32
#define RSCAN0RPGACC53L RSCAN0.RPGACC53.UINT16[L]
#define RSCAN0RPGACC53LL RSCAN0.RPGACC53.UINT8[LL]
#define RSCAN0RPGACC53LH RSCAN0.RPGACC53.UINT8[LH]
#define RSCAN0RPGACC53H RSCAN0.RPGACC53.UINT16[H]
#define RSCAN0RPGACC53HL RSCAN0.RPGACC53.UINT8[HL]
#define RSCAN0RPGACC53HH RSCAN0.RPGACC53.UINT8[HH]
#define RSCAN0RPGACC54 RSCAN0.RPGACC54.UINT32
#define RSCAN0RPGACC54L RSCAN0.RPGACC54.UINT16[L]
#define RSCAN0RPGACC54LL RSCAN0.RPGACC54.UINT8[LL]
#define RSCAN0RPGACC54LH RSCAN0.RPGACC54.UINT8[LH]
#define RSCAN0RPGACC54H RSCAN0.RPGACC54.UINT16[H]
#define RSCAN0RPGACC54HL RSCAN0.RPGACC54.UINT8[HL]
#define RSCAN0RPGACC54HH RSCAN0.RPGACC54.UINT8[HH]
#define RSCAN0RPGACC55 RSCAN0.RPGACC55.UINT32
#define RSCAN0RPGACC55L RSCAN0.RPGACC55.UINT16[L]
#define RSCAN0RPGACC55LL RSCAN0.RPGACC55.UINT8[LL]
#define RSCAN0RPGACC55LH RSCAN0.RPGACC55.UINT8[LH]
#define RSCAN0RPGACC55H RSCAN0.RPGACC55.UINT16[H]
#define RSCAN0RPGACC55HL RSCAN0.RPGACC55.UINT8[HL]
#define RSCAN0RPGACC55HH RSCAN0.RPGACC55.UINT8[HH]
#define RSCAN0RPGACC56 RSCAN0.RPGACC56.UINT32
#define RSCAN0RPGACC56L RSCAN0.RPGACC56.UINT16[L]
#define RSCAN0RPGACC56LL RSCAN0.RPGACC56.UINT8[LL]
#define RSCAN0RPGACC56LH RSCAN0.RPGACC56.UINT8[LH]
#define RSCAN0RPGACC56H RSCAN0.RPGACC56.UINT16[H]
#define RSCAN0RPGACC56HL RSCAN0.RPGACC56.UINT8[HL]
#define RSCAN0RPGACC56HH RSCAN0.RPGACC56.UINT8[HH]
#define RSCAN0RPGACC57 RSCAN0.RPGACC57.UINT32
#define RSCAN0RPGACC57L RSCAN0.RPGACC57.UINT16[L]
#define RSCAN0RPGACC57LL RSCAN0.RPGACC57.UINT8[LL]
#define RSCAN0RPGACC57LH RSCAN0.RPGACC57.UINT8[LH]
#define RSCAN0RPGACC57H RSCAN0.RPGACC57.UINT16[H]
#define RSCAN0RPGACC57HL RSCAN0.RPGACC57.UINT8[HL]
#define RSCAN0RPGACC57HH RSCAN0.RPGACC57.UINT8[HH]
#define RSCAN0RPGACC58 RSCAN0.RPGACC58.UINT32
#define RSCAN0RPGACC58L RSCAN0.RPGACC58.UINT16[L]
#define RSCAN0RPGACC58LL RSCAN0.RPGACC58.UINT8[LL]
#define RSCAN0RPGACC58LH RSCAN0.RPGACC58.UINT8[LH]
#define RSCAN0RPGACC58H RSCAN0.RPGACC58.UINT16[H]
#define RSCAN0RPGACC58HL RSCAN0.RPGACC58.UINT8[HL]
#define RSCAN0RPGACC58HH RSCAN0.RPGACC58.UINT8[HH]
#define RSCAN0RPGACC59 RSCAN0.RPGACC59.UINT32
#define RSCAN0RPGACC59L RSCAN0.RPGACC59.UINT16[L]
#define RSCAN0RPGACC59LL RSCAN0.RPGACC59.UINT8[LL]
#define RSCAN0RPGACC59LH RSCAN0.RPGACC59.UINT8[LH]
#define RSCAN0RPGACC59H RSCAN0.RPGACC59.UINT16[H]
#define RSCAN0RPGACC59HL RSCAN0.RPGACC59.UINT8[HL]
#define RSCAN0RPGACC59HH RSCAN0.RPGACC59.UINT8[HH]
#define RSCAN0RPGACC60 RSCAN0.RPGACC60.UINT32
#define RSCAN0RPGACC60L RSCAN0.RPGACC60.UINT16[L]
#define RSCAN0RPGACC60LL RSCAN0.RPGACC60.UINT8[LL]
#define RSCAN0RPGACC60LH RSCAN0.RPGACC60.UINT8[LH]
#define RSCAN0RPGACC60H RSCAN0.RPGACC60.UINT16[H]
#define RSCAN0RPGACC60HL RSCAN0.RPGACC60.UINT8[HL]
#define RSCAN0RPGACC60HH RSCAN0.RPGACC60.UINT8[HH]
#define RSCAN0RPGACC61 RSCAN0.RPGACC61.UINT32
#define RSCAN0RPGACC61L RSCAN0.RPGACC61.UINT16[L]
#define RSCAN0RPGACC61LL RSCAN0.RPGACC61.UINT8[LL]
#define RSCAN0RPGACC61LH RSCAN0.RPGACC61.UINT8[LH]
#define RSCAN0RPGACC61H RSCAN0.RPGACC61.UINT16[H]
#define RSCAN0RPGACC61HL RSCAN0.RPGACC61.UINT8[HL]
#define RSCAN0RPGACC61HH RSCAN0.RPGACC61.UINT8[HH]
#define RSCAN0RPGACC62 RSCAN0.RPGACC62.UINT32
#define RSCAN0RPGACC62L RSCAN0.RPGACC62.UINT16[L]
#define RSCAN0RPGACC62LL RSCAN0.RPGACC62.UINT8[LL]
#define RSCAN0RPGACC62LH RSCAN0.RPGACC62.UINT8[LH]
#define RSCAN0RPGACC62H RSCAN0.RPGACC62.UINT16[H]
#define RSCAN0RPGACC62HL RSCAN0.RPGACC62.UINT8[HL]
#define RSCAN0RPGACC62HH RSCAN0.RPGACC62.UINT8[HH]
#define RSCAN0RPGACC63 RSCAN0.RPGACC63.UINT32
#define RSCAN0RPGACC63L RSCAN0.RPGACC63.UINT16[L]
#define RSCAN0RPGACC63LL RSCAN0.RPGACC63.UINT8[LL]
#define RSCAN0RPGACC63LH RSCAN0.RPGACC63.UINT8[LH]
#define RSCAN0RPGACC63H RSCAN0.RPGACC63.UINT16[H]
#define RSCAN0RPGACC63HL RSCAN0.RPGACC63.UINT8[HL]
#define RSCAN0RPGACC63HH RSCAN0.RPGACC63.UINT8[HH]
#define CSIH0CTL0 CSIH0.CTL0.UINT8
#define CSIH0MBS CSIH0.CTL0.BIT.MBS
#define CSIH0JOBE CSIH0.CTL0.BIT.JOBE
#define CSIH0RXE CSIH0.CTL0.BIT.RXE
#define CSIH0TXE CSIH0.CTL0.BIT.TXE
#define CSIH0PWR CSIH0.CTL0.BIT.PWR
#define CSIH0STR0 CSIH0.STR0
#define CSIH0STCR0 CSIH0.STCR0
#define CSIH0CTL1 CSIH0.CTL1
#define CSIH0CTL2 CSIH0.CTL2
#define CSIH0EMU CSIH0.EMU.UINT8
#define CSIH0SVSDIS CSIH0.EMU.BIT.SVSDIS
#define CSIH0MCTL1 CSIH0.MCTL1
#define CSIH0MCTL2 CSIH0.MCTL2
#define CSIH0TX0W CSIH0.TX0W
#define CSIH0TX0H CSIH0.TX0H
#define CSIH0RX0W CSIH0.RX0W
#define CSIH0RX0H CSIH0.RX0H
#define CSIH0MRWP0 CSIH0.MRWP0
#define CSIH0MCTL0 CSIH0.MCTL0
#define CSIH0CFG0 CSIH0.CFG0
#define CSIH0CFG1 CSIH0.CFG1
#define CSIH0CFG2 CSIH0.CFG2
#define CSIH0CFG3 CSIH0.CFG3
#define CSIH0BRS0 CSIH0.BRS0
#define CSIH0BRS1 CSIH0.BRS1
#define CSIH0BRS2 CSIH0.BRS2
#define CSIH0BRS3 CSIH0.BRS3
#define CSIG0CTL0 CSIG0.CTL0.UINT8
#define CSIG0RXE CSIG0.CTL0.BIT.RXE
#define CSIG0TXE CSIG0.CTL0.BIT.TXE
#define CSIG0PWR CSIG0.CTL0.BIT.PWR
#define CSIG0STR0 CSIG0.STR0
#define CSIG0STCR0 CSIG0.STCR0
#define CSIG0CTL1 CSIG0.CTL1
#define CSIG0CTL2 CSIG0.CTL2
#define CSIG0EMU CSIG0.EMU.UINT8
#define CSIG0SVSDIS CSIG0.EMU.BIT.SVSDIS
#define CSIG0BCTL0 CSIG0.BCTL0.UINT8
#define CSIG0SCE CSIG0.BCTL0.BIT.SCE
#define CSIG0TX0W CSIG0.TX0W
#define CSIG0TX0H CSIG0.TX0H
#define CSIG0RX0 CSIG0.RX0
#define CSIG0CFG0 CSIG0.CFG0
#define PIC0SST PIC0.SST
#define PIC0SSER0 PIC0.SSER0
#define PIC0SSER2 PIC0.SSER2
#define PIC0HIZCEN0 PIC0.HIZCEN0
#define PIC0ADTEN400 PIC0.ADTEN400
#define PIC0ADTEN401 PIC0.ADTEN401
#define PIC0ADTEN402 PIC0.ADTEN402
#define PIC0REG200 PIC0.REG200
#define PIC0REG201 PIC0.REG201
#define PIC0REG202 PIC0.REG202
#define PIC0REG203 PIC0.REG203
#define PIC0REG30 PIC0.REG30
#define PIC0REG31 PIC0.REG31
#define TAUD0CDR0 TAUD0.CDR0
#define TAUD0CDR1 TAUD0.CDR1
#define TAUD0CDR2 TAUD0.CDR2
#define TAUD0CDR3 TAUD0.CDR3
#define TAUD0CDR4 TAUD0.CDR4
#define TAUD0CDR5 TAUD0.CDR5
#define TAUD0CDR6 TAUD0.CDR6
#define TAUD0CDR7 TAUD0.CDR7
#define TAUD0CDR8 TAUD0.CDR8
#define TAUD0CDR9 TAUD0.CDR9
#define TAUD0CDR10 TAUD0.CDR10
#define TAUD0CDR11 TAUD0.CDR11
#define TAUD0CDR12 TAUD0.CDR12
#define TAUD0CDR13 TAUD0.CDR13
#define TAUD0CDR14 TAUD0.CDR14
#define TAUD0CDR15 TAUD0.CDR15
#define TAUD0TOL TAUD0.TOL
#define TAUD0RDT TAUD0.RDT
#define TAUD0RSF TAUD0.RSF
#define TAUD0TRO TAUD0.TRO
#define TAUD0TME TAUD0.TME
#define TAUD0TDL TAUD0.TDL
#define TAUD0TO TAUD0.TO
#define TAUD0TOE TAUD0.TOE
#define TAUD0CNT0 TAUD0.CNT0
#define TAUD0CNT1 TAUD0.CNT1
#define TAUD0CNT2 TAUD0.CNT2
#define TAUD0CNT3 TAUD0.CNT3
#define TAUD0CNT4 TAUD0.CNT4
#define TAUD0CNT5 TAUD0.CNT5
#define TAUD0CNT6 TAUD0.CNT6
#define TAUD0CNT7 TAUD0.CNT7
#define TAUD0CNT8 TAUD0.CNT8
#define TAUD0CNT9 TAUD0.CNT9
#define TAUD0CNT10 TAUD0.CNT10
#define TAUD0CNT11 TAUD0.CNT11
#define TAUD0CNT12 TAUD0.CNT12
#define TAUD0CNT13 TAUD0.CNT13
#define TAUD0CNT14 TAUD0.CNT14
#define TAUD0CNT15 TAUD0.CNT15
#define TAUD0CMUR0 TAUD0.CMUR0
#define TAUD0CMUR1 TAUD0.CMUR1
#define TAUD0CMUR2 TAUD0.CMUR2
#define TAUD0CMUR3 TAUD0.CMUR3
#define TAUD0CMUR4 TAUD0.CMUR4
#define TAUD0CMUR5 TAUD0.CMUR5
#define TAUD0CMUR6 TAUD0.CMUR6
#define TAUD0CMUR7 TAUD0.CMUR7
#define TAUD0CMUR8 TAUD0.CMUR8
#define TAUD0CMUR9 TAUD0.CMUR9
#define TAUD0CMUR10 TAUD0.CMUR10
#define TAUD0CMUR11 TAUD0.CMUR11
#define TAUD0CMUR12 TAUD0.CMUR12
#define TAUD0CMUR13 TAUD0.CMUR13
#define TAUD0CMUR14 TAUD0.CMUR14
#define TAUD0CMUR15 TAUD0.CMUR15
#define TAUD0CSR0 TAUD0.CSR0
#define TAUD0CSR1 TAUD0.CSR1
#define TAUD0CSR2 TAUD0.CSR2
#define TAUD0CSR3 TAUD0.CSR3
#define TAUD0CSR4 TAUD0.CSR4
#define TAUD0CSR5 TAUD0.CSR5
#define TAUD0CSR6 TAUD0.CSR6
#define TAUD0CSR7 TAUD0.CSR7
#define TAUD0CSR8 TAUD0.CSR8
#define TAUD0CSR9 TAUD0.CSR9
#define TAUD0CSR10 TAUD0.CSR10
#define TAUD0CSR11 TAUD0.CSR11
#define TAUD0CSR12 TAUD0.CSR12
#define TAUD0CSR13 TAUD0.CSR13
#define TAUD0CSR14 TAUD0.CSR14
#define TAUD0CSR15 TAUD0.CSR15
#define TAUD0CSC0 TAUD0.CSC0
#define TAUD0CSC1 TAUD0.CSC1
#define TAUD0CSC2 TAUD0.CSC2
#define TAUD0CSC3 TAUD0.CSC3
#define TAUD0CSC4 TAUD0.CSC4
#define TAUD0CSC5 TAUD0.CSC5
#define TAUD0CSC6 TAUD0.CSC6
#define TAUD0CSC7 TAUD0.CSC7
#define TAUD0CSC8 TAUD0.CSC8
#define TAUD0CSC9 TAUD0.CSC9
#define TAUD0CSC10 TAUD0.CSC10
#define TAUD0CSC11 TAUD0.CSC11
#define TAUD0CSC12 TAUD0.CSC12
#define TAUD0CSC13 TAUD0.CSC13
#define TAUD0CSC14 TAUD0.CSC14
#define TAUD0CSC15 TAUD0.CSC15
#define TAUD0TE TAUD0.TE
#define TAUD0TS TAUD0.TS
#define TAUD0TT TAUD0.TT
#define TAUD0CMOR0 TAUD0.CMOR0
#define TAUD0CMOR1 TAUD0.CMOR1
#define TAUD0CMOR2 TAUD0.CMOR2
#define TAUD0CMOR3 TAUD0.CMOR3
#define TAUD0CMOR4 TAUD0.CMOR4
#define TAUD0CMOR5 TAUD0.CMOR5
#define TAUD0CMOR6 TAUD0.CMOR6
#define TAUD0CMOR7 TAUD0.CMOR7
#define TAUD0CMOR8 TAUD0.CMOR8
#define TAUD0CMOR9 TAUD0.CMOR9
#define TAUD0CMOR10 TAUD0.CMOR10
#define TAUD0CMOR11 TAUD0.CMOR11
#define TAUD0CMOR12 TAUD0.CMOR12
#define TAUD0CMOR13 TAUD0.CMOR13
#define TAUD0CMOR14 TAUD0.CMOR14
#define TAUD0CMOR15 TAUD0.CMOR15
#define TAUD0TPS TAUD0.TPS
#define TAUD0BRS TAUD0.BRS
#define TAUD0TOM TAUD0.TOM
#define TAUD0TOC TAUD0.TOC
#define TAUD0TDE TAUD0.TDE
#define TAUD0TDM TAUD0.TDM
#define TAUD0TRE TAUD0.TRE
#define TAUD0TRC TAUD0.TRC
#define TAUD0RDE TAUD0.RDE
#define TAUD0RDM TAUD0.RDM
#define TAUD0RDS TAUD0.RDS
#define TAUD0RDC TAUD0.RDC
#define TAUD0EMU TAUD0.EMU
#define TAUJ0CDR0 TAUJ0.CDR0
#define TAUJ0CDR1 TAUJ0.CDR1
#define TAUJ0CDR2 TAUJ0.CDR2
#define TAUJ0CDR3 TAUJ0.CDR3
#define TAUJ0CNT0 TAUJ0.CNT0
#define TAUJ0CNT1 TAUJ0.CNT1
#define TAUJ0CNT2 TAUJ0.CNT2
#define TAUJ0CNT3 TAUJ0.CNT3
#define TAUJ0CMUR0 TAUJ0.CMUR0
#define TAUJ0CMUR1 TAUJ0.CMUR1
#define TAUJ0CMUR2 TAUJ0.CMUR2
#define TAUJ0CMUR3 TAUJ0.CMUR3
#define TAUJ0CSR0 TAUJ0.CSR0
#define TAUJ0CSR1 TAUJ0.CSR1
#define TAUJ0CSR2 TAUJ0.CSR2
#define TAUJ0CSR3 TAUJ0.CSR3
#define TAUJ0CSC0 TAUJ0.CSC0
#define TAUJ0CSC1 TAUJ0.CSC1
#define TAUJ0CSC2 TAUJ0.CSC2
#define TAUJ0CSC3 TAUJ0.CSC3
#define TAUJ0TE TAUJ0.TE
#define TAUJ0TS TAUJ0.TS
#define TAUJ0TT TAUJ0.TT
#define TAUJ0TO TAUJ0.TO
#define TAUJ0TOE TAUJ0.TOE
#define TAUJ0TOL TAUJ0.TOL
#define TAUJ0RDT TAUJ0.RDT
#define TAUJ0RSF TAUJ0.RSF
#define TAUJ0CMOR0 TAUJ0.CMOR0
#define TAUJ0CMOR1 TAUJ0.CMOR1
#define TAUJ0CMOR2 TAUJ0.CMOR2
#define TAUJ0CMOR3 TAUJ0.CMOR3
#define TAUJ0TPS TAUJ0.TPS
#define TAUJ0BRS TAUJ0.BRS
#define TAUJ0TOM TAUJ0.TOM
#define TAUJ0TOC TAUJ0.TOC
#define TAUJ0RDE TAUJ0.RDE
#define TAUJ0RDM TAUJ0.RDM
#define TAUJ0EMU TAUJ0.EMU
#define PWSA0CTL PWSA0.CTL
#define PWSA0STR PWSA0.STR
#define PWSA0STC PWSA0.STC
#define PWSA0EMU PWSA0.EMU
#define PWSA0QUE0 PWSA0.QUE0
#define PWSA0QUE1 PWSA0.QUE1
#define PWSA0QUE2 PWSA0.QUE2
#define PWSA0QUE3 PWSA0.QUE3
#define PWSA0QUE4 PWSA0.QUE4
#define PWSA0QUE5 PWSA0.QUE5
#define PWSA0QUE6 PWSA0.QUE6
#define PWSA0QUE7 PWSA0.QUE7
#define PWSA0PVCR00_01 PWSA0.PVCR00_01
#define PWSA0PVCR02_03 PWSA0.PVCR02_03
#define PWSA0PVCR04_05 PWSA0.PVCR04_05
#define PWSA0PVCR06_07 PWSA0.PVCR06_07
#define PWSA0PVCR08_09 PWSA0.PVCR08_09
#define PWSA0PVCR10_11 PWSA0.PVCR10_11
#define PWSA0PVCR12_13 PWSA0.PVCR12_13
#define PWSA0PVCR14_15 PWSA0.PVCR14_15
#define PWSA0PVCR16_17 PWSA0.PVCR16_17
#define PWSA0PVCR18_19 PWSA0.PVCR18_19
#define PWSA0PVCR20_21 PWSA0.PVCR20_21
#define PWSA0PVCR22_23 PWSA0.PVCR22_23
#define PWGA0CSDR PWGA0.CSDR
#define PWGA0CRDR PWGA0.CRDR
#define PWGA0CTDR PWGA0.CTDR
#define PWGA0RDT PWGA0.RDT
#define PWGA0RSF PWGA0.RSF
#define PWGA0CNT PWGA0.CNT
#define PWGA0CTL PWGA0.CTL
#define PWGA0CSBR PWGA0.CSBR
#define PWGA0CRBR PWGA0.CRBR
#define PWGA0CTBR PWGA0.CTBR
#define PWGA1CSDR PWGA1.CSDR
#define PWGA1CRDR PWGA1.CRDR
#define PWGA1CTDR PWGA1.CTDR
#define PWGA1RDT PWGA1.RDT
#define PWGA1RSF PWGA1.RSF
#define PWGA1CNT PWGA1.CNT
#define PWGA1CTL PWGA1.CTL
#define PWGA1CSBR PWGA1.CSBR
#define PWGA1CRBR PWGA1.CRBR
#define PWGA1CTBR PWGA1.CTBR
#define PWGA2CSDR PWGA2.CSDR
#define PWGA2CRDR PWGA2.CRDR
#define PWGA2CTDR PWGA2.CTDR
#define PWGA2RDT PWGA2.RDT
#define PWGA2RSF PWGA2.RSF
#define PWGA2CNT PWGA2.CNT
#define PWGA2CTL PWGA2.CTL
#define PWGA2CSBR PWGA2.CSBR
#define PWGA2CRBR PWGA2.CRBR
#define PWGA2CTBR PWGA2.CTBR
#define PWGA3CSDR PWGA3.CSDR
#define PWGA3CRDR PWGA3.CRDR
#define PWGA3CTDR PWGA3.CTDR
#define PWGA3RDT PWGA3.RDT
#define PWGA3RSF PWGA3.RSF
#define PWGA3CNT PWGA3.CNT
#define PWGA3CTL PWGA3.CTL
#define PWGA3CSBR PWGA3.CSBR
#define PWGA3CRBR PWGA3.CRBR
#define PWGA3CTBR PWGA3.CTBR
#define PWGA4CSDR PWGA4.CSDR
#define PWGA4CRDR PWGA4.CRDR
#define PWGA4CTDR PWGA4.CTDR
#define PWGA4RDT PWGA4.RDT
#define PWGA4RSF PWGA4.RSF
#define PWGA4CNT PWGA4.CNT
#define PWGA4CTL PWGA4.CTL
#define PWGA4CSBR PWGA4.CSBR
#define PWGA4CRBR PWGA4.CRBR
#define PWGA4CTBR PWGA4.CTBR
#define PWGA5CSDR PWGA5.CSDR
#define PWGA5CRDR PWGA5.CRDR
#define PWGA5CTDR PWGA5.CTDR
#define PWGA5RDT PWGA5.RDT
#define PWGA5RSF PWGA5.RSF
#define PWGA5CNT PWGA5.CNT
#define PWGA5CTL PWGA5.CTL
#define PWGA5CSBR PWGA5.CSBR
#define PWGA5CRBR PWGA5.CRBR
#define PWGA5CTBR PWGA5.CTBR
#define PWGA6CSDR PWGA6.CSDR
#define PWGA6CRDR PWGA6.CRDR
#define PWGA6CTDR PWGA6.CTDR
#define PWGA6RDT PWGA6.RDT
#define PWGA6RSF PWGA6.RSF
#define PWGA6CNT PWGA6.CNT
#define PWGA6CTL PWGA6.CTL
#define PWGA6CSBR PWGA6.CSBR
#define PWGA6CRBR PWGA6.CRBR
#define PWGA6CTBR PWGA6.CTBR
#define PWGA7CSDR PWGA7.CSDR
#define PWGA7CRDR PWGA7.CRDR
#define PWGA7CTDR PWGA7.CTDR
#define PWGA7RDT PWGA7.RDT
#define PWGA7RSF PWGA7.RSF
#define PWGA7CNT PWGA7.CNT
#define PWGA7CTL PWGA7.CTL
#define PWGA7CSBR PWGA7.CSBR
#define PWGA7CRBR PWGA7.CRBR
#define PWGA7CTBR PWGA7.CTBR
#define PWGA8CSDR PWGA8.CSDR
#define PWGA8CRDR PWGA8.CRDR
#define PWGA8CTDR PWGA8.CTDR
#define PWGA8RDT PWGA8.RDT
#define PWGA8RSF PWGA8.RSF
#define PWGA8CNT PWGA8.CNT
#define PWGA8CTL PWGA8.CTL
#define PWGA8CSBR PWGA8.CSBR
#define PWGA8CRBR PWGA8.CRBR
#define PWGA8CTBR PWGA8.CTBR
#define PWGA9CSDR PWGA9.CSDR
#define PWGA9CRDR PWGA9.CRDR
#define PWGA9CTDR PWGA9.CTDR
#define PWGA9RDT PWGA9.RDT
#define PWGA9RSF PWGA9.RSF
#define PWGA9CNT PWGA9.CNT
#define PWGA9CTL PWGA9.CTL
#define PWGA9CSBR PWGA9.CSBR
#define PWGA9CRBR PWGA9.CRBR
#define PWGA9CTBR PWGA9.CTBR
#define PWGA10CSDR PWGA10.CSDR
#define PWGA10CRDR PWGA10.CRDR
#define PWGA10CTDR PWGA10.CTDR
#define PWGA10RDT PWGA10.RDT
#define PWGA10RSF PWGA10.RSF
#define PWGA10CNT PWGA10.CNT
#define PWGA10CTL PWGA10.CTL
#define PWGA10CSBR PWGA10.CSBR
#define PWGA10CRBR PWGA10.CRBR
#define PWGA10CTBR PWGA10.CTBR
#define PWGA11CSDR PWGA11.CSDR
#define PWGA11CRDR PWGA11.CRDR
#define PWGA11CTDR PWGA11.CTDR
#define PWGA11RDT PWGA11.RDT
#define PWGA11RSF PWGA11.RSF
#define PWGA11CNT PWGA11.CNT
#define PWGA11CTL PWGA11.CTL
#define PWGA11CSBR PWGA11.CSBR
#define PWGA11CRBR PWGA11.CRBR
#define PWGA11CTBR PWGA11.CTBR
#define PWGA12CSDR PWGA12.CSDR
#define PWGA12CRDR PWGA12.CRDR
#define PWGA12CTDR PWGA12.CTDR
#define PWGA12RDT PWGA12.RDT
#define PWGA12RSF PWGA12.RSF
#define PWGA12CNT PWGA12.CNT
#define PWGA12CTL PWGA12.CTL
#define PWGA12CSBR PWGA12.CSBR
#define PWGA12CRBR PWGA12.CRBR
#define PWGA12CTBR PWGA12.CTBR
#define PWGA13CSDR PWGA13.CSDR
#define PWGA13CRDR PWGA13.CRDR
#define PWGA13CTDR PWGA13.CTDR
#define PWGA13RDT PWGA13.RDT
#define PWGA13RSF PWGA13.RSF
#define PWGA13CNT PWGA13.CNT
#define PWGA13CTL PWGA13.CTL
#define PWGA13CSBR PWGA13.CSBR
#define PWGA13CRBR PWGA13.CRBR
#define PWGA13CTBR PWGA13.CTBR
#define PWGA14CSDR PWGA14.CSDR
#define PWGA14CRDR PWGA14.CRDR
#define PWGA14CTDR PWGA14.CTDR
#define PWGA14RDT PWGA14.RDT
#define PWGA14RSF PWGA14.RSF
#define PWGA14CNT PWGA14.CNT
#define PWGA14CTL PWGA14.CTL
#define PWGA14CSBR PWGA14.CSBR
#define PWGA14CRBR PWGA14.CRBR
#define PWGA14CTBR PWGA14.CTBR
#define PWGA15CSDR PWGA15.CSDR
#define PWGA15CRDR PWGA15.CRDR
#define PWGA15CTDR PWGA15.CTDR
#define PWGA15RDT PWGA15.RDT
#define PWGA15RSF PWGA15.RSF
#define PWGA15CNT PWGA15.CNT
#define PWGA15CTL PWGA15.CTL
#define PWGA15CSBR PWGA15.CSBR
#define PWGA15CRBR PWGA15.CRBR
#define PWGA15CTBR PWGA15.CTBR
#define PWGA16CSDR PWGA16.CSDR
#define PWGA16CRDR PWGA16.CRDR
#define PWGA16CTDR PWGA16.CTDR
#define PWGA16RDT PWGA16.RDT
#define PWGA16RSF PWGA16.RSF
#define PWGA16CNT PWGA16.CNT
#define PWGA16CTL PWGA16.CTL
#define PWGA16CSBR PWGA16.CSBR
#define PWGA16CRBR PWGA16.CRBR
#define PWGA16CTBR PWGA16.CTBR
#define PWGA17CSDR PWGA17.CSDR
#define PWGA17CRDR PWGA17.CRDR
#define PWGA17CTDR PWGA17.CTDR
#define PWGA17RDT PWGA17.RDT
#define PWGA17RSF PWGA17.RSF
#define PWGA17CNT PWGA17.CNT
#define PWGA17CTL PWGA17.CTL
#define PWGA17CSBR PWGA17.CSBR
#define PWGA17CRBR PWGA17.CRBR
#define PWGA17CTBR PWGA17.CTBR
#define PWGA18CSDR PWGA18.CSDR
#define PWGA18CRDR PWGA18.CRDR
#define PWGA18CTDR PWGA18.CTDR
#define PWGA18RDT PWGA18.RDT
#define PWGA18RSF PWGA18.RSF
#define PWGA18CNT PWGA18.CNT
#define PWGA18CTL PWGA18.CTL
#define PWGA18CSBR PWGA18.CSBR
#define PWGA18CRBR PWGA18.CRBR
#define PWGA18CTBR PWGA18.CTBR
#define PWGA19CSDR PWGA19.CSDR
#define PWGA19CRDR PWGA19.CRDR
#define PWGA19CTDR PWGA19.CTDR
#define PWGA19RDT PWGA19.RDT
#define PWGA19RSF PWGA19.RSF
#define PWGA19CNT PWGA19.CNT
#define PWGA19CTL PWGA19.CTL
#define PWGA19CSBR PWGA19.CSBR
#define PWGA19CRBR PWGA19.CRBR
#define PWGA19CTBR PWGA19.CTBR
#define PWGA20CSDR PWGA20.CSDR
#define PWGA20CRDR PWGA20.CRDR
#define PWGA20CTDR PWGA20.CTDR
#define PWGA20RDT PWGA20.RDT
#define PWGA20RSF PWGA20.RSF
#define PWGA20CNT PWGA20.CNT
#define PWGA20CTL PWGA20.CTL
#define PWGA20CSBR PWGA20.CSBR
#define PWGA20CRBR PWGA20.CRBR
#define PWGA20CTBR PWGA20.CTBR
#define PWGA21CSDR PWGA21.CSDR
#define PWGA21CRDR PWGA21.CRDR
#define PWGA21CTDR PWGA21.CTDR
#define PWGA21RDT PWGA21.RDT
#define PWGA21RSF PWGA21.RSF
#define PWGA21CNT PWGA21.CNT
#define PWGA21CTL PWGA21.CTL
#define PWGA21CSBR PWGA21.CSBR
#define PWGA21CRBR PWGA21.CRBR
#define PWGA21CTBR PWGA21.CTBR
#define PWGA22CSDR PWGA22.CSDR
#define PWGA22CRDR PWGA22.CRDR
#define PWGA22CTDR PWGA22.CTDR
#define PWGA22RDT PWGA22.RDT
#define PWGA22RSF PWGA22.RSF
#define PWGA22CNT PWGA22.CNT
#define PWGA22CTL PWGA22.CTL
#define PWGA22CSBR PWGA22.CSBR
#define PWGA22CRBR PWGA22.CRBR
#define PWGA22CTBR PWGA22.CTBR
#define PWGA23CSDR PWGA23.CSDR
#define PWGA23CRDR PWGA23.CRDR
#define PWGA23CTDR PWGA23.CTDR
#define PWGA23RDT PWGA23.RDT
#define PWGA23RSF PWGA23.RSF
#define PWGA23CNT PWGA23.CNT
#define PWGA23CTL PWGA23.CTL
#define PWGA23CSBR PWGA23.CSBR
#define PWGA23CRBR PWGA23.CRBR
#define PWGA23CTBR PWGA23.CTBR
#define PWBA0BRS0 PWBA0.BRS0
#define PWBA0BRS1 PWBA0.BRS1
#define PWBA0BRS2 PWBA0.BRS2
#define PWBA0BRS3 PWBA0.BRS3
#define PWBA0TE PWBA0.TE
#define PWBA0TS PWBA0.TS
#define PWBA0TT PWBA0.TT
#define PWBA0EMU PWBA0.EMU
#define ENCA0CCR0 ENCA0.CCR0
#define ENCA0CCR1 ENCA0.CCR1
#define ENCA0CNT ENCA0.CNT
#define ENCA0FLG ENCA0.FLG
#define ENCA0FGC ENCA0.FGC
#define ENCA0TE ENCA0.TE
#define ENCA0TS ENCA0.TS
#define ENCA0TT ENCA0.TT
#define ENCA0IOC0 ENCA0.IOC0
#define ENCA0CTL ENCA0.CTL
#define ENCA0IOC1 ENCA0.IOC1
#define ENCA0EMU ENCA0.EMU
#define TAPA0FLG TAPA0.FLG
#define TAPA0ACWE TAPA0.ACWE
#define TAPA0ACTS TAPA0.ACTS
#define TAPA0ACTT TAPA0.ACTT
#define TAPA0OPHS TAPA0.OPHS
#define TAPA0OPHT TAPA0.OPHT
#define TAPA0CTL0 TAPA0.CTL0
#define TAPA0CTL1 TAPA0.CTL1
#define TAPA0EMU TAPA0.EMU
#define OSTM0CMP OSTM0.CMP
#define OSTM0CNT OSTM0.CNT
#define OSTM0TE OSTM0.TE
#define OSTM0TS OSTM0.TS
#define OSTM0TT OSTM0.TT
#define OSTM0CTL OSTM0.CTL
#define OSTM0EMU OSTM0.EMU
#define WDTA0WDTE WDTA0.WDTE
#define WDTA0EVAC WDTA0.EVAC
#define WDTA0REF WDTA0.REF
#define WDTA0MD WDTA0.MD
#define WDTA1WDTE WDTA1.WDTE
#define WDTA1EVAC WDTA1.EVAC
#define WDTA1REF WDTA1.REF
#define WDTA1MD WDTA1.MD
#define ADCA0VCR00 ADCA0.VCR00.UINT32
#define ADCA0VCR00L ADCA0.VCR00.UINT16[L]
#define ADCA0VCR00LL ADCA0.VCR00.UINT8[LL]
#define ADCA0VCR00LH ADCA0.VCR00.UINT8[LH]
#define ADCA0VCR01 ADCA0.VCR01.UINT32
#define ADCA0VCR01L ADCA0.VCR01.UINT16[L]
#define ADCA0VCR01LL ADCA0.VCR01.UINT8[LL]
#define ADCA0VCR01LH ADCA0.VCR01.UINT8[LH]
#define ADCA0VCR02 ADCA0.VCR02.UINT32
#define ADCA0VCR02L ADCA0.VCR02.UINT16[L]
#define ADCA0VCR02LL ADCA0.VCR02.UINT8[LL]
#define ADCA0VCR02LH ADCA0.VCR02.UINT8[LH]
#define ADCA0VCR03 ADCA0.VCR03.UINT32
#define ADCA0VCR03L ADCA0.VCR03.UINT16[L]
#define ADCA0VCR03LL ADCA0.VCR03.UINT8[LL]
#define ADCA0VCR03LH ADCA0.VCR03.UINT8[LH]
#define ADCA0VCR04 ADCA0.VCR04.UINT32
#define ADCA0VCR04L ADCA0.VCR04.UINT16[L]
#define ADCA0VCR04LL ADCA0.VCR04.UINT8[LL]
#define ADCA0VCR04LH ADCA0.VCR04.UINT8[LH]
#define ADCA0VCR05 ADCA0.VCR05.UINT32
#define ADCA0VCR05L ADCA0.VCR05.UINT16[L]
#define ADCA0VCR05LL ADCA0.VCR05.UINT8[LL]
#define ADCA0VCR05LH ADCA0.VCR05.UINT8[LH]
#define ADCA0VCR06 ADCA0.VCR06.UINT32
#define ADCA0VCR06L ADCA0.VCR06.UINT16[L]
#define ADCA0VCR06LL ADCA0.VCR06.UINT8[LL]
#define ADCA0VCR06LH ADCA0.VCR06.UINT8[LH]
#define ADCA0VCR07 ADCA0.VCR07.UINT32
#define ADCA0VCR07L ADCA0.VCR07.UINT16[L]
#define ADCA0VCR07LL ADCA0.VCR07.UINT8[LL]
#define ADCA0VCR07LH ADCA0.VCR07.UINT8[LH]
#define ADCA0VCR08 ADCA0.VCR08.UINT32
#define ADCA0VCR08L ADCA0.VCR08.UINT16[L]
#define ADCA0VCR08LL ADCA0.VCR08.UINT8[LL]
#define ADCA0VCR08LH ADCA0.VCR08.UINT8[LH]
#define ADCA0VCR09 ADCA0.VCR09.UINT32
#define ADCA0VCR09L ADCA0.VCR09.UINT16[L]
#define ADCA0VCR09LL ADCA0.VCR09.UINT8[LL]
#define ADCA0VCR09LH ADCA0.VCR09.UINT8[LH]
#define ADCA0VCR10 ADCA0.VCR10.UINT32
#define ADCA0VCR10L ADCA0.VCR10.UINT16[L]
#define ADCA0VCR10LL ADCA0.VCR10.UINT8[LL]
#define ADCA0VCR10LH ADCA0.VCR10.UINT8[LH]
#define ADCA0VCR11 ADCA0.VCR11.UINT32
#define ADCA0VCR11L ADCA0.VCR11.UINT16[L]
#define ADCA0VCR11LL ADCA0.VCR11.UINT8[LL]
#define ADCA0VCR11LH ADCA0.VCR11.UINT8[LH]
#define ADCA0VCR12 ADCA0.VCR12.UINT32
#define ADCA0VCR12L ADCA0.VCR12.UINT16[L]
#define ADCA0VCR12LL ADCA0.VCR12.UINT8[LL]
#define ADCA0VCR12LH ADCA0.VCR12.UINT8[LH]
#define ADCA0VCR13 ADCA0.VCR13.UINT32
#define ADCA0VCR13L ADCA0.VCR13.UINT16[L]
#define ADCA0VCR13LL ADCA0.VCR13.UINT8[LL]
#define ADCA0VCR13LH ADCA0.VCR13.UINT8[LH]
#define ADCA0VCR14 ADCA0.VCR14.UINT32
#define ADCA0VCR14L ADCA0.VCR14.UINT16[L]
#define ADCA0VCR14LL ADCA0.VCR14.UINT8[LL]
#define ADCA0VCR14LH ADCA0.VCR14.UINT8[LH]
#define ADCA0VCR15 ADCA0.VCR15.UINT32
#define ADCA0VCR15L ADCA0.VCR15.UINT16[L]
#define ADCA0VCR15LL ADCA0.VCR15.UINT8[LL]
#define ADCA0VCR15LH ADCA0.VCR15.UINT8[LH]
#define ADCA0VCR16 ADCA0.VCR16.UINT32
#define ADCA0VCR16L ADCA0.VCR16.UINT16[L]
#define ADCA0VCR16LL ADCA0.VCR16.UINT8[LL]
#define ADCA0VCR16LH ADCA0.VCR16.UINT8[LH]
#define ADCA0VCR17 ADCA0.VCR17.UINT32
#define ADCA0VCR17L ADCA0.VCR17.UINT16[L]
#define ADCA0VCR17LL ADCA0.VCR17.UINT8[LL]
#define ADCA0VCR17LH ADCA0.VCR17.UINT8[LH]
#define ADCA0VCR18 ADCA0.VCR18.UINT32
#define ADCA0VCR18L ADCA0.VCR18.UINT16[L]
#define ADCA0VCR18LL ADCA0.VCR18.UINT8[LL]
#define ADCA0VCR18LH ADCA0.VCR18.UINT8[LH]
#define ADCA0VCR19 ADCA0.VCR19.UINT32
#define ADCA0VCR19L ADCA0.VCR19.UINT16[L]
#define ADCA0VCR19LL ADCA0.VCR19.UINT8[LL]
#define ADCA0VCR19LH ADCA0.VCR19.UINT8[LH]
#define ADCA0VCR20 ADCA0.VCR20.UINT32
#define ADCA0VCR20L ADCA0.VCR20.UINT16[L]
#define ADCA0VCR20LL ADCA0.VCR20.UINT8[LL]
#define ADCA0VCR20LH ADCA0.VCR20.UINT8[LH]
#define ADCA0VCR21 ADCA0.VCR21.UINT32
#define ADCA0VCR21L ADCA0.VCR21.UINT16[L]
#define ADCA0VCR21LL ADCA0.VCR21.UINT8[LL]
#define ADCA0VCR21LH ADCA0.VCR21.UINT8[LH]
#define ADCA0VCR22 ADCA0.VCR22.UINT32
#define ADCA0VCR22L ADCA0.VCR22.UINT16[L]
#define ADCA0VCR22LL ADCA0.VCR22.UINT8[LL]
#define ADCA0VCR22LH ADCA0.VCR22.UINT8[LH]
#define ADCA0VCR23 ADCA0.VCR23.UINT32
#define ADCA0VCR23L ADCA0.VCR23.UINT16[L]
#define ADCA0VCR23LL ADCA0.VCR23.UINT8[LL]
#define ADCA0VCR23LH ADCA0.VCR23.UINT8[LH]
#define ADCA0VCR24 ADCA0.VCR24.UINT32
#define ADCA0VCR24L ADCA0.VCR24.UINT16[L]
#define ADCA0VCR24LL ADCA0.VCR24.UINT8[LL]
#define ADCA0VCR24LH ADCA0.VCR24.UINT8[LH]
#define ADCA0VCR25 ADCA0.VCR25.UINT32
#define ADCA0VCR25L ADCA0.VCR25.UINT16[L]
#define ADCA0VCR25LL ADCA0.VCR25.UINT8[LL]
#define ADCA0VCR25LH ADCA0.VCR25.UINT8[LH]
#define ADCA0VCR26 ADCA0.VCR26.UINT32
#define ADCA0VCR26L ADCA0.VCR26.UINT16[L]
#define ADCA0VCR26LL ADCA0.VCR26.UINT8[LL]
#define ADCA0VCR26LH ADCA0.VCR26.UINT8[LH]
#define ADCA0VCR27 ADCA0.VCR27.UINT32
#define ADCA0VCR27L ADCA0.VCR27.UINT16[L]
#define ADCA0VCR27LL ADCA0.VCR27.UINT8[LL]
#define ADCA0VCR27LH ADCA0.VCR27.UINT8[LH]
#define ADCA0VCR28 ADCA0.VCR28.UINT32
#define ADCA0VCR28L ADCA0.VCR28.UINT16[L]
#define ADCA0VCR28LL ADCA0.VCR28.UINT8[LL]
#define ADCA0VCR28LH ADCA0.VCR28.UINT8[LH]
#define ADCA0PWDVCR ADCA0.PWDVCR.UINT32
#define ADCA0PWDVCRL ADCA0.PWDVCR.UINT16[L]
#define ADCA0PWDVCRLL ADCA0.PWDVCR.UINT8[LL]
#define ADCA0PWDVCRLH ADCA0.PWDVCR.UINT8[LH]
#define ADCA0DR00 ADCA0.DR00.UINT32
#define ADCA0DR00L ADCA0.DR00.UINT16[L]
#define ADCA0DR00H ADCA0.DR00.UINT16[H]
#define ADCA0DR02 ADCA0.DR02.UINT32
#define ADCA0DR02L ADCA0.DR02.UINT16[L]
#define ADCA0DR02H ADCA0.DR02.UINT16[H]
#define ADCA0DR04 ADCA0.DR04.UINT32
#define ADCA0DR04L ADCA0.DR04.UINT16[L]
#define ADCA0DR04H ADCA0.DR04.UINT16[H]
#define ADCA0DR06 ADCA0.DR06.UINT32
#define ADCA0DR06L ADCA0.DR06.UINT16[L]
#define ADCA0DR06H ADCA0.DR06.UINT16[H]
#define ADCA0DR08 ADCA0.DR08.UINT32
#define ADCA0DR08L ADCA0.DR08.UINT16[L]
#define ADCA0DR08H ADCA0.DR08.UINT16[H]
#define ADCA0DR10 ADCA0.DR10.UINT32
#define ADCA0DR10L ADCA0.DR10.UINT16[L]
#define ADCA0DR10H ADCA0.DR10.UINT16[H]
#define ADCA0DR12 ADCA0.DR12.UINT32
#define ADCA0DR12L ADCA0.DR12.UINT16[L]
#define ADCA0DR12H ADCA0.DR12.UINT16[H]
#define ADCA0DR14 ADCA0.DR14.UINT32
#define ADCA0DR14L ADCA0.DR14.UINT16[L]
#define ADCA0DR14H ADCA0.DR14.UINT16[H]
#define ADCA0DR16 ADCA0.DR16.UINT32
#define ADCA0DR16L ADCA0.DR16.UINT16[L]
#define ADCA0DR16H ADCA0.DR16.UINT16[H]
#define ADCA0DR18 ADCA0.DR18.UINT32
#define ADCA0DR18L ADCA0.DR18.UINT16[L]
#define ADCA0DR18H ADCA0.DR18.UINT16[H]
#define ADCA0DR20 ADCA0.DR20.UINT32
#define ADCA0DR20L ADCA0.DR20.UINT16[L]
#define ADCA0DR20H ADCA0.DR20.UINT16[H]
#define ADCA0DR22 ADCA0.DR22.UINT32
#define ADCA0DR22L ADCA0.DR22.UINT16[L]
#define ADCA0DR22H ADCA0.DR22.UINT16[H]
#define ADCA0DR24 ADCA0.DR24.UINT32
#define ADCA0DR24L ADCA0.DR24.UINT16[L]
#define ADCA0DR24H ADCA0.DR24.UINT16[H]
#define ADCA0DR26 ADCA0.DR26.UINT32
#define ADCA0DR26L ADCA0.DR26.UINT16[L]
#define ADCA0DR26H ADCA0.DR26.UINT16[H]
#define ADCA0DR28 ADCA0.DR28.UINT32
#define ADCA0DR28L ADCA0.DR28.UINT16[L]
#define ADCA0DR28H ADCA0.DR28.UINT16[H]
#define ADCA0PWDTSNDR ADCA0.PWDTSNDR.UINT32
#define ADCA0PWDTSNDRH ADCA0.PWDTSNDR.UINT16[H]
#define ADCA0DIR00 ADCA0.DIR00
#define ADCA0DIR01 ADCA0.DIR01
#define ADCA0DIR02 ADCA0.DIR02
#define ADCA0DIR03 ADCA0.DIR03
#define ADCA0DIR04 ADCA0.DIR04
#define ADCA0DIR05 ADCA0.DIR05
#define ADCA0DIR06 ADCA0.DIR06
#define ADCA0DIR07 ADCA0.DIR07
#define ADCA0DIR08 ADCA0.DIR08
#define ADCA0DIR09 ADCA0.DIR09
#define ADCA0DIR10 ADCA0.DIR10
#define ADCA0DIR11 ADCA0.DIR11
#define ADCA0DIR12 ADCA0.DIR12
#define ADCA0DIR13 ADCA0.DIR13
#define ADCA0DIR14 ADCA0.DIR14
#define ADCA0DIR15 ADCA0.DIR15
#define ADCA0DIR16 ADCA0.DIR16
#define ADCA0DIR17 ADCA0.DIR17
#define ADCA0DIR18 ADCA0.DIR18
#define ADCA0DIR19 ADCA0.DIR19
#define ADCA0DIR20 ADCA0.DIR20
#define ADCA0DIR21 ADCA0.DIR21
#define ADCA0DIR22 ADCA0.DIR22
#define ADCA0DIR23 ADCA0.DIR23
#define ADCA0DIR24 ADCA0.DIR24
#define ADCA0DIR25 ADCA0.DIR25
#define ADCA0DIR26 ADCA0.DIR26
#define ADCA0DIR27 ADCA0.DIR27
#define ADCA0DIR28 ADCA0.DIR28
#define ADCA0PWDDIR ADCA0.PWDDIR
#define ADCA0ADHALTR ADCA0.ADHALTR.UINT32
#define ADCA0ADHALTRL ADCA0.ADHALTR.UINT16[L]
#define ADCA0ADHALTRLL ADCA0.ADHALTR.UINT8[LL]
#define ADCA0ADCR ADCA0.ADCR.UINT32
#define ADCA0ADCRL ADCA0.ADCR.UINT16[L]
#define ADCA0ADCRLL ADCA0.ADCR.UINT8[LL]
#define ADCA0SGSTR ADCA0.SGSTR.UINT32
#define ADCA0SGSTRL ADCA0.SGSTR.UINT16[L]
#define ADCA0MPXCURR ADCA0.MPXCURR.UINT32
#define ADCA0MPXCURRL ADCA0.MPXCURR.UINT16[L]
#define ADCA0MPXCURRLL ADCA0.MPXCURR.UINT8[LL]
#define ADCA0THSMPSTCR ADCA0.THSMPSTCR.UINT32
#define ADCA0THSMPSTCRL ADCA0.THSMPSTCR.UINT16[L]
#define ADCA0THSMPSTCRLL ADCA0.THSMPSTCR.UINT8[LL]
#define ADCA0THCR ADCA0.THCR.UINT32
#define ADCA0THCRL ADCA0.THCR.UINT16[L]
#define ADCA0THCRLL ADCA0.THCR.UINT8[LL]
#define ADCA0THAHLDSTCR ADCA0.THAHLDSTCR.UINT32
#define ADCA0THAHLDSTCRL ADCA0.THAHLDSTCR.UINT16[L]
#define ADCA0THAHLDSTCRLL ADCA0.THAHLDSTCR.UINT8[LL]
#define ADCA0THBHLDSTCR ADCA0.THBHLDSTCR.UINT32
#define ADCA0THBHLDSTCRL ADCA0.THBHLDSTCR.UINT16[L]
#define ADCA0THBHLDSTCRLL ADCA0.THBHLDSTCR.UINT8[LL]
#define ADCA0THACR ADCA0.THACR.UINT32
#define ADCA0THACRL ADCA0.THACR.UINT16[L]
#define ADCA0THACRLL ADCA0.THACR.UINT8[LL]
#define ADCA0THBCR ADCA0.THBCR.UINT32
#define ADCA0THBCRL ADCA0.THBCR.UINT16[L]
#define ADCA0THBCRLL ADCA0.THBCR.UINT8[LL]
#define ADCA0THER ADCA0.THER.UINT32
#define ADCA0THERL ADCA0.THER.UINT16[L]
#define ADCA0THERLL ADCA0.THER.UINT8[LL]
#define ADCA0THGSR ADCA0.THGSR.UINT32
#define ADCA0THGSRL ADCA0.THGSR.UINT16[L]
#define ADCA0THGSRLL ADCA0.THGSR.UINT8[LL]
#define ADCA0SFTCR ADCA0.SFTCR.UINT32
#define ADCA0SFTCRL ADCA0.SFTCR.UINT16[L]
#define ADCA0SFTCRLL ADCA0.SFTCR.UINT8[LL]
#define ADCA0ULLMTBR0 ADCA0.ULLMTBR0.UINT32
#define ADCA0ULLMTBR0L ADCA0.ULLMTBR0.UINT16[L]
#define ADCA0ULLMTBR0H ADCA0.ULLMTBR0.UINT16[H]
#define ADCA0ULLMTBR1 ADCA0.ULLMTBR1.UINT32
#define ADCA0ULLMTBR1L ADCA0.ULLMTBR1.UINT16[L]
#define ADCA0ULLMTBR1H ADCA0.ULLMTBR1.UINT16[H]
#define ADCA0ULLMTBR2 ADCA0.ULLMTBR2.UINT32
#define ADCA0ULLMTBR2L ADCA0.ULLMTBR2.UINT16[L]
#define ADCA0ULLMTBR2H ADCA0.ULLMTBR2.UINT16[H]
#define ADCA0ECR ADCA0.ECR.UINT32
#define ADCA0ECRL ADCA0.ECR.UINT16[L]
#define ADCA0ECRLL ADCA0.ECR.UINT8[LL]
#define ADCA0ULER ADCA0.ULER.UINT32
#define ADCA0ULERL ADCA0.ULER.UINT16[L]
#define ADCA0ULERLL ADCA0.ULER.UINT8[LL]
#define ADCA0ULERLH ADCA0.ULER.UINT8[LH]
#define ADCA0OWER ADCA0.OWER.UINT32
#define ADCA0OWERL ADCA0.OWER.UINT16[L]
#define ADCA0OWERLL ADCA0.OWER.UINT8[LL]
#define ADCA0DGCTL0 ADCA0.DGCTL0.UINT32
#define ADCA0DGCTL0L ADCA0.DGCTL0.UINT16[L]
#define ADCA0DGCTL0LL ADCA0.DGCTL0.UINT8[LL]
#define ADCA0DGCTL1 ADCA0.DGCTL1.UINT32
#define ADCA0DGCTL1L ADCA0.DGCTL1.UINT16[L]
#define ADCA0PDCTL1 ADCA0.PDCTL1.UINT32
#define ADCA0PDCTL1L ADCA0.PDCTL1.UINT16[L]
#define ADCA0PDCTL2 ADCA0.PDCTL2.UINT32
#define ADCA0PDCTL2L ADCA0.PDCTL2.UINT16[L]
#define ADCA0PDCTL2LL ADCA0.PDCTL2.UINT8[LL]
#define ADCA0PDCTL2LH ADCA0.PDCTL2.UINT8[LH]
#define ADCA0PDCTL2H ADCA0.PDCTL2.UINT16[H]
#define ADCA0PDCTL2HL ADCA0.PDCTL2.UINT8[HL]
#define ADCA0SMPCR ADCA0.SMPCR.UINT32
#define ADCA0SMPCRL ADCA0.SMPCR.UINT16[L]
#define ADCA0SMPCRLL ADCA0.SMPCR.UINT8[LL]
#define ADCA0EMU ADCA0.EMU
#define ADCA0SGSTCR1 ADCA0.SGSTCR1.UINT32
#define ADCA0SGSTCR1L ADCA0.SGSTCR1.UINT16[L]
#define ADCA0SGSTCR1LL ADCA0.SGSTCR1.UINT8[LL]
#define ADCA0SGCR1 ADCA0.SGCR1.UINT32
#define ADCA0SGCR1L ADCA0.SGCR1.UINT16[L]
#define ADCA0SGCR1LL ADCA0.SGCR1.UINT8[LL]
#define ADCA0SGVCSP1 ADCA0.SGVCSP1.UINT32
#define ADCA0SGVCSP1L ADCA0.SGVCSP1.UINT16[L]
#define ADCA0SGVCSP1LL ADCA0.SGVCSP1.UINT8[LL]
#define ADCA0SGVCEP1 ADCA0.SGVCEP1.UINT32
#define ADCA0SGVCEP1L ADCA0.SGVCEP1.UINT16[L]
#define ADCA0SGVCEP1LL ADCA0.SGVCEP1.UINT8[LL]
#define ADCA0SGMCYCR1 ADCA0.SGMCYCR1.UINT32
#define ADCA0SGMCYCR1L ADCA0.SGMCYCR1.UINT16[L]
#define ADCA0SGMCYCR1LL ADCA0.SGMCYCR1.UINT8[LL]
#define ADCA0SGSEFCR1 ADCA0.SGSEFCR1.UINT32
#define ADCA0SGSEFCR1L ADCA0.SGSEFCR1.UINT16[L]
#define ADCA0SGSEFCR1LL ADCA0.SGSEFCR1.UINT8[LL]
#define ADCA0SGTSEL1 ADCA0.SGTSEL1.UINT32
#define ADCA0SGTSEL1L ADCA0.SGTSEL1.UINT16[L]
#define ADCA0SGSTCR2 ADCA0.SGSTCR2.UINT32
#define ADCA0SGSTCR2L ADCA0.SGSTCR2.UINT16[L]
#define ADCA0SGSTCR2LL ADCA0.SGSTCR2.UINT8[LL]
#define ADCA0SGCR2 ADCA0.SGCR2.UINT32
#define ADCA0SGCR2L ADCA0.SGCR2.UINT16[L]
#define ADCA0SGCR2LL ADCA0.SGCR2.UINT8[LL]
#define ADCA0SGVCSP2 ADCA0.SGVCSP2.UINT32
#define ADCA0SGVCSP2L ADCA0.SGVCSP2.UINT16[L]
#define ADCA0SGVCSP2LL ADCA0.SGVCSP2.UINT8[LL]
#define ADCA0SGVCEP2 ADCA0.SGVCEP2.UINT32
#define ADCA0SGVCEP2L ADCA0.SGVCEP2.UINT16[L]
#define ADCA0SGVCEP2LL ADCA0.SGVCEP2.UINT8[LL]
#define ADCA0SGMCYCR2 ADCA0.SGMCYCR2.UINT32
#define ADCA0SGMCYCR2L ADCA0.SGMCYCR2.UINT16[L]
#define ADCA0SGMCYCR2LL ADCA0.SGMCYCR2.UINT8[LL]
#define ADCA0SGSEFCR2 ADCA0.SGSEFCR2.UINT32
#define ADCA0SGSEFCR2L ADCA0.SGSEFCR2.UINT16[L]
#define ADCA0SGSEFCR2LL ADCA0.SGSEFCR2.UINT8[LL]
#define ADCA0SGTSEL2 ADCA0.SGTSEL2.UINT32
#define ADCA0SGTSEL2L ADCA0.SGTSEL2.UINT16[L]
#define ADCA0SGSTCR3 ADCA0.SGSTCR3.UINT32
#define ADCA0SGSTCR3L ADCA0.SGSTCR3.UINT16[L]
#define ADCA0SGSTCR3LL ADCA0.SGSTCR3.UINT8[LL]
#define ADCA0SGCR3 ADCA0.SGCR3.UINT32
#define ADCA0SGCR3L ADCA0.SGCR3.UINT16[L]
#define ADCA0SGCR3LL ADCA0.SGCR3.UINT8[LL]
#define ADCA0SGVCSP3 ADCA0.SGVCSP3.UINT32
#define ADCA0SGVCSP3L ADCA0.SGVCSP3.UINT16[L]
#define ADCA0SGVCSP3LL ADCA0.SGVCSP3.UINT8[LL]
#define ADCA0SGVCEP3 ADCA0.SGVCEP3.UINT32
#define ADCA0SGVCEP3L ADCA0.SGVCEP3.UINT16[L]
#define ADCA0SGVCEP3LL ADCA0.SGVCEP3.UINT8[LL]
#define ADCA0SGMCYCR3 ADCA0.SGMCYCR3.UINT32
#define ADCA0SGMCYCR3L ADCA0.SGMCYCR3.UINT16[L]
#define ADCA0SGMCYCR3LL ADCA0.SGMCYCR3.UINT8[LL]
#define ADCA0SGSEFCR3 ADCA0.SGSEFCR3.UINT32
#define ADCA0SGSEFCR3L ADCA0.SGSEFCR3.UINT16[L]
#define ADCA0SGSEFCR3LL ADCA0.SGSEFCR3.UINT8[LL]
#define ADCA0SGTSEL3 ADCA0.SGTSEL3.UINT32
#define ADCA0SGTSEL3L ADCA0.SGTSEL3.UINT16[L]
#define ADCA0PWDSGCR ADCA0.PWDSGCR.UINT32
#define ADCA0PWDSGCRL ADCA0.PWDSGCR.UINT16[L]
#define ADCA0PWDSGCRLL ADCA0.PWDSGCR.UINT8[LL]
#define ADCA0PWDSGSEFCR ADCA0.PWDSGSEFCR.UINT32
#define ADCA0PWDSGSEFCRL ADCA0.PWDSGSEFCR.UINT16[L]
#define ADCA0PWDSGSEFCRLL ADCA0.PWDSGSEFCR.UINT8[LL]
#define DCRA0CIN DCRA0.CIN
#define DCRA0COUT DCRA0.COUT
#define DCRA0CTL DCRA0.CTL
#define KR0KRM KR0.KRM.UINT8
#define KR0KRM0 KR0.KRM.BIT.KRM0
#define KR0KRM1 KR0.KRM.BIT.KRM1
#define KR0KRM2 KR0.KRM.BIT.KRM2
#define KR0KRM3 KR0.KRM.BIT.KRM3
#define KR0KRM4 KR0.KRM.BIT.KRM4
#define KR0KRM5 KR0.KRM.BIT.KRM5
#define KR0KRM6 KR0.KRM.BIT.KRM6
#define KR0KRM7 KR0.KRM.BIT.KRM7
#define CLMA0CTL0 CLMA0.CTL0
#define CLMA0CMPL CLMA0.CMPL
#define CLMA0CMPH CLMA0.CMPH
#define CLMA0PCMD CLMA0.PCMD
#define CLMA0PS CLMA0.PS
#define CLMA0EMU0 CLMA0.EMU0
#define CLMATEST CLMA.TEST
#define CLMATESTS CLMA.TESTS
#define CLMA1CTL0 CLMA1.CTL0
#define CLMA1CMPL CLMA1.CMPL
#define CLMA1CMPH CLMA1.CMPH
#define CLMA1PCMD CLMA1.PCMD
#define CLMA1PS CLMA1.PS
#define CLMA1EMU0 CLMA1.EMU0
#define CLMA2CTL0 CLMA2.CTL0
#define CLMA2CMPL CLMA2.CMPL
#define CLMA2CMPH CLMA2.CMPH
#define CLMA2PCMD CLMA2.PCMD
#define CLMA2PS CLMA2.PS
#define CLMA2EMU0 CLMA2.EMU0
#endif
