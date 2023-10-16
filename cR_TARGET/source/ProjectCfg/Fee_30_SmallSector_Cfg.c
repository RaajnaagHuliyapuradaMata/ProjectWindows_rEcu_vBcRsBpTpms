#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

#include "Std_Types.hpp"
#include "Fee_30_SmallSector.hpp"
#include "NvM_Cbk.hpp"

#define FEE_30_SMALLSECTOR_START_SEC_CONST_8BIT
#include "MemMap.hpp"
CONST(uint8, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_DatasetSelectionBits = (1U);
#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_8BIT
#include "MemMap.hpp"

#define FEE_30_SMALLSECTOR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"
CONST(Fee_30_SmallSector_PartitionConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_PartitionConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS] =
{
   {
      0x00000800UL
   ,     0x0040U
   ,     0x0008U
   ,     0x0008U
   ,     0x0000U
   ,     &Fee_30_SmallSector_FlsApi0
   ,     0xFFU
   ,     TRUE
   ,  {
        0x0004U
   }
  }
   ,  {
      0x00000C00UL
   ,     0x0040U
   ,     0x0008U
   ,     0x0008U
   ,     0x0000U
   ,     &Fee_30_SmallSector_FlsApi0
   ,     0xFFU
   ,     TRUE
   ,  {
        0x0002U
   ,     0x0006U
   ,     0x0008U
   ,     0x000AU
   ,     0x000CU
   ,     0x000EU
   ,     0x0010U
   ,     0x0012U
   ,     0x0014U
   ,     0x0016U
   ,     0x0018U
   ,     0x0034U
   }
  }
   ,  {
      0x00007800UL
   ,     0x0040U
   ,     0x0008U
   ,     0x0008U
   ,     0x0000U
   ,     &Fee_30_SmallSector_FlsApi0
   ,     0xFFU
   ,     TRUE
   ,  {
        0x001AU
   ,     0x001CU
   ,     0x001EU
   ,     0x0020U
   ,     0x0022U
   ,     0x0024U
   ,     0x0026U
   ,     0x0028U
   ,     0x002AU
   ,     0x002CU
   ,     0x002EU
   ,     0x0030U
   ,     0x0032U
   }
  }
};

CONST(Fee_30_SmallSector_BlockConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_BlockConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS] =
{
  {
      0x00000000UL
   ,     0x0004U
   ,     0x01U
   ,     0x02U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000000UL
   ,     0x0082U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000080UL
   ,     0x0036U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000140UL
   ,     0x0036U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000200UL
   ,     0x0062U
   ,     0x03U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000380UL
   ,     0x0016U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000400UL
   ,     0x0032U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000004C0UL
   ,     0x0032U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000580UL
   ,     0x001AU
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000600UL
   ,     0x001AU
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000680UL
   ,     0x0022U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000700UL
   ,     0x0006U
   ,     0x03U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000000UL
   ,     0x0014U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000040UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000000C0UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000140UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000001C0UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000240UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000002C0UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000340UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000003C0UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000440UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000004C0UL
   ,     0x0032U
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000540UL
   ,     0x002CU
   ,     0x01U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x000005C0UL
   ,     0x0016U
   ,     0x02U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
   ,  {
      0x00000780UL
   ,     0x0042U
   ,     0x03U
   ,     0x01U
   ,     FALSE
   ,     FALSE
  }
};

CONST(Fee_30_SmallSector_FlsApiType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_FlsApi0 =
{
    Fls_Read
   ,   Fls_Write
   ,   Fls_Compare
   ,   Fls_Erase
   ,   Fls_BlankCheck
   ,   Fls_GetStatus
   ,   Fls_GetJobResult
};

CONST(Fee_30_SmallSector_CbkJobEndNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobEndNotification =
    NvM_JobEndNotification;
CONST(Fee_30_SmallSector_CbkJobErrorNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobErrorNotification =
    NvM_JobErrorNotification;
#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.hpp"

