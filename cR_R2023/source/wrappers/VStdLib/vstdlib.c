

#define VSTDLIB_SOURCE

#include "vstdlib.h"

#if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (  (VSTDLIB_SW_MAJOR_VERSION != (2u)) \
    || (VSTDLIB_SW_MINOR_VERSION != (0u)) \
    || (VSTDLIB_SW_PATCH_VERSION != (2u)) )
# error "Vendor specific version numbers of vstdlib.c and vstdlib.h are inconsistent!"
#endif

#if (  (VSTDLIB_CFG_MAJOR_VERSION != (2u)) \
    || (VSTDLIB_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of vstdlib.c and VStdLib_Cfg.h are inconsistent!"
#endif

#define VSTDLIB_MASK_3               (0x03u)
#define VSTDLIB_MASK_31              (0x1Fu)

#define VSTDLIB_ALIGN_OFFSET(ptr) \
  (uint8_least)((4 - (uint32_least)(ptr)) & VSTDLIB_MASK_3)

#if !defined (VSTDLIB_LOCAL_INLINE)
# define VSTDLIB_LOCAL_INLINE        LOCAL_INLINE
#endif

#define VSTDLIB_START_SEC_CODE
#include "MemMap.h"

#if (VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON)
# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  uint8 nPattern,
  uint32_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_PartialWord(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8_least nCnt,
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pPrev,
  P2VAR(uint32_least, AUTOMATIC, VSTDLIB_VAR_FAR) pDPos);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Unaligned(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt,
  uint8_least nDstOffset);

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt)
{
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 3:
      pDst8[2] = nPattern;

    case 2:
      pDst8[1] = nPattern;

    case 1:
      pDst8[0] = nPattern;

    default:

      break;
  }

#  else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[remaining] = nPattern;
  }

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt)
{
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 31:
      pDst8[30] = nPattern;

    case 30:
      pDst8[29] = nPattern;

    case 29:
      pDst8[28] = nPattern;

    case 28:
      pDst8[27] = nPattern;

    case 27:
      pDst8[26] = nPattern;

    case 26:
      pDst8[25] = nPattern;

    case 25:
      pDst8[24] = nPattern;

    case 24:
      pDst8[23] = nPattern;

    case 23:
      pDst8[22] = nPattern;

    case 22:
      pDst8[21] = nPattern;

    case 21:
      pDst8[20] = nPattern;

    case 20:
      pDst8[19] = nPattern;

    case 19:
      pDst8[18] = nPattern;

    case 18:
      pDst8[17] = nPattern;

    case 17:
      pDst8[16] = nPattern;

    case 16:
      pDst8[15] = nPattern;

    case 15:
      pDst8[14] = nPattern;

    case 14:
      pDst8[13] = nPattern;

    case 13:
      pDst8[12] = nPattern;

    case 12:
      pDst8[11] = nPattern;

    case 11:
      pDst8[10] = nPattern;

    case 10:
      pDst8[9] = nPattern;

    case 9:
      pDst8[8] = nPattern;

    case 8:
      pDst8[7] = nPattern;

    case 7:
      pDst8[6] = nPattern;

    case 6:
      pDst8[5] = nPattern;

    case 5:
      pDst8[4] = nPattern;

    case 4:
      pDst8[3] = nPattern;

    case 3:
      pDst8[2] = nPattern;

    case 2:
      pDst8[1] = nPattern;

    case 1:
      pDst8[0] = nPattern;

    default:

      break;
  }

#  else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[remaining] = nPattern;
  }

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  uint8 nPattern,
  uint32_least nCnt)
{
  uint32_least dPos = 0;
  uint32_least remaining;
  uint32 nPattern32 =
    (uint32)(((uint32)nPattern << 24) | ((uint32)nPattern << 16) | ((uint32)nPattern << 8) | nPattern);

  for (remaining = nCnt; remaining >= 16; remaining -= 16)
  {
    pDst32[dPos + 0] = nPattern32;
    pDst32[dPos + 1] = nPattern32;
    pDst32[dPos + 2] = nPattern32;
    pDst32[dPos + 3] = nPattern32;
    dPos += 4;
  }

#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (remaining)
  {
    case 15:
    case 14:
    case 13:
    case 12:
      pDst32[dPos] = nPattern32;
      dPos++;

    case 11:
    case 10:
    case 9:
    case 8:
      pDst32[dPos] = nPattern32;
      dPos++;

    case 7:
    case 6:
    case 5:
    case 4:
      pDst32[dPos] = nPattern32;
      dPos++;

    case 3:
    case 2:
    case 1:
      VStdLib_Loc_MemSet_8_3(
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
        nPattern,
        (uint8_least) (remaining & VSTDLIB_MASK_3));

    default:

      break;
  }

#  else

  VStdLib_Loc_MemSet_8_31(
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
    nPattern,
    (uint8_least) (remaining & VSTDLIB_MASK_31));

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt)
{
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 3:
      pDst8[2] = pSrc8[2];

    case 2:
      pDst8[1] = pSrc8[1];

    case 1:
      pDst8[0] = pSrc8[0];

    default:

      break;
  }

