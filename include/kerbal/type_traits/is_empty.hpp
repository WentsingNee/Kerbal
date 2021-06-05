/**
 * @file       is_empty.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_EMPTY_HPP
#define KERBAL_TYPE_TRAITS_IS_EMPTY_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#ifndef KERBAL_HAS_IS_EMPTY_SUPPORT

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU



#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG



#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/ms177194(v=vs.90)
//		https://www.cnblogs.com/yamboo/p/14030418.html
#		if KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
#			define KERBAL_IS_EMPTY(T) __is_empty(T)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_empty)
#			define KERBAL_IS_EMPTY(T) __is_empty(T)
#		endif

#	endif


#	if !defined(KERBAL_IS_EMPTY)
#		if __cplusplus >= 201103L
#			include <type_traits>
#			define KERBAL_IS_EMPTY(T) std::is_empty<T>::value

#			if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#				pragma message ("Kerbal Warning: " "can not detect the builtin is_empty function, <type_traits> header has been included")
#			else
#				warning "Kerbal Warning: " "can not detect the built-in is_empty function, <type_traits> header has been included"
#			endif
#		endif
#	endif


#	ifdef KERBAL_IS_EMPTY
#		define KERBAL_HAS_IS_EMPTY_SUPPORT 1
#	else
#		define KERBAL_HAS_IS_EMPTY_SUPPORT 0

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "KERBAL_IS_EMPTY is not supported")
#		else
#			warning "Kerbal Warning: " "KERBAL_IS_EMPTY is not supported"
#		endif
#	endif

#endif // KERBAL_HAS_IS_EMPTY_SUPPORT



#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

#	if KERBAL_HAS_IS_EMPTY_SUPPORT

		template <typename Tp>
		struct is_empty : kerbal::type_traits::bool_constant<KERBAL_IS_EMPTY(Tp)>
		{
		};

#	endif // KERBAL_HAS_IS_EMPTY_SUPPORT

		namespace detail
		{

#	if KERBAL_HAS_IS_EMPTY_SUPPORT

			template <typename Tp>
			struct test_is_empty_cv_unrelated : kerbal::type_traits::is_empty<Tp>
			{
			};

#	else

			template <typename Tp>
			struct test_is_empty_cv_unrelated : kerbal::type_traits::false_type
			{
			};

#	endif // KERBAL_HAS_IS_EMPTY_SUPPORT

		} // namespace detail


		template <typename Tp>
		struct test_is_empty :
				detail::test_is_empty_cv_unrelated<
					typename kerbal::type_traits::remove_cv<Tp>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_EMPTY_HPP
