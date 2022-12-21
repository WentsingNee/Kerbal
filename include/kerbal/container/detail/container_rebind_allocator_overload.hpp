/**
 * @file       container_rebind_allocator_overload.hpp
 * @brief
 * @date       2022-03-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_CONTAINER_REBIND_ALLOCATOR_OVERLOAD_HPP
#define KERBAL_CONTAINER_DETAIL_CONTAINER_REBIND_ALLOCATOR_OVERLOAD_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Allocator, typename Up>
			struct container_rebind_allocator_overload_helper
			{
				public:
					typedef kerbal::memory::allocator_traits<Allocator>								original_allocator_traits;
					typedef typename original_allocator_traits::template rebind_alloc<Up>::other	rebind_allocator_type;
					typedef typename original_allocator_traits::template rebind_traits<Up>::other	rebind_allocator_traits;
			};


			template <typename Allocator, typename Up>
			class container_rebind_allocator_overload:
					private kerbal::utility::member_compress_helper<
							typename container_rebind_allocator_overload_helper<Allocator, Up>::rebind_allocator_type
					>
			{
				private:
					typedef kerbal::utility::member_compress_helper<
							typename container_rebind_allocator_overload_helper<Allocator, Up>::rebind_allocator_type
					> super;

				private:
					typedef container_rebind_allocator_overload_helper<Allocator, Up>	helper;

				protected:
					typedef typename helper::original_allocator_traits	original_allocator_traits;
					typedef typename helper::rebind_allocator_type		rebind_allocator_type;
					typedef typename helper::rebind_allocator_traits	rebind_allocator_traits;

				protected:

#			if __cplusplus >= 201103L

					struct is_nothrow_default_constructible :
							kerbal::type_traits::integral_constant<
								bool,
								std::is_nothrow_constructible<super, kerbal::utility::in_place_t>::value
							>
					{
					};

#			endif

					KERBAL_CONSTEXPR
					container_rebind_allocator_overload()
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_default_constructible::value)
							: super(kerbal::utility::in_place_t())
					{
					}

#			if __cplusplus >= 201103L

					struct is_nothrow_constructible_from_allocator_const_reference :
							kerbal::type_traits::integral_constant<
								bool,
								std::is_nothrow_constructible<super, kerbal::utility::in_place_t, const Allocator &>::value
							>
					{
					};

#			endif

					KERBAL_CONSTEXPR
					explicit
					container_rebind_allocator_overload(const Allocator & allocator)
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_constructible_from_allocator_const_reference::value)
							: super(kerbal::utility::in_place_t(), allocator)
					{
					}


#			if __cplusplus >= 201103L

					struct is_nothrow_constructible_from_allocator_rvalue_reference :
							kerbal::type_traits::integral_constant<
								bool,
								std::is_nothrow_constructible<super, kerbal::utility::in_place_t, Allocator &&>::value
							>
					{
					};

					KERBAL_CONSTEXPR
					explicit
					container_rebind_allocator_overload(Allocator && allocator)
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_constructible_from_allocator_rvalue_reference::value)
							: super(kerbal::utility::in_place_t(), kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					rebind_allocator_type & alloc() KERBAL_NOEXCEPT
					{
						return super::member();
					}

					KERBAL_CONSTEXPR
					const rebind_allocator_type & alloc() const KERBAL_NOEXCEPT
					{
						return super::member();
					}

				private:

					KERBAL_CONSTEXPR14
					static void k_swap_allocator_if_propagate_impl(container_rebind_allocator_overload & /*lhs*/, container_rebind_allocator_overload & /*rhs*/,
																	kerbal::type_traits::false_type /*propagate_on_container_swap*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR14
					static void k_swap_allocator_if_propagate_impl(container_rebind_allocator_overload & lhs, container_rebind_allocator_overload & rhs,
																	kerbal::type_traits::true_type /*propagate_on_container_swap*/)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::algorithm::swap(lhs.alloc(), rhs.alloc()))
							)
					{
						kerbal::algorithm::swap(lhs.alloc(), rhs.alloc());
					}

				public:

					KERBAL_CONSTEXPR14
					static void k_swap_allocator_if_propagate(container_rebind_allocator_overload & lhs, container_rebind_allocator_overload & rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(k_swap_allocator_if_propagate_impl(lhs, rhs, typename rebind_allocator_traits::propagate_on_container_swap()))
							)
					{
						typedef typename rebind_allocator_traits::propagate_on_container_swap propagate_on_container_swap;
						k_swap_allocator_if_propagate_impl(lhs, rhs, propagate_on_container_swap());
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_CONTAINER_REBIND_ALLOCATOR_OVERLOAD_HPP
