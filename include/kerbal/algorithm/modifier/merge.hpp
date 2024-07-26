/**
 * @file       merge.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_MERGE_HPP
#define KERBAL_ALGORITHM_MODIFIER_MERGE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename CompareFuntion>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to, CompareFuntion cmp
		)
		{
			while (a_first != a_last) {
				if (b_first != b_last) {
					if (cmp(*b_first, *a_first)) { // b < a
						kerbal::assign::generic_assign(*to, *b_first); // *to = *b_first;
						++to; // advance `to` before `b_first` and `a_first`
						      // in case of the advance of `b_first` or `a_first` throws exception
						++b_first;
					} else { // b >= a
						kerbal::assign::generic_assign(*to, *a_first); // *to = *a_first;
						++to;
						++a_first;
					}
				} else {
					return kerbal::algorithm::copy(a_first, a_last, to);
				}
			}
			return kerbal::algorithm::copy(b_first, b_last, to);
		}

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to
		)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type type2;
			return kerbal::algorithm::merge(
				a_first, a_last,
				b_first, b_last,
				to,
				kerbal::compare::binary_type_less<type2, type1>()
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MERGE_HPP
