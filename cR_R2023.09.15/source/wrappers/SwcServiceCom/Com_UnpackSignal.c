#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(Com_SigMaxType, COM_CODE) Com_UnpackSignal( VAR(uint8, AUTOMATIC)                    Endianess
   ,     VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)          Bitsize
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf
   ,     VAR(boolean, AUTOMATIC)                  IsSigned )
{

   VAR(Com_SigMaxType, AUTOMATIC)   a_data;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)    ByteNo;
   VAR(uint16_least, AUTOMATIC)     Bits_left;
   VAR(uint16_least, AUTOMATIC)     Total_BitsCopied;
   VAR(uint8_least, AUTOMATIC)      BitOffsetInByte;

    ByteNo          = (Type_SwcServiceCom_tLengthPdu)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8_least)(Bit_Pos % 8u);

    a_data = (Com_SigMaxType)(*(Src_Buf + ByteNo) >> BitOffsetInByte);

   if(Bitsize >= (8u - BitOffsetInByte))
   {

        Total_BitsCopied = (uint16_least)(8u - BitOffsetInByte);
   }
   else{

        a_data = a_data & (uint8)(~(uint8)(0xFFu << Bitsize));
        Total_BitsCopied = Bitsize;
   }

   while(Total_BitsCopied < Bitsize)
   {
        Bits_left = Bitsize - Total_BitsCopied;

        if(Endianess != COM_BIGENDIAN)
        {
            ByteNo++;
        }
        else{
            ByteNo--;
        }

        if(Bits_left >= 8u)
        {

            a_data |= (((Com_SigMaxType)(*(Src_Buf + ByteNo))) << Total_BitsCopied);

            Total_BitsCopied = Total_BitsCopied + 8u;
        }
        else{

            a_data |=
            ((Com_SigMaxType)(*(Src_Buf + ByteNo) & ((uint8)(0xFFu >> (8u - Bits_left)))) << Total_BitsCopied);

            Total_BitsCopied = Total_BitsCopied + Bits_left;
        }
   }

   if(( IsSigned ) &&
        ((a_data & ((Com_SigMaxType)0x1u << (Bitsize - 1))) != 0u))
   {
        a_data = Com_PerformSignExtension(a_data, Bitsize);
   }

    return(a_data);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint32, COM_CODE) Com_UnpackOpaqueSignal(VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)          SignalLength
   ,     P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf)
{
   VAR(uint16_least, AUTOMATIC) ByteNo;
   VAR(uint32, AUTOMATIC) a_data;

    a_data = 0x00;

    ByteNo = (Bit_Pos >> 3u);

   while(SignalLength > 0)
   {
        a_data = (uint32)( a_data << 8u) | (uint32)(*(Src_Buf + ByteNo));
        ByteNo ++;
        SignalLength--;
   }

    return(a_data);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if defined (COM_RXSIG_FLOAT64SUPP ) || defined(COM_RXGRPSIG_FLOAT64SUPP)
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(float64, COM_CODE) Com_UnPackFloatSignal(VAR(uint8, AUTOMATIC) Endianess, VAR(Com_BitpositionType, AUTOMATIC) Bit_Pos
   ,     P2CONST(uint8,AUTOMATIC,COM_APPL_DATA) Src_Buf)
{

   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) NoofBytes;
   VAR(uint8_least, AUTOMATIC) BitOffsetInByte;
   VAR(float64, AUTOMATIC) Dest_Buf_f64;
   VAR(uint8, AUTOMATIC) destdata_u8[8] = {0,0,0,0,0,0,0,0};

    NoofBytes = 8;
    ByteNo = Bit_Pos >> 3u;
    BitOffsetInByte = (uint8)(Bit_Pos % 8u);

   if(BitOffsetInByte ==  (uint8_least)0)
   {
        if(Endianess == COM_LITTLEENDIAN)
        {

            (void)LibAutosar_vptrMemCopy( (void *)destdata_u8, (const void *)(Src_Buf+ByteNo), NoofBytes );

        }
        else{
            uint8 index_u8;
            for(index_u8 = 0 ; index_u8 < NoofBytes; index_u8++)
            {
                destdata_u8[index_u8] = *(Src_Buf+ByteNo);
                ByteNo--;
            }
        }
   }
   else{
        uint16_least index_u16;
        if(Endianess == COM_LITTLEENDIAN)
        {

            for(index_u16 = 0; index_u16 < NoofBytes; index_u16++)
            {

                destdata_u8[index_u16] = (uint8)((uint8)(*(Src_Buf+ByteNo)) >> BitOffsetInByte) | (uint8)((*(Src_Buf+(ByteNo + 1u))) << (8u-BitOffsetInByte));

                ByteNo++;
            }
        }
        else{

            for(index_u16 = 0; index_u16 < NoofBytes; index_u16++)
            {

                destdata_u8[index_u16] = (uint8)((*(Src_Buf+ByteNo)) >> BitOffsetInByte) | (uint8)((*(Src_Buf+(ByteNo -1u))) << (8u-BitOffsetInByte));

                ByteNo--;
            }
        }
   }

    (void)LibAutosar_vptrMemCopy( (void *)&Dest_Buf_f64, (const void *)destdata_u8, NoofBytes );

    return(Dest_Buf_f64);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