#  else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[remaining] = pSrc8[remaining];
  }

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt)
{
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 31:
      pDst8[30] = pSrc8[30];

    case 30:
      pDst8[29] = pSrc8[29];

    case 29:
      pDst8[28] = pSrc8[28];

    case 28:
      pDst8[27] = pSrc8[27];

    case 27:
      pDst8[26] = pSrc8[26];

    case 26:
      pDst8[25] = pSrc8[25];

    case 25:
      pDst8[24] = pSrc8[24];

    case 24:
      pDst8[23] = pSrc8[23];

    case 23:
      pDst8[22] = pSrc8[22];

    case 22:
      pDst8[21] = pSrc8[21];

    case 21:
      pDst8[20] = pSrc8[20];

    case 20:
      pDst8[19] = pSrc8[19];

    case 19:
      pDst8[18] = pSrc8[18];

    case 18:
      pDst8[17] = pSrc8[17];

    case 17:
      pDst8[16] = pSrc8[16];

    case 16:
      pDst8[15] = pSrc8[15];

    case 15:
      pDst8[14] = pSrc8[14];

    case 14:
      pDst8[13] = pSrc8[13];

    case 13:
      pDst8[12] = pSrc8[12];

    case 12:
      pDst8[11] = pSrc8[11];

    case 11:
      pDst8[10] = pSrc8[10];

    case 10:
      pDst8[9] = pSrc8[9];

    case 9:
      pDst8[8] = pSrc8[8];

    case 8:
      pDst8[7] = pSrc8[7];

    case 7:
      pDst8[6] = pSrc8[6];

    case 6:
      pDst8[5] = pSrc8[5];

    case 5:
      pDst8[4] = pSrc8[4];

    case 4:
      pDst8[3] = pSrc8[3];

    case 3:
      pDst8[2] = pSrc8[2];

    case 2:
      pDst8[1] = pSrc8[1];

    case 1:
      pDst8[0] = pSrc8[0];

    default:

      break;
  }

#  else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[remaining] = pSrc8[remaining];
  }

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt)
{
  uint32_least dPos = 0;
  uint32_least remaining;
  uint32 x0, x1, x2, x3;

  for (remaining = nCnt; remaining >= 16; remaining -= 16)
  {
    x0 = pSrc32[dPos + 0];
    x1 = pSrc32[dPos + 1];
    x2 = pSrc32[dPos + 2];
    x3 = pSrc32[dPos + 3];
    pDst32[dPos + 0] = x0;
    pDst32[dPos + 1] = x1;
    pDst32[dPos + 2] = x2;
    pDst32[dPos + 3] = x3;
    dPos += 4;
  }

#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (remaining)
  {
    case 15:
    case 14:
    case 13:
    case 12:
      pDst32[dPos] = pSrc32[dPos];
      dPos++;

    case 11:
    case 10:
    case 9:
    case 8:
      pDst32[dPos] = pSrc32[dPos];
      dPos++;

    case 7:
    case 6:
    case 5:
    case 4:
      pDst32[dPos] = pSrc32[dPos];
      dPos++;

    case 3:
    case 2:
    case 1:
      VStdLib_Loc_MemCpy_8_3(
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
        (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[dPos],
        (uint8_least) (remaining & VSTDLIB_MASK_3));

    default:

      break;
  }

#  else

  VStdLib_Loc_MemCpy_8_31(
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
    (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[dPos],
    (uint8_least) (remaining & VSTDLIB_MASK_31));

#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_PartialWord(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8_least nCnt,
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pPrev,
  P2VAR(uint32_least, AUTOMATIC, VSTDLIB_VAR_FAR) pDPos)
{
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 3:
      pDst8[*pDPos] = (uint8) *pPrev;
      (*pDPos)++;
      (*pPrev) >>= 8;

    case 2:
      pDst8[*pDPos] = (uint8) *pPrev;
      (*pDPos)++;
      (*pPrev) >>= 8;

    default:
      pDst8[*pDPos] = (uint8) *pPrev;
      (*pDPos)++;
      (*pPrev) >>= 8;
      break;
  }

#   else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[*pDPos] = (uint8) (uint8) *pPrev;
    (*pDPos)++;
    (*pPrev) >>= 8;
  }

#   endif
#  else
#if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  switch (nCnt)
  {
    case 3:
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24);
      (*pDPos)++;
      (*pPrev) <<= 8;

    case 2:
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24);
      (*pDPos)++;
      (*pPrev) <<= 8;

    default:
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24);
      (*pDPos)++;
      (*pPrev) <<= 8;
      break;
  }

