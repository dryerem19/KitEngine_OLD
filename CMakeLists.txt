cmake_minimum_required(VERSION 3.23)
project(KitEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(KitEngine main.cpp)

# Include header files
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/include")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/include")
target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")

find_library(ASSIMP_LIBRARY NAMES libassimpd libassimpd.a)
if (NOT ASSIMP_LIBRARY)
    message("[WARNING] - Assimp library not found! Compiling...")

    # Set config
    set(ZLIB_LIBRARIES zlibstatic)
    set(ENABLE_BOOST_WORKAROUND ON)
    set(BUILD_STATIC_LIB ON)
    set(BUILD_ASSIMP_TOOLS  OFF)
    set(ASSIMP_BUILD_STATIC_LIB ON)

    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/assimp")
    target_include_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/assimp/include")
    target_link_libraries(${PROJECT_NAME} assimp)
else()
    message(STATUS "Assimp library found!")
    target_include_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_BINARY_DIR}/3rdparty/assimp/include")
    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
endif()

# GLEW LINKING
find_library(GLEW_LIBRARY glew)
if (NOT GLEW_LIBRARY)
    message("[WARNING] - Glew library not found! Compiling...")

    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/build/cmake")
    target_include_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/include")
    target_link_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glew-2.2.0/src")
    target_link_libraries(${PROJECT_NAME} glew)
else()
    message(STATUS "Glew library found!")
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
endif()

# GLFW LINKING
find_library(GLFW_LIBRARY glfw)
if (NOT GLFW_LIBRARY)
    message("[WARNING] - Glfw library not found! Compiling...")

    # Disable generate docs, tests and example files GLFW
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/glfw")
    target_include_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/include")
    target_link_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/glfw/src")
    target_link_libraries(${PROJECT_NAME} glfw)
else()
    message(STATUS "Glfw library found!")
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
endif()

# IMGUI LINKING
find_library(IMGUI_LIBRARY_FIND NAMES dfd
        PATHS "${PROJECT_BINARY_DIR}")
if (NOT IMGUI_LIBRARY_FIND)
    message("[WARNING] - Imgui library not found! Compiling...")

    add_library(imgui STATIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui/imgui.cpp")
    target_include_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
    target_link_directories(${PROJECT_NAME}
            PUBLIC "${PROJECT_SOURCE_DIR}/3rdparty/imgui")
    target_link_libraries(${PROJECT_NAME} imgui)
else()
    message(STATUS "Imgui library found!")
    target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARY_FIND})
endif()