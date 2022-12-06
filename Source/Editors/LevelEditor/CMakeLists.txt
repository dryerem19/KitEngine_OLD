project(LevelEditor VERSION 1.0.0 DESCRIPTION "Level Editor for KitEngine SDK")

file(GLOB_RECURSE LOCAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE LOCAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(SRC_FILES ${LOCAL_INCLUDE} ${LOCAL_SOURCES})
source_group(SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Core)

find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        imgui::imgui
        imguizmo::imguizmo
)

target_link_libraries(${PROJECT_NAME} PUBLIC ImGuiFileDialog)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Source/Core/include
        
        ${CMAKE_SOURCE_DIR}/Source/External/ImGuiFileDialog)
