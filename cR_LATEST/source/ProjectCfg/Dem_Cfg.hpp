#ifndef DEM_CFG_H
#define DEM_CFG_H

#define DEM_CFG_OBD_OFF 	0
#define DEM_CFG_OBD_ON  	1
#define DEM_CFG_OBD        DEM_CFG_OBD_OFF
#define DEM_CFG_J1939DCM_OFF     0
#define DEM_CFG_J1939DCM_ON      1
#define DEM_CFG_J1939DCM       DEM_CFG_J1939DCM_OFF
#define DEM_CFG_J1939DCM_CLEAR_SUPPORT                     DEM_CFG_J1939DCM_OFF
#define DEM_CFG_J1939DCM_READ_DTC_SUPPORT    		   FALSE
#define DEM_CFG_J1939DCM_DM31_SUPPORT        FALSE
#define DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT               FALSE
#define DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT      FALSE

#ifndef DEM_BFM_ON
#define DEM_BFM_ON TRUE
#endif

#ifndef DEM_BFM_OFF
#define DEM_BFM_OFF FALSE
#endif

#ifndef DEM_CATPRIO_ON
#define DEM_CATPRIO_ON   1
#endif
#ifndef DEM_CATPRIO_OFF
#define DEM_CATPRIO_OFF  0
#endif

#define DEM_BFM_ENABLED  DEM_BFM_OFF
#define DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED            FALSE
#define DEM_CFG_SUSPICIOUS_SUPPORT                        FALSE
#define DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME    TRUE
#define DEM_CFG_EVMEMGENERIC_SUPPORTED                    TRUE
#define DEM_CFG_VERSION_INFO_API_OFF          STD_OFF
#define DEM_CFG_VERSION_INFO_API_ON           STD_ON
#define DEM_CFG_VERSION_INFO_API              DEM_CFG_VERSION_INFO_API_OFF
#define DEM_CFG_ALTERNATIVEDTC_OFF                   STD_OFF
#define DEM_CFG_ALTERNATIVEDTC_ON                    STD_ON
#define DEM_CFG_ALTERNATIVEDTC  DEM_CFG_ALTERNATIVEDTC_OFF
#define DEM_CFG_ERASE_ALL_OFF                           0u
#define DEM_CFG_ERASE_ALL_WITHOUT_HASHID_CHECK          1u
#define DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK             2u
#define DEM_CFG_ERASE_ALL_DATA_SUPPORTED                DEM_CFG_ERASE_ALL_OFF
#define DEM_CFG_DEPENDENCY_OFF         STD_OFF
#define DEM_CFG_DEPENDENCY_ON          STD_ON
#define DEM_CFG_DEPENDENCY             DEM_CFG_DEPENDENCY_OFF
#define DEM_CFG_TESTMODE_SUPPORT_ON       STD_ON
#define DEM_CFG_TESTMODE_SUPPORT_OFF      STD_OFF
#define DEM_CFG_TESTMODE_SUPPORT          DEM_CFG_TESTMODE_SUPPORT_OFF
#define DEM_CFG_CHECKAPICONSISTENCY    TRUE
#define DEM_CFG_DEBUGDATA_OFF     0
#define DEM_CFG_DEBUGDATA_8BIT    (0+1)
#define DEM_CFG_DEBUGDATA_32BIT   (0+4)
#define DEM_CFG_DEBUGDATA         DEM_CFG_DEBUGDATA_32BIT

#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
#define DEM_DEBUGDATA_PARAM(A,B)    ,A,B
#else
#define DEM_DEBUGDATA_PARAM(A,B)
#endif

#endif

