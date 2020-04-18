/**
 * @file       sort.hpp
 * @brief
 * @date       2017-2-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_HPP
#define KERBAL_ALGORITHM_SORT_HPP

#include <kerbal/algorithm/binary_search.hpp>
#include <kerbal/algorithm/heap.hpp>
#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/stride_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/volatile_deduction.hpp>

#include <stack>
#include <memory>
#include <vector>

namespace kerbal
{
	namespace algorithm
	{

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void bubble_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			while (first != last) {
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				while (j_next != last) {
					if (cmp(*j_next, *j)) {
						kerbal::algorithm::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
				}
				last = j;
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void bubble_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::bubble_sort(first, last, std::less<value_type>());
		}


		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			bool swit = true;

			while (static_cast<bool>(first != last) && swit) {
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				swit = false;
				while (j_next != last) {
					if (cmp(*j_next, *j)) {
						swit = true;
						kerbal::algorithm::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
				}
				last = j;
			}

		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::flag_bubble_sort(first, last, std::less<value_type>());
		}


		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void selection_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			while (first != last) {
				iterator j(kerbal::algorithm::min_element(first, last, cmp));
				if (first != j) {
					if (cmp(*j, *first)) {
						kerbal::algorithm::iter_swap(j, first);
					}
				}
				++first;
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void selection_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::selection_sort(first, last, std::less<value_type>());
		}


		namespace detail
		{

			template <typename ForwardIterator, typename remove_volatile_type>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(ForwardIterator & first, size_t cnt, remove_volatile_type current, std::forward_iterator_tag)
			{
				for (size_t j = 0; j < cnt; ++j) {
					*first = current;
					++first;
				}
			}

			template <typename ForwardIterator, typename remove_volatile_type>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(ForwardIterator & first, size_t cnt, remove_volatile_type current, std::random_access_iterator_tag)
			{

#	define EACH() do {\
				*first = current;\
				++first;\
			} while (false)

				for (size_t trip_count(cnt >> 2); trip_count > 0; --trip_count) {
					EACH();
					EACH();
					EACH();
					EACH();
				}
				size_t remain(cnt % 4);
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

			}

			template <typename ForwardIterator, typename remove_volatile_type>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(ForwardIterator & first, size_t cnt, remove_volatile_type current)
			{
				__pigeonhole_sort_back_fill_n(first, cnt, current, kerbal::iterator::iterator_category(first));
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill(ForwardIterator first, size_t cnt[],
							kerbal::type_traits::false_type /*asc*/,
							kerbal::type_traits::false_type /*unsigned*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
				typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
				typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 1 : sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				for (size_t i = 0; i < cnt_array_size::value; ++i) {
					remove_volatile_type current = i;
					__pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill(ForwardIterator first, size_t cnt[],
							kerbal::type_traits::true_type /*desc*/,
							kerbal::type_traits::false_type /*unsigned*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
				typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
				typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 1 : sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				size_t i = cnt_array_size::value;
				while (i > 0) {
					--i;
					remove_volatile_type current = i;
					__pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill(ForwardIterator first, size_t cnt[],
							kerbal::type_traits::false_type /*asc*/,
							kerbal::type_traits::true_type /*signed*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
				typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
				typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 1 : sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				for (size_t i = cnt_array_size::value / 2; i < cnt_array_size::value; ++i) {
					remove_volatile_type current = i;
					__pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
				for (size_t i = 0; i < cnt_array_size::value / 2; ++i) {
					remove_volatile_type current = i;
					__pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill(ForwardIterator first, size_t cnt[],
							kerbal::type_traits::true_type /*desc*/,
							kerbal::type_traits::true_type /*signed*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
				typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
				typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 1 : sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				{
					size_t i = cnt_array_size::value / 2;
					while (i > 0) {
						--i;
						remove_volatile_type current = i;
						__pigeonhole_sort_back_fill_n(first, cnt[i], current);
					}
				}
				{
					size_t i = cnt_array_size::value;
					while (i > cnt_array_size::value / 2) {
						--i;
						remove_volatile_type current = i;
						__pigeonhole_sort_back_fill_n(first, cnt[i], current);
					}
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename Order>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last, Order order)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
			typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
			typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 1 : sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
			typedef kerbal::type_traits::integral_constant<size_t, 1ull << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

			KERBAL_STATIC_ASSERT(VALUE_TYPE_BIT_WIDTH::value <= 16,
								 "pigeonhole sort only accept bool type or integer with bit width <= 16");

			size_t cnt[cnt_array_size::value] = {0};

			for (iterator i(first); i != last; ++i) {
				++cnt[*i % cnt_array_size::value];
			}

			kerbal::algorithm::detail::__pigeonhole_sort_back_fill(first, cnt, order, kerbal::type_traits::is_signed<value_type>());
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last) // default: asc
		{
			kerbal::algorithm::pigeonhole_sort(first, last, kerbal::type_traits::false_type());
		}


		namespace detail
		{

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				for (size_t i = 0; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				size_t i = BUCKETS_NUM;
				while (i > 0) {
					--i;
					first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::true_type /*signed*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				for (size_t i = BUCKETS_NUM / 2; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
				for (size_t i = 0; i < BUCKETS_NUM / 2; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::true_type /*signed*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				{
					size_t i = BUCKETS_NUM / 2;
					while (i > 0) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
					}
				}
				{
					size_t i = BUCKETS_NUM;
					while (i > BUCKETS_NUM / 2) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
					}
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename Order, int RADIX_BIT_WIDTH>
		void radix_sort(ForwardIterator first, ForwardIterator last,
						Order order, kerbal::type_traits::integral_constant<int, RADIX_BIT_WIDTH> /*radix_bit_width*/)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef kerbal::type_traits::integral_constant<size_t, 1 << RADIX_BIT_WIDTH> BUCKETS_NUM;
			std::vector<value_type> buckets[2][BUCKETS_NUM::value];

			typedef kerbal::type_traits::integral_constant<size_t, sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH;
			typedef kerbal::type_traits::integral_constant<int, VALUE_TYPE_BIT_WIDTH::value / RADIX_BIT_WIDTH + (VALUE_TYPE_BIT_WIDTH::value % RADIX_BIT_WIDTH != 0)> ROUNDS;

