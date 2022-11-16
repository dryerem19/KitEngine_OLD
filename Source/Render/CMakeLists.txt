project(Render)

file(GLOB_RECURSE INCLUDE "include/*.h")
file(GLOB_RECURSE SOURCE  "source/*.cpp")
file(GLOB_RECURSE PCH_H   "pch/*.h")
file(GLOB_RECURSE PCH_CPP "pch/*.cpp")
set(SRC_FILES ${INCLUDE} ${SOURCE} ${PCH_H} ${PCH_CPP})
source_group(SRC_FILES)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_include_directories(${PROJECT_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/pch"
        )

find_package(GLEW CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        GLEW::GLEW
)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        assimp::assimp
)

find_package(SailC++ CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        SAIL::sail-c++
)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glm::glm
)

target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        "pch/RenderPch.h"
)