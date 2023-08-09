

#include "CanIf_Prv.h"
#include "rba_BswSrv.h"

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
static CanIf_XCore_PipeRuntimeInfoType_st CanIf_XCore_PipeRuntimeInfo_ast[CANIF_XCORE_MAX_NUM_PIPES];
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"
static VAR(boolean, CANSM_VAR) CanIf_XCore_EndBuf_InvalidFlag_b;

VAR(boolean, CANSM_VAR) CanIf_XCore_RxClrPipeFlag_b;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
P2CONST(CanIf_XCore_ConfigType, AUTOMATIC, AUTOMATIC) CanIf_XCore_Config_pcst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE)  CanIf_XCore_Pipe_PushPduHdrToFifo(CanIf_XCore_PipeRuntimeInfoType_st *CanIf_XCore_Pipe_pst, CanIf_XCore_PipeTxRxParams_st* params_pst,
														uint32** PayloadPtr_ppu32, uint32* PayloadLenU32W_pu32);

static FUNC(void, CANIF_CODE)  CanIf_XCore_Pipe_Init(uint16 PipeId, const CanIf_XCore_ConfigType *Config_pcst);

static FUNC(void, CANIF_CODE)  CanIf_XCore_Pipe_Reset(uint16 PipeId);

static FUNC(void , CANIF_CODE) CanIf_XCore_ClearPipepacket( VAR(uint16, AUTOMATIC) PipeId, VAR(uint8, AUTOMATIC)ControllerId);

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_XCore_Init(P2CONST (CanIf_XCore_ConfigType, AUTOMATIC, CANIF_APPL_CONST) Config_pcst)
{
    uint16 pipeIdx_u32;

    #if CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC
    CanIf_XCore_Config_pcst = &CanIf_XCore_Config;
    (void) Config_pcst;
    #else
    CanIf_XCore_Config_pcst = Config_pcst;
    #endif

	for (pipeIdx_u32 = 0; pipeIdx_u32 < CanIf_XCore_Config_pcst->NumPipes_u16; pipeIdx_u32++)
	{
		CanIf_XCore_Pipe_Init(pipeIdx_u32, CanIf_XCore_Config_pcst);
	}
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static FUNC(uint32, CANIF_CODE) CanIf_XCore_Pipe_CalcAlignSizeU32W(uint32 LengthBytes_u32)
{
    uint32 size_u32 = (LengthBytes_u32 + (sizeof(uint32) - 1u)) / sizeof(uint32);
    return size_u32;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_XCore_Pipe_Init(uint16 PipeId, P2CONST(CanIf_XCore_ConfigType, AUTOMATIC, CANIF_APPL_CONST)Config_pcst)
{

    P2VAR(CanIf_XCore_PipeRuntimeInfoType_st, AUTOMATIC, AUTOMATIC) CanIf_XCore_Pipe_pst;

    CanIf_XCore_Pipe_pst = &CanIf_XCore_PipeRuntimeInfo_ast[PipeId];

    CanIf_XCore_Pipe_pst->PipeConfig_pcst = &(Config_pcst->PipeConfigs_ast[PipeId]);

    CanIf_XCore_Pipe_pst->FifoBaseAddr_pv = CanIf_XCore_Pipe_pst->PipeConfig_pcst->PipeFifoRam_pv;

    CanIf_XCore_Pipe_pst->FifoEndAddr_pv = ((uint8*)CanIf_XCore_Pipe_pst->FifoBaseAddr_pv) + CanIf_XCore_Pipe_pst->PipeConfig_pcst->FifoRamSizeBytes_u32 - sizeof(CanIf_XCore_PipePktHdrType_st);

    CanIf_XCore_Pipe_Reset(PipeId);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static FUNC(void, CANIF_CODE) CanIf_XCore_Pipe_Reset(uint16 PipeId)
{

    P2VAR(CanIf_XCore_PipeRuntimeInfoType_st, AUTOMATIC, AUTOMATIC) CanIf_XCore_Pipe_pst;

    CanIf_XCore_Pipe_pst = &CanIf_XCore_PipeRuntimeInfo_ast[PipeId];

    Schm_CanIf_XCore_Enter();
    {

        CanIf_XCore_Pipe_pst->PktCnt_u32 = 0u;
        CanIf_XCore_Pipe_pst->PktCntAck_u32 = 0u;
        CanIf_XCore_Pipe_pst->WritePtr_pv = CanIf_XCore_Pipe_pst->FifoBaseAddr_pv;
        CanIf_XCore_Pipe_pst->ReadPtr_pv = CanIf_XCore_Pipe_pst->FifoBaseAddr_pv;
        CanIf_XCore_EndBuf_InvalidFlag_b = FALSE;
        CanIf_XCore_RxClrPipeFlag_b = FALSE;

    }
    Schm_CanIf_XCore_Exit();
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_XCore_PipeWrite(uint16 PipeId, P2VAR(CanIf_XCore_PipeTxRxParams_st, AUTOMATIC, CANIF_APPL_CONST)params_pst)
{

    P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) Canif_XCore_info_pcst;

    P2VAR(uint32, AUTOMATIC, AUTOMATIC) PayloadPtr_pu32;

    P2VAR(CanIf_XCore_PipeRuntimeInfoType_st, AUTOMATIC, AUTOMATIC) CanIf_XCore_Pipe_pst;

    Std_ReturnType retVal = E_NOT_OK;

    uint32 PayloadLenU32W_u32;

    CanIf_XCore_Pipe_pst = &CanIf_XCore_PipeRuntimeInfo_ast[PipeId];

    Canif_XCore_info_pcst = params_pst->PduInfoPtr;

    #if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_XCore_Pipe_pst->PipeConfig_pcst->SrcCoreId_u16 != Schm_CanIf_XCore_GetCurrentCoreId()), CANIF_XCORE_APIID_PIPEWRITE_SID, CANIF_XCORE_E_WRONGCORE)
    #endif

    #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
    CanIf_XCore_Pipe_pst->Dbg_st.NumSendCalls_u32 ++;
    CanIf_XCore_Pipe_pst->Dbg_st.SendLastAttemptedPduId = params_pst->PduId;
    CanIf_XCore_Pipe_pst->Dbg_st.SendLastAttemptedPduInfo.SduDataPtr = Canif_XCore_info_pcst->SduDataPtr;
    CanIf_XCore_Pipe_pst->Dbg_st.SendLastAttemptedPduInfo.SduLength = Canif_XCore_info_pcst->SduLength;
    #endif

    retVal = CanIf_XCore_Pipe_PushPduHdrToFifo(CanIf_XCore_Pipe_pst, params_pst, &PayloadPtr_pu32, &PayloadLenU32W_u32);

	if(retVal == E_OK)
	{
	
	
	
		if (((unsigned int)Canif_XCore_info_pcst->SduDataPtr & 0x3u) == 0x0u)
		{
	
			rba_BswSrv_MemCopy32(PayloadPtr_pu32, (const uint32*) Canif_XCore_info_pcst->SduDataPtr, PayloadLenU32W_u32 * sizeof(uint32));
		}
		else
		{
	
			(void)rba_BswSrv_MemCopy(PayloadPtr_pu32, Canif_XCore_info_pcst->SduDataPtr, PayloadLenU32W_u32 * sizeof(uint32));
		}

		
		CanIf_XCore_Pipe_pst->PktCnt_u32 = CanIf_XCore_Pipe_pst->PktCnt_u32 + 1u;

	    #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
		CanIf_XCore_Pipe_pst->Dbg_st.NumBytesSendOk_u32 += Canif_XCore_info_pcst->SduLength;
	    #endif

        switch(CANIF_XCORE_PIPE_GET_FLAG_PROC(CanIf_XCore_Pipe_pst->PipeConfig_pcst->DestFlags_u32))
        {
            case CANIF_XCORE_PIPE_FLAG_PROC_POLLING:

            break;
            case CANIF_XCORE_PIPE_FLAG_PROC_TASK:
                Schm_CanIf_XCore_Activate_Task(CanIf_XCore_Pipe_pst->PipeConfig_pcst->DestRecvId);
            break;
            case CANIF_XCORE_PIPE_FLAG_PROC_SWI:
                Schm_CanIf_XCore_Activate_SW_Irq(CanIf_XCore_Pipe_pst->PipeConfig_pcst->DestRecvId);
            break;
            default:
                #if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

                CANIF_DET_REPORT_ERROR(TRUE, CANIF_XCORE_APIID_PIPEWRITE_SID, CANIF_XCORE_E_PARAM);
                retVal = E_NOT_OK;
                #endif
                break;

        }
	}
    else
    {

        #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
        CanIf_XCore_Pipe_pst->Dbg_st.NumSendCallsNotOk_u32 ++;
        #endif
    }

    return retVal;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_XCore_PipeRead(uint16 PipeId)
{

    P2VAR(CanIf_XCore_PipeRuntimeInfoType_st, AUTOMATIC, AUTOMATIC) CanIf_XCore_Pipe_pst;

    CanIf_XCore_Pipe_pst = &CanIf_XCore_PipeRuntimeInfo_ast[PipeId];

    #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
    CanIf_XCore_Pipe_pst->Dbg_st.NumReceiveCalls_u32 ++;
    #endif

    while (CanIf_XCore_Pipe_pst->PktCnt_u32 != CanIf_XCore_Pipe_pst->PktCntAck_u32)
    {

        volatile CanIf_XCore_PipePktHdrType_st *PktHdr_pst = (volatile CanIf_XCore_PipePktHdrType_st*) CanIf_XCore_Pipe_pst->ReadPtr_pv;
        uint32 PktFlags_u32 = PktHdr_pst->PktFlags_u32;
        uint32 PayloadLenBytes_u32 = PktHdr_pst->PktPayloadLenBytes_u32;

        uint32 pktLenU32W = CanIf_XCore_Pipe_CalcAlignSizeU32W(PayloadLenBytes_u32) + CANIF_XCORE_PTK_HDR_SIZE_U32W;

        if ((PktFlags_u32 & CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU) == CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU)
        {

            CanIf_XCore_Pipe_pst->ReadPtr_pv = CanIf_XCore_Pipe_pst->FifoBaseAddr_pv;
        }
        else if ((PktFlags_u32 & CANIF_XCORE_PKT_FLAG_INVALID_PDU) == CANIF_XCORE_PKT_FLAG_INVALID_PDU)
        {

            CanIf_XCore_Pipe_pst->ReadPtr_pv = ((uint32*) CanIf_XCore_Pipe_pst->ReadPtr_pv) + pktLenU32W;
        }
        else
        {

            P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;

            P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

            PduInfoType local_PduInfo_st;

            CanIf_XCore_PipeTxRxParams_st params_st;

            VAR(uint16, AUTOMATIC)          ltxPduCustId_t;

            uint32* PayloadPtr_pu32 = ((uint32*) PktHdr_pst) + CANIF_XCORE_PTK_HDR_SIZE_U32W;

            params_st.PduId = (PduIdType) (PktFlags_u32 & CANIF_XCORE_PKT_PDUID_MASK);
			params_st.callbackIndex_u8 = (uint8) ((PktFlags_u32 & CANIF_XCORE_PKT_CALLBACKIDX_MASK) >> CANIF_XCORE_PKT_CALLBACKIDX_SHIFT);
			
			params_st.userType_e = (CanIf_Cfg_UserType_ten)((PktFlags_u32 & CANIF_XCORE_PKT_USERTYPE_MASK) >> CANIF_XCORE_PKT_USERTYPE_SHIFT);

			
            params_st.PduInfoPtr = &local_PduInfo_st;
            local_PduInfo_st.SduDataPtr = (uint8*) PayloadPtr_pu32;
            local_PduInfo_st.SduLength = PayloadLenBytes_u32;

            ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[params_st.PduId];

            lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

            RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + params_st.PduId ;

            #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
            CanIf_XCore_Pipe_pst->Dbg_st.NumReceiveCallsOk_u32 ++;
            CanIf_XCore_Pipe_pst->Dbg_st.NumBytesReceiveOk_u32 += PayloadLenBytes_u32;
            CanIf_XCore_Pipe_pst->Dbg_st.ReceiveLastPduId = params_st.PduId;
            CanIf_XCore_Pipe_pst->Dbg_st.ReceiveLastPduInfo = local_PduInfo_st;
            #endif

            switch(CANIF_XCORE_PIPE_GET_FLAG_TYPE(CanIf_XCore_Pipe_pst->PipeConfig_pcst->DestFlags_u32))
            {
                case CANIF_XCORE_PIPE_FLAG_TYPE_TX:
                    (void)CanIf_XCore_LocalCore_Transmit(params_st.PduId, &local_PduInfo_st);
                break;

                case CANIF_XCORE_PIPE_FLAG_TYPE_RX:
					(void)CanIf_XCore_LocalCore_RxIndication(RxPduCfg_pcst, &local_PduInfo_st);
                break;

                case CANIF_XCORE_PIPE_FLAG_TYPE_TXCONF:
					(void)CanIf_XCore_LocalCore_TxConfirmation(lTxPduConfig_pst);
                break;

                default:
                    #if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

                    CANIF_DET_REPORT_ERROR(TRUE, CANIF_XCORE_APIID_PIPEREAD_SID, CANIF_XCORE_E_PARAM);
                    #endif
                    break;
            }

           CanIf_XCore_Pipe_pst->ReadPtr_pv = ((uint32*) CanIf_XCore_Pipe_pst->ReadPtr_pv) + pktLenU32W;
        }
        CanIf_XCore_Pipe_pst->PktCntAck_u32 = CanIf_XCore_Pipe_pst->PktCntAck_u32 + 1u;
    }
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

static void CanIf_XCore_Pipe_CreatePduPkt(CanIf_XCore_PipeRuntimeInfoType_st *CanIf_XCore_Pipe_pst, volatile void *PktStart_pv,\
    const uint32 PktFlags_u32, uint8 ControllerID_u8, const uint32 PayloadLenBytes_u32, uint32 pktLenU32W, uint32** PayloadPtr_ppu32)
{

    volatile CanIf_XCore_PipePktHdrType_st *PktHdr_pst = (volatile CanIf_XCore_PipePktHdrType_st*) PktStart_pv;

    PktHdr_pst->PktFlags_u32 = PktFlags_u32;
    PktHdr_pst->PktPayloadLenBytes_u32 = PayloadLenBytes_u32;
    PktHdr_pst->CtrlID_u8 = ControllerID_u8;

    *PayloadPtr_ppu32 = ((uint32*) PktStart_pv) + CANIF_XCORE_PTK_HDR_SIZE_U32W;

    CanIf_XCore_Pipe_pst->WritePtr_pv = ((uint32*)PktStart_pv) + pktLenU32W;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
static void CanIf_XCore_Pipe_CreateInvalidPduPkt(CanIf_XCore_PipeRuntimeInfoType_st *Pipe_pst, volatile void *PktStart_pv)
{

    volatile CanIf_XCore_PipePktHdrType_st *PktHdr_pst = (volatile CanIf_XCore_PipePktHdrType_st*) PktStart_pv;

    if (CanIf_XCore_EndBuf_InvalidFlag_b == TRUE)
    {
        PktHdr_pst->PktFlags_u32 = CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU;
        Pipe_pst->WritePtr_pv = Pipe_pst->FifoEndAddr_pv;

        Pipe_pst->PktCnt_u32 = Pipe_pst->PktCnt_u32 + 1u;
        CanIf_XCore_EndBuf_InvalidFlag_b = FALSE;
    }
    else
    {
        PktHdr_pst->PktFlags_u32 = CANIF_XCORE_PKT_FLAG_INVALID_PDU;
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

static FUNC(Std_ReturnType, CANIF_CODE) CanIf_XCore_Pipe_PushPduHdrToFifo(CanIf_XCore_PipeRuntimeInfoType_st *CanIf_XCore_Pipe_pst, CanIf_XCore_PipeTxRxParams_st* params_pst,
														uint32** PayloadPtr_ppu32, uint32* PayloadLenU32W_pu32)
{

    Std_ReturnType retVal = E_NOT_OK;

    uint32 spaceLeftU32Words_u32 = 0 ;

    const PduInfoType *info = params_pst->PduInfoPtr;

    PduIdType PduId = params_pst->PduId;

    uint8 callbackIndex_u8 = params_pst->callbackIndex_u8;

    CanIf_Cfg_UserType_ten userType_e = params_pst->userType_e;

    uint8  CtrlId_u8 = params_pst->ControllerId_u8;

    uint32 payloadLenU32W = CanIf_XCore_Pipe_CalcAlignSizeU32W(info->SduLength);

    uint32 pktLenU32W =  payloadLenU32W + CANIF_XCORE_PTK_HDR_SIZE_U32W;

    *PayloadLenU32W_pu32 = payloadLenU32W;

    if (CanIf_XCore_Pipe_pst->WritePtr_pv >= CanIf_XCore_Pipe_pst->ReadPtr_pv)
    {

        spaceLeftU32Words_u32 = (((uint8*) CanIf_XCore_Pipe_pst->FifoEndAddr_pv) - ((uint8*) CanIf_XCore_Pipe_pst->WritePtr_pv))  / sizeof(uint32);
        if (spaceLeftU32Words_u32 < pktLenU32W)
        {

            spaceLeftU32Words_u32 = (((uint8*) CanIf_XCore_Pipe_pst->ReadPtr_pv) - ((uint8*) CanIf_XCore_Pipe_pst->FifoBaseAddr_pv))  / sizeof(uint32);
            if (spaceLeftU32Words_u32 < pktLenU32W)
            {
                retVal = E_NOT_OK;
            }
            else
            {

                CanIf_XCore_EndBuf_InvalidFlag_b  = TRUE;

                CanIf_XCore_Pipe_CreateInvalidPduPkt(CanIf_XCore_Pipe_pst, CanIf_XCore_Pipe_pst->WritePtr_pv);

                CanIf_XCore_Pipe_CreatePduPkt(CanIf_XCore_Pipe_pst, CanIf_XCore_Pipe_pst->FifoBaseAddr_pv,
                        CANIF_XCORE_PKT_HDR_CALC(PduId, (uint32)callbackIndex_u8, userType_e), CtrlId_u8, info->SduLength, pktLenU32W, PayloadPtr_ppu32);
                retVal = E_OK;
            }
        }
        else
        {
            CanIf_XCore_Pipe_CreatePduPkt(CanIf_XCore_Pipe_pst, CanIf_XCore_Pipe_pst->WritePtr_pv,
                CANIF_XCORE_PKT_HDR_CALC(PduId, (uint32)callbackIndex_u8, userType_e), CtrlId_u8,  info->SduLength, pktLenU32W, PayloadPtr_ppu32);
            retVal = E_OK;
        }
    }
    else
    {

        spaceLeftU32Words_u32 = (((uint8*) CanIf_XCore_Pipe_pst->ReadPtr_pv) - ((uint8*) CanIf_XCore_Pipe_pst->WritePtr_pv))  / sizeof(uint32);
        if (spaceLeftU32Words_u32 < pktLenU32W)
        {
            retVal = E_NOT_OK;
        }
        else
        {
            CanIf_XCore_Pipe_CreatePduPkt(CanIf_XCore_Pipe_pst, CanIf_XCore_Pipe_pst->WritePtr_pv,
                CANIF_XCORE_PKT_HDR_CALC(PduId, (uint32)callbackIndex_u8, userType_e),CtrlId_u8, info->SduLength, pktLenU32W, PayloadPtr_ppu32);
            retVal = E_OK;
        }
    }
    return retVal;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void , CANIF_CODE) CanIf_XCore_ClearPipes(VAR(uint8, AUTOMATIC)ControllerId)
{
    VAR(uint16, AUTOMATIC)PipeIndex;
    VAR(uint16, AUTOMATIC)pipeid_u16 = CANIF_XCORE_INVALID_PIPE_ID;

    for (PipeIndex = 0; PipeIndex < CANIF_XCORE_MAX_NUM_PIPES;  PipeIndex++ )
    {

        if (CanIf_XCore_RxClrPipeFlag_b == TRUE)
        {

            pipeid_u16 = CanIf_XCore_Config_pcst->PipeConfigs_ast[PipeIndex].PipeId_u16;
        }
        else if ((CANIF_XCORE_PIPE_TX == CanIf_XCore_Config_pcst->PipeConfigs_ast[PipeIndex].PipeType) || (CANIF_XCORE_PIPE_TXCONF == CanIf_XCore_Config_pcst->PipeConfigs_ast[PipeIndex].PipeType))
        {

            pipeid_u16 = CanIf_XCore_Config_pcst->PipeConfigs_ast[PipeIndex].PipeId_u16;
        }
        else
        {

        }

        if (pipeid_u16 != CANIF_XCORE_INVALID_PIPE_ID)
        {

            CanIf_XCore_ClearPipepacket( pipeid_u16,ControllerId );
        }
    }
    CanIf_XCore_RxClrPipeFlag_b = FALSE;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

static FUNC(void , CANIF_CODE) CanIf_XCore_ClearPipepacket( VAR(uint16, AUTOMATIC) PipeId, VAR(uint8, AUTOMATIC)ControllerId)
{

    volatile void *lWritePtr_pv;

    VAR(uint32, AUTOMATIC)  PayloadLenBytes_u32;
    VAR(uint32, AUTOMATIC)  pktLenU32W;
    VAR(uint32, AUTOMATIC)  PktFlags_u32;
    VAR(uint32, AUTOMATIC)  lPktCnt_u32;
    VAR(uint32, AUTOMATIC)  lPktCntAck_u32;
    VAR(uint8, AUTOMATIC)   lControllerId_u8;
    VAR(PduIdType, AUTOMATIC)   PduId;

    CanIf_XCore_PipeRuntimeInfoType_st *Pipe_pst = &CanIf_XCore_PipeRuntimeInfo_ast[PipeId];

    lWritePtr_pv = Pipe_pst->ReadPtr_pv;
    lPktCnt_u32 = Pipe_pst->PktCnt_u32;
    lPktCntAck_u32 = Pipe_pst->PktCntAck_u32;

    while (lPktCnt_u32 != lPktCntAck_u32)
    {

        volatile CanIf_XCore_PipePktHdrType_st *PktHdr_pst = (volatile CanIf_XCore_PipePktHdrType_st*) lWritePtr_pv;
        PktFlags_u32 = PktHdr_pst->PktFlags_u32;
        PduId = (PduIdType) (PktFlags_u32 & CANIF_XCORE_PKT_PDUID_MASK);
        lControllerId_u8 = PktHdr_pst->CtrlID_u8;
        PayloadLenBytes_u32 = PktHdr_pst->PktPayloadLenBytes_u32;
        pktLenU32W = CanIf_XCore_Pipe_CalcAlignSizeU32W(PayloadLenBytes_u32) + CANIF_XCORE_PTK_HDR_SIZE_U32W;

        if ((PktFlags_u32 & CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU) == CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU)
        {
            lWritePtr_pv = Pipe_pst->FifoBaseAddr_pv;
        }
        else
        {
            if (lControllerId_u8 == ControllerId)
            {
                CanIf_XCore_Pipe_CreateInvalidPduPkt(Pipe_pst, lWritePtr_pv);
            }

            lWritePtr_pv = ((uint32*) lWritePtr_pv) + pktLenU32W;
        }
        lPktCnt_u32 --;
    }
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif

