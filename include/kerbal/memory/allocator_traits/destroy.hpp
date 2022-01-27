/**
 * @file       destroy.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_DESTROY_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_DESTROY_HPP

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_destructible.hpp>
#	include <kerbal/type_traits/tribool_constant.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename T, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_destroy: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_has_destroy<Alloc, T, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
				decltype(
					kerbal::utility::declval<Alloc&>().destroy(
							kerbal::utility::declval<T*>()
					)
				)
#	else
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<Alloc&>().destroy(
							kerbal::utility::declval<T*>()
						),
						0
					)
				>
#	endif
		>::type >: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_could_use_destroy : kerbal::memory::allocator_has_destroy<Alloc, T>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T, typename U>
		struct allocator_could_use_destroy<std::allocator<T>, U>: kerbal::type_traits::false_type
		{
		};

#	endif

#	if __cplusplus > 201703L

		template <typename T, typename U>
		struct allocator_could_use_destroy<std::pmr::polymorphic_allocator<T>, U>: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc>
			struct allocator_traits_destroy_helper
			{

				private:
					template <typename T>
					KERBAL_CONSTEXPR20
					static void k_destroy(kerbal::type_traits::false_type, Alloc &, T * p)
							KERBAL_CONDITIONAL_NOEXCEPT(
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::try_test_is_nothrow_destructible<T>
								>::value
							)
					{
						kerbal::memory::destroy_at(p);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static void k_destroy(kerbal::type_traits::true_type, Alloc & alloc, T * p)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(alloc.destroy(p))
							)
					{
						alloc.destroy(p);
					}

				public:
					template <typename T>
					KERBAL_CONSTEXPR14
					static void destroy(Alloc & alloc, T * p)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(k_destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p))
							)
					{
						k_destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p);
					}

			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_DESTROY_HPP
