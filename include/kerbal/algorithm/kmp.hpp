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

#ifndef KERBAL_ALGORITHM_KMP_HPP
#define KERBAL_ALGORITHM_KMP_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/general_back_inserter.hpp>

#include <cstring>
#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
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
			longest_matched_suffix_prefix_helper(ForwardIterator pattern_first, ForwardIterator pattern_last,
					const NextContainer & next_container, EqualPredict equal_predict, BackInsertIterator back_inserter)
			{
				typedef ForwardIterator pattern_iterator;
				pattern_iterator i_pattern(pattern_first);
				*back_inserter = 0; ++back_inserter;
				if (i_pattern == pattern_last) {
					return pattern_last;
				}

				std::size_t k = 0; pattern_iterator k_pattern(pattern_first);
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

		} // namespace detail

		template <typename ForwardIterator, typename NextContainer, typename EqualPredict>
		KERBAL_CONSTEXPR14
		ForwardIterator
		longest_matched_suffix_prefix(ForwardIterator pattern_first, ForwardIterator pattern_last,
				NextContainer & next_container, EqualPredict equal_predict)
		{
			return kerbal::algorithm::detail::longest_matched_suffix_prefix_helper
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
					(pattern_first, pattern_last, next_container, kerbal::compare::equal_to<Tp>());
		}


		namespace detail
		{

			template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict, typename NextContainer>
			KERBAL_CONSTEXPR14
			BidirectionalHostIterator
			kmp_helper(BidirectionalHostIterator host_first, const BidirectionalHostIterator host_last,
				const ForwardPatternIterator pattern_first, const ForwardPatternIterator pattern_last,
				EqualPredict equal_predict, const NextContainer & lsp,
				std::bidirectional_iterator_tag /*host_iterator_type*/, std::forward_iterator_tag /*pattern_iterator_type*/)
			{
				typedef BidirectionalHostIterator host_iterator;
				typedef ForwardPatternIterator pattern_iterator;

				host_iterator it_host(host_first);
				pattern_iterator it_pattern(pattern_first); std::size_t j = 0;

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

		} // namespace detail

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict, typename NextContainer>
		KERBAL_CONSTEXPR14
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last,
			EqualPredict equal_predict, const NextContainer & lsp)
		{
			return kerbal::algorithm::detail::kmp_helper(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp,
					kerbal::iterator::iterator_category(host_first),
					kerbal::iterator::iterator_category(pattern_first));
		}

		namespace detail
		{

			template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict>
			BidirectionalHostIterator
			kmp_lsp_buffer_agent(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
				ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last, EqualPredict equal_predict,
				std::forward_iterator_tag /*pattern_iterator_type*/)
			{
				typedef ForwardPatternIterator pattern_iterator;
				typedef typename kerbal::iterator::iterator_traits<pattern_iterator>::difference_type pattern_difference_type;
				pattern_difference_type pattern_length(kerbal::iterator::distance(pattern_first, pattern_last));
				if (pattern_length < 32) {
					std::size_t lsp[32];
					kerbal::algorithm::longest_matched_suffix_prefix(pattern_first, pattern_last, lsp, equal_predict);
					return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp);
				} else {
					kerbal::container::vector<std::size_t> lsp;
					lsp.reserve(pattern_length);
					kerbal::algorithm::longest_matched_suffix_prefix(pattern_first, pattern_last, lsp, equal_predict);
					return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last, equal_predict, lsp);
				}
			}

		} // namespace detail

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator, typename EqualPredict>
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last, EqualPredict equal_predict)
		{
			return kerbal::algorithm::detail::kmp_lsp_buffer_agent(host_first, host_last,
					pattern_first, pattern_last, equal_predict, kerbal::iterator::iterator_category(pattern_first));
		}

		template <typename BidirectionalHostIterator, typename ForwardPatternIterator>
		BidirectionalHostIterator
		kmp(BidirectionalHostIterator host_first, BidirectionalHostIterator host_last,
			ForwardPatternIterator pattern_first, ForwardPatternIterator pattern_last)
		{
			typedef typename kerbal::iterator::iterator_traits<BidirectionalHostIterator>::value_type host_value_type;
			return kerbal::algorithm::kmp(host_first, host_last, pattern_first, pattern_last,
					kerbal::compare::equal_to<host_value_type>());
		}

		inline const char* kmp(const char* host, const char* pattern)
		{
			return kerbal::algorithm::kmp(host, host + std::strlen(host), pattern, pattern + std::strlen(pattern));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_KMP_HPP
