#
# @file       header_integration.cmake
# @brief
# @date       2023-11-02
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

foreach (
        sublib IN ITEMS
        kerbal
        kerbal-omp
        kerbal-parallel
)
    if (NOT TARGET ${sublib})
        message(WARNING "header_integration ${sublib} ignored")
        continue()
    endif ()

    set(content_of_header_integration
        "
#ifndef LITTLE_ENDIAN
#	define LITTLE_ENDIAN 4321
#endif

#ifndef BIG_ENDIAN
#	define BIG_ENDIAN 1234
#endif

#ifndef BYTE_ORDER
#	define BYTE_ORDER LITTLE_ENDIAN
#endif

"
    )
    foreach (header IN LISTS Kerbal_PUBLIC_HEADERS_RELATIVE_${sublib})
        string(APPEND content_of_header_integration "#include <${header}>\n")
    endforeach ()
    set(header_integration_filename "${KERBAL_CONFIGURE_ASSETS_DIR}/header_integration/${sublib}.cpp")
    file(WRITE "${header_integration_filename}" "${content_of_header_integration}")
    add_library(
            header_integration.${sublib}
            OBJECT "${header_integration_filename}"
    )
    target_link_libraries(
            header_integration.${sublib}
            PRIVATE ${CMAKE_PROJECT_NAME}::${sublib}
    )

endforeach ()
