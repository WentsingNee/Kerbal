/**
 * @file       size_type.hpp
 * @brief
 * @date       2022-01-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_SIZE_TYPE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_SIZE_TYPE_HPP

#include <kerbal/memory/allocator_traits/pointer_type.hpp>
#include <kerbal/memory/pointer_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_size_type :
			kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_size_type<
			Alloc,
			typename kerbal::type_traits::void_type<typename Alloc::size_type>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_size_type<Alloc>::value>
			struct allocator_size_type_traits_helper
			{
				private:
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type pointer;
					typedef typename kerbal::memory::pointer_traits<pointer>::difference_type difference_type;

				public:
					typedef typename kerbal::type_traits::make_unsigned<difference_type>::type type;
			};

			template <typename Alloc>
			struct allocator_size_type_traits_helper<Alloc, true>
			{
					typedef typename Alloc::size_type type;
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_SIZE_TYPE_HPP
