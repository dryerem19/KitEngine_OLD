project(Game)

file(GLOB_RECURSE LOCAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE LOCAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(SRC_FILES ${LOCAL_INCLUDE} ${LOCAL_SOURCES})
source_group(SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Source/Core/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Core)