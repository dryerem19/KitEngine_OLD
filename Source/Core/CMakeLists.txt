project(Core)

file(GLOB_RECURSE INCLUDE "include/*.h")
file(GLOB_RECURSE SOURCE "source/*.cpp")
set(SRC_FILES ${INCLUDE} ${SOURCE})
source_group(SRC_FILES)

# if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#   # using Clang
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   # using GCC
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
#   # using Intel C++
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE MSVC)
# endif()

#add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Sail CONFIG REQUIRED)
find_package(SailC++ CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

# For play sound files
find_package(OpenAL CONFIG REQUIRED)

# For read/write sound files
find_package(SndFile CONFIG REQUIRED)

# For support lua scripting
find_package(Lua REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})
find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/Array.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${LUABRIDGE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        GLEW::GLEW
        glfw
        EnTT::EnTT
        BulletSoftBody BulletDynamics BulletCollision Bullet3Common LinearMath
        glm::glm
        SAIL::sail
        SAIL::sail-c++
        spdlog::spdlog spdlog::spdlog_header_only
        yaml-cpp
        EnTT::EnTT
        assimp::assimp
        OpenAL::OpenAL
        SndFile::sndfile
)

target_precompile_headers(${PROJECT_NAME} PUBLIC "include/pch.h")