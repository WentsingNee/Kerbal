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
set(CPACK_PACKAGE_VENDOR "Wentsing Nee")
set(CPACK_PACKAGE_CONTACT "Wentsing Nee")
set(CPACK_PACKAGE_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)

if (NOT DEFINED CPACK_OUTPUT_FILE_PREFIX)
    set(CPACK_OUTPUT_FILE_PREFIX "packages/${CMAKE_PROJECT_VERSION}")
endif ()

if (NOT DEFINED CPACK_GENERATOR)
    set(CPACK_GENERATOR DEB STGZ TGZ ZIP NuGet)
endif ()


# DEB
set(CPACK_DEBIAN_PACKAGE_NAME libkerbal-dev)

# NuGet
set(CPACK_NUGET_PACKAGE_DEBUG ON)
set(CPACK_NUGET_COMPONENT_INSTALL ON)
set(
    CPACK_NUGET_FILES_TAG
    "
<files>
    <file src=\"include/\" target=\"include\" />
</files>"
)
set(CPACK_NUGET_GROUPS "include")

# Wix
file(COPY "${PROJECT_SOURCE_DIR}/cmake/cpack/config/wix_patch.cmake" DESTINATION "${KERBAL_CONFIGURE_ASSETS_DIR}/cpack/config")


# MyPack NuGet
option(KERBAL_ENABLE_MYPACK_NUGET "enable mypack nuget" OFF)

if (KERBAL_ENABLE_MYPACK_NUGET)
    message(STATUS "Finding nuget")
    find_program(NUGET_COMMAND nuget REQUIRED)
    message(STATUS "Finding nuget -- Found: ${NUGET_COMMAND}")
    set(CPACK_PROJECT_URL "https://github.com/WentsingNee/${CPACK_PACKAGE_NAME}")
    set(mypack_base_dir "${PROJECT_BINARY_DIR}/_CPack_Packages/${CMAKE_SYSTEM_NAME}/mypack-nuget/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
    set(mypack_nuspec "${mypack_base_dir}/Kerbal.nuspec")
    configure_file(
            "${PROJECT_SOURCE_DIR}/cmake/cpack/mypack_nuget/Kerbal.nuspec"
            "${mypack_nuspec}"
    )
    file(
            COPY
            "${PROJECT_SOURCE_DIR}/cmake/cpack/mypack_nuget/build/Kerbal.targets"
            DESTINATION "${mypack_base_dir}/build/"
    )
    set(MYPACK_NUGET_INSTALL_DIRECTORY "${mypack_base_dir}")
    set(MYPACK_NUGET_OUTPUT_DIRECTORY "${CPACK_OUTPUT_FILE_PREFIX}")
    add_custom_target(
            mypack_nuget
            COMMAND ${CMAKE_COMMAND} -E make_directory
                    "${MYPACK_NUGET_INSTALL_DIRECTORY}"
                    "${MYPACK_NUGET_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND}
                    -DCMAKE_INSTALL_PREFIX="${MYPACK_NUGET_INSTALL_DIRECTORY}"
                    -P "${PROJECT_BINARY_DIR}/cmake_install.cmake"
            COMMAND ${NUGET_COMMAND} pack
                    "${mypack_nuspec}"
                    -OutputDirectory "${MYPACK_NUGET_OUTPUT_DIRECTORY}"
                    -BasePath "${MYPACK_NUGET_INSTALL_DIRECTORY}"
    )
endif ()


set(CPACK_PROJECT_CONFIG_FILE "${PROJECT_SOURCE_DIR}/cmake/cpack/config.cmake")
message(STATUS "CPACK_PROJECT_CONFIG_FILE: ${CPACK_PROJECT_CONFIG_FILE}")

include(CPack)
