#pragma once
/******************************************************************************/
/* File   : Dcm_Cfg_DspUds.hpp                                                */
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
#define DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED                 DCM_CFG_ON
#define DCM_CFG_DSP_ECURESET_ENABLED                                 DCM_CFG_ON
#define DCM_CFG_DSP_SECURITYACCESS_ENABLED                           DCM_CFG_ON
#define DCM_CFG_DSP_TESTERPRESENT_ENABLED                            DCM_CFG_ON
#define DCM_CFG_DSP_TESTERPRESENTSB_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED                        DCM_CFG_ON
#define DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED               DCM_CFG_ON
#define DCM_CFG_DSP_ROUTINECONTROL_ENABLED                           DCM_CFG_ON
#define DCM_CFG_DSP_IOCBI_ENABLED                                    DCM_CFG_OFF
#define RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED                   DCM_CFG_OFF
#define DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED                     DCM_CFG_ON
#define DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED                    DCM_CFG_ON
#define DCM_CFG_DSP_TRANSFERDATA_ENABLED                             DCM_CFG_ON
#define DCM_CFG_DSP_DATA_ASYNCHCS_ENABLED                            DCM_CFG_OFF
#define DCM_CFG_DSP_IOCBI_ASP_ENABLED                                DCM_CFG_OFF
#define DCM_CFG_DSP_READ_ASP_ENABLED                                 DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_ASP_ENABLED                                DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_SYNCH_FNC_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_SR_ENABLED                                 DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_FIXED_LENGTH                               DCM_CFG_ON
#define DCM_CFG_DSP_WRITE_VARIABLE_LENGTH                            DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED              DCM_CFG_OFF
#define DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED                     DCM_CFG_ON
#define DCM_CFG_DSP_REQUESTUPLOAD_ENABLED                            DCM_CFG_OFF
#define DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED                          DCM_CFG_ON
#define DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED                      DCM_CFG_ON
#define DCM_CFG_DSP_RESPONSEONEVENT_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSP_ROEEVENT_ENABLED                                 DCM_CFG_OFF
#define DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED                      DCM_CFG_OFF
#define DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED                     DCM_CFG_OFF
#define DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED             DCM_CFG_OFF
#define DCM_CFG_DSP_READDTCINFORMATION_ENABLED                       DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED                         DCM_CFG_ON
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED                         DCM_CFG_OFF
#define DCM_CFG_NUMRDTCSUBFUNC         5u
#define DCM_CFG_RDTC_MAXNUMDTCREAD     1u
#define DCM_CFG_RDTC_MAXNUMRECREAD     1u
#define DCM_CFG_CANFD_ENABLED DCM_CFG_ON
#define DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_NUMSESSIONS        5u
#define DCM_CFG_DSP_DSC_SESRECINRESP   DCM_CFG_ON
#define DCM_CFG_DSP_SECA_ASP_ENABLED       DCM_CFG_OFF
#define DCM_CFG_DSP_NUMSECURITY        2u
#define DCM_CFG_DSP_USE_ASYNCH_FNC              DCM_CFG_ON
#define DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER    DCM_CFG_OFF

#ifndef DCM_SEC_LEV_L1
#define DCM_SEC_LEV_L1        0x1
#endif

#ifndef DCM_SEC_LEV_L2
#define DCM_SEC_LEV_L2        0x2
#endif

