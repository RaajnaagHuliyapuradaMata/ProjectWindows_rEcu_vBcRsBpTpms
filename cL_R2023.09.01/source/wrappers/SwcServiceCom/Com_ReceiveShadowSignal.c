

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE void Com_Lok_CopyData_GrpSig_UnsignedType(
                                            Com_SignalIdType        IntSignalId
   ,                                           void *                  SignalDataPtr
   ,                                           Com_MainFuncType        RxMainFuncId
                                               );

LOCAL_INLINE void Com_Lok_CopyData_GrpSig_SignedType(
                                            Com_SignalIdType        IntSignalId
   ,                                           void *                  SignalDataPtr
   ,                                           Com_MainFuncType        RxMainFuncId
                                             );

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

void Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void * SignalDataPtr)
{

   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   uint8                           SigType;
   Com_MainFuncType                rxMainFuncId;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_RX_GRPSIGNALS), (SignalDataPtr == NULL_PTR)
   ,                                  COMServiceId_ReceiveShadowSignal))
#endif
   {
        SignalId            = COM_GET_RXGRPSIGNAL_ID(SignalId);

        RxGrpSigConstPtr    = COM_GET_RXGRPSIG_CONSTDATA(SignalId);

        SigType             = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

        rxMainFuncId = (COM_GET_RX_IPDU_CONSTDATA((COM_GET_RXSIGGRP_CONSTDATA(RxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        if((SigType % COM_TWO) == COM_ZERO)
        {

            Com_Lok_CopyData_GrpSig_UnsignedType(SignalId, SignalDataPtr, rxMainFuncId);
        }
        else{

            Com_Lok_CopyData_GrpSig_SignedType(SignalId, SignalDataPtr, rxMainFuncId);
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE void Com_Lok_CopyData_GrpSig_UnsignedType(
                                            Com_SignalIdType        IntSignalId
   ,                                           void *                  SignalDataPtr
   ,                                           Com_MainFuncType        RxMainFuncId
                                               )
{

   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   Com_RxGrpSigBuffIndexType       GrpSigBuff_Index;
   uint8                           SigType;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(IntSignalId);

    SigType          = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
    GrpSigBuff_Index = RxGrpSigConstPtr->RxGrpSigBuff_Index;

   switch( SigType )
   {
        case COM_UINT8:
        {

            *(uint8*)SignalDataPtr = COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index);

        }
        break;
        case COM_UINT16:
        {
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
#endif

            *(uint16*)SignalDataPtr = COM_GET_RXGRPSIGTYPEUINT16_BUFF(RxMainFuncId,GrpSigBuff_Index);

#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
#endif
        }
        break;
        case COM_UINT32:
        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif

            *(uint32*)SignalDataPtr = COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);

#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif
        }
        break;

#ifdef COM_RXGRPSIG_INT64
        case COM_UINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();

            *(uint64*)SignalDataPtr = COM_GET_RXGRPSIGTYPEUINT64_BUFF(RxMainFuncId,GrpSigBuff_Index);

            SchM_Exit_Com_RxGrpSigBuff();
        }
        break;
#endif

        case COM_BOOLEAN:
        {

            *(boolean*)SignalDataPtr = (COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index) != COM_ZERO);

        }
        break;

#ifdef COM_GRPSIGFLOAT32SUPP
        case COM_FLOAT32:
        {
            uint32 RxNewVal_GrpSig_u32;

#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig_u32 = COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

           (void)rba_BswSrv_MemCopy(SignalDataPtr,(const void *)&RxNewVal_GrpSig_u32,COM_F32_SIZE_IN_BYTES);

        }
        break;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        case COM_FLOAT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();

            *(float64*)SignalDataPtr = COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(RxMainFuncId,GrpSigBuff_Index);

            SchM_Exit_Com_RxGrpSigBuff();
        }
        break;
#endif

       case COM_UINT8_N:
        {
            SchM_Enter_Com_RxGrpSigBuff();

            Com_ByteCopy( (uint8*)SignalDataPtr, &(COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index))
   ,                         (uint32)RxGrpSigConstPtr->BitSize);

            SchM_Exit_Com_RxGrpSigBuff();
        }
        break;
        default:

        break;
   }
}

LOCAL_INLINE void Com_Lok_CopyData_GrpSig_SignedType(
                                          Com_SignalIdType      IntSignalId
   ,                                         void *                SignalDataPtr
   ,                                         Com_MainFuncType      RxMainFuncId
                                             )
{

   Com_RxGrpSigConstPtrType        RxGrpSigConstPtr;
   Com_RxGrpSigBuffIndexType       GrpSigBuff_Index;
   uint8                           SigType;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(IntSignalId);

    SigType          = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
    GrpSigBuff_Index = RxGrpSigConstPtr->RxGrpSigBuff_Index;

   switch( SigType )
   {
        case COM_SINT8:
        {

            *(sint8*)SignalDataPtr = (sint8)COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index);

        }
        break;
        case COM_SINT16:
        {
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
#endif

            *(sint16*)SignalDataPtr = (sint16)COM_GET_RXGRPSIGTYPEUINT16_BUFF(RxMainFuncId,GrpSigBuff_Index);

#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
#endif
        }
        break;
        case COM_SINT32:
        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif

            *(sint32*)SignalDataPtr = (sint32)COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);

#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif
        }
        break;

#ifdef COM_RXGRPSIG_INT64
        case COM_SINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();

            *(sint64*)SignalDataPtr = (sint64)COM_GET_RXGRPSIGTYPEUINT64_BUFF(RxMainFuncId,GrpSigBuff_Index);

            SchM_Exit_Com_RxGrpSigBuff();
        }
        break;
#endif

        default:

       break;
   }
}
#endif

