/**
 * @file       _0_gnu.hpp
 * @brief
 * @date       2021-06-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__0_GNU_HPP
#define KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__0_GNU_HPP

#include <kerbal/config/compiler_private.hpp>


//	https://gcc.gnu.org/onlinedocs/gcc-4.3.0/gcc/Type-Traits.html#Type-Traits


#if KERBAL_GNU_VERSION_MEETS(4, 3, 0)

#	ifndef KERBAL_HAS_IS_ABSTRACT_SUPPORT
#		define KERBAL_IS_ABSTRACT(T)				__is_abstract(T)
#	endif

#	ifndef KERBAL_HAS_IS_BASE_OF_SUPPORT
#		define KERBAL_IS_BASE_OF(BASE, DERIVED)		__is_base_of(BASE, DERIVED)
#	endif

#	ifndef KERBAL_HAS_IS_CLASS_SUPPORT
#		define KERBAL_IS_CLASS(T)					__is_class(T)
#	endif

#	ifndef KERBAL_HAS_IS_EMPTY_SUPPORT
#		define KERBAL_IS_EMPTY(T)					__is_empty(T)
#	endif

#	ifndef KERBAL_HAS_IS_ENUM_SUPPORT
#		define KERBAL_IS_ENUM(T)					__is_enum(T)
#	endif

#	ifndef KERBAL_HAS_IS_POLYMORPHIC_SUPPORT
#		define KERBAL_IS_POLYMORPHIC(T)				__is_polymorphic(T)
#	endif

#	ifndef KERBAL_HAS_IS_UNION_SUPPORT
#		define KERBAL_IS_UNION(T)					__is_union(T)
#	endif

#endif



// https://gcc.gnu.org/onlinedocs/gcc-4.6.1/gcc/Type-Traits.html#Type-Traits

#ifndef KERBAL_HAS_IS_STANDARD_LAYOUT_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 6, 1)
#		define KERBAL_IS_STANDARD_LAYOUT(T)			__is_standard_layout(T)
#	endif
#endif



#ifndef KERBAL_HAS_IS_FINAL_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 7, 1) // There is no official document to describe `__is_final`, just testing result
#		define KERBAL_IS_FINAL(T)					__is_final(T)
#	endif
#endif



#ifndef KERBAL_HAS_IS_AGGREGATE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(7, 1, 0) // There is no official document to describe `__is_aggregate`, just testing result
#		define KERBAL_IS_AGGREGATE(T)				__is_aggregate(T)
#	endif
#endif


#endif // KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__0_GNU_HPP
