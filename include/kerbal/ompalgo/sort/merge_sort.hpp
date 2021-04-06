/**
 * @file       merge_sort.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_MERGE_SORT_HPP
#define KERBAL_OMPALGO_SORT_MERGE_SORT_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>

#include <omp.h>
#include <memory>

#include <kerbal/algorithm/sort/detail/merge_sort_merge.hpp>


namespace kerbal
{

	namespace ompalgo
	{

#if !defined(_OPENMP)

		template <typename ForwardIterator, typename Compare>
		void merge_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			kerbal::algorithm::merge_sort(first, last, cmp);
		}

#else

		template <typename RandomAccessIterator, typename RandomAccessIterator2, typename Compare>
		void merge_sort_afford_buffer(RandomAccessIterator first, RandomAccessIterator last, Compare cmp, RandomAccessIterator2 buffer)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			difference_type len(last - first);

			if (len == 0) {
				return;
			}
			if (len == 1) {
				return;
			}
			if (len == 2) {
				iterator i(kerbal::iterator::next(first));
				if (cmp(*i, *first)) {
					kerbal::algorithm::iter_swap(first, i);
				}
			}

			difference_type half_len = len / 2;
			iterator mid = first + half_len;

#			pragma omp task
			{
				merge_sort(first, mid, cmp, buffer);
			}
#			pragma omp task
			{
				merge_sort(mid, last, cmp, buffer + half_len);
			}
#			pragma omp taskwait

			value_type * buffer_mid(kerbal::algorithm::copy(first, mid, buffer));
			kerbal::algorithm::detail::merge_sort_merge(buffer, buffer_mid, mid, last, first, cmp);

		}

#endif

		/*
		 * return first + len
		 */
		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator
		merge_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
									ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef ForwardIterator2 buffer_iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			if (len == 0) {
				return first;
			}
			if (len == 1) {
				return kerbal::iterator::next(first);
			}
			if (len == 2) {
				iterator i(kerbal::iterator::next(first));
				if (cmp(*i, *first)) {
					kerbal::algorithm::iter_swap(first, i);
				}
				return kerbal::iterator::next(i);
			}

			difference_type first_half_len = len / 2;
			iterator mid(kerbal::algorithm::merge_sort_n_afford_buffer(first, first_half_len, buffer, cmp));
			iterator last(kerbal::algorithm::merge_sort_n_afford_buffer(mid, len - first_half_len, buffer, cmp));
			buffer_iterator buffer_mid(kerbal::algorithm::copy(first, mid, buffer));
			kerbal::algorithm::detail::merge_sort_merge(buffer, buffer_mid, mid, last, first, cmp);
			return last;
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator
		merge_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
									ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, std::less<value_type>());
		}

		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort_afford_buffer(first, last, buffer, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		ForwardIterator
		merge_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

			difference_type buffer_length(len / 2);
			value_type * const buffer = allocator_traits::allocate(allocator, buffer_length);
			value_type * k = buffer;

			typedef typename Allocator::value_type allocator_value_type;

			struct dealloc_helper
			{
					Allocator & allocator;
					difference_type const & buffer_length;
					value_type * const & buffer;
					value_type * & k;

					dealloc_helper(Allocator & allocator, difference_type const & buffer_length, value_type * const & buffer, value_type * & k) KERBAL_NOEXCEPT :
							allocator(allocator), buffer_length(buffer_length), buffer(buffer), k(k)
					{
					}

					~dealloc_helper()
					{
						while (k != buffer) {
							--k;
							allocator_traits::destroy(this->allocator, k);
						}
						allocator_traits::deallocate(this->allocator, buffer, buffer_length);
					}
			} auto_dealloc_helper(allocator, buffer_length, buffer, k);

/*
			while (k != buffer + buffer_length) {
				allocator.construct(k);
				++k;
			}
*/

#	define EACH() do {\
				/*allocator.construct(k);\*/\
				allocator_traits::construct(allocator, k);\
				++k;\
			} while(false)

			for (difference_type trip_count(buffer_length >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(buffer + buffer_length - k);
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		ForwardIterator
		merge_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::merge_sort_n_afford_allocator(first, len, allocator, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type const len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::merge_sort_n_afford_allocator(first, len, allocator, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		void merge_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			std::allocator<value_type> allocator;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, cmp);
		}

		template <typename ForwardIterator>
		void merge_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_MERGE_SORT_HPP
