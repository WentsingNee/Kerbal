/**
 * @file       rotate.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_ROTATE_HPP
#define KERBAL_ALGORITHM_MODIFIER_ROTATE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/modifier/move.hpp>
#include <kerbal/algorithm/modifier/move_backward.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			rotate_swap(ForwardIterator & first, ForwardIterator n_first, ForwardIterator last)
			{
				typedef ForwardIterator iterator;

				iterator left(first);

				while (n_first != last) {
					if (left == first) {
						first = n_first;
					}
					kerbal::algorithm::iter_swap(left, n_first);
					++left;
					++n_first;
				}

				return left;
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			rotate(
				ForwardIterator first, ForwardIterator n_first, ForwardIterator last,
				std::forward_iterator_tag
			)
			{
				typedef ForwardIterator iterator;

				if (n_first == first) {
					return last;
				}

				if (n_first == last) {
					return first;
				}

				iterator ret(rotate_swap(first, n_first, last));

				n_first = first;
				first = ret;

				while (n_first != first && n_first != last) {
					iterator left(rotate_swap(first, n_first, last));

					n_first = first;
					first = left;
					// next loop: rotate(left, first, last)
				}
				return ret;
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			rotate(
				RandomAccessIterator first, RandomAccessIterator n_first, RandomAccessIterator last,
				std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				difference_type left_len(n_first - first);
				difference_type right_len(last - n_first);

				iterator ret(first + right_len);

				while (left_len != 0 && right_len != 0) {

//					cout << left_len << "   " << right_len << endl;

					if (left_len <= right_len) {
						if (left_len == 1) {
							value_type t(kerbal::compatibility::to_xvalue(*first));
							*kerbal::algorithm::move(n_first, last, first) = kerbal::compatibility::to_xvalue(t);
							break;
						}
						while (n_first != last) {
							kerbal::algorithm::iter_swap(first, n_first);
							++first;
							++n_first;
						}
						right_len %= left_len;
						left_len -= right_len;
						n_first = last - right_len;
						// next loop: rotate(left, n_first', last)
					} else {
						if (right_len == 1) {
							value_type t(kerbal::compatibility::to_xvalue(*n_first));
							kerbal::algorithm::move_backward(first, n_first, last);
							*first = kerbal::compatibility::to_xvalue(t);
							break;
						}
						while (n_first != first) {
							--n_first;
							--last;
							kerbal::algorithm::iter_swap(n_first, last);
						}
						left_len %= right_len;
						right_len -= left_len;
						n_first = first + left_len;
						// next loop: rotate(first, n_first', right)
					}
				}

				return ret;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		rotate(ForwardIterator first, ForwardIterator n_first, ForwardIterator last)
		{
			return kerbal::algorithm::detail::rotate(
				first, n_first, last,
				kerbal::iterator::iterator_category(first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_ROTATE_HPP
