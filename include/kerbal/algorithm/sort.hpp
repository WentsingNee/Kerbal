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

#ifndef KERBAL_ALGORITHM_SORT_HPP_
#define KERBAL_ALGORITHM_SORT_HPP_

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
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/type_traits_details/volatile_deduction.hpp>

#include <stack>
#include <memory>

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

			template <typename Tp>
			struct __pigeonhole_sort_transform;

			template <typename Tp>
			struct __pigeonhole_sort_anti_transform;

			template <>
			struct __pigeonhole_sort_transform<bool>
			{
					KERBAL_CONSTEXPR
					size_t operator()(bool value) const
					{
						return value ? 1 : 0;
					}
			};

			template <>
			struct __pigeonhole_sort_anti_transform<bool>
			{
					KERBAL_CONSTEXPR
					bool operator()(size_t index) const
					{
						return index ? true : false;
					}
			};

			template <>
			struct __pigeonhole_sort_transform<kerbal::compatibility::int8_t>
			{
					KERBAL_CONSTEXPR
					size_t operator()(kerbal::compatibility::int8_t value) const
					{
						return value + 128;
					}
			};

			template <>
			struct __pigeonhole_sort_anti_transform<kerbal::compatibility::int8_t>
			{
					KERBAL_CONSTEXPR
					kerbal::compatibility::int8_t operator()(size_t index) const
					{
						return index - 128;
					}
			};

			template <>
			struct __pigeonhole_sort_transform<kerbal::compatibility::uint8_t>
			{
					KERBAL_CONSTEXPR
					size_t operator()(kerbal::compatibility::uint8_t value) const
					{
						return value;
					}
			};

			template <>
			struct __pigeonhole_sort_anti_transform<kerbal::compatibility::uint8_t>
			{
					KERBAL_CONSTEXPR
					kerbal::compatibility::uint8_t operator()(size_t index) const
					{
						return index;
					}
			};

		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last, kerbal::type_traits::false_type) // less
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
			typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
			typedef kerbal::type_traits::is_same<remove_volatile_type, kerbal::compatibility::int8_t> is_int8_t;
			typedef kerbal::type_traits::is_same<remove_volatile_type, kerbal::compatibility::uint8_t> is_uint8_t;
			KERBAL_STATIC_ASSERT((is_bool_t::value || is_int8_t::value || is_uint8_t::value),
								"pigeonhole sort only accept bool, int8_t or uint8_t");

			typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 2 : 256> cnt_array_size;
			size_t cnt[cnt_array_size::value] = {0};

			detail::__pigeonhole_sort_transform<remove_volatile_type> transform;
			detail::__pigeonhole_sort_anti_transform<remove_volatile_type> anti_transform;
			for (iterator i(first); i != last; ++i) {
				++cnt[transform(*i)];
			}

			for (size_t i = 0; i < cnt_array_size::value; ++i) {
				remove_volatile_type current = anti_transform(i);
				for (size_t j = 0; j < cnt[i]; ++j) {
					*first = current;
					++first;
				}
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last, kerbal::type_traits::true_type) // greater
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef typename kerbal::type_traits::remove_volatile<value_type>::type remove_volatile_type;
			typedef kerbal::type_traits::is_same<remove_volatile_type, bool> is_bool_t;
			typedef kerbal::type_traits::is_same<remove_volatile_type, kerbal::compatibility::int8_t> is_int8_t;
			typedef kerbal::type_traits::is_same<remove_volatile_type, kerbal::compatibility::uint8_t> is_uint8_t;
			KERBAL_STATIC_ASSERT((is_bool_t::value || is_int8_t::value || is_uint8_t::value),
								"pigeonhole sort only accept bool, int8_t or uint8_t");

			typedef kerbal::type_traits::integral_constant<size_t, is_bool_t::value ? 2 : 256> cnt_array_size;
			size_t cnt[cnt_array_size::value] = {0};

			detail::__pigeonhole_sort_transform<remove_volatile_type> transform;
			detail::__pigeonhole_sort_anti_transform<remove_volatile_type> anti_transform;
			for (iterator i(first); i != last; ++i) {
				++cnt[transform(*i)];
			}

			size_t i = cnt_array_size::value;
			while (i > 0) {
				--i;
				remove_volatile_type current = anti_transform(i);
				for (size_t j = 0; j < cnt[i]; ++j) {
					*first = current;
					++first;
				}
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last) // less
		{
			kerbal::algorithm::pigeonhole_sort(first, last, kerbal::type_traits::false_type());
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

			difference_type half_len = len / 2;
			iterator mid = kerbal::algorithm::merge_sort_n_afford_buffer(first, half_len, buffer, cmp);
			buffer_iterator buffer_mid(kerbal::iterator::next(buffer, half_len));
			iterator last = kerbal::algorithm::merge_sort_n_afford_buffer(mid, len - half_len, buffer_mid, cmp);
			kerbal::algorithm::move(first, mid, buffer);
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

			difference_type buffer_length(len / 2);
			value_type * const buffer = allocator.allocate(buffer_length);
			value_type * k = buffer;

			typedef typename Allocator::value_type allocator_value_type;

			struct dealloc_helper
			{
					Allocator & allocator;
					difference_type const & len;
					value_type * const & buffer;
					value_type * & k;

					dealloc_helper(Allocator & allocator, difference_type const & len, value_type * const & buffer, value_type * & k) :
							allocator(allocator), len(len), buffer(buffer), k(k)
					{
					}

					~dealloc_helper()
					{
						while (k != buffer) {
							--k;
//							allocator.destroy(k);
							k->~allocator_value_type();
						}
						allocator.deallocate(buffer, len);
					}
			} auto_deallocator(allocator, buffer_length, buffer, k);

/*
			while (k != buffer + buffer_length) {
				allocator.construct(k);
				++k;
			}
*/

#	define EACH() do {\
				/*allocator.construct(k);\*/\
				new (k) allocator_value_type ();\
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

			return kerbal::algorithm::merge_sort_n_afford_buffer(first, buffer_length, buffer, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		ForwardIterator merge_sort_n_afford_allocator(ForwardIterator first, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type len, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
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
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			if (first == last) { // distance == 0
				return;
			}

			const iterator back(kerbal::iterator::prev(last));

			{
				difference_type distance(kerbal::iterator::distance(first, back));

				if (distance < 16) {
					kerbal::algorithm::insertion_sort(first, last, cmp);
//					kerbal::algorithm::flag_bubble_sort(first, last, cmp);
					return;
				}

//				difference_type delta((distance + 2147483647UL) * 16807UL % distance);
//				std::iter_swap(back, kerbal::iterator::next(first, delta));

				iterator mid(kerbal::iterator::midden_iterator(first, last));
				std::iter_swap(back, mid);

			}

			const iterator partition_point(kerbal::algorithm::partition(first, back, __quick_sort_U<iterator, Compare>(back, cmp)));

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
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			StackBuffer st;
			st.push(std::make_pair(first, last));

			while (!st.empty()) {
				const iterator first(st.top().first);
				const iterator last(st.top().second);
				st.pop();

				if (first == last) { // distance == 0
					continue;
				}

				const iterator back(kerbal::iterator::prev(last));

				{
					difference_type distance(kerbal::iterator::distance(first, back));

					if (distance < 16) {
						kerbal::algorithm::bubble_sort(first, last, cmp);
						continue;
					}

					iterator mid(kerbal::iterator::midden_iterator(first, last));
					std::iter_swap(back, mid);
				}

				const iterator partition_point(kerbal::algorithm::partition(first, back, __quick_sort_U<iterator, Compare>(back, cmp)));

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

	} /* namespace algorithm */

} /* namespace kerbal */

#endif	/* End KERBAL_ALGORITHM_SORT_HPP_ */
