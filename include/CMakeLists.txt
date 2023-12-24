#
# @file       CMakeLists.txt
# @brief
# @date       2023-12-24
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

include(${PROJECT_SOURCE_DIR}/cmake/aux_headers.cmake)


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


target_include_directories(
        kerbal INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(
        kerbal INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
)
