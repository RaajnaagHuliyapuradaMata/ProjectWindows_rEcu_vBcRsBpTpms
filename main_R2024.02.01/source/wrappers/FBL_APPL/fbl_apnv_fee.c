#include "Std_Types.hpp"

#include "fbl_def.hpp"
#include "wdt.hpp"
#include "EcuabFee.hpp"
#include "EcuabFee_Cfg.hpp"
#include "Fls.hpp"

#define FBL_NV_CONTROL_DATA_FEE_BLOCK_NUMBER                   FeeConf_FeeBlockConfiguration_FeeBlock_FBL_Data
#define FBL_NV_CONTROL_DATA_FEE_BLOCK_LENGTH                   130u //kEepSizeProcessData

const vuint16 fblFeeMetaDataBlock[] =
{
   FeeConf_FeeBlockConfiguration_FeeBlock_FBL_Data
};

#define FBL_NV_META_DATA_FEE_BLOCK_NUMBER(index)               fblFeeMetaDataBlock[index]

#define FBL_NV_META_DATA_FEE_BLOCK_LENGTH                      FBL_NV_CONTROL_DATA_FEE_BLOCK_LENGTH //kEepSizeMetadata

#define FBL_NV_ERASED_VALUE                                    0xFFu

extern tFblResult ApplFblNvInit(void);

extern tFblResult ApplFblNvWriteProcessData( vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );
extern tFblResult ApplFblNvReadProcessData( vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );

extern tFblResult ApplFblNvWriteMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );
extern tFblResult ApplFblNvReadMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );

static tFblResult ApplFblNvRead( vuint16 blockNumber
   ,     vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length );
static tFblResult ApplFblNvWrite( vuint16 blockNumber
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer );

static vuint8 g_FblNvDataCached;
static vuint8 g_FblNvData[FBL_NV_CONTROL_DATA_FEE_BLOCK_LENGTH];

static tFblResult ApplFblNvRead( vuint16 blockNumber
   ,     vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length )
{
   tFblResult result;
   vuintx i;
   MemIf_JobResultType feeJobResult;

   // handle pending jobs first
   while(   (MEMIF_IDLE != Fls_GetStatus())
        || (MEMIF_IDLE != EcuabFee_GetStatus())
        || (MEMIF_JOB_PENDING == EcuabFee_GetJobResult()))
   {
        Wdt_TriggerWD0(); // Trigger Watchdog

        EcuabFee_MainFunction();
        Fls_MainFunction();
   }
   if(E_OK == EcuabFee_Read(blockNumber, blockOffset, pBuffer, length))
   {
      while(   (MEMIF_IDLE != Fls_GetStatus())
             || (MEMIF_IDLE != EcuabFee_GetStatus())
             || (MEMIF_JOB_PENDING == EcuabFee_GetJobResult()))
      {

         Wdt_TriggerWD0();  // Trigger Watchdog

         EcuabFee_MainFunction();
         Fls_MainFunction();

      }

      feeJobResult = EcuabFee_GetJobResult();
      if(MEMIF_JOB_OK == feeJobResult)
      {
         result = kFblOk;
      }
      else if(   (MEMIF_BLOCK_INCONSISTENT == feeJobResult )
               || (MEMIF_BLOCK_INVALID == feeJobResult ))
      {
         for(i = 0u; i < length; i++)
         {
            pBuffer[i] = FBL_NV_ERASED_VALUE;
         }

         result = kFblOk;
      }
      else{
         result = kFblFailed;
      }
   }
   else{
      result = kFblFailed;
   }

   return result;
}

