#
# @file       version.cmake
# @brief
# @date       2023-02-07
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

set(project_version_file_path "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")

if (${KERBAL_UPDATE_VERSION})
    execute_process(
            COMMAND date "+%Y-%-m-%-d"
            OUTPUT_VARIABLE date
    )
    string(REGEX MATCH "(.*)-(.*)-(.*)" _ ${date})
    set(year ${CMAKE_MATCH_1})
    set(month ${CMAKE_MATCH_2})
    set(day ${CMAKE_MATCH_3})
    set(KERBAL_VERSION "${year}.${month}.1")
else ()
    file(READ "${project_version_file_path}" KERBAL_VERSION)
endif ()


# increase build
#if (EXISTS "${project_version_file_path}")
#    file(READ "VERSION" version)
#    string(FIND ${version} "." pos REVERSE)
#    math(EXPR pos "${pos} + 1")
#    string(SUBSTRING ${version} ${pos} -1 build)
#    math(EXPR build "${build} + 1")
#    message("${build}")
#else ()
#    set(build 1)
#endif ()


if (${KERBAL_UPDATE_VERSION})
    message(STATUS "Updated version ${KERBAL_VERSION} to ${project_version_file_path}")
    file(WRITE "${project_version_file_path}" ${KERBAL_VERSION})
endif ()
