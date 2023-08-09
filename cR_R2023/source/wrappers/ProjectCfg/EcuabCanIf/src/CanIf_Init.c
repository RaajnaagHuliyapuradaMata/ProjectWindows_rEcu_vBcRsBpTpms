

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_Init(P2CONST (Type_CfgEcuabCanIf_st, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr)
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) controllerState_pst;

    VAR(uint32,AUTOMATIC) index_u32;

#if ( (CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON) || (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON) || \
      (CANIF_PUBLIC_READRXPDU_DATA_API   == STD_ON) || (CANIF_RB_NODE_CALIBRATION                == STD_ON) )
    VAR(uint8_least,AUTOMATIC)pdu_uo;
#endif

    VAR (uint8, AUTOMATIC) numControllers_u8;

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) dynId_pu32;

    VAR(Can_IdType, AUTOMATIC) canId_t;

    VAR (uint32, AUTOMATIC) numTxPduId_u32;

    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) txPduConfig_pcst;

#endif

#if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) dynRxPduId_pu32;

    VAR(Can_IdType, AUTOMATIC) rxpducanId_t;

    VAR (uint32, AUTOMATIC) numRxPduId_u32;

#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)

    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) ctrlConfig_pcst;
#endif

    #if CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC
    CanIf_Lok_ConfigSet_tpst = &CanIf_Config;

    (void) ConfigPtr;
    #else
    CanIf_Lok_ConfigSet_tpst = ConfigPtr;

    CANIF_DET_REPORT_ERROR_VOID_RET((ConfigPtr == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
    #endif

    numControllers_u8 = CanIf_Lok_ConfigSet_tpst->NumCanCtrl_u8;

    controllerState_pst = CanIf_Lok_ControllerState_ast;

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)

    for(pdu_uo = 0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumOfTxPdus; pdu_uo++)
    {
        CanIf_Lok_TxNotification_aen[pdu_uo] = CANIF_NO_NOTIFICATION;
    }
#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    ctrlConfig_pcst = CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr;
#endif

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
                    canId_t |= (((Can_IdType)((txPduConfig_pcst +index_u32)->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);
                    *(dynId_pu32 + ((txPduConfig_pcst +index_u32)->TxPduType)) = canId_t;
                }
            }
#endif

#if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    numRxPduId_u32 = CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t;

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst;

    dynRxPduId_pu32 = &CanIf_DynRxPduCanId_au32[0];

    for(index_u32 = 0; index_u32 < numRxPduId_u32; index_u32++)
    {

        if(((RxPduCfg_pcst + index_u32)->RxPduType) != CANIF_STATIC)
        {

            rxpducanId_t = ((RxPduCfg_pcst +index_u32)->RxPduCanId);
            rxpducanId_t &= CANIF_MSB_BIT_RESET;

            rxpducanId_t |= (((Can_IdType)((RxPduCfg_pcst +index_u32)->CanIdtype_u8))<<CANIF_CANID_BIT_SHIFT);

            *(dynRxPduId_pu32 + ((RxPduCfg_pcst +index_u32)->RxPduType)) = rxpducanId_t;
        }
    }
#endif

    for(index_u32 = 0; index_u32 < numControllers_u8; index_u32++)
    {

        (controllerState_pst + index_u32)->DeviceMode = CANIF_CS_STOPPED;
        (controllerState_pst + index_u32)->ChannelMode = CANIF_OFFLINE;

        #if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
        (controllerState_pst + index_u32)->ValidationSts_b = CANIF_RESET;
        #endif

#if ( (CANIF_RB_NODE_CALIBRATION != STD_ON) && (CANIF_PUBLIC_PN_SUPPORT == STD_ON))
        if((ctrlConfig_pcst + index_u32)->PnCtrlEn == TRUE)
        {
            (controllerState_pst + index_u32)->BlPnTxFilter = TRUE;
        }
        else
        {
            (controllerState_pst + index_u32)->BlPnTxFilter = FALSE;
        }
#endif

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON)

        (controllerState_pst + index_u32)->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;
#endif

    }

#if ( (CANIF_RB_NODE_CALIBRATION == STD_ON) && (CANIF_PUBLIC_PN_SUPPORT == STD_ON))

    for(pdu_uo = 0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumOfTxPdus; pdu_uo++)
    {
        if( CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[pdu_uo].TxPduPnFilterPdu == TRUE )
        {
            (controllerState_pst + CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[pdu_uo].CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->getCtrlCfg())->BlPnTxFilter = TRUE;
        }
    }
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)
    CanIf_Lok_BufferInit();
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
#if CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC
    CanIf_XCore_Init(NULL_PTR);
#else
    CanIf_XCore_Init(CanIf_Lok_ConfigSet_tpst->CanIf_XCoreConfigPtr);
