#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_UnsignedType (VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_signedType   (VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_ReceiveSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{

   Com_RxSigConstPtrType                       RxSigConstPtr;
   VAR(uint8, AUTOMATIC)                       Status;

   VAR(uint8, AUTOMATIC)                       SigType;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_RX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,     COMServiceId_ReceiveSignal))
#endif
   {

        SignalId = COM_GET_RXSIGNAL_ID(SignalId);

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SignalId);

        SigType = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

        if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)RxSigConstPtr->IpduRef))
        {
            Status = E_OK;
        }

        if((SigType % COM_TWO) == COM_ZERO)
        {

            Com_Lok_CopyData_UnsignedType(SignalId, SignalDataPtr);
        }
        else{

            Com_Lok_CopyData_signedType(SignalId, SignalDataPtr);
        }
   }
    return(Status);
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_UnsignedType(VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{

   Com_RxSigConstPtrType                       RxSigConstPtr;
   VAR(Com_SigMaxType, AUTOMATIC)              RxNewVal;
   VAR(Com_SigBuffIndexType, AUTOMATIC)        SigBuff_Index;

   VAR(Com_MainFuncType, AUTOMATIC)            rxMainFuncId;

   VAR(uint8, AUTOMATIC)                       Type;

    RxSigConstPtr       = COM_GET_RXSIG_CONSTDATA(SignalId);
    SigBuff_Index       = RxSigConstPtr->SigBuff_Index;

    Type                = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
    rxMainFuncId        = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

   switch(Type)
   {

        case COM_UINT8:
            {
            RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index);
             *(uint8*)SignalDataPtr =  (uint8)RxNewVal;
            }
            break;
        case COM_UINT16:
            {
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT16_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(uint16*)SignalDataPtr =  (uint16)RxNewVal;
            }
            break;
        case COM_UINT32:
            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(uint32*)SignalDataPtr =  (uint32)RxNewVal;
            }
            break;
#ifdef COM_RXSIG_INT64
        case COM_UINT64:
            {
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                RxNewVal = COM_GET_SIGTYPEUINT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
                *(uint64*)SignalDataPtr =  (uint64)RxNewVal;
            }
            break;
#endif
        case COM_BOOLEAN:
            {
                RxNewVal = (uint32)COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index);
                *(boolean*)SignalDataPtr =  (boolean)(RxNewVal != 0u);
            }
            break;
        case COM_UINT8_N:
            {

                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                Com_ByteCopy((uint8*)SignalDataPtr,&COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index)
   ,     (uint32)RxSigConstPtr->BitSize);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
            }
            break;

#ifdef COM_FLOAT32SUPP
        case COM_FLOAT32:
            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif

                (void)LibAutosar_vptrMemCopy( SignalDataPtr, (const void *)&RxNewVal, 4 );

            }
            break;
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
        case COM_FLOAT64:

            {
                float64 RxNewVal_f64;
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                RxNewVal_f64 = COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);

                *(float64*)SignalDataPtr =  (float64)RxNewVal_f64;

            }
            break;
#endif

        default:

            break;
   }
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_signedType(VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{

   Com_RxSigConstPtrType                       RxSigConstPtr;
   VAR(Com_SigMaxType, AUTOMATIC)              RxNewVal;
   VAR(Com_SigBuffIndexType, AUTOMATIC)        SigBuff_Index;

   VAR(Com_MainFuncType, AUTOMATIC)            rxMainFuncId;

   VAR(uint8, AUTOMATIC)                       Type;

    RxSigConstPtr       = COM_GET_RXSIG_CONSTDATA(SignalId);
    SigBuff_Index       = RxSigConstPtr->SigBuff_Index;

    Type                = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
    rxMainFuncId        = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

   switch(Type)
   {

        case COM_SINT8:
            {
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index);
                *(sint8*)SignalDataPtr =  (sint8)RxNewVal;
            }
            break;
        case COM_SINT16:
            {
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT16_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(sint16*)SignalDataPtr =  (sint16)RxNewVal;
            }
            break;
        case COM_SINT32:
            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(sint32*)SignalDataPtr =  (sint32)RxNewVal;
            }
            break;
#ifdef COM_RXSIG_INT64
        case COM_SINT64:
            {
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                RxNewVal = COM_GET_SIGTYPEUINT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
                *(sint64*)SignalDataPtr =  (sint64)RxNewVal;
            }
            break;
#endif

        default:

            break;
   }
}