#   else

  uint8_least remaining;

  for (remaining = 0; remaining < nCnt; remaining++)
  {
    pDst8[*pDPos] = (uint8) ((*pPrev) >> 24);
    (*pDPos)++;
    (*pPrev) <<= 8;
  }

#   endif
#  endif
}

VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Unaligned(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt,
  uint8_least nDstOffset)
{
  uint32_least dPos = 0;
  uint32_least sPos = 0;
  uint32_least remaining = nCnt;

  if (remaining >= 32)
  {
    P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32;
    uint32 prev;

    prev = pSrc32[sPos];
    remaining -= 4;
    VStdLib_Loc_MemCpy_8_PartialWord(
      pDst8,
      nDstOffset,
      &prev,
      &dPos);

    pDst32 = (uint32*) &pDst8[dPos];
    dPos = 0;
    sPos++;

    if (nDstOffset == 3)
    {
      for (; remaining >= 16; remaining -= 16)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos + 0];
        x2 = pSrc32[sPos + 1];
        x3 = pSrc32[sPos + 2];
        x4 = pSrc32[sPos + 3];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 8);
        x1 = (x1 >> 24) | (x2 << 8);
        x2 = (x2 >> 24) | (x3 << 8);
        x3 = (x3 >> 24) | (x4 << 8);
        prev = x4 >> 24;
#  else
        x0 = prev | (x1 >> 8);
        x1 = (x1 << 24) | (x2 >> 8);
        x2 = (x2 << 24) | (x3 >> 8);
        x3 = (x3 << 24) | (x4 >> 8);
        prev = x4 << 24;
#  endif
        pDst32[dPos + 0] = x0;
        pDst32[dPos + 1] = x1;
        pDst32[dPos + 2] = x2;
        pDst32[dPos + 3] = x3;
        dPos += 4;
        sPos += 4;
      }
    }
    else if (nDstOffset == 2)
    {
      for (; remaining >= 16; remaining -= 16)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos + 0];
        x2 = pSrc32[sPos + 1];
        x3 = pSrc32[sPos + 2];
        x4 = pSrc32[sPos + 3];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 16);
        x1 = (x1 >> 16) | (x2 << 16);
        x2 = (x2 >> 16) | (x3 << 16);
        x3 = (x3 >> 16) | (x4 << 16);
        prev = x4 >> 16;
#  else
        x0 = prev | (x1 >> 16);
        x1 = (x1 << 16) | (x2 >> 16);
        x2 = (x2 << 16) | (x3 >> 16);
        x3 = (x3 << 16) | (x4 >> 16);
        prev = x4 << 16;
#  endif
        pDst32[dPos + 0] = x0;
        pDst32[dPos + 1] = x1;
        pDst32[dPos + 2] = x2;
        pDst32[dPos + 3] = x3;
        dPos += 4;
        sPos += 4;
      }

    }
    else
    {
      for (; remaining >= 16; remaining -= 16)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos + 0];
        x2 = pSrc32[sPos + 1];
        x3 = pSrc32[sPos + 2];
        x4 = pSrc32[sPos + 3];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 24);
        x1 = (x1 >> 8) | (x2 << 24);
        x2 = (x2 >> 8) | (x3 << 24);
        x3 = (x3 >> 8) | (x4 << 24);
        prev = x4 >> 8;
#  else
        x0 = prev | (x1 >> 24);
        x1 = (x1 << 8) | (x2 >> 24);
        x2 = (x2 << 8) | (x3 >> 24);
        x3 = (x3 << 8) | (x4 >> 24);
        prev = x4 << 8;
#  endif
        pDst32[dPos + 0] = x0;
        pDst32[dPos + 1] = x1;
        pDst32[dPos + 2] = x2;
        pDst32[dPos + 3] = x3;
        dPos += 4;
        sPos += 4;
      }
    }

    {
      uint8_least prevShift = (nDstOffset << 3) & VSTDLIB_MASK_31;
      uint8_least xShift = 32 - prevShift;

      for (; remaining >= 4; remaining -= 4)
      {
        uint32 x0, x1;
        x1 = pSrc32[sPos];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << xShift);
        prev = x1 >> prevShift;
#  else
        x0 = prev | (x1 >> xShift);
        prev = x1 << prevShift;
#  endif
        pDst32[dPos] = x0;
        dPos++;
        sPos++;
      }
    }

    pDst8 = (uint8*) &pDst32[dPos];
    dPos = 0;
    VStdLib_Loc_MemCpy_8_PartialWord(
      pDst8,
      (4 - nDstOffset),
      &prev,
      &dPos);
  }

  VStdLib_Loc_MemCpy_8_31(
    &pDst8[dPos],
    (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[sPos],
    (uint8_least) (remaining & VSTDLIB_MASK_31));
}