#endif
#endif

    #if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API != STD_OFF)

    for(pdu_uo=CANIF_ZERO; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t; pdu_uo++)
    {
        CanIf_Lok_RxNotification_taen[pdu_uo] = CANIF_NO_NOTIFICATION;
    }
    #endif
    #if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
    for(pdu_uo=CANIF_ZERO; pdu_uo < CANIF_CFG_RX_BUFFER_SIZE; pdu_uo++)
        {
            CanIf_Lok_RxBuffer_tau8[pdu_uo]= 0x00;
        }
    #endif

    CanIf_Lok_InitStatus_b = TRUE;

}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_DeInit(P2CONST (Type_CfgEcuabCanIf_st, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr)
{

#if CANIF_CONFIGURATION_VARIANT != CANIF_CFG_VAR_PC

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) controllerState_pst;

    VAR(uint8_least,AUTOMATIC) index_u32;

#if ( (CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON) || (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API== STD_ON) || \
      (CANIF_PUBLIC_READRXPDU_DATA_API   == STD_ON) || (CANIF_RB_NODE_CALIBRATION                == STD_ON) )
    VAR(uint8_least,AUTOMATIC)pdu_uo;
#endif

    VAR (uint8, AUTOMATIC) numControllers_u8;

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
    P2VAR(uint32,AUTOMATIC,AUTOMATIC) dynId_pu32;

    VAR(Can_IdType, AUTOMATIC) canId_t;

    VAR (uint32, AUTOMATIC) numTxPduId_u32;

    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) txPduConfig_pcst;

#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)

    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) ctrlConfig_pcst;
#endif

#if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

    P2VAR(uint32,AUTOMATIC,AUTOMATIC) dynRxPduId_pu32;

    VAR(Can_IdType, AUTOMATIC) rxpducanId_t;

    VAR (uint32, AUTOMATIC) numRxPduId_u32;

#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((ConfigPtr == NULL_PTR), CANIF_DEINIT_SID, CANIF_E_PARAM_POINTER)
    CanIf_Lok_ConfigSet_tpst = ConfigPtr;

    CanIf_Lok_InitStatus_b = FALSE;
    numControllers_u8 = CanIf_Lok_ConfigSet_tpst->NumCanCtrl_u8;

    controllerState_pst = CanIf_Lok_ControllerState_ast;

    #if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API != STD_OFF)

    for(pdu_uo=0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t; pdu_uo++)
    {
        CanIf_Lok_RxNotification_taen[pdu_uo] = CANIF_NO_NOTIFICATION;
    }
    #endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    ctrlConfig_pcst = CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr;
#endif

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
                    canId_t |= (((Can_IdType)((txPduConfig_pcst +index_u32)->TxPduCanIdType))<<CANIF_CANID_BIT_SHIFT);
                    *(dynId_pu32 + ((txPduConfig_pcst +index_u32)->TxPduType)) = canId_t;
                }
            }
#endif

#if(CANIF_RB_CHANGERXPDUID_API != STD_OFF)

    numRxPduId_u32 = CanIf_Lok_ConfigSet_tpst->NumCanRxPduId_t;

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst;

    dynRxPduId_pu32 = &CanIf_DynRxPduCanId_au32[0];

    for(index_u32 = 0; index_u32 < numRxPduId_u32; index_u32++)
    {

        if(((RxPduCfg_pcst + index_u32)->RxPduType) != CANIF_STATIC)
        {

            rxpducanId_t = ((RxPduCfg_pcst +index_u32)->RxPduCanId);
            rxpducanId_t &= CANIF_MSB_BIT_RESET;

            rxpducanId_t |= (((Can_IdType)((RxPduCfg_pcst +index_u32)->CanIdtype_u8))<<CANIF_CANID_BIT_SHIFT);

            *(dynRxPduId_pu32 + ((RxPduCfg_pcst +index_u32)->RxPduType)) = rxpducanId_t;
        }
    }
#endif

    for(index_u32=0; index_u32 < numControllers_u8; index_u32++)
    {

        (controllerState_pst + index_u32)->DeviceMode = CANIF_CS_STOPPED;
        (controllerState_pst + index_u32)->ChannelMode = CANIF_OFFLINE;

#if ( (CANIF_RB_NODE_CALIBRATION != STD_ON) && (CANIF_PUBLIC_PN_SUPPORT == STD_ON) )
        if((ctrlConfig_pcst + index_u32)->PnCtrlEn == TRUE)
        {
            (controllerState_pst + index_u32)->BlPnTxFilter = TRUE;
        }
        else
        {
            (controllerState_pst + index_u32)->BlPnTxFilter = FALSE;
        }
#endif

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON)

        (controllerState_pst + index_u32)->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;
#endif

    }

#if ( (CANIF_RB_NODE_CALIBRATION == STD_ON) && (CANIF_PUBLIC_PN_SUPPORT == STD_ON) )

    for(pdu_uo = 0; pdu_uo < CanIf_Lok_ConfigSet_tpst->NumOfTxPdus; pdu_uo++)
    {
        if( CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[pdu_uo].TxPduPnFilterPdu == TRUE )
        {
            (controllerState_pst + CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr[pdu_uo].CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->getCtrlCfg())->BlPnTxFilter = TRUE;
        }
    }
#endif

#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
for(pdu_uo=0; pdu_uo < CANIF_CFG_RX_BUFFER_SIZE; pdu_uo++)
    {
        CanIf_Lok_RxBuffer_tau8[pdu_uo]= 0x00;
    }
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)
    CanIf_Lok_BufferInit();
#endif

#else

    (void)ConfigPtr;
#endif
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

