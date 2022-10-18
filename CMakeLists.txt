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

#file(GLOB IMGUI_HEADERS "3rdparty/imgui/*.h")
#file(GLOB IMGUI_SOURCE "3rdparty/imgui/*.cpp")
#
#file(GLOB IMGUI BACKEND_HEADERS "3rdparty/imgui/backends/imgui_impl_glfw.h"
#        "3rdparty/imgui/backends/imgui_impl_opengl3.h")
#file(GLOB IMGUI BACKEND_SOURCE "3rdparty/imgui/backends/imgui_impl_glfw.cpp"
#        "3rdparty/imgui/backends/imgui_impl_opengl3.cpp")

# stb does not have a CMake build, but is header-only
#find_path(STB_INCLUDE_DIRS "stb.h")

add_executable(${PROJECT_NAME} "src/main.cpp" "src/Window.cpp" "src/Window.h")

#target_include_directories(KitEngine PUBLIC "3rdparty/imgui")

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

#list(APPEND CMAKE_PREFIX_PATH "vcpkg/packages/imgui_x64-windows")
find_package(imgui CONFIG REQUIRED)
if (imgui_FOUND)
    #include_directories(${imgui_INCLUDE_DIRS})
    #target_link_libraries(${PROJECT_NAME} PRIVATE ${imgui_LIBS})
    target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
    message(STATUS "imgui library found!")
endif()

#find_library(imgui_lib imgui)
#include_directories(${imgui_lib_INCLUDE_DIRS})
#target_link_libraries(KitEngine ${imgui_lib_LIBRARIES})

#target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
#target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/packages/imguizmo_x64-windows")
#find_package(imguizmo CONFIG REQUIRED)
#if (imguizmo_FOUND)
#    message(STATUS "Imguizmo library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE imguizmo::imguizmo)
#endif()
#
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/packages/entt_x64-windows")
#find_package(EnTT CONFIG REQUIRED)
#if (EnTT_FOUND)
#    message(STATUS "EnTT library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)
#endif()
#
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/packages/bullet3_x64-windows")
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/packages/pugixml_x64-windows")
#find_package(Bullet CONFIG REQUIRED)
#if (Bullet_FOUND)
#    message(STATUS "Bullet library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE LinearMath Bullet3Common BulletDynamics BulletSoftBody)
#endif()
#
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/packages/assimp_x64-windows")
#find_package(assimp CONFIG REQUIRED)
#if (assimp_FOUND)
#    message(STATUS "Assimp library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
#endif()

# IMGUI SOURCE FILES
#set(3RDPARTY_PATH "${PROJECT_SOURCE_DIR}/3rdparty")
#
#set(IMGUI_PATH "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
#file(GLOB IMGUI_CPP "${IMGUI_PATH}/*.cpp")
#file(GLOB IMGUI_BACKEND_CPP "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
#        "${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp")

#file(GLOB IMGUIZMO_CPP "${3RDPARTY_PATH}/imguizmo/*.cpp")

#target_precompile_headers(${PROJECT_NAME} PRIVATE
#        src/pch/pch.h)

## Include header files
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/include")
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/include")
#
## Include Imgui headers
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui/backends")
#
## Include ImGuizmo headers
#target_include_directories(${PROJECT_NAME}
#        PUBLIC "${3RDPARTY_PATH}/imguizmo")
#
#find_library(ASSIMP_LIBRARY NAMES libassimpd libassimpd.a)
#if (NOT ASSIMP_LIBRARY)
#    message("[WARNING] - Assimp library not found! Compiling...")
#
#    # Set config
#    set(ZLIB_LIBRARIES zlibstatic)
#    set(ENABLE_BOOST_WORKAROUND ON)
#    set(BUILD_STATIC_LIB ON)
#    set(BUILD_ASSIMP_TOOLS  OFF)
#    set(ASSIMP_BUILD_STATIC_LIB ON)
#
#    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/assimp")
#    target_include_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
#    target_link_libraries(${PROJECT_NAME} assimp)
#else()
#    message(STATUS "Assimp library found!")
#    target_include_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_BINARY_DIR}/3rdparty/assimp/include")
#    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
#endif()
#
## GLEW LINKING
#find_library(GLEW_LIBRARY glew)
#if (NOT GLEW_LIBRARY)
#    message("[WARNING] - Glew library not found! Compiling...")
#
#    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/build/cmake")
#    target_include_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/include")
#    target_link_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/src")
#    target_link_libraries(${PROJECT_NAME} glew)
#else()
#    message(STATUS "Glew library found!")
#    find_package(OpenGL REQUIRED)
#    include_directories(${OPENGL_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
#endif()
#
## GLFW LINKING
#find_library(GLFW_LIBRARY glfw)
#if (NOT GLFW_LIBRARY)
#    message("[WARNING] - Glfw library not found! Compiling...")
#
#    # Disable generate docs, tests and example files GLFW
#    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#
#    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glfw")
#    target_include_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/include")
#    target_link_directories(${PROJECT_NAME}
#            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/src")
#    target_link_libraries(${PROJECT_NAME} glfw)
#else()
#    message(STATUS "Glfw library found!")
#    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
#endif()