#
# @file       header_list.cpp
# @brief
# @date       2022-11-25
# @author     Peter
# @copyright
#      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
#   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
#   all rights reserved
#

HEADER_ROOT=/home/peter/git/Kerbal/include/

exclude_pattern=(
    type_traits/type_traits.hpp
    \(?!utility\)
)


#exclude_pattern=(
#    bak
#    function.cxx98.hpp
#    function.cxx11.hpp
#    detail
#    config
#    openmp
#    ompalgo
#    macro
#    monotonic_allocator
#    countl_zero
#    simd
#    is_nothrow_assignable
#    is_nothrow_destructible
#    is_trivially_destructible
#    type_traits/type_traits.hpp
#)

function dir_traverse() {
    for e in $(ls $HEADER_ROOT/$1)
    do
        file=$HEADER_ROOT$1/$e
#        echo dbg $file
        if [ -d $file ]
        then
            dir_traverse $1/$e
            continue
        fi

        exclude_this_file=0
        for ep in ${exclude_pattern[@]}
        do
          if [[ "$file" =~ $ep ]]
          then
              echo $ep exclude $file > /dev/stderr
              exclude_this_file=1
              break
          fi
        done

        if [ $exclude_this_file != 0 ]
        then
            continue
        fi

        echo $1/$e
    done
}

dir_traverse kerbal
