/**
 * @file       _3_icc.hpp
 * @brief
 * @date       2021-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__3_ICC_HPP
#define KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__3_ICC_HPP

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_class)
#			define KERBAL_IS_CLASS(T) __is_class(T)
#		endif

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_empty)
#			define KERBAL_IS_EMPTY(T) __is_empty(T)
#		endif

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_enum)
#			define KERBAL_IS_ENUM(T) __is_enum(T)
#		endif

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_final)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		endif

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_union)
#			define KERBAL_IS_UNION(T) __is_union(T)
#		endif

#endif // KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__3_ICC_HPP
