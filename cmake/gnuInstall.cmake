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
include(CMakePackageConfigHelpers)


configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
        "${KERBAL_CONFIGURE_ASSETS_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)

write_basic_package_version_file(
        "${KERBAL_CONFIGURE_ASSETS_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
        ARCH_INDEPENDENT
)

install(
        FILES
            "${KERBAL_CONFIGURE_ASSETS_DIR}/${PROJECT_NAME}Config.cmake"
            "${KERBAL_CONFIGURE_ASSETS_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)
