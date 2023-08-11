

#ifndef  COMM_CFG_INTERNAL_H
#define  COMM_CFG_INTERNAL_H

#include "ComM_Cfg.h"

#define COMM_CAN                STD_ON
#define COMM_LIN                STD_OFF
#define COMM_FLXRY              STD_OFF
#define COMM_ETH                STD_OFF

#define COMM_NO_OF_USERS        1
#define COMM_NO_OF_CHANNELS     1

#define COMM_NVM_NO_WAKEUP_SIZE             1
#define COMM_MAX_CHANNEL_REQUESTERS         1
#define COMM_DEV_ERROR_DETECT               STD_OFF
#define COMM_SYNCHRONOUS_WAKE_UP            STD_OFF
#define COMM_USERID_MIN                     0
#define COMM_USERID_MAX                     0

#define COMM_VERSION_INFO_API               STD_OFF

#define COMM_NM_SUPPORT                     STD_OFF

#define COMM_DCM_SUPPORT                    STD_ON

#define COMM_RTE_SUPPORT                    STD_OFF
#define COMM_FULLCOMREQ_NOTIF               STD_OFF

#define COMM_PNC_ENABLED                    STD_OFF

#define COMM_ZERO_PNC_VECTOR_AVOIDANCE      STD_OFF

#define COMM_PNC_GW_ENABLED                 STD_OFF

#define COMM_LIMIT_TO_NOCOM_ENABLED         STD_OFF

#define COMM_PREVENT_WAKEUP_ENABLED         STD_OFF

#define COMM_NVM_ENABLED                    STD_OFF

#define COMM_MANAGING_CHANNEL_PRESENT       STD_OFF

#if(COMM_NM_SUPPORT!= STD_OFF)

#define COMM_NM_VARIANT                     COMM_NM_VARIANT_PASSIVE
#endif

#define COMM_INHIBITION_ENABLED     ((COMM_PREVENT_WAKEUP_ENABLED != STD_OFF) || (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))

#define COMM_RESET_AFTER_NO_COM             STD_OFF

#define COMM_MAX_NO_OF_PNCS                 (56)

#define COMM_NO_OF_PNCS                     (0)

#define COMM_NO_OF_CH_WITH_ERA              (0)

#define COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA     (1)

#if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
typedef ComM_UserHandleType ComM_InternalHandleArrayType;
typedef struct{
  uint8 numberOfRequesters;
  ComM_InternalHandleArrayType handleArray[COMM_MAX_CHANNEL_REQUESTERS];
} ComM_UserHandleArrayType;
#endif

typedef struct{

     Std_ReturnType (*BusSm_RequestComMode) (NetworkHandleType, ComM_ModeType);
     Std_ReturnType (*BusSm_GetCurrentComMode) (NetworkHandleType,
                    ComM_ModeType * ComM_ModePtr);
}ComM_BusSmApiType_tst;

typedef struct{
    const uint8 *       DirectChannels_pcu8;
#if (COMM_PNC_ENABLED != STD_OFF)
    const uint8 *       Pncs_pcu8;
#endif
    uint8               NumDirectChannels_u8;
    uint8               NumAllChannels_u8;
#if (COMM_PNC_ENABLED != STD_OFF)
    uint8               NumPnc_u8;
#endif
}ComM_UsersType_tst;

typedef struct ComM_ChannelTypeStruct
{
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    const uint8 *                   Pncs_pcu8;
#endif
#if (COMM_INHIBITION_ENABLED)
    const uint8 *                   DirectUsers_pcu8;
#endif
    const uint8 *                   AllUsers_pcu8;
    ComM_BusType_ten                BusType_en;
    ComM_NMVariantType_ten          ComMNmVariant_en;
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    ComM_PncGatewayType_ten         PncGwType_en;
#endif
    uint32                          NmLightTimeout_u32;
    uint16                          TMinFullComModeDuration_u16;
#if (COMM_PNC_ENABLED != STD_OFF)
    uint16                          TxSigId_u16;
#endif
    NetworkHandleType               ComMChannelId_u8;
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    uint8                           numPncs_u8;
#endif
#if (COMM_INHIBITION_ENABLED)
    uint8                           numDirectUsers_u8;
    uint8                           InhibitionInitValue_u8;
#endif
    uint8                           numAllUsers_u8;
#if (COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
    uint8                           masterChannelId_u8;
#endif
#if(COMM_PNC_ENABLED != STD_OFF)
    boolean                         PncNmRequest_b;
#endif
#if(COMM_NVM_ENABLED != STD_OFF)
    boolean                         ComMNoWakeUpInhibitionNvmStorage_b;
#endif
#if (COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
    boolean                         ComMMasterChannelPresent_b;
#endif
    boolean                         ComMFullCommRequestNotificationEnabled_b;
}ComM_ChannelType_tst;

typedef struct ComM_PncStructType
{
    const uint8 *       Channels_pcu8;
#if(COMM_INHIBITION_ENABLED)
    const uint8 *       Users_pcu8;
#endif
    uint16              PrepareSleepTimer_u16;
#if(COMM_INHIBITION_ENABLED)
    uint8               NumUsers_u8;
#endif
    uint8               NumChannels_u8;
    uint8               PncId_u8;
}ComM_PncConfigStruct_tst;

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

#if(COMM_PNC_ENABLED != STD_OFF)
// For Signal array type for ERA and EIRA Rx signals of PNC
typedef const uint16 ComM_SignalArrayType[COMM_NO_OF_PNCS];
#endif

// Global config structure to store pointers to all config tables

typedef struct{
    const ComM_ChannelType_tst *        ChannelConfig_pcst;
    const ComM_UsersType_tst *          UserConfig_pcst;
#if(COMM_PNC_ENABLED != STD_OFF)
    const ComM_PncConfigStruct_tst *    PncConfig_pcst;
    const ComM_SignalArrayType *        EiraSignalTable_pcst;
#if(COMM_PNC_GW_ENABLED != STD_OFF)
    const ComM_SignalArrayType *        EraSignalTable_pcst;
#endif
    boolean                             ComMPncEnabled_b;
#endif
}ComM_GlobalConfigType_tst;

#endif

#if (COMM_RTE_SUPPORT != STD_OFF)
extern void ComM_Lok_Rte_Switch_UM_currentMode(ComM_UserHandleType UserId_u8, uint8 lowestMode_u8);
#endif

#if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
extern void ComM_CurrentChannelRequest_Rte_Write(uint8 ChannelId,ComM_UserHandleArrayType * data);
#endif

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"
#if (COMM_INHIBITION_ENABLED)
extern const ComM_InhibitionStatusType ComM_EcuGroupClassification_Init;
#endif
extern const ComM_UserHandleType ComM_UserId_MappingTable_acst[];
#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h"
extern const ComM_BusSmApiType_tst ComM_BusSmApi_acst[];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"
extern const ComM_ChannelType_tst ComM_ChanelList_acst[];
extern const ComM_UsersType_tst ComM_UserList_acst[];

#if (COMM_PNC_ENABLED != STD_OFF)
extern const ComM_PncConfigStruct_tst ComM_PncList_acst[];
#endif
#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"
#if (COMM_PNC_ENABLED != STD_OFF)

extern const uint16 ComM_EIRA_RxSig_acu16[];

#if(COMM_PNC_GW_ENABLED != STD_OFF)
extern const uint16 ComM_ERA_RxSig_acu16[];
#endif

#endif
#define COMM_STOP_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"

#endif
