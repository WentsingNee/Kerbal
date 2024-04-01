#
# @file       config.cmake
# @brief
# @date       2024-04-01
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

list(GET CPACK_BUILD_SOURCE_DIRS 0 KERBAL_SOURCE_DIR)
list(GET CPACK_BUILD_SOURCE_DIRS 1 KERBAL_BUILD_DIR)

set(KERBAL_CONFIGURE_ASSETS_DIR "${KERBAL_BUILD_DIR}/configure_assets")

file(GLOB_RECURSE cpack_config_files "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/config/*.cmake")
foreach (file IN LISTS cpack_config_files)
    message(STATUS "Apply cpack config file: ${file}")
    include("${file}")
endforeach ()
