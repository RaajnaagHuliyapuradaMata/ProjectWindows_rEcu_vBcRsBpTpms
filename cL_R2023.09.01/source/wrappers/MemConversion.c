

#include "MemConversion.hpp"

void FblMemSetInteger( uint32 count, uint32 input, uint8* buffer )
{

   while(count > 0u)
   {
      count--;

      buffer[count] = (uint8)(input & 0xFFu);

      input >>= 8u;
   }
}

uint32 FblMemGetInteger( uint32 count, const uint8* buffer )
{
   uint32 output;
   uint32 idx;

   output = 0u;
   idx    = 0u;

   while(count > 0u)
   {

      output <<= 8u;

      output |= (uint32)buffer[idx];

      idx++;
      count--;
   }

   return output;
}