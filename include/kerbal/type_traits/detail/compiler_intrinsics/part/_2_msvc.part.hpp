/**
 * @file       _2_msvc.part.hpp
 * @brief
 * @date       2021-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__2_MSVC_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__2_MSVC_PART_HPP

#include <kerbal/config/compiler_private.hpp>


//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/ms177194(v=vs.90)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/ms177194(v=vs.100)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/ms177194(v=vs.110)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2013/ms177194(v=vs.120)
//		https://www.cnblogs.com/yamboo/p/14030418.html


#	if KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)

#		ifndef KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT
#			define KERBAL_INTRINSIC_IS_ABSTRACT(T)					__is_abstract(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_ABSTRACT
#			define KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT
#			define KERBAL_INTRINSIC_IS_BASE_OF(BASE, DERIVED)			__is_base_of(BASE, DERIVED)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_BASE_OF
#			define KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT
#			define KERBAL_INTRINSIC_IS_CLASS(T)						__is_class(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_CLASS
#			define KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT 1
#		endif



#		if KERBAL_HAS_INTRINSIC_IS_CONVERTIBLE_SUPPORT
#			define KERBAL_INTRINSIC_IS_CONVERTIBLE(FROM, TO)			__is_convertible_to(FROM, TO)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_CONVERTIBLE
#			define KERBAL_HAS_INTRINSIC_IS_CONVERTIBLE_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT
#			define KERBAL_INTRINSIC_IS_EMPTY(T)						__is_empty(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_EMPTY
#			define KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT
#			define KERBAL_INTRINSIC_IS_ENUM(T)						__is_enum(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_ENUM
#			define KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT
#			define KERBAL_INTRINSIC_IS_POLYMORPHIC(T)					__is_polymorphic(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_POLYMORPHIC
#			define KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT 1
#		endif



#		ifndef KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT
#			define KERBAL_INTRINSIC_IS_UNION(T)						__is_union(T)
#		endif

#		ifdef KERBAL_INTRINSIC_IS_UNION
#			define KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT 1
#		endif

#	endif // KERBAL_MSVC_VERSION_MEETS(15, 0, 0)




#	ifndef KERBAL_HAS_INTRINSIC_IS_CONSTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_CONSTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_CONSTRUCTIBLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_ASSIGNABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_ASSIGNABLE(To, From) __is_assignable(To, From)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_ASSIGNABLE
#		define KERBAL_HAS_INTRINSIC_IS_ASSIGNABLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_DESTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_DESTRUCTIBLE(T) __is_destructible(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_DESTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_DESTRUCTIBLE_SUPPORT 1
#	endif



#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T) __is_trivially_destructible(T)
#		elif KERBAL_MSVC_VERSION_MEETS(17, 0, 0) // (Visual Studio 2012)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T) __has_trivial_destructor(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(...) __is_trivially_constructible(__VA_ARGS__)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(17, 0, 0) // (Visual Studio 2012)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T) __has_trivial_move_constructor(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(To, From) __is_trivially_assignable(To, From)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPY_ASSIGNABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(17, 0, 0) // (Visual Studio 2012)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_COPY_ASSIGNABLE(T) __has_trivial_assign(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_COPY_ASSIGNABLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPY_ASSIGNABLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_MOVE_ASSIGNABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(17, 0, 0) // (Visual Studio 2012)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_MOVE_ASSIGNABLE(T) __has_trivial_move_assign(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_MOVE_ASSIGNABLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_MOVE_ASSIGNABLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIAL_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_TRIVIAL(T) __is_trivial(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIAL
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIAL_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_TRIVIALLY_COPYABLE(T) __is_trivially_copyable(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_COPYABLE
#		define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE_SUPPORT 1
#	endif




#	ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_NOTHROW_ASSIGNABLE(To, From) __is_nothrow_assignable(To, From)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_NOTHROW_ASSIGNABLE
#		define KERBAL_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE(T) __is_nothrow_destructible(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE
#		define KERBAL_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE_SUPPORT 1
#	endif



#	ifndef KERBAL_HAS_INTRINSIC_IS_POD_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_POD(T) __is_pod(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_POD
#		define KERBAL_HAS_INTRINSIC_IS_POD_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#		define KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR
#		define KERBAL_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS(T) __has_unique_object_representations(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS
#		define KERBAL_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_UNDERLYING_TYPE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_UNDERLYING_TYPE(T) __underlying_type(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_UNDERLYING_TYPE
#		define KERBAL_HAS_INTRINSIC_UNDERLYING_TYPE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_LITERAL_TYPE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 16, 27049) // (Visual Studio 2017)
#			define KERBAL_INTRINSIC_IS_LITERAL_TYPE(T) __is_literal_type(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_LITERAL_TYPE
#		define KERBAL_HAS_INTRINSIC_IS_LITERAL_TYPE_SUPPORT 1
#	endif


#	ifndef KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
#			define KERBAL_INTRINSIC_IS_FINAL(T) __is_final(T)
//#		elif KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
//#			define KERBAL_INTRINSIC_IS_FINAL(T) __is_sealed(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_FINAL
#		define KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT 1
#	endif



#	ifndef KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 15, 26726) // MSVC++ 19.15
#			define KERBAL_INTRINSIC_IS_AGGREGATE(T) __is_aggregate(T)
#		endif
#	endif

#	ifdef KERBAL_INTRINSIC_IS_AGGREGATE
#		define KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT 1
#	endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__2_MSVC_PART_HPP
