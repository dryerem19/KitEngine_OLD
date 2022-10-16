cmake_minimum_required(VERSION 3.23)
project(KitEngine)

set(CMAKE_CXX_STANDARD 20)

set(imgui_dir "${PROJECT_SOURCE_DIR}/3rdparty/imgui")

# ImGui linking
#file(GLOB imgui_header "${imgui_dir}/*.h")

#file(GLOB imgui_source "${imgui_dir}/*.h")

add_library(imgui_lib STATIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui/imgui.cpp")

#[[set(imgui_h "${PROJECT_SOURCE_DIR}/3rdparty/imgui/*.h")
set(imgui_cpp "${PROJECT_SOURCE_DIR}/3rdparty/imgui/*.cpp")]]



# Disable generate docs, tests and example files GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(KitEngine main.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
target_link_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
target_link_libraries(${PROJECT_NAME} imgui_lib)


#[[target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
target_link_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
target_link_libraries(${PROJECT_NAME} imgui)]]

# GLEW linking
add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/build/cmake")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/include")
target_link_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/src")
target_link_libraries(${PROJECT_NAME} glew)

# GLFW linking
 add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glfw")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/include")
target_link_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/src")
target_link_libraries(${PROJECT_NAME} glfw)

# Assimp linking
#[[set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)
add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/assimp")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
target_link_libraries(${PROJECT_NAME} assimp)]]

