/**
 * @file       allow_deallocate_null.hpp
 * @brief
 * @date       2023-06-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOW_DEALLOCATE_NULL_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOW_DEALLOCATE_NULL_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_allow_deallocate_null :
			kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_allow_deallocate_null<
			Alloc,
			typename kerbal::type_traits::void_type<typename Alloc::allow_deallocate_null>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <
				typename Alloc,
				bool = kerbal::memory::allocator_has_def_allow_deallocate_null<Alloc>::value
			>
			struct allocator_allow_deallocate_null_traits_helper :
				kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_allow_deallocate_null_traits_helper<Alloc, true> :
				kerbal::type_traits::bool_constant<
					Alloc::allow_deallocate_null::value
				>
			{
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOW_DEALLOCATE_NULL_HPP
