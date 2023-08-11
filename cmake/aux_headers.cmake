#
# @file       aux_headers.cmake
# @brief
# @date       2023-08-25
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

function(aux_headers _OUTPUT_LIST_NAME dir prefix block_patterns)
    if (NOT EXISTS ${dir})
        message(FATAL_ERROR "`dir` is not found. dir: ${dir}")
    endif ()

    file(GLOB_RECURSE header_files RELATIVE "${dir}/" "${dir}/*.hpp")

    set(headers_list)
    foreach (file ${header_files})
        set(block FALSE)
        foreach (block_pattern ${block_patterns})
            if (file MATCHES ${block_pattern})
                set(block TRUE)
                break()
            endif ()
        endforeach ()
        if (NOT block)
            if (prefix STREQUAL "")
                list(APPEND headers_list "${file}")
            else ()
                list(APPEND headers_list "${prefix}/${file}")
            endif ()
        endif ()
    endforeach ()

    list(LENGTH headers_list headers_list_len)
    if (headers_list_len EQUAL 0)
        message(WARNING "headers list is empty")
    endif ()

    set(${_OUTPUT_LIST_NAME} ${headers_list} PARENT_SCOPE)
endfunction()
