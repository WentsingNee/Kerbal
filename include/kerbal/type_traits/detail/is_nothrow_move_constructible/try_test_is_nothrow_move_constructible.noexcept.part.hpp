/**
 * @file       try_test_is_nothrow_move_constructible.noexcept.part.hpp
 * @brief
 * @date       2024-01-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP

#include <kerbal/type_traits/is_move_constructible.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_nothrow_move_constructible :
				kerbal::type_traits::try_test_is_move_constructible<T>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP
