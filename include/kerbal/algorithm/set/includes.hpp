/**
 * @file       includes.hpp
 * @brief
 * @date       2021-06-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SET_INCLUDES_HPP
#define KERBAL_ALGORITHM_SET_INCLUDES_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator1, typename InputIterator2, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		bool includes(InputIterator1 first1, InputIterator1 last1,
					  InputIterator2 first2, InputIterator2 last2, BinaryPredict cmp)
		{
			while (first2 != last2) {
				if (first1 != last1) {
					if (cmp(*first2, *first1)) { // *first2 < *first1
						return false;
					}
					// *first1 <= *first2
					if (!static_cast<bool>(cmp(*first1, *first2))) { // *first1 == *first2
						++first2;
					}
					++first1;
				} else {
					return false;
				}
			}
			return true;
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool includes(InputIterator1 first1, InputIterator1 last1,
					  InputIterator2 first2, InputIterator2 last2)
		{
			typedef InputIterator1 iterator1;
//			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			return kerbal::algorithm::includes(first1, last1, first2, last2, kerbal::compare::less<value_type1>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SET_INCLUDES_HPP
