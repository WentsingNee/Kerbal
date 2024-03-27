#
# @file       draft_release.cmake
# @brief
# @date       2024-02-24
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

set(packages_suffix
        deb
        sh
        tar.gz
        zip
)

set(asset_content_type
        application/vnd.debian.binary-package
        application/x-sh
        application/gzip
        application/zip
)

message(STATUS "Finding gh")
find_program(gh "gh")

if (NOT gh)
    message(FATAL_ERROR "gh is not found")
endif ()

message(STATUS "Finding gh -- Found")
message(STATUS "gh: ${gh}")


function(draft_release tag version)
    message(STATUS "tag: ${tag}")
    message(STATUS "version: ${version}")
    if (tag STREQUAL "")
        message(FATAL_ERROR "tag is invalid")
    endif ()
    if (version STREQUAL "")
        message(FATAL_ERROR "version is invalid")
    endif ()
    message(STATUS "Creating release... (tag: ${tag})")
    execute_process(
            COMMAND
                ${gh} release create
                "${tag}"
                --draft
                --title "draft release of ${version}"
                --repo WentsingNee/Kerbal
            COMMAND_ECHO STDOUT
    )
    foreach (i RANGE 3)
        list(GET packages_suffix ${i} suffix)
        set(package "Kerbal-${version}-Linux.${suffix}")
        set(package_path "${CMAKE_BINARY_DIR}/packages/${version}/${package}")
        message(STATUS "Uploading asset... (asset: ${package_path})")
        execute_process(
                COMMAND
                    ${gh} release upload
                    "${tag}"
                    "${package_path}"
                    --repo WentsingNee/Kerbal
                COMMAND_ECHO STDOUT
        )
    endforeach ()
endfunction()


if (TAG_NAME STREQUAL "")
    message(FATAL_ERROR "TAG_NAME is not defined")
endif ()
if (VERSION STREQUAL "")
    message(FATAL_ERROR "VERSION is not defined")
endif ()

draft_release("${TAG_NAME}" "${VERSION}")

