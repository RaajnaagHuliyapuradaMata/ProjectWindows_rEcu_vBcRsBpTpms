#ifndef BFX_BIT_INL_H
#define BFX_BIT_INL_H

//TBD: Optimize execution time
LOCAL_INLINE void Bfx_Lok_ClrBit_u16u8_Inl(uint16* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBit_u32u8_Inl(uint32* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBit_u8u8_Inl(uint8* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_ClrBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_CopyBit_u16u8u16u8_Inl(uint16* DestData, uint8 DestPn, uint16 SrcData, uint8 SrcPn);
LOCAL_INLINE void Bfx_Lok_CopyBit_u32u8u32u8_Inl(uint32* DestData, uint8 DestPn, uint32 SrcData, uint8 SrcPn);
LOCAL_INLINE void Bfx_Lok_CopyBit_u8u8u8u8_Inl(uint8* DestData, uint8 DestPn, uint8 SrcData, uint8 SrcPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u16u8_u8_Inl(uint16 Data, uint8 BitPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u32u8_u8_Inl(uint32 Data, uint8 BitPn);
LOCAL_INLINE boolean Bfx_Lok_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn);
LOCAL_INLINE uint16 Bfx_Lok_GetBits_u16u8u8_u16_Inl(uint16 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE uint32 Bfx_Lok_GetBits_u32u8u8_u32_Inl(uint32 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE uint8 Bfx_Lok_GetBits_u8u8u8_u8_Inl(uint8 Data, uint8 BitStartPn, uint8 BitLn);
LOCAL_INLINE void Bfx_Lok_PutBit_u16u8u8_Inl(uint16* Data, uint8 BitPn, boolean Value);
LOCAL_INLINE void Bfx_Lok_PutBit_u32u8u8_Inl(uint32* Data, uint8 BitPn, boolean Value);
LOCAL_INLINE void Bfx_Lok_PutBit_u8u8u8_Inl(uint8* Data, uint8 BitPn, boolean Value);
LOCAL_INLINE void Bfx_Lok_PutBits_u16u8u8u16_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint16 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBits_u32u8u8u32_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u16u16u16_Inl(uint16* Data, uint16 Pattern, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u32u32u32_Inl(uint32* Data, uint32 Pattern, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_PutBitsMask_u8u8u8_Inl(uint8* Data, uint8 Pattern, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_RotBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_SetBit_u16u8_Inl(uint16* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBit_u32u8_Inl(uint32* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBit_u8u8_Inl(uint8* Data, uint8 BitPn);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_SetBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_SetBits_u16u8u8u8_Inl(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_SetBits_u32u8u8u8_Inl(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_SetBits_u8u8u8u8_Inl(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitLt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u16u8_Inl(uint16* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u32u8_Inl(uint32* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ShiftBitRt_u8u8_Inl(uint8* Data, uint8 ShiftCnt);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u16u16_Inl(uint16* Data, uint16 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u32u32_Inl(uint32* Data, uint32 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBitMask_u8u8_Inl(uint8* Data, uint8 Mask);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u16_Inl(uint16* Data);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u32_Inl(uint32* Data);
LOCAL_INLINE void Bfx_Lok_ToggleBits_u8_Inl(uint8* Data);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u16u16_u8_Inl(uint16 Data, uint16 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u32u32_u8_Inl(uint32 Data, uint32 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u8u8_u8_Inl(uint8 Data, uint8 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u16u16_u8_Inl(uint16 Data, uint16 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u32u32_u8_Inl(uint32 Data, uint32 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u8u8_u8_Inl(uint8 Data, uint8 Mask);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u16_u8_Inl(uint16 Data);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u32_u8_Inl(uint32 Data);
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u8_u8_Inl(uint8 Data);

LOCAL_INLINE boolean Bfx_Lok_GetBit_u16u8_u8_Inl        (uint16  Data,     uint8  BitPn                                       ){return (        (((Data              ) & ((uint16) (1uL << BitPn))) != 0u));}
LOCAL_INLINE boolean Bfx_Lok_GetBit_u32u8_u8_Inl        (uint32  Data,     uint8  BitPn                                       ){return (         ((Data              ) & ((uint32) (1uL << BitPn))) != 0uL);}
LOCAL_INLINE boolean Bfx_Lok_GetBit_u8u8_u8_Inl         (uint8   Data,     uint8  BitPn                                       ){return (         ((Data              ) & ((uint8)  (1uL << BitPn))) != 0u);}
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u16u16_u8_Inl (uint16  Data,     uint16 Mask                                        ){return (          (Data                & Mask) != 0uL);}
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u32u32_u8_Inl (uint32  Data,     uint32 Mask                                        ){return (          (Data                & Mask) != 0uL);}
LOCAL_INLINE boolean Bfx_Lok_TstBitLnMask_u8u8_u8_Inl   (uint8   Data,     uint8  Mask                                        ){return (          (Data                & Mask) != 0uL);}
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u16u16_u8_Inl   (uint16  Data,     uint16 Mask                                        ){return (          (Data                & Mask) == (Mask));}
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u32u32_u8_Inl   (uint32  Data,     uint32 Mask                                        ){return (          (Data                & Mask) == (Mask));}
LOCAL_INLINE boolean Bfx_Lok_TstBitMask_u8u8_u8_Inl     (uint8   Data,     uint8  Mask                                        ){return (          (Data                & Mask) == (Mask));}
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u16_u8_Inl   (uint16  Data                                                         ){return (Bfx_Lok_TstParityEven_u32_u8_Inl (Data));}
LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u8_u8_Inl    (uint8   Data                                                         ){return (Bfx_Lok_TstParityEven_u32_u8_Inl(Data));}
LOCAL_INLINE uint16  Bfx_Lok_GetBits_u16u8u8_u16_Inl    (uint16  Data,     uint8  BitStartPn, uint8   BitLn                   ){return ((uint16) ((Data >> BitStartPn) & (BFX_MAXUINT16_U >> (16uL - BitLn))));}
LOCAL_INLINE uint32  Bfx_Lok_GetBits_u32u8u8_u32_Inl    (uint32  Data,     uint8  BitStartPn, uint8   BitLn                   ){return (          (Data >> BitStartPn) & (BFX_MAXUINT32_U >> (32uL - BitLn)));}
LOCAL_INLINE uint8   Bfx_Lok_GetBits_u8u8u8_u8_Inl      (uint8   Data,     uint8  BitStartPn, uint8   BitLn                   ){return ((uint8)  ((Data >> BitStartPn) & (BFX_MAXUINT8_U  >> (8uL - BitLn))));}
LOCAL_INLINE void    Bfx_Lok_ClrBit_u16u8_Inl           (uint16* Data,     uint8  BitPn                                       ){*Data  &=  ((uint16) (~(uint16) (1uL << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_ClrBit_u32u8_Inl           (uint32* Data,     uint8  BitPn                                       ){*Data  &=  ((uint32) (         ~(1uL << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_ClrBit_u8u8_Inl            (uint8*  Data,     uint8  BitPn                                       ){*Data  &=  ((uint8)  (~(uint8)  (1u  << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_ClrBitMask_u16u16_Inl      (uint16* Data,     uint16 Mask                                        ){*Data  &=  ((uint16) (~Mask));}
LOCAL_INLINE void    Bfx_Lok_ClrBitMask_u32u32_Inl      (uint32* Data,     uint32 Mask                                        ){*Data  &=  ((uint32) (~Mask));}
LOCAL_INLINE void    Bfx_Lok_ClrBitMask_u8u8_Inl        (uint8*  Data,     uint8  Mask                                        ){*Data  &=  ((uint8)  (~Mask));}
LOCAL_INLINE void    Bfx_Lok_CopyBit_u16u8u16u8_Inl     (uint16* DestData, uint8  DestPn,     uint16  SrcData, uint8  SrcPn   ){Bfx_Lok_PutBit_u16u8u8_Inl       (DestData, DestPn, Bfx_Lok_GetBit_u16u8_u8_Inl (SrcData, SrcPn));}
LOCAL_INLINE void    Bfx_Lok_CopyBit_u32u8u32u8_Inl     (uint32* DestData, uint8  DestPn,     uint32  SrcData, uint8  SrcPn   ){Bfx_Lok_PutBit_u32u8u8_Inl       (DestData, DestPn, Bfx_Lok_GetBit_u32u8_u8_Inl (SrcData, SrcPn));}
LOCAL_INLINE void    Bfx_Lok_CopyBit_u8u8u8u8_Inl       (uint8*  DestData, uint8  DestPn,     uint8   SrcData, uint8  SrcPn   ){Bfx_Lok_PutBit_u8u8u8_Inl        (DestData, DestPn, Bfx_Lok_GetBit_u8u8_u8_Inl  (SrcData, SrcPn));}
LOCAL_INLINE void    Bfx_Lok_PutBit_u16u8u8_Inl         (uint16* Data,     uint8  BitPn,      boolean Value                   ){*Data   = ((*Data  & ((uint16) ~(1uL << BitPn))) | ((uint16) ((uint16)((Value)? 1u : 0u) << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_PutBit_u32u8u8_Inl         (uint32* Data,     uint8  BitPn,      boolean Value                   ){*Data   = ((*Data  & ((uint32) ~(1uL << BitPn))) | ((uint32) ((uint32)((Value)? 1u : 0u) << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_PutBit_u8u8u8_Inl          (uint8*  Data,     uint8  BitPn,      boolean Value                   ){*Data   = ((*Data  & ((uint8)  ~(1uL << BitPn))) | ((uint8)  (        ((Value)? 1u : 0u) << BitPn)));}
LOCAL_INLINE void    Bfx_Lok_PutBits_u16u8u8u16_Inl     (uint16* Data,     uint8  BitStartPn, uint8   BitLn,   uint16 Pattern ){*Data   = (((uint16) (~(uint16) ((BFX_MAXUINT16_U >> (16uL - BitLn)) << BitStartPn))) & *Data) | (uint16) (((BFX_MAXUINT16_U >> (16uL - BitLn)) & Pattern) << BitStartPn);}
LOCAL_INLINE void    Bfx_Lok_PutBits_u32u8u8u32_Inl     (uint32* Data,     uint8  BitStartPn, uint8   BitLn,   uint32 Pattern ){*Data   = (((uint32) (~(uint32) ((BFX_MAXUINT32_U >> (32uL - BitLn)) << BitStartPn))) & *Data) | (uint32) (((BFX_MAXUINT32_U >> (32uL - BitLn)) & Pattern) << BitStartPn);}
LOCAL_INLINE void    Bfx_Lok_PutBits_u8u8u8u8_Inl       (uint8*  Data,     uint8  BitStartPn, uint8   BitLn,   uint8  Pattern ){*Data   = (((uint8)  (~(uint8)  ((BFX_MAXUINT8_U  >> ( 8uL - BitLn)) << BitStartPn))) & *Data) | (uint8)  (((BFX_MAXUINT8_U  >> (8uL  - BitLn)) & Pattern) << BitStartPn);}
LOCAL_INLINE void    Bfx_Lok_PutBitsMask_u16u16u16_Inl  (uint16* Data,     uint16 Pattern,    uint16  Mask                    ){*Data   =  (*Data  & ((uint16) ~(Mask))) | (Pattern & Mask);}
LOCAL_INLINE void    Bfx_Lok_PutBitsMask_u32u32u32_Inl  (uint32* Data,     uint32 Pattern,    uint32  Mask                    ){*Data   =  (*Data  & (~Mask)) | (Pattern & Mask);}
LOCAL_INLINE void    Bfx_Lok_PutBitsMask_u8u8u8_Inl     (uint8*  Data,     uint8  Pattern,    uint8   Mask                    ){*Data   =  (*Data  & ((uint8)  ~(Mask))) | (Pattern & Mask);}
LOCAL_INLINE void    Bfx_Lok_RotBitLt_u16u8_Inl         (uint16* Data,     uint8  ShiftCnt                                    ){*Data   =  ((uint16) (*Data << ShiftCnt) | (uint16) (*Data >> (16 - ShiftCnt)));}
LOCAL_INLINE void    Bfx_Lok_RotBitLt_u32u8_Inl         (uint32* Data,     uint8  ShiftCnt                                    ){*Data   = (*Data << ShiftCnt) | (*Data >> (32 - ShiftCnt));}
LOCAL_INLINE void    Bfx_Lok_RotBitLt_u8u8_Inl          (uint8*  Data,     uint8  ShiftCnt                                    ){*Data   =  ((uint8)  (*Data << ShiftCnt) | (uint8)  (*Data >> (8  - ShiftCnt)));}
LOCAL_INLINE void    Bfx_Lok_RotBitRt_u16u8_Inl         (uint16* Data,     uint8  ShiftCnt                                    ){*Data   =  ((uint16) (*Data >> ShiftCnt) | (uint16) (*Data << (16 - ShiftCnt)));}
LOCAL_INLINE void    Bfx_Lok_RotBitRt_u32u8_Inl         (uint32* Data,     uint8  ShiftCnt                                    ){*Data   = (*Data >> ShiftCnt) | (*Data << (32 - ShiftCnt));}
LOCAL_INLINE void    Bfx_Lok_RotBitRt_u8u8_Inl          (uint8*  Data,     uint8  ShiftCnt                                    ){*Data   =  ((uint8)  (*Data >> ShiftCnt) | (uint8)  (*Data << (8  - ShiftCnt)));}
LOCAL_INLINE void    Bfx_Lok_SetBit_u16u8_Inl           (uint16* Data,     uint8  BitPn                                       ){*Data  |=  ((uint16) (1uL << BitPn));}
LOCAL_INLINE void    Bfx_Lok_SetBit_u32u8_Inl           (uint32* Data,     uint8  BitPn                                       ){*Data  |=  ((uint32) (1uL << BitPn));}
LOCAL_INLINE void    Bfx_Lok_SetBit_u8u8_Inl            (uint8*  Data,     uint8  BitPn                                       ){*Data  |=  ((uint8)  (1uL << BitPn));}
LOCAL_INLINE void    Bfx_Lok_SetBitMask_u16u16_Inl      (uint16* Data,     uint16 Mask                                        ){*Data  |= Mask;}
LOCAL_INLINE void    Bfx_Lok_SetBitMask_u32u32_Inl      (uint32* Data,     uint32 Mask                                        ){*Data  |= Mask;}
LOCAL_INLINE void    Bfx_Lok_SetBitMask_u8u8_Inl        (uint8*  Data,     uint8  Mask                                        ){*Data  |= Mask;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitLt_u16u8_Inl       (uint16* Data,     uint8  ShiftCnt                                    ){*Data <<= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitLt_u32u8_Inl       (uint32* Data,     uint8  ShiftCnt                                    ){*Data <<= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitLt_u8u8_Inl        (uint8*  Data,     uint8  ShiftCnt                                    ){*Data <<= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitRt_u16u8_Inl       (uint16* Data,     uint8  ShiftCnt                                    ){*Data >>= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitRt_u32u8_Inl       (uint32* Data,     uint8  ShiftCnt                                    ){*Data >>= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ShiftBitRt_u8u8_Inl        (uint8*  Data,     uint8  ShiftCnt                                    ){*Data >>= ShiftCnt;}
LOCAL_INLINE void    Bfx_Lok_ToggleBitMask_u16u16_Inl   (uint16* Data,     uint16 Mask                                        ){*Data  ^= Mask;}
LOCAL_INLINE void    Bfx_Lok_ToggleBitMask_u32u32_Inl   (uint32* Data,     uint32 Mask                                        ){*Data  ^= Mask;}
LOCAL_INLINE void    Bfx_Lok_ToggleBitMask_u8u8_Inl     (uint8*  Data,     uint8  Mask                                        ){*Data  ^= Mask;}
LOCAL_INLINE void    Bfx_Lok_ToggleBits_u16_Inl         (uint16* Data                                                         ){*Data  ^= 0xFFFFu;}
LOCAL_INLINE void    Bfx_Lok_ToggleBits_u32_Inl         (uint32* Data                                                         ){*Data  ^= 0xFFFFFFFFuL;}
LOCAL_INLINE void    Bfx_Lok_ToggleBits_u8_Inl          (uint8*  Data                                                         ){*Data  ^= 0xFFu;}

LOCAL_INLINE void Bfx_Lok_SetBits_u16u8u8u8_Inl(
      uint16* Data
   ,  uint8   BitStartPn
   ,  uint8   BitLn
   ,  uint8 Status
){
   uint16 mask_u16;
   mask_u16 = (uint16) (BFX_MAXUINT16_U >> BitStartPn);
   mask_u16 = (uint16) (mask_u16 << (16u - BitLn));
   mask_u16 = (uint16) (mask_u16 >> (16u - BitStartPn - BitLn));
   *Data |= mask_u16;
   if(
         0
      == Status
   ){
      *Data ^= mask_u16;
   }
}

LOCAL_INLINE void Bfx_Lok_SetBits_u32u8u8u8_Inl(
      uint32* Data
   ,  uint8   BitStartPn
   ,  uint8   BitLn
   ,  uint8   Status
){
   uint32 mask_u32;
   mask_u32 = (uint32) (BFX_MAXUINT32_U >> BitStartPn);
   mask_u32 = (uint32) (mask_u32 << (32u - BitLn));
   mask_u32 = (uint32) (mask_u32 >> (32u - BitStartPn - BitLn));
   *Data |= mask_u32;
   if(
         0
      == Status
   ){
      *Data ^= mask_u32;
   }
}

LOCAL_INLINE void Bfx_Lok_SetBits_u8u8u8u8_Inl(
      uint8* Data
   ,  uint8  BitStartPn
   ,  uint8  BitLn
   ,  uint8  Status
){
   uint8 mask_u8;
   mask_u8 = (uint8) (BFX_MAXUINT8_U >> BitStartPn);
   mask_u8 = (uint8) (mask_u8 << (8u - BitLn));
   mask_u8 = (uint8) (mask_u8 >> (8u - BitStartPn - BitLn));
   *Data |= mask_u8;
   if(
         0
      == Status
   ){
      *Data ^= mask_u8;
   }
}

LOCAL_INLINE boolean Bfx_Lok_TstParityEven_u32_u8_Inl(
   uint32 Data
){
   uint32 tmp_u32        = Data;
   uint32 Parity_Bit_u32 = 1uL;
   while(
         tmp_u32
      >  0uL
   ){
      Parity_Bit_u32 ^= 0x1uL & (tmp_u32);
      tmp_u32         = tmp_u32 >> 1u;
   }
   return (Parity_Bit_u32 > 0uL);
}

#endif
