cmake_minimum_required(VERSION 3.24)

if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(UNIX)
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif(WIN32)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
project(KitEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE KIT_ENGINE_HEADERS "src/*.h")
file(GLOB_RECURSE KIT_ENGINE_SOURCE  "src/*.cpp")

add_executable(${PROJECT_NAME} "src/main.cpp" "src/Window.cpp" "src/Window.h")

find_package(GLEW CONFIG REQUIRED)
if (GLEW_FOUND)
    message(STATUS "Glew library found!")
    target_link_libraries( ${PROJECT_NAME} PRIVATE GLEW::GLEW)
endif()

find_package(glfw3 CONFIG REQUIRED)
if (glfw3_FOUND)
    message(STATUS "Glf3 library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()

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

find_package(EnTT CONFIG REQUIRED)
if (EnTT_FOUND)
    message(STATUS "EnTT library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)
endif()

find_package(Bullet CONFIG REQUIRED)
if (Bullet_FOUND)
    message(STATUS "Bullet library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE LinearMath Bullet3Common BulletDynamics BulletSoftBody)
endif()

find_package(assimp CONFIG REQUIRED)
if (assimp_FOUND)
    message(STATUS "Assimp library found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
endif()
