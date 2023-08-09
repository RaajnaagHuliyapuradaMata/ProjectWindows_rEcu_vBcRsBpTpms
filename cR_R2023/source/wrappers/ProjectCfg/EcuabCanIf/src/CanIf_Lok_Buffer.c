

#include "CanIf_Prv.h"

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)
static FUNC(void, CANIF_CODE) CanIf_Lok_GetFreeTxBufferIndex
                                            (
                                                P2VAR(uint8, AUTOMATIC, CANIF_APPL_DATA) lFreeIndex,
                                                P2CONST(CanIf_Cfg_TxBufferConfig_tst, AUTOMATIC, CANIF_APPL_DATA) TxBufferConfig_pst
                                            );

static FUNC(void, CANIF_CODE) CanIf_Lok_SortTxBuffer(VAR(uint32, AUTOMATIC) BufferId,
        P2VAR(CanIf_Cfg_CanIdBuffer_tst, AUTOMATIC, CANIF_APPL_DATA) CanIdBuf_p, VAR(uint8, AUTOMATIC) BufferSize
                                            );

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Lok_WriteTxBuffer(
                                                            VAR(PduIdType, AUTOMATIC) CanIfTxSduId,
                                                            VAR(Can_PduType, AUTOMATIC) Pdu
                                                        )
{
    P2VAR(uint8,AUTOMATIC, AUTOMATIC)  lDataBuf_p;
    P2VAR (CanIf_Cfg_CanIdBuffer_tst,AUTOMATIC, AUTOMATIC  ) lCanIdBuf_p;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, AUTOMATIC) lTxPduConfig_pst;
    P2CONST(CanIf_Cfg_TxBufferConfig_tst, AUTOMATIC, AUTOMATIC) lTxBufferConfig_pst;
    VAR(uint32 ,AUTOMATIC) lBufferId;
    VAR(uint8 ,AUTOMATIC)lBufferSize;
    VAR(uint8 ,AUTOMATIC)lDataMaxLen;
    VAR(uint8 ,AUTOMATIC)lDataLen;
    VAR(CanIf_Cfg_CanHandleType_ten ,AUTOMATIC)lCanHandleType;
    VAR(uint8 ,AUTOMATIC)lIndex;
    VAR(uint8 ,AUTOMATIC)lSduWriteIndex = 0xFF;
    VAR(uint8 ,AUTOMATIC)lCanIdWriteIndex = 0;
    VAR(uint8 ,AUTOMATIC)lDataIndex;
    P2VAR(uint8 ,AUTOMATIC, AUTOMATIC)lSduPtr;
    VAR(Std_ReturnType ,AUTOMATIC)lRetValue;

    lTxPduConfig_pst    = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + CanIfTxSduId;
    lTxBufferConfig_pst = lTxPduConfig_pst->CanIf_TxBufferConfigPtr;
    lDataBuf_p          = lTxBufferConfig_pst->DataBuf;
    lCanIdBuf_p         = lTxBufferConfig_pst->CanIdBuf;
    lBufferId           = lTxBufferConfig_pst->CanIfBufferId;
    lBufferSize         = lTxBufferConfig_pst->CanIfBufferSize;
    lDataMaxLen         = lTxBufferConfig_pst->CanIfBufferMaxDataLength;
    lCanHandleType      = lTxBufferConfig_pst->CanIf_HthConfigPtr->CanHandleType;

    if (
            ((CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus == CANIF_TXBUFFER_FULL)
                    && (CanIf_Lok_TxPduRam_ast[CanIfTxSduId].pdu_buffered_flag != TRUE))
            ||(lCanHandleType == CANIF_FULL)
       )
    {
        lRetValue = E_NOT_OK;
    }
    else
    {
        if (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus == CANIF_TXBUFFER_EMPTY)
        {
            CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus = CANIF_TXBUFFER_READY;
        }
        if(CanIf_Lok_TxPduRam_ast[CanIfTxSduId].pdu_buffered_flag == TRUE)
        {
            for (lIndex = 0; lIndex <= CanIf_Lok_TxBufferRam_ast[lBufferId].last_index; lIndex++)
            {
                if ((lCanIdBuf_p+lIndex)->swPduHandle == lTxPduConfig_pst->TxPduId)
                {
                    lSduWriteIndex   = (lCanIdBuf_p + lIndex)->BufferIndex;
                    lCanIdWriteIndex = lIndex;
                    break;
                }
            }
        }
        else
        {
            CanIf_Lok_GetFreeTxBufferIndex(&lSduWriteIndex, lTxBufferConfig_pst);
            CanIf_Lok_TxBufferRam_ast[lBufferId].last_index = (((CanIf_Lok_TxBufferRam_ast[lBufferId].last_index) + 1)&(0xFFu));

            lCanIdWriteIndex                               = CanIf_Lok_TxBufferRam_ast[lBufferId].last_index;

            if(lCanIdWriteIndex == ((lBufferSize - 1)&0xFFu))
            {
                CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus = CANIF_TXBUFFER_FULL;
            }

            (lCanIdBuf_p + lCanIdWriteIndex)->BufferIndex  = lSduWriteIndex;

            *(lDataBuf_p + ((lSduWriteIndex)*(lDataMaxLen+1)) + 0)          = 0x00;

            CanIf_Lok_TxPduRam_ast[CanIfTxSduId].pdu_buffered_flag = TRUE;

         }

        (lCanIdBuf_p + lCanIdWriteIndex)->CanId       = Pdu.id;
        (lCanIdBuf_p + lCanIdWriteIndex)->swPduHandle = Pdu.swPduHandle;

#if(CANIF_TRIGGERTRANSMIT_SUPPORT == STD_ON)
        if(lTxPduConfig_pst->TxPduTriggerTransmit != TRUE)
#endif
        {

            lSduPtr = Pdu.sdu;

            if(Pdu.length > lDataMaxLen)
            {
                lDataLen = lDataMaxLen;
                (lCanIdBuf_p + lCanIdWriteIndex)->SduLength = lDataMaxLen;
            }
            else
            {
                lDataLen = Pdu.length;
                (lCanIdBuf_p + lCanIdWriteIndex)->SduLength = Pdu.length;
            }

            for(lDataIndex=1; lDataIndex < (lDataLen + 1); lDataIndex++)
            {

                *(lDataBuf_p + ((lSduWriteIndex)*(lDataMaxLen+1)) + lDataIndex) = *(lSduPtr+(lDataIndex-1));
            }

        }

        CanIf_Lok_SortTxBuffer(lBufferId, lCanIdBuf_p, lBufferSize);
        lRetValue = E_OK;
    }
    return(lRetValue);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_Lok_SortTxBuffer(VAR(uint32, AUTOMATIC) BufferId,
        P2VAR(CanIf_Cfg_CanIdBuffer_tst, AUTOMATIC, CANIF_APPL_DATA) CanIdBuf_p, VAR(uint8, AUTOMATIC) BufferSize)
{
    VAR(uint8, AUTOMATIC)lIndex1;

    VAR(uint8, AUTOMATIC)lIndex2;

    VAR(Can_IdType ,AUTOMATIC)lCanId;

    VAR(uint8, AUTOMATIC)lBufIndex;

    VAR(PduIdType, AUTOMATIC)lswPduHandle;

    VAR(uint8, AUTOMATIC)lSduLength ;

    for (lIndex1 = 0; lIndex1 <= CanIf_Lok_TxBufferRam_ast[BufferId].last_index; lIndex1++)
    {
        for (lIndex2 = 0; lIndex2 <= ((CanIf_Lok_TxBufferRam_ast[BufferId].last_index)-lIndex1) && ((lIndex2+1)<BufferSize); lIndex2++)
        {
            if ((CanIdBuf_p+lIndex2)->CanId < (CanIdBuf_p+(lIndex2+1))->CanId)
            {
                lCanId       = (CanIdBuf_p+lIndex2)->CanId;
                lBufIndex    = (CanIdBuf_p+lIndex2)->BufferIndex;
                lswPduHandle = (CanIdBuf_p+lIndex2)->swPduHandle;
                lSduLength   = (CanIdBuf_p+lIndex2)->SduLength;

                CanIdBuf_p[lIndex2].CanId = CanIdBuf_p[lIndex2+1].CanId;
                CanIdBuf_p[lIndex2].BufferIndex = CanIdBuf_p[lIndex2+1].BufferIndex;
                CanIdBuf_p[lIndex2].swPduHandle = CanIdBuf_p[lIndex2+1].swPduHandle;
                CanIdBuf_p[lIndex2].SduLength = CanIdBuf_p[lIndex2+1].SduLength;

                CanIdBuf_p[lIndex2+1].CanId         = lCanId;
                CanIdBuf_p[lIndex2+1].BufferIndex   = lBufIndex;
                CanIdBuf_p[lIndex2+1].swPduHandle   = lswPduHandle;
                CanIdBuf_p[lIndex2+1].SduLength     = lSduLength;

            }
        }
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void , CANIF_CODE) CanIf_Lok_ClearTxChannelBuffer(VAR(uint8, AUTOMATIC)ControllerId)
{
    P2VAR(uint8,AUTOMATIC, AUTOMATIC)  lDataBuf_p;
    P2VAR (CanIf_Cfg_CanIdBuffer_tst, AUTOMATIC, AUTOMATIC) lCanIdBuf_p;
    VAR(uint32, AUTOMATIC)lBufferId;
    VAR(uint32, AUTOMATIC)lTxPduId;
    VAR(uint8, AUTOMATIC)lBufferSize;
    VAR(uint8, AUTOMATIC)lDataIndex;
    VAR(uint8, AUTOMATIC)BufferIndex;
    VAR(uint8, AUTOMATIC)lDataMaxLen;
    P2CONST(CanIf_Cfg_TxBufferConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lBufferConfig_pst;
#if ( CANIF_RB_NODE_CALIBRATION != STD_ON )
    P2VAR (uint32, AUTOMATIC, AUTOMATIC) BufferId_ptr;
    P2VAR (uint32, AUTOMATIC, AUTOMATIC) TxPduId_ptr;
    VAR(uint32, AUTOMATIC)lBufferCustId;
    VAR(uint32, AUTOMATIC)BufferIdArrayIndex;
    VAR(uint32, AUTOMATIC)TxPduIdArrayIndex;
    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
#endif
#if ( CANIF_RB_NODE_CALIBRATION == STD_ON )
    VAR(uint32, AUTOMATIC)lBufferArrayIndex;
    VAR(uint32, AUTOMATIC)lHthTxPduMapTblArryIndex;
#endif

#if ( CANIF_RB_NODE_CALIBRATION != STD_ON )

    lCtrlConfig_pst           = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + ControllerId;
    BufferId_ptr              = lCtrlConfig_pst->BufferIdPtr;
    TxPduId_ptr               = lCtrlConfig_pst->TxPduIdPtr;

    lBufferConfig_pst         = CanIf_Lok_ConfigSet_tpst->CanIf_TxBufferConfigPtr;

    for(BufferIdArrayIndex = 0; BufferIdArrayIndex < (lCtrlConfig_pst->TotalBufferCount); BufferIdArrayIndex++)
    {

        lBufferCustId   = *(BufferId_ptr + BufferIdArrayIndex);

        lDataBuf_p    = (lBufferConfig_pst + lBufferCustId)->DataBuf;

        lCanIdBuf_p  = (lBufferConfig_pst + lBufferCustId)->CanIdBuf;
        lDataMaxLen  = (lBufferConfig_pst + lBufferCustId)->CanIfBufferMaxDataLength;

        lBufferSize = (lBufferConfig_pst + lBufferCustId)->CanIfBufferSize;
        lBufferId   = (lBufferConfig_pst + lBufferCustId)->CanIfBufferId;

        if (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus != CANIF_TXBUFFER_EMPTY)
        {
            for(BufferIndex = 0 ; BufferIndex < lBufferSize ; BufferIndex++ )
            {

                *(lDataBuf_p + ((BufferIndex)*(lDataMaxLen+1)) + 0)    = 0xFF;
                for(lDataIndex=1; lDataIndex < (lDataMaxLen + 1); lDataIndex++)
                {
                    *(lDataBuf_p + ((BufferIndex)*(lDataMaxLen + 1)) + lDataIndex) = 0;
                }

                (lCanIdBuf_p + BufferIndex)->BufferIndex = 0;
                (lCanIdBuf_p + BufferIndex)->CanId = 0;
                (lCanIdBuf_p + BufferIndex)->SduLength = 0;
                (lCanIdBuf_p + BufferIndex)->swPduHandle = 0;
            }
            CanIf_Lok_TxBufferRam_ast[lBufferId].last_index   = 0xFF;
            CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus  = CANIF_TXBUFFER_EMPTY;
        }
    }

    for(TxPduIdArrayIndex = 0 ; TxPduIdArrayIndex < (lCtrlConfig_pst->TotalTxPduCount) ; TxPduIdArrayIndex++ )
    {
     lTxPduId = *(TxPduId_ptr + TxPduIdArrayIndex);
     CanIf_Lok_TxPduRam_ast[lTxPduId].pdu_buffered_flag = FALSE;

    }
#else

	for ( lBufferArrayIndex=0; lBufferArrayIndex < CANIF_TOTAL_TXBUFFERS; lBufferArrayIndex++ )
	{
	    lBufferConfig_pst = CanIf_Lok_ConfigSet_tpst->CanIf_TxBufferConfigPtr + lBufferArrayIndex;

	    if( ( lBufferConfig_pst->CanIf_HthConfigPtr->getCtrlCfg()  == ControllerId ) &&
	        ( lBufferConfig_pst->CanIf_HthConfigPtr->CanHandleType == CANIF_BASIC  ) )
	    {
	        lDataBuf_p  = lBufferConfig_pst->DataBuf;
            lCanIdBuf_p = lBufferConfig_pst->CanIdBuf;
            lDataMaxLen = lBufferConfig_pst->CanIfBufferMaxDataLength;
            lBufferSize = lBufferConfig_pst->CanIfBufferSize;
            lBufferId   = lBufferConfig_pst->CanIfBufferId;

            if ( CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus != CANIF_TXBUFFER_EMPTY )
            {
                for( BufferIndex = 0 ; BufferIndex < lBufferSize ; BufferIndex++ )
                {

                    *(lDataBuf_p + ((BufferIndex)*(lDataMaxLen+1)) + 0) = 0xFF;
                    for( lDataIndex=1; lDataIndex < (lDataMaxLen + 1); lDataIndex++ )
                    {
                       *(lDataBuf_p + ((BufferIndex)*(lDataMaxLen + 1)) + lDataIndex) = 0;
                    }

                    (lCanIdBuf_p + BufferIndex)->BufferIndex = 0;
                    (lCanIdBuf_p + BufferIndex)->CanId       = 0;
                    (lCanIdBuf_p + BufferIndex)->SduLength   = 0;
                    (lCanIdBuf_p + BufferIndex)->swPduHandle = 0;

                }
                CanIf_Lok_TxBufferRam_ast[lBufferId].last_index    = 0xFF;
                CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus  = CANIF_TXBUFFER_EMPTY;
            }

            for( lHthTxPduMapTblArryIndex = 0;
                 lHthTxPduMapTblArryIndex < lBufferConfig_pst->CanIf_HthConfigPtr->NumTxPdus;
                 lHthTxPduMapTblArryIndex++ )
            {
                lTxPduId = lBufferConfig_pst->CanIf_HthConfigPtr->HthTxPduMapTblPtr[lHthTxPduMapTblArryIndex];
                CanIf_Lok_TxPduRam_ast[lTxPduId].pdu_buffered_flag = FALSE;
            }
	    }

	}

#endif
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_Lok_BufferInit(void)
{
    P2VAR(uint8,AUTOMATIC, AUTOMATIC)   lDataBuf_p;

    P2VAR (CanIf_Cfg_CanIdBuffer_tst, AUTOMATIC, AUTOMATIC) lCanIdBuf_p;

    VAR (uint32, AUTOMATIC) lBufferCustId;
    VAR (uint32, AUTOMATIC) lBufferId;
    const CanIf_Cfg_TxBufferConfig_tst* lCanIf_TxBufferConfig_p;

    VAR(uint8, AUTOMATIC)lBufferSize;
    VAR(uint8, AUTOMATIC)lDataIndex;
    VAR(uint8, AUTOMATIC)BufferIndex;
    VAR(uint8, AUTOMATIC)lDataMaxLen;
    VAR(uint32, AUTOMATIC)TxPduId;

    lCanIf_TxBufferConfig_p = CanIf_Lok_ConfigSet_tpst->CanIf_TxBufferConfigPtr;

     for(lBufferCustId = 0; lBufferCustId < CanIf_Lok_ConfigSet_tpst->NumOfTxBuffers; lBufferCustId++)
     {

         lDataBuf_p    = (lCanIf_TxBufferConfig_p + lBufferCustId)->DataBuf;

         lCanIdBuf_p  = (lCanIf_TxBufferConfig_p + lBufferCustId)->CanIdBuf;
         lDataMaxLen  = (lCanIf_TxBufferConfig_p + lBufferCustId)->CanIfBufferMaxDataLength;

         lBufferSize = (lCanIf_TxBufferConfig_p + lBufferCustId)->CanIfBufferSize;
         lBufferId = (lCanIf_TxBufferConfig_p + lBufferCustId)->CanIfBufferId;
         for(BufferIndex = 0 ; BufferIndex < lBufferSize ; BufferIndex++ )
         {

             *(lDataBuf_p + (BufferIndex*(lDataMaxLen + 1)) + 0)    = 0xFF;
              for(lDataIndex=1; lDataIndex < (lDataMaxLen + 1); lDataIndex++)
              {
                  *(lDataBuf_p + (BufferIndex*(lDataMaxLen + 1)) + lDataIndex) = 0;
              }

             (lCanIdBuf_p + BufferIndex)->BufferIndex = 0;
             (lCanIdBuf_p + BufferIndex)->CanId = 0;
             (lCanIdBuf_p + BufferIndex)->SduLength = 0;
             (lCanIdBuf_p + BufferIndex)->swPduHandle = 0;
         }
         CanIf_Lok_TxBufferRam_ast[lBufferId].last_index   = 0xFF;
         CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus  = CANIF_TXBUFFER_EMPTY;
     }

     for(TxPduId = 0 ; TxPduId < (CanIf_Lok_ConfigSet_tpst->NumOfTxPdus) ; TxPduId++ )
     {
         CanIf_Lok_TxPduRam_ast[TxPduId].pdu_buffered_flag = FALSE;
     }
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_Lok_ReadTxBuffer(const CanIf_Cfg_TxBufferConfig_tst* CanIf_TxBufferConfig, Can_PduType* Pdu)
{

    P2VAR(uint8,AUTOMATIC, AUTOMATIC)   lDataBuf_p;
    P2VAR (CanIf_Cfg_CanIdBuffer_tst, AUTOMATIC, AUTOMATIC) lCanIdBuf_p;
    VAR(uint32, AUTOMATIC)lBufferId;
    VAR(uint8, AUTOMATIC)lDataMaxLen;
    VAR(uint8 ,AUTOMATIC)lDataLen;
    VAR(uint8, AUTOMATIC)lDataIndex;
    P2VAR (uint8, AUTOMATIC, AUTOMATIC) lSduPtr;
    VAR(uint8 ,AUTOMATIC)lSduReadIndex;
    VAR(uint8 ,AUTOMATIC)lCanIdReadIndex;
    VAR(Std_ReturnType ,AUTOMATIC)lRetValue;

#if(CANIF_TRIGGERTRANSMIT_SUPPORT == STD_ON)
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, AUTOMATIC) lTxPduConfig_pst;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
#endif

    lDataBuf_p  = CanIf_TxBufferConfig->DataBuf;
    lCanIdBuf_p = CanIf_TxBufferConfig->CanIdBuf;
    lBufferId   = CanIf_TxBufferConfig->CanIfBufferId;
    lDataMaxLen = CanIf_TxBufferConfig->CanIfBufferMaxDataLength;

    lCanIdReadIndex = CanIf_Lok_TxBufferRam_ast[lBufferId].last_index;
    lSduReadIndex   = lCanIdBuf_p[lCanIdReadIndex].BufferIndex;

    if (CanIf_Lok_TxBufferRam_ast[lBufferId].bufferstatus  == CANIF_TXBUFFER_EMPTY)
    {
        lRetValue =  E_NOT_OK;

    }
    else
    {

          Pdu->id          = (lCanIdBuf_p + lCanIdReadIndex)->CanId;
          Pdu->swPduHandle = (lCanIdBuf_p + lCanIdReadIndex)->swPduHandle;

          lSduPtr = Pdu->sdu;

#if(CANIF_TRIGGERTRANSMIT_SUPPORT == STD_ON)

          ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[Pdu->swPduHandle];
          lTxPduConfig_pst    = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

          if(lTxPduConfig_pst->TxPduTriggerTransmit == TRUE)

          {
              lSduPtr     = NULL_PTR;
              Pdu->length = 0;
          }
          else
#endif
          {
              Pdu->length      = (lCanIdBuf_p + lCanIdReadIndex)->SduLength;

              if(Pdu->length > lDataMaxLen)
              {
                  lDataLen = lDataMaxLen;
              }
              else
              {
                  lDataLen = Pdu->length;
              }

              for(lDataIndex=1; lDataIndex < (lDataLen + 1); lDataIndex++)
              {
                  *(lSduPtr + (lDataIndex-1)) = *(lDataBuf_p + ((lSduReadIndex)*(lDataMaxLen+1)) + lDataIndex);
              }

          }

          lRetValue = E_OK;
    }
    return(lRetValue);

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

static FUNC(void, CANIF_CODE) CanIf_Lok_GetFreeTxBufferIndex
                                                (
                                                P2VAR(uint8, AUTOMATIC, CANIF_APPL_DATA) lFreeIndex,
                                                P2CONST(CanIf_Cfg_TxBufferConfig_tst, AUTOMATIC, CANIF_APPL_DATA) TxBufferConfig_pst
                                                )

{
    VAR(uint8 ,AUTOMATIC)Index;
    VAR(uint8, AUTOMATIC)lBufferSize;
    VAR(uint8 ,AUTOMATIC)lDataMaxLen;
    P2VAR(uint8,AUTOMATIC, AUTOMATIC)  lDataBuf_p;

    lBufferSize = TxBufferConfig_pst->CanIfBufferSize;
    lDataMaxLen = TxBufferConfig_pst->CanIfBufferMaxDataLength;
    lDataBuf_p  = TxBufferConfig_pst->DataBuf;

    for(Index = 0; Index < lBufferSize; Index++)
    {
        if(*(lDataBuf_p + ((Index)*(lDataMaxLen+1)) + 0) == 0xFF)
        {
            *lFreeIndex = Index;
            break;
        }
    }
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
FUNC(void, CANIF_CODE) CanIf_Lok_WriteRxBuffer(P2CONST (uint8, AUTOMATIC, CANIF_APPL_CONST) CanSduPtr,
                                              P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst,
                                              CONST(PduLengthType,AUTOMATIC)CanDlc, CONST(Can_IdType,AUTOMATIC)CanId
                                               )
{

    VAR(uint8_least, AUTOMATIC) Index_u8;

    P2VAR(uint8, AUTOMATIC, AUTOMATIC)RxTemBuff_pu8;

    VAR(uint8, AUTOMATIC) SduLength_u8 = 0;

    VAR(PduLengthType, AUTOMATIC) Dlc_u8 = 0;

    VAR(PduLengthType, AUTOMATIC) ConfigRxPduDlc_u8;

    #if(CANIF_METADATA_SUPPORT == STD_ON)

    VAR(Can_IdType,AUTOMATIC)CanIdNoIdType_t;

    CanIdNoIdType_t = CanId & CANIF_PRV_MSB_BIT_RESET;
   #endif

    if(RxPduCfg_pcst->RxBuffer_u16 != (uint16)0xFFFFu)
    {
        RxTemBuff_pu8 = &CanIf_Lok_RxBuffer_tau8[RxPduCfg_pcst->RxBuffer_u16];

#if ( CANIF_RB_CALIBRATION == STD_ON )
        if( RxPduCfg_pcst->getRxPduDlc != NULL_PTR )
        {
            ConfigRxPduDlc_u8 = RxPduCfg_pcst->getRxPduDlc();
        }
        else
#endif
        {
            ConfigRxPduDlc_u8 = RxPduCfg_pcst->RxPduDlc_u8;
        }

        if( CanDlc < ConfigRxPduDlc_u8 )
        {
            Dlc_u8 = CanDlc;

            #if(CANIF_METADATA_SUPPORT == STD_ON)
            SduLength_u8 = (uint8)(CanDlc +RxPduCfg_pcst->MetadataLength_u8);
            #else
            SduLength_u8 = (uint8)(CanDlc);
            #endif
        }
        else
        {
            Dlc_u8 = ConfigRxPduDlc_u8;

            #if(CANIF_METADATA_SUPPORT == STD_ON)
            SduLength_u8 = (uint8)(ConfigRxPduDlc_u8 + RxPduCfg_pcst->MetadataLength_u8);
            #else
            SduLength_u8 = (uint8)(ConfigRxPduDlc_u8);
            #endif
        }

        SchM_Enter_CanIf_RxBufAccessNoNest();

        *(RxTemBuff_pu8) = SduLength_u8;

        for(Index_u8 = 1; Index_u8 <= Dlc_u8; Index_u8++)
        {
            *(RxTemBuff_pu8 + Index_u8) = *CanSduPtr;
            CanSduPtr++;
        }

        #if(CANIF_METADATA_SUPPORT == STD_ON)
        if(RxPduCfg_pcst->MetadataLength_u8 >= 1u)
        {

            for(Index_u8 = Dlc_u8+1u; Index_u8 <= SduLength_u8 ; Index_u8++)
            {
                *(RxTemBuff_pu8 + Index_u8) = (uint8)(CanIdNoIdType_t & 0x00ffu);
                CanIdNoIdType_t = (CanIdNoIdType_t>>SHIFT_8);
            }
        }
        #endif

        SchM_Exit_CanIf_RxBufAccessNoNest();
    }
}
#endif
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
FUNC(void, CANIF_CODE) CanIf_Lok_ReadRxBuffer(P2VAR (PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr,
                                            P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfgPtr)
{

    P2VAR(uint8, AUTOMATIC, AUTOMATIC) PduData_p;

    VAR(uint16_least, AUTOMATIC) Index_u16;

    P2VAR(uint8, AUTOMATIC, AUTOMATIC)RxBuffPtr_Temp;

    PduData_p = PduInfoPtr->SduDataPtr;

    if(RxPduCfgPtr->RxBuffer_u16 != 0xFFFFu)
    {

        RxBuffPtr_Temp = &CanIf_Lok_RxBuffer_tau8[RxPduCfgPtr->RxBuffer_u16];

        SchM_Enter_CanIf_RxBufAccessNoNest();

        PduInfoPtr->SduLength = *(RxBuffPtr_Temp);

        for(Index_u16 = 1; Index_u16 <= PduInfoPtr->SduLength; Index_u16++ )
        {
            *PduData_p = *(RxBuffPtr_Temp + Index_u16);
            PduData_p++;
        }

        SchM_Exit_CanIf_RxBufAccessNoNest();
    }
}
#endif
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
