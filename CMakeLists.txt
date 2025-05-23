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
