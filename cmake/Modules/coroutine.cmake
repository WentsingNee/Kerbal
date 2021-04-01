#
# @file       coroutine.cmake
# @brief
# @date       2022-12-09
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

include(CheckCXXCompilerFlag)


function(kerbal_check_supports_coroutine_flags _Out_support)
    set(flags ${ARGN})

    message(STATUS "Checking compiler support coroutine flags: `${flags}`")
    CHECK_CXX_COMPILER_FLAG("${flags}" check_result)
    message(STATUS "Checking compiler support coroutine flags: `${flags}` - Done")

    if (check_result GREATER 0)
        set(${_Out_support} True PARENT_SCOPE)
    else ()
        set(${_Out_support} False PARENT_SCOPE)
    endif ()

    unset(check_result CACHE)
endfunction()


function(__kerbal_cache_result_of_supports_coroutine_flags support)
    set(flags ${ARGN})
    set(KERBAL_SUPPORT_COROUTINE ${support} CACHE BOOL "Whether compiler support coroutine")
    message(STATUS "set KERBAL_SUPPORT_COROUTINE = ${support}")
    if (support)
        set(KERBAL_FLAGS_COROUTINE ${flags} CACHE STRING "Compile flags for compiler to support coroutine")
        message(STATUS "set KERBAL_FLAGS_COROUTINE = `${flags}`")
    endif ()
    message("")
endfunction()


function(__kerbal_check_supports_coroutine_flags_and_cache)
    set(flags ${ARGN})

    kerbal_check_supports_coroutine_flags(support ${flags})
    __kerbal_cache_result_of_supports_coroutine_flags(${support} ${flags})
endfunction()


function(__kerbal_multi_check_supports_coroutine_flags_and_cache)
    set(try_flags_list ${ARGN})
    foreach (e IN LISTS try_flags_list)
        set(prev_try_flags ${flags})
        if (prev_try_flags)
            message(STATUS "`${prev_try_flags}` doesn't support, re-trying: `${flags}`")
        endif ()
        get_property(flags GLOBAL PROPERTY ${e})
        kerbal_check_supports_coroutine_flags(support ${flags})
        if (support)
            __kerbal_cache_result_of_supports_coroutine_flags(True ${flags})
            return()
        endif ()
    endforeach ()

    __kerbal_cache_result_of_supports_coroutine_flags(False)
endfunction()


function(kerbal_coroutine_required)
    message("\n")
    message(STATUS "Checking compiler's support for coroutine\n")

    if (DEFINED KERBAL_SUPPORT_COROUTINE)
        message(STATUS "Checking compiler support coroutine -- Cached")
        message(STATUS "Cached KERBAL_SUPPORT_COROUTINE = ${KERBAL_SUPPORT_COROUTINE}")
        if (KERBAL_SUPPORT_COROUTINE)
            message(STATUS "Cached KERBAL_FLAGS_COROUTINE = `${KERBAL_FLAGS_COROUTINE}`")
        endif ()
        message("\n")
        return()
    endif ()

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        if ((CMAKE_CXX_STANDARD EQUAL 98) OR (CMAKE_CXX_STANDARD LESS 14))
            __kerbal_cache_result_of_supports_coroutine_flags(False)
            return()
        endif ()
        set_property(GLOBAL PROPERTY KERBAL_FLAGS_TEST_COROUTINE -fcoroutines)
        __kerbal_multi_check_supports_coroutine_flags_and_cache(
                KERBAL_FLAGS_TEST_COROUTINE
        )
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        if ((CMAKE_CXX_STANDARD EQUAL 98) OR (CMAKE_CXX_STANDARD LESS 20))
            __kerbal_cache_result_of_supports_coroutine_flags(False)
            return()
        endif ()
        set_property(GLOBAL PROPERTY KERBAL_FLAGS_TEST_COROUTINE -fcoroutines)
        set_property(GLOBAL PROPERTY KERBAL_FLAGS_TEST_COROUTINE_TS -fcoroutines-ts)
        __kerbal_multi_check_supports_coroutine_flags_and_cache(
                KERBAL_FLAGS_TEST_COROUTINE
                KERBAL_FLAGS_TEST_COROUTINE_TS
        )
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set_property(GLOBAL PROPERTY KERBAL_FLAGS_TEST_COROUTINE_MSVC /await:strict)
        __kerbal_multi_check_supports_coroutine_flags_and_cache(
                KERBAL_FLAGS_TEST_COROUTINE_MSVC
        )
    else ()
        __kerbal_cache_result_of_supports_coroutine_flags(False)
    endif ()
    message("\n")
endfunction()


##
# TARGET one string
# SCOPE one string, must be in: {PUBLIC PRIVATE INTERFACE}
# MODE optional string, default is REQUIRED, must be in: {REQUIRED, WARNING, SILENCE}
#
function(kerbal_target_with_coroutine)
    cmake_parse_arguments(
            ""
            ""
            "SCOPE;MODE;TARGET"
            ""
            ${ARGV}
    )

    if (NOT _TARGET)
        message(FATAL_ERROR "TARGET is not specified")
    endif ()
    set(target "${_TARGET}")

    if (NOT _SCOPE MATCHES "^((PUBLIC)|(PRIVATE)|(INTERFACE))$")
        message(FATAL_ERROR "SCOPE must be one of: PUBLIC PRIVATE INTERFACE, but is: ${_SCOPE}")
    endif ()
    set(scope "${_SCOPE}")

    if (NOT _MODE)
        set(_MODE "REQUIRED")
    endif ()
    if (NOT _MODE MATCHES "^((REQUIRED)|(WARNING)|(SILENCE))$")
        message(FATAL_ERROR "MODE must be one of: REQUIRED WARNING SILENCE, but is: ${_MODE}")
    endif ()
    set(mode "${_MODE}")

    if (NOT TARGET ${target})
        message(FATAL_ERROR "Target is not exist. target: ${target}")
    endif ()

    if (NOT DEFINED KERBAL_SUPPORT_COROUTINE)
        kerbal_coroutine_required()
    endif ()

    if (NOT KERBAL_SUPPORT_COROUTINE)
        if (mode STREQUAL "REQUIRED")
            message(FATAL_ERROR "Compiler doesn't support coroutine")
        elseif (mode STREQUAL "WARNING")
            message(WARNING "Compiler doesn't support coroutine")
        endif ()
    endif ()

    target_compile_options(${target} ${scope} ${KERBAL_FLAGS_COROUTINE})

endfunction()
