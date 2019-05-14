/**
 * @file       kmp.hpp
 * @brief
 * @date       May 11 2019
 * @author     [WentsingNee](http://github.com/WentsingNee)
 * @copyright
 *      WentsingNee of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef INCLUDE_KERBAL_ALGORITHM_KMP_HPP_
#define INCLUDE_KERBAL_ALGORITHM_KMP_HPP_

#include <vector>
#include <cstring>
#include <kerbal/algorithm/iterator.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename ForwardIterator2, typename Compare, typename NextContainer>
		typename kerbal::type_traits::enable_if<
			kerbal::type_traits::is_same<
				typename kerbal::type_traits::remove_cv<typename NextContainer::value_type>::type,
				size_t
			>::value
		>::type
		kmp_next(ForwardIterator2 pattern_first, ForwardIterator2 pattern_last,
				Compare cmp, NextContainer & next_container)
		{
			if (pattern_first == pattern_last) {
				return;
			}

			typedef ForwardIterator2 pattern_iterator;
			pattern_iterator i_pattern = pattern_first;
			pattern_iterator k_pattern = pattern_first; size_t k = 0;
			next_container.push_back(0);
			next_container.push_back(0);
			++i_pattern;
			while (i_pattern != pattern_last) {
				if (cmp(*i_pattern, *k_pattern) == true) {
					// A B C A B C D
					//     ^     ^
					//     k     i
					next_container.push_back(next_container.back() + 1);
					++k_pattern; ++k;
				} else {
					if (next_container[k] == 0) {
						next_container.push_back(0);
					} else {
						k = next_container[k] - 1; k_pattern = kerbal::algorithm::next(pattern_first, k);
						next_container.push_back(k);
					}
				}
				++i_pattern;
			}
		}

		template <typename BidirectionalIterator1, typename ForwardIterator2, typename Compare, typename NextContainer>
		typename kerbal::type_traits::enable_if<
			kerbal::type_traits::is_same<
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<BidirectionalIterator1>::value_type>::type,
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<ForwardIterator2>::value_type>::type
			>::value
			&&
			kerbal::type_traits::is_same<
				typename kerbal::type_traits::remove_cv<typename NextContainer::value_type>::type,
				size_t
			>::value
		, BidirectionalIterator1>::type
		kmp(BidirectionalIterator1 host_first, BidirectionalIterator1 host_last,
				ForwardIterator2 pattern_first, ForwardIterator2 pattern_last,
			Compare cmp, const NextContainer & next_container)
		{
			typedef BidirectionalIterator1 host_iterator;
			typedef ForwardIterator2 pattern_iterator;

			if (pattern_first == pattern_last) {
				return host_last;
			}

			host_iterator it_host = host_first;
			pattern_iterator it_pattern = pattern_first; size_t j = 0;

			while (it_host != host_last && it_pattern != pattern_last) {
				if (cmp(*it_host, *it_pattern)) { // *i == *j
					++it_host;
					++it_pattern; ++j;
				} else {
					if (it_pattern == pattern_first) {
						++it_host;
						++host_first;
					} else {
						j = next_container[j]; it_pattern = kerbal::algorithm::next(pattern_first, j);
						host_first = kerbal::algorithm::prev(it_host, j);
					}
				}
			}

			if (it_pattern == pattern_last) {
				return host_first;
			} else {
				return host_last;
			}
		}


		template <typename BidirectionalIterator1, typename ForwardIterator2, typename Compare>
		typename kerbal::type_traits::enable_if<
			kerbal::type_traits::is_same<
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<BidirectionalIterator1>::value_type>::type,
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<ForwardIterator2>::value_type>::type
			>::value
		, BidirectionalIterator1>::type
		kmp(BidirectionalIterator1 host_first, BidirectionalIterator1 host_last,
			ForwardIterator2 pattern_first, ForwardIterator2 pattern_last, Compare cmp)
		{
			std::vector<size_t> v;
			kmp_next(pattern_first, pattern_last, cmp, v);
			return kmp(host_first, host_last, pattern_first, pattern_last, cmp, v);
		}

		template <typename BidirectionalIterator1, typename ForwardIterator2>
		typename kerbal::type_traits::enable_if<
			kerbal::type_traits::is_same<
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<BidirectionalIterator1>::value_type>::type,
				typename kerbal::type_traits::remove_cv<typename std::iterator_traits<ForwardIterator2>::value_type>::type
			>::value
		, BidirectionalIterator1>::type
		kmp(BidirectionalIterator1 host_first, BidirectionalIterator1 host_last, ForwardIterator2 pattern_first, ForwardIterator2 pattern_last)
		{
			typedef typename std::iterator_traits<BidirectionalIterator1>::value_type host_value_type;
			return kmp(host_first, host_last, pattern_first, pattern_last,
					std::equal_to<host_value_type>());
		}

		const char* kmp(const char* host, const char* pattern)
		{
			return kmp(host, host + strlen(host), pattern, pattern + strlen(pattern));
		}


	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_ALGORITHM_KMP_HPP_ */
