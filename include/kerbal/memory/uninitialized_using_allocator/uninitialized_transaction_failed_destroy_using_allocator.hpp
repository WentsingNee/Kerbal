/**
 * @file       uninitialized_transaction_failed_destroy_using_allocator.hpp
 * @brief
 * @date       2023-10-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_USING_ALLOCATOR_HPP
#define KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_USING_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator/destroy_using_allocator.hpp>
#include <kerbal/memory/uninitialized_using_allocator/reverse_destroy_using_allocator.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy_using_allocator(alloc, first, last);
			}

			template <typename Allocator, typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy_using_allocator(alloc, first, last);
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			kerbal::memory::detail::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_USING_ALLOCATOR_HPP
