/******************************************************************************/
/* File   : MemIf_Cfg.c                                                       */
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
#include "MemIf.hpp"

#include "Fee_30_SmallSector.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#ifndef MEMIF_LOCAL
#define MEMIF_LOCAL static
#endif

#if !defined (MEMIF_LOCAL_INLINE)
#define MEMIF_LOCAL_INLINE LOCAL_INLINE
#endif


/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define MEMIF_START_SEC_CONST_8BIT
#include "MemMap.hpp"
CONST(uint8, MEMIF_CONST) MemIf_NumberOfDevices = MEMIF_NUMBER_OF_DEVICES;
#define MEMIF_STOP_SEC_CONST_8BIT
#include "MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.hpp"
MEMIF_LOCAL_INLINE FUNC (Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_Fee_30_SmallSector_WriteWrapper(
      uint16            BlockNumber
   ,  MemIf_DataPtr_pu8 DataBufferPtr
){
   return Fee_30_SmallSector_Write(
         BlockNumber
      ,  DataBufferPtr
   );
}
#define MEMIF_STOP_SEC_CODE
#include "MemMap.hpp"

#define MEMIF_START_SEC_CONST_32BIT
#include "MemMap.hpp"
CONST(MemIf_MemHwAApi_Type, MEMIF_CONST) MemIf_MemHwaApis[MEMIF_NUMBER_OF_DEVICES] = {
   {
         Fee_30_SmallSector_Read
      ,  MemIf_Fee_30_SmallSector_WriteWrapper
      ,  Fee_30_SmallSector_EraseImmediateBlock
      ,  Fee_30_SmallSector_InvalidateBlock
      ,  Fee_30_SmallSector_Cancel
      ,  Fee_30_SmallSector_GetStatus
      ,  Fee_30_SmallSector_GetJobResult
      ,  Fee_30_SmallSector_SetMode
   }
};
#define MEMIF_STOP_SEC_CONST_32BIT
#include "MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

