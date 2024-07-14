@PACKAGE_INIT@


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Modules)


## kerbal

include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets-kerbal.cmake")
get_target_property(@PROJECT_NAME@_INCLUDE_DIRS @PROJECT_NAME@::kerbal INTERFACE_INCLUDE_DIRECTORIES)


get_property(__enabled_lang GLOBAL PROPERTY ENABLED_LANGUAGES)
if ("CXX" IN_LIST __enabled_lang)

    ## kerbal-coroutine

    include(Kerbal/coroutine)
    kerbal_coroutine_required()
    if (KERBAL_SUPPORT_COROUTINE)
        include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets-kerbal-coroutine.cmake")
        kerbal_target_with_coroutine(
                TARGET Kerbal::kerbal-coroutine
                SCOPE INTERFACE
                MODE REQUIRED
        )
    endif ()

    ## kerbal-omp

    find_package(OpenMP)
    if (OpenMP_FOUND)
        include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets-kerbal-omp.cmake")
    endif ()

    ## kerbal-parallel

    find_package(Threads)
    if (Threads_FOUND)
        include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets-kerbal-parallel.cmake")
    endif ()

endif ()
unset(__enabled_lang)


include(Kerbal/list_ext)


function(__kerbal_absolute_to_relative _Out_list_name list)
    set(result)
    foreach (header IN LISTS list)
        file(RELATIVE_PATH header_relative ${Kerbal_INCLUDE_DIRS} ${header})
        list(APPEND result
            ${header_relative}
        )
    endforeach ()
    set(${_Out_list_name} ${result} PARENT_SCOPE)
endfunction()

foreach (
    sublib IN ITEMS
    kerbal
    kerbal-coroutine
    kerbal-omp
    kerbal-parallel
)
    if (NOT TARGET @PROJECT_NAME@::${sublib})
        continue()
    endif ()

    get_target_property(@PROJECT_NAME@_HEADERS_${sublib} @PROJECT_NAME@::${sublib} INTERFACE_SOURCES)
    __kerbal_absolute_to_relative(@PROJECT_NAME@_HEADERS_RELATIVE_${sublib} "${@PROJECT_NAME@_HEADERS_${sublib}}")
    kerbal_list_regex_filter(
            @PROJECT_NAME@_PUBLIC_HEADERS_RELATIVE_${sublib} "${@PROJECT_NAME@_HEADERS_RELATIVE_${sublib}}"
            BLOCK_PATTERNS
                ".*part\.hpp$"
                "detail/"
    )
    kerbal_list_regex_filter(
            @PROJECT_NAME@_PUBLIC_HEADERS_${sublib} "${@PROJECT_NAME@_HEADERS_${sublib}}"
            BLOCK_PATTERNS
                ".*part\.hpp$"
                "detail/"
    )
    unset(@PROJECT_NAME@_HEADERS_${sublib})
    unset(@PROJECT_NAME@_HEADERS_RELATIVE_${sublib})
endforeach()


check_required_components("@PROJECT_NAME@")
