
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Std_Types.h"
#include "CanIf_Cbk.h"
#include "CanIf_Integration.h"

#if(CANIF_RX_INDICATION_VERSION < 1)
extern CONST(Type_CfgEcuabCanIf_st, CANIF_CONST) CanIf_Config;
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

#if(CANIF_RX_INDICATION_VERSION < 1)
FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                                 VAR(Can_HwHandleType, AUTOMATIC) Hrh,
                                                 VAR(Can_IdType, AUTOMATIC) CanId,
                                                 VAR(uint8, AUTOMATIC) CanDlc,
                                                 P2CONST (uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
                                          )
{
    VAR(Can_HwType, AUTOMATIC) mailbox_tmp;
    VAR(PduInfoType, AUTOMATIC) pduInfo_tmp;
    P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, AUTOMATIC) CanIf_HrhConfig_tmp;
    VAR(uint16, AUTOMATIC) idx;
    VAR(uint16, AUTOMATIC) HrhId_u16;

    //The length may need to be decoded to the actual data length before copying data. See below.
    pduInfo_tmp.SduLength = CanDlc;
    pduInfo_tmp.SduDataPtr = (uint8 *)CanSduPtr;
    mailbox_tmp.Hoh = Hrh;
    mailbox_tmp.CanId = CanId;

    HrhId_u16 =  mailbox_tmp.Hoh;
    CanIf_HrhConfig_tmp = CanIf_Config.HrhConfig_pcst + CanIf_Config.HrhPduIdTable_Ptr[HrhId_u16];
    mailbox_tmp.ControllerId = CanIf_HrhConfig_tmp->ControllerId_u8;

#elif(CANIF_RX_INDICATION_VERSION >= 1)
FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                            P2CONST (Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox,
                                            P2CONST (PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
                                         )
{
#endif

//#if((CANIF_FD_SUPPORT == STD_ON) && (CANIF_RX_INDICATION_VERSION >= 1))
//    const uint8 CAN_FD_LENGTH_MAPPING[]= {12U,16U,20U,24U,32U,48U,64U};
//    VAR(PduInfoType, AUTOMATIC) pduInfo_tmp;
//    pduInfo_tmp.SduDataPtr = PduInfoPtr->SduDataPtr;
//    pduInfo_tmp.SduLength = PduInfoPtr->SduLength;
//
//    if(PduInfoPtr->SduLength > 8)
//    {
//        pduInfo_tmp.SduLength = CAN_FD_LENGTH_MAPPING[PduInfoPtr->SduLength-9];
//    }
//#endif

#if(CANIF_RX_INDICATION_VERSION < 1)
    CanIf_RxIndication_Internal(&mailbox_tmp, &pduInfo_tmp);
#elif(CANIF_RX_INDICATION_VERSION >= 1)
    //When DLC remapping is implemented, fix below function call to:
    //  CanIf_RxIndication_Internal(Mailbox, &pduInfo_tmp);
    CanIf_RxIndication_Internal(Mailbox, PduInfoPtr);
#endif
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

