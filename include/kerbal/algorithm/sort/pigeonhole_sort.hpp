/**
 * @file       pigeonhole_sort.hpp
 * @brief
 * @date       2020-5-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_PIGEONHOLE_SORT_HPP
#define KERBAL_ALGORITHM_SORT_PIGEONHOLE_SORT_HPP

#include <kerbal/algorithm/sort/detail/actual_bit_width.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/volatile_deduction.hpp>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_fill(ForwardIterator first, ForwardIterator last, size_t * cnt)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1ull << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				while (first != last) {
					++cnt[*first % cnt_array_size::value];
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(ForwardIterator & first, size_t cnt, typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type current, std::forward_iterator_tag)
			{
				for (size_t j = 0; j < cnt; ++j) {
					*first = current;
					++first;
				}
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(RandomAccessIterator & first, size_t cnt, typename kerbal::iterator::iterator_traits<RandomAccessIterator>::value_type current, std::random_access_iterator_tag)
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

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void __pigeonhole_sort_back_fill_n(ForwardIterator & first, size_t cnt, typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type current)
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
				typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				for (size_t i = 0; i < cnt_array_size::value; ++i) {
					value_type current = i;
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
				typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				size_t i = cnt_array_size::value;
				while (i > 0) {
					--i;
					value_type current = i;
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
				typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				for (size_t i = cnt_array_size::value / 2; i < cnt_array_size::value; ++i) {
					value_type current = i;
					__pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
				for (size_t i = 0; i < cnt_array_size::value / 2; ++i) {
					value_type current = i;
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
				typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
				typedef kerbal::type_traits::integral_constant<size_t, 1 << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

				{
					size_t i = cnt_array_size::value / 2;
					while (i > 0) {
						--i;
						value_type current = i;
						__pigeonhole_sort_back_fill_n(first, cnt[i], current);
					}
				}
				{
					size_t i = cnt_array_size::value;
					while (i > cnt_array_size::value / 2) {
						--i;
						value_type current = i;
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
			typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
			typedef kerbal::type_traits::integral_constant<size_t, 1ull << VALUE_TYPE_BIT_WIDTH::value> cnt_array_size;

			KERBAL_STATIC_ASSERT(VALUE_TYPE_BIT_WIDTH::value <= 16,
								 "pigeonhole sort only accept bool type or integer with bit width <= 16");

			size_t cnt[cnt_array_size::value] = {0};
			kerbal::algorithm::detail::__pigeonhole_sort_fill(first, last, cnt);
			kerbal::algorithm::detail::__pigeonhole_sort_back_fill(first, cnt, order, kerbal::type_traits::is_signed<value_type>());
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last) // default: asc
		{
			kerbal::algorithm::pigeonhole_sort(first, last, kerbal::type_traits::false_type());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_PIGEONHOLE_SORT_HPP
