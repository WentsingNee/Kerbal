/**
 * @file       mismatch_with_distance.hpp
 * @brief
 * @date       2021-06-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_MISMATCH_WITH_DISTANCE_HPP
#define KERBAL_ALGORITHM_QUERIER_MISMATCH_WITH_DISTANCE_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>
#include <utility> // std::pair


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator1, typename InputIterator2>
		struct mismatch_with_distance_result_t
		{
				InputIterator1 mismatch_point1;
				InputIterator2 mismatch_point2;
				std::size_t dist;

				KERBAL_CONSTEXPR
				mismatch_with_distance_result_t(
					InputIterator1 mismatch_point1,
					InputIterator2 mismatch_point2,
					std::size_t dist
				) :
					mismatch_point1(mismatch_point1),
					mismatch_point2(mismatch_point2),
					dist(dist)
				{
				}
		};

		namespace detail
		{

			template <
				typename InputIterator1, typename SentinelIterator1,
				typename InputIterator2,
				typename BinaryPredicate
			>
			KERBAL_CONSTEXPR14
			mismatch_with_distance_result_t<InputIterator1, InputIterator2>
			k_mismatch_with_distance(
				InputIterator1 first1, SentinelIterator1 last1,
				InputIterator2 first2, BinaryPredicate predicate,
				std::input_iterator_tag
			)
			{
				std::size_t dist = 0;
				while (first1 != last1) {
					if (predicate(*first1 , *first2)) {
						++first1;
						++first2;
						++dist;
					} else {
						break;
					}
				}
				return kerbal::algorithm::mismatch_with_distance_result_t<InputIterator1, InputIterator2>(
					first1, first2,
					dist
				);
			}

			template <
				typename InputIterator1, typename SentinelIterator1,
				typename InputIterator2,
				typename BinaryPredicate
			>
			KERBAL_CONSTEXPR14
			mismatch_with_distance_result_t<InputIterator1, InputIterator2>
			k_mismatch_with_distance(
				InputIterator1 first1, SentinelIterator1 last1,
				InputIterator2 first2,
				BinaryPredicate predicate,
				std::random_access_iterator_tag
			)
			{
				InputIterator1 it(first1);
				while (it != last1) {
					if (predicate(*it , *first2)) {
						++it;
						++first2;
					} else {
						break;
					}
				}
				return kerbal::algorithm::mismatch_with_distance_result_t<InputIterator1, InputIterator2>(
					it, first2,
					kerbal::iterator::distance(first1, it)
				);
			}

		} // namespace detail

		template <
			typename InputIterator1, typename SentinelIterator1,
			typename InputIterator2,
			typename BinaryPredicate
		>
		KERBAL_CONSTEXPR14
		mismatch_with_distance_result_t<InputIterator1, InputIterator2>
		mismatch_with_distance(
			InputIterator1 first1, SentinelIterator1 last1,
			InputIterator2 first2,
			BinaryPredicate pred
		)
		{
			return kerbal::algorithm::detail::k_mismatch_with_distance(
				first1, last1,
				first2,
				pred,
				kerbal::iterator::iterator_category(first1)
			);
		}

		template <typename InputIterator1, typename SentinelIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		mismatch_with_distance_result_t<InputIterator1, InputIterator2>
		mismatch_with_distance(InputIterator1 first1, SentinelIterator1 last1, InputIterator2 first2)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			typedef kerbal::compare::binary_type_equal_to<value_type1, value_type2> equal_to;

			return kerbal::algorithm::mismatch_with_distance(first1, last1, first2, equal_to());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_MISMATCH_WITH_DISTANCE_HPP
