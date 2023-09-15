

#ifndef COMM_PRIV_H
#define COMM_PRIV_H

#include "ComM.hpp"
#include "ComM_Cfg_Internal.hpp"
#include "BswM_ComM.hpp"
#include "ComM_Cfg_SchM.hpp"
#include "EcuM.hpp"

#include "Bfx.hpp"

#if(COMM_PNC_ENABLED != STD_OFF)
#include "Com.hpp"
#endif

#if(COMM_NM_SUPPORT != STD_OFF)
#include "Nm.hpp"
#endif

#if(COMM_DCM_SUPPORT == STD_ON)
#include "Dcm_Cbk.hpp"
#endif

#if(COMM_DEV_ERROR_DETECT==STD_ON)
#include "Det.hpp"
#endif

#if(COMM_NVM_ENABLED != STD_OFF)
#include "NvM.hpp"
#endif

// Interface API IDs for DET interface

#define COMM_INSTANCE_ID                           ((uint8)0x00)

#define COMM_INIT_APIID                            ((uint8)0x01)

#define COMM_DEINIT_APIID                          ((uint8)0x02)

#define COMM_GET_STATUS_APIID                      ((uint8)0x03)

#define COMM_GET_INHIBITION_STATUS_APIID           ((uint8)0x04)

#define COMM_REQ_COMMODE_APIID                     ((uint8)0x05)

#define COMM_GET_MAX_COMMODE_APIID                 ((uint8)0x06)

#define COMM_GET_REQ_COMMODE_APIID                 ((uint8)0x07)

#define COMM_GET_CUR_COMMODE_APIID                 ((uint8)0x08)

#define COMM_PREVENT_WAKEUP_APIID                  ((uint8)0x09)

#define COMM_LIMIT_CHNLTO_NOCOMMODE_APIID          ((uint8)0x0b)

#define COMM_LIMIT_ECUTO_NOCOMMODE_APIID           ((uint8)0x0c)

#define COMM_READ_INHIBIT_COUNTER_APIID            ((uint8)0x0d)

#define COMM_RESET_INHIBIT_COUNTER_APIID           ((uint8)0x0e)

#define COMM_SET_ECUGROUPCLASS_APIID               ((uint8)0x0f)

#define COMM_GETVERINFO_APIID                      ((uint8)0x10)

#define COMM_MAINFNC_APIID                         ((uint8)0x60)

#define COMM_NM_BUS_SLEEPMODE                      ((uint8)0x1a)

#define COMM_NM_NETWORKMODE                        ((uint8)0x18)

#define COMM_NM_NETWORKSTART_INDICATION            ((uint8)0x15)

#define COMM_NM_PREPARE_BUSSLEEPMODE               ((uint8)0x19)

#define COMM_NM_RESTARTINDICATION                  ((uint8)0x1b)

#define COMM_DCM_ACTIVEDIAG                        ((uint8)0x1f)

#define COMM_DCM_INACTIVEDIAG                      ((uint8)0x20)

#define COMM_COMMUNICATION_ALLOWED                 ((uint8)0x29)

#define COMM_ECUM_WAKEUP_INDICATION                ((uint8)0x2a)

#define COMM_ECUM_PNCWAKEUP_INDICATION             ((uint8)0x38)

#define COMM_BUSSM_MODEINDICATION                  ((uint8)0x33)

#define COMM_GET_STATE_APIID                       ((uint8)0x34)

#define COMM_EIRA_CBK_APIID                         ((uint8)0x35)

#define COMM_ERA_CBK_APIID                          ((uint8)0x36)

#define COMM_PNC_MAINFNC_APIID                      ((uint8)0x37)

#define COMM_NVM_REFERENCE_BLOCK                    ((uint8)0x40)

#define COMM_INHIBITION_COUNTER                     ((uint8)0x41)

// Module specific Return values
#define COMM_E_MODE_LIMITATION                      2

#define COMM_E_NOT_INITIALIZED                      3

// DET error ID's

#define COMM_E_NOT_INITED                          ((uint8)(0x1))

#define COMM_E_WRONG_PARAMETERS                    ((uint8)(0x2))

#define COMM_E_ERROR_IN_PROV_SERVICE               ((uint8)(0x3))

#define COMM_E_CNTR_UNDERFLW                        ((uint8)0x04)

#define COMM_E_NVM_WRITE_FAILED                     ((uint8)0x05)

#define COMM_E_IHHIBITION_CNTR_UNDERFLW             ((uint8)0x06)

#define COMM_E_IHHIBITION_CNTR_OVERFLW              ((uint8)0x07)

