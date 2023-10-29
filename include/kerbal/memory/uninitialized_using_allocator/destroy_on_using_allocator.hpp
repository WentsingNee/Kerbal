/**
 * @file       destroy_on_using_allocator.hpp
 * @brief
 * @date       2023-10-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_ON_USING_ALLOCATOR_HPP
#define KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_ON_USING_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits/destroy.hpp>
#include <kerbal/memory/uninitialized/destroy_on.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Allocator, typename T>
			KERBAL_CONSTEXPR14
			void k_destroy_on_using_allocator(Allocator & alloc, T & plc, kerbal::type_traits::true_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::memory::allocator_traits<Allocator>::destroy(alloc, &plc))
					)
			{
				kerbal::memory::allocator_traits<Allocator>::destroy(alloc, &plc);
			}

			template <typename Allocator, typename T>
			KERBAL_CONSTEXPR14
			void k_destroy_on_using_allocator(Allocator & /*alloc*/, T & plc, kerbal::type_traits::false_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::memory::destroy_on(plc))
					)
			{
				kerbal::memory::destroy_on(plc);
			}

		} // namespace detail

		template <typename Allocator, typename T>
		KERBAL_CONSTEXPR14
		void destroy_on_using_allocator(Allocator & alloc, T & plc)
		{
			kerbal::memory::detail::k_destroy_on_using_allocator(alloc, plc, kerbal::memory::allocator_could_use_destroy<Allocator, T>());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_ON_USING_ALLOCATOR_HPP
