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

include(GNUInstallDirs)

include(Kerbal/aux_headers)
include(Kerbal/list_ext)


kerbal_aux_headers(
        headers_relative_kerbal "${PROJECT_SOURCE_DIR}/include/kerbal"
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        BLOCK_PATTERNS
            "coroutine/*"
            "openmp/*"
            "parallel/*"
)

kerbal_aux_headers(
        headers_relative_kerbal-coroutine "${PROJECT_SOURCE_DIR}/include/kerbal/coroutine"
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
)

kerbal_aux_headers(
        headers_relative_kerbal-omp "${PROJECT_SOURCE_DIR}/include/kerbal/openmp"
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
)

kerbal_aux_headers(
        headers_relative_kerbal-parallel "${PROJECT_SOURCE_DIR}/include/kerbal/parallel"
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
)


foreach (
    lib IN ITEMS
    kerbal
    kerbal-coroutine
    kerbal-omp
    kerbal-parallel
)

    set(headers_relative ${headers_relative_${lib}})

    kerbal_list_regex_filter(
            public_headers_relative "${headers_relative}"
            BLOCK_PATTERNS
                ".*part\.hpp$"
                "detail/"
    )
    set(${CMAKE_PROJECT_NAME}_PUBLIC_HEADERS_RELATIVE_${lib} ${public_headers_relative} PARENT_SCOPE)

    foreach (header IN LISTS public_headers_relative)
        list(APPEND public_headers "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
    endforeach ()
    set(${CMAKE_PROJECT_NAME}_PUBLIC_HEADERS_${lib} ${public_headers} PARENT_SCOPE)

    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
        add_library(${lib} INTERFACE ${headers_relative})
    else ()
        add_library(${lib} INTERFACE)
    endif ()

    add_library(
            ${CMAKE_PROJECT_NAME}::${lib}
            ALIAS ${lib}
    )

    foreach (header IN LISTS headers_relative)
        target_sources(${lib} INTERFACE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${header}>
                $<INSTALL_INTERFACE:include/${header}>
        )
    endforeach ()

    target_include_directories(${lib} INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
    )


    install(
            TARGETS ${lib}
            EXPORT ${PROJECT_NAME}Targets-${lib}
    )
    install(
            EXPORT ${PROJECT_NAME}Targets-${lib}
            NAMESPACE ${PROJECT_NAME}::
            DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
    )
    # Header
    foreach (header IN LISTS headers_relative)
        get_filename_component(path ${header} DIRECTORY)
        install(
                FILES ${header}
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${path}
        )
    endforeach ()
endforeach ()


## kerbal

target_compile_options(
        kerbal
        INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
)


## kerbal-coroutine

target_link_libraries(
        kerbal-coroutine
        INTERFACE
        kerbal
)

include(Kerbal/coroutine)
kerbal_coroutine_required()
if (KERBAL_SUPPORT_COROUTINE)
    target_compile_options(
            kerbal-coroutine
            INTERFACE $<BUILD_INTERFACE:${KERBAL_FLAGS_COROUTINE}>
    )
endif ()


## kerbal-omp

target_link_libraries(
        kerbal-omp
        INTERFACE
            kerbal
            $<INSTALL_INTERFACE:OpenMP::OpenMP_CXX>
)

include(FindOpenMP)

if (OpenMP_FOUND)
    target_link_libraries(
            kerbal-omp
            INTERFACE $<BUILD_INTERFACE:OpenMP::OpenMP_CXX>
    )
endif ()


## kerbal-parallel

target_link_libraries(
        kerbal-parallel
        INTERFACE
            kerbal
            $<INSTALL_INTERFACE:Threads::Threads>
)

include(FindThreads)

if (Threads_FOUND)
    target_link_libraries(
            kerbal-parallel
            INTERFACE $<BUILD_INTERFACE:Threads::Threads>
    )
endif ()
