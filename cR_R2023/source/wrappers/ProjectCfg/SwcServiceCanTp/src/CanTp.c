

#include "CanTp.h"
#include "CanTp_Cbk.h"
#include "CanTp_Prv.h"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

uint8 CanTp_MainState;

#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

#if(CANTP_VERSION_INFO_API == STD_ON)

void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    if(versioninfo == NULL_PTR)
    {
        CanTp_Lok_ReportRunTimeError(CANTP_GETVERSIONINFO, CANTP_E_PARAM_POINTER);
    }
    else
    {
        versioninfo->vendorID            = CANTP_VENDOR_ID;
        versioninfo->moduleID            = CANTP_MODULE_ID;
        versioninfo->sw_major_version    = CANTP_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version    = CANTP_SW_MINOR_VERSION;
        versioninfo->sw_patch_version    = CANTP_SW_PATCH_VERSION;
    }
}
#endif

void CanTp_Init(const Type_CfgSwcServiceCanTp_st *CfgPtr)
{
    CanTp_MainState = CANTP_OFF;

    #if(CANTP_VARIANT == CANTP_PRE_COMPILE)
    CanTp_CfgPtr = &CanTp_Config;
    (void)CfgPtr;
	#else
    CanTp_CfgPtr = CfgPtr;

    if(CfgPtr == NULL_PTR)
    {
        CanTp_Lok_ReportRunTimeError(CANTP_INIT, CANTP_E_PARAM_POINTER);
    }
    #if((CANTP_DEV_ERROR_DETECT == CANTP_ON) && (CANTP_VARIANT == CANTP_POST_BUILD_SELECTABLE))
    else if(CanTp_Lok_PbCfgCheck(CfgPtr) != E_OK)
    {
        CanTp_Lok_ReportError(CANTP_INIT, CANTP_E_INIT_FAILED);
    }
    #endif
    else
    #endif
    {
        CanTp_Lok_RxParamInit();
        CanTp_Lok_QInit();

		CanTp_Lok_ArrayInit(&CanTp_SubState[0], CanTp_CfgPtr->NumberOfChannels, CANTP_IDLE);
        CanTp_Lok_ArrayInit(&CanTp_TxConfirmationChannel[0], CanTp_CfgPtr->NumberOfTxPdus, CANTP_INVALID_CHANNEL);

		CanTp_MainState = CANTP_ON;
    }
}

#if(CANTP_CANTPLITE_SUPPORT != STD_ON)

void CanTp_Shutdown(void)
{
    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_MainState != CANTP_ON)
    {
        CanTp_Lok_ReportError(CANTP_SHUTDOWN, CANTP_E_UNINIT);
    }
    else
    #endif
    {
        CanTp_MainState = CANTP_OFF;
        CanTp_Lok_RxParamInit();
        CanTp_Lok_QInit();

        CanTp_Lok_ArrayInit(&CanTp_SubState[0], CanTp_CfgPtr->NumberOfChannels, CANTP_IDLE);
        CanTp_Lok_ArrayInit(&CanTp_TxConfirmationChannel[0], CanTp_CfgPtr->NumberOfTxPdus, CANTP_INVALID_CHANNEL);
        CanTp_CfgPtr = NULL_PTR;
    }
}
#endif

void CanTp_MainFunction(void)
{
    CanTp_ChannelIdType ChannelId;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_MainState != CANTP_ON)
    {
        CanTp_Lok_ReportError(CANTP_MAINFUNCTION, CANTP_E_UNINIT);
    }
    else
    #endif
    {
        #if(CANTP_TX_BURST_MODE == CANTP_ON)
        if(CanTp_Lok_GetFromQ(&ChannelId) == E_OK)
        {
            CanTp_Lok_ExecuteState(ChannelId);
        }
        else
        #endif
        {
            for(ChannelId = 0; ChannelId < CanTp_CfgPtr->NumberOfChannels; ChannelId++)
            {
                CanTp_Lok_ExecuteState(ChannelId);
            }

            CanTp_IncrementCounter();
        }
    }
}

#if(CANTP_CHANGE_PARAMETER_API == CANTP_ON)

