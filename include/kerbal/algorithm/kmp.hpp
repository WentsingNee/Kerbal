/**
 * @file       kmp.hpp
 * @brief
 * @date       2019-5-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_KMP_HPP_
#define KERBAL_ALGORITHM_KMP_HPP_

#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/general_back_inserter.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>

#include <vector>
#include <cstring>

namespace kerbal
{

	namespace algorithm
	{

		/**
		 * @brief Generate the next array.
		 *
		 * @param pattern_first    Begin iterator direct to pattern string.
		 * @param pattern_last     End iterator direct to pattern string.
		 * @param next_container   Array, vector, etc. stored the result.
		 * @param pattern_first    General back inserter of next_container
		 *                         (std::back_inserter(container) for STL compatible container,
		 *                          pointer direct to first element for C-array).
		 *
		 */
		template <typename ForwardIterator, typename NextContainer, typename EqualPredict, typename BackInsertIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__longest_matched_suffix_prefix(ForwardIterator pattern_first, ForwardIterator pattern_last,
				const NextContainer & next_container, EqualPredict equal_predict, BackInsertIterator back_inserter)
		{
			typedef ForwardIterator pattern_iterator;
			pattern_iterator i_pattern(pattern_first);
			*back_inserter = 0; ++back_inserter;
			if (i_pattern == pattern_last) {
				return pattern_last;
			}

			size_t k = 0; pattern_iterator k_pattern(pattern_first);
			*back_inserter = k; ++back_inserter;
			++i_pattern;

			while (i_pattern != pattern_last) {
				while (true) {
					if (equal_predict(*k_pattern, *i_pattern)) {
						++k; ++k_pattern;
						break;
					}
					if (k_pattern == pattern_first) {
						break;
					}
					k = next_container[k]; k_pattern = kerbal::iterator::next(pattern_first, k);
				}
				*back_inserter = k; ++back_inserter;
				++i_pattern;
			}
			return k_pattern;
		}

		template <typename ForwardIterator, typename NextContainer, typename EqualPredict>
		KERBAL_CONSTEXPR14
		ForwardIterator
		longest_matched_suffix_prefix(ForwardIterator pattern_first, ForwardIterator pattern_last,
				NextContainer & next_container, EqualPredict equal_predict)
		{
			return kerbal::algorithm::__longest_matched_suffix_prefix
					(pattern_first, pattern_last, next_container, equal_predict, kerbal::iterator::general_inserter(next_container));
		}

		template <typename ForwardIterator, typename NextContainer>
		KERBAL_CONSTEXPR14
		ForwardIterator
		longest_matched_suffix_prefix(ForwardIterator pattern_first, ForwardIterator pattern_last,
				NextContainer & next_container)
		{
			typedef ForwardIterator pattern_iterator;
			typedef typename kerbal::iterator::iterator_traits<pattern_iterator>::value_type Tp;
			return kerbal::algorithm::longest_matched_suffix_prefix
					(pattern_first, pattern_last, next_container, std::equal_to<Tp>());
		}


		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict, typename NextContainer>
		KERBAL_CONSTEXPR14
		BidirectionalHostIterator
		__kmp(BidirectionalHostIterator host_first, const BidirectionalHostIterator host_last,
			const ForwardPatternIterator pattern_first, const ForwardPatternIterator pattern_last,
			EqualPredict equal_predict, const NextContainer & lsp,
			std::bidirectional_iterator_tag /*host_iterator_type*/, std::forward_iterator_tag /*pattern_iterator_type*/)
		{
			typedef BidirectionalHostIterator host_iterator;
			typedef ForwardPatternIterator pattern_iterator;

			host_iterator it_host(host_first);
			pattern_iterator it_pattern(pattern_first); size_t j = 0;

			while (it_pattern != pattern_last) {
				if (it_host == host_last) {
					break;
				}
				if (equal_predict(*it_host, *it_pattern)) { // *i == *j
					++it_host;
					++it_pattern; ++j;
					continue;
				}
				if (it_pattern == pattern_first) {
					while (it_host != host_last) { // *i != *j
						if (equal_predict(*it_host, *it_pattern)) {
							break;
						}
						++it_host;
					}
					host_first = it_host;
				} else {
					kerbal::iterator::advance_at_most(host_first, j, host_last);
					j = lsp[j]; it_pattern = kerbal::iterator::next(pattern_first, j);
					host_first = kerbal::iterator::prev(it_host, j);
				}
			}

			return (it_pattern == pattern_last) ? host_first : host_last;
		}

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict, typename NextContainer>
		KERBAL_CONSTEXPR14
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last,
			EqualPredict equal_predict, const NextContainer & lsp)
		{
			return kerbal::algorithm::__kmp(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp,
					kerbal::iterator::iterator_category(host_first),
					kerbal::iterator::iterator_category(pattern_first));
		}

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict>
		BidirectionalHostIterator
		__kmp_lsp_buffer_agent(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last, EqualPredict equal_predict,
			std::forward_iterator_tag /*pattern_iterator_type*/)
		{
			typedef ForwardPatternIterator pattern_iterator;
			typedef typename kerbal::iterator::iterator_traits<pattern_iterator>::difference_type pattern_difference_type;
			pattern_difference_type pattern_length(kerbal::iterator::distance(pattern_first, pattern_last));
			if (pattern_length < 32) {
				size_t lsp[32];
				kerbal::algorithm::longest_matched_suffix_prefix(pattern_first, pattern_last, lsp, equal_predict);
				return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp);
			} else {
				std::vector<size_t> lsp;
				lsp.reserve(pattern_length);
				kerbal::algorithm::longest_matched_suffix_prefix(pattern_first, pattern_last, lsp, equal_predict);
				return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp);
			}
		}

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict>
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last, EqualPredict equal_predict)
		{
			return kerbal::algorithm::__kmp_lsp_buffer_agent(host_first, host_last,
					pattern_first, pattern_last, equal_predict, kerbal::iterator::iterator_category(pattern_first));
		}

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator>
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last)
		{
			typedef typename kerbal::iterator::iterator_traits<BidirectionalHostIterator>::value_type host_value_type;
			return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last,
					std::equal_to<host_value_type>());
		}

		inline const char* kmp(const char* host, const char* pattern)
		{
			return kerbal::algorithm::kmp(host, host + strlen(host), pattern, pattern + strlen(pattern));
		}


	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_KMP_HPP_ */
