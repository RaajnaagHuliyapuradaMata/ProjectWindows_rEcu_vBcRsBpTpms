#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;

   Com_RxGrpSigConstPtrType            RxGrpSigConstPtr;
   VAR(uint16_least, AUTOMATIC)        index_ui;
   VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC) rxGrpSignalBuffIndex;
   VAR(uint8, AUTOMATIC)               Type;
   VAR(uint8, AUTOMATIC)               Status_u8;
   VAR(Com_MainFuncType,AUTOMATIC)     rxMainFuncId;

    Status_u8 = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param((SignalGroupId >= COM_GET_NUM_RX_SIGNALGRP), COMServiceId_ReceiveSignalGroup))
#endif
   {

        SignalGroupId = COM_GET_RXSIGNALGRP_ID(SignalGroupId);

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SignalGroupId);

        RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

        rxMainFuncId    = (COM_GET_RX_IPDU_CONSTDATA(RxSigGrpConstPtr->IpduRef))->MainFunctionRef;

        if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)(RxSigGrpConstPtr->IpduRef)))
        {
            Status_u8 = E_OK;
        }

        SchM_Enter_Com_RxGrpSigSecBuff();
        for(index_ui =  RxSigGrpConstPtr->No_Of_GrpSig; index_ui != 0u; index_ui--)
        {

            Type =  Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
            rxGrpSignalBuffIndex = RxGrpSigConstPtr->RxGrpSigBuff_Index;

            switch(Type >> 1u)
            {
            case 0x00u:
            case 0x03u:
            {
                COM_GET_RXGRPSIGTYPEUINT8_BUFF(rxMainFuncId,rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId,rxGrpSignalBuffIndex);
            }
                break;

            case 0x01u:
            {
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Enter_Com_RxGrpSigBuff();
#endif
                COM_GET_RXGRPSIGTYPEUINT16_BUFF(rxMainFuncId,rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU16_BUFF(rxMainFuncId,rxGrpSignalBuffIndex);
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Exit_Com_RxGrpSigBuff();
#endif
            }
                break;

            case 0x02u:

#ifdef COM_GRPSIGFLOAT32SUPP
            case (COM_FLOAT32 >> 1u):
#endif

            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxGrpSigBuff();
#endif
                COM_GET_RXGRPSIGTYPEUINT32_BUFF(rxMainFuncId,rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU32_BUFF(rxMainFuncId,rxGrpSignalBuffIndex);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxGrpSigBuff();
#endif
            }
                break;

#ifdef COM_RXGRPSIG_INT64
            case 0x08u:
            {
                SchM_Enter_Com_RxGrpSigBuff();
                COM_GET_RXGRPSIGTYPEUINT64_BUFF(rxMainFuncId,rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU64_BUFF(rxMainFuncId,rxGrpSignalBuffIndex);
                SchM_Exit_Com_RxGrpSigBuff();
            }
                break;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
            case (COM_FLOAT64 >> 1u):
            {

                SchM_Enter_Com_RxGrpSigBuff();
                COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(rxMainFuncId,rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(rxMainFuncId,rxGrpSignalBuffIndex);
                SchM_Exit_Com_RxGrpSigBuff();
            }
                break;
#endif

            case 0x04u:
            {

                SchM_Enter_Com_RxGrpSigBuff();
                Com_ByteCopy(&COM_GET_RXGRPSIGTYPEUINT8_BUFF(rxMainFuncId,rxGrpSignalBuffIndex)
   ,     &COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId,rxGrpSignalBuffIndex),RxGrpSigConstPtr->BitSize);
                SchM_Exit_Com_RxGrpSigBuff();
            }
                break;

            default:

                break;
            }

            RxGrpSigConstPtr++;
        }

        SchM_Exit_Com_RxGrpSigSecBuff();
   }
    return (Status_u8);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

