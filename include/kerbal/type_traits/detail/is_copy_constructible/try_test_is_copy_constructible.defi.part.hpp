/**
 * @file       try_test_is_copy_constructible.defi.part.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_DEFI_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_DEFI_PART_HPP

#include <kerbal/type_traits/detail/is_copy_constructible/is_copy_constructible.part.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_copy_constructible :
			kerbal::type_traits::tribool_constant<
				!!kerbal::type_traits::is_copy_constructible<T>::value
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_DEFI_PART_HPP
