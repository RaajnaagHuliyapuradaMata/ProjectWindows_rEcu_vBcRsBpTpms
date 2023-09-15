#ifndef NVM_MANAGER_H
#define NVM_MANAGER_H

#include "NvmManagerX.hpp"
#include "Rte_NvM_Type.hpp"

#define NVMMGR__BSW_NVM_SIZE              NVM_BLOCK_SIZE_BSW_DATA
#define NVMMGR__BSW_NVM_INDEX_1_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_2_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_3_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_4_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_5_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_6_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_7_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_8_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_9_SIZE          ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_10_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_11_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_12_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_13_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_14_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_15_SIZE         ((uint8) 2U)
#define NVMMGR__BSW_NVM_INDEX_16_SIZE         ((uint8) 2U)
#define NVMMGR__BSW_NVM_INDEX_17_SIZE         ((uint8) 2U)
#define NVMMGR__BSW_NVM_INDEX_18_SIZE         ((uint8) 2U)
#define NVMMGR__BSW_NVM_INDEX_19_SIZE         ((uint8) 20U)
#define NVMMGR__BSW_NVM_INDEX_20_SIZE         ((uint8) 4U)
#define NVMMGR__BSW_NVM_INDEX_22_SIZE         ((uint8) 1U)
#define NVMMGR__BSW_NVM_INDEX_21_SIZE         (NVMMGR__BSW_NVM_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_1_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_2_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_3_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_4_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_5_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_6_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_7_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_8_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_9_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_10_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_11_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_12_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_13_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_14_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_15_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_16_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_17_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_18_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_19_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_20_SIZE - \
                                               NVMMGR__BSW_NVM_INDEX_22_SIZE)

#define NVMMGR__BSW_NVM_INIT_MARKER           ((uint8) 0x58U)

typedef union{
   uint8 AU8_BSW_NvM_Array[NVMMGR__BSW_NVM_SIZE];
   struct{
      uint8 AU8_Index1_Pressure_On_Key_Enabled [NVMMGR__BSW_NVM_INDEX_1_SIZE];
      uint8 AU8_Index2_Wakeup_Interval         [NVMMGR__BSW_NVM_INDEX_2_SIZE];
      uint8 AU8_Index3_Wake_Time               [NVMMGR__BSW_NVM_INDEX_3_SIZE];
      uint8 AU8_Index4_Wake_Offset             [NVMMGR__BSW_NVM_INDEX_4_SIZE];
      uint8 AU8_Index5_POKDb                   [NVMMGR__BSW_NVM_INDEX_5_SIZE];
      uint8 AU8_Index6_Data_Existence          [NVMMGR__BSW_NVM_INDEX_6_SIZE];
      uint8 AU8_Index7_FL_Pressure             [NVMMGR__BSW_NVM_INDEX_7_SIZE];
      uint8 AU8_Index8_FL_Temperature          [NVMMGR__BSW_NVM_INDEX_8_SIZE];
      uint8 AU8_Index9_FR_Pressure             [NVMMGR__BSW_NVM_INDEX_9_SIZE];
      uint8 AU8_Index10_FR_Temperature         [NVMMGR__BSW_NVM_INDEX_10_SIZE];
      uint8 AU8_Index11_RL_Pressure            [NVMMGR__BSW_NVM_INDEX_11_SIZE];
      uint8 AU8_Index12_RL_Temperature         [NVMMGR__BSW_NVM_INDEX_12_SIZE];
      uint8 AU8_Index13_RR_Pressure            [NVMMGR__BSW_NVM_INDEX_13_SIZE];
      uint8 AU8_Index14_RR_Temperature         [NVMMGR__BSW_NVM_INDEX_14_SIZE];
      uint8 AU8_Index15_FL_Received_TG         [NVMMGR__BSW_NVM_INDEX_15_SIZE];
      uint8 AU8_Index16_FR_Received_TG         [NVMMGR__BSW_NVM_INDEX_16_SIZE];
      uint8 AU8_Index17_RL_Received_TG         [NVMMGR__BSW_NVM_INDEX_17_SIZE];
      uint8 AU8_Index18_RR_Received_TG         [NVMMGR__BSW_NVM_INDEX_18_SIZE];
      uint8 AU8_Index19_Last_Reception_Time    [NVMMGR__BSW_NVM_INDEX_19_SIZE];
      uint8 AU8_Index20_Monitoring_Time        [NVMMGR__BSW_NVM_INDEX_20_SIZE];
      uint8 AU8_Index21_Reserved               [NVMMGR__BSW_NVM_INDEX_21_SIZE];
      uint8 AU8_Index22_NvM_Intialized         [NVMMGR__BSW_NVM_INDEX_22_SIZE];
   }__attribute__((packed)) Struct_Split_BSW_NvM;
}NvmMGR__Union_BSW_NvM;

#endif
