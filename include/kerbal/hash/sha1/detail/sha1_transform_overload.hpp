/**
 * @file       sha1_transform_overload.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_HPP

#include <kerbal/hash/sha1/sha1.fwd.hpp>

#include <kerbal/hash/sha1/detail/sha1_transform_overload/sha1_transform_overload.fast.hpp>
#include <kerbal/hash/sha1/detail/sha1_transform_overload/sha1_transform_overload.size.hpp>

#if KERBAL_ENABLE_SHA1_INSTRUCT
#	include <kerbal/hash/sha1/detail/sha1_transform_overload/sha1_transform_overload.sha1_instruct.hpp>
#endif

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_HPP
