

#ifndef  V_DEF_H
#define  V_DEF_H

#include "FblHal_Cfg.h"
#include "v_cfg_fbl.h"

#define COMMON_VDEF_VERSION            0x0375
#define COMMON_VDEF_RELEASE_VERSION    0x00

#define V_DEF_VERSION                  COMMON_VDEF_VERSION

#if defined( V_COMP_GHS_RH850 )
# define V_DEF_SUPPORTED_PLATFORM
#endif

#if !defined V_DEF_SUPPORTED_PLATFORM
# error "driver not supported or C_COMP_xxx_yyy not defined"
#endif

#if !defined( vuint8 )
typedef unsigned char  vuint8;
#endif
#define canuint8 vuint8

#if !defined( vsint8 )
typedef signed char    vsint8;
#endif
#define cansint8 vsint8

#if !defined( vuint16 )
typedef unsigned short vuint16;
#endif
#define canuint16 vuint16

#if !defined( vsint16 )
typedef signed short   vsint16;
#endif
#define cansint16 vsint16

#if !defined( vuint32 )
typedef unsigned long  vuint32;
#endif
#define canuint32 vuint32

#if !defined( vsint32 )
typedef signed long    vsint32;
#endif
#define cansint32 vsint32

typedef unsigned char *TxDataPtr;
typedef unsigned char *RxDataPtr;

#if defined( C_CPUTYPE_8BIT )

# ifndef vuintx
#  define vuintx vuint8
# endif
# ifndef vsintx
#  define vsintx vsint8
# endif
#else
# if defined( C_CPUTYPE_16BIT )

#  ifndef vuintx
#   define vuintx vuint16
#  endif
#  ifndef vsintx
#   define vsintx vsint16
#  endif
# else
#  if defined( C_CPUTYPE_32BIT )

#ifndef vuintx
#    define vuintx vuint32
#   endif
#ifndef vsintx
#    define vsintx vsint32
#   endif
#  else
#if defined( C_CPUTYPE_64BIT )

#    ifndef vuintx
#     define vuintx vuint32
#    endif
#    ifndef vsintx
#     define vsintx vsint32
#    endif
#   endif
#  endif
# endif
#endif

typedef unsigned int     vbittype;
#define canbittype       vbittype

#if defined( C_SUPPORT_MIXED_CAN_LIN )

#else

#  if defined( C_CPUTYPE_BITORDER_LSB2MSB )
struct _c_bits8
{
  vbittype  b0:1;
  vbittype  b1:1;
  vbittype  b2:1;
  vbittype  b3:1;
  vbittype  b4:1;
  vbittype  b5:1;
  vbittype  b6:1;
  vbittype  b7:1;
 };

struct _c_bits16
{
  vbittype  b0:1;
  vbittype  b1:1;
  vbittype  b2:1;
  vbittype  b3:1;
  vbittype  b4:1;
  vbittype  b5:1;
  vbittype  b6:1;
  vbittype  b7:1;

  vbittype  b10:1;
  vbittype  b11:1;
  vbittype  b12:1;
  vbittype  b13:1;
  vbittype  b14:1;
  vbittype  b15:1;
  vbittype  b16:1;
  vbittype  b17:1;
};

struct _c_bits32
{
  vbittype  b0:1;
  vbittype  b1:1;
  vbittype  b2:1;
  vbittype  b3:1;
  vbittype  b4:1;
  vbittype  b5:1;
  vbittype  b6:1;
  vbittype  b7:1;

  vbittype  b10:1;
  vbittype  b11:1;
  vbittype  b12:1;
  vbittype  b13:1;
  vbittype  b14:1;
  vbittype  b15:1;
  vbittype  b16:1;
  vbittype  b17:1;

  vbittype  b20:1;
  vbittype  b21:1;
  vbittype  b22:1;
  vbittype  b23:1;
  vbittype  b24:1;
  vbittype  b25:1;
  vbittype  b26:1;
  vbittype  b27:1;

  vbittype  b30:1;
  vbittype  b31:1;
  vbittype  b32:1;
  vbittype  b33:1;
  vbittype  b34:1;
  vbittype  b35:1;
  vbittype  b36:1;
  vbittype  b37:1;
};

# else
#  if defined( C_CPUTYPE_BITORDER_MSB2LSB )
struct _c_bits8
{
  vbittype  b7:1;
  vbittype  b6:1;
  vbittype  b5:1;
  vbittype  b4:1;
  vbittype  b3:1;
  vbittype  b2:1;
  vbittype  b1:1;
  vbittype  b0:1;
};

struct _c_bits16
{
  vbittype  b7:1;
  vbittype  b6:1;
  vbittype  b5:1;
  vbittype  b4:1;
  vbittype  b3:1;
  vbittype  b2:1;
  vbittype  b1:1;
  vbittype  b0:1;

  vbittype  b17:1;
  vbittype  b16:1;
  vbittype  b15:1;
  vbittype  b14:1;
  vbittype  b13:1;
  vbittype  b12:1;
  vbittype  b11:1;
  vbittype  b10:1;
};

