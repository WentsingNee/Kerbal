/**
 * @file       sha1.cpp
 * @brief
 * @date       2020-09-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

// #include <kerbal/config/target_type.hpp>

#if KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_HEADER
#	undef KERBAL_TARGET_TYPE
#	define KERBAL_TARGET_TYPE KERBAL_TARGET_TYPE_SHARED
#endif

// #include <kerbal/config/library_export.hpp>

#undef KERBAL_LIBRARY_EXPORT
#define KERBAL_LIBRARY_EXPORT 1

#define KERBAL_CONSTEXPR
#define KERBAL_CONSTEXPR14
#define KERBAL_CONSTEXPR20

#include <kerbal/hash/sha1/sha1.impl.hpp>
