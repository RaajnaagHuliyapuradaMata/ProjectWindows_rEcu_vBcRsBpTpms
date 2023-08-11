
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "CanIf_Integration.h"
#include "Std_Types.h"
#include "CanIf_Prv.h"
#if((CANIF_FD_SUPPORT == STD_ON) && (CANIF_WRITE_INTEGRATION_VERSION < 1U))
#include "rba_BswSrv.h"
#endif

#if((CANIF_FD_SUPPORT == STD_ON) && (CANIF_WRITE_INTEGRATION_VERSION < 1U))

// #define CANFD_PADDING_VALUE             0U

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
// uint8 CanIf_Pdu_Buffer[64];
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Can_ReturnType CanIf_Write_Integration(Can_HwHandleType Hth, const Can_PduType* PduInfoPtr)
{
    Can_ReturnType  lCanStatus_en = CAN_NOT_OK;

#if((CANIF_FD_SUPPORT == STD_ON) && (CANIF_WRITE_INTEGRATION_VERSION < 1U))
    // uint8 FdPaddingByte;
    //
    // uint8 index_u8;
    // Can_PduType pduInfo_tmp;

    //
    // index_u8 = 0;
    //
    // FdPaddingByte = CANFD_PADDING_VALUE;

    // pduInfo_tmp.id = PduInfoPtr->id;
    // pduInfo_tmp.length = PduInfoPtr->length;
    // pduInfo_tmp.sdu = (uint8 *)CanIf_Pdu_Buffer;
    // (void)rba_BswSrv_MemCopy(pduInfo_tmp.sdu, PduInfoPtr->sdu, pduInfo_tmp.length);
    // pduInfo_tmp.swPduHandle = PduInfoPtr->swPduHandle;

    //
    // if((PduInfoPtr->length > 8U) && (PduInfoPtr->length <= 12U)) pduInfo_tmp.length = 12U;
    // else if((PduInfoPtr->length > 12U) && (PduInfoPtr->length <= 16U)) pduInfo_tmp.length = 16U;
    // else if((PduInfoPtr->length > 16U) && (PduInfoPtr->length <= 20U)) pduInfo_tmp.length = 20U;
    // else if((PduInfoPtr->length > 20U) && (PduInfoPtr->length <= 24U)) pduInfo_tmp.length = 24U;
    // else if((PduInfoPtr->length > 24U) && (PduInfoPtr->length <= 32U)) pduInfo_tmp.length = 32U;
    // else if((PduInfoPtr->length > 32U) && (PduInfoPtr->length <= 48U)) pduInfo_tmp.length = 48U;
    // else if((PduInfoPtr->length > 48U) && (PduInfoPtr->length <= 64U)) pduInfo_tmp.length = 64U;

    //
    // for(i = PduInfoPtr->length; i < pduInfo_tmp.length; i++)
    // {
        // pduInfo_tmp.sdu[i] = FdPaddingByte;
    // }

    //
    // pduInfo_tmp.id |= ((uint32)(1u<<14U));
#endif

#if((CANIF_FD_SUPPORT == STD_ON) && (CANIF_WRITE_INTEGRATION_VERSION < 1U))
    //When DLC remapping is implemented, fix below function call to:
    //lCanStatus_en =  Can_Write(Hth, &pduInfo_tmp);
    lCanStatus_en =  Can_Write(Hth, PduInfoPtr);
#elif ((CANIF_FD_SUPPORT == STD_OFF) && (CANIF_WRITE_INTEGRATION_VERSION < 1U))
    lCanStatus_en =  Can_Write(Hth, PduInfoPtr);
#elif(CANIF_WRITE_INTEGRATION_VERSION >= 1)
    lCanStatus_en =  Can_Write(Hth, PduInfoPtr);
#endif

    return lCanStatus_en;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

