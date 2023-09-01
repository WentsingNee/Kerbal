#
# @file       wix_patch.cmake
# @brief
# @date       2024-04-01
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

if (CPACK_GENERATOR MATCHES "WIX")
    # License: WIX package generator requires that license file cannot be no extension

    file(COPY "${KERBAL_SOURCE_DIR}/LICENSE" DESTINATION "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/wix/")
    file(RENAME "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/wix/LICENSE" "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/wix/LICENSE.txt")
    set(CPACK_RESOURCE_FILE_LICENSE "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/wix/LICENSE.txt")


    # Version
    # WIX package generator has the following requirements:
    # Product version must have a major version less than 256, a minor version less than 256, and a build version less than 65536.
    string(REGEX MATCH "(.*)\\.(.*)\\.(.*)" _ "${CPACK_PACKAGE_VERSION}")
    set(major "${CMAKE_MATCH_1}")
    set(minor "${CMAKE_MATCH_2}")
    set(patch "${CMAKE_MATCH_3}")

    math(EXPR wix_major "${major} - 2000")
    set(CPACK_PACKAGE_VERSION "${wix_major}.${minor}.${patch}")
endif ()
