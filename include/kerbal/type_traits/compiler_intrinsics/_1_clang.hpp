/**
 * @file       _1_clang.hpp
 * @brief
 * @date       2021-06-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITSCOMPILER_INTRINSICS__1_CLANG_HPP
#define KERBAL_TYPE_TRAITSCOMPILER_INTRINSICS__1_CLANG_HPP

#include <kerbal/config/compiler_private.hpp>


//		https://clang.llvm.org/docs/LanguageExtensions.html#type-trait-primitives

#	ifndef KERBAL_HAS_IS_ABSTRACT_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_abstract)
#			define KERBAL_IS_ABSTRACT(T) __is_abstract(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_abstract)
#			define KERBAL_IS_ABSTRACT(T) __is_abstract(T)
#		endif
#	endif

#	ifndef KERBAL_HAS_IS_AGGREGATE_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_aggregate)
#			define KERBAL_IS_AGGREGATE(T) __is_aggregate(T)
#		endif
#	endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_arithmetic)
#			define KERBAL_IS_ARITHMETIC(T) __is_arithmetic(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_array)
#			define KERBAL_IS_ARRAY(T) __is_array(T)
#		endif

#	ifndef KERBAL_HAS_IS_BASE_OF_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_base_of)
#			define KERBAL_IS_BASE_OF(BASE, DERIVED) __is_base_of(BASE, DERIVED)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_base_of)
#			define KERBAL_IS_BASE_OF(BASE, DERIVED) __is_base_of(BASE, DERIVED)
#		endif
#	endif

#	ifndef KERBAL_HAS_IS_CLASS_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_class)
#			define KERBAL_IS_CLASS(T) __is_class(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_class)
#			define KERBAL_IS_CLASS(T) __is_class(T)
#		endif
#	endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_compound)
#			define KERBAL_IS_COMPOUND(T) __is_compound(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_const)
#			define KERBAL_IS_CONST(T) __is_const(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_convertible)
#			define KERBAL_IS_CONVERTIBLE(FROM, TO) __is_convertible(FROM, TO)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_convertible)
#			define KERBAL_IS_CONVERTIBLE(FROM, TO) __is_convertible(FROM, TO)
#		endif

#	ifndef KERBAL_HAS_IS_EMPTY_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_empty)
#			define KERBAL_IS_EMPTY(T) __is_empty(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_empty)
#			define KERBAL_IS_EMPTY(T) __is_empty(T)
#		endif
#	endif

#	ifndef KERBAL_HAS_IS_ENUM_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_enum)
#			define KERBAL_IS_ENUM(T) __is_enum(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_enum)
#			define KERBAL_IS_ENUM(T) __is_enum(T)
#		endif
#	endif

#	ifndef KERBAL_HAS_IS_FINAL_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_final)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_final) // >= 3.1
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		endif
#	endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_function)
#			define KERBAL_IS_FUNCTION(T) __is_function(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_fundamenta)
#			define KERBAL_IS_FUNDAMENTA(T) __is_fundamenta(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_integral)
#			define KERBAL_IS_INTEGRAL(T) __is_integral(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_pointer)
#			define KERBAL_IS_POINTER(T) __is_pointer(T)
#		endif

#	ifndef KERBAL_HAS_IS_POLYMORPHIC_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_polymorphic)
#			define KERBAL_IS_POLYMORPHIC(T) __is_polymorphic(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_polymorphic)
#			define KERBAL_IS_POLYMORPHIC(T) __is_polymorphic(T)
#		endif
#	endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_reference)
#			define KERBAL_IS_REFERENCE(T) __is_reference(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_rvalue_reference)
#			define KERBAL_IS_RVALUE_REFERENCE(T) __is_rvalue_reference(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_scalar)
#			define KERBAL_IS_SCALAR(T) __is_scalar(T)
#		endif

#	ifndef KERBAL_HAS_IS_STANDARD_LAYOUT_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_standard_layout)
#			define KERBAL_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_standard_layout)
#			define KERBAL_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#		endif
#	endif

#	ifndef KERBAL_HAS_IS_UNION_SUPPORT
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_union)
#			define KERBAL_IS_UNION(T) __is_union(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_union)
#			define KERBAL_IS_UNION(T) __is_union(T)
#		endif
#	endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_volatile)
#			define KERBAL_IS_VOLATILE(T) __is_volatile(T)
#		endif



#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_assignable)
#			define KERBAL_IS_NOTHROW_ASSIGNABLE(T, U) __is_nothrow_assignable(T, U)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_assignable)
#			define KERBAL_IS_TRIVIALLY_ASSIGNABLE(T, U) __is_trivially_assignable(T, U)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivially_assignable)
#			define KERBAL_IS_TRIVIALLY_ASSIGNABLE(T, U) __is_trivially_assignable(T, U)
#		endif



#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_constructible)
#			define KERBAL_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_constructible)
#			define KERBAL_IS_TRIVIALLY_CONSTRUCTIBLE(...) __is_trivially_constructible(__VA_ARGS__)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivially_constructible)
#			define KERBAL_IS_TRIVIALLY_CONSTRUCTIBLE(...) __is_trivially_constructible(__VA_ARGS__)
#		endif



#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_destructible)
#			define KERBAL_IS_NOTHROW_DESTRUCTIBLE(T) __is_nothrow_destructible(T)
#		endif

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_constructible)
#			define KERBAL_IS_TRIVIALLY_DESTRUCTIBLE(T) __is_trivially_destructible(T)
#		endif



#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivial)
#			define KERBAL_IS_TRIVIAL(T) __is_trivial(T)
#		endif



#endif // KERBAL_TYPE_TRAITSCOMPILER_INTRINSICS__1_CLANG_HPP
