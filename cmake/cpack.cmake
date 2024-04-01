#
# @file       cpack.cmake
# @brief
# @date       2022-06-12
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "Wentsing Nee")
set(CPACK_PACKAGE_DESCRIPTION "Kerbal C++ Library")
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)

if (NOT DEFINED CPACK_OUTPUT_FILE_PREFIX)
    set(CPACK_OUTPUT_FILE_PREFIX "packages/${CMAKE_PROJECT_VERSION}")
endif ()

if (NOT DEFINED CPACK_GENERATOR)
    set(CPACK_GENERATOR DEB STGZ TGZ ZIP)
endif ()


# DEB
set(CPACK_DEBIAN_PACKAGE_NAME libkerbal-dev)


set(CPACK_PROJECT_CONFIG_FILE "${PROJECT_SOURCE_DIR}/cmake/cpack/config.cmake")
message(STATUS "CPACK_PROJECT_CONFIG_FILE: ${CPACK_PROJECT_CONFIG_FILE}")

include(CPack)
