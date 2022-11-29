project(Core)

file(GLOB_RECURSE INCLUDE "include/*.h")
file(GLOB_RECURSE SOURCE "source/*.cpp")
set(SRC_FILES ${INCLUDE} ${SOURCE})
source_group(SRC_FILES)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
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

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        GLEW::GLEW
        glfw
        EnTT::EnTT
        LinearMath Bullet3Common BulletDynamics BulletSoftBody
        glm::glm
        SAIL::sail
        SAIL::sail-c++
        spdlog::spdlog spdlog::spdlog_header_only
        yaml-cpp
        EnTT::EnTT
        assimp::assimp
)

target_precompile_headers(${PROJECT_NAME} PUBLIC "include/pch.h")