/**
 * @file       find_first_of.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FIND_FIRST_OF_HPP
#define KERBAL_ALGORITHM_QUERIER_FIND_FIRST_OF_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_first_of(
			InputIterator first, InputIterator last,
			ForwardIterator s_first, ForwardIterator s_last,
			BinaryPredicate pred
		)
		{
			while (first != last) {
				for (ForwardIterator it(s_first); it != s_last; ++it) {
					if (pred(*first, *it)) {
						return first;
					}
				}
				++first;
			}
			return first;
		}

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		InputIterator
		find_first_of(
			InputIterator first, InputIterator last,
			ForwardIterator s_first, ForwardIterator s_last
		)
		{
			typedef typename kerbal::iterator::iterator_traits<InputIterator>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type value_type2;

			return kerbal::algorithm::find_first_of(
				first, last, s_first, s_last,
				kerbal::compare::binary_type_equal_to<value_type1, value_type2>()
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_FIRST_OF_HPP
