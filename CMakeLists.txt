cmake_minimum_required(VERSION 3.24)

if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(UNIX)
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif(WIN32)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_HOME_DIRECTORY}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
set(CMAKE_CXX_STANDARD 20)

project(LevelEditor)

file(GLOB_RECURSE LEVEL_EDITOR_HEADERS "LevelEditor/src/*.h")
file(GLOB_RECURSE LEVEL_EDITOR_SOURCE  "LevelEditor/src/*.cpp")

add_executable(${PROJECT_NAME} ${LEVEL_EDITOR_HEADERS} ${LEVEL_EDITOR_SOURCE})

# Подлкючаем библиотеку KitEngine
target_include_directories(${PROJECT_NAME} PUBLIC KitEngine/include)
target_link_libraries(${PROJECT_NAME} PRIVATE KitEngine)

find_package(imgui CONFIG REQUIRED)
if (imgui_FOUND)
    message(STATUS "Imgui library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
endif()

find_package(imguizmo CONFIG REQUIRED)
if (imguizmo_FOUND)
    message(STATUS "Imguizmo library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE imguizmo::imguizmo)
endif()

add_subdirectory(KitEngine)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/build/Windows-x64/Debug/KitEngine/Debug"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()