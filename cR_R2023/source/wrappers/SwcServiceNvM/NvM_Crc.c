

#define NVM_CRC_SOURCE

#include "Std_Types.h"

#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Crc.h"

#if ((NVM_CRC_MAJOR_VERSION != (5u)) \
        || (NVM_CRC_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Crc.c and NvM_Crc.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Crc.c and NvM_Cfg.h are inconsistent!"
#endif

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Calculate (NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer (NvM_CrcBufferPtrType, NvM_CrcValueRefType);

#if (NVM_USE_CRC16 == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Calculate (NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Compare (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_CopyToBuffer (NvM_CrcBufferPtrType, NvM_CrcValueRefType);
#endif

#if (NVM_USE_CRC32 == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Calculate(NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Compare (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_CopyToBuffer (NvM_CrcBufferPtrType, NvM_CrcValueRefType);
#endif

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

NVM_LOCAL uint8 NvM_CrcQueueCountTrailingZeros(NvM_CrcQueueEntryType word);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_NoCrcHandler_t =
{
    NvM_Crc_NoCrc_Calculate,
    NvM_Crc_NoCrc_Compare,
    NvM_Crc_NoCrc_CopyToBuffer,
    0,
    0
};

#if (NVM_USE_CRC16 == STD_ON)

NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_Crc16Handler_t =
{
    NvM_Crc_Crc16_Calculate,
    NvM_Crc_Crc16_Compare,
    NvM_Crc_Crc16_CopyToBuffer,
    NVM_INITIAL_CRC_16_VALUE,
    2
};
#else
# define NvM_Crc_Crc16Handler_t NvM_Crc_NoCrcHandler_t
#endif

#if (NVM_USE_CRC32 == STD_ON)

NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_Crc32Handler_t =
{
    NvM_Crc_Crc32_Calculate,
    NvM_Crc_Crc32_Compare,
    NvM_Crc_Crc32_CopyToBuffer,
    NVM_INITIAL_CRC_32_VALUE,
    4
};
#else
# define NvM_Crc_Crc32Handler_t NvM_Crc_NoCrcHandler_t
#endif

NVM_LOCAL CONST(NvM_CrcHandlerClassConstPtr, NVM_PRIVATE_CONST) NvM_CrcHandlerTable_at[4] =
{
    &NvM_Crc_NoCrcHandler_t,
    &NvM_Crc_NoCrcHandler_t,
    &NvM_Crc_Crc16Handler_t,
    &NvM_Crc_Crc32Handler_t
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

# define NVM_SIZE_CRC_JOB_QUEUE ((NVM_TOTAL_NUM_OF_NVRAM_BLOCKS + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT)

# define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"

VAR(NvM_CrcQueueEntryType, NVM_CONFIG_DATA) NvM_CrcQueue_at[NVM_SIZE_CRC_JOB_QUEUE];

NVM_LOCAL VAR(NvM_BlockIdType, NVM_PRIVATE_DATA) NvM_CrcQueueScanStart_u16;

# define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"

# define NVM_START_SEC_CODE
# include "MemMap.h"

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueInit(void)
{
    uint16_least counter = (NvM_CrcQueueSize_u16 + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT;

    do
    {
        --counter;
        NvM_CrcQueue_at[counter] = 0u;
    } while (counter > 0);

    NvM_CrcQueueScanStart_u16 = 1u;
}

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueJob(NvM_BlockIdType BlockId)
{

    const NvM_CrcQueueEntryType bitMask = (NvM_CrcQueueEntryType)(1u << (BlockId & NVM_CRC_QUEUE_BITINDEX_MASK));
    const NvM_CrcQueueEntryPtr queueEntry = &NvM_CrcQueue_at[BlockId >> NVM_CRC_QUEUE_ENTRY_SHIFT];

    NvM_EnterCriticalSection();

    *queueEntry |= bitMask;

    NvM_ExitCriticalSection();
}

FUNC(NvM_BlockIdType, NVM_PRIVATE_CODE) NvM_CrcGetQueuedBlockId(void)
{

    uint16 newBlockId = (NvM_CrcQueueScanStart_u16 < NvM_CrcQueueSize_u16) ? NvM_CrcQueueScanStart_u16 : 1u;

    const uint16 queueSizeWords = (NvM_CrcQueueSize_u16 + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT;

    uint8 bitPos = (uint8)(newBlockId & NVM_CRC_QUEUE_BITINDEX_MASK);
    const NvM_CrcQueueEntryType entryMask = (NvM_CrcQueueEntryType)~((1u << bitPos) - 1u);

    newBlockId >>= NVM_CRC_QUEUE_ENTRY_SHIFT;

    bitPos = NvM_CrcQueueCountTrailingZeros(entryMask & NvM_CrcQueue_at[newBlockId]);

    while (bitPos >= NVM_CRC_QUEUE_ENTRY_BITS)
    {

        newBlockId++;

        if (newBlockId >= queueSizeWords)
        {
            NvM_CrcQueueScanStart_u16 = NvM_CrcQueueSize_u16;
            break;
        }

        bitPos = NvM_CrcQueueCountTrailingZeros(NvM_CrcQueue_at[newBlockId]);
    }

    if(newBlockId < queueSizeWords)
    {
        NvM_EnterCriticalSection();

        NvM_CrcQueue_at[newBlockId] ^= (1u << bitPos);

        NvM_ExitCriticalSection();

        newBlockId <<= NVM_CRC_QUEUE_ENTRY_SHIFT;

        newBlockId |= bitPos;

        NvM_CrcQueueScanStart_u16 = (NvM_BlockIdType)(newBlockId + 1u);
    }

    else
    {
        newBlockId = 0;
    }

    return (NvM_BlockIdType)newBlockId;
}

NVM_LOCAL uint8 NvM_CrcQueueCountTrailingZeros(NvM_CrcQueueEntryType word)
{
    uint8 trailingZeroes = 0;

    if(word == 0)
    {
        trailingZeroes = NVM_CRC_QUEUE_ENTRY_BITS;
    }
    else
    {

        if((word & 0xFFFFu) == 0u)
        {
            trailingZeroes |= 0x10u;
            word >>= 16u;
        }

        if((word & 0xFFu) == 0u)
        {
            trailingZeroes |= 0x08u;
            word >>= 8u;
        }

        if((word & 0x0Fu) == 0u)
        {
            trailingZeroes |= 0x04u;
            word >>= 4u;
        }

        if((word & 0x03u) == 0u)
        {
            trailingZeroes |= 2u;
            word >>= 2u;
        }

        trailingZeroes |= (uint8)((word & 1u) ^ 1u);
    }

    return trailingZeroes;
}

# define NVM_STOP_SEC_CODE
# include "MemMap.h"

#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Create(NvM_CrcJobPtrType self, NvM_BlockIdType blockId, NvM_RamAddressType ramData_pt)
{
    const NvM_BlockDescrPtrType descr_pt = &(NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(blockId)]);

    self->HandlerInstance_pt = NvM_CrcHandlerTable_at[descr_pt->CrcSettings];

    self->CurrentCrcValue = self->HandlerInstance_pt->initialCrcValue;

    self->RamData_pt = ramData_pt;
    self->CrcBuffer = (ramData_pt != NULL_PTR) ? (&ramData_pt[descr_pt->NvBlockLength_u16]) : NULL_PTR;

    self->RemainingLength_u16 =
        ((self->HandlerInstance_pt->crcLength > 0) && (ramData_pt != NULL_PTR)) ? descr_pt->NvBlockLength_u16 : 0u;

#if(NVM_USE_BLOCK_ID_CHECK == STD_ON)

    if(descr_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
    {

        NvM_BlockIdType originBlockId = NVM_BLOCK_FROM_DCM_ID(blockId);

        const NvM_RamMngmtPtrType ramMngmt_pt =
            (originBlockId != blockId) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[blockId]);

        uint8 ramData[3];

        ramData[0] = (uint8)(originBlockId >> 8);
        ramData[1] = (uint8)originBlockId;
        ramData[2] = (uint8)ramMngmt_pt->NvDataIndex_t;

        self->HandlerInstance_pt->calc(ramData, 3, &self->CurrentCrcValue);
    }
#endif
}

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Process(NvM_CrcJobPtrType self, uint16 processLength)
{
    if(self->RemainingLength_u16 > 0)
    {
        const NvM_ConstRamAddressType currRamPtr = self->RamData_pt;
        uint16 currLength = self->RemainingLength_u16;

        if(currLength > processLength)
        {
            currLength = processLength;
        }

        self->RemainingLength_u16 -= currLength;

        self->RamData_pt = &currRamPtr[currLength];

        self->HandlerInstance_pt->calc(currRamPtr, currLength, &self->CurrentCrcValue);
    }
}

FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_Compare(NvM_CrcJobConstPtrType self)
{
    boolean result = FALSE;

    if(self->CrcBuffer != NULL_PTR)
    {

        result = (self->HandlerInstance_pt->compare(self->CrcBuffer, (NvM_CrcValueRefType)&self->CurrentCrcValue));
    }

    return result;
}

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_CopyToBuffer(NvM_CrcJobConstPtrType self)
{
    if(self->CrcBuffer != NULL_PTR)
    {

        self->HandlerInstance_pt->copyToBuffer(self->CrcBuffer, (NvM_CrcValueRefType)&self->CurrentCrcValue);
    }
}

#if (NVM_CRC_INT_BUFFER == STD_ON)

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ExportBufferedValue(NvM_CrcJobConstPtrType self, NvM_CrcBufferPtrType dest_pt)
{
    if((dest_pt != NULL_PTR) && (self->CrcBuffer != NULL_PTR))
    {
        self->HandlerInstance_pt->copyToBuffer(dest_pt, self->CrcBuffer);
    }
}

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ImportBufferedValue(NvM_CrcJobConstPtrType self, NvM_CrcBufferConstPtrType src_pt)
{
    if((self->CrcBuffer != NULL_PTR) && (src_pt != NULL_PTR))
    {
        self->HandlerInstance_pt->copyToBuffer(self->CrcBuffer, src_pt);
    }
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_NoCrc_Calculate(NvM_ConstRamAddressType data_ptr, uint16 length, NvM_CrcValuePtrType currentValue)
{

    NVM_DUMMY_STATEMENT_CONST(data_ptr);
    NVM_DUMMY_STATEMENT(length);
    NVM_DUMMY_STATEMENT(currentValue);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare(NvM_CrcBufferConstPtrType crcBuff, NvM_CrcValueRefType currentValue)
{

    NVM_DUMMY_STATEMENT_CONST(crcBuff);
    NVM_DUMMY_STATEMENT_CONST(currentValue);

    return TRUE;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer(NvM_CrcBufferPtrType dest, NvM_CrcValueRefType src)
{

    NVM_DUMMY_STATEMENT(dest);
    NVM_DUMMY_STATEMENT_CONST(src);
}

#if (NVM_USE_CRC16 == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_Crc16_Calculate(NvM_ConstRamAddressType data_pt, uint16 length, NvM_CrcValuePtrType currCrc)
{

    typedef P2VAR(uint16, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_Crc16PtrType;

    *(NvM_Crc16PtrType)currCrc = Crc_CalculateCRC16(data_pt, length, *(NvM_Crc16PtrType)currCrc, FALSE);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Compare(NvM_CrcBufferConstPtrType crc1, NvM_CrcValueRefType crc2)
{
    return (boolean)((crc1[0] == crc2[0]) && (crc1[1] == crc2[1]));
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_CopyToBuffer (NvM_CrcBufferPtrType dest, NvM_CrcValueRefType src)
{
    dest[0] = src[0];
    dest[1] = src[1];
}
#endif

#if (NVM_USE_CRC32 == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_Crc32_Calculate(NvM_ConstRamAddressType data_pt, uint16 length, NvM_CrcValuePtrType currCrc)
{
    *currCrc = Crc_CalculateCRC32(data_pt, length, (*currCrc) ^ NVM_CRC32_XOR_VALUE, FALSE);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Compare(NvM_CrcBufferConstPtrType crc1, NvM_CrcValueRefType crc2)
{
    return (boolean)((crc1[0] == crc2[0]) && (crc1[1] == crc2[1]) && (crc1[2] == crc2[2]) && (crc1[3] == crc2[3]));
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_CopyToBuffer (NvM_CrcBufferPtrType dest, NvM_CrcValueRefType src)
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

