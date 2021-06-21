/**
 * @file       mismatch.hpp
 * @brief
 * @date       2021-06-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_MISMATCH_HPP
#define KERBAL_ALGORITHM_QUERIER_MISMATCH_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <cstddef>
#include <utility> // std::pair


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator1, typename SentinelIterator1, typename InputIterator2, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<InputIterator1, InputIterator2>
		mismatch(InputIterator1 first1, SentinelIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			while (first1 != last1) {
				if (pred(*first1 , *first2)) {
					++first1;
					++first2;
				} else {
					break;
				}
			}
			return std::pair<InputIterator1, InputIterator2>(first1, first2);
		}

		template <typename InputIterator1, typename SentinelIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		std::pair<InputIterator1, InputIterator2>
		mismatch(InputIterator1 first1, SentinelIterator1 last1, InputIterator2 first2)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			typedef kerbal::compare::binary_type_equal_to<value_type1, value_type2> equal_to;

			return kerbal::algorithm::mismatch(first1, last1, first2, equal_to());
		}

		template <typename T, std::size_t N, typename InputIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				std::pair<T*, InputIterator>
		>::type
		mismatch(T (&a) [N], InputIterator first, BinaryPredicate pred)
		{
			return kerbal::algorithm::mismatch(kerbal::container::begin(a), kerbal::container::end(a), first, pred);
		}

		template <typename T, std::size_t N, typename InputIterator>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				std::pair<T*, InputIterator>
		>::type
		mismatch(T (&a) [N], InputIterator first)
		{
			typedef InputIterator iterator;
			typedef T value_type1;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type2;
			typedef kerbal::compare::binary_type_equal_to<value_type1, value_type2> equal_to;

			return kerbal::algorithm::mismatch(kerbal::container::begin(a), kerbal::container::end(a), first, equal_to());
		}

/*
		template <typename InputRange, typename InputIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_range<InputRange>::value,
				std::pair<typename kerbal::container::range_traits<InputRange>::iterator, InputIterator>
		>::type
		mismatch(InputRange & range, InputIterator first, BinaryPredicate pred)
		{
			return kerbal::algorithm::mismatch(kerbal::container::begin(range), kerbal::container::end(range), first, pred);
		}

		template <typename InputRange, typename InputIterator>
		KERBAL_CONSTEXPR14
		std::pair<typename kerbal::container::range_traits<InputRange>::iterator, InputIterator>
		mismatch(InputRange & range, InputIterator first)
		{
			typedef typename kerbal::container::range_traits<InputRange>::iterator iterator1;
			typedef InputIterator iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			typedef kerbal::compare::binary_type_equal_to<value_type1, value_type2> equal_to;

			return kerbal::algorithm::mismatch(kerbal::container::begin(range), kerbal::container::end(range), first, equal_to());
		}
*/




		template <typename InputIterator1, typename SentinelIterator1, typename InputIterator2, typename SentinelIterator2, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<InputIterator1, InputIterator2>
		mismatch2(InputIterator1 first1, SentinelIterator1 last1, InputIterator2 first2, SentinelIterator2 last2, BinaryPredicate pred)
		{
			while (first1 != last1) {
				if (first2 != last2) {
					if (pred(*first1, *first2)) {
						++first1;
						++first2;
					} else {
						break;
					}
				} else {
					break;
				}
			}
			return std::pair<InputIterator1, InputIterator2>(first1, first2);
		}

		template <typename InputIterator1, typename SentinelIterator1, typename InputIterator2, typename SentinelIterator2>
		KERBAL_CONSTEXPR14
		std::pair<InputIterator1, InputIterator2>
		mismatch2(InputIterator1 first1, SentinelIterator1 last1, InputIterator2 first2, SentinelIterator2 last2)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			typedef kerbal::compare::binary_type_equal_to<value_type1, value_type2> equal_to;

			return kerbal::algorithm::mismatch2(first1, last1, first2, last2, equal_to());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_MISMATCH_HPP