//			size_t dist = kerbal::iterator::distance(first, last) /*/ BUCKETS_NUM::value*/;
//			for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
//				buckets[0][i].reserve(dist);
//				buckets[1][i].reserve(dist);
//			}

			for (iterator it(first); it != last; ++it) {
				int bucket_id = *it % BUCKETS_NUM::value;
				buckets[0][bucket_id].push_back(*it);
			}

			for (int round = 1; round < ROUNDS::value; ++round) {
				std::vector<value_type> (& buckets_from)[BUCKETS_NUM::value] = buckets[(round + 1) % 2];
				std::vector<value_type> (& buckets_to)[BUCKETS_NUM::value] = buckets[round % 2];

				for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					buckets_to[i].clear();
				}
				for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					typename std::vector<value_type>::iterator it(buckets_from[i].begin());
					typename std::vector<value_type>::iterator end(buckets_from[i].end());
					while (it != end) {
						int bucket_id = (*it >> (RADIX_BIT_WIDTH * round)) % BUCKETS_NUM::value;
						buckets_to[bucket_id].push_back(*it);
						++it;
					}
				}
			}

			kerbal::algorithm::detail::__radix_sort_back_fill(first, order,
															kerbal::type_traits::is_signed<value_type>(),
															buckets[(ROUNDS::value + 1) % 2], BUCKETS_NUM::value);
		}

		template <typename ForwardIterator, typename Order>
		void radix_sort(ForwardIterator first, ForwardIterator last, Order order)
		{
			kerbal::algorithm::radix_sort(first, last, order, kerbal::type_traits::integral_constant<int, CHAR_BIT>());
		}

		template <typename ForwardIterator>
		void radix_sort(ForwardIterator first, ForwardIterator last)
		{
			kerbal::algorithm::radix_sort(first, last, type_traits::false_type());
		}


		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void heap_sort(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::make_heap(first, last, compare);
			kerbal::algorithm::sort_heap(first, last, compare);
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void heap_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::heap_sort(first, last, std::less<value_type>());
		}


		/*
		 * return first + len
		 */
		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator merge_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len, ForwardIterator2 buffer, Compare cmp)
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
			buffer_iterator buffer_mid(kerbal::algorithm::move(first, mid, buffer));
			kerbal::algorithm::merge(buffer, buffer_mid, mid, last, first, cmp);
			return last;
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator merge_sort_n_afford_buffer(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len, ForwardIterator2 buffer)
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
		ForwardIterator merge_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len, Allocator & allocator, Compare cmp)
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
		ForwardIterator merge_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len, Allocator & allocator)
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
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
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


		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			for (iterator i(first); i != last; ++i) {
				iterator insert_pos(kerbal::algorithm::upper_bound(first, i, *i, cmp));
				if (insert_pos != i) {
					value_type value(kerbal::compatibility::to_xvalue(*i));
					kerbal::algorithm::move_backward(insert_pos, i, kerbal::iterator::next(i));
					*insert_pos = kerbal::compatibility::to_xvalue(value);
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::insertion_sort(first, last, std::less<value_type>());
		}


		template <typename differece_type>
		struct shell_sort_reduce_by_half_policy
		{
				KERBAL_CONSTEXPR14
				differece_type init_stride(differece_type dist) const
				{
					return dist / 2;
				}

				KERBAL_CONSTEXPR14
				bool operator()(differece_type & stride) const
				{
					if (stride == 0 || stride == 1) {
						return false;
					}
					stride /= 2;
					return true;
				}
		};

		template <typename differece_type>
		struct shell_sort_hibbard_policy
		{
				KERBAL_CONSTEXPR14
				differece_type init_stride(differece_type dist) const
				{
					if (dist == 0) {
						return 0;
					}

					int cnt = 0;
					while ((dist >> cnt) != 1) {
						++cnt;
					}
					for (int i = 0; i < cnt; ++i) {
						dist |= static_cast<differece_type>(1) << i;
					}
					/*
						dist |= mask(cnt);
					 */
					return dist;
				}

				KERBAL_CONSTEXPR14
				bool operator()(differece_type & stride) const
				{
					if (stride == 0 || stride == 1) {
						return false;
					}
					stride = (stride + 1) / 2 - 1;
					return true;
				}
		};

		template <typename BidirectionalIterator, typename Compare, typename GapReducePolicy>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, GapReducePolicy gap_reduce_policy)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type dist(kerbal::iterator::distance(first, last));
			difference_type stride(gap_reduce_policy.init_stride(dist));
			do {
				if (stride == 1) {
					kerbal::algorithm::insertion_sort(first, last, cmp);
				} else {
					iterator section_first(first); // first + i
					for (difference_type i = 0; i < stride; ++i) {
						kerbal::iterator::stride_iterator<iterator> stride_first(first, section_first, last, stride);
						difference_type out = 0;
						if ((dist - i) % stride != 0) {
							out = stride - (dist - i) % stride;
						}
						kerbal::iterator::stride_iterator<iterator> stride_last(first, last, last, stride, out);
						kerbal::algorithm::insertion_sort(stride_first, stride_last, cmp);
						++section_first;
					}
				}
			} while (gap_policy(stride));
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			kerbal::algorithm::shell_sort(first, last, cmp, shell_sort_hibbard_policy<difference_type>());
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::shell_sort(first, last, std::less<value_type>());
		}

		namespace detail
		{

			template <typename Iterator, typename CompareFunction>
			struct __quick_sort_U
			{
					typedef Iterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef const value_type& const_reference;

					const iterator& back;
					CompareFunction& cmp;

					KERBAL_CONSTEXPR __quick_sort_U(const iterator& back, CompareFunction& cmp) KERBAL_NOEXCEPT :
							back(back), cmp(cmp)
					{
					}

					KERBAL_CONSTEXPR bool operator()(const_reference val) const
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(cmp(val, *back)))
					{
						return cmp(val, *back);
					}
			};

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void __quick_sort_adjust_pivot(BidirectionalIterator first, BidirectionalIterator mid, BidirectionalIterator back, Compare cmp)
			{
				if (cmp(*first, *mid)) {
					if (cmp(*mid, *back)) {
						// first < mid < back
						// 0 1 2
						std::iter_swap(mid, back);
						// 0 2 1
					} else {
						if (cmp(*first, *back)) {
							// first < back < mid
							// 0 2 1
						} else {
							// back < first < mid
							// 1 2 0
							std::iter_swap(first, back);
							// 0 2 1
						}
					}
				} else {
					if (cmp(*first, *back)) {
						// mid < first < back
						// 1 0 2
						std::iter_swap(first, back);
						// 2 0 1
					} else {
						if (cmp(*mid, *back)) {
							// back
							// mid < back < first
							// 2 0 1
						} else {
							// back < mid < first
							// 2 1 0
							std::iter_swap(mid, back);
							// 2 0 1
						}
					}
					std::iter_swap(first, mid);
					// 0 2 1
				}
			}
		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			if (!kerbal::iterator::distance_greater_than(first, last, 16)) { // dist <= 16
				kerbal::algorithm::insertion_sort(first, last, cmp);
				return;
			}

			iterator back(kerbal::iterator::prev(last));

			{
				iterator mid(kerbal::iterator::midden_iterator(first, last));
				detail::__quick_sort_adjust_pivot(first, mid, back, cmp);
			}

			iterator partition_point(kerbal::algorithm::partition(first, back, detail::__quick_sort_U<iterator, Compare>(back, cmp)));

			if (partition_point != back) {
				if (cmp(*back, *partition_point)) {
					std::iter_swap(back, partition_point);
				}
				kerbal::algorithm::quick_sort(kerbal::iterator::next(partition_point), last, cmp);
			}
			kerbal::algorithm::quick_sort(first, partition_point, cmp);
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::quick_sort(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare, typename StackBuffer>
		KERBAL_CONSTEXPR14
		void __nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			StackBuffer st;
			st.push(std::make_pair(first, last));

			while (!st.empty()) {
				const iterator first(st.top().first);
				const iterator last(st.top().second);
				st.pop();

				if (!kerbal::iterator::distance_greater_than(first, last, 16)) { // dist <= 16
					kerbal::algorithm::insertion_sort(first, last, cmp);
					continue;
				}

				iterator back(kerbal::iterator::prev(last));

				{
					iterator mid(kerbal::iterator::midden_iterator(first, last));
					detail::__quick_sort_adjust_pivot(first, mid, back, cmp);
				}

				iterator partition_point(kerbal::algorithm::partition(first, back, detail::__quick_sort_U<iterator, Compare>(back, cmp)));

				if (partition_point != back) {
					if (cmp(*back, *partition_point)) {
						std::iter_swap(back, partition_point);
					}
					st.push(std::make_pair(kerbal::iterator::next(partition_point), last));
				}
				st.push(std::make_pair(first, partition_point));
			}
		}

		template <typename BidirectionalIterator, typename Compare>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			kerbal::algorithm::__nonrecursive_qsort
				<BidirectionalIterator, Compare, std::stack<std::pair<iterator, iterator> > >
			(first, last, cmp);
		}

		template <typename BidirectionalIterator>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::nonrecursive_qsort(first, last, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			if (first != last) {
				ForwardIterator nxt(kerbal::iterator::next(first));
				while (nxt != last) {
					if (cmp(*nxt, *first)) { // *first > *nxt
						return nxt;
					}
					first = nxt;
					++nxt;
				}
			}
			return last;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_sorted_until(first, last, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			return static_cast<bool>(kerbal::algorithm::is_sorted_until(first, last, cmp) == last);
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_sorted(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif	// KERBAL_ALGORITHM_SORT_HPP
