project(Engine VERSION 1.0.0 DESCRIPTION "KitEngine SDK")

file(GLOB_RECURSE INCLUDE "include/*.h")
file(GLOB_RECURSE SOURCE "source/*.cpp")
set(SRC_FILES ${INCLUDE} ${SOURCE})
source_group(SRC_FILES)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

#find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
#find_package(glm CONFIG REQUIRED)
#find_package(SailC++ CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
        LINK_PUBLIC
        ModelLoader)
target_include_directories(${PROJECT_NAME} PRIVATE {CMAKE_SOURCE_DIR}/Source/Utils/ModelLoader/include)

target_link_libraries(${PROJECT_NAME}
        LINK_PUBLIC
        Render
)
target_include_directories(${PROJECT_NAME} PRIVATE {CMAKE_SOURCE_DIR}/Source/Render/include)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
#        GLEW::GLEW
        glfw
        EnTT::EnTT
        LinearMath Bullet3Common BulletDynamics BulletSoftBody
        imgui::imgui
        imguizmo::imguizmo
#        glm::glm
#        SAIL::sail-c++
        spdlog::spdlog spdlog::spdlog_header_only
)


find_package(unofficial-nativefiledialog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::nativefiledialog::nfd)