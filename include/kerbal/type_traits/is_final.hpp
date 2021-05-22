/**
 * @file       is_final.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_FINAL_HPP
#define KERBAL_TYPE_TRAITS_IS_FINAL_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#ifndef KERBAL_HAS_IS_FINAL_SUPPORT

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if KERBAL_GNU_VERSION_MEETS(4, 7, 1) // There is no official document to describe `__is_final`, just testing result
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		elif KERBAL_GNU_PRIVATE_HAS_BUILTIN(__is_final)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

//		https://clang.llvm.org/docs/LanguageExtensions.html#type-trait-primitives
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_final)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_final) // >= 3.1
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

//		https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/ms177194(v=vs.90)
//		https://www.cnblogs.com/yamboo/p/14030418.html
#		if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		if KERBAL_MSVC_VERSION_MEETS(15, 0, 0) // MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
#			define KERBAL_IS_FINAL(T) __is_sealed(T)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if KERBAL_ICC_PRIVATE_HAS_FEATURE(is_final)
#			define KERBAL_IS_FINAL(T) __is_final(T)
#		endif

#	endif


#	if !defined(KERBAL_IS_FINAL)
#		if __cplusplus >= 201103L
#			include <type_traits>
#			define KERBAL_IS_FINAL(T) std::is_final<T>::value

#			if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#				pragma message ("Kerbal Warning: " "can not detect the builtin is_final function, <type_traits> header has been included")
#			else
#				warning "Kerbal Warning: " "can not detect the built-in is_final function, <type_traits> header has been included"
#			endif
#		endif
#	endif


#	ifdef KERBAL_IS_FINAL
#		define KERBAL_HAS_IS_FINAL_SUPPORT 1
#	else
#		define KERBAL_HAS_IS_FINAL_SUPPORT 0

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "KERBAL_IS_FINAL is not supported")
#		else
#			warning "Kerbal Warning: " "KERBAL_IS_FINAL is not supported"
#		endif
#	endif

#endif // KERBAL_HAS_IS_FINAL_SUPPORT



#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

#	if KERBAL_HAS_IS_FINAL_SUPPORT

		template <typename Tp>
		struct is_final : kerbal::type_traits::bool_constant<KERBAL_IS_FINAL(Tp)>
		{
		};

#	endif // KERBAL_HAS_IS_FINAL_SUPPORT

		namespace detail
		{

#	if KERBAL_HAS_IS_FINAL_SUPPORT

			template <typename Tp>
			struct test_is_final_cv_unrelated : kerbal::type_traits::is_final<Tp>
			{
			};

#	else

			template <typename Tp>
			struct test_is_final_cv_unrelated : kerbal::type_traits::false_type
			{
			};

#	endif // KERBAL_HAS_IS_FINAL_SUPPORT

		} // namespace detail


		template <typename Tp>
		struct test_is_final :
				detail::test_is_final_cv_unrelated<
					typename kerbal::type_traits::remove_cv<Tp>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_FINAL_HPP
