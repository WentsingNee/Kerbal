/**
 * @file       reallocate.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_REALLOCATE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_REALLOCATE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits/pointer_type.hpp>
#include <kerbal/memory/allocator_traits/size_type.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename T, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_reallocate: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_has_reallocate<Alloc, T, typename kerbal::type_traits::void_type<
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<Alloc&>().reallocate(
							kerbal::utility::declval<T*>(),
							kerbal::utility::declval<typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type>(),
							kerbal::utility::declval<typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type>()
						),
						0
					)
				>
		>::type >: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_reallocate<Alloc, typename Alloc::value_type>::value>
			struct allocator_traits_reallocate_helper;

			template <typename Alloc>
			struct allocator_traits_reallocate_helper<Alloc, false>
			{
			};

			template <typename Alloc>
			struct allocator_traits_reallocate_helper<Alloc, true>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type		pointer;
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type		size_type;

				public:
					KERBAL_CONSTEXPR14
					static pointer reallocate(Alloc & alloc, pointer p, size_type ori_size, size_type new_size)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(alloc.reallocate(p, ori_size, new_size))
							)
					{
						return alloc.reallocate(p, ori_size, new_size);
					}
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_REALLOCATE_HPP
