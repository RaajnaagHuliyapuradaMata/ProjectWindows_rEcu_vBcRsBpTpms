#ifndef NVM_MANAGER_X_H
#define NVM_MANAGER_X_H

typedef enum{
      NVM_E_PRESSURE_ON_KEY_ENABLED
   ,  NVM_E_WAKEUP_INTERVAL
   ,  NVM_E_WAKE_TIME
   ,  NVM_E_WAKE_OFFSET
   ,  NVM_E_POKDB
   ,  NVM_E_DATA_EXISTENCE
   ,  NVM_E_FL_PRESSURE
   ,  NVM_E_FL_TEMPERATURE
   ,  NVM_E_FR_PRESSURE
   ,  NVM_E_FR_TEMPERATURE
   ,  NVM_E_RL_PRESSURE
   ,  NVM_E_RL_TEMPERATURE
   ,  NVM_E_RR_PRESSURE
   ,  NVM_E_RR_TEMPERATURE
   ,  NVM_E_FL_RECEIVED_TG
   ,  NVM_E_FR_RECEIVED_TG
   ,  NVM_E_RL_RECEIVED_TG
   ,  NVM_E_RR_RECEIVED_TG
   ,  NVM_E_LAST_RECEPTION_TIME
   ,  NVM_E_MONITORING_TIME
}NvmMGR__Enum_BSW_NvM_Members;

extern void NvmMGR_Init(void);
extern void NvmMGR_WriteBSWMember(NvmMGR__Enum_BSW_NvM_Members EN_Member, const uint8 *PU8_Data);
extern void NvmMGR_ReadBSWMember(NvmMGR__Enum_BSW_NvM_Members EN_Member, uint8 *PU8_Data);

#endif
