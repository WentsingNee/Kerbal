#
# @file       pkgconfig.cmake
# @brief
# @date       2025-08-20
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/pkgconfig/kerbal.pc.in"
        "${KERBAL_CONFIGURE_ASSETS_DIR}/kerbal.pc"
        @ONLY
)

install(
        FILES
        "${KERBAL_CONFIGURE_ASSETS_DIR}/kerbal.pc"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/pkgconfig"
)
