/**
 * @file       destroy.hpp
 * @brief
 * @date       2022-01-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_DESTROY_HPP
#define KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_DESTROY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void raw_storage_destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			while (first != last) {
				first->destroy();
				++first;
			}
		}

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		void raw_storage_destroy_n(ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
		{
			while (n != 0) {
				--n;
				first->destroy();
				++first;
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void raw_storage_reverse_destroy(BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
		{
			while (first != last) {
				--last;
				last->destroy();
			}
		}

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void raw_storage_transaction_failed_destroy(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) KERBAL_NOEXCEPT
			{
				raw_storage_destroy(first, last);
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void raw_storage_transaction_failed_destroy(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) KERBAL_NOEXCEPT
			{
				raw_storage_reverse_destroy(first, last);
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void raw_storage_transaction_failed_destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			detail::raw_storage_transaction_failed_destroy(first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_DESTROY_HPP
