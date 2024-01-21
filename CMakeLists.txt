#
# @file       CMakeLists.txt
# @brief
# @date       2020-11-02
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

cmake_minimum_required(VERSION 3.10)
include(cmake/version.cmake)
project(
        Kerbal
        VERSION "${KERBAL_VERSION}"
        DESCRIPTION "Kerbal C++ Library"
        LANGUAGES CXX
)

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "CMAKE_CROSSCOMPILING: ${CMAKE_CROSSCOMPILING}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_PLATFORM_ID: ${CMAKE_CXX_PLATFORM_ID}")
message(STATUS "CMAKE_CXX_COMPILER_ARCHITECTURE_ID: ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

message(STATUS "KERBAL_VERSION: ${KERBAL_VERSION}")

set(KERBAL_CONFIGURE_ASSETS_DIR "${PROJECT_BINARY_DIR}/configure_assets")


include(cmake/modules.cmake)

# Kerbal Library Target
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
add_subdirectory(include)


# Build Header Integration
option(KERBAL_BUILD_HEADER_INTEGRATION "build header integration" OFF)
if (KERBAL_BUILD_HEADER_INTEGRATION)
    include(cmake/header_integration.cmake)
endif ()


# Build Script
option(KERBAL_BUILD_SCRIPT "build script" OFF)
if (KERBAL_BUILD_SCRIPT)
    add_subdirectory(script)
endif ()


# Build Test
option(KERBAL_BUILD_TEST "build test" OFF)
if (KERBAL_BUILD_TEST)
    add_subdirectory(test)
endif ()


# Pretty Printer
message(STATUS "Checking pretty printer module exist")

if (EXISTS ${PROJECT_SOURCE_DIR}/pretty_printer/CMakeLists.txt)
    message(STATUS "Checking pretty printer module exist -- YES")
    set(KERBAL_PRETTY_PRINTER_MODULE_EXIST True)
else ()
    message(STATUS "Checking pretty printer module exist -- NO")
    set(KERBAL_PRETTY_PRINTER_MODULE_EXIST False)
endif ()

option(KERBAL_INSTALL_PRETTY_PRINTER "install pretty printer" ${KERBAL_PRETTY_PRINTER_MODULE_EXIST})

if (KERBAL_INSTALL_PRETTY_PRINTER)
    if (NOT KERBAL_PRETTY_PRINTER_MODULE_EXIST)
        message(FATAL_ERROR "You haven't download pretty_printer submodule")
    endif ()
    add_subdirectory(pretty_printer)
endif ()


# Installation & Packing
include(cmake/gnuInstall.cmake)
include(cmake/cpack.cmake)


cmake_policy(SET CMP0155 NEW) # Scanning for imports



add_executable(use_module use_module.cpp)

#foreach (module_source_file ${Kerbal_PUBLIC_HEADERS_RELATIVE_kerbal})
foreach (module_source_file "kerbal/utility/forward.hpp")
    string(REGEX MATCH "(.*)\.hpp" _ "${module_source_file}")
    set(module_name "${CMAKE_MATCH_1}")
    string(REPLACE "/" "_" module_name "${module_name}")
#    message(STATUS ${module_name})

    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/${module_source_file}" module_source_content)
    if (
            NOT module_source_content MATCHES "KERBAL_EXPORT_MODULE_DECLARE\\(([^\\)]+)\\)"
    )
#        message(STATUS "exclude ${module_source_file}")
        continue()
    endif()

#    message(STATUS "CMAKE_MATCH_1 ${CMAKE_MATCH_1}")

    if (
            module_source_content MATCHES "#define KERBAL_EXPORT_MODULE_DECLARE"
    )
        message(WARNING "exclude ${module_source_file}")
        continue()
    endif()

    string(REGEX REPLACE "KERBAL_EXPORT_MODULE_DECLARE\\(([^\\)]+)\\)"
            "

#define KERBAL_ENABLE_MODULES_${module_name} 1
"
            module_source_content
            "${module_source_content}"
    )

    string(REPLACE "KERBAL_MODULE_GLOBAL" "module;" module_source_content "${module_source_content}")
    set(cppm_file_path "${CMAKE_CURRENT_BINARY_DIR}/cppm/${module_name}.cppm")
    file(WRITE
            "${cppm_file_path}"
            "${module_source_content}"
    )

    target_sources(
            use_module
            PUBLIC
            FILE_SET kerbal_modules
            TYPE CXX_MODULES
            FILES "${cppm_file_path}"
    )
#    message(STATUS "cppm_file_path ${cppm_file_path}")
endforeach ()


target_sources(
        use_module
        PUBLIC
        FILE_SET kerbal_modules
        TYPE CXX_MODULES
        FILES "foo.cppm"
)

