project(LevelEditor VERSION 1.0.0 DESCRIPTION "Level Editor for KitEngine SDK")

file(GLOB_RECURSE LOCAL_INCLUDE  ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE LOCAL_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(SRC_FILES ${LOCAL_INCLUDE} ${LOCAL_SOURCES})
source_group(SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Engine)

target_link_libraries(${PROJECT_NAME}
        LINK_PUBLIC
        ModelLoader)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Source/Engine/include
        ${CMAKE_SOURCE_DIR}/Source/Utils/ModelLoader/include)
