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

include (Kerbal/list_ext)


##
# RELATIVE        one, optional
# BLOCK_PATTERNS  multi
function(kerbal_aux_headers _OUTPUT_LIST_NAME dir)
    kerbal_sublist("${ARGV}" 2 -1 ARGV)
    cmake_parse_arguments(
            ""
            ""
            "RELATIVE"
            "BLOCK_PATTERNS"
            ${ARGV}
    )

    set(relative "${_RELATIVE}")
    set(block_patterns ${_BLOCK_PATTERNS})

    if (NOT EXISTS ${dir})
        message(FATAL_ERROR "`dir` is not found. dir: ${dir}")
    endif ()

    file(GLOB_RECURSE header_files RELATIVE "${dir}/" "${dir}/*.hpp")

    set(headers_list)
    foreach (file ${header_files})
        set(block FALSE)
        foreach (block_pattern ${block_patterns})
            if (${file} MATCHES ${block_pattern})
                set(block TRUE)
                break()
            endif ()
        endforeach ()
        if (block)
            continue()
        endif ()

        if (relative STREQUAL "")
            set(item "${dir}/${file}")
        else ()
            file(RELATIVE_PATH item "${relative}" "${dir}/${file}")
        endif ()
        list(APPEND headers_list ${item})
    endforeach ()

    list(LENGTH headers_list headers_list_len)
    if (${headers_list_len} EQUAL 0)
        message(WARNING "headers list is empty")
    endif ()

    set(${_OUTPUT_LIST_NAME} ${headers_list} PARENT_SCOPE)
endfunction()
