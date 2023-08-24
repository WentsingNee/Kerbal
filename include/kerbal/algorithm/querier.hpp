/**
 * @file       querier.hpp
 * @brief
 * @date       2019-9-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_HPP
#define KERBAL_ALGORITHM_QUERIER_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <cstddef>
#include <utility> // std::pair


#include <kerbal/algorithm/querier/adjacent_find.hpp>
#include <kerbal/algorithm/querier/all_of.hpp>
#include <kerbal/algorithm/querier/any_of.hpp>
#include <kerbal/algorithm/querier/count.hpp>
#include <kerbal/algorithm/querier/count_if.hpp>
#include <kerbal/algorithm/querier/find.hpp>
#include <kerbal/algorithm/querier/find_first_of.hpp>
#include <kerbal/algorithm/querier/find_if.hpp>
#include <kerbal/algorithm/querier/find_if_not.hpp>
#include <kerbal/algorithm/querier/for_each.hpp>
#include <kerbal/algorithm/querier/none_of.hpp>
#include <kerbal/algorithm/querier/rfor_each.hpp>


namespace kerbal
{

	namespace algorithm
	{


		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator __better_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;

			iterator selected(first);
			if (first != last) {
				++first;
				while (first != last) {
					if (pred(*first, *selected)) {
						selected = first;
					}
					++first;
				}
			}
			return selected;
		}

		template <typename RandomAccessIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		RandomAccessIterator __better_element(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			iterator selected(first);
			if (first != last) {
				++first;

#	define EACH() do {\
					if (pred(*first, *selected)) {\
						selected = first;\
					}\
					++first;\
				} while (false)

				difference_type trip_count(kerbal::iterator::distance(first, last));
				difference_type remain(trip_count & 3);
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
			return selected;
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__better_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::min_element(first, last, kerbal::compare::less<value_type>());
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__better_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::max_element(first, last, kerbal::compare::greater<value_type>());
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		__minmax_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;

			iterator mini(first);
			iterator maxi(first);
			if (first != last) {
				++first;
				while (first != last) {
					if (pred(*first, *mini)) { // *first < *mini
						mini = first;
					} else if (!static_cast<bool>(pred(*first, *maxi))) { // *first >= *maxi
						maxi = first;
					}
					++first;
				}
			}
			return std::make_pair(mini, maxi);
		}

		template <typename RandomAccessIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<RandomAccessIterator, RandomAccessIterator>
		__minmax_element(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			iterator mini(first);
			iterator maxi(first);
			if (first != last) {
				++first;

#	define EACH() do {\
					if (pred(*first, *mini)) {\
						mini = first;\
					} else if (!static_cast<bool>(pred(*first, *maxi))) {\
						maxi = first;\
					}\
					++first;\
				} while (false)

				difference_type trip_count(kerbal::iterator::distance(first, last));
				difference_type remain(trip_count & 3);
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
			return std::make_pair(mini, maxi);
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__minmax_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::minmax_element(first, last, kerbal::compare::less<value_type>());
		}

	} //namespace algorithm

} //namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_HPP
