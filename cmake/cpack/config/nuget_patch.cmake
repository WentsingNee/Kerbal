#
# @file       nuget_patch.cmake
# @brief
# @date       2024-04-19
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

if (CPACK_GENERATOR MATCHES "NuGet")

    set(CPACK_NUGET_PACKAGE_DEBUG True)
    set(CPACK_NUGET_ORDINAL_MONOLITIC False)
    set(CPACK_NUGET_ALL_IN_ONE True)
    set(CPACK_NUGET_COMPONENTS)

    list(APPEND CPACK_NUGET_COMPONENTS "include")

    message(STATUS "xxx CMAKE_BINARY_DIR: <${CMAKE_BINARY_DIR}>")
    message(STATUS "xxx CPACK_NUGET_COMPONENTS: <${CPACK_NUGET_COMPONENTS}>")

endif ()
