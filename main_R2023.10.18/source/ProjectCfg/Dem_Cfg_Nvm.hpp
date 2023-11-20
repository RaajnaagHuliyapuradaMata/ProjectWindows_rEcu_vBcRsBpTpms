#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Nvm.hpp                                                   */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_NVM_ID_DEM_GENERIC_NV_DATA           0u
#define DEM_NVM_ID_EVMEM_LOC_0                   1u
#define DEM_NVM_ID_EVMEM_LOC_1                   2u
#define DEM_NVM_ID_EVMEM_LOC_2                   3u
#define DEM_NVM_ID_EVMEM_LOC_3                   4u
#define DEM_NVM_ID_EVMEM_LOC_4                   5u
#define DEM_NVM_ID_EVMEM_LOC_5                   6u
#define DEM_NVM_ID_EVMEM_LOC_6                   7u
#define DEM_NVM_ID_EVMEM_LOC_7                   8u
#define DEM_NVM_ID_EVMEM_LOC_8                   9u
#define DEM_NVM_ID_EVMEM_LOC_9                   10u
#define DEM_NVM_ID_EVT_STATUSBYTE                11u

#define DEM_NVM_CFG_BLOCKID_TYPE                 uint8
#define DEM_NVM_CFG_NUM_BLOCKS_TOTAL             12
#define DEM_NVM_CFG_NUM_BLOCKS_EXTENDED          11

#define DEM_NVM_CFG_NUM_STORAGEBUFFER            2
#define DEM_CFG_COPY_FCT_ID_MEMCOPY           0
#define DEM_NVM_CFG_COPYFCT_NUM  1
#define DEM_NVM_CFG_COPYFCT_INIT  { (&Dem_NvMNormalMemCopy)   }

#define DEM_NVM_CFG_NVM_BLOCK_IDS                \
{\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdDemGenericNvData,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc0,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc1,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc2,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc3,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc4,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc5,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc6,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc7,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc8,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc9,\
    NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvStatusByte\
}

#define DEM_NVM_CFG_BLOCKS_EXTENDED              \
{\
   {&Dem_GenericNvData, DEM_SIZEOF_VAR(Dem_GenericNvData), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[0], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[1], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[2], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[3], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[4], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[5], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[6], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[7], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[8], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY},\
   {&Dem_EvMemEventMemory[9], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType), DEM_CFG_COPY_FCT_ID_MEMCOPY}\
}

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

