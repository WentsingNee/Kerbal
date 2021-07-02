/**
 * @file       _2_msvc.hpp
 * @brief
 * @date       2021-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__2_MSVC_HPP
#define KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__2_MSVC_HPP

#include <kerbal/config/compiler_private.hpp>


//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/ms177194(v=vs.90)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/ms177194(v=vs.100)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/ms177194(v=vs.110)
//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2013/ms177194(v=vs.120)
//		https://www.cnblogs.com/yamboo/p/14030418.html


#	if KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)

#		ifndef KERBAL_HAS_IS_ABSTRACT_SUPPORT
#			define KERBAL_IS_ABSTRACT(T)					__is_abstract(T)
#		endif

#		ifndef KERBAL_HAS_IS_BASE_OF_SUPPORT
#			define KERBAL_IS_BASE_OF(BASE, DERIVED)			__is_base_of(BASE, DERIVED)
#		endif

#		ifndef KERBAL_HAS_IS_CLASS_SUPPORT
#			define KERBAL_IS_CLASS(T)						__is_class(T)
#		endif

#			define KERBAL_IS_CONVERTIBLE(FROM, TO)			__is_convertible_to(FROM, TO)

#		ifndef KERBAL_HAS_IS_EMPTY_SUPPORT
#			define KERBAL_IS_EMPTY(T)						__is_empty(T)
#		endif

#		ifndef KERBAL_HAS_IS_ENUM_SUPPORT
#			define KERBAL_IS_ENUM(T)						__is_enum(T)
#		endif

#		ifndef KERBAL_HAS_IS_POLYMORPHIC_SUPPORT
#			define KERBAL_IS_POLYMORPHIC(T)					__is_polymorphic(T)
#		endif

#		ifndef KERBAL_HAS_IS_UNION_SUPPORT
#			define KERBAL_IS_UNION(T)						__is_union(T)
#		endif

#	endif


#	ifndef KERBAL_HAS_IS_FINAL_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
#			define KERBAL_IS_FINAL(T) __is_final(T)
//#		elif KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
//#			define KERBAL_IS_FINAL(T) __is_sealed(T)
#		endif
#	endif


#	ifndef KERBAL_HAS_IS_AGGREGATE_SUPPORT
#		if KERBAL_MSVC_VERSION_MEETS(19, 15, 26726) // MSVC++ 19.15
#			define KERBAL_IS_AGGREGATE(T) __is_aggregate(T)
#		endif
#	endif


#endif // KERBAL_TYPE_TRAITS_COMPILER_INTRINSICS__2_MSVC_HPP