Std_ReturnType CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
	CanTp_ChannelIdType ChannelId;
    Std_ReturnType RetVal = E_NOT_OK;

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
	if(CanTp_Lok_IsNoDevError(id, CANTP_CHANGEPARAMETER, CANTP_E_INVALID_RX_ID))
	#endif
	{
		if(CanTp_Lok_IsChangeParameterOk(parameter, value))
		{
            ChannelId = CanTp_Lok_GetRxChannelId(id);

            SchM_Enter_CanTp_EXCLUSIVE_AREA();

			if(CanTp_Lok_GetState(ChannelId) == CANTP_RECEPTION)
			{
				CanTp_Lok_ReportRunTimeError(CANTP_CHANGEPARAMETER, CANTP_E_OPER_NOT_SUPPORTED);
			}
			else
			{
				CanTp_ParamPair[id].Param[(parameter == TP_STMIN) ? 0 : 1] = (uint8)value;
				RetVal=E_OK;
			}

            SchM_Exit_CanTp_EXCLUSIVE_AREA();
		}
	}

    return RetVal;
}
#endif

#if(CANTP_READ_PARAMETER_API == CANTP_ON)

Std_ReturnType CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16 *value)
{
    Std_ReturnType RetVal = E_NOT_OK;

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(id, CANTP_READPARAMETER, CANTP_E_INVALID_RX_ID))
	#endif
	{
		if(value == NULL_PTR)
        {
		    CanTp_Lok_ReportRunTimeError(CANTP_READPARAMETER, CANTP_E_PARAM_POINTER);
        }
        else if((parameter != TP_BS) && (parameter != TP_STMIN))
        {
            CanTp_Lok_ReportRunTimeError(CANTP_READPARAMETER, CANTP_E_PARAM_ID);
        }
        else
		{
			*value = CanTp_Lok_GetRxParam(id, parameter);
			RetVal = E_OK;
		}
	}

    return(RetVal);
}
#endif

Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType *CanTpTxInfoPtr)
{
    Std_ReturnType RetVal = E_NOT_OK;
    CanTp_TickType Value = 0;
    CanTp_TickType ElapsedValue;
	uint16 MaxLength;
    uint8 PciId;
    uint8 ErrorId;
	uint8 PayloadLength;
	uint8 TX_DL;
    const CanTp_TxSduType *Connection;
    CanTp_ChannelType *Channel;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(CanTpTxSduId, CANTP_TRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {
        Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
        Channel = CanTp_Channel + Connection->ChannelId;

		if(CanTpTxInfoPtr == NULL_PTR)
		{
			ErrorId = CANTP_E_PARAM_POINTER;
		}
		else if(CanTpTxInfoPtr->SduLength == 0)
		{
			ErrorId = CANTP_E_COM;
		}
		else
		{
	        CanTp_Lok_TxPciInit(&PciId, CanTpTxSduId, CanTpTxInfoPtr);
			TX_DL = CanTp_Lok_GetTxDl(Connection);

			if(CanTp_Lok_GetBit(Connection->BitFields, CANTP_FUNCTIONAL))
			{
			    PayloadLength = TX_DL - 1 - CanTp_AddressSize[Connection->AddressFormatId];
				MaxLength = (PciId <= CANTP_NPCI_SFCANFD) ? (PayloadLength - 1) : PayloadLength;
			}
			else
			{
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
				MaxLength = (TX_DL > CANTP_DEFAULT_CAN_DL) ? CANTP_MAXFDFFDL : CANTP_MAXFFDL;
                #else
                MaxLength = CANTP_MAXFFDL;
                #endif
			}

			ErrorId = (CanTpTxInfoPtr->SduLength > MaxLength) ? CANTP_E_INVALID_TATYPE : CANTP_NO_ERROR;
		}

        if(ErrorId != CANTP_NO_ERROR)
        {
            CanTp_Lok_ReportRunTimeError(CANTP_TRANSMIT, ErrorId);
        }
        else
        {
            CanTp_GetElapsedValue(&Value, &ElapsedValue);

            SchM_Enter_CanTp_EXCLUSIVE_AREA();

            if(CanTp_Lok_GetState(Connection->ChannelId) == CANTP_IDLE)
            {
                Channel->ActiveSduId = CanTpTxSduId;
                Channel->PciId = PciId;
                Channel->SduLength = CanTpTxInfoPtr->SduLength;
                Channel->InitialTicks = Value;

                Channel->STminTicks = CANTP_INVALID_STMIN_TICKS;
                CanTp_SubState[Connection->ChannelId] = CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED;
                RetVal = E_OK;
            }

            SchM_Exit_CanTp_EXCLUSIVE_AREA();
        }
    }

    return(RetVal);
}

#if(CANTP_CANTPLITE_SUPPORT != CANTP_ON)

Std_ReturnType CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
    Std_ReturnType RetVal = E_NOT_OK;
    const CanTp_TxSduType *Connection;
    boolean TcDisabled;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(CanTpTxSduId, CANTP_CANCELTRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {
        Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
        TcDisabled = CanTp_Lok_GetBit(Connection->BitFields, CANTP_TC_DISABLED);

        SchM_Enter_CanTp_EXCLUSIVE_AREA();

        if((TcDisabled) || (CanTp_Lok_GetState(Connection->ChannelId) != CANTP_TRANSMISSION) ||
           (CanTpTxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId))
        {
			CanTp_Lok_ReportRunTimeError(CANTP_CANCELTRANSMIT, CANTP_E_OPER_NOT_SUPPORTED);
        }
        else
        {
			
			CanTp_Lok_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);

			if(CanTp_SubState[Connection->ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
			{
			    CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
			}

			CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
			RetVal = E_OK;
        }

        SchM_Exit_CanTp_EXCLUSIVE_AREA();
    }

    return (RetVal);
}

Std_ReturnType CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
    uint8 PayLoadLength;
    Std_ReturnType RetVal = E_NOT_OK;
    const CanTp_RxSduType *Connection;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(CanTpRxSduId, CANTP_CANCELRECEIVE, CANTP_E_PARAM_ID))
    #endif
    {
        Connection = CanTp_CfgPtr->RxSdu + CanTpRxSduId;

        SchM_Enter_CanTp_EXCLUSIVE_AREA();

        if((CanTp_Lok_GetState(Connection->ChannelId) != CANTP_RECEPTION) ||
           (CanTpRxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId))
        {
            CanTp_Lok_ReportRunTimeError(CANTP_CANCELRECEIVE, CANTP_E_OPER_NOT_SUPPORTED);
        }
        else
        {
            PayLoadLength = CanTp_Lok_GetRxDl(Connection->ChannelId) -
                            CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;

            if(CanTp_Channel[Connection->ChannelId].SduLengthRemaining > PayLoadLength)
            {

                CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);

                if(CanTp_SubState[Connection->ChannelId] == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION)
                {
                    CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
                }

                CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
                RetVal = E_OK;
            }
        }

        SchM_Exit_CanTp_EXCLUSIVE_AREA();
    }

    return (RetVal);
}
#endif

