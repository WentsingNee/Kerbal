/**
 * @file       is_trivially_copy_constructible.istric.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_ISTRIC_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_ISTRIC_PART_HPP

#ifndef KERBAL_HAS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/detail/is_trivially_constructible/is_trivially_constructible.part.hpp>

#if KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT
#	define KERBAL_HAS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/is_trivially_constructible.hpp>
#include <kerbal/type_traits/logical.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_copy_constructible :
			kerbal::type_traits::conditional<
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_array<T>,
					kerbal::type_traits::is_function<T>
				>::value,
				kerbal::type_traits::false_type,
				kerbal::type_traits::is_trivially_constructible<
					T,
					typename kerbal::type_traits::add_const_lvalue_reference<T>::type
				>
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_ISTRIC_PART_HPP
