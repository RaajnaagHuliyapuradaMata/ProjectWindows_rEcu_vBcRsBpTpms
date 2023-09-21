#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnvMain.hpp                                               */
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
#define DEM_CFG_ENVMINSIZE_OF_RAWENVDATA           (32u + 0u + 0u)
#define DEM_CFG_ENVMINSIZE_OF_MULTIPLE_RAWENVDATA   (32u + 0u + 0u)
#define DEM_CFG_OFFSET_OBDRAWENVDATA         0u

#define DEM_CFG_ENVEVENTID2ENVDATA \
{ \
   { 0u,0u }                                           \
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, DEM_FREEZEFRAME_FREEZEFRAMEDATASET_RIVIANSNAPSHOT }\
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
}

#define DEM_CFG_J1939_ENVEVENTID2ENVDATA \
{ \
   { 0u,0u }                                           \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
   ,{  0u, 0u }                                         \
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

