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

    message(STATUS "Checking compiler support coroutine flags: ${flag}")
    CHECK_CXX_COMPILER_FLAG("${flags}" check_result)
    message(STATUS "Checking compiler support coroutine flags: ${flag} - Done")

    if (check_result GREATER 0)
        set(${_Out_support} True PARENT_SCOPE)
    else ()
        set(${_Out_support} False PARENT_SCOPE)
    endif ()

    unset(check_result CACHE)
endfunction()


function(__kerbal_cache_result_of_supports_coroutine support)
    set(flags ${ARGN})
    set(KERBAL_SUPPORT_${ie} ${support} CACHE BOOL "Whether compiler support coroutine")
    message(STATUS "set KERBAL_SUPPORT_COROUTINE = ${support}")
    if (support)
        set(KERBAL_FLAGS_${ie} ${flags} CACHE STRING "Compile flags for compiler to support coroutine")
        message(STATUS "set KERBAL_FLAGS_COROUTINE = ${flags}")
    endif ()
    message("")
endfunction()


## TODO in next

macro(check_compiler_support_coroutine_flag)
    message(STATUS "Checking compiler support coroutine flag: ${flag}")
    CHECK_CXX_COMPILER_FLAG("${flag}" KTEST_SUPPORT_COROUTINE)
    message(STATUS "Checking compiler support coroutine flag: ${flag} - Done")
    message(STATUS "set KTEST_SUPPORT_COROUTINE = ${KTEST_SUPPORT_COROUTINE}")
    if (KTEST_SUPPORT_COROUTINE)
        set(KTEST_FLAG_COROUTINE ${flag} PARENT_SCOPE)
        message(STATUS "set KERBAL_TEST_COROUTINE_FLAGS = ${flag}")
    endif ()
    message("")
endmacro()


function(try_test_compiler_coroutine_support)
    check_compiler_support_coroutine_flag(-fcoroutines)
    if (KTEST_SUPPORT_COROUTINE)
        return()
    endif ()

    message(STATUS "-fcoroutines doesn't support, try: -fcoroutines-ts")
    unset(KTEST_SUPPORT_COROUTINE CACHE)
    check_compiler_support_coroutine_flag(-fcoroutines-ts)
    message("\n")

endfunction()


message("\n")
message(STATUS "Checking compiler's support for coroutine")
message("")
try_test_compiler_coroutine_support()


