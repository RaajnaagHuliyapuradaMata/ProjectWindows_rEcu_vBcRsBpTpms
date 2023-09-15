#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_PackSignal( VAR(uint8, AUTOMATIC)                  Endianess
   ,     VAR(Com_BitpositionType, AUTOMATIC)    Bit_Pos
   ,     VAR(Com_BitsizeType, AUTOMATIC)        Bitsize
   ,     VAR(Com_SigMaxType, AUTOMATIC)         Src_Buf
   ,     P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf )
{

   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo;
   VAR(uint16_least, AUTOMATIC)  Total_BitsCopied;
   VAR(uint16_least, AUTOMATIC)  Bits_left;
   VAR(uint8_least, AUTOMATIC)   BitOffsetInByte;
   VAR(uint8_least, AUTOMATIC)   a_data;
   VAR(uint8, AUTOMATIC)         Mask;

   if(Bitsize != COM_SIG_MAX_NO_OF_BITS)
   {
        Src_Buf = Src_Buf & (~(COM_SIG_MAX_DATA << Bitsize));
   }

    ByteNo          = (Type_SwcServiceCom_tLengthPdu)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8_least)(Bit_Pos % 8u);

    a_data = (uint8_least)(Src_Buf << BitOffsetInByte);

   if(Bitsize >= (8u - BitOffsetInByte))
   {

        Mask = (uint8)(~((uint8)(0xFFu << BitOffsetInByte)));
        Total_BitsCopied = (8u - BitOffsetInByte);
   }
   else{

        Mask = (uint8)(~(((1u << Bitsize) - 1u) << BitOffsetInByte));
        Total_BitsCopied = Bitsize;
   }

    *(Dest_Buf+ByteNo) = ((*(Dest_Buf+ByteNo)) & Mask) | (uint8)a_data;

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

        a_data = (uint8_least)(Src_Buf >> Total_BitsCopied);

        if(Bits_left >= 8u)
        {
            *(Dest_Buf+ByteNo) = (uint8)a_data;
            Total_BitsCopied = Total_BitsCopied + 8u;
        }
        else{
            Mask = (uint8)(0xFFu << Bits_left);
            *(Dest_Buf+ByteNo) = *(Dest_Buf+ByteNo) & Mask;
            *(Dest_Buf+ByteNo) = *(Dest_Buf+ByteNo) | (uint8)a_data;

            Total_BitsCopied = Total_BitsCopied + Bits_left;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if(defined(COM_TXSIG_FLOAT64SUPP) || defined(COM_TXGRPSIG_FLOAT64SUPP) ||\
    (defined(COM_RX_SIGNALGROUP_ARRAY) && defined(COM_RXGRPSIG_FLOAT64SUPP)))
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_PackFloatSignal(VAR(uint8, AUTOMATIC) Endianess, VAR(Com_BitpositionType, AUTOMATIC) Bit_Pos
   ,     VAR(float64,AUTOMATIC) Src, P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf)
{
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) NoofBytes;
   VAR(uint8_least, AUTOMATIC) BitOffsetInByte;

    NoofBytes = 8u;
    ByteNo = Bit_Pos >> 3u;
    BitOffsetInByte = (uint8)(Bit_Pos % 8u);

   if(BitOffsetInByte == 0u )
   {
        if(Endianess == COM_LITTLEENDIAN)
        {

            (void)LibAutosar_vptrMemCopy((void *)(Dest_Buf+ByteNo),(const void *)&Src,NoofBytes);

        }
        else{
            uint8 index_u8;
            uint8 convdata_u8[8];

            (void)LibAutosar_vptrMemCopy((void *)convdata_u8, (const void *)&Src, NoofBytes);

            for(index_u8 = 0; index_u8 < NoofBytes; index_u8++)
            {
                *(Dest_Buf+ByteNo) = convdata_u8[index_u8];
                ByteNo--;
            }
        }
   }
   else{
        uint16_least index_u16;
        uint8        Mask;
        uint8        convdata_u8[8];

        (void)LibAutosar_vptrMemCopy( (void *)convdata_u8, (const void *)&Src, NoofBytes );

        Mask = (uint8) (~((uint8)(0xFFu << BitOffsetInByte)));

        *(Dest_Buf+ByteNo) = (uint8)((uint8)((uint8)(*(Dest_Buf+ByteNo)) & Mask) |
                                     (uint8)(convdata_u8[0] << BitOffsetInByte));

        if(Endianess == COM_LITTLEENDIAN)
        {

            ByteNo++;

            for(index_u16 = 0; index_u16 < (NoofBytes-1u); index_u16++)
            {

                *(Dest_Buf+ByteNo) = (uint8)((uint8)(convdata_u8[index_u16] >> (8u-BitOffsetInByte)) |
                                             (uint8)(convdata_u8[index_u16 + 1u] << BitOffsetInByte));

                ByteNo++;
            }

            *(Dest_Buf+ByteNo) = (uint8)((*(Dest_Buf+ByteNo)) & ((uint8)(~Mask))) |
                                 (uint8)(convdata_u8[7] >> (8u-BitOffsetInByte));
        }
        else{

            ByteNo--;

            for(index_u16 = 0; index_u16 < (NoofBytes-1u); index_u16++)
            {

                *(Dest_Buf+ByteNo) = (uint8)((uint8)(convdata_u8[index_u16] >> (8u-BitOffsetInByte)) |
                                             (uint8)((convdata_u8[index_u16 + 1u] << BitOffsetInByte)));

                ByteNo--;
            }

            *(Dest_Buf+ByteNo) = (uint8)((*(Dest_Buf+ByteNo)) & ((uint8)(~Mask))) |
                                 (uint8)(convdata_u8[7] >> (8u-BitOffsetInByte));
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