struct _c_bits32
{
  vbittype  b7:1;
  vbittype  b6:1;
  vbittype  b5:1;
  vbittype  b4:1;
  vbittype  b3:1;
  vbittype  b2:1;
  vbittype  b1:1;
  vbittype  b0:1;

  vbittype  b17:1;
  vbittype  b16:1;
  vbittype  b15:1;
  vbittype  b14:1;
  vbittype  b13:1;
  vbittype  b12:1;
  vbittype  b11:1;
  vbittype  b10:1;

  vbittype  b27:1;
  vbittype  b26:1;
  vbittype  b25:1;
  vbittype  b24:1;
  vbittype  b23:1;
  vbittype  b22:1;
  vbittype  b21:1;
  vbittype  b20:1;

  vbittype  b37:1;
  vbittype  b36:1;
  vbittype  b35:1;
  vbittype  b34:1;
  vbittype  b33:1;
  vbittype  b32:1;
  vbittype  b31:1;
  vbittype  b30:1;
};
#  else
#  error "Bitorder unknown: C_CPUTYPE_BITORDER_MSB2LSB or C_CPUTYPE_BITORDER_LSB2MSB has to be defined"
#  endif
# endif
#endif

#if defined ( VGEN_ENABLE_CANFBL )
#endif

#ifndef MEMORY_HUGE
#  define MEMORY_HUGE
#endif

#if defined( V_COMP_GHS_RH850 )
# if !defined(V_ENABLE_CAN_ASR_ABSTRACTION) && !defined(V_ENABLE_VSTDLIB_ASR_ABSTRACTION)
#  if !defined(LOCAL_INLINE)
#   define LOCAL_INLINE       static inline
#  endif
# endif
#endif

#ifndef V_MEMROM0
# define V_MEMROM0
#endif

#ifndef V_MEMROM1_NEAR
# define V_MEMROM1_NEAR
#endif

#ifndef V_MEMROM1
# define V_MEMROM1
#endif

#ifndef V_MEMROM1_FAR
# define V_MEMROM1_FAR
#endif

#ifndef MEMORY_ROM_NEAR
# ifndef V_MEMROM2_NEAR
#  define V_MEMROM2_NEAR   const
# endif

# define MEMORY_ROM_NEAR   V_MEMROM2_NEAR
#else
# define V_MEMROM2_NEAR    MEMORY_ROM_NEAR
#endif

#ifndef MEMORY_ROM
# ifndef V_MEMROM2
#  define V_MEMROM2        const
# endif

# define MEMORY_ROM        V_MEMROM2
#else
# define V_MEMROM2         MEMORY_ROM
#endif

#ifndef MEMORY_ROM_FAR
# ifndef V_MEMROM2_FAR
#  define V_MEMROM2_FAR    const
# endif

# define MEMORY_ROM_FAR    V_MEMROM2_FAR
#else
# define V_MEMROM2_FAR     MEMORY_ROM_FAR
#endif

#ifndef V_MEMROM3
# define V_MEMROM3
#endif

#ifndef V_MEMRAM0
# define V_MEMRAM0
#endif

#ifndef V_MEMRAM1_NEAR
# define V_MEMRAM1_NEAR
#endif

#ifndef V_MEMRAM1
# define V_MEMRAM1
#endif

#ifndef V_MEMRAM1_FAR
# define V_MEMRAM1_FAR
#endif

#ifndef MEMORY_NEAR
# ifndef V_MEMRAM2_NEAR
#  define V_MEMRAM2_NEAR
# endif

# define MEMORY_NEAR   V_MEMRAM2_NEAR
#else
# define V_MEMRAM2_NEAR    MEMORY_NEAR
#endif

#ifndef MEMORY_NORMAL
# ifndef V_MEMRAM2
#  define V_MEMRAM2
# endif

# define MEMORY_NORMAL   V_MEMRAM2
#else
# define V_MEMRAM2           MEMORY_NORMAL
#endif

#ifndef MEMORY_FAR
# ifndef V_MEMRAM2_FAR
#  define V_MEMRAM2_FAR
# endif

# define MEMORY_FAR    V_MEMRAM2_FAR
#else
# define V_MEMRAM2_FAR     MEMORY_FAR
#endif

#ifndef V_MEMRAM3_NEAR
# define V_MEMRAM3_NEAR
#endif

#ifndef V_MEMRAM3
# define V_MEMRAM3
#endif

#ifndef V_MEMRAM3_FAR
# define V_MEMRAM3_FAR
#endif

#if !defined(VUINT8_CAST)
# define VUINT8_CAST
#endif
#if !defined(VSINT8_CAST)
# define VSINT8_CAST
#endif
#if !defined(VUINT16_CAST)
# define VUINT16_CAST
#endif
# if !defined(VSINT16_CAST)
# define VSINT16_CAST
#endif
#if !defined(CANBITTYPE_CAST)
# define CANBITTYPE_CAST
#endif
#if !defined(CANSINTCPUTYPE_CAST)
# define CANSINTCPUTYPE_CAST
#endif
#if !defined(CANUINTCPUTYPE_CAST)
# define CANUINTCPUTYPE_CAST
#endif

