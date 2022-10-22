cmake_minimum_required(VERSION 3.24)

project(KitEngine)

file(GLOB_RECURSE KIT_ENGINE_HEADERS "include/*.h")
file(GLOB_RECURSE KIT_ENGINE_SOURCE  "src/*.cpp")

set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
        PRIVATE ${KIT_ENGINE_SOURCE})
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

find_package(GLEW CONFIG REQUIRED)
if (GLEW_FOUND)
    message(STATUS "Glew library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
else()
    message(FATAL_ERROR "Glew library not found!")
endif()

find_package(glfw3 CONFIG REQUIRED)
if (glfw3_FOUND)
    message(STATUS "Glf3 library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
else()
    message(FATAL_ERROR "Glfw3 library not found!")
endif()

find_package(EnTT CONFIG REQUIRED)
if (EnTT_FOUND)
    message(STATUS "EnTT library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC EnTT::EnTT)
else()
    message(FATAL_ERROR "EnTT library not found!")
endif()

find_package(Bullet CONFIG REQUIRED)
if (Bullet_FOUND)
    message(STATUS "Bullet library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC LinearMath Bullet3Common BulletDynamics BulletSoftBody)
else()
    message(FATAL_ERROR "Bullet library not found!")
endif()

find_package(assimp CONFIG REQUIRED)
if (assimp_FOUND)
    message(STATUS "Assimp library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp)
else()
    message(FATAL_ERROR "Assimp library not found!")
endif()

find_package(glm CONFIG REQUIRED)
if (glm_FOUND)
    message(STATUS "glm library found!")
    target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
else()
    message(FATAL_ERROR "glm library not found!")
endif()

# Custom commands