void CanTp_TxConfirmation(PduIdType TxPduId)
{
	CanTp_ChannelType *Channel;
	CanTp_ChannelIdType ChannelId;
	uint8 SubState;
    CanTp_TickType Value = 0;
	CanTp_TickType ElapsedValue;
    uint8 MaxCopyLength;
	const CanTp_TxSduType *TxConnection;

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
	if(CanTp_Lok_IsNoDevError(TxPduId, CANTP_TXCONFIRMATION, CANTP_E_INVALID_TX_ID))
	#endif
	{
	    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	    SchM_Enter_CanTp_EXCLUSIVE_AREA();

        ChannelId = CanTp_TxConfirmationChannel[TxPduId];
        Channel = CanTp_Channel + ((ChannelId < CanTp_CfgPtr->NumberOfChannels) ? ChannelId : 0);
        SubState = (ChannelId < CanTp_CfgPtr->NumberOfChannels) ? CanTp_SubState[ChannelId] : CANTP_IDLE;

		switch(SubState)
		{
		    case CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION:

                Channel->InitialTicks = Value;
                CanTp_Lok_FcTxConfirmation(ChannelId);
                CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL;
                break;

            case CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION:

                Channel->InitialTicks = Value;
                TxConnection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
                MaxCopyLength = CanTp_Lok_GetTxDl(TxConnection) -
                                CanTp_AddressSize[TxConnection->AddressFormatId] - CanTp_PciSize[Channel->PciId];
                Channel->SduLengthRemaining = (Channel->SduLengthRemaining < MaxCopyLength) ? 0 :
                                              (Channel->SduLengthRemaining - MaxCopyLength);

                if(Channel->PciId == CANTP_NPCI_CF)
                {
                    Channel->SN++;
                    Channel->SN &= CANTP_LOWERNIBBLE_MASK ;
                    Channel->BlockCfsRemaining--;
                }

                if(Channel->SduLengthRemaining == 0)
                {
                    CanTp_SubState[ChannelId] = CANTP_IDLE;
                    CanTp_Lok_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, TxConnection->PduRPduHandleId, E_OK);
                }
                else
                {
                    if(Channel->BlockCfsRemaining != 0)
                    {
                        CanTp_SubState[ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
                    }
                    else
                    {
                        CanTp_Lok_PrepareFcRecieve(ChannelId);
                    }
                }

                CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL;
                break;

            default:
                break;
		}

		SchM_Exit_CanTp_EXCLUSIVE_AREA();
		
		CanTp_Lok_BurstMainFunction(ChannelId, CANTP_TRIGGER_TX_CONFIRMATION);
	}
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	CanTp_RxContextType Context;
	uint8 ErrorId;

	Context.PduId = RxPduId;
    Context.FrameType = 0;
    Context.ChannelId = 0;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(RxPduId, CANTP_RXINDICATION, CANTP_E_INVALID_RX_ID))
	#endif
	{
		if(PduInfoPtr == NULL_PTR)
		{
		    CanTp_Lok_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_PARAM_POINTER);
		}
		else
		{
		    ErrorId = CanTp_Lok_GetRxContext(&Context, PduInfoPtr);

		    if(ErrorId != CANTP_NO_ERROR)
            {
                CanTp_Lok_ReportRunTimeError(CANTP_RXINDICATION, ErrorId);
            }
            else if(CanTp_Lok_RxSduLengthCheck(&Context, PduInfoPtr) != E_OK)
            {
                CanTp_Lok_LengthError(&Context);
			}
			else
			{
                CanTp_Lok_ProcessFrame(&Context, PduInfoPtr);

                CanTp_Lok_BurstMainFunction(Context.ChannelId, CANTP_TRIGGER_RX_INDICATION);
            }
		}
	}
}

