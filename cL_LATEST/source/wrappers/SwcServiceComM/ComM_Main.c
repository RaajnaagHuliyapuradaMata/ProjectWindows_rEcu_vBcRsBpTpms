

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_MainFunction_ComMChannel_Can_Network_0_Channel(void){
   ComM_Lok_ChannelMainFunction(0) ;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#if(COMM_PNC_GW_ENABLED == STD_ON)

#endif

#if(COMM_PNC_ENABLED == STD_ON)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

extern void ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void);

void ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void){
   ComM_Lok_EIRA_CallBack(0);
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

