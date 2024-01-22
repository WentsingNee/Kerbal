/**
 * @file       allocate_one.hpp
 * @brief
 * @date       2023-06-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOCATE_ONE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOCATE_ONE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits/pointer_type.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <cstddef>
#endif


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_allocate_one: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_allocate_one<Alloc, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
				decltype(
					kerbal::utility::declval<Alloc&>().allocate_one()
				)
#	else
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<Alloc&>().allocate_one(),
						0
					)
				>
#	endif
		>::type >: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_allocate_one<Alloc>::value>
			struct allocator_traits_allocate_one_helper;

			template <typename Alloc>
			struct allocator_traits_allocate_one_helper<Alloc, false>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type		pointer;

				public:
					KERBAL_CONSTEXPR14
					static pointer allocate_one(Alloc & alloc)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(alloc.allocate(1))
							)
					{
						return alloc.allocate(1);
					}
			};

			template <typename Alloc>
			struct allocator_traits_allocate_one_helper<Alloc, true>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type		pointer;

				public:
					KERBAL_CONSTEXPR14
					static pointer allocate_one(Alloc & alloc)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(alloc.allocate_one())
							)
					{
						return alloc.allocate_one();
					}
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_ALLOCATE_ONE_HPP
