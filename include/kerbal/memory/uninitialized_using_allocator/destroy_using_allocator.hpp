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
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus > 201703L
#	include <memory>
#endif


namespace kerbal
{

	namespace memory
	{

	//==================
	// forward declare

		template <typename Allocator, typename Tp>
		KERBAL_CONSTEXPR20
		void destroy_on_using_allocator(Allocator & alloc, Tp & plc);

		template <typename Allocator, typename Tp>
		KERBAL_CONSTEXPR20
		void destroy_at_using_allocator(Allocator & alloc, Tp * p);

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

		template <typename Allocator, typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR20
		ForwardIterator destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n) KERBAL_NOEXCEPT;

		template <typename Allocator, typename BidirectionalIterator>
		KERBAL_CONSTEXPR20
		void reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT;

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;



	//==================
	// destroy_on_using_allocator, destroy at_using_allocator

		namespace detail
		{

			template <typename Allocator, typename Tp>
			KERBAL_CONSTEXPR20
			void _K_destroy_on_using_allocator(Allocator & alloc, Tp & plc)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<Allocator>::destroy(alloc, &plc))
					)
			{
				kerbal::memory::allocator_traits<Allocator>::destroy(alloc, &plc);
			}

		} // namespace detail

		template <typename Allocator, typename Tp>
		KERBAL_CONSTEXPR20
		void destroy_on_using_allocator(Allocator & alloc, Tp & plc)
		{
			detail::_K_destroy_on_using_allocator(alloc, plc);
		}

		template <typename Allocator, typename Tp>
		KERBAL_CONSTEXPR20
		void destroy_at_using_allocator(Allocator & alloc, Tp * p)
		{
			kerbal::memory::destroy_on_using_allocator(alloc, *p);
		}



	//==================
	// destroy_using_allocator

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
			{
				while (first != last) {
					kerbal::memory::destroy_on_using_allocator(alloc, *first);
					++first;
				}
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			detail::_K_destroy_using_allocator(alloc, first, last);
		}



	//==================
	// destroy_n_using_allocator

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
			{
				while (n > 0) {
					--n;
					kerbal::memory::destroy_on_using_allocator(alloc, *first);
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR20
		ForwardIterator destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
		{
			return detail::_K_destroy_n_using_allocator(alloc, first, n);
		}



	//==================
	// reverse_destroy_using_allocator

		namespace detail
		{

			template <typename Allocator, typename BidirectionalIterator>
			KERBAL_CONSTEXPR20
			void _K_reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
			{
				while (first != last) {
					--last;
					kerbal::memory::destroy_on_using_allocator(alloc, *last);
				}
			}

		} // namespace detail

		template <typename Allocator, typename BidirectionalIterator>
		KERBAL_CONSTEXPR20
		void reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
		{
			detail::_K_reverse_destroy_using_allocator(alloc, first, last);
		}



	//==================
	// uninitialized_transaction_failed_destroy_using_allocator

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy_using_allocator(alloc, first, last);
			}

			template <typename Allocator, typename BidirectionalIterator>
			KERBAL_CONSTEXPR20
			void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy_using_allocator(alloc, first, last);
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			detail::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_USING_ALLOCATOR_HPP
