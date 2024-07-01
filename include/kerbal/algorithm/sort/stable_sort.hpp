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

#include <kerbal/algorithm/modifier/merge.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>

#include <cstddef>
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

			const iterator t(kerbal::iterator::next(b_end, static_cast<std::size_t>(second_half_len - first_half_len)));
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
			return kerbal::algorithm::stable_sort_n_afford_buffer(first, len, buffer, kerbal::compare::less<value_type>());
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
			kerbal::algorithm::stable_sort_afford_buffer(first, last, buffer, kerbal::compare::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		KERBAL_CONSTEXPR20
		ForwardIterator
		stable_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

			KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, typename allocator_traits::value_type>::value),
								 "the afforded allocator doesn't provide the support of type which the iterator refers to");

			difference_type buffer_length(len - len / 2);
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
						kerbal::memory::reverse_destroy_using_allocator(this->allocator, this->buffer, this->buffer + this->buffer_length);
					}

			} auto_destroy_helper(allocator, buffer_length, buffer);

			return kerbal::algorithm::stable_sort_n_afford_buffer(first, len, buffer, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		KERBAL_CONSTEXPR20
		ForwardIterator
		stable_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len,
										Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::stable_sort_n_afford_allocator(first, len, allocator, kerbal::compare::less<value_type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		KERBAL_CONSTEXPR20
		void stable_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type len(kerbal::iterator::distance(first, last));
			kerbal::algorithm::stable_sort_n_afford_allocator(first, len, allocator, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		KERBAL_CONSTEXPR20
		void stable_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::stable_sort_afford_allocator(first, last, allocator, kerbal::compare::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR20
		void stable_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			std::allocator<value_type> allocator;
			kerbal::algorithm::stable_sort_afford_allocator(first, last, allocator, cmp);
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void stable_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::stable_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_STABLE_SORT_HPP
