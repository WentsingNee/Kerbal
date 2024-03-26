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

set(configure_assets_dir "${CMAKE_BINARY_DIR}/configure_assets")

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
        "${configure_assets_dir}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)

write_basic_package_version_file(
        "${configure_assets_dir}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
        ARCH_INDEPENDENT
)

install(
        FILES
            "${configure_assets_dir}/${PROJECT_NAME}Config.cmake"
            "${configure_assets_dir}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)