// Macro for Active diagnosis
#define COMM_ACTIVE_DIAGNOSTICS                     TRUE

// Macro for Inactive diagnosis
#define COMM_INACTIVE_DIAGNOSTICS                   FALSE

/*Macro for ComM NM Vaiant*/
#define COMM_NM_VARIANT_FULL                        TRUE

/*Macro for ComM NM Vaiant*/
#define COMM_NM_VARIANT_PASSIVE                     FALSE
#define COMM_NOT_USED_USER_ID                       ((uint8)0xFF)

/* Macro Functions */

// Macro to set limit to no com in ComM_InhibitionStatusType
#define COMM_SET_LIMIT_TO_NO_COM(Reg)              (void)(Bfx_SetBit_u8u8(&(Reg), 0x01))

// Macro to set prevent wake up in ComM_InhibitionStatusType
#define COMM_SET_PREVENT_WAKEUP(Reg)               (void)(Bfx_SetBit_u8u8(&(Reg), 0x00))

// Macro to clear limit to no com in ComM_InhibitionStatusType
#define COMM_CLR_LIMIT_TO_NO_COM(Reg)              (void)(Bfx_ClrBit_u8u8(&(Reg), 0x01))

// Macro to clear prevent wake up in ComM_InhibitionStatusType
#define COMM_CLR_PREVENT_WAKEUP(Reg)               (void)(Bfx_ClrBit_u8u8(&(Reg), 0x00))

// Macro to get limit to no com in ComM_InhibitionStatusType
#define COMM_GET_LIMIT_TO_NO_COM(Reg)              (Bfx_GetBit_u8u8_u8((Reg),0x01))

//Macro to get prevent wake up in ComM_InhibitionStatusType
#define COMM_GET_PREVENT_WAKEUP(Reg)               (Bfx_GetBit_u8u8_u8((Reg),0x00))

//Macro to set bit
#define COMM_SET_BIT(Reg,Position)                 (void)(Bfx_SetBit_u8u8(&(Reg),Position))
/* Constants */

#ifndef  C_ZERO
#define C_ZERO                     ((uint8)0x00)
#endif

#ifndef  C_ZERO_U16
#define C_ZERO_U16                 ((uint16)0x0000)
#endif

#ifndef  C_ONE
#define C_ONE                      ((uint8)0x01)
#endif

/* Mask for WakeUp inhibition */
#define COMM_WAKEUP_INHIBITION      ((uint8)0x01)

/* Mask for Limit to no com */
#define COMM_LIMIT_TO_NOCOM         ((uint8)0x02)

/* Macro for Invalid UserId */
#define COMM_USER_INVALID_ID        ((uint8)0xFF)

/* Macro for ComSignal invalid value */
#define COMM_COMSIGNAL_INVALID_ID   ((uint16)0xFFFF)

/* Macro for max value of u16 variable */
#define COMM_MAX_U16                ((uint16)0xFFFF)

/* Access macros to keep PC and PB variants same */
#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

/* Access macros for Post build */

/* If the variant is Post build, then get the actual value of PNC switch from configuration*/
#define COMM_GET_FEATURE_PNC_ENABLED  (ComM_GlobalConfigPtr_pgcs->ComMPncEnabled_b)

/* Access macros for config data for PB variant-- through global cfg ptrs */
#define COMM_GET_CHANNEL_LIST     (ComM_GlobalConfigPtr_pgcs->ChannelConfig_pcst)
#define COMM_GET_USER_LIST        (ComM_GlobalConfigPtr_pgcs->UserConfig_pcst)
#define COMM_GET_PNC_LIST         (ComM_GlobalConfigPtr_pgcs->PncConfig_pcst)
#define COMM_GET_EIRASIG_TABLE    (ComM_GlobalConfigPtr_pgcs->EiraSignalTable_pcst)
#define COMM_GET_ERASIG_TABLE     (ComM_GlobalConfigPtr_pgcs->EraSignalTable_pcst)

#else

/* Access macros for Pre compile */

/* If the variant is Pre compile, this always returns TRUE,
 * (because the code is switched off through compiler switch itself.
 * Runtime check will be optimsied by compiler as it it always true
 */
#define COMM_GET_FEATURE_PNC_ENABLED  (TRUE)

/* Access macro for cfg data for precompile variant-- access directly w/o pointers
 * to keep the code optimised for Pre compile variant */

