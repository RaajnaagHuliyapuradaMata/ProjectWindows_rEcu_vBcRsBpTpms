/******************************************************************************/
/* File   : Dem_Cfg_NvmCallbacks.c                                            */
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
#include "Std_Types.hpp"

#include "Dem_Cfg_NvmCallbacks.hpp"
#include "Dem_NvmCallbacks.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback0(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,0);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback1(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,1);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback2(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,2);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback3(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,3);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback4(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,4);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback5(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,5);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback6(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,6);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback7(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,7);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback8(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,8);
}

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback9(void* NvMBuffer){
   return Dem_EvMemNvMWriteRamBlockToNvCallback(NvMBuffer,9);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback0(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,0);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback1(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,1);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback2(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,2);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback3(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,3);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback4(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,4);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback5(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,5);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback6(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,6);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback7(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,7);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback8(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,8);
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback9(void* NvMBuffer){
   return Dem_EvMemNvmReadRamBlockFromNvCallback(NvMBuffer,9);
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

