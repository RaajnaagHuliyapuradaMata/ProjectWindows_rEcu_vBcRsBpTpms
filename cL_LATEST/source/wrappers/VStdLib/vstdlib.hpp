

#if !defined (VSTDLIB_H)
#define VSTDLIB_H

#include "Std_Types.hpp"

#include "VStdLib_Cfg.hpp"

# if !defined (VSTDLIB_USE_LIBRARY_FUNCTIONS)
#  error "VSTDLIB_USE_LIBRARY_FUNCTIONS has to be defined.. check VStdLib_Cfg.h!"
# endif

# if(VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON)
#  if(!defined (VStdLib_MemClr) || !defined (VStdLib_MemSet) || !defined (VStdLib_MemCpy) || \
       !defined (VStdLib_MemCpy16) || !defined (VStdLib_MemCpy32))
#   error "VStdLib_MemClr, VStdLib_MemSet, VStdLib_MemCpy, VStdLib_MemCpy16 and VStdLib_MemCpy32 have to be defined!"
#  endif
# endif

# if !defined (VSTDLIB_RUNTIME_OPTIMIZATION)
#  error "VSTDLIB_RUNTIME_OPTIMIZATION has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_USE_JUMPTABLES)
#  error "VSTDLIB_USE_JUMPTABLES has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DEV_ERROR_DETECT)
#  error "VSTDLIB_DEV_ERROR_DETECT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DEV_ERROR_REPORT)
#  error "VSTDLIB_DEV_ERROR_REPORT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if((VSTDLIB_DEV_ERROR_REPORT == STD_ON) && (VSTDLIB_DEV_ERROR_DETECT != STD_ON))
#  error "VSTDLIB_DEV_ERROR_REPORT defined to STD_ON requires VSTDLIB_DEV_ERROR_DETECT also to be defined to STD_ON!"
# endif

# if !defined (VSTDLIB_VERSION_INFO_API)
#  error "VSTDLIB_VERSION_INFO_API has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DUMMY_STATEMENT)
#  error "VSTDLIB_DUMMY_STATEMENT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_CFG_MAJOR_VERSION)
#  error "VSTDLIB_CFG_MAJOR_VERSION has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_CFG_MINOR_VERSION)
#  error "VSTDLIB_CFG_MINOR_VERSION has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_SUPPORT_LARGE_DATA)
#  define VSTDLIB_SUPPORT_LARGE_DATA         STD_ON
# endif

# if(VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON)
#  if((VSTDLIB_SUPPORT_LARGE_DATA != STD_ON) && (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON))
#   error "VSTDLIB_RUNTIME_OPTIMIZATION must not be enabled if large data support is not given!"
#  endif
# endif

#define VSTDLIB_VENDOR_ID                   (30u)
#define VSTDLIB_MODULE_ID                   (255u)

#define VSTDLIB_SW_MAJOR_VERSION            (2u)
#define VSTDLIB_SW_MINOR_VERSION            (0u)
#define VSTDLIB_SW_PATCH_VERSION            (2u)

# if !defined (VSTDLIB_INSTANCE_ID_DET)
#  define VSTDLIB_INSTANCE_ID_DET            (0u)
# endif

#define VSTDLIB_SID_MEM_SET                 (0x00u)
#define VSTDLIB_SID_MEM_COPY                (0x01u)
#define VSTDLIB_SID_MEM_COPY_16             (0x02u)
#define VSTDLIB_SID_MEM_COPY_32             (0x03u)
#define VSTDLIB_SID_MEM_COPY_S              (0x04u)
#define VSTDLIB_SID_GET_VERSION_INFO        (0x05u)

#define VSTDLIB_E_NO_ERROR                  (0x00u)
#define VSTDLIB_E_PARAM_POINTER             (0x01u)
#define VSTDLIB_E_PARAM_SIZE                (0x02u)

# if(VSTDLIB_SUPPORT_LARGE_DATA == STD_ON)
typedef uint32_least VStdLib_CntType;
# else
typedef uint16_least VStdLib_CntType;
# endif

# if(VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON)

#  define VStdLib_MemClr(pDst, nCnt)                       VStdLib_MemSet((pDst), 0, (nCnt))

# endif

# if(VSTDLIB_SUPPORT_LARGE_DATA == STD_ON)

#  define VStdLib_MemClrLarge(pDst, nCnt)                    VStdLib_MemClr((pDst), (nCnt))

