

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TX_SIGNALGROUP_ARRAY

# ifdef COM_EffectiveSigGrpTOC
LOCAL_INLINE void Com_InternalSigGrpArrayTrigOnChange(Com_SignalGroupIdType SignalGroupId);
# endif

# define COM_START_SEC_CODE
# include "Com_MemMap.h"
uint8 Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, const uint8 * SignalGroupArrayPtr)
{
    Com_TxIpduConstPtrType              TxIpduConstPtr;
# ifdef COM_TP_IPDUTYPE
    Com_TxIpduRamPtrType                TxIpduRamPtr;
# endif
    Com_TxSigGrpConstPtrType            TxSigGrpConstPtr;
    Com_TxSigGrpArrayConstPtrType       TxSigGrpArrayConstPtr;
    uint8                               ConstxSignalGrpFields;
# ifdef COM_EffectiveSigGrpTOC
    uint8                               transferProperty_u8;
# endif
    uint8                               returnValue_u8;

    returnValue_u8 = COM_SERVICE_NOT_AVAILABLE;

# if(COM_CONFIGURATION_USE_DET == STD_ON)
    if (Com_Lok_DETCheck_Param_Ptr((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP),(SignalGroupArrayPtr == NULL_PTR),
                                                                                COMServiceId_SendSignalGroupArray))
# endif
    {

        SignalGroupId         = COM_GET_TXSIGNALGRP_ID( SignalGroupId );
        TxSigGrpConstPtr      = COM_GET_TXSIGGRP_CONSTDATA( SignalGroupId );
        ConstxSignalGrpFields = TxSigGrpConstPtr->txSignalGrpFields;

        if ( Com_GetValue(TXSIGGRP,_ARRAYACCESS,ConstxSignalGrpFields) )
        {
            Com_IpduIdType IpduId_ui;
            IpduId_ui    = TxSigGrpConstPtr->IpduRef;
# ifdef COM_TP_IPDUTYPE
            TxIpduRamPtr = &COM_GET_TXPDURAM_S( IpduId_ui );
# endif

# ifdef COM_TP_IPDUTYPE
            if ( Com_GetRamValue(TXIPDU,_LARGEDATAINPROG, TxIpduRamPtr->Com_TxFlags) == COM_TRUE )
            {
                returnValue_u8 = COM_BUSY;
            }
            else
# endif
            {
                TxIpduConstPtr        = COM_GET_TX_IPDU_CONSTDATA( IpduId_ui );
                TxSigGrpArrayConstPtr = COM_GET_TXSIGGRP_ARRAY_CONSTDATA( TxSigGrpConstPtr->SigGrpArray_Index );

                SchM_Enter_Com_TxIpduProtArea(SENDSIGNALGRP);

                Com_ByteCopy( ( uint8 * )( TxIpduConstPtr->BuffPtr + TxSigGrpArrayConstPtr->FirstByteNo ),
                        ( const uint8 * )( SignalGroupArrayPtr ),
                              ( uint32  )( TxSigGrpArrayConstPtr->Length ) );

                SchM_Exit_Com_TxIpduProtArea(SENDSIGNALGRP);

# ifdef COM_EffectiveSigGrpTOC
                transferProperty_u8 = Com_GetValue(TXSIGGRP,_TP,ConstxSignalGrpFields);

                if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(transferProperty_u8))
                {

                    Com_InternalSigGrpArrayTrigOnChange( SignalGroupId );
                }
                else
                {

                }
# endif

                returnValue_u8 = Com_InternalSendSignalGroup( SignalGroupId );
            }
        }
    }
   return returnValue_u8;
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

# ifdef COM_EffectiveSigGrpTOC

LOCAL_INLINE void Com_InternalSigGrpArrayTrigOnChange(Com_SignalGroupIdType SignalGroupId)
{
    Com_TxIpduConstPtrType          TxIpduConstPtr;
    Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
    Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
    Com_TxSigGrpRamPtrType          TxSigGrpRamPtr;
    Com_SigMaxType                  TxNewVal_GrpSig;
    uint16_least                    idx_TxGrpSig_u16;
    uint8                           ConstByteValue_u8;
    uint8                           GrpSigType_u8;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);
    TxSigGrpRamPtr   = &COM_GET_TXSIGGRPFLAG(SignalGroupId);

    TxIpduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxSigGrpConstPtr->IpduRef);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

    for ( idx_TxGrpSig_u16 = TxSigGrpConstPtr->No_Of_GrpSig; idx_TxGrpSig_u16 > COM_ZERO; idx_TxGrpSig_u16-- )
    {
        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

        GrpSigType_u8     = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);

        if ( Com_GetValue(TXGRPSIG,_TP,ConstByteValue_u8) )
        {

            TxNewVal_GrpSig = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                                TxGrpSigConstPtr->Bit_Pos,
                                                TxGrpSigConstPtr->BitSize,
                                                TxIpduConstPtr->BuffPtr,
                                                ((GrpSigType_u8 & COM_ONE) != COM_ZERO));

            if ( COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) !=
                                                                            (Com_OldValTrigOnChngType)TxNewVal_GrpSig )
            {

                COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) =
                                                                             (Com_OldValTrigOnChngType)TxNewVal_GrpSig;

                Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr->txSigGrpRAMFields,COM_TRUE);
            }
            else
            {

            }
        }
        else
        {

        }
        TxGrpSigConstPtr++;
    }
}
# endif

#endif