#define COMM_GET_CHANNEL_LIST       ComM_ChanelList_acst
#define COMM_GET_USER_LIST          ComM_UserList_acst
#define COMM_GET_PNC_LIST           ComM_PncList_acst
#define COMM_GET_EIRASIG_TABLE      ComM_EIRA_RxSig_acu16
#define COMM_GET_ERASIG_TABLE       ComM_ERA_RxSig_acu16

#endif

/* boolean variable to check Diagnostic type of channel */
typedef boolean ComM_DiagnosticType;

/* to differentiate between inhibitions */
typedef enum{
  COMM_PREVENTWAKEUP
   ,  COMM_LIMITTONOCOM
}ComM_InhibitionType_ten;

/* Global RAM structure to store variables at ComM level
typedef struct{
   ComM_InitStatusType             ComM_InitStatus;                Holds ComM init status
#if(COMM_INHIBITION_ENABLED)
   uint16                          ComM_InhibitCounter_u16;        Holds count of full com requests inhibited
   ComM_InhibitionStatusType       ComM_EcuGroupClassification_u8; Holds group classification status value
#endif        COMM_INHIBITION_ENABLED compiler switch ends here
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
   boolean                         ComM_LimitECUToNoCom_b;         Holds limit ECU to No Com status
#endif       COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF compiler switch ends here
}ComM_GlobalVarType_tst;  */

typedef struct{
   ComM_InitStatusType                             ComM_InitStatus_en;
#if(COMM_INHIBITION_ENABLED)
   uint16                                          ComM_InhibitCounter_u16;
   ComM_InhibitionStatusType                       ComM_EcuGroupClassification_u8;
#endif      /*#if(COMM_INHIBITION_ENABLED)  */
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
   boolean                                         ComM_LimitECUToNoCom_b;
#endif      /*#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */
}ComM_GlobalVarType_tst;

/*
ComM_ChannelVarType
typedef struct{
   ComM_StateType              ChannelState_e;                         Holds the current state of the channel
   uint32                      LightTimeoutCtr_u32;                    Holds Light time out counter value
   uint16                      MinFullComTimeoutCtr_u16;               Holds minimum full com duration counter value
   uint16                      UserRequestCtr_u16;                     Holds the count of full com requests of users
                                                                        assigned to this channel
   ComM_ModeType               ChannelMode_u8;                         Holds the current mode of the channel
   ComM_ModeType               BusSmMode_u8;                           Holds the current mode of BusSM
   uint8                       PassiveRequestState_u8;                 Holds the passive request state of channel
   uint8                       PncRequestCtr_u8;                       Holds the count of PNC's in requested state
                                                                        that are assigned to this channel
   ComM_InhibitionStatusType   InhibitionReqStatus_u8;                 Holds the current inhibition status of the
                                                                        channel
   ComM_DiagnosticType         DiagnosticRequestState_b;               Indicates if DCM request is present or not
   boolean                     BusSmRequestedModeAchieved_b;           Indicates if BusSm is in the same mode as
                                                                        requested mode by ComM
   boolean                     CommunicationAllowed_b;                 Holds the value of Communication allowed for
                                                                        the particular channel
   boolean                     NmBusSleepIndicationStatus_b;           Indicates if Bus sleep is indicated by Nm
   boolean                     NmPrepareBusSleepIndicationStatus_b;    Indicates if prepare bus sleep is indicated by
                                                                        Nm
   boolean                     NmNetworkModeStatus_b;                  Indicates if Network mode is indicated by Nm
   boolean                     NmNetworkRequestStatus_b;               Indicates if Network request has to be called
}ComM_ChannelVarType_tst;
 */
typedef struct{
#if(COMM_PNC_ENABLED != STD_OFF)
   uint8                           PnTxSigVal_u8[8];
#endif
   ComM_StateType                  ChannelState_e;
   uint32                          LightTimeoutCtr_u32;
   uint16                          MinFullComTimeoutCtr_u16;
   uint16                          UserRequestCtr_u16;
   ComM_ModeType                   ChannelMode_u8;
   ComM_ModeType                   BusSmMode_u8;
   uint8                           PassiveRequestState_u8;
   uint8                           PncRequestCtr_u8;
   ComM_InhibitionStatusType       InhibitionReqStatus_u8;
   boolean                         NmNetworkRequestStatus_b;
   ComM_DiagnosticType             DiagnosticRequestState_b;
   boolean                         CommunicationAllowed_b;
   boolean                         NmBusSleepIndicationStatus_b;
   boolean                         NmPrepareBusSleepIndicationStatus_b;
   boolean                         NmNetworkModeStatus_b;
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
   boolean                         ComMFullComReqNotify_b;
#endif
}ComM_ChannelVarType_tst;

