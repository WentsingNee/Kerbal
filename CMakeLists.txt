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
        LANGUAGES CXX
        VERSION ${KERBAL_VERSION}
)

file(GLOB_RECURSE kerbal_src include/kerbal/container "*.hpp")
add_library(Kerbal INTERFACE ${kerbal_src})

target_include_directories(
        Kerbal INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

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
