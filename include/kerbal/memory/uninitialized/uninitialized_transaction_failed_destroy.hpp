/**
 * @file       uninitialized_transaction_failed_destroy.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_HPP
#define KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/memory/uninitialized/reverse_destroy.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy(first, last);
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy_impl(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy(first, last);
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_transaction_failed_destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			kerbal::memory::detail::uninitialized_transaction_failed_destroy_impl(first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_TRANSACTION_FAILED_DESTROY_HPP
