/**
 * @file       is_scalar.hpp
 * @brief
 * @date       2021-05-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_SCALAR_HPP
#define KERBAL_TYPE_TRAITS_IS_SCALAR_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

//		https://clang.llvm.org/docs/LanguageExtensions.html#type-trait-primitives
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_scalar)

#		define KERBAL_HAS_IS_SCALAR_SUPPORT 1

		template <typename Tp>
		struct is_scalar :
				kerbal::type_traits::bool_constant<
					__is_scalar(Tp)
				>
		{
		};

#	endif

#endif



#if !defined(KERBAL_HAS_IS_SCALAR_SUPPORT)

#include <kerbal/type_traits/is_enum.hpp>

#	if KERBAL_HAS_IS_ENUM_SUPPORT

#include <kerbal/type_traits/pointer_deduction.hpp>
#include <kerbal/type_traits/member_pointer_deduction.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>

#		define KERBAL_HAS_IS_SCALAR_SUPPORT 1

		template <typename Tp>
		struct is_scalar :
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_arithmetic<Tp>::value ||
					kerbal::type_traits::is_enum<Tp>::value ||
					kerbal::type_traits::is_pointer<Tp>::value ||
					kerbal::type_traits::is_member_pointer<Tp>::value ||
					kerbal::type_traits::is_null_pointer<Tp>::value
				>
		{
		};

#	else

#		define KERBAL_HAS_IS_SCALAR_SUPPORT 0

#	endif // KERBAL_HAS_IS_ENUM_SUPPORT

#endif // KERBAL_HAS_IS_SCALAR_SUPPORT


	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_SCALAR_HPP
