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