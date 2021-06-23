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

//	https://gcc.gnu.org/onlinedocs/gcc-4.3.0/gcc/Type-Traits.html#Type-Traits
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)

#		define KERBAL_IS_ABSTRACT(T)				__is_abstract(T)
#		define KERBAL_IS_BASE_OF(BASE, DERIVED)		__is_base_of(BASE, DERIVED)
#		define KERBAL_IS_CLASS(T)					__is_class(T)
#		define KERBAL_IS_EMPTY(T)					__is_empty(T)
#		define KERBAL_IS_ENUM(T)					__is_enum(T)
#		define KERBAL_IS_POLYMORPHIC(T)				__is_polymorphic(T)
#		define KERBAL_IS_UNION(T)					__is_union(T)

#	else

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_abstract)
#			define KERBAL_IS_ABSTRACT(T)			__is_abstract(T)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_base_of)
#			define KERBAL_IS_BASE_OF(BASE, DERIVED)	__is_base_of(BASE, DERIVED)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_class)
#			define KERBAL_IS_CLASS(T)				__is_class(T)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_empty)
#			define KERBAL_IS_EMPTY(T)				__is_empty(T)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_enum)
#			define KERBAL_IS_ENUM(T)				__is_enum(T)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_polymorphic)
#			define KERBAL_IS_POLYMORPHIC(T)			__is_polymorphic(T)
#		endif

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_union)
#			define KERBAL_IS_UNION(T)				__is_union(T)
#		endif

#	endif



#	if KERBAL_GNU_VERSION_MEETS(4, 7, 1) // There is no official document to describe `__is_final`, just testing result
#		define KERBAL_IS_FINAL(T)					__is_final(T)
#	else

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_final)
#			define KERBAL_IS_FINAL(T)				__is_final(T)
#		endif



#	if KERBAL_GNU_VERSION_MEETS(7, 1, 0) // There is no official document to describe `__is_aggregate`, just testing result
#		define KERBAL_IS_AGGREGATE(T)					__is_aggregate(T)
#	else

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_aggregate)
#			define KERBAL_IS_AGGREGATE(T)				__is_aggregate(T)
#		endif



// https://gcc.gnu.org/onlinedocs/gcc-4.6.1/gcc/Type-Traits.html#Type-Traits

#	if KERBAL_GNU_VERSION_MEETS(4, 6, 1)
#		define KERBAL_IS_STANDARD_LAYOUT(T)					__is_standard_layout(T)
#	else

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_standard_layout)
#			define KERBAL_IS_STANDARD_LAYOUT(T)				__is_standard_layout(T)
#		endif

#	endif

#endif // KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__0_GNU_HPP
