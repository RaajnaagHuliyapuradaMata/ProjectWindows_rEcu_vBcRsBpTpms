#define SRVLIBS

#include "Std_Types.hpp"

#include "Bfx.hpp"

//TBD: Remove inline wrapper functions/macros
#define BFX_START_SEC_CODE
#include "Bfx_MemMap.hpp"
boolean Bfx_GetBit_u16u8_u8        (uint16  Data,     uint8  BitPn                                       ){return Bfx_Lok_GetBit_u16u8_u8_Inl        (Data,     BitPn                        );}
boolean Bfx_GetBit_u32u8_u8        (uint32  Data,     uint8  BitPn                                       ){return Bfx_Lok_GetBit_u32u8_u8_Inl        (Data,     BitPn                        );}
boolean Bfx_GetBit_u8u8_u8         (uint8   Data,     uint8  BitPn                                       ){return Bfx_Lok_GetBit_u8u8_u8_Inl         (Data,     BitPn                        );}
boolean Bfx_TstBitLnMask_u16u16_u8 (uint16  Data,     uint16 Mask                                        ){return Bfx_Lok_TstBitLnMask_u16u16_u8_Inl (Data,     Mask                         );}
boolean Bfx_TstBitLnMask_u32u32_u8 (uint32  Data,     uint32 Mask                                        ){return Bfx_Lok_TstBitLnMask_u32u32_u8_Inl (Data,     Mask                         );}
boolean Bfx_TstBitLnMask_u8u8_u8   (uint8   Data,     uint8  Mask                                        ){return Bfx_Lok_TstBitLnMask_u8u8_u8_Inl   (Data,     Mask                         );}
boolean Bfx_TstBitMask_u16u16_u8   (uint16  Data,     uint16 Mask                                        ){return Bfx_Lok_TstBitMask_u16u16_u8_Inl   (Data,     Mask                         );}
boolean Bfx_TstBitMask_u32u32_u8   (uint32  Data,     uint32 Mask                                        ){return Bfx_Lok_TstBitMask_u32u32_u8_Inl   (Data,     Mask                         );}
boolean Bfx_TstBitMask_u8u8_u8     (uint8   Data,     uint8  Mask                                        ){return Bfx_Lok_TstBitMask_u8u8_u8_Inl     (Data,     Mask                         );}
uint16  Bfx_GetBits_u16u8u8_u16    (uint16  Data,     uint8  BitStartPn, uint8   BitLn                   ){return Bfx_Lok_GetBits_u16u8u8_u16_Inl    (Data,     BitStartPn, BitLn            );}
uint32  Bfx_GetBits_u32u8u8_u32    (uint32  Data,     uint8  BitStartPn, uint8   BitLn                   ){return Bfx_Lok_GetBits_u32u8u8_u32_Inl    (Data,     BitStartPn, BitLn            );}
uint8   Bfx_GetBits_u8u8u8_u8      (uint8   Data,     uint8  BitStartPn, uint8   BitLn                   ){return Bfx_Lok_GetBits_u8u8u8_u8_Inl      (Data,     BitStartPn, BitLn            );}
void    Bfx_ClrBit_u16u8           (uint16* Data,     uint8  BitPn                                       ){       Bfx_Lok_ClrBit_u16u8_Inl           (Data,     BitPn                        );}
void    Bfx_ClrBit_u32u8           (uint32* Data,     uint8  BitPn                                       ){       Bfx_Lok_ClrBit_u32u8_Inl           (Data,     BitPn                        );}
void    Bfx_ClrBit_u8u8            (uint8*  Data,     uint8  BitPn                                       ){       Bfx_Lok_ClrBit_u8u8_Inl            (Data,     BitPn                        );}
void    Bfx_ClrBitMask_u16u16      (uint16* Data,     uint16 Mask                                        ){       Bfx_Lok_ClrBitMask_u16u16_Inl      (Data,     Mask                         );}
void    Bfx_ClrBitMask_u32u32      (uint32* Data,     uint32 Mask                                        ){       Bfx_Lok_ClrBitMask_u32u32_Inl      (Data,     Mask                         );}
void    Bfx_ClrBitMask_u8u8        (uint8*  Data,     uint8  Mask                                        ){       Bfx_Lok_ClrBitMask_u8u8_Inl        (Data,     Mask                         );}
void    Bfx_CopyBit_u16u8u16u8     (uint16* DestData, uint8  DestPn,     uint16  SrcData, uint8  SrcPn   ){       Bfx_Lok_CopyBit_u16u8u16u8_Inl     (DestData, DestPn,     SrcData, SrcPn   );}
void    Bfx_CopyBit_u32u8u32u8     (uint32* DestData, uint8  DestPn,     uint32  SrcData, uint8  SrcPn   ){       Bfx_Lok_CopyBit_u32u8u32u8_Inl     (DestData, DestPn,     SrcData, SrcPn   );}
void    Bfx_CopyBit_u8u8u8u8       (uint8*  DestData, uint8  DestPn,     uint8   SrcData, uint8  SrcPn   ){       Bfx_Lok_CopyBit_u8u8u8u8_Inl       (DestData, DestPn,     SrcData, SrcPn   );}
void    Bfx_PutBit_u16u8u8         (uint16* Data,     uint8  BitPn,      boolean Value                   ){       Bfx_Lok_PutBit_u16u8u8_Inl         (Data,     BitPn,      Value            );}
void    Bfx_PutBit_u32u8u8         (uint32* Data,     uint8  BitPn,      boolean Value                   ){       Bfx_Lok_PutBit_u32u8u8_Inl         (Data,     BitPn,      Value            );}
void    Bfx_PutBit_u8u8u8          (uint8*  Data,     uint8  BitPn,      boolean Value                   ){       Bfx_Lok_PutBit_u8u8u8_Inl          (Data,     BitPn,      Value            );}
void    Bfx_PutBits_u16u8u8u16     (uint16* Data,     uint8  BitStartPn, uint8   BitLn,   uint16 Pattern ){       Bfx_Lok_PutBits_u16u8u8u16_Inl     (Data,     BitStartPn, BitLn,   Pattern );}
void    Bfx_PutBits_u32u8u8u32     (uint32* Data,     uint8  BitStartPn, uint8   BitLn,   uint32 Pattern ){       Bfx_Lok_PutBits_u32u8u8u32_Inl     (Data,     BitStartPn, BitLn,   Pattern );}
void    Bfx_PutBits_u8u8u8u8       (uint8*  Data,     uint8  BitStartPn, uint8   BitLn,   uint8  Pattern ){       Bfx_Lok_PutBits_u8u8u8u8_Inl       (Data,     BitStartPn, BitLn,   Pattern );}
void    Bfx_PutBitsMask_u16u16u16  (uint16* Data,     uint16 Pattern,    uint16  Mask                    ){       Bfx_Lok_PutBitsMask_u16u16u16_Inl  (Data,     Pattern,    Mask             );}
void    Bfx_PutBitsMask_u32u32u32  (uint32* Data,     uint32 Pattern,    uint32  Mask                    ){       Bfx_Lok_PutBitsMask_u32u32u32_Inl  (Data,     Pattern,    Mask             );}
void    Bfx_PutBitsMask_u8u8u8     (uint8*  Data,     uint8  Pattern,    uint8   Mask                    ){       Bfx_Lok_PutBitsMask_u8u8u8_Inl     (Data,     Pattern,    Mask             );}
void    Bfx_RotBitLt_u16u8         (uint16* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitLt_u16u8_Inl         (Data,     ShiftCnt                     );}
void    Bfx_RotBitLt_u32u8         (uint32* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitLt_u32u8_Inl         (Data,     ShiftCnt                     );}
void    Bfx_RotBitLt_u8u8          (uint8*  Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitLt_u8u8_Inl          (Data,     ShiftCnt                     );}
void    Bfx_RotBitRt_u16u8         (uint16* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitRt_u16u8_Inl         (Data,     ShiftCnt                     );}
void    Bfx_RotBitRt_u32u8         (uint32* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitRt_u32u8_Inl         (Data,     ShiftCnt                     );}
void    Bfx_RotBitRt_u8u8          (uint8*  Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_RotBitRt_u8u8_Inl          (Data,     ShiftCnt                     );}
void    Bfx_SetBit_u16u8           (uint16* Data,     uint8  BitPn                                       ){       Bfx_Lok_SetBit_u16u8_Inl           (Data,     BitPn                        );}
void    Bfx_SetBit_u32u8           (uint32* Data,     uint8  BitPn                                       ){       Bfx_Lok_SetBit_u32u8_Inl           (Data,     BitPn                        );}
void    Bfx_SetBit_u8u8            (uint8*  Data,     uint8  BitPn                                       ){       Bfx_Lok_SetBit_u8u8_Inl            (Data,     BitPn                        );}
void    Bfx_SetBitMask_u16u16      (uint16* Data,     uint16 Mask                                        ){       Bfx_Lok_SetBitMask_u16u16_Inl      (Data,     Mask                         );}
void    Bfx_SetBitMask_u32u32      (uint32* Data,     uint32 Mask                                        ){       Bfx_Lok_SetBitMask_u32u32_Inl      (Data,     Mask                         );}
void    Bfx_SetBitMask_u8u8        (uint8*  Data,     uint8  Mask                                        ){       Bfx_Lok_SetBitMask_u8u8_Inl        (Data,     Mask                         );}
void    Bfx_SetBits_u16u8u8u8      (uint16* Data,     uint8  BitStartPn, uint8   BitLn,   uint8  Status  ){       Bfx_Lok_SetBits_u16u8u8u8_Inl      (Data,     BitStartPn, BitLn,   Status  );}
void    Bfx_SetBits_u32u8u8u8      (uint32* Data,     uint8  BitStartPn, uint8   BitLn,   uint8  Status  ){       Bfx_Lok_SetBits_u32u8u8u8_Inl      (Data,     BitStartPn, BitLn,   Status  );}
void    Bfx_SetBits_u8u8u8u8       (uint8*  Data,     uint8  BitStartPn, uint8   BitLn,   uint8  Status  ){       Bfx_Lok_SetBits_u8u8u8u8_Inl       (Data,     BitStartPn, BitLn,   Status  );}
void    Bfx_ShiftBitLt_u16u8       (uint16* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitLt_u16u8_Inl       (Data,     ShiftCnt                     );}
void    Bfx_ShiftBitLt_u32u8       (uint32* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitLt_u32u8_Inl       (Data,     ShiftCnt                     );}
void    Bfx_ShiftBitLt_u8u8        (uint8*  Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitLt_u8u8_Inl        (Data,     ShiftCnt                     );}
void    Bfx_ShiftBitRt_u16u8       (uint16* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitRt_u16u8_Inl       (Data,     ShiftCnt                     );}
void    Bfx_ShiftBitRt_u32u8       (uint32* Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitRt_u32u8_Inl       (Data,     ShiftCnt                     );}
void    Bfx_ShiftBitRt_u8u8        (uint8*  Data,     uint8  ShiftCnt                                    ){       Bfx_Lok_ShiftBitRt_u8u8_Inl        (Data,     ShiftCnt                     );}
void    Bfx_ToggleBitMask_u16u16   (uint16* Data,     uint16 Mask                                        ){       Bfx_Lok_ToggleBitMask_u16u16_Inl   (Data,     Mask                         );}
void    Bfx_ToggleBitMask_u32u32   (uint32* Data,     uint32 Mask                                        ){       Bfx_Lok_ToggleBitMask_u32u32_Inl   (Data,     Mask                         );}
void    Bfx_ToggleBitMask_u8u8     (uint8*  Data,     uint8  Mask                                        ){       Bfx_Lok_ToggleBitMask_u8u8_Inl     (Data,     Mask                         );}
void    Bfx_ToggleBits_u16         (uint16* Data                                                         ){       Bfx_Lok_ToggleBits_u16_Inl         (Data                                   );}
void    Bfx_ToggleBits_u32         (uint32* Data                                                         ){       Bfx_Lok_ToggleBits_u32_Inl         (Data                                   );}
void    Bfx_ToggleBits_u8          (uint8*  Data                                                         ){       Bfx_Lok_ToggleBits_u8_Inl          (Data                                   );}
#define BFX_STOP_SEC_CODE
#include "Bfx_MemMap.hpp"

