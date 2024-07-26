/**
 * @file       merge_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2017-2-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_MERGE_SORT_HPP
#define KERBAL_ALGORITHM_SORT_MERGE_SORT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>

#include <memory>

#include <kerbal/algorithm/sort/detail/merge_sort_merge.hpp>


namespace kerbal
{

	namespace algorithm
	{

		/*
		 * return first + len
		 */
		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator
		merge_sort_n_afford_buffer(
			ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
			ForwardIterator2 buffer, Compare cmp
		)
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

			// <=> first = kerbal::algorithm::upper_bound(first, mid, *mid, cmp );
			while (static_cast<bool>(first != mid) && !static_cast<bool>(cmp(*mid, *first))) {
				// *mid >= *first
				++first;
			}

			buffer_iterator buffer_mid(kerbal::algorithm::copy(first, mid, buffer));
			kerbal::algorithm::detail::merge_sort_merge(buffer, buffer_mid, mid, last, first, cmp);
			return last;
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator
		merge_sort_n_afford_buffer(
			ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
			ForwardIterator2 buffer
		)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, kerbal::compare::less<value_type>());
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort_afford_buffer(first, last, buffer, kerbal::compare::less<value_type>());
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Allocator, typename Compare>
		KERBAL_CONSTEXPR20
		ForwardIterator
		merge_sort_n_afford_allocator(
			ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
			Allocator & allocator, Compare cmp
		)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

			KERBAL_STATIC_ASSERT(
				(kerbal::type_traits::is_same<value_type, typename allocator_traits::value_type>::value),
				"the afforded allocator doesn't provide the support of type which the iterator refers to"
			);

			difference_type buffer_length(len / 2);
			value_type * const buffer = allocator_traits::allocate(allocator, buffer_length);

			struct dealloc_helper
			{
					Allocator & allocator;
					difference_type const & buffer_length;
					value_type * const & buffer;

					KERBAL_CONSTEXPR20
					dealloc_helper(Allocator & allocator, difference_type const & buffer_length, value_type * const & buffer) KERBAL_NOEXCEPT :
						allocator(allocator), buffer_length(buffer_length), buffer(buffer)
					{
					}

					KERBAL_CONSTEXPR20
					~dealloc_helper()
					{
						allocator_traits::deallocate(this->allocator, this->buffer, this->buffer_length);
					}

			} auto_dealloc_helper(allocator, buffer_length, buffer);

			kerbal::memory::uninitialized_value_construct_using_allocator(allocator, buffer, buffer + buffer_length);

			struct destroy_helper
			{
					Allocator & allocator;
					difference_type const & buffer_length;
					value_type * const & buffer;

					KERBAL_CONSTEXPR20
					destroy_helper(Allocator & allocator, difference_type const & buffer_length, value_type * const & buffer) KERBAL_NOEXCEPT :
						allocator(allocator), buffer_length(buffer_length), buffer(buffer)
					{
					}

					KERBAL_CONSTEXPR20
					~destroy_helper()
					{
						kerbal::memory::reverse_destroy_using_allocator(
							this->allocator,
							this->buffer, this->buffer + this->buffer_length
						);
					}

			} auto_destroy_helper(allocator, buffer_length, buffer);

			return kerbal::algorithm::merge_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Allocator>
		KERBAL_CONSTEXPR20
		ForwardIterator
		merge_sort_n_afford_allocator(
			ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
			Allocator & allocator
		)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::merge_sort_n_afford_allocator(
				first, len, allocator, kerbal::compare::less<value_type>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Allocator, typename Compare>
		KERBAL_CONSTEXPR20
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type const len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::merge_sort_n_afford_allocator(first, len, allocator, cmp);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Allocator>
		KERBAL_CONSTEXPR20
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, kerbal::compare::less<value_type>());
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR20
		void merge_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			std::allocator<value_type> allocator;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, cmp);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void merge_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::merge_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_MERGE_SORT_HPP
