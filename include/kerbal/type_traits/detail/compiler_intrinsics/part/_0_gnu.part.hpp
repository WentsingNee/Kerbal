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

#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T)				__has_trivial_destructor(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_ABSTRACT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_ABSTRACT(T)				__is_abstract(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ABSTRACT
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_ABSTRACT 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_BASE_OF
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_BASE_OF(BASE, DERIVED)		__is_base_of(BASE, DERIVED)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_BASE_OF
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_BASE_OF 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_CLASS
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_CLASS(T)					__is_class(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CLASS
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_CLASS 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_EMPTY
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_EMPTY(T)					__is_empty(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_EMPTY
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_EMPTY 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_ENUM
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_ENUM(T)					__is_enum(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ENUM
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_ENUM 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_LITERAL_TYPE
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_LITERAL_TYPE(T)					__is_literal_type(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_LITERAL_TYPE
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_LITERAL_TYPE 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_POLYMORPHIC
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_POLYMORPHIC(T)				__is_polymorphic(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_POLYMORPHIC
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_POLYMORPHIC 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_STANDARD_LAYOUT
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T)				__is_standard_layout(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_STANDARD_LAYOUT 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_UNION
#	if KERBAL_GNU_VERSION_MEETS(4, 3, 0)
#		define KERBAL_INTRINSIC_IS_UNION(T)					__is_union(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_UNION
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_UNION 1
#endif



// https://gcc.gnu.org/onlinedocs/gcc-4.6.1/gcc/Type-Traits.html#Type-Traits

#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_STANDARD_LAYOUT
#	if KERBAL_GNU_VERSION_MEETS(4, 6, 1)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T)			__is_standard_layout(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_STANDARD_LAYOUT 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_FINAL
#	if KERBAL_GNU_VERSION_MEETS(4, 7, 1) // There is no official document to describe `__is_final`, just testing result
#		define KERBAL_INTRINSIC_IS_FINAL(T)					__is_final(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FINAL
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_FINAL 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#	if KERBAL_GNU_VERSION_MEETS(5, 3, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(...)				__is_trivially_constructible(__VA_ARGS__)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#	if KERBAL_GNU_VERSION_MEETS(5, 3, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(T, U)				__is_trivially_assignable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE 1
#endif



#ifndef KERBAL_PRIVATE_HAS_INTRINSIC_IS_AGGREGATE
#	if KERBAL_GNU_VERSION_MEETS(7, 1, 0) // not official documented, just testing result
#		define KERBAL_INTRINSIC_IS_AGGREGATE(T)				__is_aggregate(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_AGGREGATE
#	define KERBAL_PRIVATE_HAS_INTRINSIC_IS_AGGREGATE 1
#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__0_GNU_PART_HPP
