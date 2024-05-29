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
#include <kerbal/memory/uninitialized/destroy.hpp>
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

		template <typename Allocator, typename T>
		KERBAL_CONSTEXPR14
		void destroy_on_using_allocator(Allocator & alloc, T & plc);

		template <typename Allocator, typename T>
		KERBAL_CONSTEXPR14
		void destroy_at_using_allocator(Allocator & alloc, T * p);

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

		template <typename Allocator, typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n) KERBAL_NOEXCEPT;

		template <typename Allocator, typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT;

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_transaction_failed_destroy_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;



	//==================
	// destroy_on_using_allocator, destroy at_using_allocator

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
			detail::k_destroy_on_using_allocator(alloc, plc, kerbal::memory::allocator_could_use_destroy<Allocator, T>());
		}

		template <typename Allocator, typename T>
		KERBAL_CONSTEXPR14
		void destroy_at_using_allocator(Allocator & alloc, T * p)
		{
			kerbal::memory::destroy_on_using_allocator(alloc, *p);
		}



	//==================
	// destroy_using_allocator

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
			detail::k_destroy_using_allocator(alloc, first, last, kerbal::memory::allocator_could_use_destroy<Allocator, value_type>());
		}



	//==================
	// destroy_n_using_allocator

		namespace detail
		{

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator k_destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				while (n > 0) {
					--n;
					kerbal::memory::destroy_on_using_allocator(alloc, *first);
					++first;
				}
				return first;
			}

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator k_destroy_n_using_allocator(Allocator & /*alloc*/, ForwardIterator first, SizeType n, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return kerbal::memory::destroy_n(first, n);
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator destroy_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return detail::k_destroy_n_using_allocator(alloc, first, n, kerbal::memory::allocator_could_use_destroy<Allocator, value_type>());
		}



	//==================
	// reverse_destroy_using_allocator

		namespace detail
		{

			template <typename Allocator, typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void k_reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				while (first != last) {
					--last;
					kerbal::memory::destroy_on_using_allocator(alloc, *last);
				}
			}

			template <typename Allocator, typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void k_reverse_destroy_using_allocator(Allocator & /*alloc*/, BidirectionalIterator first, BidirectionalIterator last, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy(first, last);
			}

		} // namespace detail

		template <typename Allocator, typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy_using_allocator(Allocator & alloc, BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			detail::k_reverse_destroy_using_allocator(alloc, first, last, kerbal::memory::allocator_could_use_destroy<Allocator, value_type>());
		}



	//==================
	// uninitialized_transaction_failed_destroy_using_allocator

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
			detail::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_USING_ALLOCATOR_HPP
