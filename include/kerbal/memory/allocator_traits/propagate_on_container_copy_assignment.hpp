/**
 * @file       propagate_on_container_copy_assignment.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_propagate_on_container_copy_assignment: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_propagate_on_container_copy_assignment<
				Alloc,
				typename kerbal::type_traits::void_type<typename Alloc::propagate_on_container_copy_assignment>::type
		> :
				kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_propagate_on_container_copy_assignment<Alloc>::value>
			struct allocator_propagate_on_container_copy_assignment_traits_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_propagate_on_container_copy_assignment_traits_helper<Alloc, true> :
					kerbal::type_traits::bool_constant<
						Alloc::propagate_on_container_copy_assignment::value
					>
			{
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_HPP
