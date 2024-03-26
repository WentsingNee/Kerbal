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


set(content_of_kerbal_header_integration
    "
#ifndef LITTLE_ENDIAN
#   define LITTLE_ENDIAN 4321
#endif

#ifndef BIG_ENDIAN
#   define BIG_ENDIAN 1234
#endif

#ifndef BYTE_ORDER
#   define BYTE_ORDER LITTLE_ENDIAN
#endif

"
)
foreach (header ${Kerbal_PUBLIC_HEADERS_RELATIVE_kerbal})
    string(APPEND content_of_kerbal_header_integration "#include <${header}>\n")
endforeach ()
set(kerbal_header_integration_filename "${KERBAL_CONFIGURE_ASSETS_DIR}/kerbal_header_integration.cpp")
file(WRITE "${kerbal_header_integration_filename}" "${content_of_kerbal_header_integration}")
add_library(kerbal_header_integration OBJECT "${kerbal_header_integration_filename}")
target_link_libraries(kerbal_header_integration PRIVATE ${CMAKE_PROJECT_NAME}::kerbal)
