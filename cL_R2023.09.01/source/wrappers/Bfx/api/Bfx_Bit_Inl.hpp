

#ifndef BFX_BIT_INL_H
#define BFX_BIT_INL_H

LOCAL_INLINE void Bfx_Lok_ClrBit_u16u8_Inl(uint16* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBit_u32u8_Inl(uint32* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBit_u8u8_Inl(uint8* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBit_u64u8_Inl(Bfx_uint64* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask);
LOCAL_INLINE void Bfx_Lok_CopyBit_u16u8u16u8_Inl(uint16* DestinationData, uint8 DestinationPosition, uint16 SourceData
   ,                                                                                                uint8 SourcePosition);
LOCAL_INLINE void Bfx_Lok_CopyBit_u32u8u32u8_Inl(uint32* DestinationData, uint8 DestinationPosition, uint32 SourceData
   ,                                                                                                uint8 SourcePosition);
LOCAL_INLINE void Bfx_Lok_CopyBit_u8u8u8u8_Inl(uint8* DestinationData, uint8 DestinationPosition, uint8 SourceData
   ,                                                                                                uint8 SourcePosition);
LOCAL_INLINE void Bfx_Lok_CopyBit_u64u8u64u8_Inl(Bfx_uint64* DestinationData, uint8 DestinationPosition
   ,                                                                         Bfx_uint64 SourceData, uint8 SourcePosition);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u16u8_u8_Inl(uint16 Data, uint8 BitPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u32u8_u8_Inl(uint32 Data, uint8 BitPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u64u8_u8_Inl(Bfx_uint64 Data, uint8 BitPn);
LOCAL_INLINE uint16 Bfx_Lok_GetBits_u16u8u8_u16_Inl(uint16 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE uint32 Bfx_Lok_GetBits_u32u8u8_u32_Inl(uint32 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE uint8 Bfx_Lok_GetBits_u8u8u8_u8_Inl(uint8 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE Bfx_uint64 Bfx_Lok_GetBits_u64u8u8_u64_Inl(Bfx_uint64 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE void Bfx_Lok_PutBit_u16u8u8_Inl(uint16* Data, uint8 BitPn, boolean Status);
LOCAL_INLINE void Bfx_Lok_PutBit_u32u8u8_Inl(uint32* Data, uint8 BitPn, boolean Status);
LOCAL_INLINE void Bfx_Lok_PutBit_u8u8u8_Inl(uint8* Data, uint8 BitPn, boolean Status);
LOCAL_INLINE void Bfx_Lok_PutBit_u64u8u8_Inl(Bfx_uint64* Data, uint8 BitPn, boolean Status);
LOCAL_INLINE void Bfx_Lok_PutBits_u16u8u8u16_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint16 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBits_u32u8u8u32_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBits_u64u8u8u64_Inl(Bfx_uint64* Data, uint8 BitStartPn, uint8 BitLn, Bfx_uint64 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u16u16u16_Inl(uint16* Data, uint16 Pattern, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u32u32u32_Inl(uint32* Data, uint32 Pattern, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u8u8u8_Inl(uint8* Data, uint8 Pattern, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u64u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Pattern, Bfx_uint64 Mask);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_SetBit_u16u8_Inl(uint16* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBit_u32u8_Inl(uint32* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBit_u8u8_Inl(uint8* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBit_u64u8_Inl(Bfx_uint64* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask);
LOCAL_INLINE void Bfx_Lok_SetBits_u16u8u8u8_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_SetBits_u32u8u8u8_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_SetBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_SetBits_u64u8u8u8_Inl(Bfx_uint64* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u16_Inl(uint16* Data);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u32_Inl(uint32* Data);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u8_Inl(uint8* Data);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u64_Inl(Bfx_uint64* Data);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u16u16_u8_Inl(uint16 Data, uint16 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u32u32_u8_Inl(uint32 Data, uint32 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u8u8_u8_Inl(uint8 Data, uint8 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u64u64_u8_Inl(Bfx_uint64 Data, Bfx_uint64 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u16u16_u8_Inl(uint16 Data, uint16 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u32u32_u8_Inl(uint32 Data, uint32 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u8u8_u8_Inl(uint8 Data, uint8 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u64u64_u8_Inl(Bfx_uint64 Data, Bfx_uint64 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u16_u8_Inl(uint16 Data);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u32_u8_Inl(uint32 Data);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u8_u8_Inl(uint8 Data);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u64_u8_Inl(Bfx_uint64 Data);

#ifndef BFX_PRV_CLRBIT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBit_u16u8_Inl(uint16* Data, uint8 BitPn)
{

    *Data &= ((uint16)(~(uint16)(1uL << BitPn)));
}
#endif

#ifndef BFX_PRV_CLRBIT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBit_u32u8_Inl(uint32* Data, uint8 BitPn)
{

    *Data &= ((uint32)(~(1uL << BitPn)));
}
#endif

#ifndef BFX_PRV_CLRBIT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBit_u8u8_Inl(uint8* Data, uint8 BitPn)
{

    *Data &= ((uint8)(~(uint8)(1u << BitPn)));
}
#endif

#ifndef BFX_PRV_CLRBIT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBit_u64u8_Inl(Bfx_uint64* Data, uint8 BitPn)
{

    *Data &= ((Bfx_uint64)(~(1uLL << BitPn)));
}
#endif

#ifndef BFX_PRV_CLRBITMASK_U16U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u16u16_Inl(uint16* Data, uint16 Mask)
{
    *Data &= ((uint16)(~Mask));
}
#endif

#ifndef BFX_PRV_CLRBITMASK_U32U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u32u32_Inl(uint32* Data, uint32 Mask)
{
    *Data &= ((uint32)(~Mask));
}
#endif

#ifndef BFX_PRV_CLRBITMASK_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u8u8_Inl(uint8* Data, uint8 Mask)
{
    *Data &= ((uint8)(~Mask));
}
#endif

#ifndef BFX_PRV_CLRBITMASK_U64U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask)
{
    *Data &= ((Bfx_uint64)(~Mask));
}
#endif

#ifndef BFX_PRV_COPYBIT_U16U8U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_CopyBit_u16u8u16u8_Inl(uint16* DestinationData, uint8 DestinationPosition, uint16 SourceData, uint8 SourcePosition)
{
    Bfx_Lok_PutBit_u16u8u8_Inl(DestinationData, DestinationPosition, Bfx_Lok_GetBit_u16u8_u8_Inl(SourceData
   ,                                                                                                     SourcePosition));
}
#endif

#ifndef BFX_PRV_COPYBIT_U32U8U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_CopyBit_u32u8u32u8_Inl(uint32* DestinationData, uint8 DestinationPosition, uint32 SourceData, uint8 SourcePosition)
{
    Bfx_Lok_PutBit_u32u8u8_Inl(DestinationData, DestinationPosition, Bfx_Lok_GetBit_u32u8_u8_Inl(SourceData
   ,                                                                                                     SourcePosition));
}
#endif

#ifndef BFX_PRV_COPYBIT_U8U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_CopyBit_u8u8u8u8_Inl(uint8* DestinationData, uint8 DestinationPosition, uint8 SourceData, uint8 SourcePosition)
{
    Bfx_Lok_PutBit_u8u8u8_Inl(DestinationData, DestinationPosition, Bfx_Lok_GetBit_u8u8_u8_Inl(SourceData
   ,                                                                                                     SourcePosition));
}
#endif

#ifndef BFX_PRV_COPYBIT_U64U8U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_CopyBit_u64u8u64u8_Inl(Bfx_uint64* DestinationData, uint8 DestinationPosition
   ,                                                                          Bfx_uint64 SourceData, uint8 SourcePosition)
{
    Bfx_Lok_PutBit_u64u8u8_Inl(DestinationData, DestinationPosition, Bfx_Lok_GetBit_u64u8_u8_Inl(SourceData
   ,                                                                                                     SourcePosition));
}
#endif

#ifndef BFX_PRV_GETBIT_U16U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_GetBit_u16u8_u8_Inl(uint16 Data, uint8 BitPn)
{
    return ((((Data) & ((uint16) (1uL << BitPn))) != 0u));
}
#endif

#ifndef BFX_PRV_GETBIT_U32U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_GetBit_u32u8_u8_Inl(uint32 Data, uint8 BitPn)
{
    return (((Data) & ((uint32)(1uL << BitPn))) != 0uL);
}
#endif

#ifndef BFX_PRV_GETBIT_U8U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn)
{
    return (((Data) & ((uint8)(1uL << BitPn))) != 0u);
}
#endif

#ifndef BFX_PRV_GETBIT_U64U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_GetBit_u64u8_u8_Inl(Bfx_uint64 Data, uint8 BitPn)
{
    return (((Data) & ((Bfx_uint64)(1uLL << BitPn))) != 0uLL);
}
#endif

#ifndef BFX_PRV_GETBITS_U16U8U8_U16_INL_REMAPPED
LOCAL_INLINE uint16 Bfx_Lok_GetBits_u16u8u8_u16_Inl(uint16 Data, uint8 BitStartPn, uint8 BitLn)
{
    return ((uint16)((Data >> BitStartPn) & (BFX_MAXUINT16_U >> (16uL - BitLn))));
}
#endif

#ifndef BFX_PRV_GETBITS_U32U8U8_U32_INL_REMAPPED
LOCAL_INLINE uint32 Bfx_Lok_GetBits_u32u8u8_u32_Inl(uint32 Data, uint8 BitStartPn, uint8 BitLn)
{
    return ((Data >> BitStartPn) & (BFX_MAXUINT32_U >> (32uL - BitLn)));
}
#endif

#ifndef BFX_PRV_GETBITS_U8U8U8_U8_INL_REMAPPED
LOCAL_INLINE uint8 Bfx_Lok_GetBits_u8u8u8_u8_Inl(uint8 Data, uint8 BitStartPn, uint8 BitLn)
{
    return ((uint8)((Data >> BitStartPn) & (BFX_MAXUINT8_U >> (8uL - BitLn))));
}
#endif

#ifndef BFX_PRV_GETBITS_U8U8U8_U8_INL_REMAPPED
LOCAL_INLINE Bfx_uint64 Bfx_Lok_GetBits_u64u8u8_u64_Inl(Bfx_uint64 Data, uint8 BitStartPn, uint8 BitLn)
{
    return ((Data >> BitStartPn) & (BFX_MAXUINT64_U >> (64uLL - BitLn)));
}
#endif

#ifndef BFX_PRV_PUTBIT_U16U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBit_u16u8u8_Inl(uint16* Data, uint8 BitPn, boolean Status)
{
   uint8 tmp_u8;
    tmp_u8 = (Status)? 1u : 0u;

    *Data = ((*Data & ((uint16)~(1uL << BitPn))) | ((uint16)((uint16)tmp_u8 << BitPn)));
}
#endif

#ifndef BFX_PRV_PUTBIT_U32U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBit_u32u8u8_Inl(uint32* Data, uint8 BitPn, boolean Status)
{
   uint8 tmp_u8;
    tmp_u8 = (Status)? 1u : 0u;

    *Data = ((*Data & ((uint32)~(1uL << BitPn))) | ((uint32)((uint32)tmp_u8 << BitPn)));
}
#endif

#ifndef BFX_PRV_PUTBIT_U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBit_u8u8u8_Inl(uint8* Data, uint8 BitPn, boolean Status)
{
   uint8 tmp_u8;
    tmp_u8 = (Status)? 1u : 0u;

    *Data = ((*Data & ((uint8)~(1uL <<BitPn))) | ((uint8)(tmp_u8 << BitPn)));
}
#endif

#ifndef BFX_PRV_PUTBIT_U64U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBit_u64u8u8_Inl(Bfx_uint64* Data, uint8 BitPn, boolean Status)
{
   uint8 tmp_u8;
    tmp_u8 = (Status)? 1u : 0u;

    *Data = ((*Data & ((Bfx_uint64)~(1uLL << BitPn))) | ((Bfx_uint64)((Bfx_uint64)tmp_u8 << BitPn)));
}
#endif

#ifndef BFX_PRV_PUTBITS_U16U8U8U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBits_u16u8u8u16_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint16 Pattern)
{

    *Data = (((uint16) (~(uint16) ((BFX_MAXUINT16_U >> (16uL - BitLn)) << BitStartPn))) & *Data) |
                                                (uint16)(((BFX_MAXUINT16_U >> (16uL - BitLn)) & Pattern) << BitStartPn);
}
#endif

#ifndef BFX_PRV_PUTBITS_U32U8U8U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBits_u32u8u8u32_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern)
{

    *Data = (((uint32) (~(uint32)((BFX_MAXUINT32_U >> (32uL - BitLn)) << BitStartPn))) & *Data) |
                                                (uint32)(((BFX_MAXUINT32_U >> (32uL - BitLn)) & Pattern) << BitStartPn);
}
#endif

#ifndef BFX_PRV_PUTBITS_U8U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern)
{

    *Data = (((uint8) (~(uint8)((BFX_MAXUINT8_U >> (8uL - BitLn)) << BitStartPn))) & *Data) | (uint8)(((BFX_MAXUINT8_U
                                                                            >> (8uL - BitLn)) & Pattern) << BitStartPn);
}
#endif

#ifndef BFX_PRV_PUTBITS_U64U8U8U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBits_u64u8u8u64_Inl(Bfx_uint64* Data, uint8 BitStartPn, uint8 BitLn, Bfx_uint64 Pattern)
{

    *Data = (((Bfx_uint64) (~(Bfx_uint64)((BFX_MAXUINT64_U >> (64uLL - BitLn)) << BitStartPn))) & *Data) |
                                           (Bfx_uint64)(((BFX_MAXUINT64_U >> (64uLL - BitLn)) & Pattern) << BitStartPn);
}
#endif

#ifndef BFX_PRV_PUTBITSMASK_U16U16U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u16u16u16_Inl(uint16* Data, uint16 Pattern, uint16 Mask)
{
    *Data = (*Data & ((uint16)~(Mask)) ) | (Pattern & Mask);
}
#endif

#ifndef BFX_PRV_PUTBITSMASK_U32U32U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u32u32u32_Inl(uint32* Data, uint32 Pattern, uint32 Mask)
{
    *Data =  (*Data & (~(Mask)) ) | (Pattern & Mask);
}
#endif

#ifndef BFX_PRV_PUTBITSMASK_U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u8u8u8_Inl(uint8* Data, uint8 Pattern, uint8 Mask)
{
    *Data = (*Data & ((uint8)~(Mask)) ) | (Pattern & Mask);
}
#endif

#ifndef BFX_PRV_PUTBITSMASK_U64U64U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u64u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Pattern, Bfx_uint64 Mask)
{
    *Data =  (*Data & (~(Mask)) ) | (Pattern & Mask);
}
#endif

#ifndef BFX_PRV_ROTBITLT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt)
{
    *Data = ((uint16) (*Data << ShiftCnt) | (uint16) (*Data >> (16u - ShiftCnt)));
}
#endif

#ifndef BFX_PRV_ROTBITLT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt)
{
    *Data = (*Data << ShiftCnt) | (*Data >> (32u - ShiftCnt));
}
#endif

#ifndef BFX_PRV_ROTBITLT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt)
{
    *Data = ((uint8) (*Data << ShiftCnt) | (uint8) (*Data >> (8u - ShiftCnt)));
}
#endif

#ifndef BFX_PRV_ROTBITLT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitLt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt)
{
    *Data = (*Data << ShiftCnt) | (*Data >> (64u - ShiftCnt));
}
#endif

#ifndef BFX_PRV_ROTBITRT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt)
{
    *Data = ((uint16) (*Data >> ShiftCnt) | (uint16) (*Data << (16u - ShiftCnt)));
}
#endif

#ifndef BFX_PRV_ROTBITRT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt)
{
    *Data = (*Data >> ShiftCnt) | (*Data << (32u - ShiftCnt));
}
#endif

#ifndef BFX_PRV_ROTBITRT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt)
{
    *Data = ((uint8) (*Data >> ShiftCnt) | (uint8) (*Data << (8u - ShiftCnt)));
}
#endif

#ifndef BFX_PRV_ROTBITRT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_RotBitRt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt)
{
    *Data = (*Data >> ShiftCnt) | (*Data << (64u - ShiftCnt));
}
#endif

#ifndef BFX_PRV_SETBIT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBit_u16u8_Inl(uint16* Data, uint8 BitPn)
{
    *Data |= ((uint16) (1uL << BitPn));
}
#endif

#ifndef BFX_PRV_SETBIT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBit_u32u8_Inl(uint32* Data, uint8 BitPn)
{
    *Data |= ((uint32)(1uL << BitPn));
}
#endif

#ifndef BFX_PRV_SETBIT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBit_u8u8_Inl(uint8* Data, uint8 BitPn)
{
    *Data |= ((uint8)(1uL << BitPn));
}
#endif

#ifndef BFX_PRV_SETBIT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBit_u64u8_Inl(Bfx_uint64* Data, uint8 BitPn)
{
    *Data |= ((Bfx_uint64)(1uLL << BitPn));
}
#endif

#ifndef BFX_PRV_SETBITMASK_U16U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBitMask_u16u16_Inl(uint16* Data, uint16 Mask)
{
    *Data |= Mask;
}
#endif

#ifndef BFX_PRV_SETBITMASK_U32U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBitMask_u32u32_Inl(uint32* Data, uint32 Mask)
{
    *Data |= Mask;
}
#endif

#ifndef BFX_PRV_SETBITMASK_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBitMask_u8u8_Inl(uint8* Data, uint8 Mask)
{
    *Data |= Mask;
}
#endif

#ifndef BFX_PRV_SETBITMASK_U64U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask)
{
    *Data |= Mask;
}
#endif

#ifndef BFX_PRV_SETBITS_U16U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBits_u16u8u8u8_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
{
   uint16  mask_u16;

    mask_u16 = (uint16) (BFX_MAXUINT16_U >> BitStartPn);
    mask_u16 = (uint16) (mask_u16 << (16u - BitLn));
    mask_u16 = (uint16) (mask_u16 >> (16u - BitStartPn - BitLn));

    *Data |= mask_u16;

   if(Status == 0u)
   {
        *Data ^= mask_u16;
   }
}
#endif

#ifndef BFX_PRV_SETBITS_U32U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBits_u32u8u8u8_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
{
   uint32  mask_u32;

    mask_u32 = (uint32) (BFX_MAXUINT32_U >> BitStartPn);
    mask_u32 = (uint32) (mask_u32 << (32u - BitLn));
    mask_u32 = (uint32) (mask_u32 >> (32u - BitStartPn - BitLn));

    *Data |= mask_u32;

   if(Status == 0u)
   {
        *Data ^= mask_u32;
   }
}
#endif

#ifndef BFX_PRV_SETBITS_U8U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
{
   uint8  mask_u8;

    mask_u8 = (uint8) (BFX_MAXUINT8_U >> BitStartPn);
    mask_u8 = (uint8) (mask_u8 << (8u - BitLn));
    mask_u8 = (uint8) (mask_u8 >> (8u - BitStartPn - BitLn));

    *Data |= mask_u8;

   if(Status == 0u)
   {
        *Data ^= mask_u8;
   }
}
#endif

#ifndef BFX_PRV_SETBITS_U64U8U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_SetBits_u64u8u8u8_Inl(Bfx_uint64* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
{
    Bfx_uint64  mask_u64;

    mask_u64 = (Bfx_uint64) (BFX_MAXUINT64_U >> BitStartPn);
    mask_u64 = (Bfx_uint64) (mask_u64 << (64u - BitLn));
    mask_u64 = (Bfx_uint64) (mask_u64 >> (64u - BitStartPn - BitLn));

    *Data |= mask_u64;

   if(Status == 0u)
   {
        *Data ^= mask_u64;
   }
}
#endif

#ifndef BFX_PRV_SHIFTBITLT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt)
{
    *Data <<= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITLT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt)
{
    *Data <<= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITLT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt)
{
    *Data <<= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITLT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt)
{
    *Data <<= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITRT_U16U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt)
{
    *Data >>= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITRT_U32U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt)
{
    *Data >>= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITRT_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt)
{
    *Data >>= ShiftCnt;
}
#endif

#ifndef BFX_PRV_SHIFTBITRT_U64U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u64u8_Inl(Bfx_uint64* Data, uint8 ShiftCnt)
{
    *Data >>= ShiftCnt;
}
#endif

#ifndef BFX_PRV_TOGGLEBITMASK_U16U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u16u16_Inl(uint16* Data, uint16 Mask)
{
    *Data ^= Mask;
}
#endif

#ifndef BFX_PRV_TOGGLEBITMASK_U32U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u32u32_Inl(uint32* Data, uint32 Mask)
{
    *Data ^= Mask;
}
#endif

#ifndef BFX_PRV_TOGGLEBITMASK_U8U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u8u8_Inl(uint8* Data, uint8 Mask)
{
    *Data ^= Mask;
}
#endif

#ifndef BFX_PRV_TOGGLEBITMASK_U64U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u64u64_Inl(Bfx_uint64* Data, Bfx_uint64 Mask)
{
    *Data ^= Mask;
}
#endif

#ifndef BFX_PRV_TOGGLEBITS_U16_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBits_u16_Inl(uint16* Data)
{
    *Data ^= 0xFFFFu;
}
#endif

#ifndef BFX_PRV_TOGGLEBITS_U32_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBits_u32_Inl(uint32* Data)
{
    *Data ^= 0xFFFFFFFFuL;
}
#endif

#ifndef BFX_PRV_TOGGLEBITS_U8_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBits_u8_Inl(uint8* Data)
{
    *Data ^= 0xFFu;
}
#endif

#ifndef BFX_PRV_TOGGLEBITS_U64_INL_REMAPPED
LOCAL_INLINE void Bfx_Lok_ToggleBits_u64_Inl(Bfx_uint64* Data)
{
    *Data ^= 0xFFFFFFFFFFFFFFFFuLL;
}
#endif

#ifndef BFX_PRV_TSTBITLNMASK_U16U16_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u16u16_u8_Inl(uint16 Data, uint16 Mask)
{
    return((Data & Mask) != 0uL);
}
#endif

#ifndef BFX_PRV_TSTBITLNMASK_U32U32_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u32u32_u8_Inl(uint32 Data, uint32 Mask)
{
    return ((Data & Mask) != 0uL);
}
#endif

#ifndef BFX_PRV_TSTBITLNMASK_U8U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u8u8_u8_Inl(uint8 Data, uint8 Mask)
{
    return ((Data & Mask) != 0uL);
}
#endif

#ifndef BFX_PRV_TSTBITLNMASK_U64U64_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u64u64_u8_Inl(Bfx_uint64 Data, Bfx_uint64 Mask)
{
    return ((Data & Mask) != 0uLL);
}
#endif

#ifndef BFX_PRV_TSTBITMASK_U16U16_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u16u16_u8_Inl(uint16 Data, uint16 Mask)
{
    return ((Data & Mask) == (Mask));
}
#endif

#ifndef BFX_PRV_TSTBITMASK_U32U32_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u32u32_u8_Inl(uint32 Data, uint32 Mask)
{
    return ((Data & Mask) == (Mask));
}
#endif

#ifndef BFX_PRV_TSTBITMASK_U8U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u8u8_u8_Inl(uint8 Data, uint8 Mask)
{
    return ((Data & Mask) == (Mask));
}
#endif

#ifndef BFX_PRV_TSTBITMASK_U64U64_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u64u64_u8_Inl(Bfx_uint64 Data, Bfx_uint64 Mask)
{
    return ((Data & Mask) == (Mask));
}
#endif

#ifndef BFX_PRV_TSTPARITYEVEN_U16_U8_INL_REMAPPED
 LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u16_u8_Inl(uint16 Data)
{
     uint16 tmp0_u16;
     uint16 tmp1_u16;
     boolean res_b;

     tmp0_u16 = Data;

     tmp1_u16 = (tmp0_u16 >> 8U);
     tmp0_u16 = (tmp0_u16 ^ tmp1_u16);

     tmp1_u16 = (tmp0_u16 >> 4U);
     tmp0_u16 = (tmp0_u16 ^ tmp1_u16);

     tmp1_u16 = (tmp0_u16 >> 2U);
     tmp0_u16 = (tmp0_u16 ^ tmp1_u16);

     tmp1_u16 = (tmp0_u16 >> 1U);
     tmp0_u16 = (tmp0_u16 ^ tmp1_u16);

     tmp0_u16  = (tmp0_u16 & 0x1U);
     res_b = (boolean)((tmp0_u16 == 0u) ? TRUE : FALSE);

     return (res_b);
}
#endif

#ifndef BFX_PRV_TSTPARITYEVEN_U32_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u32_u8_Inl(uint32 Data)
{
   uint32 tmp0_u32;
   uint32 tmp1_u32;
   boolean res_b;

    tmp0_u32 = Data;

    tmp1_u32 = (tmp0_u32 >> 16UL);
    tmp0_u32 = (tmp0_u32 ^ tmp1_u32);

    tmp1_u32 = (tmp0_u32 >> 8UL);
    tmp0_u32 = (tmp0_u32 ^ tmp1_u32);

    tmp1_u32 = (tmp0_u32 >> 4UL);
    tmp0_u32 = (tmp0_u32 ^ tmp1_u32);

    tmp1_u32 = (tmp0_u32 >> 2UL);
    tmp0_u32 = (tmp0_u32 ^ tmp1_u32);

    tmp1_u32 = (tmp0_u32 >> 1UL);
    tmp0_u32 = (tmp0_u32 ^ tmp1_u32);

    tmp0_u32  = (tmp0_u32 & 0x1UL);
    res_b = (boolean)((tmp0_u32 == 0uL) ? TRUE : FALSE);

    return (res_b);
}
#endif

#ifndef BFX_PRV_TSTPARITYEVEN_U8_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u8_u8_Inl(uint8 Data)
{
   uint8 tmp0_u8;
   uint8 tmp1_u8;
   boolean res_b;

    tmp0_u8 = Data;

    tmp1_u8 = (tmp0_u8 >> 4U);
    tmp0_u8 = (tmp0_u8 ^ tmp1_u8);

    tmp1_u8 = (tmp0_u8 >> 2U);
    tmp0_u8 = (tmp0_u8 ^ tmp1_u8);

    tmp1_u8 = (tmp0_u8 >> 1U);
    tmp0_u8 = (tmp0_u8 ^ tmp1_u8);

    tmp0_u8  = (tmp0_u8 & 0x1U);
    res_b = (boolean)((tmp0_u8 == 0u) ? TRUE : FALSE);

    return (res_b);
}
#endif

#ifndef BFX_PRV_TSTPARITYEVEN_U64_U8_INL_REMAPPED
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u64_u8_Inl(Bfx_uint64 Data)
{
        Bfx_uint64 tmp0_u64;
        Bfx_uint64 tmp1_u64;
        boolean res_b;

        tmp0_u64 = Data;

        tmp1_u64 = (tmp0_u64 >> 32ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp1_u64 = (tmp0_u64 >> 16ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp1_u64 = (tmp0_u64 >> 8ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp1_u64 = (tmp0_u64 >> 4ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp1_u64 = (tmp0_u64 >> 2ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp1_u64 = (tmp0_u64 >> 1ULL);
        tmp0_u64 = (tmp0_u64 ^ tmp1_u64);

        tmp0_u64  = (tmp0_u64 & 0x1ULL);
        res_b = (boolean)((tmp0_u64 == 0uLL) ? TRUE : FALSE);

        return (res_b);
}
#endif

#endif
