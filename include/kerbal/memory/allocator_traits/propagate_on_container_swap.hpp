/**
 * @file       propagate_on_container_swap.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_SWAP_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_SWAP_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_propagate_on_container_swap :
			kerbal::type_traits::false_type
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <typename Alloc>
		struct allocator_has_def_propagate_on_container_swap<
			Alloc,
			typename kerbal::type_traits::void_type<
				typename Alloc::propagate_on_container_swap
			>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <
				typename Alloc,
				bool = kerbal::memory::allocator_has_def_propagate_on_container_swap<Alloc>::value
			>
			struct allocator_propagate_on_container_swap_traits_helper :
				kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_propagate_on_container_swap_traits_helper<Alloc, true> :
				kerbal::type_traits::bool_constant<
					Alloc::propagate_on_container_swap::value
				>
			{
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_SWAP_HPP
