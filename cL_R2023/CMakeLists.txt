cmake_minimum_required(VERSION 3.25.3)

project(
   pRealEcu_R2023
   VERSION 0.1
)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(
   -g
   -std=c2x
   -Wall
   -Werror
   -Wextra
   -pedantic
   -Wuninitialized
)

add_executable(
   pRealEcu_R2023

   ${PROJECT_SOURCE_DIR}/source/ProjectCfg/CfgMcalAdc.c
   ${PROJECT_SOURCE_DIR}/source/ProjectCfg/CfgMcalDio.c
   ${PROJECT_SOURCE_DIR}/source/SwcServiceStartUp/SwcServiceStartUp.c
   ${PROJECT_SOURCE_DIR}/source/McalAdc/McalAdc.c
   ${PROJECT_SOURCE_DIR}/source/McalDio/McalDio.c
   ${PROJECT_SOURCE_DIR}/source/McalMcu/McalMcu.c
   ${PROJECT_SOURCE_DIR}/source/McalWdg/McalWdg.c
   ${PROJECT_SOURCE_DIR}/source/wrappers/wrappers.c
)

target_include_directories(
   pRealEcu_R2023 PUBLIC
   "${PROJECT_SOURCE_DIR}/source/common"
   "${PROJECT_SOURCE_DIR}/source/ProjectCompiler"
   "${PROJECT_SOURCE_DIR}/source/ProjectCfg"
   "${PROJECT_SOURCE_DIR}/source/SwcServiceEcuM"
   "${PROJECT_SOURCE_DIR}/source/SwcServiceNvM"
   "${PROJECT_SOURCE_DIR}/source/SwcServiceOs"
   "${PROJECT_SOURCE_DIR}/source/SwcServiceStartUp"
   "${PROJECT_SOURCE_DIR}/source/McalAdc"
   "${PROJECT_SOURCE_DIR}/source/McalDio"
   "${PROJECT_SOURCE_DIR}/source/McalGpt"
   "${PROJECT_SOURCE_DIR}/source/McalMcu"
   "${PROJECT_SOURCE_DIR}/source/McalWdg"
   "${PROJECT_SOURCE_DIR}/source/wrappers"
)

