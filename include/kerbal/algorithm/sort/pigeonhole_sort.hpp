/**
 * @file       pigeonhole_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-3-6
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
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_integral.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			struct cnt_array_size_helper
			{
					typedef typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type value_type;
					typedef kerbal::algorithm::detail::actual_bit_width<value_type> VALUE_TYPE_BIT_WIDTH; // warning: must be unsigned!!!
					typedef kerbal::type_traits::integral_constant<std::size_t, 1ull << VALUE_TYPE_BIT_WIDTH::value> type;
			};

			template <typename ForwardIterator>
			struct cnt_array_size: cnt_array_size_helper<ForwardIterator>::type
			{
			};

			template <typename T>
			KERBAL_CONSTEXPR14
			const T & pigeonhole_sort_hole_index(const T & data)
			{
				return data;
			}

			// suppress msvc warning of % calculation of bool
			KERBAL_CONSTEXPR14
			unsigned int pigeonhole_sort_hole_index(const bool & data) KERBAL_NOEXCEPT
			{
				return static_cast<unsigned int>(data);
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_fill(ForwardIterator first, ForwardIterator last, std::size_t cnt[])
			{
				typedef ForwardIterator iterator;

				while (first != last) {
					++cnt[pigeonhole_sort_hole_index(*first) % cnt_array_size<iterator>::value];
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill_n(ForwardIterator & first, std::size_t cnt,
											typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type current,
											std::forward_iterator_tag)
			{
				for (std::size_t j = 0; j < cnt; ++j) {
					*first = current;
					++first;
				}
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill_n(RandomAccessIterator & first, std::size_t cnt,
											typename kerbal::iterator::iterator_traits<RandomAccessIterator>::value_type current,
											std::random_access_iterator_tag)
			{

#	define EACH() do {\
				*first = current;\
				++first;\
			} while (false)

				std::size_t trip_count(cnt);
				std::size_t remain(trip_count & 3);
				for (trip_count >>= 2; trip_count > 0; --trip_count) {
					EACH();
					EACH();
					EACH();
					EACH();
				}

				if (remain >= 2) {
					EACH();
					EACH();
					remain -= 2;
				}
				if (remain >= 1) {
					EACH();
				}

#	undef EACH

			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill_n(ForwardIterator & first, std::size_t cnt,
											typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type current)
			{
				pigeonhole_sort_back_fill_n(first, cnt, current, kerbal::iterator::iterator_category(first));
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill(ForwardIterator first, const std::size_t cnt[],
											kerbal::type_traits::false_type /*asc*/,
											kerbal::type_traits::false_type /*unsigned*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				for (std::size_t i = 0; i < cnt_array_size<iterator>::value; ++i) {
					value_type current(static_cast<value_type>(i));
					pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill(ForwardIterator first, const std::size_t cnt[],
											kerbal::type_traits::true_type /*desc*/,
											kerbal::type_traits::false_type /*unsigned*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				std::size_t i = cnt_array_size<iterator>::value;
				while (i > 0) {
					--i;
					value_type current(static_cast<value_type>(i));
					pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill(ForwardIterator first, const std::size_t cnt[],
											kerbal::type_traits::false_type /*asc*/,
											kerbal::type_traits::true_type /*signed*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef cnt_array_size<iterator> cnt_array_size;

				for (std::size_t i = cnt_array_size::value / 2; i < cnt_array_size::value; ++i) {
					value_type current(static_cast<value_type>(i));
					pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
				for (std::size_t i = 0; i < cnt_array_size::value / 2; ++i) {
					value_type current(static_cast<value_type>(i));
					pigeonhole_sort_back_fill_n(first, cnt[i], current);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void pigeonhole_sort_back_fill(ForwardIterator first, const std::size_t cnt[],
											kerbal::type_traits::true_type /*desc*/,
											kerbal::type_traits::true_type /*signed*/)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef cnt_array_size<iterator> cnt_array_size;

				{
					std::size_t i = cnt_array_size::value / 2;
					while (i > 0) {
						--i;
						value_type current(static_cast<value_type>(i));
						pigeonhole_sort_back_fill_n(first, cnt[i], current);
					}
				}
				{
					std::size_t i = cnt_array_size::value;
					while (i > cnt_array_size::value / 2) {
						--i;
						value_type current(static_cast<value_type>(i));
						pigeonhole_sort_back_fill_n(first, cnt[i], current);
					}
				}
			}

		} // namespace detail


		namespace detail
		{

			template <typename ValueType, bool IsIntegral = kerbal::type_traits::is_integral<ValueType>::value>
			struct is_pigeonhole_sort_acceptable_type_helper;

			template <typename ValueType>
			struct is_pigeonhole_sort_acceptable_type_helper<ValueType, false> :
					kerbal::type_traits::false_type
			{
			};

			template <typename ValueType>
			struct is_pigeonhole_sort_acceptable_type_helper<ValueType, true> :
					kerbal::type_traits::bool_constant<
							kerbal::algorithm::detail::actual_bit_width<ValueType>::value <= 16
					>
			{
			};

		} // namespace detail

		template <typename ValueType>
		struct is_pigeonhole_sort_acceptable_type:
				detail::is_pigeonhole_sort_acceptable_type_helper<ValueType>
		{
		};

		template <typename ForwardIterator, typename Order>
		KERBAL_CONSTEXPR14
		void pigeonhole_sort(ForwardIterator first, ForwardIterator last, Order order)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			KERBAL_STATIC_ASSERT(is_pigeonhole_sort_acceptable_type<value_type>::value,
								 "pigeonhole sort only accept bool type or integer with bit width <= 16");

			std::size_t cnt[detail::cnt_array_size<iterator>::value] = {0};
			detail::pigeonhole_sort_fill(first, last, cnt);
			detail::pigeonhole_sort_back_fill(first, cnt, order, kerbal::type_traits::is_signed<value_type>());
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
