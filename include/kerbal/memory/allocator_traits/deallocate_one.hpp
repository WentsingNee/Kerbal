/**
 * @file       deallocate_one.hpp
 * @brief
 * @date       2023-08-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_DEALLOCATE_ONE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_DEALLOCATE_ONE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
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

		template <typename Alloc, typename Pointer, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_deallocate_one :
			kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename Pointer>
		struct allocator_has_deallocate_one<
			Alloc, Pointer,
			typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
				decltype(
					kerbal::utility::declval<Alloc &>().deallocate_one(
						kerbal::utility::declval<Pointer>()
					)
				)
#	else
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<Alloc &>().deallocate_one(
							kerbal::utility::declval<Pointer>()
						),
						0
					)
				>
#	endif
			>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <
				typename Alloc,
				typename Pointer,
				bool = kerbal::memory::allocator_has_deallocate_one<Alloc, Pointer>::value
			>
			struct allocator_traits_deallocate_one_helper;

			template <typename Alloc, typename Pointer>
			struct allocator_traits_deallocate_one_helper<Alloc, Pointer, false>
			{
				public:
					KERBAL_CONSTEXPR14
					static
					void deallocate_one(Alloc & alloc, Pointer p)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(alloc.deallocate(p, 1))
						)
					{
						alloc.deallocate(p, 1);
					}
			};

			template <typename Alloc, typename Pointer>
			struct allocator_traits_deallocate_one_helper<Alloc, Pointer, true>
			{
				public:
					KERBAL_CONSTEXPR14
					static
					void deallocate_one(Alloc & alloc, Pointer p)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(alloc.deallocate_one(p))
						)
					{
						alloc.deallocate_one(p);
					}
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_DEALLOCATE_ONE_HPP
