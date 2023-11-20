#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_UnsignedType( VAR(Com_SignalIdType, AUTOMATIC)      IntSignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC)       RxMainFuncId );

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_SignedType(   VAR(Com_SignalIdType, AUTOMATIC)      IntSignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC)       RxMainFuncId );
#endif

#ifdef COM_RX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_ReceiveShadowSignal( VAR(Com_SignalIdType, AUTOMATIC)      SignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{

   Com_RxGrpSigConstPtrType                    RxGrpSigConstPtr;
   VAR(uint8, AUTOMATIC)                       SigType;
   VAR(Com_MainFuncType,AUTOMATIC)             rxMainFuncId;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_RX_GRPSIGNALS), (SignalDataPtr == NULL_PTR)
   ,     COMServiceId_ReceiveShadowSignal))
#endif
   {
        SignalId            = COM_GET_RXGRPSIGNAL_ID(SignalId);

        RxGrpSigConstPtr    = COM_GET_RXGRPSIG_CONSTDATA(SignalId);

        SigType             = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

        rxMainFuncId = (COM_GET_RX_IPDU_CONSTDATA((COM_GET_RXSIGGRP_CONSTDATA(RxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        if((SigType % COM_TWO) == COM_ZERO)
        {

            Com_Lok_CopyData_UnsignedType(SignalId, SignalDataPtr, rxMainFuncId);
        }
        else{

            Com_Lok_CopyData_SignedType(SignalId, SignalDataPtr, rxMainFuncId);
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_CopyData_UnsignedType( VAR(Com_SignalIdType, AUTOMATIC)      IntSignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC)       RxMainFuncId )
{

   Com_RxGrpSigConstPtrType                    RxGrpSigConstPtr;
   VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC)   GrpSigBuff_Index;
   VAR(uint8, AUTOMATIC)                       SigType;
   VAR(Com_SigMaxType, AUTOMATIC)              RxNewVal_GrpSig;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(IntSignalId);

    SigType          = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
    GrpSigBuff_Index = RxGrpSigConstPtr->RxGrpSigBuff_Index;

   switch( SigType )
   {

        case COM_UINT8:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index);

            *(uint8*)SignalDataPtr  =  (uint8)RxNewVal_GrpSig;
        }
        break;
        case COM_UINT16:
        {
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT16_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

            *(uint16*)SignalDataPtr =  (uint16)RxNewVal_GrpSig;
        }
        break;
        case COM_UINT32:
        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

            *(uint32*)SignalDataPtr =  (uint32)RxNewVal_GrpSig;
        }
        break;

#ifdef COM_RXGRPSIG_INT64
        case COM_UINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig = COM_GET_RXGRPSIGTYPEUINT64_BUFF(RxMainFuncId,GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();

            *(uint64*)SignalDataPtr =  (uint64)RxNewVal_GrpSig;
        }
        break;
#endif

        case COM_BOOLEAN:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index);

            *(boolean*)SignalDataPtr =  (boolean)(RxNewVal_GrpSig != 0u);
        }
        break;

#ifdef COM_GRPSIGFLOAT32SUPP
        case COM_FLOAT32:
        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

           (void)LibAutosar_vptrMemCopy(SignalDataPtr,(const void *)&RxNewVal_GrpSig,4);
        }
        break;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        case COM_FLOAT64:
        {
            VAR(float64, AUTOMATIC) RxNewVal_GrpSig_f64;
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig_f64 =  (float64)COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(RxMainFuncId,GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();

            *(float64*)SignalDataPtr =  (float64)RxNewVal_GrpSig_f64;
        }
        break;
#endif

       case COM_UINT8_N:
        {

            SchM_Enter_Com_RxGrpSigBuff();

            Com_ByteCopy( (uint8*)SignalDataPtr, &(COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index))
   ,     (uint32)RxGrpSigConstPtr->BitSize);

            SchM_Exit_Com_RxGrpSigBuff();
        }
        break;
        default:

        break;
   }
}

LOCAL_INLINE FUNC(void, COM_CODE)  Com_Lok_CopyData_SignedType( VAR(Com_SignalIdType, AUTOMATIC)      IntSignalId
   ,     P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(Com_MainFuncType,AUTOMATIC)       RxMainFuncId )
{

   Com_RxGrpSigConstPtrType                    RxGrpSigConstPtr;
   VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC)   GrpSigBuff_Index;
   VAR(uint8, AUTOMATIC)                       SigType;
   VAR(Com_SigMaxType, AUTOMATIC)              RxNewVal_GrpSig;

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(IntSignalId);

    SigType          = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
    GrpSigBuff_Index = RxGrpSigConstPtr->RxGrpSigBuff_Index;

   switch( SigType )
   {
        case COM_SINT8:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(RxMainFuncId,GrpSigBuff_Index);

            *(sint8*)SignalDataPtr  =  (sint8)RxNewVal_GrpSig;
        }
        break;
        case COM_SINT16:
        {
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT16_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

            *(sint16*)SignalDataPtr =  (sint16)RxNewVal_GrpSig;
        }
        break;
        case COM_SINT32:
        {
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
#endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(RxMainFuncId,GrpSigBuff_Index);
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
#endif

            *(sint32*)SignalDataPtr =  (sint32)RxNewVal_GrpSig;
        }
        break;

#ifdef COM_RXGRPSIG_INT64
        case COM_SINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig = COM_GET_RXGRPSIGTYPEUINT64_BUFF(RxMainFuncId,GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();

            *(sint64*)SignalDataPtr =  (sint64)RxNewVal_GrpSig;
        }
        break;
#endif

        default:

       break;
   }
}
#endif

