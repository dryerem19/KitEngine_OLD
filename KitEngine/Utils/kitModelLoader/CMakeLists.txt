cmake_minimum_required(VERSION 3.24)
project(kitModelLoader VERSION 1.0.0 DESCRIPTION "Assimp-based model loader")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES_FILES  "src/*.cpp")

#-------------------------------------------------------------------------------------
#   CREATE DYNAMIC LINK LIBRARY
#-------------------------------------------------------------------------------------
add_library(${PROJECT_NAME} SHARED ${SOURCES_FILES} include/pch.h)
target_include_directories(${PROJECT_NAME} PRIVATE include)

#-------------------------------------------------------------------------------------
#   LINK ASSIMP
#-------------------------------------------------------------------------------------
find_package(assimp CONFIG REQUIRED)
if (assimp_FOUND)
    message(STATUS "${PROJECT_NAME} - Assimp library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp)
else()
    message(FATAL_ERROR "${PROJECT_NAME} - Assimp library not found!")
endif()

#-------------------------------------------------------------------------------------
#   USE PRECOMPILE HEADERS
#-------------------------------------------------------------------------------------
target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        "include/pch.h"
)