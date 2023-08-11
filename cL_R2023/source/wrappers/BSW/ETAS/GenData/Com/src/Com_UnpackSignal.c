

#include "Com_Prv.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
Com_SigMaxType Com_UnpackSignal(
                            uint8                       Endianess,
                            Com_BitpositionType         Bit_Pos,
                            Com_BitsizeType             Bitsize,
                            const uint8 *               Src_Buf,
                            boolean                     IsSigned
                               )
{

    Com_SigMaxType      a_data;
    PduLengthType       ByteNo;
    uint16_least        Bits_left;
    uint16_least        Total_BitsCopied;
    uint8_least         BitOffsetInByte;

    ByteNo          = (PduLengthType)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8_least)(Bit_Pos % 8u);

    a_data = (Com_SigMaxType)(*(Src_Buf + ByteNo) >> BitOffsetInByte);

    if (Bitsize >= (8u - BitOffsetInByte))
    {

        Total_BitsCopied = (uint16_least)(8u - BitOffsetInByte);
    }
    else
    {

        a_data = a_data & (uint8)(~(uint8)(0xFFu << Bitsize));
        Total_BitsCopied = Bitsize;
    }

    while (Total_BitsCopied < Bitsize)
    {
        Bits_left = Bitsize - Total_BitsCopied;

        if(Endianess != COM_BIGENDIAN)
        {
            ByteNo++;
        }
        else
        {
            ByteNo--;
        }

        if(Bits_left >= 8u)
        {

            a_data |= (((Com_SigMaxType)(*(Src_Buf + ByteNo))) << Total_BitsCopied);

            Total_BitsCopied = Total_BitsCopied + 8u;
        }
        else
        {

            a_data |=
            (((Com_SigMaxType)(*(Src_Buf + ByteNo) & ((uint8)(0xFFu >> (8u - Bits_left))))) << Total_BitsCopied);

            Total_BitsCopied = Total_BitsCopied + Bits_left;
        }
    }

    if ((IsSigned) && ((a_data >> (Bitsize - COM_ONE)) != COM_ZERO))
    {
        a_data = Com_PerformSignExtension(a_data, Bitsize);
    }

    return(a_data);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint32 Com_UnpackOpaqueSignal(Com_BitpositionType Bit_Pos, Com_BitsizeType SignalLength, const uint8 * Src_Buf)
{
    uint16_least        ByteNo;
    uint32              a_data;

    a_data = COM_ZERO;

    ByteNo = (Bit_Pos >> 3u);

    while (SignalLength > COM_ZERO)
    {
        a_data = (uint32)( a_data << 8u) | (uint32)(*(Src_Buf + ByteNo));
        ByteNo ++;
        SignalLength--;
    }

    return(a_data);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined (COM_RXSIG_FLOAT64SUPP ) || defined(COM_RXGRPSIG_FLOAT64SUPP)

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
float64 Com_UnPackFloatSignal(uint8 Endianess, Com_BitpositionType Bit_Pos, const uint8 * Src_Buf)
{

    float64             Dest_Buf_f64;
    PduLengthType       ByteNo;
    uint8_least         BitOffsetInByte;
    uint8_least         index_uo;
    uint8               destdata_u8[8] = {0u,0u,0u,0u,0u,0u,0u,0u};

    ByteNo = (PduLengthType)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8)(Bit_Pos % 8u);

    if(BitOffsetInByte == COM_ZERO)
    {
        if(Endianess == COM_LITTLEENDIAN)
        {

            (void)rba_BswSrv_MemCopy( (void *)destdata_u8, (const void *)(Src_Buf+ByteNo), COM_F64_SIZE_IN_BYTES );

        }
        else
        {
            for(index_uo = COM_ZERO; index_uo < COM_F64_SIZE_IN_BYTES; index_uo++)
            {
                destdata_u8[index_uo] = *(Src_Buf+ByteNo);
                ByteNo--;
            }
        }
    }
    else
    {
        if(Endianess == COM_LITTLEENDIAN)
        {

            for(index_uo = COM_ZERO; index_uo < COM_F64_SIZE_IN_BYTES; index_uo++)
            {

                destdata_u8[index_uo] = (uint8)((uint8)(*(Src_Buf+ByteNo)) >> BitOffsetInByte) |
                                        (uint8)((*(Src_Buf+(ByteNo + COM_ONE))) << (8u-BitOffsetInByte));

                ByteNo++;
            }
        }
        else
        {

            for(index_uo = COM_ZERO; index_uo < COM_F64_SIZE_IN_BYTES; index_uo++)
            {

                destdata_u8[index_uo] = (uint8)((*(Src_Buf+ByteNo)) >> BitOffsetInByte) |
                                        (uint8)((*(Src_Buf+(ByteNo - COM_ONE))) << (8u-BitOffsetInByte));

                ByteNo--;
            }
        }
    }

    (void)rba_BswSrv_MemCopy( (void *)&Dest_Buf_f64, (const void *)destdata_u8, COM_F64_SIZE_IN_BYTES );

    return(Dest_Buf_f64);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

