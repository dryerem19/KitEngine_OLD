project(ModelLoader VERSION 1.0.0 DESCRIPTION "Assimp based model loader")

file(GLOB_RECURSE INCLUDE "include/*.h")
file(GLOB_RECURSE SOURCE "source/*.cpp")
set(SRC_FILES ${INCLUDE} ${SOURCE})
source_group(SRC_FILES)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        assimp::assimp
)