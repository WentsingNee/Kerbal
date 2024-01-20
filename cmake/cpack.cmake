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

if (NOT DEFINED CPACK_GENERATOR)
    set(CPACK_GENERATOR DEB STGZ TGZ ZIP)
endif ()


# DEB
set(CPACK_DEBIAN_PACKAGE_NAME libkerbal-dev)


include(CPack)
