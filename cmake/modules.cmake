#
# @file       modules.cmake
# @brief
# @date       2023-12-24
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

include(GNUInstallDirs)


set(
        kerbal_modules
        "${PROJECT_SOURCE_DIR}/cmake/Modules/aux_headers.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/Modules/coroutine.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/Modules/instruction_extensions.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/Modules/list_ext.cmake"
)

foreach (module IN LISTS kerbal_modules)
    install(
            FILES
            "${module}"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}/Modules/Kerbal"
    )

    file(
            COPY
            "${module}"
            DESTINATION "${KERBAL_CONFIGURE_ASSETS_DIR}/Modules/Kerbal/"
    )
endforeach ()

list(APPEND CMAKE_MODULE_PATH ${KERBAL_CONFIGURE_ASSETS_DIR}/Modules)