#if(CANTP_TRIGGER_TRANSMIT_API == CANTP_ON)

Std_ReturnType CanTp_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr)
{
    Std_ReturnType Status = E_NOT_OK;
    CanTp_ChannelIdType ChannelId;
    uint8 TX_DL = CANTP_DEFAULT_CAN_DL;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Lok_IsNoDevError(TxPduId, CANTP_TRIGGERTRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {
        if(PduInfoPtr == NULL_PTR)
        {
            CanTp_Lok_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_PARAM_POINTER);
        }
        else
        {
            ChannelId = CanTp_TxConfirmationChannel[TxPduId];

            SchM_Enter_CanTp_EXCLUSIVE_AREA();
            if(ChannelId < CanTp_CfgPtr->NumberOfChannels)
            {
                TX_DL = (CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION) ?
                        CanTp_Lok_GetTxDl(CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId) : TX_DL;

                if((PduInfoPtr->SduLength < TX_DL) || (PduInfoPtr->SduDataPtr == NULL_PTR))
                {
                    CanTp_Lok_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_PARAM_POINTER);
                }
                else
                {
                    Status = CanTp_Lok_CreateFrame(ChannelId, PduInfoPtr);
                }
            }
            SchM_Exit_CanTp_EXCLUSIVE_AREA();
        }
    }

    return Status;
}
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"