typedef struct{
   uint16             WakeUpInhibitionCtr_u16;
   uint16             LimitToNoComCtr_u16;
   ComM_ModeType      RequestedUserMode_u8;
   ComM_ModeType      IndicatedUserMode_u8;
   uint8              numChannelsInFullCom_u8;
   uint8              numChannelsInSilentCom_u8;
   uint8              numChannelsInNoCom_u8;
}ComM_UserVarType_tst;

typedef struct{
   ComM_PncModeType    PncState_en;
   uint16              PrepareSleepTimer_u16;
   uint8               UserRequestCnt_u8;
   uint8               EIRACnt_u8;
#if(COMM_INHIBITION_ENABLED)
   uint16              LimitToNoComCtr_u16;
   uint16              WakeUpInhibitionCtr_u16;
#endif
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   uint8               ERACnt_u8;
   uint8               ActiveERACnt_u8;
   boolean             ActiveERAStateOld_b;
#endif
   boolean             WakeUpStatus_b;
}ComM_PncRamStructType_tst;

typedef struct{
   boolean     ActiveRequest_b;
   boolean     PassiveRequest_b;
}ComM_RequestStructType_tst;

typedef struct{
   boolean  activeRequestState_b;
   boolean  wakeupRequestState_b;
   boolean  passiveRequestState_b;
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   boolean  activeERAState_b;
#endif
}ComM_PncEventStructType_tst;

typedef struct{
   uint16                                           Inhibitioncounter_u16;
   uint8                                            ComMNoWakeup_u8[COMM_NVM_NO_WAKEUP_SIZE];
   uint8                                            ComMEcuGroupClassification_u8;
}ComM_NvMStorageType_tst;

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_MemMap.hpp"

extern ComM_GlobalVarType_tst                       ComM_GlobalStruct;

extern ComM_ChannelVarType_tst                      ComM_ChannelStruct[];

extern ComM_NvMStorageType_tst                      ComM_NvMblock;

extern ComM_UserVarType_tst                         ComM_UserStruct[];
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
extern ComM_UserHandleArrayType                     ComM_FullComRequestors[COMM_NO_OF_CHANNELS];
#endif
#if(COMM_PNC_ENABLED != STD_OFF)

extern ComM_PncRamStructType_tst                    ComM_PncRamStruct[];

extern boolean                                      ComM_EIRA_RxSigVal[][COMM_NO_OF_PNCS];

#if(COMM_PNC_GW_ENABLED == STD_ON)

extern boolean                                      ComM_ERA_RxSigVal[][COMM_NO_OF_PNCS];

#endif
#endif

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_MemMap.hpp"

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
extern const ComM_GlobalConfigType_tst *    ComM_GlobalConfigPtr_pgcs;
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

extern void ComM_Lok_UpdateChannelModes(NetworkHandleType Channel_tu8, ComM_ModeType PreviousMode_tu8
   ,                                                                                   ComM_ModeType CurrentMode_tu8);

extern void ComM_Lok_TranslateInhibitionStatus(NetworkHandleType Channel_tu8, ComM_InhibitionType_ten InhibitionType_en
   ,                                                                                                    boolean Status_b);

extern void ComM_Lok_PncToChannelInterface(PNCHandleType PncIndex_tu8, ComM_PncModeType PncState_en
   ,                                           ComM_PncModeType PncPreviousState_en, boolean  ActiveERAState_b);

extern void ComM_Lok_PncMainFunction (PNCHandleType PncIndex_tu8);

extern void ComM_Lok_EIRA_CallBack(uint8 PnBusId_u8);

extern void ComM_Lok_ERA_CallBack(uint8 PnBusId_u8, ComM_PncGatewayType_ten channelGwType_en);

extern void ComM_Lok_ChannelMainFunction (NetworkHandleType ChannelIndex_tu8);

extern ComM_ModeType ComM_Lok_getLeastBusSmMode(ComM_UserHandleType UserIndex_tu8);

extern void ComM_Lok_RteNotifyLowestComMode (ComM_UserHandleType UserIndex_tu8);

extern void ComM_Lok_SyncWakeUpIndication(void);

extern void ComM_Lok_ProcessLimitToNoCom(NetworkHandleType Channel_tu8, boolean Status_b);

extern void ComMAppl_IncompatibleGenerator(void);

extern boolean ComM_Lok_ValidateUserId(ComM_UserHandleType UserId_tu8);

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
extern void ComM_Lok_UpdateFullComRequestors(ComM_UserHandleType User_tu8, ComM_ModeType ComMode_tu8);
#endif
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

