

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TX_SIGNALGROUP

# define COM_START_SEC_CODE
# include "Com_MemMap.h"
uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
#ifdef COM_TP_IPDUTYPE
    Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
#endif
    uint8                           Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if(Com_Lok_DETCheck_Param((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_SendSignalGroup))
#endif
    {

        SignalGroupId    = COM_GET_TXSIGNALGRP_ID(SignalGroupId);
#ifdef COM_TP_IPDUTYPE
        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA( SignalGroupId );
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,COM_GET_TXPDURAM_S(TxSigGrpConstPtr->IpduRef).Com_TxFlags) == COM_TRUE)
        {
            Status = COM_BUSY;
        }
        else
#endif
        {
            Status = Com_InternalSendSignalGroup(SignalGroupId);
        }

    }
    return Status;
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

# define COM_START_SEC_CODE
# include "Com_MemMap.h"
uint8 Com_InternalSendSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
#ifdef COM_EffectiveSigGrpTOC

    Com_TxSigGrpRamPtrType          TxSigGrpRamPtr;
#endif

    Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)

    Com_TxIpduConstPtrType          TxIpduConstPtr;
    #endif
    uint16_least                    IpduId_ui;
    uint8                           ConstByteValue_u8;
    uint8                           Status;
    uint8                           isSigTriggered_u8;
#if (defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition) || defined(COM_EffectiveSigGrpTOC))
    uint8                           transferProperty_u8;
#endif

    Status              = E_OK;
    isSigTriggered_u8   = COM_RESET;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

    IpduId_ui = TxSigGrpConstPtr->IpduRef;
    ConstByteValue_u8 = TxSigGrpConstPtr->txSignalGrpFields;

#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

#endif

#ifdef COM_EffectiveSigGrpTOC
    TxSigGrpRamPtr = &COM_GET_TXSIGGRPFLAG(SignalGroupId);
#endif

    SchM_Enter_Com_TxIpduProtArea(SENDSIGNALGRP);

#ifdef COM_TX_SIGNALGROUP_ARRAY
    if (Com_GetValue(TXSIGGRP,_ARRAYACCESS,ConstByteValue_u8) == COM_FALSE)
#endif
    {
        Com_ShadowBuffToIpduBuff(SignalGroupId);
    }
#ifdef COM_TX_SIGNALGROUP_ARRAY
    else
    {

    }
#endif

#ifdef COM_TxSigGrpUpdateBit

    if(Com_GetValue(TXSIGGRP,_UPDBITCONF,ConstByteValue_u8))
    {
        PduLengthType ByteNo_u8;

        ByteNo_u8 = (PduLengthType)((TxSigGrpConstPtr->Update_Bit_Pos)>>3u);

        Com_SetUpdateBitValue(TxIpduConstPtr,TxSigGrpConstPtr->Update_Bit_Pos,ByteNo_u8)
    }
#endif
    SchM_Exit_Com_TxIpduProtArea(SENDSIGNALGRP);

#if (defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition) || defined(COM_EffectiveSigGrpTOC))
    transferProperty_u8 = Com_GetValue(TXSIGGRP,_TP,ConstByteValue_u8);
#endif

#if defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition)

    if (COM_SIG_TP_IS_TRIGGERED(transferProperty_u8))
    {
        isSigTriggered_u8 = COM_SET;
    }
    else
#endif
    {
#ifdef COM_EffectiveSigGrpTOC

        if (COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(transferProperty_u8) &&
           (Com_GetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr ->txSigGrpRAMFields) != COM_FALSE))
        {

            isSigTriggered_u8 = COM_SET;

            Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr->txSigGrpRAMFields,COM_FALSE);
        }
#endif
    }

    if(Com_CheckTxIPduStatus((PduIdType)IpduId_ui))
    {

        Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.isSigTriggered = isSigTriggered_u8;

#ifdef COM_TxFilters

        if(Com_GetValue(TXSIGGRP,_FILTEREVALREQ,ConstByteValue_u8) != COM_FALSE)
        {

            sendIpduFlag_u16.isModeChangd = COM_BOOL_TO_UNSIGNED(Com_Lok_SigGrpTxChangeMode(SignalGroupId));
        }
#endif

#ifdef COM_TxIPduTimeOut
        sendIpduFlag_u16.isTimeoutReq = COM_BOOL_TO_UNSIGNED(Com_GetValue(TXSIGGRP,_TOENABLED,ConstByteValue_u8));
#endif

#if defined(COM_SigGrpTriggeredOnChangeWithoutRepetition) || defined(COM_SigGrpTriggeredWithoutRepetition)
        if (COM_SIG_TP_IS_WITHOUT_REPETITION(transferProperty_u8))
        {

            sendIpduFlag_u16.ignoreRepetitions = COM_SET;
        }
#endif

        Com_Lok_ProceedToSendIpdu( (Com_IpduIdType)IpduId_ui, sendIpduFlag_u16 );

    }
    else
    {
        Status = COM_SERVICE_NOT_AVAILABLE;
    }

    return (Status);
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

#endif

