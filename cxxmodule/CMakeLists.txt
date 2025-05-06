#
# @file       CMakeLists.txt
# @brief
# @date       2025-05-06
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#


function(add_kerbal_parent_target target)
    string(FIND "${target}" "." pos REVERSE)
    if (pos EQUAL -1)
        return ()
    endif ()
    string(SUBSTRING "${target}" 0 ${pos} parent_target_name)
    add_kerbal_parent_target(${parent_target_name})
    add_dependencies(${parent_target_name} ${target})
    if (NOT parent_target_name STREQUAL "cppm")
        target_link_libraries(
                "${parent_target_name}" PUBLIC "${target}"
        )
    endif ()
endfunction()


file(GLOB_RECURSE children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cppm")
foreach (file IN LISTS children)
    message(VERBOSE "${file}")
    if (NOT file MATCHES "(.+)\\.cppm$")
        string(APPEND ignored_utest_src_files "${CMAKE_CURRENT_SOURCE_DIR}/${file}:0\n")
        continue()
    endif ()
    string(REPLACE "/" "." target ${CMAKE_MATCH_1})
    string(PREPEND target "cppm.")
#    message(WARNING "	add: ${target}  <=  ${CMAKE_CURRENT_SOURCE_DIR}/${file}")

    add_library(
            "${target}"
    )
    target_sources(
            "${target}"
            PUBLIC
            FILE_SET c
            TYPE CXX_MODULES
            FILES "${CMAKE_CURRENT_SOURCE_DIR}/${file}"
    )
endforeach()


add_custom_target("cppm")

foreach (file IN LISTS children)
    add_kerbal_parent_target("${target}")
endforeach()

#MESSAGE(FATAL_ERROR "ee")
