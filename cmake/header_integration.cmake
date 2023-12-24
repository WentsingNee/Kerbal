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

include(Kerbal/aux_headers)

set(kerbal_public_header_block_patterns
        ".*part\.hpp$"
        "detail/"
)

if (NOT KERBAL_ENABLE_OPENMP)
    list(APPEND kerbal_public_header_block_patterns "^kerbal/openmp/*")
endif ()

kerbal_aux_headers(
        kerbal_public_headers "${PROJECT_SOURCE_DIR}/include/kerbal"
        RELATIVE "${PROJECT_SOURCE_DIR}/include"
        BLOCK_PATTERNS ${kerbal_public_header_block_patterns}
)


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
foreach (header ${kerbal_public_headers})
    string(APPEND content_of_kerbal_header_integration "#include <${header}>\n")
endforeach ()
set(kerbal_header_integration_filename "${CMAKE_BINARY_DIR}/kerbal_header_integration.cpp")
file(WRITE "${kerbal_header_integration_filename}" "${content_of_kerbal_header_integration}")
add_library(kerbal_header_integration OBJECT "${kerbal_header_integration_filename}")
target_link_libraries(kerbal_header_integration PRIVATE ${CMAKE_PROJECT_NAME}::kerbal)
