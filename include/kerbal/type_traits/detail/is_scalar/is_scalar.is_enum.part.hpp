/**
 * @file       is_scalar.is_enum.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_IS_SCALAR_IS_ENUM_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_IS_SCALAR_IS_ENUM_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_SCALAR

#include <kerbal/type_traits/detail/is_enum/is_enum.part.hpp>

#if KERBAL_SUPPORTS_IS_ENUM
#	define KERBAL_SUPPORTS_IS_SCALAR 1
#endif



#if KERBAL_SUPPORTS_IS_SCALAR

#include <kerbal/type_traits/is_arithmetic.hpp>
#include <kerbal/type_traits/is_enum.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/logical.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_null_pointer.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_scalar :
			kerbal::type_traits::disjunction<
#		if __cplusplus >= 201103L
				kerbal::type_traits::is_null_pointer<T>,
#		endif
				kerbal::type_traits::is_arithmetic<T>,
				kerbal::type_traits::is_enum<T>,
				kerbal::type_traits::is_member_pointer<T>,
				kerbal::type_traits::is_pointer<T>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_SCALAR

#endif // #ifndef KERBAL_SUPPORTS_IS_SCALAR

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_IS_SCALAR_IS_ENUM_PART_HPP
