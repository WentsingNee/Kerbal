#
# @file       list_ext.cmake
# @brief
# @date       2023-12-25
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

function(kerbal_sublist list begin length _Out_name)
    list(LENGTH list list_len)

    if ((begin LESS 0) OR (begin GREATER list_len))
        message(FATAL_ERROR "begin index out of range. begin: ${begin}, valid range: [0 ~ ${list_len}]")
    endif ()

    if (length LESS 0)
        math(EXPR end "${list_len}")
    else ()
        math(EXPR end "${begin} + ${length}")
        if (end GREATER list_len)
            message(FATAL_ERROR "end index out of range. end: ${end}, valid range: [0 ~ ${list_len}]")
        endif ()
    endif ()

    set(result)
    while (NOT begin EQUAL end)
        list(GET list ${begin} e)
        list(APPEND result ${e})
        math(EXPR begin "${begin} + 1")
    endwhile ()
    set(${_Out_name} ${result} PARENT_SCOPE)
endfunction()


###
# _Out_name
# list
# BLOCK_PATTERNS multi
function(kerbal_list_regex_filter _Out_name list)
    kerbal_sublist("${ARGV}" 2 -1 ARGV)
#    message(STATUS "list ${list}")
#    message(STATUS "ARGV ${ARGV}")
    cmake_parse_arguments("" "" "" "BLOCK_PATTERNS" ${ARGV})
    set(block_patterns ${_BLOCK_PATTERNS})
#    message(STATUS "block_patterns ${block_patterns}")

    set(result)
    foreach(e ${list})
        set(block False)
        foreach (pattern ${block_patterns})
            if (e MATCHES ${pattern})
                set(block True)
                break()
            endif ()
        endforeach ()
        if (block)
            continue()
        endif ()
        list(APPEND result ${e})
    endforeach ()

    set(${_Out_name} ${result} PARENT_SCOPE)
endfunction()
