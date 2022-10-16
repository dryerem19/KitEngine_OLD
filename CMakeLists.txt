cmake_minimum_required(VERSION 3.23)
project(KitEngine)

set(CMAKE_CXX_STANDARD 20)

# Disable generate docs, tests and example files GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(KitEngine main.cpp)

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

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)
add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/assimp")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
target_link_libraries(${PROJECT_NAME} assimp)