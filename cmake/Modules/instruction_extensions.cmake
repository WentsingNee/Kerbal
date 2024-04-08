#
# @file       instruction_extensions.cmake
# @brief
# @date       2022-12-02
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

include(CheckCXXCompilerFlag)


set(KERBAL_IE_LIST
        mmx sse sse2 sse3 ssse3 sse4.1 sse4.2 avx avx2 avx512f
        bmi bmi2 sha
        neon sve
)


function(kerbal_check_supports_ie_flags ie _Out_support)
    set(flags ${ARGN})

    message(STATUS "Checking compiler support ${ie} flags: `${flags}`")
    CHECK_CXX_COMPILER_FLAG("${flags}" check_result)
    message(STATUS "Checking compiler support ${ie} flags: `${flags}` - Done")

    if (check_result GREATER 0)
        set(${_Out_support} True PARENT_SCOPE)
    else ()
        set(${_Out_support} False PARENT_SCOPE)
    endif ()

    unset(check_result CACHE)
endfunction()


function(__kerbal_cache_result_of_supports_ie_flags ie support)
    set(flags ${ARGN})
    set(KERBAL_SUPPORT_${ie} ${support} CACHE BOOL "Whether compiler support ${ie}")
    message(STATUS "set KERBAL_SUPPORT_${ie} = ${support}")
    if (support)
        set(KERBAL_FLAGS_${ie} ${flags} CACHE STRING "Compile flags for compiler to support ${ie}")
        message(STATUS "set KERBAL_FLAGS_${ie} = ${flags}")
    endif ()
    message("")
endfunction()


function(__kerbal_check_supports_ie_flags_and_cache ie)
    set(flags ${ARGN})

    kerbal_check_supports_ie_flags(ie support ${flags})
    __kerbal_cache_result_of_supports_ie_flags(${ie} ${support} ${flags})
endfunction()


function(__kerbal_multi_check_supports_ie_flags_and_cache ie)
    set(try_flags_list ${ARGN})
    foreach (e IN LISTS try_flags_list)
        set(prev_try_flags ${flags})
        if (prev_try_flags)
            message(STATUS "`${prev_try_flags}` doesn't support, re-trying: `${flags}`")
        endif ()
        get_property(flags GLOBAL PROPERTY ${e})
        kerbal_check_supports_ie_flags(${ie} support ${flags})
        if (support)
            __kerbal_cache_result_of_supports_ie_flags(${ie} True ${flags})
            return()
        endif ()
    endforeach ()

    __kerbal_cache_result_of_supports_ie_flags(${ie} False)
endfunction()


function(kerbal_ies_required)
    message("\n")
    message(STATUS "Checking compiler's support for instruction extensions\n")

    set(required_ies ${ARGN})

    foreach (ie IN LISTS required_ies)
        if (DEFINED KERBAL_SUPPORT_${ie})
            message(STATUS "Checking compiler support ${ie} -- Cached")
            message(STATUS "Cached KERBAL_SUPPORT_${ie} = ${KERBAL_SUPPORT_${ie}}")
            if (KERBAL_SUPPORT_${ie})
                message(STATUS "Cached KERBAL_FLAGS_${ie} = `${KERBAL_FLAGS_${ie}}`")
            endif ()
            message("")
            continue()
        endif ()

        if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
            if (ie STREQUAL "avx512f")
                __kerbal_check_supports_ie_flags_and_cache(${ie} /arch:AVX512)
            elseif (ie MATCHES "^((avx2)|(avx)|(sse2)|(sse))$")
                string(TOUPPER ${ie} flag)
                set(flag "/arch:${flag}")
                __kerbal_check_supports_ie_flags_and_cache(${ie} ${flag})
            endif ()
        else()
            if (ie STREQUAL "mmx")
                __kerbal_check_supports_ie_flags_and_cache(${ie} -m${ie} -mno-sse)
                continue()
            endif ()
            if (ie STREQUAL "sve")
                __kerbal_check_supports_ie_flags_and_cache(${ie} -march=armv8-a+sve)
                continue()
            endif ()
            if (ie STREQUAL "neon")
                set_property(GLOBAL PROPERTY KERBAL_IE_ARM -march=armv8-a -mfpu=neon)
                set_property(GLOBAL PROPERTY KERBAL_IE_AARCH64 -march=armv8-a+simd)
                __kerbal_multi_check_supports_ie_flags_and_cache(
                        "neon"
                        KERBAL_IE_ARM
                        KERBAL_IE_AARCH64
                )
                continue()
            endif ()

            __kerbal_check_supports_ie_flags_and_cache(${ie} -m${ie})
        endif ()
    endforeach ()

    message("\n")
endfunction()


##
# TARGET one string
# IEs multi string
# SCOPE one string, must be in: {PUBLIC PRIVATE INTERFACE}
# MODE optional string, default is REQUIRED, must be in: {REQUIRED, WARNING, SILENCE}
#
function(kerbal_target_with_ies)
    cmake_parse_arguments(
            ""
            ""
            "SCOPE;MODE;TARGET"
            "IEs"
            ${ARGV}
    )

    if (NOT _TARGET)
        message(FATAL_ERROR "TARGET is not specified")
    endif ()
    set(target "${_TARGET}")

    set(ies "${_IEs}")

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

    foreach (ie IN LISTS ies)
        if (NOT KERBAL_SUPPORT_${ie})
            if (mode STREQUAL "REQUIRED")
                message(FATAL_ERROR "Compiler doesn't support ${ie}")
            elseif (mode STREQUAL "WARNING")
                message(WARNING "Compiler doesn't support ${ie}")
            endif ()
            continue()
        endif ()

        target_compile_options(${target} ${scope} ${KERBAL_FLAGS_${ie}})

    endforeach ()

endfunction()