# endif

FUNC(void, VSTDLIB_CODE) VStdLib_MemSet(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                        uint8 nPattern,
                                        VStdLib_CntType nCnt)
{

  VStdLib_CntType remaining;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)

  if (pDst == NULL_PTR)
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {

# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

    remaining = nCnt;

    if (remaining < 32)
    {

      VStdLib_Loc_MemSet_8_31(
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
        nPattern,
        (uint8_least) (remaining & VSTDLIB_MASK_31));
    }

    else
    {

      uint8_least nDstOffset = VSTDLIB_ALIGN_OFFSET(pDst);

      if (nDstOffset != 0)
      {

        VStdLib_Loc_MemSet_8_3(
          (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
          nPattern,
          nDstOffset);

        pDst = &((P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst)[nDstOffset];
        remaining -= nDstOffset;
      }

      VStdLib_Loc_MemSet_32_Aligned(
        (P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
        nPattern,
        remaining);
    }

# else

    for (remaining = 0; remaining < nCnt; remaining++)
    {
      ((P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR))(pDst))[remaining] = nPattern;
    }

# endif
  }

# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_SET, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId);
# endif
}

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                        P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                        VStdLib_CntType nCnt)
{

  VStdLib_CntType remaining;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)

  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {

# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

    remaining = nCnt;

    if (remaining < 32)
    {

      VStdLib_Loc_MemCpy_8_31(
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
        (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc,
        (uint8_least) (remaining & VSTDLIB_MASK_31));
    }

    else
    {

      uint8_least nSrcOffset = VSTDLIB_ALIGN_OFFSET(pSrc);
      uint8_least nDstOffset;

      if (nSrcOffset != 0)
      {

        VStdLib_Loc_MemCpy_8_3(
          (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
          (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc,
          nSrcOffset);

        pSrc = &((P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc)[nSrcOffset];
        pDst = &((P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst)[nSrcOffset];
        remaining -= nSrcOffset;
      }

      nDstOffset = VSTDLIB_ALIGN_OFFSET(pDst);

      if (nDstOffset == 0)
      {

        VStdLib_Loc_MemCpy_32_Aligned(
          (P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
          (P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc,
          remaining);
      }

      else
      {

        VStdLib_Loc_MemCpy_32_Unaligned(
          (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst,
          (P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc,
          remaining,
          nDstOffset);
      }
    }

# else

    for (remaining = 0; remaining < nCnt; remaining++)
    {
      ((P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR))(pDst))[remaining] =
        ((P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR))(pSrc))[remaining];
    }

# endif
  }

# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId);
# endif
}

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy16(P2VAR(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          P2CONST(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{

  VStdLib_CntType remaining;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)

  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {

    for (remaining = 0; remaining < nCnt; remaining++)
    {
      (pDst)[remaining] = (pSrc)[remaining];
    }
  }

# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_16, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId);
# endif
}

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy32(P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{

  VStdLib_CntType remaining;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)

  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {

    for (remaining = 0u; remaining < nCnt; remaining++)
    {
      (pDst)[remaining] = (pSrc)[remaining];
    }
  }

# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_32, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId);
# endif
}

#endif

FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy_s(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          VStdLib_CntType nDstSize,
                                          P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{

  uint8 errorId = VSTDLIB_E_NO_ERROR;

  if (nCnt > nDstSize)
  {
    errorId = VSTDLIB_E_PARAM_SIZE;
  }
  else
  {

    VStdLib_MemCpy(pDst, pSrc, nCnt);
  }

#if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_S, errorId);
  }
#else
  VSTDLIB_DUMMY_STATEMENT(errorId);
#endif
}

#if (VSTDLIB_VERSION_INFO_API == STD_ON)

FUNC(void, VSTDLIB_CODE) VStdLib_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VSTDLIB_APPL_VAR) versioninfo)
{

  uint8 errorId = VSTDLIB_E_NO_ERROR;

# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)

  if (versioninfo == NULL_PTR)
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {

    versioninfo->vendorID = VSTDLIB_VENDOR_ID;
    versioninfo->moduleID = VSTDLIB_MODULE_ID;
    versioninfo->sw_major_version = VSTDLIB_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = VSTDLIB_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = VSTDLIB_SW_PATCH_VERSION;
  }

# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_GET_VERSION_INFO, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId);
# endif
}

#endif

#define VSTDLIB_STOP_SEC_CODE
#include "MemMap.h"

