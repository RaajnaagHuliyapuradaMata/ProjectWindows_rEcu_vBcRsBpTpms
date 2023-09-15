

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_METADATA_SUPPORT

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

Std_ReturnType Com_TriggerIPDUSendWithMetaData(Type_SwcServiceCom_tIdPdu PduId, uint8 * MetaData )
{

   Com_TxIpduConstPtrType      TxIpduConstPtr;
    Std_ReturnType              returnVal_uo;

    returnVal_uo = E_NOT_OK;

# if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TriggerIPDUSendWithMetaData))
# endif
   {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA( PduId );

        if(TxIpduConstPtr->MetaDataPtr != NULL_PTR)
        {

            if(Com_CheckTxIPduStatus( PduId ))
            {
                Com_TxIpduRamPtrType TxIpduRamPtr;

                TxIpduRamPtr = &COM_GET_TXPDURAM_S( PduId );

# ifdef COM_TP_IPDUTYPE

                if(COM_TRUE != Com_GetRamValue(TXIPDU, _LARGEDATAINPROG, TxIpduRamPtr->Com_TxFlags))
# endif
                {
                    Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                    sendIpduFlag_u16.isEventTrig      = COM_SET;

                    sendIpduFlag_u16.ignoreRepetitions = COM_SET;

# ifdef COM_TxIPduTimeOut

                    sendIpduFlag_u16.isTimeoutReq = COM_BOOL_TO_UNSIGNED(TxIpduConstPtr->Timeout_Fact != COM_ZERO);
# endif

                    if(NULL_PTR != MetaData)
                    {

                        SchM_Enter_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );

                        Com_ByteCopy( (TxIpduConstPtr->BuffPtr + TxIpduConstPtr->Size)
   ,                                     ((const uint8 * )MetaData)
   ,                                     TxIpduConstPtr->MetaDataPtr->MetaDataLength);

                        Com_SetRamValue(TXIPDU,_METADATA_REQUEST,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

                        SchM_Exit_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );
                    }
                    else
                    {

                    }

                    Com_Lok_SendIpdu( PduId, sendIpduFlag_u16 );

                    returnVal_uo = E_OK;
                }
            }
        }
   }

    return returnVal_uo;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