static tFblResult ApplFblNvWrite( vuint16 blockNumber
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer )
{
   tFblResult result;

   // handle pending jobs first
   while(   (MEMIF_IDLE != Fls_GetStatus())
        || (MEMIF_IDLE != EcuabFee_GetStatus())
        || (MEMIF_JOB_PENDING == EcuabFee_GetJobResult()))
   {
        Wdt_TriggerWD0(); // Trigger Watchdog

        EcuabFee_MainFunction();
        Fls_MainFunction();
   }

   if(E_OK == EcuabFee_Write(blockNumber, pBuffer))
   {
      while(   (MEMIF_IDLE != Fls_GetStatus())
             || (MEMIF_IDLE != EcuabFee_GetStatus())
             || (MEMIF_JOB_PENDING == EcuabFee_GetJobResult()))
      {
         Wdt_TriggerWD0(); // Trigger Watchdog

         EcuabFee_MainFunction();
         Fls_MainFunction();
      }

      if(MEMIF_JOB_OK == EcuabFee_GetJobResult())
      {
         result = kFblOk;
      }
      else{
         result = kFblFailed;
      }
   }
   else{
      result = kFblFailed;
   }

   return result;
}

tFblResult ApplFblNvWriteProcessData( vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length )
{
   tFblResult result;
   vuintx i;

   result = kFblOk;

   if(0u == g_FblNvDataCached)
   {

      result = ApplFblNvRead(FBL_NV_CONTROL_DATA_FEE_BLOCK_NUMBER
   ,     0u
   ,     g_FblNvData
   ,     FBL_NV_CONTROL_DATA_FEE_BLOCK_LENGTH);

      if(kFblOk == result)
      {
         g_FblNvDataCached = 1u;
      }
   }

   if(kFblOk == result)
   {
      for(i = 0u; i < length; i++)
      {
         g_FblNvData[blockOffset + i] = pBuffer[i];
      }

      result = ApplFblNvWrite(FBL_NV_CONTROL_DATA_FEE_BLOCK_NUMBER, g_FblNvData);
   }

   return result;
}

tFblResult ApplFblNvReadProcessData( vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length )
{
   tFblResult result;
   vuintx i;

   result = kFblOk;

   if(0u == g_FblNvDataCached)
   {

      result = ApplFblNvRead(FBL_NV_CONTROL_DATA_FEE_BLOCK_NUMBER
   ,     0u
   ,     g_FblNvData
   ,     FBL_NV_CONTROL_DATA_FEE_BLOCK_LENGTH);

      if(kFblOk == result)
      {
         g_FblNvDataCached = 1u;
      }
   }

   if(kFblOk == result)
   {
      for(i = 0u; i < length; i++)
      {
         pBuffer[i] = g_FblNvData[blockOffset + i];
      }
   }

   return result;
}

tFblResult ApplFblNvWriteMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length )
{
   tFblResult result;
   vuintx i;

   result = kFblOk;

   if(0u == g_FblNvDataCached)
   {

      result = ApplFblNvRead(FBL_NV_META_DATA_FEE_BLOCK_NUMBER(index)
   ,     0u
   ,     g_FblNvData
   ,     FBL_NV_META_DATA_FEE_BLOCK_LENGTH);

      if(kFblOk == result)
      {
         g_FblNvDataCached = 1u;
      }
   }

   if(kFblOk == result)
   {
      for(i = 0u; i < length; i++)
      {
         g_FblNvData[blockOffset + i] = pBuffer[i];
      }

      result = ApplFblNvWrite(FBL_NV_META_DATA_FEE_BLOCK_NUMBER(index), g_FblNvData);
   }

   return result;
}

tFblResult ApplFblNvReadMetaData( vuintx index
   ,     vuint16 blockOffset
   ,     V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pBuffer
   ,     vuint16 length )
{
   tFblResult result;
   vuintx i;

   result = kFblOk;

   if(0u == g_FblNvDataCached)
   {

      result = ApplFblNvRead(FBL_NV_META_DATA_FEE_BLOCK_NUMBER(index)
   ,     0u
   ,     g_FblNvData
   ,     FBL_NV_META_DATA_FEE_BLOCK_LENGTH);

      if(kFblOk == result)
      {
         g_FblNvDataCached = 1u;
      }
   }

   if(kFblOk == result)
   {
      for(i = 0u; i < length; i++)
      {
         pBuffer[i] = g_FblNvData[blockOffset + i];
      }
   }

   return result;
}

tFblResult ApplFblNvInit(void)
{

  Fls_Init(FlsConfigSet);
  EcuabFee_Init();

  return kFblOk;
}

