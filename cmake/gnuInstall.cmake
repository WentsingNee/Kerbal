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

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.23)
    install(
            TARGETS kerbal
            EXPORT ${PROJECT_NAME}Targets
            FILE_SET "kerbal_installed_headers"
    )
else ()
    install(
            TARGETS kerbal
            EXPORT ${PROJECT_NAME}Targets
    )
    # Header
    install(
            FILES ${kerbal_installed_headers}
            TYPE INCLUDE
    )
endif ()

install(
        EXPORT ${PROJECT_NAME}Targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
)
