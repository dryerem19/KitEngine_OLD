project(Game)

set(SRC_FILES "source/main.cpp")
source_group(SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Source/Engine/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)