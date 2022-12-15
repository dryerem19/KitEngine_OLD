project(ImGuiFileDialog)

file(GLOB_RECURSE LOCAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE LOCAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(SRC_FILES ${LOCAL_INCLUDE} ${LOCAL_SOURCES})
source_group(SRC_FILES)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)