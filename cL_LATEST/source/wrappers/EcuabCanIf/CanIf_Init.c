#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_Init(
   P2CONST(Type_CfgEcuabCanIf_st, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr
){
   CanIf_ControllerStateType * controllerState_pst;
   uint32 index_u32;
   uint8_least pdu_uo;
   uint8 numControllers_u8;

#if(CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
   uint32 * dynId_pu32;
   Type_McalCan_tId canId_t;
   uint32 numTxPduId_u32;
   const CanIf_Cfg_TxPduConfig_tst * txPduConfig_pcst;
#endif

#if CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC
   CanIf_Lok_ConfigSet_tpst = &CfgEcuabCanIf_st;
    (void) ConfigPtr;
#else
   CanIf_Lok_ConfigSet_tpst = ConfigPtr;
#endif

    numControllers_u8 = CanIf_Lok_ConfigSet_tpst->NumCanCtrl_u8;
   controllerState_pst = CanIf_Lok_ControllerState_ast;

   for(pdu_uo = 0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumOfTxPdus; pdu_uo++){
        CanIf_Lok_TxNotification_aen[pdu_uo] = CANIF_NO_NOTIFICATION;
   }

#if(CANIF_PUBLIC_SETDYNAMICTXID_API== STD_ON)
    numTxPduId_u32 = CanIf_Lok_ConfigSet_tpst->NumOfTxPdus;

    txPduConfig_pcst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr;

    dynId_pu32 = &CanIf_DynTxPduCanId_au32[0];

            for(index_u32 = 0; index_u32 < numTxPduId_u32; index_u32++)
            {
                if(((txPduConfig_pcst + index_u32)->TxPduType) != CANIF_STATIC)
                {
                    canId_t = ((txPduConfig_pcst +index_u32)->TxPduCanId);
                    canId_t &= CANIF_MSB_BIT_RESET;
                    canId_t |= (((Type_McalCan_tId)((txPduConfig_pcst +index_u32)->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);
                    *(dynId_pu32 + ((txPduConfig_pcst +index_u32)->TxPduType)) = canId_t;
                }
            }
#endif

   for(index_u32 = 0; index_u32 < numControllers_u8; index_u32++)
   {
        (controllerState_pst + index_u32)->Ctrl_Pdu_mode = (((uint8)CANIF_CS_STOPPED)<<CANIF_Ctrl_BIT_SHIFT)|((uint8)CANIF_OFFLINE);
#if(CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON)
        (controllerState_pst + index_u32)->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;
#endif

   }

   for(pdu_uo=CANIF_ZERO; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t; pdu_uo++)
   {
        CanIf_Lok_RxNotification_taen[pdu_uo] = CANIF_NO_NOTIFICATION;
   }
   CanIf_Lok_InitStatus_b = TRUE;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"

void CanIf_DeInit(
   const Type_CfgEcuabCanIf_st* ConfigPtr){
#if CANIF_CONFIGURATION_VARIANT != CANIF_CFG_VAR_PC
   CanIf_ControllerStateType * controllerState_pst;
   uint8_least index_u32;
   uint8_least pdu_uo;
   uint8 numControllers_u8;

#if(CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
   uint32 * dynId_pu32;
   Type_McalCan_tId canId_t;
   uint32 numTxPduId_u32;
   const CanIf_Cfg_TxPduConfig_tst * txPduConfig_pcst;
#endif

   CanIf_Lok_ConfigSet_tpst = ConfigPtr;
   CanIf_Lok_InitStatus_b = FALSE;
    numControllers_u8 = CanIf_Lok_ConfigSet_tpst->NumCanCtrl_u8;
   controllerState_pst = CanIf_Lok_ControllerState_ast;

   for(pdu_uo=0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t; pdu_uo++)
   {
        CanIf_Lok_RxNotification_taen[pdu_uo] = CANIF_NO_NOTIFICATION;
   }

#if(CANIF_PUBLIC_SETDYNAMICTXID_API== STD_ON)
    numTxPduId_u32 = CanIf_Lok_ConfigSet_tpst->NumOfTxPdus;
    txPduConfig_pcst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr;
    dynId_pu32 = &CanIf_DynTxPduCanId_au32[0];
            for(index_u32 = 0; index_u32 < numTxPduId_u32; index_u32++)
            {
                if((txPduConfig_pcst + index_u32)->TxPduType != CANIF_STATIC)
                {
                    canId_t = ((txPduConfig_pcst +index_u32)->TxPduCanId);
                    canId_t &= CANIF_MSB_BIT_RESET;
                    canId_t |= (((Type_McalCan_tId)((txPduConfig_pcst +index_u32)->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);
                    *(dynId_pu32 + ((txPduConfig_pcst +index_u32)->TxPduType)) = canId_t;
                }
            }
#endif

   for(index_u32=0; index_u32 < numControllers_u8; index_u32++)
   {
        (controllerState_pst + index_u32)->Ctrl_Pdu_mode = (((uint8)CANIF_CS_STOPPED)<<CANIF_Ctrl_BIT_SHIFT)|((uint8)CANIF_OFFLINE);
#if(CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON)
        (controllerState_pst + index_u32)->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;
#endif
   }
#else

    (void)ConfigPtr;
#endif
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

