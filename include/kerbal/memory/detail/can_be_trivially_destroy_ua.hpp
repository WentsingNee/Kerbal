/**
 * @file       can_be_trivially_destroy_ua.hpp
 * @brief
 * @date       2022-03-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DETAIL_CAN_BE_TRIVIALLY_DESTROY_UA_HPP
#define KERBAL_MEMORY_DETAIL_CAN_BE_TRIVIALLY_DESTROY_UA_HPP

#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename T, typename Allocator>
			struct can_be_trivially_destroy_ua :
					kerbal::type_traits::conditional<
						kerbal::memory::allocator_could_use_destroy<Allocator, T>::value,
						kerbal::type_traits::false_type,
						kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<T>
						>
					>::type
			{
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DETAIL_CAN_BE_TRIVIALLY_DESTROY_UA_HPP