#  define VStdLib_MemSetLarge(pDst, nPattern, nCnt)          VStdLib_MemSet((pDst), (nPattern), (nCnt))

#  define VStdLib_MemCpyLarge(pDst, pSrc, nCnt)              VStdLib_MemCpy((pDst), (pSrc), (nCnt))

#  define VStdLib_MemCpy16Large(pDst, pSrc, nCnt)            VStdLib_MemCpy16((pDst), (pSrc), (nCnt))

#  define VStdLib_MemCpy32Large(pDst, pSrc, nCnt)            VStdLib_MemCpy32((pDst), (pSrc), (nCnt))

#  define VStdLib_MemCpyLarge_s(pDst, nDstSize, pSrc, nCnt)  VStdLib_MemCpy_s((pDst), (nDstSize), (pSrc), (nCnt))

# endif

# if !defined (VStdLib_MemClrMacro)

#  define VStdLib_MemClrMacro(pDst, nCnt) \
   { VStdLib_CntType __i; for( __i = 0u; __i < (nCnt); ++__i) { (pDst)[__i] = 0; }}\

# endif

# if !defined (VStdLib_MemSetMacro)

#  define VStdLib_MemSetMacro(pDst, nPattern, nCnt) \
   { VStdLib_CntType __i; for( __i = 0u; __i < (nCnt); ++__i) { (pDst)[__i] = (nPattern); }}\

# endif

# if !defined (VStdLib_MemCpyMacro)

#  define VStdLib_MemCpyMacro(pDst, pSrc, nCnt) \
   { VStdLib_CntType __i; for( __i = 0u; __i < (nCnt); ++__i) { (pDst)[__i] = (pSrc)[__i]; }}\

# endif

# if !defined (VStdLib_MemCpyMacro_s)

#  define VStdLib_MemCpyMacro_s(pDst, nDstSize, pSrc, nCnt) \
   { if((nDstSize) >= (nCnt)) { VStdLib_MemCpyMacro((pDst), (pSrc), (nCnt)); }}\

# endif

#define VSTDLIB_START_SEC_CODE
#include "MemMap.hpp"

# if(VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON)

FUNC(void, VSTDLIB_CODE) VStdLib_MemSet(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst
   ,                                       uint8 nPattern
   ,                                       VStdLib_CntType nCnt);

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst
   ,                                       P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc
   ,                                       VStdLib_CntType nCnt);

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy16(P2VAR(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pDst
   ,                                         P2CONST(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc
   ,                                         VStdLib_CntType nCnt);

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy32(P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst
   ,                                         P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc
   ,                                         VStdLib_CntType nCnt);

# endif

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy_s(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst
   ,                                         VStdLib_CntType nDstSize
   ,                                         P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc
   ,                                         VStdLib_CntType nCnt);

# if(VSTDLIB_VERSION_INFO_API == STD_ON)

FUNC(void, VSTDLIB_CODE) VStdLib_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VSTDLIB_APPL_VAR) versioninfo);

# endif

#define VSTDLIB_STOP_SEC_CODE
#include "MemMap.hpp"

#define VSTDLIB__COREHLL_VERSION            (0x0308u)
#define VSTDLIB__COREHLL_RELEASE_VERSION    (0x00u)
#define VSTDLIB_GENERICASR_VERSION          ((VSTDLIB_SW_MAJOR_VERSION << 8u) | VSTDLIB_SW_MINOR_VERSION)
#define VSTDLIB_GENERICASR_RELEASE_VERSION  VSTDLIB_SW_PATCH_VERSION
#define kVStdMainVersion                    VSTDLIB_SW_MAJOR_VERSION
#define kVStdSubVersion                     VSTDLIB_SW_MINOR_VERSION
#define kVStdReleaseVersion                 VSTDLIB_SW_PATCH_VERSION

#define kVStdErrorIntDisableTooOften        (0x01u)
#define kVStdErrorIntRestoreTooOften        (0x02u)
#define kVStdErrorMemClrInvalidParameter    (0x03u)
#define kVStdErrorMemCpyInvalidParameter    (0x04u)
#define kVStdErrorFunctionNotSupportedByHw  (0x05u)
#define kVStdErrorMemSetInvalidParameter    (0x06u)
#define kVStdErrorUnexpectedLockState       (0x07u)

#define VSTD_HL_DISABLE_SUPPORT_MEM_FCT
#define VSTD_HL_DISABLE_MEM_FCT_MAPPING
#define VSTD_HL_USE_VSTD_MEMCLR
#define VSTD_HL_USE_VSTD_MEMSET
#define VSTD_HL_USE_VSTD_RAMMEMCPY
#define VSTD_HL_USE_VSTD_ROMMEMCPY
#define VSTD_HL_USE_VSTD_WORD_MEMCPY
#define VSTD_HL_USE_VSTD_DWORD_MEMCPY

#define VStdInitPowerOn()

# if !defined (VStdLib_MemCpyRom)
#  define VStdLib_MemCpyRom(d, s, c)         VStdLib_MemCpy((d), (s), (c))
# endif

#define VStdMemClr(d, c)                    VStdLib_MemClr((d), (c))
#define VStdMemNearClr(d, c)                VStdLib_MemClr((d), (c))
#define VStdMemFarClr(d, c)                 VStdLib_MemClr((d), (c))
#define VStdMemSet(d, p, c)                 VStdLib_MemSet((d), (p), (c))
#define VStdMemNearSet(d, p, c)             VStdLib_MemSet((d), (p), (c))
#define VStdMemFarSet(d, p, c)              VStdLib_MemSet((d), (p), (c))

#define VStdMemCpy(d, s, c)                 VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyRom(d, s, c)              VStdLib_MemCpyRom((d), (s), (c))
#define VStdMemCpyRamToRam(d, s, c)         VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyRomToRam(d, s, c)         VStdLib_MemCpyRom((d), (s), (c))
#define VStdMemCpyRamToNearRam(d, s, c)     VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyRomToNearRam(d, s, c)     VStdLib_MemCpyRom((d), (s), (c))
#define VStdMemCpyRamToFarRam(d, s, c)      VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyRomToFarRam(d, s, c)      VStdLib_MemCpyRom((d), (s), (c))
#define VStdMemCpyFarRamToRam(d, s, c)      VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyFarRamToFarRam(d, s, c)   VStdLib_MemCpy((d), (s), (c))
#define VStdMemCpyFarRomToFarRam(d, s, c)   VStdLib_MemCpyRom((d), (s), (c))
#define VStdRamMemCpy(d, s, c)              VStdLib_MemCpy((d), (s), (c))
#define VStdRomMemCpy(d, s, c)              VStdLib_MemCpyRom((d), (s), (c))

#define VStdMemCpy16(d, s, c)               VStdLib_MemCpy16((d), (s), (c))
#define VStdMemCpy16RamToRam(d, s, c)       VStdLib_MemCpy16((d), (s), (c))
#define VStdMemCpy16RamToNearRam(d, s, c)   VStdLib_MemCpy16((d), (s), (c))
#define VStdMemCpy16NearRamToRam(d, s, c)   VStdLib_MemCpy16((d), (s), (c))
#define VStdMemCpy16RamToFarRam(d, s, c)    VStdLib_MemCpy16((d), (s), (c))
#define VStdMemCpy16FarRamToRam(d, s, c)    VStdLib_MemCpy16((d), (s), (c))
#define VStdRamMemCpy16(d, s, c)            VStdLib_MemCpy16((d), (s), (c))

#define VStdMemCpy32(d, s, c)               VStdLib_MemCpy32((d), (s), (c))
#define VStdMemCpy32RamToRam(d, s, c)       VStdLib_MemCpy32((d), (s), (c))
#define VStdMemCpy32RamToNearRam(d, s, c)   VStdLib_MemCpy32((d), (s), (c))
#define VStdMemCpy32NearRamToRam(d, s, c)   VStdLib_MemCpy32((d), (s), (c))
#define VStdMemCpy32RamToFarRam(d, s, c)    VStdLib_MemCpy32((d), (s), (c))
#define VStdMemCpy32FarRamToRam(d, s, c)    VStdLib_MemCpy32((d), (s), (c))
#define VStdRamMemCpy32(d, s, c)            VStdLib_MemCpy32((d), (s), (c))

# if !defined (VStdLib_MemCpyRomMacro)
#  define VStdLib_MemCpyRomMacro(d, s, c)    VStdLib_MemCpyMacro((d), (s), (c))
# endif

#define VStdMemClr_Macro(d, c)              VStdLib_MemClrMacro((d), (c))
#define VStdMemSet_Macro(d, p, c)           VStdLib_MemSetMacro((d), (p), (c))
#define VStdMemCpy_Macro(d, s, c)           VStdLib_MemCpyMacro((d), (s), (c))
#define VStdMemCpyRom_Macro(d, s, c)        VStdLib_MemCpyRomMacro((d), (s), (c))

#endif

