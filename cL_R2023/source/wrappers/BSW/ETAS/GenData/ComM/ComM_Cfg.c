

#include "ComStack_Types.h"
#include "ComM_Cfg.h"

#if ( COMM_ECUC_RB_RTE_IN_USE != STD_OFF )

#define COMM_RTE_GENERATED_APIS
#include "Rte_ComM.h"
#endif

#include "ComM_Priv.h"
#include "Std_Types.h"

#if(COMM_CAN == STD_ON)
#include "CanSM_ComM.h"
#endif
#if(COMM_LIN == STD_ON)
#include "LinSM.h"
#endif
#if(COMM_FLXRY == STD_ON)
#include "FrSM.h"
#endif
#if(COMM_ETH == STD_ON)
#include "EthSM.h"
#endif

#if(COMM_RTE_SUPPORT != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_Rte_Switch_UM_currentMode(ComM_UserHandleType UserId_u8, uint8 lowestMode_u8)
{
    Std_ReturnType retVal = E_OK;
    (void) lowestMode_u8;

    switch (UserId_u8)
    {

        case (ComMConf_ComMUser_ComMUser_Can_Network_0_Channel):
        {
            retVal = (Std_ReturnType)(Rte_Switch_UM_ComMUser_Can_Network_0_Channel_currentMode(lowestMode_u8));
        }
        break;
        default:
        {
            retVal = E_OK;
        }
        break;
    }
    (void)retVal;
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if ((COMM_FULLCOMREQ_NOTIF != STD_OFF))
#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_CurrentChannelRequest_Rte_Write(uint8 ChannelId,ComM_UserHandleArrayType * data)
{
    Std_ReturnType retVal;
    switch (ChannelId)
    {
        default:
        {
            retVal = E_OK;
        }
        break;
    }
    (void)retVal;
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"
static Std_ReturnType ComM_Dummy_RequestComMode(NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode);

static Std_ReturnType ComM_Dummy_GetCurrentComMode(NetworkHandleType NetworkHandle, ComM_ModeType * ComM_ModePtr);

static Std_ReturnType ComM_Dummy_RequestComMode(NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode)
{
    (void) NetworkHandle;
    (void) ComM_Mode;
    return E_OK;
}

static Std_ReturnType ComM_Dummy_GetCurrentComMode(NetworkHandleType NetworkHandle, ComM_ModeType * ComM_ModePtr)
{
    *ComM_ModePtr = ComM_ChannelStruct[NetworkHandle].ChannelMode_u8;
    return E_OK;
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h"
const ComM_BusSmApiType_tst ComM_BusSmApi_acst[] =
{

    {

        &CanSM_RequestComMode,
        &CanSM_GetCurrentComMode
    }
    ,
    {

        &ComM_Dummy_RequestComMode,
        &ComM_Dummy_GetCurrentComMode
    }
    ,
    {

        &ComM_Dummy_RequestComMode,
        &ComM_Dummy_GetCurrentComMode
    }
    ,
    {

        &ComM_Dummy_RequestComMode,
        &ComM_Dummy_GetCurrentComMode
    }
    ,
    {

        &ComM_Dummy_RequestComMode,
        &ComM_Dummy_GetCurrentComMode
    }
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h"

#if ((COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)||(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF))
#define COMM_START_SEC_CONST_8
#include "ComM_MemMap.h"
const ComM_InhibitionStatusType ComM_EcuGroupClassification_Init = 0x00;

#define COMM_STOP_SEC_CONST_8
#include "ComM_MemMap.h"
#endif

