

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

LOCAL_INLINE void Com_Lok_CopyData_Sig_UnsignedType (Com_SignalIdType SignalId, void * SignalDataPtr);
LOCAL_INLINE void Com_Lok_CopyData_Sig_SignedType   (Com_SignalIdType SignalId, void * SignalDataPtr);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void * SignalDataPtr)
{

   Com_RxSigConstPtrType       RxSigConstPtr;
   uint8                       Status;

   uint8                       SigType;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_RX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,                                                                                           COMServiceId_ReceiveSignal))
#endif
   {

        SignalId = COM_GET_RXSIGNAL_ID(SignalId);

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SignalId);

        SigType = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

        if(Com_CheckRxIPduStatus((PduIdType)RxSigConstPtr->IpduRef))
        {
            Status = E_OK;
        }

        if((SigType % COM_TWO) == COM_ZERO)
        {

            Com_Lok_CopyData_Sig_UnsignedType(SignalId, SignalDataPtr);
        }
        else{

            Com_Lok_CopyData_Sig_SignedType(SignalId, SignalDataPtr);
        }
   }
    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE void Com_Lok_CopyData_Sig_UnsignedType(Com_SignalIdType SignalId, void * SignalDataPtr)
{

   Com_RxSigConstPtrType       RxSigConstPtr;
   Com_SigBuffIndexType        SigBuff_Index;
   Com_MainFuncType            rxMainFuncId;
   uint8                       sigType;

    RxSigConstPtr       = COM_GET_RXSIG_CONSTDATA(SignalId);
    SigBuff_Index       = RxSigConstPtr->SigBuff_Index;
   sigType             = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
    rxMainFuncId        = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

   switch(sigType)
   {

        case COM_UINT8:
            {
                *(uint8*)SignalDataPtr = COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index);
            }
            break;
        case COM_UINT16:
            {
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(uint16*)SignalDataPtr = COM_GET_SIGTYPEUINT16_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
            }
            break;
        case COM_UINT32:
            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(uint32*)SignalDataPtr = COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
            }
            break;
#ifdef COM_RXSIG_INT64
        case COM_UINT64:
            {
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                *(uint64*)SignalDataPtr = COM_GET_SIGTYPEUINT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
            }
            break;
#endif
        case COM_BOOLEAN:
            {
                *(boolean*)SignalDataPtr = (COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index) != COM_ZERO);
            }
            break;
        case COM_UINT8_N:
            {

                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                Com_ByteCopy((uint8*)SignalDataPtr,&COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index)
   ,                            (uint32)RxSigConstPtr->BitSize);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
            }
            break;

#ifdef COM_FLOAT32SUPP
        case COM_FLOAT32:
            {
                uint32 RxNewVal_u32;

#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                RxNewVal_u32 = COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif

                (void)rba_BswSrv_MemCopy( SignalDataPtr, (const void *)&RxNewVal_u32, COM_F32_SIZE_IN_BYTES );

            }
            break;
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
        case COM_FLOAT64:

            {
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);

                *(float64*)SignalDataPtr = COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);

            }
            break;
#endif

        default:

            break;
   }
}

LOCAL_INLINE void Com_Lok_CopyData_Sig_SignedType(Com_SignalIdType SignalId, void * SignalDataPtr)
{

   Com_RxSigConstPtrType       RxSigConstPtr;
   Com_SigBuffIndexType        SigBuff_Index;

   Com_MainFuncType            rxMainFuncId;

   uint8                       sigType;

    RxSigConstPtr       = COM_GET_RXSIG_CONSTDATA(SignalId);
    SigBuff_Index       = RxSigConstPtr->SigBuff_Index;
   sigType                = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
    rxMainFuncId        = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

   switch(sigType)
   {

        case COM_SINT8:
            {
                *(sint8*)SignalDataPtr = (sint8)COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, SigBuff_Index);
            }
            break;
        case COM_SINT16:
            {
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(sint16*)SignalDataPtr = (sint16)COM_GET_SIGTYPEUINT16_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
            }
            break;
        case COM_SINT32:
            {
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
#endif
                *(sint32*)SignalDataPtr = (sint32)COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, SigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
#endif
            }
            break;
#ifdef COM_RXSIG_INT64
        case COM_SINT64:
            {
                SchM_Enter_Com_RxSigBuff(RECEIVESIGNAL);
                *(sint64*)SignalDataPtr = (sint64)COM_GET_SIGTYPEUINT64_BUFF(rxMainFuncId, SigBuff_Index);
                SchM_Exit_Com_RxSigBuff(RECEIVESIGNAL);
            }
            break;
#endif

        default:

            break;
   }
}
