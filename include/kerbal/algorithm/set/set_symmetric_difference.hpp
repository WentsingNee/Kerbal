/**
 * @file       set_symmetric_difference.hpp
 * @brief
 * @date       2021-06-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SET_SET_SYMMETRIC_DIFFERENCE_HPP
#define KERBAL_ALGORITHM_SET_SET_SYMMETRIC_DIFFERENCE_HPP

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
												InputIterator2 first2, InputIterator2 last2,
												OutputIterator d_first, BinaryPredict cmp)
		{
			while (first1 != last1) {
				if (first2 != last2) {
					if (cmp(*first1, *first2)) { // *first1 < *first2
						kerbal::assign::generic_assign(*d_first, *first1);
						++d_first;
						++first1;
					} else if (cmp(*first2, *first1)) { // *first2 < *first1
						kerbal::assign::generic_assign(*d_first, *first2);
						++d_first;
						++first2;
					} else { // *first1 == *first2
						++first1;
						++first2;
					}
				} else {
					return kerbal::algorithm::copy(first1, last1, d_first);
				}
			}
			return kerbal::algorithm::copy(first2, last2, d_first);
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
												InputIterator2 first2, InputIterator2 last2,
												OutputIterator d_first)
		{
			return kerbal::algorithm::set_symmetric_difference(first1, last1, first2, last2, d_first, kerbal::compare::binary_type_less<void, void>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SET_SET_SYMMETRIC_DIFFERENCE_HPP