#define DCM_CFG_DSP_SECA_ATTEMPT_COUNTER            DCM_CFG_OFF
#define DCM_CFG_DSP_SECA_STORESEED     DCM_CFG_OFF
#define DCM_CFG_DSP_DELAYTIMERMONITORING      DCM_PRV_REQUEST_SEED
#define DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT      DCM_CFG_ON
#define DCM_CFG_RAPIDPOWERSHUTDOWNRESET DCM_CFG_OFF
#define DCM_CFG_DSP_NUMRESETTYPE    3u
#define DCM_CFG_DSP_POWER_DOWN_TIME  255u
#define DCM_CFG_DSP_SUPPORTCDTCRECORD  DCM_CFG_OFF
#define DCM_CFG_RC_NUMRIDS  7u
#define DCM_CFG_DSP_NUMISRIDAVAIL          0
#define DCM_CFG_DSP_MODERULEFORROUTINES       DCM_CFG_OFF
#define DCM_CFG_RC_RANGE_NUMRIDS             0u
#define DCM_CFG_DSP_MODERULEFORRCRANGE       DCM_CFG_OFF
#define DCM_CFG_DSP_NVRAM_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_NUMISDIDAVAIL                         0u
#define DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED                           DCM_CFG_ON
#define DCM_CFG_DSP_READ_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_UINT8_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_SINT8_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_UINT16_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_SINT16_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_UINT32_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_SINT32_SR_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSP_READ_VARIABLE_LENGTH       DCM_CFG_OFF
#define DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH       DCM_CFG_OFF
#define DCM_CFG_DSP_WRITE_FIXED_LENGTH       DCM_CFG_ON
#define DCM_CFG_DSP_WRITE_VARIABLE_LENGTH       DCM_CFG_OFF
#define DCM_CFG_DSP_MODERULEFORDIDREAD       DCM_CFG_OFF
#define DCM_CFG_DSP_MODERULEFORDIDWRITE      DCM_CFG_OFF
#define DCM_CFG_DSP_MODERULEFORDIDCONTROL    DCM_CFG_OFF
#define DCM_CFG_MAXDIDTOREAD           4u
#define DCM_CFG_READDATALENGTH_BITS    DCM_CFG_OFF
#define DCM_CFG_DSP_DIDBUFFER         DCM_RAM_BUFFER
#define DCM_CFG_DIDRANGE_EXTENSION  DCM_CFG_OFF
#define DCM_CFG_NUMOFDIDRANGES 0x0
#define DCM_CFG_DIDSUPPORT DCM_CFG_ON
#define DCM_CFG_DSP_ROEDID_ENABLED       DCM_CFG_OFF
#define DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED       DCM_CFG_OFF
#define DCM_CFG_NUM_IOCBI_DIDS          0x0u
#define DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_RESETTODEFAULT_ENABLED        DCM_CFG_OFF
#define DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED   DCM_CFG_OFF
#define DCM_CFG_DSP_IOCBI_SR_ENABLED   DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED     DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROL_FIXED_LEN_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROL_VAR_LEN_ENABLED    DCM_CFG_OFF
#define DCM_CFG_LIMITRDBIRESPTOBUFSIZE      DCM_CFG_OFF
#define DCM_CFG_RDBIPAGEDBUFFERSUPPORT      DCM_CFG_OFF
#define DCM_CFG_RDTCPAGEDBUFFERSUPPORT      DCM_CFG_OFF
#define DCM_CFG_RDBIREQUESTBUFFERSIZE       8u
#define DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED      DCM_CFG_ON
#define DCM_CFG_DSP_MODERULEFORREADMEMORY       DCM_CFG_OFF
#define DCM_CFG_DSP_MODERULEFORWRITEMEMORY       DCM_CFG_OFF
#define DCM_CFG_DSP_REQUESTDOWNLOAD_SEQUENCECHECK_ENABLED     DCM_CFG_ON
#define DCM_CFG_DSP_FLEXIBLEDATA_ENABLED     DCM_CFG_ON
#define DCM_CFG_NUM_SPECIFIC_SUBNETS                    0x00
#define DCM_CFG_NUM_ALLCHANNELS_MODE_INFO                   1
#define DCM_CFG_DSP_MODERULEFORCC                   DCM_CFG_OFF
#define DCM_CFG_DSP_BSWMDCM_ENABLED    DCM_CFG_OFF
#define DCM_CFG_DSP_CDTCMODECHECK       DCM_CFG_ON
#define DCM_CFG_VIN_SUPPORTED                           DCM_CFG_ON
#define DCM_CFG_VIN_DID                                 0xF190
#define DCM_CFG_STARTSUPPORTED                         DCM_CFG_ON
#define DCM_CFG_STOPSUPPORTED                         DCM_CFG_ON
#define DCM_CFG_REQRESULTSSUPPORTED                         DCM_CFG_ON
#define DCM_CFG_ROUTINEVARLENGTH                         DCM_CFG_OFF
#define DCM_CFG_ROUTINEARRAY_INSIG                   DCM_CFG_ON
#define DCM_CFG_ROUTINEARRAY_OUTSIG                   DCM_CFG_OFF
#define DCM_CFG_RCRANGE_STARTSUPPORTED                         DCM_CFG_ON
#define DCM_CFG_RCRANGE_STOPSUPPORTED                           DCM_CFG_ON
#define DCM_CFG_RCRANGE_REQRESULTSSUPPORTED                         DCM_CFG_ON
#define DCM_CFG_RCRANGE_ROUTINEVARLENGTH                         DCM_CFG_ON
#define DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG                   DCM_CFG_OFF
#define DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG                   DCM_CFG_OFF

