

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#if defined COM_METADATA_SUPPORT
# define COM_START_SEC_CODE
# include "Com_MemMap.h"

FUNC( Std_ReturnType, COM_CODE ) Com_TriggerIPDUSendWithMetaData( VAR( PduIdType, AUTOMATIC ) PduId,
                                                     P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) MetaData )
{
    VAR( Std_ReturnType, AUTOMATIC ) returnVal_uo;
    returnVal_uo = E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if( Com_Lok_DETCheck_Param( (PduId >= COM_GET_NUM_TX_IPDU) , COMServiceId_TriggerIPDUSendWithMetaData) )
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        if ( Com_CheckTxIPduStatus( (PduIdType)PduId ) )
        {
            Com_TxIpduConstPtrType TxIPduConstPtr;

            TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA( PduId );

            if ( Com_GetValue( TXIPDU, _ISMETADATASUPPORTED, TxIPduConstPtr->txIPduFields ) )
            {
                Com_TxIpduRamPtrType TxIpduRamPtr;

                TxIpduRamPtr = &COM_GET_TXPDURAM_S( PduId );

#ifdef COM_TP_IPDUTYPE
                if ( COM_TRUE != Com_GetRamValue( TXIPDU, _LARGEDATAINPROG, TxIpduRamPtr->Com_TxFlags ) )
#endif
                {
                    P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) MetaDataConstPtr;
                    Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                    sendIpduFlag_u16.isEventTrig      = COM_SET;
                    sendIpduFlag_u16.isTriggerIpduSendWithMetadata = COM_SET;

                    sendIpduFlag_u16.ignoreRepetitions = COM_SET;

    #  ifdef COM_TxIPduTimeOut

                    sendIpduFlag_u16.isTimeoutReq = (0u != TxIPduConstPtr->Timeout_Fact)? COM_SET : COM_RESET;

    #  endif

                MetaDataConstPtr = (NULL_PTR == MetaData) ? ((P2CONST( uint8, AUTOMATIC, COM_APPL_CONST))( &TxIPduConstPtr->MetaDataPtr->MetaDataDefaultValue[0] )) : \
                                        (( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )( MetaData ));

                SchM_Enter_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );

                Com_ByteCopy(
                ( P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) )( TxIPduConstPtr->BuffPtr + TxIPduConstPtr->Size ),
                ( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )( MetaDataConstPtr ),
                                                            ( TxIPduConstPtr->MetaDataPtr->MetaDataLength ) );

                SchM_Exit_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );

                Com_Lok_SendIpdu( PduId, sendIpduFlag_u16 );
                returnVal_uo = E_OK;

                }
            }
        }
    }

    return returnVal_uo;
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"
#endif