# if defined (VGEN_ENABLE_VSTDLIB) || defined (V_ENABLE_VSTDLIB)
#  include "vstdlib.h"
# endif

#if !defined(V_NULL)
# define V_NULL ((void*)0)
#endif

#ifndef NULL
# define NULL V_NULL
#endif

#if !defined(V_ENABLE_CAN_ASR_ABSTRACTION) && !defined(V_ENABLE_VSTDLIB_ASR_ABSTRACTION)
# define V_ENABLE_CBD_ABSTRACTION
# define STATIC                                          static
# define CAN_STATIC                                      static
# define AUTOMATIC
# if !defined(NULL_PTR)
#  define NULL_PTR                                       V_NULL
# endif
# if !defined(LOCAL_INLINE)
#  define LOCAL_INLINE
# endif
# define CAN_LOCAL_INLINE                                LOCAL_INLINE

#  define V_NONE
#  define V_STORAGE_NONE

# if !defined( C_CALLBACK_1 )
#  define C_CALLBACK_1
# endif
# if !defined( C_CALLBACK_2 )
#  define C_CALLBACK_2
# endif
# if !defined( C_API_1 )
#  define C_API_1
# endif
# if !defined( C_API_2 )
#  define C_API_2
# endif
# if !defined( C_API_3 )
#  define C_API_3
# endif
# define V_DEF_VAR(storage, vartype, memclass)                    V_MEMRAM0 storage V_MEMRAM1 vartype V_MEMRAM2
# define V_DEF_VAR_NEAR(storage, vartype)                         V_MEMRAM0 storage V_MEMRAM1_NEAR vartype V_MEMRAM2_NEAR
# define V_DEF_VAR_FAR(storage, vartype)                          V_MEMRAM0 storage V_MEMRAM1_FAR vartype V_MEMRAM2_FAR
# define V_DEF_VAR_TYPE(storage, vartype)                         typedef storage V_MEMRAM1 vartype V_MEMRAM2
# define V_DEF_P2VAR(storage, ptrtype, memclass, ptrclass)        V_MEMRAM0 storage V_MEMRAM1 ptrtype V_MEMRAM2 *
# define V_DEF_P2VAR_PARA(storage, ptrtype, memclass, ptrclass)   storage V_MEMRAM1 ptrtype V_MEMRAM2 *
# define V_DEF_P2VAR_TYPE(storage, ptrtype, ptrclass)             typedef storage V_MEMRAM1 ptrtype V_MEMRAM2 *

# define V_DEF_P2SFR_CAN(storage, ptrtype, memclass)              V_MEMRAM0 storage V_MEMRAM1 ptrtype MEMORY_CAN *
# define V_DEF_P2SFR_CAN_TYPE(storage, ptrtype)                   typedef storage V_MEMRAM1 ptrtype MEMORY_CAN *

# define V_DEF_CONSTP2VAR(storage, ptrtype, memclass, ptrclass)   V_MEMROM0 storage V_MEMRAM1 ptrtype V_MEMRAM2 V_MEMRAM3 * V_MEMROM1 V_MEMROM2
# define V_DEF_CONST(storage, type, memclass)                     V_MEMROM0 storage V_MEMROM1 type V_MEMROM2
# define V_DEF_CONST_NEAR(storage, type)                          V_MEMROM0 storage V_MEMROM1_NEAR type V_MEMROM2_NEAR
# define V_DEF_CONST_FAR(storage, type)                           V_MEMROM0 storage V_MEMROM1_FAR type V_MEMROM2_FAR
# define V_DEF_CONST_TYPE(storage, type, memclass)                typedef storage V_MEMROM1 type V_MEMROM2
# define V_DEF_P2CONST(storage, ptrtype, memclass, ptrclass)      V_MEMRAM0 storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2
# define V_DEF_P2CONST_PARA(storage, ptrtype, memclass, ptrclass) storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2
# define V_DEF_P2CONST_TYPE(storage, ptrtype, ptrclass)           typedef storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 *
# define V_DEF_CONSTP2CONST(storage, ptrtype, memclass, ptrclass) V_MEMROM0 storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMROM1 V_MEMROM2
# define V_DEF_FUNC(storage, rettype, memclass)                   storage rettype
# define V_DEF_FUNC_API(storage, rettype, memclass)               storage C_API_1 rettype C_API_2
# define V_DEF_FUNC_CBK(storage, rettype, memclass)               storage C_CALLBACK_1 rettype C_CALLBACK_2
# define V_DEF_P2FUNC(storage, rettype, ptrclass, fctname)        storage C_CALLBACK_1 rettype (C_CALLBACK_2 *fctname)
#endif

#endif

