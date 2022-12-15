cmake_minimum_required(VERSION 3.24)
project(KitEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake
            CACHE STRING "Vcpkg toolchain file")
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(UNIX)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
            CACHE STRING "Vcpkg toolchain file")
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif()


# Output all libraries and executable to one folder
set(COMPILE_OUTPUT_FOLDER ${CMAKE_SOURCE_DIR}/bin/${ARCH_TYPE}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${COMPILE_OUTPUT_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${COMPILE_OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${COMPILE_OUTPUT_FOLDER})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${COMPILE_OUTPUT_FOLDER})
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${COMPILE_OUTPUT_FOLDER})


add_subdirectory(Source)
add_subdirectory(Resources)

#add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

#target_include_directories(LevelEditor PUBLIC KitEngine/include)
#target_link_libraries(LevelEditor PRIVATE KitEngine kitModelLoader LevelEditor)




#set(CMAKE_CXX_STANDARD 20)


#
#
#file(GLOB_RECURSE LEVEL_EDITOR_HEADERS "${CMAKE_SOURCE_DIR}/LevelEditor/*.h")
#file(GLOB_RECURSE LEVEL_EDITOR_SOURCE  "${CMAKE_SOURCE_DIR}/LevelEditor/src/*.cpp")
#
#
#add_executable(${PROJECT_NAME} ${LEVEL_EDITOR_HEADERS} ${LEVEL_EDITOR_SOURCE})
#target_include_directories(${PROJECT_NAME} PUBLIC LevelEditor/include)
#
## Подлкючаем библиотеку KitEngine
#target_include_directories(${PROJECT_NAME} PUBLIC KitEngine/include)
#target_link_libraries(${PROJECT_NAME} PRIVATE KitEngine kitModelLoader)

#find_package(imgui CONFIG REQUIRED)
#if (imgui_FOUND)
#    message(STATUS "Imgui library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
#endif()
#
#find_package(imguizmo CONFIG REQUIRED)
#if (imguizmo_FOUND)
#    message(STATUS "Imguizmo library found!")
#    target_link_libraries(${PROJECT_NAME} PRIVATE imguizmo::imguizmo)
#endif()

#add_subdirectory(KitEngine)

# Custom commands

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E create_symlink
#        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

#---------------------------------------------------------------------------------
# Get the full path to the Python virtual environment interpreter from relative
#---------------------------------------------------------------------------------
#get_filename_component(PYTHON_VENV_EXECUTABLE
#        "${PROJECT_SOURCE_DIR}/python_venv/Scripts/python.exe" ABSOLUTE)

#---------------------------------------------------------------------------------
# Find the installed Python interpreter and fill in the variables
#---------------------------------------------------------------------------------
#set(PYTHON_VENV ${CMAKE_SOURCE_DIR}/venv)
#set(PYTHON_REQUIREMENTS ${CMAKE_SOURCE_DIR}/requirements.txt)
#find_package(Python3 REQUIRED COMPONENTS Interpreter)
#if(Python3_FOUND)
#    message(STATUS "Python3 interpreter found!")
#
#    if (WIN32)
#        message(STATUS "Python3 running on windows")
#        set(PYTHON_SCRIPTS_DIR ${PYTHON_VENV}/Scripts)
#        set(PYTHON_EXECUTABLE  ${PYTHON_SCRIPTS_DIR}/python.exe)
#    elseif(UNIX)
#        message(STATUS "Python3 running on unix")
#        set(PYTHON_SCRIPTS_DIR ${PYTHON_VENV}/bin)
#        set(PYTHON_EXECUTABLE  ${PYTHON_SCRIPTS_DIR}/python)
#    endif()
#
#elseif(NOT Python3_FOUND)
#    message(SEND_ERROR "Please, install python environment before run cmake build!")
#endif()

#---------------------------------------------------------------------------------
# This way the command creates a Python virtual environment and installs the
# dependencies
#---------------------------------------------------------------------------------
#add_custom_command(
#        OUTPUT  ${PYTHON_EXECUTABLE}
#        COMMAND ${Python3_EXECUTABLE} -m venv ${PYTHON_VENV}
#        COMMAND ${PYTHON_SCRIPTS_DIR}/pip install -r ${PYTHON_REQUIREMENTS}
#        DEPENDS ${PYTHON_REQUIREMENTS}
#)
#add_custom_target(venv DEPENDS ${PYTHON_EXECUTABLE})
#add_dependencies(${PROJECT_NAME} venv)

#---------------------------------------------------------------------------------
# This command runs a custom Python script after the build
#---------------------------------------------------------------------------------
#add_custom_command(
#        TARGET  ${PROJECT_NAME} PRE_BUILD
#        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/post_build.py
#        ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>
#        COMMENT "Run custom python script"
#)
#
#if(WIN32)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PROJECT_SOURCE_DIR}/build/Windows/Debug/KitEngine/Debug/KitEngine.dll"
#            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#endif()
