/**
 * @file       try_test_is_trivially_assignable.defi.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_ASSIGNABLE_DEFI_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_ASSIGNABLE_DEFI_PART_HPP

#include <kerbal/type_traits/detail/is_trivially_assignable/is_trivially_assignable.part.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T, typename U>
		struct try_test_is_trivially_assignable :
				kerbal::type_traits::tribool_constant<
					!!kerbal::type_traits::is_trivially_assignable<T, U>::value
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_ASSIGNABLE_DEFI_PART_HPP
