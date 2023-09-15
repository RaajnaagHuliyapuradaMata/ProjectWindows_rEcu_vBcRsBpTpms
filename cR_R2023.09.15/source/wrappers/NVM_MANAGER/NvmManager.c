#include "Std_Types.hpp"

#include "NvmManager.hpp"
#include "iTPMS_Interface.hpp"
#include "Rte_NvM_Type.hpp"
#include "Nvm_Cfg.hpp"
#include "Nvm.hpp"

static uint32 NvmMGR__GetOffsetOfMember(NvmMGR__Enum_BSW_NvM_Members EN_Member);
static uint8 NvmMGR__GetSizeOfMember(NvmMGR__Enum_BSW_NvM_Members EN_Member);

uint8 ClientIf_NvM_ReadBlock(uint16 uiBlockNr,uint16 uiLen,NVM_BLOCK_TYPE *ulpDestPtr){
  uint8  l_ucRet;
  uint16 l_uiTemp;
  uint8* p2BlockAdress = (uint8*)NULL_PTR;
  l_ucRet = TRUE;
  if(uiLen >= NVM_MAX_AMOUNT_BLOCKS){
    l_ucRet = TRUE;
  }
  else{
    p2BlockAdress = Memstack_GetNvMRamAdress(uiBlockNr);
   for(l_uiTemp = 0U; l_uiTemp < uiLen; l_uiTemp++){
      ulpDestPtr[l_uiTemp] = ((uint32)p2BlockAdress[3]<<24) + ((uint32)p2BlockAdress[2]<<16) + ((uint32)p2BlockAdress[1]<<8) + ((uint32)p2BlockAdress[0]<<0);
      p2BlockAdress+=4;
   }
    l_ucRet = FALSE;
  }
  return (l_ucRet);
}

uint8 ClientIf_NvM_WriteBlock(uint16 uiBlockNr,uint16 uiLen,const NVM_BLOCK_TYPE ulpSrcPtr[]){
  uint8          l_ucRet;
  uint16         l_uiLauf;
  NVM_BLOCK_TYPE l_ulOldData;
  NVM_BLOCK_TYPE l_ulNewData;
  uint8* p2BlockAdress;
  l_ucRet = TRUE;
  if(uiLen >= NVM_MAX_AMOUNT_BLOCKS){
    l_ucRet = TRUE;
  }
  else{
    p2BlockAdress = Memstack_GetNvMRamAdress(uiBlockNr);
   for(l_uiLauf = 0;l_uiLauf < uiLen;l_uiLauf++){
      l_ulOldData = p2BlockAdress[l_uiLauf];
      l_ulNewData = ulpSrcPtr[l_uiLauf];
        p2BlockAdress[(l_uiLauf<<2) + 0] = ((uint8)(l_ulNewData >> 0));
        p2BlockAdress[(l_uiLauf<<2)  + 1] = ((uint8)(l_ulNewData >> 8));
        p2BlockAdress[(l_uiLauf<<2)  + 2] = ((uint8)(l_ulNewData >> 16));
        p2BlockAdress[(l_uiLauf<<2)  + 3] = ((uint8)(l_ulNewData >> 24));
        if(l_uiLauf == 0){
          Memstack_SetEcuNvMRamBlockStatus(uiBlockNr); // do it once
        }
   }
    l_ucRet = FALSE;
  }
  return (l_ucRet);
}

extern void NvmMGR_Init(void){
  uint8 *PU8_NvmIntialized;
  PU8_NvmIntialized = &(((NvmMGR__Union_BSW_NvM *) &Ram_NvMBlock_BSW_Data[0])->Struct_Split_BSW_NvM.AU8_Index22_NvM_Intialized[0]);
  if((*PU8_NvmIntialized) != NVMMGR__BSW_NVM_INIT_MARKER){
    *PU8_NvmIntialized = NVMMGR__BSW_NVM_INIT_MARKER;
  }
}

extern void NvmMGR_WriteBSWMember(
            NvmMGR__Enum_BSW_NvM_Members EN_Member
   ,  const uint8*                       PU8_Data
){
   uint8 U8_Counter;
   uint32 U32_StartPositionOfWrite = NvmMGR__GetOffsetOfMember(EN_Member);
   uint8 U8_SizeOfMember = NvmMGR__GetSizeOfMember(EN_Member);
   for(
      U8_Counter = 0U;
      U8_Counter < U8_SizeOfMember;
      U8_Counter ++
   ){
      Ram_NvMBlock_BSW_Data[U32_StartPositionOfWrite + U8_Counter] = PU8_Data[U8_Counter];
   }

   (void)NvM_SetRamBlockStatus(
         NvMConf_NvMBlockDescriptor_NvMBlock_BSW_Data
      ,  TRUE
   );
}

extern void NvmMGR_ReadBSWMember(
      NvmMGR__Enum_BSW_NvM_Members EN_Member
   ,  uint8*                       PU8_Data
){
   uint8 U8_Counter;
   uint32 U32_StartPositionOfRead = NvmMGR__GetOffsetOfMember(EN_Member);
   uint8 U8_SizeOfMember = NvmMGR__GetSizeOfMember(EN_Member);
   for(
      U8_Counter = 0U;
      U8_Counter < U8_SizeOfMember;
      U8_Counter ++
   ){
      PU8_Data[U8_Counter] = Ram_NvMBlock_BSW_Data[U32_StartPositionOfRead + U8_Counter];
   }
}