#ifndef     DCM_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED
#define DCM_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED    DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED
#endif

#ifndef     DCM_DSP_ECURESET_ENABLED
#define DCM_DSP_ECURESET_ENABLED                    DCM_CFG_DSP_ECURESET_ENABLED
#endif

#ifndef     DCM_DSP_SECURITYACCESS_ENABLED
#define DCM_DSP_SECURITYACCESS_ENABLED              DCM_CFG_DSP_SECURITYACCESS_ENABLED
#endif

#ifndef     DCM_DSP_TESTERPRESENT_ENABLED
#define DCM_DSP_TESTERPRESENT_ENABLED               DCM_CFG_DSP_TESTERPRESENT_ENABLED
#endif

#ifndef     DCM_DSP_TESTERPRESENTSB_ENABLED
#define DCM_DSP_TESTERPRESENTSB_ENABLED             DCM_CFG_DSP_TESTERPRESENTSB_ENABLED
#endif

#ifndef     DCM_DSP_CONTROLDTCSETTING_ENABLED
#define DCM_DSP_CONTROLDTCSETTING_ENABLED           DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED
#endif

#ifndef     DCM_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED
#define DCM_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED  DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED
#endif

#ifndef     DCM_DSP_ROUTINECONTROL_ENABLED
#define DCM_DSP_ROUTINECONTROL_ENABLED              DCM_CFG_DSP_ROUTINECONTROL_ENABLED
#endif

#ifndef     DCM_DSP_IOCBI_ENABLED
#define DCM_DSP_IOCBI_ENABLED                       DCM_CFG_DSP_IOCBI_ENABLED
#endif

#ifndef     DCM_DSP_READDATABYIDENTIFIER_ENABLED
#define DCM_DSP_READDATABYIDENTIFIER_ENABLED        DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED
#endif

#ifndef     DCM_DSP_WRITEDATABYIDENTIFIER_ENABLED
#define DCM_DSP_WRITEDATABYIDENTIFIER_ENABLED       DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED
#endif

#ifndef     DCM_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED
#define DCM_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED   DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED
#endif

#ifndef     DCM_DSP_COMMUNICATIONCONTROL_ENABLED
#define DCM_DSP_COMMUNICATIONCONTROL_ENABLED        DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED
#endif

#ifndef     DCM_DSP_RESPONSEONEVENT_ENABLED
#define DCM_DSP_RESPONSEONEVENT_ENABLED             DCM_CFG_DSP_RESPONSEONEVENT_ENABLED
#endif

#ifndef     DCM_DSP_READMEMORYBYADDRESS_ENABLED
#define DCM_DSP_READMEMORYBYADDRESS_ENABLED         DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED
#endif

#ifndef     DCM_DSP_WRITEMEMORYBYADDRESS_ENABLED
#define DCM_DSP_WRITEMEMORYBYADDRESS_ENABLED        DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED
#endif

#ifndef     DCM_DSP_READDATABYPERIODICIDENTIFIER_ENABLED
#define DCM_DSP_READDATABYPERIODICIDENTIFIER_ENABLED  DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED
#endif

#ifndef     DCM_DSP_READDTCINFORMATION_ENABLED
#define DCM_DSP_READDTCINFORMATION_ENABLED          DCM_CFG_DSP_READDTCINFORMATION_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x01_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x01_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x02_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x02_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x03_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x03_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x04_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x04_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x06_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x06_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x07_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x07_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x08_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x08_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x09_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x09_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x0A_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x0A_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x0F_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x0F_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x10_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x10_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x11_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x11_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x12_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x12_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x13_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x13_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x14_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x14_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x15_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x15_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x17_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x17_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x18_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x18_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED
#endif

#ifndef     DCM_DSP_RDTCSUBFUNC_0x19_ENABLED
#define DCM_DSP_RDTCSUBFUNC_0x19_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED
#endif

#ifndef     DCM_NUMRDTCSUBFUNC
#define DCM_NUMRDTCSUBFUNC                          DCM_CFG_NUMRDTCSUBFUNC
#endif

#ifndef     DCM_RDTC_MAXNUMDTCREAD
#define DCM_RDTC_MAXNUMDTCREAD                      DCM_CFG_RDTC_MAXNUMDTCREAD
#endif

