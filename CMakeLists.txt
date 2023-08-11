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

include(cmake/aux_headers.cmake)

aux_headers(kerbal_installed_headers "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/include" "")

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.19)
    add_library(kerbal INTERFACE ${kerbal_installed_headers})
else ()
    add_library(kerbal INTERFACE)
endif ()

add_library(Kerbal::kerbal ALIAS kerbal)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.23)
    target_sources(
            kerbal INTERFACE
            FILE_SET "kerbal_installed_headers"
            TYPE HEADERS
            BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
            FILES ${kerbal_installed_headers}
    )
endif ()

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

target_include_directories(
        kerbal INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(
        kerbal INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
)



# Build Header Integration
option(KERBAL_BUILD_HEADER_INTEGRATION "build header integration" OFF)
include(cmake/header_integration.cmake)


# Build Script
option(KERBAL_BUILD_SCRIPT "build script" OFF)
if (${KERBAL_BUILD_SCRIPT})
    add_subdirectory(script)
endif ()

include(cmake/gnuInstall.cmake)
include(cmake/cpack.cmake)


# pretty printer

message(STATUS "Checking pretty printer module exist")

if (EXISTS ${PROJECT_SOURCE_DIR}/pretty_printer/CMakeLists.txt)
    message(STATUS "Checking pretty printer module exist -- YES")
    set(KERBAL_PRETTY_PRINTER_MODULE_EXIST True)
else ()
    message(STATUS "Checking pretty printer module exist -- NO")
    set(KERBAL_PRETTY_PRINTER_MODULE_EXIST False)
endif ()

option(KERBAL_INSTALL_PRETTY_PRINTER "install pretty printer" ${KERBAL_PRETTY_PRINTER_MODULE_EXIST})

if (${KERBAL_INSTALL_PRETTY_PRINTER})
    if (NOT ${KERBAL_PRETTY_PRINTER_MODULE_EXIST})
        message(FATAL_ERROR "You haven't download pretty_printer submodule")
    endif ()
    add_subdirectory(pretty_printer)
endif ()
