/**
 * @file       unique.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_UNIQUE_HPP
#define KERBAL_ALGORITHM_MODIFIER_UNIQUE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last, BinaryPredict equal)
		{
			typedef ForwardIterator iterator;

			if (first == last) {
				return last;
			}

			iterator result(first);
			++first;
			while (first != last) {
				if (!static_cast<bool>(equal(*result, *first))) {
					++result;
					if (result != first) {
						kerbal::assign::generic_assign(*result, *first); //*result = *first;
					}
				}
				++first;
			}
			++result;
			return result;
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::unique(first, last, kerbal::compare::equal_to<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_UNIQUE_HPP