#ifndef     DCM_RDTC_MAXNUMRECREAD
#define DCM_RDTC_MAXNUMRECREAD                      DCM_CFG_RDTC_MAXNUMRECREAD
#endif

#ifndef     DCM_DSP_NUMSESSIONS
#define DCM_DSP_NUMSESSIONS                         DCM_CFG_DSP_NUMSESSIONS
#endif

#ifndef     DCM_DSP_DSC_SESRECINRESP
#define DCM_DSP_DSC_SESRECINRESP                    DCM_CFG_DSP_DSC_SESRECINRESP
#endif

#ifndef     DCM_DSP_NUMSECURITY
#define DCM_DSP_NUMSECURITY                         DCM_CFG_DSP_NUMSECURITY
#endif

#ifndef     DCM_SECA_MAXSEEDSIZE
#define DCM_SECA_MAXSEEDSIZE                        DCM_CFG_SECA_MAXSEEDSIZE
#endif

#ifndef     DCM_DSP_SECA_STORESEED
#define DCM_DSP_SECA_STORESEED                      DCM_CFG_DSP_SECA_STORESEED
#endif

#ifndef     DCM_DSP_DELAYTIMERMONITORING
#define DCM_DSP_DELAYTIMERMONITORING                DCM_CFG_DSP_DELAYTIMERMONITORING
#endif

#ifndef     DCM_DSP_NRC0x36_MAXDELAYCOUNT
#define DCM_DSP_NRC0x36_MAXDELAYCOUNT               DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT
#endif

#ifndef     DCM_DSP_NUMRESETTYPE
#define DCM_DSP_NUMRESETTYPE                        DCM_CFG_DSP_NUMRESETTYPE
#endif

#ifndef     DCM_DSP_POWER_DOWN_TIME
#define DCM_DSP_POWER_DOWN_TIME                     DCM_CFG_DSP_POWER_DOWN_TIME
#endif

#ifndef     DCM_DSP_CDTCRECORD_LENGTH
#define DCM_DSP_CDTCRECORD_LENGTH                   DCM_CFG_DSP_CDTCRECORDLENGTH
#endif

#ifndef     DCM_RC_NUM_RIDS
#define DCM_RC_NUM_RIDS                             DCM_CFG_RC_NUMRIDS
#endif

#ifndef     DCM_RC_RANGE_NUMRIDS
#define DCM_RC_RANGE_NUMRIDS                             DCM_CFG_RC_RANGE_NUMRIDS
#endif

#ifndef     DCM_DSP_NVRAM_ENABLED
#define DCM_DSP_NVRAM_ENABLED                       DCM_CFG_DSP_NVRAM_ENABLED
#endif

#ifndef     DCM_MAXDIDTOREAD
#define DCM_MAXDIDTOREAD                            DCM_CFG_MAXDIDTOREAD
#endif

#ifndef     DCM_LONGEST_SINGLE_DID
#define DCM_LONGEST_SINGLE_DID                      DCM_CFG_LONGESTSINGLEDID
#endif

#ifndef     DCM_DSP_DID_BUFFER
#define DCM_DSP_DID_BUFFER                          DCM_CFG_DSP_DIDBUFFER
#endif

#ifndef     DID_RANGE_EXTENSION
#define DID_RANGE_EXTENSION                         DCM_CFG_DIDRANGE_EXTENSION
#endif

#ifndef     DCM_NO_OF_DIDRANGES
#define DCM_NO_OF_DIDRANGES                         DCM_CFG_NUMOFDIDRANGES
#endif

#ifndef     DID_SUPPORT
#define DID_SUPPORT                                 DCM_CFG_DIDSUPPORT
#endif

#ifndef     DCM_ROE_WINTIMEINREPEVENTSREQ
#define DCM_ROE_WINTIMEINREPEVENTSREQ               DCM_CFG_ROE_WINTIMEINREPEVENTSREQ
#endif

#ifndef     DCM_NUM_SPECIFIC_SUBNETS
#define DCM_NUM_SPECIFIC_SUBNETS                    DCM_CFG_NUM_SPECIFIC_SUBNETS
#endif

#ifndef     DCM_NUM_ALLCHANNELS_MODE_INFO
#define DCM_NUM_ALLCHANNELS_MODE_INFO               DCM_CFG_NUM_ALLCHANNELS_MODE_INFO
#endif

#ifndef     DCM_DSP_CDTC_MODE_CHECK
#define DCM_DSP_CDTC_MODE_CHECK                     DCM_CFG_DSP_CDTCMODECHECK
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

