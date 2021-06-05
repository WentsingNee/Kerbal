/**
 * @file       _0_gnu.part.hpp
 * @brief
 * @date       2021-06-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__0_GNU_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__0_GNU_PART_HPP

#include <kerbal/config/compiler_private.hpp>


//	https://gcc.gnu.org/onlinedocs/gcc-4.3.0/gcc/Type-Traits.html#Type-Traits

#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T)				__has_trivial_destructor(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_ABSTRACT(T)				__is_abstract(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ABSTRACT
#	define KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_BASE_OF(BASE, DERIVED)		__is_base_of(BASE, DERIVED)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_BASE_OF
#	define KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_CLASS(T)					__is_class(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CLASS
#	define KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_EMPTY(T)					__is_empty(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_EMPTY
#	define KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_ENUM(T)					__is_enum(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ENUM
#	define KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_LITERAL_TYPE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_LITERAL_TYPE(T)					__is_literal_type(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_LITERAL_TYPE
#	define KERBAL_HAS_INTRINSIC_IS_LITERAL_TYPE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_POLYMORPHIC(T)				__is_polymorphic(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_POLYMORPHIC
#	define KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T)				__is_standard_layout(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_UNION(T)					__is_union(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_UNION
#	define KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT 1
#endif



// https://gcc.gnu.org/onlinedocs/gcc-4.6.1/gcc/Type-Traits.html#Type-Traits

#ifndef KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 6, 1)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T)			__is_standard_layout(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(4, 7, 1) // There is no official document to describe `__is_final`, just testing result
#		define KERBAL_INTRINSIC_IS_FINAL(T)					__is_final(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FINAL
#	define KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(5, 3, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(...)				__is_trivially_constructible(__VA_ARGS__)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(5, 3, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(T, U)				__is_trivially_assignable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT
#	if KERBAL_GNU_VERSION_MEETS(7, 1, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_AGGREGATE(T)				__is_aggregate(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_AGGREGATE
#	define KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT 1
#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__0_GNU_PART_HPP