static uint32 NvmMGR__GetOffsetOfMember(
   NvmMGR__Enum_BSW_NvM_Members EN_Member
){
   uint32 U32_AddressOfMember = 0U;
   NvmMGR__Union_BSW_NvM *PUN_BSW_NvM;
   PUN_BSW_NvM = (NvmMGR__Union_BSW_NvM*) &Ram_NvMBlock_BSW_Data[0];
   switch(
      EN_Member
   ){
      case NVM_E_PRESSURE_ON_KEY_ENABLED: U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index1_Pressure_On_Key_Enabled[0]; break;
      case NVM_E_WAKEUP_INTERVAL:         U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index2_Wakeup_Interval[0];         break;
      case NVM_E_WAKE_TIME:               U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index3_Wake_Time[0];               break;
      case NVM_E_WAKE_OFFSET:             U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index4_Wake_Offset[0];             break;
      case NVM_E_POKDB:                   U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index5_POKDb[0];                   break;
      case NVM_E_DATA_EXISTENCE:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index6_Data_Existence[0];          break;
      case NVM_E_FL_PRESSURE:             U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index7_FL_Pressure[0];             break;
      case NVM_E_FL_TEMPERATURE:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index8_FL_Temperature[0];          break;
      case NVM_E_FR_PRESSURE:             U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index9_FR_Pressure[0];             break;
      case NVM_E_FR_TEMPERATURE:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index10_FR_Temperature[0];         break;
      case NVM_E_RL_PRESSURE:             U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index11_RL_Pressure[0];            break;
      case NVM_E_RL_TEMPERATURE:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index12_RL_Temperature[0];         break;
      case NVM_E_RR_PRESSURE:             U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index13_RR_Pressure[0];            break;
      case NVM_E_RR_TEMPERATURE:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index14_RR_Temperature[0];         break;
      case NVM_E_FL_RECEIVED_TG:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index15_FL_Received_TG[0];         break;
      case NVM_E_FR_RECEIVED_TG:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index16_FR_Received_TG[0];         break;
      case NVM_E_RL_RECEIVED_TG:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index17_RL_Received_TG[0];         break;
      case NVM_E_RR_RECEIVED_TG:          U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index18_RR_Received_TG[0];         break;
      case NVM_E_LAST_RECEPTION_TIME:     U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index19_Last_Reception_Time[0];    break;
      case NVM_E_MONITORING_TIME:         U32_AddressOfMember = (uint32) &PUN_BSW_NvM->Struct_Split_BSW_NvM.AU8_Index20_Monitoring_Time[0];        break;
      default:                                                                                                                                     break;
   }
   return (U32_AddressOfMember - ((uint32) &Ram_NvMBlock_BSW_Data[0]));
}

static uint8 NvmMGR__GetSizeOfMember(
   NvmMGR__Enum_BSW_NvM_Members EN_Member
){
   uint8 U8_SizeOfMember;
   switch(
      EN_Member
   ){
      case NVM_E_PRESSURE_ON_KEY_ENABLED: U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index1_Pressure_On_Key_Enabled); break;
      case NVM_E_WAKEUP_INTERVAL:         U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index2_Wakeup_Interval);         break;
      case NVM_E_WAKE_TIME:               U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index3_Wake_Time);               break;
      case NVM_E_WAKE_OFFSET:             U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index4_Wake_Offset);             break;
      case NVM_E_POKDB:                   U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index5_POKDb);                   break;
      case NVM_E_DATA_EXISTENCE:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index6_Data_Existence);          break;
      case NVM_E_FL_PRESSURE:             U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index7_FL_Pressure);             break;
      case NVM_E_FL_TEMPERATURE:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index8_FL_Temperature);          break;
      case NVM_E_FR_PRESSURE:             U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index9_FR_Pressure);             break;
      case NVM_E_FR_TEMPERATURE:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index10_FR_Temperature);         break;
      case NVM_E_RL_PRESSURE:             U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index11_RL_Pressure);            break;
      case NVM_E_RL_TEMPERATURE:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index12_RL_Temperature);         break;
      case NVM_E_RR_PRESSURE:             U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index13_RR_Pressure);            break;
      case NVM_E_RR_TEMPERATURE:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index14_RR_Temperature);         break;
      case NVM_E_FL_RECEIVED_TG:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index15_FL_Received_TG);         break;
      case NVM_E_FR_RECEIVED_TG:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index16_FR_Received_TG);         break;
      case NVM_E_RL_RECEIVED_TG:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index17_RL_Received_TG);         break;
      case NVM_E_RR_RECEIVED_TG:          U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index18_RR_Received_TG);         break;
      case NVM_E_LAST_RECEPTION_TIME:     U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index19_Last_Reception_Time);    break;
      case NVM_E_MONITORING_TIME:         U8_SizeOfMember = sizeof(((NvmMGR__Union_BSW_NvM*) 0)->Struct_Split_BSW_NvM.AU8_Index20_Monitoring_Time);        break;
      default:                                                                                                                                             break;
   }
   return U8_SizeOfMember;
}
