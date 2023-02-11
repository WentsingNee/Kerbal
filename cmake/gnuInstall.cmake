#
# @file       gnuInstall.cmake
# @brief
# @date       2022-06-12
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

include(GNUInstallDirs)

install(
        TARGETS Kerbal
        EXPORT kerbal-config
)
install(
        EXPORT kerbal-config
        NAMESPACE kerbal::
        DESTINATION lib/cmake/Kerbal
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/kerbal-config-version.cmake
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/kerbal-config-version.cmake
        DESTINATION lib/cmake/Kerbal
)

# Header
install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/include/kerbal
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
