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

#include <kerbal/config/compiler_private.hpp>


#if KERBAL_ICC_VERSION_MEETS(13, 0, 1)

#			define KERBAL_IS_ABSTRACT(T)					__is_abstract(T)
#			define KERBAL_IS_BASE_OF(BASE, DERIVED)			__is_base_of(BASE, DERIVED)
#			define KERBAL_IS_CLASS(T)						__is_class(T)
#			define KERBAL_IS_CONVERTIBLE(FROM, TO)			__is_convertible_to(FROM, TO)
#			define KERBAL_IS_EMPTY(T)						__is_empty(T)
#			define KERBAL_IS_ENUM(T)						__is_enum(T)
#			define KERBAL_IS_FINAL(T)						__is_final(T)
#			define KERBAL_IS_POLYMORPHIC(T)					__is_polymorphic(T)
#			define KERBAL_IS_UNION(T)						__is_union(T)

#endif

#		if KERBAL_ICC_VERSION_MEETS(18, 0, 0) // 18.0.0
#			define KERBAL_IS_AGGREGATE(T) __is_aggregate(T)
#		endif

#endif // KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__3_ICC_HPP
