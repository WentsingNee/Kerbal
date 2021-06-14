/**
 * @file       is_class.hpp
 * @brief
 * @date       2020-07-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_CLASS_HPP
#define KERBAL_TYPE_TRAITS_IS_CLASS_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#ifndef KERBAL_HAS_IS_CLASS_SUPPORT

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU



#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG



#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC


#	endif


#	if !defined(KERBAL_IS_CLASS)
#		if __cplusplus >= 201103L
#			include <type_traits>
#			define KERBAL_IS_CLASS(T) std::is_class<T>::value

#			if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#				pragma message ("Kerbal Warning: " "can not detect the builtin is_class function, <type_traits> header has been included")
#			else
#				warning "Kerbal Warning: " "can not detect the built-in is_class function, <type_traits> header has been included"
#			endif
#		endif
#	endif


#	ifdef KERBAL_IS_CLASS
#		define KERBAL_HAS_IS_CLASS_SUPPORT 1
#	else
#		define KERBAL_HAS_IS_CLASS_SUPPORT 0

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "KERBAL_IS_CLASS is not supported")
#		else
#			warning "Kerbal Warning: " "KERBAL_IS_CLASS is not supported"
#		endif
#	endif

#endif // KERBAL_HAS_IS_CLASS_SUPPORT



#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

#	if KERBAL_HAS_IS_CLASS_SUPPORT

		template <typename Tp>
		struct is_class : kerbal::type_traits::bool_constant<KERBAL_IS_CLASS(Tp)>
		{
		};

#	endif // KERBAL_HAS_IS_CLASS_SUPPORT

		namespace detail
		{

#	if KERBAL_HAS_IS_CLASS_SUPPORT

			template <typename Tp>
			struct test_is_class_cv_unrelated : kerbal::type_traits::is_class<Tp>
			{
			};

#	else

			template <typename Tp>
			struct test_is_class_cv_unrelated : kerbal::type_traits::false_type
			{
			};

#	endif // KERBAL_HAS_IS_CLASS_SUPPORT

		} // namespace detail


		template <typename Tp>
		struct test_is_class :
				detail::test_is_class_cv_unrelated<
					typename kerbal::type_traits::remove_cv<Tp>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_CLASS_HPP
