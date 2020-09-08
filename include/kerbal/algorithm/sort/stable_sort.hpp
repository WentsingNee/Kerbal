/**
 * @file       stable_sort.hpp
 * @brief
 * @date       2020-6-1
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_STABLE_SORT_HPP
#define KERBAL_ALGORITHM_SORT_STABLE_SORT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>

#include <memory>

#include <kerbal/algorithm/sort/detail/merge_sort_merge.hpp>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			bool stable_sort_n_afford_buffer_small_size(ForwardIterator & first,
														typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
														Compare, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				if (len == 0) {
					return true;
				}
				if (len == 1) {
					++first;
					return true;
				}
				return false;
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			bool stable_sort_n_afford_buffer_small_size(ForwardIterator & first,
														typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
														Compare cmp, std::bidirectional_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				if (len <= 16) {
					iterator last(kerbal::iterator::next(first, len));
					kerbal::algorithm::directly_insertion_sort(first, last, cmp);
					first = last;
					return true;
				}
				return false;
			}

		} // namespace detail

		/*
		 * return first + len
		 */
		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator
		stable_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
									ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef ForwardIterator2 buffer_iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			if (detail::stable_sort_n_afford_buffer_small_size(first, len, cmp, kerbal::iterator::iterator_category(first))) {
				return first;
			}

			const difference_type first_half_len = len / 2;
			const difference_type second_half_len = len - first_half_len;

			const difference_type a = first_half_len / 2;
			const difference_type b = first_half_len - a;
			const difference_type c = second_half_len / 2;
			const difference_type d = second_half_len - c;

			const iterator a_end(kerbal::algorithm::stable_sort_n_afford_buffer(first, a, buffer, cmp));
			const iterator b_end(kerbal::algorithm::stable_sort_n_afford_buffer(a_end, b, buffer, cmp));
			const iterator c_end(kerbal::algorithm::stable_sort_n_afford_buffer(b_end, c, buffer, cmp));
			const iterator d_end(kerbal::algorithm::stable_sort_n_afford_buffer(c_end, d, buffer, cmp));
			const buffer_iterator buffer_end(kerbal::algorithm::merge(b_end, c_end, c_end, d_end, buffer, cmp));

			const iterator t(kerbal::iterator::next(b_end, static_cast<size_t>(second_half_len - first_half_len)));
			kerbal::algorithm::merge(first, a_end, a_end, b_end, t, cmp);

			kerbal::algorithm::detail::merge_sort_merge(buffer, buffer_end, t, d_end, first, cmp);
			return d_end;
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator
		stable_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
									ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::stable_sort_n_afford_buffer(first, len, buffer, std::less<value_type>());
		}

		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		void stable_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::stable_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		void stable_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::stable_sort_afford_buffer(first, last, buffer, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		ForwardIterator
		stable_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

			difference_type buffer_length(len - len / 2);
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

			return kerbal::algorithm::stable_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		ForwardIterator
		stable_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::stable_sort_n_afford_allocator(first, len, allocator, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		void stable_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::stable_sort_n_afford_allocator(first, len, allocator, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		void stable_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::stable_sort_afford_allocator(first, last, allocator, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		void stable_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			std::allocator<value_type> allocator;
			kerbal::algorithm::stable_sort_afford_allocator(first, last, allocator, cmp);
		}

		template <typename ForwardIterator>
		void stable_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::stable_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_STABLE_SORT_HPP
