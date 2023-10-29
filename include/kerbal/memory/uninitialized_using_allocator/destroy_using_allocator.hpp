/**
 * @file       destroy_using_allocator.hpp
 * @brief
 * @date       2021-08-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_USING_ALLOCATOR_HPP
#define KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_USING_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits/destroy.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/memory/uninitialized_using_allocator/destroy_on_using_allocator.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void k_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				while (first != last) {
					kerbal::memory::destroy_on_using_allocator(alloc, *first);
					++first;
				}
			}

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void k_destroy_using_allocator(Allocator & /*alloc*/, ForwardIterator first, ForwardIterator last, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy(first, last);
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::memory::detail::k_destroy_using_allocator(alloc, first, last, kerbal::memory::allocator_could_use_destroy<Allocator, value_type>());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_USING_ALLOCATOR_HPP
